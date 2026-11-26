//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include "websocket_common.hpp"

#include <algorithm>
#include <atomic>
#include <charconv>
#include <deque>
#include <type_traits>

#include <boost/asio/bind_cancellation_slot.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <binance/common/detail/utils.hpp>
#include <binance/common/logger.hpp>

#include "net.hpp"
#include "testing.hpp"
#include "utils.hpp"

namespace binance::common {

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace ssl = asio::ssl;
namespace websocket = beast::websocket;

namespace detail {

WebsocketConnectionFailureReason failure_reason_from_close_code(std::uint16_t code,
                                                                bool user_initiated) noexcept {
    using R = WebsocketConnectionFailureReason;
    if (user_initiated) {
        return R::UserInitiatedClose;
    }
    switch (code) {
    case 1000:
        return R::NormalClose;
    case 1001:
    case 1011:
    case 1012:
    case 1013:
    case 1014:
        return R::ServerTemporaryError;
    case 1002:
    case 1003:
    case 1007:
    case 1009:
    case 1010:
        return R::ProtocolViolation;
    case 1008:
        return R::PermanentServerError;
    case 1015:
        return R::ConfigurationError;
    default:
        break;
    }
    if (code >= 4000 && code <= 4999) {
        return R::PermanentServerError;
    }
    return R::UnexpectedClose;
}

namespace {

/// A TLS error that retrying cannot fix: certificate verification or protocol negotiation.
bool is_tls_configuration_error(const boost::system::error_code& ec) noexcept {
    const auto code = static_cast<unsigned long>(ec.value());
    if (ERR_GET_LIB(code) == ERR_LIB_X509) {
        return true;
    }
    if (ERR_GET_LIB(code) != ERR_LIB_SSL) {
        return false;
    }
    switch (ERR_GET_REASON(code)) {
    case SSL_R_CERTIFICATE_VERIFY_FAILED:
    case SSL_R_NO_CIPHERS_AVAILABLE:
    case SSL_R_NO_PROTOCOLS_AVAILABLE:
    case SSL_R_UNSUPPORTED_PROTOCOL:
        return true;
    default:
        return false;
    }
}

} // namespace

WebsocketConnectionFailureReason
failure_reason_from_error(const boost::system::error_code& ec) noexcept {
    using R = WebsocketConnectionFailureReason;
    if (ec == asio::error::connection_reset || ec == asio::error::connection_aborted ||
        ec == asio::error::broken_pipe || ec == websocket::error::closed) {
        return R::ConnectionReset;
    }
    if (ec == asio::error::eof || ec == http::error::end_of_stream ||
        ec == ssl::error::stream_truncated) {
        return R::StreamEnded;
    }
    if (ec == asio::error::access_denied || ec == boost::system::errc::permission_denied) {
        return R::AuthenticationFailure;
    }
    if (ec == websocket::error::message_too_big || ec == websocket::error::buffer_overflow ||
        (ec.category() == asio::error::get_ssl_category() && is_tls_configuration_error(ec))) {
        return R::ConfigurationError;
    }
    if (ec == websocket::condition::protocol_violation) {
        return R::ProtocolViolation;
    }
    return R::NetworkInterruption;
}

bool should_reconnect(WebsocketConnectionFailureReason reason) noexcept {
    using R = WebsocketConnectionFailureReason;
    switch (reason) {
    case R::NetworkInterruption:
    case R::ConnectionReset:
    case R::ServerTemporaryError:
    case R::UnexpectedClose:
    case R::StreamEnded:
    case R::ProtocolViolation:
    case R::NormalClose:
        return true;
    case R::AuthenticationFailure:
    case R::ConfigurationError:
    case R::UserInitiatedClose:
    case R::PermanentServerError:
        return false;
    }
    return false;
}

} // namespace detail

std::string_view to_string(WebsocketConnectionFailureReason reason) noexcept {
    using R = WebsocketConnectionFailureReason;
    switch (reason) {
    case R::NetworkInterruption:
        return "NetworkInterruption";
    case R::ConnectionReset:
        return "ConnectionReset";
    case R::ServerTemporaryError:
        return "ServerTemporaryError";
    case R::UnexpectedClose:
        return "UnexpectedClose";
    case R::StreamEnded:
        return "StreamEnded";
    case R::AuthenticationFailure:
        return "AuthenticationFailure";
    case R::ProtocolViolation:
        return "ProtocolViolation";
    case R::ConfigurationError:
        return "ConfigurationError";
    case R::UserInitiatedClose:
        return "UserInitiatedClose";
    case R::PermanentServerError:
        return "PermanentServerError";
    case R::NormalClose:
        return "NormalClose";
    }
    return "";
}

} // namespace binance::common

namespace binance::common::detail {

using Clock = std::chrono::steady_clock;
using tcp = asio::ip::tcp;

namespace {

std::atomic<std::chrono::milliseconds::rep> renewal_interval_override{0};

Clock::duration renewal_interval() noexcept {
    const auto ms = renewal_interval_override.load();
    return ms > 0 ? Clock::duration(std::chrono::milliseconds(ms))
                  : Clock::duration(WebsocketCommon::kRenewalInterval);
}

/// Beast pings after half of this without traffic and drops the connection after all of it.
/// Binance pings every 20 s (3 min on some products), so a live connection never gets there.
constexpr std::chrono::seconds kIdleTimeout{60};
constexpr std::size_t kMaxHandshakeBodyInError = 256;

using TlsStream = ssl::stream<beast::tcp_stream>;
using NestedTlsStream = ssl::stream<TlsStream>;

struct ConnectRoute {
    Endpoint target;
    std::optional<Endpoint> proxy;
    std::string proxy_authorization;
    std::optional<SocksRoute> socks;
    /// `Host` header and request target of the upgrade.
    std::string host;
    std::string path;
    /// Opens the TCP connection instead of resolving and connecting.
    const WebsocketTransportHook* transport = nullptr;
};

std::string what(const std::exception_ptr& ep) {
    try {
        std::rethrow_exception(ep);
    } catch (const std::exception& e) {
        return e.what();
    } catch (...) {
        return "unknown error";
    }
}

std::optional<std::chrono::seconds> parse_retry_after(std::string_view value) {
    std::uint32_t seconds = 0;
    const auto* end = value.data() + value.size();
    // NOLINTNEXTLINE(bugprone-suspicious-stringview-data-usage): bounded by `end`.
    const auto [ptr, ec] = std::from_chars(value.data(), end, seconds);
    if (ec != std::errc() || ptr != end) {
        return std::nullopt;
    }
    return std::chrono::seconds(seconds);
}

/// Whether the calling thread runs `ex`, or `nullopt` for an executor type it cannot tell.
template <class Ex> bool probe(const asio::any_io_executor& ex, std::optional<bool>& out) {
    if (const auto* e = ex.target<Ex>()) {
        out = e->running_in_this_thread();
        return true;
    }
    if (const auto* e = ex.target<asio::strand<Ex>>()) {
        out = e->get_inner_executor().running_in_this_thread();
        return true;
    }
    return false;
}

std::optional<bool> runs_in_this_thread(const asio::any_io_executor& ex) {
    using Io = asio::io_context::executor_type;
    using IoTracked = std::decay_t<decltype(asio::prefer(
        std::declval<const Io&>(), asio::execution::outstanding_work.tracked))>;
    using Pool = asio::thread_pool::executor_type;
    using PoolTracked = std::decay_t<decltype(asio::prefer(
        std::declval<const Pool&>(), asio::execution::outstanding_work.tracked))>;
    std::optional<bool> out;
    if (probe<Io>(ex, out) || probe<IoTracked>(ex, out) || probe<Pool>(ex, out) ||
        probe<PoolTracked>(ex, out)) {
        return out;
    }
    if (const auto* e = ex.target<asio::strand<asio::any_io_executor>>()) {
        return runs_in_this_thread(e->get_inner_executor());
    }
    return std::nullopt;
}

template <class Stream>
asio::awaitable<void> tunnel(Stream& stream, beast::flat_buffer& buffer, const ConnectRoute& r) {
    const auto status = co_await proxy_connect(stream, buffer, r.target, r.proxy_authorization);
    if (status < 200 || status >= 300) {
        throw WebsocketNetworkError("Proxy CONNECT failed with status " + std::to_string(status));
    }
}

} // namespace

/// A WebSocket over one of three layerings, chosen by the route:
/// - `tcp_stream`: ws://, directly or through an http proxy's tunnel;
/// - `TlsStream`: wss:// directly or through an http proxy, or ws:// through an https proxy;
/// - `NestedTlsStream`: wss:// through an https proxy (TLS to the target inside TLS to the proxy).
///
/// The whole stack is built before any I/O, so no layer is moved once in use.
class Socket : public std::enable_shared_from_this<Socket> {
public:
    struct Outgoing {
        OutKind kind;
        std::string data;
    };

