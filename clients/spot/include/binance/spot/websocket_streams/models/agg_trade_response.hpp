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

struct AggTradeResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Aggregate trade ID
    std::optional<std::int64_t> a;
    /// Price
    std::optional<std::string> p;
    /// Quantity
    std::optional<std::string> q;
    /// First trade ID
    std::optional<std::int64_t> f;
    /// Last trade ID
    std::optional<std::int64_t> l;
    /// Trade time
    std::optional<std::int64_t> t_uppercase;
    /// Is the buyer the market maker?
    std::optional<bool> m;
    /// Ignore
    std::optional<bool> m_uppercase;

    bool operator==(const AggTradeResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AggTradeResponse tag_invoke(boost::json::value_to_tag<AggTradeResponse> /*tag*/,
                                                const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AggTradeResponse& v);

} // namespace binance::spot::websocket_streams
