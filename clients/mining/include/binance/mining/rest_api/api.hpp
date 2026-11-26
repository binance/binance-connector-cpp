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
#include <binance/mining/export.hpp>
#include <binance/mining/rest_api/models/account_list_response.hpp>
#include <binance/mining/rest_api/models/acquiring_algorithm_response.hpp>
#include <binance/mining/rest_api/models/acquiring_coinname_response.hpp>
#include <binance/mining/rest_api/models/cancel_hashrate_resale_configuration_response.hpp>
#include <binance/mining/rest_api/models/earnings_list_response.hpp>
#include <binance/mining/rest_api/models/extra_bonus_list_response.hpp>
#include <binance/mining/rest_api/models/hashrate_resale_detail_response.hpp>
#include <binance/mining/rest_api/models/hashrate_resale_list_response.hpp>
#include <binance/mining/rest_api/models/hashrate_resale_request_response.hpp>
#include <binance/mining/rest_api/models/mining_account_earning_response.hpp>
#include <binance/mining/rest_api/models/request_for_detail_miner_list_response.hpp>
#include <binance/mining/rest_api/models/request_for_miner_list_response.hpp>
#include <binance/mining/rest_api/models/statistic_list_response.hpp>

namespace binance::mining::rest_api {

struct AccountListParams {
    /// Algorithm name.
    common::Required<std::string> algo;
    /// Mining account
    common::Required<std::string> user_name;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelHashrateResaleConfigurationParams {
    /// Mining ID
    common::Required<std::int64_t> config_id;
    /// Mining Account
    common::Required<std::string> user_name;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct EarningsListParams {
    /// Algorithm name.
    common::Required<std::string> algo;
    /// Mining account.
    common::Required<std::string> user_name;
    /// Coin name
    std::optional<std::string> coin = std::nullopt;
    /// Search start time in milliseconds.
    std::optional<std::int64_t> start_date = std::nullopt;
    /// Search end time in milliseconds.
    std::optional<std::int64_t> end_date = std::nullopt;
    /// Page number, starting from 1.
    std::optional<std::int64_t> page_index = std::nullopt;
    /// Number of rows per page.
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ExtraBonusListParams {
    /// Transfer algorithm
    common::Required<std::string> algo;
    /// Mining account
    common::Required<std::string> user_name;
    /// Coin name
    std::optional<std::string> coin = std::nullopt;
    /// Search start time in milliseconds.
    std::optional<std::int64_t> start_date = std::nullopt;
    /// Search end time in milliseconds.
    std::optional<std::int64_t> end_date = std::nullopt;
    /// Page number, starting from 1.
    std::optional<std::int64_t> page_index = std::nullopt;
    /// Number of rows per page.
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct HashrateResaleDetailParams {
    /// Configuration ID.
    common::Required<std::int64_t> config_id;
    /// Page number, starting from 1.
    std::optional<std::int64_t> page_index = std::nullopt;
    /// Number of rows per page.
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct HashrateResaleListParams {
    /// Page number, starting from 1.
    std::optional<std::int64_t> page_index = std::nullopt;
    /// Number of rows per page.
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct HashrateResaleRequestParams {
    /// Mining Account
    common::Required<std::string> user_name;
    /// Transfer algorithm
    common::Required<std::string> algo;
    /// Resale End Time (Millisecond timestamp)
    common::Required<std::int64_t> end_date;
    /// Resale Start Time(Millisecond timestamp)
    common::Required<std::int64_t> start_date;
    /// Mining Account
    common::Required<std::string> to_pool_user;
    /// Resale hashrate h/s must be transferred (BTC is greater than 500000000000 ETH is greater
    /// than 500000)
    common::Required<std::int64_t> hash_rate;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MiningAccountEarningParams {
    /// Algorithm
    common::Required<std::string> algo;
    /// Millisecond timestamp
    std::optional<std::int64_t> start_date = std::nullopt;
    /// Millisecond timestamp
    std::optional<std::int64_t> end_date = std::nullopt;
    /// Page number, starting from 1.
    std::optional<std::int64_t> page_index = std::nullopt;
    /// Number of rows per page.
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RequestForDetailMinerListParams {
    /// Algorithm
    common::Required<std::string> algo;
    /// Mining account
    common::Required<std::string> user_name;
    /// Miner name.
    common::Required<std::string> worker_name;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RequestForMinerListParams {
    /// Algorithm
    common::Required<std::string> algo;
    /// Mining account
    common::Required<std::string> user_name;
    /// Page number, starting from 1.
    std::optional<std::int64_t> page_index = std::nullopt;
    /// Sort order. 0 for ascending, 1 for descending.
    std::optional<std::int64_t> sort = std::nullopt;
    /// Sort by: 1 miner name, 2 real-time hashrate, 3 daily average hashrate, 4 real-time rejection
    /// rate, 5 last submission time
    std::optional<std::int64_t> sort_column = std::nullopt;
    /// Miner status. 0 all, 1 valid, 2 invalid, 3 failure.
    std::optional<std::int64_t> worker_status = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct StatisticListParams {
    /// Algorithm
    common::Required<std::string> algo;
    /// Mining account
    common::Required<std::string> user_name;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_MINING_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::RestClient> client);

    /// Account List (USER_DATA)
    ///
    /// GET /sapi/v1/mining/statistics/user/list.
    ///
    /// Query Account List
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#account-list
    [[nodiscard]] common::RestApiResponse<AccountListResponse>
    account_list(const AccountListParams& params) const;

    /// Asynchronous `account_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountListResponse>)`.
    template <class CompletionToken>
    auto async_account_list(const AccountListParams& params, CompletionToken&& token) const {
        return common::async_send<AccountListResponse>(client_, account_list_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// Acquiring Algorithm (MARKET_DATA)
    ///
    /// GET /sapi/v1/mining/pub/algoList.
    ///
    /// Acquiring Algorithm
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#acquiring-algorithm
    [[nodiscard]] common::RestApiResponse<AcquiringAlgorithmResponse> acquiring_algorithm() const;

    /// Asynchronous `acquiring_algorithm()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AcquiringAlgorithmResponse>)`.
    template <class CompletionToken> auto async_acquiring_algorithm(CompletionToken&& token) const {
        return common::async_send<AcquiringAlgorithmResponse>(
            client_, acquiring_algorithm_request(), std::forward<CompletionToken>(token));
    }

    /// Acquiring CoinName (MARKET_DATA)
    ///
    /// GET /sapi/v1/mining/pub/coinList.
    ///
    /// Acquiring CoinName
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#acquiring-coinname
    [[nodiscard]] common::RestApiResponse<AcquiringCoinnameResponse> acquiring_coinname() const;

    /// Asynchronous `acquiring_coinname()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AcquiringCoinnameResponse>)`.
    template <class CompletionToken> auto async_acquiring_coinname(CompletionToken&& token) const {
        return common::async_send<AcquiringCoinnameResponse>(client_, acquiring_coinname_request(),
                                                             std::forward<CompletionToken>(token));
    }

    /// Cancel hashrate resale configuration (USER_DATA)
    ///
    /// POST /sapi/v1/mining/hash-transfer/config/cancel.
    ///
    /// Cancel hashrate resale configuration
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#cancel-hashrate-resale-configuration
    [[nodiscard]] common::RestApiResponse<CancelHashrateResaleConfigurationResponse>
    cancel_hashrate_resale_configuration(
        const CancelHashrateResaleConfigurationParams& params) const;

    /// Asynchronous `cancel_hashrate_resale_configuration()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<CancelHashrateResaleConfigurationResponse>)`.
    template <class CompletionToken>
    auto async_cancel_hashrate_resale_configuration(
        const CancelHashrateResaleConfigurationParams& params, CompletionToken&& token) const {
        return common::async_send<CancelHashrateResaleConfigurationResponse>(
            client_, cancel_hashrate_resale_configuration_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Earnings List (USER_DATA)
    ///
    /// GET /sapi/v1/mining/payment/list.
    ///
    /// Query Earnings List
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#earnings-list
    [[nodiscard]] common::RestApiResponse<EarningsListResponse>
    earnings_list(const EarningsListParams& params) const;

    /// Asynchronous `earnings_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<EarningsListResponse>)`.
    template <class CompletionToken>
    auto async_earnings_list(const EarningsListParams& params, CompletionToken&& token) const {
        return common::async_send<EarningsListResponse>(client_, earnings_list_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// Extra Bonus List (USER_DATA)
    ///
    /// GET /sapi/v1/mining/payment/other.
    ///
    /// Extra Bonus List
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#extra-bonus-list
    [[nodiscard]] common::RestApiResponse<ExtraBonusListResponse>
    extra_bonus_list(const ExtraBonusListParams& params) const;

    /// Asynchronous `extra_bonus_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ExtraBonusListResponse>)`.
    template <class CompletionToken>
    auto async_extra_bonus_list(const ExtraBonusListParams& params, CompletionToken&& token) const {
        return common::async_send<ExtraBonusListResponse>(client_, extra_bonus_list_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Hashrate Resale Detail (USER_DATA)
    ///
    /// GET /sapi/v1/mining/hash-transfer/profit/details.
    ///
    /// Hashrate Resale Detail(USER_DATA)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#hashrate-resale-detail
    [[nodiscard]] common::RestApiResponse<HashrateResaleDetailResponse>
    hashrate_resale_detail(const HashrateResaleDetailParams& params) const;

    /// Asynchronous `hashrate_resale_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<HashrateResaleDetailResponse>)`.
    template <class CompletionToken>
    auto async_hashrate_resale_detail(const HashrateResaleDetailParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<HashrateResaleDetailResponse>(
            client_, hashrate_resale_detail_request(params), std::forward<CompletionToken>(token));
    }

    /// Hashrate Resale List (USER_DATA)
    ///
    /// GET /sapi/v1/mining/hash-transfer/config/details/list.
    ///
    /// Hashrate Resale List
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#hashrate-resale-list
    [[nodiscard]] common::RestApiResponse<HashrateResaleListResponse>
    hashrate_resale_list(const HashrateResaleListParams& params = {}) const;

    /// Asynchronous `hashrate_resale_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<HashrateResaleListResponse>)`.
    template <class CompletionToken>
    auto async_hashrate_resale_list(const HashrateResaleListParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<HashrateResaleListResponse>(
            client_, hashrate_resale_list_request(params), std::forward<CompletionToken>(token));
    }

    /// Hashrate Resale Request (USER_DATA)
    ///
    /// POST /sapi/v1/mining/hash-transfer/config.
    ///
    /// Hashrate Resale Request
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#hashrate-resale-request
    [[nodiscard]] common::RestApiResponse<HashrateResaleRequestResponse>
    hashrate_resale_request(const HashrateResaleRequestParams& params) const;

    /// Asynchronous `hashrate_resale_request()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<HashrateResaleRequestResponse>)`.
    template <class CompletionToken>
    auto async_hashrate_resale_request(const HashrateResaleRequestParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<HashrateResaleRequestResponse>(
            client_, hashrate_resale_request_request(params), std::forward<CompletionToken>(token));
    }

    /// Mining Account Earning (USER_DATA)
    ///
    /// GET /sapi/v1/mining/payment/uid.
    ///
    /// Mining Account Earning
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#mining-account-earning
    [[nodiscard]] common::RestApiResponse<MiningAccountEarningResponse>
    mining_account_earning(const MiningAccountEarningParams& params) const;

    /// Asynchronous `mining_account_earning()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MiningAccountEarningResponse>)`.
    template <class CompletionToken>
    auto async_mining_account_earning(const MiningAccountEarningParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<MiningAccountEarningResponse>(
            client_, mining_account_earning_request(params), std::forward<CompletionToken>(token));
    }

    /// Request for Detail Miner List (USER_DATA)
    ///
    /// GET /sapi/v1/mining/worker/detail.
    ///
    /// Request for Detail Miner List
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#request-for-detail-miner-list
    [[nodiscard]] common::RestApiResponse<RequestForDetailMinerListResponse>
    request_for_detail_miner_list(const RequestForDetailMinerListParams& params) const;

    /// Asynchronous `request_for_detail_miner_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RequestForDetailMinerListResponse>)`.
    template <class CompletionToken>
    auto async_request_for_detail_miner_list(const RequestForDetailMinerListParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<RequestForDetailMinerListResponse>(
            client_, request_for_detail_miner_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Request for Miner List (USER_DATA)
    ///
    /// GET /sapi/v1/mining/worker/list.
    ///
    /// Request for Miner List
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#request-for-miner-list
    [[nodiscard]] common::RestApiResponse<RequestForMinerListResponse>
    request_for_miner_list(const RequestForMinerListParams& params) const;

    /// Asynchronous `request_for_miner_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RequestForMinerListResponse>)`.
    template <class CompletionToken>
    auto async_request_for_miner_list(const RequestForMinerListParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<RequestForMinerListResponse>(
            client_, request_for_miner_list_request(params), std::forward<CompletionToken>(token));
    }

    /// Statistic List (USER_DATA)
    ///
    /// GET /sapi/v1/mining/statistics/user/status.
    ///
    /// Statistic List
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-mining/api/rest-api/~#statistic-list
    [[nodiscard]] common::RestApiResponse<StatisticListResponse>
    statistic_list(const StatisticListParams& params) const;

    /// Asynchronous `statistic_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<StatisticListResponse>)`.
    template <class CompletionToken>
    auto async_statistic_list(const StatisticListParams& params, CompletionToken&& token) const {
        return common::async_send<StatisticListResponse>(client_, statistic_list_request(params),
                                                         std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest account_list_request(const AccountListParams& params) const;
    [[nodiscard]] common::RestRequest acquiring_algorithm_request() const;
    [[nodiscard]] common::RestRequest acquiring_coinname_request() const;
    [[nodiscard]] common::RestRequest cancel_hashrate_resale_configuration_request(
        const CancelHashrateResaleConfigurationParams& params) const;
    [[nodiscard]] common::RestRequest earnings_list_request(const EarningsListParams& params) const;
    [[nodiscard]] common::RestRequest
    extra_bonus_list_request(const ExtraBonusListParams& params) const;
    [[nodiscard]] common::RestRequest
    hashrate_resale_detail_request(const HashrateResaleDetailParams& params) const;
    [[nodiscard]] common::RestRequest
    hashrate_resale_list_request(const HashrateResaleListParams& params) const;
    [[nodiscard]] common::RestRequest
    hashrate_resale_request_request(const HashrateResaleRequestParams& params) const;
    [[nodiscard]] common::RestRequest
    mining_account_earning_request(const MiningAccountEarningParams& params) const;
    [[nodiscard]] common::RestRequest
    request_for_detail_miner_list_request(const RequestForDetailMinerListParams& params) const;
    [[nodiscard]] common::RestRequest
    request_for_miner_list_request(const RequestForMinerListParams& params) const;
    [[nodiscard]] common::RestRequest
    statistic_list_request(const StatisticListParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::mining::rest_api
