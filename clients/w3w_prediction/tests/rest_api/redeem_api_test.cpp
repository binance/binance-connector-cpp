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
#include <binance/w3w_prediction/rest_api/redeem_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::w3w_prediction::rest_api;
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

RedeemApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return RedeemApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiRedeemApi, BatchRedeem) {
    const std::string example =
        R"json({"batchId":"batch_20260525_redeem_001","results":[{"requestId":"req_001","txHash":"0xabc123def456789abcdef123456789abcdef123456789abcdef123456789abcd","status":"PENDING","error":"error"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BatchRedeemParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
                                   .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
                                   .token_ids = std::vector<std::string>{}};
    const auto res = api.batch_redeem(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/batch-redeem");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenIds="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRedeemApi, BatchRedeemWithOptionalParams) {
    const std::string example =
        R"json({"batchId":"batch_20260525_redeem_001","results":[{"requestId":"req_001","txHash":"0xabc123def456789abcdef123456789abcdef123456789abcdef123456789abcd","status":"PENDING","error":"error"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BatchRedeemParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
        .token_ids = std::vector<std::string>{},
        .chain_id = "56",
    };
    const auto res = api.batch_redeem(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("chainId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRedeemApi, BatchRedeemBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const BatchRedeemParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
                                   .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
                                   .token_ids = std::vector<std::string>{}};
    EXPECT_THROW((void)api.batch_redeem(params), common::BadRequestError);
}

TEST(RestApiRedeemApi, GetRedeemStatus) {
    const std::string example =
        R"json({"txHash":"0xabc123def456789abcdef123456789abcdef123456789abcdef123456789abcd","status":"CONFIRMED"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRedeemStatusParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .tx_hash = "0xabc123def456789abcdef123456789abcdef123456789abcdef123456789abcd"};
    const auto res = api.get_redeem_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/redeem/status");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txHash="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRedeemApi, GetRedeemStatusWithOptionalParams) {
    const std::string example =
        R"json({"txHash":"0xabc123def456789abcdef123456789abcdef123456789abcdef123456789abcd","status":"CONFIRMED"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRedeemStatusParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .tx_hash = "0xabc123def456789abcdef123456789abcdef123456789abcdef123456789abcd",
        .recv_window = 5000,
    };
    const auto res = api.get_redeem_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txHash="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRedeemApi, GetRedeemStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetRedeemStatusParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .tx_hash = "0xabc123def456789abcdef123456789abcdef123456789abcdef123456789abcd"};
    EXPECT_THROW((void)api.get_redeem_status(params), common::BadRequestError);
}
