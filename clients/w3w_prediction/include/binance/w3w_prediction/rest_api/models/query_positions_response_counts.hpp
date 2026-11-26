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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryPositionsResponseCounts {
    std::optional<std::int64_t> ongoing_count;
    std::optional<std::int64_t> ended_count;
    std::optional<std::int64_t> pending_claim_count;

    bool operator==(const QueryPositionsResponseCounts& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryPositionsResponseCounts tag_invoke(
    boost::json::value_to_tag<QueryPositionsResponseCounts> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryPositionsResponseCounts& v);

} // namespace binance::w3w_prediction::rest_api
