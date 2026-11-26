//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/models/cancel_all_option_orders_response.hpp>
#include <binance/stock_options/rest_api/models/cancel_option_order_response.hpp>
#include <binance/stock_options/rest_api/models/place_option_order_response.hpp>
#include <binance/stock_options/rest_api/models/submit_option_exercise_response.hpp>

namespace binance::stock_options::rest_api {

enum class PlaceOptionOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCK_OPTIONS_EXPORT std::string_view
to_string(PlaceOptionOrderSideEnum value) noexcept;
BINANCE_STOCK_OPTIONS_EXPORT PlaceOptionOrderSideEnum tag_invoke(
    boost::json::value_to_tag<PlaceOptionOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             PlaceOptionOrderSideEnum value);

enum class PlaceOptionOrderPositionIntentEnum {
    BuyToOpen,
    SellToClose,
    SellToOpen,
    BuyToClose,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCK_OPTIONS_EXPORT std::string_view
to_string(PlaceOptionOrderPositionIntentEnum value) noexcept;
BINANCE_STOCK_OPTIONS_EXPORT PlaceOptionOrderPositionIntentEnum
tag_invoke(boost::json::value_to_tag<PlaceOptionOrderPositionIntentEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             PlaceOptionOrderPositionIntentEnum value);

enum class PlaceOptionOrderTimeInForceEnum {
    Day,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCK_OPTIONS_EXPORT std::string_view
to_string(PlaceOptionOrderTimeInForceEnum value) noexcept;
BINANCE_STOCK_OPTIONS_EXPORT PlaceOptionOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<PlaceOptionOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             PlaceOptionOrderTimeInForceEnum value);

enum class PlaceOptionOrderWalletTypeEnum {
    Card,
    Main,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCK_OPTIONS_EXPORT std::string_view
to_string(PlaceOptionOrderWalletTypeEnum value) noexcept;
BINANCE_STOCK_OPTIONS_EXPORT PlaceOptionOrderWalletTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceOptionOrderWalletTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             PlaceOptionOrderWalletTypeEnum value);

struct CancelAllOptionOrdersParams {
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelOptionOrderParams {
    /// Option order ID.
    common::Required<std::string> order_id;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PlaceOptionOrderParams {
    /// OCC contract symbol.
    common::Required<std::string> symbol;
    /// `BUY` / `SELL`.
    common::Required<PlaceOptionOrderSideEnum> side;
    /// Number of contracts. Must be a whole number, minimum `1`.
    common::Required<std::string> quantity;
    /// Limit price (premium) per share, minimum `0.01`, must be a multiple of `tickSize`. For a put
    /// `SELL` order it cannot exceed the strike price (`497438`).
    common::Required<std::string> price;
    /// Quote asset. Only `USDC` (default) is supported; other values return `497104`.
    std::optional<std::string> quote_asset = std::nullopt;
    /// May be omitted and derived from `side` (`BUY` → `BUY_TO_OPEN`, `SELL` → `SELL_TO_CLOSE`);
    /// always pass it for the short side (`SELL_TO_OPEN` / `BUY_TO_CLOSE`). Must match `side` when
    /// passed.
    std::optional<PlaceOptionOrderPositionIntentEnum> position_intent = std::nullopt;
    /// Only `DAY` (default) is supported. Other values return a parameter error.
    std::optional<PlaceOptionOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// Payment wallet: `CARD` (default) / `MAIN`.
    std::optional<PlaceOptionOrderWalletTypeEnum> wallet_type = std::nullopt;
    /// Client order ID. Format `^[a-zA-Z0-9-_]{32,36}$`. Generated by the server when omitted.
    std::optional<std::string> client_order_id = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubmitOptionExerciseParams {
    /// OCC contract symbol to exercise.
    common::Required<std::string> symbol;
    /// Number of contracts to exercise. Whole number, minimum `1`, up to `availableQty`.
    common::Required<std::string> quantity;
    /// Quote asset. Only `USDC` (default) is supported; other values return `497104`.
    std::optional<std::string> quote_asset = std::nullopt;
    /// Client ID. Format `^[a-zA-Z0-9-_]{32,36}$`. Generated by the server when omitted.
    std::optional<std::string> client_order_id = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STOCK_OPTIONS_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Cancel All Option Orders (TRADE)
    ///
    /// POST /sapi/v1/equity/option/order/cancel-all.
    ///
    /// Cancel all of the caller's open orders.
    ///
    /// **This also cancels open stock orders.** Cancel-all is account-level at the broker and does
    /// not distinguish asset classes; it is the same operation as
    /// `/sapi/v1/equity/order/cancel-all`.
    ///
    /// To cancel option orders only, fetch them with Current Open Option Orders and cancel each one
    /// with Cancel Option Order.
    ///
    /// Errors on this endpoint use the Stocks Trading error codes (`486xxx`). See Stocks Trading
    /// Error Code.
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/trade#cancel-all-option-orders
    [[nodiscard]] common::RestApiResponse<CancelAllOptionOrdersResponse>
    cancel_all_option_orders(const CancelAllOptionOrdersParams& params = {}) const;

    /// Asynchronous `cancel_all_option_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAllOptionOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_option_orders(const CancelAllOptionOrdersParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<CancelAllOptionOrdersResponse>(
            client_, cancel_all_option_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel Option Order (TRADE)
    ///
    /// POST /sapi/v1/equity/option/order/cancel.
    ///
    /// Cancel an open order by `orderId`.
    ///
    /// Cancellation applies to the caller's own brokerage account and is not restricted by asset
    /// class: passing the `orderId` of a stock order also cancels it, and
    /// `/sapi/v1/equity/order/cancel` can likewise cancel option orders. Only the caller's own
    /// orders can be canceled.
    ///
    /// Errors on this endpoint use the Stocks Trading error codes (`486xxx`). See Stocks Trading
    /// Error Code.
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/trade#cancel-option-order
    [[nodiscard]] common::RestApiResponse<CancelOptionOrderResponse>
    cancel_option_order(const CancelOptionOrderParams& params) const;

    /// Asynchronous `cancel_option_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelOptionOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_option_order(const CancelOptionOrderParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<CancelOptionOrderResponse>(
            client_, cancel_option_order_request(params), std::forward<CompletionToken>(token));
    }

    /// Place Option Order (TRADE)
    ///
    /// POST /sapi/v1/equity/option/order/place.
    ///
    /// Place an option limit order.
    ///
    /// The server calculates the amount to lock based on `positionIntent` and the contract type:
    /// buy to open locks the premium plus fees; sell to open locks the underlying shares for a
    /// covered call, or the strike-equivalent cash for a cash-secured put. Fees are calculated by
    /// the server; callers do not pass payment details.
    ///
    /// **`positionIntent`**: may be omitted, in which case it is derived from `side`: `BUY` →
    /// `BUY_TO_OPEN`, `SELL` → `SELL_TO_CLOSE`. The derivation is unreliable in two cases, and an
    /// order without `positionIntent` is rejected (parameter error): a `BUY` while you hold a
    /// **short** position in the contract (it may be meant as `BUY_TO_CLOSE`), and a `SELL` while
    /// you hold **no long** position in the contract (it can only be `SELL_TO_OPEN`). Therefore
    /// always pass it for the short side (`SELL_TO_OPEN` / `BUY_TO_CLOSE`). When passed, it must
    /// match `side` (`BUY_*` with `BUY`, `SELL_*` with `SELL`), otherwise the order is rejected.
    ///
    /// Only `LIMIT` orders with `timeInForce = DAY` are supported, and `quantity` must be a whole
    /// number of contracts.
    ///
    /// Resubmitting with the **same** `clientOrderId` is idempotent: if the original order was
    /// accepted or is still processing, the original order is returned (`S` / `P`); if the original
    /// order failed, `497401` is returned.
    ///
    /// If the request returns `497001`, `497301` or a broker-rejection error code after the order
    /// has already been submitted to the broker, the order may still be processing. Retry with the
    /// **same** `clientOrderId` (a replay then returns `P`) or query Option Order Detail by
    /// `clientOrderId` for the final status. Do not retry with a new `clientOrderId`.
    ///
    /// Rate limit: 200 requests / min (UID).
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/trade#place-option-order
    [[nodiscard]] common::RestApiResponse<PlaceOptionOrderResponse>
    place_option_order(const PlaceOptionOrderParams& params) const;

    /// Asynchronous `place_option_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<PlaceOptionOrderResponse>)`.
    template <class CompletionToken>
    auto async_place_option_order(const PlaceOptionOrderParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<PlaceOptionOrderResponse>(
            client_, place_option_order_request(params), std::forward<CompletionToken>(token));
    }

    /// Submit Option Exercise (TRADE)
    ///
    /// POST /sapi/v1/equity/option/exercise/submit.
    ///
    /// Submit an exercise request for a long option position.
    ///
    /// Requires the `TRADE` permission, because exercising changes positions and balances.
    ///
    /// **Exercise is asynchronous.** The request returns `PROCESSING`; delivery is handled by the
    /// broker. Poll Option Exercise Detail for the final status.
    ///
    /// `quantity` cannot exceed `availableQty` from Exercisable Options.
    ///
    /// Resubmitting with the **same** `clientOrderId` is idempotent: if the original exercise was
    /// accepted or is still processing, it is returned with its current status; if it failed,
    /// `497401` is returned. If the request returns `497001`, `497301` or a broker-rejection error
    /// code, the exercise **may still be processing**: retry with the same `clientOrderId` or query
    /// Option Exercise Detail by `clientOrderId`. Do not resubmit with a new `clientOrderId`.
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/trade#submit-option-exercise
    [[nodiscard]] common::RestApiResponse<SubmitOptionExerciseResponse>
    submit_option_exercise(const SubmitOptionExerciseParams& params) const;

    /// Asynchronous `submit_option_exercise()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubmitOptionExerciseResponse>)`.
    template <class CompletionToken>
    auto async_submit_option_exercise(const SubmitOptionExerciseParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<SubmitOptionExerciseResponse>(
            client_, submit_option_exercise_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    cancel_all_option_orders_request(const CancelAllOptionOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_option_order_request(const CancelOptionOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    place_option_order_request(const PlaceOptionOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    submit_option_exercise_request(const SubmitOptionExerciseParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::stock_options::rest_api
