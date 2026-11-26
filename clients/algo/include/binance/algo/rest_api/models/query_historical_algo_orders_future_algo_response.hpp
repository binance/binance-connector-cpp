//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/algo/export.hpp>
#include <binance/algo/rest_api/models/query_historical_algo_orders_future_algo_response_orders_inner.hpp>

namespace binance::algo::rest_api {

struct QueryHistoricalAlgoOrdersFutureAlgoResponse {
    std::optional<std::int64_t> total;
    std::optional<std::vector<QueryHistoricalAlgoOrdersFutureAlgoResponseOrdersInner>> orders;

    bool operator==(const QueryHistoricalAlgoOrdersFutureAlgoResponse& /*other*/) const = default;
};

BINANCE_ALGO_EXPORT QueryHistoricalAlgoOrdersFutureAlgoResponse
tag_invoke(boost::json::value_to_tag<QueryHistoricalAlgoOrdersFutureAlgoResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const QueryHistoricalAlgoOrdersFutureAlgoResponse& v);

} // namespace binance::algo::rest_api
