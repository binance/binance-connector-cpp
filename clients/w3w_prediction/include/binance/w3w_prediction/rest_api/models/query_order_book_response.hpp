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
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_book_response_asks_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_book_response_bids_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryOrderBookResponse {
    std::optional<std::string> outcome;
    std::optional<std::string> token_id;
    std::optional<std::int64_t> timestamp;
    std::optional<std::vector<QueryOrderBookResponseBidsInner>> bids;
    std::optional<std::vector<QueryOrderBookResponseAsksInner>> asks;

    bool operator==(const QueryOrderBookResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryOrderBookResponse
tag_invoke(boost::json::value_to_tag<QueryOrderBookResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryOrderBookResponse& v);

} // namespace binance::w3w_prediction::rest_api
