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
#include <binance/gift_card/export.hpp>
#include <binance/gift_card/rest_api/market_data_api.hpp>
#include <binance/gift_card/rest_api/models.hpp>

namespace binance::gift_card::rest_api {

/// GiftCard REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_GIFT_CARD_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Gift Card REST API).
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

    // MarketDataApi

    /// Create a dual-token gift card (fixed value, discount feature) (TRADE)
    ///
    /// POST /sapi/v1/giftcard/buyCode.
    ///
    /// * This API is for creating a dual-token ( stablecoin-denominated) Binance Gift Card. You may
    /// create a gift card using USDT as baseToken, that is redeemable to another designated token
    /// (faceToken). For example, you can create a fixed-value BTC gift card and pay with 100 USDT
    /// plus minting fee. This gift card can keep the value fixed at 100 USDT before redemption, and
    /// will be redeemable to BTC equivalent to 100 USDT upon redemption.
    ///
    /// * Once successfully created, the amount of baseToken (e.g. USDT) in the fixed-value gift
    /// card along with the fee would be deducted from your Spot wallet.
    ///   * To get started with, please make sure:
    ///   * You have a Binance account
    ///   * You have passed KYB
    ///   * You have a sufﬁcient balance(Gift Card amount and fee amount) in your Binance Spot
    ///   wallet
    ///   * You need Enable Withdrawals for the API Key which requests this endpoint.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-gift-card/api/rest-api/market-data#create-adual-token-gift-card
    [[nodiscard]] common::RestApiResponse<CreateADualTokenGiftCardResponse>
    create_a_dual_token_gift_card(const CreateADualTokenGiftCardParams& params) const {
        return market_data_api_.create_a_dual_token_gift_card(params);
    }
    /// Asynchronous `create_a_dual_token_gift_card()`.
    template <class CompletionToken>
    auto async_create_a_dual_token_gift_card(const CreateADualTokenGiftCardParams& params,
                                             CompletionToken&& token) const {
        return market_data_api_.async_create_a_dual_token_gift_card(
            params, std::forward<CompletionToken>(token));
    }

    /// Create a single-token gift card (USER_DATA)
    ///
    /// POST /sapi/v1/giftcard/createCode.
    ///
    /// This API is for creating a Binance Gift Card.
    ///
    /// To get started with, please make sure:
    ///   * You have a Binance account
    ///   * You have passed KYB
    ///   * You have a sufﬁcient balance(Gift Card amount and fee amount) in your Binance Spot
    ///   wallet
    ///   * You need `Enable Withdrawals` for the API Key which requests this endpoint.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-gift-card/api/rest-api/market-data#create-asingle-token-gift-card
    [[nodiscard]] common::RestApiResponse<CreateASingleTokenGiftCardResponse>
    create_a_single_token_gift_card(const CreateASingleTokenGiftCardParams& params) const {
        return market_data_api_.create_a_single_token_gift_card(params);
    }
    /// Asynchronous `create_a_single_token_gift_card()`.
    template <class CompletionToken>
    auto async_create_a_single_token_gift_card(const CreateASingleTokenGiftCardParams& params,
                                               CompletionToken&& token) const {
        return market_data_api_.async_create_a_single_token_gift_card(
            params, std::forward<CompletionToken>(token));
    }

    /// Fetch RSA Public Key (USER_DATA)
    ///
    /// GET /sapi/v1/giftcard/cryptography/rsa-public-key.
    ///
    /// This API is for fetching the RSA Public Key.
    /// This RSA Public key will be used to encrypt the card code.
    ///
    /// **Please note that the RSA Public key fetched is valid only for the current day.**
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-gift-card/api/rest-api/market-data#fetch-rsa-public-key
    [[nodiscard]] common::RestApiResponse<FetchRsaPublicKeyResponse>
    fetch_rsa_public_key(const FetchRsaPublicKeyParams& params = {}) const {
        return market_data_api_.fetch_rsa_public_key(params);
    }
    /// Asynchronous `fetch_rsa_public_key()`.
    template <class CompletionToken>
    auto async_fetch_rsa_public_key(const FetchRsaPublicKeyParams& params,
                                    CompletionToken&& token) const {
        return market_data_api_.async_fetch_rsa_public_key(params,
                                                           std::forward<CompletionToken>(token));
    }

