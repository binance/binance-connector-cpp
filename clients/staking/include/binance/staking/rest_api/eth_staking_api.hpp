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
#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/models/eth_staking_account_response.hpp>
#include <binance/staking/rest_api/models/get_current_eth_staking_quota_response.hpp>
#include <binance/staking/rest_api/models/get_eth_redemption_history_response.hpp>
#include <binance/staking/rest_api/models/get_eth_staking_history_response.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rate_history_response.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/get_wbeth_unwrap_history_response.hpp>
#include <binance/staking/rest_api/models/get_wbeth_wrap_history_response.hpp>
#include <binance/staking/rest_api/models/redeem_eth_response.hpp>
#include <binance/staking/rest_api/models/subscribe_eth_staking_response.hpp>
#include <binance/staking/rest_api/models/wrap_beth_response.hpp>

namespace binance::staking::rest_api {

enum class RedeemEthAssetEnum {
    Wbeth,
    Beth,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STAKING_EXPORT std::string_view to_string(RedeemEthAssetEnum value) noexcept;
BINANCE_STAKING_EXPORT RedeemEthAssetEnum
tag_invoke(boost::json::value_to_tag<RedeemEthAssetEnum> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       RedeemEthAssetEnum value);

struct EthStakingAccountParams {
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCurrentEthStakingQuotaParams {
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetEthRedemptionHistoryParams {
    std::optional<std::int64_t> redeem_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetEthStakingHistoryParams {
    std::optional<std::int64_t> purchase_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetWbethRateHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetWbethRewardsHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetWbethUnwrapHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetWbethWrapHistoryParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RedeemEthParams {
    /// Amount in BETH, limit 8 decimals
    common::Required<common::Decimal> amount;
    std::optional<RedeemEthAssetEnum> asset = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubscribeEthStakingParams {
    /// Amount in ETH, limit 4 decimals
    common::Required<common::Decimal> amount;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct WrapBethParams {
    /// Amount in BETH, limit 4 decimals
    common::Required<common::Decimal> amount;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STAKING_EXPORT EthStakingApi {
public:
    explicit EthStakingApi(std::shared_ptr<common::RestClient> client);

    /// ETH Staking account (USER_DATA)
    ///
    /// GET /sapi/v2/eth-staking/account.
    ///
    /// ETH Staking account
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#eth-staking-account
    [[nodiscard]] common::RestApiResponse<EthStakingAccountResponse>
    eth_staking_account(const EthStakingAccountParams& params = {}) const;

    /// Asynchronous `eth_staking_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<EthStakingAccountResponse>)`.
    template <class CompletionToken>
    auto async_eth_staking_account(const EthStakingAccountParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<EthStakingAccountResponse>(
            client_, eth_staking_account_request(params), std::forward<CompletionToken>(token));
    }

    /// Get current ETH staking quota (USER_DATA)
    ///
    /// GET /sapi/v1/eth-staking/eth/quota.
    ///
    /// Get current ETH staking quota
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#get-current-eth-staking-quota
    [[nodiscard]] common::RestApiResponse<GetCurrentEthStakingQuotaResponse>
    get_current_eth_staking_quota(const GetCurrentEthStakingQuotaParams& params = {}) const;

    /// Asynchronous `get_current_eth_staking_quota()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCurrentEthStakingQuotaResponse>)`.
    template <class CompletionToken>
    auto async_get_current_eth_staking_quota(const GetCurrentEthStakingQuotaParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetCurrentEthStakingQuotaResponse>(
            client_, get_current_eth_staking_quota_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get ETH redemption history (USER_DATA)
    ///
    /// GET /sapi/v1/eth-staking/eth/history/redemptionHistory.
    ///
    /// Get ETH redemption history
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#get-eth-redemption-history
    [[nodiscard]] common::RestApiResponse<GetEthRedemptionHistoryResponse>
    get_eth_redemption_history(const GetEthRedemptionHistoryParams& params = {}) const;

    /// Asynchronous `get_eth_redemption_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetEthRedemptionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_eth_redemption_history(const GetEthRedemptionHistoryParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<GetEthRedemptionHistoryResponse>(
            client_, get_eth_redemption_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get ETH staking history (USER_DATA)
    ///
    /// GET /sapi/v1/eth-staking/eth/history/stakingHistory.
    ///
    /// Get ETH staking history
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#get-eth-staking-history
    [[nodiscard]] common::RestApiResponse<GetEthStakingHistoryResponse>
    get_eth_staking_history(const GetEthStakingHistoryParams& params = {}) const;

    /// Asynchronous `get_eth_staking_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetEthStakingHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_eth_staking_history(const GetEthStakingHistoryParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<GetEthStakingHistoryResponse>(
            client_, get_eth_staking_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Get WBETH Rate History (USER_DATA)
    ///
    /// GET /sapi/v1/eth-staking/eth/history/rateHistory.
    ///
    /// Get WBETH Rate History
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#get-wbeth-rate-history
    [[nodiscard]] common::RestApiResponse<GetWbethRateHistoryResponse>
    get_wbeth_rate_history(const GetWbethRateHistoryParams& params = {}) const;

    /// Asynchronous `get_wbeth_rate_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetWbethRateHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_wbeth_rate_history(const GetWbethRateHistoryParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<GetWbethRateHistoryResponse>(
            client_, get_wbeth_rate_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Get WBETH rewards history (USER_DATA)
    ///
    /// GET /sapi/v1/eth-staking/eth/history/wbethRewardsHistory.
    ///
    /// Get WBETH rewards history
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#get-wbeth-rewards-history
    [[nodiscard]] common::RestApiResponse<GetWbethRewardsHistoryResponse>
    get_wbeth_rewards_history(const GetWbethRewardsHistoryParams& params = {}) const;

    /// Asynchronous `get_wbeth_rewards_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetWbethRewardsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_wbeth_rewards_history(const GetWbethRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetWbethRewardsHistoryResponse>(
            client_, get_wbeth_rewards_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get WBETH unwrap history (USER_DATA)
    ///
    /// GET /sapi/v1/eth-staking/wbeth/history/unwrapHistory.
    ///
    /// Get WBETH unwrap history
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#get-wbeth-unwrap-history
    [[nodiscard]] common::RestApiResponse<GetWbethUnwrapHistoryResponse>
    get_wbeth_unwrap_history(const GetWbethUnwrapHistoryParams& params = {}) const;

    /// Asynchronous `get_wbeth_unwrap_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetWbethUnwrapHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_wbeth_unwrap_history(const GetWbethUnwrapHistoryParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<GetWbethUnwrapHistoryResponse>(
            client_, get_wbeth_unwrap_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get WBETH wrap history (USER_DATA)
    ///
    /// GET /sapi/v1/eth-staking/wbeth/history/wrapHistory.
    ///
    /// Get WBETH wrap history
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#get-wbeth-wrap-history
    [[nodiscard]] common::RestApiResponse<GetWbethWrapHistoryResponse>
    get_wbeth_wrap_history(const GetWbethWrapHistoryParams& params = {}) const;

    /// Asynchronous `get_wbeth_wrap_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetWbethWrapHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_wbeth_wrap_history(const GetWbethWrapHistoryParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<GetWbethWrapHistoryResponse>(
            client_, get_wbeth_wrap_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Redeem ETH (TRADE)
    ///
    /// POST /sapi/v1/eth-staking/eth/redeem.
    ///
    /// Redeem WBETH or BETH and get ETH
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#redeem-eth
    [[nodiscard]] common::RestApiResponse<RedeemEthResponse>
    redeem_eth(const RedeemEthParams& params) const;

    /// Asynchronous `redeem_eth()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RedeemEthResponse>)`.
    template <class CompletionToken>
    auto async_redeem_eth(const RedeemEthParams& params, CompletionToken&& token) const {
        return common::async_send<RedeemEthResponse>(client_, redeem_eth_request(params),
                                                     std::forward<CompletionToken>(token));
    }

    /// Subscribe ETH Staking (TRADE)
    ///
    /// POST /sapi/v2/eth-staking/eth/stake.
    ///
    /// Subscribe ETH Staking
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#subscribe-eth-staking
    [[nodiscard]] common::RestApiResponse<SubscribeEthStakingResponse>
    subscribe_eth_staking(const SubscribeEthStakingParams& params) const;

    /// Asynchronous `subscribe_eth_staking()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubscribeEthStakingResponse>)`.
    template <class CompletionToken>
    auto async_subscribe_eth_staking(const SubscribeEthStakingParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<SubscribeEthStakingResponse>(
            client_, subscribe_eth_staking_request(params), std::forward<CompletionToken>(token));
    }

    /// Wrap BETH (TRADE)
    ///
    /// POST /sapi/v1/eth-staking/wbeth/wrap.
    ///
    /// Wrap BETH
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/eth-staking#wrap-beth
    [[nodiscard]] common::RestApiResponse<WrapBethResponse>
    wrap_beth(const WrapBethParams& params) const;

    /// Asynchronous `wrap_beth()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<WrapBethResponse>)`.
    template <class CompletionToken>
    auto async_wrap_beth(const WrapBethParams& params, CompletionToken&& token) const {
        return common::async_send<WrapBethResponse>(client_, wrap_beth_request(params),
                                                    std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    eth_staking_account_request(const EthStakingAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    get_current_eth_staking_quota_request(const GetCurrentEthStakingQuotaParams& params) const;
    [[nodiscard]] common::RestRequest
    get_eth_redemption_history_request(const GetEthRedemptionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_eth_staking_history_request(const GetEthStakingHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_wbeth_rate_history_request(const GetWbethRateHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_wbeth_rewards_history_request(const GetWbethRewardsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_wbeth_unwrap_history_request(const GetWbethUnwrapHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_wbeth_wrap_history_request(const GetWbethWrapHistoryParams& params) const;
    [[nodiscard]] common::RestRequest redeem_eth_request(const RedeemEthParams& params) const;
    [[nodiscard]] common::RestRequest
    subscribe_eth_staking_request(const SubscribeEthStakingParams& params) const;
    [[nodiscard]] common::RestRequest wrap_beth_request(const WrapBethParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::staking::rest_api
