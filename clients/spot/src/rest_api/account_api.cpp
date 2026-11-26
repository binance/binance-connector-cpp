//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/account_api.hpp>

namespace binance::spot::rest_api {

namespace {
constexpr bool kHasTimeUnit = true;
} // namespace

AccountApi::AccountApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
AccountApi::account_commission_request(const AccountCommissionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/account/commission";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountCommissionResponse>
AccountApi::account_commission(const AccountCommissionParams& params) const {
    return common::send<AccountCommissionResponse>(*client_, account_commission_request(params));
}

common::RestRequest AccountApi::all_order_list_request(const AllOrderListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/allOrderList";
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<AllOrderListResponseInner>>
AccountApi::all_order_list(const AllOrderListParams& params) const {
    return common::send<std::vector<AllOrderListResponseInner>>(*client_,
                                                                all_order_list_request(params));
}

common::RestRequest AccountApi::all_orders_request(const AllOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/allOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<AllOrdersResponseInner>>
AccountApi::all_orders(const AllOrdersParams& params) const {
    return common::send<std::vector<AllOrdersResponseInner>>(*client_, all_orders_request(params));
}

common::RestRequest AccountApi::get_account_request(const GetAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/account";
    common::detail::json::set_param(req.query, "omitZeroBalances", params.omit_zero_balances);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetAccountResponse>
AccountApi::get_account(const GetAccountParams& params) const {
    return common::send<GetAccountResponse>(*client_, get_account_request(params));
}

common::RestRequest AccountApi::get_open_orders_request(const GetOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetOpenOrdersResponseInner>>
AccountApi::get_open_orders(const GetOpenOrdersParams& params) const {
    return common::send<std::vector<GetOpenOrdersResponseInner>>(*client_,
                                                                 get_open_orders_request(params));
}

common::RestRequest AccountApi::get_order_request(const GetOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOrderResponse>
AccountApi::get_order(const GetOrderParams& params) const {
    return common::send<GetOrderResponse>(*client_, get_order_request(params));
}

common::RestRequest AccountApi::get_order_list_request(const GetOrderListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/orderList";
    common::detail::json::set_param(req.query, "orderListId", params.order_list_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOrderListResponse>
AccountApi::get_order_list(const GetOrderListParams& params) const {
    return common::send<GetOrderListResponse>(*client_, get_order_list_request(params));
}

common::RestRequest AccountApi::my_allocations_request(const MyAllocationsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/myAllocations";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "fromAllocationId", params.from_allocation_id);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<MyAllocationsResponseInner>>
AccountApi::my_allocations(const MyAllocationsParams& params) const {
    return common::send<std::vector<MyAllocationsResponseInner>>(*client_,
                                                                 my_allocations_request(params));
}

common::RestRequest AccountApi::my_filters_request(const MyFiltersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/myFilters";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MyFiltersResponse>
AccountApi::my_filters(const MyFiltersParams& params) const {
    return common::send<MyFiltersResponse>(*client_, my_filters_request(params));
}

common::RestRequest
AccountApi::my_prevented_matches_request(const MyPreventedMatchesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/myPreventedMatches";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "preventedMatchId", params.prevented_match_id);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "fromPreventedMatchId",
                                    params.from_prevented_match_id);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<MyPreventedMatchesResponseInner>>
AccountApi::my_prevented_matches(const MyPreventedMatchesParams& params) const {
    return common::send<std::vector<MyPreventedMatchesResponseInner>>(
        *client_, my_prevented_matches_request(params));
}

common::RestRequest AccountApi::my_trades_request(const MyTradesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/myTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<MyTradesResponseInner>>
AccountApi::my_trades(const MyTradesParams& params) const {
    return common::send<std::vector<MyTradesResponseInner>>(*client_, my_trades_request(params));
}

common::RestRequest AccountApi::open_order_list_request(const OpenOrderListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/openOrderList";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<OpenOrderListResponseInner>>
AccountApi::open_order_list(const OpenOrderListParams& params) const {
    return common::send<std::vector<OpenOrderListResponseInner>>(*client_,
                                                                 open_order_list_request(params));
}

common::RestRequest
AccountApi::order_amendments_request(const OrderAmendmentsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/order/amendments";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "fromExecutionId", params.from_execution_id);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<OrderAmendmentsResponseInner>>
AccountApi::order_amendments(const OrderAmendmentsParams& params) const {
    return common::send<std::vector<OrderAmendmentsResponseInner>>(
        *client_, order_amendments_request(params));
}

common::RestRequest AccountApi::rate_limit_order_request(const RateLimitOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/rateLimit/order";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<RateLimitOrderResponseInner>>
AccountApi::rate_limit_order(const RateLimitOrderParams& params) const {
    return common::send<std::vector<RateLimitOrderResponseInner>>(*client_,
                                                                  rate_limit_order_request(params));
}

} // namespace binance::spot::rest_api
