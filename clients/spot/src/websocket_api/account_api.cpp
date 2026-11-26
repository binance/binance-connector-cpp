//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/account_api.hpp>

namespace binance::spot::websocket_api {

AccountApi::AccountApi(std::shared_ptr<common::WebsocketApi> client) : client_(std::move(client)) {}

common::Params AccountApi::account_commission_payload(const AccountCommissionParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return p;
}

common::WebsocketApiResponse<AccountCommissionResponseResult>
AccountApi::account_commission(const AccountCommissionParams& params) const {
    return common::send<AccountCommissionResponseResult>(*client_, "account.commission",
                                                         account_commission_payload(params),
                                                         make_options(false, true, false, false));
}

common::Params
AccountApi::account_rate_limits_orders_payload(const AccountRateLimitsOrdersParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<AccountRateLimitsOrdersResponseResultInner>>
AccountApi::account_rate_limits_orders(const AccountRateLimitsOrdersParams& params) const {
    return common::send<std::vector<AccountRateLimitsOrdersResponseResultInner>>(
        *client_, "account.rateLimits.orders", account_rate_limits_orders_payload(params),
        make_options(false, true, false, false));
}

common::Params AccountApi::account_status_payload(const AccountStatusParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "omitZeroBalances", params.omit_zero_balances);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<AccountStatusResponseResult>
AccountApi::account_status(const AccountStatusParams& params) const {
    return common::send<AccountStatusResponseResult>(*client_, "account.status",
                                                     account_status_payload(params),
                                                     make_options(false, true, false, false));
}

common::Params AccountApi::all_order_lists_payload(const AllOrderListsParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "fromId", params.from_id);
    common::detail::json::set_param(p, "startTime", params.start_time);
    common::detail::json::set_param(p, "endTime", params.end_time);
    common::detail::json::set_param(p, "limit", params.limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<AllOrderListsResponseResultInner>>
AccountApi::all_order_lists(const AllOrderListsParams& params) const {
    return common::send<std::vector<AllOrderListsResponseResultInner>>(
        *client_, "allOrderLists", all_order_lists_payload(params),
        make_options(false, true, false, false));
}

common::Params AccountApi::all_orders_payload(const AllOrdersParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "startTime", params.start_time);
    common::detail::json::set_param(p, "endTime", params.end_time);
    common::detail::json::set_param(p, "limit", params.limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<AllOrdersResponseResultInner>>
AccountApi::all_orders(const AllOrdersParams& params) const {
    return common::send<std::vector<AllOrdersResponseResultInner>>(
        *client_, "allOrders", all_orders_payload(params), make_options(false, true, false, false));
}

common::Params AccountApi::my_allocations_payload(const MyAllocationsParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "startTime", params.start_time);
    common::detail::json::set_param(p, "endTime", params.end_time);
    common::detail::json::set_param(p, "fromAllocationId", params.from_allocation_id);
    common::detail::json::set_param(p, "limit", params.limit);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<MyAllocationsResponseResultInner>>
AccountApi::my_allocations(const MyAllocationsParams& params) const {
    return common::send<std::vector<MyAllocationsResponseResultInner>>(
        *client_, "myAllocations", my_allocations_payload(params),
        make_options(false, true, false, false));
}

common::Params AccountApi::my_filters_payload(const MyFiltersParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<MyFiltersResponse>
AccountApi::my_filters(const MyFiltersParams& params) const {
    return common::send<MyFiltersResponse>(*client_, "myFilters", my_filters_payload(params),
                                           make_options(false, true, false, false));
}

common::Params AccountApi::my_prevented_matches_payload(const MyPreventedMatchesParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "preventedMatchId", params.prevented_match_id);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "fromPreventedMatchId", params.from_prevented_match_id);
    common::detail::json::set_param(p, "limit", params.limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<MyPreventedMatchesResponseResultInner>>
AccountApi::my_prevented_matches(const MyPreventedMatchesParams& params) const {
    return common::send<std::vector<MyPreventedMatchesResponseResultInner>>(
        *client_, "myPreventedMatches", my_prevented_matches_payload(params),
        make_options(false, true, false, false));
}

common::Params AccountApi::my_trades_payload(const MyTradesParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "startTime", params.start_time);
    common::detail::json::set_param(p, "endTime", params.end_time);
    common::detail::json::set_param(p, "fromId", params.from_id);
    common::detail::json::set_param(p, "limit", params.limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<MyTradesResponseResultInner>>
AccountApi::my_trades(const MyTradesParams& params) const {
    return common::send<std::vector<MyTradesResponseResultInner>>(
        *client_, "myTrades", my_trades_payload(params), make_options(false, true, false, false));
}

common::Params
AccountApi::open_order_lists_status_payload(const OpenOrderListsStatusParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<OpenOrderListsStatusResponseResultInner>>
AccountApi::open_order_lists_status(const OpenOrderListsStatusParams& params) const {
    return common::send<std::vector<OpenOrderListsStatusResponseResultInner>>(
        *client_, "openOrderLists.status", open_order_lists_status_payload(params),
        make_options(false, true, false, false));
}

common::Params AccountApi::open_orders_status_payload(const OpenOrdersStatusParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<OpenOrdersStatusResponseResultInner>>
AccountApi::open_orders_status(const OpenOrdersStatusParams& params) const {
    return common::send<std::vector<OpenOrdersStatusResponseResultInner>>(
        *client_, "openOrders.status", open_orders_status_payload(params),
        make_options(false, true, false, false));
}

common::Params AccountApi::order_amendments_payload(const OrderAmendmentsParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "fromExecutionId", params.from_execution_id);
    common::detail::json::set_param(p, "limit", params.limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<OrderAmendmentsResponseResultInner>>
AccountApi::order_amendments(const OrderAmendmentsParams& params) const {
    return common::send<std::vector<OrderAmendmentsResponseResultInner>>(
        *client_, "order.amendments", order_amendments_payload(params),
        make_options(false, true, false, false));
}

common::Params AccountApi::order_list_status_payload(const OrderListStatusParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(p, "orderListId", params.order_list_id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderListStatusResponseResult>
AccountApi::order_list_status(const OrderListStatusParams& params) const {
    return common::send<OrderListStatusResponseResult>(*client_, "orderList.status",
                                                       order_list_status_payload(params),
                                                       make_options(false, true, false, false));
}

common::Params AccountApi::order_status_payload(const OrderStatusParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderStatusResponseResult>
AccountApi::order_status(const OrderStatusParams& params) const {
    return common::send<OrderStatusResponseResult>(*client_, "order.status",
                                                   order_status_payload(params),
                                                   make_options(false, true, false, false));
}

} // namespace binance::spot::websocket_api
