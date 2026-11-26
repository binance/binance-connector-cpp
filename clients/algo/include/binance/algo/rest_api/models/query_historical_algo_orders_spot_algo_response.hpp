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
#include <binance/algo/rest_api/models/query_historical_algo_orders_spot_algo_response_orders_inner.hpp>

namespace binance::algo::rest_api {

struct QueryHistoricalAlgoOrdersSpotAlgoResponse {
    std::optional<std::int64_t> total;
    std::optional<std::vector<QueryHistoricalAlgoOrdersSpotAlgoResponseOrdersInner>> orders;

    bool operator==(const QueryHistoricalAlgoOrdersSpotAlgoResponse& /*other*/) const = default;
};

BINANCE_ALGO_EXPORT QueryHistoricalAlgoOrdersSpotAlgoResponse
tag_invoke(boost::json::value_to_tag<QueryHistoricalAlgoOrdersSpotAlgoResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const QueryHistoricalAlgoOrdersSpotAlgoResponse& v);

} // namespace binance::algo::rest_api
