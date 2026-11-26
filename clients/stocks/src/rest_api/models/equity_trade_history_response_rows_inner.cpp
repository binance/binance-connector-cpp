//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/equity_trade_history_response_rows_inner.hpp>

namespace binance::stocks::rest_api {

EquityTradeHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<EquityTradeHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "EquityTradeHistoryResponseRowsInner");
    EquityTradeHistoryResponseRowsInner out;
    common::detail::json::read(obj, "executionId", out.execution_id);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "quote", out.quote);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "orderType", out.order_type);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "executionAt", out.execution_at);
    common::detail::json::read(obj, "updatedAt", out.updated_at);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EquityTradeHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "executionId", v.execution_id);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "quote", v.quote);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "orderType", v.order_type);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "executionAt", v.execution_at);
    common::detail::json::write(obj, "updatedAt", v.updated_at);
}

} // namespace binance::stocks::rest_api
