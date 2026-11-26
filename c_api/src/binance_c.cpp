//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <exception>
#include <fstream>
#include <functional>
#include <limits>
#include <memory>
#include <mutex>
#include <new>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

#include <boost/asio/bind_cancellation_slot.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/verify_context.hpp>
#include <boost/asio/strand.hpp>
#include <boost/json.hpp>
#include <boost/json/basic_parser_impl.hpp>
#include <boost/json/value_stack.hpp>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>

#include <binance/binance_c.h>
#include <binance/common/decimal.hpp>
#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/logger.hpp>
#include <binance/common/rest.hpp>
#include <binance/common/version.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/common/websocket_streams.hpp>

namespace json = boost::json;
namespace common = binance::common;

namespace {

std::atomic<std::uint32_t> g_threads{2};

/// Logs an exception that a handler or callback let escape. Never throws, not even for lack of
/// memory: it runs where an exception would end the process.
void log_escaped(const char* who, const std::exception_ptr& ep) noexcept {
    try {
        std::string what = "unknown exception";
        try {
            std::rethrow_exception(ep);
        } catch (const std::exception& e) {
            what = e.what();
        } catch (...) { // NOLINT(bugprone-empty-catch): `what` says it is unknown
        }
        common::Logger::error(std::string(who) + " threw: " + what);
    } catch (...) { // NOLINT(bugprone-empty-catch): nothing is left to report it with
    }
}

/// Whether this thread is one of the I/O pool's, i.e. runs a library callback.
thread_local bool t_pool_thread = false;

/// The I/O threads shared by every client. Never destroyed: clients may outlive static
/// destruction in the host process.
class IoPool {
public:
    static IoPool& instance() {
        static IoPool* pool = new IoPool(std::max<std::uint32_t>(g_threads.load(), 1));
        return *pool;
    }

    [[nodiscard]] boost::asio::any_io_executor executor() { return ioc_.get_executor(); }

private:
    explicit IoPool(std::uint32_t threads) : guard_(boost::asio::make_work_guard(ioc_)) {
        for (std::uint32_t i = 0; i < threads; ++i) {
            threads_.emplace_back([this] { run(); }).detach();
        }
    }

    /// An exception escaping a handler must not reach the thread function: that would end the
    /// host process. The pool logs it and goes on serving the other clients.
    void run() noexcept {
        t_pool_thread = true;
        for (;;) {
            try {
                ioc_.run();
                return;
            } catch (...) {
                log_escaped("A completion handler", std::current_exception());
            }
        }
    }

    boost::asio::io_context ioc_;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> guard_;
    std::vector<std::thread> threads_;
};

// ---- ABI ---------------------------------------------------------------------------------

// Bindings declare these layouts themselves (e.g. C# structs), so they must not change silently:
// with a compiler option (-fshort-enums, packing) or on a platform that aligns differently.
static_assert(sizeof(bnc_log_level) == 4 && sizeof(bnc_error_kind) == 4 &&
                  sizeof(bnc_ws_error_kind) == 4 && sizeof(bnc_event_type) == 4,
              "the enums of binance_c.h must be 32-bit");
static_assert(sizeof(bnc_error) == 600);
static_assert(offsetof(bnc_error, kind) == 0 && offsetof(bnc_error, http_status) == 4 &&
              offsetof(bnc_error, has_code) == 8 && offsetof(bnc_error, reserved0) == 12 &&
              offsetof(bnc_error, code) == 16 && offsetof(bnc_error, retry_after_seconds) == 24 &&
              offsetof(bnc_error, retry_at_ms) == 32 && offsetof(bnc_error, transport_code) == 40 &&
              offsetof(bnc_error, transport_category) == 44 &&
              offsetof(bnc_error, request_sent) == 76 && offsetof(bnc_error, message) == 80 &&
              offsetof(bnc_error, ws_kind) == 592 && offsetof(bnc_error, reserved1) == 596);
constexpr std::size_t kPtr = sizeof(void*);
static_assert(sizeof(std::size_t) == kPtr && sizeof(bnc_tls_verify_callback) == kPtr);
static_assert(sizeof(bnc_rest_response) == 5 * kPtr && offsetof(bnc_rest_response, body) == kPtr &&
              offsetof(bnc_rest_response, body_len) == 2 * kPtr &&
              offsetof(bnc_rest_response, headers_json) == 3 * kPtr &&
              offsetof(bnc_rest_response, rate_limits_json) == 4 * kPtr);
static_assert(sizeof(bnc_client_options) == 5 * kPtr &&
              offsetof(bnc_client_options, tls_verify) == kPtr &&
              offsetof(bnc_client_options, tls_verify_data) == 2 * kPtr &&
              offsetof(bnc_client_options, timestamp) == 3 * kPtr &&
              offsetof(bnc_client_options, timestamp_data) == 4 * kPtr);

// The enums are converted with static_cast.
static_assert(static_cast<int>(common::LogLevel::Debug) == BNC_LOG_DEBUG &&
              static_cast<int>(common::LogLevel::Info) == BNC_LOG_INFO &&
              static_cast<int>(common::LogLevel::Warn) == BNC_LOG_WARN &&
              static_cast<int>(common::LogLevel::Error) == BNC_LOG_ERROR &&
              static_cast<int>(common::LogLevel::None) == BNC_LOG_NONE);
static_assert(static_cast<int>(common::WebsocketEventType::Open) == BNC_EVENT_OPEN &&
              static_cast<int>(common::WebsocketEventType::Message) == BNC_EVENT_MESSAGE &&
              static_cast<int>(common::WebsocketEventType::Error) == BNC_EVENT_ERROR &&
              static_cast<int>(common::WebsocketEventType::Close) == BNC_EVENT_CLOSE &&
              static_cast<int>(common::WebsocketEventType::Ping) == BNC_EVENT_PING &&
              static_cast<int>(common::WebsocketEventType::Pong) == BNC_EVENT_PONG);

/// Runs a caller's callback, keeping an exception from unwinding into the I/O code that called it.
/// Only a safety net: callbacks must not throw (binance_c.h), and one thrown by code using another
/// C++ runtime than the library's own (the usual case) cannot be caught here at all.
template <class F> void call_out(const char* who, F&& f) noexcept {
    try {
        f();
    } catch (...) {
        log_escaped(who, std::current_exception());
    }
}

// ---- errors ------------------------------------------------------------------------------

void copy_text(char* dst, std::size_t size, std::string_view text) noexcept {
    const auto n = std::min(text.size(), size - 1);
    std::memcpy(dst, text.data(), n);
    dst[n] = '\0';
}

void set_transport(bnc_error& out, const boost::system::error_code& ec) {
    out.transport_code = ec.value();
    copy_text(out.transport_category, sizeof out.transport_category,
              ec ? ec.category().name() : "");
}

void set_connector(bnc_error& out, const common::ConnectorError& e) {
    if (const auto* response = e.response()) {
        out.http_status = response->status;
    }
    if (const auto retry = e.retry_after()) {
        out.retry_after_seconds = retry->count();
    }
}

bnc_ws_error_kind websocket_kind(const common::WebsocketError& e) {
    if (dynamic_cast<const common::WebsocketTimeoutError*>(&e) != nullptr) {
        return BNC_WS_TIMEOUT;
    }
    if (dynamic_cast<const common::WebsocketNotConnectedError*>(&e) != nullptr) {
        return BNC_WS_NOT_CONNECTED;
    }
    if (dynamic_cast<const common::WebsocketNoResponseError*>(&e) != nullptr) {
        return BNC_WS_NO_RESPONSE;
    }
    if (dynamic_cast<const common::WebsocketResponseError*>(&e) != nullptr) {
        return BNC_WS_RESPONSE_ERROR;
    }
    if (dynamic_cast<const common::WebsocketHandshakeError*>(&e) != nullptr) {
        return BNC_WS_HANDSHAKE;
    }
    if (dynamic_cast<const common::WebsocketProtocolError*>(&e) != nullptr) {
        return BNC_WS_PROTOCOL;
    }
    if (dynamic_cast<const common::WebsocketServerError*>(&e) != nullptr) {
        return BNC_WS_SERVER;
    }
    if (dynamic_cast<const common::WebsocketNetworkError*>(&e) != nullptr) {
        return BNC_WS_NETWORK;
    }
    if (dynamic_cast<const common::WebsocketCancelledError*>(&e) != nullptr) {
        return BNC_WS_CANCELLED;
    }
    return BNC_WS_OTHER;
}

void describe(const std::exception_ptr& ep, bnc_error* error) noexcept {
    if (error == nullptr) {
        return;
    }
    *error = {};
    error->retry_after_seconds = -1;
    error->retry_at_ms = -1;
    try {
        std::rethrow_exception(ep);
    } catch (const common::RateLimitBanError& e) {
        error->kind = BNC_ERROR_RATE_LIMIT_BAN;
        set_connector(*error, e);
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::TooManyRequestsError& e) {
        error->kind = BNC_ERROR_TOO_MANY_REQUESTS;
        set_connector(*error, e);
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::BadRequestError& e) {
        error->kind = BNC_ERROR_BAD_REQUEST;
        set_connector(*error, e);
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::UnauthorizedError& e) {
        error->kind = BNC_ERROR_UNAUTHORIZED;
        set_connector(*error, e);
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::ForbiddenError& e) {
        error->kind = BNC_ERROR_FORBIDDEN;
        set_connector(*error, e);
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::NotFoundError& e) {
        error->kind = BNC_ERROR_NOT_FOUND;
        set_connector(*error, e);
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::ConflictError& e) {
        error->kind = BNC_ERROR_CONFLICT;
        set_connector(*error, e);
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::ServerError& e) {
        error->kind = BNC_ERROR_SERVER;
        set_connector(*error, e);
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::NetworkError& e) {
        error->kind =
            dynamic_cast<const common::RequestCancelledError*>(&e) != nullptr ? BNC_ERROR_CANCELLED
            : dynamic_cast<const common::RequestTimeoutError*>(&e) != nullptr ? BNC_ERROR_TIMEOUT
                                                                              : BNC_ERROR_NETWORK;
        error->request_sent = e.request_sent();
        set_transport(*error, e.transport_error());
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::ConnectorError& e) {
        error->kind = BNC_ERROR_CLIENT;
        set_connector(*error, e);
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::ConfigError& e) {
        error->kind = BNC_ERROR_CONFIG;
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const common::WebsocketError& e) {
        error->kind = dynamic_cast<const common::WebsocketCancelledError*>(&e) != nullptr
                          ? BNC_ERROR_CANCELLED
                      : dynamic_cast<const common::WebsocketTimeoutError*>(&e) != nullptr
                          ? BNC_ERROR_TIMEOUT
                          : BNC_ERROR_WEBSOCKET;
        error->request_sent = e.request_sent();
        error->ws_kind = websocket_kind(e);
        if (const auto* net = dynamic_cast<const common::WebsocketNetworkError*>(&e)) {
            error->kind = BNC_ERROR_NETWORK;
            set_transport(*error, net->transport_error());
        } else if (const auto* handshake =
                       dynamic_cast<const common::WebsocketHandshakeError*>(&e)) {
            error->http_status = handshake->status();
            if (const auto retry = handshake->retry_after()) {
                error->retry_after_seconds = retry->count();
            }
        } else if (const auto* response = dynamic_cast<const common::WebsocketResponseError*>(&e)) {
            error->http_status = response->status();
            if (const auto retry_at = response->retry_at()) {
                error->retry_at_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                                         retry_at->time_since_epoch())
                                         .count();
            }
        }
        copy_text(error->message, sizeof error->message, e.what());
    } catch (const std::exception& e) {
        error->kind = BNC_ERROR_INTERNAL;
        copy_text(error->message, sizeof error->message, e.what());
    } catch (...) {
        error->kind = BNC_ERROR_INTERNAL;
        copy_text(error->message, sizeof error->message, "unknown error");
    }
    if (const auto* base = [&]() -> const common::Error* {
            try {
                std::rethrow_exception(ep);
            } catch (const common::Error& e) {
                return &e;
            } catch (...) {
                return nullptr;
            }
        }()) {
        if (const auto code = base->code()) {
            error->has_code = 1;
            error->code = *code;
        }
    }
    // The server answered, so the request reached it.
    if (error->http_status != 0) {
        error->request_sent = 1;
    }
}

