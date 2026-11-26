//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_account_detail_v2_response_positions_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

GetUmAccountDetailV2ResponsePositionsInner
tag_invoke(boost::json::value_to_tag<GetUmAccountDetailV2ResponsePositionsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetUmAccountDetailV2ResponsePositionsInner");
    GetUmAccountDetailV2ResponsePositionsInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "initialMargin", out.initial_margin);
    common::detail::json::read(obj, "maintMargin", out.maint_margin);
    common::detail::json::read(obj, "unrealizedProfit", out.unrealized_profit);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "positionAmt", out.position_amt);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "notional", out.notional);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetUmAccountDetailV2ResponsePositionsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "initialMargin", v.initial_margin);
    common::detail::json::write(obj, "maintMargin", v.maint_margin);
    common::detail::json::write(obj, "unrealizedProfit", v.unrealized_profit);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "positionAmt", v.position_amt);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "notional", v.notional);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
