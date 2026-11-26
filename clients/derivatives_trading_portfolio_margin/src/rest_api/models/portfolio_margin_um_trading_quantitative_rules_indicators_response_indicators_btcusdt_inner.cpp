//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/portfolio_margin_um_trading_quantitative_rules_indicators_response_indicators_btcusdt_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner tag_invoke(
    boost::json::value_to_tag<
        PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner");
    PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner out;
    common::detail::json::read(obj, "isLocked", out.is_locked);
    common::detail::json::read(obj, "plannedRecoverTime", out.planned_recover_time);
    common::detail::json::read(obj, "indicator", out.indicator);
    common::detail::json::read(obj, "value", out.value);
    common::detail::json::read(obj, "triggerValue", out.trigger_value);
    return out;
}

void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "isLocked", v.is_locked);
    common::detail::json::write(obj, "plannedRecoverTime", v.planned_recover_time);
    common::detail::json::write(obj, "indicator", v.indicator);
    common::detail::json::write(obj, "value", v.value);
    common::detail::json::write(obj, "triggerValue", v.trigger_value);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