template <class F> int32_t guarded(bnc_error* error, F&& f) noexcept {
    try {
        f();
        return 0;
    } catch (...) {
        describe(std::current_exception(), error);
        return -1;
    }
}

// ---- JSON configuration ------------------------------------------------------------------

/// Builds the value of a caller's JSON. An integer that fits in 64 bits stays a number; any other
/// number becomes the `Decimal` of its text, a JSON string, as the C++ API sends a `Decimal`: a
/// price written 0.1 is sent as "0.1", never as the double nearest to it.
class ExactNumbers {
public:
    static constexpr std::size_t max_object_size = static_cast<std::size_t>(-1);
    static constexpr std::size_t max_array_size = static_cast<std::size_t>(-1);
    static constexpr std::size_t max_key_size = static_cast<std::size_t>(-1);
    static constexpr std::size_t max_string_size = static_cast<std::size_t>(-1);

    json::value release() { return stack_.release(); }

    bool on_document_begin(boost::system::error_code& /*ec*/) {
        stack_.reset();
        return true;
    }
    bool on_document_end(boost::system::error_code& /*ec*/) { return true; }
    bool on_object_begin(boost::system::error_code& /*ec*/) { return true; }
    bool on_object_end(std::size_t n, boost::system::error_code& /*ec*/) {
        stack_.push_object(n);
        return true;
    }
    bool on_array_begin(boost::system::error_code& /*ec*/) { return true; }
    bool on_array_end(std::size_t n, boost::system::error_code& /*ec*/) {
        stack_.push_array(n);
        return true;
    }
    bool on_key_part(json::string_view s, std::size_t /*n*/, boost::system::error_code& /*ec*/) {
        stack_.push_chars(s);
        return true;
    }
    bool on_key(json::string_view s, std::size_t /*n*/, boost::system::error_code& /*ec*/) {
        stack_.push_key(s);
        return true;
    }
    bool on_string_part(json::string_view s, std::size_t /*n*/, boost::system::error_code& /*ec*/) {
        stack_.push_chars(s);
        return true;
    }
    bool on_string(json::string_view s, std::size_t /*n*/, boost::system::error_code& /*ec*/) {
        stack_.push_string(s);
        return true;
    }
    bool on_number_part(json::string_view s, boost::system::error_code& /*ec*/) {
        number_.append(s.data(), s.size());
        return true;
    }
    bool on_int64(std::int64_t i, json::string_view /*s*/, boost::system::error_code& /*ec*/) {
        number_.clear();
        stack_.push_int64(i);
        return true;
    }
    bool on_uint64(std::uint64_t u, json::string_view /*s*/, boost::system::error_code& /*ec*/) {
        number_.clear();
        stack_.push_uint64(u);
        return true;
    }
    bool on_double(double /*d*/, json::string_view s, boost::system::error_code& /*ec*/) {
        number_.append(s.data(), s.size());
        const common::Decimal exact(number_); // a JSON number token always is a valid decimal
        number_.clear();
        stack_.push_string(exact.str());
        return true;
    }
    bool on_bool(bool b, boost::system::error_code& /*ec*/) {
        stack_.push_bool(b);
        return true;
    }
    bool on_null(boost::system::error_code& /*ec*/) {
        stack_.push_null();
        return true;
    }
    bool on_comment_part(json::string_view /*s*/, boost::system::error_code& /*ec*/) {
        return true;
    }
    bool on_comment(json::string_view /*s*/, boost::system::error_code& /*ec*/) { return true; }

private:
    json::value_stack stack_;
    std::string number_;
};

/// Parses a caller's JSON with `ExactNumbers`; throws `boost::system::system_error` for invalid
/// JSON and `std::invalid_argument` for a number `Decimal` refuses (exponent beyond ±1000).
json::value parse_exact(std::string_view text) {
    json::basic_parser<ExactNumbers> parser{json::parse_options{}};
    boost::system::error_code ec;
    const auto used = parser.write_some(false, text.data(), text.size(), ec);
    if (!ec && used < text.size()) {
        ec = json::error::extra_data;
    }
    if (ec) {
        throw boost::system::system_error(ec);
    }
    return parser.handler().release();
}

json::object parse_object(const char* text, const char* what) {
    if (text == nullptr) {
        throw common::ConfigError(std::string(what) + " is missing");
    }
    try {
        auto value = parse_exact(text);
        if (!value.is_object()) {
            throw common::ConfigError(std::string(what) + " must be a JSON object");
        }
        return std::move(value.as_object());
    } catch (const common::ConfigError&) {
        throw;
    } catch (const std::exception& e) {
        throw common::ConfigError(std::string(what) + " is not valid JSON: " + e.what());
    }
}