    Socket() = default;
    virtual ~Socket() = default;
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket&&) = delete;
    Socket& operator=(Socket&&) = delete;

    virtual void configure(const WebsocketSettings& settings) = 0;
    /// DNS, TCP, proxy tunnel, TLS and the upgrade, all before `deadline`. Throws
    /// `WebsocketError` or `boost::system::system_error`.
    virtual asio::awaitable<void> establish(const ConnectRoute& route,
                                            std::chrono::milliseconds connect_timeout,
                                            Clock::time_point deadline) = 0;
    virtual asio::awaitable<void> read(beast::flat_buffer& buffer,
                                       boost::system::error_code& ec) = 0;
    [[nodiscard]] virtual bool got_binary() const = 0;
    virtual asio::awaitable<void> write(OutKind kind, const std::string& data,
                                        boost::system::error_code& ec) = 0;
    [[nodiscard]] virtual websocket::close_reason reason() const = 0;
    /// Closes the TCP socket at once; pending operations fail.
    virtual void abort() noexcept = 0;
    virtual void set_control_callback(std::function<void(websocket::frame_type)> callback) = 0;

    std::deque<Outgoing> outbox;
    bool writing = false;
    bool close_queued = false;
};

namespace {

template <class Next> class BeastSocket final : public Socket {
public:
    template <class... Args>
    explicit BeastSocket(Args&&... args) : ws_(std::forward<Args>(args)...) {}

    void configure(const WebsocketSettings& settings) override {
        ws_.set_option(websocket::stream_base::decorator(
            [ua = settings.user_agent, headers = settings.headers](websocket::request_type& req) {
                if (!ua.empty()) {
                    req.set(http::field::user_agent, ua);
                }
                for (const auto& [name, value] : headers) {
                    req.set(name, value);
                }
            }));
        if (settings.compression) {
            websocket::permessage_deflate pmd;
            pmd.client_enable = true;
            ws_.set_option(pmd);
        }
        ws_.read_message_max(settings.max_message_size);
        ws_.auto_fragment(false);
    }

    asio::awaitable<void> establish(const ConnectRoute& r,
                                    std::chrono::milliseconds connect_timeout,
                                    Clock::time_point deadline) override {
        auto& lowest = beast::get_lowest_layer(ws_);
        boost::system::error_code ec;
        if (r.transport != nullptr) {
            co_await open_with(*r.transport, r.target, deadline);
        } else {
            const Endpoint* via = &r.target;
            if (r.socks) {
                via = &r.socks->server;
            } else if (r.proxy) {
                via = &*r.proxy;
            }
            const auto results = co_await resolve(*via, deadline);
            co_await connect_staggered(lowest.socket(), interleave_families(results), deadline);
        }
        lowest.expires_at(deadline);
        lowest.socket().set_option(tcp::no_delay(true), ec);
        if (r.socks) {
            co_await socks5_connect(lowest, r.target, *r.socks, deadline);
        }

        beast::flat_buffer buffer;
        if constexpr (std::is_same_v<Next, beast::tcp_stream>) {
            if (r.proxy) {
                co_await tunnel(lowest, buffer, r);
            }
        } else if constexpr (std::is_same_v<Next, TlsStream>) {
            if (r.proxy && r.proxy->tls) {
                co_await tls_handshake(ws_.next_layer(), r.proxy->host, "proxy TLS handshake");
                co_await tunnel(ws_.next_layer(), buffer, r);
            } else {
                if (r.proxy) {
                    co_await tunnel(lowest, buffer, r);
                }
                co_await tls_handshake(ws_.next_layer(), r.target.host, "TLS handshake");
            }
        } else {
            static_assert(std::is_same_v<Next, NestedTlsStream>);
            co_await tls_handshake(ws_.next_layer().next_layer(), r.proxy->host,
                                   "proxy TLS handshake");
            co_await tunnel(ws_.next_layer().next_layer(), buffer, r);
            co_await tls_handshake(ws_.next_layer(), r.target.host, "TLS handshake");
        }

        websocket::response_type res;
        co_await ws_.async_handshake(res, r.host, r.path,
                                     asio::redirect_error(asio::use_awaitable, ec));
        if (ec) {
            if (ec == websocket::error::upgrade_declined) {
                const auto status = static_cast<std::uint16_t>(res.result_int());
                std::string msg = "HTTP " + std::to_string(status);
                if (!res.body().empty()) {
                    msg += ": " + res.body().substr(0, kMaxHandshakeBodyInError);
                }
                throw WebsocketHandshakeError(msg, status,
                                              parse_retry_after(res[http::field::retry_after]));
            }
            throw_network(ec, "WebSocket handshake");
        }

        // From here on Beast's own timeouts apply: they cover the close handshake and detect
        // dead peers with pings.
        lowest.expires_never();
        websocket::stream_base::timeout timeout{};
        timeout.handshake_timeout = connect_timeout;
        timeout.idle_timeout = kIdleTimeout;
        timeout.keep_alive_pings = true;
        ws_.set_option(timeout);
    }

    asio::awaitable<void> read(beast::flat_buffer& buffer, boost::system::error_code& ec) override {
        co_await ws_.async_read(buffer, asio::redirect_error(asio::use_awaitable, ec));
    }

    [[nodiscard]] bool got_binary() const override { return ws_.got_binary(); }

    asio::awaitable<void> write(OutKind kind, const std::string& data,
                                boost::system::error_code& ec) override {
        switch (kind) {
        case OutKind::Text:
            ws_.text(true);
            co_await ws_.async_write(asio::buffer(data),
                                     asio::redirect_error(asio::use_awaitable, ec));
            break;
        case OutKind::Ping:
            co_await ws_.async_ping({}, asio::redirect_error(asio::use_awaitable, ec));
            break;
        case OutKind::Close:
            co_await ws_.async_close(websocket::close_code::normal,
                                     asio::redirect_error(asio::use_awaitable, ec));
            break;
        }
    }

    [[nodiscard]] websocket::close_reason reason() const override { return ws_.reason(); }

    void abort() noexcept override { beast::get_lowest_layer(ws_).close(); }

    void set_control_callback(std::function<void(websocket::frame_type)> callback) override {
        ws_.control_callback([cb = std::move(callback)](websocket::frame_type kind,
                                                        beast::string_view) { cb(kind); });
    }

private:
    /// Runs the transport hook, closing the socket if it is still running at `deadline`.
    asio::awaitable<void> open_with(const WebsocketTransportHook& transport, const Endpoint& target,
                                    Clock::time_point deadline) {
        auto& socket = beast::get_lowest_layer(ws_).socket();
        const auto guard = std::make_shared<asio::steady_timer>(socket.get_executor(), deadline);
        guard->async_wait([weak = weak_from_this(), guard](const boost::system::error_code& ec) {
            if (const auto self = weak.lock(); self && !ec) {
                self->abort();
            }
        });
        std::uint16_t port = 0;
        std::from_chars(target.port.data(), target.port.data() + target.port.size(), port);
        std::exception_ptr error;
        try {
            co_await transport(socket, target.host, port);
        } catch (...) {
            error = std::current_exception();
        }
        guard->cancel();
        if (Clock::now() >= deadline) {
            throw WebsocketTimeoutError();
        }
        if (error) {
            std::rethrow_exception(error);
        }
        if (!socket.is_open()) {
            throw WebsocketNetworkError("the transport hook did not open the socket");
        }
    }

    websocket::stream<Next> ws_;
};

} // namespace

