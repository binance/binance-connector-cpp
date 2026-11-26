//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_all_current_um_open_algo_orders_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryAllCurrentUmOpenAlgoOrdersResponseInner
tag_invoke(boost::json::value_to_tag<QueryAllCurrentUmOpenAlgoOrdersResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryAllCurrentUmOpenAlgoOrdersResponseInner");
    QueryAllCurrentUmOpenAlgoOrdersResponseInner out;
    common::detail::json::read(obj, "algoId", out.algo_id);
    common::detail::json::read(obj, "clientAlgoId", out.client_algo_id);
    common::detail::json::read(obj, "algoType", out.algo_type);
    common::detail::json::read(obj, "orderType", out.order_type);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "algoStatus", out.algo_status);
    common::detail::json::read(obj, "triggerPrice", out.trigger_price);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "selfTradePreventionMode", out.self_trade_prevention_mode);
    common::detail::json::read(obj, "workingType", out.working_type);
    common::detail::json::read(obj, "priceMatch", out.price_match);
    common::detail::json::read(obj, "closePosition", out.close_position);
    common::detail::json::read(obj, "priceProtect", out.price_protect);
    common::detail::json::read(obj, "reduceOnly", out.reduce_only);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "triggerTime", out.trigger_time);
    common::detail::json::read(obj, "goodTillDate", out.good_till_date);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryAllCurrentUmOpenAlgoOrdersResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "algoId", v.algo_id);
    common::detail::json::write(obj, "clientAlgoId", v.client_algo_id);
    common::detail::json::write(obj, "algoType", v.algo_type);
    common::detail::json::write(obj, "orderType", v.order_type);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "algoStatus", v.algo_status);
    common::detail::json::write(obj, "triggerPrice", v.trigger_price);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "selfTradePreventionMode", v.self_trade_prevention_mode);
    common::detail::json::write(obj, "workingType", v.working_type);
    common::detail::json::write(obj, "priceMatch", v.price_match);
    common::detail::json::write(obj, "closePosition", v.close_position);
    common::detail::json::write(obj, "priceProtect", v.price_protect);
    common::detail::json::write(obj, "reduceOnly", v.reduce_only);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "triggerTime", v.trigger_time);
    common::detail::json::write(obj, "goodTillDate", v.good_till_date);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
