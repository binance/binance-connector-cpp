//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/on_chain_yields_api.hpp>

namespace binance::staking::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum value) noexcept {
    switch (value) {
    case SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Spot:
        return "SPOT";
    case SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Flexible:
        return "FLEXIBLE";
    case SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Unknown:
        break;
    }
    return "";
}

SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum
tag_invoke(boost::json::value_to_tag<SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Spot;
    }
    if (s == "FLEXIBLE") {
        return SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Flexible;
    }
    return SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum value) {
    if (value == SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Unknown) {
        throw std::invalid_argument(
            "SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SubscribeOnChainYieldsLockedProductSourceAccountEnum value) noexcept {
    switch (value) {
    case SubscribeOnChainYieldsLockedProductSourceAccountEnum::Spot:
        return "SPOT";
    case SubscribeOnChainYieldsLockedProductSourceAccountEnum::Fund:
        return "FUND";
    case SubscribeOnChainYieldsLockedProductSourceAccountEnum::All:
        return "ALL";
    case SubscribeOnChainYieldsLockedProductSourceAccountEnum::Unknown:
        break;
    }
    return "";
}

SubscribeOnChainYieldsLockedProductSourceAccountEnum
tag_invoke(boost::json::value_to_tag<SubscribeOnChainYieldsLockedProductSourceAccountEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return SubscribeOnChainYieldsLockedProductSourceAccountEnum::Spot;
    }
    if (s == "FUND") {
        return SubscribeOnChainYieldsLockedProductSourceAccountEnum::Fund;
    }
    if (s == "ALL") {
        return SubscribeOnChainYieldsLockedProductSourceAccountEnum::All;
    }
    return SubscribeOnChainYieldsLockedProductSourceAccountEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SubscribeOnChainYieldsLockedProductSourceAccountEnum value) {
    if (value == SubscribeOnChainYieldsLockedProductSourceAccountEnum::Unknown) {
        throw std::invalid_argument(
            "SubscribeOnChainYieldsLockedProductSourceAccountEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SubscribeOnChainYieldsLockedProductRedeemToEnum value) noexcept {
    switch (value) {
    case SubscribeOnChainYieldsLockedProductRedeemToEnum::Spot:
        return "SPOT";
    case SubscribeOnChainYieldsLockedProductRedeemToEnum::Flexible:
        return "FLEXIBLE";
    case SubscribeOnChainYieldsLockedProductRedeemToEnum::Unknown:
        break;
    }
    return "";
}

SubscribeOnChainYieldsLockedProductRedeemToEnum
tag_invoke(boost::json::value_to_tag<SubscribeOnChainYieldsLockedProductRedeemToEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return SubscribeOnChainYieldsLockedProductRedeemToEnum::Spot;
    }
    if (s == "FLEXIBLE") {
        return SubscribeOnChainYieldsLockedProductRedeemToEnum::Flexible;
    }
    return SubscribeOnChainYieldsLockedProductRedeemToEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SubscribeOnChainYieldsLockedProductRedeemToEnum value) {
    if (value == SubscribeOnChainYieldsLockedProductRedeemToEnum::Unknown) {
        throw std::invalid_argument(
            "SubscribeOnChainYieldsLockedProductRedeemToEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

OnChainYieldsApi::OnChainYieldsApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest OnChainYieldsApi::get_on_chain_yields_locked_personal_left_quota_request(
    const GetOnChainYieldsLockedPersonalLeftQuotaParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/onchain-yields/locked/personalLeftQuota";
    common::detail::json::set_param(req.query, "projectId", params.project_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOnChainYieldsLockedPersonalLeftQuotaResponse>
OnChainYieldsApi::get_on_chain_yields_locked_personal_left_quota(
    const GetOnChainYieldsLockedPersonalLeftQuotaParams& params) const {
    return common::send<GetOnChainYieldsLockedPersonalLeftQuotaResponse>(
        *client_, get_on_chain_yields_locked_personal_left_quota_request(params));
}

common::RestRequest OnChainYieldsApi::get_on_chain_yields_locked_product_list_request(
    const GetOnChainYieldsLockedProductListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/onchain-yields/locked/list";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOnChainYieldsLockedProductListResponse>
OnChainYieldsApi::get_on_chain_yields_locked_product_list(
    const GetOnChainYieldsLockedProductListParams& params) const {
    return common::send<GetOnChainYieldsLockedProductListResponse>(
        *client_, get_on_chain_yields_locked_product_list_request(params));
}

common::RestRequest OnChainYieldsApi::get_on_chain_yields_locked_product_position_request(
    const GetOnChainYieldsLockedProductPositionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/onchain-yields/locked/position";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "positionId", params.position_id);
    common::detail::json::set_param(req.query, "projectId", params.project_id);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOnChainYieldsLockedProductPositionResponse>
OnChainYieldsApi::get_on_chain_yields_locked_product_position(
    const GetOnChainYieldsLockedProductPositionParams& params) const {
    return common::send<GetOnChainYieldsLockedProductPositionResponse>(
        *client_, get_on_chain_yields_locked_product_position_request(params));
}

common::RestRequest OnChainYieldsApi::get_on_chain_yields_locked_redemption_record_request(
    const GetOnChainYieldsLockedRedemptionRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/onchain-yields/locked/history/redemptionRecord";
    common::detail::json::set_param(req.query, "positionId", params.position_id);
    common::detail::json::set_param(req.query, "redeemId", params.redeem_id);
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

common::RestApiResponse<GetOnChainYieldsLockedRedemptionRecordResponse>
OnChainYieldsApi::get_on_chain_yields_locked_redemption_record(
    const GetOnChainYieldsLockedRedemptionRecordParams& params) const {
    return common::send<GetOnChainYieldsLockedRedemptionRecordResponse>(
        *client_, get_on_chain_yields_locked_redemption_record_request(params));
}

common::RestRequest OnChainYieldsApi::get_on_chain_yields_locked_rewards_history_request(
    const GetOnChainYieldsLockedRewardsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/onchain-yields/locked/history/rewardsRecord";
    common::detail::json::set_param(req.query, "positionId", params.position_id);
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

common::RestApiResponse<GetOnChainYieldsLockedRewardsHistoryResponse>
OnChainYieldsApi::get_on_chain_yields_locked_rewards_history(
    const GetOnChainYieldsLockedRewardsHistoryParams& params) const {
    return common::send<GetOnChainYieldsLockedRewardsHistoryResponse>(
        *client_, get_on_chain_yields_locked_rewards_history_request(params));
}

common::RestRequest OnChainYieldsApi::get_on_chain_yields_locked_subscription_preview_request(
    const GetOnChainYieldsLockedSubscriptionPreviewParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/onchain-yields/locked/subscriptionPreview";
    common::detail::json::set_param(req.query, "projectId", params.project_id);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "autoSubscribe", params.auto_subscribe);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOnChainYieldsLockedSubscriptionPreviewResponse>
OnChainYieldsApi::get_on_chain_yields_locked_subscription_preview(
    const GetOnChainYieldsLockedSubscriptionPreviewParams& params) const {
    return common::send<GetOnChainYieldsLockedSubscriptionPreviewResponse>(
        *client_, get_on_chain_yields_locked_subscription_preview_request(params));
}

common::RestRequest OnChainYieldsApi::get_on_chain_yields_locked_subscription_record_request(
    const GetOnChainYieldsLockedSubscriptionRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/onchain-yields/locked/history/subscriptionRecord";
    common::detail::json::set_param(req.query, "purchaseId", params.purchase_id);
    common::detail::json::set_param(req.query, "clientId", params.client_id);
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

common::RestApiResponse<GetOnChainYieldsLockedSubscriptionRecordResponse>
OnChainYieldsApi::get_on_chain_yields_locked_subscription_record(
    const GetOnChainYieldsLockedSubscriptionRecordParams& params) const {
    return common::send<GetOnChainYieldsLockedSubscriptionRecordResponse>(
        *client_, get_on_chain_yields_locked_subscription_record_request(params));
}

common::RestRequest
OnChainYieldsApi::on_chain_yields_account_request(const OnChainYieldsAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/onchain-yields/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OnChainYieldsAccountResponse>
OnChainYieldsApi::on_chain_yields_account(const OnChainYieldsAccountParams& params) const {
    return common::send<OnChainYieldsAccountResponse>(*client_,
                                                      on_chain_yields_account_request(params));
}

common::RestRequest OnChainYieldsApi::redeem_on_chain_yields_locked_product_request(
    const RedeemOnChainYieldsLockedProductParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/onchain-yields/locked/redeem";
    common::detail::json::set_param(req.query, "positionId", params.position_id);
    common::detail::json::set_param(req.query, "channelId", params.channel_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RedeemOnChainYieldsLockedProductResponse>
OnChainYieldsApi::redeem_on_chain_yields_locked_product(
    const RedeemOnChainYieldsLockedProductParams& params) const {
    return common::send<RedeemOnChainYieldsLockedProductResponse>(
        *client_, redeem_on_chain_yields_locked_product_request(params));
}

common::RestRequest OnChainYieldsApi::set_on_chain_yields_locked_auto_subscribe_request(
    const SetOnChainYieldsLockedAutoSubscribeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/onchain-yields/locked/setAutoSubscribe";
    common::detail::json::set_param(req.query, "positionId", params.position_id);
    common::detail::json::set_param(req.query, "autoSubscribe", params.auto_subscribe);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SetOnChainYieldsLockedAutoSubscribeResponse>
OnChainYieldsApi::set_on_chain_yields_locked_auto_subscribe(
    const SetOnChainYieldsLockedAutoSubscribeParams& params) const {
    return common::send<SetOnChainYieldsLockedAutoSubscribeResponse>(
        *client_, set_on_chain_yields_locked_auto_subscribe_request(params));
}

common::RestRequest OnChainYieldsApi::set_on_chain_yields_locked_product_redeem_option_request(
    const SetOnChainYieldsLockedProductRedeemOptionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/onchain-yields/locked/setRedeemOption";
    common::detail::json::set_param(req.query, "positionId", params.position_id);
    common::detail::json::set_param(req.query, "redeemTo", params.redeem_to);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SetOnChainYieldsLockedProductRedeemOptionResponse>
OnChainYieldsApi::set_on_chain_yields_locked_product_redeem_option(
    const SetOnChainYieldsLockedProductRedeemOptionParams& params) const {
    return common::send<SetOnChainYieldsLockedProductRedeemOptionResponse>(
        *client_, set_on_chain_yields_locked_product_redeem_option_request(params));
}

common::RestRequest OnChainYieldsApi::subscribe_on_chain_yields_locked_product_request(
    const SubscribeOnChainYieldsLockedProductParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/onchain-yields/locked/subscribe";
    common::detail::json::set_param(req.query, "projectId", params.project_id);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "autoSubscribe", params.auto_subscribe);
    common::detail::json::set_param(req.query, "sourceAccount", params.source_account);
    common::detail::json::set_param(req.query, "redeemTo", params.redeem_to);
    common::detail::json::set_param(req.query, "channelId", params.channel_id);
    common::detail::json::set_param(req.query, "clientId", params.client_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubscribeOnChainYieldsLockedProductResponse>
OnChainYieldsApi::subscribe_on_chain_yields_locked_product(
    const SubscribeOnChainYieldsLockedProductParams& params) const {
    return common::send<SubscribeOnChainYieldsLockedProductResponse>(
        *client_, subscribe_on_chain_yields_locked_product_request(params));
}

} // namespace binance::staking::rest_api
