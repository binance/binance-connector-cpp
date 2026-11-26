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

#include <binance/common/decimal.hpp>
#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::websocket_streams {

struct PredictionOrderBookByMarketIdResponse {
    /// Message type, always `orderbook`.
    std::optional<std::string> msg_type;
    /// Market ID of this order book, the same `markets[].marketId` used by the REST API.
    std::optional<std::int64_t> market_id;
    /// Quote update time in milliseconds (UTC). Messages for the same market may arrive out of
    /// order, so discard anything older than the snapshot you already have.
    std::optional<std::int64_t> update_timestamp_ms;
    /// Ask levels sorted by price **ascending**, usually the top 50 or fewer; an empty array means
    /// no asks. Values may carry floating-point noise (e.g. `6865.999999999999`), so round them
    /// before display.
    std::optional<std::vector<std::vector<common::Decimal>>> asks;
    /// Bid levels sorted by price **descending**, usually the top 50 or fewer; an empty array means
    /// no bids. Values may carry floating-point noise (e.g. `6865.999999999999`), so round them
    /// before display.
    std::optional<std::vector<std::vector<common::Decimal>>> bids;

    bool operator==(const PredictionOrderBookByMarketIdResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT PredictionOrderBookByMarketIdResponse
tag_invoke(boost::json::value_to_tag<PredictionOrderBookByMarketIdResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const PredictionOrderBookByMarketIdResponse& v);

} // namespace binance::w3w_prediction::websocket_streams
