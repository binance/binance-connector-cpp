//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/soft_staking_api.hpp>

namespace binance::staking::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

SoftStakingApi::SoftStakingApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest SoftStakingApi::get_soft_staking_product_list_request(
    const GetSoftStakingProductListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/soft-staking/list";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSoftStakingProductListResponse>
SoftStakingApi::get_soft_staking_product_list(const GetSoftStakingProductListParams& params) const {
    return common::send<GetSoftStakingProductListResponse>(
        *client_, get_soft_staking_product_list_request(params));
}

common::RestRequest SoftStakingApi::get_soft_staking_rewards_history_request(
    const GetSoftStakingRewardsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/soft-staking/history/rewardsRecord";
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

common::RestApiResponse<GetSoftStakingRewardsHistoryResponse>
SoftStakingApi::get_soft_staking_rewards_history(
    const GetSoftStakingRewardsHistoryParams& params) const {
    return common::send<GetSoftStakingRewardsHistoryResponse>(
        *client_, get_soft_staking_rewards_history_request(params));
}

common::RestRequest
SoftStakingApi::set_soft_staking_request(const SetSoftStakingParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/soft-staking/set";
    common::detail::json::set_param(req.query, "softStaking", params.soft_staking);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SetSoftStakingResponse>
SoftStakingApi::set_soft_staking(const SetSoftStakingParams& params) const {
    return common::send<SetSoftStakingResponse>(*client_, set_soft_staking_request(params));
}

} // namespace binance::staking::rest_api
