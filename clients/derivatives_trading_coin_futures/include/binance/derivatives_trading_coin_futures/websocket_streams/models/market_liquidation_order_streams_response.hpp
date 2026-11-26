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
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/all_market_liquidation_order_streams_response_o.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct MarketLiquidationOrderStreamsResponse {
    /// Event Type
    std::optional<std::string> e;
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    std::optional<AllMarketLiquidationOrderStreamsResponseO> o;

    bool operator==(const MarketLiquidationOrderStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT MarketLiquidationOrderStreamsResponse
tag_invoke(boost::json::value_to_tag<MarketLiquidationOrderStreamsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MarketLiquidationOrderStreamsResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
