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
#include <string_view>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_account_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_rate_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_redemption_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_rewards_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_subscription_history_response.hpp>
#include <binance/simple_earn/rest_api/models/redeem_rwusd_response.hpp>
#include <binance/simple_earn/rest_api/models/subscribe_rwusd_response.hpp>

namespace binance::simple_earn::rest_api {

enum class GetRwusdSubscriptionHistoryAssetEnum {
    Usdc,
    Usdt,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(GetRwusdSubscriptionHistoryAssetEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT GetRwusdSubscriptionHistoryAssetEnum
tag_invoke(boost::json::value_to_tag<GetRwusdSubscriptionHistoryAssetEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           GetRwusdSubscriptionHistoryAssetEnum value);

enum class RedeemRwusdTypeEnum {
    Fast,
    Standard,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(RedeemRwusdTypeEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT RedeemRwusdTypeEnum
tag_invoke(boost::json::value_to_tag<RedeemRwusdTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv, RedeemRwusdTypeEnum value);

enum class SubscribeRwusdAssetEnum {
    Usdt,
    Usdc,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(SubscribeRwusdAssetEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT SubscribeRwusdAssetEnum tag_invoke(
    boost::json::value_to_tag<SubscribeRwusdAssetEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv, SubscribeRwusdAssetEnum value);

struct GetRwusdAccountParams {
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetRwusdQuotaDetailsParams {
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetRwusdRateHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetRwusdRedemptionHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetRwusdRewardsHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetRwusdSubscriptionHistoryParams {
    std::optional<GetRwusdSubscriptionHistoryAssetEnum> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000 (ms)
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RedeemRwusdParams {
    /// Amount in RWUSD
    common::Required<common::Decimal> amount;
    common::Required<RedeemRwusdTypeEnum> type;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubscribeRwusdParams {
    common::Required<SubscribeRwusdAssetEnum> asset;
    /// Amount
    common::Required<common::Decimal> amount;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_SIMPLE_EARN_EXPORT RwusdApi {
public:
    explicit RwusdApi(std::shared_ptr<common::RestClient> client);

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
    get_rwusd_account(const GetRwusdAccountParams& params = {}) const;

    /// Asynchronous `get_rwusd_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetRwusdAccountResponse>)`.
    template <class CompletionToken>
    auto async_get_rwusd_account(const GetRwusdAccountParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<GetRwusdAccountResponse>(
            client_, get_rwusd_account_request(params), std::forward<CompletionToken>(token));
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
    get_rwusd_quota_details(const GetRwusdQuotaDetailsParams& params = {}) const;

    /// Asynchronous `get_rwusd_quota_details()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetRwusdQuotaDetailsResponse>)`.
    template <class CompletionToken>
    auto async_get_rwusd_quota_details(const GetRwusdQuotaDetailsParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<GetRwusdQuotaDetailsResponse>(
            client_, get_rwusd_quota_details_request(params), std::forward<CompletionToken>(token));
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
    get_rwusd_rate_history(const GetRwusdRateHistoryParams& params = {}) const;

    /// Asynchronous `get_rwusd_rate_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetRwusdRateHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_rwusd_rate_history(const GetRwusdRateHistoryParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<GetRwusdRateHistoryResponse>(
            client_, get_rwusd_rate_history_request(params), std::forward<CompletionToken>(token));
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
    get_rwusd_redemption_history(const GetRwusdRedemptionHistoryParams& params = {}) const;

    /// Asynchronous `get_rwusd_redemption_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetRwusdRedemptionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_rwusd_redemption_history(const GetRwusdRedemptionHistoryParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<GetRwusdRedemptionHistoryResponse>(
            client_, get_rwusd_redemption_history_request(params),
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
    get_rwusd_rewards_history(const GetRwusdRewardsHistoryParams& params = {}) const;

    /// Asynchronous `get_rwusd_rewards_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetRwusdRewardsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_rwusd_rewards_history(const GetRwusdRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetRwusdRewardsHistoryResponse>(
            client_, get_rwusd_rewards_history_request(params),
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
    get_rwusd_subscription_history(const GetRwusdSubscriptionHistoryParams& params = {}) const;

    /// Asynchronous `get_rwusd_subscription_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetRwusdSubscriptionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_rwusd_subscription_history(const GetRwusdSubscriptionHistoryParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetRwusdSubscriptionHistoryResponse>(
            client_, get_rwusd_subscription_history_request(params),
            std::forward<CompletionToken>(token));
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
    redeem_rwusd(const RedeemRwusdParams& params) const;

    /// Asynchronous `redeem_rwusd()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RedeemRwusdResponse>)`.
    template <class CompletionToken>
    auto async_redeem_rwusd(const RedeemRwusdParams& params, CompletionToken&& token) const {
        return common::async_send<RedeemRwusdResponse>(client_, redeem_rwusd_request(params),
                                                       std::forward<CompletionToken>(token));
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
    subscribe_rwusd(const SubscribeRwusdParams& params) const;

    /// Asynchronous `subscribe_rwusd()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubscribeRwusdResponse>)`.
    template <class CompletionToken>
    auto async_subscribe_rwusd(const SubscribeRwusdParams& params, CompletionToken&& token) const {
        return common::async_send<SubscribeRwusdResponse>(client_, subscribe_rwusd_request(params),
                                                          std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_rwusd_account_request(const GetRwusdAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    get_rwusd_quota_details_request(const GetRwusdQuotaDetailsParams& params) const;
    [[nodiscard]] common::RestRequest
    get_rwusd_rate_history_request(const GetRwusdRateHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_rwusd_redemption_history_request(const GetRwusdRedemptionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_rwusd_rewards_history_request(const GetRwusdRewardsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_rwusd_subscription_history_request(const GetRwusdSubscriptionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest redeem_rwusd_request(const RedeemRwusdParams& params) const;
    [[nodiscard]] common::RestRequest
    subscribe_rwusd_request(const SubscribeRwusdParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::simple_earn::rest_api