const json::value* find(const json::object& o, const char* key) {
    const auto it = o.find(key);
    return it == o.end() || it->value().is_null() ? nullptr : &it->value();
}

std::optional<std::string> get_string(const json::object& o, const char* key) {
    const auto* v = find(o, key);
    if (v == nullptr) {
        return std::nullopt;
    }
    if (!v->is_string()) {
        throw common::ConfigError(std::string("'") + key + "' must be a string");
    }
    return std::string(v->as_string());
}

std::optional<std::int64_t> get_int(const json::object& o, const char* key) {
    const auto* v = find(o, key);
    if (v == nullptr) {
        return std::nullopt;
    }
    if (!v->is_int64() && !v->is_uint64()) {
        throw common::ConfigError(std::string("'") + key + "' must be an integer");
    }
    if (v->is_uint64() && v->get_uint64() > std::numeric_limits<std::uint64_t>::max() / 2) {
        throw common::ConfigError(std::string("'") + key + "' is out of range");
    }
    return v->to_number<std::int64_t>();
}

/// An integer in [`min`, `max`], converted to `T`: a negative count or an oversized port is an
/// error, not a value that wraps around.
template <class T>
std::optional<T> get_int_in(const json::object& o, const char* key, std::int64_t min, T max) {
    const auto value = get_int(o, key);
    if (!value) {
        return std::nullopt;
    }
    constexpr auto kInt64Max = std::numeric_limits<std::int64_t>::max();
    const auto upper = static_cast<std::uint64_t>(max) > static_cast<std::uint64_t>(kInt64Max)
                           ? kInt64Max
                           : static_cast<std::int64_t>(max);
    if (*value < min || *value > upper) {
        throw common::ConfigError(std::string("'") + key + "' must be between " +
                                  std::to_string(min) + " and " + std::to_string(upper));
    }
    return static_cast<T>(*value);
}

std::optional<bool> get_bool(const json::object& o, const char* key) {
    const auto* v = find(o, key);
    if (v == nullptr) {
        return std::nullopt;
    }
    if (!v->is_bool()) {
        throw common::ConfigError(std::string("'") + key + "' must be a boolean");
    }
    return v->as_bool();
}

const json::object* get_object(const json::object& o, const char* key) {
    const auto* v = find(o, key);
    if (v == nullptr) {
        return nullptr;
    }
    if (!v->is_object()) {
        throw common::ConfigError(std::string("'") + key + "' must be an object");
    }
    return &v->as_object();
}

std::map<std::string, std::string> get_string_map(const json::object& o, const char* key) {
    std::map<std::string, std::string> out;
    if (const auto* map = get_object(o, key)) {
        for (const auto& [name, value] : *map) {
            if (!value.is_string()) {
                throw common::ConfigError(std::string("'") + key + "' values must be strings");
            }
            out.emplace(std::string(name), std::string(value.as_string()));
        }
    }
    return out;
}

std::optional<common::ProxyConfig> get_proxy(const json::object& o) {
    const auto* p = get_object(o, "proxy");
    if (p == nullptr) {
        return std::nullopt;
    }
    common::ProxyConfig proxy;
    proxy.host = get_string(*p, "host").value_or("");
    proxy.port = get_int_in<std::uint16_t>(*p, "port", 1, 65535).value_or(0);
    if (proxy.host.empty() || proxy.port == 0) {
        throw common::ConfigError("'proxy' needs a host and a port");
    }
    if (const auto protocol = get_string(*p, "protocol")) {
        if (*protocol == "https") {
            proxy.protocol = common::ProxyProtocol::Https;
        } else if (*protocol == "socks5") {
            proxy.protocol = common::ProxyProtocol::Socks5;
        } else if (*protocol == "socks5h") {
            proxy.protocol = common::ProxyProtocol::Socks5h;
        } else if (*protocol != "http") {
            throw common::ConfigError(
                "'proxy.protocol' must be \"http\", \"https\", \"socks5\" or \"socks5h\"");
        }
    }
    if (const auto user = get_string(*p, "username")) {
        proxy.auth = common::ProxyAuth{*user, get_string(*p, "password").value_or("")};
    }
    return proxy;
}

std::optional<common::PrivateKey> get_private_key(const json::object& o) {
    if (const auto pem = get_string(o, "private_key_pem")) {
        return common::PrivateKey::from_pem(*pem);
    }
    if (const auto file = get_string(o, "private_key_file")) {
        return common::PrivateKey::from_file(*file);
    }
    return std::nullopt;
}

std::chrono::milliseconds get_ms(const json::object& o, const char* key,
                                 std::chrono::milliseconds fallback) {
    const auto value = get_int(o, key);
    if (value && *value < 0) {
        throw common::ConfigError(std::string("'") + key + "' must not be negative");
    }
    return value ? std::chrono::milliseconds(*value) : fallback;
}

/// Reads the options the caller's `struct_size` covers.
bnc_client_options read_options(const bnc_client_options* options) {
    bnc_client_options out{};
    if (options == nullptr) {
        return out;
    }
    constexpr std::size_t kV1 =
        offsetof(bnc_client_options, tls_verify_data) + sizeof options->tls_verify_data;
    if (options->struct_size < kV1) {
        throw common::ConfigError("options.struct_size is too small");
    }
    out.tls_verify = options->tls_verify;
    out.tls_verify_data = options->tls_verify_data;
    constexpr std::size_t kV2 =
        offsetof(bnc_client_options, timestamp_data) + sizeof options->timestamp_data;
    if (options->struct_size >= kV2) {
        out.timestamp = options->timestamp;
        out.timestamp_data = options->timestamp_data;
    }
    return out;
}

std::string read_file(const std::string& path, const char* key = "ca_file") {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw common::ConfigError(std::string("'") + key + "' cannot be read: " + path);
    }
    std::ostringstream out;
    out << in.rdbuf();
    return out.str();
}

/// A client certificate (mutual TLS): the certificate chain and the private key, in PEM.
struct ClientCertificate {
    std::string chain;
    std::string key;
    std::string passphrase;
};

/// `client_cert_pem` / `client_cert_file` with `client_key_pem` / `client_key_file` and
/// `client_key_passphrase`, if set.
std::optional<ClientCertificate> client_certificate(const json::object& o) {
    const auto pem_or_file = [&](const char* pem, const char* file) -> std::optional<std::string> {
        auto text = get_string(o, pem);
        const auto path = get_string(o, file);
        if (text && path) {
            throw common::ConfigError(std::string("set only one of '") + pem + "' and '" + file +
                                      "'");
        }
        return path ? read_file(*path, file) : std::move(text);
    };
    auto chain = pem_or_file("client_cert_pem", "client_cert_file");
    auto key = pem_or_file("client_key_pem", "client_key_file");
    auto passphrase = get_string(o, "client_key_passphrase");
    if (!chain && !key) {
        if (passphrase) {
            throw common::ConfigError("'client_key_passphrase' needs a client certificate");
        }
        return std::nullopt;
    }
    if (!chain || !key) {
        throw common::ConfigError(
            "a client certificate needs both the certificate and its private key");
    }
    return ClientCertificate{std::move(*chain), std::move(*key), passphrase.value_or("")};
}

/// Loads `cert` into `ctx`; a certificate or key that is not usable is a configuration error.
void use_client_certificate(boost::asio::ssl::context& ctx, const ClientCertificate& cert) {
    try {
        ctx.use_certificate_chain(boost::asio::buffer(cert.chain));
    } catch (const std::exception& e) {
        throw common::ConfigError(
            std::string("'client_cert_pem' / 'client_cert_file' hold no valid PEM certificate: ") +
            e.what());
    }
    if (!cert.passphrase.empty()) {
        ctx.set_password_callback(
            [passphrase = cert.passphrase](
                std::size_t, boost::asio::ssl::context::password_purpose) { return passphrase; });
    }
    try {
        ctx.use_private_key(boost::asio::buffer(cert.key), boost::asio::ssl::context::pem);
    } catch (const std::exception& e) {
        throw common::ConfigError(
            std::string(
                "the client private key cannot be loaded (invalid PEM, wrong passphrase, or "
                "the key of another certificate): ") +
            e.what());
    }
    if (SSL_CTX_check_private_key(ctx.native_handle()) != 1) {
        throw common::ConfigError("the client private key does not match the client certificate");
    }
}

