//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <charconv>
#include <utility>

#include <boost/asio/error.hpp>

#include <binance/common/errors.hpp>
#include <binance/common/models.hpp>

namespace binance::common {

Error::Error(const std::string& what, std::string msg, std::optional<std::int64_t> code)
    : std::runtime_error(what), msg_(std::move(msg)), code_(code) {}

ConnectorError::ConnectorError(const std::string& what, std::string msg,
                               std::optional<std::int64_t> code)
    : Error(what, std::move(msg), code) {}

std::optional<std::chrono::seconds> ConnectorError::retry_after() const noexcept {
    if (response_ == nullptr || (response_->status != 418 && response_->status != 429)) {
        return std::nullopt;
    }
    const auto it = response_->headers.find("retry-after");
    if (it == response_->headers.end()) {
        return std::nullopt;
    }
    std::string_view value = it->second;
    while (!value.empty() && (value.front() == ' ' || value.front() == '\t')) {
        value.remove_prefix(1);
    }
    while (!value.empty() && (value.back() == ' ' || value.back() == '\t')) {
        value.remove_suffix(1);
    }
    std::uint32_t seconds = 0;
    const auto* end = value.data() + value.size();
    // NOLINTNEXTLINE(bugprone-suspicious-stringview-data-usage): bounded by `end`.
    const auto [ptr, ec] = std::from_chars(value.data(), end, seconds);
    if (ec != std::errc() || ptr != end) {
        return std::nullopt;
    }
    return std::chrono::seconds(seconds);
}

ConnectorClientError::ConnectorClientError(const std::string& msg, std::optional<std::int64_t> code)
    : ConnectorError("Connector client error: " + msg, msg, code) {}

BadRequestError::BadRequestError(const std::string& msg, std::optional<std::int64_t> code)
    : ConnectorError("Bad request: " + msg, msg, code) {}

UnauthorizedError::UnauthorizedError(const std::string& msg, std::optional<std::int64_t> code)
    : ConnectorError("Unauthorized access. Authentication required. " + msg, msg, code) {}

ForbiddenError::ForbiddenError(const std::string& msg, std::optional<std::int64_t> code)
    : ConnectorError("Access to the requested resource is forbidden. " + msg, msg, code) {}

NotFoundError::NotFoundError(const std::string& msg, std::optional<std::int64_t> code)
    : ConnectorError("The requested resource was not found. " + msg, msg, code) {}

ConflictError::ConflictError(const std::string& msg, std::optional<std::int64_t> code)
    : ConnectorError("The request conflicts with the current state of the resource. " + msg, msg,
                     code) {}

RateLimitBanError::RateLimitBanError(const std::string& msg, std::optional<std::int64_t> code)
    : ConnectorError("The IP address has been banned for exceeding rate limits. " + msg, msg,
                     code) {}

TooManyRequestsError::TooManyRequestsError(const std::string& msg, std::optional<std::int64_t> code)
    : ConnectorError("Too many requests. You are being rate-limited. " + msg, msg, code) {}

namespace {
std::string server_error_what(const std::string& msg, std::optional<std::uint16_t> status_code) {
    std::string what = "Internal server error: " + msg;
    if (status_code) {
        what += " (status code: " + std::to_string(*status_code) + ")";
    }
    return what;
}
} // namespace

ServerError::ServerError(const std::string& msg, std::optional<std::uint16_t> status_code,
                         std::optional<std::int64_t> code)
    : ConnectorError(server_error_what(msg, status_code), msg, code), status_code_(status_code) {}

NetworkError::NetworkError(const std::string& msg, bool request_sent,
                           boost::system::error_code transport_error)
    : ConnectorError("Network error: " + msg, msg), request_sent_(request_sent),
      transport_error_(transport_error) {}

RequestTimeoutError::RequestTimeoutError(const std::string& msg, bool request_sent,
                                         boost::system::error_code transport_error)
    : NetworkError(msg, request_sent, transport_error) {}

RequestCancelledError::RequestCancelledError(bool request_sent)
    : NetworkError("Request cancelled", request_sent, boost::asio::error::operation_aborted) {}

ConfigError::ConfigError(const std::string& msg) : Error(msg, msg) {}

WebsocketError::WebsocketError(const std::string& what, bool request_sent)
    : Error(what, what), request_sent_(request_sent) {}

WebsocketError::WebsocketError(const std::string& what, std::string msg,
                               std::optional<std::int64_t> code, bool request_sent)
    : Error(what, std::move(msg), code), request_sent_(request_sent) {}

WebsocketTimeoutError::WebsocketTimeoutError(bool request_sent)
    : WebsocketError("WebSocket timeout error", request_sent) {}

WebsocketProtocolError::WebsocketProtocolError(const std::string& msg)
    : WebsocketError("WebSocket protocol error: " + msg, msg, std::nullopt, false) {}

WebsocketHandshakeError::WebsocketHandshakeError(const std::string& msg, std::uint16_t status,
                                                 std::optional<std::chrono::seconds> retry_after)
    : WebsocketError("WebSocket handshake error: " + msg, msg, std::nullopt, false),
      status_(status), retry_after_(retry_after) {}

WebsocketNetworkError::WebsocketNetworkError(const std::string& msg, bool request_sent,
                                             boost::system::error_code transport_error)
    : WebsocketError("Network error: " + msg, msg, std::nullopt, request_sent),
      transport_error_(transport_error) {}

WebsocketNotConnectedError::WebsocketNotConnectedError()
    : WebsocketError("No active WebSocket connection error.") {}

WebsocketServerError::WebsocketServerError(const std::string& msg)
    : WebsocketError("Server error: " + msg, msg, std::nullopt, false) {}

WebsocketNoResponseError::WebsocketNoResponseError() : WebsocketError("No response error.", true) {}

WebsocketCancelledError::WebsocketCancelledError(bool request_sent)
    : WebsocketError("WebSocket request cancelled", request_sent) {}

WebsocketResponseError::WebsocketResponseError(std::int64_t code, const std::string& msg,
                                               std::uint16_t status)
    : WebsocketResponseError(code, msg, status, {}) {}

WebsocketResponseError::WebsocketResponseError(
    std::int64_t code, const std::string& msg, std::uint16_t status,
    std::vector<WebsocketApiRateLimit> rate_limits,
    std::optional<std::chrono::system_clock::time_point> retry_at,
    std::shared_ptr<const boost::json::value> data)
    : WebsocketError("Server-side response error (code " + std::to_string(code) + "): " + msg, msg,
                     code, true),
      status_(status), rate_limits_(std::make_shared<const std::vector<WebsocketApiRateLimit>>(
                           std::move(rate_limits))),
      retry_at_(retry_at), data_(std::move(data)) {}

} // namespace binance::common
