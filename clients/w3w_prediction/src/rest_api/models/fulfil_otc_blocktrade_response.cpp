//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/fulfil_otc_blocktrade_response.hpp>

namespace binance::w3w_prediction::rest_api {

FulfilOtcBlocktradeResponse
tag_invoke(boost::json::value_to_tag<FulfilOtcBlocktradeResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FulfilOtcBlocktradeResponse");
    FulfilOtcBlocktradeResponse out;
    common::detail::json::read(obj, "orderId", out.order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FulfilOtcBlocktradeResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
}

} // namespace binance::w3w_prediction::rest_api
