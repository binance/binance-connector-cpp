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
#include <binance/derivatives_trading_usds_futures/rest_api/trade_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_usds_futures::rest_api;
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
        R"json([{"buyer":false,"commission":"0.07819010","commissionAsset":"USDT","id":698759,"maker":false,"orderId":25851813,"price":"7819.01","qty":"0.002","quoteQty":"15.63802","baseQty":"0","marginAsset":"USDT","realizedPnl":"-0.91539999","side":"SELL","positionSide":"SHORT","symbol":"BTCUSDT","pair":"BTCUSDT","time":1569514978020}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountTradeListParams params{.symbol = "BTCUSDT"};
    const auto res = api.account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/userTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AccountTradeListWithOptionalParams) {
    const std::string example =
        R"json([{"buyer":false,"commission":"0.07819010","commissionAsset":"USDT","id":698759,"maker":false,"orderId":25851813,"price":"7819.01","qty":"0.002","quoteQty":"15.63802","baseQty":"0","marginAsset":"USDT","realizedPnl":"-0.91539999","side":"SELL","positionSide":"SHORT","symbol":"BTCUSDT","pair":"BTCUSDT","time":1569514978020}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountTradeListParams params{
        .symbol = "BTCUSDT",
        .order_id = 25851813,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .from_id = 1,
        .limit = 50,
        .recv_window = 5000,
    };
    const auto res = api.account_trade_list(params);
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

TEST(RestApiTradeApi, AccountTradeListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountTradeListParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.account_trade_list(params), common::BadRequestError);
}

