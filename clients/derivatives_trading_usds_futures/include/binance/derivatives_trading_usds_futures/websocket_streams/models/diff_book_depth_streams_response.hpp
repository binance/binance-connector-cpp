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

struct DiffBookDepthStreamsResponse {
    /// Event type.
    std::optional<std::string> e;
    /// Event time.
    std::optional<std::int64_t> e_uppercase;
    /// Transaction time.
    std::optional<std::int64_t> t_uppercase;
    /// Symbol.
    std::optional<std::string> s;
    /// First update ID in the event.
    std::optional<std::int64_t> u_uppercase;
    /// Final update ID in the event.
    std::optional<std::int64_t> u;
    /// Final update ID in the previous stream event.
    std::optional<std::int64_t> pu;
    /// Bid updates.
    std::optional<std::vector<std::vector<std::string>>> b;
    /// Ask updates.
    std::optional<std::vector<std::vector<std::string>>> a;
    /// (After CM migration) Pair symbol
    std::optional<std::string> ps;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const DiffBookDepthStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT DiffBookDepthStreamsResponse tag_invoke(
    boost::json::value_to_tag<DiffBookDepthStreamsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const DiffBookDepthStreamsResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
