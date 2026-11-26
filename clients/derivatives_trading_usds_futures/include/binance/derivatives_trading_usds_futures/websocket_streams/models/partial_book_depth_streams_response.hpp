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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

struct PartialBookDepthStreamsResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Transaction time
    std::optional<std::int64_t> t_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// First update ID in event
    std::optional<std::int64_t> u_uppercase;
    /// Final update ID in event
    std::optional<std::int64_t> u;
    /// Final update Id in last stream(ie `u` in last stream)
    std::optional<std::int64_t> pu;
    /// Bids to be updated
    std::optional<std::vector<std::vector<std::string>>> b;
    /// Asks to be updated
    std::optional<std::vector<std::vector<std::string>>> a;
    /// (After CM migration) Pair symbol
    std::optional<std::string> ps;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const PartialBookDepthStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PartialBookDepthStreamsResponse
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PartialBookDepthStreamsResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
