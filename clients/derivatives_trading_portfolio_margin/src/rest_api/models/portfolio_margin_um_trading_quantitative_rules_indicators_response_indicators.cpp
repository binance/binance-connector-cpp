//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/portfolio_margin_um_trading_quantitative_rules_indicators_response_indicators.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators
tag_invoke(boost::json::value_to_tag<
               PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators");
    PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators out;
    common::detail::json::read(obj, "BTCUSDT", out.btcusdt);
    common::detail::json::read(obj, "ACCOUNT", out.account);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicators& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "BTCUSDT", v.btcusdt);
    common::detail::json::write(obj, "ACCOUNT", v.account);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