/// The TLS context hook for `ca_file`, `ca_pem`, `ca_only`, the client certificate and the verify
/// callback. It runs after the system trust store was loaded.
common::TlsContextHook tls_hook(const json::object& o, const bnc_client_options& options) {
    std::string pem;
    if (const auto file = get_string(o, "ca_file")) {
        pem += read_file(*file) + "\n";
    }
    if (const auto text = get_string(o, "ca_pem")) {
        pem += *text + "\n";
    }
    const bool only = get_bool(o, "ca_only").value_or(false);
    if (only && pem.empty()) {
        throw common::ConfigError("'ca_only' needs 'ca_file' or 'ca_pem'");
    }
    const auto verify = options.tls_verify;
    void* const verify_data = options.tls_verify_data;
    auto client_cert = client_certificate(o);
    if (pem.empty() && !only && verify == nullptr && !client_cert) {
        return {};
    }
    return [pem = std::move(pem), only, verify, verify_data,
            client_cert = std::move(client_cert)](boost::asio::ssl::context& ctx) {
        if (client_cert) {
            use_client_certificate(ctx, *client_cert);
        }
        if (only) {
            X509_STORE* empty = X509_STORE_new();
            if (empty == nullptr) {
                throw std::bad_alloc();
            }
            SSL_CTX_set_cert_store(ctx.native_handle(), empty);
        }
        if (!pem.empty()) {
            try {
                ctx.add_certificate_authority(boost::asio::buffer(pem));
            } catch (const std::exception& e) {
                throw common::ConfigError(std::string("'ca_file' / 'ca_pem' hold no valid PEM: ") +
                                          e.what());
            }
        }
        if (verify != nullptr) {
            ctx.set_verify_callback(
                [verify, verify_data](bool preverified, boost::asio::ssl::verify_context& vc) {
                    X509_STORE_CTX* store = vc.native_handle();
                    X509* cert = X509_STORE_CTX_get_current_cert(store);
                    unsigned char* der = nullptr;
                    const int length = cert != nullptr ? i2d_X509(cert, &der) : -1;
                    if (length <= 0) {
                        return false;
                    }
                    bool accept = false;
                    try {
                        accept =
                            verify(verify_data, der, static_cast<std::size_t>(length),
                                   X509_STORE_CTX_get_error_depth(store), preverified ? 1 : 0) != 0;
                    } catch (...) { // NOLINT(bugprone-empty-catch): a throwing callback rejects
                    }
                    OPENSSL_free(der);
                    return accept;
                });
        }
    };
}

/// Key errors surface when a client is built; for the caller they are configuration errors.
template <class F> auto with_key_errors_as_config(F&& f) {
    try {
        return f();
    } catch (const common::ConnectorClientError& e) {
        throw common::ConfigError(e.msg());
    }
}

/// The `timestamp` of signed requests: the caller's callback, or `time_offset_ms`, a fixed offset
/// added to the host clock.
common::TimestampProvider timestamp_provider(const json::object& o,
                                             const bnc_client_options& options) {
    const auto offset = get_int(o, "time_offset_ms").value_or(0);
    if (options.timestamp != nullptr) {
        if (offset != 0) {
            throw common::ConfigError(
                "set only one of 'time_offset_ms' and the timestamp callback");
        }
        return [callback = options.timestamp, data = options.timestamp_data] {
            return static_cast<std::int64_t>(callback(data));
        };
    }
    if (offset == 0) {
        return {};
    }
    return [offset] { return common::detail::timestamp_ms() + offset; };
}

/// `{"rateLimits": [...], "data": ...}` of an error answered by the WebSocket API (`data` only
/// when the answer has `error.data`), or empty for other errors.
std::string error_details(const std::exception_ptr& ep) {
    try {
        std::rethrow_exception(ep);
    } catch (const common::WebsocketResponseError& e) {
        json::array limits;
        for (const auto& limit : e.rate_limits()) {
            limits.push_back(json::value_from(limit));
        }
        json::object out{{"rateLimits", std::move(limits)}};
        if (const auto* data = e.data()) {
            out["data"] = *data;
        }
        return json::serialize(out);
    } catch (...) {
        return {};
    }
}

/// The options the product clients set: `user_agent` (the C interface's own by default),
/// `signed_streams` and `stream_id_is_strictly_number`.
common::detail::ClientOptions client_options(const json::object& o) {
    common::detail::ClientOptions out;
    out.user_agent = get_string(o, "user_agent").value_or(common::detail::build_user_agent("c"));
    out.signed_streams = get_bool(o, "signed_streams").value_or(false);
    out.stream_id_is_strictly_number = get_bool(o, "stream_id_is_strictly_number").value_or(false);
    return out;
}

common::RestApiConfig rest_config(const json::object& o, const bnc_client_options* options) {
    common::RestApiConfig cfg;
    cfg.agent = tls_hook(o, read_options(options));
    cfg.base_path = get_string(o, "base_path");
    if (!cfg.base_path) {
        throw common::ConfigError("'base_path' is required");
    }
    cfg.api_key = get_string(o, "api_key");
    cfg.api_secret = get_string(o, "api_secret");
    cfg.private_key = get_private_key(o);
    cfg.private_key_passphrase = get_string(o, "private_key_passphrase");
    cfg.timeout = get_ms(o, "timeout_ms", cfg.timeout);
    cfg.backoff = get_ms(o, "backoff_ms", cfg.backoff);
    cfg.retries = get_int_in(o, "retries", 0, std::numeric_limits<std::uint32_t>::max())
                      .value_or(cfg.retries);
    cfg.keep_alive = get_bool(o, "keep_alive").value_or(cfg.keep_alive);
    cfg.compression = get_bool(o, "compression").value_or(cfg.compression);
    cfg.max_response_size =
        get_int_in(o, "max_response_size", 1, std::numeric_limits<std::size_t>::max())
            .value_or(cfg.max_response_size);
    cfg.proxy = get_proxy(o);
    cfg.proxy_from_env = get_bool(o, "proxy_from_env").value_or(cfg.proxy_from_env);
    cfg.custom_headers = get_string_map(o, "custom_headers");
    cfg.time_unit = common::detail::validate_time_unit(get_string(o, "time_unit").value_or(""));
    cfg.timestamp_provider = timestamp_provider(o, read_options(options));
    cfg.executor = IoPool::instance().executor();
    return cfg;
}

common::WebsocketStreamsConfig streams_config(const json::object& o,
                                              const bnc_client_options* options) {
    common::WebsocketStreamsConfig cfg;
    cfg.agent = tls_hook(o, read_options(options));
    cfg.url = get_string(o, "url");
    if (!cfg.url) {
        throw common::ConfigError("'url' is required");
    }
    cfg.reconnect_delay = get_ms(o, "reconnect_delay_ms", cfg.reconnect_delay);
    cfg.connect_timeout = get_ms(o, "connect_timeout_ms", cfg.connect_timeout);
    if (const auto size = get_int_in(o, "pool_size", 0, std::numeric_limits<std::size_t>::max());
        size && *size > 0) {
        cfg.mode = common::WebsocketMode::pool(*size);
    }
    cfg.compression = get_bool(o, "compression").value_or(cfg.compression);
    cfg.max_message_size =
        get_int_in(o, "max_message_size", 1, std::numeric_limits<std::size_t>::max())
            .value_or(cfg.max_message_size);
    cfg.proxy = get_proxy(o);
    cfg.proxy_from_env = get_bool(o, "proxy_from_env").value_or(cfg.proxy_from_env);
    cfg.time_unit = common::detail::validate_time_unit(get_string(o, "time_unit").value_or(""));
    cfg.timestamp_provider = timestamp_provider(o, read_options(options));
    cfg.api_key = get_string(o, "api_key");
    cfg.api_secret = get_string(o, "api_secret");
    cfg.private_key = get_private_key(o);
    cfg.private_key_passphrase = get_string(o, "private_key_passphrase");
    cfg.executor = IoPool::instance().executor();
    return cfg;
}

struct RequestState {
    explicit RequestState(const boost::asio::any_io_executor& ex)
        : strand(boost::asio::make_strand(ex)) {}
    boost::asio::strand<boost::asio::any_io_executor> strand;
    boost::asio::cancellation_signal signal;
    /// For operations that cannot be aborted: completes the caller's callback early. Set before the
    /// handle is published.
    std::function<void()> abandon;
};

