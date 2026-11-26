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
#include <binance/derivatives_trading_options/rest_api/account_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_options::rest_api;
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

AccountApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return AccountApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiAccountApi, AccountFundingFlow) {
    const std::string example =
        R"json([{"id":1125899906842624000,"asset":"USDT","amount":"-0.552","symbol":"BTC-200730-9000-C","type":"FEE","createDate":1592449456000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountFundingFlowParams params{.currency = AccountFundingFlowCurrencyEnum::Usdt};
    const auto res = api.account_funding_flow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/bill");
    EXPECT_NE((rec.query() + "&" + rec.body).find("currency="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountFundingFlowWithOptionalParams) {
    const std::string example =
        R"json([{"id":1125899906842624000,"asset":"USDT","amount":"-0.552","symbol":"BTC-200730-9000-C","type":"FEE","createDate":1592449456000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountFundingFlowParams params{
        .currency = AccountFundingFlowCurrencyEnum::Usdt,
        .record_id = 100000,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.account_funding_flow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("currency="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recordId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountFundingFlowBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountFundingFlowParams params{.currency = AccountFundingFlowCurrencyEnum::Usdt};
    EXPECT_THROW((void)api.account_funding_flow(params), common::BadRequestError);
}

TEST(RestApiAccountApi, OptionMarginAccountInformation) {
    const std::string example =
        R"json({"asset":[{"asset":"USDT","marginBalance":"10099.448","equity":"10094.44662","available":"8725.92524","initialMargin":"1084.52138","maintMargin":"151.00138","unrealizedPNL":"-5.00138","adjustedEquity":"34.13282285"}],"greek":[{"underlying":"BTCUSDT","delta":"-0.05","gamma":"-0.002","theta":"-0.05","vega":"-0.002"}],"time":1762843368098,"canTrade":true,"canDeposit":true,"canWithdraw":true,"reduceOnly":false,"tradeGroupId":-1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionMarginAccountInformationParams params{};
    const auto res = api.option_margin_account_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/marginAccount");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, OptionMarginAccountInformationWithOptionalParams) {
    const std::string example =
        R"json({"asset":[{"asset":"USDT","marginBalance":"10099.448","equity":"10094.44662","available":"8725.92524","initialMargin":"1084.52138","maintMargin":"151.00138","unrealizedPNL":"-5.00138","adjustedEquity":"34.13282285"}],"greek":[{"underlying":"BTCUSDT","delta":"-0.05","gamma":"-0.002","theta":"-0.05","vega":"-0.002"}],"time":1762843368098,"canTrade":true,"canDeposit":true,"canWithdraw":true,"reduceOnly":false,"tradeGroupId":-1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionMarginAccountInformationParams params{
        .recv_window = 5000,
    };
    const auto res = api.option_margin_account_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, OptionMarginAccountInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionMarginAccountInformationParams params{};
    EXPECT_THROW((void)api.option_margin_account_information(params), common::BadRequestError);
}
