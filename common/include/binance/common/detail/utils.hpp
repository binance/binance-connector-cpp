//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <string_view>

#include <boost/json/value.hpp>

#include <binance/common/config.hpp>
#include <binance/common/export.hpp>
#include <binance/common/models.hpp>

/// SDK internals shared by the common library and the product clients. Not part of the public
/// API: they may change in any release.
namespace binance::common::detail {

/// Compact JSON. Doubles use the shortest round-trip form in plain notation (`1.5`, `100000`,
/// `0.0000001`), never exponent form, which Binance rejects. Non-finite doubles become `null`.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string to_json_string(const boost::json::value& value);

/// The textual value used for a parameter: strings as-is, scalars as JSON, arrays and objects as
/// compact JSON.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string param_to_string(const boost::json::value& value);

/// `binance-connector-cpp/<product>/<version> (C++/<compiler>; <os>; <arch>)`.
///
/// `BINANCE_CONNECTOR_CPP_USER_AGENT` overrides it, but only with a `binance-cli` /
/// `binance-skill` agent of the form `binance-cli[/x[/y]] (a; b; c)`.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string build_user_agent(std::string_view product);

/// `""` → empty, `MILLISECOND` / `MICROSECOND` (all upper or all lower case) → the unit, anything
/// else throws `ConfigError`.
[[nodiscard]] BINANCE_COMMON_EXPORT std::optional<TimeUnit>
validate_time_unit(std::string_view value);

/// Milliseconds since the Unix epoch.
[[nodiscard]] BINANCE_COMMON_EXPORT std::int64_t timestamp_ms();

/// `provider()` if set, else `timestamp_ms()`: the `timestamp` of a signed request.
[[nodiscard]] BINANCE_COMMON_EXPORT std::int64_t timestamp_ms(const TimestampProvider& provider);

/// Builds a stream name from a template such as `/<symbol>@depth<levels>@<updateSpeed>`.
///
/// - Variable names match case-insensitively, ignoring `_` and `-`.
/// - A missing variable becomes empty, and a trailing `@` is then dropped.
/// - With a leading `/`, the value of a placeholder at the very start is lower-cased (symbols),
///   unless `lowercase_head` is false. A `<listenKey>` is never lower-cased: listen keys are
///   case-sensitive.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string
replace_websocket_streams_placeholders(std::string_view input,
                                       const std::map<std::string, std::string>& variables,
                                       bool lowercase_head = true);

/// As `replace_websocket_streams_placeholders`, but no value changes case: `/<symbol>@quote` with
/// `AAPL` gives `AAPL@quote` (for products whose stream names are case-sensitive, e.g. stocks).
[[nodiscard]] BINANCE_COMMON_EXPORT std::string
replace_websocket_streams_placeholders_preserve_case(
    std::string_view input, const std::map<std::string, std::string>& variables);

} // namespace binance::common::detail
