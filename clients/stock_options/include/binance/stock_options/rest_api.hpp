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
#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/rest_api.hpp>

namespace binance::stock_options {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_STOCK_OPTIONS_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Stock Options REST API client, created with `StockOptionsRestApi::production(config)`
/// and the other factories of `rest_api::RestApi`.
using StockOptionsRestApi = rest_api::RestApi;

} // namespace binance::stock_options
