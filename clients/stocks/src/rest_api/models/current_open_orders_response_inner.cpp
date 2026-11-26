//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/current_open_orders_response_inner.hpp>

namespace binance::stocks::rest_api {

CurrentOpenOrdersResponseInner
tag_invoke(boost::json::value_to_tag<CurrentOpenOrdersResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CurrentOpenOrdersResponseInner");
    CurrentOpenOrdersResponseInner out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "quote", out.quote);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "orderType", out.order_type);
    common::detail::json::read(obj, "limitPrice", out.limit_price);
    common::detail::json::read(obj, "avgFilledPrice", out.avg_filled_price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "notional", out.notional);
    common::detail::json::read(obj, "filledQty", out.filled_qty);
    common::detail::json::read(obj, "filledTotal", out.filled_total);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "session", out.session);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "createdAt", out.created_at);
    common::detail::json::read(obj, "updatedAt", out.updated_at);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CurrentOpenOrdersResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "quote", v.quote);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "orderType", v.order_type);
    common::detail::json::write(obj, "limitPrice", v.limit_price);
    common::detail::json::write(obj, "avgFilledPrice", v.avg_filled_price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "notional", v.notional);
    common::detail::json::write(obj, "filledQty", v.filled_qty);
    common::detail::json::write(obj, "filledTotal", v.filled_total);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "session", v.session);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "createdAt", v.created_at);
    common::detail::json::write(obj, "updatedAt", v.updated_at);
}

} // namespace binance::stocks::rest_api
