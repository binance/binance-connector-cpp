//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <string>
#include <utility>

#include <binance/common/config.hpp>
#include <binance/common/rest.hpp>
#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/bfusd_api.hpp>
#include <binance/simple_earn/rest_api/flexible_locked_api.hpp>
#include <binance/simple_earn/rest_api/models.hpp>
#include <binance/simple_earn/rest_api/rwusd_api.hpp>
#include <binance/simple_earn/rest_api/yield_arena_api.hpp>

namespace binance::simple_earn::rest_api {

/// SimpleEarn REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_SIMPLE_EARN_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Simple Earn REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);

    [[nodiscard]] const common::RestApiConfig& configuration() const noexcept;

    /// Calls an endpoint the SDK does not wrap yet. `T` may be `boost::json::value`.
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                 common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), false));
    }

    /// Like `send_request`, but signed (adds `timestamp` and `signature`).
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_signed_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                        common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), true));
    }

    template <class T, class CompletionToken>
    auto async_send_request(std::string endpoint, common::HttpMethod method, common::Params query,
                            common::Params body, CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), false),
            std::forward<CompletionToken>(token));
    }

    template <class T, class CompletionToken>
    auto async_send_signed_request(std::string endpoint, common::HttpMethod method,
                                   common::Params query, common::Params body,
                                   CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), true),
            std::forward<CompletionToken>(token));
    }

    // BfusdApi

    /// Get BFUSD Account (USER_DATA)
    ///
    /// GET /sapi/v1/bfusd/account.
    ///
    /// Get BFUSD account information.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/bfusd#get-bfusd-account
    [[nodiscard]] common::RestApiResponse<GetBfusdAccountResponse>
    get_bfusd_account(const GetBfusdAccountParams& params = {}) const {
        return bfusd_api_.get_bfusd_account(params);
    }
    /// Asynchronous `get_bfusd_account()`.
    template <class CompletionToken>
    auto async_get_bfusd_account(const GetBfusdAccountParams& params,
                                 CompletionToken&& token) const {
        return bfusd_api_.async_get_bfusd_account(params, std::forward<CompletionToken>(token));
    }

    /// Get BFUSD Quota Details (USER_DATA)
    ///
    /// GET /sapi/v1/bfusd/quota.
    ///
    /// Get BFUSD quota details including subscription quota, fast redemption quota, and standard
    /// redemption quota.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/bfusd#get-bfusd-quota-details
    [[nodiscard]] common::RestApiResponse<GetBfusdQuotaDetailsResponse>
    get_bfusd_quota_details(const GetBfusdQuotaDetailsParams& params = {}) const {
        return bfusd_api_.get_bfusd_quota_details(params);
    }
    /// Asynchronous `get_bfusd_quota_details()`.
    template <class CompletionToken>
    auto async_get_bfusd_quota_details(const GetBfusdQuotaDetailsParams& params,
                                       CompletionToken&& token) const {
        return bfusd_api_.async_get_bfusd_quota_details(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Get BFUSD Rate History (USER_DATA)
    ///
    /// GET /sapi/v1/bfusd/history/rateHistory.
    ///
    /// Get BFUSD rate history sorted by descending order.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 6 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, `endTime` will default to current time, and results from `startTime` onward will be
    ///   returned.
    /// - If
    ///   `endTime` is sent but `startTime` is not sent, `startTime` defaults to the current time
    ///   minus one month, and data between `startTime` and `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/bfusd#get-bfusd-rate-history
    [[nodiscard]] common::RestApiResponse<GetBfusdRateHistoryResponse>
    get_bfusd_rate_history(const GetBfusdRateHistoryParams& params = {}) const {
        return bfusd_api_.get_bfusd_rate_history(params);
    }
    /// Asynchronous `get_bfusd_rate_history()`.
    template <class CompletionToken>
    auto async_get_bfusd_rate_history(const GetBfusdRateHistoryParams& params,
                                      CompletionToken&& token) const {
        return bfusd_api_.async_get_bfusd_rate_history(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Get BFUSD Redemption History (USER_DATA)
    ///
    /// GET /sapi/v1/bfusd/history/redemptionHistory.
    ///
    /// Get BFUSD redemption history
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 6 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, `endTime` will default to current time, and results from `startTime` onward will be
    ///   returned.
    /// - If
    ///   `endTime` is sent but `startTime` is not sent, `startTime` defaults to the current time
    ///   minus one month, and data between `startTime` and `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/bfusd#get-bfusd-redemption-history
    [[nodiscard]] common::RestApiResponse<GetBfusdRedemptionHistoryResponse>
    get_bfusd_redemption_history(const GetBfusdRedemptionHistoryParams& params = {}) const {
        return bfusd_api_.get_bfusd_redemption_history(params);
    }
    /// Asynchronous `get_bfusd_redemption_history()`.
    template <class CompletionToken>
    auto async_get_bfusd_redemption_history(const GetBfusdRedemptionHistoryParams& params,
                                            CompletionToken&& token) const {
        return bfusd_api_.async_get_bfusd_redemption_history(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Get BFUSD Rewards History (USER_DATA)
    ///
    /// GET /sapi/v1/bfusd/history/rewardsHistory.
    ///
    /// Get BFUSD rewards history
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 6 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, `endTime` will default to current time, and results from `startTime` onward will be
    ///   returned.
    /// - If
    ///   `endTime` is sent but `startTime` is not sent, `startTime` defaults to the current time
    ///   minus one month, and data between `startTime` and `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/bfusd#get-bfusd-rewards-history
    [[nodiscard]] common::RestApiResponse<GetBfusdRewardsHistoryResponse>
    get_bfusd_rewards_history(const GetBfusdRewardsHistoryParams& params = {}) const {
        return bfusd_api_.get_bfusd_rewards_history(params);
    }
    /// Asynchronous `get_bfusd_rewards_history()`.
    template <class CompletionToken>
    auto async_get_bfusd_rewards_history(const GetBfusdRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return bfusd_api_.async_get_bfusd_rewards_history(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Get BFUSD subscription history (USER_DATA)
    ///
    /// GET /sapi/v1/bfusd/history/subscriptionHistory.
    ///
    /// Get BFUSD subscription history
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 6 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, `endTime` will default to current time, and results from `startTime` onward will be
    ///   returned.
    /// - If
    ///   `endTime` is sent but `startTime` is not sent, `startTime` defaults to the current time
    ///   advanced by one month, and data between `startTime` and `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/bfusd#get-bfusd-subscription-history
    [[nodiscard]] common::RestApiResponse<GetBfusdSubscriptionHistoryResponse>
    get_bfusd_subscription_history(const GetBfusdSubscriptionHistoryParams& params = {}) const {
        return bfusd_api_.get_bfusd_subscription_history(params);
    }
    /// Asynchronous `get_bfusd_subscription_history()`.
    template <class CompletionToken>
    auto async_get_bfusd_subscription_history(const GetBfusdSubscriptionHistoryParams& params,
                                              CompletionToken&& token) const {
        return bfusd_api_.async_get_bfusd_subscription_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Redeem BFUSD (TRADE)
    ///
    /// POST /sapi/v1/bfusd/redeem.
    ///
    /// Redeem BFUSD to USDT
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    /// - This API only supports BFUSD redemption to the Spot Account. Redemptions to the Funding
    /// Account or any other account type are not supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/bfusd#redeem-bfusd
    [[nodiscard]] common::RestApiResponse<RedeemBfusdResponse>
    redeem_bfusd(const RedeemBfusdParams& params) const {
        return bfusd_api_.redeem_bfusd(params);
    }
    /// Asynchronous `redeem_bfusd()`.
    template <class CompletionToken>
    auto async_redeem_bfusd(const RedeemBfusdParams& params, CompletionToken&& token) const {
        return bfusd_api_.async_redeem_bfusd(params, std::forward<CompletionToken>(token));
    }

    /// Subscribe BFUSD (TRADE)
    ///
    /// POST /sapi/v1/bfusd/subscribe.
    ///
    /// Subscribe BFUSD
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    /// - This API only supports BFUSD subscription using assets held in the Spot Account.
    /// Subscriptions initiated from the Funding Account or any other account type are not
    /// supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/bfusd#subscribe-bfusd
    [[nodiscard]] common::RestApiResponse<SubscribeBfusdResponse>
    subscribe_bfusd(const SubscribeBfusdParams& params) const {
        return bfusd_api_.subscribe_bfusd(params);
    }
    /// Asynchronous `subscribe_bfusd()`.
    template <class CompletionToken>
    auto async_subscribe_bfusd(const SubscribeBfusdParams& params, CompletionToken&& token) const {
        return bfusd_api_.async_subscribe_bfusd(params, std::forward<CompletionToken>(token));
    }

    // FlexibleLockedApi

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
    get_collateral_record(const GetCollateralRecordParams& params = {}) const {
        return flexible_locked_api_.get_collateral_record(params);
    }
    /// Asynchronous `get_collateral_record()`.
    template <class CompletionToken>
    auto async_get_collateral_record(const GetCollateralRecordParams& params,
                                     CompletionToken&& token) const {
        return flexible_locked_api_.async_get_collateral_record(
            params, std::forward<CompletionToken>(token));
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
    get_flexible_personal_left_quota(const GetFlexiblePersonalLeftQuotaParams& params) const {
        return flexible_locked_api_.get_flexible_personal_left_quota(params);
    }
    /// Asynchronous `get_flexible_personal_left_quota()`.
    template <class CompletionToken>
    auto async_get_flexible_personal_left_quota(const GetFlexiblePersonalLeftQuotaParams& params,
                                                CompletionToken&& token) const {
        return flexible_locked_api_.async_get_flexible_personal_left_quota(
            params, std::forward<CompletionToken>(token));
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
    get_flexible_product_position(const GetFlexibleProductPositionParams& params = {}) const {
        return flexible_locked_api_.get_flexible_product_position(params);
    }
    /// Asynchronous `get_flexible_product_position()`.
    template <class CompletionToken>
    auto async_get_flexible_product_position(const GetFlexibleProductPositionParams& params,
                                             CompletionToken&& token) const {
        return flexible_locked_api_.async_get_flexible_product_position(
            params, std::forward<CompletionToken>(token));
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
    get_flexible_redemption_record(const GetFlexibleRedemptionRecordParams& params = {}) const {
        return flexible_locked_api_.get_flexible_redemption_record(params);
    }
    /// Asynchronous `get_flexible_redemption_record()`.
    template <class CompletionToken>
    auto async_get_flexible_redemption_record(const GetFlexibleRedemptionRecordParams& params,
                                              CompletionToken&& token) const {
        return flexible_locked_api_.async_get_flexible_redemption_record(
            params, std::forward<CompletionToken>(token));
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
    get_flexible_rewards_history(const GetFlexibleRewardsHistoryParams& params = {}) const {
        return flexible_locked_api_.get_flexible_rewards_history(params);
    }
    /// Asynchronous `get_flexible_rewards_history()`.
    template <class CompletionToken>
    auto async_get_flexible_rewards_history(const GetFlexibleRewardsHistoryParams& params,
                                            CompletionToken&& token) const {
        return flexible_locked_api_.async_get_flexible_rewards_history(
            params, std::forward<CompletionToken>(token));
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
    get_flexible_subscription_preview(const GetFlexibleSubscriptionPreviewParams& params) const {
        return flexible_locked_api_.get_flexible_subscription_preview(params);
    }
    /// Asynchronous `get_flexible_subscription_preview()`.
    template <class CompletionToken>
    auto async_get_flexible_subscription_preview(const GetFlexibleSubscriptionPreviewParams& params,
                                                 CompletionToken&& token) const {
        return flexible_locked_api_.async_get_flexible_subscription_preview(
            params, std::forward<CompletionToken>(token));
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
    get_flexible_subscription_record(const GetFlexibleSubscriptionRecordParams& params = {}) const {
        return flexible_locked_api_.get_flexible_subscription_record(params);
    }
    /// Asynchronous `get_flexible_subscription_record()`.
    template <class CompletionToken>
    auto async_get_flexible_subscription_record(const GetFlexibleSubscriptionRecordParams& params,
                                                CompletionToken&& token) const {
        return flexible_locked_api_.async_get_flexible_subscription_record(
            params, std::forward<CompletionToken>(token));
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
    get_locked_personal_left_quota(const GetLockedPersonalLeftQuotaParams& params) const {
        return flexible_locked_api_.get_locked_personal_left_quota(params);
    }
    /// Asynchronous `get_locked_personal_left_quota()`.
    template <class CompletionToken>
    auto async_get_locked_personal_left_quota(const GetLockedPersonalLeftQuotaParams& params,
                                              CompletionToken&& token) const {
        return flexible_locked_api_.async_get_locked_personal_left_quota(
            params, std::forward<CompletionToken>(token));
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
    get_locked_product_position(const GetLockedProductPositionParams& params = {}) const {
        return flexible_locked_api_.get_locked_product_position(params);
    }
    /// Asynchronous `get_locked_product_position()`.
    template <class CompletionToken>
    auto async_get_locked_product_position(const GetLockedProductPositionParams& params,
                                           CompletionToken&& token) const {
        return flexible_locked_api_.async_get_locked_product_position(
            params, std::forward<CompletionToken>(token));
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
    get_locked_redemption_record(const GetLockedRedemptionRecordParams& params = {}) const {
        return flexible_locked_api_.get_locked_redemption_record(params);
    }
    /// Asynchronous `get_locked_redemption_record()`.
    template <class CompletionToken>
    auto async_get_locked_redemption_record(const GetLockedRedemptionRecordParams& params,
                                            CompletionToken&& token) const {
        return flexible_locked_api_.async_get_locked_redemption_record(
            params, std::forward<CompletionToken>(token));
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
    get_locked_rewards_history(const GetLockedRewardsHistoryParams& params = {}) const {
        return flexible_locked_api_.get_locked_rewards_history(params);
    }
    /// Asynchronous `get_locked_rewards_history()`.
    template <class CompletionToken>
    auto async_get_locked_rewards_history(const GetLockedRewardsHistoryParams& params,
                                          CompletionToken&& token) const {
        return flexible_locked_api_.async_get_locked_rewards_history(
            params, std::forward<CompletionToken>(token));
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
    get_locked_subscription_preview(const GetLockedSubscriptionPreviewParams& params) const {
        return flexible_locked_api_.get_locked_subscription_preview(params);
    }
    /// Asynchronous `get_locked_subscription_preview()`.
    template <class CompletionToken>
    auto async_get_locked_subscription_preview(const GetLockedSubscriptionPreviewParams& params,
                                               CompletionToken&& token) const {
        return flexible_locked_api_.async_get_locked_subscription_preview(
            params, std::forward<CompletionToken>(token));
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
    get_locked_subscription_record(const GetLockedSubscriptionRecordParams& params = {}) const {
        return flexible_locked_api_.get_locked_subscription_record(params);
    }
    /// Asynchronous `get_locked_subscription_record()`.
    template <class CompletionToken>
    auto async_get_locked_subscription_record(const GetLockedSubscriptionRecordParams& params,
                                              CompletionToken&& token) const {
        return flexible_locked_api_.async_get_locked_subscription_record(
            params, std::forward<CompletionToken>(token));
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
    get_rate_history(const GetRateHistoryParams& params) const {
        return flexible_locked_api_.get_rate_history(params);
    }
    /// Asynchronous `get_rate_history()`.
    template <class CompletionToken>
    auto async_get_rate_history(const GetRateHistoryParams& params, CompletionToken&& token) const {
        return flexible_locked_api_.async_get_rate_history(params,
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
        const GetSimpleEarnFlexibleProductListParams& params = {}) const {
        return flexible_locked_api_.get_simple_earn_flexible_product_list(params);
    }
    /// Asynchronous `get_simple_earn_flexible_product_list()`.
    template <class CompletionToken>
    auto async_get_simple_earn_flexible_product_list(
        const GetSimpleEarnFlexibleProductListParams& params, CompletionToken&& token) const {
        return flexible_locked_api_.async_get_simple_earn_flexible_product_list(
            params, std::forward<CompletionToken>(token));
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
        const GetSimpleEarnLockedProductListParams& params = {}) const {
        return flexible_locked_api_.get_simple_earn_locked_product_list(params);
    }
    /// Asynchronous `get_simple_earn_locked_product_list()`.
    template <class CompletionToken>
    auto
    async_get_simple_earn_locked_product_list(const GetSimpleEarnLockedProductListParams& params,
                                              CompletionToken&& token) const {
        return flexible_locked_api_.async_get_simple_earn_locked_product_list(
            params, std::forward<CompletionToken>(token));
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
    redeem_flexible_product(const RedeemFlexibleProductParams& params) const {
        return flexible_locked_api_.redeem_flexible_product(params);
    }
    /// Asynchronous `redeem_flexible_product()`.
    template <class CompletionToken>
    auto async_redeem_flexible_product(const RedeemFlexibleProductParams& params,
                                       CompletionToken&& token) const {
        return flexible_locked_api_.async_redeem_flexible_product(
            params, std::forward<CompletionToken>(token));
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
    redeem_locked_product(const RedeemLockedProductParams& params) const {
        return flexible_locked_api_.redeem_locked_product(params);
    }
    /// Asynchronous `redeem_locked_product()`.
    template <class CompletionToken>
    auto async_redeem_locked_product(const RedeemLockedProductParams& params,
                                     CompletionToken&& token) const {
        return flexible_locked_api_.async_redeem_locked_product(
            params, std::forward<CompletionToken>(token));
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
    set_flexible_auto_subscribe(const SetFlexibleAutoSubscribeParams& params) const {
        return flexible_locked_api_.set_flexible_auto_subscribe(params);
    }
    /// Asynchronous `set_flexible_auto_subscribe()`.
    template <class CompletionToken>
    auto async_set_flexible_auto_subscribe(const SetFlexibleAutoSubscribeParams& params,
                                           CompletionToken&& token) const {
        return flexible_locked_api_.async_set_flexible_auto_subscribe(
            params, std::forward<CompletionToken>(token));
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
    set_locked_auto_subscribe(const SetLockedAutoSubscribeParams& params) const {
        return flexible_locked_api_.set_locked_auto_subscribe(params);
    }
    /// Asynchronous `set_locked_auto_subscribe()`.
    template <class CompletionToken>
    auto async_set_locked_auto_subscribe(const SetLockedAutoSubscribeParams& params,
                                         CompletionToken&& token) const {
        return flexible_locked_api_.async_set_locked_auto_subscribe(
            params, std::forward<CompletionToken>(token));
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
    set_locked_product_redeem_option(const SetLockedProductRedeemOptionParams& params) const {
        return flexible_locked_api_.set_locked_product_redeem_option(params);
    }
    /// Asynchronous `set_locked_product_redeem_option()`.
    template <class CompletionToken>
    auto async_set_locked_product_redeem_option(const SetLockedProductRedeemOptionParams& params,
                                                CompletionToken&& token) const {
        return flexible_locked_api_.async_set_locked_product_redeem_option(
            params, std::forward<CompletionToken>(token));
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
    simple_account(const SimpleAccountParams& params = {}) const {
        return flexible_locked_api_.simple_account(params);
    }
    /// Asynchronous `simple_account()`.
    template <class CompletionToken>
    auto async_simple_account(const SimpleAccountParams& params, CompletionToken&& token) const {
        return flexible_locked_api_.async_simple_account(params,
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
    subscribe_flexible_product(const SubscribeFlexibleProductParams& params) const {
        return flexible_locked_api_.subscribe_flexible_product(params);
    }
    /// Asynchronous `subscribe_flexible_product()`.
    template <class CompletionToken>
    auto async_subscribe_flexible_product(const SubscribeFlexibleProductParams& params,
                                          CompletionToken&& token) const {
        return flexible_locked_api_.async_subscribe_flexible_product(
            params, std::forward<CompletionToken>(token));
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
    subscribe_locked_product(const SubscribeLockedProductParams& params) const {
        return flexible_locked_api_.subscribe_locked_product(params);
    }
    /// Asynchronous `subscribe_locked_product()`.
    template <class CompletionToken>
    auto async_subscribe_locked_product(const SubscribeLockedProductParams& params,
                                        CompletionToken&& token) const {
        return flexible_locked_api_.async_subscribe_locked_product(
            params, std::forward<CompletionToken>(token));
    }

    // RwusdApi

    /// Get RWUSD Account (USER_DATA)
    ///
    /// GET /sapi/v1/rwusd/account.
    ///
    /// Get RWUSD account information.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/rwusd#get-rwusd-account
    [[nodiscard]] common::RestApiResponse<GetRwusdAccountResponse>
    get_rwusd_account(const GetRwusdAccountParams& params = {}) const {
        return rwusd_api_.get_rwusd_account(params);
    }
    /// Asynchronous `get_rwusd_account()`.
    template <class CompletionToken>
    auto async_get_rwusd_account(const GetRwusdAccountParams& params,
                                 CompletionToken&& token) const {
        return rwusd_api_.async_get_rwusd_account(params, std::forward<CompletionToken>(token));
    }

    /// Get RWUSD Quota Details (USER_DATA)
    ///
    /// GET /sapi/v1/rwusd/quota.
    ///
    /// Get RWUSD quota details including subscription quota, fast redemption quota, and standard
    /// redemption quota.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/rwusd#get-rwusd-quota-details
    [[nodiscard]] common::RestApiResponse<GetRwusdQuotaDetailsResponse>
    get_rwusd_quota_details(const GetRwusdQuotaDetailsParams& params = {}) const {
        return rwusd_api_.get_rwusd_quota_details(params);
    }
    /// Asynchronous `get_rwusd_quota_details()`.
    template <class CompletionToken>
    auto async_get_rwusd_quota_details(const GetRwusdQuotaDetailsParams& params,
                                       CompletionToken&& token) const {
        return rwusd_api_.async_get_rwusd_quota_details(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Get RWUSD Rate History (USER_DATA)
    ///
    /// GET /sapi/v1/rwusd/history/rateHistory.
    ///
    /// Get RWUSD rate history sorted by descending order.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 6 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, `endTime` will default to current time, and results from `startTime` onward will be
    ///   returned.
    /// - If
    ///   `endTime` is sent but `startTime` is not sent, `startTime` defaults to the current time
    ///   minus one month, and data between `startTime` and `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/rwusd#get-rwusd-rate-history
    [[nodiscard]] common::RestApiResponse<GetRwusdRateHistoryResponse>
    get_rwusd_rate_history(const GetRwusdRateHistoryParams& params = {}) const {
        return rwusd_api_.get_rwusd_rate_history(params);
    }
    /// Asynchronous `get_rwusd_rate_history()`.
    template <class CompletionToken>
    auto async_get_rwusd_rate_history(const GetRwusdRateHistoryParams& params,
                                      CompletionToken&& token) const {
        return rwusd_api_.async_get_rwusd_rate_history(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Get RWUSD Redemption History (USER_DATA)
    ///
    /// GET /sapi/v1/rwusd/history/redemptionHistory.
    ///
    /// Get RWUSD redemption history.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 6 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, `endTime` will default to current time, and results from `startTime` onward will be
    ///   returned.
    /// - If
    ///   `endTime` is sent but `startTime` is not sent, `startTime` defaults to the current time
    ///   minus one month, and data between `startTime` and `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/rwusd#get-rwusd-redemption-history
    [[nodiscard]] common::RestApiResponse<GetRwusdRedemptionHistoryResponse>
    get_rwusd_redemption_history(const GetRwusdRedemptionHistoryParams& params = {}) const {
        return rwusd_api_.get_rwusd_redemption_history(params);
    }
    /// Asynchronous `get_rwusd_redemption_history()`.
    template <class CompletionToken>
    auto async_get_rwusd_redemption_history(const GetRwusdRedemptionHistoryParams& params,
                                            CompletionToken&& token) const {
        return rwusd_api_.async_get_rwusd_redemption_history(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Get RWUSD Rewards History (USER_DATA)
    ///
    /// GET /sapi/v1/rwusd/history/rewardsHistory.
    ///
    /// Get RWUSD rewards history.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 6 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, `endTime` will default to current time, and results from `startTime` onward will be
    ///   returned.
    /// - If
    ///   `endTime` is sent but `startTime` is not sent, `startTime` defaults to the current time
    ///   minus one month, and data between `startTime` and `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/rwusd#get-rwusd-rewards-history
    [[nodiscard]] common::RestApiResponse<GetRwusdRewardsHistoryResponse>
    get_rwusd_rewards_history(const GetRwusdRewardsHistoryParams& params = {}) const {
        return rwusd_api_.get_rwusd_rewards_history(params);
    }
    /// Asynchronous `get_rwusd_rewards_history()`.
    template <class CompletionToken>
    auto async_get_rwusd_rewards_history(const GetRwusdRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return rwusd_api_.async_get_rwusd_rewards_history(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Get RWUSD subscription history (USER_DATA)
    ///
    /// GET /sapi/v1/rwusd/history/subscriptionHistory.
    ///
    /// Get RWUSD subscription history
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The time between `startTime` and `endTime` cannot be longer than 6 months.
    /// - If `startTime` and `endTime`
    ///   are both not sent, then the last 30 days' data will be returned.
    /// - If `startTime` is sent but `endTime` is not
    ///   sent, `endTime` will default to current time, and results from `startTime` onward will be
    ///   returned.
    /// - If
    ///   `endTime` is sent but `startTime` is not sent, `startTime` defaults to the current time
    ///   advanced by one month, and data between `startTime` and `endTime` will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/rwusd#get-rwusd-subscription-history
    [[nodiscard]] common::RestApiResponse<GetRwusdSubscriptionHistoryResponse>
    get_rwusd_subscription_history(const GetRwusdSubscriptionHistoryParams& params = {}) const {
        return rwusd_api_.get_rwusd_subscription_history(params);
    }
    /// Asynchronous `get_rwusd_subscription_history()`.
    template <class CompletionToken>
    auto async_get_rwusd_subscription_history(const GetRwusdSubscriptionHistoryParams& params,
                                              CompletionToken&& token) const {
        return rwusd_api_.async_get_rwusd_subscription_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Redeem RWUSD (TRADE)
    ///
    /// POST /sapi/v1/rwusd/redeem.
    ///
    /// Redeem RWUSD to USDC
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    /// - This API only supports RWUSD redemption to the Spot Account. Redemptions to the Funding
    /// Account or any other account type are not supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/rwusd#redeem-rwusd
    [[nodiscard]] common::RestApiResponse<RedeemRwusdResponse>
    redeem_rwusd(const RedeemRwusdParams& params) const {
        return rwusd_api_.redeem_rwusd(params);
    }
    /// Asynchronous `redeem_rwusd()`.
    template <class CompletionToken>
    auto async_redeem_rwusd(const RedeemRwusdParams& params, CompletionToken&& token) const {
        return rwusd_api_.async_redeem_rwusd(params, std::forward<CompletionToken>(token));
    }

    /// Subscribe RWUSD (TRADE)
    ///
    /// POST /sapi/v1/rwusd/subscribe.
    ///
    /// Subscribe RWUSD
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    /// - This API only supports RWUSD subscription using assets held in the Spot Account.
    /// Subscriptions initiated from the Funding Account or any other account type are not
    /// supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/rwusd#subscribe-rwusd
    [[nodiscard]] common::RestApiResponse<SubscribeRwusdResponse>
    subscribe_rwusd(const SubscribeRwusdParams& params) const {
        return rwusd_api_.subscribe_rwusd(params);
    }
    /// Asynchronous `subscribe_rwusd()`.
    template <class CompletionToken>
    auto async_subscribe_rwusd(const SubscribeRwusdParams& params, CompletionToken&& token) const {
        return rwusd_api_.async_subscribe_rwusd(params, std::forward<CompletionToken>(token));
    }

    // YieldArenaApi

    /// Get Yield Arena Activities (USER_DATA)
    ///
    /// GET /sapi/v1/earn/arena/activities.
    ///
    /// Get the list of Earn Yield Arena giveaway activities currently available to the user.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/yield-arena#get-yield-arena-activities
    [[nodiscard]] common::RestApiResponse<GetYieldArenaActivitiesResponse>
    get_yield_arena_activities(const GetYieldArenaActivitiesParams& params = {}) const {
        return yield_arena_api_.get_yield_arena_activities(params);
    }
    /// Asynchronous `get_yield_arena_activities()`.
    template <class CompletionToken>
    auto async_get_yield_arena_activities(const GetYieldArenaActivitiesParams& params,
                                          CompletionToken&& token) const {
        return yield_arena_api_.async_get_yield_arena_activities(
            params, std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::RestRequest make_request(std::string endpoint,
                                                          common::HttpMethod method,
                                                          common::Params query, common::Params body,
                                                          bool is_signed) {
        common::RestRequest req;
        req.method = method;
        req.endpoint = std::move(endpoint);
        req.query = std::move(query);
        req.body = std::move(body);
        req.is_signed = is_signed;
        return req;
    }

    std::shared_ptr<common::RestClient> client_;
    BfusdApi bfusd_api_;
    FlexibleLockedApi flexible_locked_api_;
    RwusdApi rwusd_api_;
    YieldArenaApi yield_arena_api_;
};

} // namespace binance::simple_earn::rest_api
