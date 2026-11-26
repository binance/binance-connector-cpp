//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_liability_coin_leverage_bracket_in_cross_margin_pro_mode_response_inner_brackets_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner tag_invoke(
    boost::json::value_to_tag<
        QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner");
    QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner out;
    common::detail::json::read(obj, "leverage", out.leverage);
    common::detail::json::read(obj, "maxDebt", out.max_debt);
    common::detail::json::read(obj, "maintenanceMarginRate", out.maintenance_margin_rate);
    common::detail::json::read(obj, "initialMarginRate", out.initial_margin_rate);
    common::detail::json::read(obj, "fastNum", out.fast_num);
    return out;
}

void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "leverage", v.leverage);
    common::detail::json::write(obj, "maxDebt", v.max_debt);
    common::detail::json::write(obj, "maintenanceMarginRate", v.maintenance_margin_rate);
    common::detail::json::write(obj, "initialMarginRate", v.initial_margin_rate);
    common::detail::json::write(obj, "fastNum", v.fast_num);
}

} // namespace binance::margin_trading::rest_api
