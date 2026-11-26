//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/convert/rest_api/models/place_limit_order_response.hpp>

namespace binance::convert::rest_api {

PlaceLimitOrderResponse tag_invoke(boost::json::value_to_tag<PlaceLimitOrderResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PlaceLimitOrderResponse");
    PlaceLimitOrderResponse out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PlaceLimitOrderResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::convert::rest_api
