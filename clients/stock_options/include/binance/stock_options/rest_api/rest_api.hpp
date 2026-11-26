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
#include <utility>

#include <binance/common/config.hpp>
#include <binance/common/rest.hpp>
#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/market_data_api.hpp>
#include <binance/stock_options/rest_api/models.hpp>
#include <binance/stock_options/rest_api/trade_api.hpp>
#include <binance/stock_options/rest_api/user_data_api.hpp>
#include <binance/stock_options/rest_api/user_data_streams_api.hpp>

namespace binance::stock_options::rest_api {

/// StockOptions REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_STOCK_OPTIONS_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Stock Options REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);

    [[nodiscard]] const common::RestApiConfig& configuration() const noexcept;

    /// Calls an endpoint the SDK does not wrap yet. `T` may be `boost::json::value`.
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                 common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), false));
    }

    /// Like `send_request`, but signed (adds `timestamp` and `signature`).
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_signed_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                        common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), true));
    }

    template <class T, class CompletionToken>
    auto async_send_request(std::string endpoint, common::HttpMethod method, common::Params query,
                            common::Params body, CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), false),
            std::forward<CompletionToken>(token));
    }

    template <class T, class CompletionToken>
    auto async_send_signed_request(std::string endpoint, common::HttpMethod method,
                                   common::Params query, common::Params body,
                                   CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), true),
            std::forward<CompletionToken>(token));
    }

    // MarketDataApi

    /// Option Contracts (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/option/market/contracts.
    ///
    /// Returns every option contract (calls and puts) of an underlying for one expiration date.
    /// Reference data only — no market data.
    ///
    /// Sorted by `strikePrice` ascending; for the same strike, `CALL` comes before `PUT`. Not
    /// paginated.
    ///
    /// If there is no contract for the `(underlying, root, expiration)` combination, an empty array
    /// is returned.
    ///
    /// Only the `X-MBX-APIKEY` header is required; this endpoint is **not signed** and takes no
    /// `timestamp` / `recvWindow`.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/market-data#option-contracts
    [[nodiscard]] common::RestApiResponse<std::vector<OptionContractsResponseInner>>
    option_contracts(const OptionContractsParams& params) const {
        return market_data_api_.option_contracts(params);
    }
    /// Asynchronous `option_contracts()`.
    template <class CompletionToken>
    auto async_option_contracts(const OptionContractsParams& params,
                                CompletionToken&& token) const {
        return market_data_api_.async_option_contracts(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Option Exchange Info (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/option/market/exchangeInfo.
    ///
    /// Returns the trading rules of a single option contract, combining contract-level data (type,
    /// strike, expiration, multiplier, deliverables) with underlying-level configuration (price /
    /// quantity increments and limits).
    ///
    /// `symbol` is **required**. Unlike the stock `exchangeInfo`, listing all contracts is not
    /// supported. To browse contracts, use Option Expirations and Option Contracts.
    ///
    /// **Price constraints**: a limit price must be a multiple of `tickSize`, and the order
    /// notional (`price` × `quantity` × `multiplier`, excluding fees) must fall within the closed
    /// interval `[minNotional, maxNotional]`. For a put `SELL` order, the limit price cannot exceed
    /// the strike price. All of these values are returned by this endpoint, so you can validate an
    /// order before placing it.
    ///
    /// **`multiplier` vs `contractSize`**: `multiplier` is used to calculate cost, `contractSize`
    /// is the number of shares delivered. Both are 100 for standard contracts and may differ for
    /// contracts adjusted by a corporate action (split, merger, special dividend). Always estimate
    /// cost with `multiplier`.
    ///
    /// Only the `X-MBX-APIKEY` header is required; this endpoint is **not signed** and takes no
    /// `timestamp` / `recvWindow`.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/market-data#option-exchange-info
    [[nodiscard]] common::RestApiResponse<OptionExchangeInfoResponse>
    option_exchange_info(const OptionExchangeInfoParams& params) const {
        return market_data_api_.option_exchange_info(params);
    }
    /// Asynchronous `option_exchange_info()`.
    template <class CompletionToken>
    auto async_option_exchange_info(const OptionExchangeInfoParams& params,
                                    CompletionToken&& token) const {
        return market_data_api_.async_option_exchange_info(params,
                                                           std::forward<CompletionToken>(token));
    }

    /// Option Expirations (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/option/market/expirations.
    ///
    /// Returns every expiration date currently tradable for an underlying, in ascending
    /// `expirationDate` order.
    ///
    /// When standard and corporate-action-adjusted contracts share an expiration date, **multiple**
    /// rows are returned with the same `expirationDate` and different `rootSymbol`. To list the
    /// adjusted set, pass that `rootSymbol` to Option Contracts.
    ///
    /// Reference data only — no market data.
    ///
    /// An unknown underlying, or one without listed options, returns `-1121 Invalid symbol.` An
    /// empty array is never returned.
    ///
    /// Only the `X-MBX-APIKEY` header is required; this endpoint is **not signed** and takes no
    /// `timestamp` / `recvWindow`.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/market-data#option-expirations
    [[nodiscard]] common::RestApiResponse<std::vector<OptionExpirationsResponseInner>>
    option_expirations(const OptionExpirationsParams& params) const {
        return market_data_api_.option_expirations(params);
    }
    /// Asynchronous `option_expirations()`.
    template <class CompletionToken>
    auto async_option_expirations(const OptionExpirationsParams& params,
                                  CompletionToken&& token) const {
        return market_data_api_.async_option_expirations(params,
                                                         std::forward<CompletionToken>(token));
    }

    // TradeApi

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
    cancel_all_option_orders(const CancelAllOptionOrdersParams& params = {}) const {
        return trade_api_.cancel_all_option_orders(params);
    }
    /// Asynchronous `cancel_all_option_orders()`.
    template <class CompletionToken>
    auto async_cancel_all_option_orders(const CancelAllOptionOrdersParams& params,
                                        CompletionToken&& token) const {
        return trade_api_.async_cancel_all_option_orders(params,
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
    cancel_option_order(const CancelOptionOrderParams& params) const {
        return trade_api_.cancel_option_order(params);
    }
    /// Asynchronous `cancel_option_order()`.
    template <class CompletionToken>
    auto async_cancel_option_order(const CancelOptionOrderParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_cancel_option_order(params, std::forward<CompletionToken>(token));
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
    place_option_order(const PlaceOptionOrderParams& params) const {
        return trade_api_.place_option_order(params);
    }
    /// Asynchronous `place_option_order()`.
    template <class CompletionToken>
    auto async_place_option_order(const PlaceOptionOrderParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_place_option_order(params, std::forward<CompletionToken>(token));
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
    submit_option_exercise(const SubmitOptionExerciseParams& params) const {
        return trade_api_.submit_option_exercise(params);
    }
    /// Asynchronous `submit_option_exercise()`.
    template <class CompletionToken>
    auto async_submit_option_exercise(const SubmitOptionExerciseParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_submit_option_exercise(params,
                                                       std::forward<CompletionToken>(token));
    }

    // UserDataApi

    /// Current Open Option Orders (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/order/open-orders.
    ///
    /// Query all of the caller's open **option** orders, including the remaining quantity of
    /// partially filled orders. Stock orders are not included.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#current-open-option-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CurrentOpenOptionOrdersResponseInner>>
    current_open_option_orders(const CurrentOpenOptionOrdersParams& params = {}) const {
        return user_data_api_.current_open_option_orders(params);
    }
    /// Asynchronous `current_open_option_orders()`.
    template <class CompletionToken>
    auto async_current_open_option_orders(const CurrentOpenOptionOrdersParams& params,
                                          CompletionToken&& token) const {
        return user_data_api_.async_current_open_option_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Exercisable Options (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/exercise/exercisable.
    ///
    /// Returns the contracts that can currently be exercised. Only **long** positions are
    /// exercisable; the short side is the assigned party and has no exercise right.
    ///
    /// `availableQty` is the maximum quantity for Submit Option Exercise.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#exercisable-options
    [[nodiscard]] common::RestApiResponse<std::vector<ExercisableOptionsResponseInner>>
    exercisable_options(const ExercisableOptionsParams& params = {}) const {
        return user_data_api_.exercisable_options(params);
    }
    /// Asynchronous `exercisable_options()`.
    template <class CompletionToken>
    auto async_exercisable_options(const ExercisableOptionsParams& params,
                                   CompletionToken&& token) const {
        return user_data_api_.async_exercisable_options(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Option Exercise Detail (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/exercise/detail.
    ///
    /// Query the result of a single exercise request. Provide at least one of `tranId` and
    /// `clientOrderId`; omitting both returns `-1102`. If both are provided, the lookup uses
    /// `clientOrderId` and `tranId` is ignored (the opposite of Option Order Detail).
    ///
    /// Returns `497402 Order not found.` if no record is found or the record does not belong to the
    /// caller.
    ///
    /// `errorCode` is returned only when `status` is `FAILED`.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#option-exercise-detail
    [[nodiscard]] common::RestApiResponse<OptionExerciseDetailResponse>
    option_exercise_detail(const OptionExerciseDetailParams& params = {}) const {
        return user_data_api_.option_exercise_detail(params);
    }
    /// Asynchronous `option_exercise_detail()`.
    template <class CompletionToken>
    auto async_option_exercise_detail(const OptionExerciseDetailParams& params,
                                      CompletionToken&& token) const {
        return user_data_api_.async_option_exercise_detail(params,
                                                           std::forward<CompletionToken>(token));
    }

    /// Option Exercise History (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/exercise/history.
    ///
    /// Paged exercise history.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#option-exercise-history
    [[nodiscard]] common::RestApiResponse<OptionExerciseHistoryResponse>
    option_exercise_history(const OptionExerciseHistoryParams& params = {}) const {
        return user_data_api_.option_exercise_history(params);
    }
    /// Asynchronous `option_exercise_history()`.
    template <class CompletionToken>
    auto async_option_exercise_history(const OptionExerciseHistoryParams& params,
                                       CompletionToken&& token) const {
        return user_data_api_.async_option_exercise_history(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Option Order Detail (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/order/detail.
    ///
    /// Query a single option order with its fills and an itemized fee breakdown.
    ///
    /// Provide at least one of `orderId` and `clientOrderId`; omitting both returns `-1102`. If
    /// both are provided, the order is looked up by `orderId`, and `clientOrderId` must belong to
    /// the same order, otherwise `486218 Order not found` is returned.
    ///
    /// Only option orders are accepted: the `orderId` / `clientOrderId` of a stock order returns
    /// `-2013 Order does not exist.`; an unknown order ID returns `486218 Order not found`.
    ///
    /// Example: a fully filled buy-to-open order — `filledTotal` = `total` = 1.48 × 1 × 100 = 148
    /// (excluding fees); total fees `fee` = 0.65 (`commission` + `cat` + `orf` + `occ`). `sec` /
    /// `taf` are `0` for buy orders. For an order still in progress with no fills, `fee` and the
    /// itemized fees are not returned (`platformFee` is always `"0"`); for an order canceled or
    /// expired without any fill, each fee item is `"0"`. `canceledAt` / `expiredAt` are returned
    /// only in the corresponding status; `settlementDate` is not returned for buy orders.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#option-order-detail
    [[nodiscard]] common::RestApiResponse<OptionOrderDetailResponse>
    option_order_detail(const OptionOrderDetailParams& params = {}) const {
        return user_data_api_.option_order_detail(params);
    }
    /// Asynchronous `option_order_detail()`.
    template <class CompletionToken>
    auto async_option_order_detail(const OptionOrderDetailParams& params,
                                   CompletionToken&& token) const {
        return user_data_api_.async_option_order_detail(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Option Order History (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/order/history.
    ///
    /// Paged option order history, sorted by creation time in descending order. Only option orders
    /// are returned; stock orders are not included.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#option-order-history
    [[nodiscard]] common::RestApiResponse<OptionOrderHistoryResponse>
    option_order_history(const OptionOrderHistoryParams& params) const {
        return user_data_api_.option_order_history(params);
    }
    /// Asynchronous `option_order_history()`.
    template <class CompletionToken>
    auto async_option_order_history(const OptionOrderHistoryParams& params,
                                    CompletionToken&& token) const {
        return user_data_api_.async_option_order_history(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Option Positions (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/position.
    ///
    /// Returns all current option positions.
    ///
    /// One record per contract; see `side` for the direction.
    ///
    /// **`free` / `locked` are signed: negative for short positions.** For example, with 3 short
    /// contracts of which 1 is reserved by an open order, `free` = `"-2"` and `locked` = `"-1"`.
    /// When closing (`SELL_TO_CLOSE` / `BUY_TO_CLOSE`), the quantity you can order is the
    /// **absolute value** of `free`.
    ///
    /// Positions past the last trading time and awaiting settlement are not returned.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#option-positions
    [[nodiscard]] common::RestApiResponse<std::vector<OptionPositionsResponseInner>>
    option_positions(const OptionPositionsParams& params = {}) const {
        return user_data_api_.option_positions(params);
    }
    /// Asynchronous `option_positions()`.
    template <class CompletionToken>
    auto async_option_positions(const OptionPositionsParams& params,
                                CompletionToken&& token) const {
        return user_data_api_.async_option_positions(params, std::forward<CompletionToken>(token));
    }

    /// Option Settlement Event Detail (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/event/detail.
    ///
    /// Full detail of a single settlement event, including the settlement basis and collateral
    /// release. Returns `-1102` if `eventId` does not exist or does not belong to the caller.
    ///
    /// All fields of the history endpoint are included, with two differences: `contracts` is an
    /// absolute value, and `eventTime` is the time the settlement record was created.
    ///
    /// For an `EXPIRY` event, `settlementKind`, `cashDirection`, `amount` and `shareDelta` are not
    /// returned. For an `EXPIRY` event on a short position (covered call / cash-secured put),
    /// `collateralRelease` lists the collateral released.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#option-settlement-event-detail
    [[nodiscard]] common::RestApiResponse<OptionSettlementEventDetailResponse>
    option_settlement_event_detail(const OptionSettlementEventDetailParams& params) const {
        return user_data_api_.option_settlement_event_detail(params);
    }
    /// Asynchronous `option_settlement_event_detail()`.
    template <class CompletionToken>
    auto async_option_settlement_event_detail(const OptionSettlementEventDetailParams& params,
                                              CompletionToken&& token) const {
        return user_data_api_.async_option_settlement_event_detail(
            params, std::forward<CompletionToken>(token));
    }

    /// Option Settlement Event History (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/event/history.
    ///
    /// Query option settlement events — the settlement outcome of a contract: exercise, assignment
    /// or expiry (expired worthless), along with the shares / cash delivered and the collateral
    /// released. Sorted by event time in descending order.
    ///
    /// These records are on a settlement basis, separate from orders and trades.
    ///
    /// **Cursor pagination.** Omit `lastId` on the first page, then pass the `nextLastId` from the
    /// previous page until `hasMore` is `false`.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#option-settlement-event-history
    [[nodiscard]] common::RestApiResponse<OptionSettlementEventHistoryResponse>
    option_settlement_event_history(const OptionSettlementEventHistoryParams& params = {}) const {
        return user_data_api_.option_settlement_event_history(params);
    }
    /// Asynchronous `option_settlement_event_history()`.
    template <class CompletionToken>
    auto async_option_settlement_event_history(const OptionSettlementEventHistoryParams& params,
                                               CompletionToken&& token) const {
        return user_data_api_.async_option_settlement_event_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Option Trade History (USER_DATA)
    ///
    /// GET /sapi/v1/equity/option/trade/history.
    ///
    /// Paged per-fill option trade history. Only option fills are returned. Option fees are charged
    /// per order, so individual fills carry no fee; see `fee` in Option Order History / Option
    /// Order Detail.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data#option-trade-history
    [[nodiscard]] common::RestApiResponse<OptionTradeHistoryResponse>
    option_trade_history(const OptionTradeHistoryParams& params) const {
        return user_data_api_.option_trade_history(params);
    }
    /// Asynchronous `option_trade_history()`.
    template <class CompletionToken>
    auto async_option_trade_history(const OptionTradeHistoryParams& params,
                                    CompletionToken&& token) const {
        return user_data_api_.async_option_trade_history(params,
                                                         std::forward<CompletionToken>(token));
    }

    // UserDataStreamsApi

    /// Create / Renew Listen Key (USER_STREAM)
    ///
    /// POST /sapi/v1/equity/option/listenKey.
    ///
    /// Create or renew the user data stream `listenKey`.
    ///
    /// - **Valid for 1 hour.** Calling again renews it (resets to 1 hour) and returns the **same**
    /// key; renewing every 30 minutes is recommended. After expiry, a new key is issued and you
    /// must resubscribe with it.
    /// - **Options and stocks share one key.** The key is issued per user, not per asset class.
    /// This endpoint and `/sapi/v1/equity/listenKey` return the same key; calling either is enough.
    /// - Use the key to subscribe to the Order Report V2 Stream.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data-streams#create-renew-listen-key
    [[nodiscard]] common::RestApiResponse<CreateRenewListenKeyResponse>
    create_renew_listen_key(const CreateRenewListenKeyParams& params = {}) const {
        return user_data_streams_api_.create_renew_listen_key(params);
    }
    /// Asynchronous `create_renew_listen_key()`.
    template <class CompletionToken>
    auto async_create_renew_listen_key(const CreateRenewListenKeyParams& params,
                                       CompletionToken&& token) const {
        return user_data_streams_api_.async_create_renew_listen_key(
            params, std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::RestRequest make_request(std::string endpoint,
                                                          common::HttpMethod method,
                                                          common::Params query, common::Params body,
                                                          bool is_signed) {
        common::RestRequest req;
        req.method = method;
        req.endpoint = std::move(endpoint);
        req.query = std::move(query);
        req.body = std::move(body);
        req.is_signed = is_signed;
        return req;
    }

    std::shared_ptr<common::RestClient> client_;
    MarketDataApi market_data_api_;
    TradeApi trade_api_;
    UserDataApi user_data_api_;
    UserDataStreamsApi user_data_streams_api_;
};

} // namespace binance::stock_options::rest_api
