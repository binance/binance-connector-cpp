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
#include <binance/pay/rest_api/api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::pay::rest_api;
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

Api api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return Api(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiDefaultApi, GetPayTradeHistory) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"orderType":"C2C","transactionId":"M_P_71505104267788288","transactionTime":1610090460133,"amount":"23.72469206","currency":"BNB","walletType":1,"walletTypes":[1],"fundsDetail":[{"currency":"USDT","amount":"1.2","walletAssetCost":{"1":"0.6","2":"0.6"}}],"payerInfo":{"name":"Jack","type":"USER","binanceId":"12345678"},"receiverInfo":{"name":"Alan","type":"MERCHANT","email":"alan@binance.com","binanceId":"34355667","accountId":"21326891","countryCode":"1","phoneNumber":"8057651210","mobileCode":"US","extend":{"institutionName":"","cardNumber":"","digitalWalletId":""}}}],"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPayTradeHistoryParams params{};
    const auto res = api.get_pay_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/pay/transactions");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetPayTradeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"orderType":"C2C","transactionId":"M_P_71505104267788288","transactionTime":1610090460133,"amount":"23.72469206","currency":"BNB","walletType":1,"walletTypes":[1],"fundsDetail":[{"currency":"USDT","amount":"1.2","walletAssetCost":{"1":"0.6","2":"0.6"}}],"payerInfo":{"name":"Jack","type":"USER","binanceId":"12345678"},"receiverInfo":{"name":"Alan","type":"MERCHANT","email":"alan@binance.com","binanceId":"34355667","accountId":"21326891","countryCode":"1","phoneNumber":"8057651210","mobileCode":"US","extend":{"institutionName":"","cardNumber":"","digitalWalletId":""}}}],"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPayTradeHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 100,
        .recv_window = 5000,
    };
    const auto res = api.get_pay_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetPayTradeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetPayTradeHistoryParams params{};
    EXPECT_THROW((void)api.get_pay_trade_history(params), common::BadRequestError);
}
