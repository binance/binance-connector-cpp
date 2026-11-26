//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/api.hpp>

namespace binance::mining::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

Api::Api(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest Api::account_list_request(const AccountListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/statistics/user/list";
    common::detail::json::set_param(req.query, "algo", params.algo);
    common::detail::json::set_param(req.query, "userName", params.user_name);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountListResponse>
Api::account_list(const AccountListParams& params) const {
    return common::send<AccountListResponse>(*client_, account_list_request(params));
}

common::RestRequest Api::acquiring_algorithm_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/pub/algoList";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<AcquiringAlgorithmResponse> Api::acquiring_algorithm() const {
    return common::send<AcquiringAlgorithmResponse>(*client_, acquiring_algorithm_request());
}

common::RestRequest Api::acquiring_coinname_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/pub/coinList";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<AcquiringCoinnameResponse> Api::acquiring_coinname() const {
    return common::send<AcquiringCoinnameResponse>(*client_, acquiring_coinname_request());
}

common::RestRequest Api::cancel_hashrate_resale_configuration_request(
    const CancelHashrateResaleConfigurationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/mining/hash-transfer/config/cancel";
    common::detail::json::set_param(req.query, "configId", params.config_id);
    common::detail::json::set_param(req.query, "userName", params.user_name);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelHashrateResaleConfigurationResponse>
Api::cancel_hashrate_resale_configuration(
    const CancelHashrateResaleConfigurationParams& params) const {
    return common::send<CancelHashrateResaleConfigurationResponse>(
        *client_, cancel_hashrate_resale_configuration_request(params));
}

common::RestRequest Api::earnings_list_request(const EarningsListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/payment/list";
    common::detail::json::set_param(req.query, "algo", params.algo);
    common::detail::json::set_param(req.query, "userName", params.user_name);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "startDate", params.start_date);
    common::detail::json::set_param(req.query, "endDate", params.end_date);
    common::detail::json::set_param(req.query, "pageIndex", params.page_index);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<EarningsListResponse>
Api::earnings_list(const EarningsListParams& params) const {
    return common::send<EarningsListResponse>(*client_, earnings_list_request(params));
}

common::RestRequest Api::extra_bonus_list_request(const ExtraBonusListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/payment/other";
    common::detail::json::set_param(req.query, "algo", params.algo);
    common::detail::json::set_param(req.query, "userName", params.user_name);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "startDate", params.start_date);
    common::detail::json::set_param(req.query, "endDate", params.end_date);
    common::detail::json::set_param(req.query, "pageIndex", params.page_index);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ExtraBonusListResponse>
Api::extra_bonus_list(const ExtraBonusListParams& params) const {
    return common::send<ExtraBonusListResponse>(*client_, extra_bonus_list_request(params));
}

common::RestRequest
Api::hashrate_resale_detail_request(const HashrateResaleDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/hash-transfer/profit/details";
    common::detail::json::set_param(req.query, "configId", params.config_id);
    common::detail::json::set_param(req.query, "pageIndex", params.page_index);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<HashrateResaleDetailResponse>
Api::hashrate_resale_detail(const HashrateResaleDetailParams& params) const {
    return common::send<HashrateResaleDetailResponse>(*client_,
                                                      hashrate_resale_detail_request(params));
}

common::RestRequest
Api::hashrate_resale_list_request(const HashrateResaleListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/hash-transfer/config/details/list";
    common::detail::json::set_param(req.query, "pageIndex", params.page_index);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<HashrateResaleListResponse>
Api::hashrate_resale_list(const HashrateResaleListParams& params) const {
    return common::send<HashrateResaleListResponse>(*client_, hashrate_resale_list_request(params));
}

common::RestRequest
Api::hashrate_resale_request_request(const HashrateResaleRequestParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/mining/hash-transfer/config";
    common::detail::json::set_param(req.query, "userName", params.user_name);
    common::detail::json::set_param(req.query, "algo", params.algo);
    common::detail::json::set_param(req.query, "endDate", params.end_date);
    common::detail::json::set_param(req.query, "startDate", params.start_date);
    common::detail::json::set_param(req.query, "toPoolUser", params.to_pool_user);
    common::detail::json::set_param(req.query, "hashRate", params.hash_rate);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<HashrateResaleRequestResponse>
Api::hashrate_resale_request(const HashrateResaleRequestParams& params) const {
    return common::send<HashrateResaleRequestResponse>(*client_,
                                                       hashrate_resale_request_request(params));
}

common::RestRequest
Api::mining_account_earning_request(const MiningAccountEarningParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/payment/uid";
    common::detail::json::set_param(req.query, "algo", params.algo);
    common::detail::json::set_param(req.query, "startDate", params.start_date);
    common::detail::json::set_param(req.query, "endDate", params.end_date);
    common::detail::json::set_param(req.query, "pageIndex", params.page_index);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MiningAccountEarningResponse>
Api::mining_account_earning(const MiningAccountEarningParams& params) const {
    return common::send<MiningAccountEarningResponse>(*client_,
                                                      mining_account_earning_request(params));
}

common::RestRequest
Api::request_for_detail_miner_list_request(const RequestForDetailMinerListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/worker/detail";
    common::detail::json::set_param(req.query, "algo", params.algo);
    common::detail::json::set_param(req.query, "userName", params.user_name);
    common::detail::json::set_param(req.query, "workerName", params.worker_name);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RequestForDetailMinerListResponse>
Api::request_for_detail_miner_list(const RequestForDetailMinerListParams& params) const {
    return common::send<RequestForDetailMinerListResponse>(
        *client_, request_for_detail_miner_list_request(params));
}

common::RestRequest
Api::request_for_miner_list_request(const RequestForMinerListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/worker/list";
    common::detail::json::set_param(req.query, "algo", params.algo);
    common::detail::json::set_param(req.query, "userName", params.user_name);
    common::detail::json::set_param(req.query, "pageIndex", params.page_index);
    common::detail::json::set_param(req.query, "sort", params.sort);
    common::detail::json::set_param(req.query, "sortColumn", params.sort_column);
    common::detail::json::set_param(req.query, "workerStatus", params.worker_status);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RequestForMinerListResponse>
Api::request_for_miner_list(const RequestForMinerListParams& params) const {
    return common::send<RequestForMinerListResponse>(*client_,
                                                     request_for_miner_list_request(params));
}

common::RestRequest Api::statistic_list_request(const StatisticListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/mining/statistics/user/status";
    common::detail::json::set_param(req.query, "algo", params.algo);
    common::detail::json::set_param(req.query, "userName", params.user_name);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<StatisticListResponse>
Api::statistic_list(const StatisticListParams& params) const {
    return common::send<StatisticListResponse>(*client_, statistic_list_request(params));
}

} // namespace binance::mining::rest_api
