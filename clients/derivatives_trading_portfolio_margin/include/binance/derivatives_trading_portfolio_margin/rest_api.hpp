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
#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/rest_api.hpp>

namespace binance::derivatives_trading_portfolio_margin {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Derivatives Trading Portfolio Margin REST API client, created with
/// `DerivativesTradingPortfolioMarginRestApi::production(config)` and the other factories of
/// `rest_api::RestApi`.
using DerivativesTradingPortfolioMarginRestApi = rest_api::RestApi;

} // namespace binance::derivatives_trading_portfolio_margin
