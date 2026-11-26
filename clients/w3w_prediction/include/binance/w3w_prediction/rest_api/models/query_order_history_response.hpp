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
#include <binance/w3w_prediction/rest_api/models/query_order_history_response_orders_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryOrderHistoryResponse {
    std::optional<std::int64_t> total;
    std::optional<std::int64_t> offset;
    std::optional<std::int64_t> limit;
    std::optional<std::vector<QueryOrderHistoryResponseOrdersInner>> orders;

    bool operator==(const QueryOrderHistoryResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryOrderHistoryResponse tag_invoke(
    boost::json::value_to_tag<QueryOrderHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryOrderHistoryResponse& v);

} // namespace binance::w3w_prediction::rest_api
