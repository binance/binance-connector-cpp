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

struct AggregateTradeStreamResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time (ms)
    std::optional<std::int64_t> e_uppercase;
    /// Trade time (ms)
    std::optional<std::int64_t> t_uppercase;
    /// Aggregated trade ID
    std::optional<std::int64_t> a;
    /// First trade ID in the aggregation
    std::optional<std::int64_t> f;
    /// Last trade ID in the aggregation
    std::optional<std::int64_t> l;
    /// Is the buyer the market maker
    std::optional<bool> m;
    /// Price
    std::optional<std::string> p;
    /// Quantity
    std::optional<std::string> q;
    /// Symbol
    std::optional<std::string> s;

    bool operator==(const AggregateTradeStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT AggregateTradeStreamResponse tag_invoke(
    boost::json::value_to_tag<AggregateTradeStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const AggregateTradeStreamResponse& v);

} // namespace binance::alpha::websocket_streams
