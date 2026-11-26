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
#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_account_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_rate_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_redemption_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_rewards_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_subscription_history_response.hpp>
#include <binance/simple_earn/rest_api/models/redeem_bfusd_response.hpp>
#include <binance/simple_earn/rest_api/models/subscribe_bfusd_response.hpp>

namespace binance::simple_earn::rest_api {

enum class GetBfusdSubscriptionHistoryAssetEnum {
    Usdc,
    Usdt,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(GetBfusdSubscriptionHistoryAssetEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT GetBfusdSubscriptionHistoryAssetEnum
tag_invoke(boost::json::value_to_tag<GetBfusdSubscriptionHistoryAssetEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           GetBfusdSubscriptionHistoryAssetEnum value);

enum class RedeemBfusdTypeEnum {
    Fast,
    Standard,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SIMPLE_EARN_EXPORT std::string_view
to_string(RedeemBfusdTypeEnum value) noexcept;
BINANCE_SIMPLE_EARN_EXPORT RedeemBfusdTypeEnum
tag_invoke(boost::json::value_to_tag<RedeemBfusdTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv, RedeemBfusdTypeEnum value);

struct GetBfusdAccountParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBfusdQuotaDetailsParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBfusdRateHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page. Starts from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBfusdRedemptionHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBfusdRewardsHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBfusdSubscriptionHistoryParams {
    std::optional<GetBfusdSubscriptionHistoryAssetEnum> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results per page.
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RedeemBfusdParams {
    /// Amount in BFUSD
    common::Required<common::Decimal> amount;
    /// defaults to STANDARD
    common::Required<RedeemBfusdTypeEnum> type;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubscribeBfusdParams {
    common::Required<std::string> asset;
    /// Amount
    common::Required<common::Decimal> amount;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_SIMPLE_EARN_EXPORT BfusdApi {
public:
    explicit BfusdApi(std::shared_ptr<common::RestClient> client);

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
    get_bfusd_account(const GetBfusdAccountParams& params = {}) const;

    /// Asynchronous `get_bfusd_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBfusdAccountResponse>)`.
    template <class CompletionToken>
    auto async_get_bfusd_account(const GetBfusdAccountParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<GetBfusdAccountResponse>(
            client_, get_bfusd_account_request(params), std::forward<CompletionToken>(token));
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
    get_bfusd_quota_details(const GetBfusdQuotaDetailsParams& params = {}) const;

    /// Asynchronous `get_bfusd_quota_details()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBfusdQuotaDetailsResponse>)`.
    template <class CompletionToken>
    auto async_get_bfusd_quota_details(const GetBfusdQuotaDetailsParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<GetBfusdQuotaDetailsResponse>(
            client_, get_bfusd_quota_details_request(params), std::forward<CompletionToken>(token));
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
    get_bfusd_rate_history(const GetBfusdRateHistoryParams& params = {}) const;

    /// Asynchronous `get_bfusd_rate_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBfusdRateHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_bfusd_rate_history(const GetBfusdRateHistoryParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<GetBfusdRateHistoryResponse>(
            client_, get_bfusd_rate_history_request(params), std::forward<CompletionToken>(token));
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
    get_bfusd_redemption_history(const GetBfusdRedemptionHistoryParams& params = {}) const;

    /// Asynchronous `get_bfusd_redemption_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBfusdRedemptionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_bfusd_redemption_history(const GetBfusdRedemptionHistoryParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<GetBfusdRedemptionHistoryResponse>(
            client_, get_bfusd_redemption_history_request(params),
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
    get_bfusd_rewards_history(const GetBfusdRewardsHistoryParams& params = {}) const;

    /// Asynchronous `get_bfusd_rewards_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBfusdRewardsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_bfusd_rewards_history(const GetBfusdRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetBfusdRewardsHistoryResponse>(
            client_, get_bfusd_rewards_history_request(params),
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
    get_bfusd_subscription_history(const GetBfusdSubscriptionHistoryParams& params = {}) const;

    /// Asynchronous `get_bfusd_subscription_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBfusdSubscriptionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_bfusd_subscription_history(const GetBfusdSubscriptionHistoryParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetBfusdSubscriptionHistoryResponse>(
            client_, get_bfusd_subscription_history_request(params),
            std::forward<CompletionToken>(token));
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
    redeem_bfusd(const RedeemBfusdParams& params) const;

    /// Asynchronous `redeem_bfusd()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RedeemBfusdResponse>)`.
    template <class CompletionToken>
    auto async_redeem_bfusd(const RedeemBfusdParams& params, CompletionToken&& token) const {
        return common::async_send<RedeemBfusdResponse>(client_, redeem_bfusd_request(params),
                                                       std::forward<CompletionToken>(token));
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
    subscribe_bfusd(const SubscribeBfusdParams& params) const;

    /// Asynchronous `subscribe_bfusd()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubscribeBfusdResponse>)`.
    template <class CompletionToken>
    auto async_subscribe_bfusd(const SubscribeBfusdParams& params, CompletionToken&& token) const {
        return common::async_send<SubscribeBfusdResponse>(client_, subscribe_bfusd_request(params),
                                                          std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_bfusd_account_request(const GetBfusdAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    get_bfusd_quota_details_request(const GetBfusdQuotaDetailsParams& params) const;
    [[nodiscard]] common::RestRequest
    get_bfusd_rate_history_request(const GetBfusdRateHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_bfusd_redemption_history_request(const GetBfusdRedemptionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_bfusd_rewards_history_request(const GetBfusdRewardsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_bfusd_subscription_history_request(const GetBfusdSubscriptionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest redeem_bfusd_request(const RedeemBfusdParams& params) const;
    [[nodiscard]] common::RestRequest
    subscribe_bfusd_request(const SubscribeBfusdParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::simple_earn::rest_api
