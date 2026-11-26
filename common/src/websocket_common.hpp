//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

// The connection engine shared by `WebsocketApi` and `WebsocketStreams`: the pool, the
// executor, connecting through proxies and TLS, the write queue, request / response matching,
// reconnects and renewals.
//
// Everything below runs on the strand unless stated otherwise, so it needs no locks.

#include <atomic>
#include <chrono>
#include <cstdint>
#include <deque>
#include <exception>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <boost/asio/any_completion_handler.hpp>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/execution/outstanding_work.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/prefer.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/system_executor.hpp>
#include <boost/json/object.hpp>

#include <binance/common/config.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/logger.hpp>
#include <binance/common/models.hpp>
#include <binance/common/websocket_common.hpp>
#include <binance/common/websocket_stream.hpp>

namespace binance::common::detail {

/// Transport settings common to both configurations.
struct WebsocketSettings {
    /// `WebsocketApi` or `WebsocketStreams`, for logs.
    std::string name;
    std::chrono::milliseconds reconnect_delay{5000};
    std::chrono::milliseconds connect_timeout{10000};
    bool compression = true;
    std::size_t max_message_size = 64ULL * 1024 * 1024;
    /// `WebsocketMode::is_pool()`.
    bool is_pool = false;
    std::optional<ProxyConfig> proxy;
    bool proxy_from_env = true;
    TlsContextHook agent;
    WebsocketTransportHook transport;
    std::string user_agent;
    /// Headers of the upgrade request.
    std::vector<std::pair<std::string, std::string>> headers;
    /// Empty: the client runs its own I/O thread.
    boost::asio::any_io_executor executor;
};

/// An open (or opening) WebSocket. Defined in websocket_common.cpp.
class Socket;

enum class OutKind { Text, Ping, Close };

using RequestCompletion = std::function<void(std::exception_ptr, boost::json::object)>;

struct PendingRequest {
    RequestCompletion complete;
    std::shared_ptr<boost::asio::steady_timer> timer;
    /// The socket the request went out on: if it closes, the request has no response.
    const Socket* socket = nullptr;
};

/// The request replayed after a reconnect when `auto_session_relogon` is set.
struct SessionLogon {
    std::string method;
    Params payload;
    WebsocketMessageSendOptions options;
};

/// One slot of the pool. It outlives its sockets: reconnects and renewals replace `socket`.
struct Connection {
    explicit Connection(const boost::asio::any_io_executor& ex);

    std::string id;
    /// The URL path this connection serves (`WebsocketStreams` with URL paths).
    std::optional<std::string> url_path;

    /// The open socket, or null.
    std::shared_ptr<Socket> socket;
    /// The socket being opened, so that shutdown can abort it.
    std::shared_ptr<Socket> opening;
    /// Sockets replaced by a renewal, closing once their requests are answered.
    std::vector<std::shared_ptr<Socket>> retired;
    bool connecting = false;

    bool reconnection_pending = false;
    bool renewal_pending = false;
    bool close_initiated = false;
    bool reconnect_scheduled = false;
    /// Closed for good (see `should_reconnect`) and not used again until `connect()`.
    bool failed = false;
    /// Failed attempts since the connection last stayed open, for the reconnect backoff.
    std::uint32_t failures = 0;
    /// When the current socket opened (renewals keep the original time).
    std::chrono::steady_clock::time_point opened_at{};
    /// Failed renewals since the last successful one, for the renewal retry backoff.
    std::uint32_t renewal_failures = 0;
    /// The `Retry-After` of the last rejected upgrade.
    std::optional<std::chrono::seconds> retry_after;
    /// Bumped whenever the timer is re-armed or cancelled, so that a stale expiry is ignored.
    std::uint64_t retry_generation = 0;
    std::uint64_t renewal_generation = 0;

    /// Whether the current socket is logged on.
    bool is_session_logged_on = false;
    std::optional<SessionLogon> session_logon;
    /// Requests restoring the session and subscriptions on the current socket. A renewal keeps
    /// the previous socket open until none is left.
    std::size_t restoring = 0;
    /// Whether the subscriptions were sent again on the current socket.
    bool resubscribed = false;

    std::map<std::string, PendingRequest> pending_requests;
    /// Streams to SUBSCRIBE once the connection opens.
    std::vector<std::string> pending_subscriptions;
    /// Streams in the URL of the socket being opened, to UNSUBSCRIBE once it opens.
    std::vector<std::string> pending_unsubscriptions;

