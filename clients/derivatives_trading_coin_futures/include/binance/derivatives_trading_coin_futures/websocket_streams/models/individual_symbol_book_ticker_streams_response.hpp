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

struct IndividualSymbolBookTickerStreamsResponse {
    /// Event type
    std::optional<std::string> e;
    /// Order book update Id
    std::optional<std::int64_t> u;
    /// Symbol
    std::optional<std::string> s;
    /// Best bid price
    std::optional<std::string> b;
    /// Best bid qty
    std::optional<std::string> b_uppercase;
    /// Best ask price
    std::optional<std::string> a;
    /// Best ask qty
    std::optional<std::string> a_uppercase;
    /// Transaction time
    std::optional<std::int64_t> t_uppercase;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Pair
    std::optional<std::string> ps;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const IndividualSymbolBookTickerStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT IndividualSymbolBookTickerStreamsResponse
tag_invoke(boost::json::value_to_tag<IndividualSymbolBookTickerStreamsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const IndividualSymbolBookTickerStreamsResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
