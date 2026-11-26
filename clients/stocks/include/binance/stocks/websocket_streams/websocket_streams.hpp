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
#include <binance/stocks/export.hpp>
#include <binance/stocks/websocket_streams/market_streams_api.hpp>
#include <binance/stocks/websocket_streams/models.hpp>
#include <binance/stocks/websocket_streams/user_streams_api.hpp>

namespace binance::stocks::websocket_streams {

class WebsocketStreams;

/// A connection to the Stocks WebSocket streams, returned connected by
/// `WebsocketStreams::connect()`. Cheap to copy: copies share one `common::WebsocketStreams`
/// (connection pool and executor), which reconnects, renews its connections and resubscribes
/// until `disconnect()`.
class BINANCE_STOCKS_EXPORT WebsocketStreamsConnection {
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

    // MarketStreamsApi

    /// Calendar Stream
    ///
    /// `calendar`.
    ///
    /// Single-stream broadcast of market-phase transitions. One message per transition; no periodic
    /// heartbeat payload. Server polls every 5 seconds. Also reachable via the
    /// SUBSCRIBE/UNSUBSCRIBE RPC — see Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#calendar-stream
    [[nodiscard]] common::WebsocketStream<CalendarStreamResponse>
    calendar_stream(const CalendarStreamParams& params = {}) const {
        return market_streams_api_.calendar_stream(params);
    }

    /// Kline Stream
    ///
    /// `<symbol>@kline_<interval>`.
    ///
    /// Per-symbol candlestick updates. One stream per (symbol, interval) combination. Supported
    /// intervals: 5m, 1h, 1d, 1w, 1M. Also reachable via the SUBSCRIBE/UNSUBSCRIBE RPC — see
    /// Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#kline-stream
    [[nodiscard]] common::WebsocketStream<KlineStreamResponse>
    kline_stream(const KlineStreamParams& params) const {
        return market_streams_api_.kline_stream(params);
    }

    /// Price Stream
    ///
    /// `price`.
    ///
    /// Push-all price snapshot, polled every 3 seconds. One message carries the latest price for
    /// every active US-equity symbol. Also reachable via the SUBSCRIBE/UNSUBSCRIBE RPC — see
    /// Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#price-stream
    [[nodiscard]] common::WebsocketStream<PriceStreamResponse>
    price_stream(const PriceStreamParams& params = {}) const {
        return market_streams_api_.price_stream(params);
    }

    /// Quote Stream
    ///
    /// `<symbol>@quote`.
    ///
    /// Per-symbol real-time best-bid / best-ask. Each symbol has its own stream. Per-symbol
    /// throttle: at most one push per symbol every 200 ms. Also reachable via the
    /// SUBSCRIBE/UNSUBSCRIBE RPC — see Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#quote-stream
    [[nodiscard]] common::WebsocketStream<QuoteStreamResponse>
    quote_stream(const QuoteStreamParams& params) const {
        return market_streams_api_.quote_stream(params);
    }

    /// Tradability Stream
    ///
    /// `<symbol>@tradability`.
    ///
    /// Per-symbol push whenever the tradable direction of a symbol changes. Pushed only when the
    /// value actually changes (new value ≠ old value). Also reachable via the SUBSCRIBE/UNSUBSCRIBE
    /// RPC — see Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#tradability-stream
    [[nodiscard]] common::WebsocketStream<TradabilityStreamResponse>
    tradability_stream(const TradabilityStreamParams& params) const {
        return market_streams_api_.tradability_stream(params);
    }

    /// Trading Status Stream
    ///
    /// `<symbol>@tradingStatus`.
    ///
    /// Per-symbol trading-status transitions (halts, resumes, SSR, LULD pauses, etc.). Events that
    /// do not match a known status/reason rule are not pushed. Also reachable via the
    /// SUBSCRIBE/UNSUBSCRIBE RPC — see Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#trading-status-stream
    [[nodiscard]] common::WebsocketStream<TradingStatusStreamResponse>
    trading_status_stream(const TradingStatusStreamParams& params) const {
        return market_streams_api_.trading_status_stream(params);
    }

    // UserStreamsApi

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
    order_report_stream(const OrderReportStreamParams& params) const {
        return user_streams_api_.order_report_stream(params);
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
    MarketStreamsApi market_streams_api_;
    UserStreamsApi user_streams_api_;
};

/// Stocks WebSocket streams client: holds the configuration, and `connect()` opens a new
/// connection with it, like the `connect()` of the other Binance connectors. Every call returns an
/// independent connection.
class BINANCE_STOCKS_EXPORT WebsocketStreams {
public:
    explicit WebsocketStreams(common::WebsocketStreamsConfig configuration);

    /// A client for `config.url`, production when it is not set.
    [[nodiscard]] static WebsocketStreams from_config(common::WebsocketStreamsConfig config);
    /// A client for production (Stocks WebSocket streams).
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

} // namespace binance::stocks::websocket_streams