    /// Fetch Token Limit (USER_DATA)
    ///
    /// GET /sapi/v1/giftcard/buyCode/token-limit.
    ///
    /// This API is to help you verify which tokens are available for you to create
    /// Stablecoin-Denominated gift cards as mentioned in section 2 and its’ limitation.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-gift-card/api/rest-api/market-data#fetch-token-limit
    [[nodiscard]] common::RestApiResponse<FetchTokenLimitResponse>
    fetch_token_limit(const FetchTokenLimitParams& params) const {
        return market_data_api_.fetch_token_limit(params);
    }
    /// Asynchronous `fetch_token_limit()`.
    template <class CompletionToken>
    auto async_fetch_token_limit(const FetchTokenLimitParams& params,
                                 CompletionToken&& token) const {
        return market_data_api_.async_fetch_token_limit(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Redeem a Binance Gift Card (USER_DATA)
    ///
    /// POST /sapi/v1/giftcard/redeemCode.
    ///
    /// This API is for redeeming a Binance Gift Card. Once redeemed, the coins will be deposited in
    /// your Spot wallet.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Parameter `code` can be sent in two formats: `Plaintext` and `Encrypted`.
    /// - Sending `code` in encrypted format is more secure than plaintext.
    /// - To send encrypted `code`:
    ///   - Fetch RSA public key from `GET /sapi/v1/giftcard/cryptography/rsa-public-key`.
    ///   - Encrypt card code using `RSA/ECB/OAEPWithSHA-256AndMGF1Padding`.
    /// - If you enter the wrong redemption code 5 times within 24 hours, you will no longer be able
    /// to redeem any Binance Gift Cards that day.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-gift-card/api/rest-api/market-data#redeem-abinance-gift-card
    [[nodiscard]] common::RestApiResponse<RedeemABinanceGiftCardResponse>
    redeem_a_binance_gift_card(const RedeemABinanceGiftCardParams& params) const {
        return market_data_api_.redeem_a_binance_gift_card(params);
    }
    /// Asynchronous `redeem_a_binance_gift_card()`.
    template <class CompletionToken>
    auto async_redeem_a_binance_gift_card(const RedeemABinanceGiftCardParams& params,
                                          CompletionToken&& token) const {
        return market_data_api_.async_redeem_a_binance_gift_card(
            params, std::forward<CompletionToken>(token));
    }

    /// Verify Binance Gift Card by Gift Card Number (USER_DATA)
    ///
    /// GET /sapi/v1/giftcard/verify.
    ///
    /// This API is for verifying whether the Binance Gift Card is valid or not by entering Gift
    /// Card Number.
    ///
    /// **Please note that if you enter the wrong Gift Card Number 5 times within an hour, you will
    /// no longer be able to verify any Gift Card Number for that hour.**
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-gift-card/api/rest-api/market-data#verify-binance-gift-card-by-gift-card-number
    [[nodiscard]] common::RestApiResponse<VerifyBinanceGiftCardByGiftCardNumberResponse>
    verify_binance_gift_card_by_gift_card_number(
        const VerifyBinanceGiftCardByGiftCardNumberParams& params) const {
        return market_data_api_.verify_binance_gift_card_by_gift_card_number(params);
    }
    /// Asynchronous `verify_binance_gift_card_by_gift_card_number()`.
    template <class CompletionToken>
    auto async_verify_binance_gift_card_by_gift_card_number(
        const VerifyBinanceGiftCardByGiftCardNumberParams& params, CompletionToken&& token) const {
        return market_data_api_.async_verify_binance_gift_card_by_gift_card_number(
            params, std::forward<CompletionToken>(token));
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
    MarketDataApi market_data_api_;
};

} // namespace binance::gift_card::rest_api
