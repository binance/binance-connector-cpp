//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/place_order_response.hpp>

namespace binance::w3w_prediction::rest_api {

PlaceOrderResponse tag_invoke(boost::json::value_to_tag<PlaceOrderResponse> /*tag*/,
                              const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PlaceOrderResponse");
    PlaceOrderResponse out;
    common::detail::json::read(obj, "orderId", out.order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PlaceOrderResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
}

} // namespace binance::w3w_prediction::rest_api
