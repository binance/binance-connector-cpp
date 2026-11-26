//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_cancel_all_open_orders_on_a_symbol_response_inner.hpp>

namespace binance::margin_trading::rest_api {

MarginAccountCancelAllOpenOrdersOnASymbolResponseInner tag_invoke(
    boost::json::value_to_tag<MarginAccountCancelAllOpenOrdersOnASymbolResponseInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "MarginAccountCancelAllOpenOrdersOnASymbolResponseInner");
    MarginAccountCancelAllOpenOrdersOnASymbolResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "isIsolated", out.is_isolated);
    common::detail::json::read(obj, "origClientOrderId", out.orig_client_order_id);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "orderListId", out.order_list_id);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "origQty", out.orig_qty);
    common::detail::json::read(obj, "executedQty", out.executed_qty);
    common::detail::json::read(obj, "cummulativeQuoteQty", out.cummulative_quote_qty);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "selfTradePreventionMode", out.self_trade_prevention_mode);
    common::detail::json::read(obj, "contingencyType", out.contingency_type);
    common::detail::json::read(obj, "listStatusType", out.list_status_type);
    common::detail::json::read(obj, "listOrderStatus", out.list_order_status);
    common::detail::json::read(obj, "listClientOrderId", out.list_client_order_id);
    common::detail::json::read(obj, "transactionTime", out.transaction_time);
    common::detail::json::read(obj, "orders", out.orders);
    common::detail::json::read(obj, "orderReports", out.order_reports);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MarginAccountCancelAllOpenOrdersOnASymbolResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "isIsolated", v.is_isolated);
    common::detail::json::write(obj, "origClientOrderId", v.orig_client_order_id);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "orderListId", v.order_list_id);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "origQty", v.orig_qty);
    common::detail::json::write(obj, "executedQty", v.executed_qty);
    common::detail::json::write(obj, "cummulativeQuoteQty", v.cummulative_quote_qty);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "selfTradePreventionMode", v.self_trade_prevention_mode);
    common::detail::json::write(obj, "contingencyType", v.contingency_type);
    common::detail::json::write(obj, "listStatusType", v.list_status_type);
    common::detail::json::write(obj, "listOrderStatus", v.list_order_status);
    common::detail::json::write(obj, "listClientOrderId", v.list_client_order_id);
    common::detail::json::write(obj, "transactionTime", v.transaction_time);
    common::detail::json::write(obj, "orders", v.orders);
    common::detail::json::write(obj, "orderReports", v.order_reports);
}

} // namespace binance::margin_trading::rest_api
