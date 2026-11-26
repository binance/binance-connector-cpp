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
#include <binance/derivatives_trading_portfolio_margin/rest_api/trade_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_portfolio_margin::rest_api;
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

TEST(RestApiTradeApi, CancelAllCmOpenConditionalOrders) {
    const std::string example =
        R"json({"code":"200","msg":"The operation of cancel all conditional open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllCmOpenConditionalOrdersParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_all_cm_open_conditional_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/conditional/allOpenOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllCmOpenConditionalOrdersWithOptionalParams) {
    const std::string example =
        R"json({"code":"200","msg":"The operation of cancel all conditional open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllCmOpenConditionalOrdersParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_cm_open_conditional_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllCmOpenConditionalOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllCmOpenConditionalOrdersParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_all_cm_open_conditional_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelAllCmOpenOrders) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllCmOpenOrdersParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_all_cm_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/allOpenOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllCmOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllCmOpenOrdersParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_cm_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllCmOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllCmOpenOrdersParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_all_cm_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelAllUmAlgoOpenOrders) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllUmAlgoOpenOrdersParams params{.symbol = "BNBUSDT"};
    const auto res = api.cancel_all_um_algo_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/um/algo/allOpenOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllUmAlgoOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllUmAlgoOpenOrdersParams params{
        .symbol = "BNBUSDT",
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_um_algo_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllUmAlgoOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllUmAlgoOpenOrdersParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.cancel_all_um_algo_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelAllUmOpenOrders) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllUmOpenOrdersParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_all_um_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/um/allOpenOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllUmOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllUmOpenOrdersParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_um_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllUmOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllUmOpenOrdersParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_all_um_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelCmConditionalOrder) {
    const std::string example =
        R"json({"newClientStrategyId":"myOrder1","strategyId":123445,"strategyStatus":"CANCELED","strategyType":"TRAILING_STOP_MARKET","origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","timeInForce":"GTC","activatePrice":"9020","priceRate":"0.3","bookTime":1566818724710,"updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelCmConditionalOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_cm_conditional_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/conditional/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelCmConditionalOrderWithOptionalParams) {
    const std::string example =
        R"json({"newClientStrategyId":"myOrder1","strategyId":123445,"strategyStatus":"CANCELED","strategyType":"TRAILING_STOP_MARKET","origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","timeInForce":"GTC","activatePrice":"9020","priceRate":"0.3","bookTime":1566818724710,"updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelCmConditionalOrderParams params{
        .symbol = "BTCUSDT",
        .strategy_id = 1,
        .new_client_strategy_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.cancel_cm_conditional_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelCmConditionalOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelCmConditionalOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_cm_conditional_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewCmConditionalOrder) {
    const std::string example =
        R"json({"newClientStrategyId":"testOrder","strategyId":123445,"strategyStatus":"NEW","strategyType":"TRAILING_STOP_MARKET","origQty":"10","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","activatePrice":"9020","priceRate":"0.3","bookTime":1566818724710,"updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewCmConditionalOrderParams params{.symbol = "BTCUSDT",
                                             .side = NewCmConditionalOrderSideEnum::Buy,
                                             .strategy_type =
                                                 NewCmConditionalOrderStrategyTypeEnum::Stop};
    const auto res = api.new_cm_conditional_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/conditional/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewCmConditionalOrderWithOptionalParams) {
    const std::string example =
        R"json({"newClientStrategyId":"testOrder","strategyId":123445,"strategyStatus":"NEW","strategyType":"TRAILING_STOP_MARKET","origQty":"10","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","activatePrice":"9020","priceRate":"0.3","bookTime":1566818724710,"updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewCmConditionalOrderParams params{
        .symbol = "BTCUSDT",
        .side = NewCmConditionalOrderSideEnum::Buy,
        .strategy_type = NewCmConditionalOrderStrategyTypeEnum::Stop,
        .position_side = NewCmConditionalOrderPositionSideEnum::Both,
        .time_in_force = NewCmConditionalOrderTimeInForceEnum::Gtc,
        .quantity = common::Decimal("1.0"),
        .reduce_only = "true",
        .price = common::Decimal("1.0"),
        .working_type = NewCmConditionalOrderWorkingTypeEnum::MarkPrice,
        .price_protect = NewCmConditionalOrderPriceProtectEnum::True_,
        .new_client_strategy_id = "1",
        .stop_price = common::Decimal("1.0"),
        .activation_price = common::Decimal("1.0"),
        .callback_rate = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.new_cm_conditional_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceProtect="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("activationPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("callbackRate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewCmConditionalOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewCmConditionalOrderParams params{.symbol = "BTCUSDT",
                                             .side = NewCmConditionalOrderSideEnum::Buy,
                                             .strategy_type =
                                                 NewCmConditionalOrderStrategyTypeEnum::Stop};
    EXPECT_THROW((void)api.new_cm_conditional_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelCmOrder) {
    const std::string example =
        R"json({"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"2","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","type":"LIMIT","updateTime":1571110484038})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelCmOrderParams params{.symbol = "BTCUSD_200925"};
    const auto res = api.cancel_cm_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelCmOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"2","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","type":"LIMIT","updateTime":1571110484038})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelCmOrderParams params{
        .symbol = "BTCUSD_200925",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.cancel_cm_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelCmOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelCmOrderParams params{.symbol = "BTCUSD_200925"};
    EXPECT_THROW((void)api.cancel_cm_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ModifyCmOrder) {
    const std::string example =
        R"json({"orderId":20072994037,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"side":"BUY","positionSide":"LONG","origType":"LIMIT","updateTime":1629182711600})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyCmOrderParams params{.symbol = "BTCUSD_PERP",
                                     .side = ModifyCmOrderSideEnum::Buy,
                                     .quantity = common::Decimal("1.0"),
                                     .price = common::Decimal("1.0")};
    const auto res = api.modify_cm_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyCmOrderWithOptionalParams) {
    const std::string example =
        R"json({"orderId":20072994037,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"side":"BUY","positionSide":"LONG","origType":"LIMIT","updateTime":1629182711600})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyCmOrderParams params{
        .symbol = "BTCUSD_PERP",
        .side = ModifyCmOrderSideEnum::Buy,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .order_id = 1,
        .orig_client_order_id = "1",
        .price_match = ModifyCmOrderPriceMatchEnum::Opponent,
        .modify_id = 1,
        .recv_window = 5000,
    };
    const auto res = api.modify_cm_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceMatch="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("modifyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyCmOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ModifyCmOrderParams params{.symbol = "BTCUSD_PERP",
                                     .side = ModifyCmOrderSideEnum::Buy,
                                     .quantity = common::Decimal("1.0"),
                                     .price = common::Decimal("1.0")};
    EXPECT_THROW((void)api.modify_cm_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewCmOrder) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","type":"MARKET","updateTime":1566818724722})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewCmOrderParams params{
        .symbol = "BTCUSDT", .side = NewCmOrderSideEnum::Buy, .type = NewCmOrderTypeEnum::Limit};
    const auto res = api.new_cm_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewCmOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","type":"MARKET","updateTime":1566818724722})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewCmOrderParams params{
        .symbol = "BTCUSDT",
        .side = NewCmOrderSideEnum::Buy,
        .type = NewCmOrderTypeEnum::Limit,
        .position_side = NewCmOrderPositionSideEnum::Both,
        .time_in_force = NewCmOrderTimeInForceEnum::Gtc,
        .quantity = common::Decimal("1.0"),
        .reduce_only = NewCmOrderReduceOnlyEnum::True_,
        .price = common::Decimal("1.0"),
        .price_match = NewCmOrderPriceMatchEnum::Opponent,
        .new_client_order_id = "1",
        .new_order_resp_type = NewCmOrderNewOrderRespTypeEnum::Ack,
        .recv_window = 5000,
    };
    const auto res = api.new_cm_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceMatch="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewCmOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewCmOrderParams params{
        .symbol = "BTCUSDT", .side = NewCmOrderSideEnum::Buy, .type = NewCmOrderTypeEnum::Limit};
    EXPECT_THROW((void)api.new_cm_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCmOrder) {
    const std::string example =
        R"json({"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","positionSide":"SHORT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCmOrderParams params{.symbol = "BTCUSD_200925"};
    const auto res = api.query_cm_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCmOrderWithOptionalParams) {
    const std::string example =
        R"json({"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","positionSide":"SHORT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCmOrderParams params{
        .symbol = "BTCUSD_200925",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_cm_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCmOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCmOrderParams params{.symbol = "BTCUSD_200925"};
    EXPECT_THROW((void)api.query_cm_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelMarginAccountAllOpenOrdersOnASymbol) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","origClientOrderId":"E6APeyTJvkMvLMYMqu1KQ4","orderId":11,"orderListId":-1,"clientOrderId":"pXLV6Hz6mprAcVYpVMTGgx","price":"0.089853","origQty":"0.178622","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"BUY","contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"2inzWQdDvZLHbbAmAozX2N","transactionTime":1585230948299,"orders":[{"symbol":"BTCUSDT","orderId":20,"clientOrderId":"CwOOIPHSmYywx6jZX77TdL"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"CwOOIPHSmYywx6jZX77TdL","orderId":20,"orderListId":1929,"clientOrderId":"pXLV6Hz6mprAcVYpVMTGgx","price":"0.668611","origQty":"0.690354","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"0.378131","icebergQty":"0.017083"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMarginAccountAllOpenOrdersOnASymbolParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_margin_account_all_open_orders_on_a_symbol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/allOpenOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelMarginAccountAllOpenOrdersOnASymbolWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","origClientOrderId":"E6APeyTJvkMvLMYMqu1KQ4","orderId":11,"orderListId":-1,"clientOrderId":"pXLV6Hz6mprAcVYpVMTGgx","price":"0.089853","origQty":"0.178622","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"BUY","contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"2inzWQdDvZLHbbAmAozX2N","transactionTime":1585230948299,"orders":[{"symbol":"BTCUSDT","orderId":20,"clientOrderId":"CwOOIPHSmYywx6jZX77TdL"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"CwOOIPHSmYywx6jZX77TdL","orderId":20,"orderListId":1929,"clientOrderId":"pXLV6Hz6mprAcVYpVMTGgx","price":"0.668611","origQty":"0.690354","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"0.378131","icebergQty":"0.017083"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMarginAccountAllOpenOrdersOnASymbolParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.cancel_margin_account_all_open_orders_on_a_symbol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelMarginAccountAllOpenOrdersOnASymbolBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelMarginAccountAllOpenOrdersOnASymbolParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_margin_account_all_open_orders_on_a_symbol(params),
                 common::BadRequestError);
}

