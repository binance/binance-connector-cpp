//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <array>
#include <chrono>
#include <list>
#include <optional>
#include <thread>
#include <utility>
#include <vector>

#ifndef _WIN32
#include <cerrno>
#include <sys/socket.h>
#endif

#include <boost/asio/bind_cancellation_slot.hpp>
#include <boost/asio/cancel_after.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/this_coro.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/json/value.hpp>

#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/logger.hpp>
#include <binance/common/rest.hpp>

#include "net.hpp"
#include "utils.hpp"

namespace binance::common {

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace ssl = asio::ssl;
using tcp = asio::ip::tcp;
using Clock = std::chrono::steady_clock;
using HttpRequest = http::request<http::string_body>;
using HttpResponse = http::response<http::string_body>;
using detail::Endpoint;

struct detail::ErrorAccess {
    static void set_response(ConnectorError& error, std::shared_ptr<const RawResponse> response) {
        error.response_ = std::move(response);
    }
};
using detail::lower;
using detail::throw_network;

namespace {

constexpr std::uint32_t kHeaderLimit = 64U * 1024;
constexpr std::size_t kMaxIdleConnections = 16;
/// Pooled connections idle for longer are closed rather than reused, so the server is unlikely
/// to close one under us just as a request goes out.
constexpr std::chrono::seconds kMaxIdleTime{30};

http::verb to_verb(HttpMethod method) {
    switch (method) {
    case HttpMethod::Get:
        return http::verb::get;
    case HttpMethod::Post:
        return http::verb::post;
    case HttpMethod::Put:
        return http::verb::put;
    case HttpMethod::Delete:
        return http::verb::delete_;
    case HttpMethod::Patch:
        return http::verb::patch;
    }
    return http::verb::get;
}

/// ASCII only: `std::isalnum` and friends depend on the C locale.
bool is_alnum(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

bool is_token_char(char c) {
    return is_alnum(c) || std::string_view("!#$%&'*+-.^_`|~").find(c) != std::string_view::npos;
}

bool valid_header_name(std::string_view name) {
    return !name.empty() && std::all_of(name.begin(), name.end(), is_token_char);
}

/// RFC 3986 path characters (`pchar` and `/`) plus `%` escapes: no spaces, controls, `?` or `#`.
bool valid_endpoint(std::string_view endpoint) {
    return endpoint.starts_with('/') && std::all_of(endpoint.begin(), endpoint.end(), [](char c) {
               return is_alnum(c) ||
                      std::string_view("-._~!$&'()*+,;=:@/%").find(c) != std::string_view::npos;
           });
}

bool valid_header_value(std::string_view value) {
    return std::none_of(value.begin(), value.end(),
                        [](char c) { return c == '\r' || c == '\n' || c == '\0'; });
}

std::string_view trim(std::string_view s) {
    while (!s.empty() && is_space(s.front())) {
        s.remove_prefix(1);
    }
    while (!s.empty() && is_space(s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

/// Decodes `body` in place. A body that cannot be decoded fails a 2xx response; on any other
/// status it is kept as received, so the status is still mapped to its error.
void inflate_body(std::string& body, std::size_t limit, bool success) {
    std::string out;
    const auto status = detail::inflate(body, limit, out);
    if (status == detail::InflateStatus::Ok) {
        body = std::move(out);
        return;
    }
    if (!success) {
        return;
    }
    if (status == detail::InflateStatus::TooLarge) {
        throw ConnectorClientError("Decompressed response exceeds max_response_size (" +
                                   std::to_string(limit) + " bytes)");
    }
    throw ConnectorClientError("Failed to decompress gzip response");
}

bool is_stale_connection_error(const boost::system::error_code& ec) {
    return ec == http::error::end_of_stream || ec == asio::error::eof ||
           ec == asio::error::connection_reset || ec == asio::error::broken_pipe ||
           ec == asio::error::connection_aborted || ec == ssl::error::stream_truncated;
}

template <class E>
[[noreturn]] void raise(E error, const std::shared_ptr<const RawResponse>& response) {
    detail::ErrorAccess::set_response(error, response);
    throw error;
}

RawResponse to_raw_response(HttpResponse res, std::size_t max_size) {
    RawResponse out;
    out.status = static_cast<std::uint16_t>(res.result_int());
    for (const auto& field : res) {
        auto name = lower(field.name_string());
        auto [it, inserted] = out.headers.emplace(name, std::string(field.value()));
        if (!inserted) {
            it->second += ", ";
            it->second += field.value();
        }
    }
    out.body = std::move(res.body());
    const bool success = out.status >= 200 && out.status < 300;

    // An empty body (e.g. an error page without content) has nothing to decode.
    if (const auto enc = out.headers.find("content-encoding");
        enc != out.headers.end() && !out.body.empty()) {
        const auto value = lower(enc->second);
        if (value.find("gzip") != std::string::npos || value.find("deflate") != std::string::npos) {
            inflate_body(out.body, max_size, success);
        }
    }

    auto limits = detail::parse_rate_limit_headers(out.headers);
    if (!limits.empty()) {
        out.rate_limits = std::move(limits);
    }

    if (success) {
        return out;
    }

    std::optional<std::string> body_msg;
    std::optional<std::int64_t> code;
    try {
        const auto jv = parse_json(out.body);
        if (const auto* obj = jv.if_object()) {
            if (const auto* m = obj->if_contains("msg"); m != nullptr && m->is_string()) {
                body_msg = std::string(m->get_string());
            }
            if (const auto* c = obj->if_contains("code"); c != nullptr) {
                if (c->is_int64()) {
                    code = c->get_int64();
                } else if (c->is_uint64()) {
                    code = static_cast<std::int64_t>(c->get_uint64());
                }
            }
        }
    } catch (const ConnectorError&) { // NOLINT(bugprone-empty-catch): not JSON, keep the raw body
    }
    const auto status = out.status;
    std::string msg = body_msg.value_or(out.body);
    const auto response = std::make_shared<const RawResponse>(std::move(out));

    switch (status) {
    case 400:
        raise(BadRequestError(msg, code), response);
    case 401:
        raise(UnauthorizedError(msg, code), response);
    case 403:
        raise(ForbiddenError(msg, code), response);
    case 404:
        raise(NotFoundError(msg, code), response);
    case 409:
        raise(ConflictError(msg, code), response);
    case 418:
        raise(RateLimitBanError(msg, code), response);
    case 429:
        raise(TooManyRequestsError(msg, code), response);
    default:
        break;
    }
    if (status >= 500 && status < 600) {
        raise(
            ServerError(body_msg.value_or("Server error: " + std::to_string(status)), status, code),
            response);
    }
    if (status < 400) {
        // 1xx / 3xx. Binance never redirects, and following one could forward a signed request
        // to another host.
        std::string unexpected = "Unexpected HTTP status " + std::to_string(status);
        if (const auto location = response->headers.find("location");
            location != response->headers.end()) {
            unexpected += " (Location: " + location->second + ")";
        }
        raise(ConnectorClientError(unexpected), response);
    }
    raise(ConnectorClientError(msg, code), response);
}

using TlsStream = ssl::stream<beast::tcp_stream&>;
using NestedTlsStream = ssl::stream<TlsStream&>;

/// One pooled connection. The layers depend on the route:
/// - `tcp`: an http target, directly or through an http proxy;
/// - `outer`: TLS to the target (directly or through an http proxy's CONNECT tunnel), or TLS to an
///   https proxy;
/// - `inner`: TLS to an https target, tunnelled through an https proxy's TLS session.
struct Connection {
    explicit Connection(const asio::any_io_executor& ex) : tcp(ex) {}

    beast::tcp_stream tcp;
    std::optional<TlsStream> outer;
    std::optional<NestedTlsStream> inner;
    beast::flat_buffer buffer;
    Clock::time_point idle_since;

    /// Calls `f` with the stream that carries HTTP to the target.
    template <class F> auto visit(F&& f) {
        if (inner) {
            return std::forward<F>(f)(*inner);
        }
        if (outer) {
            return std::forward<F>(f)(*outer);
        }
        return std::forward<F>(f)(tcp);
    }

    /// An idle keep-alive connection must have nothing to read. EOF, buffered bytes (e.g. a TLS
    /// close_notify) or an error all mean that the server has closed it or is closing it.
    [[nodiscard]] bool idle_and_open() {
        if (buffer.size() > 0) {
            return false;
        }
        auto& socket = tcp.socket();
        char byte = 0;
#ifdef _WIN32
        boost::system::error_code ec;
        const bool was_non_blocking = socket.non_blocking();
        socket.non_blocking(true, ec);
        if (ec) {
            return false; // Peeking could block; do not reuse the connection.
        }
        (void)socket.receive(asio::buffer(&byte, 1), tcp::socket::message_peek, ec);
        boost::system::error_code restore_ec;
        socket.non_blocking(was_non_blocking, restore_ec);
        return ec == asio::error::would_block && !restore_ec;
#else
        const auto n = ::recv(socket.native_handle(), &byte, 1, MSG_PEEK | MSG_DONTWAIT);
        return n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK);
#endif
    }
};

/// `Clock::now() + timeout`, saturated: a timeout too large to represent means no deadline.
Clock::time_point deadline_after(std::chrono::milliseconds timeout) {
    const auto now = Clock::now();
    if (timeout >=
        std::chrono::duration_cast<std::chrono::milliseconds>(Clock::time_point::max() - now)) {
        return Clock::time_point::max();
    }
    return now + timeout;
}

/// Writes `req` and reads the response, all before `deadline` (the end of the attempt).
/// `write_started` is set before the first byte may leave.
template <class Stream>
asio::awaitable<void> exchange(Stream& stream, beast::tcp_stream& tcp, Clock::time_point deadline,
                               beast::flat_buffer& buffer, const HttpRequest& req,
                               http::response_parser<http::string_body>& parser,
                               bool& write_started, bool& written, boost::system::error_code& ec) {
    tcp.expires_at(deadline);
    write_started = true;
    co_await http::async_write(stream, req, asio::redirect_error(asio::use_awaitable, ec));
    if (ec) {
        co_return;
    }
    written = true;
    while (!parser.is_done()) {
        co_await http::async_read_some(stream, buffer, parser,
                                       asio::redirect_error(asio::use_awaitable, ec));
        if (ec) {
            co_return;
        }
    }
}

/// Methods that RFC 9110 defines as idempotent, which may be replayed on a fresh connection when
/// a pooled one turns out to be closed after the request was written.
bool is_idempotent(HttpMethod method) {
    return method == HttpMethod::Get || method == HttpMethod::Put || method == HttpMethod::Delete;
}

bool cancelled(const asio::cancellation_state& state) {
    return state.cancelled() != asio::cancellation_type::none;
}

} // namespace

std::string_view to_string(HttpMethod method) noexcept {
    switch (method) {
    case HttpMethod::Get:
        return "GET";
    case HttpMethod::Post:
        return "POST";
    case HttpMethod::Put:
        return "PUT";
    case HttpMethod::Delete:
        return "DELETE";
    case HttpMethod::Patch:
        return "PATCH";
    }
    return "";
}

// Declaration order matters for destruction: connections, then the strand, then the owned
// I/O context (with any coroutine frames), then the TLS context.
struct RestClient::Impl : std::enable_shared_from_this<RestClient::Impl> {
    /// One in-flight request. Only touched on the strand.
    struct Operation {
        asio::cancellation_signal signal;
    };

    RestApiConfig cfg;
    std::string user_agent;
    SignatureGenerator signer;
    Endpoint target;
    std::optional<Endpoint> proxy;
    std::string proxy_authorization;
    std::optional<detail::SocksRoute> socks;
    std::string host_header;
    ssl::context tls{ssl::context::tls_client};
    /// Only without `cfg.executor`.
    std::optional<asio::io_context> owned_ioc;
    std::optional<asio::executor_work_guard<asio::io_context::executor_type>> work;
    /// Initialised by `base_executor()`, after the two above.
    asio::strand<asio::any_io_executor> strand;
    std::vector<std::unique_ptr<Connection>> idle;
    std::list<std::shared_ptr<Operation>> operations;
    bool stopping = false;
    std::thread thread;

    Impl(RestApiConfig c, std::string ua)
        : cfg(std::move(c)), user_agent(std::move(ua)),
          signer(cfg.api_secret, cfg.private_key, cfg.private_key_passphrase),
          strand(asio::make_strand(base_executor())) {
        if (!cfg.base_path || cfg.base_path->empty()) {
            throw ConfigError("Configuration missing or invalid `base_path`");
        }
        target = detail::parse_url(*cfg.base_path, "http", "https", "base_path");
        host_header = target.authority();
        auto route = detail::make_proxy_route(cfg.proxy, cfg.proxy_from_env, target);
        proxy = std::move(route.proxy);
        proxy_authorization = std::move(route.authorization);
        socks = std::move(route.socks);
        detail::init_tls_context(tls, cfg.agent);
        signer.load_key();
        // The signer keeps the parsed key, so the passphrase is not kept in the configuration.
        cfg.private_key_passphrase.reset();
    }

    asio::any_io_executor base_executor() {
        if (cfg.executor != nullptr) {
            return cfg.executor;
        }
        work.emplace(owned_ioc.emplace(1).get_executor());
        return owned_ioc->get_executor();
    }

    /// Runs the owned I/O context. An exception that escapes a completion handler (user code, when
    /// the handler has no executor of its own) is logged and the loop continues; it must not
    /// terminate the process or strand other requests.
    void run() noexcept {
        for (;;) {
            try {
                owned_ioc->run();
                return;
            } catch (const std::exception& e) {
                Logger::error(std::string("Exception escaped a completion handler: ") + e.what());
            } catch (...) {
                Logger::error("Unknown exception escaped a completion handler");
            }
        }
    }

    /// On the strand: cancels every in-flight request, which then completes with
    /// `RequestCancelledError`, and lets the owned thread finish once they have.
    void shutdown() {
        stopping = true;
        const auto pending = operations;
        for (const auto& op : pending) {
            op->signal.emit(asio::cancellation_type::terminal);
        }
        idle.clear();
        work.reset();
    }

    [[nodiscard]] HttpRequest build(const RestRequest& r) const {
        if (!valid_endpoint(r.endpoint)) {
            throw ConnectorClientError("Invalid endpoint '" + r.endpoint +
                                       "': must start with '/' and contain only URL path "
                                       "characters");
        }

        std::string body = r.body.empty() ? std::string() : detail::build_query_string(r.body);
        std::string query_string;
        if (r.is_signed) {
            Params query = r.query;
            query["timestamp"] = detail::timestamp_ms(cfg.timestamp_provider);
            query_string = detail::build_query_string(query);
            const auto signature = signer.sign_payload(query_string + body);
            query_string += (query_string.empty() ? "" : "&");
            query_string += "signature=" + detail::form_urlencode(signature);
        } else {
            query_string = detail::build_query_string(r.query);
        }

        std::string path = target.prefix + r.endpoint;
        if (!query_string.empty()) {
            path += '?';
            path += query_string;
        }
        if (proxy && !target.tls) {
            path = "http://" + host_header + path; // absolute-form through a forward proxy
        }

        HttpRequest req{to_verb(r.method), path, 11};

        const auto add_headers = [&req](const auto& headers) {
            // Framing, hop-by-hop and credential headers, which the SDK controls.
            static constexpr std::array<std::string_view, 14> kForbidden = {"host",
                                                                            "authorization",
                                                                            "cookie",
                                                                            ":method",
                                                                            ":path",
                                                                            "content-length",
                                                                            "transfer-encoding",
                                                                            "connection",
                                                                            "keep-alive",
                                                                            "proxy-authorization",
                                                                            "te",
                                                                            "upgrade",
                                                                            "expect",
                                                                            "x-mbx-apikey"};
            for (const auto& [raw_name, value] : headers) {
                const auto name = trim(raw_name);
                if (std::find(kForbidden.begin(), kForbidden.end(), lower(name)) !=
                    kForbidden.end()) {
                    Logger::warn("Dropping forbidden header: " + std::string(name));
                    continue;
                }
                if (!valid_header_name(name) || !valid_header_value(value)) {
                    Logger::warn("Dropping invalid header '" + std::string(name) + "'");
                    continue;
                }
                req.insert(name, value);
            }
        };
        add_headers(cfg.custom_headers);
        add_headers(r.headers);

        req.set(http::field::host, host_header);
        req.set(http::field::content_type,
                r.body.empty() ? "application/json" : "application/x-www-form-urlencoded");
        req.set(http::field::user_agent, user_agent);
        if (cfg.api_key) {
            if (!valid_header_value(*cfg.api_key)) {
                throw ConnectorClientError("Invalid api_key: contains CR, LF or NUL");
            }
            req.set("X-MBX-APIKEY", *cfg.api_key);
        }
        if (cfg.compression) {
            req.set(http::field::accept_encoding, "gzip, deflate");
        }
        if (r.time_unit) {
            req.set("X-MBX-TIME-UNIT", to_upper_string(*r.time_unit));
        }
        if (proxy && !target.tls && !proxy_authorization.empty()) {
            req.set(http::field::proxy_authorization, proxy_authorization);
        }
        req.keep_alive(cfg.keep_alive);
        if (!body.empty()) {
            req.body() = std::move(body);
        }
        req.prepare_payload();
        return req;
    }

    /// Every step (DNS, TCP, proxy, TLS) must end before `deadline`, the end of the attempt. The
    /// TCP step starts the resolved addresses one after another (see `detail::connect_staggered`)
    /// within that time, so one that never answers (e.g. IPv6 without a route) does not hold up
    /// the others.
    asio::awaitable<std::unique_ptr<Connection>> connect(Clock::time_point deadline) {
        auto conn = std::make_unique<Connection>(strand);
        auto& sock = conn->tcp;
        const Endpoint* via = &target;
        if (socks) {
            via = &socks->server;
        } else if (proxy) {
            via = &*proxy;
        }

        const auto results = co_await detail::resolve(*via, deadline);
        co_await detail::connect_staggered(sock.socket(), detail::interleave_families(results),
                                           deadline);
        boost::system::error_code ec;
        // NOLINTNEXTLINE(bugprone-unused-return-value): best effort; the error is in `ec`.
        sock.socket().set_option(tcp::no_delay(true), ec);

        if (socks) {
            sock.expires_at(deadline);
            co_await detail::socks5_connect(conn->tcp, target, *socks, deadline);
        }
        if (proxy && proxy->tls) {
            conn->outer.emplace(conn->tcp, tls);
            sock.expires_at(deadline);
            co_await detail::tls_handshake(*conn->outer, proxy->host, "proxy TLS handshake");
        }
        if (proxy && target.tls) {
            sock.expires_at(deadline);
            // Not a `?:` with two `co_await`s, which older GCC and MSVC miscompile.
            unsigned status = 0;
            if (conn->outer) {
                status = co_await detail::proxy_connect(*conn->outer, conn->buffer, target,
                                                        proxy_authorization);
            } else {
                status = co_await detail::proxy_connect(conn->tcp, conn->buffer, target,
                                                        proxy_authorization);
            }
            if (status < 200 || status >= 300) {
                throw NetworkError("Proxy CONNECT failed with status " + std::to_string(status));
            }
        }
        if (target.tls) {
            sock.expires_at(deadline);
            if (conn->outer) {
                conn->inner.emplace(*conn->outer, tls);
                co_await detail::tls_handshake(*conn->inner, target.host, "TLS handshake");
            } else {
                conn->outer.emplace(conn->tcp, tls);
                co_await detail::tls_handshake(*conn->outer, target.host, "TLS handshake");
            }
        }
        co_return conn;
    }

    /// A pooled connection that is still usable, or null.
    std::unique_ptr<Connection> take_idle() {
        const auto now = Clock::now();
        while (!idle.empty()) {
            auto conn = std::move(idle.back());
            idle.pop_back();
            if (now - conn->idle_since < kMaxIdleTime && conn->idle_and_open()) {
                return conn;
            }
        }
        return nullptr;
    }

    /// One attempt. Throws `boost::system::system_error` on transport failure. Sets
    /// `write_started` before the request may start to leave, and `request_sent` once the whole
    /// request has been written.
    asio::awaitable<HttpResponse> perform(const HttpRequest& req, HttpMethod method,
                                          bool& write_started, bool& request_sent) {
        // `timeout` bounds the whole attempt, as in the other Binance connectors: connecting,
        // writing and reading the whole response. A retry starts a new one.
        const auto deadline = deadline_after(cfg.timeout);
        for (bool allow_reuse = true;; allow_reuse = false) {
            std::unique_ptr<Connection> conn;
            if (allow_reuse && cfg.keep_alive) {
                conn = take_idle();
            }
            const bool reused = conn != nullptr;
            if (!reused) {
                conn = co_await connect(deadline);
            }

            http::response_parser<http::string_body> parser;
            parser.body_limit(static_cast<std::uint64_t>(cfg.max_response_size));
            parser.header_limit(kHeaderLimit);
            boost::system::error_code ec;
            bool written = false;
            auto& sock = conn->tcp;
            co_await conn->visit([&](auto& stream) {
                return exchange(stream, sock, deadline, conn->buffer, req, parser, write_started,
                                written, ec);
            });
            request_sent = request_sent || written;
            if (ec) {
                // A pooled connection the server had already closed. Replaying is safe if the
                // request never left, or if the method is idempotent. A POST that was written may
                // have reached Binance, so it fails with request_sent() instead of being sent
                // twice.
                if (reused && !parser.got_some() && is_stale_connection_error(ec) &&
                    (!written || is_idempotent(method))) {
                    Logger::debug("Pooled connection was closed by the server, reconnecting");
                    continue;
                }
                throw_network(ec, "HTTP exchange");
            }
            sock.expires_never();

            auto res = parser.release();
            if (cfg.keep_alive && res.keep_alive() && !stopping &&
                idle.size() < kMaxIdleConnections) {
                conn->idle_since = Clock::now();
                idle.push_back(std::move(conn));
            }
            co_return res;
        }
    }

    asio::awaitable<RawResponse> execute(RestRequest r) {
        // Terminal and partial cancellation are always accepted. Total cancellation (no side
        // effects) only until the request may have started to leave. Whichever is accepted
        // aborts the pending step.
        const auto write_started = std::make_shared<bool>(false);
        co_await asio::this_coro::reset_cancellation_state(
            [write_started](asio::cancellation_type type) {
                return *write_started ? type & ~asio::cancellation_type::total : type;
            },
            [](asio::cancellation_type type) {
                return type == asio::cancellation_type::none ? type
                                                             : asio::cancellation_type::terminal;
            });
        const auto state = co_await asio::this_coro::cancellation_state;
        const auto method = to_string(r.method);
        bool request_sent = false;
        std::uint32_t attempt = 0;
        for (;;) {
            // Built per attempt so a signed retry carries a fresh timestamp and stays within
            // recvWindow after the backoff.
            const auto req = build(r);
            std::optional<HttpResponse> res;
            std::string network_error;
            boost::system::error_code transport_error;
            bool timed_out = false;
            try {
                res = co_await perform(req, r.method, *write_started, request_sent);
            } catch (const boost::system::system_error& e) {
                // An oversized response would be just as large on a retry.
                if (e.code() == http::error::body_limit) {
                    throw ConnectorClientError("Response exceeds max_response_size (" +
                                               std::to_string(cfg.max_response_size) + " bytes)");
                }
                if (e.code() == http::error::header_limit) {
                    throw ConnectorClientError("Response headers exceed " +
                                               std::to_string(kHeaderLimit) + " bytes");
                }
                network_error = detail::error_message(e);
                transport_error = e.code();
                timed_out = e.code() == beast::error::timeout;
            }
            // A response that arrived as the request was being cancelled is returned, not retried.
            const bool was_cancelled = cancelled(state);
            if (was_cancelled && !res) {
                throw RequestCancelledError(request_sent);
            }

            ++attempt;
            const auto retries_left =
                static_cast<std::int64_t>(cfg.retries) - static_cast<std::int64_t>(attempt);
            const std::optional<std::uint16_t> status =
                res ? std::optional<std::uint16_t>(static_cast<std::uint16_t>(res->result_int()))
                    : std::nullopt;
            const bool retriable_failure = !res || (*status >= 500 && *status < 600);
            if (retriable_failure && !was_cancelled &&
                detail::should_retry_request(method, status, retries_left)) {
                const auto wait = cfg.backoff * attempt;
                if (Logger::enabled(LogLevel::Debug)) {
                    Logger::debug(std::string(method) + " " + r.endpoint + " failed (" +
                                  (res ? "HTTP " + std::to_string(*status) : network_error) +
                                  "), retrying in " + std::to_string(wait.count()) + "ms");
                }
                asio::steady_timer timer(strand, wait);
                boost::system::error_code ec;
                co_await timer.async_wait(asio::redirect_error(asio::use_awaitable, ec));
                if (cancelled(state)) {
                    throw RequestCancelledError(request_sent);
                }
                continue;
            }
            if (!res) {
                auto msg = "HTTP request failed: " + network_error +
                           (attempt > 1 ? " (after " + std::to_string(attempt) + " attempts)"
                                        : std::string());
                if (timed_out) {
                    throw RequestTimeoutError(msg, request_sent, transport_error);
                }
                throw NetworkError(msg, request_sent, transport_error);
            }
            co_return to_raw_response(std::move(*res), cfg.max_response_size);
        }
    }

    /// On the strand: runs one request and completes `handler` on `handler_ex`.
    /// Returns the new operation, or null if the client is stopping.
    template <class HandlerExecutor>
    std::shared_ptr<Operation> launch(RestRequest request, Handler handler,
                                      const HandlerExecutor& handler_ex,
                                      asio::cancellation_slot user_slot) {
        auto complete = [handler_ex, user_slot](Handler h, std::exception_ptr ep,
                                                RawResponse res) mutable {
            asio::dispatch(handler_ex,
                           [h = std::move(h), ep, res = std::move(res), user_slot]() mutable {
                               // The slot belongs to the caller's executor, so it is released
                               // there.
                               if (user_slot.is_connected()) {
                                   user_slot.clear();
                               }
                               std::move(h)(ep, std::move(res));
                           });
        };
        if (stopping) {
            complete(std::move(handler), std::make_exception_ptr(RequestCancelledError()), {});
            return nullptr;
        }

        auto op = std::make_shared<Operation>();
        const auto it = operations.insert(operations.end(), op);
        asio::co_spawn(
            strand,
            [this, request = std::move(request)]() mutable -> asio::awaitable<RawResponse> {
                co_return co_await execute(std::move(request));
            },
            // Keeps `Impl` alive until the request completes; a shared executor would not.
            asio::bind_cancellation_slot(
                op->signal.slot(), [self = shared_from_this(), it, handler = std::move(handler),
                                    complete](std::exception_ptr ep, RawResponse res) mutable {
                    self->operations.erase(it);
                    complete(std::move(handler), std::move(ep), std::move(res));
                }));
        return op;
    }
};

RestClient::RestClient(RestApiConfig configuration, detail::ClientOptions options)
    : impl_(std::make_shared<Impl>(std::move(configuration),
                                   detail::user_agent_or_default(std::move(options.user_agent)))) {
    if (impl_->owned_ioc) {
        impl_->thread = std::thread([self = impl_] { self->run(); });
    }
}

// NOLINTNEXTLINE(bugprone-exception-escape): only std::bad_alloc, which ends the process anyway.
RestClient::~RestClient() {
    if (!impl_->owned_ioc) {
        // The cancelled requests complete on the shared executor and keep `Impl` alive.
        asio::dispatch(impl_->strand, [impl = impl_] { impl->shutdown(); });
        return;
    }
    // On the strand, or on the I/O thread through another executor: either way, the thread
    // cannot be joined from itself.
    if (impl_->strand.running_in_this_thread() ||
        std::this_thread::get_id() == impl_->thread.get_id()) {
        // Destroyed from one of our own handlers: the thread cannot join itself. It finishes the
        // cancelled requests and exits on its own, keeping `Impl` alive until then.
        impl_->shutdown();
        impl_->thread.detach();
        return;
    }
    asio::post(impl_->strand, [impl = impl_] { impl->shutdown(); });
    try {
        impl_->thread.join();
    } catch (const std::system_error& e) {
        Logger::error(std::string("RestClient: failed to join the I/O thread: ") + e.what());
    }
}

const RestApiConfig& RestClient::configuration() const noexcept {
    return impl_->cfg;
}

const SignatureGenerator& RestClient::signature_generator() const noexcept {
    return impl_->signer;
}

// NOLINTNEXTLINE(bugprone-exception-escape): bad_executor needs an empty executor, never the case.
asio::any_io_executor RestClient::get_executor() const noexcept {
    return impl_->strand;
}

void RestClient::start(RestRequest request, Handler handler) {
    auto handler_ex = asio::prefer(asio::get_associated_executor(handler, impl_->strand),
                                   asio::execution::outstanding_work.tracked);

    // Caller-side cancellation (`cancel_after`, `bind_cancellation_slot`, parallel groups, …) is
    // forwarded to the request on the strand.
    auto user_slot = asio::get_associated_cancellation_slot(handler);
    auto op_signal = std::make_shared<std::weak_ptr<Impl::Operation>>();
    if (user_slot.is_connected()) {
        // The slot may outlive the client, so it holds it only weakly.
        user_slot.assign(
            [weak = std::weak_ptr<Impl>(impl_), op_signal](asio::cancellation_type type) {
                const auto alive = weak.lock();
                if (!alive) {
                    return;
                }
                asio::post(alive->strand, [op_signal, type] {
                    if (const auto op = op_signal->lock()) {
                        op->signal.emit(type);
                    }
                });
            });
    }

    asio::dispatch(impl_->strand, [impl = impl_, request = std::move(request),
                                   handler = std::move(handler), handler_ex, user_slot,
                                   op_signal]() mutable {
        *op_signal = impl->launch(std::move(request), std::move(handler), handler_ex, user_slot);
    });
}

RawResponse RestClient::send_request(RestRequest request) {
    if (impl_->strand.running_in_this_thread()) {
        throw ConnectorClientError(
            "Blocking send_request called from the client's executor; use async_send_request");
    }
    return async_send_request(std::move(request), asio::use_future).get();
}

} // namespace binance::common
