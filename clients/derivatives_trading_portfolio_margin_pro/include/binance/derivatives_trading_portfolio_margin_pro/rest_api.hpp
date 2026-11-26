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
#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/rest_api.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT std::string_view
product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Derivatives Trading Portfolio Margin Pro REST API client, created with
/// `DerivativesTradingPortfolioMarginProRestApi::production(config)` and the other factories of
/// `rest_api::RestApi`.
using DerivativesTradingPortfolioMarginProRestApi = rest_api::RestApi;

} // namespace binance::derivatives_trading_portfolio_margin_pro
