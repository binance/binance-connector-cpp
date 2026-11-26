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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_streams/models/outbound_account_position_b_inner.hpp>

namespace binance::spot::websocket_streams {

struct OutboundAccountPosition {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Time of last account update
    std::optional<std::int64_t> u;
    /// Balances Array
    std::optional<std::vector<OutboundAccountPositionBInner>> b_uppercase;

    bool operator==(const OutboundAccountPosition& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OutboundAccountPosition tag_invoke(
    boost::json::value_to_tag<OutboundAccountPosition> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OutboundAccountPosition& v);

} // namespace binance::spot::websocket_streams
