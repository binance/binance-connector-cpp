//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/order_amendments_response_result_inner.hpp>

namespace binance::spot::websocket_api {

OrderAmendmentsResponseResultInner
tag_invoke(boost::json::value_to_tag<OrderAmendmentsResponseResultInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OrderAmendmentsResponseResultInner");
    OrderAmendmentsResponseResultInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "executionId", out.execution_id);
    common::detail::json::read(obj, "origClientOrderId", out.orig_client_order_id);
    common::detail::json::read(obj, "newClientOrderId", out.new_client_order_id);
    common::detail::json::read(obj, "origQty", out.orig_qty);
    common::detail::json::read(obj, "newQty", out.new_qty);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderAmendmentsResponseResultInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "executionId", v.execution_id);
    common::detail::json::write(obj, "origClientOrderId", v.orig_client_order_id);
    common::detail::json::write(obj, "newClientOrderId", v.new_client_order_id);
    common::detail::json::write(obj, "origQty", v.orig_qty);
    common::detail::json::write(obj, "newQty", v.new_qty);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::spot::websocket_api
