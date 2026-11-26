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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct AggregateTradeStreamsResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Aggregate trade ID
    std::optional<std::int64_t> a;
    /// Symbol
    std::optional<std::string> s;
    /// Price
    std::optional<std::string> p;
    /// Quantity
    std::optional<std::string> q;
    /// First trade ID
    std::optional<std::int64_t> f;
    /// Last trade ID
    std::optional<std::int64_t> l;
    /// Trade time
    std::optional<std::int64_t> t_uppercase;
    /// Is the buyer the market maker?
    std::optional<bool> m;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const AggregateTradeStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AggregateTradeStreamsResponse tag_invoke(
    boost::json::value_to_tag<AggregateTradeStreamsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AggregateTradeStreamsResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
