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
#include <binance/w3w_prediction/rest_api/models/list_prediction_markets_response_market_topics_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct ListPredictionMarketsResponse {
    std::optional<std::vector<ListPredictionMarketsResponseMarketTopicsInner>> market_topics;
    std::optional<std::int64_t> total;
    std::optional<std::int64_t> offset;
    std::optional<std::int64_t> limit;
    std::optional<bool> has_more;

    bool operator==(const ListPredictionMarketsResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT ListPredictionMarketsResponse tag_invoke(
    boost::json::value_to_tag<ListPredictionMarketsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const ListPredictionMarketsResponse& v);

} // namespace binance::w3w_prediction::rest_api
