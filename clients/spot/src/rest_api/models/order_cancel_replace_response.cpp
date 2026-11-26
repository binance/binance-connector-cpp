//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/order_cancel_replace_response.hpp>

namespace binance::spot::rest_api {

OrderCancelReplaceResponse tag_invoke(boost::json::value_to_tag<OrderCancelReplaceResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OrderCancelReplaceResponse");
    OrderCancelReplaceResponse out;
    common::detail::json::read(obj, "cancelResult", out.cancel_result);
    common::detail::json::read(obj, "newOrderResult", out.new_order_result);
    common::detail::json::read(obj, "cancelResponse", out.cancel_response);
    common::detail::json::read(obj, "newOrderResponse", out.new_order_response);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderCancelReplaceResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "cancelResult", v.cancel_result);
    common::detail::json::write(obj, "newOrderResult", v.new_order_result);
    common::detail::json::write(obj, "cancelResponse", v.cancel_response);
    common::detail::json::write(obj, "newOrderResponse", v.new_order_response);
}

} // namespace binance::spot::rest_api
