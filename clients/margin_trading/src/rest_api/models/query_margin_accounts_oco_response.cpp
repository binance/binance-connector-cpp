//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_oco_response.hpp>

namespace binance::margin_trading::rest_api {

QueryMarginAccountsOcoResponse
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOcoResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryMarginAccountsOcoResponse");
    QueryMarginAccountsOcoResponse out;
    common::detail::json::read(obj, "orderListId", out.order_list_id);
    common::detail::json::read(obj, "contingencyType", out.contingency_type);
    common::detail::json::read(obj, "listStatusType", out.list_status_type);
    common::detail::json::read(obj, "listOrderStatus", out.list_order_status);
    common::detail::json::read(obj, "listClientOrderId", out.list_client_order_id);
    common::detail::json::read(obj, "transactionTime", out.transaction_time);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "isIsolated", out.is_isolated);
    common::detail::json::read(obj, "orders", out.orders);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryMarginAccountsOcoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderListId", v.order_list_id);
    common::detail::json::write(obj, "contingencyType", v.contingency_type);
    common::detail::json::write(obj, "listStatusType", v.list_status_type);
    common::detail::json::write(obj, "listOrderStatus", v.list_order_status);
    common::detail::json::write(obj, "listClientOrderId", v.list_client_order_id);
    common::detail::json::write(obj, "transactionTime", v.transaction_time);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "isIsolated", v.is_isolated);
    common::detail::json::write(obj, "orders", v.orders);
}

} // namespace binance::margin_trading::rest_api
