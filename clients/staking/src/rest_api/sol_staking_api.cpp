//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/sol_staking_api.hpp>

namespace binance::staking::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetBoostRewardsHistoryTypeEnum value) noexcept {
    switch (value) {
    case GetBoostRewardsHistoryTypeEnum::Claim:
        return "CLAIM";
    case GetBoostRewardsHistoryTypeEnum::Distribute:
        return "DISTRIBUTE";
    case GetBoostRewardsHistoryTypeEnum::Unknown:
        break;
    }
    return "";
}

GetBoostRewardsHistoryTypeEnum
tag_invoke(boost::json::value_to_tag<GetBoostRewardsHistoryTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "CLAIM") {
        return GetBoostRewardsHistoryTypeEnum::Claim;
    }
    if (s == "DISTRIBUTE") {
        return GetBoostRewardsHistoryTypeEnum::Distribute;
    }
    return GetBoostRewardsHistoryTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetBoostRewardsHistoryTypeEnum value) {
    if (value == GetBoostRewardsHistoryTypeEnum::Unknown) {
        throw std::invalid_argument("GetBoostRewardsHistoryTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

SolStakingApi::SolStakingApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
SolStakingApi::claim_boost_rewards_request(const ClaimBoostRewardsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sol-staking/sol/claim";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ClaimBoostRewardsResponse>
SolStakingApi::claim_boost_rewards(const ClaimBoostRewardsParams& params) const {
    return common::send<ClaimBoostRewardsResponse>(*client_, claim_boost_rewards_request(params));
}

common::RestRequest
SolStakingApi::get_bnsol_rate_history_request(const GetBnsolRateHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sol-staking/sol/history/rateHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBnsolRateHistoryResponse>
SolStakingApi::get_bnsol_rate_history(const GetBnsolRateHistoryParams& params) const {
    return common::send<GetBnsolRateHistoryResponse>(*client_,
                                                     get_bnsol_rate_history_request(params));
}

common::RestRequest
SolStakingApi::get_bnsol_rewards_history_request(const GetBnsolRewardsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sol-staking/sol/history/bnsolRewardsHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBnsolRewardsHistoryResponse>
SolStakingApi::get_bnsol_rewards_history(const GetBnsolRewardsHistoryParams& params) const {
    return common::send<GetBnsolRewardsHistoryResponse>(*client_,
                                                        get_bnsol_rewards_history_request(params));
}

common::RestRequest
SolStakingApi::get_boost_rewards_history_request(const GetBoostRewardsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sol-staking/sol/history/boostRewardsHistory";
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBoostRewardsHistoryResponse>
SolStakingApi::get_boost_rewards_history(const GetBoostRewardsHistoryParams& params) const {
    return common::send<GetBoostRewardsHistoryResponse>(*client_,
                                                        get_boost_rewards_history_request(params));
}

common::RestRequest SolStakingApi::get_sol_redemption_history_request(
    const GetSolRedemptionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sol-staking/sol/history/redemptionHistory";
    common::detail::json::set_param(req.query, "redeemId", params.redeem_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSolRedemptionHistoryResponse>
SolStakingApi::get_sol_redemption_history(const GetSolRedemptionHistoryParams& params) const {
    return common::send<GetSolRedemptionHistoryResponse>(
        *client_, get_sol_redemption_history_request(params));
}

common::RestRequest
SolStakingApi::get_sol_staking_history_request(const GetSolStakingHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sol-staking/sol/history/stakingHistory";
    common::detail::json::set_param(req.query, "purchaseId", params.purchase_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSolStakingHistoryResponse>
SolStakingApi::get_sol_staking_history(const GetSolStakingHistoryParams& params) const {
    return common::send<GetSolStakingHistoryResponse>(*client_,
                                                      get_sol_staking_history_request(params));
}

common::RestRequest SolStakingApi::get_sol_staking_quota_details_request(
    const GetSolStakingQuotaDetailsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sol-staking/sol/quota";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSolStakingQuotaDetailsResponse>
SolStakingApi::get_sol_staking_quota_details(const GetSolStakingQuotaDetailsParams& params) const {
    return common::send<GetSolStakingQuotaDetailsResponse>(
        *client_, get_sol_staking_quota_details_request(params));
}

common::RestRequest
SolStakingApi::get_unclaimed_rewards_request(const GetUnclaimedRewardsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sol-staking/sol/history/unclaimedRewards";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetUnclaimedRewardsResponseInner>>
SolStakingApi::get_unclaimed_rewards(const GetUnclaimedRewardsParams& params) const {
    return common::send<std::vector<GetUnclaimedRewardsResponseInner>>(
        *client_, get_unclaimed_rewards_request(params));
}

common::RestRequest SolStakingApi::redeem_sol_request(const RedeemSolParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sol-staking/sol/redeem";
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RedeemSolResponse>
SolStakingApi::redeem_sol(const RedeemSolParams& params) const {
    return common::send<RedeemSolResponse>(*client_, redeem_sol_request(params));
}

common::RestRequest
SolStakingApi::sol_staking_account_request(const SolStakingAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/sol-staking/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SolStakingAccountResponse>
SolStakingApi::sol_staking_account(const SolStakingAccountParams& params) const {
    return common::send<SolStakingAccountResponse>(*client_, sol_staking_account_request(params));
}

common::RestRequest
SolStakingApi::subscribe_sol_staking_request(const SubscribeSolStakingParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/sol-staking/sol/stake";
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubscribeSolStakingResponse>
SolStakingApi::subscribe_sol_staking(const SubscribeSolStakingParams& params) const {
    return common::send<SubscribeSolStakingResponse>(*client_,
                                                     subscribe_sol_staking_request(params));
}

} // namespace binance::staking::rest_api
