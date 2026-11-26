//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/algo/rest_api/models/query_sub_orders_future_algo_response_sub_orders_inner.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::algo::rest_api {

QuerySubOrdersFutureAlgoResponseSubOrdersInner
tag_invoke(boost::json::value_to_tag<QuerySubOrdersFutureAlgoResponseSubOrdersInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QuerySubOrdersFutureAlgoResponseSubOrdersInner");
    QuerySubOrdersFutureAlgoResponseSubOrdersInner out;
    common::detail::json::read(obj, "algoId", out.algo_id);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "orderStatus", out.order_status);
    common::detail::json::read(obj, "executedQty", out.executed_qty);
    common::detail::json::read(obj, "executedAmt", out.executed_amt);
    common::detail::json::read(obj, "feeAmt", out.fee_amt);
    common::detail::json::read(obj, "feeAsset", out.fee_asset);
    common::detail::json::read(obj, "bookTime", out.book_time);
    common::detail::json::read(obj, "avgPrice", out.avg_price);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "subId", out.sub_id);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "origQty", out.orig_qty);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubOrdersFutureAlgoResponseSubOrdersInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "algoId", v.algo_id);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "orderStatus", v.order_status);
    common::detail::json::write(obj, "executedQty", v.executed_qty);
    common::detail::json::write(obj, "executedAmt", v.executed_amt);
    common::detail::json::write(obj, "feeAmt", v.fee_amt);
    common::detail::json::write(obj, "feeAsset", v.fee_asset);
    common::detail::json::write(obj, "bookTime", v.book_time);
    common::detail::json::write(obj, "avgPrice", v.avg_price);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "subId", v.sub_id);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "origQty", v.orig_qty);
}

} // namespace binance::algo::rest_api
