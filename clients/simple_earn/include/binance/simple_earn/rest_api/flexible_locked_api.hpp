//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/models/get_collateral_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_personal_left_quota_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_product_position_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_redemption_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_rewards_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_subscription_preview_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_subscription_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_personal_left_quota_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_product_position_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_redemption_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_rewards_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_subscription_preview_response_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_subscription_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rate_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_flexible_product_list_response.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_locked_product_list_response.hpp>
#include <binance/simple_earn/rest_api/models/redeem_flexible_product_response.hpp>
#include <binance/simple_earn/rest_api/models/redeem_locked_product_response.hpp>
#include <binance/simple_earn/rest_api/models/set_flexible_auto_subscribe_response.hpp>
#include <binance/simple_earn/rest_api/models/set_locked_auto_subscribe_response.hpp>
#include <binance/simple_earn/rest_api/models/set_locked_product_redeem_option_response.hpp>
#include <binance/simple_earn/rest_api/models/simple_account_response.hpp>
#include <binance/simple_earn/rest_api/models/subscribe_flexible_product_response.hpp>
#include <binance/simple_earn/rest_api/models/subscribe_locked_product_response.hpp>

namespace binance::simple_earn::rest_api {

enum class GetFlexibleRewardsHistoryTypeEnum {
    Bonus,
    Realtime,
    Rewards,
    All,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(GetFlexibleRewardsHistoryTypeEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT GetFlexibleRewardsHistoryTypeEnum
tag_invoke(boost::json::value_to_tag<GetFlexibleRewardsHistoryTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           GetFlexibleRewardsHistoryTypeEnum value);

enum class GetRateHistoryAprPeriodEnum {
    Day,
    Year,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(GetRateHistoryAprPeriodEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT GetRateHistoryAprPeriodEnum tag_invoke(
    boost::json::value_to_tag<GetRateHistoryAprPeriodEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           GetRateHistoryAprPeriodEnum value);

enum class RedeemFlexibleProductDestAccountEnum {
    Spot,
    Fund,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(RedeemFlexibleProductDestAccountEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT RedeemFlexibleProductDestAccountEnum
tag_invoke(boost::json::value_to_tag<RedeemFlexibleProductDestAccountEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           RedeemFlexibleProductDestAccountEnum value);

enum class SetLockedProductRedeemOptionRedeemToEnum {
    Spot,
    Flexible,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(SetLockedProductRedeemOptionRedeemToEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT SetLockedProductRedeemOptionRedeemToEnum
tag_invoke(boost::json::value_to_tag<SetLockedProductRedeemOptionRedeemToEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           SetLockedProductRedeemOptionRedeemToEnum value);

enum class SubscribeFlexibleProductSourceAccountEnum {
    Spot,
    Fund,
    All,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(SubscribeFlexibleProductSourceAccountEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT SubscribeFlexibleProductSourceAccountEnum
tag_invoke(boost::json::value_to_tag<SubscribeFlexibleProductSourceAccountEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           SubscribeFlexibleProductSourceAccountEnum value);

enum class SubscribeLockedProductSourceAccountEnum {
    Spot,
    Fund,
    All,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(SubscribeLockedProductSourceAccountEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT SubscribeLockedProductSourceAccountEnum
tag_invoke(boost::json::value_to_tag<SubscribeLockedProductSourceAccountEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           SubscribeLockedProductSourceAccountEnum value);

enum class SubscribeLockedProductRedeemToEnum {
    Spot,
    Flexible,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(SubscribeLockedProductRedeemToEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT SubscribeLockedProductRedeemToEnum
tag_invoke(boost::json::value_to_tag<SubscribeLockedProductRedeemToEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           SubscribeLockedProductRedeemToEnum value);

struct GetCollateralRecordParams {
    std::optional<std::string> product_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexiblePersonalLeftQuotaParams {
    common::Required<std::string> product_id;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleProductPositionParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::string> product_id = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleRedemptionRecordParams {
    std::optional<std::string> product_id = std::nullopt;
    std::optional<std::string> redeem_id = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleRewardsHistoryParams {
    std::optional<std::string> product_id = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// `BONUS` - Bonus tiered APR, `REALTIME` - Real-time APR, `REWARDS` - Historical rewards,
    /// `ALL` - All types. Default: `ALL`
    std::optional<GetFlexibleRewardsHistoryTypeEnum> type = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleSubscriptionPreviewParams {
    common::Required<std::string> product_id;
    common::Required<common::Decimal> amount;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleSubscriptionRecordParams {
    std::optional<std::string> product_id = std::nullopt;
    std::optional<std::string> purchase_id = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetLockedPersonalLeftQuotaParams {
    common::Required<std::string> project_id;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetLockedProductPositionParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::string> position_id = std::nullopt;
    std::optional<std::string> project_id = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetLockedRedemptionRecordParams {
    std::optional<std::string> position_id = std::nullopt;
    std::optional<std::string> redeem_id = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetLockedRewardsHistoryParams {
    std::optional<std::string> position_id = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetLockedSubscriptionPreviewParams {
    common::Required<std::string> project_id;
    common::Required<common::Decimal> amount;
    /// default true.
    std::optional<bool> auto_subscribe = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetLockedSubscriptionRecordParams {
    std::optional<std::string> purchase_id = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetRateHistoryParams {
    common::Required<std::string> product_id;
    std::optional<GetRateHistoryAprPeriodEnum> apr_period = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSimpleEarnFlexibleProductListParams {
    std::optional<std::string> asset = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSimpleEarnLockedProductListParams {
    std::optional<std::string> asset = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RedeemFlexibleProductParams {
    common::Required<std::string> product_id;
    std::optional<bool> redeem_all = std::nullopt;
    /// if redeemAll is false, amount is mandatory
    std::optional<common::Decimal> amount = std::nullopt;
    std::optional<RedeemFlexibleProductDestAccountEnum> dest_account = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RedeemLockedProductParams {
    /// Locked product position ID
    common::Required<std::string> position_id;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SetFlexibleAutoSubscribeParams {
    common::Required<std::string> product_id;
    common::Required<bool> auto_subscribe;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SetLockedAutoSubscribeParams {
    common::Required<std::string> position_id;
    common::Required<bool> auto_subscribe;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SetLockedProductRedeemOptionParams {
    common::Required<std::string> position_id;
    common::Required<SetLockedProductRedeemOptionRedeemToEnum> redeem_to;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SimpleAccountParams {
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubscribeFlexibleProductParams {
    common::Required<std::string> product_id;
    common::Required<common::Decimal> amount;
    std::optional<bool> auto_subscribe = std::nullopt;
    std::optional<SubscribeFlexibleProductSourceAccountEnum> source_account = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubscribeLockedProductParams {
    common::Required<std::string> project_id;
    common::Required<common::Decimal> amount;
    std::optional<bool> auto_subscribe = std::nullopt;
    std::optional<SubscribeLockedProductSourceAccountEnum> source_account = std::nullopt;
    std::optional<SubscribeLockedProductRedeemToEnum> redeem_to = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_SIMPLE_EARN_EXPORT FlexibleLockedApi {
public:
    explicit FlexibleLockedApi(std::shared_ptr<common::RestClient> client);

    /// Get Collateral Record (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/flexible/history/collateralRecord.
    ///
    /// Get Collateral Record
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 30 days.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-collateral-record
    [[nodiscard]] common::RestApiResponse<GetCollateralRecordResponse>
    get_collateral_record(const GetCollateralRecordParams& params = {}) const;

    /// Asynchronous `get_collateral_record()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCollateralRecordResponse>)`.
    template <class CompletionToken>
    auto async_get_collateral_record(const GetCollateralRecordParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<GetCollateralRecordResponse>(
            client_, get_collateral_record_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Flexible Personal Left Quota (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/flexible/personalLeftQuota.
    ///
    /// Get Flexible Personal Left Quota
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-flexible-personal-left-quota
    [[nodiscard]] common::RestApiResponse<GetFlexiblePersonalLeftQuotaResponse>
    get_flexible_personal_left_quota(const GetFlexiblePersonalLeftQuotaParams& params) const;

    /// Asynchronous `get_flexible_personal_left_quota()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFlexiblePersonalLeftQuotaResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_personal_left_quota(const GetFlexiblePersonalLeftQuotaParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<GetFlexiblePersonalLeftQuotaResponse>(
            client_, get_flexible_personal_left_quota_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Flexible Product Position (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/flexible/position.
    ///
    /// Get Flexible Product Position
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-flexible-product-position
    [[nodiscard]] common::RestApiResponse<GetFlexibleProductPositionResponse>
    get_flexible_product_position(const GetFlexibleProductPositionParams& params = {}) const;

    /// Asynchronous `get_flexible_product_position()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFlexibleProductPositionResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_product_position(const GetFlexibleProductPositionParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetFlexibleProductPositionResponse>(
            client_, get_flexible_product_position_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Flexible Redemption Record (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/flexible/history/redemptionRecord.
    ///
    /// Get Flexible Redemption Record
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 30 days.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-flexible-redemption-record
    [[nodiscard]] common::RestApiResponse<GetFlexibleRedemptionRecordResponse>
    get_flexible_redemption_record(const GetFlexibleRedemptionRecordParams& params = {}) const;

    /// Asynchronous `get_flexible_redemption_record()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFlexibleRedemptionRecordResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_redemption_record(const GetFlexibleRedemptionRecordParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetFlexibleRedemptionRecordResponse>(
            client_, get_flexible_redemption_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Flexible Rewards History (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/flexible/history/rewardsRecord.
    ///
    /// Get Flexible Rewards History
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 30 days.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-flexible-rewards-history
    [[nodiscard]] common::RestApiResponse<GetFlexibleRewardsHistoryResponse>
    get_flexible_rewards_history(const GetFlexibleRewardsHistoryParams& params = {}) const;

    /// Asynchronous `get_flexible_rewards_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFlexibleRewardsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_rewards_history(const GetFlexibleRewardsHistoryParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<GetFlexibleRewardsHistoryResponse>(
            client_, get_flexible_rewards_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Flexible Subscription Preview (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/flexible/subscriptionPreview.
    ///
    /// Get Flexible Subscription Preview
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-flexible-subscription-preview
    [[nodiscard]] common::RestApiResponse<GetFlexibleSubscriptionPreviewResponse>
    get_flexible_subscription_preview(const GetFlexibleSubscriptionPreviewParams& params) const;

    /// Asynchronous `get_flexible_subscription_preview()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFlexibleSubscriptionPreviewResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_subscription_preview(const GetFlexibleSubscriptionPreviewParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<GetFlexibleSubscriptionPreviewResponse>(
            client_, get_flexible_subscription_preview_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Flexible Subscription Record (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/flexible/history/subscriptionRecord.
    ///
    /// Get Flexible Subscription Record
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 30 days.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-flexible-subscription-record
    [[nodiscard]] common::RestApiResponse<GetFlexibleSubscriptionRecordResponse>
    get_flexible_subscription_record(const GetFlexibleSubscriptionRecordParams& params = {}) const;

    /// Asynchronous `get_flexible_subscription_record()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFlexibleSubscriptionRecordResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_subscription_record(const GetFlexibleSubscriptionRecordParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<GetFlexibleSubscriptionRecordResponse>(
            client_, get_flexible_subscription_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Locked Personal Left Quota (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/locked/personalLeftQuota.
    ///
    /// Get Locked Personal Left Quota
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-locked-personal-left-quota
    [[nodiscard]] common::RestApiResponse<GetLockedPersonalLeftQuotaResponse>
    get_locked_personal_left_quota(const GetLockedPersonalLeftQuotaParams& params) const;

    /// Asynchronous `get_locked_personal_left_quota()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetLockedPersonalLeftQuotaResponse>)`.
    template <class CompletionToken>
    auto async_get_locked_personal_left_quota(const GetLockedPersonalLeftQuotaParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetLockedPersonalLeftQuotaResponse>(
            client_, get_locked_personal_left_quota_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Locked Product Position (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/locked/position.
    ///
    /// Get Locked Product Position
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-locked-product-position
    [[nodiscard]] common::RestApiResponse<GetLockedProductPositionResponse>
    get_locked_product_position(const GetLockedProductPositionParams& params = {}) const;

    /// Asynchronous `get_locked_product_position()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetLockedProductPositionResponse>)`.
    template <class CompletionToken>
    auto async_get_locked_product_position(const GetLockedProductPositionParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<GetLockedProductPositionResponse>(
            client_, get_locked_product_position_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Locked Redemption Record (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/locked/history/redemptionRecord.
    ///
    /// Get Locked Redemption Record
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 30 days.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-locked-redemption-record
    [[nodiscard]] common::RestApiResponse<GetLockedRedemptionRecordResponse>
    get_locked_redemption_record(const GetLockedRedemptionRecordParams& params = {}) const;

    /// Asynchronous `get_locked_redemption_record()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetLockedRedemptionRecordResponse>)`.
    template <class CompletionToken>
    auto async_get_locked_redemption_record(const GetLockedRedemptionRecordParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<GetLockedRedemptionRecordResponse>(
            client_, get_locked_redemption_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Locked Rewards History (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/locked/history/rewardsRecord.
    ///
    /// Get Locked Rewards History
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 30 days.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-locked-rewards-history
    [[nodiscard]] common::RestApiResponse<GetLockedRewardsHistoryResponse>
    get_locked_rewards_history(const GetLockedRewardsHistoryParams& params = {}) const;

    /// Asynchronous `get_locked_rewards_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetLockedRewardsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_locked_rewards_history(const GetLockedRewardsHistoryParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<GetLockedRewardsHistoryResponse>(
            client_, get_locked_rewards_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Locked Subscription Preview (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/locked/subscriptionPreview.
    ///
    /// Get Locked Subscription Preview
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-locked-subscription-preview
    [[nodiscard]] common::RestApiResponse<std::vector<GetLockedSubscriptionPreviewResponseInner>>
    get_locked_subscription_preview(const GetLockedSubscriptionPreviewParams& params) const;

    /// Asynchronous `get_locked_subscription_preview()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetLockedSubscriptionPreviewResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_locked_subscription_preview(const GetLockedSubscriptionPreviewParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<GetLockedSubscriptionPreviewResponseInner>>(
            client_, get_locked_subscription_preview_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Locked Subscription Record (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/locked/history/subscriptionRecord.
    ///
    /// Get Locked Subscription Record
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 30 days.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-locked-subscription-record
    [[nodiscard]] common::RestApiResponse<GetLockedSubscriptionRecordResponse>
    get_locked_subscription_record(const GetLockedSubscriptionRecordParams& params = {}) const;

    /// Asynchronous `get_locked_subscription_record()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetLockedSubscriptionRecordResponse>)`.
    template <class CompletionToken>
    auto async_get_locked_subscription_record(const GetLockedSubscriptionRecordParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetLockedSubscriptionRecordResponse>(
            client_, get_locked_subscription_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Rate History (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/flexible/history/rateHistory.
    ///
    /// Get Rate History
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between startTime and endTime cannot be longer than 1 year.
    /// - If `startTime` and `endTime` are
    ///   both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-rate-history
    [[nodiscard]] common::RestApiResponse<GetRateHistoryResponse>
    get_rate_history(const GetRateHistoryParams& params) const;

    /// Asynchronous `get_rate_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetRateHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_rate_history(const GetRateHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetRateHistoryResponse>(client_, get_rate_history_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Get Simple Earn Flexible Product List (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/flexible/list.
    ///
    /// Get available Simple Earn flexible product list
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-simple-earn-flexible-product-list
    [[nodiscard]] common::RestApiResponse<GetSimpleEarnFlexibleProductListResponse>
    get_simple_earn_flexible_product_list(
        const GetSimpleEarnFlexibleProductListParams& params = {}) const;

    /// Asynchronous `get_simple_earn_flexible_product_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetSimpleEarnFlexibleProductListResponse>)`.
    template <class CompletionToken>
    auto async_get_simple_earn_flexible_product_list(
        const GetSimpleEarnFlexibleProductListParams& params, CompletionToken&& token) const {
        return common::async_send<GetSimpleEarnFlexibleProductListResponse>(
            client_, get_simple_earn_flexible_product_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Simple Earn Locked Product List (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/locked/list.
    ///
    /// Get Simple Earn Locked Product List
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Get available Simple Earn locked product list
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#get-simple-earn-locked-product-list
    [[nodiscard]] common::RestApiResponse<GetSimpleEarnLockedProductListResponse>
    get_simple_earn_locked_product_list(
        const GetSimpleEarnLockedProductListParams& params = {}) const;

    /// Asynchronous `get_simple_earn_locked_product_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetSimpleEarnLockedProductListResponse>)`.
    template <class CompletionToken>
    auto
    async_get_simple_earn_locked_product_list(const GetSimpleEarnLockedProductListParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetSimpleEarnLockedProductListResponse>(
            client_, get_simple_earn_locked_product_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Redeem Flexible Product (TRADE)
    ///
    /// POST /sapi/v1/simple-earn/flexible/redeem.
    ///
    /// Redeem Flexible Product
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open `Enable Spot & Margin Trading` permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#redeem-flexible-product
    [[nodiscard]] common::RestApiResponse<RedeemFlexibleProductResponse>
    redeem_flexible_product(const RedeemFlexibleProductParams& params) const;

    /// Asynchronous `redeem_flexible_product()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RedeemFlexibleProductResponse>)`.
    template <class CompletionToken>
    auto async_redeem_flexible_product(const RedeemFlexibleProductParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<RedeemFlexibleProductResponse>(
            client_, redeem_flexible_product_request(params), std::forward<CompletionToken>(token));
    }

    /// Redeem Locked Product (TRADE)
    ///
    /// POST /sapi/v1/simple-earn/locked/redeem.
    ///
    /// Redeem Locked Product
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open `Enable Spot & Margin Trading` permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#redeem-locked-product
    [[nodiscard]] common::RestApiResponse<RedeemLockedProductResponse>
    redeem_locked_product(const RedeemLockedProductParams& params) const;

    /// Asynchronous `redeem_locked_product()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RedeemLockedProductResponse>)`.
    template <class CompletionToken>
    auto async_redeem_locked_product(const RedeemLockedProductParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<RedeemLockedProductResponse>(
            client_, redeem_locked_product_request(params), std::forward<CompletionToken>(token));
    }

    /// Set Flexible Auto Subscribe (USER_DATA)
    ///
    /// POST /sapi/v1/simple-earn/flexible/setAutoSubscribe.
    ///
    /// Set Flexible Auto Subscribe
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#set-flexible-auto-subscribe
    [[nodiscard]] common::RestApiResponse<SetFlexibleAutoSubscribeResponse>
    set_flexible_auto_subscribe(const SetFlexibleAutoSubscribeParams& params) const;

    /// Asynchronous `set_flexible_auto_subscribe()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SetFlexibleAutoSubscribeResponse>)`.
    template <class CompletionToken>
    auto async_set_flexible_auto_subscribe(const SetFlexibleAutoSubscribeParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<SetFlexibleAutoSubscribeResponse>(
            client_, set_flexible_auto_subscribe_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Set Locked Auto Subscribe (USER_DATA)
    ///
    /// POST /sapi/v1/simple-earn/locked/setAutoSubscribe.
    ///
    /// Set locked auto subscribe
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#set-locked-auto-subscribe
    [[nodiscard]] common::RestApiResponse<SetLockedAutoSubscribeResponse>
    set_locked_auto_subscribe(const SetLockedAutoSubscribeParams& params) const;

    /// Asynchronous `set_locked_auto_subscribe()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SetLockedAutoSubscribeResponse>)`.
    template <class CompletionToken>
    auto async_set_locked_auto_subscribe(const SetLockedAutoSubscribeParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<SetLockedAutoSubscribeResponse>(
            client_, set_locked_auto_subscribe_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Set Locked Product Redeem Option (USER_DATA)
    ///
    /// POST /sapi/v1/simple-earn/locked/setRedeemOption.
    ///
    /// Set redeem option for Locked product
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#set-locked-product-redeem-option
    [[nodiscard]] common::RestApiResponse<SetLockedProductRedeemOptionResponse>
    set_locked_product_redeem_option(const SetLockedProductRedeemOptionParams& params) const;

    /// Asynchronous `set_locked_product_redeem_option()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SetLockedProductRedeemOptionResponse>)`.
    template <class CompletionToken>
    auto async_set_locked_product_redeem_option(const SetLockedProductRedeemOptionParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<SetLockedProductRedeemOptionResponse>(
            client_, set_locked_product_redeem_option_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Simple Account (USER_DATA)
    ///
    /// GET /sapi/v1/simple-earn/account.
    ///
    /// Simple Account query
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#simple-account
    [[nodiscard]] common::RestApiResponse<SimpleAccountResponse>
    simple_account(const SimpleAccountParams& params = {}) const;

    /// Asynchronous `simple_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SimpleAccountResponse>)`.
    template <class CompletionToken>
    auto async_simple_account(const SimpleAccountParams& params, CompletionToken&& token) const {
        return common::async_send<SimpleAccountResponse>(client_, simple_account_request(params),
                                                         std::forward<CompletionToken>(token));
    }

    /// Subscribe Flexible Product (TRADE)
    ///
    /// POST /sapi/v1/simple-earn/flexible/subscribe.
    ///
    /// Subscribe Flexible Product
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open `Enable Spot & Margin Trading` permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#subscribe-flexible-product
    [[nodiscard]] common::RestApiResponse<SubscribeFlexibleProductResponse>
    subscribe_flexible_product(const SubscribeFlexibleProductParams& params) const;

    /// Asynchronous `subscribe_flexible_product()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubscribeFlexibleProductResponse>)`.
    template <class CompletionToken>
    auto async_subscribe_flexible_product(const SubscribeFlexibleProductParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<SubscribeFlexibleProductResponse>(
            client_, subscribe_flexible_product_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Subscribe Locked Product (TRADE)
    ///
    /// POST /sapi/v1/simple-earn/locked/subscribe.
    ///
    /// Subscribe Locked Product
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open `Enable Spot & Margin Trading` permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/flexible-locked#subscribe-locked-product
    [[nodiscard]] common::RestApiResponse<SubscribeLockedProductResponse>
    subscribe_locked_product(const SubscribeLockedProductParams& params) const;

    /// Asynchronous `subscribe_locked_product()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubscribeLockedProductResponse>)`.
    template <class CompletionToken>
    auto async_subscribe_locked_product(const SubscribeLockedProductParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<SubscribeLockedProductResponse>(
            client_, subscribe_locked_product_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_collateral_record_request(const GetCollateralRecordParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_personal_left_quota_request(
        const GetFlexiblePersonalLeftQuotaParams& params) const;
    [[nodiscard]] common::RestRequest
    get_flexible_product_position_request(const GetFlexibleProductPositionParams& params) const;
    [[nodiscard]] common::RestRequest
    get_flexible_redemption_record_request(const GetFlexibleRedemptionRecordParams& params) const;
    [[nodiscard]] common::RestRequest
    get_flexible_rewards_history_request(const GetFlexibleRewardsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_subscription_preview_request(
        const GetFlexibleSubscriptionPreviewParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_subscription_record_request(
        const GetFlexibleSubscriptionRecordParams& params) const;
    [[nodiscard]] common::RestRequest
    get_locked_personal_left_quota_request(const GetLockedPersonalLeftQuotaParams& params) const;
    [[nodiscard]] common::RestRequest
    get_locked_product_position_request(const GetLockedProductPositionParams& params) const;
    [[nodiscard]] common::RestRequest
    get_locked_redemption_record_request(const GetLockedRedemptionRecordParams& params) const;
    [[nodiscard]] common::RestRequest
    get_locked_rewards_history_request(const GetLockedRewardsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_locked_subscription_preview_request(const GetLockedSubscriptionPreviewParams& params) const;
    [[nodiscard]] common::RestRequest
    get_locked_subscription_record_request(const GetLockedSubscriptionRecordParams& params) const;
    [[nodiscard]] common::RestRequest
    get_rate_history_request(const GetRateHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_simple_earn_flexible_product_list_request(
        const GetSimpleEarnFlexibleProductListParams& params) const;
    [[nodiscard]] common::RestRequest get_simple_earn_locked_product_list_request(
        const GetSimpleEarnLockedProductListParams& params) const;
    [[nodiscard]] common::RestRequest
    redeem_flexible_product_request(const RedeemFlexibleProductParams& params) const;
    [[nodiscard]] common::RestRequest
    redeem_locked_product_request(const RedeemLockedProductParams& params) const;
    [[nodiscard]] common::RestRequest
    set_flexible_auto_subscribe_request(const SetFlexibleAutoSubscribeParams& params) const;
    [[nodiscard]] common::RestRequest
    set_locked_auto_subscribe_request(const SetLockedAutoSubscribeParams& params) const;
    [[nodiscard]] common::RestRequest set_locked_product_redeem_option_request(
        const SetLockedProductRedeemOptionParams& params) const;
    [[nodiscard]] common::RestRequest
    simple_account_request(const SimpleAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    subscribe_flexible_product_request(const SubscribeFlexibleProductParams& params) const;
    [[nodiscard]] common::RestRequest
    subscribe_locked_product_request(const SubscribeLockedProductParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::simple_earn::rest_api
