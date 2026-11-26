//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/algo/rest_api/models/query_current_algo_open_orders_spot_algo_response_orders_inner.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::algo::rest_api {

QueryCurrentAlgoOpenOrdersSpotAlgoResponseOrdersInner
tag_invoke(boost::json::value_to_tag<QueryCurrentAlgoOpenOrdersSpotAlgoResponseOrdersInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryCurrentAlgoOpenOrdersSpotAlgoResponseOrdersInner");
    QueryCurrentAlgoOpenOrdersSpotAlgoResponseOrdersInner out;
    common::detail::json::read(obj, "algoId", out.algo_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "totalQty", out.total_qty);
    common::detail::json::read(obj, "executedQty", out.executed_qty);
    common::detail::json::read(obj, "executedAmt", out.executed_amt);
    common::detail::json::read(obj, "avgPrice", out.avg_price);
    common::detail::json::read(obj, "clientAlgoId", out.client_algo_id);
    common::detail::json::read(obj, "bookTime", out.book_time);
    common::detail::json::read(obj, "endTime", out.end_time);
    common::detail::json::read(obj, "algoStatus", out.algo_status);
    common::detail::json::read(obj, "algoType", out.algo_type);
    common::detail::json::read(obj, "urgency", out.urgency);
    common::detail::json::read(obj, "duration", out.duration);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryCurrentAlgoOpenOrdersSpotAlgoResponseOrdersInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "algoId", v.algo_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "totalQty", v.total_qty);
    common::detail::json::write(obj, "executedQty", v.executed_qty);
    common::detail::json::write(obj, "executedAmt", v.executed_amt);
    common::detail::json::write(obj, "avgPrice", v.avg_price);
    common::detail::json::write(obj, "clientAlgoId", v.client_algo_id);
    common::detail::json::write(obj, "bookTime", v.book_time);
    common::detail::json::write(obj, "endTime", v.end_time);
    common::detail::json::write(obj, "algoStatus", v.algo_status);
    common::detail::json::write(obj, "algoType", v.algo_type);
    common::detail::json::write(obj, "urgency", v.urgency);
    common::detail::json::write(obj, "duration", v.duration);
}

} // namespace binance::algo::rest_api
