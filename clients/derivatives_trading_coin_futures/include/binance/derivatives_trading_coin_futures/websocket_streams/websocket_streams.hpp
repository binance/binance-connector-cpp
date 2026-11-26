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
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/api.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

class WebsocketStreams;

/// A connection to the DerivativesTradingCoinFutures WebSocket streams, returned connected by
/// `WebsocketStreams::connect()`. Cheap to copy: copies share one `common::WebsocketStreams`
/// (connection pool and executor), which reconnects, renews its connections and resubscribes
/// until `disconnect()`.
class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT WebsocketStreamsConnection {
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

    /// User data stream of `listen_key`, as returned by `start_user_data_stream()` of the REST API.
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
    /// The Aggregate Trade Streams push market trade information that is aggregated for fills with
    /// same price and taking side every 100 milliseconds.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#aggregate-trade-streams
    [[nodiscard]] common::WebsocketStream<AggregateTradeStreamsResponse>
    aggregate_trade_streams(const AggregateTradeStreamsParams& params) const {
        return api_.aggregate_trade_streams(params);
    }

    /// All Book Tickers Stream
    ///
    /// `!bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in real-time for all symbols.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#all-book-tickers-stream
    [[nodiscard]] common::WebsocketStream<AllBookTickersStreamResponse>
    all_book_tickers_stream(const AllBookTickersStreamParams& params = {}) const {
        return api_.all_book_tickers_stream(params);
    }

    /// All Market Liquidation Order Streams
    ///
    /// `!forceOrder@arr`.
    ///
    /// The All Liquidation Order Snapshot Streams push force liquidation order information for all
    /// symbols in the market. For each symbol，only the latest one liquidation order within 1000ms
    /// will be pushed as the snapshot. If no liquidation happens in the interval of 1000ms, no
    /// stream will be pushed.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#all-market-liquidation-order-streams
    [[nodiscard]] common::WebsocketStream<AllMarketLiquidationOrderStreamsResponse>
    all_market_liquidation_order_streams(
        const AllMarketLiquidationOrderStreamsParams& params = {}) const {
        return api_.all_market_liquidation_order_streams(params);
    }

    /// All Market Mini Tickers Stream
    ///
    /// `!miniTicker@arr`.
    ///
    /// 24hr rolling window mini-ticker statistics for all symbols. These are NOT the statistics of
    /// the UTC day, but a 24hr rolling window from requestTime to 24hrs before. Note that only
    /// tickers that have changed will be present in the array.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#all-market-mini-tickers-stream
    [[nodiscard]] common::WebsocketStream<std::vector<AllMarketMiniTickersStreamResponseInner>>
    all_market_mini_tickers_stream(const AllMarketMiniTickersStreamParams& params = {}) const {
        return api_.all_market_mini_tickers_stream(params);
    }

    /// All Market Tickers Streams
    ///
    /// `!ticker@arr`.
    ///
    /// 24hr rolling window ticker statistics for all symbols. These are NOT the statistics of the
    /// UTC day, but a 24hr rolling window from requestTime to 24hrs before. Note that only tickers
    /// that have changed will be present in the array.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#all-market-tickers-streams
    [[nodiscard]] common::WebsocketStream<std::vector<AllMarketTickersStreamsResponseInner>>
    all_market_tickers_streams(const AllMarketTickersStreamsParams& params = {}) const {
        return api_.all_market_tickers_streams(params);
    }

    /// Continuous Contract Kline/Candlestick Streams
    ///
    /// `<pair>_<contractType>@continuousKline_<interval>`.
    ///
    /// Kline update every second
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to either UM or CM
    /// symbols on this stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#continuous-contract-kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<ContinuousContractKlineCandlestickStreamsResponse>
    continuous_contract_kline_candlestick_streams(
        const ContinuousContractKlineCandlestickStreamsParams& params) const {
        return api_.continuous_contract_kline_candlestick_streams(params);
    }

    /// Contract Info Stream
    ///
    /// `!contractInfo`.
    ///
    /// ContractInfo stream pushes when contract info updates(listing/settlement/contract bracket
    /// update). bks field only shows up when bracket gets updated.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#contract-info-stream
    [[nodiscard]] common::WebsocketStream<ContractInfoStreamResponse>
    contract_info_stream(const ContractInfoStreamParams& params = {}) const {
        return api_.contract_info_stream(params);
    }

    /// Diff. Book Depth Streams
    ///
    /// `<symbol>@depth@<updateSpeed>`.
    ///
    /// Bids and asks, pushed every 250 milliseconds, 500 milliseconds, or 100 milliseconds
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 250ms or 500ms or 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#diff-book-depth-streams
    [[nodiscard]] common::WebsocketStream<DiffBookDepthStreamsResponse>
    diff_book_depth_streams(const DiffBookDepthStreamsParams& params) const {
        return api_.diff_book_depth_streams(params);
    }

    /// Index Kline/Candlestick Streams
    ///
    /// `<pair>@indexPriceKline_<interval>`.
    ///
    /// Index Kline/Candlestick Streams
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to CM symbols on this
    /// stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#index-kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<IndexKlineCandlestickStreamsResponse>
    index_kline_candlestick_streams(const IndexKlineCandlestickStreamsParams& params) const {
        return api_.index_kline_candlestick_streams(params);
    }

    /// Index Price Stream
    ///
    /// `<pair>@indexPrice@<updateSpeed>`.
    ///
    /// Index Price Stream
    ///
    /// Update Speed: 3000ms OR 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#index-price-stream
    [[nodiscard]] common::WebsocketStream<IndexPriceStreamResponse>
    index_price_stream(const IndexPriceStreamParams& params) const {
        return api_.index_price_stream(params);
    }

