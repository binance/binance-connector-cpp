//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string>

#include <gtest/gtest.h>

#include <binance/algo/rest_api/future_algo_api.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/rest.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::algo::rest_api;
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

FutureAlgoApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return FutureAlgoApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiFutureAlgoApi, CancelAlgoOrderFutureAlgo) {
    const std::string example = R"json({"algoId":14511,"success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAlgoOrderFutureAlgoParams params{};
    const auto res = api.cancel_algo_order_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/futures/order");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, CancelAlgoOrderFutureAlgoWithOptionalParams) {
    const std::string example = R"json({"algoId":14511,"success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAlgoOrderFutureAlgoParams params{
        .algo_id = 1,
        .client_algo_id = "65ce1630101a480b85915d7e11fd5078",
        .recv_window = 5000,
    };
    const auto res = api.cancel_algo_order_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientAlgoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, CancelAlgoOrderFutureAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAlgoOrderFutureAlgoParams params{};
    EXPECT_THROW((void)api.cancel_algo_order_future_algo(params), common::BadRequestError);
}

TEST(RestApiFutureAlgoApi, QueryCurrentAlgoOpenOrdersFutureAlgo) {
    const std::string example =
        R"json({"total":1,"orders":[{"algoId":14517,"symbol":"ETHUSDT","side":"SELL","positionSide":"SHORT","totalQty":"5.000","executedQty":"0.000","executedAmt":"0.00000000","avgPrice":"0.00","clientAlgoId":"d7096549481642f8a0bb69e9e2e31f2e","bookTime":1649756817004,"endTime":0,"algoStatus":"WORKING","algoType":"VP","urgency":"LOW"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentAlgoOpenOrdersFutureAlgoParams params{};
    const auto res = api.query_current_algo_open_orders_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/futures/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, QueryCurrentAlgoOpenOrdersFutureAlgoWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"orders":[{"algoId":14517,"symbol":"ETHUSDT","side":"SELL","positionSide":"SHORT","totalQty":"5.000","executedQty":"0.000","executedAmt":"0.00000000","avgPrice":"0.00","clientAlgoId":"d7096549481642f8a0bb69e9e2e31f2e","bookTime":1649756817004,"endTime":0,"algoStatus":"WORKING","algoType":"VP","urgency":"LOW"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentAlgoOpenOrdersFutureAlgoParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_current_algo_open_orders_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, QueryCurrentAlgoOpenOrdersFutureAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentAlgoOpenOrdersFutureAlgoParams params{};
    EXPECT_THROW((void)api.query_current_algo_open_orders_future_algo(params),
                 common::BadRequestError);
}

TEST(RestApiFutureAlgoApi, QueryHistoricalAlgoOrdersFutureAlgo) {
    const std::string example =
        R"json({"total":1,"orders":[{"algoId":14518,"symbol":"BNBUSDT","side":"BUY","positionSide":"BOTH","totalQty":"100.00","executedQty":"0.00","executedAmt":"0.00000000","avgPrice":"0.000","clientAlgoId":"acacab56b3c44bef9f6a8f8ebd2a8408","bookTime":1649757019503,"endTime":1649757088101,"algoStatus":"CANCELLED","algoType":"VP","urgency":"LOW"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryHistoricalAlgoOrdersFutureAlgoParams params{};
    const auto res = api.query_historical_algo_orders_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/futures/historicalOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, QueryHistoricalAlgoOrdersFutureAlgoWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"orders":[{"algoId":14518,"symbol":"BNBUSDT","side":"BUY","positionSide":"BOTH","totalQty":"100.00","executedQty":"0.00","executedAmt":"0.00000000","avgPrice":"0.000","clientAlgoId":"acacab56b3c44bef9f6a8f8ebd2a8408","bookTime":1649757019503,"endTime":1649757088101,"algoStatus":"CANCELLED","algoType":"VP","urgency":"LOW"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryHistoricalAlgoOrdersFutureAlgoParams params{
        .symbol = "BTCUSDT",
        .side = QueryHistoricalAlgoOrdersFutureAlgoSideEnum::Buy,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .page_size = 100,
        .recv_window = 5000,
    };
    const auto res = api.query_historical_algo_orders_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, QueryHistoricalAlgoOrdersFutureAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryHistoricalAlgoOrdersFutureAlgoParams params{};
    EXPECT_THROW((void)api.query_historical_algo_orders_future_algo(params),
                 common::BadRequestError);
}

TEST(RestApiFutureAlgoApi, QuerySubOrdersFutureAlgo) {
    const std::string example =
        R"json({"total":1,"executedQty":"1.000","executedAmt":"3229.44000000","subOrders":[{"algoId":13723,"orderId":8389765519993909000,"orderStatus":"FILLED","executedQty":"1.000","executedAmt":"3229.44000000","feeAmt":"-1.61471999","feeAsset":"USDT","bookTime":1649319001964,"avgPrice":"3229.44","side":"SELL","symbol":"ETHUSDT","subId":1,"timeInForce":"IMMEDIATE_OR_CANCEL","origQty":"1.000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubOrdersFutureAlgoParams params{.algo_id = 1};
    const auto res = api.query_sub_orders_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/futures/subOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, QuerySubOrdersFutureAlgoWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"executedQty":"1.000","executedAmt":"3229.44000000","subOrders":[{"algoId":13723,"orderId":8389765519993909000,"orderStatus":"FILLED","executedQty":"1.000","executedAmt":"3229.44000000","feeAmt":"-1.61471999","feeAsset":"USDT","bookTime":1649319001964,"avgPrice":"3229.44","side":"SELL","symbol":"ETHUSDT","subId":1,"timeInForce":"IMMEDIATE_OR_CANCEL","origQty":"1.000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubOrdersFutureAlgoParams params{
        .algo_id = 1,
        .page = 1,
        .page_size = 100,
        .recv_window = 5000,
    };
    const auto res = api.query_sub_orders_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, QuerySubOrdersFutureAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubOrdersFutureAlgoParams params{.algo_id = 1};
    EXPECT_THROW((void)api.query_sub_orders_future_algo(params), common::BadRequestError);
}

TEST(RestApiFutureAlgoApi, TimeWeightedAveragePriceFutureAlgo) {
    const std::string example =
        R"json({"clientAlgoId":"65ce1630101a480b85915d7e11fd5078","success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TimeWeightedAveragePriceFutureAlgoParams params{
        .symbol = "BTCUSDT",
        .side = TimeWeightedAveragePriceFutureAlgoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .duration = 5000};
    const auto res = api.time_weighted_average_price_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/futures/newOrderTwap");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("duration="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, TimeWeightedAveragePriceFutureAlgoWithOptionalParams) {
    const std::string example =
        R"json({"clientAlgoId":"65ce1630101a480b85915d7e11fd5078","success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TimeWeightedAveragePriceFutureAlgoParams params{
        .symbol = "BTCUSDT",
        .side = TimeWeightedAveragePriceFutureAlgoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .duration = 5000,
        .position_side = TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Both,
        .client_algo_id = "1",
        .reduce_only = false,
        .limit_price = common::Decimal("1"),
        .recv_window = 5000,
    };
    const auto res = api.time_weighted_average_price_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("duration="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientAlgoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, TimeWeightedAveragePriceFutureAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TimeWeightedAveragePriceFutureAlgoParams params{
        .symbol = "BTCUSDT",
        .side = TimeWeightedAveragePriceFutureAlgoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .duration = 5000};
    EXPECT_THROW((void)api.time_weighted_average_price_future_algo(params),
                 common::BadRequestError);
}

TEST(RestApiFutureAlgoApi, VolumeParticipationFutureAlgo) {
    const std::string example =
        R"json({"clientAlgoId":"00358ce6a268403398bd34eaa36dffe7","success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VolumeParticipationFutureAlgoParams params{
        .symbol = "BTCUSDT",
        .side = VolumeParticipationFutureAlgoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .urgency = VolumeParticipationFutureAlgoUrgencyEnum::Low};
    const auto res = api.volume_participation_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/futures/newOrderVp");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("urgency="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, VolumeParticipationFutureAlgoWithOptionalParams) {
    const std::string example =
        R"json({"clientAlgoId":"00358ce6a268403398bd34eaa36dffe7","success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VolumeParticipationFutureAlgoParams params{
        .symbol = "BTCUSDT",
        .side = VolumeParticipationFutureAlgoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .urgency = VolumeParticipationFutureAlgoUrgencyEnum::Low,
        .position_side = VolumeParticipationFutureAlgoPositionSideEnum::Both,
        .client_algo_id = "1",
        .reduce_only = false,
        .limit_price = common::Decimal("1"),
        .recv_window = 5000,
    };
    const auto res = api.volume_participation_future_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("urgency="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientAlgoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFutureAlgoApi, VolumeParticipationFutureAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const VolumeParticipationFutureAlgoParams params{
        .symbol = "BTCUSDT",
        .side = VolumeParticipationFutureAlgoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .urgency = VolumeParticipationFutureAlgoUrgencyEnum::Low};
    EXPECT_THROW((void)api.volume_participation_future_algo(params), common::BadRequestError);
}
