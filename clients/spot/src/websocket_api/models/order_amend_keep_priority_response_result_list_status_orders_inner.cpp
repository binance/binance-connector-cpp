//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/order_amend_keep_priority_response_result_list_status_orders_inner.hpp>

namespace binance::spot::websocket_api {

OrderAmendKeepPriorityResponseResultListStatusOrdersInner tag_invoke(
    boost::json::value_to_tag<OrderAmendKeepPriorityResponseResultListStatusOrdersInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "OrderAmendKeepPriorityResponseResultListStatusOrdersInner");
    OrderAmendKeepPriorityResponseResultListStatusOrdersInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderAmendKeepPriorityResponseResultListStatusOrdersInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
}

} // namespace binance::spot::websocket_api
