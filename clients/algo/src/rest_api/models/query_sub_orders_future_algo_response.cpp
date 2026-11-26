//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/algo/rest_api/models/query_sub_orders_future_algo_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::algo::rest_api {

QuerySubOrdersFutureAlgoResponse
tag_invoke(boost::json::value_to_tag<QuerySubOrdersFutureAlgoResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QuerySubOrdersFutureAlgoResponse");
    QuerySubOrdersFutureAlgoResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "executedQty", out.executed_qty);
    common::detail::json::read(obj, "executedAmt", out.executed_amt);
    common::detail::json::read(obj, "subOrders", out.sub_orders);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubOrdersFutureAlgoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "executedQty", v.executed_qty);
    common::detail::json::write(obj, "executedAmt", v.executed_amt);
    common::detail::json::write(obj, "subOrders", v.sub_orders);
}

} // namespace binance::algo::rest_api
