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
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/websocket_streams/market_api.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models.hpp>
#include <binance/derivatives_trading_options/websocket_streams/public_api.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

class WebsocketStreams;

/// A connection to the DerivativesTradingOptions WebSocket streams, returned connected by
/// `WebsocketStreams::connect()`. Cheap to copy: copies share one `common::WebsocketStreams`
/// (connection pool and executor), which reconnects, renews its connections and resubscribes
/// until `disconnect()`.
class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT WebsocketStreamsConnection {
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

    /// Index Price Streams
    ///
    /// `!index@arr`.
    ///
    /// Underlying(e.g ETHUSDT) index stream.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#index-price-streams
    [[nodiscard]] common::WebsocketStream<std::vector<IndexPriceStreamsResponseInner>>
    index_price_streams(const IndexPriceStreamsParams& params = {}) const {
        return market_api_.index_price_streams(params);
    }

    /// Kline/Candlestick Streams
    ///
    /// `<symbol>@kline_<interval>`.
    ///
    /// The Kline/Candlestick Stream push updates to the current klines/candlestick every 1000
    /// milliseconds (if existing).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<KlineCandlestickStreamsResponse>
    kline_candlestick_streams(const KlineCandlestickStreamsParams& params) const {
        return market_api_.kline_candlestick_streams(params);
    }

    /// New Symbol Info
    ///
    /// `!optionSymbol`.
    ///
    /// New symbol listing stream.
    ///
    /// Update Speed: 50ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#new-symbol-info
    [[nodiscard]] common::WebsocketStream<NewSymbolInfoResponse>
    new_symbol_info(const NewSymbolInfoParams& params = {}) const {
        return market_api_.new_symbol_info(params);
    }

    /// Open Interest
    ///
    /// `<underlying>@optionOpenInterest@<expirationDate>`.
    ///
    /// Option open interest for specific underlying asset on specific expiration date.
    /// E.g.ethusdt@optionOpenInterest@221125
    ///
    /// Update Speed: 60s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#open-interest
    [[nodiscard]] common::WebsocketStream<std::vector<OpenInterestResponseInner>>
    open_interest(const OpenInterestParams& params) const {
        return market_api_.open_interest(params);
    }

    /// Option Mark Price
    ///
    /// `<underlying>@optionMarkPrice`.
    ///
    /// The mark price for all option symbols on specific underlying asset.
    /// E.g.btcusdt@optionMarkPrice
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#option-mark-price
    [[nodiscard]] common::WebsocketStream<std::vector<OptionMarkPriceResponseInner>>
    option_mark_price(const OptionMarkPriceParams& params) const {
        return market_api_.option_mark_price(params);
    }

    // PublicApi

    /// Diff Book Depth Streams
    ///
    /// `<symbol>@depth@<updateSpeed>`.
    ///
    /// Bids and asks, pushed every 500 milliseconds, 100 milliseconds (if existing)
    ///
    /// Update Speed: 100ms or 500ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#diff-book-depth-streams
    [[nodiscard]] common::WebsocketStream<DiffBookDepthStreamsResponse>
    diff_book_depth_streams(const DiffBookDepthStreamsParams& params) const {
        return public_api_.diff_book_depth_streams(params);
    }

    /// 24-hour TICKER
    ///
    /// `<symbol>@optionTicker<expirationDate>`.
    ///
    /// 24hr ticker info for all symbols. Only symbols whose ticker info changed will be sent.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#hour24-ticker
    [[nodiscard]] common::WebsocketStream<Hour24TickerResponse>
    hour24_ticker(const Hour24TickerParams& params) const {
        return public_api_.hour24_ticker(params);
    }

    /// Individual Symbol Book Ticker Streams
    ///
    /// `<symbol>@bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in real-time for a specified
    /// symbol.
    ///
    /// Update Speed: Real-Time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#individual-symbol-book-ticker-streams
    [[nodiscard]] common::WebsocketStream<IndividualSymbolBookTickerStreamsResponse>
    individual_symbol_book_ticker_streams(
        const IndividualSymbolBookTickerStreamsParams& params) const {
        return public_api_.individual_symbol_book_ticker_streams(params);
    }

    /// Partial Book Depth Streams
    ///
    /// `<symbol>@depth<level>@<updateSpeed>`.
    ///
    /// Top <levels> bids and asks. Valid <levels> are 5, 10, 20.
    ///
    /// Update Speed: 100ms or 500ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#partial-book-depth-streams
    [[nodiscard]] common::WebsocketStream<PartialBookDepthStreamsResponse>
    partial_book_depth_streams(const PartialBookDepthStreamsParams& params) const {
        return public_api_.partial_book_depth_streams(params);
    }

    /// Trade Streams
    ///
    /// `<symbol>@optionTrade`.
    ///
    /// The Trade Streams push raw trade information for specific symbol or underlying asset.
    /// E.g.btcusdt@optionTrade
    ///
    /// Update Speed: 50ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#trade-streams
    [[nodiscard]] common::WebsocketStream<TradeStreamsResponse>
    trade_streams(const TradeStreamsParams& params) const {
        return public_api_.trade_streams(params);
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

/// DerivativesTradingOptions WebSocket streams client: holds the configuration, and `connect()`
/// opens a new connection with it, like the `connect()` of the other Binance connectors. Every call
/// returns an independent connection.
class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT WebsocketStreams {
public:
    explicit WebsocketStreams(common::WebsocketStreamsConfig configuration);

    /// A client for `config.url`, production when it is not set.
    [[nodiscard]] static WebsocketStreams from_config(common::WebsocketStreamsConfig config);
    /// A client for production (Derivatives Trading Options WebSocket streams).
    [[nodiscard]] static WebsocketStreams production(common::WebsocketStreamsConfig config);
    /// A client for the testnet.
    [[nodiscard]] static WebsocketStreams testnet(common::WebsocketStreamsConfig config);

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

} // namespace binance::derivatives_trading_options::websocket_streams
