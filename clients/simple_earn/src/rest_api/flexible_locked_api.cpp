//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/flexible_locked_api.hpp>

namespace binance::simple_earn::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetFlexibleRewardsHistoryTypeEnum value) noexcept {
    switch (value) {
    case GetFlexibleRewardsHistoryTypeEnum::Bonus:
        return "BONUS";
    case GetFlexibleRewardsHistoryTypeEnum::Realtime:
        return "REALTIME";
    case GetFlexibleRewardsHistoryTypeEnum::Rewards:
        return "REWARDS";
    case GetFlexibleRewardsHistoryTypeEnum::All:
        return "ALL";
    case GetFlexibleRewardsHistoryTypeEnum::Unknown:
        break;
    }
    return "";
}

GetFlexibleRewardsHistoryTypeEnum
tag_invoke(boost::json::value_to_tag<GetFlexibleRewardsHistoryTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BONUS") {
        return GetFlexibleRewardsHistoryTypeEnum::Bonus;
    }
    if (s == "REALTIME") {
        return GetFlexibleRewardsHistoryTypeEnum::Realtime;
    }
    if (s == "REWARDS") {
        return GetFlexibleRewardsHistoryTypeEnum::Rewards;
    }
    if (s == "ALL") {
        return GetFlexibleRewardsHistoryTypeEnum::All;
    }
    return GetFlexibleRewardsHistoryTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetFlexibleRewardsHistoryTypeEnum value) {
    if (value == GetFlexibleRewardsHistoryTypeEnum::Unknown) {
        throw std::invalid_argument("GetFlexibleRewardsHistoryTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(GetRateHistoryAprPeriodEnum value) noexcept {
    switch (value) {
    case GetRateHistoryAprPeriodEnum::Day:
        return "DAY";
    case GetRateHistoryAprPeriodEnum::Year:
        return "YEAR";
    case GetRateHistoryAprPeriodEnum::Unknown:
        break;
    }
    return "";
}

GetRateHistoryAprPeriodEnum
tag_invoke(boost::json::value_to_tag<GetRateHistoryAprPeriodEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "DAY") {
        return GetRateHistoryAprPeriodEnum::Day;
    }
    if (s == "YEAR") {
        return GetRateHistoryAprPeriodEnum::Year;
    }
    return GetRateHistoryAprPeriodEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetRateHistoryAprPeriodEnum value) {
    if (value == GetRateHistoryAprPeriodEnum::Unknown) {
        throw std::invalid_argument("GetRateHistoryAprPeriodEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(RedeemFlexibleProductDestAccountEnum value) noexcept {
    switch (value) {
    case RedeemFlexibleProductDestAccountEnum::Spot:
        return "SPOT";
    case RedeemFlexibleProductDestAccountEnum::Fund:
        return "FUND";
    case RedeemFlexibleProductDestAccountEnum::Unknown:
        break;
    }
    return "";
}

RedeemFlexibleProductDestAccountEnum
tag_invoke(boost::json::value_to_tag<RedeemFlexibleProductDestAccountEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return RedeemFlexibleProductDestAccountEnum::Spot;
    }
    if (s == "FUND") {
        return RedeemFlexibleProductDestAccountEnum::Fund;
    }
    return RedeemFlexibleProductDestAccountEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                RedeemFlexibleProductDestAccountEnum value) {
    if (value == RedeemFlexibleProductDestAccountEnum::Unknown) {
        throw std::invalid_argument("RedeemFlexibleProductDestAccountEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SetLockedProductRedeemOptionRedeemToEnum value) noexcept {
    switch (value) {
    case SetLockedProductRedeemOptionRedeemToEnum::Spot:
        return "SPOT";
    case SetLockedProductRedeemOptionRedeemToEnum::Flexible:
        return "FLEXIBLE";
    case SetLockedProductRedeemOptionRedeemToEnum::Unknown:
        break;
    }
    return "";
}

SetLockedProductRedeemOptionRedeemToEnum
tag_invoke(boost::json::value_to_tag<SetLockedProductRedeemOptionRedeemToEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return SetLockedProductRedeemOptionRedeemToEnum::Spot;
    }
    if (s == "FLEXIBLE") {
        return SetLockedProductRedeemOptionRedeemToEnum::Flexible;
    }
    return SetLockedProductRedeemOptionRedeemToEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SetLockedProductRedeemOptionRedeemToEnum value) {
    if (value == SetLockedProductRedeemOptionRedeemToEnum::Unknown) {
        throw std::invalid_argument(
            "SetLockedProductRedeemOptionRedeemToEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SubscribeFlexibleProductSourceAccountEnum value) noexcept {
    switch (value) {
    case SubscribeFlexibleProductSourceAccountEnum::Spot:
        return "SPOT";
    case SubscribeFlexibleProductSourceAccountEnum::Fund:
        return "FUND";
    case SubscribeFlexibleProductSourceAccountEnum::All:
        return "ALL";
    case SubscribeFlexibleProductSourceAccountEnum::Unknown:
        break;
    }
    return "";
}

SubscribeFlexibleProductSourceAccountEnum
tag_invoke(boost::json::value_to_tag<SubscribeFlexibleProductSourceAccountEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return SubscribeFlexibleProductSourceAccountEnum::Spot;
    }
    if (s == "FUND") {
        return SubscribeFlexibleProductSourceAccountEnum::Fund;
    }
    if (s == "ALL") {
        return SubscribeFlexibleProductSourceAccountEnum::All;
    }
    return SubscribeFlexibleProductSourceAccountEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SubscribeFlexibleProductSourceAccountEnum value) {
    if (value == SubscribeFlexibleProductSourceAccountEnum::Unknown) {
        throw std::invalid_argument(
            "SubscribeFlexibleProductSourceAccountEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SubscribeLockedProductSourceAccountEnum value) noexcept {
    switch (value) {
    case SubscribeLockedProductSourceAccountEnum::Spot:
        return "SPOT";
    case SubscribeLockedProductSourceAccountEnum::Fund:
        return "FUND";
    case SubscribeLockedProductSourceAccountEnum::All:
        return "ALL";
    case SubscribeLockedProductSourceAccountEnum::Unknown:
        break;
    }
    return "";
}

SubscribeLockedProductSourceAccountEnum
tag_invoke(boost::json::value_to_tag<SubscribeLockedProductSourceAccountEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return SubscribeLockedProductSourceAccountEnum::Spot;
    }
    if (s == "FUND") {
        return SubscribeLockedProductSourceAccountEnum::Fund;
    }
    if (s == "ALL") {
        return SubscribeLockedProductSourceAccountEnum::All;
    }
    return SubscribeLockedProductSourceAccountEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SubscribeLockedProductSourceAccountEnum value) {
    if (value == SubscribeLockedProductSourceAccountEnum::Unknown) {
        throw std::invalid_argument(
            "SubscribeLockedProductSourceAccountEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SubscribeLockedProductRedeemToEnum value) noexcept {
    switch (value) {
    case SubscribeLockedProductRedeemToEnum::Spot:
        return "SPOT";
    case SubscribeLockedProductRedeemToEnum::Flexible:
        return "FLEXIBLE";
    case SubscribeLockedProductRedeemToEnum::Unknown:
        break;
    }
    return "";
}

SubscribeLockedProductRedeemToEnum
tag_invoke(boost::json::value_to_tag<SubscribeLockedProductRedeemToEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return SubscribeLockedProductRedeemToEnum::Spot;
    }
    if (s == "FLEXIBLE") {
        return SubscribeLockedProductRedeemToEnum::Flexible;
    }
    return SubscribeLockedProductRedeemToEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SubscribeLockedProductRedeemToEnum value) {
    if (value == SubscribeLockedProductRedeemToEnum::Unknown) {
        throw std::invalid_argument("SubscribeLockedProductRedeemToEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

FlexibleLockedApi::FlexibleLockedApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
FlexibleLockedApi::get_collateral_record_request(const GetCollateralRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/flexible/history/collateralRecord";
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCollateralRecordResponse>
FlexibleLockedApi::get_collateral_record(const GetCollateralRecordParams& params) const {
    return common::send<GetCollateralRecordResponse>(*client_,
                                                     get_collateral_record_request(params));
}

common::RestRequest FlexibleLockedApi::get_flexible_personal_left_quota_request(
    const GetFlexiblePersonalLeftQuotaParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/flexible/personalLeftQuota";
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexiblePersonalLeftQuotaResponse>
FlexibleLockedApi::get_flexible_personal_left_quota(
    const GetFlexiblePersonalLeftQuotaParams& params) const {
    return common::send<GetFlexiblePersonalLeftQuotaResponse>(
        *client_, get_flexible_personal_left_quota_request(params));
}

common::RestRequest FlexibleLockedApi::get_flexible_product_position_request(
    const GetFlexibleProductPositionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/flexible/position";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleProductPositionResponse>
FlexibleLockedApi::get_flexible_product_position(
    const GetFlexibleProductPositionParams& params) const {
    return common::send<GetFlexibleProductPositionResponse>(
        *client_, get_flexible_product_position_request(params));
}

common::RestRequest FlexibleLockedApi::get_flexible_redemption_record_request(
    const GetFlexibleRedemptionRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/flexible/history/redemptionRecord";
    common::detail::json::set_param(req.query, "productId", params.product_id);
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

common::RestApiResponse<GetFlexibleRedemptionRecordResponse>
FlexibleLockedApi::get_flexible_redemption_record(
    const GetFlexibleRedemptionRecordParams& params) const {
    return common::send<GetFlexibleRedemptionRecordResponse>(
        *client_, get_flexible_redemption_record_request(params));
}

common::RestRequest FlexibleLockedApi::get_flexible_rewards_history_request(
    const GetFlexibleRewardsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/flexible/history/rewardsRecord";
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleRewardsHistoryResponse>
FlexibleLockedApi::get_flexible_rewards_history(
    const GetFlexibleRewardsHistoryParams& params) const {
    return common::send<GetFlexibleRewardsHistoryResponse>(
        *client_, get_flexible_rewards_history_request(params));
}

common::RestRequest FlexibleLockedApi::get_flexible_subscription_preview_request(
    const GetFlexibleSubscriptionPreviewParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/flexible/subscriptionPreview";
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleSubscriptionPreviewResponse>
FlexibleLockedApi::get_flexible_subscription_preview(
    const GetFlexibleSubscriptionPreviewParams& params) const {
    return common::send<GetFlexibleSubscriptionPreviewResponse>(
        *client_, get_flexible_subscription_preview_request(params));
}

common::RestRequest FlexibleLockedApi::get_flexible_subscription_record_request(
    const GetFlexibleSubscriptionRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/flexible/history/subscriptionRecord";
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "purchaseId", params.purchase_id);
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

common::RestApiResponse<GetFlexibleSubscriptionRecordResponse>
FlexibleLockedApi::get_flexible_subscription_record(
    const GetFlexibleSubscriptionRecordParams& params) const {
    return common::send<GetFlexibleSubscriptionRecordResponse>(
        *client_, get_flexible_subscription_record_request(params));
}

common::RestRequest FlexibleLockedApi::get_locked_personal_left_quota_request(
    const GetLockedPersonalLeftQuotaParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/locked/personalLeftQuota";
    common::detail::json::set_param(req.query, "projectId", params.project_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetLockedPersonalLeftQuotaResponse>
FlexibleLockedApi::get_locked_personal_left_quota(
    const GetLockedPersonalLeftQuotaParams& params) const {
    return common::send<GetLockedPersonalLeftQuotaResponse>(
        *client_, get_locked_personal_left_quota_request(params));
}

common::RestRequest FlexibleLockedApi::get_locked_product_position_request(
    const GetLockedProductPositionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/locked/position";
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

common::RestApiResponse<GetLockedProductPositionResponse>
FlexibleLockedApi::get_locked_product_position(const GetLockedProductPositionParams& params) const {
    return common::send<GetLockedProductPositionResponse>(
        *client_, get_locked_product_position_request(params));
}

common::RestRequest FlexibleLockedApi::get_locked_redemption_record_request(
    const GetLockedRedemptionRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/locked/history/redemptionRecord";
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

common::RestApiResponse<GetLockedRedemptionRecordResponse>
FlexibleLockedApi::get_locked_redemption_record(
    const GetLockedRedemptionRecordParams& params) const {
    return common::send<GetLockedRedemptionRecordResponse>(
        *client_, get_locked_redemption_record_request(params));
}

common::RestRequest FlexibleLockedApi::get_locked_rewards_history_request(
    const GetLockedRewardsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/locked/history/rewardsRecord";
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

common::RestApiResponse<GetLockedRewardsHistoryResponse>
FlexibleLockedApi::get_locked_rewards_history(const GetLockedRewardsHistoryParams& params) const {
    return common::send<GetLockedRewardsHistoryResponse>(
        *client_, get_locked_rewards_history_request(params));
}

common::RestRequest FlexibleLockedApi::get_locked_subscription_preview_request(
    const GetLockedSubscriptionPreviewParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/locked/subscriptionPreview";
    common::detail::json::set_param(req.query, "projectId", params.project_id);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "autoSubscribe", params.auto_subscribe);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetLockedSubscriptionPreviewResponseInner>>
FlexibleLockedApi::get_locked_subscription_preview(
    const GetLockedSubscriptionPreviewParams& params) const {
    return common::send<std::vector<GetLockedSubscriptionPreviewResponseInner>>(
        *client_, get_locked_subscription_preview_request(params));
}

common::RestRequest FlexibleLockedApi::get_locked_subscription_record_request(
    const GetLockedSubscriptionRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/locked/history/subscriptionRecord";
    common::detail::json::set_param(req.query, "purchaseId", params.purchase_id);
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

common::RestApiResponse<GetLockedSubscriptionRecordResponse>
FlexibleLockedApi::get_locked_subscription_record(
    const GetLockedSubscriptionRecordParams& params) const {
    return common::send<GetLockedSubscriptionRecordResponse>(
        *client_, get_locked_subscription_record_request(params));
}

common::RestRequest
FlexibleLockedApi::get_rate_history_request(const GetRateHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/flexible/history/rateHistory";
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "aprPeriod", params.apr_period);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetRateHistoryResponse>
FlexibleLockedApi::get_rate_history(const GetRateHistoryParams& params) const {
    return common::send<GetRateHistoryResponse>(*client_, get_rate_history_request(params));
}

common::RestRequest FlexibleLockedApi::get_simple_earn_flexible_product_list_request(
    const GetSimpleEarnFlexibleProductListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/flexible/list";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSimpleEarnFlexibleProductListResponse>
FlexibleLockedApi::get_simple_earn_flexible_product_list(
    const GetSimpleEarnFlexibleProductListParams& params) const {
    return common::send<GetSimpleEarnFlexibleProductListResponse>(
        *client_, get_simple_earn_flexible_product_list_request(params));
}

common::RestRequest FlexibleLockedApi::get_simple_earn_locked_product_list_request(
    const GetSimpleEarnLockedProductListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/locked/list";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSimpleEarnLockedProductListResponse>
FlexibleLockedApi::get_simple_earn_locked_product_list(
    const GetSimpleEarnLockedProductListParams& params) const {
    return common::send<GetSimpleEarnLockedProductListResponse>(
        *client_, get_simple_earn_locked_product_list_request(params));
}

common::RestRequest FlexibleLockedApi::redeem_flexible_product_request(
    const RedeemFlexibleProductParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/simple-earn/flexible/redeem";
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "redeemAll", params.redeem_all);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "destAccount", params.dest_account);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RedeemFlexibleProductResponse>
FlexibleLockedApi::redeem_flexible_product(const RedeemFlexibleProductParams& params) const {
    return common::send<RedeemFlexibleProductResponse>(*client_,
                                                       redeem_flexible_product_request(params));
}

common::RestRequest
FlexibleLockedApi::redeem_locked_product_request(const RedeemLockedProductParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/simple-earn/locked/redeem";
    common::detail::json::set_param(req.query, "positionId", params.position_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RedeemLockedProductResponse>
FlexibleLockedApi::redeem_locked_product(const RedeemLockedProductParams& params) const {
    return common::send<RedeemLockedProductResponse>(*client_,
                                                     redeem_locked_product_request(params));
}

common::RestRequest FlexibleLockedApi::set_flexible_auto_subscribe_request(
    const SetFlexibleAutoSubscribeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/simple-earn/flexible/setAutoSubscribe";
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "autoSubscribe", params.auto_subscribe);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SetFlexibleAutoSubscribeResponse>
FlexibleLockedApi::set_flexible_auto_subscribe(const SetFlexibleAutoSubscribeParams& params) const {
    return common::send<SetFlexibleAutoSubscribeResponse>(
        *client_, set_flexible_auto_subscribe_request(params));
}

common::RestRequest FlexibleLockedApi::set_locked_auto_subscribe_request(
    const SetLockedAutoSubscribeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/simple-earn/locked/setAutoSubscribe";
    common::detail::json::set_param(req.query, "positionId", params.position_id);
    common::detail::json::set_param(req.query, "autoSubscribe", params.auto_subscribe);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SetLockedAutoSubscribeResponse>
FlexibleLockedApi::set_locked_auto_subscribe(const SetLockedAutoSubscribeParams& params) const {
    return common::send<SetLockedAutoSubscribeResponse>(*client_,
                                                        set_locked_auto_subscribe_request(params));
}

common::RestRequest FlexibleLockedApi::set_locked_product_redeem_option_request(
    const SetLockedProductRedeemOptionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/simple-earn/locked/setRedeemOption";
    common::detail::json::set_param(req.query, "positionId", params.position_id);
    common::detail::json::set_param(req.query, "redeemTo", params.redeem_to);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SetLockedProductRedeemOptionResponse>
FlexibleLockedApi::set_locked_product_redeem_option(
    const SetLockedProductRedeemOptionParams& params) const {
    return common::send<SetLockedProductRedeemOptionResponse>(
        *client_, set_locked_product_redeem_option_request(params));
}

common::RestRequest
FlexibleLockedApi::simple_account_request(const SimpleAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/simple-earn/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SimpleAccountResponse>
FlexibleLockedApi::simple_account(const SimpleAccountParams& params) const {
    return common::send<SimpleAccountResponse>(*client_, simple_account_request(params));
}

common::RestRequest FlexibleLockedApi::subscribe_flexible_product_request(
    const SubscribeFlexibleProductParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/simple-earn/flexible/subscribe";
    common::detail::json::set_param(req.query, "productId", params.product_id);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "autoSubscribe", params.auto_subscribe);
    common::detail::json::set_param(req.query, "sourceAccount", params.source_account);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubscribeFlexibleProductResponse>
FlexibleLockedApi::subscribe_flexible_product(const SubscribeFlexibleProductParams& params) const {
    return common::send<SubscribeFlexibleProductResponse>(
        *client_, subscribe_flexible_product_request(params));
}

common::RestRequest FlexibleLockedApi::subscribe_locked_product_request(
    const SubscribeLockedProductParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/simple-earn/locked/subscribe";
    common::detail::json::set_param(req.query, "projectId", params.project_id);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "autoSubscribe", params.auto_subscribe);
    common::detail::json::set_param(req.query, "sourceAccount", params.source_account);
    common::detail::json::set_param(req.query, "redeemTo", params.redeem_to);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubscribeLockedProductResponse>
FlexibleLockedApi::subscribe_locked_product(const SubscribeLockedProductParams& params) const {
    return common::send<SubscribeLockedProductResponse>(*client_,
                                                        subscribe_locked_product_request(params));
}

} // namespace binance::simple_earn::rest_api
