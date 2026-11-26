//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/websocket_streams.hpp>
#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/websocket_streams/models/batch_claim_partially_succeeded_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/fund_transfer_failed_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/fund_transfer_succeeded_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/limit_order_fully_filled_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/limit_order_partially_filled_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/limit_order_submission_failed_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/limit_order_submitted_successfully_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/market_buy_order_failed_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/market_buy_order_fully_filled_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/market_resolution_notification_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/market_sell_order_failed_expired_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/market_sell_order_fully_filled_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/prediction_order_book_by_market_id_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/reward_claim_failed_response.hpp>
#include <binance/w3w_prediction/websocket_streams/models/reward_claim_succeeded_response.hpp>

namespace binance::w3w_prediction::websocket_streams {

struct PredictionOrderBookByMarketIdParams {
    /// Market ID to subscribe to — the `marketId` inside `markets[]` returned by `market/list` or
    /// `market/detail`. It is **not** `marketTopicId` and **not** `externalId`. A wrong id is never
    /// rejected: subscribing with `marketTopicId`, `externalId`, or with a closed or resolved
    /// market returns the same successful `COMMAND` reply as a correct id and then pushes nothing
    /// at all, so a stream that stays silent is far more likely a wrong id than a broken
    /// connection.
    common::Required<std::string> market_id;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_W3W_PREDICTION_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::WebsocketStreams> client);

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
    batch_claim_partially_succeeded() const;

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
    [[nodiscard]] common::WebsocketStream<FundTransferFailedResponse> fund_transfer_failed() const;

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
    fund_transfer_succeeded() const;

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
    limit_order_fully_filled() const;

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
    limit_order_partially_filled() const;

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
    limit_order_submission_failed() const;

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
    limit_order_submitted_successfully() const;

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
    market_buy_order_failed() const;

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
    market_buy_order_fully_filled() const;

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
    market_resolution_notification() const;

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
    market_sell_order_failed_expired() const;

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
    market_sell_order_fully_filled() const;

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
    prediction_order_book_by_market_id(const PredictionOrderBookByMarketIdParams& params) const;

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
    [[nodiscard]] common::WebsocketStream<RewardClaimFailedResponse> reward_claim_failed() const;

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
    reward_claim_succeeded() const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::w3w_prediction::websocket_streams
