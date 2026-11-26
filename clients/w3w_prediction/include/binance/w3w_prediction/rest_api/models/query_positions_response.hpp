//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response_counts.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response_positions_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response_summary.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryPositionsResponse {
    std::optional<QueryPositionsResponseSummary> summary;
    std::optional<QueryPositionsResponseCounts> counts;
    std::optional<std::vector<QueryPositionsResponsePositionsInner>> positions;

    bool operator==(const QueryPositionsResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryPositionsResponse
tag_invoke(boost::json::value_to_tag<QueryPositionsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryPositionsResponse& v);

} // namespace binance::w3w_prediction::rest_api
