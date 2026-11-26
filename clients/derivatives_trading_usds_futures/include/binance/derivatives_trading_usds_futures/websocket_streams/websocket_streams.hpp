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
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/market_api.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/public_api.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

class WebsocketStreams;

/// A connection to the DerivativesTradingUsdsFutures WebSocket streams, returned connected by
/// `WebsocketStreams::connect()`. Cheap to copy: copies share one `common::WebsocketStreams`
/// (connection pool and executor), which reconnects, renews its connections and resubscribes
/// until `disconnect()`.
class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT WebsocketStreamsConnection {
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
        return common::WebsocketStream<UserDataStreamEventsResponse>(client_->create_stream(
            std::move(listen_key), std::move(id), std::optional<std::string>("private")));
    }

    // MarketApi

    /// Aggregate Trade Streams
    ///
    /// `<symbol>@aggTrade`.
    ///
    /// The Aggregate Trade Streams push market trade information that is aggregated for fills with
    /// same price and taking side every 100 milliseconds. Only market trades will be aggregated,
    /// which means the insurance fund trades and ADL trades won't be aggregated.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 100ms
    ///
    /// Response Notes:
    /// - Retail Price Improvement(RPI) orders are aggregated into field q and without special tags
    /// to be distinguished.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#aggregate-trade-streams
    [[nodiscard]] common::WebsocketStream<AggregateTradeStreamsResponse>
    aggregate_trade_streams(const AggregateTradeStreamsParams& params) const {
        return market_api_.aggregate_trade_streams(params);
    }

    /// All Market Liquidation Order Streams
    ///
    /// `!forceOrder@arr`.
    ///
    /// The All Liquidation Order Snapshot Streams push force liquidation order information for all
    /// symbols in the market. For each symbol，only the largest one liquidation order within 1000ms
    /// will be pushed as the snapshot. If no liquidation happens in the interval of 1000ms, no
    /// stream will be pushed.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM) and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#all-market-liquidation-order-streams
    [[nodiscard]] common::WebsocketStream<AllMarketLiquidationOrderStreamsResponse>
    all_market_liquidation_order_streams(
        const AllMarketLiquidationOrderStreamsParams& params = {}) const {
        return market_api_.all_market_liquidation_order_streams(params);
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
    /// = CM) and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#all-market-mini-tickers-stream
    [[nodiscard]] common::WebsocketStream<std::vector<AllMarketMiniTickersStreamResponseInner>>
    all_market_mini_tickers_stream(const AllMarketMiniTickersStreamParams& params = {}) const {
        return market_api_.all_market_mini_tickers_stream(params);
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
    /// = CM) and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#all-market-tickers-streams
    [[nodiscard]] common::WebsocketStream<std::vector<AllMarketTickersStreamsResponseInner>>
    all_market_tickers_streams(const AllMarketTickersStreamsParams& params = {}) const {
        return market_api_.all_market_tickers_streams(params);
    }

    /// Multi-Assets Mode Asset Index
    ///
    /// `!assetIndex@arr`.
    ///
    /// Asset index price. Subscribe with `!assetIndex@arr` for all assets, or
    /// `<assetSymbol>@assetIndex` for a specific asset.
    ///
    /// > **CM-UM Integration (Effective 2026-06-30):** Renamed from *Multi-Assets Mode Asset
    /// Index*. The stream `!assetIndex@arr` now additionally pushes COIN-M settlement-asset price
    /// index entries (e.g., `BTCUSD`, `ETHUSD`, `BNBUSD`). The on-the-wire stream key is unchanged;
    /// existing subscriptions continue to work.
    ///
    /// Update Speed: 1s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#asset-index
    [[nodiscard]] common::WebsocketStream<std::vector<AssetIndexResponseInner>>
    asset_index(const AssetIndexParams& params = {}) const {
        return market_api_.asset_index(params);
    }

    /// Composite Index Symbol Information Streams
    ///
    /// `<symbol>@compositeIndex`.
    ///
    /// Composite index information for index symbols pushed every second.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#composite-index-symbol-information-streams
    [[nodiscard]] common::WebsocketStream<CompositeIndexSymbolInformationStreamsResponse>
    composite_index_symbol_information_streams(
        const CompositeIndexSymbolInformationStreamsParams& params) const {
        return market_api_.composite_index_symbol_information_streams(params);
    }

    /// Continuous Contract Kline/Candlestick Streams
    ///
    /// `<pair>_<contractType>@continuousKline_<interval>`.
    ///
    /// Continuous Contract Kline/Candlestick Streams
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to either UM or CM
    /// symbols on this stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#continuous-contract-kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<ContinuousContractKlineCandlestickStreamsResponse>
    continuous_contract_kline_candlestick_streams(
        const ContinuousContractKlineCandlestickStreamsParams& params) const {
        return market_api_.continuous_contract_kline_candlestick_streams(params);
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#contract-info-stream
    [[nodiscard]] common::WebsocketStream<ContractInfoStreamResponse>
    contract_info_stream(const ContractInfoStreamParams& params = {}) const {
        return market_api_.contract_info_stream(params);
    }

    /// Individual Symbol Mini Ticker Stream
    ///
    /// `<symbol>@miniTicker`.
    ///
    /// 24hr rolling window mini-ticker statistics for a single symbol. These are NOT the statistics
    /// of the UTC day, but a 24hr rolling window from requestTime to 24hrs before.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 2s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#individual-symbol-mini-ticker-stream
    [[nodiscard]] common::WebsocketStream<IndividualSymbolMiniTickerStreamResponse>
    individual_symbol_mini_ticker_stream(
        const IndividualSymbolMiniTickerStreamParams& params) const {
        return market_api_.individual_symbol_mini_ticker_stream(params);
    }

    /// Individual Symbol Ticker Streams
    ///
    /// `<symbol>@ticker`.
    ///
    /// 24hr rolling window ticker statistics for a single symbol. These are NOT the statistics of
    /// the UTC day, but a 24hr rolling window from requestTime to 24hrs before.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 2000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#individual-symbol-ticker-streams
    [[nodiscard]] common::WebsocketStream<IndividualSymbolTickerStreamsResponse>
    individual_symbol_ticker_streams(const IndividualSymbolTickerStreamsParams& params) const {
        return market_api_.individual_symbol_ticker_streams(params);
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<KlineCandlestickStreamsResponse>
    kline_candlestick_streams(const KlineCandlestickStreamsParams& params) const {
        return market_api_.kline_candlestick_streams(params);
    }

    /// Liquidation Order Streams
    ///
    /// `<symbol>@forceOrder`.
    ///
    /// The Liquidation Order Snapshot Streams push force liquidation order information for specific
    /// symbol. For each symbol，only the largest one liquidation order within 1000ms will be pushed
    /// as the snapshot. If no liquidation happens in the interval of 1000ms, no stream will be
    /// pushed.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#liquidation-order-streams
    [[nodiscard]] common::WebsocketStream<LiquidationOrderStreamsResponse>
    liquidation_order_streams(const LiquidationOrderStreamsParams& params) const {
        return market_api_.liquidation_order_streams(params);
    }

    /// Mark Price Stream
    ///
    /// `<symbol>@markPrice@<updateSpeed>`.
    ///
    /// Mark price and funding rate for a single symbol pushed every 3 seconds or every second.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM); both `fstream` and `dstream` may subscribe to either UM or CM symbols on this stream.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#mark-price-stream
    [[nodiscard]] common::WebsocketStream<MarkPriceStreamResponse>
    mark_price_stream(const MarkPriceStreamParams& params) const {
        return market_api_.mark_price_stream(params);
    }

    /// Mark Price Stream for All market
    ///
    /// `!markPrice@arr@<updateSpeed>`.
    ///
    /// Mark price and funding rate for all symbols pushed every 3 seconds or every second.
    ///
    /// **Note:**
    /// - TradFi symbols will be pushed through a seperate message.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM); both `fstream` and `dstream` may subscribe to either UM or CM symbols on this stream.
    ///
    /// Update Speed: 3s or 1s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#mark-price-stream-for-all-market
    [[nodiscard]] common::WebsocketStream<std::vector<MarkPriceStreamForAllMarketResponseInner>>
    mark_price_stream_for_all_market(const MarkPriceStreamForAllMarketParams& params = {}) const {
        return market_api_.mark_price_stream_for_all_market(params);
    }

    /// Trading Session Stream
    ///
    /// `tradingSession`.
    ///
    /// Trading session information for the underlying assets of TradFi Perpetual contracts,
    /// covering the U.S. equity market, Korean equity market, Hong Kong equity market, China equity
    /// market, the commodity market, and the FX market, is updated every second. Trading session
    /// information for different underlying markets is pushed in separate messages.
    ///
    /// **Event type:**
    ///
    /// - `EquityUpdate`: Session types for the U.S. equity market include "PRE_MARKET", "REGULAR",
    /// "AFTER_MARKET", "OVERNIGHT", and "NO_TRADING".
    /// - `CommodityUpdate`: Session types for the commodity market include "REGULAR" and
    /// "NO_TRADING".
    /// - `KR_EquityUpdate`: Session types for the Korean equity market include "REGULAR" and
    /// "NO_TRADING".
    /// - `HK_EquityUpdate`: Session types for the Hong Kong equity market include "REGULAR" and
    /// "NO_TRADING".
    /// - `CN_EquityUpdate`: Session types for the China equity market include "REGULAR" and
    /// "NO_TRADING".
    /// - `FXUpdate`: Session types for the FX market include "REGULAR" and "NO_TRADING".
    ///
    /// Update Speed: 1s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#trading-session-stream
    [[nodiscard]] common::WebsocketStream<TradingSessionStreamResponse>
    trading_session_stream(const TradingSessionStreamParams& params = {}) const {
        return market_api_.trading_session_stream(params);
    }

    // PublicApi

    /// All Book Tickers Stream
    ///
    /// `!bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in real-time for all symbols.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM) and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 5s
    ///
    /// Response Notes:
    /// - Retail Price Improvement(RPI) orders are not visible and excluded in the response message.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#all-book-tickers-stream
    [[nodiscard]] common::WebsocketStream<AllBookTickersStreamResponse>
    all_book_tickers_stream(const AllBookTickersStreamParams& params = {}) const {
        return public_api_.all_book_tickers_stream(params);
    }

    /// Diff. Book Depth Streams
    ///
    /// `<symbol>@depth@<updateSpeed>`.
    ///
    /// Bids and asks, pushed every 250 milliseconds, 500 milliseconds, 100 milliseconds (if
    /// existing).
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 250ms, 500ms, 100ms
    ///
    /// Response Notes:
    /// - Retail Price Improvement(RPI) orders are not visible and excluded in the response message.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#diff-book-depth-streams
    [[nodiscard]] common::WebsocketStream<DiffBookDepthStreamsResponse>
    diff_book_depth_streams(const DiffBookDepthStreamsParams& params) const {
        return public_api_.diff_book_depth_streams(params);
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
    /// Response Notes:
    /// Retail Price Improvement (RPI) orders are not visible and excluded in the response message.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#individual-symbol-book-ticker-streams
    [[nodiscard]] common::WebsocketStream<IndividualSymbolBookTickerStreamsResponse>
    individual_symbol_book_ticker_streams(
        const IndividualSymbolBookTickerStreamsParams& params) const {
        return public_api_.individual_symbol_book_ticker_streams(params);
    }

    /// Partial Book Depth Streams
    ///
    /// `<symbol>@depth<levels>@<updateSpeed>`.
    ///
    /// Top <levels> bids and asks
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 250ms or 500ms or 100ms
    ///
    /// Response Notes:
    /// Retail Price Improvement (RPI) orders are not visible and excluded in the response message.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#partial-book-depth-streams
    [[nodiscard]] common::WebsocketStream<PartialBookDepthStreamsResponse>
    partial_book_depth_streams(const PartialBookDepthStreamsParams& params) const {
        return public_api_.partial_book_depth_streams(params);
    }

    /// RPI Diff. Book Depth Streams
    ///
    /// `<symbol>@rpiDepth@500ms`.
    ///
    /// Bids and asks including RPI orders, pushed every 500 milliseconds
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 500ms
    ///
    /// Response Notes:
    /// - RPI(Retail Price Improvement) orders are included and aggreated in the response message.
    /// When the quantity of a price level to be updated is equal to 0, it means either all
    /// quotations for this price have been filled/canceled, or the quantity of crossed RPI orders
    /// for this price are hidden
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#rpi-diff-book-depth-streams
    [[nodiscard]] common::WebsocketStream<RpiDiffBookDepthStreamsResponse>
    rpi_diff_book_depth_streams(const RpiDiffBookDepthStreamsParams& params) const {
        return public_api_.rpi_diff_book_depth_streams(params);
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
    MarketApi market_api_;
    PublicApi public_api_;
};

/// DerivativesTradingUsdsFutures WebSocket streams client: holds the configuration, and `connect()`
/// opens a new connection with it, like the `connect()` of the other Binance connectors. Every call
/// returns an independent connection.
class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT WebsocketStreams {
public:
    explicit WebsocketStreams(common::WebsocketStreamsConfig configuration);

    /// A client for `config.url`, production when it is not set.
    [[nodiscard]] static WebsocketStreams from_config(common::WebsocketStreamsConfig config);
    /// A client for production (Derivatives Trading Usds Futures WebSocket streams).
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

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
