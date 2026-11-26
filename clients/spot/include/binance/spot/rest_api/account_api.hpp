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
#include <binance/common/rest.hpp>
#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/account_commission_response.hpp>
#include <binance/spot/rest_api/models/all_order_list_response_inner.hpp>
#include <binance/spot/rest_api/models/all_orders_response_inner.hpp>
#include <binance/spot/rest_api/models/get_account_response.hpp>
#include <binance/spot/rest_api/models/get_open_orders_response_inner.hpp>
#include <binance/spot/rest_api/models/get_order_list_response.hpp>
#include <binance/spot/rest_api/models/get_order_response.hpp>
#include <binance/spot/rest_api/models/my_allocations_response_inner.hpp>
#include <binance/spot/rest_api/models/my_filters_response.hpp>
#include <binance/spot/rest_api/models/my_prevented_matches_response_inner.hpp>
#include <binance/spot/rest_api/models/my_trades_response_inner.hpp>
#include <binance/spot/rest_api/models/open_order_list_response_inner.hpp>
#include <binance/spot/rest_api/models/order_amendments_response_inner.hpp>
#include <binance/spot/rest_api/models/rate_limit_order_response_inner.hpp>

namespace binance::spot::rest_api {

struct AccountCommissionParams {
    common::Required<std::string> symbol;
};

struct AllOrderListParams {
    /// If supplied, neither startTime or endTime can be provided
    std::optional<std::int64_t> from_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct AllOrdersParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    /// The value cannot be greater than `60000`.
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct GetAccountParams {
    /// When set to `true`, emits only the non-zero balances of an account.
    std::optional<bool> omit_zero_balances = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct GetOpenOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct GetOrderParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct GetOrderListParams {
    /// Query order list by `orderListId`. `orderListId` or `origClientOrderId` must be provided.
    std::optional<std::int64_t> order_list_id = std::nullopt;
    /// Query order list by `listClientOrderId`. `orderListId` or `origClientOrderId` must be
    /// provided.
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct MyAllocationsParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> from_allocation_id = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct MyFiltersParams {
    common::Required<std::string> symbol;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct MyPreventedMatchesParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> prevented_match_id = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::int64_t> from_prevented_match_id = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct MyTradesParams {
    common::Required<std::string> symbol;
    /// This can only be used in combination with `symbol`.
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// TradeId to fetch from. Default gets most recent trades.
    std::optional<std::int64_t> from_id = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OpenOrderListParams {
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderAmendmentsParams {
    common::Required<std::string> symbol;
    common::Required<std::int64_t> order_id;
    std::optional<std::int64_t> from_execution_id = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct RateLimitOrderParams {
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

class BINANCE_SPOT_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::RestClient> client);

    /// Query Commission Rates (USER_DATA)
    ///
    /// GET /api/v3/account/commission.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#account-commission
    [[nodiscard]] common::RestApiResponse<AccountCommissionResponse>
    account_commission(const AccountCommissionParams& params) const;

    /// Asynchronous `account_commission()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountCommissionResponse>)`.
    template <class CompletionToken>
    auto async_account_commission(const AccountCommissionParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<AccountCommissionResponse>(
            client_, account_commission_request(params), std::forward<CompletionToken>(token));
    }

    /// Query all Order lists (USER_DATA)
    ///
    /// GET /api/v3/allOrderList.
    ///
    /// Retrieves all order lists based on provided optional parameters.
    ///
    /// Note that the time between `startTime` and `endTime` can't be longer
    /// than 24 hours.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#all-order-list
    [[nodiscard]] common::RestApiResponse<std::vector<AllOrderListResponseInner>>
    all_order_list(const AllOrderListParams& params = {}) const;

    /// Asynchronous `all_order_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<AllOrderListResponseInner>>)`.
    template <class CompletionToken>
    auto async_all_order_list(const AllOrderListParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<AllOrderListResponseInner>>(
            client_, all_order_list_request(params), std::forward<CompletionToken>(token));
    }

    /// All orders (USER_DATA)
    ///
    /// GET /api/v3/allOrders.
    ///
    /// Get all account orders; active, canceled, or filled.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// - If `orderId` is set, it will get orders >= that `orderId`. Otherwise most recent orders
    /// are returned.
    /// - For some historical orders `cummulativeQuoteQty` will be < 0, meaning the data is not
    /// available at this time.
    /// - If `startTime` and/or `endTime` provided, `orderId` is not required.
    /// - The time between `startTime` and `endTime` can't be longer than 24 hours.
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#all-orders
    [[nodiscard]] common::RestApiResponse<std::vector<AllOrdersResponseInner>>
    all_orders(const AllOrdersParams& params) const;

    /// Asynchronous `all_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<AllOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_all_orders(const AllOrdersParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<AllOrdersResponseInner>>(
            client_, all_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Account information (USER_DATA)
    ///
    /// GET /api/v3/account.
    ///
    /// Get current account information.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory => Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#get-account
    [[nodiscard]] common::RestApiResponse<GetAccountResponse>
    get_account(const GetAccountParams& params = {}) const;

    /// Asynchronous `get_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetAccountResponse>)`.
    template <class CompletionToken>
    auto async_get_account(const GetAccountParams& params, CompletionToken&& token) const {
        return common::async_send<GetAccountResponse>(client_, get_account_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Current open orders (USER_DATA)
    ///
    /// GET /api/v3/openOrders.
    ///
    /// Get all open orders on a symbol. **Careful** when accessing this with no symbol.
    ///
    /// Weight: 6 for a single symbol; 80 when the symbol parameter is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory => Database
    ///
    /// - If the symbol is not sent, orders for all symbols will be returned in an array.
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#get-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<GetOpenOrdersResponseInner>>
    get_open_orders(const GetOpenOrdersParams& params = {}) const;

    /// Asynchronous `get_open_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetOpenOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_open_orders(const GetOpenOrdersParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<GetOpenOrdersResponseInner>>(
            client_, get_open_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Query order (USER_DATA)
    ///
    /// GET /api/v3/order.
    ///
    /// Check an order's status.
    ///
    /// Weight(IP): 4
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory => Database
    ///
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - If both `orderId` and `origClientOrderId` are provided, the `orderId` is searched first,
    /// then the `origClientOrderId` from that result is checked against that order. If both
    /// conditions are not met the request will be rejected.
    /// - For some historical orders `cummulativeQuoteQty` will be < 0, meaning the data is not
    /// available at this time.
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#get-order
    [[nodiscard]] common::RestApiResponse<GetOrderResponse>
    get_order(const GetOrderParams& params) const;

    /// Asynchronous `get_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetOrderResponse>)`.
    template <class CompletionToken>
    auto async_get_order(const GetOrderParams& params, CompletionToken&& token) const {
        return common::async_send<GetOrderResponse>(client_, get_order_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Query Order list (USER_DATA)
    ///
    /// GET /api/v3/orderList.
    ///
    /// Retrieves a specific order list based on provided optional parameters.
    ///
    /// Weight(IP): 4
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#get-order-list
    [[nodiscard]] common::RestApiResponse<GetOrderListResponse>
    get_order_list(const GetOrderListParams& params = {}) const;

    /// Asynchronous `get_order_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetOrderListResponse>)`.
    template <class CompletionToken>
    auto async_get_order_list(const GetOrderListParams& params, CompletionToken&& token) const {
        return common::async_send<GetOrderListResponse>(client_, get_order_list_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// Query Allocations (USER_DATA)
    ///
    /// GET /api/v3/myAllocations.
    ///
    /// Retrieves allocations resulting from SOR order placement.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Database"
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#my-allocations
    [[nodiscard]] common::RestApiResponse<std::vector<MyAllocationsResponseInner>>
    my_allocations(const MyAllocationsParams& params) const;

    /// Asynchronous `my_allocations()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<MyAllocationsResponseInner>>)`.
    template <class CompletionToken>
    auto async_my_allocations(const MyAllocationsParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<MyAllocationsResponseInner>>(
            client_, my_allocations_request(params), std::forward<CompletionToken>(token));
    }

    /// Query relevant filters (USER_DATA)
    ///
    /// GET /api/v3/myFilters.
    ///
    /// Retrieves the list of filters relevant to an account on a given symbol. This is the only
    /// endpoint that shows if an account has `MAX_ASSET` filters applied to it.
    ///
    /// Weight(IP): 40
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#my-filters
    [[nodiscard]] common::RestApiResponse<MyFiltersResponse>
    my_filters(const MyFiltersParams& params) const;

    /// Asynchronous `my_filters()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MyFiltersResponse>)`.
    template <class CompletionToken>
    auto async_my_filters(const MyFiltersParams& params, CompletionToken&& token) const {
        return common::async_send<MyFiltersResponse>(client_, my_filters_request(params),
                                                     std::forward<CompletionToken>(token));
    }

    /// Query Prevented Matches (USER_DATA)
    ///
    /// GET /api/v3/myPreventedMatches.
    ///
    /// Displays the list of orders that were expired due to STP.
    ///
    /// These are the combinations supported:
    ///   - `symbol` + `preventedMatchId`
    ///   - `symbol` + `orderId`
    ///   - `symbol` + `orderId` + `fromPreventedMatchId` (`limit` will default to 500)
    ///   - `symbol` + `orderId` + `fromPreventedMatchId` + `limit`
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#my-prevented-matches
    [[nodiscard]] common::RestApiResponse<std::vector<MyPreventedMatchesResponseInner>>
    my_prevented_matches(const MyPreventedMatchesParams& params) const;

    /// Asynchronous `my_prevented_matches()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<MyPreventedMatchesResponseInner>>)`.
    template <class CompletionToken>
    auto async_my_prevented_matches(const MyPreventedMatchesParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<std::vector<MyPreventedMatchesResponseInner>>(
            client_, my_prevented_matches_request(params), std::forward<CompletionToken>(token));
    }

    /// Account trade list (USER_DATA)
    ///
    /// GET /api/v3/myTrades.
    ///
    /// Get trades for a specific account and symbol.
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
    /// **Notes:**:
    /// - If `fromId` is set, it will get trades >= that `fromId`. Otherwise most recent trades are
    /// returned.
    /// - The time between `startTime` and `endTime` can't be longer than 24 hours.
    /// - These are the supported combinations of all parameters:
    ///   - `symbol`
    ///   - `symbol` + `orderId`
    ///   - `symbol` + `startTime`
    ///   - `symbol` + `endTime`
    ///   - `symbol` + `fromId`
    ///   - `symbol` + `startTime` + `endTime`
    ///   - `symbol`+ `orderId` + `fromId`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#my-trades
    [[nodiscard]] common::RestApiResponse<std::vector<MyTradesResponseInner>>
    my_trades(const MyTradesParams& params) const;

    /// Asynchronous `my_trades()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<MyTradesResponseInner>>)`.
    template <class CompletionToken>
    auto async_my_trades(const MyTradesParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<MyTradesResponseInner>>(
            client_, my_trades_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Open Order lists (USER_DATA)
    ///
    /// GET /api/v3/openOrderList.
    ///
    /// Query Open Order lists
    ///
    /// Weight(IP): 6
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory -> Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#open-order-list
    [[nodiscard]] common::RestApiResponse<std::vector<OpenOrderListResponseInner>>
    open_order_list(const OpenOrderListParams& params = {}) const;

    /// Asynchronous `open_order_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<OpenOrderListResponseInner>>)`.
    template <class CompletionToken>
    auto async_open_order_list(const OpenOrderListParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<OpenOrderListResponseInner>>(
            client_, open_order_list_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Order Amendments (USER_DATA)
    ///
    /// GET /api/v3/order/amendments.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#order-amendments
    [[nodiscard]] common::RestApiResponse<std::vector<OrderAmendmentsResponseInner>>
    order_amendments(const OrderAmendmentsParams& params) const;

    /// Asynchronous `order_amendments()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<OrderAmendmentsResponseInner>>)`.
    template <class CompletionToken>
    auto async_order_amendments(const OrderAmendmentsParams& params,
                                CompletionToken&& token) const {
        return common::async_send<std::vector<OrderAmendmentsResponseInner>>(
            client_, order_amendments_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Unfilled Order Count (USER_DATA)
    ///
    /// GET /api/v3/rateLimit/order.
    ///
    /// Displays the user's unfilled order count for all intervals.
    ///
    /// Weight(IP): 40
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/account#rate-limit-order
    [[nodiscard]] common::RestApiResponse<std::vector<RateLimitOrderResponseInner>>
    rate_limit_order(const RateLimitOrderParams& params = {}) const;

    /// Asynchronous `rate_limit_order()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<RateLimitOrderResponseInner>>)`.
    template <class CompletionToken>
    auto async_rate_limit_order(const RateLimitOrderParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<RateLimitOrderResponseInner>>(
            client_, rate_limit_order_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    account_commission_request(const AccountCommissionParams& params) const;
    [[nodiscard]] common::RestRequest
    all_order_list_request(const AllOrderListParams& params) const;
    [[nodiscard]] common::RestRequest all_orders_request(const AllOrdersParams& params) const;
    [[nodiscard]] common::RestRequest get_account_request(const GetAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    get_open_orders_request(const GetOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest get_order_request(const GetOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    get_order_list_request(const GetOrderListParams& params) const;
    [[nodiscard]] common::RestRequest
    my_allocations_request(const MyAllocationsParams& params) const;
    [[nodiscard]] common::RestRequest my_filters_request(const MyFiltersParams& params) const;
    [[nodiscard]] common::RestRequest
    my_prevented_matches_request(const MyPreventedMatchesParams& params) const;
    [[nodiscard]] common::RestRequest my_trades_request(const MyTradesParams& params) const;
    [[nodiscard]] common::RestRequest
    open_order_list_request(const OpenOrderListParams& params) const;
    [[nodiscard]] common::RestRequest
    order_amendments_request(const OrderAmendmentsParams& params) const;
    [[nodiscard]] common::RestRequest
    rate_limit_order_request(const RateLimitOrderParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::spot::rest_api
