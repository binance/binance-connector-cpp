//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/asset_management_api.hpp>

namespace binance::sub_account::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetMovePositionHistoryForSubAccountProductTypeEnum value) noexcept {
    switch (value) {
    case GetMovePositionHistoryForSubAccountProductTypeEnum::Um:
        return "UM";
    case GetMovePositionHistoryForSubAccountProductTypeEnum::Option:
        return "OPTION";
    case GetMovePositionHistoryForSubAccountProductTypeEnum::Unknown:
        break;
    }
    return "";
}

GetMovePositionHistoryForSubAccountProductTypeEnum
tag_invoke(boost::json::value_to_tag<GetMovePositionHistoryForSubAccountProductTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "UM") {
        return GetMovePositionHistoryForSubAccountProductTypeEnum::Um;
    }
    if (s == "OPTION") {
        return GetMovePositionHistoryForSubAccountProductTypeEnum::Option;
    }
    return GetMovePositionHistoryForSubAccountProductTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetMovePositionHistoryForSubAccountProductTypeEnum value) {
    if (value == GetMovePositionHistoryForSubAccountProductTypeEnum::Unknown) {
        throw std::invalid_argument(
            "GetMovePositionHistoryForSubAccountProductTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MovePositionForSubAccountProductTypeEnum value) noexcept {
    switch (value) {
    case MovePositionForSubAccountProductTypeEnum::Um:
        return "UM";
    case MovePositionForSubAccountProductTypeEnum::Option:
        return "OPTION";
    case MovePositionForSubAccountProductTypeEnum::Unknown:
        break;
    }
    return "";
}

MovePositionForSubAccountProductTypeEnum
tag_invoke(boost::json::value_to_tag<MovePositionForSubAccountProductTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "UM") {
        return MovePositionForSubAccountProductTypeEnum::Um;
    }
    if (s == "OPTION") {
        return MovePositionForSubAccountProductTypeEnum::Option;
    }
    return MovePositionForSubAccountProductTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MovePositionForSubAccountProductTypeEnum value) {
    if (value == MovePositionForSubAccountProductTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MovePositionForSubAccountProductTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(UniversalTransferFromAccountTypeEnum value) noexcept {
    switch (value) {
    case UniversalTransferFromAccountTypeEnum::Spot:
        return "SPOT";
    case UniversalTransferFromAccountTypeEnum::UsdtFuture:
        return "USDT_FUTURE";
    case UniversalTransferFromAccountTypeEnum::CoinFuture:
        return "COIN_FUTURE";
    case UniversalTransferFromAccountTypeEnum::Margin:
        return "MARGIN";
    case UniversalTransferFromAccountTypeEnum::IsolatedMargin:
        return "ISOLATED_MARGIN";
    case UniversalTransferFromAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

UniversalTransferFromAccountTypeEnum
tag_invoke(boost::json::value_to_tag<UniversalTransferFromAccountTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return UniversalTransferFromAccountTypeEnum::Spot;
    }
    if (s == "USDT_FUTURE") {
        return UniversalTransferFromAccountTypeEnum::UsdtFuture;
    }
    if (s == "COIN_FUTURE") {
        return UniversalTransferFromAccountTypeEnum::CoinFuture;
    }
    if (s == "MARGIN") {
        return UniversalTransferFromAccountTypeEnum::Margin;
    }
    if (s == "ISOLATED_MARGIN") {
        return UniversalTransferFromAccountTypeEnum::IsolatedMargin;
    }
    return UniversalTransferFromAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                UniversalTransferFromAccountTypeEnum value) {
    if (value == UniversalTransferFromAccountTypeEnum::Unknown) {
        throw std::invalid_argument("UniversalTransferFromAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(UniversalTransferToAccountTypeEnum value) noexcept {
    switch (value) {
    case UniversalTransferToAccountTypeEnum::Spot:
        return "SPOT";
    case UniversalTransferToAccountTypeEnum::UsdtFuture:
        return "USDT_FUTURE";
    case UniversalTransferToAccountTypeEnum::CoinFuture:
        return "COIN_FUTURE";
    case UniversalTransferToAccountTypeEnum::Margin:
        return "MARGIN";
    case UniversalTransferToAccountTypeEnum::IsolatedMargin:
        return "ISOLATED_MARGIN";
    case UniversalTransferToAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

UniversalTransferToAccountTypeEnum
tag_invoke(boost::json::value_to_tag<UniversalTransferToAccountTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return UniversalTransferToAccountTypeEnum::Spot;
    }
    if (s == "USDT_FUTURE") {
        return UniversalTransferToAccountTypeEnum::UsdtFuture;
    }
    if (s == "COIN_FUTURE") {
        return UniversalTransferToAccountTypeEnum::CoinFuture;
    }
    if (s == "MARGIN") {
        return UniversalTransferToAccountTypeEnum::Margin;
    }
    if (s == "ISOLATED_MARGIN") {
        return UniversalTransferToAccountTypeEnum::IsolatedMargin;
    }
    return UniversalTransferToAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                UniversalTransferToAccountTypeEnum value) {
    if (value == UniversalTransferToAccountTypeEnum::Unknown) {
        throw std::invalid_argument("UniversalTransferToAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

AssetManagementApi::AssetManagementApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest AssetManagementApi::futures_transfer_for_sub_account_request(
    const FuturesTransferForSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/futures/transfer";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FuturesTransferForSubAccountResponse>
AssetManagementApi::futures_transfer_for_sub_account(
    const FuturesTransferForSubAccountParams& params) const {
    return common::send<FuturesTransferForSubAccountResponse>(
        *client_, futures_transfer_for_sub_account_request(params));
}

common::RestRequest AssetManagementApi::get_detail_on_sub_accounts_futures_account_request(
    const GetDetailOnSubAccountsFuturesAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/futures/account";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDetailOnSubAccountsFuturesAccountResponse>
AssetManagementApi::get_detail_on_sub_accounts_futures_account(
    const GetDetailOnSubAccountsFuturesAccountParams& params) const {
    return common::send<GetDetailOnSubAccountsFuturesAccountResponse>(
        *client_, get_detail_on_sub_accounts_futures_account_request(params));
}

common::RestRequest AssetManagementApi::get_detail_on_sub_accounts_futures_account_v2_request(
    const GetDetailOnSubAccountsFuturesAccountV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/sub-account/futures/account";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "futuresType", params.futures_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDetailOnSubAccountsFuturesAccountV2Response>
AssetManagementApi::get_detail_on_sub_accounts_futures_account_v2(
    const GetDetailOnSubAccountsFuturesAccountV2Params& params) const {
    return common::send<GetDetailOnSubAccountsFuturesAccountV2Response>(
        *client_, get_detail_on_sub_accounts_futures_account_v2_request(params));
}

common::RestRequest AssetManagementApi::get_detail_on_sub_accounts_margin_account_request(
    const GetDetailOnSubAccountsMarginAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/margin/account";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDetailOnSubAccountsMarginAccountResponse>
AssetManagementApi::get_detail_on_sub_accounts_margin_account(
    const GetDetailOnSubAccountsMarginAccountParams& params) const {
    return common::send<GetDetailOnSubAccountsMarginAccountResponse>(
        *client_, get_detail_on_sub_accounts_margin_account_request(params));
}

common::RestRequest AssetManagementApi::get_move_position_history_for_sub_account_request(
    const GetMovePositionHistoryForSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/futures/move-position";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "rows", params.rows);
    common::detail::json::set_param(req.query, "productType", params.product_type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetMovePositionHistoryForSubAccountResponse>
AssetManagementApi::get_move_position_history_for_sub_account(
    const GetMovePositionHistoryForSubAccountParams& params) const {
    return common::send<GetMovePositionHistoryForSubAccountResponse>(
        *client_, get_move_position_history_for_sub_account_request(params));
}

common::RestRequest AssetManagementApi::move_position_for_sub_account_request(
    const MovePositionForSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/futures/move-position";
    common::detail::json::set_param(req.query, "fromUserEmail", params.from_user_email);
    common::detail::json::set_param(req.query, "toUserEmail", params.to_user_email);
    common::detail::json::set_param(req.query, "productType", params.product_type);
    common::detail::json::set_param(req.query, "orderArgs", params.order_args);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MovePositionForSubAccountResponse>
AssetManagementApi::move_position_for_sub_account(
    const MovePositionForSubAccountParams& params) const {
    return common::send<MovePositionForSubAccountResponse>(
        *client_, move_position_for_sub_account_request(params));
}

common::RestRequest AssetManagementApi::get_sub_account_deposit_address_request(
    const GetSubAccountDepositAddressParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/capital/deposit/subAddress";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSubAccountDepositAddressResponse>
AssetManagementApi::get_sub_account_deposit_address(
    const GetSubAccountDepositAddressParams& params) const {
    return common::send<GetSubAccountDepositAddressResponse>(
        *client_, get_sub_account_deposit_address_request(params));
}

common::RestRequest AssetManagementApi::get_sub_account_deposit_history_request(
    const GetSubAccountDepositHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/capital/deposit/subHisrec";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "includeSource", params.include_source);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "status", params.status);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetSubAccountDepositHistoryResponseInner>>
AssetManagementApi::get_sub_account_deposit_history(
    const GetSubAccountDepositHistoryParams& params) const {
    return common::send<std::vector<GetSubAccountDepositHistoryResponseInner>>(
        *client_, get_sub_account_deposit_history_request(params));
}

common::RestRequest AssetManagementApi::get_summary_of_sub_accounts_futures_account_request(
    const GetSummaryOfSubAccountsFuturesAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/futures/accountSummary";
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSummaryOfSubAccountsFuturesAccountResponse>
AssetManagementApi::get_summary_of_sub_accounts_futures_account(
    const GetSummaryOfSubAccountsFuturesAccountParams& params) const {
    return common::send<GetSummaryOfSubAccountsFuturesAccountResponse>(
        *client_, get_summary_of_sub_accounts_futures_account_request(params));
}

common::RestRequest AssetManagementApi::get_summary_of_sub_accounts_futures_account_v2_request(
    const GetSummaryOfSubAccountsFuturesAccountV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/sub-account/futures/accountSummary";
    common::detail::json::set_param(req.query, "futuresType", params.futures_type);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSummaryOfSubAccountsFuturesAccountV2Response>
AssetManagementApi::get_summary_of_sub_accounts_futures_account_v2(
    const GetSummaryOfSubAccountsFuturesAccountV2Params& params) const {
    return common::send<GetSummaryOfSubAccountsFuturesAccountV2Response>(
        *client_, get_summary_of_sub_accounts_futures_account_v2_request(params));
}

common::RestRequest AssetManagementApi::get_summary_of_sub_accounts_margin_account_request(
    const GetSummaryOfSubAccountsMarginAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/margin/accountSummary";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSummaryOfSubAccountsMarginAccountResponse>
AssetManagementApi::get_summary_of_sub_accounts_margin_account(
    const GetSummaryOfSubAccountsMarginAccountParams& params) const {
    return common::send<GetSummaryOfSubAccountsMarginAccountResponse>(
        *client_, get_summary_of_sub_accounts_margin_account_request(params));
}

common::RestRequest AssetManagementApi::margin_transfer_for_sub_account_request(
    const MarginTransferForSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/margin/transfer";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginTransferForSubAccountResponse>
AssetManagementApi::margin_transfer_for_sub_account(
    const MarginTransferForSubAccountParams& params) const {
    return common::send<MarginTransferForSubAccountResponse>(
        *client_, margin_transfer_for_sub_account_request(params));
}

common::RestRequest AssetManagementApi::query_sub_account_assets_request(
    const QuerySubAccountAssetsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v3/sub-account/assets";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySubAccountAssetsResponse>
AssetManagementApi::query_sub_account_assets(const QuerySubAccountAssetsParams& params) const {
    return common::send<QuerySubAccountAssetsResponse>(*client_,
                                                       query_sub_account_assets_request(params));
}

common::RestRequest AssetManagementApi::query_sub_account_assets_asset_management_request(
    const QuerySubAccountAssetsAssetManagementParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v4/sub-account/assets";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySubAccountAssetsAssetManagementResponse>
AssetManagementApi::query_sub_account_assets_asset_management(
    const QuerySubAccountAssetsAssetManagementParams& params) const {
    return common::send<QuerySubAccountAssetsAssetManagementResponse>(
        *client_, query_sub_account_assets_asset_management_request(params));
}

common::RestRequest AssetManagementApi::query_sub_account_futures_asset_transfer_history_request(
    const QuerySubAccountFuturesAssetTransferHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/futures/internalTransfer";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "futuresType", params.futures_type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySubAccountFuturesAssetTransferHistoryResponse>
AssetManagementApi::query_sub_account_futures_asset_transfer_history(
    const QuerySubAccountFuturesAssetTransferHistoryParams& params) const {
    return common::send<QuerySubAccountFuturesAssetTransferHistoryResponse>(
        *client_, query_sub_account_futures_asset_transfer_history_request(params));
}

common::RestRequest AssetManagementApi::sub_account_futures_asset_transfer_request(
    const SubAccountFuturesAssetTransferParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/futures/internalTransfer";
    common::detail::json::set_param(req.query, "fromEmail", params.from_email);
    common::detail::json::set_param(req.query, "toEmail", params.to_email);
    common::detail::json::set_param(req.query, "futuresType", params.futures_type);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubAccountFuturesAssetTransferResponse>
AssetManagementApi::sub_account_futures_asset_transfer(
    const SubAccountFuturesAssetTransferParams& params) const {
    return common::send<SubAccountFuturesAssetTransferResponse>(
        *client_, sub_account_futures_asset_transfer_request(params));
}

common::RestRequest AssetManagementApi::query_sub_account_spot_asset_transfer_history_request(
    const QuerySubAccountSpotAssetTransferHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/sub/transfer/history";
    common::detail::json::set_param(req.query, "fromEmail", params.from_email);
    common::detail::json::set_param(req.query, "toEmail", params.to_email);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QuerySubAccountSpotAssetTransferHistoryResponseInner>>
AssetManagementApi::query_sub_account_spot_asset_transfer_history(
    const QuerySubAccountSpotAssetTransferHistoryParams& params) const {
    return common::send<std::vector<QuerySubAccountSpotAssetTransferHistoryResponseInner>>(
        *client_, query_sub_account_spot_asset_transfer_history_request(params));
}

common::RestRequest AssetManagementApi::query_sub_account_spot_assets_summary_request(
    const QuerySubAccountSpotAssetsSummaryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/spotSummary";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySubAccountSpotAssetsSummaryResponse>
AssetManagementApi::query_sub_account_spot_assets_summary(
    const QuerySubAccountSpotAssetsSummaryParams& params) const {
    return common::send<QuerySubAccountSpotAssetsSummaryResponse>(
        *client_, query_sub_account_spot_assets_summary_request(params));
}

common::RestRequest AssetManagementApi::query_universal_transfer_history_request(
    const QueryUniversalTransferHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/universalTransfer";
    common::detail::json::set_param(req.query, "fromEmail", params.from_email);
    common::detail::json::set_param(req.query, "toEmail", params.to_email);
    common::detail::json::set_param(req.query, "clientTranId", params.client_tran_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryUniversalTransferHistoryResponse>
AssetManagementApi::query_universal_transfer_history(
    const QueryUniversalTransferHistoryParams& params) const {
    return common::send<QueryUniversalTransferHistoryResponse>(
        *client_, query_universal_transfer_history_request(params));
}

common::RestRequest
AssetManagementApi::universal_transfer_request(const UniversalTransferParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/universalTransfer";
    common::detail::json::set_param(req.query, "fromAccountType", params.from_account_type);
    common::detail::json::set_param(req.query, "toAccountType", params.to_account_type);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "fromEmail", params.from_email);
    common::detail::json::set_param(req.query, "toEmail", params.to_email);
    common::detail::json::set_param(req.query, "clientTranId", params.client_tran_id);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<UniversalTransferResponse>
AssetManagementApi::universal_transfer(const UniversalTransferParams& params) const {
    return common::send<UniversalTransferResponse>(*client_, universal_transfer_request(params));
}

common::RestRequest AssetManagementApi::sub_account_transfer_history_request(
    const SubAccountTransferHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sub-account/transfer/subUserHistory";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "returnFailHistory", params.return_fail_history);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<SubAccountTransferHistoryResponseInner>>
AssetManagementApi::sub_account_transfer_history(
    const SubAccountTransferHistoryParams& params) const {
    return common::send<std::vector<SubAccountTransferHistoryResponseInner>>(
        *client_, sub_account_transfer_history_request(params));
}

common::RestRequest
AssetManagementApi::transfer_to_master_request(const TransferToMasterParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/transfer/subToMaster";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TransferToMasterResponse>
AssetManagementApi::transfer_to_master(const TransferToMasterParams& params) const {
    return common::send<TransferToMasterResponse>(*client_, transfer_to_master_request(params));
}

common::RestRequest AssetManagementApi::transfer_to_sub_account_of_same_master_request(
    const TransferToSubAccountOfSameMasterParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sub-account/transfer/subToSub";
    common::detail::json::set_param(req.query, "toEmail", params.to_email);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TransferToSubAccountOfSameMasterResponse>
AssetManagementApi::transfer_to_sub_account_of_same_master(
    const TransferToSubAccountOfSameMasterParams& params) const {
    return common::send<TransferToSubAccountOfSameMasterResponse>(
        *client_, transfer_to_sub_account_of_same_master_request(params));
}

} // namespace binance::sub_account::rest_api
