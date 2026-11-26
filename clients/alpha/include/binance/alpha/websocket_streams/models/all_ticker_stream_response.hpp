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

#include <binance/alpha/export.hpp>

namespace binance::alpha::websocket_streams {

struct AllTickerStreamResponse {
    /// eventType
    std::optional<std::string> e;
    /// eventTime
    std::optional<std::int64_t> e_uppercase;
    /// symbol
    std::optional<std::string> s;
    /// priceChange
    std::optional<std::string> p;
    /// priceChangePercent
    std::optional<std::string> p_uppercase;
    /// averagePrice
    std::optional<std::string> w;
    /// closePrice
    std::optional<std::string> c;
    /// lastTradeVolume
    std::optional<std::string> q_uppercase;
    /// openPrice
    std::optional<std::string> o;
    /// highPrice
    std::optional<std::string> h;
    /// lowPrice
    std::optional<std::string> l;
    /// volume
    std::optional<std::string> v;
    /// quoteVolume
    std::optional<std::string> q;
    /// startTime
    std::optional<std::int64_t> o_uppercase;
    /// endTime
    std::optional<std::int64_t> c_uppercase;
    /// firstTradeId
    std::optional<std::int64_t> f_uppercase;
    /// lastTradeId
    std::optional<std::int64_t> l_uppercase;
    /// tradeNum
    std::optional<std::int64_t> n;

    bool operator==(const AllTickerStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT AllTickerStreamResponse tag_invoke(
    boost::json::value_to_tag<AllTickerStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const AllTickerStreamResponse& v);

} // namespace binance::alpha::websocket_streams
