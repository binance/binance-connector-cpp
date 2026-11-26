//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/portfolio_margin_um_trading_quantitative_rules_indicators_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse tag_invoke(
    boost::json::value_to_tag<PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse");
    PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse out;
    common::detail::json::read(obj, "indicators", out.indicators);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "indicators", v.indicators);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
