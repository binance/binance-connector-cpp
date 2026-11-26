//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_cancel_orders_response_failed_inner.hpp>

namespace binance::w3w_prediction::rest_api {

BatchCancelOrdersResponseFailedInner
tag_invoke(boost::json::value_to_tag<BatchCancelOrdersResponseFailedInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BatchCancelOrdersResponseFailedInner");
    BatchCancelOrdersResponseFailedInner out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "reason", out.reason);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BatchCancelOrdersResponseFailedInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "reason", v.reason);
}

} // namespace binance::w3w_prediction::rest_api
