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
#include <binance/stocks/rest_api/tokenized_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::stocks::rest_api;
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

TokenizedApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return TokenizedApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiTokenizedApi, BstocksCorporateActionRecords) {
    const std::string example =
        R"json({"items":[{"id":123456,"userId":100001,"assetCode":"EQ_AAPL","eventType":"FORWARD_SPLIT","amount":"10.50000000","dbModifyTime":1795593600000}],"nextTime":1795593600000,"nextId":123456})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BstocksCorporateActionRecordsParams params{.limit = 20};
    const auto res = api.bstocks_corporate_action_records(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/bstocks/corp-action");
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, BstocksCorporateActionRecordsWithOptionalParams) {
    const std::string example =
        R"json({"items":[{"id":123456,"userId":100001,"assetCode":"EQ_AAPL","eventType":"FORWARD_SPLIT","amount":"10.50000000","dbModifyTime":1795593600000}],"nextTime":1795593600000,"nextId":123456})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BstocksCorporateActionRecordsParams params{
        .limit = 20,
        .last_time = 1795593600000,
        .last_id = 123456,
        .recv_window = 5000,
    };
    const auto res = api.bstocks_corporate_action_records(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("lastTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("lastId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, BstocksCorporateActionRecordsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const BstocksCorporateActionRecordsParams params{.limit = 20};
    EXPECT_THROW((void)api.bstocks_corporate_action_records(params), common::BadRequestError);
}

TEST(RestApiTokenizedApi, CorporateActionRecords) {
    const std::string example =
        R"json({"items":[{"id":123456,"userId":100001,"assetCode":"EQ_AAPL","eventType":"FORWARD_SPLIT","amount":"10.50000000","dbModifyTime":1795593600000}],"nextTime":1795593600000,"nextId":123456})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CorporateActionRecordsParams params{.limit = 20};
    const auto res = api.corporate_action_records(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/corp-action");
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, CorporateActionRecordsWithOptionalParams) {
    const std::string example =
        R"json({"items":[{"id":123456,"userId":100001,"assetCode":"EQ_AAPL","eventType":"FORWARD_SPLIT","amount":"10.50000000","dbModifyTime":1795593600000}],"nextTime":1795593600000,"nextId":123456})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CorporateActionRecordsParams params{
        .limit = 20,
        .last_time = 1795593600000,
        .last_id = 123456,
        .recv_window = 5000,
    };
    const auto res = api.corporate_action_records(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("lastTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("lastId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, CorporateActionRecordsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CorporateActionRecordsParams params{.limit = 20};
    EXPECT_THROW((void)api.corporate_action_records(params), common::BadRequestError);
}

TEST(RestApiTokenizedApi, TokenizedConvertHistory) {
    const std::string example =
        R"json({"rows":[{"underlyingAsset":"AAPL","underlyingAssetAmount":"1.000000000","tokenizedAsset":"AAPLB","tokenizedAssetAmount":"1.000000000","issuerRequestId":"mint-20260505-8f3b9e1a2d3c4b5a","convertType":"MINT","status":"S","createdAt":1735900000000,"updatedAt":1735900060000,"tokenizedAssetSettleWalletType":"CARD"}],"hasMore":true,"nextLastId":10020})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TokenizedConvertHistoryParams params{};
    const auto res = api.tokenized_convert_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/tokenized/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, TokenizedConvertHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"underlyingAsset":"AAPL","underlyingAssetAmount":"1.000000000","tokenizedAsset":"AAPLB","tokenizedAssetAmount":"1.000000000","issuerRequestId":"mint-20260505-8f3b9e1a2d3c4b5a","convertType":"MINT","status":"S","createdAt":1735900000000,"updatedAt":1735900060000,"tokenizedAssetSettleWalletType":"CARD"}],"hasMore":true,"nextLastId":10020})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TokenizedConvertHistoryParams params{
        .start_time = 1735800000000,
        .end_time = 1735900000000,
        .last_id = 10019,
        .size = 20,
        .recv_window = 5000,
    };
    const auto res = api.tokenized_convert_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("lastId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, TokenizedConvertHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TokenizedConvertHistoryParams params{};
    EXPECT_THROW((void)api.tokenized_convert_history(params), common::BadRequestError);
}

TEST(RestApiTokenizedApi, TokenizedConvertStatus) {
    const std::string example =
        R"json({"underlyingAsset":"AAPL","underlyingAssetAmount":"1.000000000","tokenizedAsset":"AAPLB","tokenizedAssetAmount":"1.000000000","issuerRequestId":"mint-20260505-8f3b9e1a2d3c4b5a","convertType":"MINT","status":"S","createdAt":1735900000000,"updatedAt":1735900060000,"tokenizedAssetSettleWalletType":"CARD"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TokenizedConvertStatusParams params{.issuer_request_id = "mint-20260505-8f3b9e1a2d3c4b5a",
                                              .convert_type =
                                                  TokenizedConvertStatusConvertTypeEnum::Mint};
    const auto res = api.tokenized_convert_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/tokenized/convert-status");
    EXPECT_NE((rec.query() + "&" + rec.body).find("issuerRequestId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("convertType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, TokenizedConvertStatusWithOptionalParams) {
    const std::string example =
        R"json({"underlyingAsset":"AAPL","underlyingAssetAmount":"1.000000000","tokenizedAsset":"AAPLB","tokenizedAssetAmount":"1.000000000","issuerRequestId":"mint-20260505-8f3b9e1a2d3c4b5a","convertType":"MINT","status":"S","createdAt":1735900000000,"updatedAt":1735900060000,"tokenizedAssetSettleWalletType":"CARD"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TokenizedConvertStatusParams params{
        .issuer_request_id = "mint-20260505-8f3b9e1a2d3c4b5a",
        .convert_type = TokenizedConvertStatusConvertTypeEnum::Mint,
        .recv_window = 5000,
    };
    const auto res = api.tokenized_convert_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("issuerRequestId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("convertType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, TokenizedConvertStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TokenizedConvertStatusParams params{.issuer_request_id = "mint-20260505-8f3b9e1a2d3c4b5a",
                                              .convert_type =
                                                  TokenizedConvertStatusConvertTypeEnum::Mint};
    EXPECT_THROW((void)api.tokenized_convert_status(params), common::BadRequestError);
}

TEST(RestApiTokenizedApi, TokenizedMint) {
    const std::string example =
        R"json({"issuerRequestId":"mint-20260505-8f3b9e1a2d3c4b5a","status":"P","tokenizedAssetSettleWalletType":"CARD"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TokenizedMintParams params{.underlying_asset = "AAPL", .underlying_asset_amount = "1"};
    const auto res = api.tokenized_mint(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/tokenized/mint");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingAssetAmount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, TokenizedMintWithOptionalParams) {
    const std::string example =
        R"json({"issuerRequestId":"mint-20260505-8f3b9e1a2d3c4b5a","status":"P","tokenizedAssetSettleWalletType":"CARD"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TokenizedMintParams params{
        .underlying_asset = "AAPL",
        .underlying_asset_amount = "1",
        .client_order_id = "mint-client-id-32chars-0000000001",
        .tokenized_asset_settle_wallet_type = TokenizedMintTokenizedAssetSettleWalletTypeEnum::Main,
        .recv_window = 5000,
    };
    const auto res = api.tokenized_mint(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingAssetAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenizedAssetSettleWalletType="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, TokenizedMintBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TokenizedMintParams params{.underlying_asset = "AAPL", .underlying_asset_amount = "1"};
    EXPECT_THROW((void)api.tokenized_mint(params), common::BadRequestError);
}

TEST(RestApiTokenizedApi, TokenizedRedeem) {
    const std::string example =
        R"json({"issuerRequestId":"redeem-20260505-a1b2c3d4e5f6","status":"P","tokenizedAssetSettleWalletType":"CARD"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TokenizedRedeemParams params{.tokenized_asset = "AAPLB", .tokenized_asset_amount = "1"};
    const auto res = api.tokenized_redeem(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/tokenized/redeem");
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenizedAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenizedAssetAmount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, TokenizedRedeemWithOptionalParams) {
    const std::string example =
        R"json({"issuerRequestId":"redeem-20260505-a1b2c3d4e5f6","status":"P","tokenizedAssetSettleWalletType":"CARD"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TokenizedRedeemParams params{
        .tokenized_asset = "AAPLB",
        .tokenized_asset_amount = "1",
        .client_order_id = "redeem-client-id-32chars-000000001",
        .tokenized_asset_settle_wallet_type =
            TokenizedRedeemTokenizedAssetSettleWalletTypeEnum::Main,
        .recv_window = 5000,
    };
    const auto res = api.tokenized_redeem(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenizedAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenizedAssetAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenizedAssetSettleWalletType="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTokenizedApi, TokenizedRedeemBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TokenizedRedeemParams params{.tokenized_asset = "AAPLB", .tokenized_asset_amount = "1"};
    EXPECT_THROW((void)api.tokenized_redeem(params), common::BadRequestError);
}
