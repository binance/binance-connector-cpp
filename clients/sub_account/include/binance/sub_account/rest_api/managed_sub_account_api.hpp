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
#include <string_view>
#include <utility>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/deposit_assets_into_the_managed_sub_account_response.hpp>
#include <binance/sub_account/rest_api/models/get_managed_sub_account_deposit_address_response.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_asset_details_response_inner.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_futures_asset_details_response.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_list_response.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_margin_asset_details_response.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_transfer_log_master_account_investor_response.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_transfer_log_master_account_trading_response.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_transfer_log_sub_account_trading_response.hpp>
#include <binance/sub_account/rest_api/models/withdrawl_assets_from_the_managed_sub_account_response.hpp>

namespace binance::sub_account::rest_api {

enum class QueryManagedSubAccountSnapshotTypeEnum {
    Spot,
    Margin,
    Futures,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SUB_ACCOUNT_EXPORT std::string_view
to_string(QueryManagedSubAccountSnapshotTypeEnum value) noexcept;
BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountSnapshotTypeEnum
tag_invoke(boost::json::value_to_tag<QueryManagedSubAccountSnapshotTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           QueryManagedSubAccountSnapshotTypeEnum value);

enum class QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum {
    Spot,
    Margin,
    IsolatedMargin,
    UsdtFuture,
    CoinFuture,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SUB_ACCOUNT_EXPORT std::string_view
to_string(QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum
              value) noexcept;
BINANCE_SUB_ACCOUNT_EXPORT
QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum tag_invoke(
    boost::json::value_to_tag<
        QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum> /*tag*/
    ,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum value);

enum class QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum {
    Spot,
    Margin,
    IsolatedMargin,
    UsdtFuture,
    CoinFuture,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SUB_ACCOUNT_EXPORT std::string_view
to_string(QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum
              value) noexcept;
BINANCE_SUB_ACCOUNT_EXPORT
QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum tag_invoke(
    boost::json::value_to_tag<
        QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum> /*tag*/
    ,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum value);

enum class QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum {
    Spot,
    Margin,
    IsolatedMargin,
    UsdtFuture,
    CoinFuture,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SUB_ACCOUNT_EXPORT std::string_view
to_string(QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum
              value) noexcept;
BINANCE_SUB_ACCOUNT_EXPORT
QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum tag_invoke(
    boost::json::value_to_tag<
        QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum> /*tag*/
    ,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum value);

struct DepositAssetsIntoTheManagedSubAccountParams {
    common::Required<std::string> to_email;
    common::Required<std::string> asset;
    common::Required<common::Decimal> amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetManagedSubAccountDepositAddressParams {
    common::Required<std::string> email;
    common::Required<std::string> coin;
    /// networks can be found in `GET /sapi/v1/capital/deposit/address`
    std::optional<std::string> network = std::nullopt;
    std::optional<common::Decimal> amount = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryManagedSubAccountAssetDetailsParams {
    common::Required<std::string> email;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryManagedSubAccountFuturesAssetDetailsParams {
    common::Required<std::string> email;
    /// No input or input "USDT_FUTURE" to get UM Futures account details. Input "COIN_FUTURE" to
    /// get CM Futures account details.
    std::optional<std::string> account_type = std::nullopt;
};

struct QueryManagedSubAccountListParams {
    std::optional<std::string> email = std::nullopt;
    std::optional<std::int64_t> page = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryManagedSubAccountMarginAssetDetailsParams {
    common::Required<std::string> email;
    /// No input or input "MARGIN" to get Cross Margin account details. Input "ISOLATED_MARGIN" to
    /// get Isolated Margin account details.
    std::optional<std::string> account_type = std::nullopt;
};

struct QueryManagedSubAccountSnapshotParams {
    common::Required<std::string> email;
    common::Required<QueryManagedSubAccountSnapshotTypeEnum> type;
    /// Query time range must be within 30 days and only supports data within the last month.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// If both startTime and endTime are omitted, records from the last 7 days are returned by
    /// default.
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryManagedSubAccountTransferLogMasterAccountInvestorParams {
    common::Required<std::string> email;
    /// Start Time
    common::Required<std::int64_t> start_time;
    /// End Time (The start time and end time interval cannot exceed half a year)
    common::Required<std::int64_t> end_time;
    /// Page
    common::Required<std::int64_t> page;
    common::Required<std::int64_t> limit;
    /// Transfer Direction (FROM/TO)
    std::optional<std::string> transfers = std::nullopt;
    std::optional<
        QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum>
        transfer_function_account_type = std::nullopt;
};

struct QueryManagedSubAccountTransferLogMasterAccountTradingParams {
    common::Required<std::string> email;
    /// Start Time
    common::Required<std::int64_t> start_time;
    /// End Time (The start time and end time interval cannot exceed half a year)
    common::Required<std::int64_t> end_time;
    common::Required<std::int64_t> page;
    common::Required<std::int64_t> limit;
    /// Transfer Direction (FROM/TO)
    std::optional<std::string> transfers = std::nullopt;
    std::optional<
        QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum>
        transfer_function_account_type = std::nullopt;
};

struct QueryManagedSubAccountTransferLogSubAccountTradingParams {
    /// Start Time
    common::Required<std::int64_t> start_time;
    /// End Time (The start time and end time interval cannot exceed half a year)
    common::Required<std::int64_t> end_time;
    common::Required<std::int64_t> page;
    common::Required<std::int64_t> limit;
    /// Transfer Direction (from/to)
    std::optional<std::string> transfers = std::nullopt;
    std::optional<QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum>
        transfer_function_account_type = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct WithdrawlAssetsFromTheManagedSubAccountParams {
    common::Required<std::string> from_email;
    common::Required<std::string> asset;
    common::Required<common::Decimal> amount;
    /// Withdrawal will happen automatically on the selected date (UTC 0). If no date is selected,
    /// withdrawal takes effect immediately.
    std::optional<std::int64_t> transfer_date = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_SUB_ACCOUNT_EXPORT ManagedSubAccountApi {
public:
    explicit ManagedSubAccountApi(std::shared_ptr<common::RestClient> client);

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
        const DepositAssetsIntoTheManagedSubAccountParams& params) const;

    /// Asynchronous `deposit_assets_into_the_managed_sub_account()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<DepositAssetsIntoTheManagedSubAccountResponse>)`.
    template <class CompletionToken>
    auto async_deposit_assets_into_the_managed_sub_account(
        const DepositAssetsIntoTheManagedSubAccountParams& params, CompletionToken&& token) const {
        return common::async_send<DepositAssetsIntoTheManagedSubAccountResponse>(
            client_, deposit_assets_into_the_managed_sub_account_request(params),
            std::forward<CompletionToken>(token));
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
        const GetManagedSubAccountDepositAddressParams& params) const;

    /// Asynchronous `get_managed_sub_account_deposit_address()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetManagedSubAccountDepositAddressResponse>)`.
    template <class CompletionToken>
    auto async_get_managed_sub_account_deposit_address(
        const GetManagedSubAccountDepositAddressParams& params, CompletionToken&& token) const {
        return common::async_send<GetManagedSubAccountDepositAddressResponse>(
            client_, get_managed_sub_account_deposit_address_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryManagedSubAccountAssetDetailsParams& params) const;

    /// Asynchronous `query_managed_sub_account_asset_details()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryManagedSubAccountAssetDetailsResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_asset_details(
        const QueryManagedSubAccountAssetDetailsParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<QueryManagedSubAccountAssetDetailsResponseInner>>(
            client_, query_managed_sub_account_asset_details_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryManagedSubAccountFuturesAssetDetailsParams& params) const;

    /// Asynchronous `query_managed_sub_account_futures_asset_details()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryManagedSubAccountFuturesAssetDetailsResponse>)`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_futures_asset_details(
        const QueryManagedSubAccountFuturesAssetDetailsParams& params,
        CompletionToken&& token) const {
        return common::async_send<QueryManagedSubAccountFuturesAssetDetailsResponse>(
            client_, query_managed_sub_account_futures_asset_details_request(params),
            std::forward<CompletionToken>(token));
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
    query_managed_sub_account_list(const QueryManagedSubAccountListParams& params = {}) const;

    /// Asynchronous `query_managed_sub_account_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryManagedSubAccountListResponse>)`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_list(const QueryManagedSubAccountListParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<QueryManagedSubAccountListResponse>(
            client_, query_managed_sub_account_list_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryManagedSubAccountMarginAssetDetailsParams& params) const;

    /// Asynchronous `query_managed_sub_account_margin_asset_details()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryManagedSubAccountMarginAssetDetailsResponse>)`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_margin_asset_details(
        const QueryManagedSubAccountMarginAssetDetailsParams& params,
        CompletionToken&& token) const {
        return common::async_send<QueryManagedSubAccountMarginAssetDetailsResponse>(
            client_, query_managed_sub_account_margin_asset_details_request(params),
            std::forward<CompletionToken>(token));
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
    query_managed_sub_account_snapshot(const QueryManagedSubAccountSnapshotParams& params) const;

    /// Asynchronous `query_managed_sub_account_snapshot()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryManagedSubAccountSnapshotResponse>)`.
    template <class CompletionToken>
    auto
    async_query_managed_sub_account_snapshot(const QueryManagedSubAccountSnapshotParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<QueryManagedSubAccountSnapshotResponse>(
            client_, query_managed_sub_account_snapshot_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryManagedSubAccountTransferLogMasterAccountInvestorParams& params) const;

    /// Asynchronous `query_managed_sub_account_transfer_log_master_account_investor()`. Completes
    /// with `void(std::exception_ptr,
    /// common::RestApiResponse<QueryManagedSubAccountTransferLogMasterAccountInvestorResponse>)`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_transfer_log_master_account_investor(
        const QueryManagedSubAccountTransferLogMasterAccountInvestorParams& params,
        CompletionToken&& token) const {
        return common::async_send<QueryManagedSubAccountTransferLogMasterAccountInvestorResponse>(
            client_, query_managed_sub_account_transfer_log_master_account_investor_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryManagedSubAccountTransferLogMasterAccountTradingParams& params) const;

    /// Asynchronous `query_managed_sub_account_transfer_log_master_account_trading()`. Completes
    /// with `void(std::exception_ptr,
    /// common::RestApiResponse<QueryManagedSubAccountTransferLogMasterAccountTradingResponse>)`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_transfer_log_master_account_trading(
        const QueryManagedSubAccountTransferLogMasterAccountTradingParams& params,
        CompletionToken&& token) const {
        return common::async_send<QueryManagedSubAccountTransferLogMasterAccountTradingResponse>(
            client_, query_managed_sub_account_transfer_log_master_account_trading_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryManagedSubAccountTransferLogSubAccountTradingParams& params) const;

    /// Asynchronous `query_managed_sub_account_transfer_log_sub_account_trading()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryManagedSubAccountTransferLogSubAccountTradingResponse>)`.
    template <class CompletionToken>
    auto async_query_managed_sub_account_transfer_log_sub_account_trading(
        const QueryManagedSubAccountTransferLogSubAccountTradingParams& params,
        CompletionToken&& token) const {
        return common::async_send<QueryManagedSubAccountTransferLogSubAccountTradingResponse>(
            client_, query_managed_sub_account_transfer_log_sub_account_trading_request(params),
            std::forward<CompletionToken>(token));
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
        const WithdrawlAssetsFromTheManagedSubAccountParams& params) const;

    /// Asynchronous `withdrawl_assets_from_the_managed_sub_account()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<WithdrawlAssetsFromTheManagedSubAccountResponse>)`.
    template <class CompletionToken>
    auto async_withdrawl_assets_from_the_managed_sub_account(
        const WithdrawlAssetsFromTheManagedSubAccountParams& params,
        CompletionToken&& token) const {
        return common::async_send<WithdrawlAssetsFromTheManagedSubAccountResponse>(
            client_, withdrawl_assets_from_the_managed_sub_account_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest deposit_assets_into_the_managed_sub_account_request(
        const DepositAssetsIntoTheManagedSubAccountParams& params) const;
    [[nodiscard]] common::RestRequest get_managed_sub_account_deposit_address_request(
        const GetManagedSubAccountDepositAddressParams& params) const;
    [[nodiscard]] common::RestRequest query_managed_sub_account_asset_details_request(
        const QueryManagedSubAccountAssetDetailsParams& params) const;
    [[nodiscard]] common::RestRequest query_managed_sub_account_futures_asset_details_request(
        const QueryManagedSubAccountFuturesAssetDetailsParams& params) const;
    [[nodiscard]] common::RestRequest
    query_managed_sub_account_list_request(const QueryManagedSubAccountListParams& params) const;
    [[nodiscard]] common::RestRequest query_managed_sub_account_margin_asset_details_request(
        const QueryManagedSubAccountMarginAssetDetailsParams& params) const;
    [[nodiscard]] common::RestRequest query_managed_sub_account_snapshot_request(
        const QueryManagedSubAccountSnapshotParams& params) const;
    [[nodiscard]] common::RestRequest
    query_managed_sub_account_transfer_log_master_account_investor_request(
        const QueryManagedSubAccountTransferLogMasterAccountInvestorParams& params) const;
    [[nodiscard]] common::RestRequest
    query_managed_sub_account_transfer_log_master_account_trading_request(
        const QueryManagedSubAccountTransferLogMasterAccountTradingParams& params) const;
    [[nodiscard]] common::RestRequest
    query_managed_sub_account_transfer_log_sub_account_trading_request(
        const QueryManagedSubAccountTransferLogSubAccountTradingParams& params) const;
    [[nodiscard]] common::RestRequest withdrawl_assets_from_the_managed_sub_account_request(
        const WithdrawlAssetsFromTheManagedSubAccountParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::sub_account::rest_api
