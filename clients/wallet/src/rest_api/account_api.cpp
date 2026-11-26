//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/account_api.hpp>

namespace binance::wallet::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(DailyAccountSnapshotTypeEnum value) noexcept {
    switch (value) {
    case DailyAccountSnapshotTypeEnum::Spot:
        return "SPOT";
    case DailyAccountSnapshotTypeEnum::Margin:
        return "MARGIN";
    case DailyAccountSnapshotTypeEnum::Futures:
        return "FUTURES";
    case DailyAccountSnapshotTypeEnum::Unknown:
        break;
    }
    return "";
}

DailyAccountSnapshotTypeEnum
tag_invoke(boost::json::value_to_tag<DailyAccountSnapshotTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return DailyAccountSnapshotTypeEnum::Spot;
    }
    if (s == "MARGIN") {
        return DailyAccountSnapshotTypeEnum::Margin;
    }
    if (s == "FUTURES") {
        return DailyAccountSnapshotTypeEnum::Futures;
    }
    return DailyAccountSnapshotTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                DailyAccountSnapshotTypeEnum value) {
    if (value == DailyAccountSnapshotTypeEnum::Unknown) {
        throw std::invalid_argument("DailyAccountSnapshotTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

AccountApi::AccountApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
AccountApi::account_api_trading_status_request(const AccountApiTradingStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/account/apiTradingStatus";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountApiTradingStatusResponse>
AccountApi::account_api_trading_status(const AccountApiTradingStatusParams& params) const {
    return common::send<AccountApiTradingStatusResponse>(
        *client_, account_api_trading_status_request(params));
}

common::RestRequest AccountApi::account_info_request(const AccountInfoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/account/info";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountInfoResponse>
AccountApi::account_info(const AccountInfoParams& params) const {
    return common::send<AccountInfoResponse>(*client_, account_info_request(params));
}

common::RestRequest AccountApi::account_status_request(const AccountStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/account/status";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountStatusResponse>
AccountApi::account_status(const AccountStatusParams& params) const {
    return common::send<AccountStatusResponse>(*client_, account_status_request(params));
}

common::RestRequest
AccountApi::daily_account_snapshot_request(const DailyAccountSnapshotParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/accountSnapshot";
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DailyAccountSnapshotResponse>
AccountApi::daily_account_snapshot(const DailyAccountSnapshotParams& params) const {
    return common::send<DailyAccountSnapshotResponse>(*client_,
                                                      daily_account_snapshot_request(params));
}

common::RestRequest AccountApi::disable_fast_withdraw_switch_request(
    const DisableFastWithdrawSwitchParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/account/disableFastWithdrawSwitch";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<boost::json::value>
AccountApi::disable_fast_withdraw_switch(const DisableFastWithdrawSwitchParams& params) const {
    return common::send<boost::json::value>(*client_, disable_fast_withdraw_switch_request(params));
}

common::RestRequest AccountApi::enable_fast_withdraw_switch_request(
    const EnableFastWithdrawSwitchParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/account/enableFastWithdrawSwitch";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<boost::json::value>
AccountApi::enable_fast_withdraw_switch(const EnableFastWithdrawSwitchParams& params) const {
    return common::send<boost::json::value>(*client_, enable_fast_withdraw_switch_request(params));
}

common::RestRequest
AccountApi::get_api_key_permission_request(const GetApiKeyPermissionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/account/apiRestrictions";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetApiKeyPermissionResponse>
AccountApi::get_api_key_permission(const GetApiKeyPermissionParams& params) const {
    return common::send<GetApiKeyPermissionResponse>(*client_,
                                                     get_api_key_permission_request(params));
}

} // namespace binance::wallet::rest_api