    /// `connect()` calls waiting for the attempt in flight.
    std::vector<std::function<void(std::exception_ptr)>> connect_waiters;

    boost::asio::steady_timer renewal_timer;
    boost::asio::steady_timer retry_timer;
    boost::asio::steady_timer ping_timer;
    std::uint64_t ping_generation = 0;
    boost::asio::cancellation_signal connect_signal;
};

/// Guards user callbacks: once closed, none starts, and `close` waits for those running on
/// other threads. Owned by a `shared_ptr`, so that callbacks queued on their own executors can
/// check it after the client is gone.
class DeliveryGate : public std::enable_shared_from_this<DeliveryGate> {
public:
    class Pass {
    public:
        explicit Pass(DeliveryGate& gate) noexcept : gate_(gate), open_(gate.enter()) {}
        ~Pass() {
            if (open_) {
                gate_.leave();
            }
        }
        Pass(const Pass&) = delete;
        Pass& operator=(const Pass&) = delete;
        Pass(Pass&&) = delete;
        Pass& operator=(Pass&&) = delete;

        explicit operator bool() const noexcept { return open_; }

    private:
        DeliveryGate& gate_;
        bool open_;
    };

    /// Stops callbacks. With `wait`, returns once none is running.
    void close(bool wait) noexcept;
    [[nodiscard]] bool is_open() const noexcept { return open_; }

private:
    bool enter() noexcept;
    void leave() noexcept;

    std::atomic<bool> open_{true};
    std::atomic<std::uint32_t> active_{0};
};

/// The callbacks of one stream or user-data subscription.
class StreamListeners {
public:
    /// Payloads kept for a first callback that is not added yet.
    static constexpr std::size_t kMaxBacklog = 1000;

    /// Keeps the payloads that arrive before the first callback is added, and hands them to it.
    void buffer_until_first_callback() noexcept { buffering_ = slots_.empty(); }
    void add(std::shared_ptr<StreamSlot> slot, DeliveryGate& gate);
    void remove(const std::vector<std::shared_ptr<StreamSlot>>& slots);
    void deliver(const boost::json::value& payload, DeliveryGate& gate);
    [[nodiscard]] bool empty() const noexcept { return slots_.empty(); }

private:
    std::vector<std::shared_ptr<StreamSlot>> slots_;
    std::deque<boost::json::value> backlog_;
    bool buffering_ = false;
};

class WebsocketCommon : public std::enable_shared_from_this<WebsocketCommon> {
public:
    /// Connections are renewed this often (Binance closes them after 24 hours).
    static constexpr std::chrono::hours kRenewalInterval{23};
    /// Longest wait for responses before a graceful close.
    static constexpr std::chrono::seconds kDrainTimeout{30};
    /// Minimum spacing of reconnects and renewals.
    static constexpr std::chrono::seconds kReconnectThrottle{1};
    /// A connection closed sooner than this after opening counts as a failed attempt, so that a
    /// server closing every new connection gets the growing reconnect delay.
    static constexpr std::chrono::seconds kStableConnection{30};
    /// Backoff of a failed reconnect or renewal attempt: 1 s, doubling up to 60 s, with jitter.
    static constexpr std::chrono::seconds kRetryBaseDelay{1};
    static constexpr std::chrono::seconds kRetryMaxDelay{60};

    /// Validates the proxy settings against `url` (throws `ConfigError`) and sets up TLS.
    WebsocketCommon(WebsocketSettings settings, const std::string& url, std::size_t count);
    virtual ~WebsocketCommon();
    WebsocketCommon(const WebsocketCommon&) = delete;
    WebsocketCommon& operator=(const WebsocketCommon&) = delete;
    WebsocketCommon(WebsocketCommon&&) = delete;
    WebsocketCommon& operator=(WebsocketCommon&&) = delete;

    // ---- Any thread ----

    /// Starts the owned I/O thread, if any. Called once, by the client's constructor.
    void start();
    /// Shuts down; pending operations fail with `WebsocketCancelledError`. Joins the owned
    /// thread (detaches when called from it). Called by the client's destructor.
    void stop() noexcept;

