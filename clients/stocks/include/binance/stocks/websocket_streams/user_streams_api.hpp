//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/websocket_streams.hpp>
#include <binance/stocks/export.hpp>
#include <binance/stocks/websocket_streams/models/order_report_stream_response.hpp>

namespace binance::stocks::websocket_streams {

struct OrderReportStreamParams {
    /// User data listen key obtained from the Listen Key endpoint.
    common::Required<std::string> listen_key;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_STOCKS_EXPORT UserStreamsApi {
public:
    explicit UserStreamsApi(std::shared_ptr<common::WebsocketStreams> client);

    /// Order Report Stream
    ///
    /// `<listenKey>@orderReport`.
    ///
    /// Real-time push of the authenticated user's order state transitions — both open-state updates
    /// (`ORDER_UPDATE`) and terminal-state notifications (`ORDER_TERMINAL`). Prerequisite: obtain a
    /// `listenKey` via the Listen Key endpoint first.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/user-streams#order-report-stream
    [[nodiscard]] common::WebsocketStream<OrderReportStreamResponse>
    order_report_stream(const OrderReportStreamParams& params) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::stocks::websocket_streams
