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
#include <binance/algo/rest_api/models/query_current_algo_open_orders_spot_algo_response_orders_inner.hpp>

namespace binance::algo::rest_api {

struct QueryCurrentAlgoOpenOrdersSpotAlgoResponse {
    std::optional<std::int64_t> total;
    std::optional<std::vector<QueryCurrentAlgoOpenOrdersSpotAlgoResponseOrdersInner>> orders;

    bool operator==(const QueryCurrentAlgoOpenOrdersSpotAlgoResponse& /*other*/) const = default;
};

BINANCE_ALGO_EXPORT QueryCurrentAlgoOpenOrdersSpotAlgoResponse
tag_invoke(boost::json::value_to_tag<QueryCurrentAlgoOpenOrdersSpotAlgoResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const QueryCurrentAlgoOpenOrdersSpotAlgoResponse& v);

} // namespace binance::algo::rest_api
