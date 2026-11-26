//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cm_notional_and_leverage_brackets_response_inner_brackets_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

CmNotionalAndLeverageBracketsResponseInnerBracketsInner tag_invoke(
    boost::json::value_to_tag<CmNotionalAndLeverageBracketsResponseInnerBracketsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "CmNotionalAndLeverageBracketsResponseInnerBracketsInner");
    CmNotionalAndLeverageBracketsResponseInnerBracketsInner out;
    common::detail::json::read(obj, "bracket", out.bracket);
    common::detail::json::read(obj, "initialLeverage", out.initial_leverage);
    common::detail::json::read(obj, "qtyCap", out.qty_cap);
    common::detail::json::read(obj, "qtyFloor", out.qty_floor);
    common::detail::json::read(obj, "maintMarginRatio", out.maint_margin_ratio);
    common::detail::json::read(obj, "cum", out.cum);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CmNotionalAndLeverageBracketsResponseInnerBracketsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "bracket", v.bracket);
    common::detail::json::write(obj, "initialLeverage", v.initial_leverage);
    common::detail::json::write(obj, "qtyCap", v.qty_cap);
    common::detail::json::write(obj, "qtyFloor", v.qty_floor);
    common::detail::json::write(obj, "maintMarginRatio", v.maint_margin_ratio);
    common::detail::json::write(obj, "cum", v.cum);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
