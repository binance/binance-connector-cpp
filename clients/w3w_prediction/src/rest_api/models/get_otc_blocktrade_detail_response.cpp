//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_detail_response.hpp>

namespace binance::w3w_prediction::rest_api {

GetOtcBlocktradeDetailResponse
tag_invoke(boost::json::value_to_tag<GetOtcBlocktradeDetailResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetOtcBlocktradeDetailResponse");
    GetOtcBlocktradeDetailResponse out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "orderData", out.order_data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOtcBlocktradeDetailResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "orderData", v.order_data);
}

} // namespace binance::w3w_prediction::rest_api
