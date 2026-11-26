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

struct AllBookTickersStreamResponse {
    /// event type
    std::optional<std::string> e;
    /// order book updateId
    std::optional<std::int64_t> u;
    /// event time
    std::optional<std::int64_t> e_uppercase;
    /// transaction time
    std::optional<std::int64_t> t_uppercase;
    /// symbol
    std::optional<std::string> s;
    /// best bid price
    std::optional<std::string> b;
    /// best bid qty
    std::optional<std::string> b_uppercase;
    /// best ask price
    std::optional<std::string> a;
    /// best ask qty
    std::optional<std::string> a_uppercase;
    /// (After CM migration) Pair symbol
    std::optional<std::string> ps;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const AllBookTickersStreamResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AllBookTickersStreamResponse tag_invoke(
    boost::json::value_to_tag<AllBookTickersStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AllBookTickersStreamResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
