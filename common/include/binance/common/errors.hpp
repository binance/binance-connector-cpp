//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/system/error_code.hpp>

#include <binance/common/export.hpp>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4275) // exported class derived from non-exported std::runtime_error
#endif

namespace boost::json {
class value; // NOLINT(readability-identifier-naming): forward declaration of Boost.JSON's type
} // namespace boost::json

namespace binance::common {

struct RawResponse;
struct WebsocketApiRateLimit;

namespace detail {
struct ErrorAccess;
} // namespace detail

/// Base class of every error raised by the SDK, so that `catch (const common::Error&)` handles
/// them all.
///
/// `what()` returns the formatted, human readable message; `msg()` and `code()` give the raw server
/// (or client) message and the Binance error code, when one was returned.
class BINANCE_COMMON_EXPORT Error : public std::runtime_error {
public:
    Error(const std::string& what, std::string msg,
          std::optional<std::int64_t> code = std::nullopt);

    [[nodiscard]] const std::string& msg() const noexcept { return msg_; }
    [[nodiscard]] std::optional<std::int64_t> code() const noexcept { return code_; }

private:
    std::string msg_;
    std::optional<std::int64_t> code_;
};

/// Base class of every error raised while sending a REST request.
class BINANCE_COMMON_EXPORT ConnectorError : public Error {
public:
    ConnectorError(const std::string& what, std::string msg,
                   std::optional<std::int64_t> code = std::nullopt);

    /// The HTTP response that caused the error, when there was one: status, headers (e.g.
    /// `retry-after` on 418 / 429), parsed rate limits and the raw body. `nullptr` otherwise.
    [[nodiscard]] const RawResponse* response() const noexcept { return response_.get(); }

    /// The delay from the `Retry-After` header of a 418 / 429 response, if it has one. Only the
    /// delay-seconds form is read: an HTTP-date, a negative or a non-numeric value gives
    /// `nullopt`, as does any other error.
    [[nodiscard]] std::optional<std::chrono::seconds> retry_after() const noexcept;

private:
    friend struct detail::ErrorAccess;
    std::shared_ptr<const RawResponse> response_;
};

/// Generic client-side failure: unexpected status, invalid request, malformed response, …
class BINANCE_COMMON_EXPORT ConnectorClientError : public ConnectorError {
public:
    explicit ConnectorClientError(const std::string& msg,
                                  std::optional<std::int64_t> code = std::nullopt);
};

/// HTTP 400.
class BINANCE_COMMON_EXPORT BadRequestError : public ConnectorError {
public:
    explicit BadRequestError(const std::string& msg,
                             std::optional<std::int64_t> code = std::nullopt);
};

/// HTTP 401.
class BINANCE_COMMON_EXPORT UnauthorizedError : public ConnectorError {
public:
    explicit UnauthorizedError(const std::string& msg,
                               std::optional<std::int64_t> code = std::nullopt);
};

/// HTTP 403.
class BINANCE_COMMON_EXPORT ForbiddenError : public ConnectorError {
public:
    explicit ForbiddenError(const std::string& msg,
                            std::optional<std::int64_t> code = std::nullopt);
};

/// HTTP 404.
class BINANCE_COMMON_EXPORT NotFoundError : public ConnectorError {
public:
    explicit NotFoundError(const std::string& msg, std::optional<std::int64_t> code = std::nullopt);
};

/// HTTP 409: the request conflicts with the current state of the resource.
class BINANCE_COMMON_EXPORT ConflictError : public ConnectorError {
public:
    explicit ConflictError(const std::string& msg, std::optional<std::int64_t> code = std::nullopt);
};

/// HTTP 418: the IP has been auto-banned for continuing to send requests after a 429.
class BINANCE_COMMON_EXPORT RateLimitBanError : public ConnectorError {
public:
    explicit RateLimitBanError(const std::string& msg,
                               std::optional<std::int64_t> code = std::nullopt);
};

/// HTTP 429.
class BINANCE_COMMON_EXPORT TooManyRequestsError : public ConnectorError {
public:
    explicit TooManyRequestsError(const std::string& msg,
                                  std::optional<std::int64_t> code = std::nullopt);
};

/// HTTP 5xx. `msg()` and `code()` carry Binance's error when the body has one. For example,
/// 503 with code -1007 means the request reached the matching engine but its outcome is unknown,
/// so query the order before resending. Otherwise `msg()` is `"Server error: <status>"`.
class BINANCE_COMMON_EXPORT ServerError : public ConnectorError {
public:
    explicit ServerError(const std::string& msg,
                         std::optional<std::uint16_t> status_code = std::nullopt,
                         std::optional<std::int64_t> code = std::nullopt);

