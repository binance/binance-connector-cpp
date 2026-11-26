//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/place_multiple_orders_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

PlaceMultipleOrdersResponseInner
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PlaceMultipleOrdersResponseInner");
    PlaceMultipleOrdersResponseInner out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "executedQty", out.executed_qty);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "reduceOnly", out.reduce_only);
    common::detail::json::read(obj, "postOnly", out.post_only);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "avgPrice", out.avg_price);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    common::detail::json::read(obj, "priceScale", out.price_scale);
    common::detail::json::read(obj, "quantityScale", out.quantity_scale);
    common::detail::json::read(obj, "optionSide", out.option_side);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    common::detail::json::read(obj, "mmp", out.mmp);
    common::detail::json::read(obj, "selfTradePreventionMode", out.self_trade_prevention_mode);
    common::detail::json::read(obj, "source", out.source);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PlaceMultipleOrdersResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "executedQty", v.executed_qty);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "reduceOnly", v.reduce_only);
    common::detail::json::write(obj, "postOnly", v.post_only);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "avgPrice", v.avg_price);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
    common::detail::json::write(obj, "priceScale", v.price_scale);
    common::detail::json::write(obj, "quantityScale", v.quantity_scale);
    common::detail::json::write(obj, "optionSide", v.option_side);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
    common::detail::json::write(obj, "mmp", v.mmp);
    common::detail::json::write(obj, "selfTradePreventionMode", v.self_trade_prevention_mode);
    common::detail::json::write(obj, "source", v.source);
}

} // namespace binance::derivatives_trading_options::rest_api
