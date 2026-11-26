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
#include <binance/mining/export.hpp>
#include <binance/mining/rest_api/api.hpp>
#include <binance/mining/rest_api/models.hpp>

namespace binance::mining::rest_api {

/// Mining REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_MINING_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Mining REST API).
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

    // Api

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
    account_list(const AccountListParams& params) const {
        return api_.account_list(params);
    }
    /// Asynchronous `account_list()`.
    template <class CompletionToken>
    auto async_account_list(const AccountListParams& params, CompletionToken&& token) const {
        return api_.async_account_list(params, std::forward<CompletionToken>(token));
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
    [[nodiscard]] common::RestApiResponse<AcquiringAlgorithmResponse> acquiring_algorithm() const {
        return api_.acquiring_algorithm();
    }
    /// Asynchronous `acquiring_algorithm()`.
    template <class CompletionToken> auto async_acquiring_algorithm(CompletionToken&& token) const {
        return api_.async_acquiring_algorithm(std::forward<CompletionToken>(token));
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
    [[nodiscard]] common::RestApiResponse<AcquiringCoinnameResponse> acquiring_coinname() const {
        return api_.acquiring_coinname();
    }
    /// Asynchronous `acquiring_coinname()`.
    template <class CompletionToken> auto async_acquiring_coinname(CompletionToken&& token) const {
        return api_.async_acquiring_coinname(std::forward<CompletionToken>(token));
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
        const CancelHashrateResaleConfigurationParams& params) const {
        return api_.cancel_hashrate_resale_configuration(params);
    }
    /// Asynchronous `cancel_hashrate_resale_configuration()`.
    template <class CompletionToken>
    auto async_cancel_hashrate_resale_configuration(
        const CancelHashrateResaleConfigurationParams& params, CompletionToken&& token) const {
        return api_.async_cancel_hashrate_resale_configuration(
            params, std::forward<CompletionToken>(token));
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
    earnings_list(const EarningsListParams& params) const {
        return api_.earnings_list(params);
    }
    /// Asynchronous `earnings_list()`.
    template <class CompletionToken>
    auto async_earnings_list(const EarningsListParams& params, CompletionToken&& token) const {
        return api_.async_earnings_list(params, std::forward<CompletionToken>(token));
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
    extra_bonus_list(const ExtraBonusListParams& params) const {
        return api_.extra_bonus_list(params);
    }
    /// Asynchronous `extra_bonus_list()`.
    template <class CompletionToken>
    auto async_extra_bonus_list(const ExtraBonusListParams& params, CompletionToken&& token) const {
        return api_.async_extra_bonus_list(params, std::forward<CompletionToken>(token));
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
    hashrate_resale_detail(const HashrateResaleDetailParams& params) const {
        return api_.hashrate_resale_detail(params);
    }
    /// Asynchronous `hashrate_resale_detail()`.
    template <class CompletionToken>
    auto async_hashrate_resale_detail(const HashrateResaleDetailParams& params,
                                      CompletionToken&& token) const {
        return api_.async_hashrate_resale_detail(params, std::forward<CompletionToken>(token));
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
    hashrate_resale_list(const HashrateResaleListParams& params = {}) const {
        return api_.hashrate_resale_list(params);
    }
    /// Asynchronous `hashrate_resale_list()`.
    template <class CompletionToken>
    auto async_hashrate_resale_list(const HashrateResaleListParams& params,
                                    CompletionToken&& token) const {
        return api_.async_hashrate_resale_list(params, std::forward<CompletionToken>(token));
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
    hashrate_resale_request(const HashrateResaleRequestParams& params) const {
        return api_.hashrate_resale_request(params);
    }
    /// Asynchronous `hashrate_resale_request()`.
    template <class CompletionToken>
    auto async_hashrate_resale_request(const HashrateResaleRequestParams& params,
                                       CompletionToken&& token) const {
        return api_.async_hashrate_resale_request(params, std::forward<CompletionToken>(token));
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
    mining_account_earning(const MiningAccountEarningParams& params) const {
        return api_.mining_account_earning(params);
    }
    /// Asynchronous `mining_account_earning()`.
    template <class CompletionToken>
    auto async_mining_account_earning(const MiningAccountEarningParams& params,
                                      CompletionToken&& token) const {
        return api_.async_mining_account_earning(params, std::forward<CompletionToken>(token));
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
    request_for_detail_miner_list(const RequestForDetailMinerListParams& params) const {
        return api_.request_for_detail_miner_list(params);
    }
    /// Asynchronous `request_for_detail_miner_list()`.
    template <class CompletionToken>
    auto async_request_for_detail_miner_list(const RequestForDetailMinerListParams& params,
                                             CompletionToken&& token) const {
        return api_.async_request_for_detail_miner_list(params,
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
    request_for_miner_list(const RequestForMinerListParams& params) const {
        return api_.request_for_miner_list(params);
    }
    /// Asynchronous `request_for_miner_list()`.
    template <class CompletionToken>
    auto async_request_for_miner_list(const RequestForMinerListParams& params,
                                      CompletionToken&& token) const {
        return api_.async_request_for_miner_list(params, std::forward<CompletionToken>(token));
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
    statistic_list(const StatisticListParams& params) const {
        return api_.statistic_list(params);
    }
    /// Asynchronous `statistic_list()`.
    template <class CompletionToken>
    auto async_statistic_list(const StatisticListParams& params, CompletionToken&& token) const {
        return api_.async_statistic_list(params, std::forward<CompletionToken>(token));
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
    Api api_;
};

} // namespace binance::mining::rest_api
