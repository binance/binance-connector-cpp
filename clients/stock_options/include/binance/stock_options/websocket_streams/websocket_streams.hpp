//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <chrono>
#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <boost/asio/append.hpp>
#include <boost/asio/async_result.hpp>

#include <binance/common/config.hpp>
#include <binance/common/websocket_streams.hpp>
#include <binance/stock_options/export.hpp>
#include <binance/stock_options/websocket_streams/models.hpp>
#include <binance/stock_options/websocket_streams/user_streams_api.hpp>

namespace binance::stock_options::websocket_streams {

class WebsocketStreams;

/// A connection to the StockOptions WebSocket streams, returned connected by
/// `WebsocketStreams::connect()`. Cheap to copy: copies share one `common::WebsocketStreams`
/// (connection pool and executor), which reconnects, renews its connections and resubscribes
/// until `disconnect()`.
class BINANCE_STOCK_OPTIONS_EXPORT WebsocketStreamsConnection {
public:
    [[nodiscard]] const common::WebsocketStreamsConfig& configuration() const noexcept {
        return client_->configuration();
    }

    void disconnect() { client_->disconnect(); }
    template <class CompletionToken> auto async_disconnect(CompletionToken&& token) {
        return client_->async_disconnect(std::forward<CompletionToken>(token));
    }
    [[nodiscard]] bool is_connected() const { return client_->is_connected(); }
    /// Sends a ping frame on every open connection.
    void ping_server() { client_->ping_server(); }
    /// Registers a lifecycle callback (`common::WebsocketEvent`). Destroying the returned
    /// subscription removes it.
    template <class F> common::Subscription on_event(F&& callback) {
        return client_->on_event(std::forward<F>(callback));
    }

    /// Subscribes to a stream by its name, for streams the SDK does not wrap yet, and returns a
    /// handle for its callbacks (payloads as `boost::json::value`). Data arriving before the first
    /// callback is added is kept for it (up to 1000 messages).
    [[nodiscard]] common::WebsocketStreamHandle stream(std::string name,
                                                       std::optional<common::StreamId> id = {},
                                                       std::optional<std::string> url_path = {}) {
        return client_->create_stream(std::move(name), std::move(id), std::move(url_path));
    }

    /// Subscribes to raw stream names. Messages are delivered to handles from `stream()`.
    void subscribe(const std::vector<std::string>& streams, std::optional<common::StreamId> id = {},
                   const std::optional<std::string>& url_path = {}) {
        client_->subscribe(streams, std::move(id), url_path);
    }
    void unsubscribe(const std::vector<std::string>& streams,
                     std::optional<common::StreamId> id = {},
                     const std::optional<std::string>& url_path = {}) {
        client_->unsubscribe(streams, std::move(id), url_path);
    }
    [[nodiscard]] bool is_subscribed(const std::string& stream) const {
        return client_->is_subscribed(stream);
    }
    /// Completes once the server has acknowledged the subscription of `stream`; see
    /// `common::WebsocketStreams::async_wait_subscribed`.
    template <class CompletionToken>
    auto async_wait_subscribed(std::string stream, std::optional<std::string> url_path,
                               CompletionToken&& token) {
        return client_->async_wait_subscribed(std::move(stream), std::move(url_path),
                                              std::forward<CompletionToken>(token));
    }
    void wait_subscribed(std::string stream, std::optional<std::string> url_path = {},
                         std::optional<std::chrono::milliseconds> timeout = {}) {
        client_->wait_subscribed(std::move(stream), std::move(url_path), timeout);
    }

    // UserStreamsApi

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
    order_report_v2_stream(const OrderReportV2StreamParams& params) const {
        return user_streams_api_.order_report_v2_stream(params);
    }

private:
    friend class WebsocketStreams;

    /// Not connected yet: `WebsocketStreams::connect()` creates and connects one. Throws
    /// `common::ConfigError` if the configuration is invalid.
    explicit WebsocketStreamsConnection(common::WebsocketStreamsConfig configuration);

    [[nodiscard]] const std::shared_ptr<common::WebsocketStreams>& client() const noexcept {
        return client_;
    }

    std::shared_ptr<common::WebsocketStreams> client_;
    UserStreamsApi user_streams_api_;
};

/// StockOptions WebSocket streams client: holds the configuration, and `connect()` opens a new
/// connection with it, like the `connect()` of the other Binance connectors. Every call returns an
/// independent connection.
class BINANCE_STOCK_OPTIONS_EXPORT WebsocketStreams {
public:
    explicit WebsocketStreams(common::WebsocketStreamsConfig configuration);

    /// A client for `config.url`, production when it is not set.
    [[nodiscard]] static WebsocketStreams from_config(common::WebsocketStreamsConfig config);
    /// A client for production (Stock Options WebSocket streams).
    [[nodiscard]] static WebsocketStreams production(common::WebsocketStreamsConfig config);

    [[nodiscard]] const common::WebsocketStreamsConfig& configuration() const noexcept {
        return configuration_;
    }

    /// Opens a connection (a pool of them with `mode`, overriding the configuration), subscribed to
    /// `streams` (raw stream names), and returns it once connected. Throws `common::ConfigError` if
    /// the configuration is invalid, and the error of the first connection that fails to open.
    [[nodiscard]] WebsocketStreamsConnection
    connect(std::vector<std::string> streams = {},
            std::optional<common::WebsocketMode> mode = {}) const {
        WebsocketStreamsConnection connection(configuration_for(mode));
        connection.client()->connect(std::move(streams));
        return connection;
    }

    /// Asynchronous `connect()`, completing with `void(std::exception_ptr,
    /// WebsocketStreamsConnection)`.
    template <class CompletionToken> auto async_connect(CompletionToken&& token) const {
        return async_connect({}, std::nullopt, std::forward<CompletionToken>(token));
    }
    template <class CompletionToken>
    auto async_connect(std::vector<std::string> streams, CompletionToken&& token) const {
        return async_connect(std::move(streams), std::nullopt,
                             std::forward<CompletionToken>(token));
    }
    template <class CompletionToken>
    auto async_connect(std::vector<std::string> streams, std::optional<common::WebsocketMode> mode,
                       CompletionToken&& token) const {
        return boost::asio::async_initiate<CompletionToken,
                                           void(std::exception_ptr, WebsocketStreamsConnection)>(
            [](auto handler, WebsocketStreamsConnection connection,
               std::vector<std::string> initial) {
                const auto client = connection.client();
                client->async_connect(
                    std::move(initial),
                    boost::asio::append(std::move(handler), std::move(connection)));
            },
            token, WebsocketStreamsConnection(configuration_for(mode)), std::move(streams));
    }

private:
    [[nodiscard]] common::WebsocketStreamsConfig
    configuration_for(std::optional<common::WebsocketMode> mode) const {
        auto configuration = configuration_;
        if (mode) {
            configuration.mode = *mode;
        }
        return configuration;
    }

    common::WebsocketStreamsConfig configuration_;
};

} // namespace binance::stock_options::websocket_streams
