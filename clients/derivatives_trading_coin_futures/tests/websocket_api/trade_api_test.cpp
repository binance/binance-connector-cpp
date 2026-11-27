//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string>

#include <boost/json/parse.hpp>
#include <boost/json/serialize.hpp>
#include <gtest/gtest.h>

#include <binance/common/errors.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/trade_api.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_coin_futures::websocket_api;
using binance::test::MockWsServer;

namespace {

// Answers every request with `example` (a spec response envelope, or an empty result), or with
// an error envelope when `status` is not 200, under the request's id.
MockWsServer::Handler reply(std::string example, int status = 200) {
    return
        [example = std::move(example), status](MockWsServer::Session& s, const std::string& text) {
            const auto req = boost::json::parse(text).as_object();
            boost::json::object res;
            if (status != 200) {
                res["status"] = status;
                res["error"] = {{"code", -1102}, {"msg", "Mandatory parameter was not sent."}};
            } else if (example.empty()) {
                res["status"] = 200;
                res["result"] = boost::json::object{};
            } else {
                res = boost::json::parse(example).as_object();
            }
            res["id"] = req.at("id");
            s.send(boost::json::serialize(res));
        };
}

TradeApi api_for(const MockWsServer& server) {
    common::WebsocketApiConfig cfg;
    cfg.url = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    cfg.proxy_from_env = false;
    auto client = std::make_shared<common::WebsocketApi>(std::move(cfg));
    client->connect();
    return TradeApi(std::move(client));
}

boost::json::object first_request(const MockWsServer& server) {
    return boost::json::parse(server.sessions().front().received.front()).as_object();
}

} // namespace

