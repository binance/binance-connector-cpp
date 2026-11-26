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
#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/account_api.hpp>
#include <binance/wallet/rest_api/asset_api.hpp>
#include <binance/wallet/rest_api/capital_api.hpp>
#include <binance/wallet/rest_api/models.hpp>
#include <binance/wallet/rest_api/others_api.hpp>
#include <binance/wallet/rest_api/travel_rule_api.hpp>

namespace binance::wallet::rest_api {

/// Wallet REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_WALLET_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Wallet REST API).
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

    // AccountApi

    /// Account API Trading Status (USER_DATA)
    ///
    /// GET /sapi/v1/account/apiTradingStatus.
    ///
    /// Fetch account api trading status detail.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#account-api-trading-status
    [[nodiscard]] common::RestApiResponse<AccountApiTradingStatusResponse>
    account_api_trading_status(const AccountApiTradingStatusParams& params = {}) const {
        return account_api_.account_api_trading_status(params);
    }
    /// Asynchronous `account_api_trading_status()`.
    template <class CompletionToken>
    auto async_account_api_trading_status(const AccountApiTradingStatusParams& params,
                                          CompletionToken&& token) const {
        return account_api_.async_account_api_trading_status(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Account info (USER_DATA)
    ///
    /// GET /sapi/v1/account/info.
    ///
    /// Fetch account info detail.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#account-info
    [[nodiscard]] common::RestApiResponse<AccountInfoResponse>
    account_info(const AccountInfoParams& params = {}) const {
        return account_api_.account_info(params);
    }
    /// Asynchronous `account_info()`.
    template <class CompletionToken>
    auto async_account_info(const AccountInfoParams& params, CompletionToken&& token) const {
        return account_api_.async_account_info(params, std::forward<CompletionToken>(token));
    }

    /// Account Status (USER_DATA)
    ///
    /// GET /sapi/v1/account/status.
    ///
    /// Fetch account status detail.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#account-status
    [[nodiscard]] common::RestApiResponse<AccountStatusResponse>
    account_status(const AccountStatusParams& params = {}) const {
        return account_api_.account_status(params);
    }
    /// Asynchronous `account_status()`.
    template <class CompletionToken>
    auto async_account_status(const AccountStatusParams& params, CompletionToken&& token) const {
        return account_api_.async_account_status(params, std::forward<CompletionToken>(token));
    }

    /// Daily Account Snapshot (USER_DATA)
    ///
    /// GET /sapi/v1/accountSnapshot.
    ///
    /// Daily account snapshot
    ///
    /// Weight(IP): 2400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The query time period must be less then 30 days
    /// - Support query within the last one month only
    /// - If startTimeand endTime not sent, return records of the last 7 days by default
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#daily-account-snapshot
    [[nodiscard]] common::RestApiResponse<DailyAccountSnapshotResponse>
    daily_account_snapshot(const DailyAccountSnapshotParams& params) const {
        return account_api_.daily_account_snapshot(params);
    }
    /// Asynchronous `daily_account_snapshot()`.
    template <class CompletionToken>
    auto async_daily_account_snapshot(const DailyAccountSnapshotParams& params,
                                      CompletionToken&& token) const {
        return account_api_.async_daily_account_snapshot(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Disable Fast Withdraw Switch (USER_DATA)
    ///
    /// POST /sapi/v1/account/disableFastWithdrawSwitch.
    ///
    /// Disable Fast Withdraw Switch
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - This request will disable fastwithdraw switch under your account. You need to enable
    /// "trade" option for the api key which requests this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#disable-fast-withdraw-switch
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    disable_fast_withdraw_switch(const DisableFastWithdrawSwitchParams& params = {}) const {
        return account_api_.disable_fast_withdraw_switch(params);
    }
    /// Asynchronous `disable_fast_withdraw_switch()`.
    template <class CompletionToken>
    auto async_disable_fast_withdraw_switch(const DisableFastWithdrawSwitchParams& params,
                                            CompletionToken&& token) const {
        return account_api_.async_disable_fast_withdraw_switch(
            params, std::forward<CompletionToken>(token));
    }

    /// Enable Fast Withdraw Switch (USER_DATA)
    ///
    /// POST /sapi/v1/account/enableFastWithdrawSwitch.
    ///
    /// Enable Fast Withdraw Switch (USER_DATA)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - This request will enable fastwithdraw switch under your account. You need to enable
    /// "trade" option for the api key which requests this endpoint.
    /// - When Fast Withdraw Switch is on, transferring funds to a Binance account will be done
    /// instantly. There is no on-chain transaction, no transaction ID and no withdrawal fee.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#enable-fast-withdraw-switch
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    enable_fast_withdraw_switch(const EnableFastWithdrawSwitchParams& params = {}) const {
        return account_api_.enable_fast_withdraw_switch(params);
    }
    /// Asynchronous `enable_fast_withdraw_switch()`.
    template <class CompletionToken>
    auto async_enable_fast_withdraw_switch(const EnableFastWithdrawSwitchParams& params,
                                           CompletionToken&& token) const {
        return account_api_.async_enable_fast_withdraw_switch(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Get API Key Permission (USER_DATA)
    ///
    /// GET /sapi/v1/account/apiRestrictions.
    ///
    /// Get API Key Permission
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#get-api-key-permission
    [[nodiscard]] common::RestApiResponse<GetApiKeyPermissionResponse>
    get_api_key_permission(const GetApiKeyPermissionParams& params = {}) const {
        return account_api_.get_api_key_permission(params);
    }
    /// Asynchronous `get_api_key_permission()`.
    template <class CompletionToken>
    auto async_get_api_key_permission(const GetApiKeyPermissionParams& params,
                                      CompletionToken&& token) const {
        return account_api_.async_get_api_key_permission(params,
                                                         std::forward<CompletionToken>(token));
    }

    // AssetApi

    /// Asset Detail (USER_DATA)
    ///
    /// GET /sapi/v1/asset/assetDetail.
    ///
    /// Fetch details of assets supported on Binance.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please get network and other deposit or withdraw details from `GET
    /// /sapi/v1/capital/config/getall`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#asset-detail
    [[nodiscard]] common::RestApiResponse<AssetDetailResponse>
    asset_detail(const AssetDetailParams& params = {}) const {
        return asset_api_.asset_detail(params);
    }
    /// Asynchronous `asset_detail()`.
    template <class CompletionToken>
    auto async_asset_detail(const AssetDetailParams& params, CompletionToken&& token) const {
        return asset_api_.async_asset_detail(params, std::forward<CompletionToken>(token));
    }

    /// Asset Dividend Record (USER_DATA)
    ///
    /// GET /sapi/v1/asset/assetDividend.
    ///
    /// Query asset dividend record.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - There cannot be more than 180 days between parameter `startTime` and `endTime`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#asset-dividend-record
    [[nodiscard]] common::RestApiResponse<AssetDividendRecordResponse>
    asset_dividend_record(const AssetDividendRecordParams& params = {}) const {
        return asset_api_.asset_dividend_record(params);
    }
    /// Asynchronous `asset_dividend_record()`.
    template <class CompletionToken>
    auto async_asset_dividend_record(const AssetDividendRecordParams& params,
                                     CompletionToken&& token) const {
        return asset_api_.async_asset_dividend_record(params, std::forward<CompletionToken>(token));
    }

    /// Dust Convert (USER_DATA)
    ///
    /// POST /sapi/v1/asset/dust-convert/convert.
    ///
    /// Convert dust assets
    ///
    /// Weight(UID): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#dust-convert
    [[nodiscard]] common::RestApiResponse<DustConvertResponse>
    dust_convert(const DustConvertParams& params) const {
        return asset_api_.dust_convert(params);
    }
    /// Asynchronous `dust_convert()`.
    template <class CompletionToken>
    auto async_dust_convert(const DustConvertParams& params, CompletionToken&& token) const {
        return asset_api_.async_dust_convert(params, std::forward<CompletionToken>(token));
    }

    /// Dust Convertible Assets (USER_DATA)
    ///
    /// POST /sapi/v1/asset/dust-convert/query-convertible-assets.
    ///
    /// Query dust convertible assets
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#dust-convertible-assets
    [[nodiscard]] common::RestApiResponse<DustConvertibleAssetsResponse>
    dust_convertible_assets(const DustConvertibleAssetsParams& params) const {
        return asset_api_.dust_convertible_assets(params);
    }
    /// Asynchronous `dust_convertible_assets()`.
    template <class CompletionToken>
    auto async_dust_convertible_assets(const DustConvertibleAssetsParams& params,
                                       CompletionToken&& token) const {
        return asset_api_.async_dust_convertible_assets(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Dust Transfer (USER_DATA)
    ///
    /// POST /sapi/v1/asset/dust.
    ///
    /// Convert dust assets to BNB.
    ///
    /// Weight(UID): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to open`Enable Spot & Margin Trading` permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#dust-transfer
    [[nodiscard]] common::RestApiResponse<DustTransferResponse>
    dust_transfer(const DustTransferParams& params) const {
        return asset_api_.dust_transfer(params);
    }
    /// Asynchronous `dust_transfer()`.
    template <class CompletionToken>
    auto async_dust_transfer(const DustTransferParams& params, CompletionToken&& token) const {
        return asset_api_.async_dust_transfer(params, std::forward<CompletionToken>(token));
    }

    /// DustLog (USER_DATA)
    ///
    /// GET /sapi/v1/asset/dribblet.
    ///
    /// Dustlog
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Only return last 100 records
    /// - Only return records after 2020/12/01
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#dustlog
    [[nodiscard]] common::RestApiResponse<DustlogResponse>
    dustlog(const DustlogParams& params = {}) const {
        return asset_api_.dustlog(params);
    }
    /// Asynchronous `dustlog()`.
    template <class CompletionToken>
    auto async_dustlog(const DustlogParams& params, CompletionToken&& token) const {
        return asset_api_.async_dustlog(params, std::forward<CompletionToken>(token));
    }

    /// Funding Wallet (USER_DATA)
    ///
    /// POST /sapi/v1/asset/get-funding-asset.
    ///
    /// Query Funding Wallet
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Currently supports querying the following business assets：Binance Pay, Binance Card,
    /// Binance Gift Card, Stock Token
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#funding-wallet
    [[nodiscard]] common::RestApiResponse<std::vector<FundingWalletResponseInner>>
    funding_wallet(const FundingWalletParams& params = {}) const {
        return asset_api_.funding_wallet(params);
    }
    /// Asynchronous `funding_wallet()`.
    template <class CompletionToken>
    auto async_funding_wallet(const FundingWalletParams& params, CompletionToken&& token) const {
        return asset_api_.async_funding_wallet(params, std::forward<CompletionToken>(token));
    }

    /// Get Assets That Can Be Converted Into BNB (USER_DATA)
    ///
    /// POST /sapi/v1/asset/dust-btc.
    ///
    /// Get Assets That Can Be Converted Into BNB
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#get-assets-that-can-be-converted-into-bnb
    [[nodiscard]] common::RestApiResponse<GetAssetsThatCanBeConvertedIntoBnbResponse>
    get_assets_that_can_be_converted_into_bnb(
        const GetAssetsThatCanBeConvertedIntoBnbParams& params = {}) const {
        return asset_api_.get_assets_that_can_be_converted_into_bnb(params);
    }
    /// Asynchronous `get_assets_that_can_be_converted_into_bnb()`.
    template <class CompletionToken>
    auto async_get_assets_that_can_be_converted_into_bnb(
        const GetAssetsThatCanBeConvertedIntoBnbParams& params, CompletionToken&& token) const {
        return asset_api_.async_get_assets_that_can_be_converted_into_bnb(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Cloud-Mining payment and refund history (USER_DATA)
    ///
    /// GET /sapi/v1/asset/ledger-transfer/cloud-mining/queryByPage.
    ///
    /// The query of Cloud-Mining payment and refund history
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Just return the SUCCESS records of payment and refund.
    /// - For response, type = 248 means payment, type = 249 means refund, status =S means SUCCESS.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#get-cloud-mining-payment-and-refund-history
    [[nodiscard]] common::RestApiResponse<GetCloudMiningPaymentAndRefundHistoryResponse>
    get_cloud_mining_payment_and_refund_history(
        const GetCloudMiningPaymentAndRefundHistoryParams& params) const {
        return asset_api_.get_cloud_mining_payment_and_refund_history(params);
    }
    /// Asynchronous `get_cloud_mining_payment_and_refund_history()`.
    template <class CompletionToken>
    auto async_get_cloud_mining_payment_and_refund_history(
        const GetCloudMiningPaymentAndRefundHistoryParams& params, CompletionToken&& token) const {
        return asset_api_.async_get_cloud_mining_payment_and_refund_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Open Symbol List (MARKET_DATA)
    ///
    /// GET /sapi/v1/spot/open-symbol-list.
    ///
    /// Get the list of symbols that are scheduled to be opened for trading in
    /// the market.
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#get-open-symbol-list
    [[nodiscard]] common::RestApiResponse<std::vector<GetOpenSymbolListResponseInner>>
    get_open_symbol_list() const {
        return asset_api_.get_open_symbol_list();
    }
    /// Asynchronous `get_open_symbol_list()`.
    template <class CompletionToken>
    auto async_get_open_symbol_list(CompletionToken&& token) const {
        return asset_api_.async_get_open_symbol_list(std::forward<CompletionToken>(token));
    }

    /// Get Spot Asset Tags (MARKET_DATA)
    ///
    /// GET /sapi/v1/spot/asset/tags.
    ///
    /// Get the tags configured for spot-tradable assets.
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#get-spot-asset-tags
    [[nodiscard]] common::RestApiResponse<std::vector<GetSpotAssetTagsResponseInner>>
    get_spot_asset_tags(const GetSpotAssetTagsParams& params = {}) const {
        return asset_api_.get_spot_asset_tags(params);
    }
    /// Asynchronous `get_spot_asset_tags()`.
    template <class CompletionToken>
    auto async_get_spot_asset_tags(const GetSpotAssetTagsParams& params,
                                   CompletionToken&& token) const {
        return asset_api_.async_get_spot_asset_tags(params, std::forward<CompletionToken>(token));
    }

    /// Query User Delegation History(For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/asset/custody/transfer-history.
    ///
    /// Query User Delegation History
    ///
    /// Weight(IP): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#query-user-delegation-history
    [[nodiscard]] common::RestApiResponse<QueryUserDelegationHistoryResponse>
    query_user_delegation_history(const QueryUserDelegationHistoryParams& params) const {
        return asset_api_.query_user_delegation_history(params);
    }
    /// Asynchronous `query_user_delegation_history()`.
    template <class CompletionToken>
    auto async_query_user_delegation_history(const QueryUserDelegationHistoryParams& params,
                                             CompletionToken&& token) const {
        return asset_api_.async_query_user_delegation_history(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Query User Universal Transfer History (USER_DATA)
    ///
    /// GET /sapi/v1/asset/transfer.
    ///
    /// Query User Universal Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `fromSymbol` must be sent when type are ISOLATEDMARGIN_MARGIN and
    /// ISOLATEDMARGIN_ISOLATEDMARGIN
    /// - `toSymbol` must be sent when type are MARGIN_ISOLATEDMARGIN and
    /// ISOLATEDMARGIN_ISOLATEDMARGIN
    /// - Support query within the last 6 months only
    /// - If `startTime`and `endTime` not sent, return records of the last 7 days by default
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#query-user-universal-transfer-history
    [[nodiscard]] common::RestApiResponse<QueryUserUniversalTransferHistoryResponse>
    query_user_universal_transfer_history(
        const QueryUserUniversalTransferHistoryParams& params) const {
        return asset_api_.query_user_universal_transfer_history(params);
    }
    /// Asynchronous `query_user_universal_transfer_history()`.
    template <class CompletionToken>
    auto async_query_user_universal_transfer_history(
        const QueryUserUniversalTransferHistoryParams& params, CompletionToken&& token) const {
        return asset_api_.async_query_user_universal_transfer_history(
            params, std::forward<CompletionToken>(token));
    }

    /// User Universal Transfer (USER_DATA)
    ///
    /// POST /sapi/v1/asset/transfer.
    ///
    /// User universal transfer
    ///
    /// Weight(UID): 300
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable Permits Universal Transfer option for the API Key that requests this
    /// endpoint.
    /// - `fromSymbol` must be sent when type is `ISOLATEDMARGIN_MARGIN` or
    /// `ISOLATEDMARGIN_ISOLATEDMARGIN`.
    /// - `toSymbol` must be sent when type is `MARGIN_ISOLATEDMARGIN` or
    /// `ISOLATEDMARGIN_ISOLATEDMARGIN`.
    /// - ENUM of transfer types:
    /// - `MAIN_UMFUTURE`: Spot → USDⓈ-M Futures
    /// - `MAIN_CMFUTURE`: Spot → COIN-M Futures
    /// - `MAIN_MARGIN`: Spot → Margin (cross)
    /// - `UMFUTURE_MAIN`: USDⓈ-M Futures → Spot
    /// - `UMFUTURE_MARGIN`: USDⓈ-M Futures → Margin (cross)
    /// - `CMFUTURE_MAIN`: COIN-M Futures → Spot
    /// - `CMFUTURE_MARGIN`: COIN-M Futures → Margin (cross)
    /// - `MARGIN_MAIN`: Margin (cross) → Spot
    /// - `MARGIN_UMFUTURE`: Margin (cross) → USDⓈ-M Futures
    /// - `MARGIN_CMFUTURE`: Margin (cross) → COIN-M Futures
    /// - `ISOLATEDMARGIN_MARGIN`: Isolated margin → Margin (cross)
    /// - `MARGIN_ISOLATEDMARGIN`: Margin (cross) → Isolated margin
    /// - `ISOLATEDMARGIN_ISOLATEDMARGIN`: Isolated margin → Isolated margin
    /// - `MAIN_FUNDING`: Spot → Funding
    /// - `FUNDING_MAIN`: Funding → Spot
    /// - `FUNDING_UMFUTURE`: Funding → USDⓈ-M Futures
    /// - `UMFUTURE_FUNDING`: USDⓈ-M Futures → Funding
    /// - `MARGIN_FUNDING`: Margin (cross) → Funding
    /// - `FUNDING_MARGIN`: Funding → Margin (cross)
    /// - `FUNDING_CMFUTURE`: Funding → COIN-M Futures
    /// - `CMFUTURE_FUNDING`: COIN-M Futures → Funding
    /// - `MAIN_OPTION`: Spot → Options
    /// - `OPTION_MAIN`: Options → Spot
    /// - `UMFUTURE_OPTION`: USDⓈ-M Futures → Options
    /// - `OPTION_UMFUTURE`: Options → USDⓈ-M Futures
    /// - `MARGIN_OPTION`: Margin (cross) → Options
    /// - `OPTION_MARGIN`: Options → Margin (cross)
    /// - `FUNDING_OPTION`: Funding → Options
    /// - `OPTION_FUNDING`: Options → Funding
    /// - `MAIN_PORTFOLIO_MARGIN`: Spot → Portfolio Margin
    /// - `PORTFOLIO_MARGIN_MAIN`: Portfolio Margin → Spot
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#user-universal-transfer
    [[nodiscard]] common::RestApiResponse<UserUniversalTransferResponse>
    user_universal_transfer(const UserUniversalTransferParams& params) const {
        return asset_api_.user_universal_transfer(params);
    }
    /// Asynchronous `user_universal_transfer()`.
    template <class CompletionToken>
    auto async_user_universal_transfer(const UserUniversalTransferParams& params,
                                       CompletionToken&& token) const {
        return asset_api_.async_user_universal_transfer(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Query User Wallet Balance (USER_DATA)
    ///
    /// GET /sapi/v1/asset/wallet/balance.
    ///
    /// Query User Wallet Balance
    ///
    /// Weight(IP): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#query-user-wallet-balance
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUserWalletBalanceResponseInner>>
    query_user_wallet_balance(const QueryUserWalletBalanceParams& params = {}) const {
        return asset_api_.query_user_wallet_balance(params);
    }
    /// Asynchronous `query_user_wallet_balance()`.
    template <class CompletionToken>
    auto async_query_user_wallet_balance(const QueryUserWalletBalanceParams& params,
                                         CompletionToken&& token) const {
        return asset_api_.async_query_user_wallet_balance(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Toggle BNB Burn On Spot Trade And Margin Interest (USER_DATA)
    ///
    /// POST /sapi/v1/bnbBurn.
    ///
    /// Toggle BNB Burn On Spot Trade And Margin Interest
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - "spotBNBBurn" and "interestBNBBurn" should be sent at least one.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#toggle-bnb-burn-on-spot-trade-and-margin-interest
    [[nodiscard]] common::RestApiResponse<ToggleBnbBurnOnSpotTradeAndMarginInterestResponse>
    toggle_bnb_burn_on_spot_trade_and_margin_interest(
        const ToggleBnbBurnOnSpotTradeAndMarginInterestParams& params = {}) const {
        return asset_api_.toggle_bnb_burn_on_spot_trade_and_margin_interest(params);
    }
    /// Asynchronous `toggle_bnb_burn_on_spot_trade_and_margin_interest()`.
    template <class CompletionToken>
    auto async_toggle_bnb_burn_on_spot_trade_and_margin_interest(
        const ToggleBnbBurnOnSpotTradeAndMarginInterestParams& params,
        CompletionToken&& token) const {
        return asset_api_.async_toggle_bnb_burn_on_spot_trade_and_margin_interest(
            params, std::forward<CompletionToken>(token));
    }

    /// Trade Fee (USER_DATA)
    ///
    /// GET /sapi/v1/asset/tradeFee.
    ///
    /// Fetch trade fee
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#trade-fee
    [[nodiscard]] common::RestApiResponse<std::vector<TradeFeeResponseInner>>
    trade_fee(const TradeFeeParams& params = {}) const {
        return asset_api_.trade_fee(params);
    }
    /// Asynchronous `trade_fee()`.
    template <class CompletionToken>
    auto async_trade_fee(const TradeFeeParams& params, CompletionToken&& token) const {
        return asset_api_.async_trade_fee(params, std::forward<CompletionToken>(token));
    }

    /// User Asset (USER_DATA)
    ///
    /// POST /sapi/v3/asset/getUserAsset.
    ///
    /// Get user assets, just for positive data.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If asset is set, then return this asset, otherwise return all assets positive.
    /// - If needBtcValuation is set, then return btcValudation.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/asset#user-asset
    [[nodiscard]] common::RestApiResponse<std::vector<UserAssetResponseInner>>
    user_asset(const UserAssetParams& params = {}) const {
        return asset_api_.user_asset(params);
    }
    /// Asynchronous `user_asset()`.
    template <class CompletionToken>
    auto async_user_asset(const UserAssetParams& params, CompletionToken&& token) const {
        return asset_api_.async_user_asset(params, std::forward<CompletionToken>(token));
    }

    // CapitalApi

    /// All Coins' Information (USER_DATA)
    ///
    /// GET /sapi/v1/capital/config/getall.
    ///
    /// Get information of coins (available for deposit and withdraw) for user.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#all-coins-information
    [[nodiscard]] common::RestApiResponse<std::vector<AllCoinsInformationResponseInner>>
    all_coins_information(const AllCoinsInformationParams& params = {}) const {
        return capital_api_.all_coins_information(params);
    }
    /// Asynchronous `all_coins_information()`.
    template <class CompletionToken>
    auto async_all_coins_information(const AllCoinsInformationParams& params,
                                     CompletionToken&& token) const {
        return capital_api_.async_all_coins_information(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Deposit Address(supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/address.
    ///
    /// Fetch deposit address with network.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `network` is not send, return with default network of the coin.
    /// - You can get `network` and `isDefault` in `networkList` in the response of `Get
    /// /sapi/v1/capital/config/getall (HMAC SHA256)`.
    /// - `amount` needs to be sent if using LIGHTNING network
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#deposit-address
    [[nodiscard]] common::RestApiResponse<DepositAddressResponse>
    deposit_address(const DepositAddressParams& params) const {
        return capital_api_.deposit_address(params);
    }
    /// Asynchronous `deposit_address()`.
    template <class CompletionToken>
    auto async_deposit_address(const DepositAddressParams& params, CompletionToken&& token) const {
        return capital_api_.async_deposit_address(params, std::forward<CompletionToken>(token));
    }

    /// Deposit History (supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/hisrec.
    ///
    /// Fetch deposit history.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime` are sent, time between `startTime` and `endTime` must be
    /// less than 90 days.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#deposit-history
    [[nodiscard]] common::RestApiResponse<std::vector<DepositHistoryResponseInner>>
    deposit_history(const DepositHistoryParams& params = {}) const {
        return capital_api_.deposit_history(params);
    }
    /// Asynchronous `deposit_history()`.
    template <class CompletionToken>
    auto async_deposit_history(const DepositHistoryParams& params, CompletionToken&& token) const {
        return capital_api_.async_deposit_history(params, std::forward<CompletionToken>(token));
    }

    /// Fetch deposit address list with network (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/address/list.
    ///
    /// Fetch deposit address list with network.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#fetch-deposit-address-list-with-network
    [[nodiscard]] common::RestApiResponse<
        std::vector<FetchDepositAddressListWithNetworkResponseInner>>
    fetch_deposit_address_list_with_network(
        const FetchDepositAddressListWithNetworkParams& params) const {
        return capital_api_.fetch_deposit_address_list_with_network(params);
    }
    /// Asynchronous `fetch_deposit_address_list_with_network()`.
    template <class CompletionToken>
    auto async_fetch_deposit_address_list_with_network(
        const FetchDepositAddressListWithNetworkParams& params, CompletionToken&& token) const {
        return capital_api_.async_fetch_deposit_address_list_with_network(
            params, std::forward<CompletionToken>(token));
    }

    /// Fetch withdraw address list (USER_DATA)
    ///
    /// GET /sapi/v1/capital/withdraw/address/list.
    ///
    /// Fetch withdraw address list
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#fetch-withdraw-address-list
    [[nodiscard]] common::RestApiResponse<std::vector<FetchWithdrawAddressListResponseInner>>
    fetch_withdraw_address_list() const {
        return capital_api_.fetch_withdraw_address_list();
    }
    /// Asynchronous `fetch_withdraw_address_list()`.
    template <class CompletionToken>
    auto async_fetch_withdraw_address_list(CompletionToken&& token) const {
        return capital_api_.async_fetch_withdraw_address_list(std::forward<CompletionToken>(token));
    }

    /// Fetch withdraw quota (USER_DATA)
    ///
    /// GET /sapi/v1/capital/withdraw/quota.
    ///
    /// Fetch withdraw quota
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#fetch-withdraw-quota
    [[nodiscard]] common::RestApiResponse<FetchWithdrawQuotaResponse> fetch_withdraw_quota() const {
        return capital_api_.fetch_withdraw_quota();
    }
    /// Asynchronous `fetch_withdraw_quota()`.
    template <class CompletionToken>
    auto async_fetch_withdraw_quota(CompletionToken&& token) const {
        return capital_api_.async_fetch_withdraw_quota(std::forward<CompletionToken>(token));
    }

    /// One click arrival deposit apply (for expired address deposit) (USER_DATA)
    ///
    /// POST /sapi/v1/capital/deposit/credit-apply.
    ///
    /// Apply deposit credit for expired address (One click arrival)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#one-click-arrival-deposit-apply
    [[nodiscard]] common::RestApiResponse<OneClickArrivalDepositApplyResponse>
    one_click_arrival_deposit_apply(const OneClickArrivalDepositApplyParams& params = {}) const {
        return capital_api_.one_click_arrival_deposit_apply(params);
    }
    /// Asynchronous `one_click_arrival_deposit_apply()`.
    template <class CompletionToken>
    auto async_one_click_arrival_deposit_apply(const OneClickArrivalDepositApplyParams& params,
                                               CompletionToken&& token) const {
        return capital_api_.async_one_click_arrival_deposit_apply(
            params, std::forward<CompletionToken>(token));
    }

    /// Withdraw (USER_DATA)
    ///
    /// POST /sapi/v1/capital/withdraw/apply.
    ///
    /// Submit a withdraw request
    ///
    /// Weight(UID): 900
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `network` not send, return with default network of the coin.
    /// - You can get `network` and `isDefault` in `networkList` of a coin in the response of `Get
    /// /sapi/v1/capital/config/getall (HMAC SHA256)`.
    /// - To check if travel rule is required, by using `GET
    /// /sapi/v1/localentity/questionnaire-requirements` and if it returns anything other than `NIL`
    /// you will need update SAPI to `POST /sapi/v1/localentity/withdraw/apply` else you can
    /// continue `POST /sapi/v1/capital/withdraw/apply`. Please note that if you are required to
    /// comply to travel rule please refer to the Travel Rule SAPI.
    /// - "For networks that do not support memo/tag, submitting a withdrawal request with a
    /// non-empty `addressTag` will return error `-4106 TAG_NOT_SUPPORTED_FOR_NETWORK`. Please omit
    /// the `addressTag` field for such networks. You can check whether a network requires a tag via
    /// `GET /sapi/v1/capital/config/getall`: If `withdrawTag` = `true` → memo/tag is required. If
    /// `withdrawTag` = `false` → memo/tag is not supported; omit `addressTag`."
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#withdraw
    [[nodiscard]] common::RestApiResponse<WithdrawResponse>
    withdraw(const WithdrawParams& params) const {
        return capital_api_.withdraw(params);
    }
    /// Asynchronous `withdraw()`.
    template <class CompletionToken>
    auto async_withdraw(const WithdrawParams& params, CompletionToken&& token) const {
        return capital_api_.async_withdraw(params, std::forward<CompletionToken>(token));
    }

    /// Withdraw History (supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/withdraw/history.
    ///
    /// Fetch withdraw history
    ///
    /// Weight(UID): 18000 (10 requests per second)
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `network` may not be in the response for old withdraw.
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime`are sent, time between `startTime`and `endTime`must be
    /// less than 90 days.
    /// - If `withdrawOrderId` is sent, time between `startTime` and `endTime` must be less than 7
    /// days.
    /// - If `withdrawOrderId` is sent, `startTime` and `endTime` are not sent, will return last 7
    /// days records by default.
    /// - Maximum support `idList` number is 45.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#withdraw-history
    [[nodiscard]] common::RestApiResponse<std::vector<WithdrawHistoryResponseInner>>
    withdraw_history(const WithdrawHistoryParams& params = {}) const {
        return capital_api_.withdraw_history(params);
    }
    /// Asynchronous `withdraw_history()`.
    template <class CompletionToken>
    auto async_withdraw_history(const WithdrawHistoryParams& params,
                                CompletionToken&& token) const {
        return capital_api_.async_withdraw_history(params, std::forward<CompletionToken>(token));
    }

    // OthersApi

    /// Get Spot Delist Schedule (MARKET_DATA)
    ///
    /// GET /sapi/v1/spot/delist-schedule.
    ///
    /// Get symbols delist schedule for spot
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/others#get-symbols-delist-schedule-for-spot
    [[nodiscard]] common::RestApiResponse<std::vector<GetSymbolsDelistScheduleForSpotResponseInner>>
    get_symbols_delist_schedule_for_spot(
        const GetSymbolsDelistScheduleForSpotParams& params = {}) const {
        return others_api_.get_symbols_delist_schedule_for_spot(params);
    }
    /// Asynchronous `get_symbols_delist_schedule_for_spot()`.
    template <class CompletionToken>
    auto
    async_get_symbols_delist_schedule_for_spot(const GetSymbolsDelistScheduleForSpotParams& params,
                                               CompletionToken&& token) const {
        return others_api_.async_get_symbols_delist_schedule_for_spot(
            params, std::forward<CompletionToken>(token));
    }

    /// System Status
    ///
    /// GET /sapi/v1/system/status.
    ///
    /// Fetch system status.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: System
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/others#system-status
    [[nodiscard]] common::RestApiResponse<SystemStatusResponse> system_status() const {
        return others_api_.system_status();
    }
    /// Asynchronous `system_status()`.
    template <class CompletionToken> auto async_system_status(CompletionToken&& token) const {
        return others_api_.async_system_status(std::forward<CompletionToken>(token));
    }

    // TravelRuleApi

    /// Broker Withdraw (for brokers of local entities that require travel rule) (USER_DATA)
    ///
    /// POST /sapi/v1/localentity/broker/withdraw/apply.
    ///
    /// Submit a withdrawal request for brokers of local entities that required travel rule.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `network` not send, return with default network of the coin, but if the address could
    /// not match default network, the withdraw will be rejected.
    /// - You can get `network` in `networkList` of a coin in the response of `Get
    /// /sapi/v1/capital/config/getall (HMAC SHA256)`.
    /// - Questionnaire is different for each local entity, please refer to the `Withdraw
    /// Questionnaire Contents` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// **StandardPii**
    ///
    /// **For Natural Person**
    ///
    /// - `piiType` (INTEGER, Mandatory): Fix to 0: Natural Person
    /// - `latinNames` (List<PiiName>, Mandatory): In case a person have complicated names or
    /// multiple names, this parameter is a list
    /// - `localNames` (List<PiiName>, Optional): In case a person have complicated names or
    /// multiple names, this parameter is a list
    /// - `nationality` (STRING, Optional)
    /// - `residenceCountry` (STRING, Mandatory)
    /// - `nationalIdentifier` (STRING, Optional)
    /// - `nationalIdentifierType` (STRING, Optional)
    /// - `nationalIdentifierIssueCountry` (STRING, Optional)
    /// - `dateOfBirth` (STRING, Optional): yyyy-mm-dd. Not required but strongly recommended.
    /// Providing DOB could greatly reduce false positive rate during risk checking process.
    /// - `placeOfBirth` (STRING, Optional)
    /// - `address` (STRING, Optional)
    ///
    /// **For Legal Person**
    ///
    /// - `piiType` (INTEGER, Mandatory): Fix to 1: Legal Person
    /// - `latinName` (STRING, Mandatory): It's company name for Legal Person
    /// - `localName` (STRING, Optional)
    /// - `registrationCountry` (STRING, Mandatory)
    /// - `nationalIdentifier` (STRING, Optional)
    /// - `nationalIdentifierType` (STRING, Optional)
    /// - `nationalIdentifierIssueCountry` (STRING, Optional)
    /// - `registrationDate` (STRING, Optional): yyyy-mm-dd. Not required but strongly recommended.
    /// - `address` (STRING, Optional)
    /// - `walletAddress` (STRING, Optional)
    /// - `walletTag` (STRING, Optional)
    ///
    /// **PiiName**
    ///
    /// - `firstName` (STRING, Mandatory): Mandatory for Natural person
    /// - `middleName` (STRING, Optional)
    /// - `lastName` (STRING, Optional)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#broker-withdraw
    [[nodiscard]] common::RestApiResponse<BrokerWithdrawResponse>
    broker_withdraw(const BrokerWithdrawParams& params) const {
        return travel_rule_api_.broker_withdraw(params);
    }
    /// Asynchronous `broker_withdraw()`.
    template <class CompletionToken>
    auto async_broker_withdraw(const BrokerWithdrawParams& params, CompletionToken&& token) const {
        return travel_rule_api_.async_broker_withdraw(params, std::forward<CompletionToken>(token));
    }

    /// Check Questionnaire Requirements (for local entities that require travel rule) (supporting
    /// network) (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/questionnaire-requirements.
    ///
    /// This API will return user-specific Travel Rule questionnaire requirement information in
    /// reference to the current API key.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#check-questionnaire-requirements
    [[nodiscard]] common::RestApiResponse<CheckQuestionnaireRequirementsResponse>
    check_questionnaire_requirements(
        const CheckQuestionnaireRequirementsParams& params = {}) const {
        return travel_rule_api_.check_questionnaire_requirements(params);
    }
    /// Asynchronous `check_questionnaire_requirements()`.
    template <class CompletionToken>
    auto async_check_questionnaire_requirements(const CheckQuestionnaireRequirementsParams& params,
                                                CompletionToken&& token) const {
        return travel_rule_api_.async_check_questionnaire_requirements(
            params, std::forward<CompletionToken>(token));
    }

    /// Deposit History Travel Rule (for local entities that required travel rule) (supporting
    /// network) (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/deposit/history.
    ///
    /// Fetch deposit history for local entities that required travel rule.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime` are sent, time between `startTime` and `endTime` must be
    /// less than 90 days.
    /// - Please, note that due to network-specific characteristics, the returned source address may
    /// be inaccurate. If multiple source addresses are found, only the first one will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#deposit-history-travel-rule
    [[nodiscard]] common::RestApiResponse<std::vector<DepositHistoryTravelRuleResponseInner>>
    deposit_history_travel_rule(const DepositHistoryTravelRuleParams& params = {}) const {
        return travel_rule_api_.deposit_history_travel_rule(params);
    }
    /// Asynchronous `deposit_history_travel_rule()`.
    template <class CompletionToken>
    auto async_deposit_history_travel_rule(const DepositHistoryTravelRuleParams& params,
                                           CompletionToken&& token) const {
        return travel_rule_api_.async_deposit_history_travel_rule(
            params, std::forward<CompletionToken>(token));
    }

    /// Deposit History V2 (for local entities that required travel rule) (supporting network)
    /// (USER_DATA)
    ///
    /// GET /sapi/v2/localentity/deposit/history.
    ///
    /// Fetch deposit history for local entities that with required travel rule information.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime` are sent, time between `startTime` and `endTime` must be
    /// less than 90 days.
    /// - Please, note that due to network-specific characteristics, the returned source address may
    /// be inaccurate. If multiple source addresses are found, only the first one will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#deposit-history-v2
    [[nodiscard]] common::RestApiResponse<std::vector<DepositHistoryV2ResponseInner>>
    deposit_history_v2(const DepositHistoryV2Params& params = {}) const {
        return travel_rule_api_.deposit_history_v2(params);
    }
    /// Asynchronous `deposit_history_v2()`.
    template <class CompletionToken>
    auto async_deposit_history_v2(const DepositHistoryV2Params& params,
                                  CompletionToken&& token) const {
        return travel_rule_api_.async_deposit_history_v2(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Fetch address verification list (USER_DATA)
    ///
    /// GET /sapi/v1/addressVerify/list.
    ///
    /// Fetch address verification list for user to check on status and other details for the
    /// addresses stored in Address Book.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#fetch-address-verification-list
    [[nodiscard]] common::RestApiResponse<std::vector<FetchAddressVerificationListResponseInner>>
    fetch_address_verification_list(const FetchAddressVerificationListParams& params = {}) const {
        return travel_rule_api_.fetch_address_verification_list(params);
    }
    /// Asynchronous `fetch_address_verification_list()`.
    template <class CompletionToken>
    auto async_fetch_address_verification_list(const FetchAddressVerificationListParams& params,
                                               CompletionToken&& token) const {
        return travel_rule_api_.async_fetch_address_verification_list(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Country List (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/country/list.
    ///
    /// Query the active country list for travel rule questionnaires. Currently supports AU and BR
    /// entities.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#get-country-list
    [[nodiscard]] common::RestApiResponse<GetCountryListResponse>
    get_country_list(const GetCountryListParams& params = {}) const {
        return travel_rule_api_.get_country_list(params);
    }
    /// Asynchronous `get_country_list()`.
    template <class CompletionToken>
    auto async_get_country_list(const GetCountryListParams& params, CompletionToken&& token) const {
        return travel_rule_api_.async_get_country_list(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Get Region List (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/region/list.
    ///
    /// Query the active region/city list for a given country. Currently, only supports AU entity.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#get-region-list
    [[nodiscard]] common::RestApiResponse<GetRegionListResponse>
    get_region_list(const GetRegionListParams& params) const {
        return travel_rule_api_.get_region_list(params);
    }
    /// Asynchronous `get_region_list()`.
    template <class CompletionToken>
    auto async_get_region_list(const GetRegionListParams& params, CompletionToken&& token) const {
        return travel_rule_api_.async_get_region_list(params, std::forward<CompletionToken>(token));
    }

    /// Submit Deposit Questionnaire Broker (For local entities that require travel rule)
    /// (supporting network) (USER_DATA)
    ///
    /// PUT /sapi/v1/localentity/broker/deposit/provide-info.
    ///
    /// Submit questionnaire for brokers of local entities that require travel rule.
    /// The questionnaire is only applies to transactions from un-hosted wallets or VASPs that are
    /// not yet onboarded with GTR.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Questionnaire is different for each local entity, please refer to `Deposit Questionnaire
    /// Content` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// **StandardPii**
    ///
    /// **For Natural Person**
    ///
    /// - `piiType` (INTEGER, Mandatory): Fix to 0: Natural Person
    /// - `latinNames` (List<PiiName>, Mandatory): In case a person have complicated names or
    /// multiple names, this parameter is a list
    /// - `localNames` (List<PiiName>, Optional): In case a person have complicated names or
    /// multiple names, this parameter is a list
    /// - `nationality` (STRING, Optional)
    /// - `residenceCountry` (STRING, Mandatory)
    /// - `nationalIdentifier` (STRING, Optional)
    /// - `nationalIdentifierType` (STRING, Optional)
    /// - `nationalIdentifierIssueCountry` (STRING, Optional)
    /// - `dateOfBirth` (STRING, Optional): yyyy-mm-dd. Not required but strongly recommended.
    /// Providing DOB could greatly reduce false positive rate during risk checking process.
    /// - `placeOfBirth` (STRING, Optional)
    /// - `address` (STRING, Optional)
    ///
    /// **For Legal Person**
    ///
    /// - `piiType` (INTEGER, Mandatory): Fix to 1: Legal Person
    /// - `latinName` (STRING, Mandatory): It's company name for Legal Person
    /// - `localName` (STRING, Optional)
    /// - `registrationCountry` (STRING, Mandatory)
    /// - `nationalIdentifier` (STRING, Optional)
    /// - `nationalIdentifierType` (STRING, Optional)
    /// - `nationalIdentifierIssueCountry` (STRING, Optional)
    /// - `registrationDate` (STRING, Optional): yyyy-mm-dd. Not required but strongly recommended.
    /// - `address` (STRING, Optional)
    /// - `walletAddress` (STRING, Optional)
    /// - `walletTag` (STRING, Optional)
    ///
    /// **PiiName**
    ///
    /// - `firstName` (STRING, Mandatory): Mandatory for Natural person
    /// - `middleName` (STRING, Optional)
    /// - `lastName` (STRING, Optional)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#submit-deposit-questionnaire
    [[nodiscard]] common::RestApiResponse<SubmitDepositQuestionnaireResponse>
    submit_deposit_questionnaire(const SubmitDepositQuestionnaireParams& params) const {
        return travel_rule_api_.submit_deposit_questionnaire(params);
    }
    /// Asynchronous `submit_deposit_questionnaire()`.
    template <class CompletionToken>
    auto async_submit_deposit_questionnaire(const SubmitDepositQuestionnaireParams& params,
                                            CompletionToken&& token) const {
        return travel_rule_api_.async_submit_deposit_questionnaire(
            params, std::forward<CompletionToken>(token));
    }

    /// Submit Deposit Questionnaire (For local entities that require travel rule) (supporting
    /// network) (USER_DATA)
    ///
    /// PUT /sapi/v1/localentity/deposit/provide-info.
    ///
    /// Submit questionnaire for local entities that require travel rule.
    /// The questionnaire is only applies to transactions from unhosted wallets or VASPs that are
    /// not yet onboarded with GTR.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Questionnaire is different for each local entity, please refer to `Deposit Questionnaire
    /// Content` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#submit-deposit-questionnaire-travel-rule
    [[nodiscard]] common::RestApiResponse<SubmitDepositQuestionnaireTravelRuleResponse>
    submit_deposit_questionnaire_travel_rule(
        const SubmitDepositQuestionnaireTravelRuleParams& params) const {
        return travel_rule_api_.submit_deposit_questionnaire_travel_rule(params);
    }
    /// Asynchronous `submit_deposit_questionnaire_travel_rule()`.
    template <class CompletionToken>
    auto async_submit_deposit_questionnaire_travel_rule(
        const SubmitDepositQuestionnaireTravelRuleParams& params, CompletionToken&& token) const {
        return travel_rule_api_.async_submit_deposit_questionnaire_travel_rule(
            params, std::forward<CompletionToken>(token));
    }

    /// Submit Deposit Questionnaire V2 (For local entities that require travel rule) (supporting
    /// network) (USER_DATA)
    ///
    /// PUT /sapi/v2/localentity/deposit/provide-info.
    ///
    /// Submit questionnaire for local entities that require travel rule.
    /// The questionnaire is only applies to transactions from unhosted wallets or VASPs that are
    /// not yet onboarded with GTR.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Questionnaire is different for each local entity, please refer to `Deposit Questionnaire
    /// Content` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#submit-deposit-questionnaire-v2
    [[nodiscard]] common::RestApiResponse<SubmitDepositQuestionnaireV2Response>
    submit_deposit_questionnaire_v2(const SubmitDepositQuestionnaireV2Params& params) const {
        return travel_rule_api_.submit_deposit_questionnaire_v2(params);
    }
    /// Asynchronous `submit_deposit_questionnaire_v2()`.
    template <class CompletionToken>
    auto async_submit_deposit_questionnaire_v2(const SubmitDepositQuestionnaireV2Params& params,
                                               CompletionToken&& token) const {
        return travel_rule_api_.async_submit_deposit_questionnaire_v2(
            params, std::forward<CompletionToken>(token));
    }

    /// VASP list (for local entities that require travel rule) (supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/vasp.
    ///
    /// Fetch the VASP list for local entities.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#vasp-list
    [[nodiscard]] common::RestApiResponse<std::vector<VaspListResponseInner>>
    vasp_list(const VaspListParams& params = {}) const {
        return travel_rule_api_.vasp_list(params);
    }
    /// Asynchronous `vasp_list()`.
    template <class CompletionToken>
    auto async_vasp_list(const VaspListParams& params, CompletionToken&& token) const {
        return travel_rule_api_.async_vasp_list(params, std::forward<CompletionToken>(token));
    }

    /// Withdraw History Travel Rule (supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/withdraw/history.
    ///
    /// Fetch withdraw history for local entities that required travel rule.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `network` may not be in the response for old withdraw.
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime`are sent, time between `startTime`and `endTime`must be
    /// less than 90 days.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#withdraw-history-v1
    [[nodiscard]] common::RestApiResponse<std::vector<WithdrawHistoryV1ResponseInner>>
    withdraw_history_v1(const WithdrawHistoryV1Params& params = {}) const {
        return travel_rule_api_.withdraw_history_v1(params);
    }
    /// Asynchronous `withdraw_history_v1()`.
    template <class CompletionToken>
    auto async_withdraw_history_v1(const WithdrawHistoryV1Params& params,
                                   CompletionToken&& token) const {
        return travel_rule_api_.async_withdraw_history_v1(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Withdraw History V2 (for local entities that require travel rule) (supporting network)
    /// (USER_DATA)
    ///
    /// GET /sapi/v2/localentity/withdraw/history.
    ///
    /// Fetch withdraw history for local entities that required travel rule.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `network` may not be in the response for old withdraw.
    /// - Withdrawal made through /sapi/v1/capital/withdraw/apply may not be in the response.
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime`are sent, time between `startTime`and `endTime`must be
    /// less than 90 days.
    /// - If withdrawOrderId is sent, time between startTime and endTime must be less than 7 days.
    /// - If withdrawOrderId is sent, startTime and endTime are not sent, will return last 7 days
    /// records by default.
    /// - Maximum support trId,txId number is 45.
    /// - WithdrawOrderId only support 1.
    /// - If responsible does not include withdrawalStatus, please input trId or txId retrieve the
    /// data.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#withdraw-history-v2
    [[nodiscard]] common::RestApiResponse<std::vector<WithdrawHistoryV1ResponseInner>>
    withdraw_history_v2(const WithdrawHistoryV2Params& params = {}) const {
        return travel_rule_api_.withdraw_history_v2(params);
    }
    /// Asynchronous `withdraw_history_v2()`.
    template <class CompletionToken>
    auto async_withdraw_history_v2(const WithdrawHistoryV2Params& params,
                                   CompletionToken&& token) const {
        return travel_rule_api_.async_withdraw_history_v2(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Withdraw Travel Rule (USER_DATA)
    ///
    /// POST /sapi/v1/localentity/withdraw/apply.
    ///
    /// Submit a withdrawal request for local entities that required travel rule.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `network` not send, return with default network of the coin, but if the address could
    /// not match default network, the withdraw will be rejected.
    /// - You can get `network` and `isDefault` in `networkList` of a coin in the response of `Get
    /// /sapi/v1/capital/config/getall (HMAC SHA256)`.
    /// - Questionnaire is different for each local entity, please refer to the `Withdraw
    /// Questionnaire Contents` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#withdraw-travel-rule
    [[nodiscard]] common::RestApiResponse<WithdrawTravelRuleResponse>
    withdraw_travel_rule(const WithdrawTravelRuleParams& params) const {
        return travel_rule_api_.withdraw_travel_rule(params);
    }
    /// Asynchronous `withdraw_travel_rule()`.
    template <class CompletionToken>
    auto async_withdraw_travel_rule(const WithdrawTravelRuleParams& params,
                                    CompletionToken&& token) const {
        return travel_rule_api_.async_withdraw_travel_rule(params,
                                                           std::forward<CompletionToken>(token));
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
    AccountApi account_api_;
    AssetApi asset_api_;
    CapitalApi capital_api_;
    OthersApi others_api_;
    TravelRuleApi travel_rule_api_;
};

} // namespace binance::wallet::rest_api
