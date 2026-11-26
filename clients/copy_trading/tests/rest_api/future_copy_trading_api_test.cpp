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
#include <binance/copy_trading/rest_api/future_copy_trading_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::copy_trading::rest_api;
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

FutureCopyTradingApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return FutureCopyTradingApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiFutureCopyTradingApi, GetFuturesLeadTraderStatus) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"isLeadTrader":true,"time":1717382310843},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesLeadTraderStatusParams params{};
    const auto res = api.get_futures_lead_trader_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/copyTrading/futures/userStatus");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureCopyTradingApi, GetFuturesLeadTraderStatusWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"isLeadTrader":true,"time":1717382310843},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesLeadTraderStatusParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_futures_lead_trader_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureCopyTradingApi, GetFuturesLeadTraderStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesLeadTraderStatusParams params{};
    EXPECT_THROW((void)api.get_futures_lead_trader_status(params), common::BadRequestError);
}

TEST(RestApiFutureCopyTradingApi, GetFuturesLeadTradingSymbolWhitelist) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"symbol":"BTCUSDT","baseAsset":"BTC","quoteAsset":"USDT"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesLeadTradingSymbolWhitelistParams params{};
    const auto res = api.get_futures_lead_trading_symbol_whitelist(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/copyTrading/futures/leadSymbol");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureCopyTradingApi, GetFuturesLeadTradingSymbolWhitelistWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"symbol":"BTCUSDT","baseAsset":"BTC","quoteAsset":"USDT"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesLeadTradingSymbolWhitelistParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_futures_lead_trading_symbol_whitelist(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureCopyTradingApi, GetFuturesLeadTradingSymbolWhitelistBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesLeadTradingSymbolWhitelistParams params{};
    EXPECT_THROW((void)api.get_futures_lead_trading_symbol_whitelist(params),
                 common::BadRequestError);
}
