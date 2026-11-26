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
#include <binance/derivatives_trading_options/websocket_streams/models/kline_candlestick_streams_response_k.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct KlineCandlestickStreamsResponse {
    /// event type
    std::optional<std::string> e;
    /// event time
    std::optional<std::int64_t> e_uppercase;
    /// Option trading symbol
    std::optional<std::string> s;
    std::optional<KlineCandlestickStreamsResponseK> k;

    bool operator==(const KlineCandlestickStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT KlineCandlestickStreamsResponse
tag_invoke(boost::json::value_to_tag<KlineCandlestickStreamsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const KlineCandlestickStreamsResponse& v);

} // namespace binance::derivatives_trading_options::websocket_streams