/// Lets the real completion of an operation and its early completion by cancelling race: the
/// first one wins.
struct Completion {
    template <class F> void run(F&& f) {
        if (!done.exchange(true)) {
            f();
        }
    }
    std::atomic<bool> done{false};
};

} // namespace

struct bnc_request {
    std::shared_ptr<RequestState> state;
};

namespace {

/// Starts an operation with `init(token)`. With `out`, the operation can be cancelled through
/// the handle: the signal's slot belongs to a strand, which also runs the completion.
template <class Init, class Handler>
void start_cancellable(bnc_request** out, const boost::asio::any_io_executor& ex, Handler handler,
                       Init init) {
    if (out == nullptr) {
        init(std::move(handler));
        return;
    }
    // Everything that can fail is done before the operation starts: once it has, the call must
    // succeed, because the callback will be called.
    auto state = std::make_shared<RequestState>(ex);
    auto request = std::make_unique<bnc_request>(bnc_request{state});
    init(boost::asio::bind_cancellation_slot(
        state->signal.slot(),
        boost::asio::bind_executor(state->strand,
                                   [state, handler = std::move(handler)](auto&&... args) mutable {
                                       handler(std::forward<decltype(args)>(args)...);
                                   })));
    *out = request.release();
}

/// For an operation that cannot be aborted, a handle whose cancellation runs `early` (once, unless
/// the operation completed first); null if the caller wants none. The operation's own completion
/// must go through `completion`. Made before the operation starts and published after, with
/// `publish`, so that a failure to make it does not leave a started operation behind.
template <class Early>
std::unique_ptr<bnc_request> make_abandonable(bnc_request** out,
                                              const boost::asio::any_io_executor& ex,
                                              std::shared_ptr<Completion> completion, Early early) {
    if (out == nullptr) {
        return nullptr;
    }
    auto state = std::make_shared<RequestState>(ex);
    state->abandon = [completion = std::move(completion), early = std::move(early)] {
        completion->run(early);
    };
    return std::make_unique<bnc_request>(bnc_request{std::move(state)});
}

void publish(bnc_request** out, std::unique_ptr<bnc_request> handle) noexcept {
    if (out != nullptr) {
        *out = handle.release();
    }
}

common::Params params_of(const json::object& o, const char* key);

common::WebsocketApiConfig wsapi_config(const json::object& o, const bnc_client_options* options) {
    common::WebsocketApiConfig cfg;
    cfg.agent = tls_hook(o, read_options(options));
    cfg.url = get_string(o, "url");
    if (!cfg.url) {
        throw common::ConfigError("'url' is required");
    }
    cfg.api_key = get_string(o, "api_key");
    cfg.api_secret = get_string(o, "api_secret");
    cfg.private_key = get_private_key(o);
    cfg.private_key_passphrase = get_string(o, "private_key_passphrase");
    cfg.timeout = get_ms(o, "timeout_ms", cfg.timeout);
    cfg.reconnect_delay = get_ms(o, "reconnect_delay_ms", cfg.reconnect_delay);
    cfg.connect_timeout = get_ms(o, "connect_timeout_ms", cfg.connect_timeout);
    if (const auto size = get_int_in(o, "pool_size", 0, std::numeric_limits<std::size_t>::max());
        size && *size > 0) {
        cfg.mode = common::WebsocketMode::pool(*size);
    }
    cfg.compression = get_bool(o, "compression").value_or(cfg.compression);
    cfg.max_message_size =
        get_int_in(o, "max_message_size", 1, std::numeric_limits<std::size_t>::max())
            .value_or(cfg.max_message_size);
    cfg.proxy = get_proxy(o);
    cfg.proxy_from_env = get_bool(o, "proxy_from_env").value_or(cfg.proxy_from_env);
    cfg.time_unit = common::detail::validate_time_unit(get_string(o, "time_unit").value_or(""));
    cfg.timestamp_provider = timestamp_provider(o, read_options(options));
    cfg.auto_session_relogon = get_bool(o, "auto_session_relogon").value_or(true);
    cfg.executor = IoPool::instance().executor();
    return cfg;
}

struct WsRequest {
    std::string method;
    common::Params params;
    common::WebsocketMessageSendOptions options;
};

WsRequest wsapi_request(const char* text) {
    const auto o = parse_object(text, "request");
    WsRequest req;
    const auto method = get_string(o, "method");
    if (!method) {
        throw common::ConfigError("'method' is required");
    }
    req.method = *method;
    req.params = params_of(o, "params");
    if (const auto* id = find(o, "id")) {
        if (!id->is_string() && !id->is_int64() && !id->is_uint64()) {
            throw common::ConfigError("'id' must be a string or an integer");
        }
        req.params["id"] = *id;
    }
    const auto auth = get_string(o, "auth").value_or("none");
    if (auth == "api_key") {
        req.options.with_api_key = true;
    } else if (auth == "signed") {
        req.options.is_signed = true;
    } else if (auth == "session_logon") {
        req.options.is_signed = true;
        req.options.is_session_logon = true;
    } else if (auth == "session_logout") {
        req.options.is_session_logout = true;
    } else if (auth != "none") {
        throw common::ConfigError("unknown 'auth': " + auth);
    }
    return req;
}

json::value response_json(const common::WebsocketApiRawResponse& r) {
    json::object out{{"result", r.result}};
    json::array limits;
    for (const auto& limit : r.rate_limits.value_or(std::vector<common::WebsocketApiRateLimit>{})) {
        limits.push_back(json::value_from(limit));
    }
    out["rateLimits"] = std::move(limits);
    return out;
}

std::optional<common::StreamId> stream_id(const char* text) {
    if (text == nullptr || *text == '\0') {
        return std::nullopt;
    }
    json::value value;
    try {
        value = json::parse(text);
    } catch (const std::exception& e) {
        throw common::ConfigError(std::string("id is not valid JSON: ") + e.what());
    }
    if (value.is_string()) {
        return common::StreamId(std::string(value.as_string()));
    }
    if (value.is_int64() || value.is_uint64()) {
        const auto n = value.to_number<std::int64_t>();
        if (n >= 0 && n <= std::numeric_limits<std::uint32_t>::max()) {
            return common::StreamId(static_cast<std::uint32_t>(n));
        }
    }
    throw common::ConfigError("id must be a string or an unsigned 32-bit number");
}

std::vector<std::string> string_array(const char* text, const char* what) {
    std::vector<std::string> out;
    if (text == nullptr || *text == '\0') {
        return out;
    }
    try {
        const auto value = json::parse(text);
        if (!value.is_array()) {
            throw common::ConfigError(std::string(what) + " must be a JSON array");
        }
        for (const auto& item : value.as_array()) {
            if (!item.is_string()) {
                throw common::ConfigError(std::string(what) + " must hold strings");
            }
            out.emplace_back(item.as_string());
        }
    } catch (const common::ConfigError&) {
        throw;
    } catch (const std::exception& e) {
        throw common::ConfigError(std::string(what) + " is not valid JSON: " + e.what());
    }
    return out;
}

common::Params params_of(const json::object& o, const char* key) {
    common::Params out;
    if (const auto* map = get_object(o, key)) {
        for (const auto& [name, value] : *map) {
            out.emplace(std::string(name), value);
        }
    }
    return out;
}

common::RestRequest rest_request(const char* text) {
    const auto o = parse_object(text, "request");
    common::RestRequest req;
    const auto method = get_string(o, "method").value_or("GET");
    if (method == "GET") {
        req.method = common::HttpMethod::Get;
    } else if (method == "POST") {
        req.method = common::HttpMethod::Post;
    } else if (method == "PUT") {
        req.method = common::HttpMethod::Put;
    } else if (method == "DELETE") {
        req.method = common::HttpMethod::Delete;
    } else if (method == "PATCH") {
        req.method = common::HttpMethod::Patch;
    } else {
        throw common::ConfigError("unknown 'method': " + method);
    }
    const auto endpoint = get_string(o, "endpoint");
    if (!endpoint) {
        throw common::ConfigError("'endpoint' is required");
    }
    req.endpoint = *endpoint;
    req.query = params_of(o, "query");
    req.body = params_of(o, "body");
    req.is_signed = get_bool(o, "signed").value_or(false);
    req.time_unit = common::detail::validate_time_unit(get_string(o, "time_unit").value_or(""));
    for (auto& [name, value] : get_string_map(o, "headers")) {
        req.headers.emplace_back(name, std::move(value));
    }
    return req;
}

} // namespace

