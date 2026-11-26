//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/algo/rest_api/models/query_historical_algo_orders_spot_algo_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::algo::rest_api {

QueryHistoricalAlgoOrdersSpotAlgoResponse
tag_invoke(boost::json::value_to_tag<QueryHistoricalAlgoOrdersSpotAlgoResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryHistoricalAlgoOrdersSpotAlgoResponse");
    QueryHistoricalAlgoOrdersSpotAlgoResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "orders", out.orders);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryHistoricalAlgoOrdersSpotAlgoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "orders", v.orders);
}

} // namespace binance::algo::rest_api
