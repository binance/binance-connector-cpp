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

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_streams {

struct TickerResponse {
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
    /// First trade(F)-1 price (first trade before the 24hr rolling window)
    std::optional<std::string> x;
    /// Last price
    std::optional<std::string> c;
    /// Last quantity
    std::optional<std::string> q_uppercase;
    /// Best bid price
    std::optional<std::string> b;
    /// Best bid quantity
    std::optional<std::string> b_uppercase;
    /// Best ask price
    std::optional<std::string> a;
    /// Best ask quantity
    std::optional<std::string> a_uppercase;
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

    bool operator==(const TickerResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerResponse tag_invoke(boost::json::value_to_tag<TickerResponse> /*tag*/,
                                              const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerResponse& v);

} // namespace binance::spot::websocket_streams