struct bnc_rest_client {
    bnc_rest_client(common::RestApiConfig cfg, common::detail::ClientOptions options)
        : client(std::move(cfg), std::move(options)) {}
    common::RestClient client;
};

namespace {

struct StreamRegistry;

/// A stream created with `bnc_stream_new`, shared with the registry of its `bnc_streams`.
struct StreamEntry {
    std::string stream;
    bnc_status_callback on_terminated = nullptr;
    void* terminated_data = nullptr;
    std::weak_ptr<StreamRegistry> owner;
    /// Held while `on_terminated` runs, so that `bnc_stream_free` can wait for it. Recursive:
    /// the callback may free its own stream.
    std::recursive_mutex mutex;
    std::atomic<bool> done{false};
};

struct StreamRegistry {
    std::mutex mutex;
    std::vector<std::shared_ptr<StreamEntry>> entries;

    [[nodiscard]] std::vector<std::shared_ptr<StreamEntry>> snapshot() {
        const std::lock_guard lock(mutex);
        return entries;
    }
};

/// Ends a stream once: calls `on_terminated` unless it is done already (or freed).
void finish(StreamEntry& entry, const bnc_error* error) {
    const std::lock_guard lock(entry.mutex);
    if (entry.done.exchange(true)) {
        return;
    }
    if (entry.on_terminated != nullptr) {
        call_out("on_terminated", [&] { entry.on_terminated(entry.terminated_data, error); });
    }
}

void finish_all(const std::vector<std::shared_ptr<StreamEntry>>& entries, const bnc_error* error) {
    for (const auto& entry : entries) {
        finish(*entry, error);
    }
}

bnc_error websocket_failure(const std::string& message) {
    bnc_error out{};
    out.kind = BNC_ERROR_WEBSOCKET;
    out.ws_kind = BNC_WS_RESPONSE_ERROR;
    out.retry_after_seconds = -1;
    out.retry_at_ms = -1;
    copy_text(out.message, sizeof out.message, message);
    return out;
}

} // namespace

struct bnc_streams {
    bnc_streams(common::WebsocketStreamsConfig cfg, std::vector<std::string> paths,
                common::detail::ClientOptions options)
        : client(std::move(cfg), std::move(paths), std::move(options)) {
        // A rejected SUBSCRIBE drops its streams and emits an Error event.
        terminals = client.on_event(
            [registry = std::weak_ptr(streams), api = &client](const common::WebsocketEvent& e) {
                const auto live = registry.lock();
                if (e.type != common::WebsocketEventType::Error || !live) {
                    return;
                }
                const auto failure = websocket_failure(e.data);
                for (const auto& entry : live->snapshot()) {
                    if (!entry->done && !api->is_subscribed(entry->stream)) {
                        finish(*entry, &failure);
                    }
                }
            },
            false);
    }
    common::WebsocketStreams client;
    std::shared_ptr<StreamRegistry> streams = std::make_shared<StreamRegistry>();
    std::mutex mutex;
    std::optional<common::Subscription> events;
    common::Subscription terminals;
};

struct bnc_wsapi {
    bnc_wsapi(common::WebsocketApiConfig cfg, common::detail::ClientOptions options)
        : client(std::move(cfg), std::move(options)) {}
    common::WebsocketApi client;
    std::mutex mutex;
    std::optional<common::Subscription> events;
};

struct bnc_stream {
    common::WebsocketStreamHandle handle;
    /// Null for a subscription made with `bnc_wsapi_subscribe`.
    std::shared_ptr<StreamEntry> entry;
};

template <class Owner>
void set_events(Owner& owner, bnc_event_callback callback, void* user_data, bool with_messages) {
    const auto replace = [&owner, callback, user_data, with_messages] {
        std::optional<common::Subscription> subscription;
        if (callback != nullptr) {
            subscription = owner.client.on_event(
                [callback, user_data](const common::WebsocketEvent& e) {
                    callback(user_data, static_cast<bnc_event_type>(e.type), e.data.data(),
                             e.data.size(), e.close_code, e.connection_id.c_str());
                },
                with_messages);
        }
        {
            const std::lock_guard lock(owner.mutex);
            owner.events.swap(subscription);
        }
        // `subscription` now holds the old registration; destroying it waits for a running call.
    };
    try {
        if (t_pool_thread) {
            // From a library callback: at once, without waiting for the client's strand, which may
            // be the one running this call.
            replace();
            return;
        }
        // On the client's strand the new callback is added and the old one removed in one turn,
        // so that no event falls between them (lost) or reaches both.
        // Not std::promise (its std::call_once crashes with the static libstdc++ of the linux-arm
        // and musl builds): an atomic wait, as the core uses. Shared, so that the strand may still
        // touch it after the waiter returned.
        struct Done {
            std::atomic<bool> finished{false};
            std::exception_ptr error;
        };
        const auto done = std::make_shared<Done>();
        boost::asio::post(owner.client.get_executor(), [replace, done] {
            try {
                replace();
            } catch (...) {
                done->error = std::current_exception();
            }
            done->finished.store(true, std::memory_order_release);
            done->finished.notify_one();
        });
        done->finished.wait(false, std::memory_order_acquire);
        if (done->error) {
            std::rethrow_exception(done->error);
        }
    } catch (...) {
        log_escaped("Setting the event callback", std::current_exception());
    }
}

namespace {

/// Calls `f` with `raw` as a `bnc_rest_response`, valid during the call.
template <class F> void with_rest_response(const common::RawResponse& raw, F&& f) {
    const json::value headers = json::value_from(raw.headers);
    json::array limits;
    for (const auto& limit : raw.rate_limits.value_or(std::vector<common::RestApiRateLimit>{})) {
        limits.push_back(json::value_from(limit));
    }
    const auto headers_json = json::serialize(headers);
    const auto limits_json = json::serialize(limits);
    const bnc_rest_response response{raw.status, raw.body.data(), raw.body.size(),
                                     headers_json.c_str(), limits_json.c_str()};
    std::forward<F>(f)(response);
}

} // namespace

