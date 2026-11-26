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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct TradeStreamsResponse {
    /// event type
    std::optional<std::string> e;
    /// event time
    std::optional<std::int64_t> e_uppercase;
    /// trade completed time
    std::optional<std::int64_t> t_uppercase;
    /// Option trading symbol
    std::optional<std::string> s;
    /// trade ID
    std::optional<std::int64_t> t;
    /// price
    std::optional<std::string> p;
    /// quantity, always positive
    std::optional<std::string> q;
    /// trade type enum, "MARKET" for Orderbook trading, "BLOCK" for Block trade
    std::optional<std::string> x_uppercase;
    /// direction
    std::optional<std::string> s_uppercase;
    /// Is the buyer the market maker?
    std::optional<bool> m;

    bool operator==(const TradeStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT TradeStreamsResponse
tag_invoke(boost::json::value_to_tag<TradeStreamsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const TradeStreamsResponse& v);

} // namespace binance::derivatives_trading_options::websocket_streams
