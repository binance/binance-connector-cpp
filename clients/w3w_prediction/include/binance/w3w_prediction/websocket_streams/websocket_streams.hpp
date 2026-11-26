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
#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/websocket_streams/api.hpp>
#include <binance/w3w_prediction/websocket_streams/models.hpp>

namespace binance::w3w_prediction::websocket_streams {

class WebsocketStreams;

/// A connection to the W3WPrediction WebSocket streams, returned connected by
/// `WebsocketStreams::connect()`. Cheap to copy: copies share one `common::WebsocketStreams`
/// (connection pool and executor), which reconnects, renews its connections and resubscribes
/// until `disconnect()`.
class BINANCE_W3W_PREDICTION_EXPORT WebsocketStreamsConnection {
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

    // Api

    /// Batch claim partially succeeded
    ///
    /// `web3_prediction_pm_claim_partial_success`.
    ///
    /// Pushed when only part of a batch claim succeeds. Only `pushId` is included — call the REST
    /// API for details.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#batch-claim-partially-succeeded
    [[nodiscard]] common::WebsocketStream<BatchClaimPartiallySucceededResponse>
    batch_claim_partially_succeeded() const {
        return api_.batch_claim_partially_succeeded();
    }

    /// Fund transfer failed
    ///
    /// `web3_prediction_pm_transfer_fail`.
    ///
    /// Pushed when a fund transfer fails.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#fund-transfer-failed
    [[nodiscard]] common::WebsocketStream<FundTransferFailedResponse> fund_transfer_failed() const {
        return api_.fund_transfer_failed();
    }

    /// Fund transfer succeeded
    ///
    /// `web3_prediction_pm_transfer_success`.
    ///
    /// Pushed when a fund transfer into or out of the prediction wallet succeeds. The direction and
    /// the token are not included (currently USDT only).
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#fund-transfer-succeeded
    [[nodiscard]] common::WebsocketStream<FundTransferSucceededResponse>
    fund_transfer_succeeded() const {
        return api_.fund_transfer_succeeded();
    }

    /// Limit order fully filled
    ///
    /// `web3_prediction_pm_limit_order_filled`.
    ///
    /// Pushed when a **limit order** is fully filled.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#limit-order-fully-filled
    [[nodiscard]] common::WebsocketStream<LimitOrderFullyFilledResponse>
    limit_order_fully_filled() const {
        return api_.limit_order_fully_filled();
    }

    /// Limit order partially filled
    ///
    /// `web3_prediction_pm_limit_order_partial_fill`.
    ///
    /// Pushed on each new partial fill of a **limit order**. One order can be pushed several times,
    /// so always remove duplicates by `pushId`.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#limit-order-partially-filled
    [[nodiscard]] common::WebsocketStream<LimitOrderPartiallyFilledResponse>
    limit_order_partially_filled() const {
        return api_.limit_order_partially_filled();
    }

    /// Limit order submission failed
    ///
    /// `web3_prediction_pm_limit_submit_fail`.
    ///
    /// Pushed when a **limit order** is rejected when placed. No `amount` is included.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#limit-order-submission-failed
    [[nodiscard]] common::WebsocketStream<LimitOrderSubmissionFailedResponse>
    limit_order_submission_failed() const {
        return api_.limit_order_submission_failed();
    }

    /// Limit order submitted successfully
    ///
    /// `web3_prediction_pm_limit_submit_success`.
    ///
    /// Pushed when the user's **limit order** is successfully placed on the order book.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#limit-order-submitted-successfully
    [[nodiscard]] common::WebsocketStream<LimitOrderSubmittedSuccessfullyResponse>
    limit_order_submitted_successfully() const {
        return api_.limit_order_submitted_successfully();
    }

    /// Market buy order failed / expired
    ///
    /// `web3_prediction_pm_market_buy_fail`.
    ///
    /// Pushed when the user's **market buy order** fails or expires.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#market-buy-order-failed
    [[nodiscard]] common::WebsocketStream<MarketBuyOrderFailedResponse>
    market_buy_order_failed() const {
        return api_.market_buy_order_failed();
    }

