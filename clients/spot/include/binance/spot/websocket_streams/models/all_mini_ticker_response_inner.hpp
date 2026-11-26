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

struct AllMiniTickerResponseInner {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Close price
    std::optional<std::string> c;
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

    bool operator==(const AllMiniTickerResponseInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AllMiniTickerResponseInner tag_invoke(
    boost::json::value_to_tag<AllMiniTickerResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AllMiniTickerResponseInner& v);

} // namespace binance::spot::websocket_streams
