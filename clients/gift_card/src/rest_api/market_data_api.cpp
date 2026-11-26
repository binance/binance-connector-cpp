//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/gift_card/rest_api/market_data_api.hpp>

namespace binance::gift_card::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest MarketDataApi::create_a_dual_token_gift_card_request(
    const CreateADualTokenGiftCardParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/giftcard/buyCode";
    common::detail::json::set_param(req.query, "baseToken", params.base_token);
    common::detail::json::set_param(req.query, "faceToken", params.face_token);
    common::detail::json::set_param(req.query, "baseTokenAmount", params.base_token_amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CreateADualTokenGiftCardResponse>
MarketDataApi::create_a_dual_token_gift_card(const CreateADualTokenGiftCardParams& params) const {
    return common::send<CreateADualTokenGiftCardResponse>(
        *client_, create_a_dual_token_gift_card_request(params));
}

common::RestRequest MarketDataApi::create_a_single_token_gift_card_request(
    const CreateASingleTokenGiftCardParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/giftcard/createCode";
    common::detail::json::set_param(req.query, "token", params.token);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CreateASingleTokenGiftCardResponse>
MarketDataApi::create_a_single_token_gift_card(
    const CreateASingleTokenGiftCardParams& params) const {
    return common::send<CreateASingleTokenGiftCardResponse>(
        *client_, create_a_single_token_gift_card_request(params));
}

common::RestRequest
MarketDataApi::fetch_rsa_public_key_request(const FetchRsaPublicKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/giftcard/cryptography/rsa-public-key";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FetchRsaPublicKeyResponse>
MarketDataApi::fetch_rsa_public_key(const FetchRsaPublicKeyParams& params) const {
    return common::send<FetchRsaPublicKeyResponse>(*client_, fetch_rsa_public_key_request(params));
}

common::RestRequest
MarketDataApi::fetch_token_limit_request(const FetchTokenLimitParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/giftcard/buyCode/token-limit";
    common::detail::json::set_param(req.query, "baseToken", params.base_token);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FetchTokenLimitResponse>
MarketDataApi::fetch_token_limit(const FetchTokenLimitParams& params) const {
    return common::send<FetchTokenLimitResponse>(*client_, fetch_token_limit_request(params));
}

common::RestRequest MarketDataApi::redeem_a_binance_gift_card_request(
    const RedeemABinanceGiftCardParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/giftcard/redeemCode";
    common::detail::json::set_param(req.query, "code", params.code);
    common::detail::json::set_param(req.query, "externalUid", params.external_uid);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RedeemABinanceGiftCardResponse>
MarketDataApi::redeem_a_binance_gift_card(const RedeemABinanceGiftCardParams& params) const {
    return common::send<RedeemABinanceGiftCardResponse>(*client_,
                                                        redeem_a_binance_gift_card_request(params));
}

common::RestRequest MarketDataApi::verify_binance_gift_card_by_gift_card_number_request(
    const VerifyBinanceGiftCardByGiftCardNumberParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/giftcard/verify";
    common::detail::json::set_param(req.query, "referenceNo", params.reference_no);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<VerifyBinanceGiftCardByGiftCardNumberResponse>
MarketDataApi::verify_binance_gift_card_by_gift_card_number(
    const VerifyBinanceGiftCardByGiftCardNumberParams& params) const {
    return common::send<VerifyBinanceGiftCardByGiftCardNumberResponse>(
        *client_, verify_binance_gift_card_by_gift_card_number_request(params));
}

} // namespace binance::gift_card::rest_api
