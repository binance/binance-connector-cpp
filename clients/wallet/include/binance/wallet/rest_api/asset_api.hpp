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
#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/asset_detail_response.hpp>
#include <binance/wallet/rest_api/models/asset_dividend_record_response.hpp>
#include <binance/wallet/rest_api/models/dust_convert_response.hpp>
#include <binance/wallet/rest_api/models/dust_convertible_assets_response.hpp>
#include <binance/wallet/rest_api/models/dust_transfer_response.hpp>
#include <binance/wallet/rest_api/models/dustlog_response.hpp>
#include <binance/wallet/rest_api/models/funding_wallet_response_inner.hpp>
#include <binance/wallet/rest_api/models/get_assets_that_can_be_converted_into_bnb_response.hpp>
#include <binance/wallet/rest_api/models/get_cloud_mining_payment_and_refund_history_response.hpp>
#include <binance/wallet/rest_api/models/get_open_symbol_list_response_inner.hpp>
#include <binance/wallet/rest_api/models/get_spot_asset_tags_response_inner.hpp>
#include <binance/wallet/rest_api/models/query_user_delegation_history_response.hpp>
#include <binance/wallet/rest_api/models/query_user_universal_transfer_history_response.hpp>
#include <binance/wallet/rest_api/models/query_user_wallet_balance_response_inner.hpp>
#include <binance/wallet/rest_api/models/toggle_bnb_burn_on_spot_trade_and_margin_interest_response.hpp>
#include <binance/wallet/rest_api/models/trade_fee_response_inner.hpp>
#include <binance/wallet/rest_api/models/user_asset_response_inner.hpp>
#include <binance/wallet/rest_api/models/user_universal_transfer_response.hpp>

