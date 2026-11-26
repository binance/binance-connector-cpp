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
#include <binance/stocks/rest_api/trade_api.hpp>

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

TradeApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return TradeApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiTradeApi, CancelAllEquityOrders) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllEquityOrdersParams params{};
    const auto res = api.cancel_all_equity_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/order/cancel-all");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllEquityOrdersWithOptionalParams) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllEquityOrdersParams params{
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_equity_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllEquityOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllEquityOrdersParams params{};
    EXPECT_THROW((void)api.cancel_all_equity_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelEquityOrder) {
    const std::string example =
        R"json({"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","status":"S"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelEquityOrderParams params{.order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71"};
    const auto res = api.cancel_equity_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/order/cancel");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelEquityOrderWithOptionalParams) {
    const std::string example =
        R"json({"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","status":"S"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelEquityOrderParams params{
        .order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71",
        .recv_window = 5000,
    };
    const auto res = api.cancel_equity_order(params);
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

TEST(RestApiTradeApi, CancelEquityOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelEquityOrderParams params{.order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71"};
    EXPECT_THROW((void)api.cancel_equity_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CurrentOpenOrders) {
    const std::string example =
        R"json([{"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","symbol":"AAPL","quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"180.50","avgFilledPrice":"avgFilledPrice","qty":"1","notional":"notional","filledQty":"0","filledTotal":"filledTotal","fee":"0","session":"RTH","status":"NEW","createdAt":1735900000000,"updatedAt":1735900000000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentOpenOrdersParams params{};
    const auto res = api.current_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/order/open-orders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CurrentOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","symbol":"AAPL","quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"180.50","avgFilledPrice":"avgFilledPrice","qty":"1","notional":"notional","filledQty":"0","filledTotal":"filledTotal","fee":"0","session":"RTH","status":"NEW","createdAt":1735900000000,"updatedAt":1735900000000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentOpenOrdersParams params{
        .recv_window = 5000,
    };
    const auto res = api.current_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CurrentOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CurrentOpenOrdersParams params{};
    EXPECT_THROW((void)api.current_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, EquityOrderDetail) {
    const std::string example =
        R"json({"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"AAPL","quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"180.50","avgFilledPrice":"180.48","qty":"1","notional":"notional","filledQty":"1","filledTotal":"filledTotal","fee":"0.10","session":"RTH","status":"FILLED","createdAt":1735900000000,"updatedAt":1735900120000,"trades":[{"executionId":"exec-20260504-0001","executionAt":1735900115000,"price":"180.48","qty":"1"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EquityOrderDetailParams params{};
    const auto res = api.equity_order_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/order/detail");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, EquityOrderDetailWithOptionalParams) {
    const std::string example =
        R"json({"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"AAPL","quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"180.50","avgFilledPrice":"180.48","qty":"1","notional":"notional","filledQty":"1","filledTotal":"filledTotal","fee":"0.10","session":"RTH","status":"FILLED","createdAt":1735900000000,"updatedAt":1735900120000,"trades":[{"executionId":"exec-20260504-0001","executionAt":1735900115000,"price":"180.48","qty":"1"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EquityOrderDetailParams params{
        .order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71",
        .client_order_id = "web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a",
        .recv_window = 5000,
    };
    const auto res = api.equity_order_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, EquityOrderDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EquityOrderDetailParams params{};
    EXPECT_THROW((void)api.equity_order_detail(params), common::BadRequestError);
}

TEST(RestApiTradeApi, EquityOrderHistory) {
    const std::string example =
        R"json({"total":2,"page":1,"size":20,"rows":[{"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","symbol":"AAPL","quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"180.50","avgFilledPrice":"180.48","qty":"1","notional":"notional","filledQty":"1","filledTotal":"filledTotal","fee":"0.10","session":"RTH","status":"FILLED","createdAt":1735900000000,"updatedAt":1735900120000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EquityOrderHistoryParams params{.start_time = 1735800000000, .end_time = 1735900000000};
    const auto res = api.equity_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/order/history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, EquityOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":2,"page":1,"size":20,"rows":[{"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","symbol":"AAPL","quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"180.50","avgFilledPrice":"180.48","qty":"1","notional":"notional","filledQty":"1","filledTotal":"filledTotal","fee":"0.10","session":"RTH","status":"FILLED","createdAt":1735900000000,"updatedAt":1735900120000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EquityOrderHistoryParams params{
        .start_time = 1735800000000,
        .end_time = 1735900000000,
        .symbol = "NVDA",
        .order_type = EquityOrderHistoryOrderTypeEnum::Market,
        .side = EquityOrderHistorySideEnum::Buy,
        .order_status = "FILLED,CANCELED",
        .current = 1,
        .size = 20,
        .recv_window = 5000,
    };
    const auto res = api.equity_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderStatus="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, EquityOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EquityOrderHistoryParams params{.start_time = 1735800000000, .end_time = 1735900000000};
    EXPECT_THROW((void)api.equity_order_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, EquityTradeHistory) {
    const std::string example =
        R"json({"total":1,"page":1,"size":20,"rows":[{"executionId":"exec-20260504-0001","orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","symbol":"AAPL","quote":"USDC","side":"BUY","orderType":"LIMIT","price":"180.50","qty":"1","total":"180.50","executionAt":1735900115000,"updatedAt":1735900115200}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EquityTradeHistoryParams params{.start_time = 1735800000000, .end_time = 1735900000000};
    const auto res = api.equity_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/trade/history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, EquityTradeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"page":1,"size":20,"rows":[{"executionId":"exec-20260504-0001","orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","symbol":"AAPL","quote":"USDC","side":"BUY","orderType":"LIMIT","price":"180.50","qty":"1","total":"180.50","executionAt":1735900115000,"updatedAt":1735900115200}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EquityTradeHistoryParams params{
        .start_time = 1735800000000,
        .end_time = 1735900000000,
        .symbol = "NVDA",
        .side = EquityTradeHistorySideEnum::Buy,
        .order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71",
        .current = 1,
        .size = 20,
        .recv_window = 5000,
    };
    const auto res = api.equity_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, EquityTradeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EquityTradeHistoryParams params{.start_time = 1735800000000, .end_time = 1735900000000};
    EXPECT_THROW((void)api.equity_trade_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, PlaceEquityOrder) {
    const std::string example =
        R"json({"status":"S","orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceEquityOrderParams params{.symbol = "AAPL",
                                        .side = PlaceEquityOrderSideEnum::Buy,
                                        .order_type = PlaceEquityOrderOrderTypeEnum::Market};
    const auto res = api.place_equity_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/order/place");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceEquityOrderWithOptionalParams) {
    const std::string example =
        R"json({"status":"S","orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceEquityOrderParams params{
        .symbol = "AAPL",
        .side = PlaceEquityOrderSideEnum::Buy,
        .order_type = PlaceEquityOrderOrderTypeEnum::Market,
        .quote_asset = "USDC",
        .price = "180.50",
        .quantity = "1",
        .notional = "1000.00",
        .time_in_force = PlaceEquityOrderTimeInForceEnum::Day,
        .trading_session = PlaceEquityOrderTradingSessionEnum::Rth,
        .wallet_type = PlaceEquityOrderWalletTypeEnum::Card,
        .client_order_id = "web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a",
        .tokenize = true,
        .tokenized_asset_settle_wallet_type =
            PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum::Main,
        .recv_window = 5000,
    };
    const auto res = api.place_equity_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("notional="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tradingSession="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenizedAssetSettleWalletType="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceEquityOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PlaceEquityOrderParams params{.symbol = "AAPL",
                                        .side = PlaceEquityOrderSideEnum::Buy,
                                        .order_type = PlaceEquityOrderOrderTypeEnum::Market};
    EXPECT_THROW((void)api.place_equity_order(params), common::BadRequestError);
}
