//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/move_position_for_sub_account_order_args_parameter_inner.hpp>

namespace binance::sub_account::rest_api {

MovePositionForSubAccountOrderArgsParameterInner
tag_invoke(boost::json::value_to_tag<MovePositionForSubAccountOrderArgsParameterInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "MovePositionForSubAccountOrderArgsParameterInner");
    MovePositionForSubAccountOrderArgsParameterInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "positionSide", out.position_side);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MovePositionForSubAccountOrderArgsParameterInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "positionSide", v.position_side);
}

} // namespace binance::sub_account::rest_api
