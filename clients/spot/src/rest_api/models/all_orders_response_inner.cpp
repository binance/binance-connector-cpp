//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/all_orders_response_inner.hpp>

namespace binance::spot::rest_api {

AllOrdersResponseInner tag_invoke(boost::json::value_to_tag<AllOrdersResponseInner> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AllOrdersResponseInner");
    AllOrdersResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
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
    common::detail::json::read(obj, "stopPrice", out.stop_price);
    common::detail::json::read(obj, "icebergQty", out.iceberg_qty);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "isWorking", out.is_working);
    common::detail::json::read(obj, "origQuoteOrderQty", out.orig_quote_order_qty);
    common::detail::json::read(obj, "workingTime", out.working_time);
    common::detail::json::read(obj, "selfTradePreventionMode", out.self_trade_prevention_mode);
    common::detail::json::read(obj, "preventedMatchId", out.prevented_match_id);
    common::detail::json::read(obj, "preventedQuantity", out.prevented_quantity);
    common::detail::json::read(obj, "strategyId", out.strategy_id);
    common::detail::json::read(obj, "strategyType", out.strategy_type);
    common::detail::json::read(obj, "trailingDelta", out.trailing_delta);
    common::detail::json::read(obj, "trailingTime", out.trailing_time);
    common::detail::json::read(obj, "usedSor", out.used_sor);
    common::detail::json::read(obj, "workingFloor", out.working_floor);
    common::detail::json::read(obj, "pegPriceType", out.peg_price_type);
    common::detail::json::read(obj, "pegOffsetType", out.peg_offset_type);
    common::detail::json::read(obj, "pegOffsetValue", out.peg_offset_value);
    common::detail::json::read(obj, "peggedPrice", out.pegged_price);
    common::detail::json::read(obj, "expiryReason", out.expiry_reason);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AllOrdersResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
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
    common::detail::json::write(obj, "stopPrice", v.stop_price);
    common::detail::json::write(obj, "icebergQty", v.iceberg_qty);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "isWorking", v.is_working);
    common::detail::json::write(obj, "origQuoteOrderQty", v.orig_quote_order_qty);
    common::detail::json::write(obj, "workingTime", v.working_time);
    common::detail::json::write(obj, "selfTradePreventionMode", v.self_trade_prevention_mode);
    common::detail::json::write(obj, "preventedMatchId", v.prevented_match_id);
    common::detail::json::write(obj, "preventedQuantity", v.prevented_quantity);
    common::detail::json::write(obj, "strategyId", v.strategy_id);
    common::detail::json::write(obj, "strategyType", v.strategy_type);
    common::detail::json::write(obj, "trailingDelta", v.trailing_delta);
    common::detail::json::write(obj, "trailingTime", v.trailing_time);
    common::detail::json::write(obj, "usedSor", v.used_sor);
    common::detail::json::write(obj, "workingFloor", v.working_floor);
    common::detail::json::write(obj, "pegPriceType", v.peg_price_type);
    common::detail::json::write(obj, "pegOffsetType", v.peg_offset_type);
    common::detail::json::write(obj, "pegOffsetValue", v.peg_offset_value);
    common::detail::json::write(obj, "peggedPrice", v.pegged_price);
    common::detail::json::write(obj, "expiryReason", v.expiry_reason);
}

} // namespace binance::spot::rest_api