TEST(RestApiTradeApi, AllOrders) {
    const std::string example =
        R"json([{"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","pair":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllOrdersParams params{};
    const auto res = api.all_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/allOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AllOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","cumBase":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","pair":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllOrdersParams params{
        .symbol = "BTCUSDT",
        .order_id = 1917641,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
        .recv_window = 5000,
    };
    const auto res = api.all_orders(params);
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

TEST(RestApiTradeApi, AllOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AllOrdersParams params{};
    EXPECT_THROW((void)api.all_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, AutoCancelAllOpenOrders) {
    const std::string example = R"json({"symbol":"BTCUSDT","countdownTime":"100000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AutoCancelAllOpenOrdersParams params{.symbol = "BTCUSDT", .countdown_time = 1000};
    const auto res = api.auto_cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/countdownCancelAll");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("countdownTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AutoCancelAllOpenOrdersWithOptionalParams) {
    const std::string example = R"json({"symbol":"BTCUSDT","countdownTime":"100000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AutoCancelAllOpenOrdersParams params{
        .symbol = "BTCUSDT",
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
    const AutoCancelAllOpenOrdersParams params{.symbol = "BTCUSDT", .countdown_time = 1000};
    EXPECT_THROW((void)api.auto_cancel_all_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelAlgoOrder) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","code":"200","msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAlgoOrderParams params{};
    const auto res = api.cancel_algo_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/fapi/v1/algoOrder");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAlgoOrderWithOptionalParams) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","code":"200","msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAlgoOrderParams params{
        .algo_id = 2146760,
        .client_algo_id = "6B2I9XVcJpCjqPAJ4YoFX7",
        .recv_window = 5000,
    };
    const auto res = api.cancel_algo_order(params);
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

TEST(RestApiTradeApi, CancelAlgoOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAlgoOrderParams params{};
    EXPECT_THROW((void)api.cancel_algo_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewAlgoOrder) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"NEW","triggerPrice":"750.000","price":"750.000","icebergQuantity":"null","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"activatePrice":"","callbackRate":"","createTime":1750485492076,"updateTime":1750485492076,"triggerTime":0,"goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewAlgoOrderParams params{.algo_type = NewAlgoOrderAlgoTypeEnum::Conditional,
                                    .symbol = "BNBUSDT",
                                    .side = NewAlgoOrderSideEnum::Buy,
                                    .type = NewAlgoOrderTypeEnum::Limit};
    const auto res = api.new_algo_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/algoOrder");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algoType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewAlgoOrderWithOptionalParams) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"NEW","triggerPrice":"750.000","price":"750.000","icebergQuantity":"null","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"activatePrice":"","callbackRate":"","createTime":1750485492076,"updateTime":1750485492076,"triggerTime":0,"goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewAlgoOrderParams params{
        .algo_type = NewAlgoOrderAlgoTypeEnum::Conditional,
        .symbol = "BNBUSDT",
        .side = NewAlgoOrderSideEnum::Buy,
        .type = NewAlgoOrderTypeEnum::Limit,
        .position_side = "BOTH",
        .time_in_force = NewAlgoOrderTimeInForceEnum::Gtc,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .trigger_price = common::Decimal("1.0"),
        .working_type = NewAlgoOrderWorkingTypeEnum::MarkPrice,
        .price_match = NewAlgoOrderPriceMatchEnum::Opponent,
        .close_position = NewAlgoOrderClosePositionEnum::True_,
        .price_protect = NewAlgoOrderPriceProtectEnum::True_,
        .reduce_only = NewAlgoOrderReduceOnlyEnum::True_,
        .activate_price = common::Decimal("1.0"),
        .callback_rate = common::Decimal("1"),
        .client_algo_id = "1",
        .new_order_resp_type = NewAlgoOrderNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = NewAlgoOrderSelfTradePreventionModeEnum::None_,
        .good_till_date = 1770736694138,
        .recv_window = 5000,
    };
    const auto res = api.new_algo_order(params);
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

TEST(RestApiTradeApi, NewAlgoOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewAlgoOrderParams params{.algo_type = NewAlgoOrderAlgoTypeEnum::Conditional,
                                    .symbol = "BNBUSDT",
                                    .side = NewAlgoOrderSideEnum::Buy,
                                    .type = NewAlgoOrderTypeEnum::Limit};
    EXPECT_THROW((void)api.new_algo_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAlgoOrder) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"CANCELED","actualOrderId":"","actualPrice":"0.00000","actualType":"LIMIT","actualQty":"0.01","triggerPrice":"750.000","price":"750.000","icebergQuantity":"null","tpOrderType":"","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750514545091,"triggerTime":0,"goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAlgoOrderParams params{};
    const auto res = api.query_algo_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/algoOrder");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAlgoOrderWithOptionalParams) {
    const std::string example =
        R"json({"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"CANCELED","actualOrderId":"","actualPrice":"0.00000","actualType":"LIMIT","actualQty":"0.01","triggerPrice":"750.000","price":"750.000","icebergQuantity":"null","tpOrderType":"","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750514545091,"triggerTime":0,"goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAlgoOrderParams params{
        .algo_id = 1,
        .client_algo_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_algo_order(params);
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

TEST(RestApiTradeApi, QueryAlgoOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAlgoOrderParams params{};
    EXPECT_THROW((void)api.query_algo_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelAllAlgoOpenOrders) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllAlgoOpenOrdersParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_all_algo_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/fapi/v1/algoOpenOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllAlgoOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllAlgoOpenOrdersParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_algo_open_orders(params);
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

TEST(RestApiTradeApi, CancelAllAlgoOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllAlgoOpenOrdersParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_all_algo_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelAllOpenOrders) {
    const std::string example =
        R"json({"code":200,"msg":"The operation of cancel all open order is done."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllOpenOrdersParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/fapi/v1/allOpenOrders");
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
        .symbol = "BTCUSDT",
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
    const CancelAllOpenOrdersParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_all_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelMultipleOrders) {
    const std::string example =
        R"json([{"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTC","origType":"TRAILING_STOP_MARKET","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1571110484038,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"code":-2011,"msg":"Unknown order sent."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMultipleOrdersParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_multiple_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/fapi/v1/batchOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelMultipleOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTC","origType":"TRAILING_STOP_MARKET","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1571110484038,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"code":-2011,"msg":"Unknown order sent."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMultipleOrdersParams params{
        .symbol = "BTCUSDT",
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
    const CancelMultipleOrdersParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_multiple_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ModifyMultipleOrders) {
    const std::string example =
        R"json([{"orderId":20072994037,"symbol":"BTCUSDT","pair":"BTCUSDT","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"updateTime":1629182711600,"code":-2022,"msg":"ReduceOnly Order is rejected."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyMultipleOrdersParams params{
        .batch_orders = std::vector<ModifyMultipleOrdersBatchOrdersParameterInner>{}};
    const auto res = api.modify_multiple_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/fapi/v1/batchOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("batchOrders="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyMultipleOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":20072994037,"symbol":"BTCUSDT","pair":"BTCUSDT","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"updateTime":1629182711600,"code":-2022,"msg":"ReduceOnly Order is rejected."}])json";
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
        R"json([{"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTC","type":"TRAILING_STOP_MARKET","origType":"TRAILING_STOP_MARKET","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1693207680000,"code":-2022,"msg":"ReduceOnly Order is rejected."}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceMultipleOrdersParams params{
        .batch_orders = std::vector<PlaceMultipleOrdersBatchOrdersParameterInner>{}};
    const auto res = api.place_multiple_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/batchOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("batchOrders="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceMultipleOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTC","type":"TRAILING_STOP_MARKET","origType":"TRAILING_STOP_MARKET","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1693207680000,"code":-2022,"msg":"ReduceOnly Order is rejected."}])json";
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
        R"json({"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTC","origType":"TRAILING_STOP_MARKET","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1571110484038,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.cancel_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/fapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"myOrder1","cumQty":"0","executedQty":"0","orderId":283194212,"origQty":"11","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"CANCELED","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTC","origType":"TRAILING_STOP_MARKET","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1571110484038,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelOrderParams params{
        .symbol = "BTCUSDT",
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
    const CancelOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ModifyOrder) {
    const std::string example =
        R"json({"orderId":20072994037,"symbol":"BTCUSDT","pair":"BTCUSDT","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"updateTime":1629182711600})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyOrderParams params{.symbol = "BTCUSDT",
                                   .side = ModifyOrderSideEnum::Buy,
                                   .quantity = common::Decimal("1.0"),
                                   .price = common::Decimal("30005")};
    const auto res = api.modify_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/fapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyOrderWithOptionalParams) {
    const std::string example =
        R"json({"orderId":20072994037,"symbol":"BTCUSDT","pair":"BTCUSDT","status":"NEW","clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","modifyId":1,"price":"30005","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"updateTime":1629182711600})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifyOrderParams params{
        .symbol = "BTCUSDT",
        .side = ModifyOrderSideEnum::Buy,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("30005"),
        .order_id = 20072994037,
        .orig_client_order_id = "LJ9R4QZDihCaS8UAOOLpgW",
        .price_match = ModifyOrderPriceMatchEnum::Opponent,
        .modify_id = 1,
        .reduce_only = ModifyOrderReduceOnlyEnum::True_,
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
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceMatch="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("modifyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ModifyOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ModifyOrderParams params{.symbol = "BTCUSDT",
                                   .side = ModifyOrderSideEnum::Buy,
                                   .quantity = common::Decimal("1.0"),
                                   .price = common::Decimal("30005")};
    EXPECT_THROW((void)api.modify_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewOrder) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTD","type":"LIMIT","origType":"LIMIT","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1693207680000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTCUSDT", .side = NewOrderSideEnum::Buy, .type = NewOrderTypeEnum::Limit};
    const auto res = api.new_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","executedQty":"0","orderId":22542179,"origQty":"10","price":"0","reduceOnly":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTD","type":"LIMIT","origType":"LIMIT","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1693207680000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTCUSDT",
        .side = NewOrderSideEnum::Buy,
        .type = NewOrderTypeEnum::Limit,
        .position_side = "BOTH",
        .time_in_force = NewOrderTimeInForceEnum::Gtc,
        .reduce_only = NewOrderReduceOnlyEnum::True_,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .new_client_order_id = "1",
        .new_order_resp_type = NewOrderNewOrderRespTypeEnum::Ack,
        .price_match = NewOrderPriceMatchEnum::Opponent,
        .self_trade_prevention_mode = NewOrderSelfTradePreventionModeEnum::ExpireTaker,
        .good_till_date = 1770736694138,
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
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
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

TEST(RestApiTradeApi, NewOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTCUSDT", .side = NewOrderSideEnum::Buy, .type = NewOrderTypeEnum::Limit};
    EXPECT_THROW((void)api.new_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryOrder) {
    const std::string example =
        R"json({"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1573346959,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryOrderWithOptionalParams) {
    const std::string example =
        R"json({"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1573346959,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOrderParams params{
        .symbol = "BTCUSDT",
        .order_id = 1917641,
        .orig_client_order_id = "abc",
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
    const QueryOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ChangeInitialLeverage) {
    const std::string example =
        R"json({"leverage":21,"maxNotionalValue":"1000000","symbol":"BTCUSDT"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeInitialLeverageParams params{.symbol = "BTCUSDT", .leverage = 1};
    const auto res = api.change_initial_leverage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/leverage");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("leverage="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ChangeInitialLeverageWithOptionalParams) {
    const std::string example =
        R"json({"leverage":21,"maxNotionalValue":"1000000","symbol":"BTCUSDT"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeInitialLeverageParams params{
        .symbol = "BTCUSDT",
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
    const ChangeInitialLeverageParams params{.symbol = "BTCUSDT", .leverage = 1};
    EXPECT_THROW((void)api.change_initial_leverage(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ChangeMarginType) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeMarginTypeParams params{.symbol = "BTCUSDT",
                                        .margin_type = ChangeMarginTypeMarginTypeEnum::Isolated};
    const auto res = api.change_margin_type(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/marginType");
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
        .symbol = "BTCUSDT",
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
    const ChangeMarginTypeParams params{.symbol = "BTCUSDT",
                                        .margin_type = ChangeMarginTypeMarginTypeEnum::Isolated};
    EXPECT_THROW((void)api.change_margin_type(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ChangeMultiAssetsMode) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeMultiAssetsModeParams params{.multi_assets_margin = "true"};
    const auto res = api.change_multi_assets_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/multiAssetsMargin");
    EXPECT_NE((rec.query() + "&" + rec.body).find("multiAssetsMargin="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ChangeMultiAssetsModeWithOptionalParams) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeMultiAssetsModeParams params{
        .multi_assets_margin = "true",
        .recv_window = 5000,
    };
    const auto res = api.change_multi_assets_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("multiAssetsMargin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ChangeMultiAssetsModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ChangeMultiAssetsModeParams params{.multi_assets_margin = "true"};
    EXPECT_THROW((void)api.change_multi_assets_mode(params), common::BadRequestError);
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
    EXPECT_EQ(rec.path(), "/fapi/v1/positionSide/dual");
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

TEST(RestApiTradeApi, CurrentAllAlgoOpenOrders) {
    const std::string example =
        R"json([{"algoId":2148627,"clientAlgoId":"MRumok0dkhrP4kCm12AHaB","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"NEW","actualOrderId":"","actualPrice":"0.00000","triggerPrice":"750.000","price":"750.000","icebergQuantity":"null","tpTriggerPrice":"0.000","tpPrice":"0.000","slTriggerPrice":"0.000","slPrice":"0.000","tpOrderType":"","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750514941540,"updateTime":1750514941540,"triggerTime":0,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentAllAlgoOpenOrdersParams params{};
    const auto res = api.current_all_algo_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/openAlgoOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CurrentAllAlgoOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"algoId":2148627,"clientAlgoId":"MRumok0dkhrP4kCm12AHaB","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"NEW","actualOrderId":"","actualPrice":"0.00000","triggerPrice":"750.000","price":"750.000","icebergQuantity":"null","tpTriggerPrice":"0.000","tpPrice":"0.000","slTriggerPrice":"0.000","slPrice":"0.000","tpOrderType":"","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750514941540,"updateTime":1750514941540,"triggerTime":0,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentAllAlgoOpenOrdersParams params{
        .algo_type = "CONDITIONAL",
        .symbol = "BTCUSDT",
        .algo_id = 2148627,
        .recv_window = 5000,
    };
    const auto res = api.current_all_algo_open_orders(params);
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

TEST(RestApiTradeApi, CurrentAllAlgoOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CurrentAllAlgoOpenOrdersParams params{};
    EXPECT_THROW((void)api.current_all_algo_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CurrentAllOpenOrders) {
    const std::string example =
        R"json([{"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentAllOpenOrdersParams params{};
    const auto res = api.current_all_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CurrentAllOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","positionSide":"SHORT","status":"NEW","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CurrentAllOpenOrdersParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.current_all_open_orders(params);
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

TEST(RestApiTradeApi, CurrentAllOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CurrentAllOpenOrdersParams params{};
    EXPECT_THROW((void)api.current_all_open_orders(params), common::BadRequestError);
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
    EXPECT_EQ(rec.path(), "/fapi/v1/stock/contract");
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

TEST(RestApiTradeApi, GetOrderModifyHistory) {
    const std::string example =
        R"json([{"amendmentId":5363,"symbol":"BTCUSDT","pair":"BTCUSDT","orderId":20072994037,"clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","time":1629184560899,"amendment":{"price":{"before":"30004","after":"30003.2"},"origQty":{"before":"1","after":"1"},"count":3,"modifyId":123}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderModifyHistoryParams params{.symbol = "BTCUSDT"};
    const auto res = api.get_order_modify_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/orderAmendment");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetOrderModifyHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"amendmentId":5363,"symbol":"BTCUSDT","pair":"BTCUSDT","orderId":20072994037,"clientOrderId":"LJ9R4QZDihCaS8UAOOLpgW","time":1629184560899,"amendment":{"price":{"before":"30004","after":"30003.2"},"origQty":{"before":"1","after":"1"},"count":3,"modifyId":123}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderModifyHistoryParams params{
        .symbol = "BTCUSDT",
        .order_id = 20072994037,
        .orig_client_order_id = "LJ9R4QZDihCaS8UAOOLpgW",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
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
    const GetOrderModifyHistoryParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.get_order_modify_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetPositionMarginChangeHistory) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","type":1,"deltaType":"USER_ADJUST","amount":"23.36332311","asset":"USDT","time":1578047897183,"positionSide":"BOTH"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPositionMarginChangeHistoryParams params{.symbol = "BTCUSDT"};
    const auto res = api.get_position_margin_change_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/positionMargin/history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetPositionMarginChangeHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","type":1,"deltaType":"USER_ADJUST","amount":"23.36332311","asset":"USDT","time":1578047897183,"positionSide":"BOTH"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPositionMarginChangeHistoryParams params{
        .symbol = "BTCUSDT",
        .type = "1",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
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
    const GetPositionMarginChangeHistoryParams params{.symbol = "BTCUSDT"};
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
    EXPECT_EQ(rec.path(), "/fapi/v1/positionMargin");
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
        .position_side = "BOTH",
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
    const std::string example = R"json([{"symbol":"ETHUSDT","adlQuantile":{}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionAdlQuantileEstimationParams params{};
    const auto res = api.position_adl_quantile_estimation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/adlQuantile");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PositionAdlQuantileEstimationWithOptionalParams) {
    const std::string example = R"json([{"symbol":"ETHUSDT","adlQuantile":{}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionAdlQuantileEstimationParams params{
        .symbol = "BTCUSDT",
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

TEST(RestApiTradeApi, PositionInformationV2) {
    const std::string example =
        R"json([{"entryPrice":"0.00000","breakEvenPrice":"0.0","marginType":"isolated","isAutoAddMargin":"false","isolatedMargin":"0.00000000","leverage":"10","liquidationPrice":"0","markPrice":"6679.50671178","maxNotionalValue":"20000000","positionAmt":"0.000","notional":"0","isolatedWallet":"0","symbol":"BTCUSDT","unRealizedProfit":"0.00000000","positionSide":"BOTH","updateTime":1625474304765}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionInformationV2Params params{};
    const auto res = api.position_information_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v2/positionRisk");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PositionInformationV2WithOptionalParams) {
    const std::string example =
        R"json([{"entryPrice":"0.00000","breakEvenPrice":"0.0","marginType":"isolated","isAutoAddMargin":"false","isolatedMargin":"0.00000000","leverage":"10","liquidationPrice":"0","markPrice":"6679.50671178","maxNotionalValue":"20000000","positionAmt":"0.000","notional":"0","isolatedWallet":"0","symbol":"BTCUSDT","unRealizedProfit":"0.00000000","positionSide":"BOTH","updateTime":1625474304765}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionInformationV2Params params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.position_information_v2(params);
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

TEST(RestApiTradeApi, PositionInformationV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PositionInformationV2Params params{};
    EXPECT_THROW((void)api.position_information_v2(params), common::BadRequestError);
}

TEST(RestApiTradeApi, PositionInformationV3) {
    const std::string example =
        R"json([{"symbol":"ADAUSDT","positionSide":"BOTH","positionAmt":"30","entryPrice":"0.385","breakEvenPrice":"0.385077","markPrice":"0.41047590","unRealizedProfit":"0.76427700","liquidationPrice":"0","isolatedMargin":"0","notional":"12.31427700","marginAsset":"USDT","isolatedWallet":"0","initialMargin":"0.61571385","maintMargin":"0.08004280","positionInitialMargin":"0.61571385","openOrderInitialMargin":"0","adl":2,"bidNotional":"0","askNotional":"0","updateTime":1720736417660}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionInformationV3Params params{};
    const auto res = api.position_information_v3(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v3/positionRisk");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PositionInformationV3WithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"ADAUSDT","positionSide":"BOTH","positionAmt":"30","entryPrice":"0.385","breakEvenPrice":"0.385077","markPrice":"0.41047590","unRealizedProfit":"0.76427700","liquidationPrice":"0","isolatedMargin":"0","notional":"12.31427700","marginAsset":"USDT","isolatedWallet":"0","initialMargin":"0.61571385","maintMargin":"0.08004280","positionInitialMargin":"0.61571385","openOrderInitialMargin":"0","adl":2,"bidNotional":"0","askNotional":"0","updateTime":1720736417660}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PositionInformationV3Params params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.position_information_v3(params);
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

TEST(RestApiTradeApi, PositionInformationV3BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PositionInformationV3Params params{};
    EXPECT_THROW((void)api.position_information_v3(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryAllAlgoOrders) {
    const std::string example =
        R"json([{"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"CANCELED","actualOrderId":"","actualPrice":"0.00000","triggerPrice":"750.000","price":"750.000","icebergQuantity":"null","tpTriggerPrice":"0.000","tpPrice":"0.000","slTriggerPrice":"0.000","slPrice":"0.000","tpOrderType":"","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750514545091,"triggerTime":0,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllAlgoOrdersParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_all_algo_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/allAlgoOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryAllAlgoOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"algoId":2146760,"clientAlgoId":"6B2I9XVcJpCjqPAJ4YoFX7","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BNBUSDT","side":"SELL","positionSide":"BOTH","timeInForce":"GTC","quantity":"0.01","algoStatus":"CANCELED","actualOrderId":"","actualPrice":"0.00000","triggerPrice":"750.000","price":"750.000","icebergQuantity":"null","tpTriggerPrice":"0.000","tpPrice":"0.000","slTriggerPrice":"0.000","slPrice":"0.000","tpOrderType":"","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1750485492076,"updateTime":1750514545091,"triggerTime":0,"goodTillDate":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryAllAlgoOrdersParams params{
        .symbol = "BTCUSDT",
        .algo_id = 2146760,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
        .recv_window = 5000,
    };
    const auto res = api.query_all_algo_orders(params);
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

TEST(RestApiTradeApi, QueryAllAlgoOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryAllAlgoOrdersParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_all_algo_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCurrentOpenOrder) {
    const std::string example =
        R"json({"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","status":"NEW","positionSide":"SHORT","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentOpenOrderParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_current_open_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/openOrder");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentOpenOrderWithOptionalParams) {
    const std::string example =
        R"json({"avgPrice":"0.00000","clientOrderId":"abc","cumQuote":"0","executedQty":"0","orderId":1917641,"origQty":"0.40","origType":"TRAILING_STOP_MARKET","price":"0","reduceOnly":false,"side":"BUY","status":"NEW","positionSide":"SHORT","stopPrice":"9300","closePosition":false,"symbol":"BTCUSDT","time":1579276756075,"timeInForce":"GTC","type":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1579276756075,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentOpenOrderParams params{
        .symbol = "BTCUSDT",
        .order_id = 1917641,
        .orig_client_order_id = "abc",
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
    const QueryCurrentOpenOrderParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_current_open_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, TestOrder) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","cumQuote":"0","executedQty":"0","orderId":22542179,"avgPrice":"0.00000","origQty":"10","price":"0","reduceOnly":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTD","type":"TRAILING_STOP_MARKET","origType":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1693207680000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TestOrderParams params{
        .symbol = "BTCUSDT", .side = TestOrderSideEnum::Buy, .type = TestOrderTypeEnum::Limit};
    const auto res = api.test_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/order/test");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, TestOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"testOrder","cumQty":"0","cumQuote":"0","executedQty":"0","orderId":22542179,"avgPrice":"0.00000","origQty":"10","price":"0","reduceOnly":false,"side":"SELL","positionSide":"SHORT","status":"NEW","stopPrice":"0","closePosition":false,"symbol":"BTCUSDT","timeInForce":"GTD","type":"TRAILING_STOP_MARKET","origType":"TRAILING_STOP_MARKET","activatePrice":"9020","priceRate":"0.3","updateTime":1566818724722,"workingType":"CONTRACT_PRICE","priceProtect":false,"priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":1693207680000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TestOrderParams params{
        .symbol = "BTCUSDT",
        .side = TestOrderSideEnum::Buy,
        .type = TestOrderTypeEnum::Limit,
        .position_side = TestOrderPositionSideEnum::Both,
        .reduce_only = TestOrderReduceOnlyEnum::True_,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .new_client_order_id = "1",
        .stop_price = common::Decimal("1.0"),
        .close_position = TestOrderClosePositionEnum::True_,
        .activation_price = common::Decimal("1.0"),
        .callback_rate = common::Decimal("1"),
        .time_in_force = TestOrderTimeInForceEnum::Gtc,
        .working_type = TestOrderWorkingTypeEnum::MarkPrice,
        .price_protect = TestOrderPriceProtectEnum::True_,
        .new_order_resp_type = TestOrderNewOrderRespTypeEnum::Ack,
        .price_match = TestOrderPriceMatchEnum::Opponent,
        .self_trade_prevention_mode = TestOrderSelfTradePreventionModeEnum::None_,
        .good_till_date = 1770736694138,
        .recv_window = 5000,
    };
    const auto res = api.test_order(params);
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
    EXPECT_NE((rec.query() + "&" + rec.body).find("goodTillDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, TestOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TestOrderParams params{
        .symbol = "BTCUSDT", .side = TestOrderSideEnum::Buy, .type = TestOrderTypeEnum::Limit};
    EXPECT_THROW((void)api.test_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, UsersForceOrders) {
    const std::string example =
        R"json([{"orderId":6071832819,"symbol":"BTCUSDT","pair":"BTCUSDT","status":"FILLED","clientOrderId":"autoclose-1596107620040000020","price":"10871.09","avgPrice":"10913.21000","origQty":"0.001","executedQty":"0.001","cumQuote":"10.91321","cumBase":"0.001","timeInForce":"IOC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"SELL","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","origType":"LIMIT","time":1596107620044,"updateTime":1596107620087}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UsersForceOrdersParams params{};
    const auto res = api.users_force_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/forceOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UsersForceOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":6071832819,"symbol":"BTCUSDT","pair":"BTCUSDT","status":"FILLED","clientOrderId":"autoclose-1596107620040000020","price":"10871.09","avgPrice":"10913.21000","origQty":"0.001","executedQty":"0.001","cumQuote":"10.91321","cumBase":"0.001","timeInForce":"IOC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"SELL","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","origType":"LIMIT","time":1596107620044,"updateTime":1596107620087}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UsersForceOrdersParams params{
        .symbol = "BTCUSDT",
        .auto_close_type = UsersForceOrdersAutoCloseTypeEnum::Liquidation,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
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
