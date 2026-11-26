//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/asset_api.hpp>

namespace binance::wallet::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(DustTransferAccountTypeEnum value) noexcept {
    switch (value) {
    case DustTransferAccountTypeEnum::Spot:
        return "SPOT";
    case DustTransferAccountTypeEnum::Margin:
        return "MARGIN";
    case DustTransferAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

DustTransferAccountTypeEnum
tag_invoke(boost::json::value_to_tag<DustTransferAccountTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return DustTransferAccountTypeEnum::Spot;
    }
    if (s == "MARGIN") {
        return DustTransferAccountTypeEnum::Margin;
    }
    return DustTransferAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                DustTransferAccountTypeEnum value) {
    if (value == DustTransferAccountTypeEnum::Unknown) {
        throw std::invalid_argument("DustTransferAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(DustlogAccountTypeEnum value) noexcept {
    switch (value) {
    case DustlogAccountTypeEnum::Spot:
        return "SPOT";
    case DustlogAccountTypeEnum::Margin:
        return "MARGIN";
    case DustlogAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

DustlogAccountTypeEnum tag_invoke(boost::json::value_to_tag<DustlogAccountTypeEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return DustlogAccountTypeEnum::Spot;
    }
    if (s == "MARGIN") {
        return DustlogAccountTypeEnum::Margin;
    }
    return DustlogAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                DustlogAccountTypeEnum value) {
    if (value == DustlogAccountTypeEnum::Unknown) {
        throw std::invalid_argument("DustlogAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum value) noexcept {
    switch (value) {
    case GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum::Spot:
        return "SPOT";
    case GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum::Margin:
        return "MARGIN";
    case GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum
tag_invoke(boost::json::value_to_tag<GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum::Spot;
    }
    if (s == "MARGIN") {
        return GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum::Margin;
    }
    return GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum value) {
    if (value == GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum::Unknown) {
        throw std::invalid_argument(
            "GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryUserDelegationHistoryTypeEnum value) noexcept {
    switch (value) {
    case QueryUserDelegationHistoryTypeEnum::Delegate:
        return "DELEGATE";
    case QueryUserDelegationHistoryTypeEnum::Undelegate:
        return "UNDELEGATE";
    case QueryUserDelegationHistoryTypeEnum::Unknown:
        break;
    }
    return "";
}

QueryUserDelegationHistoryTypeEnum
tag_invoke(boost::json::value_to_tag<QueryUserDelegationHistoryTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "DELEGATE") {
        return QueryUserDelegationHistoryTypeEnum::Delegate;
    }
    if (s == "UNDELEGATE") {
        return QueryUserDelegationHistoryTypeEnum::Undelegate;
    }
    return QueryUserDelegationHistoryTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryUserDelegationHistoryTypeEnum value) {
    if (value == QueryUserDelegationHistoryTypeEnum::Unknown) {
        throw std::invalid_argument("QueryUserDelegationHistoryTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryUserUniversalTransferHistoryFromSymbolEnum value) noexcept {
    switch (value) {
    case QueryUserUniversalTransferHistoryFromSymbolEnum::IsolatedmarginMargin:
        return "ISOLATEDMARGIN_MARGIN";
    case QueryUserUniversalTransferHistoryFromSymbolEnum::IsolatedmarginIsolatedmargin:
        return "ISOLATEDMARGIN_ISOLATEDMARGIN";
    case QueryUserUniversalTransferHistoryFromSymbolEnum::Unknown:
        break;
    }
    return "";
}

QueryUserUniversalTransferHistoryFromSymbolEnum
tag_invoke(boost::json::value_to_tag<QueryUserUniversalTransferHistoryFromSymbolEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ISOLATEDMARGIN_MARGIN") {
        return QueryUserUniversalTransferHistoryFromSymbolEnum::IsolatedmarginMargin;
    }
    if (s == "ISOLATEDMARGIN_ISOLATEDMARGIN") {
        return QueryUserUniversalTransferHistoryFromSymbolEnum::IsolatedmarginIsolatedmargin;
    }
    return QueryUserUniversalTransferHistoryFromSymbolEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryUserUniversalTransferHistoryFromSymbolEnum value) {
    if (value == QueryUserUniversalTransferHistoryFromSymbolEnum::Unknown) {
        throw std::invalid_argument(
            "QueryUserUniversalTransferHistoryFromSymbolEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryUserUniversalTransferHistoryToSymbolEnum value) noexcept {
    switch (value) {
    case QueryUserUniversalTransferHistoryToSymbolEnum::MarginIsolatedmargin:
        return "MARGIN_ISOLATEDMARGIN";
    case QueryUserUniversalTransferHistoryToSymbolEnum::IsolatedmarginIsolatedmargin:
        return "ISOLATEDMARGIN_ISOLATEDMARGIN";
    case QueryUserUniversalTransferHistoryToSymbolEnum::Unknown:
        break;
    }
    return "";
}

QueryUserUniversalTransferHistoryToSymbolEnum
tag_invoke(boost::json::value_to_tag<QueryUserUniversalTransferHistoryToSymbolEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARGIN_ISOLATEDMARGIN") {
        return QueryUserUniversalTransferHistoryToSymbolEnum::MarginIsolatedmargin;
    }
    if (s == "ISOLATEDMARGIN_ISOLATEDMARGIN") {
        return QueryUserUniversalTransferHistoryToSymbolEnum::IsolatedmarginIsolatedmargin;
    }
    return QueryUserUniversalTransferHistoryToSymbolEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryUserUniversalTransferHistoryToSymbolEnum value) {
    if (value == QueryUserUniversalTransferHistoryToSymbolEnum::Unknown) {
        throw std::invalid_argument(
            "QueryUserUniversalTransferHistoryToSymbolEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(UserUniversalTransferTypeEnum value) noexcept {
    switch (value) {
    case UserUniversalTransferTypeEnum::MainUmfuture:
        return "MAIN_UMFUTURE";
    case UserUniversalTransferTypeEnum::MainCmfuture:
        return "MAIN_CMFUTURE";
    case UserUniversalTransferTypeEnum::MainMargin:
        return "MAIN_MARGIN";
    case UserUniversalTransferTypeEnum::UmfutureMain:
        return "UMFUTURE_MAIN";
    case UserUniversalTransferTypeEnum::UmfutureMargin:
        return "UMFUTURE_MARGIN";
    case UserUniversalTransferTypeEnum::CmfutureMain:
        return "CMFUTURE_MAIN";
    case UserUniversalTransferTypeEnum::CmfutureMargin:
        return "CMFUTURE_MARGIN";
    case UserUniversalTransferTypeEnum::MarginMain:
        return "MARGIN_MAIN";
    case UserUniversalTransferTypeEnum::MarginUmfuture:
        return "MARGIN_UMFUTURE";
    case UserUniversalTransferTypeEnum::MarginCmfuture:
        return "MARGIN_CMFUTURE";
    case UserUniversalTransferTypeEnum::IsolatedmarginMargin:
        return "ISOLATEDMARGIN_MARGIN";
    case UserUniversalTransferTypeEnum::MarginIsolatedmargin:
        return "MARGIN_ISOLATEDMARGIN";
    case UserUniversalTransferTypeEnum::IsolatedmarginIsolatedmargin:
        return "ISOLATEDMARGIN_ISOLATEDMARGIN";
    case UserUniversalTransferTypeEnum::MainFunding:
        return "MAIN_FUNDING";
    case UserUniversalTransferTypeEnum::FundingMain:
        return "FUNDING_MAIN";
    case UserUniversalTransferTypeEnum::FundingUmfuture:
        return "FUNDING_UMFUTURE";
    case UserUniversalTransferTypeEnum::UmfutureFunding:
        return "UMFUTURE_FUNDING";
    case UserUniversalTransferTypeEnum::MarginFunding:
        return "MARGIN_FUNDING";
    case UserUniversalTransferTypeEnum::FundingMargin:
        return "FUNDING_MARGIN";
    case UserUniversalTransferTypeEnum::FundingCmfuture:
        return "FUNDING_CMFUTURE";
    case UserUniversalTransferTypeEnum::CmfutureFunding:
        return "CMFUTURE_FUNDING";
    case UserUniversalTransferTypeEnum::MainOption:
        return "MAIN_OPTION";
    case UserUniversalTransferTypeEnum::OptionMain:
        return "OPTION_MAIN";
    case UserUniversalTransferTypeEnum::UmfutureOption:
        return "UMFUTURE_OPTION";
    case UserUniversalTransferTypeEnum::OptionUmfuture:
        return "OPTION_UMFUTURE";
    case UserUniversalTransferTypeEnum::MarginOption:
        return "MARGIN_OPTION";
    case UserUniversalTransferTypeEnum::OptionMargin:
        return "OPTION_MARGIN";
    case UserUniversalTransferTypeEnum::FundingOption:
        return "FUNDING_OPTION";
    case UserUniversalTransferTypeEnum::OptionFunding:
        return "OPTION_FUNDING";
    case UserUniversalTransferTypeEnum::MainPortfolioMargin:
        return "MAIN_PORTFOLIO_MARGIN";
    case UserUniversalTransferTypeEnum::PortfolioMarginMain:
        return "PORTFOLIO_MARGIN_MAIN";
    case UserUniversalTransferTypeEnum::Unknown:
        break;
    }
    return "";
}

UserUniversalTransferTypeEnum
tag_invoke(boost::json::value_to_tag<UserUniversalTransferTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MAIN_UMFUTURE") {
        return UserUniversalTransferTypeEnum::MainUmfuture;
    }
    if (s == "MAIN_CMFUTURE") {
        return UserUniversalTransferTypeEnum::MainCmfuture;
    }
    if (s == "MAIN_MARGIN") {
        return UserUniversalTransferTypeEnum::MainMargin;
    }
    if (s == "UMFUTURE_MAIN") {
        return UserUniversalTransferTypeEnum::UmfutureMain;
    }
    if (s == "UMFUTURE_MARGIN") {
        return UserUniversalTransferTypeEnum::UmfutureMargin;
    }
    if (s == "CMFUTURE_MAIN") {
        return UserUniversalTransferTypeEnum::CmfutureMain;
    }
    if (s == "CMFUTURE_MARGIN") {
        return UserUniversalTransferTypeEnum::CmfutureMargin;
    }
    if (s == "MARGIN_MAIN") {
        return UserUniversalTransferTypeEnum::MarginMain;
    }
    if (s == "MARGIN_UMFUTURE") {
        return UserUniversalTransferTypeEnum::MarginUmfuture;
    }
    if (s == "MARGIN_CMFUTURE") {
        return UserUniversalTransferTypeEnum::MarginCmfuture;
    }
    if (s == "ISOLATEDMARGIN_MARGIN") {
        return UserUniversalTransferTypeEnum::IsolatedmarginMargin;
    }
    if (s == "MARGIN_ISOLATEDMARGIN") {
        return UserUniversalTransferTypeEnum::MarginIsolatedmargin;
    }
    if (s == "ISOLATEDMARGIN_ISOLATEDMARGIN") {
        return UserUniversalTransferTypeEnum::IsolatedmarginIsolatedmargin;
    }
    if (s == "MAIN_FUNDING") {
        return UserUniversalTransferTypeEnum::MainFunding;
    }
    if (s == "FUNDING_MAIN") {
        return UserUniversalTransferTypeEnum::FundingMain;
    }
    if (s == "FUNDING_UMFUTURE") {
        return UserUniversalTransferTypeEnum::FundingUmfuture;
    }
    if (s == "UMFUTURE_FUNDING") {
        return UserUniversalTransferTypeEnum::UmfutureFunding;
    }
    if (s == "MARGIN_FUNDING") {
        return UserUniversalTransferTypeEnum::MarginFunding;
    }
    if (s == "FUNDING_MARGIN") {
        return UserUniversalTransferTypeEnum::FundingMargin;
    }
    if (s == "FUNDING_CMFUTURE") {
        return UserUniversalTransferTypeEnum::FundingCmfuture;
    }
    if (s == "CMFUTURE_FUNDING") {
        return UserUniversalTransferTypeEnum::CmfutureFunding;
    }
    if (s == "MAIN_OPTION") {
        return UserUniversalTransferTypeEnum::MainOption;
    }
    if (s == "OPTION_MAIN") {
        return UserUniversalTransferTypeEnum::OptionMain;
    }
    if (s == "UMFUTURE_OPTION") {
        return UserUniversalTransferTypeEnum::UmfutureOption;
    }
    if (s == "OPTION_UMFUTURE") {
        return UserUniversalTransferTypeEnum::OptionUmfuture;
    }
    if (s == "MARGIN_OPTION") {
        return UserUniversalTransferTypeEnum::MarginOption;
    }
    if (s == "OPTION_MARGIN") {
        return UserUniversalTransferTypeEnum::OptionMargin;
    }
    if (s == "FUNDING_OPTION") {
        return UserUniversalTransferTypeEnum::FundingOption;
    }
    if (s == "OPTION_FUNDING") {
        return UserUniversalTransferTypeEnum::OptionFunding;
    }
    if (s == "MAIN_PORTFOLIO_MARGIN") {
        return UserUniversalTransferTypeEnum::MainPortfolioMargin;
    }
    if (s == "PORTFOLIO_MARGIN_MAIN") {
        return UserUniversalTransferTypeEnum::PortfolioMarginMain;
    }
    return UserUniversalTransferTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                UserUniversalTransferTypeEnum value) {
    if (value == UserUniversalTransferTypeEnum::Unknown) {
        throw std::invalid_argument("UserUniversalTransferTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(UserUniversalTransferFromSymbolEnum value) noexcept {
    switch (value) {
    case UserUniversalTransferFromSymbolEnum::IsolatedmarginMargin:
        return "ISOLATEDMARGIN_MARGIN";
    case UserUniversalTransferFromSymbolEnum::IsolatedmarginIsolatedmargin:
        return "ISOLATEDMARGIN_ISOLATEDMARGIN";
    case UserUniversalTransferFromSymbolEnum::Unknown:
        break;
    }
    return "";
}

UserUniversalTransferFromSymbolEnum
tag_invoke(boost::json::value_to_tag<UserUniversalTransferFromSymbolEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ISOLATEDMARGIN_MARGIN") {
        return UserUniversalTransferFromSymbolEnum::IsolatedmarginMargin;
    }
    if (s == "ISOLATEDMARGIN_ISOLATEDMARGIN") {
        return UserUniversalTransferFromSymbolEnum::IsolatedmarginIsolatedmargin;
    }
    return UserUniversalTransferFromSymbolEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                UserUniversalTransferFromSymbolEnum value) {
    if (value == UserUniversalTransferFromSymbolEnum::Unknown) {
        throw std::invalid_argument("UserUniversalTransferFromSymbolEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(UserUniversalTransferToSymbolEnum value) noexcept {
    switch (value) {
    case UserUniversalTransferToSymbolEnum::MarginIsolatedmargin:
        return "MARGIN_ISOLATEDMARGIN";
    case UserUniversalTransferToSymbolEnum::IsolatedmarginIsolatedmargin:
        return "ISOLATEDMARGIN_ISOLATEDMARGIN";
    case UserUniversalTransferToSymbolEnum::Unknown:
        break;
    }
    return "";
}

UserUniversalTransferToSymbolEnum
tag_invoke(boost::json::value_to_tag<UserUniversalTransferToSymbolEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARGIN_ISOLATEDMARGIN") {
        return UserUniversalTransferToSymbolEnum::MarginIsolatedmargin;
    }
    if (s == "ISOLATEDMARGIN_ISOLATEDMARGIN") {
        return UserUniversalTransferToSymbolEnum::IsolatedmarginIsolatedmargin;
    }
    return UserUniversalTransferToSymbolEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                UserUniversalTransferToSymbolEnum value) {
    if (value == UserUniversalTransferToSymbolEnum::Unknown) {
        throw std::invalid_argument("UserUniversalTransferToSymbolEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

AssetApi::AssetApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest AssetApi::asset_detail_request(const AssetDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/asset/assetDetail";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AssetDetailResponse>
AssetApi::asset_detail(const AssetDetailParams& params) const {
    return common::send<AssetDetailResponse>(*client_, asset_detail_request(params));
}

common::RestRequest
AssetApi::asset_dividend_record_request(const AssetDividendRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/asset/assetDividend";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AssetDividendRecordResponse>
AssetApi::asset_dividend_record(const AssetDividendRecordParams& params) const {
    return common::send<AssetDividendRecordResponse>(*client_,
                                                     asset_dividend_record_request(params));
}

common::RestRequest AssetApi::dust_convert_request(const DustConvertParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/asset/dust-convert/convert";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    common::detail::json::set_param(req.query, "clientId", params.client_id);
    common::detail::json::set_param(req.query, "targetAsset", params.target_asset);
    common::detail::json::set_param(req.query, "thirdPartyClientId", params.third_party_client_id);
    common::detail::json::set_param(req.query, "dustQuotaAssetToTargetAssetPrice",
                                    params.dust_quota_asset_to_target_asset_price);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DustConvertResponse>
AssetApi::dust_convert(const DustConvertParams& params) const {
    return common::send<DustConvertResponse>(*client_, dust_convert_request(params));
}

common::RestRequest
AssetApi::dust_convertible_assets_request(const DustConvertibleAssetsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/asset/dust-convert/query-convertible-assets";
    common::detail::json::set_param(req.query, "targetAsset", params.target_asset);
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    common::detail::json::set_param(req.query, "dustQuotaAssetToTargetAssetPrice",
                                    params.dust_quota_asset_to_target_asset_price);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DustConvertibleAssetsResponse>
AssetApi::dust_convertible_assets(const DustConvertibleAssetsParams& params) const {
    return common::send<DustConvertibleAssetsResponse>(*client_,
                                                       dust_convertible_assets_request(params));
}

common::RestRequest AssetApi::dust_transfer_request(const DustTransferParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/asset/dust";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DustTransferResponse>
AssetApi::dust_transfer(const DustTransferParams& params) const {
    return common::send<DustTransferResponse>(*client_, dust_transfer_request(params));
}

common::RestRequest AssetApi::dustlog_request(const DustlogParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/asset/dribblet";
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DustlogResponse> AssetApi::dustlog(const DustlogParams& params) const {
    return common::send<DustlogResponse>(*client_, dustlog_request(params));
}

common::RestRequest AssetApi::funding_wallet_request(const FundingWalletParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/asset/get-funding-asset";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "needBtcValuation", params.need_btc_valuation);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<FundingWalletResponseInner>>
AssetApi::funding_wallet(const FundingWalletParams& params) const {
    return common::send<std::vector<FundingWalletResponseInner>>(*client_,
                                                                 funding_wallet_request(params));
}

common::RestRequest AssetApi::get_assets_that_can_be_converted_into_bnb_request(
    const GetAssetsThatCanBeConvertedIntoBnbParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/asset/dust-btc";
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetAssetsThatCanBeConvertedIntoBnbResponse>
AssetApi::get_assets_that_can_be_converted_into_bnb(
    const GetAssetsThatCanBeConvertedIntoBnbParams& params) const {
    return common::send<GetAssetsThatCanBeConvertedIntoBnbResponse>(
        *client_, get_assets_that_can_be_converted_into_bnb_request(params));
}

common::RestRequest AssetApi::get_cloud_mining_payment_and_refund_history_request(
    const GetCloudMiningPaymentAndRefundHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/asset/ledger-transfer/cloud-mining/queryByPage";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "tranId", params.tran_id);
    common::detail::json::set_param(req.query, "clientTranId", params.client_tran_id);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCloudMiningPaymentAndRefundHistoryResponse>
AssetApi::get_cloud_mining_payment_and_refund_history(
    const GetCloudMiningPaymentAndRefundHistoryParams& params) const {
    return common::send<GetCloudMiningPaymentAndRefundHistoryResponse>(
        *client_, get_cloud_mining_payment_and_refund_history_request(params));
}

common::RestRequest AssetApi::get_open_symbol_list_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/spot/open-symbol-list";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetOpenSymbolListResponseInner>>
AssetApi::get_open_symbol_list() const {
    return common::send<std::vector<GetOpenSymbolListResponseInner>>(
        *client_, get_open_symbol_list_request());
}

common::RestRequest
AssetApi::get_spot_asset_tags_request(const GetSpotAssetTagsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/spot/asset/tags";
    common::detail::json::set_param(req.query, "tag", params.tag);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetSpotAssetTagsResponseInner>>
AssetApi::get_spot_asset_tags(const GetSpotAssetTagsParams& params) const {
    return common::send<std::vector<GetSpotAssetTagsResponseInner>>(
        *client_, get_spot_asset_tags_request(params));
}

common::RestRequest AssetApi::query_user_delegation_history_request(
    const QueryUserDelegationHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/asset/custody/transfer-history";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryUserDelegationHistoryResponse>
AssetApi::query_user_delegation_history(const QueryUserDelegationHistoryParams& params) const {
    return common::send<QueryUserDelegationHistoryResponse>(
        *client_, query_user_delegation_history_request(params));
}

common::RestRequest AssetApi::query_user_universal_transfer_history_request(
    const QueryUserUniversalTransferHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/asset/transfer";
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "fromSymbol", params.from_symbol);
    common::detail::json::set_param(req.query, "toSymbol", params.to_symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryUserUniversalTransferHistoryResponse>
AssetApi::query_user_universal_transfer_history(
    const QueryUserUniversalTransferHistoryParams& params) const {
    return common::send<QueryUserUniversalTransferHistoryResponse>(
        *client_, query_user_universal_transfer_history_request(params));
}

common::RestRequest
AssetApi::user_universal_transfer_request(const UserUniversalTransferParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/asset/transfer";
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "fromSymbol", params.from_symbol);
    common::detail::json::set_param(req.query, "toSymbol", params.to_symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<UserUniversalTransferResponse>
AssetApi::user_universal_transfer(const UserUniversalTransferParams& params) const {
    return common::send<UserUniversalTransferResponse>(*client_,
                                                       user_universal_transfer_request(params));
}

common::RestRequest
AssetApi::query_user_wallet_balance_request(const QueryUserWalletBalanceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/asset/wallet/balance";
    common::detail::json::set_param(req.query, "quoteAsset", params.quote_asset);
    common::detail::json::set_param(req.query, "needBalanceDetail", params.need_balance_detail);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryUserWalletBalanceResponseInner>>
AssetApi::query_user_wallet_balance(const QueryUserWalletBalanceParams& params) const {
    return common::send<std::vector<QueryUserWalletBalanceResponseInner>>(
        *client_, query_user_wallet_balance_request(params));
}

common::RestRequest AssetApi::toggle_bnb_burn_on_spot_trade_and_margin_interest_request(
    const ToggleBnbBurnOnSpotTradeAndMarginInterestParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/bnbBurn";
    common::detail::json::set_param(req.query, "spotBNBBurn", params.spot_bnb_burn);
    common::detail::json::set_param(req.query, "interestBNBBurn", params.interest_bnb_burn);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ToggleBnbBurnOnSpotTradeAndMarginInterestResponse>
AssetApi::toggle_bnb_burn_on_spot_trade_and_margin_interest(
    const ToggleBnbBurnOnSpotTradeAndMarginInterestParams& params) const {
    return common::send<ToggleBnbBurnOnSpotTradeAndMarginInterestResponse>(
        *client_, toggle_bnb_burn_on_spot_trade_and_margin_interest_request(params));
}

common::RestRequest AssetApi::trade_fee_request(const TradeFeeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/asset/tradeFee";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<TradeFeeResponseInner>>
AssetApi::trade_fee(const TradeFeeParams& params) const {
    return common::send<std::vector<TradeFeeResponseInner>>(*client_, trade_fee_request(params));
}

common::RestRequest AssetApi::user_asset_request(const UserAssetParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v3/asset/getUserAsset";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "needBtcValuation", params.need_btc_valuation);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<UserAssetResponseInner>>
AssetApi::user_asset(const UserAssetParams& params) const {
    return common::send<std::vector<UserAssetResponseInner>>(*client_, user_asset_request(params));
}

} // namespace binance::wallet::rest_api
