//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_cm_conditional_order_history_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryCmConditionalOrderHistoryResponse
tag_invoke(boost::json::value_to_tag<QueryCmConditionalOrderHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryCmConditionalOrderHistoryResponse");
    QueryCmConditionalOrderHistoryResponse out;
    common::detail::json::read(obj, "newClientStrategyId", out.new_client_strategy_id);
    common::detail::json::read(obj, "strategyId", out.strategy_id);
    common::detail::json::read(obj, "strategyStatus", out.strategy_status);
    common::detail::json::read(obj, "strategyType", out.strategy_type);
    common::detail::json::read(obj, "origQty", out.orig_qty);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "reduceOnly", out.reduce_only);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "stopPrice", out.stop_price);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "bookTime", out.book_time);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "triggerTime", out.trigger_time);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "activatePrice", out.activate_price);
    common::detail::json::read(obj, "priceRate", out.price_rate);
    common::detail::json::read(obj, "workingType", out.working_type);
    common::detail::json::read(obj, "priceProtect", out.price_protect);
    common::detail::json::read(obj, "priceMatch", out.price_match);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryCmConditionalOrderHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "newClientStrategyId", v.new_client_strategy_id);
    common::detail::json::write(obj, "strategyId", v.strategy_id);
    common::detail::json::write(obj, "strategyStatus", v.strategy_status);
    common::detail::json::write(obj, "strategyType", v.strategy_type);
    common::detail::json::write(obj, "origQty", v.orig_qty);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "reduceOnly", v.reduce_only);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "stopPrice", v.stop_price);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "bookTime", v.book_time);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "triggerTime", v.trigger_time);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "activatePrice", v.activate_price);
    common::detail::json::write(obj, "priceRate", v.price_rate);
    common::detail::json::write(obj, "workingType", v.working_type);
    common::detail::json::write(obj, "priceProtect", v.price_protect);
    common::detail::json::write(obj, "priceMatch", v.price_match);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
