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
#include <binance/convert/rest_api/trade_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::convert::rest_api;
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

TradeApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return TradeApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiTradeApi, AcceptQuote) {
    const std::string example =
        R"json({"orderId":"933256278426274426","createTime":1623381330472,"orderStatus":"PROCESS"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AcceptQuoteParams params{.quote_id = "1"};
    const auto res = api.accept_quote(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/convert/acceptQuote");
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AcceptQuoteWithOptionalParams) {
    const std::string example =
        R"json({"orderId":"933256278426274426","createTime":1623381330472,"orderStatus":"PROCESS"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AcceptQuoteParams params{
        .quote_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.accept_quote(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AcceptQuoteBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AcceptQuoteParams params{.quote_id = "1"};
    EXPECT_THROW((void)api.accept_quote(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelLimitOrder) {
    const std::string example = R"json({"orderId":1603680255057330400,"status":"CANCELED"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelLimitOrderParams params{.order_id = 1603680255057330400};
    const auto res = api.cancel_limit_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/convert/limit/cancelOrder");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelLimitOrderWithOptionalParams) {
    const std::string example = R"json({"orderId":1603680255057330400,"status":"CANCELED"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelLimitOrderParams params{
        .order_id = 1603680255057330400,
        .recv_window = 5000,
    };
    const auto res = api.cancel_limit_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelLimitOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelLimitOrderParams params{.order_id = 1603680255057330400};
    EXPECT_THROW((void)api.cancel_limit_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetConvertTradeHistory) {
    const std::string example =
        R"json({"list":[{"quoteId":"f3b91c525b2644c7bc1e1cd31b6e1aa6","orderId":940708407462087200,"orderStatus":"SUCCESS","fromAsset":"USDT","fromAmount":"20","toAsset":"BNB","toAmount":"0.06154036","ratio":"0.00307702","inverseRatio":"324.99","createTime":1624248872184}],"startTime":1623824139000,"endTime":1626416139000,"limit":100,"moreData":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetConvertTradeHistoryParams params{.start_time = 1623319461670,
                                              .end_time = 1641782889000};
    const auto res = api.get_convert_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/convert/tradeFlow");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetConvertTradeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"list":[{"quoteId":"f3b91c525b2644c7bc1e1cd31b6e1aa6","orderId":940708407462087200,"orderStatus":"SUCCESS","fromAsset":"USDT","fromAmount":"20","toAsset":"BNB","toAmount":"0.06154036","ratio":"0.00307702","inverseRatio":"324.99","createTime":1624248872184}],"startTime":1623824139000,"endTime":1626416139000,"limit":100,"moreData":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetConvertTradeHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 100,
        .recv_window = 5000,
    };
    const auto res = api.get_convert_trade_history(params);
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

TEST(RestApiTradeApi, GetConvertTradeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetConvertTradeHistoryParams params{.start_time = 1623319461670,
                                              .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_convert_trade_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderStatus) {
    const std::string example =
        R"json({"orderId":933256278426274400,"orderStatus":"SUCCESS","fromAsset":"BTC","fromAmount":"0.00054414","toAsset":"USDT","toAmount":"20","ratio":"36755","inverseRatio":"0.00002721","createTime":1623381330472})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderStatusParams params{};
    const auto res = api.order_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/convert/orderStatus");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderStatusWithOptionalParams) {
    const std::string example =
        R"json({"orderId":933256278426274400,"orderStatus":"SUCCESS","fromAsset":"BTC","fromAmount":"0.00054414","toAsset":"USDT","toAmount":"20","ratio":"36755","inverseRatio":"0.00002721","createTime":1623381330472})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderStatusParams params{
        .order_id = "1",
        .quote_id = "1",
    };
    const auto res = api.order_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderStatusParams params{};
    EXPECT_THROW((void)api.order_status(params), common::BadRequestError);
}

TEST(RestApiTradeApi, PlaceLimitOrder) {
    const std::string example = R"json({"orderId":1603680255057330400,"status":"PROCESS"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceLimitOrderParams params{.base_asset = "BTC",
                                       .quote_asset = "USDT",
                                       .limit_price = common::Decimal("1"),
                                       .side = PlaceLimitOrderSideEnum::Buy,
                                       .expired_type =
                                           PlaceLimitOrderExpiredTypeEnum::ExpiredType1D};
    const auto res = api.place_limit_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/convert/limit/placeOrder");
    EXPECT_NE((rec.query() + "&" + rec.body).find("baseAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("expiredType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceLimitOrderWithOptionalParams) {
    const std::string example = R"json({"orderId":1603680255057330400,"status":"PROCESS"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceLimitOrderParams params{
        .base_asset = "BTC",
        .quote_asset = "USDT",
        .limit_price = common::Decimal("1"),
        .side = PlaceLimitOrderSideEnum::Buy,
        .expired_type = PlaceLimitOrderExpiredTypeEnum::ExpiredType1D,
        .base_amount = common::Decimal("1"),
        .quote_amount = common::Decimal("1"),
        .wallet_type = PlaceLimitOrderWalletTypeEnum::Spot,
        .recv_window = 5000,
    };
    const auto res = api.place_limit_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("baseAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("expiredType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("baseAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceLimitOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PlaceLimitOrderParams params{.base_asset = "BTC",
                                       .quote_asset = "USDT",
                                       .limit_price = common::Decimal("1"),
                                       .side = PlaceLimitOrderSideEnum::Buy,
                                       .expired_type =
                                           PlaceLimitOrderExpiredTypeEnum::ExpiredType1D};
    EXPECT_THROW((void)api.place_limit_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryLimitOpenOrders) {
    const std::string example =
        R"json({"list":[{"quoteId":"18sdf87kh9df","orderId":1150901289839,"orderStatus":"SUCCESS","fromAsset":"BNB","fromAmount":"10","toAsset":"USDT","toAmount":"2317.89","ratio":"231.789","inverseRatio":"0.00431427","createTime":1614089498000,"expiredTimestamp":1614099498000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryLimitOpenOrdersParams params{};
    const auto res = api.query_limit_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/convert/limit/queryOpenOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryLimitOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json({"list":[{"quoteId":"18sdf87kh9df","orderId":1150901289839,"orderStatus":"SUCCESS","fromAsset":"BNB","fromAmount":"10","toAsset":"USDT","toAmount":"2317.89","ratio":"231.789","inverseRatio":"0.00431427","createTime":1614089498000,"expiredTimestamp":1614099498000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryLimitOpenOrdersParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_limit_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryLimitOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryLimitOpenOrdersParams params{};
    EXPECT_THROW((void)api.query_limit_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, SendQuoteRequest) {
    const std::string example =
        R"json({"quoteId":"12415572564","ratio":"38163.7","inverseRatio":"0.0000262","validTimestamp":1623319461670,"toAmount":"3816.37","fromAmount":"0.1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SendQuoteRequestParams params{.from_asset = "BTC", .to_asset = "USDT"};
    const auto res = api.send_quote_request(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/convert/getQuote");
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toAsset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SendQuoteRequestWithOptionalParams) {
    const std::string example =
        R"json({"quoteId":"12415572564","ratio":"38163.7","inverseRatio":"0.0000262","validTimestamp":1623319461670,"toAmount":"3816.37","fromAmount":"0.1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SendQuoteRequestParams params{
        .from_asset = "BTC",
        .to_asset = "USDT",
        .from_amount = common::Decimal("1"),
        .to_amount = common::Decimal("1"),
        .wallet_type = SendQuoteRequestWalletTypeEnum::Spot,
        .valid_time = SendQuoteRequestValidTimeEnum::ValidTime10s,
        .recv_window = 5000,
    };
    const auto res = api.send_quote_request(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("validTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SendQuoteRequestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SendQuoteRequestParams params{.from_asset = "BTC", .to_asset = "USDT"};
    EXPECT_THROW((void)api.send_quote_request(params), common::BadRequestError);
}
