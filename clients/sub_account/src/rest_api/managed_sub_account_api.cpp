//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/managed_sub_account_api.hpp>

namespace binance::sub_account::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(QueryManagedSubAccountSnapshotTypeEnum value) noexcept {
    switch (value) {
    case QueryManagedSubAccountSnapshotTypeEnum::Spot:
        return "SPOT";
    case QueryManagedSubAccountSnapshotTypeEnum::Margin:
        return "MARGIN";
    case QueryManagedSubAccountSnapshotTypeEnum::Futures:
        return "FUTURES";
    case QueryManagedSubAccountSnapshotTypeEnum::Unknown:
        break;
    }
    return "";
}

QueryManagedSubAccountSnapshotTypeEnum
tag_invoke(boost::json::value_to_tag<QueryManagedSubAccountSnapshotTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return QueryManagedSubAccountSnapshotTypeEnum::Spot;
    }
    if (s == "MARGIN") {
        return QueryManagedSubAccountSnapshotTypeEnum::Margin;
    }
    if (s == "FUTURES") {
        return QueryManagedSubAccountSnapshotTypeEnum::Futures;
    }
    return QueryManagedSubAccountSnapshotTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryManagedSubAccountSnapshotTypeEnum value) {
    if (value == QueryManagedSubAccountSnapshotTypeEnum::Unknown) {
        throw std::invalid_argument(
            "QueryManagedSubAccountSnapshotTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum
              value) noexcept {
    switch (value) {
    case QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
        Spot:
        return "SPOT";
    case QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
        Margin:
        return "MARGIN";
    case QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
        IsolatedMargin:
        return "ISOLATED_MARGIN";
    case QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
        UsdtFuture:
        return "USDT_FUTURE";
    case QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
        CoinFuture:
        return "COIN_FUTURE";
    case QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
        Unknown:
        break;
    }
    return "";
}

QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum tag_invoke(
    boost::json::value_to_tag<
        QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum> /*tag*/
    ,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
            Spot;
    }
    if (s == "MARGIN") {
        return QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
            Margin;
    }
    if (s == "ISOLATED_MARGIN") {
        return QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
            IsolatedMargin;
    }
    if (s == "USDT_FUTURE") {
        return QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
            UsdtFuture;
    }
    if (s == "COIN_FUTURE") {
        return QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
            CoinFuture;
    }
    return QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
        Unknown;
}

void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum value) {
    if (value ==
        QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
            Unknown) {
        throw std::invalid_argument("QueryManagedSubAccountTransferLogMasterAccountInvestorTransfer"
                                    "FunctionAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum
              value) noexcept {
    switch (value) {
    case QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::Spot:
        return "SPOT";
    case QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
        Margin:
        return "MARGIN";
    case QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
        IsolatedMargin:
        return "ISOLATED_MARGIN";
    case QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
        UsdtFuture:
        return "USDT_FUTURE";
    case QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
        CoinFuture:
        return "COIN_FUTURE";
    case QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
        Unknown:
        break;
    }
    return "";
}

QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum tag_invoke(
    boost::json::value_to_tag<
        QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum> /*tag*/
    ,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
            Spot;
    }
    if (s == "MARGIN") {
        return QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
            Margin;
    }
    if (s == "ISOLATED_MARGIN") {
        return QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
            IsolatedMargin;
    }
    if (s == "USDT_FUTURE") {
        return QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
            UsdtFuture;
    }
    if (s == "COIN_FUTURE") {
        return QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
            CoinFuture;
    }
    return QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
        Unknown;
}

void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum value) {
    if (value ==
        QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
            Unknown) {
        throw std::invalid_argument("QueryManagedSubAccountTransferLogMasterAccountTradingTransferF"
                                    "unctionAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum
              value) noexcept {
    switch (value) {
    case QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::Spot:
        return "SPOT";
    case QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::Margin:
        return "MARGIN";
    case QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
        IsolatedMargin:
        return "ISOLATED_MARGIN";
    case QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
        UsdtFuture:
        return "USDT_FUTURE";
    case QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
        CoinFuture:
        return "COIN_FUTURE";
    case QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum tag_invoke(
    boost::json::value_to_tag<
        QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
            Spot;
    }
    if (s == "MARGIN") {
        return QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
            Margin;
    }
    if (s == "ISOLATED_MARGIN") {
        return QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
            IsolatedMargin;
    }
    if (s == "USDT_FUTURE") {
        return QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
            UsdtFuture;
    }
    if (s == "COIN_FUTURE") {
        return QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
            CoinFuture;
    }
    return QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
        Unknown;
}

void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum value) {
    if (value == QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::
                     Unknown) {
        throw std::invalid_argument("QueryManagedSubAccountTransferLogSubAccountTradingTransferFunc"
                                    "tionAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

ManagedSubAccountApi::ManagedSubAccountApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest ManagedSubAccountApi::deposit_assets_into_the_managed_sub_account_request(
    const DepositAssetsIntoTheManagedSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/managed-subaccount/deposit";
    common::detail::json::set_param(req.query, "toEmail", params.to_email);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DepositAssetsIntoTheManagedSubAccountResponse>
ManagedSubAccountApi::deposit_assets_into_the_managed_sub_account(
    const DepositAssetsIntoTheManagedSubAccountParams& params) const {
    return common::send<DepositAssetsIntoTheManagedSubAccountResponse>(
        *client_, deposit_assets_into_the_managed_sub_account_request(params));
}

common::RestRequest ManagedSubAccountApi::get_managed_sub_account_deposit_address_request(
    const GetManagedSubAccountDepositAddressParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/managed-subaccount/deposit/address";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetManagedSubAccountDepositAddressResponse>
ManagedSubAccountApi::get_managed_sub_account_deposit_address(
    const GetManagedSubAccountDepositAddressParams& params) const {
    return common::send<GetManagedSubAccountDepositAddressResponse>(
        *client_, get_managed_sub_account_deposit_address_request(params));
}

common::RestRequest ManagedSubAccountApi::query_managed_sub_account_asset_details_request(
    const QueryManagedSubAccountAssetDetailsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/managed-subaccount/asset";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryManagedSubAccountAssetDetailsResponseInner>>
ManagedSubAccountApi::query_managed_sub_account_asset_details(
    const QueryManagedSubAccountAssetDetailsParams& params) const {
    return common::send<std::vector<QueryManagedSubAccountAssetDetailsResponseInner>>(
        *client_, query_managed_sub_account_asset_details_request(params));
}

common::RestRequest ManagedSubAccountApi::query_managed_sub_account_futures_asset_details_request(
    const QueryManagedSubAccountFuturesAssetDetailsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/managed-subaccount/fetch-future-asset";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryManagedSubAccountFuturesAssetDetailsResponse>
ManagedSubAccountApi::query_managed_sub_account_futures_asset_details(
    const QueryManagedSubAccountFuturesAssetDetailsParams& params) const {
    return common::send<QueryManagedSubAccountFuturesAssetDetailsResponse>(
        *client_, query_managed_sub_account_futures_asset_details_request(params));
}

common::RestRequest ManagedSubAccountApi::query_managed_sub_account_list_request(
    const QueryManagedSubAccountListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/managed-subaccount/info";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryManagedSubAccountListResponse>
ManagedSubAccountApi::query_managed_sub_account_list(
    const QueryManagedSubAccountListParams& params) const {
    return common::send<QueryManagedSubAccountListResponse>(
        *client_, query_managed_sub_account_list_request(params));
}

common::RestRequest ManagedSubAccountApi::query_managed_sub_account_margin_asset_details_request(
    const QueryManagedSubAccountMarginAssetDetailsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/managed-subaccount/marginAsset";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryManagedSubAccountMarginAssetDetailsResponse>
ManagedSubAccountApi::query_managed_sub_account_margin_asset_details(
    const QueryManagedSubAccountMarginAssetDetailsParams& params) const {
    return common::send<QueryManagedSubAccountMarginAssetDetailsResponse>(
        *client_, query_managed_sub_account_margin_asset_details_request(params));
}

common::RestRequest ManagedSubAccountApi::query_managed_sub_account_snapshot_request(
    const QueryManagedSubAccountSnapshotParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/managed-subaccount/accountSnapshot";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryManagedSubAccountSnapshotResponse>
ManagedSubAccountApi::query_managed_sub_account_snapshot(
    const QueryManagedSubAccountSnapshotParams& params) const {
    return common::send<QueryManagedSubAccountSnapshotResponse>(
        *client_, query_managed_sub_account_snapshot_request(params));
}

common::RestRequest
ManagedSubAccountApi::query_managed_sub_account_transfer_log_master_account_investor_request(
    const QueryManagedSubAccountTransferLogMasterAccountInvestorParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/managed-subaccount/queryTransLogForInvestor";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "transfers", params.transfers);
    common::detail::json::set_param(req.query, "transferFunctionAccountType",
                                    params.transfer_function_account_type);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryManagedSubAccountTransferLogMasterAccountInvestorResponse>
ManagedSubAccountApi::query_managed_sub_account_transfer_log_master_account_investor(
    const QueryManagedSubAccountTransferLogMasterAccountInvestorParams& params) const {
    return common::send<QueryManagedSubAccountTransferLogMasterAccountInvestorResponse>(
        *client_, query_managed_sub_account_transfer_log_master_account_investor_request(params));
}

common::RestRequest
ManagedSubAccountApi::query_managed_sub_account_transfer_log_master_account_trading_request(
    const QueryManagedSubAccountTransferLogMasterAccountTradingParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/managed-subaccount/queryTransLogForTradeParent";
    common::detail::json::set_param(req.query, "email", params.email);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "transfers", params.transfers);
    common::detail::json::set_param(req.query, "transferFunctionAccountType",
                                    params.transfer_function_account_type);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryManagedSubAccountTransferLogMasterAccountTradingResponse>
ManagedSubAccountApi::query_managed_sub_account_transfer_log_master_account_trading(
    const QueryManagedSubAccountTransferLogMasterAccountTradingParams& params) const {
    return common::send<QueryManagedSubAccountTransferLogMasterAccountTradingResponse>(
        *client_, query_managed_sub_account_transfer_log_master_account_trading_request(params));
}

common::RestRequest
ManagedSubAccountApi::query_managed_sub_account_transfer_log_sub_account_trading_request(
    const QueryManagedSubAccountTransferLogSubAccountTradingParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/managed-subaccount/query-trans-log";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "transfers", params.transfers);
    common::detail::json::set_param(req.query, "transferFunctionAccountType",
                                    params.transfer_function_account_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryManagedSubAccountTransferLogSubAccountTradingResponse>
ManagedSubAccountApi::query_managed_sub_account_transfer_log_sub_account_trading(
    const QueryManagedSubAccountTransferLogSubAccountTradingParams& params) const {
    return common::send<QueryManagedSubAccountTransferLogSubAccountTradingResponse>(
        *client_, query_managed_sub_account_transfer_log_sub_account_trading_request(params));
}

common::RestRequest ManagedSubAccountApi::withdrawl_assets_from_the_managed_sub_account_request(
    const WithdrawlAssetsFromTheManagedSubAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/managed-subaccount/withdraw";
    common::detail::json::set_param(req.query, "fromEmail", params.from_email);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "transferDate", params.transfer_date);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<WithdrawlAssetsFromTheManagedSubAccountResponse>
ManagedSubAccountApi::withdrawl_assets_from_the_managed_sub_account(
    const WithdrawlAssetsFromTheManagedSubAccountParams& params) const {
    return common::send<WithdrawlAssetsFromTheManagedSubAccountResponse>(
        *client_, withdrawl_assets_from_the_managed_sub_account_request(params));
}

} // namespace binance::sub_account::rest_api