    [[nodiscard]] boost::asio::any_io_executor executor() const noexcept { return strand_; }
    [[nodiscard]] bool on_io_thread() const noexcept { return strand_.running_in_this_thread(); }
    /// False on the strand, and on a thread running the client's executor (blocking there could
    /// deadlock). Executors of unknown types are assumed not to run on this thread.
    [[nodiscard]] bool may_block() const noexcept;
    /// `is_connected()`, readable from any thread.
    [[nodiscard]] bool connected() const noexcept { return connected_; }
    [[nodiscard]] DeliveryGate& gate() noexcept { return *gate_; }

    /// Posts `f` to the strand unless the client is shutting down.
    template <class F> void post(F&& f) {
        const std::lock_guard lock(post_mutex_);
        if (accepting_) {
            boost::asio::post(
                strand_, [self = shared_from_this(), f = std::forward<F>(f)]() mutable { f(); });
        }
    }

    /// Runs `f` on the strand: inline when already there, else posted, never waiting for the
    /// executor (which may not be running yet). Dropped once the client is shutting down.
    template <class F> void execute_or_post(F&& f) {
        if (on_io_thread()) {
            f();
        } else {
            post(std::forward<F>(f));
        }
    }

    /// Registers an event callback; the subscription removes it from any thread.
    Subscription add_event_callback(Callback<WebsocketEvent> callback, bool with_messages);

    // ---- Strand ----

    /// Opens every connection of `targets` that is not open, with the URL from `url_for`, and
    /// calls `done` once all are open, or with the first failure.
    void connect_connections(const std::vector<Connection*>& targets,
                             const std::function<std::string(Connection&)>& url_for,
                             std::function<void(std::exception_ptr)> done);

    /// Stops reconnecting, closes every connection gracefully and calls `done`.
    void disconnect_all(std::function<void(std::exception_ptr)> done);

    /// Not reconnecting, closing or failed; and open, unless `allow_non_established`.
    [[nodiscard]] static bool is_connection_ready(const Connection& conn,
                                                  bool allow_non_established) noexcept;
    [[nodiscard]] bool is_connected() const noexcept;

    /// The connections ready for use (see `is_connection_ready`). In single mode without a URL
    /// path: the only connection, whatever its state.
    [[nodiscard]] std::vector<Connection*>
    available_connections(bool allow_non_established, const std::optional<std::string>& url_path);

    /// Round-robin over `available_connections`. Throws `WebsocketNotConnectedError`.
    [[nodiscard]] Connection& get_connection(bool allow_non_established,
                                             const std::optional<std::string>& url_path);
    /// Round-robin over `available_connections` other than `exclude`, or null.
    [[nodiscard]] Connection* next_connection(bool allow_non_established,
                                              const std::optional<std::string>& url_path,
                                              const Connection* exclude = nullptr);

    void ping_server();

    /// Sends a text message without waiting for a reply. Throws `WebsocketNotConnectedError`.
    void send_text(Connection& conn, std::string text);

    /// Sends a request and calls `complete` with its response (an object with this `id`), or
    /// with `WebsocketTimeoutError` / `WebsocketNoResponseError`. Throws
    /// `WebsocketNotConnectedError`.
    void send_request(Connection& conn, const std::string& id, std::string text,
                      std::chrono::milliseconds timeout, RequestCompletion complete);

    /// Completes a pending request. Returns false if there is none with this `id`.
    bool complete_request(Connection& conn, const std::string& id, std::exception_ptr error,
                          boost::json::object response);

    /// Forgets a pending request without completing it, once its caller has been cancelled.
    void drop_request(Connection& conn, const std::string& id);

    /// Replaces the connection's socket (on `serverShutdown` and every 23 hours), keeping the
    /// old one until its requests are answered. No-op unless the connection is open and idle.
    /// The new socket uses `reconnect_url(conn)`.
    void renew(Connection& conn);

    void emit(WebsocketEvent event);

    /// Wakes `wait_until` callers so they re-check their condition.
    void notify();

