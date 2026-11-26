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
#include <binance/stock_options/rest_api/user_data_api.hpp>

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

UserDataApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return UserDataApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiUserDataApi, CurrentOpenOptionOrders) {
    const std::string example =
        R"json([{"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionIntent":"BUY_TO_OPEN","quoteAsset":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"1.5","qty":"1","filledQty":"0","filledNotional":"0","totalCost":"150.65","filledPercent":"0","status":"NEW","createdAt":1790173800000,"updatedAt":1790173800000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentOpenOptionOrdersParams params{};
    const auto res = api.current_open_option_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/order/open-orders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, CurrentOpenOptionOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionIntent":"BUY_TO_OPEN","quoteAsset":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"1.5","qty":"1","filledQty":"0","filledNotional":"0","totalCost":"150.65","filledPercent":"0","status":"NEW","createdAt":1790173800000,"updatedAt":1790173800000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentOpenOptionOrdersParams params{
        .recv_window = 5000,
    };
    const auto res = api.current_open_option_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, CurrentOpenOptionOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CurrentOpenOptionOrdersParams params{};
    EXPECT_THROW((void)api.current_open_option_orders(params), common::BadRequestError);
}

TEST(RestApiUserDataApi, ExercisableOptions) {
    const std::string example =
        R"json([{"symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionQty":"2","availableQty":"2","deliverables":[{"type":"EQUITY","symbol":"NVDA","amount":"100"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExercisableOptionsParams params{};
    const auto res = api.exercisable_options(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/exercise/exercisable");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, ExercisableOptionsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionQty":"2","availableQty":"2","deliverables":[{"type":"EQUITY","symbol":"NVDA","amount":"100"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExercisableOptionsParams params{
        .recv_window = 5000,
    };
    const auto res = api.exercisable_options(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, ExercisableOptionsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ExercisableOptionsParams params{};
    EXPECT_THROW((void)api.exercisable_options(params), common::BadRequestError);
}

TEST(RestApiUserDataApi, OptionExerciseDetail) {
    const std::string example =
        R"json({"tranId":1234567890,"clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"requestedQty":"2","status":"SUCCESS","requestedTime":1790704800000,"updateTime":1790766761000,"optionEventId":"a7f3c2e1-4b5d-4e8f-9c0a-1b2c3d4e5f60","underlyingEventId":"c9d8e7f6-a5b4-4c3d-8e2f-1a0b9c8d7e6f","multiplier":"100","errorCode":"497505"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionExerciseDetailParams params{};
    const auto res = api.option_exercise_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/exercise/detail");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionExerciseDetailWithOptionalParams) {
    const std::string example =
        R"json({"tranId":1234567890,"clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"requestedQty":"2","status":"SUCCESS","requestedTime":1790704800000,"updateTime":1790766761000,"optionEventId":"a7f3c2e1-4b5d-4e8f-9c0a-1b2c3d4e5f60","underlyingEventId":"c9d8e7f6-a5b4-4c3d-8e2f-1a0b9c8d7e6f","multiplier":"100","errorCode":"497505"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionExerciseDetailParams params{
        .tran_id = 1234567890,
        .client_order_id = "web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a",
        .recv_window = 5000,
    };
    const auto res = api.option_exercise_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tranId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionExerciseDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionExerciseDetailParams params{};
    EXPECT_THROW((void)api.option_exercise_detail(params), common::BadRequestError);
}

TEST(RestApiUserDataApi, OptionExerciseHistory) {
    const std::string example =
        R"json({"total":1,"page":1,"size":20,"rows":[{"tranId":1234567890,"clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"requestedQty":"2","status":"SUCCESS","requestedTime":1790704800000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionExerciseHistoryParams params{};
    const auto res = api.option_exercise_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/exercise/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionExerciseHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"page":1,"size":20,"rows":[{"tranId":1234567890,"clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"requestedQty":"2","status":"SUCCESS","requestedTime":1790704800000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionExerciseHistoryParams params{
        .status = "SUCCESS,FAILED",
        .start_time = 1790600000000,
        .end_time = 1790800000000,
        .current = 1,
        .size = 20,
        .recv_window = 5000,
    };
    const auto res = api.option_exercise_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionExerciseHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionExerciseHistoryParams params{};
    EXPECT_THROW((void)api.option_exercise_history(params), common::BadRequestError);
}

TEST(RestApiUserDataApi, OptionOrderDetail) {
    const std::string example =
        R"json({"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionIntent":"BUY_TO_OPEN","autoLiquidation":false,"quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"1.5","avgFilledPrice":"1.48","qty":"1","filledQty":"1","filledTotal":"148","fee":"0.65","status":"FILLED","createdAt":1790173800000,"updatedAt":1790173802000,"timeInForce":"DAY","commission":"0.6","platformFee":"0","sec":"0","taf":"0","cat":"0.01","orf":"0.02","occ":"0.02","total":"148","filledAt":1790173802000,"canceledAt":1790173802000,"expiredAt":1790173802000,"settlementDate":1790272800000,"trades":[{"executionId":"8f2d0c1e-5b7a-4e3c-9d61-2a4b6c8e0f13","executionAt":1790173802000,"price":"1.48","qty":"1"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionOrderDetailParams params{};
    const auto res = api.option_order_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/order/detail");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionOrderDetailWithOptionalParams) {
    const std::string example =
        R"json({"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionIntent":"BUY_TO_OPEN","autoLiquidation":false,"quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"1.5","avgFilledPrice":"1.48","qty":"1","filledQty":"1","filledTotal":"148","fee":"0.65","status":"FILLED","createdAt":1790173800000,"updatedAt":1790173802000,"timeInForce":"DAY","commission":"0.6","platformFee":"0","sec":"0","taf":"0","cat":"0.01","orf":"0.02","occ":"0.02","total":"148","filledAt":1790173802000,"canceledAt":1790173802000,"expiredAt":1790173802000,"settlementDate":1790272800000,"trades":[{"executionId":"8f2d0c1e-5b7a-4e3c-9d61-2a4b6c8e0f13","executionAt":1790173802000,"price":"1.48","qty":"1"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionOrderDetailParams params{
        .order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71",
        .client_order_id = "web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a",
        .recv_window = 5000,
    };
    const auto res = api.option_order_detail(params);
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

TEST(RestApiUserDataApi, OptionOrderDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionOrderDetailParams params{};
    EXPECT_THROW((void)api.option_order_detail(params), common::BadRequestError);
}

TEST(RestApiUserDataApi, OptionOrderHistory) {
    const std::string example =
        R"json({"total":1,"page":1,"size":20,"rows":[{"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionIntent":"BUY_TO_OPEN","autoLiquidation":false,"quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"1.5","avgFilledPrice":"1.48","qty":"1","filledQty":"1","filledTotal":"148","fee":"0.65","status":"FILLED","createdAt":1790173800000,"updatedAt":1790173802000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionOrderHistoryParams params{.start_time = 1790100000000, .end_time = 1790200000000};
    const auto res = api.option_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/order/history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"page":1,"size":20,"rows":[{"orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionIntent":"BUY_TO_OPEN","autoLiquidation":false,"quote":"USDC","side":"BUY","orderType":"LIMIT","limitPrice":"1.5","avgFilledPrice":"1.48","qty":"1","filledQty":"1","filledTotal":"148","fee":"0.65","status":"FILLED","createdAt":1790173800000,"updatedAt":1790173802000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionOrderHistoryParams params{
        .start_time = 1790100000000,
        .end_time = 1790200000000,
        .underlying_symbol = "NVDA",
        .side = OptionOrderHistorySideEnum::Buy,
        .order_status = "FILLED,CANCELED",
        .current = 1,
        .size = 20,
        .recv_window = 5000,
    };
    const auto res = api.option_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderStatus="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionOrderHistoryParams params{.start_time = 1790100000000, .end_time = 1790200000000};
    EXPECT_THROW((void)api.option_order_history(params), common::BadRequestError);
}

TEST(RestApiUserDataApi, OptionPositions) {
    const std::string example =
        R"json([{"symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","contractType":"CALL","side":"LONG","free":"2","locked":"1","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionPositionsParams params{};
    const auto res = api.option_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/position");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionPositionsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","contractType":"CALL","side":"LONG","free":"2","locked":"1","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionPositionsParams params{
        .recv_window = 5000,
    };
    const auto res = api.option_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionPositionsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionPositionsParams params{};
    EXPECT_THROW((void)api.option_positions(params), common::BadRequestError);
}

TEST(RestApiUserDataApi, OptionSettlementEventDetail) {
    const std::string example =
        R"json({"eventId":"a7f3c2e1-4b5d-4e8f-9c0a-1b2c3d4e5f60","eventType":"EXERCISE","status":"Completed","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","contractType":"CALL","contracts":"2","expirationDate":1790784000000,"strikePrice":"100","shareDelta":"200","deliverables":[{"type":"OPEXC","symbol":"USDC","amount":"-20000"}],"eventTime":1790766761000,"settlementKind":"PHYSICAL","underlyingPrice":"123.45","cashDirection":"DEBIT","amount":"20000","collateralRelease":[{"symbol":"USDC","amount":"9000"}],"updatedTime":1790766761000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionSettlementEventDetailParams params{.event_id =
                                                       "a7f3c2e1-4b5d-4e8f-9c0a-1b2c3d4e5f60"};
    const auto res = api.option_settlement_event_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/event/detail");
    EXPECT_NE((rec.query() + "&" + rec.body).find("eventId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionSettlementEventDetailWithOptionalParams) {
    const std::string example =
        R"json({"eventId":"a7f3c2e1-4b5d-4e8f-9c0a-1b2c3d4e5f60","eventType":"EXERCISE","status":"Completed","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","contractType":"CALL","contracts":"2","expirationDate":1790784000000,"strikePrice":"100","shareDelta":"200","deliverables":[{"type":"OPEXC","symbol":"USDC","amount":"-20000"}],"eventTime":1790766761000,"settlementKind":"PHYSICAL","underlyingPrice":"123.45","cashDirection":"DEBIT","amount":"20000","collateralRelease":[{"symbol":"USDC","amount":"9000"}],"updatedTime":1790766761000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionSettlementEventDetailParams params{
        .event_id = "a7f3c2e1-4b5d-4e8f-9c0a-1b2c3d4e5f60",
        .recv_window = 5000,
    };
    const auto res = api.option_settlement_event_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("eventId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionSettlementEventDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionSettlementEventDetailParams params{.event_id =
                                                       "a7f3c2e1-4b5d-4e8f-9c0a-1b2c3d4e5f60"};
    EXPECT_THROW((void)api.option_settlement_event_detail(params), common::BadRequestError);
}

TEST(RestApiUserDataApi, OptionSettlementEventHistory) {
    const std::string example =
        R"json({"rows":[{"eventId":"a7f3c2e1-4b5d-4e8f-9c0a-1b2c3d4e5f60","eventType":"EXERCISE","status":"Completed","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","contractType":"CALL","contracts":"2","expirationDate":1790784000000,"strikePrice":"100","shareDelta":"200","deliverables":[{"type":"OPEXC","symbol":"USDC","amount":"-20000"}],"eventTime":1790766760000}],"hasMore":false,"nextLastId":10086})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionSettlementEventHistoryParams params{};
    const auto res = api.option_settlement_event_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/event/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionSettlementEventHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"eventId":"a7f3c2e1-4b5d-4e8f-9c0a-1b2c3d4e5f60","eventType":"EXERCISE","status":"Completed","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","contractType":"CALL","contracts":"2","expirationDate":1790784000000,"strikePrice":"100","shareDelta":"200","deliverables":[{"type":"OPEXC","symbol":"USDC","amount":"-20000"}],"eventTime":1790766760000}],"hasMore":false,"nextLastId":10086})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionSettlementEventHistoryParams params{
        .underlying_symbol = "NVDA",
        .symbol = "NVDA260930C00100000",
        .event_type = "EXERCISE,ASSIGNMENT",
        .start_time = 1790700000000,
        .end_time = 1790900000000,
        .last_id = 10086,
        .size = 20,
        .recv_window = 5000,
    };
    const auto res = api.option_settlement_event_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("eventType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("lastId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionSettlementEventHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionSettlementEventHistoryParams params{};
    EXPECT_THROW((void)api.option_settlement_event_history(params), common::BadRequestError);
}

TEST(RestApiUserDataApi, OptionTradeHistory) {
    const std::string example =
        R"json({"total":1,"page":1,"size":20,"rows":[{"executionId":"8f2d0c1e-5b7a-4e3c-9d61-2a4b6c8e0f13","orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionIntent":"BUY_TO_OPEN","autoLiquidation":false,"quote":"USDC","side":"BUY","orderType":"LIMIT","price":"1.48","qty":"1","total":"148","executionAt":1790173802000,"updatedAt":1790173802000,"settlementDate":1790272800000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionTradeHistoryParams params{.start_time = 1790100000000, .end_time = 1790200000000};
    const auto res = api.option_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/trade/history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionTradeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"page":1,"size":20,"rows":[{"executionId":"8f2d0c1e-5b7a-4e3c-9d61-2a4b6c8e0f13","orderId":"c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71","clientOrderId":"web_2c9c92b74f1e4a7c8f3b9e1a2d3c4b5a","symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","positionIntent":"BUY_TO_OPEN","autoLiquidation":false,"quote":"USDC","side":"BUY","orderType":"LIMIT","price":"1.48","qty":"1","total":"148","executionAt":1790173802000,"updatedAt":1790173802000,"settlementDate":1790272800000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionTradeHistoryParams params{
        .start_time = 1790100000000,
        .end_time = 1790200000000,
        .underlying_symbol = "NVDA",
        .side = OptionTradeHistorySideEnum::Buy,
        .order_id = "c3c58f49-7b0d-4b9e-a2db-1a2f9a3b8c71",
        .current = 1,
        .size = 20,
        .recv_window = 5000,
    };
    const auto res = api.option_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataApi, OptionTradeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionTradeHistoryParams params{.start_time = 1790100000000, .end_time = 1790200000000};
    EXPECT_THROW((void)api.option_trade_history(params), common::BadRequestError);
}
