//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include <boost/asio/append.hpp>
#include <boost/asio/async_result.hpp>

#include <binance/common/config.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/account_api.hpp>
#include <binance/spot/websocket_api/auth_api.hpp>
#include <binance/spot/websocket_api/general_api.hpp>
#include <binance/spot/websocket_api/market_api.hpp>
#include <binance/spot/websocket_api/models.hpp>
#include <binance/spot/websocket_api/trade_api.hpp>
#include <binance/spot/websocket_api/user_data_stream_api.hpp>

namespace binance::spot::websocket_api {

class WebsocketApi;

/// A connection to the Spot WebSocket API, returned connected by `WebsocketApi::connect()`.
/// Cheap to copy: copies share one `common::WebsocketApi` (connection pool and executor), which
/// reconnects and renews its connections until `disconnect()`.
///
/// Every method has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_SPOT_EXPORT WebsocketApiConnection {
public:
    [[nodiscard]] const common::WebsocketApiConfig& configuration() const noexcept {
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

    /// Calls a method the SDK does not wrap yet. `T` may be `boost::json::value`.
    template <class T>
    [[nodiscard]] common::WebsocketApiResponse<T> send_message(std::string method,
                                                               common::Params payload = {}) const {
        return common::send<T>(*client_, std::move(method), std::move(payload));
    }

    /// Like `send_message`, but signed (adds `apiKey`, `timestamp` and `signature`).
    template <class T>
    [[nodiscard]] common::WebsocketApiResponse<T>
    send_signed_message(std::string method, common::Params payload = {}) const {
        return common::send<T>(*client_, std::move(method), std::move(payload), signed_options());
    }

    template <class T, class CompletionToken>
    auto async_send_message(std::string method, common::Params payload,
                            CompletionToken&& token) const {
        return common::async_send<T>(client_, std::move(method), std::move(payload), {},
                                     std::forward<CompletionToken>(token));
    }

    template <class T, class CompletionToken>
    auto async_send_signed_message(std::string method, common::Params payload,
                                   CompletionToken&& token) const {
        return common::async_send<T>(client_, std::move(method), std::move(payload),
                                     signed_options(), std::forward<CompletionToken>(token));
    }

    // AccountApi

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
    account_commission(const AccountCommissionParams& params) const {
        return account_api_.account_commission(params);
    }
    template <class CompletionToken>
    auto async_account_commission(const AccountCommissionParams& params,
                                  CompletionToken&& token) const {
        return account_api_.async_account_commission(params, std::forward<CompletionToken>(token));
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
    account_rate_limits_orders(const AccountRateLimitsOrdersParams& params = {}) const {
        return account_api_.account_rate_limits_orders(params);
    }
    template <class CompletionToken>
    auto async_account_rate_limits_orders(const AccountRateLimitsOrdersParams& params,
                                          CompletionToken&& token) const {
        return account_api_.async_account_rate_limits_orders(params,
                                                             std::forward<CompletionToken>(token));
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
    account_status(const AccountStatusParams& params = {}) const {
        return account_api_.account_status(params);
    }
    template <class CompletionToken>
    auto async_account_status(const AccountStatusParams& params, CompletionToken&& token) const {
        return account_api_.async_account_status(params, std::forward<CompletionToken>(token));
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
    all_order_lists(const AllOrderListsParams& params = {}) const {
        return account_api_.all_order_lists(params);
    }
    template <class CompletionToken>
    auto async_all_order_lists(const AllOrderListsParams& params, CompletionToken&& token) const {
        return account_api_.async_all_order_lists(params, std::forward<CompletionToken>(token));
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
    all_orders(const AllOrdersParams& params) const {
        return account_api_.all_orders(params);
    }
    template <class CompletionToken>
    auto async_all_orders(const AllOrdersParams& params, CompletionToken&& token) const {
        return account_api_.async_all_orders(params, std::forward<CompletionToken>(token));
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
    my_allocations(const MyAllocationsParams& params) const {
        return account_api_.my_allocations(params);
    }
    template <class CompletionToken>
    auto async_my_allocations(const MyAllocationsParams& params, CompletionToken&& token) const {
        return account_api_.async_my_allocations(params, std::forward<CompletionToken>(token));
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
    my_filters(const MyFiltersParams& params) const {
        return account_api_.my_filters(params);
    }
    template <class CompletionToken>
    auto async_my_filters(const MyFiltersParams& params, CompletionToken&& token) const {
        return account_api_.async_my_filters(params, std::forward<CompletionToken>(token));
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
    my_prevented_matches(const MyPreventedMatchesParams& params) const {
        return account_api_.my_prevented_matches(params);
    }
    template <class CompletionToken>
    auto async_my_prevented_matches(const MyPreventedMatchesParams& params,
                                    CompletionToken&& token) const {
        return account_api_.async_my_prevented_matches(params,
                                                       std::forward<CompletionToken>(token));
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
    my_trades(const MyTradesParams& params) const {
        return account_api_.my_trades(params);
    }
    template <class CompletionToken>
    auto async_my_trades(const MyTradesParams& params, CompletionToken&& token) const {
        return account_api_.async_my_trades(params, std::forward<CompletionToken>(token));
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
    open_order_lists_status(const OpenOrderListsStatusParams& params = {}) const {
        return account_api_.open_order_lists_status(params);
    }
    template <class CompletionToken>
    auto async_open_order_lists_status(const OpenOrderListsStatusParams& params,
                                       CompletionToken&& token) const {
        return account_api_.async_open_order_lists_status(params,
                                                          std::forward<CompletionToken>(token));
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
    open_orders_status(const OpenOrdersStatusParams& params = {}) const {
        return account_api_.open_orders_status(params);
    }
    template <class CompletionToken>
    auto async_open_orders_status(const OpenOrdersStatusParams& params,
                                  CompletionToken&& token) const {
        return account_api_.async_open_orders_status(params, std::forward<CompletionToken>(token));
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
    order_amendments(const OrderAmendmentsParams& params) const {
        return account_api_.order_amendments(params);
    }
    template <class CompletionToken>
    auto async_order_amendments(const OrderAmendmentsParams& params,
                                CompletionToken&& token) const {
        return account_api_.async_order_amendments(params, std::forward<CompletionToken>(token));
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
    order_list_status(const OrderListStatusParams& params = {}) const {
        return account_api_.order_list_status(params);
    }
    template <class CompletionToken>
    auto async_order_list_status(const OrderListStatusParams& params,
                                 CompletionToken&& token) const {
        return account_api_.async_order_list_status(params, std::forward<CompletionToken>(token));
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
    order_status(const OrderStatusParams& params) const {
        return account_api_.order_status(params);
    }
    template <class CompletionToken>
    auto async_order_status(const OrderStatusParams& params, CompletionToken&& token) const {
        return account_api_.async_order_status(params, std::forward<CompletionToken>(token));
    }

    // AuthApi

    /// Log in with API key (USER_DATA)
    ///
    /// `session.logon`.
    ///
    /// Authenticate WebSocket connection using the provided API key.
    ///
    /// After calling `session.logon`, you can omit `apiKey` and `signature` parameters for future
    /// requests that require them.
    ///
    /// Note that only one API key can be authenticated.
    ///
    /// Calling `session.logon` multiple times changes the current authenticated API key.
    ///
    /// **Note:** Only Ed25519 keys are supported for this feature.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/auth#session-logon
    [[nodiscard]] std::vector<common::WebsocketApiResponse<SessionLogonResponseResult>>
    session_logon(const SessionLogonParams& params = {}) const {
        return auth_api_.session_logon(params);
    }
    template <class CompletionToken>
    auto async_session_logon(const SessionLogonParams& params, CompletionToken&& token) const {
        return auth_api_.async_session_logon(params, std::forward<CompletionToken>(token));
    }

    /// Log out of the session
    ///
    /// `session.logout`.
    ///
    /// Forget the API key previously authenticated. If the connection is not authenticated, this
    /// request does nothing.
    ///
    /// Note that the WebSocket connection stays open after `session.logout` request. You can
    /// continue using the connection, but now you will have to explicitly provide the `apiKey` and
    /// `signature` parameters where needed.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/auth#session-logout
    [[nodiscard]] std::vector<common::WebsocketApiResponse<SessionLogoutResponseResult>>
    session_logout(const SessionLogoutParams& params = {}) const {
        return auth_api_.session_logout(params);
    }
    template <class CompletionToken>
    auto async_session_logout(const SessionLogoutParams& params, CompletionToken&& token) const {
        return auth_api_.async_session_logout(params, std::forward<CompletionToken>(token));
    }

    /// Query session status
    ///
    /// `session.status`.
    ///
    /// Query the status of the WebSocket connection,
    /// inspecting which API key (if any) is used to authorize requests.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/auth#session-status
    [[nodiscard]] common::WebsocketApiResponse<SessionStatusResponseResult>
    session_status(const SessionStatusParams& params = {}) const {
        return auth_api_.session_status(params);
    }
    template <class CompletionToken>
    auto async_session_status(const SessionStatusParams& params, CompletionToken&& token) const {
        return auth_api_.async_session_status(params, std::forward<CompletionToken>(token));
    }

    // GeneralApi

    /// Exchange information
    ///
    /// `exchangeInfo`.
    ///
    /// Query current exchange trading rules, rate limits, and symbol
    /// information.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// **Notes:**
    /// * If the value provided to `symbol` or `symbols` do not exist, the endpoint will throw an
    /// error saying the symbol is invalid.
    /// * All parameters are optional.
    /// * Only one of `symbol`, `symbols`, `permissions` parameters can be specified.
    /// * Without parameters, `exchangeInfo` displays all symbols with `["SPOT", "MARGIN",
    /// "LEVERAGED"]` permissions.
    ///   * In order to list *all* active symbols on the exchange, you need to explicitly request
    ///   all permissions.
    /// * `permissions` accepts either a list of permissions, or a single permission name. E.g.
    /// `"SPOT"`.
    ///
    /// **Examples of Symbol Permissions Interpretation from the Response:**
    ///
    /// * `[["A","B"]]` means you may place an order if your account has either permission "A"
    /// **or** permission "B".
    /// * `[["A"],["B"]]` means you can place an order if your account has permission "A" **and**
    /// permission "B".
    /// * `[["A"],["B","C"]]` means you can place an order if your account has permission "A"
    /// **and** permission "B" or permission "C". (Inclusive or is applied here, not exclusive or,
    /// so your account may have both permission "B" and permission "C".)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/general#exchange-info
    [[nodiscard]] common::WebsocketApiResponse<ExchangeInfoResponse>
    exchange_info(const ExchangeInfoParams& params = {}) const {
        return general_api_.exchange_info(params);
    }
    template <class CompletionToken>
    auto async_exchange_info(const ExchangeInfoParams& params, CompletionToken&& token) const {
        return general_api_.async_exchange_info(params, std::forward<CompletionToken>(token));
    }

    /// Query Execution Rules
    ///
    /// `executionRules`.
    ///
    /// Query execution rules for symbols.
    ///
    /// Weight: Parameter | Weight
    /// --- | ---
    /// `symbol` | 2
    /// `symbols` | 2 for each `symbol`, capped at a max of 40
    /// `symbolStatus` | 40
    /// None | 40
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// **Note:** No combination of multiple parameters is allowed.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/general#execution-rules
    [[nodiscard]] common::WebsocketApiResponse<ExecutionRulesResponseResult>
    execution_rules(const ExecutionRulesParams& params = {}) const {
        return general_api_.execution_rules(params);
    }
    template <class CompletionToken>
    auto async_execution_rules(const ExecutionRulesParams& params, CompletionToken&& token) const {
        return general_api_.async_execution_rules(params, std::forward<CompletionToken>(token));
    }

    /// Test connectivity
    ///
    /// `ping`.
    ///
    /// Test connectivity to the WebSocket API.
    ///
    /// Note: You can use regular WebSocket ping frames to test connectivity as well, WebSocket API
    /// will respond with pong frames as soon as possible. ping request along with time is a safe
    /// way to test request-response handling in your application.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/general#ping
    [[nodiscard]] common::WebsocketApiResponse<boost::json::value>
    ping(const PingParams& params = {}) const {
        return general_api_.ping(params);
    }
    template <class CompletionToken>
    auto async_ping(const PingParams& params, CompletionToken&& token) const {
        return general_api_.async_ping(params, std::forward<CompletionToken>(token));
    }

    /// Check server time
    ///
    /// `time`.
    ///
    /// Test connectivity to the WebSocket API and get the current server time.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/general#time
    [[nodiscard]] common::WebsocketApiResponse<TimeResponseResult>
    time(const TimeParams& params = {}) const {
        return general_api_.time(params);
    }
    template <class CompletionToken>
    auto async_time(const TimeParams& params, CompletionToken&& token) const {
        return general_api_.async_time(params, std::forward<CompletionToken>(token));
    }

    // MarketApi

    /// Current average price
    ///
    /// `avgPrice`.
    ///
    /// Get current average price for a symbol.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#avg-price
    [[nodiscard]] common::WebsocketApiResponse<AvgPriceResponseResult>
    avg_price(const AvgPriceParams& params) const {
        return market_api_.avg_price(params);
    }
    template <class CompletionToken>
    auto async_avg_price(const AvgPriceParams& params, CompletionToken&& token) const {
        return market_api_.async_avg_price(params, std::forward<CompletionToken>(token));
    }

    /// Historical Block Trades
    ///
    /// `blockTrades.historical`.
    ///
    /// Get block trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#block-trades-historical
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<BlockTradesHistoricalResponseResultInner>>
    block_trades_historical(const BlockTradesHistoricalParams& params) const {
        return market_api_.block_trades_historical(params);
    }
    template <class CompletionToken>
    auto async_block_trades_historical(const BlockTradesHistoricalParams& params,
                                       CompletionToken&& token) const {
        return market_api_.async_block_trades_historical(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Order book
    ///
    /// `depth`.
    ///
    /// Get current order book.
    ///
    /// Note that this request returns limited market depth.
    ///
    /// If you need to continuously monitor order book updates, please consider using WebSocket
    /// Streams:
    ///   * `<symbol>@depth<levels>`
    ///   * `<symbol>@depth`
    ///
    /// You can use `depth` request together with `<symbol>@depth` streams to maintain a local order
    /// book.
    ///
    /// Weight: Adjusted based on the limit:
    ///
    /// |Limit|Request Weight
    /// ------|-------
    /// 1-100|  5
    /// 101-500| 25
    /// 501-1000| 50
    /// 1001-5000| 250
    /// 5001-7500| 500
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#depth
    [[nodiscard]] common::WebsocketApiResponse<DepthResponseResult>
    depth(const DepthParams& params) const {
        return market_api_.depth(params);
    }
    template <class CompletionToken>
    auto async_depth(const DepthParams& params, CompletionToken&& token) const {
        return market_api_.async_depth(params, std::forward<CompletionToken>(token));
    }

    /// Klines
    ///
    /// `klines`.
    ///
    /// Get klines (candlestick bars).
    ///
    /// Klines are uniquely identified by their open & close time.
    ///
    /// If you need access to real-time kline updates, please consider using WebSocket Streams:
    ///   * `<symbol>@kline_<interval>`
    ///
    /// If you need historical kline data, please consider using data.binance.vision.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Supported kline intervals (case-sensitive):
    ///
    /// Interval  | `interval` value
    /// --------- | ----------------
    /// seconds   | `1s`
    /// minutes   | `1m`, `3m`, `5m`, `15m`, `30m`
    /// hours     | `1h`, `2h`, `4h`, `6h`, `8h`, `12h`
    /// days      | `1d`, `3d`
    /// weeks     | `1w`
    /// months    | `1M`
    ///
    /// **Notes:**
    ///
    /// * If `startTime` and `endTime` are not sent, the most recent klines are returned.
    /// * Supported values for `timeZone`:
    ///   * Hours and minutes (e.g. `-1:00`, `05:45`)
    ///   * Only hours (e.g. `0`, `8`, `4`)
    ///   * Accepted range is strictly [-12:00 to +14:00] inclusive
    /// * If `timeZone` provided, kline intervals are interpreted in that timezone instead of UTC.
    /// * Note that `startTime` and `endTime` are always interpreted in UTC, regardless of
    /// `timeZone`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#klines
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<std::vector<KlinesResponseResultInnerInner>>>
    klines(const KlinesParams& params) const {
        return market_api_.klines(params);
    }
    template <class CompletionToken>
    auto async_klines(const KlinesParams& params, CompletionToken&& token) const {
        return market_api_.async_klines(params, std::forward<CompletionToken>(token));
    }

    /// Query Reference Price
    ///
    /// `referencePrice`.
    ///
    /// Query Reference Price
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// If the symbol has never had a reference price set, the request is rejected with:
    ///
    /// ```json
    /// {
    ///     "code": -2043,
    ///     "msg": "This symbol doesn't have a reference price."
    /// }
    /// ```
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#reference-price
    [[nodiscard]] common::WebsocketApiResponse<ReferencePriceResponseResult>
    reference_price(const ReferencePriceParams& params) const {
        return market_api_.reference_price(params);
    }
    template <class CompletionToken>
    auto async_reference_price(const ReferencePriceParams& params, CompletionToken&& token) const {
        return market_api_.async_reference_price(params, std::forward<CompletionToken>(token));
    }

    /// Query Reference Price Calculation
    ///
    /// `referencePrice.calculation`.
    ///
    /// Query Reference Price Calculation
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#reference-price-calculation
    [[nodiscard]] common::WebsocketApiResponse<ReferencePriceCalculationResponseResult>
    reference_price_calculation(const ReferencePriceCalculationParams& params) const {
        return market_api_.reference_price_calculation(params);
    }
    template <class CompletionToken>
    auto async_reference_price_calculation(const ReferencePriceCalculationParams& params,
                                           CompletionToken&& token) const {
        return market_api_.async_reference_price_calculation(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Rolling window price change statistics
    ///
    /// `ticker`.
    ///
    /// Get rolling window price change statistics with a custom window.
    ///
    /// This request is similar to `ticker.24hr` but statistics are computed on demand using the
    /// arbitrary window you specify.
    ///
    /// **Note:** Window size precision is limited to 1 minute.
    /// While the `closeTime` is the current time of the request, `openTime` always start on a
    /// minute boundary. As such, the effective window might be up to 59999 ms wider than the
    /// requested `windowSize`.
    ///
    /// **Window computation example**
    ///
    /// For example, a request for `"windowSize": "7d"` might result in the following window:
    ///
    /// ```json
    /// {
    ///     "openTime": 1659580020000,
    ///     "closeTime": 1660184865291
    /// }
    /// ```
    ///
    /// Time of the request – `closeTime` – is 1660184865291 (August 11, 2022 02:27:45.291).
    /// Requested window size should put the `openTime` 7 days before that – August 4, 02:27:45.291
    /// – but due to limited precision it ends up a bit earlier: 1659580020000 (August 4, 2022
    /// 02:27:00), exactly at the start of a minute.
    ///
    /// If you need to continuously monitor trading statistics, please consider using WebSocket
    /// Streams:
    ///   * `<symbol>@ticker_<window_size>` or `!ticker_<window-size>@arr`
    ///
    /// Weight: Adjusted based on the number of requested symbols:
    ///
    /// | Symbols | Weight |
    /// |:-------:|:------:|
    /// |    1–50 | 4 per symbol |
    /// |  51–100 |    200 |
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Supported window sizes:
    ///
    /// Unit    | `windowSize` value
    /// ------- | ------------------
    /// minutes | `1m`, `2m` ... `59m`
    /// hours   | `1h`, `2h` ... `23h`
    /// days    | `1d`, `2d` ... `7d`
    ///
    /// Notes:
    ///
    /// * Either `symbol` or `symbols` must be specified.
    ///
    /// * Maximum number of symbols in one request: 200.
    ///
    /// * Window size units cannot be combined.
    ///   E.g., `1d 2h` is not supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker
    [[nodiscard]] common::WebsocketApiResponse<std::variant<
        TickerResponse1Result, std::vector<TickerResponse2ResultInner>, boost::json::value>>
    ticker(const TickerParams& params = {}) const {
        return market_api_.ticker(params);
    }
    template <class CompletionToken>
    auto async_ticker(const TickerParams& params, CompletionToken&& token) const {
        return market_api_.async_ticker(params, std::forward<CompletionToken>(token));
    }

    /// 24hr ticker price change statistics
    ///
    /// `ticker.24hr`.
    ///
    /// Get 24-hour rolling window price change statistics.
    ///
    /// If you need to continuously monitor trading statistics, please consider using WebSocket
    /// Streams:
    ///
    /// * `<symbol>@ticker` or `!ticker@arr`
    ///
    /// * `<symbol>@miniTicker` or `!miniTicker@arr`
    ///
    /// If you need different window sizes,
    ///
    /// use the `ticker` request.
    ///
    /// Weight: Adjusted based on the number of requested symbols:
    ///
    /// |Parameter|Symbols Provided|Weight|
    /// |---|---|---|
    /// |symbol| 1 |2|
    /// | |omitted| 80|
    /// |symbols| 1-20 |2|
    /// | | 21-100 |40|
    /// | | 101+ |80|
    /// | |omitted| 80|
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// Notes:
    ///
    /// * `symbol` and `symbols` cannot be used together.
    ///
    /// * If no symbol is specified, returns information about all symbols currently trading on the
    /// exchange.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker24hr
    [[nodiscard]] common::WebsocketApiResponse<std::variant<
        Ticker24hrResponse1Result, std::vector<Ticker24hrResponse2ResultInner>, boost::json::value>>
    ticker24hr(const Ticker24hrParams& params = {}) const {
        return market_api_.ticker24hr(params);
    }
    template <class CompletionToken>
    auto async_ticker24hr(const Ticker24hrParams& params, CompletionToken&& token) const {
        return market_api_.async_ticker24hr(params, std::forward<CompletionToken>(token));
    }

    /// Symbol order book ticker
    ///
    /// `ticker.book`.
    ///
    /// Get the current best price and quantity on the order book.
    ///
    /// If you need access to real-time order book ticker updates, please
    /// consider using WebSocket Streams:
    ///
    /// * `<symbol>@bookTicker`
    ///
    /// Weight: Adjusted based on the number of requested symbols:
    ///
    /// |Parameter|Symbols Provided|Weight|
    /// |---|---|---|
    /// |symbol| 1 |2|
    /// | |omitted| 4|
    /// |symbols| Any |4|
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// Notes:
    ///
    /// * `symbol` and `symbols` cannot be used together.
    ///
    /// * If no symbol is specified, returns information about all symbols currently trading on the
    /// exchange.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker-book
    [[nodiscard]] common::WebsocketApiResponse<std::variant<
        TickerBookResponse1Result, std::vector<TickerBookResponse2ResultInner>, boost::json::value>>
    ticker_book(const TickerBookParams& params = {}) const {
        return market_api_.ticker_book(params);
    }
    template <class CompletionToken>
    auto async_ticker_book(const TickerBookParams& params, CompletionToken&& token) const {
        return market_api_.async_ticker_book(params, std::forward<CompletionToken>(token));
    }

    /// Symbol price ticker
    ///
    /// `ticker.price`.
    ///
    /// Get the latest market price for a symbol.
    ///
    /// If you need access to real-time price updates, please consider using
    /// WebSocket Streams:
    ///
    /// * `<symbol>@aggTrade`
    ///
    /// * `<symbol>@trade`
    ///
    /// Weight: Adjusted based on the number of requested symbols:
    ///
    /// |Parameter|Symbols Provided|Weight|
    /// |---|---|---|
    /// |symbol| 1 |2|
    /// | |omitted| 4|
    /// |symbols| Any |4|
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// Notes:
    ///
    /// * `symbol` and `symbols` cannot be used together.
    ///
    /// * If no symbol is specified, returns information about all symbols currently trading on the
    /// exchange.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker-price
    [[nodiscard]] common::WebsocketApiResponse<
        std::variant<TickerPriceResponse1Result, std::vector<TickerPriceResponse2ResultInner>,
                     boost::json::value>>
    ticker_price(const TickerPriceParams& params = {}) const {
        return market_api_.ticker_price(params);
    }
    template <class CompletionToken>
    auto async_ticker_price(const TickerPriceParams& params, CompletionToken&& token) const {
        return market_api_.async_ticker_price(params, std::forward<CompletionToken>(token));
    }

    /// Trading Day Ticker
    ///
    /// `ticker.tradingDay`.
    ///
    /// Price change statistics for a trading day.
    ///
    /// Weight: 4 for each requested symbol regardless of windowSize. The weight for this request
    /// will cap at 200 once the number of symbols in the request is more than 50.
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// **Notes:**
    ///
    /// * Supported values for `timeZone`:
    ///   * Hours and minutes (e.g. `-1:00`, `05:45`)
    ///   * Only hours (e.g. `0`, `8`, `4`)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker-trading-day
    [[nodiscard]] common::WebsocketApiResponse<
        std::variant<TickerTradingDayResponse1Result,
                     std::vector<TickerTradingDayResponse2ResultInner>, boost::json::value>>
    ticker_trading_day(const TickerTradingDayParams& params = {}) const {
        return market_api_.ticker_trading_day(params);
    }
    template <class CompletionToken>
    auto async_ticker_trading_day(const TickerTradingDayParams& params,
                                  CompletionToken&& token) const {
        return market_api_.async_ticker_trading_day(params, std::forward<CompletionToken>(token));
    }

    /// Aggregate trades
    ///
    /// `trades.aggregate`.
    ///
    /// Get aggregate trades.
    ///
    /// An *aggregate trade* (aggtrade) represents one or more individual
    /// trades.
    ///
    /// Trades that fill at the same time, from the same taker order, with the
    /// same price –
    ///
    /// those trades are collected into an aggregate trade with total quantity
    /// of the individual trades.
    ///
    /// If you need access to real-time trading activity, please consider using
    /// WebSocket Streams:
    ///
    /// * `<symbol>@aggTrade`
    ///
    /// If you need historical aggregate trade data, please consider using data.binance.vision.
    ///
    /// Weight(IP): 4
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// - If `fromId` is specified, return aggtrades with aggregate trade ID >= `fromId`. Use
    /// `fromId` and `limit` to page through all aggtrades.
    /// - If `startTime` and/or `endTime` are specified, aggtrades are filtered by execution time
    /// (`T`). `fromId` cannot be used together with `startTime` and `endTime`.
    /// - If no condition is specified, the most recent aggregate trades are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#trades-aggregate
    [[nodiscard]] common::WebsocketApiResponse<std::vector<TradesAggregateResponseResultInner>>
    trades_aggregate(const TradesAggregateParams& params) const {
        return market_api_.trades_aggregate(params);
    }
    template <class CompletionToken>
    auto async_trades_aggregate(const TradesAggregateParams& params,
                                CompletionToken&& token) const {
        return market_api_.async_trades_aggregate(params, std::forward<CompletionToken>(token));
    }

    /// Historical trades
    ///
    /// `trades.historical`.
    ///
    /// Get historical trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Notes:
    ///
    /// * If `fromId` is not specified, the most recent trades are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#trades-historical
    [[nodiscard]] common::WebsocketApiResponse<std::vector<TradesHistoricalResponseResultInner>>
    trades_historical(const TradesHistoricalParams& params) const {
        return market_api_.trades_historical(params);
    }
    template <class CompletionToken>
    auto async_trades_historical(const TradesHistoricalParams& params,
                                 CompletionToken&& token) const {
        return market_api_.async_trades_historical(params, std::forward<CompletionToken>(token));
    }

    /// Recent trades
    ///
    /// `trades.recent`.
    ///
    /// Get recent trades.
    ///
    /// If you need access to real-time trading activity, please consider using
    /// WebSocket Streams:
    ///
    /// * `<symbol>@trade`
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#trades-recent
    [[nodiscard]] common::WebsocketApiResponse<std::vector<TradesRecentResponseResultInner>>
    trades_recent(const TradesRecentParams& params) const {
        return market_api_.trades_recent(params);
    }
    template <class CompletionToken>
    auto async_trades_recent(const TradesRecentParams& params, CompletionToken&& token) const {
        return market_api_.async_trades_recent(params, std::forward<CompletionToken>(token));
    }

    /// UI Klines
    ///
    /// `uiKlines`.
    ///
    /// Get klines (candlestick bars) optimized for presentation.
    ///
    /// This request is similar to `klines`, having the same parameters and response. `uiKlines`
    /// return modified kline data, optimized for presentation of candlestick charts.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// - If `startTime` and `endTime` are not sent, the most recent klines are returned.
    /// - Supported values for `timeZone`:
    ///   - Hours and minutes (e.g. `-1:00`, `05:45`)
    ///   - Only hours (e.g. `0`, `8`, `4`)
    ///   - Accepted range is strictly [-12:00 to +14:00] inclusive
    /// - If `timeZone` provided, kline intervals are interpreted in that timezone instead of UTC.
    /// - Note that `startTime` and `endTime` are always interpreted in UTC, regardless of
    /// `timeZone`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ui-klines
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<std::vector<KlinesResponseResultInnerInner>>>
    ui_klines(const UiKlinesParams& params) const {
        return market_api_.ui_klines(params);
    }
    template <class CompletionToken>
    auto async_ui_klines(const UiKlinesParams& params, CompletionToken&& token) const {
        return market_api_.async_ui_klines(params, std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// Cancel open orders (TRADE)
    ///
    /// `openOrders.cancelAll`.
    ///
    /// Cancel all open orders on a symbol.
    /// This includes orders that are part of an order list.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#open-orders-cancel-all
    [[nodiscard]] common::WebsocketApiResponse<std::vector<OpenOrdersCancelAllResponseResultInner>>
    open_orders_cancel_all(const OpenOrdersCancelAllParams& params) const {
        return trade_api_.open_orders_cancel_all(params);
    }
    template <class CompletionToken>
    auto async_open_orders_cancel_all(const OpenOrdersCancelAllParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_open_orders_cancel_all(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Order Amend Keep Priority (TRADE)
    ///
    /// `order.amend.keepPriority`.
    ///
    /// Reduce the quantity of an existing open order.
    ///
    /// This adds 0 orders to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter.
    ///
    /// Read Order Amend Keep Priority FAQ to learn more.
    ///
    /// Weight(IP): 4
    ///
    /// Unfilled Order Count: 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-amend-keep-priority
    [[nodiscard]] common::WebsocketApiResponse<OrderAmendKeepPriorityResponseResult>
    order_amend_keep_priority(const OrderAmendKeepPriorityParams& params) const {
        return trade_api_.order_amend_keep_priority(params);
    }
    template <class CompletionToken>
    auto async_order_amend_keep_priority(const OrderAmendKeepPriorityParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_order_amend_keep_priority(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Cancel order (TRADE)
    ///
    /// `order.cancel`.
    ///
    /// Cancel an active order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Notes:
    ///
    /// * If both `orderId` and `origClientOrderId` parameters are provided, the `orderId` is
    /// searched first, then the `origClientOrderId` from that result is checked against that order.
    /// If both conditions are not met the request will be rejected.
    ///
    /// * `newClientOrderId` will replace `clientOrderId` of the canceled order, freeing it up for
    /// new orders.
    ///
    /// * If you cancel an order that is a part of an order list, the entire order list is canceled.
    ///
    /// * The performance for canceling an order (single cancel or as part of a cancel-replace) is
    /// always better when only `orderId` is sent. Sending `origClientOrderId` or both `orderId` +
    /// `origClientOrderId` will be slower.
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// **Regarding `cancelRestrictions`**
    ///
    /// * If the `cancelRestrictions` value is not any of the supported values, the error will be:
    /// ```json
    /// {
    ///     "code": -1145,
    ///     "msg": "Invalid cancelRestrictions"
    /// }
    /// ```
    /// * If the order did not pass the conditions for `cancelRestrictions`, the error will be:
    /// ```json
    /// {
    ///     "code": -2011,
    ///     "msg": "Order was not canceled due to cancel restrictions."
    /// }
    /// ```
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-cancel
    [[nodiscard]] common::WebsocketApiResponse<OrderCancelResponseResult>
    order_cancel(const OrderCancelParams& params) const {
        return trade_api_.order_cancel(params);
    }
    template <class CompletionToken>
    auto async_order_cancel(const OrderCancelParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_cancel(params, std::forward<CompletionToken>(token));
    }

    /// Cancel and replace order (TRADE)
    ///
    /// `order.cancelReplace`.
    ///
    /// * Cancel an existing order and immediately place a new order instead of the canceled one.
    /// * A new order that was not attempted (i.e. when `newOrderResult: NOT_ATTEMPTED`), will still
    /// increase the unfilled order count by 1.
    /// * You can only cancel an individual order from an orderList using this method, but the
    /// result is the same as canceling the entire orderList.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Similar to the `order.place` request,
    /// additional mandatory parameters (*) are determined by the new order `type`.
    ///
    /// Available `cancelReplaceMode` options:
    ///
    /// * `STOP_ON_FAILURE` – if cancellation request fails, new order placement will not be
    /// attempted.
    /// * `ALLOW_FAILURE` – new order placement will be attempted even if the cancel request fails.
    ///
    /// - Request | Response
    /// - `cancelReplaceMode` | `orderRateLimitExceededMode` | Unfilled Order Count | `cancelResult`
    /// | `newOrderResult` | `status`
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Within Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Within Limits | ❌ `FAILURE` | ➖ `NOT_ATTEMPTED` |
    /// `400`
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Within Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Exceeds Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | N/A
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Exceeds Limits | ❌ `FAILURE` | ➖ `NOT_ATTEMPTED` |
    /// N/A
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | N/A
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Within Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Within Limits | ❌ `FAILURE` | ➖ `NOT_ATTEMPTED` |
    /// `400`
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Within Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ➖ `NOT_ATTEMPTED` |
    /// `429`
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `429`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Within Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Within Limits | ❌ `FAILURE` | ❌ `FAILURE` | `400`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Within Limits | ❌ `FAILURE` | ✅ `SUCCESS` | `409`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Within Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Exceeds Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | N/A
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Exceeds Limits | ❌ `FAILURE` | ❌ `FAILURE` | N/A
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Exceeds Limits | ❌ `FAILURE` | ✅ `SUCCESS` | N/A
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | N/A
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Within Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Within Limits | ❌ `FAILURE` | ❌ `FAILURE` | `400`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Within Limits | ❌ `FAILURE` | ✅ `SUCCESS` | `409`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Within Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ❌ `FAILURE` | `400`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ✅ `SUCCESS` | N/A
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    ///
    /// Notes:
    ///
    /// * If both `cancelOrderId` and `cancelOrigClientOrderId` parameters are provided, the
    /// `cancelOrderId` is searched first, then the `cancelOrigClientOrderId` from that result is
    /// checked against that order. If both conditions are not met the request will be rejected.
    ///
    /// * `cancelNewClientOrderId` will replace `clientOrderId` of the canceled order, freeing it up
    /// for new orders.
    ///
    /// * `newClientOrderId` specifies `clientOrderId` value for the placed order.
    ///
    ///   A new order with the same `clientOrderId` is accepted only when the previous one is filled
    ///   or expired.
    ///
    ///   The new order can reuse old `clientOrderId` of the canceled order.
    ///
    /// * This cancel-replace operation is **not transactional**.
    ///
    ///   If one operation succeeds but the other one fails, the successful operation is still
    ///   executed.
    ///
    ///   For example, in `STOP_ON_FAILURE` mode, if the new order placement fails, the old order is
    ///   still canceled.
    ///
    /// * Filters and order count limits are evaluated before cancellation and order placement
    /// occurs.
    ///
    /// * If new order placement is not attempted, your order count is still incremented.
    ///
    /// * Like `order.cancel`, if you cancel an individual order from an order list, the entire
    /// order list is canceled.
    ///
    /// * The performance for canceling an order (single cancel or as part of a cancel-replace) is
    /// always better when only `orderId` is sent. Sending `origClientOrderId` or both `orderId` +
    /// `origClientOrderId` will be slower.
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-cancel-replace
    [[nodiscard]] common::WebsocketApiResponse<OrderCancelReplaceResponseResult>
    order_cancel_replace(const OrderCancelReplaceParams& params) const {
        return trade_api_.order_cancel_replace(params);
    }
    template <class CompletionToken>
    auto async_order_cancel_replace(const OrderCancelReplaceParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_order_cancel_replace(params, std::forward<CompletionToken>(token));
    }

    /// Cancel Order list (TRADE)
    ///
    /// `orderList.cancel`.
    ///
    /// Cancel an active order list.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Notes:
    ///
    /// * If both `orderListId` and `listClientOrderId` parameters are provided, the `orderListId`
    /// is searched first, then the `listClientOrderId` from that result is checked against that
    /// order. If both conditions are not met the request will be rejected.
    ///
    /// * Canceling an individual order with `order.cancel` will cancel the entire order list as
    /// well.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-cancel
    [[nodiscard]] common::WebsocketApiResponse<OrderListCancelResponseResult>
    order_list_cancel(const OrderListCancelParams& params) const {
        return trade_api_.order_list_cancel(params);
    }
    template <class CompletionToken>
    auto async_order_list_cancel(const OrderListCancelParams& params,
                                 CompletionToken&& token) const {
        return trade_api_.async_order_list_cancel(params, std::forward<CompletionToken>(token));
    }

    /// Place new OCO - Deprecated (TRADE)
    ///
    /// `orderList.place`.
    ///
    /// Send in a new one-cancels-the-other (OCO) pair:
    /// `LIMIT_MAKER` + `STOP_LOSS`/`STOP_LOSS_LIMIT` orders (called *legs*),
    /// where activation of one order immediately cancels the other.
    ///
    /// This adds 1 order to `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Notes:
    ///
    /// * `listClientOrderId` parameter specifies `listClientOrderId` for the OCO pair.
    ///
    ///   A new OCO with the same `listClientOrderId` is accepted only when the previous one is
    ///   filled or completely expired.
    ///
    ///   `listClientOrderId` is distinct from `clientOrderId` of individual orders.
    ///
    /// * `limitClientOrderId` and `stopClientOrderId` specify `clientOrderId` values for both legs
    /// of the OCO.
    ///
    ///   A new order with the same `clientOrderId` is accepted only when the previous one is filled
    ///   or expired.
    ///
    /// * Price restrictions on the legs:
    ///
    ///   | `side` | Price relation |
    ///   | ------ | -------------- |
    ///   | `BUY`  | `price` < market price < `stopPrice` |
    ///   | `SELL` | `price` > market price > `stopPrice` |
    ///
    /// * Both legs have the same `quantity`.
    ///
    ///   However, you can set different iceberg quantity for individual legs.
    ///
    ///   If `stopIcebergQty` is used, `stopLimitTimeInForce` must be `GTC`.
    ///
    /// * `trailingDelta` applies only to the `STOP_LOSS`/`STOP_LOSS_LIMIT` leg of the OCO.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place
    ///
    /// Deprecated: this endpoint may be removed in a future version.
    [[deprecated("This endpoint may be removed in a future version.")]]
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceResponseResult>
    order_list_place(const OrderListPlaceParams& params) const {
        return trade_api_.order_list_place(params);
    }
    template <class CompletionToken>
    [[deprecated("This endpoint may be removed in a future version.")]] auto
    async_order_list_place(const OrderListPlaceParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_list_place(params, std::forward<CompletionToken>(token));
    }

    /// Place new Order list - OCO (TRADE)
    ///
    /// `orderList.place.oco`.
    ///
    /// Send in an one-cancels-the-other (OCO) pair, where activation of one order immediately
    /// cancels the other.
    ///
    /// * An OCO has 2 orders called the **above order** and **below order**.
    ///
    /// * One of the orders must be a `LIMIT_MAKER/TAKE_PROFIT/TAKE_PROFIT_LIMIT` order and the
    /// other must be `STOP_LOSS` or `STOP_LOSS_LIMIT` order.
    ///
    /// * Price restrictions:
    ///   * If the OCO is on the `SELL` side:
    ///     * `LIMIT_MAKER/TAKE_PROFIT_LIMIT` `price` > Last Traded Price >
    ///     `STOP_LOSS/STOP_LOSS_LIMIT`
    /// `stopPrice`
    ///     * `TAKE_PROFIT stopPrice` > Last Traded Price > `STOP_LOSS/STOP_LOSS_LIMIT
    /// stopPrice`
    ///   * If the OCO is on the `BUY` side:
    ///     * `LIMIT_MAKER` `price` < Last Traded Price < `STOP_LOSS/STOP_LOSS_LIMIT` `stopPrice`
    ///     * `TAKE_PROFIT stopPrice` > Last Traded Price > `STOP_LOSS/STOP_LOSS_LIMIT stopPrice`
    /// *  OCOs add **2 orders** to the `EXCHANGE_MAX_ORDERS` filter and `MAX_NUM_ORDERS` filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-oco
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOcoResponseResult>
    order_list_place_oco(const OrderListPlaceOcoParams& params) const {
        return trade_api_.order_list_place_oco(params);
    }
    template <class CompletionToken>
    auto async_order_list_place_oco(const OrderListPlaceOcoParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_order_list_place_oco(params, std::forward<CompletionToken>(token));
    }

    /// OPO (TRADE)
    ///
    /// `orderList.place.opo`.
    ///
    /// Place an OPO.
    ///
    /// * The working order must be `LIMIT` or `LIMIT_MAKER`.
    /// * OPOs add 2 orders to the EXCHANGE_MAX_NUM_ORDERS filter and MAX_NUM_ORDERS filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-opo
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOpoResponseResult>
    order_list_place_opo(const OrderListPlaceOpoParams& params) const {
        return trade_api_.order_list_place_opo(params);
    }
    template <class CompletionToken>
    auto async_order_list_place_opo(const OrderListPlaceOpoParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_order_list_place_opo(params, std::forward<CompletionToken>(token));
    }

    /// OPOCO (TRADE)
    ///
    /// `orderList.place.opoco`.
    ///
    /// Place an OPOCO.
    ///
    /// * The working order must be `LIMIT` or `LIMIT_MAKER`.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 3
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-opoco
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOpocoResponseResult>
    order_list_place_opoco(const OrderListPlaceOpocoParams& params) const {
        return trade_api_.order_list_place_opoco(params);
    }
    template <class CompletionToken>
    auto async_order_list_place_opoco(const OrderListPlaceOpocoParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_order_list_place_opoco(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Place new Order list - OTO (TRADE)
    ///
    /// `orderList.place.oto`.
    ///
    /// Places an OTO.
    ///
    /// * An OTO (One-Triggers-the-Other) is an order list comprised of 2 orders.
    ///
    /// * The first order is called the **working order** and must be `LIMIT` or `LIMIT_MAKER`.
    /// Initially, only the working order goes on the order book.
    ///
    /// * The second order is called the **pending order**. It can be any order type except for
    /// `MARKET` orders using parameter `quoteOrderQty`. The pending order is only placed on the
    /// order book when the working order gets
    /// **fully filled**.
    ///
    /// * If either the working order or the pending order is cancelled individually, the other
    /// order in the order list will also be canceled or expired.
    ///
    /// * When the order list is placed, if the working order gets **immediately fully filled**, the
    /// placement response will show the working order as `FILLED` but the pending order will still
    /// appear as `PENDING_NEW`. You need to query the status of the pending order again to see its
    /// updated status.
    ///
    /// * OTOs add **2 orders** to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS` filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// **Mandatory parameters based on `pendingType` or `workingType`**
    ///
    /// Depending on the `pendingType` or `workingType`, some optional parameters will become
    /// mandatory.
    ///
    /// |Type                                                  |Additional mandatory
    /// parameters|Additional information|
    /// |----                                                  |---- |------
    /// |`workingType` = `LIMIT`                               |`workingTimeInForce`           |
    /// |`pendingType` = `LIMIT`                                |`pendingPrice`,
    /// `pendingTimeInForce`          |
    /// |`pendingType` = `STOP_LOSS` or `TAKE_PROFIT`           |`pendingStopPrice` and/or
    /// `pendingTrailingDelta`|
    /// |`pendingType` =`STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT`|`pendingPrice`, `pendingStopPrice`
    /// and/or `pendingTrailingDelta`, `pendingTimeInForce`|
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-oto
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOtoResponseResult>
    order_list_place_oto(const OrderListPlaceOtoParams& params) const {
        return trade_api_.order_list_place_oto(params);
    }
    template <class CompletionToken>
    auto async_order_list_place_oto(const OrderListPlaceOtoParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_order_list_place_oto(params, std::forward<CompletionToken>(token));
    }

    /// Place new Order list - OTOCO (TRADE)
    ///
    /// `orderList.place.otoco`.
    ///
    /// Place an OTOCO.
    ///
    /// * An OTOCO (One-Triggers-One-Cancels-the-Other) is an order list comprised of 3 orders.
    /// * The first order is called the **working order** and must be `LIMIT` or `LIMIT_MAKER`.
    /// Initially, only the working order goes on the order book.
    ///   * The behavior of the working order is the same as the OTO.
    /// * OTOCO has 2 pending orders (pending above and pending below), forming an OCO pair. The
    /// pending orders are only placed on the order book when the working order gets **fully
    /// filled**.
    ///   * The rules of the pending above and pending below follow the same rules as the Order list
    ///   OCO.
    /// * OTOCOs add **3 orders** to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS`
    /// filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 3
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// **Mandatory parameters based on `pendingAboveType`, `pendingBelowType` or `workingType`**
    ///
    /// Depending on the `pendingAboveType`/`pendingBelowType` or `workingType`, some optional
    /// parameters will become mandatory.
    ///
    /// |Type                                                       |Additional mandatory
    /// parameters|Additional information|
    /// |----                                                       |---- |------
    /// |`workingType` = `LIMIT`                                    |`workingTimeInForce` |
    /// |`pendingAboveType`= `LIMIT_MAKER`                                |`pendingAbovePrice` |
    /// |`pendingAboveType` = `STOP_LOSS/TAKE_PROFIT`         |`pendingAboveStopPrice` and/or
    /// `pendingAboveTrailingDelta`|
    /// |`pendingAboveType=STOP_LOSS_LIMIT/TAKE_PROFIT_LIMIT`|`pendingAbovePrice`,
    /// `pendingAboveStopPrice` and/or `pendingAboveTrailingDelta`, `pendingAboveTimeInForce`|
    /// |`pendingBelowType`= `LIMIT_MAKER`                                |`pendingBelowPrice` |
    /// `pendingBelowType= STOP_LOSS/TAKE_PROFIT`         |`pendingBelowStopPrice` and/or
    /// `pendingBelowTrailingDelta`|
    /// |`pendingBelowType=STOP_LOSS_LIMIT/TAKE_PROFIT_LIMIT`|`pendingBelowPrice`,
    /// `pendingBelowStopPrice` and/or `pendingBelowTrailingDelta`, `pendingBelowTimeInForce`|
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-otoco
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOtocoResponseResult>
    order_list_place_otoco(const OrderListPlaceOtocoParams& params) const {
        return trade_api_.order_list_place_otoco(params);
    }
    template <class CompletionToken>
    auto async_order_list_place_otoco(const OrderListPlaceOtocoParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_order_list_place_otoco(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Place new order (TRADE)
    ///
    /// `order.place`.
    ///
    /// Send in a new order.
    ///
    /// This adds 1 order to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Certain parameters (*) become mandatory based on the order `type`:
    ///
    /// - Order `type` | Mandatory parameters
    /// - `LIMIT` |
    /// ,
    /// - `timeInForce`,
    /// - `price`,
    /// - `quantity`,
    ///
    /// - `LIMIT_MAKER` |
    /// ,
    /// - `price`,
    /// - `quantity`,
    ///
    /// - `MARKET` |
    /// ,
    /// - `quantity` or `quoteOrderQty`,
    ///
    /// - `STOP_LOSS` |
    /// ,
    /// - `quantity`,
    /// - `stopPrice` or `trailingDelta`,
    ///
    /// - `STOP_LOSS_LIMIT` |
    /// ,
    /// - `timeInForce`,
    /// - `price`,
    /// - `quantity`,
    /// - `stopPrice` or `trailingDelta`,
    ///
    /// - `TAKE_PROFIT` |
    /// ,
    /// - `quantity`,
    /// - `stopPrice` or `trailingDelta`,
    ///
    /// - `TAKE_PROFIT_LIMIT` |
    /// ,
    /// - `timeInForce`,
    /// - `price`,
    /// - `quantity`,
    /// - `stopPrice` or `trailingDelta`,
    ///
    /// Supported order types:
    ///
    /// - Order `type` | Description
    /// - `LIMIT` |
    ///
    /// , Buy or sell `quantity` at the specified `price` or better.,
    ///
    /// - `LIMIT_MAKER` |
    ///
    /// , `LIMIT` order that will be rejected if it immediately matches and trades as a taker.,
    ///
    /// ,
    ///
    /// , This order type is also known as a POST-ONLY order.,
    ///
    /// - `MARKET` |
    ///
    /// , Buy or sell at the best available market price.,
    ///
    /// ,
    /// ,
    /// - ,
    ///
    /// , `MARKET` order with `quantity` parameter, specifies the amount of the *base asset* you
    /// want to buy or sell., Actually executed quantity of the quote asset will be determined by
    /// available market liquidity.,
    ///
    /// ,
    ///
    /// , E.g., a MARKET BUY order on BTCUSDT for `"quantity": "0.1000"`, specifies that you want to
    /// buy 0.1 BTC at the best available price., If there is not enough BTC at the best price, keep
    /// buying at the next best price,, until either your order is filled, or you run out of USDT,
    /// or market runs out of BTC.,
    ///
    /// , ,
    /// - ,
    ///
    /// , `MARKET` order with `quoteOrderQty` parameter, specifies the amount of the *quote asset*
    /// you want to spend (when buying) or receive (when selling)., Actually executed quantity of
    /// the base asset will be determined by available market liquidity.,
    ///
    /// ,
    ///
    /// , E.g., a MARKET BUY on BTCUSDT for `"quoteOrderQty": "100.00"`, specifies that you want to
    /// buy as much BTC as you can for 100 USDT at the best available price., Similarly, a SELL
    /// order will sell as much available BTC as needed for you to receive 100 USDT, (before
    /// commission).,
    ///
    /// , ,
    ///
    /// - `STOP_LOSS` |
    ///
    /// , Execute a `MARKET` order for given `quantity` when specified conditions are met.,
    ///
    /// ,
    ///
    /// , I.e., when `stopPrice` is reached, or when `trailingDelta` is activated.,
    ///
    /// - `STOP_LOSS_LIMIT` |
    ///
    /// , Place a `LIMIT` order with given parameters when specified conditions are met.,
    ///
    /// - `TAKE_PROFIT` |
    ///
    /// , Like `STOP_LOSS` but activates when market price moves in the favorable direction.,
    ///
    /// - `TAKE_PROFIT_LIMIT` |
    ///
    /// , Like `STOP_LOSS_LIMIT` but activates when market price moves in the favorable direction.,
    ///
    /// Notes on using parameters for Pegged Orders:
    ///
    /// * These parameters are allowed for `LIMIT`, `LIMIT_MAKER`, `STOP_LOSS_LIMIT`,
    /// `TAKE_PROFIT_LIMIT` orders.
    /// * If `pegPriceType` is specified, `price` becomes optional. Otherwise, it is still
    /// mandatory.
    /// * `pegPriceType=PRIMARY_PEG` means the primary peg, that is the best price on the same side
    /// of the order book as your order.
    /// * `pegPriceType=MARKET_PEG` means the market peg, that is the best price on the opposite
    /// side of the order book from your order.
    /// * Use `pegOffsetType` and `pegOffsetValue` to request a price level other than the best one.
    /// These parameters must be specified together.
    ///
    /// Available `timeInForce` options,
    /// setting how long the order should be active before expiration:
    ///
    /// TIF  | Description
    /// ----- | --------------
    /// `GTC` | **Good 'til Canceled** – the order will remain on the book until you cancel it, or
    /// the order is completely filled. `IOC` | **Immediate or Cancel** – the order will be filled
    /// for as much as possible, the unfilled quantity immediately expires. `FOK` | **Fill or Kill**
    /// – the order will expire unless it cannot be immediately filled for the entire quantity.
    ///
    /// Notes:
    ///
    /// * `newClientOrderId` specifies `clientOrderId` value for the order.
    ///
    ///   A new order with the same `clientOrderId` is accepted only when the previous one is filled
    ///   or expired.
    ///
    /// * Any `LIMIT` or `LIMIT_MAKER` order can be made into an iceberg order by specifying the
    /// `icebergQty`.
    ///
    ///   An order with an `icebergQty` must have `timeInForce` set to `GTC`.
    ///
    /// * Trigger order price rules for `STOP_LOSS`/`TAKE_PROFIT` orders:
    ///
    ///   * `stopPrice` must be above market price: `STOP_LOSS BUY`, `TAKE_PROFIT SELL`
    ///   * `stopPrice` must be below market price: `STOP_LOSS SELL`, `TAKE_PROFIT BUY`
    ///
    /// * `MARKET` orders using `quoteOrderQty` follow `LOT_SIZE` filter rules.
    ///
    ///   The order will execute a quantity that has notional value as close as possible to
    ///   requested `quoteOrderQty`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-place
    [[nodiscard]] common::WebsocketApiResponse<OrderPlaceResponseResult>
    order_place(const OrderPlaceParams& params) const {
        return trade_api_.order_place(params);
    }
    template <class CompletionToken>
    auto async_order_place(const OrderPlaceParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_place(params, std::forward<CompletionToken>(token));
    }

    /// Test new order (TRADE)
    ///
    /// `order.test`.
    ///
    /// Test order placement.
    ///
    /// Validates new order parameters and verifies your signature
    /// but does not send the order into the matching engine.
    ///
    /// Weight: | Condition | Request Weight |
    /// | --- | --- |
    /// | Without `computeCommissionRates` | 1 |
    /// | With `computeCommissionRates` | 20 |
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-test
    [[nodiscard]] common::WebsocketApiResponse<OrderTestResponseResult>
    order_test(const OrderTestParams& params) const {
        return trade_api_.order_test(params);
    }
    template <class CompletionToken>
    auto async_order_test(const OrderTestParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_test(params, std::forward<CompletionToken>(token));
    }

    /// Place new order using SOR (TRADE)
    ///
    /// `sor.order.place`.
    ///
    /// Places an order using smart order routing (SOR).
    ///
    /// This adds 1 order to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter.
    ///
    /// Read SOR FAQ to learn more.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// **Note:** `sor.order.place` only supports `LIMIT` and `MARKET` orders. `quoteOrderQty` is
    /// not supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#sor-order-place
    [[nodiscard]] common::WebsocketApiResponse<std::vector<SorOrderPlaceResponseResultInner>>
    sor_order_place(const SorOrderPlaceParams& params) const {
        return trade_api_.sor_order_place(params);
    }
    template <class CompletionToken>
    auto async_sor_order_place(const SorOrderPlaceParams& params, CompletionToken&& token) const {
        return trade_api_.async_sor_order_place(params, std::forward<CompletionToken>(token));
    }

    /// Test new order using SOR (TRADE)
    ///
    /// `sor.order.test`.
    ///
    /// Test new order creation and signature/recvWindow using smart order routing (SOR).
    /// Creates and validates a new order but does not send it into the matching engine.
    ///
    /// Weight: | Condition | Request Weight |
    /// | --- | --- |
    /// | Without `computeCommissionRates` | 1 |
    /// | With `computeCommissionRates` | 20 |
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#sor-order-test
    [[nodiscard]] common::WebsocketApiResponse<SorOrderTestResponseResult>
    sor_order_test(const SorOrderTestParams& params) const {
        return trade_api_.sor_order_test(params);
    }
    template <class CompletionToken>
    auto async_sor_order_test(const SorOrderTestParams& params, CompletionToken&& token) const {
        return trade_api_.async_sor_order_test(params, std::forward<CompletionToken>(token));
    }

    // UserDataStreamApi

    /// Listing all subscriptions
    ///
    /// `session.subscriptions`.
    ///
    /// **Note:**
    ///
    /// * Users should track the corresponding subscription status of related accounts as needed.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/user-data-stream#session-subscriptions
    [[nodiscard]] common::WebsocketApiResponse<std::vector<SessionSubscriptionsResponseResultInner>>
    session_subscriptions(const SessionSubscriptionsParams& params = {}) const {
        return user_data_stream_api_.session_subscriptions(params);
    }
    template <class CompletionToken>
    auto async_session_subscriptions(const SessionSubscriptionsParams& params,
                                     CompletionToken&& token) const {
        return user_data_stream_api_.async_session_subscriptions(
            params, std::forward<CompletionToken>(token));
    }

    /// Subscribe to User Data Stream (USER_STREAM)
    ///
    /// `userDataStream.subscribe`.
    ///
    /// Subscribe to the User Data Stream in the current WebSocket connection.
    ///
    /// **Notes:**
    ///   - This method requires an authenticated WebSocket connection using Ed25519 keys. Please
    ///   refer to `session.logon`.
    ///   - To check the subscription status, use `session.status`, see the `userDataStream` flag
    ///   indicating you have an active subscription.
    ///   - User Data Stream events are available in both JSON and SBE sessions.
    ///     - Please refer to User Data Streams for the event format details.
    ///     - For SBE, only SBE schema 2:1 or later is supported.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/user-data-stream#user-data-stream-subscribe
    [[nodiscard]] common::WebsocketApiSubscription<UserDataStreamSubscribeResponseResult,
                                                   UserDataStreamEventsResponse>
    user_data_stream_subscribe(const UserDataStreamSubscribeParams& params = {}) const {
        return user_data_stream_api_.user_data_stream_subscribe(params);
    }
    template <class CompletionToken>
    auto async_user_data_stream_subscribe(const UserDataStreamSubscribeParams& params,
                                          CompletionToken&& token) const {
        return user_data_stream_api_.async_user_data_stream_subscribe(
            params, std::forward<CompletionToken>(token));
    }

    /// Subscribe to User Data Stream through signature subscription (USER_STREAM)
    ///
    /// `userDataStream.subscribe.signature`.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: USER_STREAM
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/user-data-stream#user-data-stream-subscribe-signature
    [[nodiscard]] common::WebsocketApiSubscription<UserDataStreamSubscribeResponseResult,
                                                   UserDataStreamEventsResponse>
    user_data_stream_subscribe_signature(
        const UserDataStreamSubscribeSignatureParams& params = {}) const {
        return user_data_stream_api_.user_data_stream_subscribe_signature(params);
    }
    template <class CompletionToken>
    auto
    async_user_data_stream_subscribe_signature(const UserDataStreamSubscribeSignatureParams& params,
                                               CompletionToken&& token) const {
        return user_data_stream_api_.async_user_data_stream_subscribe_signature(
            params, std::forward<CompletionToken>(token));
    }

    /// Unsubscribe from User Data Stream
    ///
    /// `userDataStream.unsubscribe`.
    ///
    /// Stop listening to the User Data Stream in the current WebSocket
    /// connection.
    ///
    /// Note that `session.logout` will only close the subscription created with
    /// `userDataStream.subscribe` but not subscriptions opened with
    /// `userDataStream.subscribe.signature`.
    ///
    /// Weight(IP): 2
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/user-data-stream#user-data-stream-unsubscribe
    [[nodiscard]] common::WebsocketApiResponse<boost::json::value>
    user_data_stream_unsubscribe(const UserDataStreamUnsubscribeParams& params = {}) const {
        return user_data_stream_api_.user_data_stream_unsubscribe(params);
    }
    template <class CompletionToken>
    auto async_user_data_stream_unsubscribe(const UserDataStreamUnsubscribeParams& params,
                                            CompletionToken&& token) const {
        return user_data_stream_api_.async_user_data_stream_unsubscribe(
            params, std::forward<CompletionToken>(token));
    }

private:
    friend class WebsocketApi;

    /// Not connected yet: `WebsocketApi::connect()` creates and connects one. Throws
    /// `common::ConfigError` if the configuration is invalid.
    explicit WebsocketApiConnection(common::WebsocketApiConfig configuration);

    [[nodiscard]] const std::shared_ptr<common::WebsocketApi>& client() const noexcept {
        return client_;
    }

    [[nodiscard]] static common::WebsocketMessageSendOptions signed_options() {
        common::WebsocketMessageSendOptions options;
        options.is_signed = true;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
    AccountApi account_api_;
    AuthApi auth_api_;
    GeneralApi general_api_;
    MarketApi market_api_;
    TradeApi trade_api_;
    UserDataStreamApi user_data_stream_api_;
};

/// Spot WebSocket API client: holds the configuration, and `connect()` opens a new
/// connection with it, like the `connect()` of the other Binance connectors. Every call returns an
/// independent connection.
class BINANCE_SPOT_EXPORT WebsocketApi {
public:
    explicit WebsocketApi(common::WebsocketApiConfig configuration);

    /// A client for `config.url`, production when it is not set.
    [[nodiscard]] static WebsocketApi from_config(common::WebsocketApiConfig config);
    /// A client for production (Spot WebSocket API).
    [[nodiscard]] static WebsocketApi production(common::WebsocketApiConfig config);
    /// A client for the testnet.
    [[nodiscard]] static WebsocketApi testnet(common::WebsocketApiConfig config);
    /// A client for the demo environment.
    [[nodiscard]] static WebsocketApi demo(common::WebsocketApiConfig config);

    [[nodiscard]] const common::WebsocketApiConfig& configuration() const noexcept {
        return configuration_;
    }

    /// Opens a connection (a pool of them with `mode`, overriding the configuration) and returns
    /// it once connected. Throws `common::ConfigError` if the configuration is invalid, and the
    /// error of the first connection that fails to open.
    [[nodiscard]] WebsocketApiConnection
    connect(std::optional<common::WebsocketMode> mode = {}) const {
        WebsocketApiConnection connection(configuration_for(mode));
        connection.client()->connect();
        return connection;
    }

    /// Asynchronous `connect()`, completing with `void(std::exception_ptr,
    /// WebsocketApiConnection)`.
    template <class CompletionToken> auto async_connect(CompletionToken&& token) const {
        return async_connect(std::nullopt, std::forward<CompletionToken>(token));
    }
    template <class CompletionToken>
    auto async_connect(std::optional<common::WebsocketMode> mode, CompletionToken&& token) const {
        return boost::asio::async_initiate<CompletionToken,
                                           void(std::exception_ptr, WebsocketApiConnection)>(
            [](auto handler, WebsocketApiConnection connection) {
                const auto client = connection.client();
                client->async_connect(
                    boost::asio::append(std::move(handler), std::move(connection)));
            },
            token, WebsocketApiConnection(configuration_for(mode)));
    }

private:
    [[nodiscard]] common::WebsocketApiConfig
    configuration_for(std::optional<common::WebsocketMode> mode) const {
        auto configuration = configuration_;
        if (mode) {
            configuration.mode = *mode;
        }
        return configuration;
    }

    common::WebsocketApiConfig configuration_;
};

} // namespace binance::spot::websocket_api
