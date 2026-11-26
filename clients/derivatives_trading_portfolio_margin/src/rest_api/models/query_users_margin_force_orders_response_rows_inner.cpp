//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_users_margin_force_orders_response_rows_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryUsersMarginForceOrdersResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryUsersMarginForceOrdersResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryUsersMarginForceOrdersResponseRowsInner");
    QueryUsersMarginForceOrdersResponseRowsInner out;
    common::detail::json::read(obj, "avgPrice", out.avg_price);
    common::detail::json::read(obj, "executedQty", out.executed_qty);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "updatedTime", out.updated_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUsersMarginForceOrdersResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "avgPrice", v.avg_price);
    common::detail::json::write(obj, "executedQty", v.executed_qty);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "updatedTime", v.updated_time);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