Connection::Connection(const asio::any_io_executor& ex)
    : id(detail::random_string()), renewal_timer(ex), retry_timer(ex), ping_timer(ex) {}

bool DeliveryGate::enter() noexcept {
    ++active_;
    if (open_) {
        return true;
    }
    leave();
    return false;
}

void DeliveryGate::leave() noexcept {
    if (--active_ == 0) {
        active_.notify_all();
    }
}

void DeliveryGate::close(bool wait) noexcept {
    open_ = false;
    if (!wait) {
        return;
    }
    for (auto n = active_.load(); n != 0; n = active_.load()) {
        active_.wait(n);
    }
}

namespace {

/// Stream callbacks this thread is in.
thread_local std::uint32_t delivering = 0;

/// Runs `fn(arg)` through `dispatch` if `allowed()` still holds there, logging what it throws.
template <class Arg>
void run_on_executor(const CallbackDispatch& dispatch, const std::function<void(const Arg&)>& fn,
                     const Arg& arg, std::function<bool()> allowed) {
    dispatch([fn, arg, allowed = std::move(allowed)] {
        if (!allowed()) {
            return;
        }
        try {
            fn(arg);
        } catch (const std::exception& e) {
            Logger::error(std::string("WebSocket callback threw: ") + e.what());
        } catch (...) {
            Logger::error("WebSocket callback threw");
        }
    });
}

void invoke(const std::shared_ptr<StreamSlot>& slot, const boost::json::value& payload,
            DeliveryGate& gate) {
    if (slot->dispatch) {
        // Queued on its own executor: checked again there, as it may be unsubscribed (or the
        // client destroyed) meanwhile.
        run_on_executor(
            slot->dispatch, slot->callback, payload,
            [slot, gate = gate.shared_from_this()] { return slot->active && gate->is_open(); });
        return;
    }
    // Counted before `active` is checked again, so that `wait_until_idle` sees this call.
    ++slot->running;
    ++delivering;
    if (slot->active) {
        try {
            slot->callback(payload);
        } catch (const std::exception& e) {
            Logger::error(std::string("WebSocket stream callback threw: ") + e.what());
        } catch (...) {
            Logger::error("WebSocket stream callback threw");
        }
    }
    --delivering;
    if (--slot->running == 0) {
        slot->running.notify_all();
    }
}

} // namespace

void wait_until_idle(const std::vector<std::shared_ptr<StreamSlot>>& slots) noexcept {
    // Within a callback, on the strand: no other callback can be running.
    if (delivering != 0) {
        return;
    }
    for (const auto& slot : slots) {
        for (auto n = slot->running.load(); n != 0; n = slot->running.load()) {
            slot->running.wait(n);
        }
    }
}

void StreamListeners::add(std::shared_ptr<StreamSlot> slot, DeliveryGate& gate) {
    slots_.push_back(slot);
    if (!std::exchange(buffering_, false)) {
        return;
    }
    // Moved out: a callback may drop these listeners.
    const auto backlog = std::exchange(backlog_, {});
    for (const auto& payload : backlog) {
        const DeliveryGate::Pass pass(gate);
        if (!pass || !slot->active) {
            return;
        }
        invoke(slot, payload, gate);
    }
}

void StreamListeners::remove(const std::vector<std::shared_ptr<StreamSlot>>& slots) {
    std::erase_if(slots_, [&slots](const auto& s) {
        return std::find(slots.begin(), slots.end(), s) != slots.end();
    });
}

void StreamListeners::deliver(const boost::json::value& payload, DeliveryGate& gate) {
    if (slots_.empty()) {
        if (buffering_) {
            if (backlog_.size() == kMaxBacklog) {
                backlog_.pop_front();
            }
            backlog_.push_back(payload);
        }
        return;
    }
    // Copied: a callback may remove itself, or drop these listeners.
    const auto slots = slots_;
    for (const auto& slot : slots) {
        const DeliveryGate::Pass pass(gate);
        if (!pass) {
            return;
        }
        if (slot->active) {
            invoke(slot, payload, gate);
        }
    }
}

WebsocketCommon::WebsocketCommon(WebsocketSettings settings, const std::string& url,
                                 std::size_t count)
    : settings_(std::move(settings)), tls_(ssl::context::tls_client),
      strand_(asio::make_strand(base_executor())) {
    const auto target = parse_url(url, "ws", "wss", "url");
    (void)make_proxy_route(settings_.proxy, settings_.proxy_from_env, target);
    init_tls_context(tls_, settings_.agent);
    connections.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        connections.push_back(std::make_unique<Connection>(strand_));
    }
}

WebsocketCommon::~WebsocketCommon() = default;

asio::any_io_executor WebsocketCommon::base_executor() {
    if (settings_.executor != nullptr) {
        return settings_.executor;
    }
    work_.emplace(owned_ioc_.emplace(1).get_executor());
    return owned_ioc_->get_executor();
}

