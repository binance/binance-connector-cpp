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
#include <binance/spot/export.hpp>
#include <binance/spot/websocket_streams/api.hpp>
#include <binance/spot/websocket_streams/models.hpp>

namespace binance::spot::websocket_streams {

class WebsocketStreams;

/// A connection to the Spot WebSocket streams, returned connected by
/// `WebsocketStreams::connect()`. Cheap to copy: copies share one `common::WebsocketStreams`
/// (connection pool and executor), which reconnects, renews its connections and resubscribes
/// until `disconnect()`.
class BINANCE_SPOT_EXPORT WebsocketStreamsConnection {
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

    /// User data stream of `listen_key`. No method of this SDK creates a listen key for this
    /// product: subscribe with `user_data_stream_subscribe()` of the WebSocket API instead.
    [[nodiscard]] common::WebsocketStream<UserDataStreamEventsResponse>
    user_data(std::string listen_key, std::optional<common::StreamId> id = {}) const {
        return common::WebsocketStream<UserDataStreamEventsResponse>(
            client_->create_stream(std::move(listen_key), std::move(id), std::nullopt));
    }

    // Api

    /// Aggregate Trade Streams
    ///
    /// `<symbol>@aggTrade`.
    ///
    /// The Aggregate Trade Streams push trade information that is aggregated
    /// for a single taker order.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#agg-trade
    [[nodiscard]] common::WebsocketStream<AggTradeResponse>
    agg_trade(const AggTradeParams& params) const {
        return api_.agg_trade(params);
    }

    /// All Market Rolling Window Statistics Streams
    ///
    /// `!ticker_<windowSize>@arr`.
    ///
    /// Rolling window ticker statistics for all market symbols, computed over
    /// multiple windows.
    ///
    /// Note that only tickers that have changed will be present in the array.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#all-market-rolling-window-ticker
    [[nodiscard]] common::WebsocketStream<std::vector<AllMarketRollingWindowTickerResponseInner>>
    all_market_rolling_window_ticker(const AllMarketRollingWindowTickerParams& params) const {
        return api_.all_market_rolling_window_ticker(params);
    }

    /// All Market Mini Tickers Stream
    ///
    /// `!miniTicker@arr`.
    ///
    /// 24hr rolling window mini-ticker statistics for all symbols that changed
    /// in an array. These are NOT the statistics of the UTC day, but a 24hr
    /// rolling window for the previous 24hrs. Note that only tickers that have
    /// changed will be present in the array.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#all-mini-ticker
    [[nodiscard]] common::WebsocketStream<std::vector<AllMiniTickerResponseInner>>
    all_mini_ticker(const AllMiniTickerParams& params = {}) const {
        return api_.all_mini_ticker(params);
    }

    /// Average Price
    ///
    /// `<symbol>@avgPrice`.
    ///
    /// Average price streams push changes in the average price over a fixed time interval.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#avg-price
    [[nodiscard]] common::WebsocketStream<AvgPriceResponse>
    avg_price(const AvgPriceParams& params) const {
        return api_.avg_price(params);
    }

    /// Block Trade Streams
    ///
    /// `<symbol>@blockTrade`.
    ///
    /// Block Trade Streams push block trade information in real-time.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#block-trade
    [[nodiscard]] common::WebsocketStream<BlockTradeResponse>
    block_trade(const BlockTradeParams& params) const {
        return api_.block_trade(params);
    }

    /// Individual Symbol Book Ticker Streams
    ///
    /// `<symbol>@bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in
    /// real-time for a specified symbol.
    ///
    /// Multiple `<symbol>@bookTicker` streams can be subscribed to over one
    /// connection.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#book-ticker
    [[nodiscard]] common::WebsocketStream<BookTickerResponse>
    book_ticker(const BookTickerParams& params) const {
        return api_.book_ticker(params);
    }

    /// Diff. Depth Stream
    ///
    /// `<symbol>@depth@<updateSpeed>`.
    ///
    /// Order book price and quantity depth updates used to locally manage an order book.
    ///
    /// Update Speed: 1000ms or 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#diff-book-depth
    [[nodiscard]] common::WebsocketStream<DiffBookDepthResponse>
    diff_book_depth(const DiffBookDepthParams& params) const {
        return api_.diff_book_depth(params);
    }

    /// Kline/Candlestick Streams for UTC
    ///
    /// `<symbol>@kline_<interval>`.
    ///
    /// The Kline/Candlestick Stream push updates to the current
    /// klines/candlestick every second in `UTC+0` timezone
    ///
    /// Update Speed: 1000ms for `1s`, 2000ms for the other intervals
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#kline
    [[nodiscard]] common::WebsocketStream<KlineResponse> kline(const KlineParams& params) const {
        return api_.kline(params);
    }

