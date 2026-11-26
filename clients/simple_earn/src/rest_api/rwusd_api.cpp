//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/rwusd_api.hpp>

namespace binance::simple_earn::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetRwusdSubscriptionHistoryAssetEnum value) noexcept {
    switch (value) {
    case GetRwusdSubscriptionHistoryAssetEnum::Usdc:
        return "USDC";
    case GetRwusdSubscriptionHistoryAssetEnum::Usdt:
        return "USDT";
    case GetRwusdSubscriptionHistoryAssetEnum::Unknown:
        break;
    }
    return "";
}

GetRwusdSubscriptionHistoryAssetEnum
tag_invoke(boost::json::value_to_tag<GetRwusdSubscriptionHistoryAssetEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "USDC") {
        return GetRwusdSubscriptionHistoryAssetEnum::Usdc;
    }
    if (s == "USDT") {
        return GetRwusdSubscriptionHistoryAssetEnum::Usdt;
    }
    return GetRwusdSubscriptionHistoryAssetEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetRwusdSubscriptionHistoryAssetEnum value) {
    if (value == GetRwusdSubscriptionHistoryAssetEnum::Unknown) {
        throw std::invalid_argument("GetRwusdSubscriptionHistoryAssetEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(RedeemRwusdTypeEnum value) noexcept {
    switch (value) {
    case RedeemRwusdTypeEnum::Fast:
        return "FAST";
    case RedeemRwusdTypeEnum::Standard:
        return "STANDARD";
    case RedeemRwusdTypeEnum::Unknown:
        break;
    }
    return "";
}

RedeemRwusdTypeEnum tag_invoke(boost::json::value_to_tag<RedeemRwusdTypeEnum> /*tag*/,
                               const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "FAST") {
        return RedeemRwusdTypeEnum::Fast;
    }
    if (s == "STANDARD") {
        return RedeemRwusdTypeEnum::Standard;
    }
    return RedeemRwusdTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                RedeemRwusdTypeEnum value) {
    if (value == RedeemRwusdTypeEnum::Unknown) {
        throw std::invalid_argument("RedeemRwusdTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SubscribeRwusdAssetEnum value) noexcept {
    switch (value) {
    case SubscribeRwusdAssetEnum::Usdt:
        return "USDT";
    case SubscribeRwusdAssetEnum::Usdc:
        return "USDC";
    case SubscribeRwusdAssetEnum::Unknown:
        break;
    }
    return "";
}

SubscribeRwusdAssetEnum tag_invoke(boost::json::value_to_tag<SubscribeRwusdAssetEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "USDT") {
        return SubscribeRwusdAssetEnum::Usdt;
    }
    if (s == "USDC") {
        return SubscribeRwusdAssetEnum::Usdc;
    }
    return SubscribeRwusdAssetEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SubscribeRwusdAssetEnum value) {
    if (value == SubscribeRwusdAssetEnum::Unknown) {
        throw std::invalid_argument("SubscribeRwusdAssetEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

RwusdApi::RwusdApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest RwusdApi::get_rwusd_account_request(const GetRwusdAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/rwusd/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetRwusdAccountResponse>
RwusdApi::get_rwusd_account(const GetRwusdAccountParams& params) const {
    return common::send<GetRwusdAccountResponse>(*client_, get_rwusd_account_request(params));
}

common::RestRequest
RwusdApi::get_rwusd_quota_details_request(const GetRwusdQuotaDetailsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/rwusd/quota";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetRwusdQuotaDetailsResponse>
RwusdApi::get_rwusd_quota_details(const GetRwusdQuotaDetailsParams& params) const {
    return common::send<GetRwusdQuotaDetailsResponse>(*client_,
                                                      get_rwusd_quota_details_request(params));
}

common::RestRequest
RwusdApi::get_rwusd_rate_history_request(const GetRwusdRateHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/rwusd/history/rateHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetRwusdRateHistoryResponse>
RwusdApi::get_rwusd_rate_history(const GetRwusdRateHistoryParams& params) const {
    return common::send<GetRwusdRateHistoryResponse>(*client_,
                                                     get_rwusd_rate_history_request(params));
}

common::RestRequest RwusdApi::get_rwusd_redemption_history_request(
    const GetRwusdRedemptionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/rwusd/history/redemptionHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetRwusdRedemptionHistoryResponse>
RwusdApi::get_rwusd_redemption_history(const GetRwusdRedemptionHistoryParams& params) const {
    return common::send<GetRwusdRedemptionHistoryResponse>(
        *client_, get_rwusd_redemption_history_request(params));
}

common::RestRequest
RwusdApi::get_rwusd_rewards_history_request(const GetRwusdRewardsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/rwusd/history/rewardsHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetRwusdRewardsHistoryResponse>
RwusdApi::get_rwusd_rewards_history(const GetRwusdRewardsHistoryParams& params) const {
    return common::send<GetRwusdRewardsHistoryResponse>(*client_,
                                                        get_rwusd_rewards_history_request(params));
}

common::RestRequest RwusdApi::get_rwusd_subscription_history_request(
    const GetRwusdSubscriptionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/rwusd/history/subscriptionHistory";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetRwusdSubscriptionHistoryResponse>
RwusdApi::get_rwusd_subscription_history(const GetRwusdSubscriptionHistoryParams& params) const {
    return common::send<GetRwusdSubscriptionHistoryResponse>(
        *client_, get_rwusd_subscription_history_request(params));
}

common::RestRequest RwusdApi::redeem_rwusd_request(const RedeemRwusdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/rwusd/redeem";
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RedeemRwusdResponse>
RwusdApi::redeem_rwusd(const RedeemRwusdParams& params) const {
    return common::send<RedeemRwusdResponse>(*client_, redeem_rwusd_request(params));
}

common::RestRequest RwusdApi::subscribe_rwusd_request(const SubscribeRwusdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/rwusd/subscribe";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubscribeRwusdResponse>
RwusdApi::subscribe_rwusd(const SubscribeRwusdParams& params) const {
    return common::send<SubscribeRwusdResponse>(*client_, subscribe_rwusd_request(params));
}

} // namespace binance::simple_earn::rest_api
