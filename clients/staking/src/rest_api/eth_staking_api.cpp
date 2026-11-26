//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/eth_staking_api.hpp>

namespace binance::staking::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(RedeemEthAssetEnum value) noexcept {
    switch (value) {
    case RedeemEthAssetEnum::Wbeth:
        return "WBETH";
    case RedeemEthAssetEnum::Beth:
        return "BETH";
    case RedeemEthAssetEnum::Unknown:
        break;
    }
    return "";
}

RedeemEthAssetEnum tag_invoke(boost::json::value_to_tag<RedeemEthAssetEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "WBETH") {
        return RedeemEthAssetEnum::Wbeth;
    }
    if (s == "BETH") {
        return RedeemEthAssetEnum::Beth;
    }
    return RedeemEthAssetEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                RedeemEthAssetEnum value) {
    if (value == RedeemEthAssetEnum::Unknown) {
        throw std::invalid_argument("RedeemEthAssetEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

EthStakingApi::EthStakingApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
EthStakingApi::eth_staking_account_request(const EthStakingAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/eth-staking/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<EthStakingAccountResponse>
EthStakingApi::eth_staking_account(const EthStakingAccountParams& params) const {
    return common::send<EthStakingAccountResponse>(*client_, eth_staking_account_request(params));
}

common::RestRequest EthStakingApi::get_current_eth_staking_quota_request(
    const GetCurrentEthStakingQuotaParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/eth-staking/eth/quota";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCurrentEthStakingQuotaResponse>
EthStakingApi::get_current_eth_staking_quota(const GetCurrentEthStakingQuotaParams& params) const {
    return common::send<GetCurrentEthStakingQuotaResponse>(
        *client_, get_current_eth_staking_quota_request(params));
}

common::RestRequest EthStakingApi::get_eth_redemption_history_request(
    const GetEthRedemptionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/eth-staking/eth/history/redemptionHistory";
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

common::RestApiResponse<GetEthRedemptionHistoryResponse>
EthStakingApi::get_eth_redemption_history(const GetEthRedemptionHistoryParams& params) const {
    return common::send<GetEthRedemptionHistoryResponse>(
        *client_, get_eth_redemption_history_request(params));
}

common::RestRequest
EthStakingApi::get_eth_staking_history_request(const GetEthStakingHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/eth-staking/eth/history/stakingHistory";
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

common::RestApiResponse<GetEthStakingHistoryResponse>
EthStakingApi::get_eth_staking_history(const GetEthStakingHistoryParams& params) const {
    return common::send<GetEthStakingHistoryResponse>(*client_,
                                                      get_eth_staking_history_request(params));
}

common::RestRequest
EthStakingApi::get_wbeth_rate_history_request(const GetWbethRateHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/eth-staking/eth/history/rateHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetWbethRateHistoryResponse>
EthStakingApi::get_wbeth_rate_history(const GetWbethRateHistoryParams& params) const {
    return common::send<GetWbethRateHistoryResponse>(*client_,
                                                     get_wbeth_rate_history_request(params));
}

common::RestRequest
EthStakingApi::get_wbeth_rewards_history_request(const GetWbethRewardsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/eth-staking/eth/history/wbethRewardsHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetWbethRewardsHistoryResponse>
EthStakingApi::get_wbeth_rewards_history(const GetWbethRewardsHistoryParams& params) const {
    return common::send<GetWbethRewardsHistoryResponse>(*client_,
                                                        get_wbeth_rewards_history_request(params));
}

common::RestRequest
EthStakingApi::get_wbeth_unwrap_history_request(const GetWbethUnwrapHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/eth-staking/wbeth/history/unwrapHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetWbethUnwrapHistoryResponse>
EthStakingApi::get_wbeth_unwrap_history(const GetWbethUnwrapHistoryParams& params) const {
    return common::send<GetWbethUnwrapHistoryResponse>(*client_,
                                                       get_wbeth_unwrap_history_request(params));
}

common::RestRequest
EthStakingApi::get_wbeth_wrap_history_request(const GetWbethWrapHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/eth-staking/wbeth/history/wrapHistory";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetWbethWrapHistoryResponse>
EthStakingApi::get_wbeth_wrap_history(const GetWbethWrapHistoryParams& params) const {
    return common::send<GetWbethWrapHistoryResponse>(*client_,
                                                     get_wbeth_wrap_history_request(params));
}

common::RestRequest EthStakingApi::redeem_eth_request(const RedeemEthParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/eth-staking/eth/redeem";
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RedeemEthResponse>
EthStakingApi::redeem_eth(const RedeemEthParams& params) const {
    return common::send<RedeemEthResponse>(*client_, redeem_eth_request(params));
}

common::RestRequest
EthStakingApi::subscribe_eth_staking_request(const SubscribeEthStakingParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v2/eth-staking/eth/stake";
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubscribeEthStakingResponse>
EthStakingApi::subscribe_eth_staking(const SubscribeEthStakingParams& params) const {
    return common::send<SubscribeEthStakingResponse>(*client_,
                                                     subscribe_eth_staking_request(params));
}

common::RestRequest EthStakingApi::wrap_beth_request(const WrapBethParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/eth-staking/wbeth/wrap";
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<WrapBethResponse>
EthStakingApi::wrap_beth(const WrapBethParams& params) const {
    return common::send<WrapBethResponse>(*client_, wrap_beth_request(params));
}

} // namespace binance::staking::rest_api
