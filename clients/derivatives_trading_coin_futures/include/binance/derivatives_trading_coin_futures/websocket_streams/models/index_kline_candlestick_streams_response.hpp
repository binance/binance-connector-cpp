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
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/index_kline_candlestick_streams_response_k.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct IndexKlineCandlestickStreamsResponse {
    /// eventType
    std::optional<std::string> e;
    /// eventTime
    std::optional<std::int64_t> e_uppercase;
    /// Pair
    std::optional<std::string> ps;
    std::optional<IndexKlineCandlestickStreamsResponseK> k;

    bool operator==(const IndexKlineCandlestickStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT IndexKlineCandlestickStreamsResponse
tag_invoke(boost::json::value_to_tag<IndexKlineCandlestickStreamsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const IndexKlineCandlestickStreamsResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
