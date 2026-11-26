//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string>

#include <gtest/gtest.h>

#include <binance/c2c/rest_api/api.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/rest.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::c2c::rest_api;
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

TEST(RestApiDefaultApi, GetC2CTradeHistory) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"orderNumber":"20219644646554779648","advNo":"11218246497340923904","tradeType":"SELL","asset":"BUSD","fiat":"CNY","fiatSymbol":"￥","amount":"5000.00000000","totalPrice":"33400.00000000","unitPrice":"6.68","orderStatus":"COMPLETED","createTime":1619361369000,"commission":"0","counterPartNickName":"阿涛❤***","payMethodName":"BANK","additionalKycVerify":0,"takerCommissionRate":"0","takerCommission":"0","takerAmount":"343.4","advertisementRole":"TAKER"}],"total":1,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetC2CTradeHistoryParams params{};
    const auto res = api.get_c2c_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/c2c/orderMatch/listUserOrderHistory");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetC2CTradeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"orderNumber":"20219644646554779648","advNo":"11218246497340923904","tradeType":"SELL","asset":"BUSD","fiat":"CNY","fiatSymbol":"￥","amount":"5000.00000000","totalPrice":"33400.00000000","unitPrice":"6.68","orderStatus":"COMPLETED","createTime":1619361369000,"commission":"0","counterPartNickName":"阿涛❤***","payMethodName":"BANK","additionalKycVerify":0,"takerCommissionRate":"0","takerCommission":"0","takerAmount":"343.4","advertisementRole":"TAKER"}],"total":1,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetC2CTradeHistoryParams params{
        .trade_type = GetC2CTradeHistoryTradeTypeEnum::Buy,
        .start_timestamp = 1770736694138,
        .end_timestamp = 1770736694138,
        .page = 1,
        .rows = 100,
    };
    const auto res = api.get_c2c_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tradeType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTimestamp="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTimestamp="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("rows="), std::string::npos);
}

TEST(RestApiDefaultApi, GetC2CTradeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetC2CTradeHistoryParams params{};
    EXPECT_THROW((void)api.get_c2c_trade_history(params), common::BadRequestError);
}
