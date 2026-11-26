//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string>

#include <gtest/gtest.h>

#include <binance/algo/rest_api/spot_algo_api.hpp>
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

SpotAlgoApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return SpotAlgoApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiSpotAlgoApi, CancelAlgoOrderSpotAlgo) {
    const std::string example = R"json({"algoId":14511,"success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAlgoOrderSpotAlgoParams params{};
    const auto res = api.cancel_algo_order_spot_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/spot/order");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSpotAlgoApi, CancelAlgoOrderSpotAlgoWithOptionalParams) {
    const std::string example = R"json({"algoId":14511,"success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAlgoOrderSpotAlgoParams params{
        .algo_id = 14511,
        .client_algo_id = "65ce1630101a480b85915d7e11fd5078",
        .recv_window = 5000,
    };
    const auto res = api.cancel_algo_order_spot_algo(params);
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

TEST(RestApiSpotAlgoApi, CancelAlgoOrderSpotAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAlgoOrderSpotAlgoParams params{};
    EXPECT_THROW((void)api.cancel_algo_order_spot_algo(params), common::BadRequestError);
}

TEST(RestApiSpotAlgoApi, QueryCurrentAlgoOpenOrdersSpotAlgo) {
    const std::string example =
        R"json({"total":1,"orders":[{"algoId":14517,"symbol":"ETHUSDT","side":"SELL","totalQty":"5.000","executedQty":"0.000","executedAmt":"0.00000000","avgPrice":"0.00","clientAlgoId":"d7096549481642f8a0bb69e9e2e31f2e","bookTime":1649756817004,"endTime":0,"algoStatus":"WORKING","algoType":"TWAP","urgency":"LOW","duration":86400}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentAlgoOpenOrdersSpotAlgoParams params{};
    const auto res = api.query_current_algo_open_orders_spot_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/spot/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSpotAlgoApi, QueryCurrentAlgoOpenOrdersSpotAlgoWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"orders":[{"algoId":14517,"symbol":"ETHUSDT","side":"SELL","totalQty":"5.000","executedQty":"0.000","executedAmt":"0.00000000","avgPrice":"0.00","clientAlgoId":"d7096549481642f8a0bb69e9e2e31f2e","bookTime":1649756817004,"endTime":0,"algoStatus":"WORKING","algoType":"TWAP","urgency":"LOW","duration":86400}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentAlgoOpenOrdersSpotAlgoParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_current_algo_open_orders_spot_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSpotAlgoApi, QueryCurrentAlgoOpenOrdersSpotAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentAlgoOpenOrdersSpotAlgoParams params{};
    EXPECT_THROW((void)api.query_current_algo_open_orders_spot_algo(params),
                 common::BadRequestError);
}

TEST(RestApiSpotAlgoApi, QueryHistoricalAlgoOrdersSpotAlgo) {
    const std::string example =
        R"json({"total":1,"orders":[{"algoId":14518,"symbol":"BNBUSDT","side":"BUY","totalQty":"100.00","executedQty":"0.00","executedAmt":"0.00000000","avgPrice":"0.000","clientAlgoId":"acacab56b3c44bef9f6a8f8ebd2a8408","bookTime":1649757019503,"endTime":1649757088101,"algoStatus":"CANCELLED","algoType":"TWAP","urgency":"LOW","duration":86400}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryHistoricalAlgoOrdersSpotAlgoParams params{};
    const auto res = api.query_historical_algo_orders_spot_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/spot/historicalOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSpotAlgoApi, QueryHistoricalAlgoOrdersSpotAlgoWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"orders":[{"algoId":14518,"symbol":"BNBUSDT","side":"BUY","totalQty":"100.00","executedQty":"0.00","executedAmt":"0.00000000","avgPrice":"0.000","clientAlgoId":"acacab56b3c44bef9f6a8f8ebd2a8408","bookTime":1649757019503,"endTime":1649757088101,"algoStatus":"CANCELLED","algoType":"TWAP","urgency":"LOW","duration":86400}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryHistoricalAlgoOrdersSpotAlgoParams params{
        .symbol = "BTCUSDT",
        .side = QueryHistoricalAlgoOrdersSpotAlgoSideEnum::Buy,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .page_size = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_historical_algo_orders_spot_algo(params);
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

TEST(RestApiSpotAlgoApi, QueryHistoricalAlgoOrdersSpotAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryHistoricalAlgoOrdersSpotAlgoParams params{};
    EXPECT_THROW((void)api.query_historical_algo_orders_spot_algo(params), common::BadRequestError);
}

TEST(RestApiSpotAlgoApi, QuerySubOrdersSpotAlgo) {
    const std::string example =
        R"json({"total":1,"executedQty":"1.000","executedAmt":"3229.44000000","subOrders":[{"algoId":13723,"orderId":8389765519993909000,"orderStatus":"FILLED","executedQty":"1.000","executedAmt":"3229.44000000","feeAmt":"-1.61471999","feeAsset":"USDT","bookTime":1649319001964,"avgPrice":"3229.44","side":"SELL","symbol":"ETHUSDT","subId":1,"timeInForce":"IMMEDIATE_OR_CANCEL","origQty":"1.000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubOrdersSpotAlgoParams params{.algo_id = 1};
    const auto res = api.query_sub_orders_spot_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/spot/subOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSpotAlgoApi, QuerySubOrdersSpotAlgoWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"executedQty":"1.000","executedAmt":"3229.44000000","subOrders":[{"algoId":13723,"orderId":8389765519993909000,"orderStatus":"FILLED","executedQty":"1.000","executedAmt":"3229.44000000","feeAmt":"-1.61471999","feeAsset":"USDT","bookTime":1649319001964,"avgPrice":"3229.44","side":"SELL","symbol":"ETHUSDT","subId":1,"timeInForce":"IMMEDIATE_OR_CANCEL","origQty":"1.000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubOrdersSpotAlgoParams params{
        .algo_id = 1,
        .page = 1,
        .page_size = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_sub_orders_spot_algo(params);
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

TEST(RestApiSpotAlgoApi, QuerySubOrdersSpotAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubOrdersSpotAlgoParams params{.algo_id = 1};
    EXPECT_THROW((void)api.query_sub_orders_spot_algo(params), common::BadRequestError);
}

TEST(RestApiSpotAlgoApi, TimeWeightedAveragePriceSpotAlgo) {
    const std::string example =
        R"json({"clientAlgoId":"65ce1630101a480b85915d7e11fd5078","success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TimeWeightedAveragePriceSpotAlgoParams params{
        .symbol = "BTCUSDT",
        .side = TimeWeightedAveragePriceSpotAlgoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .duration = 5000};
    const auto res = api.time_weighted_average_price_spot_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/spot/newOrderTwap");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("duration="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSpotAlgoApi, TimeWeightedAveragePriceSpotAlgoWithOptionalParams) {
    const std::string example =
        R"json({"clientAlgoId":"65ce1630101a480b85915d7e11fd5078","success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TimeWeightedAveragePriceSpotAlgoParams params{
        .symbol = "BTCUSDT",
        .side = TimeWeightedAveragePriceSpotAlgoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .duration = 5000,
        .client_algo_id = "1",
        .limit_price = common::Decimal("1"),
    };
    const auto res = api.time_weighted_average_price_spot_algo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("duration="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientAlgoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitPrice="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSpotAlgoApi, TimeWeightedAveragePriceSpotAlgoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TimeWeightedAveragePriceSpotAlgoParams params{
        .symbol = "BTCUSDT",
        .side = TimeWeightedAveragePriceSpotAlgoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .duration = 5000};
    EXPECT_THROW((void)api.time_weighted_average_price_spot_algo(params), common::BadRequestError);
}

TEST(RestApiSpotAlgoApi, VolumeParticipation) {
    const std::string example =
        R"json({"clientAlgoId":"65ce1630101a480b85915d7e11fd5078","success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VolumeParticipationParams params{.symbol = "BTCUSDT",
                                           .side = VolumeParticipationSideEnum::Buy,
                                           .quantity = common::Decimal("1"),
                                           .urgency = VolumeParticipationUrgencyEnum::Low};
    const auto res = api.volume_participation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/algo/spot/newOrderVp");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("urgency="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSpotAlgoApi, VolumeParticipationWithOptionalParams) {
    const std::string example =
        R"json({"clientAlgoId":"65ce1630101a480b85915d7e11fd5078","success":true,"code":0,"msg":"OK"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VolumeParticipationParams params{
        .symbol = "BTCUSDT",
        .side = VolumeParticipationSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .urgency = VolumeParticipationUrgencyEnum::Low,
        .client_algo_id = "1",
        .vp_time_limit = 5000,
        .recv_window = 5000,
    };
    const auto res = api.volume_participation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("urgency="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientAlgoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("vpTimeLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSpotAlgoApi, VolumeParticipationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const VolumeParticipationParams params{.symbol = "BTCUSDT",
                                           .side = VolumeParticipationSideEnum::Buy,
                                           .quantity = common::Decimal("1"),
                                           .urgency = VolumeParticipationUrgencyEnum::Low};
    EXPECT_THROW((void)api.volume_participation(params), common::BadRequestError);
}