    [[nodiscard]] bool stopping() const noexcept { return stopping_; }
    [[nodiscard]] const WebsocketSettings& settings() const noexcept { return settings_; }

protected:
    /// A socket opened, including by a reconnect or renewal. Called before the `Open` event.
    virtual void on_open(Connection& conn) = 0;
    /// A text message (binary messages are inflated first) received on `socket`. `retired`: it
    /// came on a socket that a renewal replaced. Returns whether to emit it as a `Message` event.
    virtual bool on_message(Connection& conn, const Socket& socket, std::string_view text,
                            bool retired) = 0;
    /// Sends a PING frame on the current socket of `conn` every `interval`, until the socket is
    /// replaced or closed.
    void keep_alive(Connection& conn, std::chrono::milliseconds interval);
    /// The URL to reconnect or renew `conn` with.
    virtual std::string reconnect_url(Connection& conn) = 0;
    /// `conn` closed and will not reconnect by itself.
    virtual void on_connection_failed(Connection& /*conn*/) {}
    /// The client is being destroyed, on the strand: the operations a subclass keeps waiting must
    /// complete now (with `WebsocketCancelledError`).
    virtual void on_shutdown() {}

private:
    void run() noexcept;
    void shutdown();
    /// Waits until `done()` holds or `deadline` passes; returns `done()`.
    boost::asio::awaitable<bool> wait_until(std::function<bool()> done,
                                            std::chrono::steady_clock::time_point deadline);

    void start_connect(Connection& conn, std::string url, bool is_renewal);
    boost::asio::awaitable<std::shared_ptr<Socket>> open_socket(Connection& conn, std::string url);
    void on_connected(Connection& conn, bool is_renewal, std::exception_ptr error,
                      std::shared_ptr<Socket> socket);
    void finish_connect_waiters(Connection& conn, std::exception_ptr error);

    void refresh_connected() noexcept;
    void schedule_reconnect(Connection& conn);
    /// Wait before reconnecting after `failures` failed attempts: `reconnect_delay`, plus
    /// `retry_delay(failures - 1)` after a failure, and at least a handshake's `Retry-After`.
    [[nodiscard]] std::chrono::milliseconds backoff(const Connection& conn,
                                                    std::uint32_t failures) const;
    /// Exponential backoff with equal jitter of failed attempt number `attempt` (from 0).
    [[nodiscard]] static std::chrono::milliseconds retry_delay(std::uint32_t attempt);
    void on_retry_timer(Connection& conn, std::uint64_t generation,
                        const boost::system::error_code& ec);
    void arm_renewal(Connection& conn, std::chrono::steady_clock::duration delay);
    boost::asio::awaitable<void> disconnect_flow(std::function<void(std::exception_ptr)> done);
    /// `connect_connections` once the disconnect in progress has closed `targets`.
    boost::asio::awaitable<void>
    connect_after_close(std::vector<Connection*> targets,
                        std::function<std::string(Connection&)> url_for,
                        std::function<void(std::exception_ptr)> done);
    [[nodiscard]] static bool closing(const std::vector<Connection*>& targets) noexcept;

    boost::asio::awaitable<void> read_loop(Connection& conn, std::shared_ptr<Socket> socket);
    void on_socket_closed(Connection& conn, const std::shared_ptr<Socket>& socket,
                          const boost::system::error_code& ec);

    void enqueue(const std::shared_ptr<Socket>& socket, OutKind kind, std::string data);
    boost::asio::awaitable<void> write_loop(std::shared_ptr<Socket> socket) const;

    /// Closes `socket` once its requests are answered and, for a socket replaced by a renewal,
    /// once nothing is `restoring` on the new one (each within `kDrainTimeout`).
    boost::asio::awaitable<void> close_gracefully(Connection& conn, std::shared_ptr<Socket> socket,
                                                  bool renewal);
    void fail_requests(Connection& conn, const Socket* socket, const std::exception_ptr& error);

    template <class Awaitable> void spawn(Awaitable&& a);

    boost::asio::any_io_executor base_executor();

