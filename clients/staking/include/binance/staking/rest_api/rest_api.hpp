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
#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/eth_staking_api.hpp>
#include <binance/staking/rest_api/models.hpp>
#include <binance/staking/rest_api/on_chain_yields_api.hpp>
#include <binance/staking/rest_api/soft_staking_api.hpp>
#include <binance/staking/rest_api/sol_staking_api.hpp>

namespace binance::staking::rest_api {

/// Staking REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_STAKING_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Staking REST API).
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

    // EthStakingApi

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
    eth_staking_account(const EthStakingAccountParams& params = {}) const {
        return eth_staking_api_.eth_staking_account(params);
    }
    /// Asynchronous `eth_staking_account()`.
    template <class CompletionToken>
    auto async_eth_staking_account(const EthStakingAccountParams& params,
                                   CompletionToken&& token) const {
        return eth_staking_api_.async_eth_staking_account(params,
                                                          std::forward<CompletionToken>(token));
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
    get_current_eth_staking_quota(const GetCurrentEthStakingQuotaParams& params = {}) const {
        return eth_staking_api_.get_current_eth_staking_quota(params);
    }
    /// Asynchronous `get_current_eth_staking_quota()`.
    template <class CompletionToken>
    auto async_get_current_eth_staking_quota(const GetCurrentEthStakingQuotaParams& params,
                                             CompletionToken&& token) const {
        return eth_staking_api_.async_get_current_eth_staking_quota(
            params, std::forward<CompletionToken>(token));
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
    get_eth_redemption_history(const GetEthRedemptionHistoryParams& params = {}) const {
        return eth_staking_api_.get_eth_redemption_history(params);
    }
    /// Asynchronous `get_eth_redemption_history()`.
    template <class CompletionToken>
    auto async_get_eth_redemption_history(const GetEthRedemptionHistoryParams& params,
                                          CompletionToken&& token) const {
        return eth_staking_api_.async_get_eth_redemption_history(
            params, std::forward<CompletionToken>(token));
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
    get_eth_staking_history(const GetEthStakingHistoryParams& params = {}) const {
        return eth_staking_api_.get_eth_staking_history(params);
    }
    /// Asynchronous `get_eth_staking_history()`.
    template <class CompletionToken>
    auto async_get_eth_staking_history(const GetEthStakingHistoryParams& params,
                                       CompletionToken&& token) const {
        return eth_staking_api_.async_get_eth_staking_history(params,
                                                              std::forward<CompletionToken>(token));
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
    get_wbeth_rate_history(const GetWbethRateHistoryParams& params = {}) const {
        return eth_staking_api_.get_wbeth_rate_history(params);
    }
    /// Asynchronous `get_wbeth_rate_history()`.
    template <class CompletionToken>
    auto async_get_wbeth_rate_history(const GetWbethRateHistoryParams& params,
                                      CompletionToken&& token) const {
        return eth_staking_api_.async_get_wbeth_rate_history(params,
                                                             std::forward<CompletionToken>(token));
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
    get_wbeth_rewards_history(const GetWbethRewardsHistoryParams& params = {}) const {
        return eth_staking_api_.get_wbeth_rewards_history(params);
    }
    /// Asynchronous `get_wbeth_rewards_history()`.
    template <class CompletionToken>
    auto async_get_wbeth_rewards_history(const GetWbethRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return eth_staking_api_.async_get_wbeth_rewards_history(
            params, std::forward<CompletionToken>(token));
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
    get_wbeth_unwrap_history(const GetWbethUnwrapHistoryParams& params = {}) const {
        return eth_staking_api_.get_wbeth_unwrap_history(params);
    }
    /// Asynchronous `get_wbeth_unwrap_history()`.
    template <class CompletionToken>
    auto async_get_wbeth_unwrap_history(const GetWbethUnwrapHistoryParams& params,
                                        CompletionToken&& token) const {
        return eth_staking_api_.async_get_wbeth_unwrap_history(
            params, std::forward<CompletionToken>(token));
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
    get_wbeth_wrap_history(const GetWbethWrapHistoryParams& params = {}) const {
        return eth_staking_api_.get_wbeth_wrap_history(params);
    }
    /// Asynchronous `get_wbeth_wrap_history()`.
    template <class CompletionToken>
    auto async_get_wbeth_wrap_history(const GetWbethWrapHistoryParams& params,
                                      CompletionToken&& token) const {
        return eth_staking_api_.async_get_wbeth_wrap_history(params,
                                                             std::forward<CompletionToken>(token));
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
    redeem_eth(const RedeemEthParams& params) const {
        return eth_staking_api_.redeem_eth(params);
    }
    /// Asynchronous `redeem_eth()`.
    template <class CompletionToken>
    auto async_redeem_eth(const RedeemEthParams& params, CompletionToken&& token) const {
        return eth_staking_api_.async_redeem_eth(params, std::forward<CompletionToken>(token));
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
    subscribe_eth_staking(const SubscribeEthStakingParams& params) const {
        return eth_staking_api_.subscribe_eth_staking(params);
    }
    /// Asynchronous `subscribe_eth_staking()`.
    template <class CompletionToken>
    auto async_subscribe_eth_staking(const SubscribeEthStakingParams& params,
                                     CompletionToken&& token) const {
        return eth_staking_api_.async_subscribe_eth_staking(params,
                                                            std::forward<CompletionToken>(token));
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
    wrap_beth(const WrapBethParams& params) const {
        return eth_staking_api_.wrap_beth(params);
    }
    /// Asynchronous `wrap_beth()`.
    template <class CompletionToken>
    auto async_wrap_beth(const WrapBethParams& params, CompletionToken&& token) const {
        return eth_staking_api_.async_wrap_beth(params, std::forward<CompletionToken>(token));
    }

    // OnChainYieldsApi

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
        const GetOnChainYieldsLockedPersonalLeftQuotaParams& params) const {
        return on_chain_yields_api_.get_on_chain_yields_locked_personal_left_quota(params);
    }
    /// Asynchronous `get_on_chain_yields_locked_personal_left_quota()`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_personal_left_quota(
        const GetOnChainYieldsLockedPersonalLeftQuotaParams& params,
        CompletionToken&& token) const {
        return on_chain_yields_api_.async_get_on_chain_yields_locked_personal_left_quota(
            params, std::forward<CompletionToken>(token));
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
        const GetOnChainYieldsLockedProductListParams& params = {}) const {
        return on_chain_yields_api_.get_on_chain_yields_locked_product_list(params);
    }
    /// Asynchronous `get_on_chain_yields_locked_product_list()`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_product_list(
        const GetOnChainYieldsLockedProductListParams& params, CompletionToken&& token) const {
        return on_chain_yields_api_.async_get_on_chain_yields_locked_product_list(
            params, std::forward<CompletionToken>(token));
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
        const GetOnChainYieldsLockedProductPositionParams& params = {}) const {
        return on_chain_yields_api_.get_on_chain_yields_locked_product_position(params);
    }
    /// Asynchronous `get_on_chain_yields_locked_product_position()`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_product_position(
        const GetOnChainYieldsLockedProductPositionParams& params, CompletionToken&& token) const {
        return on_chain_yields_api_.async_get_on_chain_yields_locked_product_position(
            params, std::forward<CompletionToken>(token));
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
        const GetOnChainYieldsLockedRedemptionRecordParams& params = {}) const {
        return on_chain_yields_api_.get_on_chain_yields_locked_redemption_record(params);
    }
    /// Asynchronous `get_on_chain_yields_locked_redemption_record()`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_redemption_record(
        const GetOnChainYieldsLockedRedemptionRecordParams& params, CompletionToken&& token) const {
        return on_chain_yields_api_.async_get_on_chain_yields_locked_redemption_record(
            params, std::forward<CompletionToken>(token));
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
        const GetOnChainYieldsLockedRewardsHistoryParams& params = {}) const {
        return on_chain_yields_api_.get_on_chain_yields_locked_rewards_history(params);
    }
    /// Asynchronous `get_on_chain_yields_locked_rewards_history()`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_rewards_history(
        const GetOnChainYieldsLockedRewardsHistoryParams& params, CompletionToken&& token) const {
        return on_chain_yields_api_.async_get_on_chain_yields_locked_rewards_history(
            params, std::forward<CompletionToken>(token));
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
        const GetOnChainYieldsLockedSubscriptionPreviewParams& params) const {
        return on_chain_yields_api_.get_on_chain_yields_locked_subscription_preview(params);
    }
    /// Asynchronous `get_on_chain_yields_locked_subscription_preview()`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_subscription_preview(
        const GetOnChainYieldsLockedSubscriptionPreviewParams& params,
        CompletionToken&& token) const {
        return on_chain_yields_api_.async_get_on_chain_yields_locked_subscription_preview(
            params, std::forward<CompletionToken>(token));
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
        const GetOnChainYieldsLockedSubscriptionRecordParams& params = {}) const {
        return on_chain_yields_api_.get_on_chain_yields_locked_subscription_record(params);
    }
    /// Asynchronous `get_on_chain_yields_locked_subscription_record()`.
    template <class CompletionToken>
    auto async_get_on_chain_yields_locked_subscription_record(
        const GetOnChainYieldsLockedSubscriptionRecordParams& params,
        CompletionToken&& token) const {
        return on_chain_yields_api_.async_get_on_chain_yields_locked_subscription_record(
            params, std::forward<CompletionToken>(token));
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
    on_chain_yields_account(const OnChainYieldsAccountParams& params = {}) const {
        return on_chain_yields_api_.on_chain_yields_account(params);
    }
    /// Asynchronous `on_chain_yields_account()`.
    template <class CompletionToken>
    auto async_on_chain_yields_account(const OnChainYieldsAccountParams& params,
                                       CompletionToken&& token) const {
        return on_chain_yields_api_.async_on_chain_yields_account(
            params, std::forward<CompletionToken>(token));
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
        const RedeemOnChainYieldsLockedProductParams& params) const {
        return on_chain_yields_api_.redeem_on_chain_yields_locked_product(params);
    }
    /// Asynchronous `redeem_on_chain_yields_locked_product()`.
    template <class CompletionToken>
    auto async_redeem_on_chain_yields_locked_product(
        const RedeemOnChainYieldsLockedProductParams& params, CompletionToken&& token) const {
        return on_chain_yields_api_.async_redeem_on_chain_yields_locked_product(
            params, std::forward<CompletionToken>(token));
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
        const SetOnChainYieldsLockedAutoSubscribeParams& params) const {
        return on_chain_yields_api_.set_on_chain_yields_locked_auto_subscribe(params);
    }
    /// Asynchronous `set_on_chain_yields_locked_auto_subscribe()`.
    template <class CompletionToken>
    auto async_set_on_chain_yields_locked_auto_subscribe(
        const SetOnChainYieldsLockedAutoSubscribeParams& params, CompletionToken&& token) const {
        return on_chain_yields_api_.async_set_on_chain_yields_locked_auto_subscribe(
            params, std::forward<CompletionToken>(token));
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
        const SetOnChainYieldsLockedProductRedeemOptionParams& params) const {
        return on_chain_yields_api_.set_on_chain_yields_locked_product_redeem_option(params);
    }
    /// Asynchronous `set_on_chain_yields_locked_product_redeem_option()`.
    template <class CompletionToken>
    auto async_set_on_chain_yields_locked_product_redeem_option(
        const SetOnChainYieldsLockedProductRedeemOptionParams& params,
        CompletionToken&& token) const {
        return on_chain_yields_api_.async_set_on_chain_yields_locked_product_redeem_option(
            params, std::forward<CompletionToken>(token));
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
        const SubscribeOnChainYieldsLockedProductParams& params) const {
        return on_chain_yields_api_.subscribe_on_chain_yields_locked_product(params);
    }
    /// Asynchronous `subscribe_on_chain_yields_locked_product()`.
    template <class CompletionToken>
    auto async_subscribe_on_chain_yields_locked_product(
        const SubscribeOnChainYieldsLockedProductParams& params, CompletionToken&& token) const {
        return on_chain_yields_api_.async_subscribe_on_chain_yields_locked_product(
            params, std::forward<CompletionToken>(token));
    }

    // SoftStakingApi

    /// Get Soft Staking Product List (USER_DATA)
    ///
    /// GET /sapi/v1/soft-staking/list.
    ///
    /// Get the available Soft Staking product list.
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/soft-staking#get-soft-staking-product-list
    [[nodiscard]] common::RestApiResponse<GetSoftStakingProductListResponse>
    get_soft_staking_product_list(const GetSoftStakingProductListParams& params = {}) const {
        return soft_staking_api_.get_soft_staking_product_list(params);
    }
    /// Asynchronous `get_soft_staking_product_list()`.
    template <class CompletionToken>
    auto async_get_soft_staking_product_list(const GetSoftStakingProductListParams& params,
                                             CompletionToken&& token) const {
        return soft_staking_api_.async_get_soft_staking_product_list(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Soft Staking Rewards History (USER_DATA)
    ///
    /// GET /sapi/v1/soft-staking/history/rewardsRecord.
    ///
    /// Get Soft Staking Rewards History
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
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/soft-staking#get-soft-staking-rewards-history
    [[nodiscard]] common::RestApiResponse<GetSoftStakingRewardsHistoryResponse>
    get_soft_staking_rewards_history(const GetSoftStakingRewardsHistoryParams& params = {}) const {
        return soft_staking_api_.get_soft_staking_rewards_history(params);
    }
    /// Asynchronous `get_soft_staking_rewards_history()`.
    template <class CompletionToken>
    auto async_get_soft_staking_rewards_history(const GetSoftStakingRewardsHistoryParams& params,
                                                CompletionToken&& token) const {
        return soft_staking_api_.async_get_soft_staking_rewards_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Set Soft Staking (USER_DATA)
    ///
    /// GET /sapi/v1/soft-staking/set.
    ///
    /// Enable or disable Soft Staking.
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-staking/api/rest-api/soft-staking#set-soft-staking
    [[nodiscard]] common::RestApiResponse<SetSoftStakingResponse>
    set_soft_staking(const SetSoftStakingParams& params) const {
        return soft_staking_api_.set_soft_staking(params);
    }
    /// Asynchronous `set_soft_staking()`.
    template <class CompletionToken>
    auto async_set_soft_staking(const SetSoftStakingParams& params, CompletionToken&& token) const {
        return soft_staking_api_.async_set_soft_staking(params,
                                                        std::forward<CompletionToken>(token));
    }

    // SolStakingApi

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
    claim_boost_rewards(const ClaimBoostRewardsParams& params = {}) const {
        return sol_staking_api_.claim_boost_rewards(params);
    }
    /// Asynchronous `claim_boost_rewards()`.
    template <class CompletionToken>
    auto async_claim_boost_rewards(const ClaimBoostRewardsParams& params,
                                   CompletionToken&& token) const {
        return sol_staking_api_.async_claim_boost_rewards(params,
                                                          std::forward<CompletionToken>(token));
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
    get_bnsol_rate_history(const GetBnsolRateHistoryParams& params = {}) const {
        return sol_staking_api_.get_bnsol_rate_history(params);
    }
    /// Asynchronous `get_bnsol_rate_history()`.
    template <class CompletionToken>
    auto async_get_bnsol_rate_history(const GetBnsolRateHistoryParams& params,
                                      CompletionToken&& token) const {
        return sol_staking_api_.async_get_bnsol_rate_history(params,
                                                             std::forward<CompletionToken>(token));
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
    get_bnsol_rewards_history(const GetBnsolRewardsHistoryParams& params = {}) const {
        return sol_staking_api_.get_bnsol_rewards_history(params);
    }
    /// Asynchronous `get_bnsol_rewards_history()`.
    template <class CompletionToken>
    auto async_get_bnsol_rewards_history(const GetBnsolRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return sol_staking_api_.async_get_bnsol_rewards_history(
            params, std::forward<CompletionToken>(token));
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
    get_boost_rewards_history(const GetBoostRewardsHistoryParams& params) const {
        return sol_staking_api_.get_boost_rewards_history(params);
    }
    /// Asynchronous `get_boost_rewards_history()`.
    template <class CompletionToken>
    auto async_get_boost_rewards_history(const GetBoostRewardsHistoryParams& params,
                                         CompletionToken&& token) const {
        return sol_staking_api_.async_get_boost_rewards_history(
            params, std::forward<CompletionToken>(token));
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
    get_sol_redemption_history(const GetSolRedemptionHistoryParams& params = {}) const {
        return sol_staking_api_.get_sol_redemption_history(params);
    }
    /// Asynchronous `get_sol_redemption_history()`.
    template <class CompletionToken>
    auto async_get_sol_redemption_history(const GetSolRedemptionHistoryParams& params,
                                          CompletionToken&& token) const {
        return sol_staking_api_.async_get_sol_redemption_history(
            params, std::forward<CompletionToken>(token));
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
    get_sol_staking_history(const GetSolStakingHistoryParams& params = {}) const {
        return sol_staking_api_.get_sol_staking_history(params);
    }
    /// Asynchronous `get_sol_staking_history()`.
    template <class CompletionToken>
    auto async_get_sol_staking_history(const GetSolStakingHistoryParams& params,
                                       CompletionToken&& token) const {
        return sol_staking_api_.async_get_sol_staking_history(params,
                                                              std::forward<CompletionToken>(token));
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
    get_sol_staking_quota_details(const GetSolStakingQuotaDetailsParams& params = {}) const {
        return sol_staking_api_.get_sol_staking_quota_details(params);
    }
    /// Asynchronous `get_sol_staking_quota_details()`.
    template <class CompletionToken>
    auto async_get_sol_staking_quota_details(const GetSolStakingQuotaDetailsParams& params,
                                             CompletionToken&& token) const {
        return sol_staking_api_.async_get_sol_staking_quota_details(
            params, std::forward<CompletionToken>(token));
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
    get_unclaimed_rewards(const GetUnclaimedRewardsParams& params = {}) const {
        return sol_staking_api_.get_unclaimed_rewards(params);
    }
    /// Asynchronous `get_unclaimed_rewards()`.
    template <class CompletionToken>
    auto async_get_unclaimed_rewards(const GetUnclaimedRewardsParams& params,
                                     CompletionToken&& token) const {
        return sol_staking_api_.async_get_unclaimed_rewards(params,
                                                            std::forward<CompletionToken>(token));
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
    redeem_sol(const RedeemSolParams& params) const {
        return sol_staking_api_.redeem_sol(params);
    }
    /// Asynchronous `redeem_sol()`.
    template <class CompletionToken>
    auto async_redeem_sol(const RedeemSolParams& params, CompletionToken&& token) const {
        return sol_staking_api_.async_redeem_sol(params, std::forward<CompletionToken>(token));
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
    sol_staking_account(const SolStakingAccountParams& params = {}) const {
        return sol_staking_api_.sol_staking_account(params);
    }
    /// Asynchronous `sol_staking_account()`.
    template <class CompletionToken>
    auto async_sol_staking_account(const SolStakingAccountParams& params,
                                   CompletionToken&& token) const {
        return sol_staking_api_.async_sol_staking_account(params,
                                                          std::forward<CompletionToken>(token));
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
    subscribe_sol_staking(const SubscribeSolStakingParams& params) const {
        return sol_staking_api_.subscribe_sol_staking(params);
    }
    /// Asynchronous `subscribe_sol_staking()`.
    template <class CompletionToken>
    auto async_subscribe_sol_staking(const SubscribeSolStakingParams& params,
                                     CompletionToken&& token) const {
        return sol_staking_api_.async_subscribe_sol_staking(params,
                                                            std::forward<CompletionToken>(token));
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
    EthStakingApi eth_staking_api_;
    OnChainYieldsApi on_chain_yields_api_;
    SoftStakingApi soft_staking_api_;
    SolStakingApi sol_staking_api_;
};

} // namespace binance::staking::rest_api
