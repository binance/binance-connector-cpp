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
#include <binance/derivatives_trading_coin_futures/rest_api/trade_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_coin_futures::rest_api;
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

TEST(RestApiTradeApi, AccountTradeList) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200626","id":6,"orderId":28,"pair":"BTCUSD","side":"SELL","price":"8800","qty":"1","realizedPnl":"0","marginAsset":"BTC","baseQty":"0.01136364","quoteQty":"0","commission":"0.00000454","commissionAsset":"BTC","time":1590743483586,"positionSide":"BOTH","buyer":false,"maker":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountTradeListParams params{};
    const auto res = api.account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/userTrades");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AccountTradeListWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200626","id":6,"orderId":28,"pair":"BTCUSD","side":"SELL","price":"8800","qty":"1","realizedPnl":"0","marginAsset":"BTC","baseQty":"0.01136364","quoteQty":"0","commission":"0.00000454","commissionAsset":"BTC","time":1590743483586,"positionSide":"BOTH","buyer":false,"maker":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountTradeListParams params{
        .symbol = "BTCUSD_200626",
        .pair = "BTCUSD",
        .order_id = "1",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .from_id = 6,
        .limit = 30,
        .recv_window = 5000,
    };
    const auto res = api.account_trade_list(params);
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
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AccountTradeListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountTradeListParams params{};
    EXPECT_THROW((void)api.account_trade_list(params), common::BadRequestError);
}

TEST(RestApiTradeApi, AllOrders) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTD","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1579385751000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllOrdersParams params{};
    const auto res = api.all_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/allOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AllOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTD","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1579385751000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllOrdersParams params{
        .symbol = "BTCUSD_200925",
        .pair = "BTCUSD",
        .order_id = 1917641,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
        .recv_window = 5000,
    };
    const auto res = api.all_orders(params);
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

