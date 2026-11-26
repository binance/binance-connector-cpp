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

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/gift_card/export.hpp>
#include <binance/gift_card/rest_api/models/create_a_dual_token_gift_card_response.hpp>
#include <binance/gift_card/rest_api/models/create_a_single_token_gift_card_response.hpp>
#include <binance/gift_card/rest_api/models/fetch_rsa_public_key_response.hpp>
#include <binance/gift_card/rest_api/models/fetch_token_limit_response.hpp>
#include <binance/gift_card/rest_api/models/redeem_a_binance_gift_card_response.hpp>
#include <binance/gift_card/rest_api/models/verify_binance_gift_card_by_gift_card_number_response.hpp>

namespace binance::gift_card::rest_api {

struct CreateADualTokenGiftCardParams {
    /// The token you want to pay, example: BUSD
    common::Required<std::string> base_token;
    /// The token you want to buy, example: BNB. If faceToken = baseToken, it's the same as
    /// createCode endpoint.
    common::Required<std::string> face_token;
    /// The base token asset quantity, example : 1.002
    common::Required<common::Decimal> base_token_amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CreateASingleTokenGiftCardParams {
    /// The token type contained in the Binance Gift Card
    common::Required<std::string> token;
    /// The amount of the token contained in the Binance Gift Card
    common::Required<common::Decimal> amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FetchRsaPublicKeyParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FetchTokenLimitParams {
    /// The token you want to pay, example: BUSD
    common::Required<std::string> base_token;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RedeemABinanceGiftCardParams {
    /// Redemption code of Binance Gift Card to be redeemed, supports both Plaintext & Encrypted
    /// code.
    common::Required<std::string> code;
    /// Each external unique ID represents a unique user on the partner platform. The function helps
    /// you to identify the redemption behavior of different users, such as redemption frequency and
    /// amount. It also helps risk and limit control of a single account, such as daily limit on
    /// redemption volume, frequency, and incorrect number of entries. This will also prevent a
    /// single user account reach the partner's daily redemption limits. We strongly recommend you
    /// to use this feature and transfer us the User ID of your users if you have different users
    /// redeeming Binance Gift Cards on your platform. To protect user data privacy, you may choose
    /// to transfer the user id in any desired format (max. 400 characters).
    std::optional<std::string> external_uid = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct VerifyBinanceGiftCardByGiftCardNumberParams {
    /// Enter the Gift Card Number
    common::Required<std::string> reference_no;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_GIFT_CARD_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

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
    create_a_dual_token_gift_card(const CreateADualTokenGiftCardParams& params) const;

    /// Asynchronous `create_a_dual_token_gift_card()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateADualTokenGiftCardResponse>)`.
    template <class CompletionToken>
    auto async_create_a_dual_token_gift_card(const CreateADualTokenGiftCardParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<CreateADualTokenGiftCardResponse>(
            client_, create_a_dual_token_gift_card_request(params),
            std::forward<CompletionToken>(token));
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
    create_a_single_token_gift_card(const CreateASingleTokenGiftCardParams& params) const;

    /// Asynchronous `create_a_single_token_gift_card()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateASingleTokenGiftCardResponse>)`.
    template <class CompletionToken>
    auto async_create_a_single_token_gift_card(const CreateASingleTokenGiftCardParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<CreateASingleTokenGiftCardResponse>(
            client_, create_a_single_token_gift_card_request(params),
            std::forward<CompletionToken>(token));
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
    fetch_rsa_public_key(const FetchRsaPublicKeyParams& params = {}) const;

    /// Asynchronous `fetch_rsa_public_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FetchRsaPublicKeyResponse>)`.
    template <class CompletionToken>
    auto async_fetch_rsa_public_key(const FetchRsaPublicKeyParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<FetchRsaPublicKeyResponse>(
            client_, fetch_rsa_public_key_request(params), std::forward<CompletionToken>(token));
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
    fetch_token_limit(const FetchTokenLimitParams& params) const;

    /// Asynchronous `fetch_token_limit()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FetchTokenLimitResponse>)`.
    template <class CompletionToken>
    auto async_fetch_token_limit(const FetchTokenLimitParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<FetchTokenLimitResponse>(
            client_, fetch_token_limit_request(params), std::forward<CompletionToken>(token));
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
    redeem_a_binance_gift_card(const RedeemABinanceGiftCardParams& params) const;

    /// Asynchronous `redeem_a_binance_gift_card()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RedeemABinanceGiftCardResponse>)`.
    template <class CompletionToken>
    auto async_redeem_a_binance_gift_card(const RedeemABinanceGiftCardParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<RedeemABinanceGiftCardResponse>(
            client_, redeem_a_binance_gift_card_request(params),
            std::forward<CompletionToken>(token));
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
        const VerifyBinanceGiftCardByGiftCardNumberParams& params) const;

    /// Asynchronous `verify_binance_gift_card_by_gift_card_number()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<VerifyBinanceGiftCardByGiftCardNumberResponse>)`.
    template <class CompletionToken>
    auto async_verify_binance_gift_card_by_gift_card_number(
        const VerifyBinanceGiftCardByGiftCardNumberParams& params, CompletionToken&& token) const {
        return common::async_send<VerifyBinanceGiftCardByGiftCardNumberResponse>(
            client_, verify_binance_gift_card_by_gift_card_number_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    create_a_dual_token_gift_card_request(const CreateADualTokenGiftCardParams& params) const;
    [[nodiscard]] common::RestRequest
    create_a_single_token_gift_card_request(const CreateASingleTokenGiftCardParams& params) const;
    [[nodiscard]] common::RestRequest
    fetch_rsa_public_key_request(const FetchRsaPublicKeyParams& params) const;
    [[nodiscard]] common::RestRequest
    fetch_token_limit_request(const FetchTokenLimitParams& params) const;
    [[nodiscard]] common::RestRequest
    redeem_a_binance_gift_card_request(const RedeemABinanceGiftCardParams& params) const;
    [[nodiscard]] common::RestRequest verify_binance_gift_card_by_gift_card_number_request(
        const VerifyBinanceGiftCardByGiftCardNumberParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::gift_card::rest_api