namespace binance::wallet::rest_api {

enum class DustTransferAccountTypeEnum {
    Spot,
    Margin,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(DustTransferAccountTypeEnum value) noexcept;
BINANCE_WALLET_EXPORT DustTransferAccountTypeEnum tag_invoke(
    boost::json::value_to_tag<DustTransferAccountTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      DustTransferAccountTypeEnum value);

enum class DustlogAccountTypeEnum {
    Spot,
    Margin,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(DustlogAccountTypeEnum value) noexcept;
BINANCE_WALLET_EXPORT DustlogAccountTypeEnum
tag_invoke(boost::json::value_to_tag<DustlogAccountTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      DustlogAccountTypeEnum value);

enum class GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum {
    Spot,
    Margin,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum value) noexcept;
BINANCE_WALLET_EXPORT GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum
tag_invoke(boost::json::value_to_tag<GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum value);

enum class QueryUserDelegationHistoryTypeEnum {
    Delegate,
    Undelegate,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(QueryUserDelegationHistoryTypeEnum value) noexcept;
BINANCE_WALLET_EXPORT QueryUserDelegationHistoryTypeEnum
tag_invoke(boost::json::value_to_tag<QueryUserDelegationHistoryTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      QueryUserDelegationHistoryTypeEnum value);

enum class QueryUserUniversalTransferHistoryFromSymbolEnum {
    IsolatedmarginMargin,
    IsolatedmarginIsolatedmargin,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(QueryUserUniversalTransferHistoryFromSymbolEnum value) noexcept;
BINANCE_WALLET_EXPORT QueryUserUniversalTransferHistoryFromSymbolEnum
tag_invoke(boost::json::value_to_tag<QueryUserUniversalTransferHistoryFromSymbolEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      QueryUserUniversalTransferHistoryFromSymbolEnum value);

enum class QueryUserUniversalTransferHistoryToSymbolEnum {
    MarginIsolatedmargin,
    IsolatedmarginIsolatedmargin,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(QueryUserUniversalTransferHistoryToSymbolEnum value) noexcept;
BINANCE_WALLET_EXPORT QueryUserUniversalTransferHistoryToSymbolEnum
tag_invoke(boost::json::value_to_tag<QueryUserUniversalTransferHistoryToSymbolEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      QueryUserUniversalTransferHistoryToSymbolEnum value);

enum class UserUniversalTransferTypeEnum {
    MainUmfuture,
    MainCmfuture,
    MainMargin,
    UmfutureMain,
    UmfutureMargin,
    CmfutureMain,
    CmfutureMargin,
    MarginMain,
    MarginUmfuture,
    MarginCmfuture,
    IsolatedmarginMargin,
    MarginIsolatedmargin,
    IsolatedmarginIsolatedmargin,
    MainFunding,
    FundingMain,
    FundingUmfuture,
    UmfutureFunding,
    MarginFunding,
    FundingMargin,
    FundingCmfuture,
    CmfutureFunding,
    MainOption,
    OptionMain,
    UmfutureOption,
    OptionUmfuture,
    MarginOption,
    OptionMargin,
    FundingOption,
    OptionFunding,
    MainPortfolioMargin,
    PortfolioMarginMain,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(UserUniversalTransferTypeEnum value) noexcept;
BINANCE_WALLET_EXPORT UserUniversalTransferTypeEnum tag_invoke(
    boost::json::value_to_tag<UserUniversalTransferTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      UserUniversalTransferTypeEnum value);

enum class UserUniversalTransferFromSymbolEnum {
    IsolatedmarginMargin,
    IsolatedmarginIsolatedmargin,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(UserUniversalTransferFromSymbolEnum value) noexcept;
BINANCE_WALLET_EXPORT UserUniversalTransferFromSymbolEnum
tag_invoke(boost::json::value_to_tag<UserUniversalTransferFromSymbolEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      UserUniversalTransferFromSymbolEnum value);

enum class UserUniversalTransferToSymbolEnum {
    MarginIsolatedmargin,
    IsolatedmarginIsolatedmargin,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(UserUniversalTransferToSymbolEnum value) noexcept;
BINANCE_WALLET_EXPORT UserUniversalTransferToSymbolEnum
tag_invoke(boost::json::value_to_tag<UserUniversalTransferToSymbolEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      UserUniversalTransferToSymbolEnum value);

struct AssetDetailParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AssetDividendRecordParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DustConvertParams {
    common::Required<std::string> asset;
    /// `SPOT` or `MARGIN`, default `SPOT`
    std::optional<std::string> account_type = std::nullopt;
    /// A unique id for the request
    std::optional<std::string> client_id = std::nullopt;
    std::optional<std::string> target_asset = std::nullopt;
    std::optional<std::string> third_party_client_id = std::nullopt;
    std::optional<common::Decimal> dust_quota_asset_to_target_asset_price = std::nullopt;
};

struct DustConvertibleAssetsParams {
    common::Required<std::string> target_asset;
    /// `SPOT` or `MARGIN`, default `SPOT`
    std::optional<std::string> account_type = std::nullopt;
    std::optional<common::Decimal> dust_quota_asset_to_target_asset_price = std::nullopt;
};

struct DustTransferParams {
    /// The asset being converted. For example: asset=BTC,USDT
    common::Required<std::string> asset;
    std::optional<DustTransferAccountTypeEnum> account_type = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DustlogParams {
    std::optional<DustlogAccountTypeEnum> account_type = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FundingWalletParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<bool> need_btc_valuation = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetAssetsThatCanBeConvertedIntoBnbParams {
    std::optional<GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum> account_type = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCloudMiningPaymentAndRefundHistoryParams {
    /// inclusive, unit: ms
    common::Required<std::int64_t> start_time;
    /// exclusive, unit: ms
    common::Required<std::int64_t> end_time;
    /// The transaction id
    std::optional<std::int64_t> tran_id = std::nullopt;
    /// The unique flag
    std::optional<std::string> client_tran_id = std::nullopt;
    /// If it is blank, we will query all assets
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
};

struct GetSpotAssetTagsParams {
    /// Tag filter. Supports multiple comma-separated tags with OR semantics (an asset is returned
    /// if it matches any one tag); leading/trailing whitespace around each tag is ignored. Returns
    /// all eligible assets when omitted.
    std::optional<std::string> tag = std::nullopt;
};

struct QueryUserDelegationHistoryParams {
    common::Required<std::string> email;
    common::Required<std::int64_t> start_time;
    common::Required<std::int64_t> end_time;
    std::optional<QueryUserDelegationHistoryTypeEnum> type = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUserUniversalTransferHistoryParams {
    common::Required<std::string> type;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<QueryUserUniversalTransferHistoryFromSymbolEnum> from_symbol = std::nullopt;
    std::optional<QueryUserUniversalTransferHistoryToSymbolEnum> to_symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UserUniversalTransferParams {
    common::Required<UserUniversalTransferTypeEnum> type;
    common::Required<std::string> asset;
    common::Required<common::Decimal> amount;
    std::optional<UserUniversalTransferFromSymbolEnum> from_symbol = std::nullopt;
    std::optional<UserUniversalTransferToSymbolEnum> to_symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUserWalletBalanceParams {
    std::optional<std::string> quote_asset = std::nullopt;
    /// Whether to return the per-asset balance detail for each wallet. When `false` or omitted, the
    /// response is unchanged from current behavior.
    std::optional<bool> need_balance_detail = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ToggleBnbBurnOnSpotTradeAndMarginInterestParams {
    /// Determines whether to use BNB to pay for trading fees on SPOT
    std::optional<std::string> spot_bnb_burn = std::nullopt;
    /// Determines whether to use BNB to pay for margin loan's interest
    std::optional<std::string> interest_bnb_burn = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TradeFeeParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UserAssetParams {
    /// If asset is blank, then query all positive assets user have.
    std::optional<std::string> asset = std::nullopt;
    /// Whether need btc valuation or not.
    std::optional<bool> need_btc_valuation = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_WALLET_EXPORT AssetApi {
public:
    explicit AssetApi(std::shared_ptr<common::RestClient> client);

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
    asset_detail(const AssetDetailParams& params = {}) const;

    /// Asynchronous `asset_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AssetDetailResponse>)`.
    template <class CompletionToken>
    auto async_asset_detail(const AssetDetailParams& params, CompletionToken&& token) const {
        return common::async_send<AssetDetailResponse>(client_, asset_detail_request(params),
                                                       std::forward<CompletionToken>(token));
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
    asset_dividend_record(const AssetDividendRecordParams& params = {}) const;

    /// Asynchronous `asset_dividend_record()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AssetDividendRecordResponse>)`.
    template <class CompletionToken>
    auto async_asset_dividend_record(const AssetDividendRecordParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<AssetDividendRecordResponse>(
            client_, asset_dividend_record_request(params), std::forward<CompletionToken>(token));
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
    dust_convert(const DustConvertParams& params) const;

    /// Asynchronous `dust_convert()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DustConvertResponse>)`.
    template <class CompletionToken>
    auto async_dust_convert(const DustConvertParams& params, CompletionToken&& token) const {
        return common::async_send<DustConvertResponse>(client_, dust_convert_request(params),
                                                       std::forward<CompletionToken>(token));
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
    dust_convertible_assets(const DustConvertibleAssetsParams& params) const;

    /// Asynchronous `dust_convertible_assets()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DustConvertibleAssetsResponse>)`.
    template <class CompletionToken>
    auto async_dust_convertible_assets(const DustConvertibleAssetsParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<DustConvertibleAssetsResponse>(
            client_, dust_convertible_assets_request(params), std::forward<CompletionToken>(token));
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
    dust_transfer(const DustTransferParams& params) const;

    /// Asynchronous `dust_transfer()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DustTransferResponse>)`.
    template <class CompletionToken>
    auto async_dust_transfer(const DustTransferParams& params, CompletionToken&& token) const {
        return common::async_send<DustTransferResponse>(client_, dust_transfer_request(params),
                                                        std::forward<CompletionToken>(token));
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
    dustlog(const DustlogParams& params = {}) const;

    /// Asynchronous `dustlog()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DustlogResponse>)`.
    template <class CompletionToken>
    auto async_dustlog(const DustlogParams& params, CompletionToken&& token) const {
        return common::async_send<DustlogResponse>(client_, dustlog_request(params),
                                                   std::forward<CompletionToken>(token));
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
    funding_wallet(const FundingWalletParams& params = {}) const;

    /// Asynchronous `funding_wallet()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<FundingWalletResponseInner>>)`.
    template <class CompletionToken>
    auto async_funding_wallet(const FundingWalletParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<FundingWalletResponseInner>>(
            client_, funding_wallet_request(params), std::forward<CompletionToken>(token));
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
        const GetAssetsThatCanBeConvertedIntoBnbParams& params = {}) const;

    /// Asynchronous `get_assets_that_can_be_converted_into_bnb()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetAssetsThatCanBeConvertedIntoBnbResponse>)`.
    template <class CompletionToken>
    auto async_get_assets_that_can_be_converted_into_bnb(
        const GetAssetsThatCanBeConvertedIntoBnbParams& params, CompletionToken&& token) const {
        return common::async_send<GetAssetsThatCanBeConvertedIntoBnbResponse>(
            client_, get_assets_that_can_be_converted_into_bnb_request(params),
            std::forward<CompletionToken>(token));
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
        const GetCloudMiningPaymentAndRefundHistoryParams& params) const;

    /// Asynchronous `get_cloud_mining_payment_and_refund_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetCloudMiningPaymentAndRefundHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_cloud_mining_payment_and_refund_history(
        const GetCloudMiningPaymentAndRefundHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetCloudMiningPaymentAndRefundHistoryResponse>(
            client_, get_cloud_mining_payment_and_refund_history_request(params),
            std::forward<CompletionToken>(token));
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
    get_open_symbol_list() const;

    /// Asynchronous `get_open_symbol_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetOpenSymbolListResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_open_symbol_list(CompletionToken&& token) const {
        return common::async_send<std::vector<GetOpenSymbolListResponseInner>>(
            client_, get_open_symbol_list_request(), std::forward<CompletionToken>(token));
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
    get_spot_asset_tags(const GetSpotAssetTagsParams& params = {}) const;

    /// Asynchronous `get_spot_asset_tags()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetSpotAssetTagsResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_spot_asset_tags(const GetSpotAssetTagsParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<std::vector<GetSpotAssetTagsResponseInner>>(
            client_, get_spot_asset_tags_request(params), std::forward<CompletionToken>(token));
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
    query_user_delegation_history(const QueryUserDelegationHistoryParams& params) const;

    /// Asynchronous `query_user_delegation_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryUserDelegationHistoryResponse>)`.
    template <class CompletionToken>
    auto async_query_user_delegation_history(const QueryUserDelegationHistoryParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<QueryUserDelegationHistoryResponse>(
            client_, query_user_delegation_history_request(params),
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
        const QueryUserUniversalTransferHistoryParams& params) const;

    /// Asynchronous `query_user_universal_transfer_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryUserUniversalTransferHistoryResponse>)`.
    template <class CompletionToken>
    auto async_query_user_universal_transfer_history(
        const QueryUserUniversalTransferHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<QueryUserUniversalTransferHistoryResponse>(
            client_, query_user_universal_transfer_history_request(params),
            std::forward<CompletionToken>(token));
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
    user_universal_transfer(const UserUniversalTransferParams& params) const;

    /// Asynchronous `user_universal_transfer()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<UserUniversalTransferResponse>)`.
    template <class CompletionToken>
    auto async_user_universal_transfer(const UserUniversalTransferParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<UserUniversalTransferResponse>(
            client_, user_universal_transfer_request(params), std::forward<CompletionToken>(token));
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
    query_user_wallet_balance(const QueryUserWalletBalanceParams& params = {}) const;

    /// Asynchronous `query_user_wallet_balance()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryUserWalletBalanceResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_user_wallet_balance(const QueryUserWalletBalanceParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<std::vector<QueryUserWalletBalanceResponseInner>>(
            client_, query_user_wallet_balance_request(params),
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
        const ToggleBnbBurnOnSpotTradeAndMarginInterestParams& params = {}) const;

    /// Asynchronous `toggle_bnb_burn_on_spot_trade_and_margin_interest()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<ToggleBnbBurnOnSpotTradeAndMarginInterestResponse>)`.
    template <class CompletionToken>
    auto async_toggle_bnb_burn_on_spot_trade_and_margin_interest(
        const ToggleBnbBurnOnSpotTradeAndMarginInterestParams& params,
        CompletionToken&& token) const {
        return common::async_send<ToggleBnbBurnOnSpotTradeAndMarginInterestResponse>(
            client_, toggle_bnb_burn_on_spot_trade_and_margin_interest_request(params),
            std::forward<CompletionToken>(token));
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
    trade_fee(const TradeFeeParams& params = {}) const;

    /// Asynchronous `trade_fee()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<TradeFeeResponseInner>>)`.
    template <class CompletionToken>
    auto async_trade_fee(const TradeFeeParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<TradeFeeResponseInner>>(
            client_, trade_fee_request(params), std::forward<CompletionToken>(token));
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
    user_asset(const UserAssetParams& params = {}) const;

    /// Asynchronous `user_asset()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<UserAssetResponseInner>>)`.
    template <class CompletionToken>
    auto async_user_asset(const UserAssetParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<UserAssetResponseInner>>(
            client_, user_asset_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest asset_detail_request(const AssetDetailParams& params) const;
    [[nodiscard]] common::RestRequest
    asset_dividend_record_request(const AssetDividendRecordParams& params) const;
    [[nodiscard]] common::RestRequest dust_convert_request(const DustConvertParams& params) const;
    [[nodiscard]] common::RestRequest
    dust_convertible_assets_request(const DustConvertibleAssetsParams& params) const;
    [[nodiscard]] common::RestRequest dust_transfer_request(const DustTransferParams& params) const;
    [[nodiscard]] common::RestRequest dustlog_request(const DustlogParams& params) const;
    [[nodiscard]] common::RestRequest
    funding_wallet_request(const FundingWalletParams& params) const;
    [[nodiscard]] common::RestRequest get_assets_that_can_be_converted_into_bnb_request(
        const GetAssetsThatCanBeConvertedIntoBnbParams& params) const;
    [[nodiscard]] common::RestRequest get_cloud_mining_payment_and_refund_history_request(
        const GetCloudMiningPaymentAndRefundHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_open_symbol_list_request() const;
    [[nodiscard]] common::RestRequest
    get_spot_asset_tags_request(const GetSpotAssetTagsParams& params) const;
    [[nodiscard]] common::RestRequest
    query_user_delegation_history_request(const QueryUserDelegationHistoryParams& params) const;
    [[nodiscard]] common::RestRequest query_user_universal_transfer_history_request(
        const QueryUserUniversalTransferHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    user_universal_transfer_request(const UserUniversalTransferParams& params) const;
    [[nodiscard]] common::RestRequest
    query_user_wallet_balance_request(const QueryUserWalletBalanceParams& params) const;
    [[nodiscard]] common::RestRequest toggle_bnb_burn_on_spot_trade_and_margin_interest_request(
        const ToggleBnbBurnOnSpotTradeAndMarginInterestParams& params) const;
    [[nodiscard]] common::RestRequest trade_fee_request(const TradeFeeParams& params) const;
    [[nodiscard]] common::RestRequest user_asset_request(const UserAssetParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::wallet::rest_api
