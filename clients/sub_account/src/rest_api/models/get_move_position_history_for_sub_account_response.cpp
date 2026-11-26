//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_move_position_history_for_sub_account_response.hpp>

namespace binance::sub_account::rest_api {

GetMovePositionHistoryForSubAccountResponse
tag_invoke(boost::json::value_to_tag<GetMovePositionHistoryForSubAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetMovePositionHistoryForSubAccountResponse");
    GetMovePositionHistoryForSubAccountResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "futureMovePositionOrderVoList",
                               out.future_move_position_order_vo_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetMovePositionHistoryForSubAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "futureMovePositionOrderVoList",
                                v.future_move_position_order_vo_list);
}

} // namespace binance::sub_account::rest_api
