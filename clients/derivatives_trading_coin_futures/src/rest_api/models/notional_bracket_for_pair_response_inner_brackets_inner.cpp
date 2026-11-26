//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/notional_bracket_for_pair_response_inner_brackets_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

NotionalBracketForPairResponseInnerBracketsInner
tag_invoke(boost::json::value_to_tag<NotionalBracketForPairResponseInnerBracketsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "NotionalBracketForPairResponseInnerBracketsInner");
    NotionalBracketForPairResponseInnerBracketsInner out;
    common::detail::json::read(obj, "bracket", out.bracket);
    common::detail::json::read(obj, "initialLeverage", out.initial_leverage);
    common::detail::json::read(obj, "qtyCap", out.qty_cap);
    common::detail::json::read(obj, "qtylFloor", out.qtyl_floor);
    common::detail::json::read(obj, "maintMarginRatio", out.maint_margin_ratio);
    common::detail::json::read(obj, "cum", out.cum);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const NotionalBracketForPairResponseInnerBracketsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "bracket", v.bracket);
    common::detail::json::write(obj, "initialLeverage", v.initial_leverage);
    common::detail::json::write(obj, "qtyCap", v.qty_cap);
    common::detail::json::write(obj, "qtylFloor", v.qtyl_floor);
    common::detail::json::write(obj, "maintMarginRatio", v.maint_margin_ratio);
    common::detail::json::write(obj, "cum", v.cum);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
