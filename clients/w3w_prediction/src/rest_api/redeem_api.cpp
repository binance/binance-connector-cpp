//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/redeem_api.hpp>

namespace binance::w3w_prediction::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

RedeemApi::RedeemApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest RedeemApi::batch_redeem_request(const BatchRedeemParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/batch-redeem";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "walletId", params.wallet_id);
    common::detail::json::set_param(req.query, "tokenIds", params.token_ids);
    common::detail::json::set_param(req.query, "chainId", params.chain_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<BatchRedeemResponse>
RedeemApi::batch_redeem(const BatchRedeemParams& params) const {
    return common::send<BatchRedeemResponse>(*client_, batch_redeem_request(params));
}

common::RestRequest
RedeemApi::get_redeem_status_request(const GetRedeemStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/redeem/status";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "txHash", params.tx_hash);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetRedeemStatusResponse>
RedeemApi::get_redeem_status(const GetRedeemStatusParams& params) const {
    return common::send<GetRedeemStatusResponse>(*client_, get_redeem_status_request(params));
}

} // namespace binance::w3w_prediction::rest_api