    /// Individual Symbol Book Ticker Streams
    ///
    /// `<symbol>@bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in real-time for a specified
    /// symbol.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#individual-symbol-book-ticker-streams
    [[nodiscard]] common::WebsocketStream<IndividualSymbolBookTickerStreamsResponse>
    individual_symbol_book_ticker_streams(
        const IndividualSymbolBookTickerStreamsParams& params) const {
        return api_.individual_symbol_book_ticker_streams(params);
    }

    /// Individual Symbol Mini Ticker Stream
    ///
    /// `<symbol>@miniTicker`.
    ///
    /// 24hr rolling window mini-ticker statistics for a single symbol. These are NOT the statistics
    /// of the UTC day, but a 24hr rolling window from requestTime to 24hrs before.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 500ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#individual-symbol-mini-ticker-stream
    [[nodiscard]] common::WebsocketStream<IndividualSymbolMiniTickerStreamResponse>
    individual_symbol_mini_ticker_stream(
        const IndividualSymbolMiniTickerStreamParams& params) const {
        return api_.individual_symbol_mini_ticker_stream(params);
    }

    /// Individual Symbol Ticker Streams
    ///
    /// `<symbol>@ticker`.
    ///
    /// 24hr rolling window ticker statistics for a single symbol. These are NOT the statistics of
    /// the UTC day, but a 24hr rolling window from requestTime to 24hrs before.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 500ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#individual-symbol-ticker-streams
    [[nodiscard]] common::WebsocketStream<IndividualSymbolTickerStreamsResponse>
    individual_symbol_ticker_streams(const IndividualSymbolTickerStreamsParams& params) const {
        return api_.individual_symbol_ticker_streams(params);
    }

    /// Kline/Candlestick Streams
    ///
    /// `<symbol>@kline_<interval>`.
    ///
    /// The Kline/Candlestick Stream push updates to the current klines/candlestick every 250
    /// milliseconds (if existing).
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to either UM or CM
    /// symbols on this stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<KlineCandlestickStreamsResponse>
    kline_candlestick_streams(const KlineCandlestickStreamsParams& params) const {
        return api_.kline_candlestick_streams(params);
    }

    /// Mark Price Kline/Candlestick Streams
    ///
    /// `<symbol>@markPriceKline_<interval>`.
    ///
    /// Mark Price Kline/Candlestick Streams
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to CM symbols on this
    /// stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#mark-price-kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<MarkPriceKlineCandlestickStreamsResponse>
    mark_price_kline_candlestick_streams(
        const MarkPriceKlineCandlestickStreamsParams& params) const {
        return api_.mark_price_kline_candlestick_streams(params);
    }

    /// Mark Price of All Symbols of a Pair
    ///
    /// `<pair>@markPrice@<updateSpeed>`.
    ///
    /// Mark Price of All Symbols of a Pair
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM); both `fstream` and `dstream` may subscribe to either UM or CM symbols on this stream.
    ///
    /// Update Speed: 3000ms OR 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#mark-price-of-all-symbols-of-apair
    [[nodiscard]] common::WebsocketStream<std::vector<MarkPriceOfAllSymbolsOfAPairResponseInner>>
    mark_price_of_all_symbols_of_a_pair(const MarkPriceOfAllSymbolsOfAPairParams& params) const {
        return api_.mark_price_of_all_symbols_of_a_pair(params);
    }

    /// Mark Price Stream
    ///
    /// `<symbol>@markPrice@<updateSpeed>`.
    ///
    /// Mark price update stream
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM); both `fstream` and `dstream` may subscribe to either UM or CM symbols on this stream.
    ///
    /// Update Speed: 3000ms OR 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#mark-price-stream
    [[nodiscard]] common::WebsocketStream<MarkPriceStreamResponse>
    mark_price_stream(const MarkPriceStreamParams& params) const {
        return api_.mark_price_stream(params);
    }

    /// Market Liquidation Order Streams
    ///
    /// `<symbol>@forceOrder`.
    ///
    /// The Liquidation Order Snapshot Streams push force liquidation order information for specific
    /// symbol. For each symbol，only the latest one liquidation order within 1000ms will be pushed
    /// as the snapshot. If no liquidation happens in the interval of 1000ms, no stream will be
    /// pushed.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#market-liquidation-order-streams
    [[nodiscard]] common::WebsocketStream<MarketLiquidationOrderStreamsResponse>
    market_liquidation_order_streams(const MarketLiquidationOrderStreamsParams& params) const {
        return api_.market_liquidation_order_streams(params);
    }

    /// Partial Book Depth Streams
    ///
    /// `<symbol>@depth<levels>@<updateSpeed>`.
    ///
    /// Top levels bids and asks.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 250ms, 500ms or 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#partial-book-depth-streams
    [[nodiscard]] common::WebsocketStream<PartialBookDepthStreamsResponse>
    partial_book_depth_streams(const PartialBookDepthStreamsParams& params) const {
        return api_.partial_book_depth_streams(params);
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

/// DerivativesTradingCoinFutures WebSocket streams client: holds the configuration, and `connect()`
/// opens a new connection with it, like the `connect()` of the other Binance connectors. Every call
/// returns an independent connection.
class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT WebsocketStreams {
public:
    explicit WebsocketStreams(common::WebsocketStreamsConfig configuration);

    /// A client for `config.url`, production when it is not set.
    [[nodiscard]] static WebsocketStreams from_config(common::WebsocketStreamsConfig config);
    /// A client for production (Derivatives Trading Coin Futures WebSocket streams).
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

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
