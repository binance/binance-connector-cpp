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

struct TradeResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Trade ID
    std::optional<std::int64_t> t;
    /// Price
    std::optional<std::string> p;
    /// Quantity
    std::optional<std::string> q;
    /// Trade time
    std::optional<std::int64_t> t_uppercase;
    /// Is the buyer the market maker?
    std::optional<bool> m;
    /// Ignore
    std::optional<bool> m_uppercase;

    bool operator==(const TradeResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TradeResponse tag_invoke(boost::json::value_to_tag<TradeResponse> /*tag*/,
                                             const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TradeResponse& v);

} // namespace binance::spot::websocket_streams
