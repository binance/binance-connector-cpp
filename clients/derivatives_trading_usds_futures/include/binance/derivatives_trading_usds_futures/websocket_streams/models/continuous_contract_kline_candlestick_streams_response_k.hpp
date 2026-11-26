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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

/// Kline payload.
struct ContinuousContractKlineCandlestickStreamsResponseK {
    /// Kline start time
    std::optional<std::int64_t> t;
    /// Kline close time
    std::optional<std::int64_t> t_uppercase;
    /// Interval
    std::optional<std::string> i;
    /// First updateId
    std::optional<std::int64_t> f;
    /// Last updateId
    std::optional<std::int64_t> l_uppercase;
    /// Open price
    std::optional<std::string> o;
    /// Close price
    std::optional<std::string> c;
    /// High price
    std::optional<std::string> h;
    /// Low price
    std::optional<std::string> l;
    /// volume
    std::optional<std::string> v;
    /// Number of trades
    std::optional<std::int64_t> n;
    /// Is this kline closed?
    std::optional<bool> x;
    /// Quote asset volume
    std::optional<std::string> q;
    /// Taker buy volume
    std::optional<std::string> v_uppercase;
    /// Taker buy quote asset volume
    std::optional<std::string> q_uppercase;
    /// Ignore
    std::optional<std::string> b_uppercase;

    bool
    operator==(const ContinuousContractKlineCandlestickStreamsResponseK& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ContinuousContractKlineCandlestickStreamsResponseK
tag_invoke(boost::json::value_to_tag<ContinuousContractKlineCandlestickStreamsResponseK> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ContinuousContractKlineCandlestickStreamsResponseK& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
