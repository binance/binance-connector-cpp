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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/portfolio_margin_um_trading_quantitative_rules_indicators_response_indicators.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse {
    std::optional<PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators> indicators;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool operator==(const PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse tag_invoke(
    boost::json::value_to_tag<PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
