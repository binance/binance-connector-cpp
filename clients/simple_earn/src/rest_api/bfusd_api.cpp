//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/bfusd_api.hpp>

namespace binance::simple_earn::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetBfusdSubscriptionHistoryAssetEnum value) noexcept {
    switch (value) {
    case GetBfusdSubscriptionHistoryAssetEnum::Usdc:
        return "USDC";
    case GetBfusdSubscriptionHistoryAssetEnum::Usdt:
        return "USDT";
    case GetBfusdSubscriptionHistoryAssetEnum::Unknown:
        break;
    }
    return "";
}

GetBfusdSubscriptionHistoryAssetEnum
tag_invoke(boost::json::value_to_tag<GetBfusdSubscriptionHistoryAssetEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "USDC") {
        return GetBfusdSubscriptionHistoryAssetEnum::Usdc;
    }
    if (s == "USDT") {
        return GetBfusdSubscriptionHistoryAssetEnum::Usdt;
    }
    return GetBfusdSubscriptionHistoryAssetEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetBfusdSubscriptionHistoryAssetEnum value) {
    if (value == GetBfusdSubscriptionHistoryAssetEnum::Unknown) {
        throw std::invalid_argument("GetBfusdSubscriptionHistoryAssetEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(RedeemBfusdTypeEnum value) noexcept {
    switch (value) {
    case RedeemBfusdTypeEnum::Fast:
        return "FAST";
    case RedeemBfusdTypeEnum::Standard:
        return "STANDARD";
    case RedeemBfusdTypeEnum::Unknown:
        break;
    }
    return "";
}

RedeemBfusdTypeEnum tag_invoke(boost::json::value_to_tag<RedeemBfusdTypeEnum> /*tag*/,
                               const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "FAST") {
        return RedeemBfusdTypeEnum::Fast;
    }
    if (s == "STANDARD") {
        return RedeemBfusdTypeEnum::Standard;
    }
    return RedeemBfusdTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                RedeemBfusdTypeEnum value) {
    if (value == RedeemBfusdTypeEnum::Unknown) {
        throw std::invalid_argument("RedeemBfusdTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

BfusdApi::BfusdApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest BfusdApi::get_bfusd_account_request(const GetBfusdAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/bfusd/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBfusdAccountResponse>
BfusdApi::get_bfusd_account(const GetBfusdAccountParams& params) const {
    return common::send<GetBfusdAccountResponse>(*client_, get_bfusd_account_request(params));
}

common::RestRequest
BfusdApi::get_bfusd_quota_details_request(const GetBfusdQuotaDetailsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/bfusd/quota";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBfusdQuotaDetailsResponse>
BfusdApi::get_bfusd_quota_details(const GetBfusdQuotaDetailsParams& params) const {
    return common::send<GetBfusdQuotaDetailsResponse>(*client_,
                                                      get_bfusd_quota_details_request(params));
}

common::RestRequest
BfusdApi::get_bfusd_rate_history_request(const GetBfusdRateHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/bfusd/history/rateHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBfusdRateHistoryResponse>
BfusdApi::get_bfusd_rate_history(const GetBfusdRateHistoryParams& params) const {
    return common::send<GetBfusdRateHistoryResponse>(*client_,
                                                     get_bfusd_rate_history_request(params));
}

common::RestRequest BfusdApi::get_bfusd_redemption_history_request(
    const GetBfusdRedemptionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/bfusd/history/redemptionHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBfusdRedemptionHistoryResponse>
BfusdApi::get_bfusd_redemption_history(const GetBfusdRedemptionHistoryParams& params) const {
    return common::send<GetBfusdRedemptionHistoryResponse>(
        *client_, get_bfusd_redemption_history_request(params));
}

common::RestRequest
BfusdApi::get_bfusd_rewards_history_request(const GetBfusdRewardsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/bfusd/history/rewardsHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBfusdRewardsHistoryResponse>
BfusdApi::get_bfusd_rewards_history(const GetBfusdRewardsHistoryParams& params) const {
    return common::send<GetBfusdRewardsHistoryResponse>(*client_,
                                                        get_bfusd_rewards_history_request(params));
}

common::RestRequest BfusdApi::get_bfusd_subscription_history_request(
    const GetBfusdSubscriptionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/bfusd/history/subscriptionHistory";
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

common::RestApiResponse<GetBfusdSubscriptionHistoryResponse>
BfusdApi::get_bfusd_subscription_history(const GetBfusdSubscriptionHistoryParams& params) const {
    return common::send<GetBfusdSubscriptionHistoryResponse>(
        *client_, get_bfusd_subscription_history_request(params));
}

common::RestRequest BfusdApi::redeem_bfusd_request(const RedeemBfusdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/bfusd/redeem";
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RedeemBfusdResponse>
BfusdApi::redeem_bfusd(const RedeemBfusdParams& params) const {
    return common::send<RedeemBfusdResponse>(*client_, redeem_bfusd_request(params));
}

common::RestRequest BfusdApi::subscribe_bfusd_request(const SubscribeBfusdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/bfusd/subscribe";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubscribeBfusdResponse>
BfusdApi::subscribe_bfusd(const SubscribeBfusdParams& params) const {
    return common::send<SubscribeBfusdResponse>(*client_, subscribe_bfusd_request(params));
}

} // namespace binance::simple_earn::rest_api
