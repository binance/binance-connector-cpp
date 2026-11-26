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
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_product_list_response.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/set_soft_staking_response.hpp>

namespace binance::staking::rest_api {

struct GetSoftStakingProductListParams {
    std::optional<std::string> asset = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSoftStakingRewardsHistoryParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Currently querying page
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SetSoftStakingParams {
    common::Required<bool> soft_staking;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STAKING_EXPORT SoftStakingApi {
public:
    explicit SoftStakingApi(std::shared_ptr<common::RestClient> client);

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
    get_soft_staking_product_list(const GetSoftStakingProductListParams& params = {}) const;

    /// Asynchronous `get_soft_staking_product_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetSoftStakingProductListResponse>)`.
    template <class CompletionToken>
    auto async_get_soft_staking_product_list(const GetSoftStakingProductListParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetSoftStakingProductListResponse>(
            client_, get_soft_staking_product_list_request(params),
            std::forward<CompletionToken>(token));
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
    get_soft_staking_rewards_history(const GetSoftStakingRewardsHistoryParams& params = {}) const;

    /// Asynchronous `get_soft_staking_rewards_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetSoftStakingRewardsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_soft_staking_rewards_history(const GetSoftStakingRewardsHistoryParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<GetSoftStakingRewardsHistoryResponse>(
            client_, get_soft_staking_rewards_history_request(params),
            std::forward<CompletionToken>(token));
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
    set_soft_staking(const SetSoftStakingParams& params) const;

    /// Asynchronous `set_soft_staking()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SetSoftStakingResponse>)`.
    template <class CompletionToken>
    auto async_set_soft_staking(const SetSoftStakingParams& params, CompletionToken&& token) const {
        return common::async_send<SetSoftStakingResponse>(client_, set_soft_staking_request(params),
                                                          std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_soft_staking_product_list_request(const GetSoftStakingProductListParams& params) const;
    [[nodiscard]] common::RestRequest get_soft_staking_rewards_history_request(
        const GetSoftStakingRewardsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    set_soft_staking_request(const SetSoftStakingParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::staking::rest_api
