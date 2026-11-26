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

/// Kline payload
struct MarkPriceKlineCandlestickStreamsResponseK {
    /// Kline start time
    std::optional<std::int64_t> t;
    /// Kline close time
    std::optional<std::int64_t> t_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Interval
    std::optional<std::string> i;
    /// ignore
    std::optional<std::int64_t> f;
    /// ignore
    std::optional<std::int64_t> l_uppercase;
    /// Open price
    std::optional<std::string> o;
    /// Close price
    std::optional<std::string> c;
    /// High price
    std::optional<std::string> h;
    /// Low price
    std::optional<std::string> l;
    /// ignore
    std::optional<std::string> v;
    /// Number of basic data
    std::optional<std::int64_t> n;
    /// Is this kline closed?
    std::optional<bool> x;
    /// ignore
    std::optional<std::string> q;
    /// ignore
    std::optional<std::string> v_uppercase;
    /// ignore
    std::optional<std::string> q_uppercase;
    /// ignore
    std::optional<std::string> b_uppercase;

    bool operator==(const MarkPriceKlineCandlestickStreamsResponseK& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT MarkPriceKlineCandlestickStreamsResponseK
tag_invoke(boost::json::value_to_tag<MarkPriceKlineCandlestickStreamsResponseK> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MarkPriceKlineCandlestickStreamsResponseK& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
