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
#include <binance/margin_trading/rest_api/transfer_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::margin_trading::rest_api;
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

TransferApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return TransferApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiTransferApi, GetCrossMarginTransferHistory) {
    const std::string example =
        R"json({"rows":[{"amount":"0.10000000","asset":"BNB","status":"CONFIRMED","timestamp":1566898617,"txId":5240372201,"type":"ROLL_IN","transFrom":"SPOT","transTo":"ISOLATED_MARGIN","fromSymbol":"BNBUSDT","toSymbol":"BTCUSDT"}],"total":3})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCrossMarginTransferHistoryParams params{};
    const auto res = api.get_cross_margin_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/transfer");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, GetCrossMarginTransferHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"amount":"0.10000000","asset":"BNB","status":"CONFIRMED","timestamp":1566898617,"txId":5240372201,"type":"ROLL_IN","transFrom":"SPOT","transTo":"ISOLATED_MARGIN","fromSymbol":"BNBUSDT","toSymbol":"BTCUSDT"}],"total":3})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCrossMarginTransferHistoryParams params{
        .asset = "BNB",
        .type = GetCrossMarginTransferHistoryTypeEnum::RollIn,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .isolated_symbol = "BNBUSDT",
        .recv_window = 5000,
    };
    const auto res = api.get_cross_margin_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isolatedSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, GetCrossMarginTransferHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCrossMarginTransferHistoryParams params{};
    EXPECT_THROW((void)api.get_cross_margin_transfer_history(params), common::BadRequestError);
}

TEST(RestApiTransferApi, QueryMaxTransferOutAmount) {
    const std::string example = R"json({"amount":"3.59498107"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMaxTransferOutAmountParams params{.asset = "BTC"};
    const auto res = api.query_max_transfer_out_amount(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/maxTransferable");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, QueryMaxTransferOutAmountWithOptionalParams) {
    const std::string example = R"json({"amount":"3.59498107"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMaxTransferOutAmountParams params{
        .asset = "BTC",
        .isolated_symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_max_transfer_out_amount(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isolatedSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, QueryMaxTransferOutAmountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMaxTransferOutAmountParams params{.asset = "BTC"};
    EXPECT_THROW((void)api.query_max_transfer_out_amount(params), common::BadRequestError);
}
