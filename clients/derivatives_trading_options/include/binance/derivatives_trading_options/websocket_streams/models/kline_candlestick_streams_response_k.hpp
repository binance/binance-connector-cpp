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

/// k
struct KlineCandlestickStreamsResponseK {
    /// kline start time
    std::optional<std::int64_t> t;
    /// kline end time
    std::optional<std::int64_t> t_uppercase;
    /// Option trading symbol
    std::optional<std::string> s;
    /// candle period
    std::optional<std::string> i;
    /// first trade ID
    std::optional<std::int64_t> f;
    /// last trade ID
    std::optional<std::int64_t> l_uppercase;
    /// open
    std::optional<std::string> o;
    /// close
    std::optional<std::string> c;
    /// high
    std::optional<std::string> h;
    /// low
    std::optional<std::string> l;
    /// volume(in contracts)
    std::optional<std::string> v;
    /// number of trades
    std::optional<std::int64_t> n;
    /// current candle has been completed Y/N
    std::optional<bool> x;
    /// completed trade amount   (in quote asset)
    std::optional<std::string> q;
    /// taker completed trade volume (in contracts)
    std::optional<std::string> v_uppercase;
    /// taker trade amount(in quote asset)
    std::optional<std::string> q_uppercase;

    bool operator==(const KlineCandlestickStreamsResponseK& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT KlineCandlestickStreamsResponseK
tag_invoke(boost::json::value_to_tag<KlineCandlestickStreamsResponseK> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const KlineCandlestickStreamsResponseK& v);

} // namespace binance::derivatives_trading_options::websocket_streams
