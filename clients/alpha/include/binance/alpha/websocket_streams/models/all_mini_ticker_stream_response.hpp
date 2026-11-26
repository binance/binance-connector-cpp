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

struct AllMiniTickerStreamResponse {
    /// eventType
    std::optional<std::string> e;
    /// eventTime
    std::optional<std::int64_t> e_uppercase;
    /// symbol
    std::optional<std::string> s;
    /// closePrice
    std::optional<std::string> c;
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

    bool operator==(const AllMiniTickerStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT AllMiniTickerStreamResponse tag_invoke(
    boost::json::value_to_tag<AllMiniTickerStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const AllMiniTickerStreamResponse& v);

} // namespace binance::alpha::websocket_streams
