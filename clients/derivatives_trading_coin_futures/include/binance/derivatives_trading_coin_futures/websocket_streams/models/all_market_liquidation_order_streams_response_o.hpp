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

/// Order Type
struct AllMarketLiquidationOrderStreamsResponseO {
    /// Symbol
    std::optional<std::string> s;
    /// Pair
    std::optional<std::string> ps;
    /// Side
    std::optional<std::string> s_uppercase;
    /// Order Type
    std::optional<std::string> o;
    /// Time in Force
    std::optional<std::string> f;
    /// Original Quantity
    std::optional<std::string> q;
    /// Price
    std::optional<std::string> p;
    /// Average Price
    std::optional<std::string> ap;
    /// Order Status
    std::optional<std::string> x_uppercase;
    /// Order Last Filled Quantity
    std::optional<std::string> l;
    /// Order Filled Accumulated Quantity
    std::optional<std::string> z;
    /// Order Trade Time
    std::optional<std::int64_t> t_uppercase;

    bool operator==(const AllMarketLiquidationOrderStreamsResponseO& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AllMarketLiquidationOrderStreamsResponseO
tag_invoke(boost::json::value_to_tag<AllMarketLiquidationOrderStreamsResponseO> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AllMarketLiquidationOrderStreamsResponseO& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
