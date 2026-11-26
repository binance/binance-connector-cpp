//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/place_option_order_response.hpp>

namespace binance::stock_options::rest_api {

PlaceOptionOrderResponse tag_invoke(boost::json::value_to_tag<PlaceOptionOrderResponse> /*tag*/,
                                    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PlaceOptionOrderResponse");
    PlaceOptionOrderResponse out;
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PlaceOptionOrderResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
}

} // namespace binance::stock_options::rest_api
