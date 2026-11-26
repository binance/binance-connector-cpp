//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/open_order_list_response_inner_orders_inner.hpp>

namespace binance::spot::rest_api {

OpenOrderListResponseInnerOrdersInner
tag_invoke(boost::json::value_to_tag<OpenOrderListResponseInnerOrdersInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OpenOrderListResponseInnerOrdersInner");
    OpenOrderListResponseInnerOrdersInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OpenOrderListResponseInnerOrdersInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
}

} // namespace binance::spot::rest_api
