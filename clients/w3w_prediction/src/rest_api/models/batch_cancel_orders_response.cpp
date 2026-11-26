//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_cancel_orders_response.hpp>

namespace binance::w3w_prediction::rest_api {

BatchCancelOrdersResponse tag_invoke(boost::json::value_to_tag<BatchCancelOrdersResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BatchCancelOrdersResponse");
    BatchCancelOrdersResponse out;
    common::detail::json::read(obj, "canceled", out.canceled);
    common::detail::json::read(obj, "failed", out.failed);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BatchCancelOrdersResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "canceled", v.canceled);
    common::detail::json::write(obj, "failed", v.failed);
}

} // namespace binance::w3w_prediction::rest_api