TEST(RestApiTradeApi, AllOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AllOrdersParams params{};
    EXPECT_THROW((void)api.all_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, AutoCancelAllOpenOrders) {
    const std::string example = R"json({"symbol":"BTCUSD_200925","countdownTime":"100000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AutoCancelAllOpenOrdersParams params{.symbol = "BTCUSD_200925", .countdown_time = 1000};
    const auto res = api.auto_cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/dapi/v1/countdownCancelAll");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("countdownTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AutoCancelAllOpenOrdersWithOptionalParams) {
    const std::string example = R"json({"symbol":"BTCUSD_200925","countdownTime":"100000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AutoCancelAllOpenOrdersParams params{
        .symbol = "BTCUSD_200925",
        .countdown_time = 1000,
        .recv_window = 5000,
    };
    const auto res = api.auto_cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("countdownTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AutoCancelAllOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AutoCancelAllOpenOrdersParams params{.symbol = "BTCUSD_200925", .countdown_time = 1000};
    EXPECT_THROW((void)api.auto_cancel_all_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelAllOpenOrders) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllOpenOrdersParams params{.symbol = "BTCUSD_200925"};
    const auto res = api.cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/dapi/v1/allOpenOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllOpenOrdersParams params{
        .symbol = "BTCUSD_200925",
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_open_orders(params);
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

TEST(RestApiTradeApi, CancelAllOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllOpenOrdersParams params{.symbol = "BTCUSD_200925"};
    EXPECT_THROW((void)api.cancel_all_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelMultipleOrders) {
    const std::string example =
        R"json([{"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","origType":"TRAILING_STOP_MARKET","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","updateTime":1571110484038,"code":-2011,"msg":"Unknown order sent."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMultipleOrdersParams params{.symbol = "BTCUSD_200925"};
    const auto res = api.cancel_multiple_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/dapi/v1/batchOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelMultipleOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","origType":"TRAILING_STOP_MARKET","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","updateTime":1571110484038,"code":-2011,"msg":"Unknown order sent."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMultipleOrdersParams params{
        .symbol = "BTCUSD_200925",
        .order_id_list = std::vector<std::int64_t>{},
        .orig_client_order_id_list = std::vector<std::string>{},
        .recv_window = 5000,
    };
    const auto res = api.cancel_multiple_orders(params);
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

TEST(RestApiTradeApi, CancelMultipleOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelMultipleOrdersParams params{.symbol = "BTCUSD_200925"};
    EXPECT_THROW((void)api.cancel_multiple_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ModifyMultipleOrders) {
    const std::string example =
        R"json([{"orderId":20072994037,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","updateTime":1629182711600,"code":-2022,"msg":"ReduceOnly Order is rejected."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyMultipleOrdersParams params{
        .batch_orders = std::vector<ModifyMultipleOrdersBatchOrdersParameterInner>{}};
    const auto res = api.modify_multiple_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/dapi/v1/batchOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("batchOrders="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyMultipleOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":20072994037,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","updateTime":1629182711600,"code":-2022,"msg":"ReduceOnly Order is rejected."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyMultipleOrdersParams params{
        .batch_orders = std::vector<ModifyMultipleOrdersBatchOrdersParameterInner>{},
        .recv_window = 5000,
    };
    const auto res = api.modify_multiple_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyMultipleOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ModifyMultipleOrdersParams params{
        .batch_orders = std::vector<ModifyMultipleOrdersBatchOrdersParameterInner>{}};
    EXPECT_THROW((void)api.modify_multiple_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, PlaceMultipleOrders) {
    const std::string example =
        R"json([{"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","type":"TRAILING_STOP_MARKET","origType":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","code":-2022,"msg":"ReduceOnly Order is rejected."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceMultipleOrdersParams params{
        .batch_orders = std::vector<PlaceMultipleOrdersBatchOrdersParameterInner>{}};
    const auto res = api.place_multiple_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/dapi/v1/batchOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("batchOrders="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceMultipleOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","type":"TRAILING_STOP_MARKET","origType":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","code":-2022,"msg":"ReduceOnly Order is rejected."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceMultipleOrdersParams params{
        .batch_orders = std::vector<PlaceMultipleOrdersBatchOrdersParameterInner>{},
        .recv_window = 5000,
    };
    const auto res = api.place_multiple_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceMultipleOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PlaceMultipleOrdersParams params{
        .batch_orders = std::vector<PlaceMultipleOrdersBatchOrdersParameterInner>{}};
    EXPECT_THROW((void)api.place_multiple_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelOrder) {
    const std::string example =
        R"json({"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","origType":"TRAILING_STOP_MARKET","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1571110484038,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelOrderParams params{.symbol = "BTCUSD_200925"};
    const auto res = api.cancel_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/dapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","origType":"TRAILING_STOP_MARKET","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1571110484038,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelOrderParams params{
        .symbol = "BTCUSD_200925",
        .order_id = 283194212,
        .orig_client_order_id = "myOrder1",
        .recv_window = 5000,
    };
    const auto res = api.cancel_order(params);
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

TEST(RestApiTradeApi, CancelOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelOrderParams params{.symbol = "BTCUSD_200925"};
    EXPECT_THROW((void)api.cancel_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ModifyOrder) {
    const std::string example =
        R"json({"orderId":20072994037,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","updateTime":1629182711600})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyOrderParams params{.symbol = "BTCUSD_PERP", .side = ModifyOrderSideEnum::Buy};
    const auto res = api.modify_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/dapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyOrderWithOptionalParams) {
    const std::string example =
        R"json({"orderId":20072994037,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","updateTime":1629182711600})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyOrderParams params{
        .symbol = "BTCUSD_PERP",
        .side = ModifyOrderSideEnum::Buy,
        .order_id = 1,
        .orig_client_order_id = "1",
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .price_match = ModifyOrderPriceMatchEnum::Opponent,
        .modify_id = 1,
        .recv_window = 5000,
    };
    const auto res = api.modify_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceMatch="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("modifyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ModifyOrderParams params{.symbol = "BTCUSD_PERP", .side = ModifyOrderSideEnum::Buy};
    EXPECT_THROW((void)api.modify_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewOrder) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"closePosition":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","type":"TRAILING_STOP_MARKET","origType":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTCUSD_200925", .side = NewOrderSideEnum::Buy, .type = NewOrderTypeEnum::Limit};
    const auto res = api.new_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/dapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"closePosition":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","symbol":"BTCUSD_200925","pair":"BTCUSD","timeInForce":"GTC","type":"TRAILING_STOP_MARKET","origType":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTCUSD_200925",
        .side = NewOrderSideEnum::Buy,
        .type = NewOrderTypeEnum::Limit,
        .position_side = NewOrderPositionSideEnum::Both,
        .reduce_only = NewOrderReduceOnlyEnum::True_,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .new_client_order_id = "1",
        .stop_price = common::Decimal("1.0"),
        .close_position = "true",
        .activation_price = common::Decimal("1.0"),
        .callback_rate = common::Decimal("5000.0"),
        .time_in_force = NewOrderTimeInForceEnum::Gtc,
        .working_type = NewOrderWorkingTypeEnum::MarkPrice,
        .price_protect = NewOrderPriceProtectEnum::True_,
        .new_order_resp_type = NewOrderNewOrderRespTypeEnum::Ack,
        .price_match = NewOrderPriceMatchEnum::Opponent,
        .self_trade_prevention_mode = NewOrderSelfTradePreventionModeEnum::None_,
        .recv_window = 5000,
    };
    const auto res = api.new_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("closePosition="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("activationPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("callbackRate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceProtect="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceMatch="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTCUSD_200925", .side = NewOrderSideEnum::Buy, .type = NewOrderTypeEnum::Limit};
    EXPECT_THROW((void)api.new_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryOrder) {
    const std::string example =
        R"json({"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1573346959,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOrderParams params{.symbol = "BTCUSD_200925"};
    const auto res = api.query_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryOrderWithOptionalParams) {
    const std::string example =
        R"json({"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1573346959,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOrderParams params{
        .symbol = "BTCUSD_200925",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_order(params);
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

TEST(RestApiTradeApi, QueryOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryOrderParams params{.symbol = "BTCUSD_200925"};
    EXPECT_THROW((void)api.query_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ChangeInitialLeverage) {
    const std::string example =
        R"json({"leverage":21,"maxQty":"1000","symbol":"BTCUSD_200925"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeInitialLeverageParams params{.symbol = "BTCUSD_200925", .leverage = 1};
    const auto res = api.change_initial_leverage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/dapi/v1/leverage");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("leverage="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ChangeInitialLeverageWithOptionalParams) {
    const std::string example =
        R"json({"leverage":21,"maxQty":"1000","symbol":"BTCUSD_200925"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeInitialLeverageParams params{
        .symbol = "BTCUSD_200925",
        .leverage = 1,
        .recv_window = 5000,
    };
    const auto res = api.change_initial_leverage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("leverage="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ChangeInitialLeverageBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ChangeInitialLeverageParams params{.symbol = "BTCUSD_200925", .leverage = 1};
    EXPECT_THROW((void)api.change_initial_leverage(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ChangeMarginType) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeMarginTypeParams params{.symbol = "BTCUSD_200925",
                                        .margin_type = ChangeMarginTypeMarginTypeEnum::Isolated};
    const auto res = api.change_margin_type(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/dapi/v1/marginType");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marginType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ChangeMarginTypeWithOptionalParams) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeMarginTypeParams params{
        .symbol = "BTCUSD_200925",
        .margin_type = ChangeMarginTypeMarginTypeEnum::Isolated,
        .recv_window = 5000,
    };
    const auto res = api.change_margin_type(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marginType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ChangeMarginTypeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ChangeMarginTypeParams params{.symbol = "BTCUSD_200925",
                                        .margin_type = ChangeMarginTypeMarginTypeEnum::Isolated};
    EXPECT_THROW((void)api.change_margin_type(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ChangePositionMode) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangePositionModeParams params{.dual_side_position = "true"};
    const auto res = api.change_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/dapi/v1/positionSide/dual");
    EXPECT_NE((rec.query() + "&" + rec.body).find("dualSidePosition="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ChangePositionModeWithOptionalParams) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangePositionModeParams params{
        .dual_side_position = "true",
        .recv_window = 5000,
    };
    const auto res = api.change_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("dualSidePosition="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ChangePositionModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ChangePositionModeParams params{.dual_side_position = "true"};
    EXPECT_THROW((void)api.change_position_mode(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CurrentAllOpenOrders) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentAllOpenOrdersParams params{};
    const auto res = api.current_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CurrentAllOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentAllOpenOrdersParams params{
        .symbol = "BTCUSD_200925",
        .pair = "BTCUSD",
        .recv_window = 5000,
    };
    const auto res = api.current_all_open_orders(params);
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

TEST(RestApiTradeApi, CurrentAllOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CurrentAllOpenOrdersParams params{};
    EXPECT_THROW((void)api.current_all_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetOrderModifyHistory) {
    const std::string example =
        R"json([{"amendmentId":5363,"symbol":"BTCUSD_PERP","pair":"BTCUSD","orderId":20072994037,"clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","time":1629184560899,"amendment":{"price":{"before":"30004","after":"30003.2"},"origQty":{"before":"1","after":"1"},"count":3,"modifyId":123}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderModifyHistoryParams params{.symbol = "BTCUSD_PERP"};
    const auto res = api.get_order_modify_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/orderAmendment");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetOrderModifyHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"amendmentId":5363,"symbol":"BTCUSD_PERP","pair":"BTCUSD","orderId":20072994037,"clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","time":1629184560899,"amendment":{"price":{"before":"30004","after":"30003.2"},"origQty":{"before":"1","after":"1"},"count":3,"modifyId":123}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderModifyHistoryParams params{
        .symbol = "BTCUSD_PERP",
        .order_id = 20072994037,
        .orig_client_order_id = "LJ9R4QZDihCaS8UAOOLpgW",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
        .recv_window = 5000,
    };
    const auto res = api.get_order_modify_history(params);
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

TEST(RestApiTradeApi, GetOrderModifyHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOrderModifyHistoryParams params{.symbol = "BTCUSD_PERP"};
    EXPECT_THROW((void)api.get_order_modify_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetPositionMarginChangeHistory) {
    const std::string example =
        R"json([{"amount":"23.36332311","asset":"BTC","symbol":"BTCUSD_200925","time":1578047897183,"type":1,"positionSide":"BOTH"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPositionMarginChangeHistoryParams params{.symbol = "BTCUSD"};
    const auto res = api.get_position_margin_change_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/positionMargin/history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetPositionMarginChangeHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"amount":"23.36332311","asset":"BTC","symbol":"BTCUSD_200925","time":1578047897183,"type":1,"positionSide":"BOTH"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPositionMarginChangeHistoryParams params{
        .symbol = "BTCUSD",
        .type = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
        .recv_window = 5000,
    };
    const auto res = api.get_position_margin_change_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetPositionMarginChangeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetPositionMarginChangeHistoryParams params{.symbol = "BTCUSD"};
    EXPECT_THROW((void)api.get_position_margin_change_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ModifyIsolatedPositionMargin) {
    const std::string example =
        R"json({"amount":100,"code":200,"msg":"Successfully modify position margin.","type":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyIsolatedPositionMarginParams params{
        .symbol = "BTCUSDT", .amount = common::Decimal("1.0"), .type = 1};
    const auto res = api.modify_isolated_position_margin(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/dapi/v1/positionMargin");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyIsolatedPositionMarginWithOptionalParams) {
    const std::string example =
        R"json({"amount":100,"code":200,"msg":"Successfully modify position margin.","type":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyIsolatedPositionMarginParams params{
        .symbol = "BTCUSDT",
        .amount = common::Decimal("1.0"),
        .type = 1,
        .position_side = ModifyIsolatedPositionMarginPositionSideEnum::Both,
        .recv_window = 5000,
    };
    const auto res = api.modify_isolated_position_margin(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyIsolatedPositionMarginBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ModifyIsolatedPositionMarginParams params{
        .symbol = "BTCUSDT", .amount = common::Decimal("1.0"), .type = 1};
    EXPECT_THROW((void)api.modify_isolated_position_margin(params), common::BadRequestError);
}

TEST(RestApiTradeApi, PositionAdlQuantileEstimation) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200925","adlQuantile":{"LONG":3,"SHORT":3,"HEDGE":0,"BOTH":0}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionAdlQuantileEstimationParams params{};
    const auto res = api.position_adl_quantile_estimation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/adlQuantile");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PositionAdlQuantileEstimationWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200925","adlQuantile":{"LONG":3,"SHORT":3,"HEDGE":0,"BOTH":0}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionAdlQuantileEstimationParams params{
        .symbol = "BTCUSD_200925",
        .recv_window = 5000,
    };
    const auto res = api.position_adl_quantile_estimation(params);
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

TEST(RestApiTradeApi, PositionAdlQuantileEstimationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PositionAdlQuantileEstimationParams params{};
    EXPECT_THROW((void)api.position_adl_quantile_estimation(params), common::BadRequestError);
}

TEST(RestApiTradeApi, PositionInformation) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_201225","positionAmt":"0","entryPrice":"0.0","breakEvenPrice":"0.0","markPrice":"0.00000000","unRealizedProfit":"0.00000000","liquidationPrice":"0","leverage":"125","maxQty":"50","marginType":"cross","isolatedMargin":"0.00000000","isAutoAddMargin":"false","positionSide":"BOTH","updateTime":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionInformationParams params{};
    const auto res = api.position_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/positionRisk");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PositionInformationWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_201225","positionAmt":"0","entryPrice":"0.0","breakEvenPrice":"0.0","markPrice":"0.00000000","unRealizedProfit":"0.00000000","liquidationPrice":"0","leverage":"125","maxQty":"50","marginType":"cross","isolatedMargin":"0.00000000","isAutoAddMargin":"false","positionSide":"BOTH","updateTime":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionInformationParams params{
        .margin_asset = "USDT",
        .pair = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.position_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marginAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PositionInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PositionInformationParams params{};
    EXPECT_THROW((void)api.position_information(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCurrentOpenOrder) {
    const std::string example =
        R"json({"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentOpenOrderParams params{.symbol = "BTCUSD_200925"};
    const auto res = api.query_current_open_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/openOrder");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentOpenOrderWithOptionalParams) {
    const std::string example =
        R"json({"avgPrice":"0.0","clientOrderId":"abc","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSD_200925","pair":"BTCUSD","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentOpenOrderParams params{
        .symbol = "BTCUSD_200925",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_current_open_order(params);
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

TEST(RestApiTradeApi, QueryCurrentOpenOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentOpenOrderParams params{.symbol = "BTCUSD_200925"};
    EXPECT_THROW((void)api.query_current_open_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, UsersForceOrders) {
    const std::string example =
        R"json([{"orderId":165123080,"symbol":"BTCUSD_200925","pair":"BTCUSD","status":"FILLED","clientOrderId":"autoclose-1596542005017000006","price":"11326.9","avgPrice":"11326.9","origQty":"1","executedQty":"1","cumBase":"0.00882854","cumQuote":"100","timeInForce":"IOC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"SELL","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","time":1596542005019,"updateTime":1596542005050,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UsersForceOrdersParams params{};
    const auto res = api.users_force_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/forceOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UsersForceOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":165123080,"symbol":"BTCUSD_200925","pair":"BTCUSD","status":"FILLED","clientOrderId":"autoclose-1596542005017000006","price":"11326.9","avgPrice":"11326.9","origQty":"1","executedQty":"1","cumBase":"0.00882854","cumQuote":"100","timeInForce":"IOC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"SELL","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","time":1596542005019,"updateTime":1596542005050,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UsersForceOrdersParams params{
        .symbol = "BTCUSD_200925",
        .auto_close_type = UsersForceOrdersAutoCloseTypeEnum::Liquidation,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
        .recv_window = 5000,
    };
    const auto res = api.users_force_orders(params);
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

TEST(RestApiTradeApi, UsersForceOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UsersForceOrdersParams params{};
    EXPECT_THROW((void)api.users_force_orders(params), common::BadRequestError);
}
