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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_personal_left_quota_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_list_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_position_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_redemption_record_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_subscription_preview_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_subscription_record_response.hpp>
#include <binance/staking/rest_api/models/on_chain_yields_account_response.hpp>
#include <binance/staking/rest_api/models/redeem_on_chain_yields_locked_product_response.hpp>
#include <binance/staking/rest_api/models/set_on_chain_yields_locked_auto_subscribe_response.hpp>
#include <binance/staking/rest_api/models/set_on_chain_yields_locked_product_redeem_option_response.hpp>
#include <binance/staking/rest_api/models/subscribe_on_chain_yields_locked_product_response.hpp>

namespace binance::staking::rest_api {

enum class SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum {
    Spot,
    Flexible,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STAKING_EXPORT std::string_view
to_string(SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum value) noexcept;
BINANCE_STAKING_EXPORT SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum
tag_invoke(boost::json::value_to_tag<SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum value);

enum class SubscribeOnChainYieldsLockedProductSourceAccountEnum {
    Spot,
    Fund,
    All,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STAKING_EXPORT std::string_view
to_string(SubscribeOnChainYieldsLockedProductSourceAccountEnum value) noexcept;
BINANCE_STAKING_EXPORT SubscribeOnChainYieldsLockedProductSourceAccountEnum
tag_invoke(boost::json::value_to_tag<SubscribeOnChainYieldsLockedProductSourceAccountEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       SubscribeOnChainYieldsLockedProductSourceAccountEnum value);

enum class SubscribeOnChainYieldsLockedProductRedeemToEnum {
    Spot,
    Flexible,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STAKING_EXPORT std::string_view
to_string(SubscribeOnChainYieldsLockedProductRedeemToEnum value) noexcept;
BINANCE_STAKING_EXPORT SubscribeOnChainYieldsLockedProductRedeemToEnum
tag_invoke(boost::json::value_to_tag<SubscribeOnChainYieldsLockedProductRedeemToEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       SubscribeOnChainYieldsLockedProductRedeemToEnum value);

struct GetOnChainYieldsLockedPersonalLeftQuotaParams {
    common::Required<std::string> project_id;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetOnChainYieldsLockedProductListParams {
    std::optional<std::string> asset = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetOnChainYieldsLockedProductPositionParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::string> position_id = std::nullopt;
    std::optional<std::string> project_id = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetOnChainYieldsLockedRedemptionRecordParams {
    std::optional<std::string> position_id = std::nullopt;
    std::optional<std::string> redeem_id = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetOnChainYieldsLockedRewardsHistoryParams {
    std::optional<std::string> position_id = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetOnChainYieldsLockedSubscriptionPreviewParams {
    common::Required<std::string> project_id;
    common::Required<common::Decimal> amount;
    std::optional<bool> auto_subscribe = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetOnChainYieldsLockedSubscriptionRecordParams {
    std::optional<std::string> purchase_id = std::nullopt;
    std::optional<std::string> client_id = std::nullopt;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OnChainYieldsAccountParams {
    /// The value cannot be greater than `60000`
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RedeemOnChainYieldsLockedProductParams {
    /// Locked product position ID
    common::Required<std::string> position_id;
    std::optional<std::string> channel_id = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SetOnChainYieldsLockedAutoSubscribeParams {
    common::Required<std::string> position_id;
    common::Required<bool> auto_subscribe;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SetOnChainYieldsLockedProductRedeemOptionParams {
    common::Required<std::string> position_id;
    common::Required<SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum> redeem_to;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubscribeOnChainYieldsLockedProductParams {
    common::Required<std::string> project_id;
    common::Required<common::Decimal> amount;
    std::optional<bool> auto_subscribe = std::nullopt;
    std::optional<SubscribeOnChainYieldsLockedProductSourceAccountEnum> source_account =
        std::nullopt;
    /// Takes effect when Auto Subscribe is false
    std::optional<SubscribeOnChainYieldsLockedProductRedeemToEnum> redeem_to = std::nullopt;
    std::optional<std::string> channel_id = std::nullopt;
    std::optional<std::string> client_id = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STAKING_EXPORT OnChainYieldsApi {
public:
    explicit OnChainYieldsApi(std::shared_ptr<common::RestClient> client);

    /// Get On-chain Yields Locked Personal Left Quota (USER_DATA)
    ///
    /// GET /sapi/v1/onchain-yields/locked/personalLeftQuota.
    ///
    /// Get On-chain Yields Locked Personal Left Quota
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#get-on-chain-yields-locked-personal-left-quota
    [[nodiscard]] common::RestApiResponse<GetOnChainYieldsLockedPersonalLeftQuotaResponse>
    get_on_chain_yields_locked_personal_left_quota(
        const GetOnChainYieldsLockedPersonalLeftQuotaParams& params) const;

    /// Asynchronous `get_on_chain_yields_locked_personal_left_quota()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetOnChainYieldsLockedPersonalLeftQuotaResponse>)`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_personal_left_quota(
        const GetOnChainYieldsLockedPersonalLeftQuotaParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetOnChainYieldsLockedPersonalLeftQuotaResponse>(
            client_, get_on_chain_yields_locked_personal_left_quota_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get On-chain Yields Locked Product List (USER_DATA)
    ///
    /// GET /sapi/v1/onchain-yields/locked/list.
    ///
    /// Get available On-chain Yields Locked product list
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Get available On-chain Yields Locked product list
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#get-on-chain-yields-locked-product-list
    [[nodiscard]] common::RestApiResponse<GetOnChainYieldsLockedProductListResponse>
    get_on_chain_yields_locked_product_list(
        const GetOnChainYieldsLockedProductListParams& params = {}) const;

    /// Asynchronous `get_on_chain_yields_locked_product_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetOnChainYieldsLockedProductListResponse>)`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_product_list(
        const GetOnChainYieldsLockedProductListParams& params, CompletionToken&& token) const {
        return common::async_send<GetOnChainYieldsLockedProductListResponse>(
            client_, get_on_chain_yields_locked_product_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get On-chain Yields Locked Product Position (USER_DATA)
    ///
    /// GET /sapi/v1/onchain-yields/locked/position.
    ///
    /// Get On-chain Yields Locked Product Position
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#get-on-chain-yields-locked-product-position
    [[nodiscard]] common::RestApiResponse<GetOnChainYieldsLockedProductPositionResponse>
    get_on_chain_yields_locked_product_position(
        const GetOnChainYieldsLockedProductPositionParams& params = {}) const;

    /// Asynchronous `get_on_chain_yields_locked_product_position()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetOnChainYieldsLockedProductPositionResponse>)`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_product_position(
        const GetOnChainYieldsLockedProductPositionParams& params, CompletionToken&& token) const {
        return common::async_send<GetOnChainYieldsLockedProductPositionResponse>(
            client_, get_on_chain_yields_locked_product_position_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get On-chain Yields Locked Redemption Record (USER_DATA)
    ///
    /// GET /sapi/v1/onchain-yields/locked/history/redemptionRecord.
    ///
    /// Get On-chain Yields Locked Redemption Record
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 3 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#get-on-chain-yields-locked-redemption-record
    [[nodiscard]] common::RestApiResponse<GetOnChainYieldsLockedRedemptionRecordResponse>
    get_on_chain_yields_locked_redemption_record(
        const GetOnChainYieldsLockedRedemptionRecordParams& params = {}) const;

    /// Asynchronous `get_on_chain_yields_locked_redemption_record()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetOnChainYieldsLockedRedemptionRecordResponse>)`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_redemption_record(
        const GetOnChainYieldsLockedRedemptionRecordParams& params, CompletionToken&& token) const {
        return common::async_send<GetOnChainYieldsLockedRedemptionRecordResponse>(
            client_, get_on_chain_yields_locked_redemption_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get On-chain Yields Locked Rewards History (USER_DATA)
    ///
    /// GET /sapi/v1/onchain-yields/locked/history/rewardsRecord.
    ///
    /// Get On-chain Yields Locked Rewards History
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 3 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#get-on-chain-yields-locked-rewards-history
    [[nodiscard]] common::RestApiResponse<GetOnChainYieldsLockedRewardsHistoryResponse>
    get_on_chain_yields_locked_rewards_history(
        const GetOnChainYieldsLockedRewardsHistoryParams& params = {}) const;

    /// Asynchronous `get_on_chain_yields_locked_rewards_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetOnChainYieldsLockedRewardsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_rewards_history(
        const GetOnChainYieldsLockedRewardsHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetOnChainYieldsLockedRewardsHistoryResponse>(
            client_, get_on_chain_yields_locked_rewards_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get On-chain Yields Locked Subscription Preview (USER_DATA)
    ///
    /// GET /sapi/v1/onchain-yields/locked/subscriptionPreview.
    ///
    /// Get On-chain Yields Locked Subscription Preview
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#get-on-chain-yields-locked-subscription-preview
    [[nodiscard]] common::RestApiResponse<GetOnChainYieldsLockedSubscriptionPreviewResponse>
    get_on_chain_yields_locked_subscription_preview(
        const GetOnChainYieldsLockedSubscriptionPreviewParams& params) const;

    /// Asynchronous `get_on_chain_yields_locked_subscription_preview()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetOnChainYieldsLockedSubscriptionPreviewResponse>)`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_subscription_preview(
        const GetOnChainYieldsLockedSubscriptionPreviewParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetOnChainYieldsLockedSubscriptionPreviewResponse>(
            client_, get_on_chain_yields_locked_subscription_preview_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get On-chain Yields Locked Subscription Record (USER_DATA)
    ///
    /// GET /sapi/v1/onchain-yields/locked/history/subscriptionRecord.
    ///
    /// Get On-chain Yields Locked Subscription Record
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 3 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, the next 30 days' data beginning from `startTime` will be returned.
    /// - If `endTime` is sent but
    ///   `startTime` is not sent, the 30 days' data before `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#get-on-chain-yields-locked-subscription-record
    [[nodiscard]] common::RestApiResponse<GetOnChainYieldsLockedSubscriptionRecordResponse>
    get_on_chain_yields_locked_subscription_record(
        const GetOnChainYieldsLockedSubscriptionRecordParams& params = {}) const;

    /// Asynchronous `get_on_chain_yields_locked_subscription_record()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetOnChainYieldsLockedSubscriptionRecordResponse>)`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_subscription_record(
        const GetOnChainYieldsLockedSubscriptionRecordParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetOnChainYieldsLockedSubscriptionRecordResponse>(
            client_, get_on_chain_yields_locked_subscription_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// On-chain Yields Account (USER_DATA)
    ///
    /// GET /sapi/v1/onchain-yields/account.
    ///
    /// On-chain Yields Account query
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#on-chain-yields-account
    [[nodiscard]] common::RestApiResponse<OnChainYieldsAccountResponse>
    on_chain_yields_account(const OnChainYieldsAccountParams& params = {}) const;

    /// Asynchronous `on_chain_yields_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OnChainYieldsAccountResponse>)`.
    template <class CompletionToken>
    auto async_on_chain_yields_account(const OnChainYieldsAccountParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<OnChainYieldsAccountResponse>(
            client_, on_chain_yields_account_request(params), std::forward<CompletionToken>(token));
    }

    /// Redeem On-chain Yields Locked Product (TRADE)
    ///
    /// POST /sapi/v1/onchain-yields/locked/redeem.
    ///
    /// Redeem On-chain Yields Locked Product
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open `Enable Spot & Margin Trading` permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#redeem-on-chain-yields-locked-product
    [[nodiscard]] common::RestApiResponse<RedeemOnChainYieldsLockedProductResponse>
    redeem_on_chain_yields_locked_product(
        const RedeemOnChainYieldsLockedProductParams& params) const;

    /// Asynchronous `redeem_on_chain_yields_locked_product()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<RedeemOnChainYieldsLockedProductResponse>)`.
    template <class CompletionToken>
    auto async_redeem_on_chain_yields_locked_product(
        const RedeemOnChainYieldsLockedProductParams& params, CompletionToken&& token) const {
        return common::async_send<RedeemOnChainYieldsLockedProductResponse>(
            client_, redeem_on_chain_yields_locked_product_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Set On-chain Yields Locked Auto Subscribe (USER_DATA)
    ///
    /// POST /sapi/v1/onchain-yields/locked/setAutoSubscribe.
    ///
    /// Set On-chain Yield locked auto subscribe
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#set-on-chain-yields-locked-auto-subscribe
    [[nodiscard]] common::RestApiResponse<SetOnChainYieldsLockedAutoSubscribeResponse>
    set_on_chain_yields_locked_auto_subscribe(
        const SetOnChainYieldsLockedAutoSubscribeParams& params) const;

    /// Asynchronous `set_on_chain_yields_locked_auto_subscribe()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<SetOnChainYieldsLockedAutoSubscribeResponse>)`.
    template <class CompletionToken>
    auto async_set_on_chain_yields_locked_auto_subscribe(
        const SetOnChainYieldsLockedAutoSubscribeParams& params, CompletionToken&& token) const {
        return common::async_send<SetOnChainYieldsLockedAutoSubscribeResponse>(
            client_, set_on_chain_yields_locked_auto_subscribe_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Set On-chain Yields Locked Product Redeem Option (USER_DATA)
    ///
    /// POST /sapi/v1/onchain-yields/locked/setRedeemOption.
    ///
    /// Set On-chain Yields redeem option for Locked product
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#set-on-chain-yields-locked-product-redeem-option
    [[nodiscard]] common::RestApiResponse<SetOnChainYieldsLockedProductRedeemOptionResponse>
    set_on_chain_yields_locked_product_redeem_option(
        const SetOnChainYieldsLockedProductRedeemOptionParams& params) const;

    /// Asynchronous `set_on_chain_yields_locked_product_redeem_option()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<SetOnChainYieldsLockedProductRedeemOptionResponse>)`.
    template <class CompletionToken>
    auto async_set_on_chain_yields_locked_product_redeem_option(
        const SetOnChainYieldsLockedProductRedeemOptionParams& params,
        CompletionToken&& token) const {
        return common::async_send<SetOnChainYieldsLockedProductRedeemOptionResponse>(
            client_, set_on_chain_yields_locked_product_redeem_option_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Subscribe On-chain Yields Locked Product (TRADE)
    ///
    /// POST /sapi/v1/onchain-yields/locked/subscribe.
    ///
    /// Subscribe On-chain Yields Locked Product
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open `Enable Spot & Margin Trading` permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/on-chain-yields#subscribe-on-chain-yields-locked-product
    [[nodiscard]] common::RestApiResponse<SubscribeOnChainYieldsLockedProductResponse>
    subscribe_on_chain_yields_locked_product(
        const SubscribeOnChainYieldsLockedProductParams& params) const;

    /// Asynchronous `subscribe_on_chain_yields_locked_product()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<SubscribeOnChainYieldsLockedProductResponse>)`.
    template <class CompletionToken>
    auto async_subscribe_on_chain_yields_locked_product(
        const SubscribeOnChainYieldsLockedProductParams& params, CompletionToken&& token) const {
        return common::async_send<SubscribeOnChainYieldsLockedProductResponse>(
            client_, subscribe_on_chain_yields_locked_product_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest get_on_chain_yields_locked_personal_left_quota_request(
        const GetOnChainYieldsLockedPersonalLeftQuotaParams& params) const;
    [[nodiscard]] common::RestRequest get_on_chain_yields_locked_product_list_request(
        const GetOnChainYieldsLockedProductListParams& params) const;
    [[nodiscard]] common::RestRequest get_on_chain_yields_locked_product_position_request(
        const GetOnChainYieldsLockedProductPositionParams& params) const;
    [[nodiscard]] common::RestRequest get_on_chain_yields_locked_redemption_record_request(
        const GetOnChainYieldsLockedRedemptionRecordParams& params) const;
    [[nodiscard]] common::RestRequest get_on_chain_yields_locked_rewards_history_request(
        const GetOnChainYieldsLockedRewardsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_on_chain_yields_locked_subscription_preview_request(
        const GetOnChainYieldsLockedSubscriptionPreviewParams& params) const;
    [[nodiscard]] common::RestRequest get_on_chain_yields_locked_subscription_record_request(
        const GetOnChainYieldsLockedSubscriptionRecordParams& params) const;
    [[nodiscard]] common::RestRequest
    on_chain_yields_account_request(const OnChainYieldsAccountParams& params) const;
    [[nodiscard]] common::RestRequest redeem_on_chain_yields_locked_product_request(
        const RedeemOnChainYieldsLockedProductParams& params) const;
    [[nodiscard]] common::RestRequest set_on_chain_yields_locked_auto_subscribe_request(
        const SetOnChainYieldsLockedAutoSubscribeParams& params) const;
    [[nodiscard]] common::RestRequest set_on_chain_yields_locked_product_redeem_option_request(
        const SetOnChainYieldsLockedProductRedeemOptionParams& params) const;
    [[nodiscard]] common::RestRequest subscribe_on_chain_yields_locked_product_request(
        const SubscribeOnChainYieldsLockedProductParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::staking::rest_api
