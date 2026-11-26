//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/tokenized_api.hpp>

namespace binance::stocks::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(TokenizedConvertStatusConvertTypeEnum value) noexcept {
    switch (value) {
    case TokenizedConvertStatusConvertTypeEnum::Mint:
        return "MINT";
    case TokenizedConvertStatusConvertTypeEnum::Redeem:
        return "REDEEM";
    case TokenizedConvertStatusConvertTypeEnum::Unknown:
        break;
    }
    return "";
}

TokenizedConvertStatusConvertTypeEnum
tag_invoke(boost::json::value_to_tag<TokenizedConvertStatusConvertTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MINT") {
        return TokenizedConvertStatusConvertTypeEnum::Mint;
    }
    if (s == "REDEEM") {
        return TokenizedConvertStatusConvertTypeEnum::Redeem;
    }
    return TokenizedConvertStatusConvertTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TokenizedConvertStatusConvertTypeEnum value) {
    if (value == TokenizedConvertStatusConvertTypeEnum::Unknown) {
        throw std::invalid_argument(
            "TokenizedConvertStatusConvertTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TokenizedMintTokenizedAssetSettleWalletTypeEnum value) noexcept {
    switch (value) {
    case TokenizedMintTokenizedAssetSettleWalletTypeEnum::Main:
        return "MAIN";
    case TokenizedMintTokenizedAssetSettleWalletTypeEnum::Card:
        return "CARD";
    case TokenizedMintTokenizedAssetSettleWalletTypeEnum::Unknown:
        break;
    }
    return "";
}

TokenizedMintTokenizedAssetSettleWalletTypeEnum
tag_invoke(boost::json::value_to_tag<TokenizedMintTokenizedAssetSettleWalletTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MAIN") {
        return TokenizedMintTokenizedAssetSettleWalletTypeEnum::Main;
    }
    if (s == "CARD") {
        return TokenizedMintTokenizedAssetSettleWalletTypeEnum::Card;
    }
    return TokenizedMintTokenizedAssetSettleWalletTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TokenizedMintTokenizedAssetSettleWalletTypeEnum value) {
    if (value == TokenizedMintTokenizedAssetSettleWalletTypeEnum::Unknown) {
        throw std::invalid_argument(
            "TokenizedMintTokenizedAssetSettleWalletTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TokenizedRedeemTokenizedAssetSettleWalletTypeEnum value) noexcept {
    switch (value) {
    case TokenizedRedeemTokenizedAssetSettleWalletTypeEnum::Main:
        return "MAIN";
    case TokenizedRedeemTokenizedAssetSettleWalletTypeEnum::Card:
        return "CARD";
    case TokenizedRedeemTokenizedAssetSettleWalletTypeEnum::Unknown:
        break;
    }
    return "";
}

TokenizedRedeemTokenizedAssetSettleWalletTypeEnum
tag_invoke(boost::json::value_to_tag<TokenizedRedeemTokenizedAssetSettleWalletTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MAIN") {
        return TokenizedRedeemTokenizedAssetSettleWalletTypeEnum::Main;
    }
    if (s == "CARD") {
        return TokenizedRedeemTokenizedAssetSettleWalletTypeEnum::Card;
    }
    return TokenizedRedeemTokenizedAssetSettleWalletTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TokenizedRedeemTokenizedAssetSettleWalletTypeEnum value) {
    if (value == TokenizedRedeemTokenizedAssetSettleWalletTypeEnum::Unknown) {
        throw std::invalid_argument(
            "TokenizedRedeemTokenizedAssetSettleWalletTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TokenizedApi::TokenizedApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest TokenizedApi::bstocks_corporate_action_records_request(
    const BstocksCorporateActionRecordsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/bstocks/corp-action";
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "lastTime", params.last_time);
    common::detail::json::set_param(req.query, "lastId", params.last_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<BstocksCorporateActionRecordsResponse>
TokenizedApi::bstocks_corporate_action_records(
    const BstocksCorporateActionRecordsParams& params) const {
    return common::send<BstocksCorporateActionRecordsResponse>(
        *client_, bstocks_corporate_action_records_request(params));
}

common::RestRequest
TokenizedApi::corporate_action_records_request(const CorporateActionRecordsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/corp-action";
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "lastTime", params.last_time);
    common::detail::json::set_param(req.query, "lastId", params.last_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CorporateActionRecordsResponse>
TokenizedApi::corporate_action_records(const CorporateActionRecordsParams& params) const {
    return common::send<CorporateActionRecordsResponse>(*client_,
                                                        corporate_action_records_request(params));
}

common::RestRequest
TokenizedApi::tokenized_convert_history_request(const TokenizedConvertHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/tokenized/history";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "lastId", params.last_id);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TokenizedConvertHistoryResponse>
TokenizedApi::tokenized_convert_history(const TokenizedConvertHistoryParams& params) const {
    return common::send<TokenizedConvertHistoryResponse>(*client_,
                                                         tokenized_convert_history_request(params));
}

common::RestRequest
TokenizedApi::tokenized_convert_status_request(const TokenizedConvertStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/tokenized/convert-status";
    common::detail::json::set_param(req.query, "issuerRequestId", params.issuer_request_id);
    common::detail::json::set_param(req.query, "convertType", params.convert_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TokenizedConvertStatusResponse>
TokenizedApi::tokenized_convert_status(const TokenizedConvertStatusParams& params) const {
    return common::send<TokenizedConvertStatusResponse>(*client_,
                                                        tokenized_convert_status_request(params));
}

common::RestRequest TokenizedApi::tokenized_mint_request(const TokenizedMintParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/tokenized/mint";
    common::detail::json::set_param(req.query, "underlyingAsset", params.underlying_asset);
    common::detail::json::set_param(req.query, "underlyingAssetAmount",
                                    params.underlying_asset_amount);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "tokenizedAssetSettleWalletType",
                                    params.tokenized_asset_settle_wallet_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TokenizedMintResponse>
TokenizedApi::tokenized_mint(const TokenizedMintParams& params) const {
    return common::send<TokenizedMintResponse>(*client_, tokenized_mint_request(params));
}

common::RestRequest
TokenizedApi::tokenized_redeem_request(const TokenizedRedeemParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/tokenized/redeem";
    common::detail::json::set_param(req.query, "tokenizedAsset", params.tokenized_asset);
    common::detail::json::set_param(req.query, "tokenizedAssetAmount",
                                    params.tokenized_asset_amount);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "tokenizedAssetSettleWalletType",
                                    params.tokenized_asset_settle_wallet_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TokenizedRedeemResponse>
TokenizedApi::tokenized_redeem(const TokenizedRedeemParams& params) const {
    return common::send<TokenizedRedeemResponse>(*client_, tokenized_redeem_request(params));
}

} // namespace binance::stocks::rest_api
