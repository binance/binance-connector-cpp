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
struct ContinuousContractKlineCandlestickStreamsResponseK {
    /// Kline start time
    std::optional<std::int64_t> t;
    /// transactionTime
    std::optional<std::int64_t> t_uppercase;
    /// interval
    std::optional<std::string> i;
    /// First update ID
    std::optional<std::int64_t> f;
    /// Last update ID
    std::optional<std::int64_t> l_uppercase;
    /// openPrice
    std::optional<std::string> o;
    /// closePrice
    std::optional<std::string> c;
    /// highPrice
    std::optional<std::string> h;
    /// lowPrice
    std::optional<std::string> l;
    /// volume
    std::optional<std::string> v;
    /// tradeNum
    std::optional<std::int64_t> n;
    /// Is this kline closed?
    std::optional<bool> x;
    /// quoteVolume
    std::optional<std::string> q;
    /// Taker buy volume
    std::optional<std::string> v_uppercase;
    /// lastTradeVolume
    std::optional<std::string> q_uppercase;
    /// Best bid qty
    std::optional<std::string> b_uppercase;

    bool
    operator==(const ContinuousContractKlineCandlestickStreamsResponseK& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ContinuousContractKlineCandlestickStreamsResponseK
tag_invoke(boost::json::value_to_tag<ContinuousContractKlineCandlestickStreamsResponseK> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ContinuousContractKlineCandlestickStreamsResponseK& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
