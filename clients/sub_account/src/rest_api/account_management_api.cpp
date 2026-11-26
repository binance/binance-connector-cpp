//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/account_management_api.hpp>

namespace binance::sub_account::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

AccountManagementApi::AccountManagementApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest AccountManagementApi::create_a_virtual_sub_account_request(
    const CreateAVirtualSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/virtualSubAccount";
    common::detail::json::set_param(req.query, "subAccountString", params.sub_account_string);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CreateAVirtualSubAccountResponse>
AccountManagementApi::create_a_virtual_sub_account(
    const CreateAVirtualSubAccountParams& params) const {
    return common::send<CreateAVirtualSubAccountResponse>(
        *client_, create_a_virtual_sub_account_request(params));
}

common::RestRequest AccountManagementApi::enable_futures_for_sub_account_request(
    const EnableFuturesForSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/futures/enable";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<EnableFuturesForSubAccountResponse>
AccountManagementApi::enable_futures_for_sub_account(
    const EnableFuturesForSubAccountParams& params) const {
    return common::send<EnableFuturesForSubAccountResponse>(
        *client_, enable_futures_for_sub_account_request(params));
}

common::RestRequest AccountManagementApi::enable_options_for_sub_account_request(
    const EnableOptionsForSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/eoptions/enable";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<EnableOptionsForSubAccountResponse>
AccountManagementApi::enable_options_for_sub_account(
    const EnableOptionsForSubAccountParams& params) const {
    return common::send<EnableOptionsForSubAccountResponse>(
        *client_, enable_options_for_sub_account_request(params));
}

common::RestRequest AccountManagementApi::get_futures_position_risk_of_sub_account_request(
    const GetFuturesPositionRiskOfSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/futures/positionRisk";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetFuturesPositionRiskOfSubAccountResponseInner>>
AccountManagementApi::get_futures_position_risk_of_sub_account(
    const GetFuturesPositionRiskOfSubAccountParams& params) const {
    return common::send<std::vector<GetFuturesPositionRiskOfSubAccountResponseInner>>(
        *client_, get_futures_position_risk_of_sub_account_request(params));
}

common::RestRequest AccountManagementApi::get_futures_position_risk_of_sub_account_v2_request(
    const GetFuturesPositionRiskOfSubAccountV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/sub-account/futures/positionRisk";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "futuresType", params.futures_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFuturesPositionRiskOfSubAccountV2Response>
AccountManagementApi::get_futures_position_risk_of_sub_account_v2(
    const GetFuturesPositionRiskOfSubAccountV2Params& params) const {
    return common::send<GetFuturesPositionRiskOfSubAccountV2Response>(
        *client_, get_futures_position_risk_of_sub_account_v2_request(params));
}

common::RestRequest AccountManagementApi::get_sub_accounts_status_on_margin_or_futures_request(
    const GetSubAccountsStatusOnMarginOrFuturesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/status";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetSubAccountsStatusOnMarginOrFuturesResponseInner>>
AccountManagementApi::get_sub_accounts_status_on_margin_or_futures(
    const GetSubAccountsStatusOnMarginOrFuturesParams& params) const {
    return common::send<std::vector<GetSubAccountsStatusOnMarginOrFuturesResponseInner>>(
        *client_, get_sub_accounts_status_on_margin_or_futures_request(params));
}

common::RestRequest AccountManagementApi::query_sub_account_list_request(
    const QuerySubAccountListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/list";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "isFreeze", params.is_freeze);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySubAccountListResponse>
AccountManagementApi::query_sub_account_list(const QuerySubAccountListParams& params) const {
    return common::send<QuerySubAccountListResponse>(*client_,
                                                     query_sub_account_list_request(params));
}

common::RestRequest AccountManagementApi::query_sub_account_transaction_statistics_request(
    const QuerySubAccountTransactionStatisticsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/transaction-statistics";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySubAccountTransactionStatisticsResponse>
AccountManagementApi::query_sub_account_transaction_statistics(
    const QuerySubAccountTransactionStatisticsParams& params) const {
    return common::send<QuerySubAccountTransactionStatisticsResponse>(
        *client_, query_sub_account_transaction_statistics_request(params));
}

} // namespace binance::sub_account::rest_api
