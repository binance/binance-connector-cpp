//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <string_view>

#include <binance/common/config.hpp>
#include <binance/pay/export.hpp>
#include <binance/pay/rest_api/rest_api.hpp>

namespace binance::pay {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_PAY_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Pay REST API client, created with `PayRestApi::production(config)`
/// and the other factories of `rest_api::RestApi`.
using PayRestApi = rest_api::RestApi;

} // namespace binance::pay
