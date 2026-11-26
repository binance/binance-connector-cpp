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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/alpha/export.hpp>

namespace binance::alpha::websocket_streams {

struct FullDepthStreamResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time (ms)
    std::optional<std::int64_t> e_uppercase;
    /// Matching time (ms)
    std::optional<std::int64_t> t_uppercase;
    /// First updateId in this event
    std::optional<std::int64_t> u_uppercase;
    /// Last updateId in this event
    std::optional<std::int64_t> u;
    /// Previous updateId from the last push
    std::optional<std::int64_t> pu;
    /// Symbol
    std::optional<std::string> s;
    /// bids to be updated
    std::optional<std::vector<std::vector<std::string>>> b;
    /// asks to be updated
    std::optional<std::vector<std::vector<std::string>>> a;

    bool operator==(const FullDepthStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT FullDepthStreamResponse tag_invoke(
    boost::json::value_to_tag<FullDepthStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const FullDepthStreamResponse& v);

} // namespace binance::alpha::websocket_streams