extern "C" {

uint32_t BNC_CALL bnc_abi_version(void) {
    return BNC_ABI_VERSION;
}

const char* BNC_CALL bnc_version(void) {
    return common::sdk_version().data();
}

void BNC_CALL bnc_set_thread_count(uint32_t threads) {
    g_threads = threads;
}

void BNC_CALL bnc_set_log_level(bnc_log_level level) {
    common::Logger::set_level(static_cast<common::LogLevel>(level));
}

void BNC_CALL bnc_set_log_callback(bnc_log_callback callback, void* user_data) {
    if (callback == nullptr) {
        common::Logger::set_sink({});
        return;
    }
    common::Logger::set_sink([callback, user_data](common::LogLevel level, std::string_view text) {
        try {
            callback(user_data, static_cast<bnc_log_level>(level), text.data(), text.size());
        } catch (...) { // NOLINT(bugprone-empty-catch): logging it would call the callback again
        }
    });
}

bnc_rest_client* BNC_CALL bnc_rest_new(const char* config_json, bnc_error* error) {
    return bnc_rest_new_ex(config_json, nullptr, error);
}

bnc_rest_client* BNC_CALL bnc_rest_new_ex(const char* config_json,
                                          const bnc_client_options* options, bnc_error* error) {
    bnc_rest_client* out = nullptr;
    guarded(error, [&] {
        const auto config = parse_object(config_json, "config");
        out = with_key_errors_as_config([&] {
            return new bnc_rest_client(rest_config(config, options), client_options(config));
        });
    });
    return out;
}

void BNC_CALL bnc_rest_free(bnc_rest_client* client) {
    delete client;
}

int32_t BNC_CALL bnc_rest_send(bnc_rest_client* client, const char* request_json,
                               bnc_rest_callback callback, void* user_data,
                               bnc_request** out_request, bnc_error* error) {
    return guarded(error, [&] {
        if (client == nullptr || callback == nullptr) {
            throw common::ConfigError("client and callback are required");
        }
        auto request = rest_request(request_json);
        start_cancellable(
            out_request, client->client.get_executor(),
            [callback, user_data](std::exception_ptr ep, common::RawResponse raw) noexcept {
                if (!ep) {
                    try {
                        with_rest_response(raw, [&](const bnc_rest_response& response) {
                            call_out("REST", [&] { callback(user_data, nullptr, &response); });
                        });
                        return;
                    } catch (...) {
                        // Building the response failed: the caller still gets its one call.
                        ep = std::current_exception();
                    }
                }
                bnc_error failure;
                describe(ep, &failure);
                // An HTTP error comes with the response that caused it.
                const common::RawResponse* failed = nullptr;
                try {
                    std::rethrow_exception(ep);
                } catch (const common::ConnectorError& e) {
                    failed = e.response();
                } catch (...) {
                }
                if (failed != nullptr) {
                    try {
                        with_rest_response(*failed, [&](const bnc_rest_response& response) {
                            call_out("REST", [&] { callback(user_data, &failure, &response); });
                        });
                        return;
                    } catch (...) {
                        // Without the response, the error alone.
                    }
                }
                call_out("REST", [&] { callback(user_data, &failure, nullptr); });
            },
            [&](auto&& token) {
                client->client.async_send_request(std::move(request),
                                                  std::forward<decltype(token)>(token));
            });
    });
}

void BNC_CALL bnc_request_cancel(bnc_request* request) {
    if (request != nullptr) {
        boost::asio::post(request->state->strand, [state = request->state] {
            if (state->abandon) {
                state->abandon();
            } else {
                state->signal.emit(boost::asio::cancellation_type::terminal);
            }
        });
    }
}

void BNC_CALL bnc_request_release(bnc_request* request) {
    delete request;
}

bnc_streams* BNC_CALL bnc_streams_new(const char* config_json, const char* url_paths_json,
                                      bnc_error* error) {
    return bnc_streams_new_ex(config_json, url_paths_json, nullptr, error);
}

bnc_streams* BNC_CALL bnc_streams_new_ex(const char* config_json, const char* url_paths_json,
                                         const bnc_client_options* options, bnc_error* error) {
    bnc_streams* out = nullptr;
    guarded(error, [&] {
        const auto config = parse_object(config_json, "config");
        out = with_key_errors_as_config([&] {
            return new bnc_streams(streams_config(config, options),
                                   string_array(url_paths_json, "url_paths"),
                                   client_options(config));
        });
    });
    return out;
}

void BNC_CALL bnc_streams_free(bnc_streams* streams) {
    if (streams != nullptr) {
        finish_all(streams->streams->snapshot(), nullptr);
    }
    delete streams;
}

namespace {

void report(const std::exception_ptr& ep, bnc_status_callback callback, void* user_data) noexcept {
    if (!ep) {
        call_out("status", [&] { callback(user_data, nullptr); });
        return;
    }
    bnc_error error;
    describe(ep, &error);
    call_out("status", [&] { callback(user_data, &error); });
}

/// Reports a wait abandoned with `bnc_request_cancel`.
void report_cancelled(bnc_status_callback callback, void* user_data) {
    report(std::make_exception_ptr(common::WebsocketCancelledError()), callback, user_data);
}

} // namespace

int32_t BNC_CALL bnc_streams_connect(bnc_streams* streams, const char* streams_json,
                                     bnc_status_callback callback, void* user_data,
                                     bnc_request** out_request, bnc_error* error) {
    return guarded(error, [&] {
        if (streams == nullptr || callback == nullptr) {
            throw common::ConfigError("streams and callback are required");
        }
        const auto completion = std::make_shared<Completion>();
        auto handle =
            make_abandonable(out_request, streams->client.get_executor(), completion,
                             [callback, user_data] { report_cancelled(callback, user_data); });
        streams->client.async_connect(string_array(streams_json, "streams"),
                                      [callback, user_data, completion](std::exception_ptr ep) {
                                          completion->run([&] { report(ep, callback, user_data); });
                                      });
        publish(out_request, std::move(handle));
    });
}

int32_t BNC_CALL bnc_streams_disconnect(bnc_streams* streams, bnc_status_callback callback,
                                        void* user_data, bnc_request** out_request,
                                        bnc_error* error) {
    return guarded(error, [&] {
        if (streams == nullptr || callback == nullptr) {
            throw common::ConfigError("streams and callback are required");
        }
        const auto completion = std::make_shared<Completion>();
        auto handle =
            make_abandonable(out_request, streams->client.get_executor(), completion,
                             [callback, user_data] { report_cancelled(callback, user_data); });
        // The streams that exist now are dropped by the disconnect; later ones are not.
        streams->client.async_disconnect(
            [callback, user_data, completion,
             dropped = streams->streams->snapshot()](std::exception_ptr ep) {
                finish_all(dropped, nullptr);
                completion->run([&] { report(ep, callback, user_data); });
            });
        publish(out_request, std::move(handle));
    });
}

int32_t BNC_CALL bnc_streams_wait_subscribed(bnc_streams* streams, const char* stream,
                                             const char* url_path, bnc_status_callback callback,
                                             void* user_data, bnc_request** out_request,
                                             bnc_error* error) {
    return guarded(error, [&] {
        if (streams == nullptr || stream == nullptr || callback == nullptr) {
            throw common::ConfigError("streams, stream and callback are required");
        }
        const auto completion = std::make_shared<Completion>();
        auto handle =
            make_abandonable(out_request, streams->client.get_executor(), completion,
                             [callback, user_data] { report_cancelled(callback, user_data); });
        streams->client.async_wait_subscribed(
            stream, url_path != nullptr ? std::optional<std::string>(url_path) : std::nullopt,
            [callback, user_data, completion](std::exception_ptr ep) {
                completion->run([&] { report(ep, callback, user_data); });
            });
        publish(out_request, std::move(handle));
    });
}

int32_t BNC_CALL bnc_streams_ping(bnc_streams* streams, bnc_error* error) {
    return guarded(error, [&] {
        if (streams == nullptr) {
            throw common::ConfigError("streams is required");
        }
        streams->client.ping_server();
    });
}

int32_t BNC_CALL bnc_streams_is_connected(const bnc_streams* streams) {
    return streams != nullptr && streams->client.is_connected() ? 1 : 0;
}

int32_t BNC_CALL bnc_streams_subscribe(bnc_streams* streams, const char* streams_json,
                                       const char* url_path, const char* id_json,
                                       bnc_error* error) {
    return guarded(error, [&] {
        if (streams == nullptr) {
            throw common::ConfigError("streams is required");
        }
        streams->client.subscribe(string_array(streams_json, "streams"), stream_id(id_json),
                                  url_path != nullptr ? std::optional<std::string>(url_path)
                                                      : std::nullopt);
    });
}

int32_t BNC_CALL bnc_streams_unsubscribe(bnc_streams* streams, const char* streams_json,
                                         const char* url_path, const char* id_json,
                                         bnc_error* error) {
    return guarded(error, [&] {
        if (streams == nullptr) {
            throw common::ConfigError("streams is required");
        }
        streams->client.unsubscribe(string_array(streams_json, "streams"), stream_id(id_json),
                                    url_path != nullptr ? std::optional<std::string>(url_path)
                                                        : std::nullopt);
    });
}

int32_t BNC_CALL bnc_streams_is_subscribed(const bnc_streams* streams, const char* stream) {
    if (streams == nullptr || stream == nullptr) {
        return -1;
    }
    try {
        return streams->client.is_subscribed(stream) ? 1 : 0;
    } catch (...) {
        return -1;
    }
}

void BNC_CALL bnc_streams_set_event_callback(bnc_streams* streams, bnc_event_callback callback,
                                             void* user_data) {
    if (streams != nullptr) {
        set_events(*streams, callback, user_data, true);
    }
}

void BNC_CALL bnc_streams_set_lifecycle_callback(bnc_streams* streams, bnc_event_callback callback,
                                                 void* user_data) {
    if (streams != nullptr) {
        set_events(*streams, callback, user_data, false);
    }
}

bnc_stream* BNC_CALL bnc_stream_new(bnc_streams* streams, const char* stream, const char* url_path,
                                    const char* id_json, bnc_message_callback callback,
                                    void* user_data, bnc_status_callback on_terminated,
                                    void* terminated_data, bnc_error* error) {
    bnc_stream* out = nullptr;
    guarded(error, [&] {
        if (streams == nullptr || stream == nullptr || callback == nullptr) {
            throw common::ConfigError("streams, stream and callback are required");
        }
        auto handle = streams->client.create_stream(
            stream, stream_id(id_json),
            url_path != nullptr ? std::optional<std::string>(url_path) : std::nullopt);
        handle.on_message([callback, user_data](const json::value& v) {
            const auto text = json::serialize(v);
            callback(user_data, text.data(), text.size());
        });
        auto entry = std::make_shared<StreamEntry>();
        entry->stream = stream;
        entry->on_terminated = on_terminated;
        entry->terminated_data = terminated_data;
        entry->owner = streams->streams;
        {
            const std::lock_guard lock(streams->streams->mutex);
            streams->streams->entries.push_back(entry);
        }
        out = new bnc_stream{std::move(handle), entry};
        // Rejected before it was registered: the Error event found nobody to tell. The client
        // keeps the rejection, with the server's message and code.
        if (!streams->client.is_subscribed(entry->stream)) {
            streams->client.async_wait_subscribed(
                entry->stream,
                url_path != nullptr ? std::optional<std::string>(url_path) : std::nullopt,
                [entry](std::exception_ptr ep) {
                    auto failure = websocket_failure("the subscription was dropped");
                    try {
                        if (ep) {
                            std::rethrow_exception(ep);
                        }
                    } catch (const common::WebsocketResponseError& e) {
                        failure = websocket_failure(e.what());
                        if (const auto code = e.code()) {
                            failure.has_code = 1;
                            failure.code = *code;
                        }
                    } catch (...) { // NOLINT(bugprone-empty-catch): dropped for another reason
                    }
                    finish(*entry, &failure);
                });
        }
    });
    return out;
}

int32_t BNC_CALL bnc_stream_is_active(const bnc_stream* stream) {
    return stream != nullptr && (stream->entry == nullptr || !stream->entry->done) ? 1 : 0;
}

void BNC_CALL bnc_stream_free(bnc_stream* stream) {
    if (stream != nullptr && stream->entry != nullptr) {
        if (const auto registry = stream->entry->owner.lock()) {
            const std::lock_guard lock(registry->mutex);
            std::erase(registry->entries, stream->entry);
        }
        // Waits for a running `on_terminated`; none starts afterwards.
        const std::lock_guard lock(stream->entry->mutex);
        stream->entry->done = true;
    }
    delete stream;
}

bnc_wsapi* BNC_CALL bnc_wsapi_new(const char* config_json, bnc_error* error) {
    return bnc_wsapi_new_ex(config_json, nullptr, error);
}

bnc_wsapi* BNC_CALL bnc_wsapi_new_ex(const char* config_json, const bnc_client_options* options,
                                     bnc_error* error) {
    bnc_wsapi* out = nullptr;
    guarded(error, [&] {
        const auto config = parse_object(config_json, "config");
        out = with_key_errors_as_config(
            [&] { return new bnc_wsapi(wsapi_config(config, options), client_options(config)); });
    });
    return out;
}

void BNC_CALL bnc_wsapi_free(bnc_wsapi* api) {
    delete api;
}

int32_t BNC_CALL bnc_wsapi_connect(bnc_wsapi* api, bnc_status_callback callback, void* user_data,
                                   bnc_request** out_request, bnc_error* error) {
    return guarded(error, [&] {
        if (api == nullptr || callback == nullptr) {
            throw common::ConfigError("api and callback are required");
        }
        const auto completion = std::make_shared<Completion>();
        auto handle =
            make_abandonable(out_request, api->client.get_executor(), completion,
                             [callback, user_data] { report_cancelled(callback, user_data); });
        api->client.async_connect([callback, user_data, completion](std::exception_ptr ep) {
            completion->run([&] { report(ep, callback, user_data); });
        });
        publish(out_request, std::move(handle));
    });
}

int32_t BNC_CALL bnc_wsapi_disconnect(bnc_wsapi* api, bnc_status_callback callback, void* user_data,
                                      bnc_request** out_request, bnc_error* error) {
    return guarded(error, [&] {
        if (api == nullptr || callback == nullptr) {
            throw common::ConfigError("api and callback are required");
        }
        const auto completion = std::make_shared<Completion>();
        auto handle =
            make_abandonable(out_request, api->client.get_executor(), completion,
                             [callback, user_data] { report_cancelled(callback, user_data); });
        api->client.async_disconnect([callback, user_data, completion](std::exception_ptr ep) {
            completion->run([&] { report(ep, callback, user_data); });
        });
        publish(out_request, std::move(handle));
    });
}

int32_t BNC_CALL bnc_wsapi_is_connected(const bnc_wsapi* api) {
    return api != nullptr && api->client.is_connected() ? 1 : 0;
}

int32_t BNC_CALL bnc_wsapi_ping(bnc_wsapi* api, bnc_error* error) {
    return guarded(error, [&] {
        if (api == nullptr) {
            throw common::ConfigError("api is required");
        }
        api->client.ping_server();
    });
}

void BNC_CALL bnc_wsapi_set_event_callback(bnc_wsapi* api, bnc_event_callback callback,
                                           void* user_data) {
    if (api != nullptr) {
        set_events(*api, callback, user_data, true);
    }
}

void BNC_CALL bnc_wsapi_set_lifecycle_callback(bnc_wsapi* api, bnc_event_callback callback,
                                               void* user_data) {
    if (api != nullptr) {
        set_events(*api, callback, user_data, false);
    }
}

int32_t BNC_CALL bnc_wsapi_send(bnc_wsapi* api, const char* request_json,
                                bnc_wsapi_callback callback, void* user_data,
                                bnc_request** out_request, bnc_error* error) {
    return guarded(error, [&] {
        if (api == nullptr || callback == nullptr) {
            throw common::ConfigError("api and callback are required");
        }
        auto req = wsapi_request(request_json);
        start_cancellable(
            out_request, api->client.get_executor(),
            [callback, user_data](std::exception_ptr ep,
                                  std::vector<common::WebsocketApiRawResponse> responses) noexcept {
                if (!ep) {
                    try {
                        json::array out;
                        for (const auto& r : responses) {
                            out.push_back(response_json(r));
                        }
                        const auto text = json::serialize(out);
                        call_out("WebSocket API",
                                 [&] { callback(user_data, nullptr, text.data(), text.size()); });
                        return;
                    } catch (...) {
                        ep = std::current_exception();
                    }
                }
                bnc_error failure;
                describe(ep, &failure);
                const auto details = error_details(ep);
                call_out("WebSocket API", [&] {
                    callback(user_data, &failure, details.empty() ? nullptr : details.c_str(),
                             details.size());
                });
            },
            [&](auto&& token) {
                api->client.async_send_message(std::move(req.method), std::move(req.params),
                                               req.options, std::forward<decltype(token)>(token));
            });
    });
}

int32_t BNC_CALL bnc_wsapi_subscribe(bnc_wsapi* api, const char* request_json,
                                     bnc_wsapi_subscribe_callback callback, void* user_data,
                                     bnc_message_callback message_callback, void* message_data,
                                     bnc_request** out_request, bnc_error* error) {
    return guarded(error, [&] {
        if (api == nullptr || callback == nullptr || message_callback == nullptr) {
            throw common::ConfigError("api and both callbacks are required");
        }
        auto req = wsapi_request(request_json);
        const auto completion = std::make_shared<Completion>();
        auto handle = make_abandonable(
            out_request, api->client.get_executor(), completion, [callback, user_data] {
                bnc_error failure;
                describe(std::make_exception_ptr(common::WebsocketCancelledError(true)), &failure);
                call_out("subscribe", [&] { callback(user_data, &failure, nullptr, 0, nullptr); });
            });
        api->client.async_subscribe(
            std::move(req.method), std::move(req.params), req.options,
            [callback, user_data, message_callback, message_data,
             completion](std::exception_ptr ep, common::WebsocketApiRawSubscription sub) {
                // An abandoned wait drops `sub`, which stops the event stream.
                completion->run([&]() noexcept {
                    if (!ep) {
                        try {
                            const auto text = json::serialize(response_json(sub.response));
                            auto stream =
                                std::make_unique<bnc_stream>(bnc_stream{std::move(sub.stream), {}});
                            stream->handle.on_message(
                                [message_callback, message_data](const json::value& v) {
                                    const auto event = json::serialize(v);
                                    message_callback(message_data, event.data(), event.size());
                                });
                            // The callee owns the stream from here, even if the callback throws.
                            call_out("subscribe", [&] {
                                callback(user_data, nullptr, text.data(), text.size(),
                                         stream.release());
                            });
                            return;
                        } catch (...) {
                            ep = std::current_exception();
                        }
                    }
                    bnc_error failure;
                    describe(ep, &failure);
                    const auto details = error_details(ep);
                    call_out("subscribe", [&] {
                        callback(user_data, &failure, details.empty() ? nullptr : details.c_str(),
                                 details.size(), nullptr);
                    });
                });
            });
        publish(out_request, std::move(handle));
    });
}

} // extern "C"
