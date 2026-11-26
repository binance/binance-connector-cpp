//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/um_notional_and_leverage_brackets_response_inner_brackets_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

UmNotionalAndLeverageBracketsResponseInnerBracketsInner tag_invoke(
    boost::json::value_to_tag<UmNotionalAndLeverageBracketsResponseInnerBracketsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "UmNotionalAndLeverageBracketsResponseInnerBracketsInner");
    UmNotionalAndLeverageBracketsResponseInnerBracketsInner out;
    common::detail::json::read(obj, "bracket", out.bracket);
    common::detail::json::read(obj, "initialLeverage", out.initial_leverage);
    common::detail::json::read(obj, "notionalCap", out.notional_cap);
    common::detail::json::read(obj, "notionalFloor", out.notional_floor);
    common::detail::json::read(obj, "maintMarginRatio", out.maint_margin_ratio);
    common::detail::json::read(obj, "cum", out.cum);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UmNotionalAndLeverageBracketsResponseInnerBracketsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "bracket", v.bracket);
    common::detail::json::write(obj, "initialLeverage", v.initial_leverage);
    common::detail::json::write(obj, "notionalCap", v.notional_cap);
    common::detail::json::write(obj, "notionalFloor", v.notional_floor);
    common::detail::json::write(obj, "maintMarginRatio", v.maint_margin_ratio);
    common::detail::json::write(obj, "cum", v.cum);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
