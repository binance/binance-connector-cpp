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

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/query_settled_position_history_response_positions_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct QuerySettledPositionHistoryResponse {
    std::optional<std::int64_t> total_count;
    std::optional<std::vector<QuerySettledPositionHistoryResponsePositionsInner>> positions;

    bool operator==(const QuerySettledPositionHistoryResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QuerySettledPositionHistoryResponse
tag_invoke(boost::json::value_to_tag<QuerySettledPositionHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QuerySettledPositionHistoryResponse& v);

} // namespace binance::w3w_prediction::rest_api
