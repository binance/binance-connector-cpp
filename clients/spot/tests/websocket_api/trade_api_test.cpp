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
#include <binance/spot/websocket_api/trade_api.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::spot::websocket_api;
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

TEST(WebsocketApiTradeApi, OpenOrdersCancelAll) {
    MockWsServer server(reply(
        R"json({"id":"778f938f-9041-4b88-9914-efbf64eeacc8","status":200,"result":[{"symbol":"BTCUSDT","origClientOrderId":"4d96324ff9d44481926157","orderId":12569099453,"orderListId":-1,"clientOrderId":"91fe37ce9e69c90d6358c0","transactTime":1684804350068,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00001000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.23416100","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","stopPrice":"0.00000000","trailingDelta":0,"trailingTime":-1,"icebergQty":"0.00000000","strategyId":37463720,"strategyType":1000000,"selfTradePreventionMode":"NONE"},{"orderListId":19431,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"iuVNVJYYrByz6C4yGOPPK0","transactionTime":1660803702431,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569099453,"clientOrderId":"bX5wROblo6YeDwa9iTLeyY"},{"symbol":"BTCUSDT","orderId":12569099454,"clientOrderId":"Tnu2IP0J5Y4mxw3IATBfmW"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"bX5wROblo6YeDwa9iTLeyY","orderId":12569099453,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23450.50000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"23430.00000000","selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","origClientOrderId":"Tnu2IP0J5Y4mxw3IATBfmW","orderId":12569099454,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23400.00000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","selfTradePreventionMode":"NONE"}]}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OpenOrdersCancelAllParams params{.symbol = "BNBUSDT"};
    const auto res = api.open_orders_cancel_all(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "openOrders.cancelAll");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OpenOrdersCancelAllWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"778f938f-9041-4b88-9914-efbf64eeacc8","status":200,"result":[{"symbol":"BTCUSDT","origClientOrderId":"4d96324ff9d44481926157","orderId":12569099453,"orderListId":-1,"clientOrderId":"91fe37ce9e69c90d6358c0","transactTime":1684804350068,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00001000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.23416100","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","stopPrice":"0.00000000","trailingDelta":0,"trailingTime":-1,"icebergQty":"0.00000000","strategyId":37463720,"strategyType":1000000,"selfTradePreventionMode":"NONE"},{"orderListId":19431,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"iuVNVJYYrByz6C4yGOPPK0","transactionTime":1660803702431,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569099453,"clientOrderId":"bX5wROblo6YeDwa9iTLeyY"},{"symbol":"BTCUSDT","orderId":12569099454,"clientOrderId":"Tnu2IP0J5Y4mxw3IATBfmW"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"bX5wROblo6YeDwa9iTLeyY","orderId":12569099453,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23450.50000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"23430.00000000","selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","origClientOrderId":"Tnu2IP0J5Y4mxw3IATBfmW","orderId":12569099454,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23400.00000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","selfTradePreventionMode":"NONE"}]}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OpenOrdersCancelAllParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.open_orders_cancel_all(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "openOrders.cancelAll");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OpenOrdersCancelAllErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OpenOrdersCancelAllParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.open_orders_cancel_all(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderAmendKeepPriority) {
    MockWsServer server(reply(
        R"json({"id":"56374a46-3061-486b-a311-89ee972eb648","status":200,"result":{"transactTime":1741923284382,"executionId":16,"amendedOrder":{"symbol":"BTCUSDT","orderId":12,"orderListId":-1,"origClientOrderId":"my_test_order1","clientOrderId":"4zR9HFcEq8gM1tWUqPEUHc","price":"5.00000000","qty":"5.00000000","executedQty":"0.00000000","preventedQty":"0.00000000","quoteOrderQty":"0.00000000","cumulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1741923284364,"selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"listStatus":{"orderListId":4,"contingencyType":"OTO","listOrderStatus":"EXECUTING","listClientOrderId":"8nOGLLawudj1QoOiwbroRH","symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":22,"clientOrderId":"g04EWsjaackzedjC9wRkWD"},{"symbol":"BTCUSDT","orderId":23,"clientOrderId":"xbxXh5SSwaHS7oUEOCI88B"}]}},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderAmendKeepPriorityParams params{.symbol = "BNBUSDT", .new_qty = common::Decimal("5")};
    const auto res = api.order_amend_keep_priority(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.amend.keepPriority");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderAmendKeepPriorityWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"56374a46-3061-486b-a311-89ee972eb648","status":200,"result":{"transactTime":1741923284382,"executionId":16,"amendedOrder":{"symbol":"BTCUSDT","orderId":12,"orderListId":-1,"origClientOrderId":"my_test_order1","clientOrderId":"4zR9HFcEq8gM1tWUqPEUHc","price":"5.00000000","qty":"5.00000000","executedQty":"0.00000000","preventedQty":"0.00000000","quoteOrderQty":"0.00000000","cumulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1741923284364,"selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"listStatus":{"orderListId":4,"contingencyType":"OTO","listOrderStatus":"EXECUTING","listClientOrderId":"8nOGLLawudj1QoOiwbroRH","symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":22,"clientOrderId":"g04EWsjaackzedjC9wRkWD"},{"symbol":"BTCUSDT","orderId":23,"clientOrderId":"xbxXh5SSwaHS7oUEOCI88B"}]}},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderAmendKeepPriorityParams params{
        .symbol = "BNBUSDT",
        .new_qty = common::Decimal("5"),
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .order_id = 1,
        .orig_client_order_id = "myOrder1",
        .new_client_order_id = "myOrder2",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_amend_keep_priority(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.amend.keepPriority");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("newQty"));

    EXPECT_TRUE(sent.contains("orderId"));
    EXPECT_TRUE(sent.contains("origClientOrderId"));
    EXPECT_TRUE(sent.contains("newClientOrderId"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderAmendKeepPriorityErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderAmendKeepPriorityParams params{.symbol = "BNBUSDT", .new_qty = common::Decimal("5")};
    EXPECT_THROW((void)api.order_amend_keep_priority(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderCancel) {
    MockWsServer server(reply(
        R"json({"id":"5633b6a2-90a9-4192-83e7-925c90b6a2fd","status":200,"result":{"symbol":"BTCUSDT","origClientOrderId":"4d96324ff9d44481926157","orderId":12569099453,"orderListId":-1,"clientOrderId":"91fe37ce9e69c90d6358c0","transactTime":1684804350068,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00001000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.23416100","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","stopPrice":"0.00000000","trailingDelta":0,"icebergQty":"0.00000000","strategyId":37463720,"strategyType":1000000,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY","contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"iuVNVJYYrByz6C4yGOPPK0","transactionTime":1660803702431,"orders":[{"symbol":"BTCUSDT","orderId":12569099453,"clientOrderId":"bX5wROblo6YeDwa9iTLeyY"},{"symbol":"BTCUSDT","orderId":12569099454,"clientOrderId":"Tnu2IP0J5Y4mxw3IATBfmW"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"bX5wROblo6YeDwa9iTLeyY","orderId":12569099453,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23450.50000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"23430.00000000","selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","origClientOrderId":"Tnu2IP0J5Y4mxw3IATBfmW","orderId":12569099454,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23400.00000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderCancelParams params{.symbol = "BNBUSDT"};
    const auto res = api.order_cancel(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.cancel");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderCancelWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"5633b6a2-90a9-4192-83e7-925c90b6a2fd","status":200,"result":{"symbol":"BTCUSDT","origClientOrderId":"4d96324ff9d44481926157","orderId":12569099453,"orderListId":-1,"clientOrderId":"91fe37ce9e69c90d6358c0","transactTime":1684804350068,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00001000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.23416100","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","stopPrice":"0.00000000","trailingDelta":0,"icebergQty":"0.00000000","strategyId":37463720,"strategyType":1000000,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY","contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"iuVNVJYYrByz6C4yGOPPK0","transactionTime":1660803702431,"orders":[{"symbol":"BTCUSDT","orderId":12569099453,"clientOrderId":"bX5wROblo6YeDwa9iTLeyY"},{"symbol":"BTCUSDT","orderId":12569099454,"clientOrderId":"Tnu2IP0J5Y4mxw3IATBfmW"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"bX5wROblo6YeDwa9iTLeyY","orderId":12569099453,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23450.50000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"23430.00000000","selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","origClientOrderId":"Tnu2IP0J5Y4mxw3IATBfmW","orderId":12569099454,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23400.00000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderCancelParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .order_id = 1,
        .orig_client_order_id = "myOrder1",
        .new_client_order_id = "cancelMyOrder1",
        .cancel_restrictions = OrderCancelCancelRestrictionsEnum::OnlyNew,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_cancel(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.cancel");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("orderId"));
    EXPECT_TRUE(sent.contains("origClientOrderId"));
    EXPECT_TRUE(sent.contains("newClientOrderId"));
    EXPECT_TRUE(sent.contains("cancelRestrictions"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderCancelErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderCancelParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.order_cancel(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderCancelReplace) {
    MockWsServer server(reply(
        R"json({"id":"99de1036-b5e2-4e0f-9b5c-13d751c93a1a","status":200,"result":{"cancelResult":"SUCCESS","newOrderResult":"SUCCESS","cancelResponse":{"symbol":"BTCUSDT","origClientOrderId":"4d96324ff9d44481926157","orderId":125690984230,"orderListId":-1,"clientOrderId":"91fe37ce9e69c90d6358c0","transactTime":1684804350068,"price":"23450.00000000","origQty":"0.00847000","executedQty":"0.00001000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.23450000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"newOrderResponse":{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"bX5wROblo6YeDwa9iTLeyY","transactTime":1660813156959,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}},"rateLimits":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":1},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":1},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderCancelReplaceParams params{
        .symbol = "BNBUSDT",
        .cancel_replace_mode = OrderCancelReplaceCancelReplaceModeEnum::StopOnFailure,
        .side = OrderCancelReplaceSideEnum::Buy,
        .type = OrderCancelReplaceTypeEnum::Market};
    const auto res = api.order_cancel_replace(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.cancelReplace");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderCancelReplaceWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"99de1036-b5e2-4e0f-9b5c-13d751c93a1a","status":200,"result":{"cancelResult":"SUCCESS","newOrderResult":"SUCCESS","cancelResponse":{"symbol":"BTCUSDT","origClientOrderId":"4d96324ff9d44481926157","orderId":125690984230,"orderListId":-1,"clientOrderId":"91fe37ce9e69c90d6358c0","transactTime":1684804350068,"price":"23450.00000000","origQty":"0.00847000","executedQty":"0.00001000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.23450000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"newOrderResponse":{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"bX5wROblo6YeDwa9iTLeyY","transactTime":1660813156959,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}},"rateLimits":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":1},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":1},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderCancelReplaceParams params{
        .symbol = "BNBUSDT",
        .cancel_replace_mode = OrderCancelReplaceCancelReplaceModeEnum::StopOnFailure,
        .side = OrderCancelReplaceSideEnum::Buy,
        .type = OrderCancelReplaceTypeEnum::Market,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .cancel_order_id = 1,
        .cancel_orig_client_order_id = "myOrder1",
        .cancel_new_client_order_id = "cancelMyOrder1",
        .time_in_force = OrderCancelReplaceTimeInForceEnum::Gtc,
        .price = common::Decimal("1"),
        .quantity = common::Decimal("1"),
        .quote_order_qty = common::Decimal("1"),
        .new_client_order_id = "myOrder2",
        .new_order_resp_type = OrderCancelReplaceNewOrderRespTypeEnum::Ack,
        .stop_price = common::Decimal("1"),
        .trailing_delta = common::Decimal("1"),
        .iceberg_qty = common::Decimal("1"),
        .strategy_id = 1,
        .strategy_type = 1,
        .self_trade_prevention_mode = OrderCancelReplaceSelfTradePreventionModeEnum::None_,
        .cancel_restrictions = OrderCancelReplaceCancelRestrictionsEnum::OnlyNew,
        .order_rate_limit_exceeded_mode =
            OrderCancelReplaceOrderRateLimitExceededModeEnum::DoNothing,
        .peg_price_type = OrderCancelReplacePegPriceTypeEnum::PrimaryPeg,
        .peg_offset_value = 1,
        .peg_offset_type = OrderCancelReplacePegOffsetTypeEnum::PriceLevel,
        .quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_cancel_replace(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.cancelReplace");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("cancelReplaceMode"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("type"));

    EXPECT_TRUE(sent.contains("cancelOrderId"));
    EXPECT_TRUE(sent.contains("cancelOrigClientOrderId"));
    EXPECT_TRUE(sent.contains("cancelNewClientOrderId"));
    EXPECT_TRUE(sent.contains("timeInForce"));
    EXPECT_TRUE(sent.contains("price"));
    EXPECT_TRUE(sent.contains("quantity"));
    EXPECT_TRUE(sent.contains("quoteOrderQty"));
    EXPECT_TRUE(sent.contains("newClientOrderId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("stopPrice"));
    EXPECT_TRUE(sent.contains("trailingDelta"));
    EXPECT_TRUE(sent.contains("icebergQty"));
    EXPECT_TRUE(sent.contains("strategyId"));
    EXPECT_TRUE(sent.contains("strategyType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("cancelRestrictions"));
    EXPECT_TRUE(sent.contains("orderRateLimitExceededMode"));
    EXPECT_TRUE(sent.contains("pegPriceType"));
    EXPECT_TRUE(sent.contains("pegOffsetValue"));
    EXPECT_TRUE(sent.contains("pegOffsetType"));
    EXPECT_TRUE(sent.contains("quoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderCancelReplaceErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderCancelReplaceParams params{
        .symbol = "BNBUSDT",
        .cancel_replace_mode = OrderCancelReplaceCancelReplaceModeEnum::StopOnFailure,
        .side = OrderCancelReplaceSideEnum::Buy,
        .type = OrderCancelReplaceTypeEnum::Market};
    EXPECT_THROW((void)api.order_cancel_replace(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderListCancel) {
    MockWsServer server(reply(
        R"json({"id":"c5899911-d3f4-47ae-8835-97da553d27d0","status":200,"result":{"orderListId":1274512,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"6023531d7edaad348f5aff","transactionTime":1660801720215,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569138901,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU"},{"symbol":"BTCUSDT","orderId":12569138902,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us"}],"orderReports":[{"symbol":"BTCUSDT","orderId":12569138901,"orderListId":1274512,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU","transactTime":1660801720215,"price":"23410.00000000","origQty":"0.00650000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"23405.00000000","selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":12569138902,"orderListId":1274512,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us","transactTime":1660801720215,"price":"23420.00000000","origQty":"0.00650000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderListCancelParams params{.symbol = "BNBUSDT"};
    const auto res = api.order_list_cancel(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.cancel");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListCancelWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"c5899911-d3f4-47ae-8835-97da553d27d0","status":200,"result":{"orderListId":1274512,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"6023531d7edaad348f5aff","transactionTime":1660801720215,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569138901,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU"},{"symbol":"BTCUSDT","orderId":12569138902,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us"}],"orderReports":[{"symbol":"BTCUSDT","orderId":12569138901,"orderListId":1274512,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU","transactTime":1660801720215,"price":"23410.00000000","origQty":"0.00650000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"23405.00000000","selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":12569138902,"orderListId":1274512,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us","transactTime":1660801720215,"price":"23420.00000000","origQty":"0.00650000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderListCancelParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .order_list_id = 1,
        .list_client_order_id = "C3wyj4WVEktd7u9aVBRXcN",
        .new_client_order_id = "cancelMyOrder1",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_cancel(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.cancel");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("orderListId"));
    EXPECT_TRUE(sent.contains("listClientOrderId"));
    EXPECT_TRUE(sent.contains("newClientOrderId"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListCancelErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderListCancelParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.order_list_cancel(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderListPlace) {
    MockWsServer server(reply(
        R"json({"id":"57833dc0-e3f2-43fb-ba20-46480973b0aa","status":200,"result":{"orderListId":1274512,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"08985fedd9ea2cf6b28996","transactionTime":1660801713793,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569138901,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU"},{"symbol":"BTCUSDT","orderId":12569138902,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us"}],"orderReports":[{"symbol":"BTCUSDT","orderId":12569138901,"orderListId":1274512,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU","transactTime":1660801713793,"price":"23410.00000000","origQty":"0.00650000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"23405.00000000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":12569138902,"orderListId":1274512,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us","transactTime":1660801713793,"price":"23420.00000000","origQty":"0.00650000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":1660801713793,"selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":2},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":2},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderListPlaceParams params{.symbol = "BNBUSDT",
                                      .side = OrderListPlaceSideEnum::Buy,
                                      .price = common::Decimal("1"),
                                      .quantity = common::Decimal("1")};
    const auto res = api.order_list_place(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"57833dc0-e3f2-43fb-ba20-46480973b0aa","status":200,"result":{"orderListId":1274512,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"08985fedd9ea2cf6b28996","transactionTime":1660801713793,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569138901,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU"},{"symbol":"BTCUSDT","orderId":12569138902,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us"}],"orderReports":[{"symbol":"BTCUSDT","orderId":12569138901,"orderListId":1274512,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU","transactTime":1660801713793,"price":"23410.00000000","origQty":"0.00650000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"23405.00000000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":12569138902,"orderListId":1274512,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us","transactTime":1660801713793,"price":"23420.00000000","origQty":"0.00650000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":1660801713793,"selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":2},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":2},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderListPlaceParams params{
        .symbol = "BNBUSDT",
        .side = OrderListPlaceSideEnum::Buy,
        .price = common::Decimal("1"),
        .quantity = common::Decimal("1"),
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .list_client_order_id = "08985fedd9ea2cf6b28996",
        .limit_client_order_id = "limitOrder1",
        .limit_iceberg_qty = common::Decimal("1"),
        .limit_strategy_id = 1,
        .limit_strategy_type = 1,
        .stop_price = common::Decimal("1"),
        .trailing_delta = 1,
        .stop_client_order_id = "stopOrder1",
        .stop_limit_price = common::Decimal("1"),
        .stop_limit_time_in_force = OrderListPlaceStopLimitTimeInForceEnum::Gtc,
        .stop_iceberg_qty = common::Decimal("1"),
        .stop_strategy_id = 1,
        .stop_strategy_type = 1,
        .new_order_resp_type = OrderListPlaceNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListPlaceSelfTradePreventionModeEnum::None_,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_place(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("price"));
    EXPECT_TRUE(sent.contains("quantity"));

    EXPECT_TRUE(sent.contains("listClientOrderId"));
    EXPECT_TRUE(sent.contains("limitClientOrderId"));
    EXPECT_TRUE(sent.contains("limitIcebergQty"));
    EXPECT_TRUE(sent.contains("limitStrategyId"));
    EXPECT_TRUE(sent.contains("limitStrategyType"));
    EXPECT_TRUE(sent.contains("stopPrice"));
    EXPECT_TRUE(sent.contains("trailingDelta"));
    EXPECT_TRUE(sent.contains("stopClientOrderId"));
    EXPECT_TRUE(sent.contains("stopLimitPrice"));
    EXPECT_TRUE(sent.contains("stopLimitTimeInForce"));
    EXPECT_TRUE(sent.contains("stopIcebergQty"));
    EXPECT_TRUE(sent.contains("stopStrategyId"));
    EXPECT_TRUE(sent.contains("stopStrategyType"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderListPlaceParams params{.symbol = "BNBUSDT",
                                      .side = OrderListPlaceSideEnum::Buy,
                                      .price = common::Decimal("1"),
                                      .quantity = common::Decimal("1")};
    EXPECT_THROW((void)api.order_list_place(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderListPlaceOco) {
    MockWsServer
        server(reply(R"json({"id":"56374a46-3261-486b-a211-99ed972eb648","status":200,"result":{"orderListId":2,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"cKPMnDCbcLQILtDYM4f4fX","transactionTime":1711062760648,"symbol":"LTCBNB","orders":[{"symbol":"LTCBNB","orderId":2,"clientOrderId":"0m6I4wfxvTUrOBSMUl0OPU"},{"symbol":"LTCBNB","orderId":3,"clientOrderId":"Z2IMlR79XNY5LU0tOxrWyW"}],"orderReports":[{"symbol":"LTCBNB","orderId":2,"orderListId":2,"clientOrderId":"0m6I4wfxvTUrOBSMUl0OPU","transactTime":1711062760648,"price":"1.50000000","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"1.50000001","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBNB","orderId":3,"orderListId":2,"clientOrderId":"Z2IMlR79XNY5LU0tOxrWyW","transactTime":1711062760648,"price":"1.49999999","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","workingTime":1711062760648,"selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":2},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":2},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderListPlaceOcoParams params{.symbol = "BNBUSDT",
                                         .side = OrderListPlaceOcoSideEnum::Buy,
                                         .quantity = common::Decimal("1"),
                                         .above_type =
                                             OrderListPlaceOcoAboveTypeEnum::StopLossLimit,
                                         .below_type = OrderListPlaceOcoBelowTypeEnum::StopLoss};
    const auto res = api.order_list_place_oco(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.oco");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOcoWithOptionalParams) {
    MockWsServer
        server(reply(R"json({"id":"56374a46-3261-486b-a211-99ed972eb648","status":200,"result":{"orderListId":2,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"cKPMnDCbcLQILtDYM4f4fX","transactionTime":1711062760648,"symbol":"LTCBNB","orders":[{"symbol":"LTCBNB","orderId":2,"clientOrderId":"0m6I4wfxvTUrOBSMUl0OPU"},{"symbol":"LTCBNB","orderId":3,"clientOrderId":"Z2IMlR79XNY5LU0tOxrWyW"}],"orderReports":[{"symbol":"LTCBNB","orderId":2,"orderListId":2,"clientOrderId":"0m6I4wfxvTUrOBSMUl0OPU","transactTime":1711062760648,"price":"1.50000000","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"1.50000001","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBNB","orderId":3,"orderListId":2,"clientOrderId":"Z2IMlR79XNY5LU0tOxrWyW","transactTime":1711062760648,"price":"1.49999999","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","workingTime":1711062760648,"selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":2},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":2},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderListPlaceOcoParams params{
        .symbol = "BNBUSDT",
        .side = OrderListPlaceOcoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .above_type = OrderListPlaceOcoAboveTypeEnum::StopLossLimit,
        .below_type = OrderListPlaceOcoBelowTypeEnum::StopLoss,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .list_client_order_id = "cKPMnDCbcLQILtDYM4f4fX",
        .above_client_order_id = "aboveOrder1",
        .above_iceberg_qty = common::Decimal("1"),
        .above_price = common::Decimal("1.5"),
        .above_stop_price = common::Decimal("1.50000001"),
        .above_trailing_delta = 1,
        .above_time_in_force = OrderListPlaceOcoAboveTimeInForceEnum::Gtc,
        .above_strategy_id = 1,
        .above_strategy_type = 1,
        .above_peg_price_type = OrderListPlaceOcoAbovePegPriceTypeEnum::PrimaryPeg,
        .above_peg_offset_type = OrderListPlaceOcoAbovePegOffsetTypeEnum::PriceLevel,
        .above_peg_offset_value = 1,
        .below_client_order_id = "belowOrder1",
        .below_iceberg_qty = common::Decimal("1"),
        .below_price = common::Decimal("1.49999999"),
        .below_stop_price = common::Decimal("1.50000001"),
        .below_trailing_delta = 1,
        .below_time_in_force = OrderListPlaceOcoBelowTimeInForceEnum::Gtc,
        .below_strategy_id = 1,
        .below_strategy_type = 1,
        .below_peg_price_type = OrderListPlaceOcoBelowPegPriceTypeEnum::PrimaryPeg,
        .below_peg_offset_type = OrderListPlaceOcoBelowPegOffsetTypeEnum::PriceLevel,
        .below_peg_offset_value = 1,
        .new_order_resp_type = OrderListPlaceOcoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListPlaceOcoSelfTradePreventionModeEnum::None_,
        .above_quote_notional_limit = common::Decimal("100"),
        .below_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_place_oco(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.oco");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("quantity"));
    EXPECT_TRUE(sent.contains("aboveType"));
    EXPECT_TRUE(sent.contains("belowType"));

    EXPECT_TRUE(sent.contains("listClientOrderId"));
    EXPECT_TRUE(sent.contains("aboveClientOrderId"));
    EXPECT_TRUE(sent.contains("aboveIcebergQty"));
    EXPECT_TRUE(sent.contains("abovePrice"));
    EXPECT_TRUE(sent.contains("aboveStopPrice"));
    EXPECT_TRUE(sent.contains("aboveTrailingDelta"));
    EXPECT_TRUE(sent.contains("aboveTimeInForce"));
    EXPECT_TRUE(sent.contains("aboveStrategyId"));
    EXPECT_TRUE(sent.contains("aboveStrategyType"));
    EXPECT_TRUE(sent.contains("abovePegPriceType"));
    EXPECT_TRUE(sent.contains("abovePegOffsetType"));
    EXPECT_TRUE(sent.contains("abovePegOffsetValue"));
    EXPECT_TRUE(sent.contains("belowClientOrderId"));
    EXPECT_TRUE(sent.contains("belowIcebergQty"));
    EXPECT_TRUE(sent.contains("belowPrice"));
    EXPECT_TRUE(sent.contains("belowStopPrice"));
    EXPECT_TRUE(sent.contains("belowTrailingDelta"));
    EXPECT_TRUE(sent.contains("belowTimeInForce"));
    EXPECT_TRUE(sent.contains("belowStrategyId"));
    EXPECT_TRUE(sent.contains("belowStrategyType"));
    EXPECT_TRUE(sent.contains("belowPegPriceType"));
    EXPECT_TRUE(sent.contains("belowPegOffsetType"));
    EXPECT_TRUE(sent.contains("belowPegOffsetValue"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("aboveQuoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("belowQuoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOcoErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderListPlaceOcoParams params{.symbol = "BNBUSDT",
                                         .side = OrderListPlaceOcoSideEnum::Buy,
                                         .quantity = common::Decimal("1"),
                                         .above_type =
                                             OrderListPlaceOcoAboveTypeEnum::StopLossLimit,
                                         .below_type = OrderListPlaceOcoBelowTypeEnum::StopLoss};
    EXPECT_THROW((void)api.order_list_place_oco(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderListPlaceOpo) {
    MockWsServer server(reply(
        R"json({"id":"eabb220d-1c53-4f8a-8bca-a1cd3594b3ce","status":200,"result":{"orderListId":2,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"OiOgqvRagBefpzdM5gjYX3","transactionTime":1762941318142,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":2,"clientOrderId":"pUzhKBbc0ZVdMScIRAqitH"},{"symbol":"BTCUSDT","orderId":3,"clientOrderId":"x7ISSjywZxFXOdzwsThNnd"}],"orderReports":[{"symbol":"BTCUSDT","orderId":2,"orderListId":2,"clientOrderId":"pUzhKBbc0ZVdMScIRAqitH","transactTime":1762941318142,"price":"101496.00000000","origQty":"0.00070000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1762941318142,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":3,"orderListId":2,"clientOrderId":"x7ISSjywZxFXOdzwsThNnd","transactTime":1762941318142,"price":"0.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"MARKET","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]}})json"));
    const auto api = api_for(server);
    const OrderListPlaceOpoParams params{.symbol = "BNBUSDT",
                                         .working_type = OrderListPlaceOpoWorkingTypeEnum::Limit,
                                         .working_side = OrderListPlaceOpoWorkingSideEnum::Buy,
                                         .working_price = common::Decimal("1"),
                                         .working_quantity = common::Decimal("1"),
                                         .pending_type = OrderListPlaceOpoPendingTypeEnum::Limit,
                                         .pending_side = OrderListPlaceOpoPendingSideEnum::Buy};
    const auto res = api.order_list_place_opo(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.opo");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOpoWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"eabb220d-1c53-4f8a-8bca-a1cd3594b3ce","status":200,"result":{"orderListId":2,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"OiOgqvRagBefpzdM5gjYX3","transactionTime":1762941318142,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":2,"clientOrderId":"pUzhKBbc0ZVdMScIRAqitH"},{"symbol":"BTCUSDT","orderId":3,"clientOrderId":"x7ISSjywZxFXOdzwsThNnd"}],"orderReports":[{"symbol":"BTCUSDT","orderId":2,"orderListId":2,"clientOrderId":"pUzhKBbc0ZVdMScIRAqitH","transactTime":1762941318142,"price":"101496.00000000","origQty":"0.00070000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1762941318142,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":3,"orderListId":2,"clientOrderId":"x7ISSjywZxFXOdzwsThNnd","transactTime":1762941318142,"price":"0.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"MARKET","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]}})json"));
    const auto api = api_for(server);
    const OrderListPlaceOpoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListPlaceOpoWorkingTypeEnum::Limit,
        .working_side = OrderListPlaceOpoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_type = OrderListPlaceOpoPendingTypeEnum::Limit,
        .pending_side = OrderListPlaceOpoPendingSideEnum::Buy,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .list_client_order_id = "OiOgqvRagBefpzdM5gjYX3",
        .new_order_resp_type = OrderListPlaceOpoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListPlaceOpoSelfTradePreventionModeEnum::None_,
        .working_client_order_id = "workingOrder1",
        .working_iceberg_qty = common::Decimal("1"),
        .working_time_in_force = OrderListPlaceOpoWorkingTimeInForceEnum::Gtc,
        .working_strategy_id = 1,
        .working_strategy_type = 1,
        .working_peg_price_type = OrderListPlaceOpoWorkingPegPriceTypeEnum::PrimaryPeg,
        .working_peg_offset_type = OrderListPlaceOpoWorkingPegOffsetTypeEnum::PriceLevel,
        .working_peg_offset_value = 1,
        .pending_client_order_id = "pendingOrder1",
        .pending_price = common::Decimal("1"),
        .pending_stop_price = common::Decimal("1"),
        .pending_trailing_delta = common::Decimal("1"),
        .pending_iceberg_qty = common::Decimal("1"),
        .pending_time_in_force = OrderListPlaceOpoPendingTimeInForceEnum::Gtc,
        .pending_strategy_id = 1,
        .pending_strategy_type = 1,
        .pending_peg_price_type = OrderListPlaceOpoPendingPegPriceTypeEnum::PrimaryPeg,
        .pending_peg_offset_type = OrderListPlaceOpoPendingPegOffsetTypeEnum::PriceLevel,
        .pending_peg_offset_value = 1,
        .working_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_place_opo(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.opo");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("workingType"));
    EXPECT_TRUE(sent.contains("workingSide"));
    EXPECT_TRUE(sent.contains("workingPrice"));
    EXPECT_TRUE(sent.contains("workingQuantity"));
    EXPECT_TRUE(sent.contains("pendingType"));
    EXPECT_TRUE(sent.contains("pendingSide"));

    EXPECT_TRUE(sent.contains("listClientOrderId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("workingClientOrderId"));
    EXPECT_TRUE(sent.contains("workingIcebergQty"));
    EXPECT_TRUE(sent.contains("workingTimeInForce"));
    EXPECT_TRUE(sent.contains("workingStrategyId"));
    EXPECT_TRUE(sent.contains("workingStrategyType"));
    EXPECT_TRUE(sent.contains("workingPegPriceType"));
    EXPECT_TRUE(sent.contains("workingPegOffsetType"));
    EXPECT_TRUE(sent.contains("workingPegOffsetValue"));
    EXPECT_TRUE(sent.contains("pendingClientOrderId"));
    EXPECT_TRUE(sent.contains("pendingPrice"));
    EXPECT_TRUE(sent.contains("pendingStopPrice"));
    EXPECT_TRUE(sent.contains("pendingTrailingDelta"));
    EXPECT_TRUE(sent.contains("pendingIcebergQty"));
    EXPECT_TRUE(sent.contains("pendingTimeInForce"));
    EXPECT_TRUE(sent.contains("pendingStrategyId"));
    EXPECT_TRUE(sent.contains("pendingStrategyType"));
    EXPECT_TRUE(sent.contains("pendingPegPriceType"));
    EXPECT_TRUE(sent.contains("pendingPegOffsetType"));
    EXPECT_TRUE(sent.contains("pendingPegOffsetValue"));
    EXPECT_TRUE(sent.contains("workingQuoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOpoErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderListPlaceOpoParams params{.symbol = "BNBUSDT",
                                         .working_type = OrderListPlaceOpoWorkingTypeEnum::Limit,
                                         .working_side = OrderListPlaceOpoWorkingSideEnum::Buy,
                                         .working_price = common::Decimal("1"),
                                         .working_quantity = common::Decimal("1"),
                                         .pending_type = OrderListPlaceOpoPendingTypeEnum::Limit,
                                         .pending_side = OrderListPlaceOpoPendingSideEnum::Buy};
    EXPECT_THROW((void)api.order_list_place_opo(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderListPlaceOpoco) {
    MockWsServer server(reply(
        R"json({"id":"606063bf-43ea-40a6-a463-5c66fbd53b56","status":200,"result":{"orderListId":1,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"TVbG6ymkYMXTj7tczbOsBf","transactionTime":1763000139104,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":6,"clientOrderId":"3czuJSeyjPwV9Xo28j1Dv3"},{"symbol":"BTCUSDT","orderId":7,"clientOrderId":"kyIKnMLKQclE5FmyYgaMSo"},{"symbol":"BTCUSDT","orderId":8,"clientOrderId":"i76cGJWN9J1FpADS56TtQZ"}],"orderReports":[{"symbol":"BTCUSDT","orderId":6,"orderListId":1,"clientOrderId":"3czuJSeyjPwV9Xo28j1Dv3","transactTime":1763000139104,"price":"102496.00000000","origQty":"0.00170000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1763000139104,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":7,"orderListId":1,"clientOrderId":"kyIKnMLKQclE5FmyYgaMSo","transactTime":1763000139104,"price":"101613.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"IOC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"10100.00000000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":8,"orderListId":1,"clientOrderId":"i76cGJWN9J1FpADS56TtQZ","transactTime":1763000139104,"price":"104261.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]}})json"));
    const auto api = api_for(server);
    const OrderListPlaceOpocoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListPlaceOpocoWorkingTypeEnum::Limit,
        .working_side = OrderListPlaceOpocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_side = OrderListPlaceOpocoPendingSideEnum::Buy,
        .pending_above_type = OrderListPlaceOpocoPendingAboveTypeEnum::StopLossLimit};
    const auto res = api.order_list_place_opoco(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.opoco");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOpocoWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"606063bf-43ea-40a6-a463-5c66fbd53b56","status":200,"result":{"orderListId":1,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"TVbG6ymkYMXTj7tczbOsBf","transactionTime":1763000139104,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":6,"clientOrderId":"3czuJSeyjPwV9Xo28j1Dv3"},{"symbol":"BTCUSDT","orderId":7,"clientOrderId":"kyIKnMLKQclE5FmyYgaMSo"},{"symbol":"BTCUSDT","orderId":8,"clientOrderId":"i76cGJWN9J1FpADS56TtQZ"}],"orderReports":[{"symbol":"BTCUSDT","orderId":6,"orderListId":1,"clientOrderId":"3czuJSeyjPwV9Xo28j1Dv3","transactTime":1763000139104,"price":"102496.00000000","origQty":"0.00170000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1763000139104,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":7,"orderListId":1,"clientOrderId":"kyIKnMLKQclE5FmyYgaMSo","transactTime":1763000139104,"price":"101613.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"IOC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"10100.00000000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":8,"orderListId":1,"clientOrderId":"i76cGJWN9J1FpADS56TtQZ","transactTime":1763000139104,"price":"104261.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]}})json"));
    const auto api = api_for(server);
    const OrderListPlaceOpocoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListPlaceOpocoWorkingTypeEnum::Limit,
        .working_side = OrderListPlaceOpocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_side = OrderListPlaceOpocoPendingSideEnum::Buy,
        .pending_above_type = OrderListPlaceOpocoPendingAboveTypeEnum::StopLossLimit,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .list_client_order_id = "TVbG6ymkYMXTj7tczbOsBf",
        .new_order_resp_type = OrderListPlaceOpocoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListPlaceOpocoSelfTradePreventionModeEnum::None_,
        .working_client_order_id = "workingOrder1",
        .working_iceberg_qty = common::Decimal("1"),
        .working_time_in_force = OrderListPlaceOpocoWorkingTimeInForceEnum::Gtc,
        .working_strategy_id = 1,
        .working_strategy_type = 1,
        .working_peg_price_type = OrderListPlaceOpocoWorkingPegPriceTypeEnum::PrimaryPeg,
        .working_peg_offset_type = OrderListPlaceOpocoWorkingPegOffsetTypeEnum::PriceLevel,
        .working_peg_offset_value = 1,
        .pending_above_client_order_id = "pendingAboveOrder1",
        .pending_above_price = common::Decimal("1"),
        .pending_above_stop_price = common::Decimal("1"),
        .pending_above_trailing_delta = common::Decimal("1"),
        .pending_above_iceberg_qty = common::Decimal("1"),
        .pending_above_time_in_force = OrderListPlaceOpocoPendingAboveTimeInForceEnum::Gtc,
        .pending_above_strategy_id = 1,
        .pending_above_strategy_type = 1,
        .pending_above_peg_price_type = OrderListPlaceOpocoPendingAbovePegPriceTypeEnum::PrimaryPeg,
        .pending_above_peg_offset_type =
            OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum::PriceLevel,
        .pending_above_peg_offset_value = 1,
        .pending_below_type = OrderListPlaceOpocoPendingBelowTypeEnum::StopLoss,
        .pending_below_client_order_id = "pendingBelowOrder1",
        .pending_below_price = common::Decimal("1"),
        .pending_below_stop_price = common::Decimal("1"),
        .pending_below_trailing_delta = common::Decimal("1"),
        .pending_below_iceberg_qty = common::Decimal("1"),
        .pending_below_time_in_force = OrderListPlaceOpocoPendingBelowTimeInForceEnum::Gtc,
        .pending_below_strategy_id = 1,
        .pending_below_strategy_type = 1,
        .pending_below_peg_price_type = OrderListPlaceOpocoPendingBelowPegPriceTypeEnum::PrimaryPeg,
        .pending_below_peg_offset_type =
            OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum::PriceLevel,
        .pending_below_peg_offset_value = 1,
        .working_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_place_opoco(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.opoco");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("workingType"));
    EXPECT_TRUE(sent.contains("workingSide"));
    EXPECT_TRUE(sent.contains("workingPrice"));
    EXPECT_TRUE(sent.contains("workingQuantity"));
    EXPECT_TRUE(sent.contains("pendingSide"));
    EXPECT_TRUE(sent.contains("pendingAboveType"));

    EXPECT_TRUE(sent.contains("listClientOrderId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("workingClientOrderId"));
    EXPECT_TRUE(sent.contains("workingIcebergQty"));
    EXPECT_TRUE(sent.contains("workingTimeInForce"));
    EXPECT_TRUE(sent.contains("workingStrategyId"));
    EXPECT_TRUE(sent.contains("workingStrategyType"));
    EXPECT_TRUE(sent.contains("workingPegPriceType"));
    EXPECT_TRUE(sent.contains("workingPegOffsetType"));
    EXPECT_TRUE(sent.contains("workingPegOffsetValue"));
    EXPECT_TRUE(sent.contains("pendingAboveClientOrderId"));
    EXPECT_TRUE(sent.contains("pendingAbovePrice"));
    EXPECT_TRUE(sent.contains("pendingAboveStopPrice"));
    EXPECT_TRUE(sent.contains("pendingAboveTrailingDelta"));
    EXPECT_TRUE(sent.contains("pendingAboveIcebergQty"));
    EXPECT_TRUE(sent.contains("pendingAboveTimeInForce"));
    EXPECT_TRUE(sent.contains("pendingAboveStrategyId"));
    EXPECT_TRUE(sent.contains("pendingAboveStrategyType"));
    EXPECT_TRUE(sent.contains("pendingAbovePegPriceType"));
    EXPECT_TRUE(sent.contains("pendingAbovePegOffsetType"));
    EXPECT_TRUE(sent.contains("pendingAbovePegOffsetValue"));
    EXPECT_TRUE(sent.contains("pendingBelowType"));
    EXPECT_TRUE(sent.contains("pendingBelowClientOrderId"));
    EXPECT_TRUE(sent.contains("pendingBelowPrice"));
    EXPECT_TRUE(sent.contains("pendingBelowStopPrice"));
    EXPECT_TRUE(sent.contains("pendingBelowTrailingDelta"));
    EXPECT_TRUE(sent.contains("pendingBelowIcebergQty"));
    EXPECT_TRUE(sent.contains("pendingBelowTimeInForce"));
    EXPECT_TRUE(sent.contains("pendingBelowStrategyId"));
    EXPECT_TRUE(sent.contains("pendingBelowStrategyType"));
    EXPECT_TRUE(sent.contains("pendingBelowPegPriceType"));
    EXPECT_TRUE(sent.contains("pendingBelowPegOffsetType"));
    EXPECT_TRUE(sent.contains("pendingBelowPegOffsetValue"));
    EXPECT_TRUE(sent.contains("workingQuoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOpocoErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderListPlaceOpocoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListPlaceOpocoWorkingTypeEnum::Limit,
        .working_side = OrderListPlaceOpocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_side = OrderListPlaceOpocoPendingSideEnum::Buy,
        .pending_above_type = OrderListPlaceOpocoPendingAboveTypeEnum::StopLossLimit};
    EXPECT_THROW((void)api.order_list_place_opoco(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderListPlaceOto) {
    MockWsServer server(reply(
        R"json({"id":"1712544395950","status":200,"result":{"orderListId":626,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"KA4EBjGnzvSwSCQsDdTrlf","transactionTime":1712544395981,"symbol":"LTCBNB","orders":[{"symbol":"LTCBNB","orderId":13,"clientOrderId":"YiAUtM9yJjl1a2jXHSp9Ny"},{"symbol":"LTCBNB","orderId":14,"clientOrderId":"9MxJSE1TYkmyx5lbGLve7R"}],"orderReports":[{"symbol":"LTCBNB","orderId":13,"orderListId":626,"clientOrderId":"YiAUtM9yJjl1a2jXHSp9Ny","transactTime":1712544395981,"price":"1.000000","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1712544395981,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBNB","orderId":14,"orderListId":626,"clientOrderId":"9MxJSE1TYkmyx5lbGLve7R","transactTime":1712544395981,"price":"0.000000","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"PENDING_NEW","timeInForce":"GTC","type":"MARKET","side":"BUY","workingTime":-1,"selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"MINUTE","intervalNum":1,"limit":10000000,"count":10},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":1000,"count":38}]})json"));
    const auto api = api_for(server);
    const OrderListPlaceOtoParams params{.symbol = "BNBUSDT",
                                         .working_type = OrderListPlaceOtoWorkingTypeEnum::Limit,
                                         .working_side = OrderListPlaceOtoWorkingSideEnum::Buy,
                                         .working_price = common::Decimal("1"),
                                         .working_quantity = common::Decimal("1"),
                                         .pending_type = OrderListPlaceOtoPendingTypeEnum::Limit,
                                         .pending_side = OrderListPlaceOtoPendingSideEnum::Buy,
                                         .pending_quantity = common::Decimal("1")};
    const auto res = api.order_list_place_oto(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.oto");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOtoWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"1712544395950","status":200,"result":{"orderListId":626,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"KA4EBjGnzvSwSCQsDdTrlf","transactionTime":1712544395981,"symbol":"LTCBNB","orders":[{"symbol":"LTCBNB","orderId":13,"clientOrderId":"YiAUtM9yJjl1a2jXHSp9Ny"},{"symbol":"LTCBNB","orderId":14,"clientOrderId":"9MxJSE1TYkmyx5lbGLve7R"}],"orderReports":[{"symbol":"LTCBNB","orderId":13,"orderListId":626,"clientOrderId":"YiAUtM9yJjl1a2jXHSp9Ny","transactTime":1712544395981,"price":"1.000000","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1712544395981,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBNB","orderId":14,"orderListId":626,"clientOrderId":"9MxJSE1TYkmyx5lbGLve7R","transactTime":1712544395981,"price":"0.000000","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"PENDING_NEW","timeInForce":"GTC","type":"MARKET","side":"BUY","workingTime":-1,"selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"MINUTE","intervalNum":1,"limit":10000000,"count":10},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":1000,"count":38}]})json"));
    const auto api = api_for(server);
    const OrderListPlaceOtoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListPlaceOtoWorkingTypeEnum::Limit,
        .working_side = OrderListPlaceOtoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_type = OrderListPlaceOtoPendingTypeEnum::Limit,
        .pending_side = OrderListPlaceOtoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1"),
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .list_client_order_id = "KA4EBjGnzvSwSCQsDdTrlf",
        .new_order_resp_type = OrderListPlaceOtoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListPlaceOtoSelfTradePreventionModeEnum::None_,
        .working_client_order_id = "workingOrder1",
        .working_iceberg_qty = common::Decimal("1"),
        .working_time_in_force = OrderListPlaceOtoWorkingTimeInForceEnum::Gtc,
        .working_strategy_id = 1,
        .working_strategy_type = 1,
        .working_peg_price_type = OrderListPlaceOtoWorkingPegPriceTypeEnum::PrimaryPeg,
        .working_peg_offset_type = OrderListPlaceOtoWorkingPegOffsetTypeEnum::PriceLevel,
        .working_peg_offset_value = 1,
        .pending_client_order_id = "pendingOrder1",
        .pending_price = common::Decimal("1"),
        .pending_stop_price = common::Decimal("1"),
        .pending_trailing_delta = common::Decimal("1"),
        .pending_iceberg_qty = common::Decimal("1"),
        .pending_time_in_force = OrderListPlaceOtoPendingTimeInForceEnum::Gtc,
        .pending_strategy_id = 1,
        .pending_strategy_type = 1,
        .pending_peg_offset_type = OrderListPlaceOtoPendingPegOffsetTypeEnum::PriceLevel,
        .pending_peg_price_type = OrderListPlaceOtoPendingPegPriceTypeEnum::PrimaryPeg,
        .pending_peg_offset_value = 1,
        .working_quote_notional_limit = common::Decimal("100"),
        .pending_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_place_oto(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.oto");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("workingType"));
    EXPECT_TRUE(sent.contains("workingSide"));
    EXPECT_TRUE(sent.contains("workingPrice"));
    EXPECT_TRUE(sent.contains("workingQuantity"));
    EXPECT_TRUE(sent.contains("pendingType"));
    EXPECT_TRUE(sent.contains("pendingSide"));
    EXPECT_TRUE(sent.contains("pendingQuantity"));

    EXPECT_TRUE(sent.contains("listClientOrderId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("workingClientOrderId"));
    EXPECT_TRUE(sent.contains("workingIcebergQty"));
    EXPECT_TRUE(sent.contains("workingTimeInForce"));
    EXPECT_TRUE(sent.contains("workingStrategyId"));
    EXPECT_TRUE(sent.contains("workingStrategyType"));
    EXPECT_TRUE(sent.contains("workingPegPriceType"));
    EXPECT_TRUE(sent.contains("workingPegOffsetType"));
    EXPECT_TRUE(sent.contains("workingPegOffsetValue"));
    EXPECT_TRUE(sent.contains("pendingClientOrderId"));
    EXPECT_TRUE(sent.contains("pendingPrice"));
    EXPECT_TRUE(sent.contains("pendingStopPrice"));
    EXPECT_TRUE(sent.contains("pendingTrailingDelta"));
    EXPECT_TRUE(sent.contains("pendingIcebergQty"));
    EXPECT_TRUE(sent.contains("pendingTimeInForce"));
    EXPECT_TRUE(sent.contains("pendingStrategyId"));
    EXPECT_TRUE(sent.contains("pendingStrategyType"));
    EXPECT_TRUE(sent.contains("pendingPegOffsetType"));
    EXPECT_TRUE(sent.contains("pendingPegPriceType"));
    EXPECT_TRUE(sent.contains("pendingPegOffsetValue"));
    EXPECT_TRUE(sent.contains("workingQuoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("pendingQuoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOtoErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderListPlaceOtoParams params{.symbol = "BNBUSDT",
                                         .working_type = OrderListPlaceOtoWorkingTypeEnum::Limit,
                                         .working_side = OrderListPlaceOtoWorkingSideEnum::Buy,
                                         .working_price = common::Decimal("1"),
                                         .working_quantity = common::Decimal("1"),
                                         .pending_type = OrderListPlaceOtoPendingTypeEnum::Limit,
                                         .pending_side = OrderListPlaceOtoPendingSideEnum::Buy,
                                         .pending_quantity = common::Decimal("1")};
    EXPECT_THROW((void)api.order_list_place_oto(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderListPlaceOtoco) {
    MockWsServer server(reply(
        R"json({"id":"1712544408508","status":200,"result":{"orderListId":629,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"GaeJHjZPasPItFj4x7Mqm6","transactionTime":1712544408537,"symbol":"LTCBNB","orders":[{"symbol":"LTCBNB","orderId":23,"clientOrderId":"OVQOpKwfmPCfaBTD0n7e7H"},{"symbol":"LTCBNB","orderId":24,"clientOrderId":"YcCPKCDMQIjNvLtNswt82X"},{"symbol":"LTCBNB","orderId":25,"clientOrderId":"ilpIoShcFZ1ZGgSASKxMPt"}],"orderReports":[{"symbol":"LTCBNB","orderId":23,"orderListId":629,"clientOrderId":"OVQOpKwfmPCfaBTD0n7e7H","transactTime":1712544408537,"price":"1.500000","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1712544408537,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBNB","orderId":24,"orderListId":629,"clientOrderId":"YcCPKCDMQIjNvLtNswt82X","transactTime":1712544408537,"price":"0.000000","origQty":"5.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"PENDING_NEW","timeInForce":"GTC","type":"STOP_LOSS","side":"SELL","stopPrice":"0.500000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBNB","orderId":25,"orderListId":629,"clientOrderId":"ilpIoShcFZ1ZGgSASKxMPt","transactTime":1712544408537,"price":"5.000000","origQty":"5.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"PENDING_NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"MINUTE","intervalNum":1,"limit":10000000,"count":18},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":1000,"count":65}]})json"));
    const auto api = api_for(server);
    const OrderListPlaceOtocoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListPlaceOtocoWorkingTypeEnum::Limit,
        .working_side = OrderListPlaceOtocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_side = OrderListPlaceOtocoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1"),
        .pending_above_type = OrderListPlaceOtocoPendingAboveTypeEnum::StopLossLimit};
    const auto res = api.order_list_place_otoco(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.otoco");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOtocoWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"1712544408508","status":200,"result":{"orderListId":629,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"GaeJHjZPasPItFj4x7Mqm6","transactionTime":1712544408537,"symbol":"LTCBNB","orders":[{"symbol":"LTCBNB","orderId":23,"clientOrderId":"OVQOpKwfmPCfaBTD0n7e7H"},{"symbol":"LTCBNB","orderId":24,"clientOrderId":"YcCPKCDMQIjNvLtNswt82X"},{"symbol":"LTCBNB","orderId":25,"clientOrderId":"ilpIoShcFZ1ZGgSASKxMPt"}],"orderReports":[{"symbol":"LTCBNB","orderId":23,"orderListId":629,"clientOrderId":"OVQOpKwfmPCfaBTD0n7e7H","transactTime":1712544408537,"price":"1.500000","origQty":"1.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1712544408537,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBNB","orderId":24,"orderListId":629,"clientOrderId":"YcCPKCDMQIjNvLtNswt82X","transactTime":1712544408537,"price":"0.000000","origQty":"5.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"PENDING_NEW","timeInForce":"GTC","type":"STOP_LOSS","side":"SELL","stopPrice":"0.500000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBNB","orderId":25,"orderListId":629,"clientOrderId":"ilpIoShcFZ1ZGgSASKxMPt","transactTime":1712544408537,"price":"5.000000","origQty":"5.000000","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"PENDING_NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"MINUTE","intervalNum":1,"limit":10000000,"count":18},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":1000,"count":65}]})json"));
    const auto api = api_for(server);
    const OrderListPlaceOtocoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListPlaceOtocoWorkingTypeEnum::Limit,
        .working_side = OrderListPlaceOtocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_side = OrderListPlaceOtocoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1"),
        .pending_above_type = OrderListPlaceOtocoPendingAboveTypeEnum::StopLossLimit,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .list_client_order_id = "GaeJHjZPasPItFj4x7Mqm6",
        .new_order_resp_type = OrderListPlaceOtocoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListPlaceOtocoSelfTradePreventionModeEnum::None_,
        .working_client_order_id = "workingOrder1",
        .working_iceberg_qty = common::Decimal("1"),
        .working_time_in_force = OrderListPlaceOtocoWorkingTimeInForceEnum::Gtc,
        .working_strategy_id = 1,
        .working_strategy_type = 1,
        .working_peg_price_type = OrderListPlaceOtocoWorkingPegPriceTypeEnum::PrimaryPeg,
        .working_peg_offset_type = OrderListPlaceOtocoWorkingPegOffsetTypeEnum::PriceLevel,
        .working_peg_offset_value = 1,
        .pending_above_client_order_id = "pendingAboveOrder1",
        .pending_above_price = common::Decimal("1"),
        .pending_above_stop_price = common::Decimal("1"),
        .pending_above_trailing_delta = common::Decimal("1"),
        .pending_above_iceberg_qty = common::Decimal("1"),
        .pending_above_time_in_force = OrderListPlaceOtocoPendingAboveTimeInForceEnum::Gtc,
        .pending_above_strategy_id = 1,
        .pending_above_strategy_type = 1,
        .pending_above_peg_price_type = OrderListPlaceOtocoPendingAbovePegPriceTypeEnum::PrimaryPeg,
        .pending_above_peg_offset_type =
            OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum::PriceLevel,
        .pending_above_peg_offset_value = 1,
        .pending_below_type = OrderListPlaceOtocoPendingBelowTypeEnum::StopLoss,
        .pending_below_client_order_id = "pendingBelowOrder1",
        .pending_below_price = common::Decimal("1"),
        .pending_below_stop_price = common::Decimal("1"),
        .pending_below_trailing_delta = common::Decimal("1"),
        .pending_below_iceberg_qty = common::Decimal("1"),
        .pending_below_time_in_force = OrderListPlaceOtocoPendingBelowTimeInForceEnum::Gtc,
        .pending_below_strategy_id = 1,
        .pending_below_strategy_type = 1,
        .pending_below_peg_price_type = OrderListPlaceOtocoPendingBelowPegPriceTypeEnum::PrimaryPeg,
        .pending_below_peg_offset_type =
            OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum::PriceLevel,
        .pending_below_peg_offset_value = 1,
        .working_quote_notional_limit = common::Decimal("100"),
        .pending_above_quote_notional_limit = common::Decimal("100"),
        .pending_below_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_place_otoco(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.place.otoco");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("workingType"));
    EXPECT_TRUE(sent.contains("workingSide"));
    EXPECT_TRUE(sent.contains("workingPrice"));
    EXPECT_TRUE(sent.contains("workingQuantity"));
    EXPECT_TRUE(sent.contains("pendingSide"));
    EXPECT_TRUE(sent.contains("pendingQuantity"));
    EXPECT_TRUE(sent.contains("pendingAboveType"));

    EXPECT_TRUE(sent.contains("listClientOrderId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("workingClientOrderId"));
    EXPECT_TRUE(sent.contains("workingIcebergQty"));
    EXPECT_TRUE(sent.contains("workingTimeInForce"));
    EXPECT_TRUE(sent.contains("workingStrategyId"));
    EXPECT_TRUE(sent.contains("workingStrategyType"));
    EXPECT_TRUE(sent.contains("workingPegPriceType"));
    EXPECT_TRUE(sent.contains("workingPegOffsetType"));
    EXPECT_TRUE(sent.contains("workingPegOffsetValue"));
    EXPECT_TRUE(sent.contains("pendingAboveClientOrderId"));
    EXPECT_TRUE(sent.contains("pendingAbovePrice"));
    EXPECT_TRUE(sent.contains("pendingAboveStopPrice"));
    EXPECT_TRUE(sent.contains("pendingAboveTrailingDelta"));
    EXPECT_TRUE(sent.contains("pendingAboveIcebergQty"));
    EXPECT_TRUE(sent.contains("pendingAboveTimeInForce"));
    EXPECT_TRUE(sent.contains("pendingAboveStrategyId"));
    EXPECT_TRUE(sent.contains("pendingAboveStrategyType"));
    EXPECT_TRUE(sent.contains("pendingAbovePegPriceType"));
    EXPECT_TRUE(sent.contains("pendingAbovePegOffsetType"));
    EXPECT_TRUE(sent.contains("pendingAbovePegOffsetValue"));
    EXPECT_TRUE(sent.contains("pendingBelowType"));
    EXPECT_TRUE(sent.contains("pendingBelowClientOrderId"));
    EXPECT_TRUE(sent.contains("pendingBelowPrice"));
    EXPECT_TRUE(sent.contains("pendingBelowStopPrice"));
    EXPECT_TRUE(sent.contains("pendingBelowTrailingDelta"));
    EXPECT_TRUE(sent.contains("pendingBelowIcebergQty"));
    EXPECT_TRUE(sent.contains("pendingBelowTimeInForce"));
    EXPECT_TRUE(sent.contains("pendingBelowStrategyId"));
    EXPECT_TRUE(sent.contains("pendingBelowStrategyType"));
    EXPECT_TRUE(sent.contains("pendingBelowPegPriceType"));
    EXPECT_TRUE(sent.contains("pendingBelowPegOffsetType"));
    EXPECT_TRUE(sent.contains("pendingBelowPegOffsetValue"));
    EXPECT_TRUE(sent.contains("workingQuoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("pendingAboveQuoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("pendingBelowQuoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderListPlaceOtocoErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderListPlaceOtocoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListPlaceOtocoWorkingTypeEnum::Limit,
        .working_side = OrderListPlaceOtocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_side = OrderListPlaceOtocoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1"),
        .pending_above_type = OrderListPlaceOtocoPendingAboveTypeEnum::StopLossLimit};
    EXPECT_THROW((void)api.order_list_place_otoco(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderPlace) {
    MockWsServer server(reply(
        R"json({"id":"56374a46-3061-486b-a311-99ee972eb648","status":200,"result":{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"4d96324ff9d44481926157ec08158a40","transactTime":1660801715639,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1660801715639,"selfTradePreventionMode":"NONE","stopPrice":"0.00000000","trailingDelta":10,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY","fills":[{"price":"23416.10000000","qty":"0.00635000","commission":"0.000000","commissionAsset":"BNB","tradeId":1650422481},{"price":"23416.50000000","qty":"0.00212000","commission":"0.000000","commissionAsset":"BNB","tradeId":1650422482}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":1},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":1},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderPlaceParams params{
        .symbol = "BNBUSDT", .side = OrderPlaceSideEnum::Buy, .type = OrderPlaceTypeEnum::Market};
    const auto res = api.order_place(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.place");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderPlaceWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"56374a46-3061-486b-a311-99ee972eb648","status":200,"result":{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"4d96324ff9d44481926157ec08158a40","transactTime":1660801715639,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1660801715639,"selfTradePreventionMode":"NONE","stopPrice":"0.00000000","trailingDelta":10,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY","fills":[{"price":"23416.10000000","qty":"0.00635000","commission":"0.000000","commissionAsset":"BNB","tradeId":1650422481},{"price":"23416.50000000","qty":"0.00212000","commission":"0.000000","commissionAsset":"BNB","tradeId":1650422482}]},"rateLimits":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":1},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":1},{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderPlaceParams params{
        .symbol = "BNBUSDT",
        .side = OrderPlaceSideEnum::Buy,
        .type = OrderPlaceTypeEnum::Market,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .time_in_force = OrderPlaceTimeInForceEnum::Gtc,
        .price = common::Decimal("1"),
        .quantity = common::Decimal("1"),
        .quote_order_qty = common::Decimal("1"),
        .new_client_order_id = "myOrder1",
        .new_order_resp_type = OrderPlaceNewOrderRespTypeEnum::Ack,
        .stop_price = common::Decimal("1"),
        .trailing_delta = 1,
        .iceberg_qty = common::Decimal("1"),
        .strategy_id = 1,
        .strategy_type = 1,
        .self_trade_prevention_mode = OrderPlaceSelfTradePreventionModeEnum::None_,
        .peg_price_type = OrderPlacePegPriceTypeEnum::PrimaryPeg,
        .peg_offset_value = 1,
        .peg_offset_type = OrderPlacePegOffsetTypeEnum::PriceLevel,
        .quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_place(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.place");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("type"));

    EXPECT_TRUE(sent.contains("timeInForce"));
    EXPECT_TRUE(sent.contains("price"));
    EXPECT_TRUE(sent.contains("quantity"));
    EXPECT_TRUE(sent.contains("quoteOrderQty"));
    EXPECT_TRUE(sent.contains("newClientOrderId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("stopPrice"));
    EXPECT_TRUE(sent.contains("trailingDelta"));
    EXPECT_TRUE(sent.contains("icebergQty"));
    EXPECT_TRUE(sent.contains("strategyId"));
    EXPECT_TRUE(sent.contains("strategyType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("pegPriceType"));
    EXPECT_TRUE(sent.contains("pegOffsetValue"));
    EXPECT_TRUE(sent.contains("pegOffsetType"));
    EXPECT_TRUE(sent.contains("quoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderPlaceErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderPlaceParams params{
        .symbol = "BNBUSDT", .side = OrderPlaceSideEnum::Buy, .type = OrderPlaceTypeEnum::Market};
    EXPECT_THROW((void)api.order_place(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, OrderTest) {
    MockWsServer server(reply(
        R"json({"id":"6ffebe91-01d9-43ac-be99-57cf062e0e30","status":200,"result":{"standardCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"specialCommissionForOrder":{"maker":"0.05000000","taker":"0.06000000"},"taxCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.25000000"}},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderTestParams params{
        .symbol = "BNBUSDT", .side = OrderTestSideEnum::Buy, .type = OrderTestTypeEnum::Market};
    const auto res = api.order_test(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.test");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderTestWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"6ffebe91-01d9-43ac-be99-57cf062e0e30","status":200,"result":{"standardCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"specialCommissionForOrder":{"maker":"0.05000000","taker":"0.06000000"},"taxCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.25000000"}},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const OrderTestParams params{
        .symbol = "BNBUSDT",
        .side = OrderTestSideEnum::Buy,
        .type = OrderTestTypeEnum::Market,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .compute_commission_rates = false,
        .time_in_force = OrderTestTimeInForceEnum::Gtc,
        .price = common::Decimal("1"),
        .quantity = common::Decimal("1"),
        .quote_order_qty = common::Decimal("1"),
        .new_client_order_id = "myOrder1",
        .new_order_resp_type = OrderTestNewOrderRespTypeEnum::Ack,
        .stop_price = common::Decimal("1"),
        .trailing_delta = 1,
        .iceberg_qty = common::Decimal("1"),
        .strategy_id = 1,
        .strategy_type = 1,
        .self_trade_prevention_mode = OrderTestSelfTradePreventionModeEnum::None_,
        .peg_price_type = OrderTestPegPriceTypeEnum::PrimaryPeg,
        .peg_offset_value = 1,
        .peg_offset_type = OrderTestPegOffsetTypeEnum::PriceLevel,
        .quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_test(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.test");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("type"));

    EXPECT_TRUE(sent.contains("computeCommissionRates"));
    EXPECT_TRUE(sent.contains("timeInForce"));
    EXPECT_TRUE(sent.contains("price"));
    EXPECT_TRUE(sent.contains("quantity"));
    EXPECT_TRUE(sent.contains("quoteOrderQty"));
    EXPECT_TRUE(sent.contains("newClientOrderId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("stopPrice"));
    EXPECT_TRUE(sent.contains("trailingDelta"));
    EXPECT_TRUE(sent.contains("icebergQty"));
    EXPECT_TRUE(sent.contains("strategyId"));
    EXPECT_TRUE(sent.contains("strategyType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("pegPriceType"));
    EXPECT_TRUE(sent.contains("pegOffsetValue"));
    EXPECT_TRUE(sent.contains("pegOffsetType"));
    EXPECT_TRUE(sent.contains("quoteNotionalLimit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, OrderTestErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderTestParams params{
        .symbol = "BNBUSDT", .side = OrderTestSideEnum::Buy, .type = OrderTestTypeEnum::Market};
    EXPECT_THROW((void)api.order_test(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, SorOrderPlace) {
    MockWsServer server(reply(
        R"json({"id":"3a4437e2-41a3-4c19-897c-9cadc5dce8b6","status":200,"result":[{"symbol":"BTCUSDT","orderId":2,"orderListId":-1,"clientOrderId":"sBI1KM6nNtOfj5tccZSKly","transactTime":1689149087774,"price":"31000.00000000","origQty":"0.50000000","executedQty":"0.50000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"14000.00000000","status":"FILLED","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1689149087774,"fills":[{"matchType":"ONE_PARTY_TRADE_REPORT","price":"28000.00000000","qty":"0.50000000","commission":"0.00000000","commissionAsset":"BTC","tradeId":-1,"allocId":0}],"workingFloor":"SOR","selfTradePreventionMode":"NONE","usedSor":true,"stopPrice":"0.00000000","trailingDelta":10,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const SorOrderPlaceParams params{.symbol = "BNBUSDT",
                                     .side = SorOrderPlaceSideEnum::Buy,
                                     .type = SorOrderPlaceTypeEnum::Market,
                                     .quantity = common::Decimal("1")};
    const auto res = api.sor_order_place(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "sor.order.place");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, SorOrderPlaceWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"3a4437e2-41a3-4c19-897c-9cadc5dce8b6","status":200,"result":[{"symbol":"BTCUSDT","orderId":2,"orderListId":-1,"clientOrderId":"sBI1KM6nNtOfj5tccZSKly","transactTime":1689149087774,"price":"31000.00000000","origQty":"0.50000000","executedQty":"0.50000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"14000.00000000","status":"FILLED","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1689149087774,"fills":[{"matchType":"ONE_PARTY_TRADE_REPORT","price":"28000.00000000","qty":"0.50000000","commission":"0.00000000","commissionAsset":"BTC","tradeId":-1,"allocId":0}],"workingFloor":"SOR","selfTradePreventionMode":"NONE","usedSor":true,"stopPrice":"0.00000000","trailingDelta":10,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const SorOrderPlaceParams params{
        .symbol = "BNBUSDT",
        .side = SorOrderPlaceSideEnum::Buy,
        .type = SorOrderPlaceTypeEnum::Market,
        .quantity = common::Decimal("1"),
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .time_in_force = SorOrderPlaceTimeInForceEnum::Gtc,
        .price = common::Decimal("1"),
        .new_client_order_id = "myOrder1",
        .new_order_resp_type = SorOrderPlaceNewOrderRespTypeEnum::Ack,
        .iceberg_qty = common::Decimal("1"),
        .strategy_id = 1,
        .strategy_type = 1,
        .self_trade_prevention_mode = SorOrderPlaceSelfTradePreventionModeEnum::None_,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.sor_order_place(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "sor.order.place");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("type"));
    EXPECT_TRUE(sent.contains("quantity"));

    EXPECT_TRUE(sent.contains("timeInForce"));
    EXPECT_TRUE(sent.contains("price"));
    EXPECT_TRUE(sent.contains("newClientOrderId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("icebergQty"));
    EXPECT_TRUE(sent.contains("strategyId"));
    EXPECT_TRUE(sent.contains("strategyType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, SorOrderPlaceErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const SorOrderPlaceParams params{.symbol = "BNBUSDT",
                                     .side = SorOrderPlaceSideEnum::Buy,
                                     .type = SorOrderPlaceTypeEnum::Market,
                                     .quantity = common::Decimal("1")};
    EXPECT_THROW((void)api.sor_order_place(params), common::WebsocketResponseError);
}

TEST(WebsocketApiTradeApi, SorOrderTest) {
    MockWsServer server(reply(
        R"json({"id":"3a4437e2-41a3-4c19-897c-9cadc5dce8b6","status":200,"result":{"standardCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"taxCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.25000000"}},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const SorOrderTestParams params{.symbol = "BNBUSDT",
                                    .side = SorOrderTestSideEnum::Buy,
                                    .type = SorOrderTestTypeEnum::Market,
                                    .quantity = common::Decimal("1")};
    const auto res = api.sor_order_test(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "sor.order.test");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiTradeApi, SorOrderTestWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"3a4437e2-41a3-4c19-897c-9cadc5dce8b6","status":200,"result":{"standardCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"taxCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.25000000"}},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const SorOrderTestParams params{
        .symbol = "BNBUSDT",
        .side = SorOrderTestSideEnum::Buy,
        .type = SorOrderTestTypeEnum::Market,
        .quantity = common::Decimal("1"),
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .compute_commission_rates = false,
        .time_in_force = SorOrderTestTimeInForceEnum::Gtc,
        .price = common::Decimal("1"),
        .new_client_order_id = "myOrder1",
        .new_order_resp_type = SorOrderTestNewOrderRespTypeEnum::Ack,
        .iceberg_qty = common::Decimal("1"),
        .strategy_id = 1,
        .strategy_type = 1,
        .self_trade_prevention_mode = SorOrderTestSelfTradePreventionModeEnum::None_,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.sor_order_test(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "sor.order.test");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("side"));
    EXPECT_TRUE(sent.contains("type"));
    EXPECT_TRUE(sent.contains("quantity"));

    EXPECT_TRUE(sent.contains("computeCommissionRates"));
    EXPECT_TRUE(sent.contains("timeInForce"));
    EXPECT_TRUE(sent.contains("price"));
    EXPECT_TRUE(sent.contains("newClientOrderId"));
    EXPECT_TRUE(sent.contains("newOrderRespType"));
    EXPECT_TRUE(sent.contains("icebergQty"));
    EXPECT_TRUE(sent.contains("strategyId"));
    EXPECT_TRUE(sent.contains("strategyType"));
    EXPECT_TRUE(sent.contains("selfTradePreventionMode"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiTradeApi, SorOrderTestErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const SorOrderTestParams params{.symbol = "BNBUSDT",
                                    .side = SorOrderTestSideEnum::Buy,
                                    .type = SorOrderTestTypeEnum::Market,
                                    .quantity = common::Decimal("1")};
    EXPECT_THROW((void)api.sor_order_test(params), common::WebsocketResponseError);
}
