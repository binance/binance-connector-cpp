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

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/balance_update.hpp>
#include <binance/spot/websocket_api/models/event_stream_terminated.hpp>
#include <binance/spot/websocket_api/models/execution_report.hpp>
#include <binance/spot/websocket_api/models/external_lock_update.hpp>
#include <binance/spot/websocket_api/models/list_status.hpp>
#include <binance/spot/websocket_api/models/outbound_account_position.hpp>

namespace binance::spot::websocket_api {

struct UserDataStreamEventsResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<BalanceUpdate, EventStreamTerminated, ExecutionReport, ExternalLockUpdate,
                 ListStatus, OutboundAccountPosition, boost::json::value>
        value;

    bool operator==(const UserDataStreamEventsResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT UserDataStreamEventsResponse tag_invoke(
    boost::json::value_to_tag<UserDataStreamEventsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const UserDataStreamEventsResponse& v);

} // namespace binance::spot::websocket_api
