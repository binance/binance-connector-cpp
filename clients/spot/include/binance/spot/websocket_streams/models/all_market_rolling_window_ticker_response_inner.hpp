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

struct AllMarketRollingWindowTickerResponseInner {
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
    /// Open price
    std::optional<std::string> o;
    /// High price
    std::optional<std::string> h;
    /// Low price
    std::optional<std::string> l;
    /// Last price
    std::optional<std::string> c;
    /// Weighted average price
    std::optional<std::string> w;
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

    bool operator==(const AllMarketRollingWindowTickerResponseInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AllMarketRollingWindowTickerResponseInner
tag_invoke(boost::json::value_to_tag<AllMarketRollingWindowTickerResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AllMarketRollingWindowTickerResponseInner& v);

} // namespace binance::spot::websocket_streams
