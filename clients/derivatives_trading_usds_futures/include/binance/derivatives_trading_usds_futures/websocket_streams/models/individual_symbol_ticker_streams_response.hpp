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

struct IndividualSymbolTickerStreamsResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Price change
    std::optional<std::string> p;
    /// Price change percent
    std::optional<std::string> p_uppercase;
    /// Weighted average price
    std::optional<std::string> w;
    /// Last price
    std::optional<std::string> c;
    /// Last quantity
    std::optional<std::string> q_uppercase;
    /// Open price
    std::optional<std::string> o;
    /// High price
    std::optional<std::string> h;
    /// Low price
    std::optional<std::string> l;
    /// Total traded base asset volume
    std::optional<std::string> v;
    /// Total traded quote asset volume
    std::optional<std::string> q;
    /// Statistics open time
    std::optional<std::int64_t> o_uppercase;
    /// Statistics close time
    std::optional<std::int64_t> c_uppercase;
    /// First trade ID
    std::optional<std::int64_t> f_uppercase;
    /// Last trade Id
    std::optional<std::int64_t> l_uppercase;
    /// Total number of trades
    std::optional<std::int64_t> n;
    /// (After CM migration) Pair symbol
    std::optional<std::string> ps;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const IndividualSymbolTickerStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT IndividualSymbolTickerStreamsResponse
tag_invoke(boost::json::value_to_tag<IndividualSymbolTickerStreamsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const IndividualSymbolTickerStreamsResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