    [[nodiscard]] std::optional<std::uint16_t> status_code() const noexcept { return status_code_; }

private:
    std::optional<std::uint16_t> status_code_;
};

/// The request never produced an HTTP response (DNS, connect, TLS, timeout, reset, …).
class BINANCE_COMMON_EXPORT NetworkError : public ConnectorError {
public:
    explicit NetworkError(const std::string& msg, bool request_sent = false,
                          boost::system::error_code transport_error = {});

    /// True when the full request was written on at least one attempt, so Binance may have
    /// executed it. The outcome is then unknown. For orders, look the order up (e.g. by
    /// `newClientOrderId`) before sending it again.
    [[nodiscard]] bool request_sent() const noexcept { return request_sent_; }

    /// The transport-level cause (e.g. `boost::asio::error::connection_refused`,
    /// `boost::asio::error::host_not_found`, `boost::beast::error::timeout`, an SSL error), or an
    /// empty error code when there is none, e.g. for a rejected proxy CONNECT.
    [[nodiscard]] boost::system::error_code transport_error() const noexcept {
        return transport_error_;
    }

private:
    bool request_sent_;
    boost::system::error_code transport_error_;
};

/// The attempt took longer than `timeout`. `request_sent()` has the same meaning as for
/// `NetworkError`.
class BINANCE_COMMON_EXPORT RequestTimeoutError : public NetworkError {
public:
    explicit RequestTimeoutError(const std::string& msg, bool request_sent = false,
                                 boost::system::error_code transport_error = {});
};

/// The operation was cancelled through its cancellation slot (e.g. `asio::cancel_after`) or
/// because the `RestClient` was destroyed. `request_sent()` has the same meaning as for
/// `NetworkError`; `transport_error()` is `boost::asio::error::operation_aborted`.
class BINANCE_COMMON_EXPORT RequestCancelledError : public NetworkError {
public:
    explicit RequestCancelledError(bool request_sent = false);
};

/// A configuration value is missing or invalid.
class BINANCE_COMMON_EXPORT ConfigError : public Error {
public:
    explicit ConfigError(const std::string& msg);
};

/// Base class of every error raised by the WebSocket clients.
///
/// As for `ConnectorError`, `what()` is the formatted message and `msg()` the underlying one
/// without the error-kind prefix; errors with no underlying message use `what()` for both.
class BINANCE_COMMON_EXPORT WebsocketError : public Error {
public:
    explicit WebsocketError(const std::string& what, bool request_sent = false);
    WebsocketError(const std::string& what, std::string msg, std::optional<std::int64_t> code,
                   bool request_sent);

    /// True when the request was handed to the connection, so Binance may have executed it and
    /// the outcome is unknown. For orders, look the order up (e.g. by `newClientOrderId`) before
    /// sending it again.
    [[nodiscard]] bool request_sent() const noexcept { return request_sent_; }

private:
    bool request_sent_;
};

/// No response arrived within `timeout`, or a connection was not established in time.
class BINANCE_COMMON_EXPORT WebsocketTimeoutError : public WebsocketError {
public:
    explicit WebsocketTimeoutError(bool request_sent = false);
};

/// The server broke the WebSocket protocol or sent a malformed message.
class BINANCE_COMMON_EXPORT WebsocketProtocolError : public WebsocketError {
public:
    explicit WebsocketProtocolError(const std::string& msg);
};

/// The WebSocket upgrade was rejected (e.g. HTTP 403 / 429) or failed.
class BINANCE_COMMON_EXPORT WebsocketHandshakeError : public WebsocketError {
public:
    explicit WebsocketHandshakeError(const std::string& msg, std::uint16_t status = 0,
                                     std::optional<std::chrono::seconds> retry_after = {});

