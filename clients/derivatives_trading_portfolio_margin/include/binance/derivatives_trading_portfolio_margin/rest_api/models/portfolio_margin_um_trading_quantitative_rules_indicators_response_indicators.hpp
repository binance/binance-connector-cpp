//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/portfolio_margin_um_trading_quantitative_rules_indicators_response_indicators_account_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/portfolio_margin_um_trading_quantitative_rules_indicators_response_indicators_btcusdt_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

/// Indicators.
struct PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators {
    /// BTCUSDT.
    std::optional<std::vector<
        PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner>>
        btcusdt;
    /// ACCOUNT.
    std::optional<std::vector<
        PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsACCOUNTInner>>
        account;

    bool operator==(
        const PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators
tag_invoke(boost::json::value_to_tag<
               PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
