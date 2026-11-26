//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <boost/json/object.hpp>
#include <boost/json/value.hpp>

#include <binance/common/config.hpp>
#include <binance/common/detail/utils.hpp>
#include <binance/common/export.hpp>
#include <binance/common/models.hpp>
#include <binance/common/signer.hpp>

/// Internals of the common library only. Not installed: exported only so that its tests can use
/// them with a shared library.
namespace binance::common::detail {

/// `application/x-www-form-urlencoded` encoding of one component (space → `+`).
[[nodiscard]] BINANCE_COMMON_EXPORT std::string form_urlencode(std::string_view text);

/// The shortest round-trip form of `d` in plain notation (`1.5`, `100000`, `0.0000001`), never
/// exponent form. Integers from 2^53 up are written exactly (`1e23` →
/// `99999999999999991611392`). Non-finite values become `null`. Locale-independent.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string format_double(double d);

/// `k1=v1&k2=v2` in key order, form-url-encoded, skipping `null` values.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string build_query_string(const Params& params);

/// Like `build_query_string` but without percent-encoding (WebSocket API signing).
/// Throws `ConnectorClientError` if a key or value contains `&`, `=` or a control character.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string build_plain_query_string(const Params& params);

/// Retry policy: GET / DELETE only, with retries left, on a network error (`status` empty)
/// or HTTP 500 / 502 / 503 / 504.
[[nodiscard]] BINANCE_COMMON_EXPORT bool should_retry_request(std::string_view method,
                                                              std::optional<std::uint16_t> status,
                                                              std::int64_t retries_left);

/// Reads `x-mbx-used-weight-<n><s|m|h|d>`, `x-mbx-order-count-<n><s|m|h|d>` and `retry-after`.
/// Header names are matched case-insensitively.
[[nodiscard]] BINANCE_COMMON_EXPORT std::vector<RestApiRateLimit>
parse_rate_limit_headers(const Headers& headers);

/// 32 lower-case hex characters from a CSPRNG.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string random_string();

/// Uniformly random 32-bit integer from a CSPRNG.
[[nodiscard]] BINANCE_COMMON_EXPORT std::uint32_t random_integer();

/// True for 32 lower-case hex characters: the request ids the SDK generates and accepts.
[[nodiscard]] BINANCE_COMMON_EXPORT bool is_valid_request_id(std::string_view id) noexcept;

/// `user_agent`, or the core library's own when empty.
[[nodiscard]] std::string user_agent_or_default(std::string user_agent);

/// A SUBSCRIBE / UNSUBSCRIBE id.
///
/// - `strictly_number`: `id` if it is a number, otherwise `random_integer()`.
/// - Otherwise: a number is kept, a string is kept if `is_valid_request_id`, anything else
///   becomes `random_string()`.
[[nodiscard]] BINANCE_COMMON_EXPORT boost::json::value
normalize_stream_id(const std::optional<StreamId>& id, bool strictly_number = false);

/// `params` without `null` values and empty strings.
[[nodiscard]] BINANCE_COMMON_EXPORT Params remove_empty_value(Params params);

/// A WebSocket API request `{"id","method","params"}` and its id.
///
/// - `payload["id"]` is used as the id if `is_valid_request_id`, else a random one; it is never
///   sent as a parameter.
/// - `null` and empty-string parameters are dropped.
/// - Doubles, nested ones included, are sent as `format_double` strings (`"0.0000001"`), the
///   text that is signed; non-finite ones become `null` (dropped at the top level).
/// - `apiKey` is added when `with_api_key` or `is_signed`, unless `skip_auth`.
/// - Signed requests get `timestamp`, and `signature` over the sorted, unencoded parameters
///   unless `skip_auth` (the session is logged on).
///
/// Throws `ConnectorClientError` if `api_key` is needed but unset, or signing fails.
[[nodiscard]] BINANCE_COMMON_EXPORT std::pair<std::string, boost::json::object>
build_websocket_api_message(const WebsocketApiConfig& configuration,
                            const SignatureGenerator& signer, std::string_view method,
                            Params payload, const WebsocketMessageSendOptions& options,
                            bool skip_auth);

} // namespace binance::common::detail
