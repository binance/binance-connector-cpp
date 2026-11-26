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

struct Hour24TickerResponse {
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
    /// Trading volume(in contracts)
    std::optional<std::string> v;
    /// trade amount(in quote asset)
    std::optional<std::string> q;
    /// Statistics open time
    std::optional<std::int64_t> o_uppercase;
    /// Statistics close time
    std::optional<std::int64_t> c_uppercase;
    /// First trade ID
    std::optional<std::int64_t> f_uppercase;
    /// Last trade Id
    std::optional<std::int64_t> l_uppercase;
    /// Total number of trade
    std::optional<std::int64_t> n;

    bool operator==(const Hour24TickerResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT Hour24TickerResponse
tag_invoke(boost::json::value_to_tag<Hour24TickerResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const Hour24TickerResponse& v);

} // namespace binance::derivatives_trading_options::websocket_streams