    /// Market buy order fully filled
    ///
    /// `web3_prediction_pm_market_buy_success`.
    ///
    /// Pushed when the user's **market buy order** is fully filled.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#market-buy-order-fully-filled
    [[nodiscard]] common::WebsocketStream<MarketBuyOrderFullyFilledResponse>
    market_buy_order_fully_filled() const {
        return api_.market_buy_order_fully_filled();
    }

    /// Market resolution notification
    ///
    /// `web3_prediction_pm_market_close`.
    ///
    /// Pushed when a market is resolved, to every user holding a position in it, win or lose. No
    /// amount or outcome is included — call the REST API for the user's profit and loss.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#market-resolution-notification
    [[nodiscard]] common::WebsocketStream<MarketResolutionNotificationResponse>
    market_resolution_notification() const {
        return api_.market_resolution_notification();
    }

    /// Market sell order failed / expired
    ///
    /// `web3_prediction_pm_market_sell_fail`.
    ///
    /// Pushed when the user's **market sell order** fails or expires.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#market-sell-order-failed-expired
    [[nodiscard]] common::WebsocketStream<MarketSellOrderFailedExpiredResponse>
    market_sell_order_failed_expired() const {
        return api_.market_sell_order_failed_expired();
    }

    /// Market sell order fully filled
    ///
    /// `web3_prediction_pm_market_sell_success`.
    ///
    /// Pushed when the user's **market sell order** is fully filled.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#market-sell-order-fully-filled
    [[nodiscard]] common::WebsocketStream<MarketSellOrderFullyFilledResponse>
    market_sell_order_fully_filled() const {
        return api_.market_sell_order_fully_filled();
    }

    /// Prediction Order Book by marketId
    ///
    /// `web3_prediction_orderbook_<marketId>`.
    ///
    /// Order book (bid/ask) updates for one market. Only active markets are pushed.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#prediction-order-book-by-market-id
    [[nodiscard]] common::WebsocketStream<PredictionOrderBookByMarketIdResponse>
    prediction_order_book_by_market_id(const PredictionOrderBookByMarketIdParams& params) const {
        return api_.prediction_order_book_by_market_id(params);
    }

    /// Reward claim failed
    ///
    /// `web3_prediction_pm_claim_fail`.
    ///
    /// Pushed when a claim fails completely — a single claim, or every item of a batch. For a
    /// batch, only the first failed item's amount and outcome are included.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#reward-claim-failed
    [[nodiscard]] common::WebsocketStream<RewardClaimFailedResponse> reward_claim_failed() const {
        return api_.reward_claim_failed();
    }

    /// Reward claim succeeded
    ///
    /// `web3_prediction_pm_claim_success`.
    ///
    /// Pushed when a claim fully succeeds — a single claim, or every item of a batch. Only the
    /// total is reported; no market title or outcome is included.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/ws-streams/~#reward-claim-succeeded
    [[nodiscard]] common::WebsocketStream<RewardClaimSucceededResponse>
    reward_claim_succeeded() const {
        return api_.reward_claim_succeeded();
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

/// W3WPrediction WebSocket streams client: holds the configuration, and `connect()` opens a new
/// connection with it, like the `connect()` of the other Binance connectors. Every call returns an
/// independent connection.
///
/// These streams are signed: the configuration needs `api_key` and `api_secret` (or `private_key`).
class BINANCE_W3W_PREDICTION_EXPORT WebsocketStreams {
public:
    explicit WebsocketStreams(common::WebsocketStreamsConfig configuration);

    /// A client for `config.url`, production when it is not set.
    [[nodiscard]] static WebsocketStreams from_config(common::WebsocketStreamsConfig config);
    /// A client for production (W3w Prediction WebSocket streams).
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

} // namespace binance::w3w_prediction::websocket_streams
