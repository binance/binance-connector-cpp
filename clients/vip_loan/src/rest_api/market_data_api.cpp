//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/market_data_api.hpp>

namespace binance::vip_loan::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
MarketDataApi::get_borrow_interest_rate_request(const GetBorrowInterestRateParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/request/interestRate";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetBorrowInterestRateResponseInner>>
MarketDataApi::get_borrow_interest_rate(const GetBorrowInterestRateParams& params) const {
    return common::send<std::vector<GetBorrowInterestRateResponseInner>>(
        *client_, get_borrow_interest_rate_request(params));
}

common::RestRequest
MarketDataApi::get_collateral_asset_data_request(const GetCollateralAssetDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/collateral/data";
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCollateralAssetDataResponse>
MarketDataApi::get_collateral_asset_data(const GetCollateralAssetDataParams& params) const {
    return common::send<GetCollateralAssetDataResponse>(*client_,
                                                        get_collateral_asset_data_request(params));
}

common::RestRequest
MarketDataApi::get_loanable_assets_data_request(const GetLoanableAssetsDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/loanable/data";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "vipLevel", params.vip_level);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetLoanableAssetsDataResponse>
MarketDataApi::get_loanable_assets_data(const GetLoanableAssetsDataParams& params) const {
    return common::send<GetLoanableAssetsDataResponse>(*client_,
                                                       get_loanable_assets_data_request(params));
}

common::RestRequest MarketDataApi::get_vip_loan_interest_rate_history_request(
    const GetVIPLoanInterestRateHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/interestRateHistory";
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetVIPLoanInterestRateHistoryResponse>
MarketDataApi::get_vip_loan_interest_rate_history(
    const GetVIPLoanInterestRateHistoryParams& params) const {
    return common::send<GetVIPLoanInterestRateHistoryResponse>(
        *client_, get_vip_loan_interest_rate_history_request(params));
}

common::RestRequest MarketDataApi::query_vip_loan_fixed_rate_market_request(
    const QueryVIPLoanFixedRateMarketParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/fixed/market";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "duration", params.duration);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryVIPLoanFixedRateMarketResponse>
MarketDataApi::query_vip_loan_fixed_rate_market(
    const QueryVIPLoanFixedRateMarketParams& params) const {
    return common::send<QueryVIPLoanFixedRateMarketResponse>(
        *client_, query_vip_loan_fixed_rate_market_request(params));
}

} // namespace binance::vip_loan::rest_api
