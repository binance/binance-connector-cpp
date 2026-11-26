//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/api_management_api.hpp>

namespace binance::sub_account::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

ApiManagementApi::ApiManagementApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest ApiManagementApi::add_ip_restriction_for_sub_account_api_key_request(
    const AddIpRestrictionForSubAccountApiKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v2/sub-account/subAccountApi/ipRestriction";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "subAccountApiKey", params.sub_account_api_key);
    common::detail::json::set_param(req.query, "status", params.status);
    common::detail::json::set_param(req.query, "ipAddress", params.ip_address);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AddIpRestrictionForSubAccountApiKeyResponse>
ApiManagementApi::add_ip_restriction_for_sub_account_api_key(
    const AddIpRestrictionForSubAccountApiKeyParams& params) const {
    return common::send<AddIpRestrictionForSubAccountApiKeyResponse>(
        *client_, add_ip_restriction_for_sub_account_api_key_request(params));
}

common::RestRequest ApiManagementApi::create_sub_account_api_key_request(
    const CreateSubAccountApiKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/subAccountApi";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "apiName", params.api_name);
    common::detail::json::set_param(req.query, "status", params.status);
    common::detail::json::set_param(req.query, "canTrade", params.can_trade);
    common::detail::json::set_param(req.query, "canMarginLoanRepay", params.can_margin_loan_repay);
    common::detail::json::set_param(req.query, "canFuturesTrade", params.can_futures_trade);
    common::detail::json::set_param(req.query, "canUniversalTransfer",
                                    params.can_universal_transfer);
    common::detail::json::set_param(req.query, "canVanillaOptions", params.can_vanilla_options);
    common::detail::json::set_param(req.query, "canFixApiTrading", params.can_fix_api_trading);
    common::detail::json::set_param(req.query, "canFixApiReading", params.can_fix_api_reading);
    common::detail::json::set_param(req.query, "ipAddress", params.ip_address);
    common::detail::json::set_param(req.query, "thirdPartyName", params.third_party_name);
    common::detail::json::set_param(req.query, "publicKey", params.public_key);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CreateSubAccountApiKeyResponse>
ApiManagementApi::create_sub_account_api_key(const CreateSubAccountApiKeyParams& params) const {
    return common::send<CreateSubAccountApiKeyResponse>(*client_,
                                                        create_sub_account_api_key_request(params));
}

common::RestRequest ApiManagementApi::delete_sub_account_api_key_request(
    const DeleteSubAccountApiKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/sub-account/subAccountApi";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "subAccountApiKey", params.sub_account_api_key);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<boost::json::value>
ApiManagementApi::delete_sub_account_api_key(const DeleteSubAccountApiKeyParams& params) const {
    return common::send<boost::json::value>(*client_, delete_sub_account_api_key_request(params));
}

common::RestRequest ApiManagementApi::query_sub_account_api_key_request(
    const QuerySubAccountApiKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/subAccountApi";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "subAccountApiKey", params.sub_account_api_key);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySubAccountApiKeyResponse>
ApiManagementApi::query_sub_account_api_key(const QuerySubAccountApiKeyParams& params) const {
    return common::send<QuerySubAccountApiKeyResponse>(*client_,
                                                       query_sub_account_api_key_request(params));
}

common::RestRequest ApiManagementApi::create_sub_account_api_key_v2_request(
    const CreateSubAccountApiKeyV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v2/sub-account/subAccountApi";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "apiName", params.api_name);
    common::detail::json::set_param(req.query, "status", params.status);
    common::detail::json::set_param(req.query, "canTrade", params.can_trade);
    common::detail::json::set_param(req.query, "canMarginLoanRepay", params.can_margin_loan_repay);
    common::detail::json::set_param(req.query, "canFuturesTrade", params.can_futures_trade);
    common::detail::json::set_param(req.query, "canUniversalTransfer",
                                    params.can_universal_transfer);
    common::detail::json::set_param(req.query, "canVanillaOptions", params.can_vanilla_options);
    common::detail::json::set_param(req.query, "canFixApiTrading", params.can_fix_api_trading);
    common::detail::json::set_param(req.query, "canFixApiReading", params.can_fix_api_reading);
    common::detail::json::set_param(req.query, "ipAddress", params.ip_address);
    common::detail::json::set_param(req.query, "thirdPartyName", params.third_party_name);
    common::detail::json::set_param(req.query, "publicKey", params.public_key);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CreateSubAccountApiKeyV2Response>
ApiManagementApi::create_sub_account_api_key_v2(
    const CreateSubAccountApiKeyV2Params& params) const {
    return common::send<CreateSubAccountApiKeyV2Response>(
        *client_, create_sub_account_api_key_v2_request(params));
}

common::RestRequest ApiManagementApi::delete_ip_list_for_a_sub_account_api_key_request(
    const DeleteIpListForASubAccountApiKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/sub-account/subAccountApi/ipRestriction/ipList";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "subAccountApiKey", params.sub_account_api_key);
    common::detail::json::set_param(req.query, "ipAddress", params.ip_address);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DeleteIpListForASubAccountApiKeyResponse>
ApiManagementApi::delete_ip_list_for_a_sub_account_api_key(
    const DeleteIpListForASubAccountApiKeyParams& params) const {
    return common::send<DeleteIpListForASubAccountApiKeyResponse>(
        *client_, delete_ip_list_for_a_sub_account_api_key_request(params));
}

common::RestRequest ApiManagementApi::get_ip_restriction_for_a_sub_account_api_key_request(
    const GetIpRestrictionForASubAccountApiKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/subAccountApi/ipRestriction";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "subAccountApiKey", params.sub_account_api_key);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetIpRestrictionForASubAccountApiKeyResponse>
ApiManagementApi::get_ip_restriction_for_a_sub_account_api_key(
    const GetIpRestrictionForASubAccountApiKeyParams& params) const {
    return common::send<GetIpRestrictionForASubAccountApiKeyResponse>(
        *client_, get_ip_restriction_for_a_sub_account_api_key_request(params));
}

common::RestRequest ApiManagementApi::modify_sub_account_api_key_permission_request(
    const ModifySubAccountApiKeyPermissionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/subAccountApiPermission";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "subAccountApiKey", params.sub_account_api_key);
    common::detail::json::set_param(req.query, "canTrade", params.can_trade);
    common::detail::json::set_param(req.query, "canMarginLoanRepay", params.can_margin_loan_repay);
    common::detail::json::set_param(req.query, "canFuturesTrade", params.can_futures_trade);
    common::detail::json::set_param(req.query, "canUniversalTransfer",
                                    params.can_universal_transfer);
    common::detail::json::set_param(req.query, "canVanillaOptions", params.can_vanilla_options);
    common::detail::json::set_param(req.query, "canFixApiTrading", params.can_fix_api_trading);
    common::detail::json::set_param(req.query, "canFixApiReading", params.can_fix_api_reading);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ModifySubAccountApiKeyPermissionResponse>
ApiManagementApi::modify_sub_account_api_key_permission(
    const ModifySubAccountApiKeyPermissionParams& params) const {
    return common::send<ModifySubAccountApiKeyPermissionResponse>(
        *client_, modify_sub_account_api_key_permission_request(params));
}

} // namespace binance::sub_account::rest_api
