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

struct IndividualSymbolMiniTickerStreamResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Pair
    std::optional<std::string> ps;
    /// Close price
    std::optional<std::string> c;
    /// Open price
    std::optional<std::string> o;
    /// High price
    std::optional<std::string> h;
    /// Low price
    std::optional<std::string> l;
    /// Total traded volume
    std::optional<std::string> v;
    /// Total traded base asset volume
    std::optional<std::string> q;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const IndividualSymbolMiniTickerStreamResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT IndividualSymbolMiniTickerStreamResponse
tag_invoke(boost::json::value_to_tag<IndividualSymbolMiniTickerStreamResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const IndividualSymbolMiniTickerStreamResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