    // Declaration order matters for destruction: connections (and the sockets they own), then
    // the strand, then the owned I/O context (with any coroutine frames), then the TLS context.
    WebsocketSettings settings_;
    boost::asio::ssl::context tls_;
    std::optional<boost::asio::io_context> owned_ioc_;
    std::optional<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> work_;
    /// Initialised by `base_executor()`, after the two above.
    boost::asio::strand<boost::asio::any_io_executor> strand_;

public:
    std::vector<std::unique_ptr<Connection>> connections;

private:
    struct EventSlot {
        EventSlot(Callback<WebsocketEvent> cb, bool with_messages)
            : callback(std::move(cb.fn)), dispatch(std::move(cb.dispatch)),
              messages(with_messages) {}
        WebsocketEventCallback callback;
        CallbackDispatch dispatch;
        const bool messages;
        std::atomic<bool> active{true};
        /// Calls in progress on the client's executor.
        std::atomic<std::uint32_t> running{0};
    };
    std::map<std::uint64_t, std::shared_ptr<EventSlot>> event_callbacks_;
    std::atomic<std::uint64_t> next_callback_id_{0};
    std::vector<std::shared_ptr<boost::asio::steady_timer>> waiters_;
    std::chrono::steady_clock::time_point next_connect_at_{};
    std::size_t round_robin_ = 0;
    /// `disconnect_all` calls in progress.
    std::size_t disconnecting_ = 0;
    bool stopping_ = false;
    std::atomic<bool> connected_{false};
    std::shared_ptr<DeliveryGate> gate_ = std::make_shared<DeliveryGate>();

    std::mutex post_mutex_;
    bool accepting_ = true;
    std::thread thread_;
};

/// Runs a user completion handler, logging what it throws: it must not unwind into the client.
template <class F> void run_handler(F&& f) {
    try {
        std::forward<F>(f)();
    } catch (const std::exception& e) {
        Logger::error(std::string("WebSocket completion handler threw: ") + e.what());
    } catch (...) {
        Logger::error("WebSocket completion handler threw");
    }
}

/// Completes `handler` with `ep` on its associated executor, never inside the caller. The handler's
/// executor is an `any_completion_executor`, which `post` does not accept (it has no
/// `blocking.never`): the completion is posted to the system executor, then dispatched to it.
inline void complete_later(boost::asio::any_completion_handler<void(std::exception_ptr)> handler,
                           std::exception_ptr ep) {
    auto ex = boost::asio::prefer(boost::asio::get_associated_executor(handler),
                                  boost::asio::execution::outstanding_work.tracked);
    boost::asio::post(boost::asio::system_executor(),
                      [ex = std::move(ex), handler = std::move(handler), ep]() mutable {
                          boost::asio::dispatch(ex, [handler = std::move(handler), ep]() mutable {
                              run_handler([&] { std::move(handler)(ep); });
                          });
                      });
}

/// A `StreamBinding` forwarding to functions that hold the client weakly. Without `wait`
/// (user-data subscriptions), `wait_subscribed` completes at once.
class FunctionStreamBinding final : public StreamBinding {
public:
    using Add = std::function<void(std::shared_ptr<StreamSlot>)>;
    using Remove = std::function<void(std::vector<std::shared_ptr<StreamSlot>>, bool wait)>;
    using Wait = std::function<void(boost::asio::any_completion_handler<void(std::exception_ptr)>)>;
    using MayBlock = std::function<bool()>;

    FunctionStreamBinding(Add add, Remove remove, Wait wait = {}, MayBlock may_block = {})
        : add_(std::move(add)), remove_(std::move(remove)), wait_(std::move(wait)),
          may_block_(std::move(may_block)) {}

    void add(std::shared_ptr<StreamSlot> slot) override { add_(std::move(slot)); }
    void remove(std::vector<std::shared_ptr<StreamSlot>> slots, bool wait) override {
        remove_(std::move(slots), wait);
    }
    void wait_subscribed(
        boost::asio::any_completion_handler<void(std::exception_ptr)> handler) override {
        if (wait_) {
            wait_(std::move(handler));
            return;
        }
        complete_later(std::move(handler), nullptr);
    }
    [[nodiscard]] bool may_block() const noexcept override {
        try {
            return !may_block_ || may_block_();
        } catch (...) {
            return true;
        }
    }

private:
    Add add_;
    Remove remove_;
    Wait wait_;
    MayBlock may_block_;
};

/// Waits until no callback of `slots` (already inactive) runs, except one this thread is in.
void wait_until_idle(const std::vector<std::shared_ptr<StreamSlot>>& slots) noexcept;

/// `params` with `apiKey`, `apiSecret` and `signature` replaced by `***`, for debug logs.
[[nodiscard]] boost::json::object redact_request(boost::json::object request);

/// Error for a blocking call made from the client's executor.
[[nodiscard]] WebsocketError blocking_call_error(const char* call, const char* async_call);

} // namespace binance::common::detail