    /// The HTTP status of a rejected upgrade, or 0.
    [[nodiscard]] std::uint16_t status() const noexcept { return status_; }
    /// The `Retry-After` header of a rejected upgrade (418 / 429), if any. Reconnects wait at
    /// least this long.
    [[nodiscard]] std::optional<std::chrono::seconds> retry_after() const noexcept {
        return retry_after_;
    }

private:
    std::uint16_t status_;
    std::optional<std::chrono::seconds> retry_after_;
};

/// DNS, TCP, proxy or TLS failure.
class BINANCE_COMMON_EXPORT WebsocketNetworkError : public WebsocketError {
public:
    explicit WebsocketNetworkError(const std::string& msg, bool request_sent = false,
                                   boost::system::error_code transport_error = {});

    /// The transport-level cause (e.g. `boost::asio::error::connection_refused`), or an empty
    /// error code when there is none.
    [[nodiscard]] boost::system::error_code transport_error() const noexcept {
        return transport_error_;
    }

private:
    boost::system::error_code transport_error_;
};

/// There is no open connection to send on.
class BINANCE_COMMON_EXPORT WebsocketNotConnectedError : public WebsocketError {
public:
    WebsocketNotConnectedError();
};

/// A server-side failure that is not an error response.
class BINANCE_COMMON_EXPORT WebsocketServerError : public WebsocketError {
public:
    explicit WebsocketServerError(const std::string& msg);
};

/// The connection closed after the request was sent and before its response arrived.
class BINANCE_COMMON_EXPORT WebsocketNoResponseError : public WebsocketError {
public:
    WebsocketNoResponseError();
};

/// The operation was cancelled through its cancellation slot or because the client was
/// destroyed.
class BINANCE_COMMON_EXPORT WebsocketCancelledError : public WebsocketError {
public:
    explicit WebsocketCancelledError(bool request_sent = false);
};

/// The server answered with an error (`status` >= 400), e.g. `{"code":-1021,"msg":"..."}`.
class BINANCE_COMMON_EXPORT WebsocketResponseError : public WebsocketError {
public:
    WebsocketResponseError(std::int64_t code, const std::string& msg, std::uint16_t status = 0);
    WebsocketResponseError(std::int64_t code, const std::string& msg, std::uint16_t status,
                           std::vector<WebsocketApiRateLimit> rate_limits,
                           std::optional<std::chrono::system_clock::time_point> retry_at = {},
                           std::shared_ptr<const boost::json::value> data = nullptr);

    // `code()` is Binance's error code, or the response `status` when the body has none.

    /// The response's `status` (e.g. 400, 403, 429, 418), or 0.
    [[nodiscard]] std::uint16_t status() const noexcept { return status_; }
    /// The response's `rateLimits`, if any.
    [[nodiscard]] const std::vector<WebsocketApiRateLimit>& rate_limits() const noexcept {
        return *rate_limits_;
    }
    /// When to retry, from `error.data.retryAfter` (418 / 429). Binance sends this as an epoch
    /// timestamp in milliseconds, so it is a point in time, not a delay.
    [[nodiscard]] std::optional<std::chrono::system_clock::time_point> retry_at() const noexcept {
        return retry_at_;
    }
    /// The response's `error.data`, as Binance sent it, or `nullptr` when it has none.
    [[nodiscard]] const boost::json::value* data() const noexcept { return data_.get(); }

private:
    std::uint16_t status_;
    std::shared_ptr<const std::vector<WebsocketApiRateLimit>> rate_limits_;
    std::optional<std::chrono::system_clock::time_point> retry_at_;
    std::shared_ptr<const boost::json::value> data_;
};

} // namespace binance::common

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
