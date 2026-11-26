//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/order_list_opo_response.hpp>

namespace binance::spot::rest_api {

OrderListOpoResponse tag_invoke(boost::json::value_to_tag<OrderListOpoResponse> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OrderListOpoResponse");
    OrderListOpoResponse out;
    common::detail::json::read(obj, "orderListId", out.order_list_id);
    common::detail::json::read(obj, "contingencyType", out.contingency_type);
    common::detail::json::read(obj, "listStatusType", out.list_status_type);
    common::detail::json::read(obj, "listOrderStatus", out.list_order_status);
    common::detail::json::read(obj, "listClientOrderId", out.list_client_order_id);
    common::detail::json::read(obj, "transactionTime", out.transaction_time);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "orders", out.orders);
    common::detail::json::read(obj, "orderReports", out.order_reports);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderListOpoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderListId", v.order_list_id);
    common::detail::json::write(obj, "contingencyType", v.contingency_type);
    common::detail::json::write(obj, "listStatusType", v.list_status_type);
    common::detail::json::write(obj, "listOrderStatus", v.list_order_status);
    common::detail::json::write(obj, "listClientOrderId", v.list_client_order_id);
    common::detail::json::write(obj, "transactionTime", v.transaction_time);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "orders", v.orders);
    common::detail::json::write(obj, "orderReports", v.order_reports);
}

} // namespace binance::spot::rest_api
