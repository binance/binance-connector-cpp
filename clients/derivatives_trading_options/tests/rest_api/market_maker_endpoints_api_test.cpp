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
#include <binance/derivatives_trading_options/rest_api/market_maker_endpoints_api.hpp>

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

MarketMakerEndpointsApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return MarketMakerEndpointsApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiMarketMakerEndpointsApi, AutoCancelAllOpenOrders) {
    const std::string example = R"json({"underlyings":["BTCUSDT"]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AutoCancelAllOpenOrdersParams params{.underlyings = "BTCUSDT,ETHUSDT"};
    const auto res = api.auto_cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/eapi/v1/countdownCancelAllHeartBeat");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyings="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, AutoCancelAllOpenOrdersWithOptionalParams) {
    const std::string example = R"json({"underlyings":["BTCUSDT"]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AutoCancelAllOpenOrdersParams params{
        .underlyings = "BTCUSDT,ETHUSDT",
        .recv_window = 5000,
    };
    const auto res = api.auto_cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyings="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, AutoCancelAllOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AutoCancelAllOpenOrdersParams params{.underlyings = "BTCUSDT,ETHUSDT"};
    EXPECT_THROW((void)api.auto_cancel_all_open_orders(params), common::BadRequestError);
}

TEST(RestApiMarketMakerEndpointsApi, GetAutoCancelAllOpenOrders) {
    const std::string example = R"json({"underlying":"ETHUSDT","countdownTime":100000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAutoCancelAllOpenOrdersParams params{};
    const auto res = api.get_auto_cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/countdownCancelAll");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, GetAutoCancelAllOpenOrdersWithOptionalParams) {
    const std::string example = R"json({"underlying":"ETHUSDT","countdownTime":100000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAutoCancelAllOpenOrdersParams params{
        .underlying = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.get_auto_cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, GetAutoCancelAllOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetAutoCancelAllOpenOrdersParams params{};
    EXPECT_THROW((void)api.get_auto_cancel_all_open_orders(params), common::BadRequestError);
}

TEST(RestApiMarketMakerEndpointsApi, SetAutoCancelAllOpenOrders) {
    const std::string example = R"json({"underlying":"ETHUSDT","countdownTime":100000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetAutoCancelAllOpenOrdersParams params{.underlying = "BTCUSDT", .countdown_time = 5000};
    const auto res = api.set_auto_cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/eapi/v1/countdownCancelAll");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("countdownTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, SetAutoCancelAllOpenOrdersWithOptionalParams) {
    const std::string example = R"json({"underlying":"ETHUSDT","countdownTime":100000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetAutoCancelAllOpenOrdersParams params{
        .underlying = "BTCUSDT",
        .countdown_time = 5000,
        .recv_window = 5000,
    };
    const auto res = api.set_auto_cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("countdownTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, SetAutoCancelAllOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SetAutoCancelAllOpenOrdersParams params{.underlying = "BTCUSDT", .countdown_time = 5000};
    EXPECT_THROW((void)api.set_auto_cancel_all_open_orders(params), common::BadRequestError);
}

TEST(RestApiMarketMakerEndpointsApi, GetMarketMakerProtectionConfig) {
    const std::string example =
        R"json({"underlyingId":2,"underlying":"BTCUSDT","windowTimeInMilliseconds":3000,"frozenTimeInMilliseconds":300000,"qtyLimit":"2","deltaLimit":"2.3","lastTriggerTime":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetMarketMakerProtectionConfigParams params{.underlying = "BTCUSDT"};
    const auto res = api.get_market_maker_protection_config(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/mmp");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, GetMarketMakerProtectionConfigWithOptionalParams) {
    const std::string example =
        R"json({"underlyingId":2,"underlying":"BTCUSDT","windowTimeInMilliseconds":3000,"frozenTimeInMilliseconds":300000,"qtyLimit":"2","deltaLimit":"2.3","lastTriggerTime":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetMarketMakerProtectionConfigParams params{
        .underlying = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.get_market_maker_protection_config(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, GetMarketMakerProtectionConfigBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetMarketMakerProtectionConfigParams params{.underlying = "BTCUSDT"};
    EXPECT_THROW((void)api.get_market_maker_protection_config(params), common::BadRequestError);
}

TEST(RestApiMarketMakerEndpointsApi, ResetMarketMakerProtectionConfig) {
    const std::string example =
        R"json({"underlyingId":2,"underlying":"BTCUSDT","windowTimeInMilliseconds":3000,"frozenTimeInMilliseconds":300000,"qtyLimit":"2","deltaLimit":"2.3","lastTriggerTime":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ResetMarketMakerProtectionConfigParams params{.underlying = "BTCUSDT"};
    const auto res = api.reset_market_maker_protection_config(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/eapi/v1/mmpReset");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, ResetMarketMakerProtectionConfigWithOptionalParams) {
    const std::string example =
        R"json({"underlyingId":2,"underlying":"BTCUSDT","windowTimeInMilliseconds":3000,"frozenTimeInMilliseconds":300000,"qtyLimit":"2","deltaLimit":"2.3","lastTriggerTime":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ResetMarketMakerProtectionConfigParams params{
        .underlying = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.reset_market_maker_protection_config(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, ResetMarketMakerProtectionConfigBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ResetMarketMakerProtectionConfigParams params{.underlying = "BTCUSDT"};
    EXPECT_THROW((void)api.reset_market_maker_protection_config(params), common::BadRequestError);
}

TEST(RestApiMarketMakerEndpointsApi, SetMarketMakerProtectionConfig) {
    const std::string example =
        R"json({"underlyingId":2,"underlying":"BTCUSDT","windowTimeInMilliseconds":3000,"frozenTimeInMilliseconds":300000,"qtyLimit":"2","deltaLimit":"2.3","lastTriggerTime":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetMarketMakerProtectionConfigParams params{.underlying = "BTCUSDT",
                                                      .window_time_in_milliseconds = 1000,
                                                      .frozen_time_in_milliseconds = 1000,
                                                      .qty_limit = common::Decimal("1.0"),
                                                      .delta_limit = common::Decimal("1.0")};
    const auto res = api.set_market_maker_protection_config(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/eapi/v1/mmpSet");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("windowTimeInMilliseconds="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("frozenTimeInMilliseconds="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("qtyLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("deltaLimit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, SetMarketMakerProtectionConfigWithOptionalParams) {
    const std::string example =
        R"json({"underlyingId":2,"underlying":"BTCUSDT","windowTimeInMilliseconds":3000,"frozenTimeInMilliseconds":300000,"qtyLimit":"2","deltaLimit":"2.3","lastTriggerTime":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetMarketMakerProtectionConfigParams params{
        .underlying = "BTCUSDT",
        .window_time_in_milliseconds = 1000,
        .frozen_time_in_milliseconds = 1000,
        .qty_limit = common::Decimal("1.0"),
        .delta_limit = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.set_market_maker_protection_config(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("windowTimeInMilliseconds="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("frozenTimeInMilliseconds="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("qtyLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("deltaLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerEndpointsApi, SetMarketMakerProtectionConfigBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SetMarketMakerProtectionConfigParams params{.underlying = "BTCUSDT",
                                                      .window_time_in_milliseconds = 1000,
                                                      .frozen_time_in_milliseconds = 1000,
                                                      .qty_limit = common::Decimal("1.0"),
                                                      .delta_limit = common::Decimal("1.0")};
    EXPECT_THROW((void)api.set_market_maker_protection_config(params), common::BadRequestError);
}
