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
#include <binance/margin_trading/websocket_streams/models/balance_update.hpp>
#include <binance/margin_trading/websocket_streams/models/execution_report.hpp>
#include <binance/margin_trading/websocket_streams/models/list_status.hpp>
#include <binance/margin_trading/websocket_streams/models/listen_key_expired.hpp>
#include <binance/margin_trading/websocket_streams/models/margin_level_status_change.hpp>
#include <binance/margin_trading/websocket_streams/models/outbound_account_position.hpp>
#include <binance/margin_trading/websocket_streams/models/user_liability_change.hpp>

namespace binance::margin_trading::websocket_streams {

struct TradeDataStreamEventsResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<MarginLevelStatusChange, UserLiabilityChange, BalanceUpdate, ExecutionReport,
                 ListStatus, ListenKeyExpired, OutboundAccountPosition, boost::json::value>
        value;

    bool operator==(const TradeDataStreamEventsResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT TradeDataStreamEventsResponse tag_invoke(
    boost::json::value_to_tag<TradeDataStreamEventsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const TradeDataStreamEventsResponse& v);

} // namespace binance::margin_trading::websocket_streams
