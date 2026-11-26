//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/move_position_for_sub_account_response.hpp>

namespace binance::sub_account::rest_api {

MovePositionForSubAccountResponse
tag_invoke(boost::json::value_to_tag<MovePositionForSubAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MovePositionForSubAccountResponse");
    MovePositionForSubAccountResponse out;
    common::detail::json::read(obj, "movePositionOrders", out.move_position_orders);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MovePositionForSubAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "movePositionOrders", v.move_position_orders);
}

} // namespace binance::sub_account::rest_api