void WebsocketCommon::start() {
    if (owned_ioc_) {
        thread_ = std::thread([self = shared_from_this()] { self->run(); });
    }
}

bool WebsocketCommon::may_block() const noexcept {
    if (on_io_thread()) {
        return false;
    }
    return !runs_in_this_thread(strand_.get_inner_executor()).value_or(false);
}

// NOLINTNEXTLINE(bugprone-exception-escape): only std::bad_alloc, which ends the process anyway.
void WebsocketCommon::stop() noexcept {
    // A callback running on another thread finishes before the client is gone.
    // The I/O thread may also run code outside the strand (a handler bound to the inner
    // executor): it cannot wait for itself, nor join itself.
    const bool own_thread =
        on_io_thread() || (owned_ioc_ && std::this_thread::get_id() == thread_.get_id());
    gate_->close(!own_thread);
    {
        const std::lock_guard lock(post_mutex_);
        accepting_ = false;
    }
    if (!owned_ioc_) {
        // The cancelled operations complete on the shared executor and keep this object alive.
        asio::dispatch(strand_, [self = shared_from_this()] { self->shutdown(); });
        return;
    }
    if (own_thread) {
        // Destroyed from one of our own callbacks: the thread cannot join itself. It finishes
        // the cancelled operations and exits on its own, keeping this object alive until then.
        shutdown();
        thread_.detach();
        return;
    }
    asio::post(strand_, [self = shared_from_this()] { self->shutdown(); });
    try {
        thread_.join();
    } catch (const std::system_error& e) {
        Logger::error(settings_.name + ": failed to join the I/O thread: " + e.what());
    }
}

void WebsocketCommon::run() noexcept {
    for (;;) {
        try {
            owned_ioc_->run();
            return;
        } catch (const std::exception& e) {
            Logger::error(std::string("Exception escaped a WebSocket handler: ") + e.what());
        } catch (...) {
            Logger::error("Unknown exception escaped a WebSocket handler");
        }
    }
}

void WebsocketCommon::shutdown() {
    stopping_ = true;
    const auto cancelled = std::make_exception_ptr(WebsocketCancelledError(true));
    for (const auto& c : connections) {
        auto& conn = *c;
        ++conn.retry_generation;
        ++conn.renewal_generation;
        ++conn.ping_generation;
        conn.retry_timer.cancel();
        conn.renewal_timer.cancel();
        conn.ping_timer.cancel();
        conn.connect_signal.emit(asio::cancellation_type::terminal);
        if (conn.opening) {
            conn.opening->abort();
        }
        if (conn.socket) {
            conn.socket->abort();
        }
        for (const auto& old : conn.retired) {
            old->abort();
        }
        fail_requests(conn, nullptr, cancelled);
        finish_connect_waiters(conn, std::make_exception_ptr(WebsocketCancelledError()));
    }
    on_shutdown();
    event_callbacks_.clear();
    notify();
    work_.reset();
    connected_ = false;
}

template <class Awaitable> void WebsocketCommon::spawn(Awaitable&& a) {
    // The completion handler holds this object until the coroutine finishes.
    asio::co_spawn(strand_, std::forward<Awaitable>(a),
                   [self = shared_from_this()](std::exception_ptr ep) {
                       if (ep) {
                           Logger::error(self->settings_.name + ": " + what(ep));
                       }
                   });
}

void WebsocketCommon::notify() {
    refresh_connected();
    for (const auto& timer : std::exchange(waiters_, {})) {
        timer->cancel();
    }
}

void WebsocketCommon::refresh_connected() noexcept {
    connected_ = !stopping_ && is_connected();
}

asio::awaitable<bool> WebsocketCommon::wait_until(std::function<bool()> done,
                                                  Clock::time_point deadline) {
    while (!done()) {
        if (Clock::now() >= deadline) {
            co_return false;
        }
        auto timer = std::make_shared<asio::steady_timer>(strand_, deadline);
        waiters_.push_back(timer);
        boost::system::error_code ec;
        co_await timer->async_wait(asio::redirect_error(asio::use_awaitable, ec));
        std::erase(waiters_, timer);
    }
    co_return true;
}

Subscription WebsocketCommon::add_event_callback(Callback<WebsocketEvent> callback,
                                                 bool with_messages) {
    auto slot = std::make_shared<EventSlot>(std::move(callback), with_messages);
    const auto id = ++next_callback_id_;
    execute_or_post([this, slot, id] { event_callbacks_.emplace(id, slot); });
    return Subscription([weak = weak_from_this(), slot, id] {
        slot->active = false;
        if (const auto self = weak.lock()) {
            // A call in progress on another thread finishes first (on the strand, none can be).
            if (!self->on_io_thread()) {
                for (auto n = slot->running.load(); n != 0; n = slot->running.load()) {
                    slot->running.wait(n);
                }
            }
            self->post([self = self.get(), id] { self->event_callbacks_.erase(id); });
        }
    });
}

void WebsocketCommon::emit(WebsocketEvent event) {
    if (event_callbacks_.empty() || stopping_) {
        return;
    }
    // Copied: a callback may unsubscribe (itself or another) while we iterate.
    std::vector<std::shared_ptr<EventSlot>> callbacks;
    callbacks.reserve(event_callbacks_.size());
    for (const auto& entry : event_callbacks_) {
        if (event.type != WebsocketEventType::Message || entry.second->messages) {
            callbacks.push_back(entry.second);
        }
    }
    for (const auto& slot : callbacks) {
        const DeliveryGate::Pass pass(*gate_);
        if (!pass) {
            return;
        }
        if (slot->dispatch) {
            if (slot->active) {
                run_on_executor(slot->dispatch, slot->callback, event,
                                [slot, gate = gate_] { return slot->active && gate->is_open(); });
            }
            continue;
        }
        // Counted before `active` is checked, so that removing the callback sees this call.
        ++slot->running;
        if (slot->active) {
            try {
                slot->callback(event);
            } catch (const std::exception& e) {
                Logger::error(settings_.name + ": event callback threw: " + e.what());
            } catch (...) {
                Logger::error(settings_.name + ": event callback threw");
            }
        }
        if (--slot->running == 0) {
            slot->running.notify_all();
        }
    }
}

// ---- Connecting ----

