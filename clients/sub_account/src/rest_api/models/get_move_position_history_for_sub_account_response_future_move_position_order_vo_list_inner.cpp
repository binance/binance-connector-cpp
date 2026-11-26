//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_move_position_history_for_sub_account_response_future_move_position_order_vo_list_inner.hpp>

namespace binance::sub_account::rest_api {

GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner tag_invoke(
    boost::json::value_to_tag<
        GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner");
    GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner out;
    common::detail::json::read(obj, "fromUserEmail", out.from_user_email);
    common::detail::json::read(obj, "toUserEmail", out.to_user_email);
    common::detail::json::read(obj, "productType", out.product_type);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "timeStamp", out.time_stamp);
    return out;
}

void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "fromUserEmail", v.from_user_email);
    common::detail::json::write(obj, "toUserEmail", v.to_user_email);
    common::detail::json::write(obj, "productType", v.product_type);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "timeStamp", v.time_stamp);
}

} // namespace binance::sub_account::rest_api
