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
#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/account_api.hpp>
#include <binance/spot/rest_api/general_api.hpp>
#include <binance/spot/rest_api/market_api.hpp>
#include <binance/spot/rest_api/models.hpp>
#include <binance/spot/rest_api/trade_api.hpp>

namespace binance::spot::rest_api {

/// Spot REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_SPOT_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Spot REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);
    /// A client for the testnet.
    [[nodiscard]] static RestApi testnet(common::RestApiConfig config);
    /// A client for the demo environment.
    [[nodiscard]] static RestApi demo(common::RestApiConfig config);

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

    // AccountApi

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
    account_commission(const AccountCommissionParams& params) const {
        return account_api_.account_commission(params);
    }
    /// Asynchronous `account_commission()`.
    template <class CompletionToken>
    auto async_account_commission(const AccountCommissionParams& params,
                                  CompletionToken&& token) const {
        return account_api_.async_account_commission(params, std::forward<CompletionToken>(token));
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
    all_order_list(const AllOrderListParams& params = {}) const {
        return account_api_.all_order_list(params);
    }
    /// Asynchronous `all_order_list()`.
    template <class CompletionToken>
    auto async_all_order_list(const AllOrderListParams& params, CompletionToken&& token) const {
        return account_api_.async_all_order_list(params, std::forward<CompletionToken>(token));
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
    all_orders(const AllOrdersParams& params) const {
        return account_api_.all_orders(params);
    }
    /// Asynchronous `all_orders()`.
    template <class CompletionToken>
    auto async_all_orders(const AllOrdersParams& params, CompletionToken&& token) const {
        return account_api_.async_all_orders(params, std::forward<CompletionToken>(token));
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
    get_account(const GetAccountParams& params = {}) const {
        return account_api_.get_account(params);
    }
    /// Asynchronous `get_account()`.
    template <class CompletionToken>
    auto async_get_account(const GetAccountParams& params, CompletionToken&& token) const {
        return account_api_.async_get_account(params, std::forward<CompletionToken>(token));
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
    get_open_orders(const GetOpenOrdersParams& params = {}) const {
        return account_api_.get_open_orders(params);
    }
    /// Asynchronous `get_open_orders()`.
    template <class CompletionToken>
    auto async_get_open_orders(const GetOpenOrdersParams& params, CompletionToken&& token) const {
        return account_api_.async_get_open_orders(params, std::forward<CompletionToken>(token));
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
    get_order(const GetOrderParams& params) const {
        return account_api_.get_order(params);
    }
    /// Asynchronous `get_order()`.
    template <class CompletionToken>
    auto async_get_order(const GetOrderParams& params, CompletionToken&& token) const {
        return account_api_.async_get_order(params, std::forward<CompletionToken>(token));
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
    get_order_list(const GetOrderListParams& params = {}) const {
        return account_api_.get_order_list(params);
    }
    /// Asynchronous `get_order_list()`.
    template <class CompletionToken>
    auto async_get_order_list(const GetOrderListParams& params, CompletionToken&& token) const {
        return account_api_.async_get_order_list(params, std::forward<CompletionToken>(token));
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
    my_allocations(const MyAllocationsParams& params) const {
        return account_api_.my_allocations(params);
    }
    /// Asynchronous `my_allocations()`.
    template <class CompletionToken>
    auto async_my_allocations(const MyAllocationsParams& params, CompletionToken&& token) const {
        return account_api_.async_my_allocations(params, std::forward<CompletionToken>(token));
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
    my_filters(const MyFiltersParams& params) const {
        return account_api_.my_filters(params);
    }
    /// Asynchronous `my_filters()`.
    template <class CompletionToken>
    auto async_my_filters(const MyFiltersParams& params, CompletionToken&& token) const {
        return account_api_.async_my_filters(params, std::forward<CompletionToken>(token));
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
    my_prevented_matches(const MyPreventedMatchesParams& params) const {
        return account_api_.my_prevented_matches(params);
    }
    /// Asynchronous `my_prevented_matches()`.
    template <class CompletionToken>
    auto async_my_prevented_matches(const MyPreventedMatchesParams& params,
                                    CompletionToken&& token) const {
        return account_api_.async_my_prevented_matches(params,
                                                       std::forward<CompletionToken>(token));
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
    my_trades(const MyTradesParams& params) const {
        return account_api_.my_trades(params);
    }
    /// Asynchronous `my_trades()`.
    template <class CompletionToken>
    auto async_my_trades(const MyTradesParams& params, CompletionToken&& token) const {
        return account_api_.async_my_trades(params, std::forward<CompletionToken>(token));
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
    open_order_list(const OpenOrderListParams& params = {}) const {
        return account_api_.open_order_list(params);
    }
    /// Asynchronous `open_order_list()`.
    template <class CompletionToken>
    auto async_open_order_list(const OpenOrderListParams& params, CompletionToken&& token) const {
        return account_api_.async_open_order_list(params, std::forward<CompletionToken>(token));
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
    order_amendments(const OrderAmendmentsParams& params) const {
        return account_api_.order_amendments(params);
    }
    /// Asynchronous `order_amendments()`.
    template <class CompletionToken>
    auto async_order_amendments(const OrderAmendmentsParams& params,
                                CompletionToken&& token) const {
        return account_api_.async_order_amendments(params, std::forward<CompletionToken>(token));
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
    rate_limit_order(const RateLimitOrderParams& params = {}) const {
        return account_api_.rate_limit_order(params);
    }
    /// Asynchronous `rate_limit_order()`.
    template <class CompletionToken>
    auto async_rate_limit_order(const RateLimitOrderParams& params, CompletionToken&& token) const {
        return account_api_.async_rate_limit_order(params, std::forward<CompletionToken>(token));
    }

    // GeneralApi

    /// Exchange information
    ///
    /// GET /api/v3/exchangeInfo.
    ///
    /// Current exchange trading rules and symbol information
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
    /// * `permissions` can support single or multiple values (e.g. `SPOT`,
    /// `["MARGIN","LEVERAGED"]`). This cannot be used in combination with `symbol` or `symbols`.
    /// * If `permissions` parameter not provided, all symbols that have either `SPOT`, `MARGIN`, or
    /// `LEVERAGED` permission will be exposed.
    ///   * To display symbols with any permission you need to specify them explicitly in
    ///   `permissions`: (e.g. `["SPOT","MARGIN",...]`.). See Account and Symbol Permissions for the
    ///   full list.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/general#exchange-info
    [[nodiscard]] common::RestApiResponse<ExchangeInfoResponse>
    exchange_info(const ExchangeInfoParams& params = {}) const {
        return general_api_.exchange_info(params);
    }
    /// Asynchronous `exchange_info()`.
    template <class CompletionToken>
    auto async_exchange_info(const ExchangeInfoParams& params, CompletionToken&& token) const {
        return general_api_.async_exchange_info(params, std::forward<CompletionToken>(token));
    }

    /// Query Execution Rules
    ///
    /// GET /api/v3/executionRules.
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
    /// **Note:**: No combination of multiple parameters is allowed.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/general#execution-rules
    [[nodiscard]] common::RestApiResponse<ExecutionRulesResponse>
    execution_rules(const ExecutionRulesParams& params = {}) const {
        return general_api_.execution_rules(params);
    }
    /// Asynchronous `execution_rules()`.
    template <class CompletionToken>
    auto async_execution_rules(const ExecutionRulesParams& params, CompletionToken&& token) const {
        return general_api_.async_execution_rules(params, std::forward<CompletionToken>(token));
    }

    /// Test connectivity
    ///
    /// GET /api/v3/ping.
    ///
    /// Test connectivity to the Rest API.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/general#ping
    [[nodiscard]] common::RestApiResponse<boost::json::value> ping() const {
        return general_api_.ping();
    }
    /// Asynchronous `ping()`.
    template <class CompletionToken> auto async_ping(CompletionToken&& token) const {
        return general_api_.async_ping(std::forward<CompletionToken>(token));
    }

    /// Check server time
    ///
    /// GET /api/v3/time.
    ///
    /// Test connectivity to the Rest API and get the current server time.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/general#time
    [[nodiscard]] common::RestApiResponse<TimeResponse> time() const { return general_api_.time(); }
    /// Asynchronous `time()`.
    template <class CompletionToken> auto async_time(CompletionToken&& token) const {
        return general_api_.async_time(std::forward<CompletionToken>(token));
    }

    // MarketApi

    /// Compressed/Aggregate trades list
    ///
    /// GET /api/v3/aggTrades.
    ///
    /// Get compressed, aggregate trades. Trades that fill at the time, from the same taker order,
    /// with the same price will have the quantity aggregated.
    ///
    /// Weight(IP): 4
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// - If fromId, startTime, and endTime are not sent, the most recent aggregate trades will be
    /// returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#agg-trades
    [[nodiscard]] common::RestApiResponse<std::vector<AggTradesResponseInner>>
    agg_trades(const AggTradesParams& params) const {
        return market_api_.agg_trades(params);
    }
    /// Asynchronous `agg_trades()`.
    template <class CompletionToken>
    auto async_agg_trades(const AggTradesParams& params, CompletionToken&& token) const {
        return market_api_.async_agg_trades(params, std::forward<CompletionToken>(token));
    }

    /// Current average price
    ///
    /// GET /api/v3/avgPrice.
    ///
    /// Current average price for a symbol.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#avg-price
    [[nodiscard]] common::RestApiResponse<AvgPriceResponse>
    avg_price(const AvgPriceParams& params) const {
        return market_api_.avg_price(params);
    }
    /// Asynchronous `avg_price()`.
    template <class CompletionToken>
    auto async_avg_price(const AvgPriceParams& params, CompletionToken&& token) const {
        return market_api_.async_avg_price(params, std::forward<CompletionToken>(token));
    }

    /// Order book
    ///
    /// GET /api/v3/depth.
    ///
    /// Order book
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#depth
    [[nodiscard]] common::RestApiResponse<DepthResponse> depth(const DepthParams& params) const {
        return market_api_.depth(params);
    }
    /// Asynchronous `depth()`.
    template <class CompletionToken>
    auto async_depth(const DepthParams& params, CompletionToken&& token) const {
        return market_api_.async_depth(params, std::forward<CompletionToken>(token));
    }

    /// Recent trades list
    ///
    /// GET /api/v3/trades.
    ///
    /// Get recent trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#get-trades
    [[nodiscard]] common::RestApiResponse<std::vector<GetTradesResponseInner>>
    get_trades(const GetTradesParams& params) const {
        return market_api_.get_trades(params);
    }
    /// Asynchronous `get_trades()`.
    template <class CompletionToken>
    auto async_get_trades(const GetTradesParams& params, CompletionToken&& token) const {
        return market_api_.async_get_trades(params, std::forward<CompletionToken>(token));
    }

    /// Historical Block Trades (MARKET_DATA)
    ///
    /// GET /api/v3/historicalBlockTrades.
    ///
    /// Get block trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: MARKET_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#historical-block-trades
    [[nodiscard]] common::RestApiResponse<std::vector<HistoricalBlockTradesResponseInner>>
    historical_block_trades(const HistoricalBlockTradesParams& params) const {
        return market_api_.historical_block_trades(params);
    }
    /// Asynchronous `historical_block_trades()`.
    template <class CompletionToken>
    auto async_historical_block_trades(const HistoricalBlockTradesParams& params,
                                       CompletionToken&& token) const {
        return market_api_.async_historical_block_trades(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Old trade lookup
    ///
    /// GET /api/v3/historicalTrades.
    ///
    /// Get older trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#historical-trades
    [[nodiscard]] common::RestApiResponse<std::vector<GetTradesResponseInner>>
    historical_trades(const HistoricalTradesParams& params) const {
        return market_api_.historical_trades(params);
    }
    /// Asynchronous `historical_trades()`.
    template <class CompletionToken>
    auto async_historical_trades(const HistoricalTradesParams& params,
                                 CompletionToken&& token) const {
        return market_api_.async_historical_trades(params, std::forward<CompletionToken>(token));
    }

    /// Kline/Candlestick data
    ///
    /// GET /api/v3/klines.
    ///
    /// Kline/candlestick bars for a symbol.
    /// Klines are uniquely identified by their open time.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#klines
    [[nodiscard]] common::RestApiResponse<std::vector<std::vector<KlinesItemInner>>>
    klines(const KlinesParams& params) const {
        return market_api_.klines(params);
    }
    /// Asynchronous `klines()`.
    template <class CompletionToken>
    auto async_klines(const KlinesParams& params, CompletionToken&& token) const {
        return market_api_.async_klines(params, std::forward<CompletionToken>(token));
    }

    /// Query Reference Price
    ///
    /// GET /api/v3/referencePrice.
    ///
    /// Query the reference price for a symbol.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#reference-price
    [[nodiscard]] common::RestApiResponse<ReferencePriceResponse>
    reference_price(const ReferencePriceParams& params) const {
        return market_api_.reference_price(params);
    }
    /// Asynchronous `reference_price()`.
    template <class CompletionToken>
    auto async_reference_price(const ReferencePriceParams& params, CompletionToken&& token) const {
        return market_api_.async_reference_price(params, std::forward<CompletionToken>(token));
    }

    /// Query Reference Price Calculation
    ///
    /// GET /api/v3/referencePrice/calculation.
    ///
    /// Describes how reference price is calculated for a given symbol.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#reference-price-calculation
    [[nodiscard]] common::RestApiResponse<ReferencePriceCalculationResponse>
    reference_price_calculation(const ReferencePriceCalculationParams& params) const {
        return market_api_.reference_price_calculation(params);
    }
    /// Asynchronous `reference_price_calculation()`.
    template <class CompletionToken>
    auto async_reference_price_calculation(const ReferencePriceCalculationParams& params,
                                           CompletionToken&& token) const {
        return market_api_.async_reference_price_calculation(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Rolling window price change statistics
    ///
    /// GET /api/v3/ticker.
    ///
    /// **Note:** This endpoint differs from `GET /api/v3/ticker/24hr`.
    ///
    /// The statistical time range of this endpoint can be up to 59999ms longer
    /// than the requested `windowSize`.
    ///
    /// `openTime` starts at the beginning of a minute, while the end time is
    /// the current time. Therefore, the actual interval can be up to 59999ms
    /// longer than the requested window.
    ///
    /// For example, if `closeTime` is 1641287867099 (January 04, 2022
    /// 09:17:47:099 UTC) and `windowSize` is `1d`, then `openTime` is
    /// 1641201420000 (January 3, 2022, 09:17:00 UTC).
    ///
    /// Weight: 4 for each requested symbol regardless of windowSize.
    ///
    /// The weight for this request will cap at 200 once the number of `symbols` in the request is
    /// more than 50.
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker
    [[nodiscard]] common::RestApiResponse<TickerResponse>
    ticker(const TickerParams& params = {}) const {
        return market_api_.ticker(params);
    }
    /// Asynchronous `ticker()`.
    template <class CompletionToken>
    auto async_ticker(const TickerParams& params, CompletionToken&& token) const {
        return market_api_.async_ticker(params, std::forward<CompletionToken>(token));
    }

    /// 24hr ticker price change statistics
    ///
    /// GET /api/v3/ticker/24hr.
    ///
    /// 24 hour rolling window price change statistics. **Careful** when accessing this with no
    /// symbol.
    ///
    /// Weight:
    ///
    /// - Parameter | Symbols Provided | Weight
    /// - symbol | 1 | 2
    /// - symbol | symbol parameter is omitted | 80
    /// - symbols | 1-20 | 2
    /// - symbols | 21-100 | 40
    /// - symbols | 101 or more | 80
    /// - symbols | symbols parameter is omitted | 80
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker24hr
    [[nodiscard]] common::RestApiResponse<Ticker24hrResponse>
    ticker24hr(const Ticker24hrParams& params = {}) const {
        return market_api_.ticker24hr(params);
    }
    /// Asynchronous `ticker24hr()`.
    template <class CompletionToken>
    auto async_ticker24hr(const Ticker24hrParams& params, CompletionToken&& token) const {
        return market_api_.async_ticker24hr(params, std::forward<CompletionToken>(token));
    }

    /// Symbol order book ticker
    ///
    /// GET /api/v3/ticker/bookTicker.
    ///
    /// Best price/qty on the order book for a symbol or symbols.
    ///
    /// Weight: |Parameter|Symbols Provided|Weight|
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
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker-book-ticker
    [[nodiscard]] common::RestApiResponse<TickerBookTickerResponse>
    ticker_book_ticker(const TickerBookTickerParams& params = {}) const {
        return market_api_.ticker_book_ticker(params);
    }
    /// Asynchronous `ticker_book_ticker()`.
    template <class CompletionToken>
    auto async_ticker_book_ticker(const TickerBookTickerParams& params,
                                  CompletionToken&& token) const {
        return market_api_.async_ticker_book_ticker(params, std::forward<CompletionToken>(token));
    }

    /// Symbol price ticker
    ///
    /// GET /api/v3/ticker/price.
    ///
    /// Latest price for a symbol or symbols.
    ///
    /// Weight: |Parameter|Symbols Provided|Weight|
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
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker-price
    [[nodiscard]] common::RestApiResponse<TickerPriceResponse>
    ticker_price(const TickerPriceParams& params = {}) const {
        return market_api_.ticker_price(params);
    }
    /// Asynchronous `ticker_price()`.
    template <class CompletionToken>
    auto async_ticker_price(const TickerPriceParams& params, CompletionToken&& token) const {
        return market_api_.async_ticker_price(params, std::forward<CompletionToken>(token));
    }

    /// Trading Day Ticker
    ///
    /// GET /api/v3/ticker/tradingDay.
    ///
    /// Price change statistics for a trading day.
    ///
    /// Weight: 4 for each requested symbol. The weight for this request will cap at 200 once the
    /// number of symbols in the request is more than 50.
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// **Notes:**:
    ///   - Supported values for `timeZone`:
    ///     - Hours and minutes (e.g. `-1:00`, `05:45`)
    ///     - Only hours (e.g. `0`, `8`, `4`)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker-trading-day
    [[nodiscard]] common::RestApiResponse<TickerTradingDayResponse>
    ticker_trading_day(const TickerTradingDayParams& params = {}) const {
        return market_api_.ticker_trading_day(params);
    }
    /// Asynchronous `ticker_trading_day()`.
    template <class CompletionToken>
    auto async_ticker_trading_day(const TickerTradingDayParams& params,
                                  CompletionToken&& token) const {
        return market_api_.async_ticker_trading_day(params, std::forward<CompletionToken>(token));
    }

    /// UIKlines
    ///
    /// GET /api/v3/uiKlines.
    ///
    /// The request is similar to klines having the same parameters and
    /// response.
    ///
    /// `uiKlines` return modified kline data, optimized for presentation of
    /// candlestick charts.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ui-klines
    [[nodiscard]] common::RestApiResponse<std::vector<std::vector<KlinesItemInner>>>
    ui_klines(const UiKlinesParams& params) const {
        return market_api_.ui_klines(params);
    }
    /// Asynchronous `ui_klines()`.
    template <class CompletionToken>
    auto async_ui_klines(const UiKlinesParams& params, CompletionToken&& token) const {
        return market_api_.async_ui_klines(params, std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// Cancel All Open Orders on a Symbol (TRADE)
    ///
    /// DELETE /api/v3/openOrders.
    ///
    /// Cancels all active orders on a symbol.
    /// This includes orders that are part of an order list.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#delete-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<DeleteOpenOrdersResponseInner>>
    delete_open_orders(const DeleteOpenOrdersParams& params) const {
        return trade_api_.delete_open_orders(params);
    }
    /// Asynchronous `delete_open_orders()`.
    template <class CompletionToken>
    auto async_delete_open_orders(const DeleteOpenOrdersParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_delete_open_orders(params, std::forward<CompletionToken>(token));
    }

    /// Cancel order (TRADE)
    ///
    /// DELETE /api/v3/order.
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
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - If both `orderId` and `origClientOrderId` are provided, the `orderId` is searched first,
    /// then the `origClientOrderId` from that result is checked against that order. If both
    /// conditions are not met the request will be rejected.
    ///
    /// Response Notes:
    /// **Notes:**
    /// - The payload above does not show all fields that can appear in the order response. Please
    /// refer to Conditional fields in Order Responses.
    /// - The performance for canceling an order (single cancel or as part of a cancel-replace) is
    /// always better when only `orderId` is sent. Sending `origClientOrderId` or both `orderId` +
    /// `origClientOrderId` will be slower.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#delete-order
    [[nodiscard]] common::RestApiResponse<DeleteOrderResponse>
    delete_order(const DeleteOrderParams& params) const {
        return trade_api_.delete_order(params);
    }
    /// Asynchronous `delete_order()`.
    template <class CompletionToken>
    auto async_delete_order(const DeleteOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_delete_order(params, std::forward<CompletionToken>(token));
    }

    /// New order (TRADE)
    ///
    /// POST /api/v3/order.
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
    /// Some additional mandatory parameters based on order `type`:
    ///
    /// Type | Additional mandatory parameters | Additional Information
    /// ------------ | ------------| ------
    /// `LIMIT` | `timeInForce`, `quantity`, `price`|
    /// `MARKET` | `quantity` or `quoteOrderQty`| `MARKET` orders using the `quantity` field
    /// specifies the amount of the `base asset` the user wants to buy or sell at the market price.
    /// E.g. MARKET order on BTCUSDT will specify how much BTC the user is buying or selling.
    ///
    /// `MARKET` orders using `quoteOrderQty` specifies the amount the user wants to spend (when
    /// buying) or receive (when selling) the `quote` asset; the correct `quantity` will be
    /// determined based on the market liquidity and `quoteOrderQty`. E.g. Using the symbol BTCUSDT:
    /// `BUY` side, the order will buy as many BTC as `quoteOrderQty` USDT can.
    /// `SELL` side, the order will sell as much BTC needed to receive `quoteOrderQty` USDT.
    /// `STOP_LOSS` | `quantity`, `stopPrice` or `trailingDelta`| This will execute a `MARKET` order
    /// when the conditions are met. (e.g. `stopPrice` is met or `trailingDelta` is activated)
    /// `STOP_LOSS_LIMIT` | `timeInForce`, `quantity`,  `price`, `stopPrice` or `trailingDelta`
    /// `TAKE_PROFIT` | `quantity`, `stopPrice` or `trailingDelta` | This will execute a `MARKET`
    /// order when the conditions are met. (e.g. `stopPrice` is met or `trailingDelta` is activated)
    /// `TAKE_PROFIT_LIMIT` | `timeInForce`, `quantity`, `price`, `stopPrice` or `trailingDelta` |
    /// `LIMIT_MAKER` | `quantity`, `price`| This is a `LIMIT` order that will be rejected if the
    /// order immediately matches and trades as a taker. This is also known as a POST-ONLY order.
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
    /// Other info:
    /// * Any `LIMIT` or `LIMIT_MAKER` type order can be made an iceberg order by sending an
    /// `icebergQty`.
    /// * Any order with an `icebergQty` MUST have `timeInForce` set to `GTC`.
    /// * For `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT_LIMIT` and `TAKE_PROFIT` orders,
    /// `trailingDelta` can be combined with `stopPrice`.
    /// * `MARKET` orders using `quoteOrderQty` will not break `LOT_SIZE` filter rules; the order
    /// will execute a `quantity` that will have the notional value as close as possible to
    /// `quoteOrderQty`. Trigger order price rules against market price for both MARKET and LIMIT
    /// versions:
    ///   * Price above market price: `STOP_LOSS` `BUY`, `TAKE_PROFIT` `SELL`
    ///   * Price below market price: `STOP_LOSS` `SELL`, `TAKE_PROFIT` `BUY`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#new-order
    [[nodiscard]] common::RestApiResponse<NewOrderResponse>
    new_order(const NewOrderParams& params) const {
        return trade_api_.new_order(params);
    }
    /// Asynchronous `new_order()`.
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_new_order(params, std::forward<CompletionToken>(token));
    }

    /// Cancel Order list (TRADE)
    ///
    /// DELETE /api/v3/orderList.
    ///
    /// Cancel an entire Order list
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// **Notes:**
    ///   - Canceling an individual order from an order list will cancel the entire order list.
    ///   - If both orderListId and listClientOrderId parameters are provided, the orderListId is
    ///   searched first, then the listClientOrderId from that result is checked against that order.
    ///   If both conditions are not met the request will be rejected.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#delete-order-list
    [[nodiscard]] common::RestApiResponse<DeleteOrderListResponse>
    delete_order_list(const DeleteOrderListParams& params) const {
        return trade_api_.delete_order_list(params);
    }
    /// Asynchronous `delete_order_list()`.
    template <class CompletionToken>
    auto async_delete_order_list(const DeleteOrderListParams& params,
                                 CompletionToken&& token) const {
        return trade_api_.async_delete_order_list(params, std::forward<CompletionToken>(token));
    }

    /// Order Amend Keep Priority (TRADE)
    ///
    /// PUT /api/v3/order/amend/keepPriority.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-amend-keep-priority
    [[nodiscard]] common::RestApiResponse<OrderAmendKeepPriorityResponse>
    order_amend_keep_priority(const OrderAmendKeepPriorityParams& params) const {
        return trade_api_.order_amend_keep_priority(params);
    }
    /// Asynchronous `order_amend_keep_priority()`.
    template <class CompletionToken>
    auto async_order_amend_keep_priority(const OrderAmendKeepPriorityParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_order_amend_keep_priority(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Cancel an Existing Order and Send a New Order (TRADE)
    ///
    /// POST /api/v3/order/cancelReplace.
    ///
    /// - Cancels an existing order and places a new order on the same symbol.
    /// - Filters and Order Count are evaluated before the processing of the cancellation and order
    /// placement occurs.
    /// - A new order that was not attempted (i.e. when `newOrderResult: NOT_ATTEMPTED`), will still
    /// increase the unfilled order count by 1.
    /// - You can only cancel an individual order from an orderList using this endpoint, but the
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
    /// Similar to `POST /api/v3/order`, additional mandatory parameters are determined by `type`.
    /// Response format varies depending on whether the processing of the message succeeded,
    /// partially succeeded, or failed.
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
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `N/A`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ❌ `FAILURE` | `400`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ✅ `SUCCESS` | N/A
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    ///
    /// Response Notes:
    /// **Notes:**
    /// - The payload above does not show all fields that can appear. Please refer to Conditional
    /// fields in Order Responses.
    /// - The performance for canceling an order (single cancel or as part of a cancel-replace) is
    /// always better when only `orderId` is sent. Sending `origClientOrderId` or both `orderId` +
    /// `origClientOrderId` will be slower.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-cancel-replace
    [[nodiscard]] common::RestApiResponse<OrderCancelReplaceResponse>
    order_cancel_replace(const OrderCancelReplaceParams& params) const {
        return trade_api_.order_cancel_replace(params);
    }
    /// Asynchronous `order_cancel_replace()`.
    template <class CompletionToken>
    auto async_order_cancel_replace(const OrderCancelReplaceParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_order_cancel_replace(params, std::forward<CompletionToken>(token));
    }

    /// New Order list - OCO (TRADE)
    ///
    /// POST /api/v3/orderList/oco.
    ///
    /// Send in an one-cancels-the-other (OCO) pair, where activation of one
    /// order immediately cancels the other.
    ///
    /// - An OCO has 2 orders called the **above order** and **below order**.
    /// - One of the orders must be a `LIMIT_MAKER/TAKE_PROFIT/TAKE_PROFIT_LIMIT` order and the
    /// other must be `STOP_LOSS` or `STOP_LOSS_LIMIT` order.
    /// - Price restrictions
    ///   - If the OCO is on the `SELL` side:
    ///     - `LIMIT_MAKER/TAKE_PROFIT_LIMIT` `price` > Last Traded Price >
    ///     `STOP_LOSS/STOP_LOSS_LIMIT` `stopPrice`
    ///     - `TAKE_PROFIT stopPrice` > Last Traded Price > `STOP_LOSS/STOP_LOSS_LIMIT stopPrice`
    ///   - If the OCO is on the `BUY` side:
    ///     - `LIMIT_MAKER/TAKE_PROFIT_LIMIT price` < Last Traded Price < `stopPrice`
    ///     - `TAKE_PROFIT stopPrice` < Last Traded Price < `STOP_LOSS/STOP_LOSS_LIMIT stopPrice` *
    ///     OCOs add **2 orders** to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS`
    ///     filter.
    /// - OCOs add 2 orders to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-oco
    [[nodiscard]] common::RestApiResponse<OrderListOcoResponse>
    order_list_oco(const OrderListOcoParams& params) const {
        return trade_api_.order_list_oco(params);
    }
    /// Asynchronous `order_list_oco()`.
    template <class CompletionToken>
    auto async_order_list_oco(const OrderListOcoParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_list_oco(params, std::forward<CompletionToken>(token));
    }

    /// New Order List - OPO (TRADE)
    ///
    /// POST /api/v3/orderList/opo.
    ///
    /// Place an OPO.
    ///
    /// - The working order must be `LIMIT` or `LIMIT_MAKER`.
    /// - OPOs add 2 orders to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS` filter.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-opo
    [[nodiscard]] common::RestApiResponse<OrderListOpoResponse>
    order_list_opo(const OrderListOpoParams& params) const {
        return trade_api_.order_list_opo(params);
    }
    /// Asynchronous `order_list_opo()`.
    template <class CompletionToken>
    auto async_order_list_opo(const OrderListOpoParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_list_opo(params, std::forward<CompletionToken>(token));
    }

    /// New Order List - OPOCO (TRADE)
    ///
    /// POST /api/v3/orderList/opoco.
    ///
    /// Place an OPOCO.
    ///
    /// - The working order must be `LIMIT` or `LIMIT_MAKER`.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-opoco
    [[nodiscard]] common::RestApiResponse<OrderListOpocoResponse>
    order_list_opoco(const OrderListOpocoParams& params) const {
        return trade_api_.order_list_opoco(params);
    }
    /// Asynchronous `order_list_opoco()`.
    template <class CompletionToken>
    auto async_order_list_opoco(const OrderListOpocoParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_list_opoco(params, std::forward<CompletionToken>(token));
    }

    /// New Order list - OTO (TRADE)
    ///
    /// POST /api/v3/orderList/oto.
    ///
    /// Place an OTO.
    ///
    /// - An OTO (One-Triggers-the-Other) is an order list comprised of 2 orders.
    /// - The first order is called the **working order** and must be `LIMIT` or `LIMIT_MAKER`.
    /// Initially, only the working order goes on the order book.
    /// - The second order is called the **pending order**. It can be any order type except for
    /// `MARKET` orders using parameter `quoteOrderQty`. The pending order is only placed on the
    /// order book when the working order gets **fully filled**.
    /// - If either the working order or the pending order is cancelled individually, the other
    /// order in the order list will also be canceled or expired.
    /// - When the order list is placed, if the working order gets **immediately fully filled**, the
    /// placement response will show the working order as `FILLED` but the pending order will still
    /// appear as `PENDING_NEW`. You need to query the status of the pending order again to see its
    /// updated status.
    /// - OTOs add **2 orders** to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS` filter.
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
    /// |`pendingType` = `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT`|`pendingPrice`, `pendingStopPrice`
    /// and/or `pendingTrailingDelta`, `pendingTimeInForce`|
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-oto
    [[nodiscard]] common::RestApiResponse<OrderListOtoResponse>
    order_list_oto(const OrderListOtoParams& params) const {
        return trade_api_.order_list_oto(params);
    }
    /// Asynchronous `order_list_oto()`.
    template <class CompletionToken>
    auto async_order_list_oto(const OrderListOtoParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_list_oto(params, std::forward<CompletionToken>(token));
    }

    /// New Order list - OTOCO (TRADE)
    ///
    /// POST /api/v3/orderList/otoco.
    ///
    /// Place an OTOCO.
    ///
    /// - An OTOCO (One-Triggers-One-Cancels-the-Other) is an order list comprised of 3 orders.
    /// - The first order is called the **working order** and must be `LIMIT` or `LIMIT_MAKER`.
    /// Initially, only the working order goes on the order book.
    ///   - The behavior of the working order is the same as the OTO.
    /// - OTOCO has 2 pending orders (pending above and pending below), forming an OCO pair. The
    /// pending orders are only placed on the order book when the working order gets **fully
    /// filled**.
    ///   - The rules of the pending above and pending below follow the same rules as the Order list
    ///   OCO.
    /// - OTOCOs add **3 orders** to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS`
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
    /// |`pendingAboveType`= `LIMIT_MAKER`                                |`pendingAbovePrice`     |
    /// |`pendingAboveType` = `STOP_LOSS/TAKE_PROFIT`        |`pendingAboveStopPrice` and/or
    /// `pendingAboveTrailingDelta`|
    /// |`pendingAboveType=STOP_LOSS_LIMIT/TAKE_PROFIT_LIMIT` |`pendingAbovePrice`,
    /// `pendingAboveStopPrice` and/or `pendingAboveTrailingDelta`, `pendingAboveTimeInForce`|
    /// |`pendingBelowType`= `LIMIT_MAKER`                                |`pendingBelowPrice` |
    /// |`pendingBelowType= STOP_LOSS/TAKE_PROFIT`         |`pendingBelowStopPrice` and/or
    /// `pendingBelowTrailingDelta`|
    /// |`pendingBelowType=STOP_LOSS_LIMIT/TAKE_PROFIT_LIMIT` |`pendingBelowPrice`,
    /// `pendingBelowStopPrice` and/or `pendingBelowTrailingDelta`, `pendingBelowTimeInForce`|
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-otoco
    [[nodiscard]] common::RestApiResponse<OrderListOtocoResponse>
    order_list_otoco(const OrderListOtocoParams& params) const {
        return trade_api_.order_list_otoco(params);
    }
    /// Asynchronous `order_list_otoco()`.
    template <class CompletionToken>
    auto async_order_list_otoco(const OrderListOtocoParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_list_otoco(params, std::forward<CompletionToken>(token));
    }

    /// New OCO - Deprecated (TRADE)
    ///
    /// POST /api/v3/order/oco.
    ///
    /// Send in a new OCO.
    ///
    /// - Price Restrictions:
    ///   - `SELL`: Limit Price > Last Price > Stop Price
    ///   - `BUY`: Limit Price < Last Price < Stop Price
    /// - Quantity Restrictions:
    ///   - Both legs must have the same quantity.
    ///   - `ICEBERG` quantities however do not have to be the same
    /// - `OCO` adds **2 orders** to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS`
    /// filter.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-oco
    ///
    /// Deprecated: this endpoint may be removed in a future version.
    [[deprecated("This endpoint may be removed in a future version.")]]
    [[nodiscard]] common::RestApiResponse<OrderOcoResponse>
    order_oco(const OrderOcoParams& params) const {
        return trade_api_.order_oco(params);
    }
    /// Asynchronous `order_oco()`.
    template <class CompletionToken>
    [[deprecated("This endpoint may be removed in a future version.")]] auto
    async_order_oco(const OrderOcoParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_oco(params, std::forward<CompletionToken>(token));
    }

    /// Test new order (TRADE)
    ///
    /// POST /api/v3/order/test.
    ///
    /// Test new order creation and signature/recvWindow long.
    ///
    /// Creates and validates a new order but does not send it into the matching
    /// engine.
    ///
    /// Weight: |Condition|Weight|
    /// |---|---|
    /// |Without `computeCommissionRates`|1|
    /// |With `computeCommissionRates`|20|
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-test
    [[nodiscard]] common::RestApiResponse<OrderTestResponse>
    order_test(const OrderTestParams& params) const {
        return trade_api_.order_test(params);
    }
    /// Asynchronous `order_test()`.
    template <class CompletionToken>
    auto async_order_test(const OrderTestParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_test(params, std::forward<CompletionToken>(token));
    }

    /// New order using SOR (TRADE)
    ///
    /// POST /api/v3/sor/order.
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
    /// **Note:** `POST /api/v3/sor/order` only supports `LIMIT` and `MARKET` orders.
    /// `quoteOrderQty` is not supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#sor-order
    [[nodiscard]] common::RestApiResponse<SorOrderResponse>
    sor_order(const SorOrderParams& params) const {
        return trade_api_.sor_order(params);
    }
    /// Asynchronous `sor_order()`.
    template <class CompletionToken>
    auto async_sor_order(const SorOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_sor_order(params, std::forward<CompletionToken>(token));
    }

    /// Test new order using SOR (TRADE)
    ///
    /// POST /api/v3/sor/order/test.
    ///
    /// Test new order creation and signature/recvWindow using smart order routing (SOR).
    /// Creates and validates a new order but does not send it into the matching engine.
    ///
    /// Weight: |Condition|Weight|
    /// |---|---|
    /// |Without `computeCommissionRates`|1|
    /// |With `computeCommissionRates`|20|
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#sor-order-test
    [[nodiscard]] common::RestApiResponse<SorOrderTestResponse>
    sor_order_test(const SorOrderTestParams& params) const {
        return trade_api_.sor_order_test(params);
    }
    /// Asynchronous `sor_order_test()`.
    template <class CompletionToken>
    auto async_sor_order_test(const SorOrderTestParams& params, CompletionToken&& token) const {
        return trade_api_.async_sor_order_test(params, std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest make_request(std::string endpoint, common::HttpMethod method,
                                                   common::Params query, common::Params body,
                                                   bool is_signed) const {
        common::RestRequest req;
        req.method = method;
        req.endpoint = std::move(endpoint);
        req.query = std::move(query);
        req.body = std::move(body);
        req.time_unit = client_->configuration().time_unit;
        req.is_signed = is_signed;
        return req;
    }

    std::shared_ptr<common::RestClient> client_;
    AccountApi account_api_;
    GeneralApi general_api_;
    MarketApi market_api_;
    TradeApi trade_api_;
};

} // namespace binance::spot::rest_api