void WebsocketCommon::connect_connections(const std::vector<Connection*>& targets,
                                          const std::function<std::string(Connection&)>& url_for,
                                          std::function<void(std::exception_ptr)> done) {
    if (stopping_) {
        run_handler([&] { done(std::make_exception_ptr(WebsocketCancelledError())); });
        return;
    }
    if (disconnecting_ != 0 || closing(targets)) {
        Logger::info(settings_.name + ": connecting once the disconnect in progress completes");
        spawn(connect_after_close(targets, url_for, std::move(done)));
        return;
    }
    struct State {
        std::size_t remaining = 0;
        std::exception_ptr error;
        std::function<void(std::exception_ptr)> done;
        std::vector<Connection*> started;
    };
    auto state = std::make_shared<State>();
    state->done = std::move(done);

    std::vector<Connection*> to_start;
    for (auto* conn : targets) {
        if (conn->socket) {
            continue;
        }
        conn->close_initiated = false;
        conn->failed = false;
        conn->failures = 0;
        ++state->remaining;
        state->started.push_back(conn);
        conn->connect_waiters.emplace_back([this, state](std::exception_ptr ep) {
            if (ep && !state->error) {
                state->error = ep;
            }
            if (--state->remaining != 0) {
                return;
            }
            // Part of the pool opened: the rest keeps retrying in the background.
            if (state->error && std::any_of(state->started.begin(), state->started.end(),
                                            [](const auto* c) { return c->socket != nullptr; })) {
                for (auto* c : state->started) {
                    if (!c->socket && !c->connecting) {
                        schedule_reconnect(*c);
                    }
                }
            }
            run_handler([&] { state->done(state->error); });
        });
        if (!conn->connecting) {
            to_start.push_back(conn);
        }
    }
    if (state->remaining == 0) {
        Logger::info(settings_.name + ": already connected");
        run_handler([&] { state->done(nullptr); });
        return;
    }
    for (auto* conn : to_start) {
        // Connecting now supersedes a scheduled reconnect.
        ++conn->retry_generation;
        conn->retry_timer.cancel();
        conn->reconnect_scheduled = false;
        start_connect(*conn, url_for(*conn), false);
    }
}

bool WebsocketCommon::closing(const std::vector<Connection*>& targets) noexcept {
    return std::any_of(targets.begin(), targets.end(), [](const Connection* c) {
        return c->close_initiated && (c->socket || c->connecting);
    });
}

asio::awaitable<void>
WebsocketCommon::connect_after_close(std::vector<Connection*> targets,
                                     std::function<std::string(Connection&)> url_for,
                                     std::function<void(std::exception_ptr)> done) {
    const bool closed = co_await wait_until(
        [this, &targets] { return stopping_ || (disconnecting_ == 0 && !closing(targets)); },
        Clock::now() + kDrainTimeout + 2 * settings_.connect_timeout);
    if (!closed) {
        run_handler([&] { done(std::make_exception_ptr(WebsocketTimeoutError())); });
        co_return;
    }
    connect_connections(targets, url_for, std::move(done));
}

void WebsocketCommon::start_connect(Connection& conn, std::string url, bool is_renewal) {
    conn.connecting = true;
    if (Logger::enabled(LogLevel::Debug)) {
        Logger::debug(settings_.name + ": connecting " + conn.id +
                      (is_renewal ? " (renewal)" : "") + " to " + url);
    }
    asio::co_spawn(strand_, open_socket(conn, std::move(url)),
                   asio::bind_cancellation_slot(
                       conn.connect_signal.slot(),
                       [self = shared_from_this(), &conn,
                        is_renewal](std::exception_ptr ep, std::shared_ptr<Socket> socket) {
                           conn.connecting = false;
                           conn.opening.reset();
                           self->on_connected(conn, is_renewal, ep, std::move(socket));
                       }));
}

asio::awaitable<std::shared_ptr<Socket>> WebsocketCommon::open_socket(Connection& conn,
                                                                      std::string url) {
    ConnectRoute route;
    route.target = parse_url(url, "ws", "wss", "url");
    if (settings_.transport) {
        route.transport = &settings_.transport;
    } else {
        auto proxy = make_proxy_route(settings_.proxy, settings_.proxy_from_env, route.target);
        route.proxy = std::move(proxy.proxy);
        route.proxy_authorization = std::move(proxy.authorization);
        route.socks = std::move(proxy.socks);
    }
    route.host = route.target.authority();
    route.path = route.target.prefix.empty() ? "/" : route.target.prefix;
    if (!route.target.query.empty()) {
        route.path += "?" + route.target.query;
    }

    const asio::any_io_executor ex = strand_;
    std::shared_ptr<Socket> socket;
    const bool proxy_tls = route.proxy && route.proxy->tls;
    if (route.target.tls && proxy_tls) {
        socket = std::make_shared<BeastSocket<NestedTlsStream>>(TlsStream(ex, tls_), tls_);
    } else if (route.target.tls || proxy_tls) {
        socket = std::make_shared<BeastSocket<TlsStream>>(ex, tls_);
    } else {
        socket = std::make_shared<BeastSocket<beast::tcp_stream>>(ex);
    }
    socket->configure(settings_);
    conn.opening = socket;

    try {
        co_await socket->establish(route, settings_.connect_timeout,
                                   Clock::now() + settings_.connect_timeout);
    } catch (const WebsocketError&) {
        throw;
    } catch (const boost::system::system_error& e) {
        if (e.code() == beast::error::timeout) {
            throw WebsocketTimeoutError();
        }
        throw WebsocketNetworkError(error_message(e), false, e.code());
    } catch (const std::exception& e) {
        throw WebsocketNetworkError(e.what());
    }
    co_return socket;
}

void WebsocketCommon::finish_connect_waiters(Connection& conn, std::exception_ptr error) {
    refresh_connected();
    for (const auto& waiter : std::exchange(conn.connect_waiters, {})) {
        run_handler([&] { waiter(error); });
    }
}

void WebsocketCommon::on_connected(Connection& conn, bool is_renewal, std::exception_ptr error,
                                   std::shared_ptr<Socket> socket) {
    if (stopping_) {
        if (socket) {
            socket->abort();
        }
        finish_connect_waiters(conn, std::make_exception_ptr(WebsocketCancelledError()));
        return;
    }

    if (error) {
        // NOLINTNEXTLINE(clang-analyzer-deadcode.DeadStores): read in every branch below.
        const auto msg = what(error);
        conn.retry_after.reset();
        try {
            std::rethrow_exception(error);
        } catch (const WebsocketHandshakeError& e) {
            conn.retry_after = e.retry_after();
        } catch (...) { // NOLINT(bugprone-empty-catch): no Retry-After; the error is logged below
        }
        if (is_renewal && conn.socket) {
            // The old socket still serves: retry the renewal, without counting it as a failed
            // reconnect.
            conn.renewal_pending = false;
            Logger::warn(settings_.name + ": renewal of connection " + conn.id + " failed: " + msg);
            auto delay = retry_delay(conn.renewal_failures++);
            if (conn.retry_after) {
                delay = std::max<std::chrono::milliseconds>(delay, *conn.retry_after);
            }
            arm_renewal(conn, delay);
        } else if (is_renewal) {
            conn.renewal_pending = false;
            ++conn.failures;
            Logger::warn(settings_.name + ": renewal of connection " + conn.id + " failed: " + msg);
            schedule_reconnect(conn);
        } else {
            ++conn.failures;
            Logger::error(settings_.name + ": connection " + conn.id + " failed: " + msg);
            if (conn.reconnection_pending) {
                // A failed reconnect is retried until disconnect().
                schedule_reconnect(conn);
            }
        }
        finish_connect_waiters(conn, error);
        emit({WebsocketEventType::Error, msg, 0, conn.id});
        notify();
        return;
    }

    if (conn.close_initiated) {
        // disconnect() ran while this socket was opening: close it without using it.
        conn.retired.push_back(socket);
        spawn(read_loop(conn, socket));
        enqueue(socket, OutKind::Close, {});
        conn.renewal_pending = false;
        finish_connect_waiters(conn, std::make_exception_ptr(WebsocketCancelledError()));
        notify();
        return;
    }

    std::shared_ptr<Socket> old;
    if (is_renewal) {
        conn.renewal_pending = false;
        old = std::exchange(conn.socket, socket);
    } else {
        conn.socket = socket;
    }
    // A renewal whose old socket died meanwhile counts as a reconnect.
    const bool reopened = !old;
    if (reopened) {
        conn.opened_at = Clock::now();
    }
    conn.reconnection_pending = false;
    conn.failed = false;
    conn.renewal_failures = 0;
    conn.retry_after.reset();
    // A new socket is never logged on, renewed or not: `on_open` logs it on again.
    conn.is_session_logged_on = false;
    conn.restoring = 0;
    conn.resubscribed = false;

    socket->set_control_callback([this, id = conn.id](websocket::frame_type kind) {
        if (kind == websocket::frame_type::ping) {
            emit({WebsocketEventType::Ping, {}, 0, id});
        } else if (kind == websocket::frame_type::pong) {
            emit({WebsocketEventType::Pong, {}, 0, id});
        }
    });
    spawn(read_loop(conn, socket));
    arm_renewal(conn, renewal_interval());
    if (old) {
        conn.retired.push_back(old);
    }
    Logger::info(settings_.name + ": connection " + conn.id + (old ? " renewed" : " established"));

    try {
        on_open(conn);
    } catch (const std::exception& e) {
        Logger::error(settings_.name + ": on_open failed for " + conn.id + ": " + e.what());
    }
    if (old) {
        spawn(close_gracefully(conn, old, true));
    }
    if (reopened) {
        emit({WebsocketEventType::Open, {}, 0, conn.id});
    }
    finish_connect_waiters(conn, nullptr);
    notify();
}

