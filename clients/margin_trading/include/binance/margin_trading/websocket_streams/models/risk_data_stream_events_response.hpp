//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/websocket_streams/models/margin_level_status_change.hpp>
#include <binance/margin_trading/websocket_streams/models/user_liability_change.hpp>

namespace binance::margin_trading::websocket_streams {

struct RiskDataStreamEventsResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<MarginLevelStatusChange, UserLiabilityChange, boost::json::value> value;

    bool operator==(const RiskDataStreamEventsResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT RiskDataStreamEventsResponse tag_invoke(
    boost::json::value_to_tag<RiskDataStreamEventsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const RiskDataStreamEventsResponse& v);

} // namespace binance::margin_trading::websocket_streams
