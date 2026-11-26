//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_futures_position_risk_of_sub_account_response_inner.hpp>

namespace binance::sub_account::rest_api {

GetFuturesPositionRiskOfSubAccountResponseInner
tag_invoke(boost::json::value_to_tag<GetFuturesPositionRiskOfSubAccountResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFuturesPositionRiskOfSubAccountResponseInner");
    GetFuturesPositionRiskOfSubAccountResponseInner out;
    common::detail::json::read(obj, "entryPrice", out.entry_price);
    common::detail::json::read(obj, "leverage", out.leverage);
    common::detail::json::read(obj, "maxNotional", out.max_notional);
    common::detail::json::read(obj, "liquidationPrice", out.liquidation_price);
    common::detail::json::read(obj, "markPrice", out.mark_price);
    common::detail::json::read(obj, "positionAmount", out.position_amount);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "unrealizedProfit", out.unrealized_profit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFuturesPositionRiskOfSubAccountResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "entryPrice", v.entry_price);
    common::detail::json::write(obj, "leverage", v.leverage);
    common::detail::json::write(obj, "maxNotional", v.max_notional);
    common::detail::json::write(obj, "liquidationPrice", v.liquidation_price);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "positionAmount", v.position_amount);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "unrealizedProfit", v.unrealized_profit);
}

} // namespace binance::sub_account::rest_api