void WebsocketCommon::schedule_reconnect(Connection& conn) {
    if (stopping_ || conn.close_initiated) {
        return;
    }
    conn.reconnection_pending = true;
    conn.is_session_logged_on = false;
    if (conn.reconnect_scheduled) {
        return;
    }
    conn.reconnect_scheduled = true;
    const auto generation = ++conn.retry_generation;
    const auto delay = backoff(conn, conn.failures);
    Logger::info(settings_.name + ": reconnecting " + conn.id + " in " +
                 std::to_string(delay.count()) + "ms");
    conn.retry_timer.expires_after(delay);
    conn.retry_timer.async_wait(
        [self = shared_from_this(), &conn, generation](const boost::system::error_code& ec) {
            self->on_retry_timer(conn, generation, ec);
        });
}

std::chrono::milliseconds WebsocketCommon::retry_delay(std::uint32_t attempt) {
    using std::chrono::milliseconds;
    auto delay = milliseconds(kRetryBaseDelay);
    for (std::uint32_t i = 0; i < attempt && delay < kRetryMaxDelay; ++i) {
        delay *= 2;
    }
    const auto half = std::min<milliseconds>(delay, kRetryMaxDelay) / 2;
    // "Equal jitter": a random value in the upper half, so pool connections do not retry in
    // lockstep.
    const auto jitter = static_cast<milliseconds::rep>(
        static_cast<double>(half.count()) *
        (static_cast<double>(detail::random_integer()) / 4294967296.0));
    return half + milliseconds(jitter);
}

std::chrono::milliseconds WebsocketCommon::backoff(const Connection& conn,
                                                   std::uint32_t failures) const {
    auto delay = settings_.reconnect_delay;
    if (failures > 0) {
        delay += retry_delay(failures - 1);
    }
    if (conn.retry_after) {
        delay = std::max<std::chrono::milliseconds>(delay, *conn.retry_after);
    }
    return delay;
}

void WebsocketCommon::on_retry_timer(Connection& conn, std::uint64_t generation,
                                     const boost::system::error_code& ec) {
    if (ec || stopping_ || generation != conn.retry_generation) {
        return;
    }
    const auto now = Clock::now();
    if (now < next_connect_at_) {
        conn.retry_timer.expires_at(next_connect_at_);
        conn.retry_timer.async_wait(
            [self = shared_from_this(), &conn, generation](const boost::system::error_code& e) {
                self->on_retry_timer(conn, generation, e);
            });
        return;
    }
    next_connect_at_ = now + kReconnectThrottle;
    conn.reconnect_scheduled = false;
    if (conn.close_initiated || conn.socket || conn.connecting) {
        return;
    }
    start_connect(conn, reconnect_url(conn), false);
}

void WebsocketCommon::arm_renewal(Connection& conn, Clock::duration delay) {
    const auto generation = ++conn.renewal_generation;
    conn.renewal_timer.expires_after(delay);
    conn.renewal_timer.async_wait(
        [self = shared_from_this(), &conn, generation](const boost::system::error_code& ec) {
            if (ec || self->stopping_ || generation != conn.renewal_generation) {
                return;
            }
            self->renew(conn);
        });
}

void WebsocketCommon::renew(Connection& conn) {
    if (stopping_ || conn.close_initiated || conn.renewal_pending || conn.connecting ||
        !conn.socket || conn.reconnection_pending) {
        return;
    }
    const auto now = Clock::now();
    if (now < next_connect_at_) {
        arm_renewal(conn, next_connect_at_ - now);
        return;
    }
    next_connect_at_ = now + kReconnectThrottle;
    conn.renewal_pending = true;
    Logger::info(settings_.name + ": renewing connection " + conn.id);
    // Built only now: building it hands the queued subscriptions to the new URL.
    start_connect(conn, reconnect_url(conn), true);
}

// ---- Reading and writing ----

asio::awaitable<void> WebsocketCommon::read_loop(Connection& conn, std::shared_ptr<Socket> socket) {
    beast::flat_buffer buffer;
    boost::system::error_code ec;
    for (;;) {
        co_await socket->read(buffer, ec);
        if (ec || stopping_) {
            break;
        }
        // A flat_buffer is contiguous, so text frames are read in place.
        const auto data = buffer.cdata();
        std::string_view text(static_cast<const char*>(data.data()), data.size());
        std::string inflated;
        if (socket->got_binary()) {
            if (inflate(text, settings_.max_message_size, inflated) != InflateStatus::Ok) {
                buffer.consume(buffer.size());
                Logger::error(settings_.name + ": failed to decompress a binary message on " +
                              conn.id);
                continue;
            }
            text = inflated;
        }
        const bool retired = socket != conn.socket;
        bool as_event = true;
        try {
            as_event = on_message(conn, *socket, text, retired);
        } catch (const std::exception& e) {
            Logger::error(settings_.name + ": failed to handle a message: " + e.what());
        }
        if (as_event && std::ranges::any_of(event_callbacks_, [](const auto& entry) {
                return entry.second->messages;
            })) {
            emit({WebsocketEventType::Message, std::string(text), 0, conn.id});
        }
        buffer.consume(buffer.size());
    }
    on_socket_closed(conn, socket, ec);
}

