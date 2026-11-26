//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/wallet_api.hpp>

namespace binance::w3w_prediction::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

WalletApi::WalletApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest WalletApi::get_portfolio_request(const GetPortfolioParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/pnl/portfolio";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "tokenId", params.token_id);
    common::detail::json::set_param(req.query, "marketId", params.market_id);
    common::detail::json::set_param(req.query, "marketTopicId", params.market_topic_id);
    common::detail::json::set_param(req.query, "activeOnly", params.active_only);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetPortfolioResponse>
WalletApi::get_portfolio(const GetPortfolioParams& params) const {
    return common::send<GetPortfolioResponse>(*client_, get_portfolio_request(params));
}

common::RestRequest WalletApi::get_quota_status_request(const GetQuotaStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/quota/limit/status";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetQuotaStatusResponse>
WalletApi::get_quota_status(const GetQuotaStatusParams& params) const {
    return common::send<GetQuotaStatusResponse>(*client_, get_quota_status_request(params));
}

common::RestRequest
WalletApi::list_prediction_wallets_request(const ListPredictionWalletsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/wallet/list";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ListPredictionWalletsResponse>
WalletApi::list_prediction_wallets(const ListPredictionWalletsParams& params) const {
    return common::send<ListPredictionWalletsResponse>(*client_,
                                                       list_prediction_wallets_request(params));
}

common::RestRequest WalletApi::query_payment_option_balances_request(
    const QueryPaymentOptionBalancesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/balance/payment-options";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryPaymentOptionBalancesResponse>
WalletApi::query_payment_option_balances(const QueryPaymentOptionBalancesParams& params) const {
    return common::send<QueryPaymentOptionBalancesResponse>(
        *client_, query_payment_option_balances_request(params));
}

} // namespace binance::w3w_prediction::rest_api
