//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/test_order_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

TestOrderResponse tag_invoke(boost::json::value_to_tag<TestOrderResponse> /*tag*/,
                             const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TestOrderResponse");
    TestOrderResponse out;
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    common::detail::json::read(obj, "cumQty", out.cum_qty);
    common::detail::json::read(obj, "cumQuote", out.cum_quote);
    common::detail::json::read(obj, "executedQty", out.executed_qty);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "avgPrice", out.avg_price);
    common::detail::json::read(obj, "origQty", out.orig_qty);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "reduceOnly", out.reduce_only);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "stopPrice", out.stop_price);
    common::detail::json::read(obj, "closePosition", out.close_position);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "origType", out.orig_type);
    common::detail::json::read(obj, "activatePrice", out.activate_price);
    common::detail::json::read(obj, "priceRate", out.price_rate);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "workingType", out.working_type);
    common::detail::json::read(obj, "priceProtect", out.price_protect);
    common::detail::json::read(obj, "priceMatch", out.price_match);
    common::detail::json::read(obj, "selfTradePreventionMode", out.self_trade_prevention_mode);
    common::detail::json::read(obj, "goodTillDate", out.good_till_date);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TestOrderResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
    common::detail::json::write(obj, "cumQty", v.cum_qty);
    common::detail::json::write(obj, "cumQuote", v.cum_quote);
    common::detail::json::write(obj, "executedQty", v.executed_qty);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "avgPrice", v.avg_price);
    common::detail::json::write(obj, "origQty", v.orig_qty);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "reduceOnly", v.reduce_only);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "stopPrice", v.stop_price);
    common::detail::json::write(obj, "closePosition", v.close_position);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "origType", v.orig_type);
    common::detail::json::write(obj, "activatePrice", v.activate_price);
    common::detail::json::write(obj, "priceRate", v.price_rate);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "workingType", v.working_type);
    common::detail::json::write(obj, "priceProtect", v.price_protect);
    common::detail::json::write(obj, "priceMatch", v.price_match);
    common::detail::json::write(obj, "selfTradePreventionMode", v.self_trade_prevention_mode);
    common::detail::json::write(obj, "goodTillDate", v.good_till_date);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
