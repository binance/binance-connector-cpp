//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string>

#include <gtest/gtest.h>

#include <binance/common/errors.hpp>
#include <binance/common/rest.hpp>
#include <binance/gift_card/rest_api/market_data_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::gift_card::rest_api;
using binance::test::MockResponse;
using binance::test::MockServer;
using binance::test::RecordedRequest;

namespace {

MockServer::Handler reply(std::string body, unsigned status = 200) {
    return [body = std::move(body), status](const RecordedRequest&) {
        MockResponse r;
        r.status = status;
        r.body = body.empty() ? "{}" : body;
        return r;
    };
}

MarketDataApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return MarketDataApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiMarketDataApi, CreateADualTokenGiftCard) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"referenceNo":"0033002144060553","code":"6H9EKF5ECCWFBHGE","expiredTime":1727417154000},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateADualTokenGiftCardParams params{
        .base_token = "BUSD", .face_token = "BNB", .base_token_amount = common::Decimal("1")};
    const auto res = api.create_a_dual_token_gift_card(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/giftcard/buyCode");
    EXPECT_NE((rec.query() + "&" + rec.body).find("baseToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("faceToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("baseTokenAmount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CreateADualTokenGiftCardWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"referenceNo":"0033002144060553","code":"6H9EKF5ECCWFBHGE","expiredTime":1727417154000},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateADualTokenGiftCardParams params{
        .base_token = "BUSD",
        .face_token = "BNB",
        .base_token_amount = common::Decimal("1"),
        .recv_window = 5000,
    };
    const auto res = api.create_a_dual_token_gift_card(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("baseToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("faceToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("baseTokenAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CreateADualTokenGiftCardBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateADualTokenGiftCardParams params{
        .base_token = "BUSD", .face_token = "BNB", .base_token_amount = common::Decimal("1")};
    EXPECT_THROW((void)api.create_a_dual_token_gift_card(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, CreateASingleTokenGiftCard) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"referenceNo":"0033002144060553","code":"6H9EKF5ECCWFBHGE","expiredTime":1727417154000},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateASingleTokenGiftCardParams params{.token = "BNB", .amount = common::Decimal("1")};
    const auto res = api.create_a_single_token_gift_card(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/giftcard/createCode");
    EXPECT_NE((rec.query() + "&" + rec.body).find("token="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CreateASingleTokenGiftCardWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"referenceNo":"0033002144060553","code":"6H9EKF5ECCWFBHGE","expiredTime":1727417154000},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateASingleTokenGiftCardParams params{
        .token = "BNB",
        .amount = common::Decimal("1"),
        .recv_window = 5000,
    };
    const auto res = api.create_a_single_token_gift_card(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("token="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CreateASingleTokenGiftCardBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateASingleTokenGiftCardParams params{.token = "BNB", .amount = common::Decimal("1")};
    EXPECT_THROW((void)api.create_a_single_token_gift_card(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, FetchRsaPublicKey) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCXBBVKLAc1GQ5FsIFFqOHrPTox5noBONIKr+IAedTR9FkVxq6e65updEbfdhRNkMOeYIO2i0UylrjGC0X8YSoIszmrVHeV0l06Zh1oJuZos1+7N+WLuz9JvlPaawof3GUakTxYWWCa9+8KIbLKsoKMdfS96VT+8iOXO3quMGKUmQIDAQAB","success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FetchRsaPublicKeyParams params{};
    const auto res = api.fetch_rsa_public_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/giftcard/cryptography/rsa-public-key");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, FetchRsaPublicKeyWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCXBBVKLAc1GQ5FsIFFqOHrPTox5noBONIKr+IAedTR9FkVxq6e65updEbfdhRNkMOeYIO2i0UylrjGC0X8YSoIszmrVHeV0l06Zh1oJuZos1+7N+WLuz9JvlPaawof3GUakTxYWWCa9+8KIbLKsoKMdfS96VT+8iOXO3quMGKUmQIDAQAB","success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FetchRsaPublicKeyParams params{
        .recv_window = 5000,
    };
    const auto res = api.fetch_rsa_public_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, FetchRsaPublicKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FetchRsaPublicKeyParams params{};
    EXPECT_THROW((void)api.fetch_rsa_public_key(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, FetchTokenLimit) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"coin":"BNB","fromMin":"0.01","fromMax":"1"}],"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FetchTokenLimitParams params{.base_token = "BUSD"};
    const auto res = api.fetch_token_limit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/giftcard/buyCode/token-limit");
    EXPECT_NE((rec.query() + "&" + rec.body).find("baseToken="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, FetchTokenLimitWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"coin":"BNB","fromMin":"0.01","fromMax":"1"}],"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FetchTokenLimitParams params{
        .base_token = "BUSD",
        .recv_window = 5000,
    };
    const auto res = api.fetch_token_limit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("baseToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, FetchTokenLimitBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FetchTokenLimitParams params{.base_token = "BUSD"};
    EXPECT_THROW((void)api.fetch_token_limit(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, RedeemABinanceGiftCard) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"referenceNo":"0033002328060227","identityNo":"10317392647411060736","token":"BNB","amount":"0.00000001"},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemABinanceGiftCardParams params{.code = "6H9EKF5ECCWFBHGE"};
    const auto res = api.redeem_a_binance_gift_card(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/giftcard/redeemCode");
    EXPECT_NE((rec.query() + "&" + rec.body).find("code="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, RedeemABinanceGiftCardWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"referenceNo":"0033002328060227","identityNo":"10317392647411060736","token":"BNB","amount":"0.00000001"},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemABinanceGiftCardParams params{
        .code = "6H9EKF5ECCWFBHGE",
        .external_uid = "user-123",
        .recv_window = 5000,
    };
    const auto res = api.redeem_a_binance_gift_card(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("code="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("externalUid="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, RedeemABinanceGiftCardBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RedeemABinanceGiftCardParams params{.code = "6H9EKF5ECCWFBHGE"};
    EXPECT_THROW((void)api.redeem_a_binance_gift_card(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, VerifyBinanceGiftCardByGiftCardNumber) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"valid":true,"token":"BNB","amount":"0.00000001"},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VerifyBinanceGiftCardByGiftCardNumberParams params{.reference_no = "0033002328060227"};
    const auto res = api.verify_binance_gift_card_by_gift_card_number(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/giftcard/verify");
    EXPECT_NE((rec.query() + "&" + rec.body).find("referenceNo="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, VerifyBinanceGiftCardByGiftCardNumberWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"valid":true,"token":"BNB","amount":"0.00000001"},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VerifyBinanceGiftCardByGiftCardNumberParams params{
        .reference_no = "0033002328060227",
        .recv_window = 5000,
    };
    const auto res = api.verify_binance_gift_card_by_gift_card_number(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("referenceNo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, VerifyBinanceGiftCardByGiftCardNumberBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const VerifyBinanceGiftCardByGiftCardNumberParams params{.reference_no = "0033002328060227"};
    EXPECT_THROW((void)api.verify_binance_gift_card_by_gift_card_number(params),
                 common::BadRequestError);
}
