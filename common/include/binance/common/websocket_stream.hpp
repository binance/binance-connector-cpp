//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <exception>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/asio/any_completion_handler.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/json/value.hpp>
#include <boost/json/value_to.hpp>

#include <binance/common/export.hpp>
#include <binance/common/logger.hpp>
#include <binance/common/websocket_common.hpp>

namespace binance::common {

namespace detail {

/// A callback registered on a stream. Clearing `active` stops it at once, from any thread.
struct StreamSlot {
    explicit StreamSlot(Callback<boost::json::value> cb)
        : callback(std::move(cb.fn)), dispatch(std::move(cb.dispatch)) {}
    StreamCallback callback;
    /// Set when the callback runs on its own executor.
    CallbackDispatch dispatch;
    std::atomic<bool> active{true};
    /// Calls in progress on the client's executor.
    std::atomic<std::uint32_t> running{0};
};

/// Implemented by the WebSocket clients. A stream handle forwards to it; once the client is
/// destroyed, every call is a no-op.
class StreamBinding {
public:
    StreamBinding() = default;
    virtual ~StreamBinding() = default;
    StreamBinding(const StreamBinding&) = delete;
    StreamBinding& operator=(const StreamBinding&) = delete;
    StreamBinding(StreamBinding&&) = delete;
    StreamBinding& operator=(StreamBinding&&) = delete;

    virtual void add(std::shared_ptr<StreamSlot> slot) = 0;
    /// Removes the (already inactive) callbacks. WebSocket streams then send UNSUBSCRIBE if no
    /// callbacks remain for the stream; user-data subscriptions are forgotten. `wait`: called by
    /// `unsubscribe()` rather than a destructor. Never waits for the client's executor, which
    /// may not be running.
    virtual void remove(std::vector<std::shared_ptr<StreamSlot>> slots, bool wait) = 0;
    /// Completes `handler` once the subscription is acknowledged (see
    /// `WebsocketStreamHandle::async_wait_subscribed`).
    virtual void
    wait_subscribed(boost::asio::any_completion_handler<void(std::exception_ptr)> handler) = 0;
    /// False on the client's own thread, where a blocking wait would never complete.
    [[nodiscard]] virtual bool may_block() const noexcept = 0;
};

} // namespace detail

/// One subscribed stream (WebSocket streams) or user-data subscription (WebSocket API), with
/// untyped callbacks. Move-only: destroying it unsubscribes, like `unsubscribe()`; `release()`
/// keeps the subscription and its callbacks for the client's lifetime. `on_message` and
/// `unsubscribe` are thread-safe.
///
/// Payloads received before the first callback is added are kept (up to 1000) and delivered to
/// it. A default-constructed handle is empty: its calls do nothing.
class [[nodiscard]] BINANCE_COMMON_EXPORT WebsocketStreamHandle {
public:
    WebsocketStreamHandle() = default;
    WebsocketStreamHandle(std::string stream, std::shared_ptr<detail::StreamBinding> binding);
    WebsocketStreamHandle(WebsocketStreamHandle&&) noexcept = default;
    WebsocketStreamHandle& operator=(WebsocketStreamHandle&& other) noexcept;
    WebsocketStreamHandle(const WebsocketStreamHandle&) = delete;
    WebsocketStreamHandle& operator=(const WebsocketStreamHandle&) = delete;
    ~WebsocketStreamHandle();

    /// The stream name, or the subscription's id for user data.
    [[nodiscard]] const std::string& stream() const noexcept;

    /// Adds a callback. It runs on its associated executor if it has one (see
    /// `boost::asio::bind_executor`), else on the client's executor, so it should not block.
    /// Exceptions it throws are logged. No callback starts once `unsubscribe()` or the client's
    /// destructor has returned. The destructor waits for callbacks running on the client's
    /// executor, but not for those running on their own.
    template <class F> void on_message(F&& callback) {
        add(detail::bind_callback<boost::json::value>(std::forward<F>(callback)));
    }

