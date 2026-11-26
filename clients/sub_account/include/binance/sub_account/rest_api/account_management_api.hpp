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

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/create_a_virtual_sub_account_response.hpp>
#include <binance/sub_account/rest_api/models/enable_futures_for_sub_account_response.hpp>
#include <binance/sub_account/rest_api/models/enable_options_for_sub_account_response.hpp>
#include <binance/sub_account/rest_api/models/get_futures_position_risk_of_sub_account_response_inner.hpp>
#include <binance/sub_account/rest_api/models/get_futures_position_risk_of_sub_account_v2_response.hpp>
#include <binance/sub_account/rest_api/models/get_sub_accounts_status_on_margin_or_futures_response_inner.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_list_response.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_transaction_statistics_response.hpp>

namespace binance::sub_account::rest_api {

struct CreateAVirtualSubAccountParams {
    /// Please input a string. We will create a virtual email using that string for you to register
    common::Required<std::string> sub_account_string;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct EnableFuturesForSubAccountParams {
    common::Required<std::string> email;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct EnableOptionsForSubAccountParams {
    common::Required<std::string> email;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFuturesPositionRiskOfSubAccountParams {
    common::Required<std::string> email;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFuturesPositionRiskOfSubAccountV2Params {
    common::Required<std::string> email;
    /// 1: USDT-margined Futures，2: Coin-margined Futures
    common::Required<std::int64_t> futures_type;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSubAccountsStatusOnMarginOrFuturesParams {
    std::optional<std::string> email = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySubAccountListParams {
    std::optional<std::string> email = std::nullopt;
    std::optional<std::string> is_freeze = std::nullopt;
    std::optional<std::int64_t> page = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySubAccountTransactionStatisticsParams {
    /// Managed sub-account email
    std::optional<std::string> email = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_SUB_ACCOUNT_EXPORT AccountManagementApi {
public:
    explicit AccountManagementApi(std::shared_ptr<common::RestClient> client);

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
    create_a_virtual_sub_account(const CreateAVirtualSubAccountParams& params) const;

    /// Asynchronous `create_a_virtual_sub_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateAVirtualSubAccountResponse>)`.
    template <class CompletionToken>
    auto async_create_a_virtual_sub_account(const CreateAVirtualSubAccountParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<CreateAVirtualSubAccountResponse>(
            client_, create_a_virtual_sub_account_request(params),
            std::forward<CompletionToken>(token));
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
    enable_futures_for_sub_account(const EnableFuturesForSubAccountParams& params) const;

    /// Asynchronous `enable_futures_for_sub_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<EnableFuturesForSubAccountResponse>)`.
    template <class CompletionToken>
    auto async_enable_futures_for_sub_account(const EnableFuturesForSubAccountParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<EnableFuturesForSubAccountResponse>(
            client_, enable_futures_for_sub_account_request(params),
            std::forward<CompletionToken>(token));
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
    enable_options_for_sub_account(const EnableOptionsForSubAccountParams& params) const;

    /// Asynchronous `enable_options_for_sub_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<EnableOptionsForSubAccountResponse>)`.
    template <class CompletionToken>
    auto async_enable_options_for_sub_account(const EnableOptionsForSubAccountParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<EnableOptionsForSubAccountResponse>(
            client_, enable_options_for_sub_account_request(params),
            std::forward<CompletionToken>(token));
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
        const GetFuturesPositionRiskOfSubAccountParams& params) const;

    /// Asynchronous `get_futures_position_risk_of_sub_account()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetFuturesPositionRiskOfSubAccountResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_futures_position_risk_of_sub_account(
        const GetFuturesPositionRiskOfSubAccountParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<GetFuturesPositionRiskOfSubAccountResponseInner>>(
            client_, get_futures_position_risk_of_sub_account_request(params),
            std::forward<CompletionToken>(token));
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
        const GetFuturesPositionRiskOfSubAccountV2Params& params) const;

    /// Asynchronous `get_futures_position_risk_of_sub_account_v2()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFuturesPositionRiskOfSubAccountV2Response>)`.
    template <class CompletionToken>
    auto async_get_futures_position_risk_of_sub_account_v2(
        const GetFuturesPositionRiskOfSubAccountV2Params& params, CompletionToken&& token) const {
        return common::async_send<GetFuturesPositionRiskOfSubAccountV2Response>(
            client_, get_futures_position_risk_of_sub_account_v2_request(params),
            std::forward<CompletionToken>(token));
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
        const GetSubAccountsStatusOnMarginOrFuturesParams& params = {}) const;

    /// Asynchronous `get_sub_accounts_status_on_margin_or_futures()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetSubAccountsStatusOnMarginOrFuturesResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_sub_accounts_status_on_margin_or_futures(
        const GetSubAccountsStatusOnMarginOrFuturesParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<GetSubAccountsStatusOnMarginOrFuturesResponseInner>>(
            client_, get_sub_accounts_status_on_margin_or_futures_request(params),
            std::forward<CompletionToken>(token));
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
    query_sub_account_list(const QuerySubAccountListParams& params = {}) const;

    /// Asynchronous `query_sub_account_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QuerySubAccountListResponse>)`.
    template <class CompletionToken>
    auto async_query_sub_account_list(const QuerySubAccountListParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<QuerySubAccountListResponse>(
            client_, query_sub_account_list_request(params), std::forward<CompletionToken>(token));
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
        const QuerySubAccountTransactionStatisticsParams& params = {}) const;

    /// Asynchronous `query_sub_account_transaction_statistics()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QuerySubAccountTransactionStatisticsResponse>)`.
    template <class CompletionToken>
    auto async_query_sub_account_transaction_statistics(
        const QuerySubAccountTransactionStatisticsParams& params, CompletionToken&& token) const {
        return common::async_send<QuerySubAccountTransactionStatisticsResponse>(
            client_, query_sub_account_transaction_statistics_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    create_a_virtual_sub_account_request(const CreateAVirtualSubAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    enable_futures_for_sub_account_request(const EnableFuturesForSubAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    enable_options_for_sub_account_request(const EnableOptionsForSubAccountParams& params) const;
    [[nodiscard]] common::RestRequest get_futures_position_risk_of_sub_account_request(
        const GetFuturesPositionRiskOfSubAccountParams& params) const;
    [[nodiscard]] common::RestRequest get_futures_position_risk_of_sub_account_v2_request(
        const GetFuturesPositionRiskOfSubAccountV2Params& params) const;
    [[nodiscard]] common::RestRequest get_sub_accounts_status_on_margin_or_futures_request(
        const GetSubAccountsStatusOnMarginOrFuturesParams& params) const;
    [[nodiscard]] common::RestRequest
    query_sub_account_list_request(const QuerySubAccountListParams& params) const;
    [[nodiscard]] common::RestRequest query_sub_account_transaction_statistics_request(
        const QuerySubAccountTransactionStatisticsParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::sub_account::rest_api
