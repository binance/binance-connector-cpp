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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/models/claim_boost_rewards_response.hpp>
#include <binance/staking/rest_api/models/get_bnsol_rate_history_response.hpp>
#include <binance/staking/rest_api/models/get_bnsol_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/get_boost_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/get_sol_redemption_history_response.hpp>
#include <binance/staking/rest_api/models/get_sol_staking_history_response.hpp>
#include <binance/staking/rest_api/models/get_sol_staking_quota_details_response.hpp>
#include <binance/staking/rest_api/models/get_unclaimed_rewards_response_inner.hpp>
#include <binance/staking/rest_api/models/redeem_sol_response.hpp>
#include <binance/staking/rest_api/models/sol_staking_account_response.hpp>
#include <binance/staking/rest_api/models/subscribe_sol_staking_response.hpp>

namespace binance::staking::rest_api {

enum class GetBoostRewardsHistoryTypeEnum {
    Claim,
    Distribute,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STAKING_EXPORT std::string_view
to_string(GetBoostRewardsHistoryTypeEnum value) noexcept;
BINANCE_STAKING_EXPORT GetBoostRewardsHistoryTypeEnum
tag_invoke(boost::json::value_to_tag<GetBoostRewardsHistoryTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       GetBoostRewardsHistoryTypeEnum value);

struct ClaimBoostRewardsParams {
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBnsolRateHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBnsolRewardsHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBoostRewardsHistoryParams {
    common::Required<GetBoostRewardsHistoryTypeEnum> type;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSolRedemptionHistoryParams {
    std::optional<std::int64_t> redeem_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSolStakingHistoryParams {
    std::optional<std::int64_t> purchase_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSolStakingQuotaDetailsParams {
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUnclaimedRewardsParams {
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RedeemSolParams {
    /// Amount in BNSOL, limit 8 decimals
    common::Required<common::Decimal> amount;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SolStakingAccountParams {
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubscribeSolStakingParams {
    /// Amount in SOL.
    common::Required<common::Decimal> amount;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STAKING_EXPORT SolStakingApi {
public:
    explicit SolStakingApi(std::shared_ptr<common::RestClient> client);

    /// Claim Boost Rewards (TRADE)
    ///
    /// POST /sapi/v1/sol-staking/sol/claim.
    ///
    /// Claim Boost APR Airdrop Rewards
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#claim-boost-rewards
    [[nodiscard]] common::RestApiResponse<ClaimBoostRewardsResponse>
    claim_boost_rewards(const ClaimBoostRewardsParams& params = {}) const;

    /// Asynchronous `claim_boost_rewards()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ClaimBoostRewardsResponse>)`.
    template <class CompletionToken>
    auto async_claim_boost_rewards(const ClaimBoostRewardsParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<ClaimBoostRewardsResponse>(
            client_, claim_boost_rewards_request(params), std::forward<CompletionToken>(token));
    }

    /// Get BNSOL Rate History (USER_DATA)
    ///
    /// GET /sapi/v1/sol-staking/sol/history/rateHistory.
    ///
    /// Get BNSOL Rate History
    ///
    /// Weight(IP): 150
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#get-bnsol-rate-history
    [[nodiscard]] common::RestApiResponse<GetBnsolRateHistoryResponse>
    get_bnsol_rate_history(const GetBnsolRateHistoryParams& params = {}) const;

    /// Asynchronous `get_bnsol_rate_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBnsolRateHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_bnsol_rate_history(const GetBnsolRateHistoryParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<GetBnsolRateHistoryResponse>(
            client_, get_bnsol_rate_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Get BNSOL rewards history (USER_DATA)
    ///
    /// GET /sapi/v1/sol-staking/sol/history/bnsolRewardsHistory.
    ///
    /// Get BNSOL rewards history
    ///
    /// Weight(IP): 150
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#get-bnsol-rewards-history
    [[nodiscard]] common::RestApiResponse<GetBnsolRewardsHistoryResponse>
    get_bnsol_rewards_history(const GetBnsolRewardsHistoryParams& params = {}) const;

    /// Asynchronous `get_bnsol_rewards_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBnsolRewardsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_bnsol_rewards_history(const GetBnsolRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetBnsolRewardsHistoryResponse>(
            client_, get_bnsol_rewards_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Boost Rewards History (USER_DATA)
    ///
    /// GET /sapi/v1/sol-staking/sol/history/boostRewardsHistory.
    ///
    /// Get Boost rewards history
    ///
    /// Weight(IP): 150
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#get-boost-rewards-history
    [[nodiscard]] common::RestApiResponse<GetBoostRewardsHistoryResponse>
    get_boost_rewards_history(const GetBoostRewardsHistoryParams& params) const;

    /// Asynchronous `get_boost_rewards_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBoostRewardsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_boost_rewards_history(const GetBoostRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetBoostRewardsHistoryResponse>(
            client_, get_boost_rewards_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get SOL redemption history (USER_DATA)
    ///
    /// GET /sapi/v1/sol-staking/sol/history/redemptionHistory.
    ///
    /// Get SOL redemption history
    ///
    /// Weight(IP): 150
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#get-sol-redemption-history
    [[nodiscard]] common::RestApiResponse<GetSolRedemptionHistoryResponse>
    get_sol_redemption_history(const GetSolRedemptionHistoryParams& params = {}) const;

    /// Asynchronous `get_sol_redemption_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetSolRedemptionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_sol_redemption_history(const GetSolRedemptionHistoryParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<GetSolRedemptionHistoryResponse>(
            client_, get_sol_redemption_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get SOL staking history (USER_DATA)
    ///
    /// GET /sapi/v1/sol-staking/sol/history/stakingHistory.
    ///
    /// Get SOL staking history
    ///
    /// Weight(IP): 150
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#get-sol-staking-history
    [[nodiscard]] common::RestApiResponse<GetSolStakingHistoryResponse>
    get_sol_staking_history(const GetSolStakingHistoryParams& params = {}) const;

    /// Asynchronous `get_sol_staking_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetSolStakingHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_sol_staking_history(const GetSolStakingHistoryParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<GetSolStakingHistoryResponse>(
            client_, get_sol_staking_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Get SOL staking quota details (USER_DATA)
    ///
    /// GET /sapi/v1/sol-staking/sol/quota.
    ///
    /// Get SOL staking quota
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#get-sol-staking-quota-details
    [[nodiscard]] common::RestApiResponse<GetSolStakingQuotaDetailsResponse>
    get_sol_staking_quota_details(const GetSolStakingQuotaDetailsParams& params = {}) const;

    /// Asynchronous `get_sol_staking_quota_details()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetSolStakingQuotaDetailsResponse>)`.
    template <class CompletionToken>
    auto async_get_sol_staking_quota_details(const GetSolStakingQuotaDetailsParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetSolStakingQuotaDetailsResponse>(
            client_, get_sol_staking_quota_details_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Unclaimed Rewards (USER_DATA)
    ///
    /// GET /sapi/v1/sol-staking/sol/history/unclaimedRewards.
    ///
    /// Get Unclaimed rewards
    ///
    /// Weight(IP): 150
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#get-unclaimed-rewards
    [[nodiscard]] common::RestApiResponse<std::vector<GetUnclaimedRewardsResponseInner>>
    get_unclaimed_rewards(const GetUnclaimedRewardsParams& params = {}) const;

    /// Asynchronous `get_unclaimed_rewards()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetUnclaimedRewardsResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_unclaimed_rewards(const GetUnclaimedRewardsParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<GetUnclaimedRewardsResponseInner>>(
            client_, get_unclaimed_rewards_request(params), std::forward<CompletionToken>(token));
    }

    /// Redeem SOL (TRADE)
    ///
    /// POST /sapi/v1/sol-staking/sol/redeem.
    ///
    /// Redeem BNSOL get SOL
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#redeem-sol
    [[nodiscard]] common::RestApiResponse<RedeemSolResponse>
    redeem_sol(const RedeemSolParams& params) const;

    /// Asynchronous `redeem_sol()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RedeemSolResponse>)`.
    template <class CompletionToken>
    auto async_redeem_sol(const RedeemSolParams& params, CompletionToken&& token) const {
        return common::async_send<RedeemSolResponse>(client_, redeem_sol_request(params),
                                                     std::forward<CompletionToken>(token));
    }

    /// SOL Staking account (USER_DATA)
    ///
    /// GET /sapi/v1/sol-staking/account.
    ///
    /// SOL Staking account
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#sol-staking-account
    [[nodiscard]] common::RestApiResponse<SolStakingAccountResponse>
    sol_staking_account(const SolStakingAccountParams& params = {}) const;

    /// Asynchronous `sol_staking_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SolStakingAccountResponse>)`.
    template <class CompletionToken>
    auto async_sol_staking_account(const SolStakingAccountParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<SolStakingAccountResponse>(
            client_, sol_staking_account_request(params), std::forward<CompletionToken>(token));
    }

    /// Subscribe SOL Staking (TRADE)
    ///
    /// POST /sapi/v1/sol-staking/sol/stake.
    ///
    /// Subscribe SOL Staking
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/sol-staking#subscribe-sol-staking
    [[nodiscard]] common::RestApiResponse<SubscribeSolStakingResponse>
    subscribe_sol_staking(const SubscribeSolStakingParams& params) const;

    /// Asynchronous `subscribe_sol_staking()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubscribeSolStakingResponse>)`.
    template <class CompletionToken>
    auto async_subscribe_sol_staking(const SubscribeSolStakingParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<SubscribeSolStakingResponse>(
            client_, subscribe_sol_staking_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    claim_boost_rewards_request(const ClaimBoostRewardsParams& params) const;
    [[nodiscard]] common::RestRequest
    get_bnsol_rate_history_request(const GetBnsolRateHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_bnsol_rewards_history_request(const GetBnsolRewardsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_boost_rewards_history_request(const GetBoostRewardsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_sol_redemption_history_request(const GetSolRedemptionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_sol_staking_history_request(const GetSolStakingHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_sol_staking_quota_details_request(const GetSolStakingQuotaDetailsParams& params) const;
    [[nodiscard]] common::RestRequest
    get_unclaimed_rewards_request(const GetUnclaimedRewardsParams& params) const;
    [[nodiscard]] common::RestRequest redeem_sol_request(const RedeemSolParams& params) const;
    [[nodiscard]] common::RestRequest
    sol_staking_account_request(const SolStakingAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    subscribe_sol_staking_request(const SubscribeSolStakingParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::staking::rest_api