TEST(WebsocketApiTradeApi, CancelAlgoOrder) {
    MockWsServer server(reply(
        R"json({"id":"unique-cancel-request-id-5678","status":200,"result":{"algoId":2000000002162519,"clientAlgoId":"rDMG8WSde6LkyMNtk6s825","code":"200","msg":"success"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const CancelAlgoOrderParams params{};
    const auto res = api.cancel_algo_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "algoOrder.cancel");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, CancelAlgoOrderWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"unique-cancel-request-id-5678","status":200,"result":{"algoId":2000000002162519,"clientAlgoId":"rDMG8WSde6LkyMNtk6s825","code":"200","msg":"success"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const CancelAlgoOrderParams params{
        .id = "e9d6b4349871b40611412680b3445fac",
        .algo_id = 2000000002162519,
        .client_algo_id = "rDMG8WSde6LkyMNtk6s825",
        .recv_window = 5000,
    };
    const auto res = api.cancel_algo_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "algoOrder.cancel");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("algoId"));
    EXPECT_TRUE(sent.contains("clientAlgoId"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, CancelAlgoOrderErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const CancelAlgoOrderParams params{};
    EXPECT_THROW((void)api.cancel_algo_order(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, CancelOrder) {
    MockWsServer server(reply(
        R"json({"id":"a8627ea5-8b9f-452f-90ae-4136f2b442e2","status":200,"result":{"orderId":333245211,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"CANCELED","clientOrderId":"5SztZiGFAxgAqw4J9EN9fA","price":"51000","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","updateTime":1728416138285},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const CancelOrderParams params{.symbol = "BTCUSD_PERP"};
    const auto res = api.cancel_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.cancel");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, CancelOrderWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"a8627ea5-8b9f-452f-90ae-4136f2b442e2","status":200,"result":{"orderId":333245211,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"CANCELED","clientOrderId":"5SztZiGFAxgAqw4J9EN9fA","price":"51000","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","updateTime":1728416138285},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const CancelOrderParams params{
        .symbol = "BTCUSD_PERP",
        .id = "e9d6b4349871b40611412680b3445fac",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.cancel_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.cancel");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("orderId"));
    EXPECT_TRUE(sent.contains("origClientOrderId"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, CancelOrderErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const CancelOrderParams params{.symbol = "BTCUSD_PERP"};
    EXPECT_THROW((void)api.cancel_order(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, ModifyOrder) {
    MockWsServer server(reply(
        R"json({"id":"88601d02-bd0d-430d-8733-2708a569ebda","status":200,"result":{"orderId":333245211,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"5SztZiGFAxgAqw4J9EN9fA","modifyId":1,"price":"51000","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","updateTime":1728415765493},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const ModifyOrderParams params{.symbol = "BTCUSD_PERP",
                                   .side = ModifyOrderSideEnum::Buy,
                                   .quantity = common::Decimal("1.0"),
                                   .price = common::Decimal("1.0")};
    const auto res = api.modify_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.modify");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, ModifyOrderWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"88601d02-bd0d-430d-8733-2708a569ebda","status":200,"result":{"orderId":333245211,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"5SztZiGFAxgAqw4J9EN9fA","modifyId":1,"price":"51000","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","updateTime":1728415765493},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const ModifyOrderParams params{
        .symbol = "BTCUSD_PERP",
        .side = ModifyOrderSideEnum::Buy,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .id = "e9d6b4349871b40611412680b3445fac",
        .order_id = 1,
        .orig_client_order_id = "1",
        .price_match = ModifyOrderPriceMatchEnum::Opponent,
        .modify_id = 1,
        .recv_window = 5000,
    };
    const auto res = api.modify_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.modify");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("quantity"));
    EXPECT_TRUE(sent.contains("price"));

    EXPECT_TRUE(sent.contains("orderId"));
    EXPECT_TRUE(sent.contains("origClientOrderId"));
    EXPECT_TRUE(sent.contains("priceMatch"));
    EXPECT_TRUE(sent.contains("modifyId"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, ModifyOrderErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const ModifyOrderParams params{.symbol = "BTCUSD_PERP",
                                   .side = ModifyOrderSideEnum::Buy,
                                   .quantity = common::Decimal("1.0"),
                                   .price = common::Decimal("1.0")};
    EXPECT_THROW((void)api.modify_order(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, NewAlgoOrder) {
    MockWsServer server(reply(
        R"json({"id":"06c9dbd8-ccbf-4ecf-a29c-fe31495ac73f","status":200,"result":{"algoId":3000000000003505,"clientAlgoId":"0Xkl1p621E4EryvufmYre1","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BTCUSD_PERP","side":"SELL","positionSide":"SHORT","timeInForce":"GTC","quantity":"1.000","algoStatus":"NEW","triggerPrice":"120000.00","price":"160000.00","icebergQuantity":"null","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1762507264142,"updateTime":1762507264143,"triggerTime":0,"goodTillDate":0},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":1}]})json"));
    const auto api = api_for(server);
    const NewAlgoOrderParams params{.algo_type = NewAlgoOrderAlgoTypeEnum::Conditional,
                                    .symbol = "BTCUSD_PERP",
                                    .side = NewAlgoOrderSideEnum::Buy,
                                    .type = NewAlgoOrderTypeEnum::StopMarket};
    const auto res = api.new_algo_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "algoOrder.place");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, NewAlgoOrderWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"06c9dbd8-ccbf-4ecf-a29c-fe31495ac73f","status":200,"result":{"algoId":3000000000003505,"clientAlgoId":"0Xkl1p621E4EryvufmYre1","algoType":"CONDITIONAL","orderType":"TAKE_PROFIT","symbol":"BTCUSD_PERP","side":"SELL","positionSide":"SHORT","timeInForce":"GTC","quantity":"1.000","algoStatus":"NEW","triggerPrice":"120000.00","price":"160000.00","icebergQuantity":"null","selfTradePreventionMode":"EXPIRE_MAKER","workingType":"CONTRACT_PRICE","priceMatch":"NONE","closePosition":false,"priceProtect":false,"reduceOnly":false,"createTime":1762507264142,"updateTime":1762507264143,"triggerTime":0,"goodTillDate":0},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":1}]})json"));
    const auto api = api_for(server);
    const NewAlgoOrderParams params{
        .algo_type = NewAlgoOrderAlgoTypeEnum::Conditional,
        .symbol = "BTCUSD_PERP",
        .side = NewAlgoOrderSideEnum::Buy,
        .type = NewAlgoOrderTypeEnum::StopMarket,
        .id = "e9d6b4349871b40611412680b3445fac",
        .position_side = NewAlgoOrderPositionSideEnum::Both,
        .time_in_force = NewAlgoOrderTimeInForceEnum::Ioc,
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
        .recv_window = 5000,
    };
    const auto res = api.new_algo_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "algoOrder.place");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("algoType"));
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("type"));

    EXPECT_TRUE(sent.contains("positionSide"));
    EXPECT_TRUE(sent.contains("timeInForce"));
    EXPECT_TRUE(sent.contains("quantity"));
    EXPECT_TRUE(sent.contains("price"));
    EXPECT_TRUE(sent.contains("triggerPrice"));
    EXPECT_TRUE(sent.contains("workingType"));
    EXPECT_TRUE(sent.contains("priceMatch"));
    EXPECT_TRUE(sent.contains("closePosition"));
    EXPECT_TRUE(sent.contains("priceProtect"));
    EXPECT_TRUE(sent.contains("reduceOnly"));
    EXPECT_TRUE(sent.contains("activatePrice"));
    EXPECT_TRUE(sent.contains("callbackRate"));
    EXPECT_TRUE(sent.contains("clientAlgoId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, NewAlgoOrderErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const NewAlgoOrderParams params{.algo_type = NewAlgoOrderAlgoTypeEnum::Conditional,
                                    .symbol = "BTCUSD_PERP",
                                    .side = NewAlgoOrderSideEnum::Buy,
                                    .type = NewAlgoOrderTypeEnum::StopMarket};
    EXPECT_THROW((void)api.new_algo_order(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, NewOrder) {
    MockWsServer server(reply(
        R"json({"id":"60fa4366-f96e-42fe-a82b-f819952c6db4","status":200,"result":{"orderId":333245211,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"5SztZiGFAxgAqw4J9EN9fA","price":"50000","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","updateTime":1728413795125},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTCUSD_PERP", .side = NewOrderSideEnum::Buy, .type = NewOrderTypeEnum::Limit};
    const auto res = api.new_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.place");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, NewOrderWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"60fa4366-f96e-42fe-a82b-f819952c6db4","status":200,"result":{"orderId":333245211,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"5SztZiGFAxgAqw4J9EN9fA","price":"50000","origQty":"1","executedQty":"0","cumQty":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"BOTH","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","updateTime":1728413795125},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTCUSD_PERP",
        .side = NewOrderSideEnum::Buy,
        .type = NewOrderTypeEnum::Limit,
        .id = "e9d6b4349871b40611412680b3445fac",
        .position_side = NewOrderPositionSideEnum::Both,
        .time_in_force = NewOrderTimeInForceEnum::Gtc,
        .quantity = common::Decimal("1.0"),
        .reduce_only = NewOrderReduceOnlyEnum::True_,
        .price = common::Decimal("1.0"),
        .new_client_order_id = "1",
        .stop_price = common::Decimal("1.0"),
        .close_position = NewOrderClosePositionEnum::True_,
        .activation_price = common::Decimal("1.0"),
        .callback_rate = common::Decimal("5000.0"),
        .working_type = NewOrderWorkingTypeEnum::MarkPrice,
        .price_protect = NewOrderPriceProtectEnum::True_,
        .new_order_resp_type = NewOrderNewOrderRespTypeEnum::Ack,
        .price_match = NewOrderPriceMatchEnum::Opponent,
        .self_trade_prevention_mode = NewOrderSelfTradePreventionModeEnum::None_,
        .recv_window = 5000,
    };
    const auto res = api.new_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.place");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("type"));

    EXPECT_TRUE(sent.contains("positionSide"));
    EXPECT_TRUE(sent.contains("timeInForce"));
    EXPECT_TRUE(sent.contains("quantity"));
    EXPECT_TRUE(sent.contains("reduceOnly"));
    EXPECT_TRUE(sent.contains("price"));
    EXPECT_TRUE(sent.contains("newClientOrderId"));
    EXPECT_TRUE(sent.contains("stopPrice"));
    EXPECT_TRUE(sent.contains("closePosition"));
    EXPECT_TRUE(sent.contains("activationPrice"));
    EXPECT_TRUE(sent.contains("callbackRate"));
    EXPECT_TRUE(sent.contains("workingType"));
    EXPECT_TRUE(sent.contains("priceProtect"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("priceMatch"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, NewOrderErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTCUSD_PERP", .side = NewOrderSideEnum::Buy, .type = NewOrderTypeEnum::Limit};
    EXPECT_THROW((void)api.new_order(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, PositionInformation) {
    MockWsServer server(reply(
        R"json({"id":"233b8741-a96d-48e8-8ce1-160f43548aeb","status":200,"result":[{"symbol":"BTCUSD_PERP","positionAmt":"0","entryPrice":"0.00000000","markPrice":"62297.60417296","unRealizedProfit":"0.00000000","liquidationPrice":"0","leverage":"7","maxQty":"100","marginType":"cross","isolatedMargin":"0.00000000","isAutoAddMargin":"false","positionSide":"BOTH","notionalValue":"0","isolatedWallet":"0","updateTime":1726731195634,"breakEvenPrice":"0.00000000"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":10}]})json"));
    const auto api = api_for(server);
    const PositionInformationParams params{};
    const auto res = api.position_information(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.position");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, PositionInformationWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"233b8741-a96d-48e8-8ce1-160f43548aeb","status":200,"result":[{"symbol":"BTCUSD_PERP","positionAmt":"0","entryPrice":"0.00000000","markPrice":"62297.60417296","unRealizedProfit":"0.00000000","liquidationPrice":"0","leverage":"7","maxQty":"100","marginType":"cross","isolatedMargin":"0.00000000","isAutoAddMargin":"false","positionSide":"BOTH","notionalValue":"0","isolatedWallet":"0","updateTime":1726731195634,"breakEvenPrice":"0.00000000"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":10}]})json"));
    const auto api = api_for(server);
    const PositionInformationParams params{
        .id = "e9d6b4349871b40611412680b3445fac",
        .margin_asset = "USDT",
        .pair = "BTCUSD",
        .recv_window = 5000,
    };
    const auto res = api.position_information(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.position");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("marginAsset"));
    EXPECT_TRUE(sent.contains("pair"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, PositionInformationErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const PositionInformationParams params{};
    EXPECT_THROW((void)api.position_information(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, QueryOrder) {
    MockWsServer server(reply(
        R"json({"id":"0ce5d070-a5e5-4ff2-b57f-1556741a4204","status":200,"result":{"orderId":328999071,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"ArY8Ng1rln0s9x3fclmAHy","price":"58000","avgPrice":"0.00","origQty":"1","executedQty":"0","cumQty":"0","cumBase":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","selfTradePreventionMode":"EXPIRE_TAKER","time":1733740063619,"updateTime":1733740063619,"priceMatch":"NONE"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const QueryOrderParams params{.symbol = "BTCUSD_PERP"};
    const auto res = api.query_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.status");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, QueryOrderWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"0ce5d070-a5e5-4ff2-b57f-1556741a4204","status":200,"result":{"orderId":328999071,"symbol":"BTCUSD_PERP","pair":"BTCUSD","status":"NEW","clientOrderId":"ArY8Ng1rln0s9x3fclmAHy","price":"58000","avgPrice":"0.00","origQty":"1","executedQty":"0","cumQty":"0","cumBase":"0","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"LONG","stopPrice":"0","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","selfTradePreventionMode":"EXPIRE_TAKER","time":1733740063619,"updateTime":1733740063619,"priceMatch":"NONE"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":6}]})json"));
    const auto api = api_for(server);
    const QueryOrderParams params{
        .symbol = "BTCUSD_PERP",
        .id = "e9d6b4349871b40611412680b3445fac",
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_order(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.status");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("orderId"));
    EXPECT_TRUE(sent.contains("origClientOrderId"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, QueryOrderErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const QueryOrderParams params{.symbol = "BTCUSD_PERP"};
    EXPECT_THROW((void)api.query_order(params), common::WebsocketResponseError);
}