TEST(RestApiTradeApi, CancelMarginAccountOcoOrders) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"C3wyj4WVEktd7u9aVBRXcN","transactionTime":1574040868128,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"pO9ufTiFGg3nw2fOdgeOXa"}],"orderReports":[{"symbol":"LTCBTC","origClientOrderId":"pO9ufTiFGg3nw2fOdgeOXa","orderId":2,"orderListId":0,"clientOrderId":"unfWT8ig8i0uj6lPuYLez6","price":"1.00000000","origQty":"10.00000000","executedQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"1.00000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMarginAccountOcoOrdersParams params{.symbol = "LTCBTC"};
    const auto res = api.cancel_margin_account_oco_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/orderList");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelMarginAccountOcoOrdersWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"C3wyj4WVEktd7u9aVBRXcN","transactionTime":1574040868128,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"pO9ufTiFGg3nw2fOdgeOXa"}],"orderReports":[{"symbol":"LTCBTC","origClientOrderId":"pO9ufTiFGg3nw2fOdgeOXa","orderId":2,"orderListId":0,"clientOrderId":"unfWT8ig8i0uj6lPuYLez6","price":"1.00000000","origQty":"10.00000000","executedQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"1.00000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMarginAccountOcoOrdersParams params{
        .symbol = "LTCBTC",
        .order_list_id = 1,
        .list_client_order_id = "1",
        .new_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.cancel_margin_account_oco_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderListId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelMarginAccountOcoOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelMarginAccountOcoOrdersParams params{.symbol = "LTCBTC"};
    EXPECT_THROW((void)api.cancel_margin_account_oco_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsOco) {
    const std::string example =
        R"json({"orderListId":27,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"h2USkA5YQpaXHPIrkd96xE","transactionTime":1565245656253,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"qD1gy3kc3Gx0rihm9Y3xwS"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOcoParams params{};
    const auto res = api.query_margin_accounts_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/orderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOcoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":27,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"h2USkA5YQpaXHPIrkd96xE","transactionTime":1565245656253,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"qD1gy3kc3Gx0rihm9Y3xwS"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOcoParams params{
        .order_list_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderListId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsOcoParams params{};
    EXPECT_THROW((void)api.query_margin_accounts_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelMarginAccountOrder) {
    const std::string example =
        R"json({"symbol":"LTCBTC","orderId":28,"origClientOrderId":"myOrder1","clientOrderId":"cancelMyOrder1","price":"1.00000000","origQty":"10.00000000","executedQty":"8.00000000","cummulativeQuoteQty":"8.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMarginAccountOrderParams params{.symbol = "LTCBTC"};
    const auto res = api.cancel_margin_account_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelMarginAccountOrderWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"LTCBTC","orderId":28,"origClientOrderId":"myOrder1","clientOrderId":"cancelMyOrder1","price":"1.00000000","origQty":"10.00000000","executedQty":"8.00000000","cummulativeQuoteQty":"8.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMarginAccountOrderParams params{
        .symbol = "LTCBTC",
        .order_id = 1,
        .orig_client_order_id = "1",
        .new_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.cancel_margin_account_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelMarginAccountOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelMarginAccountOrderParams params{.symbol = "LTCBTC"};
    EXPECT_THROW((void)api.cancel_margin_account_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewMarginOrder) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","orderId":28,"clientOrderId":"6gCrw2kRUAF9CvJDGP16IP","transactTime":1507725176595,"price":"1.00000000","origQty":"10.00000000","executedQty":"10.00000000","cummulativeQuoteQty":"10.00000000","status":"FILLED","timeInForce":"GTC","type":"MARKET","side":"SELL","marginBuyBorrowAmount":"5","marginBuyBorrowAsset":"BTC","fills":[{"price":"4000.00000000","qty":"1.00000000","commission":"4.00000000","commissionAsset":"USDT"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewMarginOrderParams params{.symbol = "BTCUSDT",
                                      .side = NewMarginOrderSideEnum::Buy,
                                      .type = NewMarginOrderTypeEnum::Limit};
    const auto res = api.new_margin_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewMarginOrderWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","orderId":28,"clientOrderId":"6gCrw2kRUAF9CvJDGP16IP","transactTime":1507725176595,"price":"1.00000000","origQty":"10.00000000","executedQty":"10.00000000","cummulativeQuoteQty":"10.00000000","status":"FILLED","timeInForce":"GTC","type":"MARKET","side":"SELL","marginBuyBorrowAmount":"5","marginBuyBorrowAsset":"BTC","fills":[{"price":"4000.00000000","qty":"1.00000000","commission":"4.00000000","commissionAsset":"USDT"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewMarginOrderParams params{
        .symbol = "BTCUSDT",
        .side = NewMarginOrderSideEnum::Buy,
        .type = NewMarginOrderTypeEnum::Limit,
        .quantity = common::Decimal("1.0"),
        .quote_order_qty = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .stop_price = common::Decimal("1.0"),
        .new_client_order_id = "1",
        .new_order_resp_type = NewMarginOrderNewOrderRespTypeEnum::Ack,
        .iceberg_qty = common::Decimal("1.0"),
        .side_effect_type = NewMarginOrderSideEffectTypeEnum::NoSideEffect,
        .time_in_force = NewMarginOrderTimeInForceEnum::Gtc,
        .self_trade_prevention_mode = NewMarginOrderSelfTradePreventionModeEnum::None_,
        .auto_repay_at_cancel = true,
        .recv_window = 5000,
    };
    const auto res = api.new_margin_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteOrderQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("icebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sideEffectType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoRepayAtCancel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewMarginOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewMarginOrderParams params{.symbol = "BTCUSDT",
                                      .side = NewMarginOrderSideEnum::Buy,
                                      .type = NewMarginOrderTypeEnum::Limit};
    EXPECT_THROW((void)api.new_margin_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountOrder) {
    const std::string example =
        R"json({"clientOrderId":"ZwfQzuDIGpceVhKW5DvCmO","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":true,"orderId":213205622,"origQty":"0.30000000","price":"0.00493630","side":"SELL","status":"NEW","stopPrice":"0.00000000","symbol":"BNBBTC","time":1562133008725,"timeInForce":"GTC","type":"LIMIT","updateTime":1562133008725,"accountId":152950866,"selfTradePreventionMode":"EXPIRE_TAKER","preventedMatchId":"null","preventedQuantity":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_margin_account_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"ZwfQzuDIGpceVhKW5DvCmO","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":true,"orderId":213205622,"origQty":"0.30000000","price":"0.00493630","side":"SELL","status":"NEW","stopPrice":"0.00000000","symbol":"BNBBTC","time":1562133008725,"timeInForce":"GTC","type":"LIMIT","updateTime":1562133008725,"accountId":152950866,"selfTradePreventionMode":"EXPIRE_TAKER","preventedMatchId":"null","preventedQuantity":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountOrderParams params{
        .symbol = "BTCUSDT",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_margin_account_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_margin_account_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelUmAlgoOrder) {
    const std::string example = R"json({"complete":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelUmAlgoOrderParams params{};
    const auto res = api.cancel_um_algo_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/um/algo/order");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelUmAlgoOrderWithOptionalParams) {
    const std::string example = R"json({"complete":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelUmAlgoOrderParams params{
        .algo_id = 2146760,
        .client_algo_id = "6B2I9XVcJpCjqPAJ4YoFX7",
        .recv_window = 5000,
    };
    const auto res = api.cancel_um_algo_order(params);
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

TEST(RestApiTradeApi, CancelUmAlgoOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelUmAlgoOrderParams params{};
    EXPECT_THROW((void)api.cancel_um_algo_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewUmAlgoOrder) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"NEW","triggerPrice":"750.000","price":"750.000","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"activatePrice":"","callbackRate":"","createTime":1750485492076,"updateTime":1750485492076,"triggerTime":0,"goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewUmAlgoOrderParams params{.algo_type = NewUmAlgoOrderAlgoTypeEnum::Conditional,
                                      .symbol = "BNBUSDT",
                                      .side = NewUmAlgoOrderSideEnum::Buy,
                                      .type = NewUmAlgoOrderTypeEnum::Stop};
    const auto res = api.new_um_algo_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/um/algo/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewUmAlgoOrderWithOptionalParams) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"NEW","triggerPrice":"750.000","price":"750.000","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"activatePrice":"","callbackRate":"","createTime":1750485492076,"updateTime":1750485492076,"triggerTime":0,"goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewUmAlgoOrderParams params{
        .algo_type = NewUmAlgoOrderAlgoTypeEnum::Conditional,
        .symbol = "BNBUSDT",
        .side = NewUmAlgoOrderSideEnum::Buy,
        .type = NewUmAlgoOrderTypeEnum::Stop,
        .position_side = NewUmAlgoOrderPositionSideEnum::Both,
        .time_in_force = NewUmAlgoOrderTimeInForceEnum::Ioc,
        .quantity = common::Decimal("0.01"),
        .price = common::Decimal("750.000"),
        .trigger_price = common::Decimal("750.000"),
        .working_type = NewUmAlgoOrderWorkingTypeEnum::MarkPrice,
        .price_match = NewUmAlgoOrderPriceMatchEnum::Opponent,
        .close_position = NewUmAlgoOrderClosePositionEnum::True_,
        .price_protect = NewUmAlgoOrderPriceProtectEnum::True_,
        .reduce_only = NewUmAlgoOrderReduceOnlyEnum::True_,
        .activate_price = common::Decimal("700"),
        .callback_rate = common::Decimal("1"),
        .client_algo_id = "6B2I9XVcJpCjqPAJ4YoFX7",
        .new_order_resp_type = NewUmAlgoOrderNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = NewUmAlgoOrderSelfTradePreventionModeEnum::None_,
        .good_till_date = 0,
        .recv_window = 5000,
    };
    const auto res = api.new_um_algo_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("triggerPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceMatch="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("closePosition="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceProtect="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("activatePrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("callbackRate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientAlgoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("goodTillDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewUmAlgoOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewUmAlgoOrderParams params{.algo_type = NewUmAlgoOrderAlgoTypeEnum::Conditional,
                                      .symbol = "BNBUSDT",
                                      .side = NewUmAlgoOrderSideEnum::Buy,
                                      .type = NewUmAlgoOrderTypeEnum::Stop};
    EXPECT_THROW((void)api.new_um_algo_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelUmOrder) {
    const std::string example =
        R"json({"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":4611875134427365000,"origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","symbol":"BTCUSDT","timeInForce":"GTC","type":"LIMIT","updateTime":1571110484038,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelUmOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_um_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/papi/v1/um/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelUmOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":4611875134427365000,"origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","symbol":"BTCUSDT","timeInForce":"GTC","type":"LIMIT","updateTime":1571110484038,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelUmOrderParams params{
        .symbol = "BTCUSDT",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.cancel_um_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelUmOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelUmOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_um_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ModifyUmOrder) {
    const std::string example =
        R"json({"orderId":20072994037,"symbol":"BTCUSDT","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"side":"BUY","positionSide":"LONG","origType":"LIMIT","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"updateTime":1629182711600,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyUmOrderParams params{.symbol = "BTCUSDT",
                                     .side = ModifyUmOrderSideEnum::Buy,
                                     .quantity = common::Decimal("1.0"),
                                     .price = common::Decimal("1.0")};
    const auto res = api.modify_um_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/papi/v1/um/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyUmOrderWithOptionalParams) {
    const std::string example =
        R"json({"orderId":20072994037,"symbol":"BTCUSDT","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"side":"BUY","positionSide":"LONG","origType":"LIMIT","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"updateTime":1629182711600,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyUmOrderParams params{
        .symbol = "BTCUSDT",
        .side = ModifyUmOrderSideEnum::Buy,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .order_id = 1,
        .orig_client_order_id = "1",
        .price_match = ModifyUmOrderPriceMatchEnum::Opponent,
        .modify_id = 1,
        .recv_window = 5000,
    };
    const auto res = api.modify_um_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceMatch="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("modifyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyUmOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ModifyUmOrderParams params{.symbol = "BTCUSDT",
                                     .side = ModifyUmOrderSideEnum::Buy,
                                     .quantity = common::Decimal("1.0"),
                                     .price = common::Decimal("1.0")};
    EXPECT_THROW((void)api.modify_um_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewUmOrder) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","timeInForce":"GTD","type":"MARKET","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1693207680000,"updateTime":1566818724722,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewUmOrderParams params{
        .symbol = "BTCUSDT", .side = NewUmOrderSideEnum::Buy, .type = NewUmOrderTypeEnum::Limit};
    const auto res = api.new_um_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/um/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewUmOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","timeInForce":"GTD","type":"MARKET","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1693207680000,"updateTime":1566818724722,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewUmOrderParams params{
        .symbol = "BTCUSDT",
        .side = NewUmOrderSideEnum::Buy,
        .type = NewUmOrderTypeEnum::Limit,
        .position_side = NewUmOrderPositionSideEnum::Both,
        .time_in_force = NewUmOrderTimeInForceEnum::Gtc,
        .quantity = common::Decimal("1.0"),
        .reduce_only = NewUmOrderReduceOnlyEnum::True_,
        .price = common::Decimal("1.0"),
        .new_client_order_id = "1",
        .new_order_resp_type = NewUmOrderNewOrderRespTypeEnum::Ack,
        .price_match = NewUmOrderPriceMatchEnum::Opponent,
        .self_trade_prevention_mode = NewUmOrderSelfTradePreventionModeEnum::ExpireTaker,
        .good_till_date = 1770736694138,
        .recv_window = 5000,
    };
    const auto res = api.new_um_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceMatch="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("goodTillDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewUmOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewUmOrderParams params{
        .symbol = "BTCUSDT", .side = NewUmOrderSideEnum::Buy, .type = NewUmOrderTypeEnum::Limit};
    EXPECT_THROW((void)api.new_um_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryUmOrder) {
    const std::string example =
        R"json({"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUmOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_um_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUmOrderWithOptionalParams) {
    const std::string example =
        R"json({"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUmOrderParams params{
        .symbol = "BTCUSDT",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_um_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUmOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUmOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_um_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CmAccountTradeList) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200626","id":6,"orderId":28,"pair":"BTCUSD","side":"SELL","price":"8800","qty":"1","realizedPnl":"0","marginAsset":"BTC","baseQty":"0.01136364","commission":"0.00000454","commissionAsset":"BTC","time":1590743483586,"positionSide":"BOTH","buyer":false,"maker":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CmAccountTradeListParams params{};
    const auto res = api.cm_account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/userTrades");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CmAccountTradeListWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200626","id":6,"orderId":28,"pair":"BTCUSD","side":"SELL","price":"8800","qty":"1","realizedPnl":"0","marginAsset":"BTC","baseQty":"0.01136364","commission":"0.00000454","commissionAsset":"BTC","time":1590743483586,"positionSide":"BOTH","buyer":false,"maker":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CmAccountTradeListParams params{
        .symbol = "BTCUSD_200626",
        .pair = "BTCUSD",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .from_id = 1,
        .limit = 50,
        .recv_window = 5000,
    };
    const auto res = api.cm_account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CmAccountTradeListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CmAccountTradeListParams params{};
    EXPECT_THROW((void)api.cm_account_trade_list(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CmPositionAdlQuantileEstimation) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_201225","adlQuantile":{"LONG":3,"SHORT":3,"HEDGE":0,"BOTH":0}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CmPositionAdlQuantileEstimationParams params{};
    const auto res = api.cm_position_adl_quantile_estimation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/adlQuantile");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CmPositionAdlQuantileEstimationWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_201225","adlQuantile":{"LONG":3,"SHORT":3,"HEDGE":0,"BOTH":0}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CmPositionAdlQuantileEstimationParams params{
        .symbol = "BTCUSD_201225",
        .recv_window = 5000,
    };
    const auto res = api.cm_position_adl_quantile_estimation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CmPositionAdlQuantileEstimationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CmPositionAdlQuantileEstimationParams params{};
    EXPECT_THROW((void)api.cm_position_adl_quantile_estimation(params), common::BadRequestError);
}

TEST(RestApiTradeApi, FuturesTradfiPerpsContract) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesTradfiPerpsContractParams params{};
    const auto res = api.futures_tradfi_perps_contract(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/um/stock/contract");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, FuturesTradfiPerpsContractWithOptionalParams) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesTradfiPerpsContractParams params{
        .recv_window = 5000,
    };
    const auto res = api.futures_tradfi_perps_contract(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, FuturesTradfiPerpsContractBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FuturesTradfiPerpsContractParams params{};
    EXPECT_THROW((void)api.futures_tradfi_perps_contract(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetUmFuturesBnbBurnStatus) {
    const std::string example = R"json({"feeBurn":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmFuturesBnbBurnStatusParams params{};
    const auto res = api.get_um_futures_bnb_burn_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/feeBurn");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetUmFuturesBnbBurnStatusWithOptionalParams) {
    const std::string example = R"json({"feeBurn":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmFuturesBnbBurnStatusParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_um_futures_bnb_burn_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetUmFuturesBnbBurnStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUmFuturesBnbBurnStatusParams params{};
    EXPECT_THROW((void)api.get_um_futures_bnb_burn_status(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ToggleBnbBurnOnUmFuturesTrade) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ToggleBnbBurnOnUmFuturesTradeParams params{
        .fee_burn = ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::True_};
    const auto res = api.toggle_bnb_burn_on_um_futures_trade(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/um/feeBurn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("feeBurn="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ToggleBnbBurnOnUmFuturesTradeWithOptionalParams) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ToggleBnbBurnOnUmFuturesTradeParams params{
        .fee_burn = ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.toggle_bnb_burn_on_um_futures_trade(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("feeBurn="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ToggleBnbBurnOnUmFuturesTradeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ToggleBnbBurnOnUmFuturesTradeParams params{
        .fee_burn = ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::True_};
    EXPECT_THROW((void)api.toggle_bnb_burn_on_um_futures_trade(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountBorrow) {
    const std::string example = R"json({"tranId":100000001})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountBorrowParams params{.asset = "USDT", .amount = common::Decimal("1.0")};
    const auto res = api.margin_account_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/marginLoan");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountBorrowWithOptionalParams) {
    const std::string example = R"json({"tranId":100000001})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountBorrowParams params{
        .asset = "USDT",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.margin_account_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountBorrowBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountBorrowParams params{.asset = "USDT", .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.margin_account_borrow(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountNewOco) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"JYVpp3F0f5CAG15DhtrqLp","transactionTime":1563417480525,"symbol":"LTCBTC","marginBuyBorrowAmount":"5","marginBuyBorrowAsset":"BTC","orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos"}],"orderReports":[{"symbol":"LTCBTC","orderId":2,"orderListId":0,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos","transactTime":1563417480525,"price":"0.000000","origQty":"0.624363","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS","side":"BUY","stopPrice":"0.960664"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOcoParams params{.symbol = "LTCBTC",
                                           .side = MarginAccountNewOcoSideEnum::Buy,
                                           .quantity = common::Decimal("1.0"),
                                           .price = common::Decimal("1.0"),
                                           .stop_price = common::Decimal("1.0")};
    const auto res = api.margin_account_new_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/order/oco");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOcoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"JYVpp3F0f5CAG15DhtrqLp","transactionTime":1563417480525,"symbol":"LTCBTC","marginBuyBorrowAmount":"5","marginBuyBorrowAsset":"BTC","orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos"}],"orderReports":[{"symbol":"LTCBTC","orderId":2,"orderListId":0,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos","transactTime":1563417480525,"price":"0.000000","origQty":"0.624363","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS","side":"BUY","stopPrice":"0.960664"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOcoParams params{
        .symbol = "LTCBTC",
        .side = MarginAccountNewOcoSideEnum::Buy,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .stop_price = common::Decimal("1.0"),
        .list_client_order_id = "1",
        .limit_client_order_id = "1",
        .limit_iceberg_qty = common::Decimal("1.0"),
        .stop_client_order_id = "1",
        .stop_limit_price = common::Decimal("1.0"),
        .stop_iceberg_qty = common::Decimal("1.0"),
        .stop_limit_time_in_force = MarginAccountNewOcoStopLimitTimeInForceEnum::Gtc,
        .new_order_resp_type = MarginAccountNewOcoNewOrderRespTypeEnum::Ack,
        .side_effect_type = MarginAccountNewOcoSideEffectTypeEnum::NoSideEffect,
        .recv_window = 5000,
    };
    const auto res = api.margin_account_new_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopLimitPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopLimitTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sideEffectType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountNewOcoParams params{.symbol = "LTCBTC",
                                           .side = MarginAccountNewOcoSideEnum::Buy,
                                           .quantity = common::Decimal("1.0"),
                                           .price = common::Decimal("1.0"),
                                           .stop_price = common::Decimal("1.0")};
    EXPECT_THROW((void)api.margin_account_new_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountRepay) {
    const std::string example = R"json({"tranId":100000001})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountRepayParams params{.asset = "USDT", .amount = common::Decimal("1.0")};
    const auto res = api.margin_account_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/repayLoan");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountRepayWithOptionalParams) {
    const std::string example = R"json({"tranId":100000001})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountRepayParams params{
        .asset = "USDT",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.margin_account_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountRepayBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountRepayParams params{.asset = "USDT", .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.margin_account_repay(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountRepayDebt) {
    const std::string example =
        R"json({"amount":"0.10000000","asset":"BNB","specifyRepayAssets":["USDT"],"updateTime":1636371437000,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountRepayDebtParams params{.asset = "USDT"};
    const auto res = api.margin_account_repay_debt(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/repay-debt");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountRepayDebtWithOptionalParams) {
    const std::string example =
        R"json({"amount":"0.10000000","asset":"BNB","specifyRepayAssets":["USDT"],"updateTime":1636371437000,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountRepayDebtParams params{
        .asset = "USDT",
        .amount = "1.0",
        .specify_repay_assets = "BNB",
        .recv_window = 5000,
    };
    const auto res = api.margin_account_repay_debt(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("specifyRepayAssets="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountRepayDebtBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountRepayDebtParams params{.asset = "USDT"};
    EXPECT_THROW((void)api.margin_account_repay_debt(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountTradeList) {
    const std::string example =
        R"json([{"commission":"0.00006000","commissionAsset":"BTC","id":34,"isBestMatch":true,"isBuyer":false,"isMaker":false,"orderId":39324,"price":"0.02000000","qty":"3.00000000","symbol":"BNBBTC","time":1561973357171}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountTradeListParams params{.symbol = "BTCUSDT"};
    const auto res = api.margin_account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/myTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountTradeListWithOptionalParams) {
    const std::string example =
        R"json([{"commission":"0.00006000","commissionAsset":"BTC","id":34,"isBestMatch":true,"isBuyer":false,"isMaker":false,"orderId":39324,"price":"0.02000000","qty":"3.00000000","symbol":"BNBBTC","time":1561973357171}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountTradeListParams params{
        .symbol = "BTCUSDT",
        .order_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .from_id = 1,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.margin_account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountTradeListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountTradeListParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.margin_account_trade_list(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAllCmConditionalOrders) {
    const std::string example =
        R"json([{"newClientStrategyId":"abc","strategyId":123445,"strategyStatus":"TRIGGERED","strategyType":"TRAILING_STOP_MARKET","origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","orderId":12123343534,"status":"NEW","bookTime":1566818724710,"updateTime":1566818724722,"triggerTime":1566818724750,"timeInForce":"GTC","type":"MARKET","activatePrice":"9020","priceRate":"0.3"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCmConditionalOrdersParams params{};
    const auto res = api.query_all_cm_conditional_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/conditional/allOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCmConditionalOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"newClientStrategyId":"abc","strategyId":123445,"strategyStatus":"TRIGGERED","strategyType":"TRAILING_STOP_MARKET","origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","orderId":12123343534,"status":"NEW","bookTime":1566818724710,"updateTime":1566818724722,"triggerTime":1566818724750,"timeInForce":"GTC","type":"MARKET","activatePrice":"9020","priceRate":"0.3"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCmConditionalOrdersParams params{
        .symbol = "BTCUSDT",
        .strategy_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_all_cm_conditional_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCmConditionalOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAllCmConditionalOrdersParams params{};
    EXPECT_THROW((void)api.query_all_cm_conditional_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAllCmOrders) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCmOrdersParams params{};
    const auto res = api.query_all_cm_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/allOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCmOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCmOrdersParams params{
        .symbol = "BTCUSD_200925",
        .pair = "BTCUSD",
        .order_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_all_cm_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCmOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAllCmOrdersParams params{};
    EXPECT_THROW((void)api.query_all_cm_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAllCurrentCmOpenConditionalOrders) {
    const std::string example =
        R"json([{"newClientStrategyId":"abc","strategyId":123445,"strategyStatus":"NEW","strategyType":"TRAILING_STOP_MARKET","origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","bookTime":1566818724710,"updateTime":1566818724722,"timeInForce":"GTC","activatePrice":"9020","priceRate":"0.3"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCurrentCmOpenConditionalOrdersParams params{};
    const auto res = api.query_all_current_cm_open_conditional_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/conditional/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCurrentCmOpenConditionalOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"newClientStrategyId":"abc","strategyId":123445,"strategyStatus":"NEW","strategyType":"TRAILING_STOP_MARKET","origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","bookTime":1566818724710,"updateTime":1566818724722,"timeInForce":"GTC","activatePrice":"9020","priceRate":"0.3"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCurrentCmOpenConditionalOrdersParams params{
        .symbol = "BTCUSD",
        .recv_window = 5000,
    };
    const auto res = api.query_all_current_cm_open_conditional_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCurrentCmOpenConditionalOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAllCurrentCmOpenConditionalOrdersParams params{};
    EXPECT_THROW((void)api.query_all_current_cm_open_conditional_orders(params),
                 common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAllCurrentCmOpenOrders) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCurrentCmOpenOrdersParams params{};
    const auto res = api.query_all_current_cm_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCurrentCmOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCurrentCmOpenOrdersParams params{
        .symbol = "BTCUSD_200925",
        .pair = "BTCUSD",
        .recv_window = 5000,
    };
    const auto res = api.query_all_current_cm_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCurrentCmOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAllCurrentCmOpenOrdersParams params{};
    EXPECT_THROW((void)api.query_all_current_cm_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAllCurrentUmOpenAlgoOrders) {
    const std::string example =
        R"json([{"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"NEW","triggerPrice":"750.000","price":"750.000","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750485492076,"triggerTime":0,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCurrentUmOpenAlgoOrdersParams params{};
    const auto res = api.query_all_current_um_open_algo_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/algo/openAlgoOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCurrentUmOpenAlgoOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"NEW","triggerPrice":"750.000","price":"750.000","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750485492076,"triggerTime":0,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCurrentUmOpenAlgoOrdersParams params{
        .algo_type = "CONDITIONAL",
        .symbol = "BNBUSDT",
        .algo_id = 2146760,
        .recv_window = 5000,
    };
    const auto res = api.query_all_current_um_open_algo_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCurrentUmOpenAlgoOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAllCurrentUmOpenAlgoOrdersParams params{};
    EXPECT_THROW((void)api.query_all_current_um_open_algo_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAllCurrentUmOpenOrders) {
    const std::string example =
        R"json([{"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCurrentUmOpenOrdersParams params{};
    const auto res = api.query_all_current_um_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCurrentUmOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllCurrentUmOpenOrdersParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_all_current_um_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllCurrentUmOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAllCurrentUmOpenOrdersParams params{};
    EXPECT_THROW((void)api.query_all_current_um_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAllMarginAccountOrders) {
    const std::string example =
        R"json([{"clientOrderId":"D2KDy4DIeS56PvkM13f8cP","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":false,"orderId":41295,"origQty":"5.31000000","price":"0.22500000","side":"SELL","status":"CANCELED","stopPrice":"0.18000000","symbol":"BNBBTC","time":1565769338806,"timeInForce":"GTC","type":"TAKE_PROFIT_LIMIT","updateTime":1565769342148,"accountId":152950866,"selfTradePreventionMode":"EXPIRE_TAKER","preventedMatchId":"null","preventedQuantity":"null"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllMarginAccountOrdersParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_all_margin_account_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/allOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllMarginAccountOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"clientOrderId":"D2KDy4DIeS56PvkM13f8cP","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":false,"orderId":41295,"origQty":"5.31000000","price":"0.22500000","side":"SELL","status":"CANCELED","stopPrice":"0.18000000","symbol":"BNBBTC","time":1565769338806,"timeInForce":"GTC","type":"TAKE_PROFIT_LIMIT","updateTime":1565769342148,"accountId":152950866,"selfTradePreventionMode":"EXPIRE_TAKER","preventedMatchId":"null","preventedQuantity":"null"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllMarginAccountOrdersParams params{
        .symbol = "BTCUSDT",
        .order_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_all_margin_account_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllMarginAccountOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAllMarginAccountOrdersParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_all_margin_account_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAllUmOrders) {
    const std::string example =
        R"json([{"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllUmOrdersParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_all_um_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/allOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllUmOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllUmOrdersParams params{
        .symbol = "BTCUSDT",
        .order_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_all_um_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllUmOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAllUmOrdersParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_all_um_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCmConditionalOrderHistory) {
    const std::string example =
        R"json({"newClientStrategyId":"abc","strategyId":123445,"strategyStatus":"TRIGGERED","strategyType":"TRAILING_STOP_MARKET","origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","orderId":12123343534,"status":"NEW","bookTime":1566818724710,"updateTime":1566818724722,"triggerTime":1566818724750,"timeInForce":"GTC","type":"MARKET","activatePrice":"9020","priceRate":"0.3","workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCmConditionalOrderHistoryParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_cm_conditional_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/conditional/orderHistory");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCmConditionalOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json({"newClientStrategyId":"abc","strategyId":123445,"strategyStatus":"TRIGGERED","strategyType":"TRAILING_STOP_MARKET","origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","orderId":12123343534,"status":"NEW","bookTime":1566818724710,"updateTime":1566818724722,"triggerTime":1566818724750,"timeInForce":"GTC","type":"MARKET","activatePrice":"9020","priceRate":"0.3","workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCmConditionalOrderHistoryParams params{
        .symbol = "BTCUSDT",
        .strategy_id = 1,
        .new_client_strategy_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_cm_conditional_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCmConditionalOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCmConditionalOrderHistoryParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_cm_conditional_order_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCmModifyOrderHistory) {
    const std::string example =
        R"json([{"amendmentId":5363,"symbol":"BTCUSD_PERP","pair":"BTCUSD","orderId":20072994037,"clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","time":1629184560899,"amendment":{"price":{"before":"30004","after":"30003.2"},"origQty":{"before":"1","after":"1"},"count":3,"modifyId":123}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCmModifyOrderHistoryParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_cm_modify_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/orderAmendment");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCmModifyOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"amendmentId":5363,"symbol":"BTCUSD_PERP","pair":"BTCUSD","orderId":20072994037,"clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","time":1629184560899,"amendment":{"price":{"before":"30004","after":"30003.2"},"origQty":{"before":"1","after":"1"},"count":3,"modifyId":123}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCmModifyOrderHistoryParams params{
        .symbol = "BTCUSDT",
        .order_id = 1,
        .orig_client_order_id = "1",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_cm_modify_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCmModifyOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCmModifyOrderHistoryParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_cm_modify_order_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCurrentCmOpenConditionalOrder) {
    const std::string example =
        R"json({"newClientStrategyId":"abc","strategyId":123445,"strategyStatus":"NEW","strategyType":"TRAILING_STOP_MARKET","origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","bookTime":1566818724710,"updateTime":1566818724722,"timeInForce":"GTC","activatePrice":"9020","priceRate":"0.3"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentCmOpenConditionalOrderParams params{.symbol = "BTCUSD_200925"};
    const auto res = api.query_current_cm_open_conditional_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/conditional/openOrder");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentCmOpenConditionalOrderWithOptionalParams) {
    const std::string example =
        R"json({"newClientStrategyId":"abc","strategyId":123445,"strategyStatus":"NEW","strategyType":"TRAILING_STOP_MARKET","origQty":"0.40","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","stopPrice":"9300","symbol":"BTCUSD","bookTime":1566818724710,"updateTime":1566818724722,"timeInForce":"GTC","activatePrice":"9020","priceRate":"0.3"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentCmOpenConditionalOrderParams params{
        .symbol = "BTCUSD_200925",
        .strategy_id = 1,
        .new_client_strategy_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_current_cm_open_conditional_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentCmOpenConditionalOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentCmOpenConditionalOrderParams params{.symbol = "BTCUSD_200925"};
    EXPECT_THROW((void)api.query_current_cm_open_conditional_order(params),
                 common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCurrentCmOpenOrder) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentCmOpenOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_current_cm_open_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/openOrder");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentCmOpenOrderWithOptionalParams) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentCmOpenOrderParams params{
        .symbol = "BTCUSDT",
        .order_id = 1917641,
        .orig_client_order_id = "abc",
        .recv_window = 5000,
    };
    const auto res = api.query_current_cm_open_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentCmOpenOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentCmOpenOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_current_cm_open_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCurrentMarginOpenOrder) {
    const std::string example =
        R"json([{"clientOrderId":"qhcZw71gAkCCTv0t0k8LUK","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":true,"orderId":211842552,"origQty":"0.30000000","price":"0.00475010","side":"SELL","status":"NEW","stopPrice":"0.00000000","symbol":"BNBBTC","time":1562040170089,"timeInForce":"GTC","type":"LIMIT","updateTime":1562040170089,"accountId":152950866,"selfTradePreventionMode":"EXPIRE_TAKER","preventedMatchId":"null","preventedQuantity":"null"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentMarginOpenOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_current_margin_open_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/openOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentMarginOpenOrderWithOptionalParams) {
    const std::string example =
        R"json([{"clientOrderId":"qhcZw71gAkCCTv0t0k8LUK","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":true,"orderId":211842552,"origQty":"0.30000000","price":"0.00475010","side":"SELL","status":"NEW","stopPrice":"0.00000000","symbol":"BNBBTC","time":1562040170089,"timeInForce":"GTC","type":"LIMIT","updateTime":1562040170089,"accountId":152950866,"selfTradePreventionMode":"EXPIRE_TAKER","preventedMatchId":"null","preventedQuantity":"null"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentMarginOpenOrderParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_current_margin_open_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentMarginOpenOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentMarginOpenOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_current_margin_open_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCurrentUmOpenAlgoOrder) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"CANCELED","actualOrderId":"","actualPrice":"0.00000","triggerPrice":"750.000","price":"750.000","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750514545091,"triggerTime":0,"goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentUmOpenAlgoOrderParams params{};
    const auto res = api.query_current_um_open_algo_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/algo/algoOrder");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentUmOpenAlgoOrderWithOptionalParams) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"CANCELED","actualOrderId":"","actualPrice":"0.00000","triggerPrice":"750.000","price":"750.000","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750514545091,"triggerTime":0,"goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentUmOpenAlgoOrderParams params{
        .algo_id = 2146760,
        .client_algo_id = "6B2I9XVcJpCjqPAJ4YoFX7",
        .recv_window = 5000,
    };
    const auto res = api.query_current_um_open_algo_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientAlgoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentUmOpenAlgoOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentUmOpenAlgoOrderParams params{};
    EXPECT_THROW((void)api.query_current_um_open_algo_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCurrentUmOpenOrder) {
    const std::string example =
        R"json({"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentUmOpenOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_current_um_open_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/openOrder");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentUmOpenOrderWithOptionalParams) {
    const std::string example =
        R"json({"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"LIMIT","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"LIMIT","updateTime":1579276756075,"selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"priceMatch":"NONE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentUmOpenOrderParams params{
        .symbol = "BTCUSDT",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_current_um_open_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentUmOpenOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentUmOpenOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_current_um_open_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsAllOco) {
    const std::string example =
        R"json([{"orderListId":29,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"amEEAXryFzFwYF1FeRpUoZ","transactionTime":1565245913483,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"oD7aesZqjEGlZrbtRpy5zB"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsAllOcoParams params{};
    const auto res = api.query_margin_accounts_all_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/allOrderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsAllOcoWithOptionalParams) {
    const std::string example =
        R"json([{"orderListId":29,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"amEEAXryFzFwYF1FeRpUoZ","transactionTime":1565245913483,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"oD7aesZqjEGlZrbtRpy5zB"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsAllOcoParams params{
        .from_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_all_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsAllOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsAllOcoParams params{};
    EXPECT_THROW((void)api.query_margin_accounts_all_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOco) {
    const std::string example =
        R"json([{"orderListId":31,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"wuB13fmulKj3YjdqWEcsnp","transactionTime":1565246080644,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"r3EH2N76dHfLoSZWIUw1bT"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOcoParams params{};
    const auto res = api.query_margin_accounts_open_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/openOrderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOcoWithOptionalParams) {
    const std::string example =
        R"json([{"orderListId":31,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"wuB13fmulKj3YjdqWEcsnp","transactionTime":1565246080644,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"r3EH2N76dHfLoSZWIUw1bT"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOcoParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_open_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOcoParams params{};
    EXPECT_THROW((void)api.query_margin_accounts_open_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryUmAlgoOrderHistory) {
    const std::string example =
        R"json([{"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"CANCELED","actualOrderId":"","actualPrice":"0.00000","triggerPrice":"750.000","price":"750.000","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750514545091,"triggerTime":0,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUmAlgoOrderHistoryParams params{.symbol = "BNBUSDT"};
    const auto res = api.query_um_algo_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/algo/allAlgoOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUmAlgoOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"CANCELED","actualOrderId":"","actualPrice":"0.00000","triggerPrice":"750.000","price":"750.000","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750514545091,"triggerTime":0,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUmAlgoOrderHistoryParams params{
        .symbol = "BNBUSDT",
        .algo_id = 2146760,
        .start_time = 1770130294138,
        .end_time = 1770736694138,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_um_algo_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUmAlgoOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUmAlgoOrderHistoryParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.query_um_algo_order_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryUmModifyOrderHistory) {
    const std::string example =
        R"json([{"amendmentId":5363,"symbol":"BTCUSDT","pair":"BTCUSDT","orderId":20072994037,"clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","time":1629184560899,"amendment":{"price":{"before":"30004","after":"30003.2"},"origQty":{"before":"1","after":"1"},"count":3,"modifyId":123},"priceMatch":"NONE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUmModifyOrderHistoryParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_um_modify_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/orderAmendment");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUmModifyOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"amendmentId":5363,"symbol":"BTCUSDT","pair":"BTCUSDT","orderId":20072994037,"clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","time":1629184560899,"amendment":{"price":{"before":"30004","after":"30003.2"},"origQty":{"before":"1","after":"1"},"count":3,"modifyId":123},"priceMatch":"NONE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUmModifyOrderHistoryParams params{
        .symbol = "BTCUSDT",
        .order_id = 1,
        .orig_client_order_id = "1",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_um_modify_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUmModifyOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUmModifyOrderHistoryParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_um_modify_order_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryUsersCmForceOrders) {
    const std::string example =
        R"json([{"orderId":165123080,"symbol":"BTCUSD_200925","pair":"BTCUSD","status":"FILLED","clientOrderId":"autoclose-1596542005017000006","price":"11326.9","avgPrice":"11326.9","origQty":"1","executedQty":"1","cumBase":"0.00882854","timeInForce":"IOC","type":"LIMIT","reduceOnly":false,"side":"SELL","positionSide":"BOTH","origType":"LIMIT","time":1596542005019,"updateTime":1596542005050}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUsersCmForceOrdersParams params{};
    const auto res = api.query_users_cm_force_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/forceOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUsersCmForceOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":165123080,"symbol":"BTCUSD_200925","pair":"BTCUSD","status":"FILLED","clientOrderId":"autoclose-1596542005017000006","price":"11326.9","avgPrice":"11326.9","origQty":"1","executedQty":"1","cumBase":"0.00882854","timeInForce":"IOC","type":"LIMIT","reduceOnly":false,"side":"SELL","positionSide":"BOTH","origType":"LIMIT","time":1596542005019,"updateTime":1596542005050}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUsersCmForceOrdersParams params{
        .symbol = "BTCUSDT",
        .auto_close_type = QueryUsersCmForceOrdersAutoCloseTypeEnum::Liquidation,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_users_cm_force_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoCloseType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUsersCmForceOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUsersCmForceOrdersParams params{};
    EXPECT_THROW((void)api.query_users_cm_force_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryUsersMarginForceOrders) {
    const std::string example =
        R"json({"rows":[{"avgPrice":"0.00388359","executedQty":"31.39000000","orderId":180015097,"price":"0.00388110","qty":"31.39000000","side":"SELL","symbol":"BNBBTC","timeInForce":"GTC","updatedTime":1558941374745}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUsersMarginForceOrdersParams params{};
    const auto res = api.query_users_margin_force_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/forceOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUsersMarginForceOrdersWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"avgPrice":"0.00388359","executedQty":"31.39000000","orderId":180015097,"price":"0.00388110","qty":"31.39000000","side":"SELL","symbol":"BNBBTC","timeInForce":"GTC","updatedTime":1558941374745}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUsersMarginForceOrdersParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_users_margin_force_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUsersMarginForceOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUsersMarginForceOrdersParams params{};
    EXPECT_THROW((void)api.query_users_margin_force_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryUsersUmForceOrders) {
    const std::string example =
        R"json([{"orderId":6071832819,"symbol":"BTCUSDT","status":"FILLED","clientOrderId":"autoclose-1596107620040000020","price":"10871.09","avgPrice":"10913.21000","origQty":"0.001","executedQty":"0.001","cumQuote":"10.91321","timeInForce":"IOC","type":"LIMIT","reduceOnly":false,"side":"SELL","positionSide":"BOTH","origType":"LIMIT","time":1596107620044,"updateTime":1596107620087}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUsersUmForceOrdersParams params{};
    const auto res = api.query_users_um_force_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/forceOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUsersUmForceOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":6071832819,"symbol":"BTCUSDT","status":"FILLED","clientOrderId":"autoclose-1596107620040000020","price":"10871.09","avgPrice":"10913.21000","origQty":"0.001","executedQty":"0.001","cumQuote":"10.91321","timeInForce":"IOC","type":"LIMIT","reduceOnly":false,"side":"SELL","positionSide":"BOTH","origType":"LIMIT","time":1596107620044,"updateTime":1596107620087}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUsersUmForceOrdersParams params{
        .symbol = "BTCUSDT",
        .auto_close_type = QueryUsersUmForceOrdersAutoCloseTypeEnum::Liquidation,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_users_um_force_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoCloseType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryUsersUmForceOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUsersUmForceOrdersParams params{};
    EXPECT_THROW((void)api.query_users_um_force_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, UmAccountTradeList) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","id":67880589,"orderId":270093109,"side":"SELL","price":"28511.00","qty":"0.010","realizedPnl":"2.58500000","quoteQty":"285.11000","commission":"0.11404400","commissionAsset":"USDT","time":1680688557875,"buyer":false,"maker":false,"positionSide":"BOTH"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmAccountTradeListParams params{.symbol = "BTCUSDT"};
    const auto res = api.um_account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/userTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UmAccountTradeListWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","id":67880589,"orderId":270093109,"side":"SELL","price":"28511.00","qty":"0.010","realizedPnl":"2.58500000","quoteQty":"285.11000","commission":"0.11404400","commissionAsset":"USDT","time":1680688557875,"buyer":false,"maker":false,"positionSide":"BOTH"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmAccountTradeListParams params{
        .symbol = "BTCUSDT",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .from_id = 1,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.um_account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UmAccountTradeListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UmAccountTradeListParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.um_account_trade_list(params), common::BadRequestError);
}

TEST(RestApiTradeApi, UmPositionAdlQuantileEstimation) {
    const std::string example =
        R"json([{"symbol":"ETHUSDT","adlQuantile":{"LONG":3,"SHORT":3,"BOTH":0}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmPositionAdlQuantileEstimationParams params{};
    const auto res = api.um_position_adl_quantile_estimation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/adlQuantile");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UmPositionAdlQuantileEstimationWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"ETHUSDT","adlQuantile":{"LONG":3,"SHORT":3,"BOTH":0}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmPositionAdlQuantileEstimationParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.um_position_adl_quantile_estimation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UmPositionAdlQuantileEstimationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UmPositionAdlQuantileEstimationParams params{};
    EXPECT_THROW((void)api.um_position_adl_quantile_estimation(params), common::BadRequestError);
}
