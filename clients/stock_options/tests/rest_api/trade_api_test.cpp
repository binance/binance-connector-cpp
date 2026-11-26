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
#include <binance/stock_options/rest_api/trade_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::stock_options::rest_api;
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

TEST(RestApiTradeApi, CancelAllOptionOrders) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllOptionOrdersParams params{};
    const auto res = api.cancel_all_option_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/order/cancel-all");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllOptionOrdersWithOptionalParams) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllOptionOrdersParams params{
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_option_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllOptionOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllOptionOrdersParams params{};
    EXPECT_THROW((void)api.cancel_all_option_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelOptionOrder) {
    const std::string example =
        R"json({"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","status":"S"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelOptionOrderParams params{.order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71"};
    const auto res = api.cancel_option_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/order/cancel");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelOptionOrderWithOptionalParams) {
    const std::string example =
        R"json({"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","status":"S"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelOptionOrderParams params{
        .order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71",
        .recv_window = 5000,
    };
    const auto res = api.cancel_option_order(params);
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

TEST(RestApiTradeApi, CancelOptionOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelOptionOrderParams params{.order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71"};
    EXPECT_THROW((void)api.cancel_option_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, PlaceOptionOrder) {
    const std::string example =
        R"json({"status":"S","orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceOptionOrderParams params{.symbol = "NVDA260930C00100000",
                                        .side = PlaceOptionOrderSideEnum::Buy,
                                        .quantity = "1",
                                        .price = "1.5"};
    const auto res = api.place_option_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/order/place");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceOptionOrderWithOptionalParams) {
    const std::string example =
        R"json({"status":"S","orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceOptionOrderParams params{
        .symbol = "NVDA260930C00100000",
        .side = PlaceOptionOrderSideEnum::Buy,
        .quantity = "1",
        .price = "1.5",
        .quote_asset = "USDC",
        .position_intent = PlaceOptionOrderPositionIntentEnum::BuyToOpen,
        .time_in_force = PlaceOptionOrderTimeInForceEnum::Day,
        .wallet_type = PlaceOptionOrderWalletTypeEnum::Card,
        .client_order_id = "web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a",
        .recv_window = 5000,
    };
    const auto res = api.place_option_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionIntent="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceOptionOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PlaceOptionOrderParams params{.symbol = "NVDA260930C00100000",
                                        .side = PlaceOptionOrderSideEnum::Buy,
                                        .quantity = "1",
                                        .price = "1.5"};
    EXPECT_THROW((void)api.place_option_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, SubmitOptionExercise) {
    const std::string example =
        R"json({"tranId":1234567890,"clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","status":"PROCESSING"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubmitOptionExerciseParams params{.symbol = "NVDA260930C00100000", .quantity = "1"};
    const auto res = api.submit_option_exercise(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/exercise/submit");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SubmitOptionExerciseWithOptionalParams) {
    const std::string example =
        R"json({"tranId":1234567890,"clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","status":"PROCESSING"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubmitOptionExerciseParams params{
        .symbol = "NVDA260930C00100000",
        .quantity = "1",
        .quote_asset = "USDC",
        .client_order_id = "web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a",
        .recv_window = 5000,
    };
    const auto res = api.submit_option_exercise(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SubmitOptionExerciseBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubmitOptionExerciseParams params{.symbol = "NVDA260930C00100000", .quantity = "1"};
    EXPECT_THROW((void)api.submit_option_exercise(params), common::BadRequestError);
}
