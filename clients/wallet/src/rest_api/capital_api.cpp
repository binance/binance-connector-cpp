//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/capital_api.hpp>

namespace binance::wallet::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(DepositHistoryStatusEnum value) noexcept {
    switch (value) {
    case DepositHistoryStatusEnum::Status0:
        return "0";
    case DepositHistoryStatusEnum::Status1:
        return "1";
    case DepositHistoryStatusEnum::Status2:
        return "2";
    case DepositHistoryStatusEnum::Status6:
        return "6";
    case DepositHistoryStatusEnum::Status7:
        return "7";
    case DepositHistoryStatusEnum::Status8:
        return "8";
    case DepositHistoryStatusEnum::Unknown:
        break;
    }
    return "";
}

DepositHistoryStatusEnum tag_invoke(boost::json::value_to_tag<DepositHistoryStatusEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "0") {
        return DepositHistoryStatusEnum::Status0;
    }
    if (s == "1") {
        return DepositHistoryStatusEnum::Status1;
    }
    if (s == "2") {
        return DepositHistoryStatusEnum::Status2;
    }
    if (s == "6") {
        return DepositHistoryStatusEnum::Status6;
    }
    if (s == "7") {
        return DepositHistoryStatusEnum::Status7;
    }
    if (s == "8") {
        return DepositHistoryStatusEnum::Status8;
    }
    return DepositHistoryStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                DepositHistoryStatusEnum value) {
    if (value == DepositHistoryStatusEnum::Unknown) {
        throw std::invalid_argument("DepositHistoryStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

CapitalApi::CapitalApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
CapitalApi::all_coins_information_request(const AllCoinsInformationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/capital/config/getall";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<AllCoinsInformationResponseInner>>
CapitalApi::all_coins_information(const AllCoinsInformationParams& params) const {
    return common::send<std::vector<AllCoinsInformationResponseInner>>(
        *client_, all_coins_information_request(params));
}

common::RestRequest CapitalApi::deposit_address_request(const DepositAddressParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/capital/deposit/address";
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DepositAddressResponse>
CapitalApi::deposit_address(const DepositAddressParams& params) const {
    return common::send<DepositAddressResponse>(*client_, deposit_address_request(params));
}

common::RestRequest CapitalApi::deposit_history_request(const DepositHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/capital/deposit/hisrec";
    common::detail::json::set_param(req.query, "includeSource", params.include_source);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "status", params.status);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<DepositHistoryResponseInner>>
CapitalApi::deposit_history(const DepositHistoryParams& params) const {
    return common::send<std::vector<DepositHistoryResponseInner>>(*client_,
                                                                  deposit_history_request(params));
}

common::RestRequest CapitalApi::fetch_deposit_address_list_with_network_request(
    const FetchDepositAddressListWithNetworkParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/capital/deposit/address/list";
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "network", params.network);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<FetchDepositAddressListWithNetworkResponseInner>>
CapitalApi::fetch_deposit_address_list_with_network(
    const FetchDepositAddressListWithNetworkParams& params) const {
    return common::send<std::vector<FetchDepositAddressListWithNetworkResponseInner>>(
        *client_, fetch_deposit_address_list_with_network_request(params));
}

common::RestRequest CapitalApi::fetch_withdraw_address_list_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/capital/withdraw/address/list";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<FetchWithdrawAddressListResponseInner>>
CapitalApi::fetch_withdraw_address_list() const {
    return common::send<std::vector<FetchWithdrawAddressListResponseInner>>(
        *client_, fetch_withdraw_address_list_request());
}

common::RestRequest CapitalApi::fetch_withdraw_quota_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/capital/withdraw/quota";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FetchWithdrawQuotaResponse> CapitalApi::fetch_withdraw_quota() const {
    return common::send<FetchWithdrawQuotaResponse>(*client_, fetch_withdraw_quota_request());
}

common::RestRequest CapitalApi::one_click_arrival_deposit_apply_request(
    const OneClickArrivalDepositApplyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/capital/deposit/credit-apply";
    common::detail::json::set_param(req.query, "depositId", params.deposit_id);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    common::detail::json::set_param(req.query, "subAccountId", params.sub_account_id);
    common::detail::json::set_param(req.query, "subUserId", params.sub_user_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OneClickArrivalDepositApplyResponse>
CapitalApi::one_click_arrival_deposit_apply(const OneClickArrivalDepositApplyParams& params) const {
    return common::send<OneClickArrivalDepositApplyResponse>(
        *client_, one_click_arrival_deposit_apply_request(params));
}

common::RestRequest CapitalApi::withdraw_request(const WithdrawParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/capital/withdraw/apply";
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "address", params.address);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "withdrawOrderId", params.withdraw_order_id);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "addressTag", params.address_tag);
    common::detail::json::set_param(req.query, "transactionFeeFlag", params.transaction_fee_flag);
    common::detail::json::set_param(req.query, "name", params.name);
    common::detail::json::set_param(req.query, "walletType", params.wallet_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<WithdrawResponse> CapitalApi::withdraw(const WithdrawParams& params) const {
    return common::send<WithdrawResponse>(*client_, withdraw_request(params));
}

common::RestRequest
CapitalApi::withdraw_history_request(const WithdrawHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/capital/withdraw/history";
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "withdrawOrderId", params.withdraw_order_id);
    common::detail::json::set_param(req.query, "status", params.status);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "idList", params.id_list);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<WithdrawHistoryResponseInner>>
CapitalApi::withdraw_history(const WithdrawHistoryParams& params) const {
    return common::send<std::vector<WithdrawHistoryResponseInner>>(
        *client_, withdraw_history_request(params));
}

} // namespace binance::wallet::rest_api
