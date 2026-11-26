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
#include <utility>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/account_commission_response_result.hpp>
#include <binance/spot/websocket_api/models/account_rate_limits_orders_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/account_status_response_result.hpp>
#include <binance/spot/websocket_api/models/all_order_lists_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/all_orders_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/my_allocations_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/my_filters_response.hpp>
#include <binance/spot/websocket_api/models/my_prevented_matches_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/my_trades_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/open_order_lists_status_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/open_orders_status_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/order_amendments_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/order_list_status_response_result.hpp>
#include <binance/spot/websocket_api/models/order_status_response_result.hpp>

namespace binance::spot::websocket_api {

struct AccountCommissionParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
};

struct AccountRateLimitsOrdersParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct AccountStatusParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// When set to `true`, emits only the non-zero balances of an account. Default value: `false`.
    std::optional<bool> omit_zero_balances = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct AllOrderListsParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Order list ID to begin at
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Timestamp in ms
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Default: 500; Maximum: 1000
    std::optional<std::int64_t> limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct AllOrdersParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Order ID to begin at
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Timestamp in ms
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Default: 500; Maximum: 1000
    std::optional<std::int64_t> limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct MyAllocationsParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Timestamp in ms
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Allocation ID to begin at
    std::optional<std::int64_t> from_allocation_id = std::nullopt;
    /// Default: 500; Maximum: 1000
    std::optional<std::int64_t> limit = std::nullopt;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct MyFiltersParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct MyPreventedMatchesParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Prevented match ID
    std::optional<std::int64_t> prevented_match_id = std::nullopt;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Prevented match ID to begin at
    std::optional<std::int64_t> from_prevented_match_id = std::nullopt;
    /// Default: 500; Maximum: 1000
    std::optional<std::int64_t> limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct MyTradesParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// This can only be used in combination with `symbol`.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Timestamp in ms
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms
    std::optional<std::int64_t> end_time = std::nullopt;
    /// First trade ID to query
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Default: 500; Maximum: 1000
    std::optional<std::int64_t> limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OpenOrderListsStatusParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OpenOrdersStatusParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// If omitted, open orders for all symbols are returned
    std::optional<std::string> symbol = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderAmendmentsParams {
    common::Required<std::string> symbol;
    /// Order ID
    common::Required<std::int64_t> order_id;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Execution ID to begin at
    std::optional<std::int64_t> from_execution_id = std::nullopt;
    /// Default: 500; Maximum: 1000
    std::optional<std::int64_t> limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListStatusParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Query order list by `listClientOrderId`. `orderListId` or `origClientOrderId` must be
    /// provided.
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Query order list by `orderListId`. `orderListId` or `origClientOrderId` must be provided.
    std::optional<std::int64_t> order_list_id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderStatusParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Lookup order by `orderId`
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Lookup order by `clientOrderId`
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

class BINANCE_SPOT_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::WebsocketApi> client);

    /// Account Commission Rates (USER_DATA)
    ///
    /// `account.commission`.
    ///
    /// Get current account commission rates.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#account-commission
    [[nodiscard]] common::WebsocketApiResponse<AccountCommissionResponseResult>
    account_commission(const AccountCommissionParams& params) const;

    /// Asynchronous `account_commission()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<AccountCommissionResponseResult>)`.
    template <class CompletionToken>
    auto async_account_commission(const AccountCommissionParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<AccountCommissionResponseResult>(
            client_, "account.commission", account_commission_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Unfilled Order Count (USER_DATA)
    ///
    /// `account.rateLimits.orders`.
    ///
    /// Query your current unfilled order count for all intervals.
    ///
    /// Weight(IP): 40
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#account-rate-limits-orders
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<AccountRateLimitsOrdersResponseResultInner>>
    account_rate_limits_orders(const AccountRateLimitsOrdersParams& params = {}) const;

    /// Asynchronous `account_rate_limits_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<AccountRateLimitsOrdersResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_account_rate_limits_orders(const AccountRateLimitsOrdersParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<std::vector<AccountRateLimitsOrdersResponseResultInner>>(
            client_, "account.rateLimits.orders", account_rate_limits_orders_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Account information (USER_DATA)
    ///
    /// `account.status`.
    ///
    /// Query information about your account.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory => Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#account-status
    [[nodiscard]] common::WebsocketApiResponse<AccountStatusResponseResult>
    account_status(const AccountStatusParams& params = {}) const;

    /// Asynchronous `account_status()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<AccountStatusResponseResult>)`.
    template <class CompletionToken>
    auto async_account_status(const AccountStatusParams& params, CompletionToken&& token) const {
        return common::async_send<AccountStatusResponseResult>(
            client_, "account.status", account_status_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Account order list history (USER_DATA)
    ///
    /// `allOrderLists`.
    ///
    /// Query information about all your order lists, filtered by time range.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Notes:
    /// * If `startTime` and/or `endTime` are specified, `fromId` is ignored.
    ///   Order lists are filtered by `transactionTime` of the last order list execution status
    ///   update.
    /// * If `fromId` is specified, return order lists with order list ID >= `fromId`.
    /// * If no condition is specified, the most recent order lists are returned.
    /// * The time between `startTime` and `endTime` can't be longer than 24 hours.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#all-order-lists
    [[nodiscard]] common::WebsocketApiResponse<std::vector<AllOrderListsResponseResultInner>>
    all_order_lists(const AllOrderListsParams& params = {}) const;

    /// Asynchronous `all_order_lists()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<AllOrderListsResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_all_order_lists(const AllOrderListsParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<AllOrderListsResponseResultInner>>(
            client_, "allOrderLists", all_order_lists_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Account order history (USER_DATA)
    ///
    /// `allOrders`.
    ///
    /// Query information about all your orders – active, canceled, filled – filtered by time range.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Notes:
    ///
    /// * If `startTime` and/or `endTime` are specified, `orderId` is ignored.
    ///
    ///   Orders are filtered by `time` of the last execution status update.
    ///
    /// * If `orderId` is specified, return orders with order ID >= `orderId`.
    ///
    /// * If no condition is specified, the most recent orders are returned.
    ///
    /// * For some historical orders the `cummulativeQuoteQty` response field may be negative,
    ///   meaning the data is not available at this time.
    ///
    /// * The time between `startTime` and `endTime` can't be longer than 24 hours.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#all-orders
    [[nodiscard]] common::WebsocketApiResponse<std::vector<AllOrdersResponseResultInner>>
    all_orders(const AllOrdersParams& params) const;

    /// Asynchronous `all_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<AllOrdersResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_all_orders(const AllOrdersParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<AllOrdersResponseResultInner>>(
            client_, "allOrders", all_orders_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Account allocations (USER_DATA)
    ///
    /// `myAllocations`.
    ///
    /// Retrieves allocations resulting from SOR order placement.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Supported parameter combinations:
    ///
    /// Parameters                                  | Response |
    /// ------------------------------------------- | -------- |
    /// `symbol`                                    | allocations from oldest to newest |
    /// `symbol` + `startTime`                      | oldest allocations since `startTime` |
    /// `symbol` + `endTime`                        | newest allocations until `endTime` |
    /// `symbol` + `startTime` + `endTime`          | allocations within the time range |
    /// `symbol` + `fromAllocationId`               | allocations by allocation ID |
    /// `symbol` + `orderId`                        | allocations related to an order starting with
    /// oldest | `symbol` + `orderId` + `fromAllocationId`   | allocations related to an order by
    /// allocation ID |
    ///
    /// **Note:** The time between `startTime` and `endTime` can't be longer than 24 hours.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#my-allocations
    [[nodiscard]] common::WebsocketApiResponse<std::vector<MyAllocationsResponseResultInner>>
    my_allocations(const MyAllocationsParams& params) const;

    /// Asynchronous `my_allocations()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<MyAllocationsResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_my_allocations(const MyAllocationsParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<MyAllocationsResponseResultInner>>(
            client_, "myAllocations", my_allocations_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Query Relevant Filters (USER_DATA)
    ///
    /// `myFilters`.
    ///
    /// Retrieves the list of filters relevant to an account on a given symbol. This is the only
    /// method that shows if an account has `MAX_ASSET` filters applied to it.
    ///
    /// Weight(IP): 40
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#my-filters
    [[nodiscard]] common::WebsocketApiResponse<MyFiltersResponse>
    my_filters(const MyFiltersParams& params) const;

    /// Asynchronous `my_filters()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<MyFiltersResponse>)`.
    template <class CompletionToken>
    auto async_my_filters(const MyFiltersParams& params, CompletionToken&& token) const {
        return common::async_send<MyFiltersResponse>(
            client_, "myFilters", my_filters_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Account prevented matches (USER_DATA)
    ///
    /// `myPreventedMatches`.
    ///
    /// Displays the list of orders that were expired due to STP.
    ///
    /// These are the combinations supported:
    ///
    /// * `symbol` + `preventedMatchId`
    /// * `symbol` + `orderId`
    /// * `symbol` + `orderId` + `fromPreventedMatchId` (`limit` will default to 500)
    /// * `symbol` + `orderId` + `fromPreventedMatchId` + `limit`
    ///
    /// Weight: Case                            | Weight
    /// ----                            | -----
    /// If `symbol` is invalid          | 2
    /// Querying by `preventedMatchId`  | 2
    /// Querying by `orderId`           | 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#my-prevented-matches
    [[nodiscard]] common::WebsocketApiResponse<std::vector<MyPreventedMatchesResponseResultInner>>
    my_prevented_matches(const MyPreventedMatchesParams& params) const;

    /// Asynchronous `my_prevented_matches()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<MyPreventedMatchesResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_my_prevented_matches(const MyPreventedMatchesParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<std::vector<MyPreventedMatchesResponseResultInner>>(
            client_, "myPreventedMatches", my_prevented_matches_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Account trade history (USER_DATA)
    ///
    /// `myTrades`.
    ///
    /// Query information about all your trades, filtered by time range.
    ///
    /// Weight: Condition| Weight|
    /// ---| ---
    /// |Without orderId|20|
    /// |With orderId|5|
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory => Database
    ///
    /// Notes:
    /// - If `fromId` is specified, return trades with trade ID >= `fromId`.
    /// - If `startTime` and/or `endTime` are specified, trades are filtered by execution time
    /// (`time`).
    /// - `fromId` cannot be used together with `startTime` and `endTime`.
    /// - If `orderId` is specified, only trades related to that order are returned.
    /// - `startTime` and `endTime` cannot be used together with `orderId`.
    /// - If no condition is specified, the most recent trades are returned.
    /// - The time between `startTime` and `endTime` can't be longer than 24 hours.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#my-trades
    [[nodiscard]] common::WebsocketApiResponse<std::vector<MyTradesResponseResultInner>>
    my_trades(const MyTradesParams& params) const;

    /// Asynchronous `my_trades()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<MyTradesResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_my_trades(const MyTradesParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<MyTradesResponseResultInner>>(
            client_, "myTrades", my_trades_payload(params), make_options(false, true, false, false),
            std::forward<CompletionToken>(token));
    }

    /// Current open Order lists (USER_DATA)
    ///
    /// `openOrderLists.status`.
    ///
    /// Query execution status of all open order lists.
    ///
    /// If you need to continuously monitor order status updates, please consider using WebSocket
    /// Streams:
    ///
    /// * `userDataStream.subscribe` if on an authenticated session
    /// * `userDataStream.subscribe.signature` if subscribing through signature subscription
    ///
    /// Weight(IP): 6
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory -> Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#open-order-lists-status
    [[nodiscard]] common::WebsocketApiResponse<std::vector<OpenOrderListsStatusResponseResultInner>>
    open_order_lists_status(const OpenOrderListsStatusParams& params = {}) const;

    /// Asynchronous `open_order_lists_status()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<OpenOrderListsStatusResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_open_order_lists_status(const OpenOrderListsStatusParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<OpenOrderListsStatusResponseResultInner>>(
            client_, "openOrderLists.status", open_order_lists_status_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Current open orders (USER_DATA)
    ///
    /// `openOrders.status`.
    ///
    /// Query execution status of all open orders.
    ///
    /// If you need to continuously monitor order status updates, please consider using WebSocket
    /// Streams:
    ///
    /// * `userDataStream.subscribe` if on an authenticated session
    /// * `userDataStream.subscribe.signature` if subscribing through signature subscription
    ///
    /// Weight: | Parameter | Weight |
    /// | --------- | ------ |
    /// | `symbol`  |      6 |
    /// | none      |     80 |
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory => Database
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#open-orders-status
    [[nodiscard]] common::WebsocketApiResponse<std::vector<OpenOrdersStatusResponseResultInner>>
    open_orders_status(const OpenOrdersStatusParams& params = {}) const;

    /// Asynchronous `open_orders_status()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<OpenOrdersStatusResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_open_orders_status(const OpenOrdersStatusParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<OpenOrdersStatusResponseResultInner>>(
            client_, "openOrders.status", open_orders_status_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Query Order Amendments (USER_DATA)
    ///
    /// `order.amendments`.
    ///
    /// Queries all amendments of a single order.
    ///
    /// Weight(IP): 4
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#order-amendments
    [[nodiscard]] common::WebsocketApiResponse<std::vector<OrderAmendmentsResponseResultInner>>
    order_amendments(const OrderAmendmentsParams& params) const;

    /// Asynchronous `order_amendments()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<OrderAmendmentsResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_order_amendments(const OrderAmendmentsParams& params,
                                CompletionToken&& token) const {
        return common::async_send<std::vector<OrderAmendmentsResponseResultInner>>(
            client_, "order.amendments", order_amendments_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Query Order list (USER_DATA)
    ///
    /// `orderList.status`.
    ///
    /// Check execution status of an Order list.
    ///
    /// For execution status of individual orders, use `order.status`.
    ///
    /// Weight(IP): 4
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Notes:
    ///
    /// * `origClientOrderId` refers to `listClientOrderId` of the order list itself.
    ///
    /// * If both `origClientOrderId` and `orderListId` parameters are specified,
    ///   only `origClientOrderId` is used and `orderListId` is ignored.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#order-list-status
    [[nodiscard]] common::WebsocketApiResponse<OrderListStatusResponseResult>
    order_list_status(const OrderListStatusParams& params = {}) const;

    /// Asynchronous `order_list_status()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderListStatusResponseResult>)`.
    template <class CompletionToken>
    auto async_order_list_status(const OrderListStatusParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<OrderListStatusResponseResult>(
            client_, "orderList.status", order_list_status_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Query order (USER_DATA)
    ///
    /// `order.status`.
    ///
    /// Check execution status of an order.
    ///
    /// Weight(IP): 4
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory => Database
    ///
    /// Notes:
    ///
    /// * If both `orderId` and `origClientOrderId` are provided, the `orderId` is searched first,
    /// then the `origClientOrderId` from that result is checked against that order. If both
    /// conditions are not met the request will be rejected.
    ///
    /// * For some historical orders the `cummulativeQuoteQty` response field may be negative,
    ///   meaning the data is not available at this time.
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/account#order-status
    [[nodiscard]] common::WebsocketApiResponse<OrderStatusResponseResult>
    order_status(const OrderStatusParams& params) const;

    /// Asynchronous `order_status()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderStatusResponseResult>)`.
    template <class CompletionToken>
    auto async_order_status(const OrderStatusParams& params, CompletionToken&& token) const {
        return common::async_send<OrderStatusResponseResult>(
            client_, "order.status", order_status_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params
    account_commission_payload(const AccountCommissionParams& params);
    [[nodiscard]] static common::Params
    account_rate_limits_orders_payload(const AccountRateLimitsOrdersParams& params);
    [[nodiscard]] static common::Params account_status_payload(const AccountStatusParams& params);
    [[nodiscard]] static common::Params all_order_lists_payload(const AllOrderListsParams& params);
    [[nodiscard]] static common::Params all_orders_payload(const AllOrdersParams& params);
    [[nodiscard]] static common::Params my_allocations_payload(const MyAllocationsParams& params);
    [[nodiscard]] static common::Params my_filters_payload(const MyFiltersParams& params);
    [[nodiscard]] static common::Params
    my_prevented_matches_payload(const MyPreventedMatchesParams& params);
    [[nodiscard]] static common::Params my_trades_payload(const MyTradesParams& params);
    [[nodiscard]] static common::Params
    open_order_lists_status_payload(const OpenOrderListsStatusParams& params);
    [[nodiscard]] static common::Params
    open_orders_status_payload(const OpenOrdersStatusParams& params);
    [[nodiscard]] static common::Params
    order_amendments_payload(const OrderAmendmentsParams& params);
    [[nodiscard]] static common::Params
    order_list_status_payload(const OrderListStatusParams& params);
    [[nodiscard]] static common::Params order_status_payload(const OrderStatusParams& params);
    [[nodiscard]] static common::WebsocketMessageSendOptions
    make_options(bool with_api_key, bool is_signed, bool is_session_logon, bool is_session_logout) {
        common::WebsocketMessageSendOptions options;
        options.with_api_key = with_api_key;
        options.is_signed = is_signed;
        options.is_session_logon = is_session_logon;
        options.is_session_logout = is_session_logout;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
};

} // namespace binance::spot::websocket_api
