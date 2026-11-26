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
#include <binance/stock_options/export.hpp>
#include <binance/stock_options/websocket_streams/models/order_report_v2_stream_response.hpp>

namespace binance::stock_options::websocket_streams {

struct OrderReportV2StreamParams {
    /// User data listen key obtained from the Listen Key endpoint.
    common::Required<std::string> listen_key;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_STOCK_OPTIONS_EXPORT UserStreamsApi {
public:
    explicit UserStreamsApi(std::shared_ptr<common::WebsocketStreams> client);

    /// Order Report V2 Stream
    ///
    /// `<listenKey>@orderReportV2`.
    ///
    /// Real-time push of the user's order updates. Option orders are pushed on `orderReportV2`,
    /// **not** on `orderReport`.
    ///
    /// `orderReportV2` carries both US stock and US stock option orders; tell them apart with the
    /// `ac` field. To process option orders only, subscribe to `orderReportV2` and handle events
    /// where `ac` = `us_option`.
    ///
    /// A push is sent once when an open order changes (`x` = `ORDER_UPDATE`) and once when it
    /// reaches a terminal state (`x` = `ORDER_TERMINAL`). Pushes are best-effort: a failed push is
    /// not retried, events while the `listenKey` is invalid are not replayed, and an order never
    /// pushed in an open state (e.g. rejected immediately) may not get a terminal push. After
    /// reconnecting, call Current Open Option Orders for a full snapshot first. Fill-level details
    /// are not pushed; use Option Order Detail or Option Trade History.
    ///
    /// For expiration-day auto-liquidation orders by the broker (`o` = `market`), `p`, `b`, `q`,
    /// `tc`, `u`, `ct`, `sp` and `ed` may be `null`; get contract details from Option Exchange Info
    /// by `os`.
    ///
    /// Prerequisite: obtain a `listenKey` via the Listen Key endpoint first.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/ws-streams/user-streams#order-report-v2-stream
    [[nodiscard]] common::WebsocketStream<OrderReportV2StreamResponse>
    order_report_v2_stream(const OrderReportV2StreamParams& params) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::stock_options::websocket_streams
