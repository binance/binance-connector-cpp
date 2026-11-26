//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_futures_position_risk_of_sub_account_v2_response_delivery_position_risk_vos_inner.hpp>

namespace binance::sub_account::rest_api {

GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner
tag_invoke(boost::json::value_to_tag<
               GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner");
    GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner out;
    common::detail::json::read(obj, "entryPrice", out.entry_price);
    common::detail::json::read(obj, "markPrice", out.mark_price);
    common::detail::json::read(obj, "leverage", out.leverage);
    common::detail::json::read(obj, "isolated", out.isolated);
    common::detail::json::read(obj, "isolatedWallet", out.isolated_wallet);
    common::detail::json::read(obj, "isolatedMargin", out.isolated_margin);
    common::detail::json::read(obj, "isAutoAddMargin", out.is_auto_add_margin);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "positionAmount", out.position_amount);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "unrealizedProfit", out.unrealized_profit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "entryPrice", v.entry_price);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "leverage", v.leverage);
    common::detail::json::write(obj, "isolated", v.isolated);
    common::detail::json::write(obj, "isolatedWallet", v.isolated_wallet);
    common::detail::json::write(obj, "isolatedMargin", v.isolated_margin);
    common::detail::json::write(obj, "isAutoAddMargin", v.is_auto_add_margin);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "positionAmount", v.position_amount);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "unrealizedProfit", v.unrealized_profit);
}

} // namespace binance::sub_account::rest_api