    /// Removes this handle's callbacks and, for WebSocket streams, unsubscribes from the stream
    /// once no other handle uses it. A callback running on another thread of the client's
    /// executor is waited for (one on its own executor is not). A user-data subscription is
    /// ended on the server (see `WebsocketApi::async_subscribe`).
    void unsubscribe() noexcept;

    /// Detaches this handle: the subscription and its callbacks stay until the client is
    /// destroyed, and the handle becomes empty.
    void release() noexcept;

    /// Completes once the server has acknowledged the subscription (see
    /// `WebsocketStreams::async_wait_subscribed`), at once for a user-data subscription. Fails with
    /// `WebsocketCancelledError` if the handle is empty or unsubscribed, or the client is gone.
    /// `wait_subscribed` blocks and throws `WebsocketTimeoutError` once `timeout` passes, if given.
    template <class CompletionToken> auto async_wait_subscribed(CompletionToken&& token) {
        return boost::asio::async_initiate<CompletionToken, void(std::exception_ptr)>(
            // The state, not `this`: a deferred token may initiate after the handle has moved.
            [state = state_](auto handler) {
                start_wait_subscribed(state,
                                      boost::asio::any_completion_handler<void(std::exception_ptr)>(
                                          std::move(handler)));
            },
            token);
    }
    void wait_subscribed(std::optional<std::chrono::milliseconds> timeout = {});

private:
    void add(detail::Callback<boost::json::value> callback);

    void unsubscribe(bool wait) noexcept;

    struct State {
        std::string stream;
        std::shared_ptr<detail::StreamBinding> binding;
        std::mutex mutex;
        std::vector<std::shared_ptr<detail::StreamSlot>> slots;
        bool unsubscribed = false;
    };
    std::shared_ptr<State> state_;

    static void
    start_wait_subscribed(const std::shared_ptr<State>& state,
                          boost::asio::any_completion_handler<void(std::exception_ptr)> handler);
};

/// A stream whose payloads are decoded into `T` with `boost::json::value_to<T>`.
template <class T> class [[nodiscard]] WebsocketStream {
public:
    WebsocketStream() = default;
    explicit WebsocketStream(WebsocketStreamHandle handle) : handle_(std::move(handle)) {}

    [[nodiscard]] const std::string& stream() const noexcept { return handle_.stream(); }

    /// Adds a callback taking `T` (or `const T&`). Payloads that fail to decode are logged and
    /// skipped. See `WebsocketStreamHandle::on_message` for where it runs.
    template <class F> void on_message(F&& callback) {
        using Fn = std::decay_t<F>;
        // The decoder carries the callback's executor, so that it runs (and decodes) there.
        if constexpr (!detail::has_associated_executor_v<Fn>) {
            handle_.on_message(decoder(std::make_shared<Fn>(std::forward<F>(callback))));
        } else {
            auto ex = boost::asio::get_associated_executor(callback);
            handle_.on_message(boost::asio::bind_executor(
                ex, decoder(std::make_shared<Fn>(std::forward<F>(callback)))));
        }
    }

    void unsubscribe() noexcept { handle_.unsubscribe(); }
    void release() noexcept { handle_.release(); }

    /// See `WebsocketStreamHandle::async_wait_subscribed`.
    template <class CompletionToken> auto async_wait_subscribed(CompletionToken&& token) {
        return handle_.async_wait_subscribed(std::forward<CompletionToken>(token));
    }
    void wait_subscribed(std::optional<std::chrono::milliseconds> timeout = {}) {
        handle_.wait_subscribed(timeout);
    }

    [[nodiscard]] const WebsocketStreamHandle& handle() const noexcept { return handle_; }

private:
    template <class Fn> static auto decoder(std::shared_ptr<Fn> callback) {
        return [callback = std::move(callback)](const boost::json::value& v) {
            std::optional<T> data;
            try {
                data.emplace(boost::json::value_to<T>(v));
            } catch (const std::exception& e) {
                Logger::error(std::string("Failed to deserialize stream payload: ") + e.what());
                return;
            }
            (*callback)(*data);
        };
    }

    WebsocketStreamHandle handle_;
};

} // namespace binance::common
