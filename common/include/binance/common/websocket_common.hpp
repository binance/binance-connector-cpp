//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include <boost/asio/associated_executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/system_executor.hpp>
#include <boost/json/value.hpp>
#include <boost/system/error_code.hpp>

#include <binance/common/export.hpp>
#include <binance/common/logger.hpp>

namespace binance::common {

enum class WebsocketEventType { Open, Message, Error, Close, Ping, Pong };

/// A connection lifecycle event.
struct WebsocketEvent {
    WebsocketEventType type = WebsocketEventType::Open;
    /// The message text (`Message`), the error description (`Error`) or the close reason
    /// (`Close`).
    std::string data;
    /// The close code (`Close`).
    std::uint16_t close_code = 0;
    /// The connection the event comes from.
    std::string connection_id;
};

using WebsocketEventCallback = std::function<void(const WebsocketEvent&)>;

/// Why a connection ended, and whether it is worth reconnecting.
enum class WebsocketConnectionFailureReason {
    NetworkInterruption,
    ConnectionReset,
    ServerTemporaryError,
    UnexpectedClose,
    StreamEnded,
    AuthenticationFailure,
    ProtocolViolation,
    ConfigurationError,
    UserInitiatedClose,
    PermanentServerError,
    NormalClose,
};

[[nodiscard]] BINANCE_COMMON_EXPORT std::string_view
to_string(WebsocketConnectionFailureReason reason) noexcept;

/// A registration made with `on_event`. Move-only: destroying it, or assigning over it,
/// removes the callback. `release()` keeps the callback for the client's lifetime.
class [[nodiscard]] Subscription {
public:
    Subscription() = default;
    explicit Subscription(std::function<void()> unsubscribe)
        : unsubscribe_(std::move(unsubscribe)) {}
    Subscription(Subscription&& other) noexcept
        : unsubscribe_(std::exchange(other.unsubscribe_, nullptr)) {}
    Subscription& operator=(Subscription&& other) noexcept {
        if (this != &other) {
            unsubscribe();
            unsubscribe_ = std::exchange(other.unsubscribe_, nullptr);
        }
        return *this;
    }
    Subscription(const Subscription&) = delete;
    Subscription& operator=(const Subscription&) = delete;
    ~Subscription() { unsubscribe(); }

    /// Stops the callback. Safe to call more than once and after the client is gone, but not
    /// concurrently on the same object. A callback running on another thread of the client's
    /// executor is waited for (one on its own executor is not).
    void unsubscribe() noexcept {
        if (auto fn = std::exchange(unsubscribe_, nullptr)) {
            try {
                fn();
            } catch (...) { // NOLINT(bugprone-empty-catch): nothing to do if it cannot be queued
            }
        }
    }

    /// Detaches the callback from this handle: it then runs until the client is destroyed.
    void release() noexcept { unsubscribe_ = nullptr; }

private:
    std::function<void()> unsubscribe_;
};

/// Called with a stream's `data` (WebSocket streams) or a user-data `event` (WebSocket API).
using StreamCallback = std::function<void(const boost::json::value&)>;

namespace detail {

/// Classifies a close frame's code. `user_initiated` wins over the code.
[[nodiscard]] BINANCE_COMMON_EXPORT WebsocketConnectionFailureReason
failure_reason_from_close_code(std::uint16_t code, bool user_initiated) noexcept;

/// Classifies a transport error that ended a connection:
/// resets and aborts → `ConnectionReset`, EOF / TLS truncation → `StreamEnded`, access denied →
/// `AuthenticationFailure`, certificate verification and TLS negotiation failures, and oversized
/// messages → `ConfigurationError`, WebSocket protocol errors → `ProtocolViolation`, anything
/// else (other TLS errors included) → `NetworkInterruption`.
[[nodiscard]] BINANCE_COMMON_EXPORT WebsocketConnectionFailureReason
failure_reason_from_error(const boost::system::error_code& ec) noexcept;

/// False for authentication failures, configuration errors, user-initiated closes and permanent
/// server errors (close codes 1008 and 4000-4999); true for everything else, including a normal
/// close or a protocol violation by the server.
[[nodiscard]] BINANCE_COMMON_EXPORT bool
should_reconnect(WebsocketConnectionFailureReason reason) noexcept;

/// Whether `F` has an associated executor (`boost::asio::bind_executor`). The fallback is given
/// explicitly: its default differs between Boost versions.
template <class F>
// NOLINTNEXTLINE(readability-identifier-naming): named like the standard traits (`is_same_v`).
inline constexpr bool has_associated_executor_v =
    !std::is_same_v<boost::asio::associated_executor_t<F, boost::asio::system_executor>,
                    boost::asio::system_executor>;

/// Runs a task on a callback's associated executor.
using CallbackDispatch = std::function<void(std::function<void()>)>;

/// A callback and, if it has an associated executor, the dispatch to it (else empty: it runs
/// inline on the client's executor). Kept apart rather than detected from the `std::function`,
/// whose type checks do not hold across shared-library boundaries.
template <class Arg> struct Callback {
    std::function<void(const Arg&)> fn;
    CallbackDispatch dispatch;
};

/// Wraps `f`, recording its associated executor (`boost::asio::bind_executor`) if it has one.
template <class Arg, class F> Callback<Arg> bind_callback(F&& f) {
    using Fn = std::decay_t<F>;
    if constexpr (!has_associated_executor_v<Fn>) {
        return {std::function<void(const Arg&)>(std::forward<F>(f)), {}};
    } else {
        auto ex = boost::asio::get_associated_executor(f);
        auto fn = std::make_shared<Fn>(std::forward<F>(f));
        return {[fn](const Arg& arg) { (*fn)(arg); },
                [ex](std::function<void()> task) { boost::asio::dispatch(ex, std::move(task)); }};
    }
}

} // namespace detail

} // namespace binance::common
