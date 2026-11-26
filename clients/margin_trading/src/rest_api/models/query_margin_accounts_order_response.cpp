//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_order_response.hpp>

namespace binance::margin_trading::rest_api {

QueryMarginAccountsOrderResponse
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOrderResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryMarginAccountsOrderResponse");
    QueryMarginAccountsOrderResponse out;
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    common::detail::json::read(obj, "cummulativeQuoteQty", out.cummulative_quote_qty);
    common::detail::json::read(obj, "executedQty", out.executed_qty);
    common::detail::json::read(obj, "icebergQty", out.iceberg_qty);
    common::detail::json::read(obj, "isWorking", out.is_working);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "origQty", out.orig_qty);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "stopPrice", out.stop_price);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "isIsolated", out.is_isolated);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "selfTradePreventionMode", out.self_trade_prevention_mode);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryMarginAccountsOrderResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
    common::detail::json::write(obj, "cummulativeQuoteQty", v.cummulative_quote_qty);
    common::detail::json::write(obj, "executedQty", v.executed_qty);
    common::detail::json::write(obj, "icebergQty", v.iceberg_qty);
    common::detail::json::write(obj, "isWorking", v.is_working);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "origQty", v.orig_qty);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "stopPrice", v.stop_price);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "isIsolated", v.is_isolated);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "selfTradePreventionMode", v.self_trade_prevention_mode);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::margin_trading::rest_api