void WebsocketCommon::on_socket_closed(Connection& conn, const std::shared_ptr<Socket>& socket,
                                       const boost::system::error_code& ec) {
    if (const auto it = std::find(conn.retired.begin(), conn.retired.end(), socket);
        it != conn.retired.end()) {
        conn.retired.erase(it);
        if (!stopping_) {
            fail_requests(conn, socket.get(), std::make_exception_ptr(WebsocketNoResponseError()));
            Logger::debug(settings_.name + ": previous socket of " + conn.id + " closed");
        }
        notify();
        return;
    }
    if (conn.socket != socket) {
        return;
    }
    conn.socket.reset();
    // The renewal of that socket is moot; the reconnect arms a new one when it opens.
    ++conn.renewal_generation;
    conn.renewal_timer.cancel();
    conn.is_session_logged_on = false;
    conn.restoring = 0;
    conn.resubscribed = false;
    if (stopping_) {
        refresh_connected();
        return;
    }
    socket->outbox.clear();
    socket->abort();
    fail_requests(conn, socket.get(), std::make_exception_ptr(WebsocketNoResponseError()));

    WebsocketConnectionFailureReason reason{};
    // A close frame was received, either by the read or by our own close handshake (the read
    // then ends with another error).
    const auto close = socket->reason();
    if (ec == websocket::error::closed || close.code != websocket::close_code::none) {
        const auto code = static_cast<std::uint16_t>(close.code);
        reason = failure_reason_from_close_code(code, conn.close_initiated);
        Logger::info(
            settings_.name + ": connection " + conn.id + " closed: code=" + std::to_string(code) +
            (close.reason.empty() ? std::string() : " reason='" + std::string(close.reason) + "'") +
            ", classified as " + std::string(to_string(reason)));
        emit({WebsocketEventType::Close, std::string(close.reason), code, conn.id});
    } else {
        if (conn.close_initiated) {
            reason = WebsocketConnectionFailureReason::UserInitiatedClose;
        } else if (ec) {
            reason = failure_reason_from_error(ec);
        } else {
            reason = WebsocketConnectionFailureReason::StreamEnded;
        }
        if (!conn.close_initiated) {
            Logger::warn(settings_.name + ": connection " + conn.id + " lost: " + ec.message() +
                         ", classified as " + std::string(to_string(reason)));
            emit({WebsocketEventType::Error, ec.message(), 0, conn.id});
        }
        // No close frame: 1006 (abnormal closure).
        emit({WebsocketEventType::Close, {}, 1006, conn.id});
    }

    if (conn.renewal_pending) {
        // The renewal in flight replaces this socket (or schedules a reconnect if it fails).
        notify();
        return;
    }
    if (!conn.close_initiated && should_reconnect(reason)) {
        // The first quick close still reconnects after `reconnect_delay`; repeated ones back off.
        const bool stable = Clock::now() - conn.opened_at >= kStableConnection;
        if (stable) {
            conn.failures = 0;
        }
        schedule_reconnect(conn);
        if (!stable) {
            ++conn.failures;
        }
    } else if (!conn.close_initiated) {
        const auto msg = "[CRITICAL] Connection " + conn.id +
                         " permanently failed: " + std::string(to_string(reason));
        Logger::error(settings_.name + ": " + msg);
        conn.failed = true;
        emit({WebsocketEventType::Error, msg, 0, conn.id});
        try {
            on_connection_failed(conn);
        } catch (const std::exception& e) {
            Logger::error(settings_.name + ": failed to move the work of " + conn.id + ": " +
                          e.what());
        }
    }
    notify();
}

void WebsocketCommon::enqueue(const std::shared_ptr<Socket>& socket, OutKind kind,
                              std::string data) {
    if (socket->close_queued) {
        return;
    }
    if (kind == OutKind::Close) {
        socket->close_queued = true;
    }
    socket->outbox.push_back({kind, std::move(data)});
    if (!socket->writing) {
        socket->writing = true;
        spawn(write_loop(socket));
    }
}

asio::awaitable<void> WebsocketCommon::write_loop(std::shared_ptr<Socket> socket) const {
    while (!socket->outbox.empty() && !stopping_) {
        auto item = std::move(socket->outbox.front());
        socket->outbox.pop_front();
        boost::system::error_code ec;
        co_await socket->write(item.kind, item.data, ec);
        if (ec) {
            if (item.kind != OutKind::Close) {
                Logger::warn(settings_.name + ": write failed: " + ec.message());
            }
            // The reader then fails too, and handles the reconnect.
            socket->outbox.clear();
            socket->abort();
            break;
        }
    }
    socket->writing = false;
}

asio::awaitable<void>
WebsocketCommon::close_gracefully(Connection& conn, std::shared_ptr<Socket> socket, bool renewal) {
    const Socket* raw = socket.get();
    if (renewal) {
        const bool restored =
            co_await wait_until([this, &conn] { return stopping_ || conn.restoring == 0; },
                                Clock::now() + kDrainTimeout);
        if (stopping_) {
            co_return;
        }
        if (!restored) {
            Logger::warn(settings_.name + ": timeout waiting for " + conn.id +
                         " to restore its session and subscriptions; closing the previous socket");
        }
    }
    const bool drained = co_await wait_until(
        [this, &conn, raw] {
            return stopping_ ||
                   std::none_of(conn.pending_requests.begin(), conn.pending_requests.end(),
                                [raw](const auto& entry) { return entry.second.socket == raw; });
        },
        Clock::now() + kDrainTimeout);
    if (stopping_) {
        co_return;
    }
    if (!drained) {
        Logger::warn(settings_.name + ": timeout waiting for pending requests on " + conn.id +
                     "; forcing close");
    }
    Logger::info(settings_.name + ": closing a socket of connection " + conn.id);
    enqueue(socket, OutKind::Close, {});
}

void WebsocketCommon::disconnect_all(std::function<void(std::exception_ptr)> done) {
    // Counted now: a connect queued before the flow starts must wait for it too.
    ++disconnecting_;
    spawn(disconnect_flow(std::move(done)));
}

asio::awaitable<void>
WebsocketCommon::disconnect_flow(std::function<void(std::exception_ptr)> done) {
    bool any = false;
    for (const auto& c : connections) {
        auto& conn = *c;
        conn.close_initiated = true;
        conn.reconnect_scheduled = false;
        ++conn.retry_generation;
        ++conn.renewal_generation;
        conn.retry_timer.cancel();
        conn.renewal_timer.cancel();
        if (conn.socket) {
            any = true;
            spawn(close_gracefully(conn, conn.socket, false));
        }
        // A connect in flight closes its socket when it completes (see on_connected).
        any = any || conn.connecting;
    }
    refresh_connected();
    if (!any) {
        Logger::warn(settings_.name + ": no active connection to close");
    }
    const bool closed = co_await wait_until(
        [this] {
            return stopping_ ||
                   std::all_of(connections.begin(), connections.end(),
                               [](const auto& conn) { return !conn->socket && !conn->connecting; });
        },
        Clock::now() + kDrainTimeout + settings_.connect_timeout);
    for (const auto& conn : connections) {
        conn->is_session_logged_on = false;
        conn->session_logon.reset();
    }
    --disconnecting_;
    // Wakes the connects waiting for this disconnect.
    notify();
    if (stopping_) {
        run_handler([&] { done(std::make_exception_ptr(WebsocketCancelledError())); });
        co_return;
    }
    if (!closed) {
        Logger::error(settings_.name + ": timed out while disconnecting; aborting connections");
        for (const auto& conn : connections) {
            if (conn->socket) {
                conn->socket->abort();
            }
        }
        run_handler([&] { done(std::make_exception_ptr(WebsocketTimeoutError())); });
        co_return;
    }
    Logger::info(settings_.name + ": disconnected");
    run_handler([&] { done(nullptr); });
}

