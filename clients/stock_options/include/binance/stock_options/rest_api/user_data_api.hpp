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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/models/current_open_option_orders_response_inner.hpp>
#include <binance/stock_options/rest_api/models/exercisable_options_response_inner.hpp>
#include <binance/stock_options/rest_api/models/option_exercise_detail_response.hpp>
#include <binance/stock_options/rest_api/models/option_exercise_history_response.hpp>
#include <binance/stock_options/rest_api/models/option_order_detail_response.hpp>
#include <binance/stock_options/rest_api/models/option_order_history_response.hpp>
#include <binance/stock_options/rest_api/models/option_positions_response_inner.hpp>
#include <binance/stock_options/rest_api/models/option_settlement_event_detail_response.hpp>
#include <binance/stock_options/rest_api/models/option_settlement_event_history_response.hpp>
#include <binance/stock_options/rest_api/models/option_trade_history_response.hpp>

namespace binance::stock_options::rest_api {

enum class OptionOrderHistorySideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCK_OPTIONS_EXPORT std::string_view
to_string(OptionOrderHistorySideEnum value) noexcept;
BINANCE_STOCK_OPTIONS_EXPORT OptionOrderHistorySideEnum tag_invoke(
    boost::json::value_to_tag<OptionOrderHistorySideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             OptionOrderHistorySideEnum value);

enum class OptionTradeHistorySideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCK_OPTIONS_EXPORT std::string_view
to_string(OptionTradeHistorySideEnum value) noexcept;
BINANCE_STOCK_OPTIONS_EXPORT OptionTradeHistorySideEnum tag_invoke(
    boost::json::value_to_tag<OptionTradeHistorySideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             OptionTradeHistorySideEnum value);

struct CurrentOpenOptionOrdersParams {
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ExercisableOptionsParams {
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionExerciseDetailParams {
    /// Exercise transaction ID returned by Submit Option Exercise.
    std::optional<std::int64_t> tran_id = std::nullopt;
    /// Client ID used at submission.
    std::optional<std::string> client_order_id = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionExerciseHistoryParams {
    /// Comma-separated status filter: `PROCESSING` / `SUCCESS` / `FAILED`.
    std::optional<std::string> status = std::nullopt;
    /// Start time (ms).
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time (ms).
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Page number. Default `1`.
    std::optional<std::int64_t> current = std::nullopt;
    /// Page size. Default `20`, max `100`.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionOrderDetailParams {
    /// Option order ID. Provide at least one of `orderId` and `clientOrderId`.
    std::optional<std::string> order_id = std::nullopt;
    /// Client order ID. Provide at least one of `orderId` and `clientOrderId`.
    std::optional<std::string> client_order_id = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionOrderHistoryParams {
    /// Start of the order creation time (`createdAt`) filter (ms). If the span to `endTime` exceeds
    /// 180 days, it is truncated to 180 days before `endTime`.
    common::Required<std::int64_t> start_time;
    /// End of the order creation time (`createdAt`) filter (ms).
    common::Required<std::int64_t> end_time;
    /// Underlying US-equity ticker filter, e.g. `NVDA`, case-insensitive. Matches orders on **all**
    /// contracts of that underlying, not a single OCC contract. An unlisted or delisted ticker
    /// returns `-26004`.
    std::optional<std::string> underlying_symbol = std::nullopt;
    /// `BUY` / `SELL`.
    std::optional<OptionOrderHistorySideEnum> side = std::nullopt;
    /// Comma-separated status filter, without spaces: `FILLED` / `PARTIALLY_FILLED` / `CANCELED` /
    /// `EXPIRED` / `REJECTED`. If omitted, all statuses are returned except open orders with no
    /// fills (`NEW` / `ACCEPTED`, etc.).
    std::optional<std::string> order_status = std::nullopt;
    /// Page number. Default `1`.
    std::optional<std::int64_t> current = std::nullopt;
    /// Page size. Default `20`, max `100`.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionPositionsParams {
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionSettlementEventDetailParams {
    /// Event ID from Option Settlement Event History.
    common::Required<std::string> event_id;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionSettlementEventHistoryParams {
    /// Underlying US-equity ticker filter.
    std::optional<std::string> underlying_symbol = std::nullopt;
    /// OCC contract symbol filter. If both `symbol` and `underlyingSymbol` are sent, `symbol` takes
    /// precedence.
    std::optional<std::string> symbol = std::nullopt;
    /// Comma-separated event type filter: `EXERCISE` / `ASSIGNMENT` / `EXPIRY`, case-insensitive.
    std::optional<std::string> event_type = std::nullopt;
    /// Start of the event time (`eventTime`) filter (ms).
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End of the event time (`eventTime`) filter (ms).
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Cursor returned by the previous page. Omit on the first page.
    std::optional<std::int64_t> last_id = std::nullopt;
    /// Page size. Default `20`, max `100`.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionTradeHistoryParams {
    /// Start of the execution time (`executionAt`) filter (ms).
    common::Required<std::int64_t> start_time;
    /// End of the execution time (`executionAt`) filter (ms).
    common::Required<std::int64_t> end_time;
    /// Underlying US-equity ticker filter, e.g. `NVDA`, case-insensitive. Matches fills on **all**
    /// contracts of that underlying, not a single OCC contract. An unlisted or delisted ticker
    /// returns `-26004`.
    std::optional<std::string> underlying_symbol = std::nullopt;
    /// `BUY` / `SELL`.
    std::optional<OptionTradeHistorySideEnum> side = std::nullopt;
    /// Return fills of this order only.
    std::optional<std::string> order_id = std::nullopt;
    /// Page number. Default `1`.
    std::optional<std::int64_t> current = std::nullopt;
    /// Page size. Default `20`, max `100`.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STOCK_OPTIONS_EXPORT UserDataApi {
public:
    explicit UserDataApi(std::shared_ptr<common::RestClient> client);

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
    current_open_option_orders(const CurrentOpenOptionOrdersParams& params = {}) const;

    /// Asynchronous `current_open_option_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CurrentOpenOptionOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_current_open_option_orders(const CurrentOpenOptionOrdersParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<std::vector<CurrentOpenOptionOrdersResponseInner>>(
            client_, current_open_option_orders_request(params),
            std::forward<CompletionToken>(token));
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
    exercisable_options(const ExercisableOptionsParams& params = {}) const;

    /// Asynchronous `exercisable_options()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<ExercisableOptionsResponseInner>>)`.
    template <class CompletionToken>
    auto async_exercisable_options(const ExercisableOptionsParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<std::vector<ExercisableOptionsResponseInner>>(
            client_, exercisable_options_request(params), std::forward<CompletionToken>(token));
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
    option_exercise_detail(const OptionExerciseDetailParams& params = {}) const;

    /// Asynchronous `option_exercise_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OptionExerciseDetailResponse>)`.
    template <class CompletionToken>
    auto async_option_exercise_detail(const OptionExerciseDetailParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<OptionExerciseDetailResponse>(
            client_, option_exercise_detail_request(params), std::forward<CompletionToken>(token));
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
    option_exercise_history(const OptionExerciseHistoryParams& params = {}) const;

    /// Asynchronous `option_exercise_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OptionExerciseHistoryResponse>)`.
    template <class CompletionToken>
    auto async_option_exercise_history(const OptionExerciseHistoryParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<OptionExerciseHistoryResponse>(
            client_, option_exercise_history_request(params), std::forward<CompletionToken>(token));
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
    option_order_detail(const OptionOrderDetailParams& params = {}) const;

    /// Asynchronous `option_order_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OptionOrderDetailResponse>)`.
    template <class CompletionToken>
    auto async_option_order_detail(const OptionOrderDetailParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<OptionOrderDetailResponse>(
            client_, option_order_detail_request(params), std::forward<CompletionToken>(token));
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
    option_order_history(const OptionOrderHistoryParams& params) const;

    /// Asynchronous `option_order_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OptionOrderHistoryResponse>)`.
    template <class CompletionToken>
    auto async_option_order_history(const OptionOrderHistoryParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<OptionOrderHistoryResponse>(
            client_, option_order_history_request(params), std::forward<CompletionToken>(token));
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
    option_positions(const OptionPositionsParams& params = {}) const;

    /// Asynchronous `option_positions()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<OptionPositionsResponseInner>>)`.
    template <class CompletionToken>
    auto async_option_positions(const OptionPositionsParams& params,
                                CompletionToken&& token) const {
        return common::async_send<std::vector<OptionPositionsResponseInner>>(
            client_, option_positions_request(params), std::forward<CompletionToken>(token));
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
    option_settlement_event_detail(const OptionSettlementEventDetailParams& params) const;

    /// Asynchronous `option_settlement_event_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OptionSettlementEventDetailResponse>)`.
    template <class CompletionToken>
    auto async_option_settlement_event_detail(const OptionSettlementEventDetailParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<OptionSettlementEventDetailResponse>(
            client_, option_settlement_event_detail_request(params),
            std::forward<CompletionToken>(token));
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
    option_settlement_event_history(const OptionSettlementEventHistoryParams& params = {}) const;

    /// Asynchronous `option_settlement_event_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OptionSettlementEventHistoryResponse>)`.
    template <class CompletionToken>
    auto async_option_settlement_event_history(const OptionSettlementEventHistoryParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<OptionSettlementEventHistoryResponse>(
            client_, option_settlement_event_history_request(params),
            std::forward<CompletionToken>(token));
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
    option_trade_history(const OptionTradeHistoryParams& params) const;

    /// Asynchronous `option_trade_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OptionTradeHistoryResponse>)`.
    template <class CompletionToken>
    auto async_option_trade_history(const OptionTradeHistoryParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<OptionTradeHistoryResponse>(
            client_, option_trade_history_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    current_open_option_orders_request(const CurrentOpenOptionOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    exercisable_options_request(const ExercisableOptionsParams& params) const;
    [[nodiscard]] common::RestRequest
    option_exercise_detail_request(const OptionExerciseDetailParams& params) const;
    [[nodiscard]] common::RestRequest
    option_exercise_history_request(const OptionExerciseHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    option_order_detail_request(const OptionOrderDetailParams& params) const;
    [[nodiscard]] common::RestRequest
    option_order_history_request(const OptionOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    option_positions_request(const OptionPositionsParams& params) const;
    [[nodiscard]] common::RestRequest
    option_settlement_event_detail_request(const OptionSettlementEventDetailParams& params) const;
    [[nodiscard]] common::RestRequest
    option_settlement_event_history_request(const OptionSettlementEventHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    option_trade_history_request(const OptionTradeHistoryParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::stock_options::rest_api
