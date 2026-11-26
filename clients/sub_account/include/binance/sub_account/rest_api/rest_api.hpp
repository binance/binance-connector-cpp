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
#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/account_management_api.hpp>
#include <binance/sub_account/rest_api/api_management_api.hpp>
#include <binance/sub_account/rest_api/asset_management_api.hpp>
#include <binance/sub_account/rest_api/managed_sub_account_api.hpp>
#include <binance/sub_account/rest_api/models.hpp>

namespace binance::sub_account::rest_api {

/// SubAccount REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_SUB_ACCOUNT_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Sub Account REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);

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

    // AccountManagementApi

    /// Create a Virtual Sub-account (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/virtualSubAccount.
    ///
    /// Create a Virtual Sub-account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - This request generates a virtual sub-account under your master account.
    /// - The API key used to call this endpoint must have the `trade` option enabled.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/account-management#create-avirtual-sub-account
    [[nodiscard]] common::RestApiResponse<CreateAVirtualSubAccountResponse>
    create_a_virtual_sub_account(const CreateAVirtualSubAccountParams& params) const {
        return account_management_api_.create_a_virtual_sub_account(params);
    }
    /// Asynchronous `create_a_virtual_sub_account()`.
    template <class CompletionToken>
    auto async_create_a_virtual_sub_account(const CreateAVirtualSubAccountParams& params,
                                            CompletionToken&& token) const {
        return account_management_api_.async_create_a_virtual_sub_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Enable Futures for Sub-account (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/futures/enable.
    ///
    /// Enable Futures for Sub-account for Master Account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/account-management#enable-futures-for-sub-account
    [[nodiscard]] common::RestApiResponse<EnableFuturesForSubAccountResponse>
    enable_futures_for_sub_account(const EnableFuturesForSubAccountParams& params) const {
        return account_management_api_.enable_futures_for_sub_account(params);
    }
    /// Asynchronous `enable_futures_for_sub_account()`.
    template <class CompletionToken>
    auto async_enable_futures_for_sub_account(const EnableFuturesForSubAccountParams& params,
                                              CompletionToken&& token) const {
        return account_management_api_.async_enable_futures_for_sub_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Enable Options for Sub-account (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/eoptions/enable.
    ///
    /// Enable Options for Sub-account (For Master Account).
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/account-management#enable-options-for-sub-account
    [[nodiscard]] common::RestApiResponse<EnableOptionsForSubAccountResponse>
    enable_options_for_sub_account(const EnableOptionsForSubAccountParams& params) const {
        return account_management_api_.enable_options_for_sub_account(params);
    }
    /// Asynchronous `enable_options_for_sub_account()`.
    template <class CompletionToken>
    auto async_enable_options_for_sub_account(const EnableOptionsForSubAccountParams& params,
                                              CompletionToken&& token) const {
        return account_management_api_.async_enable_options_for_sub_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Futures Position-Risk of Sub-account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/futures/positionRisk.
    ///
    /// Get Futures Position-Risk of Sub-account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/account-management#get-futures-position-risk-of-sub-account
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetFuturesPositionRiskOfSubAccountResponseInner>>
    get_futures_position_risk_of_sub_account(
        const GetFuturesPositionRiskOfSubAccountParams& params) const {
        return account_management_api_.get_futures_position_risk_of_sub_account(params);
    }
    /// Asynchronous `get_futures_position_risk_of_sub_account()`.
    template <class CompletionToken>
    auto async_get_futures_position_risk_of_sub_account(
        const GetFuturesPositionRiskOfSubAccountParams& params, CompletionToken&& token) const {
        return account_management_api_.async_get_futures_position_risk_of_sub_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Futures Position-Risk of Sub-account V2 (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v2/sub-account/futures/positionRisk.
    ///
    /// Get Futures Position-Risk of Sub-account V2
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/account-management#get-futures-position-risk-of-sub-account-v2
    [[nodiscard]] common::RestApiResponse<GetFuturesPositionRiskOfSubAccountV2Response>
    get_futures_position_risk_of_sub_account_v2(
        const GetFuturesPositionRiskOfSubAccountV2Params& params) const {
        return account_management_api_.get_futures_position_risk_of_sub_account_v2(params);
    }
    /// Asynchronous `get_futures_position_risk_of_sub_account_v2()`.
    template <class CompletionToken>
    auto async_get_futures_position_risk_of_sub_account_v2(
        const GetFuturesPositionRiskOfSubAccountV2Params& params, CompletionToken&& token) const {
        return account_management_api_.async_get_futures_position_risk_of_sub_account_v2(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Sub-account's Status on Margin Or Futures (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/status.
    ///
    /// Get Sub-account's Status on Margin Or Futures
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If no email sent, all sub-accounts' information will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/account-management#get-sub-accounts-status-on-margin-or-futures
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetSubAccountsStatusOnMarginOrFuturesResponseInner>>
    get_sub_accounts_status_on_margin_or_futures(
        const GetSubAccountsStatusOnMarginOrFuturesParams& params = {}) const {
        return account_management_api_.get_sub_accounts_status_on_margin_or_futures(params);
    }
    /// Asynchronous `get_sub_accounts_status_on_margin_or_futures()`.
    template <class CompletionToken>
    auto async_get_sub_accounts_status_on_margin_or_futures(
        const GetSubAccountsStatusOnMarginOrFuturesParams& params, CompletionToken&& token) const {
        return account_management_api_.async_get_sub_accounts_status_on_margin_or_futures(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Sub-account List (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/list.
    ///
    /// Query Sub-account List
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/account-management#query-sub-account-list
    [[nodiscard]] common::RestApiResponse<QuerySubAccountListResponse>
    query_sub_account_list(const QuerySubAccountListParams& params = {}) const {
        return account_management_api_.query_sub_account_list(params);
    }
    /// Asynchronous `query_sub_account_list()`.
    template <class CompletionToken>
    auto async_query_sub_account_list(const QuerySubAccountListParams& params,
                                      CompletionToken&& token) const {
        return account_management_api_.async_query_sub_account_list(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Transaction Statistics (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/transaction-statistics.
    ///
    /// Query Sub-account Transaction statistics (For Master Account).
    ///
    /// Weight(IP): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/account-management#query-sub-account-transaction-statistics
    [[nodiscard]] common::RestApiResponse<QuerySubAccountTransactionStatisticsResponse>
    query_sub_account_transaction_statistics(
        const QuerySubAccountTransactionStatisticsParams& params = {}) const {
        return account_management_api_.query_sub_account_transaction_statistics(params);
    }
    /// Asynchronous `query_sub_account_transaction_statistics()`.
    template <class CompletionToken>
    auto async_query_sub_account_transaction_statistics(
        const QuerySubAccountTransactionStatisticsParams& params, CompletionToken&& token) const {
        return account_management_api_.async_query_sub_account_transaction_statistics(
            params, std::forward<CompletionToken>(token));
    }

    // ApiManagementApi

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
        const AddIpRestrictionForSubAccountApiKeyParams& params) const {
        return api_management_api_.add_ip_restriction_for_sub_account_api_key(params);
    }
    /// Asynchronous `add_ip_restriction_for_sub_account_api_key()`.
    template <class CompletionToken>
    auto async_add_ip_restriction_for_sub_account_api_key(
        const AddIpRestrictionForSubAccountApiKeyParams& params, CompletionToken&& token) const {
        return api_management_api_.async_add_ip_restriction_for_sub_account_api_key(
            params, std::forward<CompletionToken>(token));
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
    create_sub_account_api_key(const CreateSubAccountApiKeyParams& params) const {
        return api_management_api_.create_sub_account_api_key(params);
    }
    /// Asynchronous `create_sub_account_api_key()`.
    template <class CompletionToken>
    auto async_create_sub_account_api_key(const CreateSubAccountApiKeyParams& params,
                                          CompletionToken&& token) const {
        return api_management_api_.async_create_sub_account_api_key(
            params, std::forward<CompletionToken>(token));
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
    delete_sub_account_api_key(const DeleteSubAccountApiKeyParams& params) const {
        return api_management_api_.delete_sub_account_api_key(params);
    }
    /// Asynchronous `delete_sub_account_api_key()`.
    template <class CompletionToken>
    auto async_delete_sub_account_api_key(const DeleteSubAccountApiKeyParams& params,
                                          CompletionToken&& token) const {
        return api_management_api_.async_delete_sub_account_api_key(
            params, std::forward<CompletionToken>(token));
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
    query_sub_account_api_key(const QuerySubAccountApiKeyParams& params) const {
        return api_management_api_.query_sub_account_api_key(params);
    }
    /// Asynchronous `query_sub_account_api_key()`.
    template <class CompletionToken>
    auto async_query_sub_account_api_key(const QuerySubAccountApiKeyParams& params,
                                         CompletionToken&& token) const {
        return api_management_api_.async_query_sub_account_api_key(
            params, std::forward<CompletionToken>(token));
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
    create_sub_account_api_key_v2(const CreateSubAccountApiKeyV2Params& params) const {
        return api_management_api_.create_sub_account_api_key_v2(params);
    }
    /// Asynchronous `create_sub_account_api_key_v2()`.
    template <class CompletionToken>
    auto async_create_sub_account_api_key_v2(const CreateSubAccountApiKeyV2Params& params,
                                             CompletionToken&& token) const {
        return api_management_api_.async_create_sub_account_api_key_v2(
            params, std::forward<CompletionToken>(token));
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
        const DeleteIpListForASubAccountApiKeyParams& params) const {
        return api_management_api_.delete_ip_list_for_a_sub_account_api_key(params);
    }
    /// Asynchronous `delete_ip_list_for_a_sub_account_api_key()`.
    template <class CompletionToken>
    auto async_delete_ip_list_for_a_sub_account_api_key(
        const DeleteIpListForASubAccountApiKeyParams& params, CompletionToken&& token) const {
        return api_management_api_.async_delete_ip_list_for_a_sub_account_api_key(
            params, std::forward<CompletionToken>(token));
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
        const GetIpRestrictionForASubAccountApiKeyParams& params) const {
        return api_management_api_.get_ip_restriction_for_a_sub_account_api_key(params);
    }
    /// Asynchronous `get_ip_restriction_for_a_sub_account_api_key()`.
    template <class CompletionToken>
    auto async_get_ip_restriction_for_a_sub_account_api_key(
        const GetIpRestrictionForASubAccountApiKeyParams& params, CompletionToken&& token) const {
        return api_management_api_.async_get_ip_restriction_for_a_sub_account_api_key(
            params, std::forward<CompletionToken>(token));
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
        const ModifySubAccountApiKeyPermissionParams& params) const {
        return api_management_api_.modify_sub_account_api_key_permission(params);
    }
    /// Asynchronous `modify_sub_account_api_key_permission()`.
    template <class CompletionToken>
    auto async_modify_sub_account_api_key_permission(
        const ModifySubAccountApiKeyPermissionParams& params, CompletionToken&& token) const {
        return api_management_api_.async_modify_sub_account_api_key_permission(
            params, std::forward<CompletionToken>(token));
    }

    // AssetManagementApi

    /// Futures Transfer for Sub-account (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/futures/transfer.
    ///
    /// Futures Transfer for Sub-account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#futures-transfer-for-sub-account
    [[nodiscard]] common::RestApiResponse<FuturesTransferForSubAccountResponse>
    futures_transfer_for_sub_account(const FuturesTransferForSubAccountParams& params) const {
        return asset_management_api_.futures_transfer_for_sub_account(params);
    }
    /// Asynchronous `futures_transfer_for_sub_account()`.
    template <class CompletionToken>
    auto async_futures_transfer_for_sub_account(const FuturesTransferForSubAccountParams& params,
                                                CompletionToken&& token) const {
        return asset_management_api_.async_futures_transfer_for_sub_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Detail on Sub-account's Futures Account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/futures/account.
    ///
    /// Get Detail on Sub-account's Futures Account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-detail-on-sub-accounts-futures-account
    [[nodiscard]] common::RestApiResponse<GetDetailOnSubAccountsFuturesAccountResponse>
    get_detail_on_sub_accounts_futures_account(
        const GetDetailOnSubAccountsFuturesAccountParams& params) const {
        return asset_management_api_.get_detail_on_sub_accounts_futures_account(params);
    }
    /// Asynchronous `get_detail_on_sub_accounts_futures_account()`.
    template <class CompletionToken>
    auto async_get_detail_on_sub_accounts_futures_account(
        const GetDetailOnSubAccountsFuturesAccountParams& params, CompletionToken&& token) const {
        return asset_management_api_.async_get_detail_on_sub_accounts_futures_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Detail on Sub-account's Futures Account V2 (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v2/sub-account/futures/account.
    ///
    /// Get Detail on Sub-account's Futures Account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-detail-on-sub-accounts-futures-account-v2
    [[nodiscard]] common::RestApiResponse<GetDetailOnSubAccountsFuturesAccountV2Response>
    get_detail_on_sub_accounts_futures_account_v2(
        const GetDetailOnSubAccountsFuturesAccountV2Params& params) const {
        return asset_management_api_.get_detail_on_sub_accounts_futures_account_v2(params);
    }
    /// Asynchronous `get_detail_on_sub_accounts_futures_account_v2()`.
    template <class CompletionToken>
    auto async_get_detail_on_sub_accounts_futures_account_v2(
        const GetDetailOnSubAccountsFuturesAccountV2Params& params, CompletionToken&& token) const {
        return asset_management_api_.async_get_detail_on_sub_accounts_futures_account_v2(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Detail on Sub-account's Margin Account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/margin/account.
    ///
    /// Get Detail on Sub-account's Margin Account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-detail-on-sub-accounts-margin-account
    [[nodiscard]] common::RestApiResponse<GetDetailOnSubAccountsMarginAccountResponse>
    get_detail_on_sub_accounts_margin_account(
        const GetDetailOnSubAccountsMarginAccountParams& params) const {
        return asset_management_api_.get_detail_on_sub_accounts_margin_account(params);
    }
    /// Asynchronous `get_detail_on_sub_accounts_margin_account()`.
    template <class CompletionToken>
    auto async_get_detail_on_sub_accounts_margin_account(
        const GetDetailOnSubAccountsMarginAccountParams& params, CompletionToken&& token) const {
        return asset_management_api_.async_get_detail_on_sub_accounts_margin_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Move Position History for Sub-account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/futures/move-position.
    ///
    /// Query move position history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are both omitted, records from the last 90 days are returned
    /// by default (up to 100 records).
    /// - If `startTime` is sent and `endTime` is omitted, records in `[max(startTime, now-90d),
    /// now]` are returned.
    /// - If `startTime` is omitted and `endTime` is sent, records in `[max(now, endTime-90d),
    /// endTime]` are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-move-position-history-for-sub-account
    [[nodiscard]] common::RestApiResponse<GetMovePositionHistoryForSubAccountResponse>
    get_move_position_history_for_sub_account(
        const GetMovePositionHistoryForSubAccountParams& params) const {
        return asset_management_api_.get_move_position_history_for_sub_account(params);
    }
    /// Asynchronous `get_move_position_history_for_sub_account()`.
    template <class CompletionToken>
    auto async_get_move_position_history_for_sub_account(
        const GetMovePositionHistoryForSubAccountParams& params, CompletionToken&& token) const {
        return asset_management_api_.async_get_move_position_history_for_sub_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Move Position for Sub-account (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/futures/move-position.
    ///
    /// Move position between sub-master, master-sub, or sub-sub accounts when necessary
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable the `Trading` permission for the API key used to call this endpoint.
    /// - This function is only available for VIP levels 7-9.
    /// - Only master accounts can call this endpoint.
    /// - `quantity` must be a positive number.
    /// - Supported account types: normal account, PM PRO, PM PRO SPAN, and PM Retail.
    /// - The source account must have positions.
    /// - For orders in the same `orderArgs` request, if any symbol's total close position quantity
    /// exceeds current position quantity, all orders in that batch fail.
    /// - Only cross margin mode is supported.
    /// - The move position price supports `MARK_PRICE` only.
    /// - MSA is not supported.
    /// - Symbols configured with `Reduce-Only` are not supported.
    /// - Move Position charges a trading fee. The fee rate is based on the master account's VIP
    /// level: the source account (`fromUserEmail`) is the taker and pays the taker fee, and the
    /// destination account (`toUserEmail`) is the maker and pays the maker fee.
    /// - The `clientOrderId` of orders generated by Move Position now starts with `otcCHGFE`
    /// (previously `otc-`).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#move-position-for-sub-account
    [[nodiscard]] common::RestApiResponse<MovePositionForSubAccountResponse>
    move_position_for_sub_account(const MovePositionForSubAccountParams& params) const {
        return asset_management_api_.move_position_for_sub_account(params);
    }
    /// Asynchronous `move_position_for_sub_account()`.
    template <class CompletionToken>
    auto async_move_position_for_sub_account(const MovePositionForSubAccountParams& params,
                                             CompletionToken&& token) const {
        return asset_management_api_.async_move_position_for_sub_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Sub-account Deposit Address (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/subAddress.
    ///
    /// Fetch sub-account deposit address
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `amount` needs to be sent if using LIGHTNING network
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-sub-account-deposit-address
    [[nodiscard]] common::RestApiResponse<GetSubAccountDepositAddressResponse>
    get_sub_account_deposit_address(const GetSubAccountDepositAddressParams& params) const {
        return asset_management_api_.get_sub_account_deposit_address(params);
    }
    /// Asynchronous `get_sub_account_deposit_address()`.
    template <class CompletionToken>
    auto async_get_sub_account_deposit_address(const GetSubAccountDepositAddressParams& params,
                                               CompletionToken&& token) const {
        return asset_management_api_.async_get_sub_account_deposit_address(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Sub-account Deposit History (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/subHisrec.
    ///
    /// Fetch sub-account deposit history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-sub-account-deposit-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetSubAccountDepositHistoryResponseInner>>
    get_sub_account_deposit_history(const GetSubAccountDepositHistoryParams& params) const {
        return asset_management_api_.get_sub_account_deposit_history(params);
    }
    /// Asynchronous `get_sub_account_deposit_history()`.
    template <class CompletionToken>
    auto async_get_sub_account_deposit_history(const GetSubAccountDepositHistoryParams& params,
                                               CompletionToken&& token) const {
        return asset_management_api_.async_get_sub_account_deposit_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Summary of Sub-account's Futures Account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/futures/accountSummary.
    ///
    /// Get Summary of Sub-account's Futures Account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-summary-of-sub-accounts-futures-account
    [[nodiscard]] common::RestApiResponse<GetSummaryOfSubAccountsFuturesAccountResponse>
    get_summary_of_sub_accounts_futures_account(
        const GetSummaryOfSubAccountsFuturesAccountParams& params) const {
        return asset_management_api_.get_summary_of_sub_accounts_futures_account(params);
    }
    /// Asynchronous `get_summary_of_sub_accounts_futures_account()`.
    template <class CompletionToken>
    auto async_get_summary_of_sub_accounts_futures_account(
        const GetSummaryOfSubAccountsFuturesAccountParams& params, CompletionToken&& token) const {
        return asset_management_api_.async_get_summary_of_sub_accounts_futures_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Summary of Sub-account's Futures Account V2 (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v2/sub-account/futures/accountSummary.
    ///
    /// Get Summary of Sub-account's Futures Account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-summary-of-sub-accounts-futures-account-v2
    [[nodiscard]] common::RestApiResponse<GetSummaryOfSubAccountsFuturesAccountV2Response>
    get_summary_of_sub_accounts_futures_account_v2(
        const GetSummaryOfSubAccountsFuturesAccountV2Params& params) const {
        return asset_management_api_.get_summary_of_sub_accounts_futures_account_v2(params);
    }
    /// Asynchronous `get_summary_of_sub_accounts_futures_account_v2()`.
    template <class CompletionToken>
    auto async_get_summary_of_sub_accounts_futures_account_v2(
        const GetSummaryOfSubAccountsFuturesAccountV2Params& params,
        CompletionToken&& token) const {
        return asset_management_api_.async_get_summary_of_sub_accounts_futures_account_v2(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Summary of Sub-account's Margin Account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/margin/accountSummary.
    ///
    /// Get Summary of Sub-account's Margin Account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-summary-of-sub-accounts-margin-account
    [[nodiscard]] common::RestApiResponse<GetSummaryOfSubAccountsMarginAccountResponse>
    get_summary_of_sub_accounts_margin_account(
        const GetSummaryOfSubAccountsMarginAccountParams& params = {}) const {
        return asset_management_api_.get_summary_of_sub_accounts_margin_account(params);
    }
    /// Asynchronous `get_summary_of_sub_accounts_margin_account()`.
    template <class CompletionToken>
    auto async_get_summary_of_sub_accounts_margin_account(
        const GetSummaryOfSubAccountsMarginAccountParams& params, CompletionToken&& token) const {
        return asset_management_api_.async_get_summary_of_sub_accounts_margin_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Margin Transfer for Sub-account (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/margin/transfer.
    ///
    /// Margin Transfer for Sub-account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#margin-transfer-for-sub-account
    [[nodiscard]] common::RestApiResponse<MarginTransferForSubAccountResponse>
    margin_transfer_for_sub_account(const MarginTransferForSubAccountParams& params) const {
        return asset_management_api_.margin_transfer_for_sub_account(params);
    }
    /// Asynchronous `margin_transfer_for_sub_account()`.
    template <class CompletionToken>
    auto async_margin_transfer_for_sub_account(const MarginTransferForSubAccountParams& params,
                                               CompletionToken&& token) const {
        return asset_management_api_.async_margin_transfer_for_sub_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Assets (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v3/sub-account/assets.
    ///
    /// Fetch sub-account assets
    ///
    /// Weight(UID): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-assets
    [[nodiscard]] common::RestApiResponse<QuerySubAccountAssetsResponse>
    query_sub_account_assets(const QuerySubAccountAssetsParams& params) const {
        return asset_management_api_.query_sub_account_assets(params);
    }
    /// Asynchronous `query_sub_account_assets()`.
    template <class CompletionToken>
    auto async_query_sub_account_assets(const QuerySubAccountAssetsParams& params,
                                        CompletionToken&& token) const {
        return asset_management_api_.async_query_sub_account_assets(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Assets V4 (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v4/sub-account/assets.
    ///
    /// Fetch sub-account assets
    ///
    /// Weight(UID): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-assets-asset-management
    [[nodiscard]] common::RestApiResponse<QuerySubAccountAssetsAssetManagementResponse>
    query_sub_account_assets_asset_management(
        const QuerySubAccountAssetsAssetManagementParams& params) const {
        return asset_management_api_.query_sub_account_assets_asset_management(params);
    }
    /// Asynchronous `query_sub_account_assets_asset_management()`.
    template <class CompletionToken>
    auto async_query_sub_account_assets_asset_management(
        const QuerySubAccountAssetsAssetManagementParams& params, CompletionToken&& token) const {
        return asset_management_api_.async_query_sub_account_assets_asset_management(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Futures Asset Transfer History (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/futures/internalTransfer.
    ///
    /// Query Sub-account Futures Asset Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-futures-asset-transfer-history
    [[nodiscard]] common::RestApiResponse<QuerySubAccountFuturesAssetTransferHistoryResponse>
    query_sub_account_futures_asset_transfer_history(
        const QuerySubAccountFuturesAssetTransferHistoryParams& params) const {
        return asset_management_api_.query_sub_account_futures_asset_transfer_history(params);
    }
    /// Asynchronous `query_sub_account_futures_asset_transfer_history()`.
    template <class CompletionToken>
    auto async_query_sub_account_futures_asset_transfer_history(
        const QuerySubAccountFuturesAssetTransferHistoryParams& params,
        CompletionToken&& token) const {
        return asset_management_api_.async_query_sub_account_futures_asset_transfer_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Sub-account Futures Asset Transfer (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/futures/internalTransfer.
    ///
    /// Sub-account Futures Asset Transfer
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - A master account can transfer at most 2000 times per minute.
    /// - The futures wallet must have sufficient margin balance to execute the transfer.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#sub-account-futures-asset-transfer
    [[nodiscard]] common::RestApiResponse<SubAccountFuturesAssetTransferResponse>
    sub_account_futures_asset_transfer(const SubAccountFuturesAssetTransferParams& params) const {
        return asset_management_api_.sub_account_futures_asset_transfer(params);
    }
    /// Asynchronous `sub_account_futures_asset_transfer()`.
    template <class CompletionToken>
    auto
    async_sub_account_futures_asset_transfer(const SubAccountFuturesAssetTransferParams& params,
                                             CompletionToken&& token) const {
        return asset_management_api_.async_sub_account_futures_asset_transfer(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Spot Asset Transfer History (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/sub/transfer/history.
    ///
    /// Query Sub-account Spot Asset Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `fromEmail` and `toEmail` cannot be sent at the same time.
    /// - If both `fromEmail` and `toEmail` are omitted, records with `fromEmail` equal to the
    /// master account are returned by default.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-spot-asset-transfer-history
    [[nodiscard]] common::RestApiResponse<
        std::vector<QuerySubAccountSpotAssetTransferHistoryResponseInner>>
    query_sub_account_spot_asset_transfer_history(
        const QuerySubAccountSpotAssetTransferHistoryParams& params = {}) const {
        return asset_management_api_.query_sub_account_spot_asset_transfer_history(params);
    }
    /// Asynchronous `query_sub_account_spot_asset_transfer_history()`.
    template <class CompletionToken>
    auto async_query_sub_account_spot_asset_transfer_history(
        const QuerySubAccountSpotAssetTransferHistoryParams& params,
        CompletionToken&& token) const {
        return asset_management_api_.async_query_sub_account_spot_asset_transfer_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Spot Assets Summary (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/spotSummary.
    ///
    /// Get BTC valued asset summary of subaccounts.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-spot-assets-summary
    [[nodiscard]] common::RestApiResponse<QuerySubAccountSpotAssetsSummaryResponse>
    query_sub_account_spot_assets_summary(
        const QuerySubAccountSpotAssetsSummaryParams& params = {}) const {
        return asset_management_api_.query_sub_account_spot_assets_summary(params);
    }
    /// Asynchronous `query_sub_account_spot_assets_summary()`.
    template <class CompletionToken>
    auto async_query_sub_account_spot_assets_summary(
        const QuerySubAccountSpotAssetsSummaryParams& params, CompletionToken&& token) const {
        return asset_management_api_.async_query_sub_account_spot_assets_summary(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Universal Transfer History (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/universalTransfer.
    ///
    /// Query Universal Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `fromEmail` and `toEmail` cannot be sent at the same time.
    /// - If both `fromEmail` and `toEmail` are omitted, records with `fromEmail` equal to the
    /// master account are returned by default.
    /// - The query time range must be less than 7 days.
    /// - If `startTime` and `endTime` are omitted, records from the last 7 days are returned by
    /// default.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-universal-transfer-history
    [[nodiscard]] common::RestApiResponse<QueryUniversalTransferHistoryResponse>
    query_universal_transfer_history(const QueryUniversalTransferHistoryParams& params = {}) const {
        return asset_management_api_.query_universal_transfer_history(params);
    }
    /// Asynchronous `query_universal_transfer_history()`.
    template <class CompletionToken>
    auto async_query_universal_transfer_history(const QueryUniversalTransferHistoryParams& params,
                                                CompletionToken&& token) const {
        return asset_management_api_.async_query_universal_transfer_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Universal Transfer (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/universalTransfer.
    ///
    /// Universal Transfer
    ///
    /// Weight(IP): 1
    ///
    /// Weight(UID): 360
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable the `internal transfer` option for the API key used to call this
    /// endpoint.
    /// - If `fromEmail` is not sent, transfer out from the master account by default.
    /// - If `toEmail` is not sent, transfer into the master account by default.
    /// - When `fromAccountType` and `toAccountType` are the same, at least one of `fromEmail` or
    /// `toEmail` must be sent.
    /// - Supported transfer scenarios:
    ///   - `SPOT` -> `SPOT` / `USDT_FUTURE` / `COIN_FUTURE` (master or sub-account).
    ///   - `SPOT` / `USDT_FUTURE` / `COIN_FUTURE` -> `SPOT` (master or sub-account).
    ///   - Master account `SPOT` -> sub-account `MARGIN(Cross)` / `ISOLATED_MARGIN`.
    ///   - Sub-account `MARGIN(Cross)` / `ISOLATED_MARGIN` -> master account `SPOT`.
    ///   - Sub-account `MARGIN(Cross)` -> sub-account `MARGIN(Cross)`.
    ///   - `ALPHA` -> `ALPHA` (master or sub-account).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#universal-transfer
    [[nodiscard]] common::RestApiResponse<UniversalTransferResponse>
    universal_transfer(const UniversalTransferParams& params) const {
        return asset_management_api_.universal_transfer(params);
    }
    /// Asynchronous `universal_transfer()`.
    template <class CompletionToken>
    auto async_universal_transfer(const UniversalTransferParams& params,
                                  CompletionToken&& token) const {
        return asset_management_api_.async_universal_transfer(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Sub-account Transfer History (For Sub-account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/transfer/subUserHistory.
    ///
    /// Sub-account Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `type` is not sent, records of type `2` (transfer out) are returned by default.
    /// - If `startTime` and `endTime` are not sent, data from the most recent 30 days is returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#sub-account-transfer-history
    [[nodiscard]] common::RestApiResponse<std::vector<SubAccountTransferHistoryResponseInner>>
    sub_account_transfer_history(const SubAccountTransferHistoryParams& params = {}) const {
        return asset_management_api_.sub_account_transfer_history(params);
    }
    /// Asynchronous `sub_account_transfer_history()`.
    template <class CompletionToken>
    auto async_sub_account_transfer_history(const SubAccountTransferHistoryParams& params,
                                            CompletionToken&& token) const {
        return asset_management_api_.async_sub_account_transfer_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Transfer to Master (For Sub-account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/transfer/subToMaster.
    ///
    /// Transfer to Master
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#transfer-to-master
    [[nodiscard]] common::RestApiResponse<TransferToMasterResponse>
    transfer_to_master(const TransferToMasterParams& params) const {
        return asset_management_api_.transfer_to_master(params);
    }
    /// Asynchronous `transfer_to_master()`.
    template <class CompletionToken>
    auto async_transfer_to_master(const TransferToMasterParams& params,
                                  CompletionToken&& token) const {
        return asset_management_api_.async_transfer_to_master(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Transfer to Sub-account of Same Master (For Sub-account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/transfer/subToSub.
    ///
    /// Transfer to Sub-account of Same Master
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#transfer-to-sub-account-of-same-master
    [[nodiscard]] common::RestApiResponse<TransferToSubAccountOfSameMasterResponse>
    transfer_to_sub_account_of_same_master(
        const TransferToSubAccountOfSameMasterParams& params) const {
        return asset_management_api_.transfer_to_sub_account_of_same_master(params);
    }
    /// Asynchronous `transfer_to_sub_account_of_same_master()`.
    template <class CompletionToken>
    auto async_transfer_to_sub_account_of_same_master(
        const TransferToSubAccountOfSameMasterParams& params, CompletionToken&& token) const {
        return asset_management_api_.async_transfer_to_sub_account_of_same_master(
            params, std::forward<CompletionToken>(token));
    }

    // ManagedSubAccountApi

    /// Deposit Assets Into The Managed Sub-account (For Investor Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/managed-subaccount/deposit.
    ///
    /// Deposit Assets Into The Managed Sub-account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable `Enable Spot & Margin Trading` option for the api key which requests
    /// this endpoint
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#deposit-assets-into-the-managed-sub-account
    [[nodiscard]] common::RestApiResponse<DepositAssetsIntoTheManagedSubAccountResponse>
    deposit_assets_into_the_managed_sub_account(
        const DepositAssetsIntoTheManagedSubAccountParams& params) const {
        return managed_sub_account_api_.deposit_assets_into_the_managed_sub_account(params);
    }
    /// Asynchronous `deposit_assets_into_the_managed_sub_account()`.
    template <class CompletionToken>
    auto async_deposit_assets_into_the_managed_sub_account(
        const DepositAssetsIntoTheManagedSubAccountParams& params, CompletionToken&& token) const {
        return managed_sub_account_api_.async_deposit_assets_into_the_managed_sub_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Managed Sub-account Deposit Address (For Investor Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/managed-subaccount/deposit/address.
    ///
    /// Get investor's managed sub-account deposit address.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `network` is not sent, the default `network` for the `coin` is returned.
    /// - When using `LIGHTNING`, `amount` must be provided.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#get-managed-sub-account-deposit-address
    [[nodiscard]] common::RestApiResponse<GetManagedSubAccountDepositAddressResponse>
    get_managed_sub_account_deposit_address(
        const GetManagedSubAccountDepositAddressParams& params) const {
        return managed_sub_account_api_.get_managed_sub_account_deposit_address(params);
    }
    /// Asynchronous `get_managed_sub_account_deposit_address()`.
    template <class CompletionToken>
    auto async_get_managed_sub_account_deposit_address(
        const GetManagedSubAccountDepositAddressParams& params, CompletionToken&& token) const {
        return managed_sub_account_api_.async_get_managed_sub_account_deposit_address(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Managed Sub-account Asset Details (For Investor Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/managed-subaccount/asset.
    ///
    /// Query Managed Sub-account Asset Details
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#query-managed-sub-account-asset-details
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryManagedSubAccountAssetDetailsResponseInner>>
    query_managed_sub_account_asset_details(
        const QueryManagedSubAccountAssetDetailsParams& params) const {
        return managed_sub_account_api_.query_managed_sub_account_asset_details(params);
    }
    /// Asynchronous `query_managed_sub_account_asset_details()`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_asset_details(
        const QueryManagedSubAccountAssetDetailsParams& params, CompletionToken&& token) const {
        return managed_sub_account_api_.async_query_managed_sub_account_asset_details(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Managed Sub-account Futures Asset Details (For Investor Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/managed-subaccount/fetch-future-asset.
    ///
    /// Investor can use this api to query managed sub account futures asset details
    ///
    /// Weight(UID): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#query-managed-sub-account-futures-asset-details
    [[nodiscard]] common::RestApiResponse<QueryManagedSubAccountFuturesAssetDetailsResponse>
    query_managed_sub_account_futures_asset_details(
        const QueryManagedSubAccountFuturesAssetDetailsParams& params) const {
        return managed_sub_account_api_.query_managed_sub_account_futures_asset_details(params);
    }
    /// Asynchronous `query_managed_sub_account_futures_asset_details()`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_futures_asset_details(
        const QueryManagedSubAccountFuturesAssetDetailsParams& params,
        CompletionToken&& token) const {
        return managed_sub_account_api_.async_query_managed_sub_account_futures_asset_details(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Managed Sub-account List (For Investor) (USER_DATA)
    ///
    /// GET /sapi/v1/managed-subaccount/info.
    ///
    /// Get investor's managed sub-account list.
    ///
    /// Weight(UID): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#query-managed-sub-account-list
    [[nodiscard]] common::RestApiResponse<QueryManagedSubAccountListResponse>
    query_managed_sub_account_list(const QueryManagedSubAccountListParams& params = {}) const {
        return managed_sub_account_api_.query_managed_sub_account_list(params);
    }
    /// Asynchronous `query_managed_sub_account_list()`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_list(const QueryManagedSubAccountListParams& params,
                                              CompletionToken&& token) const {
        return managed_sub_account_api_.async_query_managed_sub_account_list(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Managed Sub-account Margin Asset Details (For Investor Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/managed-subaccount/marginAsset.
    ///
    /// Investor can use this api to query managed sub account margin asset details
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#query-managed-sub-account-margin-asset-details
    [[nodiscard]] common::RestApiResponse<QueryManagedSubAccountMarginAssetDetailsResponse>
    query_managed_sub_account_margin_asset_details(
        const QueryManagedSubAccountMarginAssetDetailsParams& params) const {
        return managed_sub_account_api_.query_managed_sub_account_margin_asset_details(params);
    }
    /// Asynchronous `query_managed_sub_account_margin_asset_details()`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_margin_asset_details(
        const QueryManagedSubAccountMarginAssetDetailsParams& params,
        CompletionToken&& token) const {
        return managed_sub_account_api_.async_query_managed_sub_account_margin_asset_details(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Managed Sub-account Snapshot (For Investor Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/managed-subaccount/accountSnapshot.
    ///
    /// Query Managed Sub-account Snapshot
    ///
    /// Weight(IP): 2400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The query time range must be less than 30 days.
    /// - Only data from the most recent month is supported.
    /// - If `startTime` and `endTime` are omitted, records from the last 7 days are returned by
    /// default.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#query-managed-sub-account-snapshot
    [[nodiscard]] common::RestApiResponse<QueryManagedSubAccountSnapshotResponse>
    query_managed_sub_account_snapshot(const QueryManagedSubAccountSnapshotParams& params) const {
        return managed_sub_account_api_.query_managed_sub_account_snapshot(params);
    }
    /// Asynchronous `query_managed_sub_account_snapshot()`.
    template <class CompletionToken>
    auto
    async_query_managed_sub_account_snapshot(const QueryManagedSubAccountSnapshotParams& params,
                                             CompletionToken&& token) const {
        return managed_sub_account_api_.async_query_managed_sub_account_snapshot(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Managed Sub Account Transfer Log For Investor Master Account (USER_DATA)
    ///
    /// GET /sapi/v1/managed-subaccount/queryTransLogForInvestor.
    ///
    /// Query Managed Sub Account Transfer Log For Investor Master Account
    ///
    /// Investor can use this api to query managed sub account transfer log. This endpoint is
    /// available for investor of Managed Sub-Account. A Managed Sub-Account is an account type for
    /// investors who value flexibility in asset allocation and account application, while
    /// delegating trades to a professional trading team.
    ///
    /// Please refer to
    /// link
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#query-managed-sub-account-transfer-log-master-account-investor
    [[nodiscard]] common::RestApiResponse<
        QueryManagedSubAccountTransferLogMasterAccountInvestorResponse>
    query_managed_sub_account_transfer_log_master_account_investor(
        const QueryManagedSubAccountTransferLogMasterAccountInvestorParams& params) const {
        return managed_sub_account_api_
            .query_managed_sub_account_transfer_log_master_account_investor(params);
    }
    /// Asynchronous `query_managed_sub_account_transfer_log_master_account_investor()`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_transfer_log_master_account_investor(
        const QueryManagedSubAccountTransferLogMasterAccountInvestorParams& params,
        CompletionToken&& token) const {
        return managed_sub_account_api_
            .async_query_managed_sub_account_transfer_log_master_account_investor(
                params, std::forward<CompletionToken>(token));
    }

    /// Query Managed Sub Account Transfer Log For Trading Team Master Account (USER_DATA)
    ///
    /// GET /sapi/v1/managed-subaccount/queryTransLogForTradeParent.
    ///
    /// Query Managed Sub Account Transfer Log For Trading Team Master Account
    ///
    /// Trading team can use this api to query managed sub account transfer log. This endpoint is
    /// available for trading team of Managed Sub-Account. A Managed Sub-Account is an account type
    /// for investors who value flexibility in asset allocation and account application, while
    /// delegating trades to a professional trading team.
    ///
    /// Please refer to
    /// link
    ///
    /// Weight(UID): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#query-managed-sub-account-transfer-log-master-account-trading
    [[nodiscard]] common::RestApiResponse<
        QueryManagedSubAccountTransferLogMasterAccountTradingResponse>
    query_managed_sub_account_transfer_log_master_account_trading(
        const QueryManagedSubAccountTransferLogMasterAccountTradingParams& params) const {
        return managed_sub_account_api_
            .query_managed_sub_account_transfer_log_master_account_trading(params);
    }
    /// Asynchronous `query_managed_sub_account_transfer_log_master_account_trading()`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_transfer_log_master_account_trading(
        const QueryManagedSubAccountTransferLogMasterAccountTradingParams& params,
        CompletionToken&& token) const {
        return managed_sub_account_api_
            .async_query_managed_sub_account_transfer_log_master_account_trading(
                params, std::forward<CompletionToken>(token));
    }

    /// Query Managed Sub Account Transfer Log (For Trading Team Sub Account) (USER_DATA)
    ///
    /// GET /sapi/v1/managed-subaccount/query-trans-log.
    ///
    /// Query Managed Sub Account Transfer Log (For Trading Team Sub Account)
    ///
    /// Weight(UID): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#query-managed-sub-account-transfer-log-sub-account-trading
    [[nodiscard]] common::RestApiResponse<
        QueryManagedSubAccountTransferLogSubAccountTradingResponse>
    query_managed_sub_account_transfer_log_sub_account_trading(
        const QueryManagedSubAccountTransferLogSubAccountTradingParams& params) const {
        return managed_sub_account_api_.query_managed_sub_account_transfer_log_sub_account_trading(
            params);
    }
    /// Asynchronous `query_managed_sub_account_transfer_log_sub_account_trading()`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_transfer_log_sub_account_trading(
        const QueryManagedSubAccountTransferLogSubAccountTradingParams& params,
        CompletionToken&& token) const {
        return managed_sub_account_api_
            .async_query_managed_sub_account_transfer_log_sub_account_trading(
                params, std::forward<CompletionToken>(token));
    }

    /// Withdrawl Assets From The Managed Sub-account (For Investor Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/managed-subaccount/withdraw.
    ///
    /// Withdrawl Assets From The Managed Sub-account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Your API key must have the permission `Enable Spot & Margin Trading`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/managed-sub-account#withdrawl-assets-from-the-managed-sub-account
    [[nodiscard]] common::RestApiResponse<WithdrawlAssetsFromTheManagedSubAccountResponse>
    withdrawl_assets_from_the_managed_sub_account(
        const WithdrawlAssetsFromTheManagedSubAccountParams& params) const {
        return managed_sub_account_api_.withdrawl_assets_from_the_managed_sub_account(params);
    }
    /// Asynchronous `withdrawl_assets_from_the_managed_sub_account()`.
    template <class CompletionToken>
    auto async_withdrawl_assets_from_the_managed_sub_account(
        const WithdrawlAssetsFromTheManagedSubAccountParams& params,
        CompletionToken&& token) const {
        return managed_sub_account_api_.async_withdrawl_assets_from_the_managed_sub_account(
            params, std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::RestRequest make_request(std::string endpoint,
                                                          common::HttpMethod method,
                                                          common::Params query, common::Params body,
                                                          bool is_signed) {
        common::RestRequest req;
        req.method = method;
        req.endpoint = std::move(endpoint);
        req.query = std::move(query);
        req.body = std::move(body);
        req.is_signed = is_signed;
        return req;
    }

    std::shared_ptr<common::RestClient> client_;
    AccountManagementApi account_management_api_;
    ApiManagementApi api_management_api_;
    AssetManagementApi asset_management_api_;
    ManagedSubAccountApi managed_sub_account_api_;
};

} // namespace binance::sub_account::rest_api