// ---- Connection selection ----

bool WebsocketCommon::is_connection_ready(const Connection& conn,
                                          bool allow_non_established) noexcept {
    return (allow_non_established || conn.socket != nullptr) && !conn.reconnection_pending &&
           !conn.close_initiated && !conn.failed;
}

bool WebsocketCommon::is_connected() const noexcept {
    return std::any_of(connections.begin(), connections.end(),
                       [](const auto& conn) { return is_connection_ready(*conn, false); });
}

std::vector<Connection*>
WebsocketCommon::available_connections(bool allow_non_established,
                                       const std::optional<std::string>& url_path) {
    std::vector<Connection*> out;
    if (!settings_.is_pool && !url_path) {
        out.push_back(connections.front().get());
        return out;
    }
    for (const auto& conn : connections) {
        if (is_connection_ready(*conn, allow_non_established) &&
            (!url_path || conn->url_path == url_path)) {
            out.push_back(conn.get());
        }
    }
    return out;
}

Connection& WebsocketCommon::get_connection(bool allow_non_established,
                                            const std::optional<std::string>& url_path) {
    auto* conn = next_connection(allow_non_established, url_path);
    if (conn == nullptr) {
        throw WebsocketNotConnectedError();
    }
    return *conn;
}

Connection* WebsocketCommon::next_connection(bool allow_non_established,
                                             const std::optional<std::string>& url_path,
                                             const Connection* exclude) {
    auto ready = available_connections(allow_non_established, url_path);
    std::erase(ready, exclude);
    if (ready.empty()) {
        return nullptr;
    }
    return ready[round_robin_++ % ready.size()];
}

void WebsocketCommon::keep_alive(Connection& conn, std::chrono::milliseconds interval) {
    const auto generation = ++conn.ping_generation;
    conn.ping_timer.expires_after(interval);
    conn.ping_timer.async_wait(
        [self = shared_from_this(), &conn, interval, generation,
         socket = std::weak_ptr<Socket>(conn.socket)](const boost::system::error_code& ec) {
            const auto current = socket.lock();
            if (ec || self->stopping_ || generation != conn.ping_generation || !current ||
                current != conn.socket || conn.close_initiated) {
                return;
            }
            self->enqueue(current, OutKind::Ping, {});
            self->keep_alive(conn, interval);
        });
}

void WebsocketCommon::ping_server() {
    std::size_t count = 0;
    for (const auto& conn : connections) {
        if (is_connection_ready(*conn, false)) {
            enqueue(conn->socket, OutKind::Ping, {});
            ++count;
        }
    }
    if (count == 0) {
        Logger::warn(settings_.name + ": no ready connections for PING");
    } else {
        Logger::debug(settings_.name + ": sent PING to " + std::to_string(count) +
                      " connection(s)");
    }
}

// ---- Requests ----

void WebsocketCommon::send_text(Connection& conn, std::string text) {
    if (!conn.socket) {
        throw WebsocketNotConnectedError();
    }
    enqueue(conn.socket, OutKind::Text, std::move(text));
}

void WebsocketCommon::send_request(Connection& conn, const std::string& id, std::string text,
                                   std::chrono::milliseconds timeout, RequestCompletion complete) {
    if (!conn.socket) {
        throw WebsocketNotConnectedError();
    }
    if (conn.pending_requests.contains(id)) {
        throw WebsocketError("A request with id " + id + " is already pending");
    }
    auto timer = std::make_shared<asio::steady_timer>(strand_, timeout);
    conn.pending_requests.emplace(id,
                                  PendingRequest{std::move(complete), timer, conn.socket.get()});
    timer->async_wait([this, self = shared_from_this(), &conn, id,
                       weak = std::weak_ptr<asio::steady_timer>(timer)](
                          const boost::system::error_code& ec) {
        if (ec) {
            return;
        }
        const auto it = conn.pending_requests.find(id);
        if (it == conn.pending_requests.end() || it->second.timer != weak.lock()) {
            return;
        }
        auto callback = std::move(it->second.complete);
        conn.pending_requests.erase(it);
        notify();
        run_handler([&] { callback(std::make_exception_ptr(WebsocketTimeoutError(true)), {}); });
    });
    enqueue(conn.socket, OutKind::Text, std::move(text));
}

bool WebsocketCommon::complete_request(Connection& conn, const std::string& id,
                                       std::exception_ptr error, boost::json::object response) {
    const auto it = conn.pending_requests.find(id);
    if (it == conn.pending_requests.end()) {
        return false;
    }
    it->second.timer->cancel();
    auto callback = std::move(it->second.complete);
    conn.pending_requests.erase(it);
    notify();
    run_handler([&] { callback(error, std::move(response)); });
    return true;
}

void WebsocketCommon::drop_request(Connection& conn, const std::string& id) {
    const auto it = conn.pending_requests.find(id);
    if (it == conn.pending_requests.end()) {
        return;
    }
    it->second.timer->cancel();
    conn.pending_requests.erase(it);
    notify();
}

void WebsocketCommon::fail_requests(Connection& conn, const Socket* socket,
                                    const std::exception_ptr& error) {
    std::vector<RequestCompletion> failed;
    for (auto it = conn.pending_requests.begin(); it != conn.pending_requests.end();) {
        if (socket == nullptr || it->second.socket == socket) {
            it->second.timer->cancel();
            failed.push_back(std::move(it->second.complete));
            it = conn.pending_requests.erase(it);
        } else {
            ++it;
        }
    }
    if (!failed.empty()) {
        notify();
    }
    for (const auto& callback : failed) {
        run_handler([&] { callback(error, {}); });
    }
}

boost::json::object redact_request(boost::json::object request) {
    if (auto* params = request.if_contains("params"); params != nullptr && params->is_object()) {
        for (const auto* key : {"apiKey", "apiSecret", "signature"}) {
            if (auto* value = params->get_object().if_contains(key); value != nullptr) {
                *value = "***";
            }
        }
    }
    return request;
}

WebsocketError blocking_call_error(const char* call, const char* async_call) {
    return WebsocketError(std::string("Blocking ") + call +
                          " called from the client's executor; use " + async_call);
}

void set_renewal_interval_for_testing(std::chrono::milliseconds interval) noexcept {
    renewal_interval_override = interval.count();
}

} // namespace binance::common::detail