    /// Kline/Candlestick Streams with timezone offset
    ///
    /// `<symbol>@kline_<interval>@+08:00`.
    ///
    /// The Kline/Candlestick Stream push updates to the current
    /// klines/candlestick every second in `UTC+8` timezone
    ///
    /// **Kline/Candlestick chart intervals:**
    ///
    /// Supported intervals: See Kline/Candlestick chart intervals
    ///
    /// **UTC+8 timezone offset:**
    ///
    /// - Kline intervals open and close in the `UTC+8` timezone. For example the `1d` klines will
    /// open at the beginning of the `UTC+8` day, and close at the end of the `UTC+8` day.
    /// - Note that `E` (event time), `t` (start time) and `T` (close time) in the payload are Unix
    /// timestamps, which are always interpreted in UTC.
    ///
    /// Update Speed: 1000ms for `1s`, 2000ms for the other intervals
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#kline-offset
    [[nodiscard]] common::WebsocketStream<KlineOffsetResponse>
    kline_offset(const KlineOffsetParams& params) const {
        return api_.kline_offset(params);
    }

    /// Individual Symbol Mini Ticker Stream
    ///
    /// `<symbol>@miniTicker`.
    ///
    /// 24hr rolling window mini-ticker statistics. These are NOT the statistics
    /// of the UTC day, but a 24hr rolling window for the previous 24hrs.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#mini-ticker
    [[nodiscard]] common::WebsocketStream<MiniTickerResponse>
    mini_ticker(const MiniTickerParams& params) const {
        return api_.mini_ticker(params);
    }

    /// Partial Book Depth Streams
    ///
    /// `<symbol>@depth<levels>@<updateSpeed>`.
    ///
    /// Top **\<levels\>** bids and asks, pushed every second. Valid **\<levels\>** are 5, 10,
    /// or 20.
    ///
    /// Update Speed: 1000ms or 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#partial-book-depth
    [[nodiscard]] common::WebsocketStream<PartialBookDepthResponse>
    partial_book_depth(const PartialBookDepthParams& params) const {
        return api_.partial_book_depth(params);
    }

    /// Reference Price Streams
    ///
    /// `<symbol>@referencePrice`.
    ///
    /// Reference price stream for a symbol.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#reference-price
    [[nodiscard]] common::WebsocketStream<ReferencePriceResponse>
    reference_price(const ReferencePriceParams& params) const {
        return api_.reference_price(params);
    }

    /// Individual Symbol Rolling Window Statistics Streams
    ///
    /// `<symbol>@ticker_<windowSize>`.
    ///
    /// Rolling window ticker statistics for a single symbol, computed over
    /// multiple windows.
    ///
    /// **Note:** This stream is different from the `<symbol>@ticker` stream. The open time `"O"`
    /// always starts on a minute, while the closing time `"C"` is the current time of the update.
    /// As such, the effective window might be up to 59999ms wider than `<windowSize>`.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#rolling-window-ticker
    [[nodiscard]] common::WebsocketStream<RollingWindowTickerResponse>
    rolling_window_ticker(const RollingWindowTickerParams& params) const {
        return api_.rolling_window_ticker(params);
    }

    /// Individual Symbol Ticker Streams
    ///
    /// `<symbol>@ticker`.
    ///
    /// 24hr rolling window ticker statistics for a single symbol. These are NOT
    /// the statistics of the UTC day, but a 24hr rolling window for the
    /// previous 24hrs.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#ticker
    [[nodiscard]] common::WebsocketStream<TickerResponse> ticker(const TickerParams& params) const {
        return api_.ticker(params);
    }

    /// Trade Streams
    ///
    /// `<symbol>@trade`.
    ///
    /// The Trade Streams push raw trade information; each trade has a unique
    /// buyer and seller.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#trade
    [[nodiscard]] common::WebsocketStream<TradeResponse> trade(const TradeParams& params) const {
        return api_.trade(params);
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
    Api api_;
};

/// Spot WebSocket streams client: holds the configuration, and `connect()` opens a new
/// connection with it, like the `connect()` of the other Binance connectors. Every call returns an
/// independent connection.
class BINANCE_SPOT_EXPORT WebsocketStreams {
public:
    explicit WebsocketStreams(common::WebsocketStreamsConfig configuration);

    /// A client for `config.url`, production when it is not set.
    [[nodiscard]] static WebsocketStreams from_config(common::WebsocketStreamsConfig config);
    /// A client for production (Spot WebSocket streams).
    [[nodiscard]] static WebsocketStreams production(common::WebsocketStreamsConfig config);
    /// A client for the testnet.
    [[nodiscard]] static WebsocketStreams testnet(common::WebsocketStreamsConfig config);
    /// A client for the demo environment.
    [[nodiscard]] static WebsocketStreams demo(common::WebsocketStreamsConfig config);

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

} // namespace binance::spot::websocket_streams
