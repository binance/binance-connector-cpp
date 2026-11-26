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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/add_ip_restriction_for_sub_account_api_key_response.hpp>
#include <binance/sub_account/rest_api/models/create_sub_account_api_key_response.hpp>
#include <binance/sub_account/rest_api/models/create_sub_account_api_key_v2_response.hpp>
#include <binance/sub_account/rest_api/models/delete_ip_list_for_a_sub_account_api_key_response.hpp>
#include <binance/sub_account/rest_api/models/get_ip_restriction_for_a_sub_account_api_key_response.hpp>
#include <binance/sub_account/rest_api/models/modify_sub_account_api_key_permission_response.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_api_key_response.hpp>

namespace binance::sub_account::rest_api {

struct AddIpRestrictionForSubAccountApiKeyParams {
    common::Required<std::string> email;
    common::Required<std::string> sub_account_api_key;
    /// IP Restriction status. 1 = IP Unrestricted. 2 = Restrict access to trusted IPs only.
    common::Required<std::int64_t> status;
    /// Insert static IP in batch, separated by commas.
    std::optional<std::string> ip_address = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CreateSubAccountApiKeyParams {
    /// Sub-account email
    common::Required<std::string> email;
    /// API Key name
    common::Required<std::string> api_name;
    /// IP restriction status. 1 = unrestricted, 2 = restricted to trusted IPs, 3 = third-party IP
    /// restriction
    common::Required<std::int64_t> status;
    /// Spot & Margin trading permission, default false
    std::optional<bool> can_trade = std::nullopt;
    /// Margin borrow/repay permission, default false
    std::optional<bool> can_margin_loan_repay = std::nullopt;
    /// Futures trading permission, default false
    std::optional<bool> can_futures_trade = std::nullopt;
    /// Universal transfer permission, default false
    std::optional<bool> can_universal_transfer = std::nullopt;
    /// Vanilla options permission, default false
    std::optional<bool> can_vanilla_options = std::nullopt;
    /// FIX API Trading permission. Only supported for API Keys using an Ed25519 public key. Setting
    /// it to `true` for any other key type returns `-9000` `Unsupported operation`
    std::optional<bool> can_fix_api_trading = std::nullopt;
    /// FIX API Reading permission. Only supported for API Keys using an Ed25519 public key. Setting
    /// it to `true` for any other key type returns `-9000` `Unsupported operation`
    std::optional<bool> can_fix_api_reading = std::nullopt;
    /// Required when status=2. IP address list, max 500 chars
    std::optional<std::string> ip_address = std::nullopt;
    /// Required when status=3. Third-party name
    std::optional<std::string> third_party_name = std::nullopt;
    /// Ed25519 public key (optional, for Ed25519 type API Key)
    std::optional<std::string> public_key = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DeleteSubAccountApiKeyParams {
    /// Sub-account email
    common::Required<std::string> email;
    /// The sub-account API Key to be deleted
    common::Required<std::string> sub_account_api_key;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySubAccountApiKeyParams {
    /// Sub-account email
    common::Required<std::string> email;
    /// Specify an API Key for exact match
    std::optional<std::string> sub_account_api_key = std::nullopt;
    /// Page number, default 1, minimum 1
    std::optional<std::int64_t> page = std::nullopt;
    /// Page size, default 30, maximum 100
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CreateSubAccountApiKeyV2Params {
    /// Sub-account email
    common::Required<std::string> email;
    /// API Key name
    common::Required<std::string> api_name;
    /// IP restriction status. 1 = unrestricted, 2 = restricted to trusted IPs, 3 = third-party IP
    /// restriction
    common::Required<std::int64_t> status;
    /// Spot & Margin trading permission, default false
    std::optional<bool> can_trade = std::nullopt;
    /// Margin borrow/repay permission, default false
    std::optional<bool> can_margin_loan_repay = std::nullopt;
    /// Futures trading permission, default false
    std::optional<bool> can_futures_trade = std::nullopt;
    /// Universal transfer permission, default false
    std::optional<bool> can_universal_transfer = std::nullopt;
    /// Vanilla options permission, default false
    std::optional<bool> can_vanilla_options = std::nullopt;
    /// FIX API Trading permission. Only supported for API Keys using an Ed25519 public key. Setting
    /// it to `true` for any other key type returns `-9000` `Unsupported operation`
    std::optional<bool> can_fix_api_trading = std::nullopt;
    /// FIX API Reading permission. Only supported for API Keys using an Ed25519 public key. Setting
    /// it to `true` for any other key type returns `-9000` `Unsupported operation`
    std::optional<bool> can_fix_api_reading = std::nullopt;
    /// Required when status=2. IP address list, max 500 chars
    std::optional<std::string> ip_address = std::nullopt;
    /// Required when status=3. Third-party name
    std::optional<std::string> third_party_name = std::nullopt;
    /// RSA or Ed25519 public key (optional). Must be sent in the request body; it is rejected if
    /// passed in the URL query string
    std::optional<std::string> public_key = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DeleteIpListForASubAccountApiKeyParams {
    common::Required<std::string> email;
    common::Required<std::string> sub_account_api_key;
    /// IPs to be deleted. Can be added in batches, separated by commas
    common::Required<std::string> ip_address;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetIpRestrictionForASubAccountApiKeyParams {
    common::Required<std::string> email;
    common::Required<std::string> sub_account_api_key;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifySubAccountApiKeyPermissionParams {
    /// Sub-account email
    common::Required<std::string> email;
    /// Sub-account API Key
    common::Required<std::string> sub_account_api_key;
    /// Spot & Margin trading permission
    std::optional<bool> can_trade = std::nullopt;
    /// Margin borrow/repay permission
    std::optional<bool> can_margin_loan_repay = std::nullopt;
    /// Futures trading permission
    std::optional<bool> can_futures_trade = std::nullopt;
    /// Universal transfer permission
    std::optional<bool> can_universal_transfer = std::nullopt;
    /// Vanilla options permission
    std::optional<bool> can_vanilla_options = std::nullopt;
    /// FIX API Trading permission. If omitted, the existing value is unchanged. Only supported for
    /// API Keys using an Ed25519 public key. Setting it to `true` for any other key type returns
    /// `-9000` `Unsupported operation`
    std::optional<bool> can_fix_api_trading = std::nullopt;
    /// FIX API Reading permission. If omitted, the existing value is unchanged. Only supported for
    /// API Keys using an Ed25519 public key. Setting it to `true` for any other key type returns
    /// `-9000` `Unsupported operation`
    std::optional<bool> can_fix_api_reading = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_SUB_ACCOUNT_EXPORT ApiManagementApi {
public:
    explicit ApiManagementApi(std::shared_ptr<common::RestClient> client);

    /// Add IP Restriction for Sub-Account API key (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v2/sub-account/subAccountApi/ipRestriction.
    ///
    /// Add IP Restriction for Sub-Account API key
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable Enable Spot & Margin Trading option for the api key which requests this
    /// endpoint
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/api-management#add-ip-restriction-for-sub-account-api-key
    [[nodiscard]] common::RestApiResponse<AddIpRestrictionForSubAccountApiKeyResponse>
    add_ip_restriction_for_sub_account_api_key(
        const AddIpRestrictionForSubAccountApiKeyParams& params) const;

    /// Asynchronous `add_ip_restriction_for_sub_account_api_key()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<AddIpRestrictionForSubAccountApiKeyResponse>)`.
    template <class CompletionToken>
    auto async_add_ip_restriction_for_sub_account_api_key(
        const AddIpRestrictionForSubAccountApiKeyParams& params, CompletionToken&& token) const {
        return common::async_send<AddIpRestrictionForSubAccountApiKeyResponse>(
            client_, add_ip_restriction_for_sub_account_api_key_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Create Sub-account API Key (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/subAccountApi.
    ///
    /// Create a new API Key for a sub-account.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `status=2` requires `ipAddress`
    /// - `status=3` requires `thirdPartyName`
    /// - Asset Sub Account is not supported
    /// - The caller must pass the KYC IP restriction check
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/api-management#create-sub-account-api-key
    [[nodiscard]] common::RestApiResponse<CreateSubAccountApiKeyResponse>
    create_sub_account_api_key(const CreateSubAccountApiKeyParams& params) const;

    /// Asynchronous `create_sub_account_api_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateSubAccountApiKeyResponse>)`.
    template <class CompletionToken>
    auto async_create_sub_account_api_key(const CreateSubAccountApiKeyParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<CreateSubAccountApiKeyResponse>(
            client_, create_sub_account_api_key_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Delete Sub-account API Key (For Master Account) (USER_DATA)
    ///
    /// DELETE /sapi/v1/sub-account/subAccountApi.
    ///
    /// Delete an API Key of a sub-account.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Asset Sub Account is not supported
    /// - The caller must pass the KYC IP restriction check
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/api-management#delete-sub-account-api-key
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    delete_sub_account_api_key(const DeleteSubAccountApiKeyParams& params) const;

    /// Asynchronous `delete_sub_account_api_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_delete_sub_account_api_key(const DeleteSubAccountApiKeyParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_,
                                                      delete_sub_account_api_key_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Query Sub-account API Key (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/subAccountApi.
    ///
    /// Query the API Key list of a sub-account.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/api-management#query-sub-account-api-key
    [[nodiscard]] common::RestApiResponse<QuerySubAccountApiKeyResponse>
    query_sub_account_api_key(const QuerySubAccountApiKeyParams& params) const;

    /// Asynchronous `query_sub_account_api_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QuerySubAccountApiKeyResponse>)`.
    template <class CompletionToken>
    auto async_query_sub_account_api_key(const QuerySubAccountApiKeyParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<QuerySubAccountApiKeyResponse>(
            client_, query_sub_account_api_key_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Create Sub-account API Key V2 (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v2/sub-account/subAccountApi.
    ///
    /// Create a new API Key for a sub-account.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `status=2` requires `ipAddress`
    /// - `status=3` requires `thirdPartyName`
    /// - Asset Sub Account is not supported
    /// - The caller must pass the KYC IP restriction check
    /// - `publicKey` is rejected if passed in the URL query string. The example sends it in the
    /// request body with `--data-urlencode`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/api-management#create-sub-account-api-key-v2
    [[nodiscard]] common::RestApiResponse<CreateSubAccountApiKeyV2Response>
    create_sub_account_api_key_v2(const CreateSubAccountApiKeyV2Params& params) const;

    /// Asynchronous `create_sub_account_api_key_v2()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateSubAccountApiKeyV2Response>)`.
    template <class CompletionToken>
    auto async_create_sub_account_api_key_v2(const CreateSubAccountApiKeyV2Params& params,
                                             CompletionToken&& token) const {
        return common::async_send<CreateSubAccountApiKeyV2Response>(
            client_, create_sub_account_api_key_v2_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Delete IP List For a Sub-account API Key (For Master Account) (USER_DATA)
    ///
    /// DELETE /sapi/v1/sub-account/subAccountApi/ipRestriction/ipList.
    ///
    /// Delete IP List For a Sub-account API Key
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable Enable Spot & Margin Trading option for the api key which requests this
    /// endpoint
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/api-management#delete-ip-list-for-asub-account-api-key
    [[nodiscard]] common::RestApiResponse<DeleteIpListForASubAccountApiKeyResponse>
    delete_ip_list_for_a_sub_account_api_key(
        const DeleteIpListForASubAccountApiKeyParams& params) const;

    /// Asynchronous `delete_ip_list_for_a_sub_account_api_key()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<DeleteIpListForASubAccountApiKeyResponse>)`.
    template <class CompletionToken>
    auto async_delete_ip_list_for_a_sub_account_api_key(
        const DeleteIpListForASubAccountApiKeyParams& params, CompletionToken&& token) const {
        return common::async_send<DeleteIpListForASubAccountApiKeyResponse>(
            client_, delete_ip_list_for_a_sub_account_api_key_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get IP Restriction for a Sub-account API Key (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/subAccountApi/ipRestriction.
    ///
    /// Get IP Restriction for a Sub-account API Key
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/api-management#get-ip-restriction-for-asub-account-api-key
    [[nodiscard]] common::RestApiResponse<GetIpRestrictionForASubAccountApiKeyResponse>
    get_ip_restriction_for_a_sub_account_api_key(
        const GetIpRestrictionForASubAccountApiKeyParams& params) const;

    /// Asynchronous `get_ip_restriction_for_a_sub_account_api_key()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetIpRestrictionForASubAccountApiKeyResponse>)`.
    template <class CompletionToken>
    auto async_get_ip_restriction_for_a_sub_account_api_key(
        const GetIpRestrictionForASubAccountApiKeyParams& params, CompletionToken&& token) const {
        return common::async_send<GetIpRestrictionForASubAccountApiKeyResponse>(
            client_, get_ip_restriction_for_a_sub_account_api_key_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Modify Sub-account API Key Permission (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/subAccountApiPermission.
    ///
    /// Modify the trading permissions of a sub-account API Key.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Portfolio Margin Retail User is not supported
    /// - Asset Sub Account is not supported
    /// - The caller must pass the KYC IP restriction check
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/api-management#modify-sub-account-api-key-permission
    [[nodiscard]] common::RestApiResponse<ModifySubAccountApiKeyPermissionResponse>
    modify_sub_account_api_key_permission(
        const ModifySubAccountApiKeyPermissionParams& params) const;

    /// Asynchronous `modify_sub_account_api_key_permission()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<ModifySubAccountApiKeyPermissionResponse>)`.
    template <class CompletionToken>
    auto async_modify_sub_account_api_key_permission(
        const ModifySubAccountApiKeyPermissionParams& params, CompletionToken&& token) const {
        return common::async_send<ModifySubAccountApiKeyPermissionResponse>(
            client_, modify_sub_account_api_key_permission_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest add_ip_restriction_for_sub_account_api_key_request(
        const AddIpRestrictionForSubAccountApiKeyParams& params) const;
    [[nodiscard]] common::RestRequest
    create_sub_account_api_key_request(const CreateSubAccountApiKeyParams& params) const;
    [[nodiscard]] common::RestRequest
    delete_sub_account_api_key_request(const DeleteSubAccountApiKeyParams& params) const;
    [[nodiscard]] common::RestRequest
    query_sub_account_api_key_request(const QuerySubAccountApiKeyParams& params) const;
    [[nodiscard]] common::RestRequest
    create_sub_account_api_key_v2_request(const CreateSubAccountApiKeyV2Params& params) const;
    [[nodiscard]] common::RestRequest delete_ip_list_for_a_sub_account_api_key_request(
        const DeleteIpListForASubAccountApiKeyParams& params) const;
    [[nodiscard]] common::RestRequest get_ip_restriction_for_a_sub_account_api_key_request(
        const GetIpRestrictionForASubAccountApiKeyParams& params) const;
    [[nodiscard]] common::RestRequest modify_sub_account_api_key_permission_request(
        const ModifySubAccountApiKeyPermissionParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::sub_account::rest_api
