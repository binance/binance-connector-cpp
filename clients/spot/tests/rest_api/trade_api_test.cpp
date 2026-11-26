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
#include <binance/spot/rest_api/trade_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::spot::rest_api;
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

TEST(RestApiTradeApi, DeleteOpenOrders) {
    const std::string example =
        R"json([{"orderListId":-1,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"iuVNVJYYrByz6C4yGOPPK0","transactionTime":1660803702431,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569099453,"clientOrderId":"bX5wROblo6YeDwa9iTLeyY"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"bX5wROblo6YeDwa9iTLeyY","orderId":12569099453,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23450.50000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}],"origClientOrderId":"4d96324ff9d44481926157","orderId":12569099453,"clientOrderId":"91fe37ce9e69c90d6358c0","transactTime":1684804350068,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00001000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.23416100","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","stopPrice":"0.00000000","trailingDelta":10,"trailingTime":-1,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteOpenOrdersParams params{.symbol = "BNBUSDT"};
    const auto res = api.delete_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/api/v3/openOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, DeleteOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderListId":-1,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"iuVNVJYYrByz6C4yGOPPK0","transactionTime":1660803702431,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569099453,"clientOrderId":"bX5wROblo6YeDwa9iTLeyY"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"bX5wROblo6YeDwa9iTLeyY","orderId":12569099453,"orderListId":19431,"clientOrderId":"OFFXQtxVFZ6Nbcg4PgE2DA","transactTime":1684804350068,"price":"23450.50000000","origQty":"0.00850000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}],"origClientOrderId":"4d96324ff9d44481926157","orderId":12569099453,"clientOrderId":"91fe37ce9e69c90d6358c0","transactTime":1684804350068,"price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00001000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.23416100","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","stopPrice":"0.00000000","trailingDelta":10,"trailingTime":-1,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteOpenOrdersParams params{
        .symbol = "BNBUSDT",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.delete_open_orders(params);
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

TEST(RestApiTradeApi, DeleteOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DeleteOpenOrdersParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.delete_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, DeleteOrder) {
    const std::string example =
        R"json({"symbol":"LTCBTC","orderId":4,"orderListId":-1,"origClientOrderId":"myOrder1","clientOrderId":"cancelMyOrder1","transactTime":1684804350068,"price":"2.00000000","origQty":"1.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"BUY","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"23500.00000000","strategyId":37463720,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteOrderParams params{.symbol = "BNBUSDT"};
    const auto res = api.delete_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/api/v3/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, DeleteOrderWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"LTCBTC","orderId":4,"orderListId":-1,"origClientOrderId":"myOrder1","clientOrderId":"cancelMyOrder1","transactTime":1684804350068,"price":"2.00000000","origQty":"1.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"BUY","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"23500.00000000","strategyId":37463720,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteOrderParams params{
        .symbol = "BNBUSDT",
        .order_id = 1,
        .orig_client_order_id = "myOrder1",
        .new_client_order_id = "cancelMyOrder1",
        .cancel_restrictions = DeleteOrderCancelRestrictionsEnum::OnlyNew,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.delete_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("cancelRestrictions="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, DeleteOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DeleteOrderParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.delete_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewOrder) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","orderId":28,"orderListId":-1,"clientOrderId":"6gCrw2kRUAF9CvJDGP16IP","transactTime":1507725176595,"price":"0.00000000","origQty":"10.00000000","executedQty":"10.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"10.00000000","status":"FILLED","timeInForce":"GTC","type":"MARKET","side":"SELL","workingTime":1507725176595,"selfTradePreventionMode":"NONE","stopPrice":"0.00000000","trailingDelta":10,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY","fills":[{"price":"4000.00000000","qty":"1.00000000","commission":"4.00000000","commissionAsset":"USDT","tradeId":56},{"price":"3999.00000000","qty":"5.00000000","commission":"19.99500000","commissionAsset":"USDT","tradeId":57},{"price":"3998.00000000","qty":"2.00000000","commission":"7.99600000","commissionAsset":"USDT","tradeId":58},{"price":"3997.00000000","qty":"1.00000000","commission":"3.99700000","commissionAsset":"USDT","tradeId":59},{"price":"3995.00000000","qty":"1.00000000","commission":"3.99500000","commissionAsset":"USDT","tradeId":60}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BNBUSDT", .side = NewOrderSideEnum::Buy, .type = NewOrderTypeEnum::Market};
    const auto res = api.new_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewOrderWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","orderId":28,"orderListId":-1,"clientOrderId":"6gCrw2kRUAF9CvJDGP16IP","transactTime":1507725176595,"price":"0.00000000","origQty":"10.00000000","executedQty":"10.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"10.00000000","status":"FILLED","timeInForce":"GTC","type":"MARKET","side":"SELL","workingTime":1507725176595,"selfTradePreventionMode":"NONE","stopPrice":"0.00000000","trailingDelta":10,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY","fills":[{"price":"4000.00000000","qty":"1.00000000","commission":"4.00000000","commissionAsset":"USDT","tradeId":56},{"price":"3999.00000000","qty":"5.00000000","commission":"19.99500000","commissionAsset":"USDT","tradeId":57},{"price":"3998.00000000","qty":"2.00000000","commission":"7.99600000","commissionAsset":"USDT","tradeId":58},{"price":"3997.00000000","qty":"1.00000000","commission":"3.99700000","commissionAsset":"USDT","tradeId":59},{"price":"3995.00000000","qty":"1.00000000","commission":"3.99500000","commissionAsset":"USDT","tradeId":60}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BNBUSDT",
        .side = NewOrderSideEnum::Buy,
        .type = NewOrderTypeEnum::Market,
        .time_in_force = NewOrderTimeInForceEnum::Gtc,
        .quantity = common::Decimal("1"),
        .quote_order_qty = common::Decimal("1"),
        .price = common::Decimal("400"),
        .new_client_order_id = "myOrder1",
        .strategy_id = 1,
        .strategy_type = 1,
        .stop_price = common::Decimal("1"),
        .trailing_delta = 1,
        .iceberg_qty = common::Decimal("1"),
        .new_order_resp_type = NewOrderNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = NewOrderSelfTradePreventionModeEnum::None_,
        .peg_price_type = NewOrderPegPriceTypeEnum::PrimaryPeg,
        .peg_offset_value = 1,
        .peg_offset_type = NewOrderPegOffsetTypeEnum::PriceLevel,
        .quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
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
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteOrderQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("trailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("icebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BNBUSDT", .side = NewOrderSideEnum::Buy, .type = NewOrderTypeEnum::Market};
    EXPECT_THROW((void)api.new_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, DeleteOrderList) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"C3wyj4WVEktd7u9aVBRXcN","transactionTime":1574040868128,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"pO9ufTiFGg3nw2fOdgeOXa"},{"symbol":"LTCBTC","orderId":3,"clientOrderId":"TXOvglzXuaubXAaENpaRCB"}],"orderReports":[{"symbol":"LTCBTC","origClientOrderId":"pO9ufTiFGg3nw2fOdgeOXa","orderId":2,"orderListId":0,"clientOrderId":"unfWT8ig8i0uj6lPuYLez6","transactTime":1688005070874,"price":"1.00000000","origQty":"10.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"1.00000000","selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","origClientOrderId":"TXOvglzXuaubXAaENpaRCB","orderId":3,"orderListId":0,"clientOrderId":"unfWT8ig8i0uj6lPuYLez6","transactTime":1688005070874,"price":"3.00000000","origQty":"10.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteOrderListParams params{.symbol = "BNBUSDT"};
    const auto res = api.delete_order_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/api/v3/orderList");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, DeleteOrderListWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"C3wyj4WVEktd7u9aVBRXcN","transactionTime":1574040868128,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"pO9ufTiFGg3nw2fOdgeOXa"},{"symbol":"LTCBTC","orderId":3,"clientOrderId":"TXOvglzXuaubXAaENpaRCB"}],"orderReports":[{"symbol":"LTCBTC","origClientOrderId":"pO9ufTiFGg3nw2fOdgeOXa","orderId":2,"orderListId":0,"clientOrderId":"unfWT8ig8i0uj6lPuYLez6","transactTime":1688005070874,"price":"1.00000000","origQty":"10.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"1.00000000","selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","origClientOrderId":"TXOvglzXuaubXAaENpaRCB","orderId":3,"orderListId":0,"clientOrderId":"unfWT8ig8i0uj6lPuYLez6","transactTime":1688005070874,"price":"3.00000000","origQty":"10.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteOrderListParams params{
        .symbol = "BNBUSDT",
        .order_list_id = 1,
        .list_client_order_id = "C3wyj4WVEktd7u9aVBRXcN",
        .new_client_order_id = "cancelMyOrder1",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.delete_order_list(params);
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

TEST(RestApiTradeApi, DeleteOrderListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DeleteOrderListParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.delete_order_list(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderAmendKeepPriority) {
    const std::string example =
        R"json({"transactTime":1741926410255,"executionId":75,"amendedOrder":{"symbol":"BTCUSDT","orderId":33,"orderListId":-1,"origClientOrderId":"5xrgbMyg6z36NzBn2pbT8H","clientOrderId":"PFaq6hIHxqFENGfdtn4J6Q","price":"6.00000000","qty":"5.00000000","executedQty":"0.00000000","preventedQty":"0.00000000","quoteOrderQty":"0.00000000","cumulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1741926410242,"selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"listStatus":{"orderListId":1,"contingencyType":"OTO","listOrderStatus":"EXECUTING","listClientOrderId":"AT7FTxZXylVSwRoZs52mt3","symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":8,"clientOrderId":"GkwwHZUUbFtZOoH1YsZk9Q"},{"symbol":"BTCUSDT","orderId":9,"clientOrderId":"UQ1Np3bmQ71jJzsSDW9Vpi"}]}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderAmendKeepPriorityParams params{.symbol = "BNBUSDT", .new_qty = common::Decimal("5")};
    const auto res = api.order_amend_keep_priority(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/api/v3/order/amend/keepPriority");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newQty="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderAmendKeepPriorityWithOptionalParams) {
    const std::string example =
        R"json({"transactTime":1741926410255,"executionId":75,"amendedOrder":{"symbol":"BTCUSDT","orderId":33,"orderListId":-1,"origClientOrderId":"5xrgbMyg6z36NzBn2pbT8H","clientOrderId":"PFaq6hIHxqFENGfdtn4J6Q","price":"6.00000000","qty":"5.00000000","executedQty":"0.00000000","preventedQty":"0.00000000","quoteOrderQty":"0.00000000","cumulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1741926410242,"selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"listStatus":{"orderListId":1,"contingencyType":"OTO","listOrderStatus":"EXECUTING","listClientOrderId":"AT7FTxZXylVSwRoZs52mt3","symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":8,"clientOrderId":"GkwwHZUUbFtZOoH1YsZk9Q"},{"symbol":"BTCUSDT","orderId":9,"clientOrderId":"UQ1Np3bmQ71jJzsSDW9Vpi"}]}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderAmendKeepPriorityParams params{
        .symbol = "BNBUSDT",
        .new_qty = common::Decimal("5"),
        .order_id = 1,
        .orig_client_order_id = "myOrder1",
        .new_client_order_id = "myOrder2",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_amend_keep_priority(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderAmendKeepPriorityBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderAmendKeepPriorityParams params{.symbol = "BNBUSDT", .new_qty = common::Decimal("5")};
    EXPECT_THROW((void)api.order_amend_keep_priority(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderCancelReplace) {
    const std::string example =
        R"json({"cancelResult":"SUCCESS","newOrderResult":"SUCCESS","cancelResponse":{"symbol":"BTCUSDT","origClientOrderId":"DnLo3vTAQcjha43lAZhZ0y","orderId":9,"orderListId":-1,"clientOrderId":"osxN3JXAtJvKvCqGeMWMVR","transactTime":1684804350068,"price":"0.01000000","origQty":"0.000100","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"newOrderResponse":{"symbol":"BTCUSDT","orderId":10,"orderListId":-1,"clientOrderId":"wOceeeOzNORyLiQfw7jd8S","transactTime":1652928801803,"price":"0.02000000","origQty":"0.040000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1669277163808,"fills":[],"selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderCancelReplaceParams params{
        .symbol = "BNBUSDT",
        .side = OrderCancelReplaceSideEnum::Buy,
        .type = OrderCancelReplaceTypeEnum::Market,
        .cancel_replace_mode = OrderCancelReplaceCancelReplaceModeEnum::StopOnFailure};
    const auto res = api.order_cancel_replace(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/order/cancelReplace");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("cancelReplaceMode="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderCancelReplaceWithOptionalParams) {
    const std::string example =
        R"json({"cancelResult":"SUCCESS","newOrderResult":"SUCCESS","cancelResponse":{"symbol":"BTCUSDT","origClientOrderId":"DnLo3vTAQcjha43lAZhZ0y","orderId":9,"orderListId":-1,"clientOrderId":"osxN3JXAtJvKvCqGeMWMVR","transactTime":1684804350068,"price":"0.01000000","origQty":"0.000100","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"newOrderResponse":{"symbol":"BTCUSDT","orderId":10,"orderListId":-1,"clientOrderId":"wOceeeOzNORyLiQfw7jd8S","transactTime":1652928801803,"price":"0.02000000","origQty":"0.040000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1669277163808,"fills":[],"selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderCancelReplaceParams params{
        .symbol = "BNBUSDT",
        .side = OrderCancelReplaceSideEnum::Buy,
        .type = OrderCancelReplaceTypeEnum::Market,
        .cancel_replace_mode = OrderCancelReplaceCancelReplaceModeEnum::StopOnFailure,
        .time_in_force = OrderCancelReplaceTimeInForceEnum::Gtc,
        .quantity = common::Decimal("1"),
        .quote_order_qty = common::Decimal("1"),
        .price = common::Decimal("400"),
        .cancel_new_client_order_id = "cancelMyOrder1",
        .cancel_orig_client_order_id = "myOrder1",
        .cancel_order_id = 1,
        .new_client_order_id = "myOrder2",
        .strategy_id = 1,
        .strategy_type = 1,
        .stop_price = common::Decimal("1"),
        .trailing_delta = 1,
        .iceberg_qty = common::Decimal("1"),
        .new_order_resp_type = OrderCancelReplaceNewOrderRespTypeEnum::Ack,
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
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("cancelReplaceMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteOrderQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("cancelNewClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("cancelOrigClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("cancelOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("trailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("icebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("cancelRestrictions="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderRateLimitExceededMode="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderCancelReplaceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderCancelReplaceParams params{
        .symbol = "BNBUSDT",
        .side = OrderCancelReplaceSideEnum::Buy,
        .type = OrderCancelReplaceTypeEnum::Market,
        .cancel_replace_mode = OrderCancelReplaceCancelReplaceModeEnum::StopOnFailure};
    EXPECT_THROW((void)api.order_cancel_replace(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderListOco) {
    const std::string example =
        R"json({"orderListId":1,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"lH1YDkuQKWiXVXHPSKYEIp","transactionTime":1710485608839,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":10,"clientOrderId":"44nZvqpemY7sVYgPYbvPih"},{"symbol":"LTCBTC","orderId":11,"clientOrderId":"NuMp0nVYnciDiFmVqfpBqK"}],"orderReports":[{"symbol":"LTCBTC","orderId":10,"orderListId":1,"clientOrderId":"44nZvqpemY7sVYgPYbvPih","transactTime":1710485608839,"price":"1.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"1.00000000","workingTime":-1,"icebergQty":"1.00000000","selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":11,"orderListId":1,"clientOrderId":"NuMp0nVYnciDiFmVqfpBqK","transactTime":1710485608839,"price":"3.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":1710485608839,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOcoParams params{.symbol = "BNBUSDT",
                                    .side = OrderListOcoSideEnum::Buy,
                                    .quantity = common::Decimal("1"),
                                    .above_type = OrderListOcoAboveTypeEnum::StopLossLimit,
                                    .below_type = OrderListOcoBelowTypeEnum::StopLoss};
    const auto res = api.order_list_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/orderList/oco");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOcoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":1,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"lH1YDkuQKWiXVXHPSKYEIp","transactionTime":1710485608839,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":10,"clientOrderId":"44nZvqpemY7sVYgPYbvPih"},{"symbol":"LTCBTC","orderId":11,"clientOrderId":"NuMp0nVYnciDiFmVqfpBqK"}],"orderReports":[{"symbol":"LTCBTC","orderId":10,"orderListId":1,"clientOrderId":"44nZvqpemY7sVYgPYbvPih","transactTime":1710485608839,"price":"1.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"1.00000000","workingTime":-1,"icebergQty":"1.00000000","selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":11,"orderListId":1,"clientOrderId":"NuMp0nVYnciDiFmVqfpBqK","transactTime":1710485608839,"price":"3.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":1710485608839,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOcoParams params{
        .symbol = "BNBUSDT",
        .side = OrderListOcoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .above_type = OrderListOcoAboveTypeEnum::StopLossLimit,
        .below_type = OrderListOcoBelowTypeEnum::StopLoss,
        .list_client_order_id = "lH1YDkuQKWiXVXHPSKYEIp",
        .above_client_order_id = "aboveOrder1",
        .above_iceberg_qty = common::Decimal("1"),
        .above_price = common::Decimal("1.5"),
        .above_stop_price = common::Decimal("1.50000001"),
        .above_trailing_delta = 1,
        .above_time_in_force = OrderListOcoAboveTimeInForceEnum::Gtc,
        .above_strategy_id = 1,
        .above_strategy_type = 1,
        .above_peg_price_type = OrderListOcoAbovePegPriceTypeEnum::PrimaryPeg,
        .above_peg_offset_type = OrderListOcoAbovePegOffsetTypeEnum::PriceLevel,
        .above_peg_offset_value = 1,
        .below_client_order_id = "belowOrder1",
        .below_iceberg_qty = common::Decimal("1"),
        .below_price = common::Decimal("1.49999999"),
        .below_stop_price = common::Decimal("1.50000001"),
        .below_trailing_delta = 1,
        .below_time_in_force = OrderListOcoBelowTimeInForceEnum::Gtc,
        .below_strategy_id = 1,
        .below_strategy_type = 1,
        .below_peg_price_type = OrderListOcoBelowPegPriceTypeEnum::PrimaryPeg,
        .below_peg_offset_type = OrderListOcoBelowPegOffsetTypeEnum::PriceLevel,
        .below_peg_offset_value = 1,
        .new_order_resp_type = OrderListOcoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListOcoSelfTradePreventionModeEnum::None_,
        .above_quote_notional_limit = common::Decimal("100"),
        .below_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("abovePrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("abovePegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("abovePegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("abovePegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowPegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowPegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowPegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aboveQuoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("belowQuoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderListOcoParams params{.symbol = "BNBUSDT",
                                    .side = OrderListOcoSideEnum::Buy,
                                    .quantity = common::Decimal("1"),
                                    .above_type = OrderListOcoAboveTypeEnum::StopLossLimit,
                                    .below_type = OrderListOcoBelowTypeEnum::StopLoss};
    EXPECT_THROW((void)api.order_list_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderListOpo) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"H94qCqO27P74OEiO4X8HOG","transactionTime":1762998011671,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":2,"clientOrderId":"JX6xfdjo0wysiGumfHNmPu"},{"symbol":"BTCUSDT","orderId":3,"clientOrderId":"2ZJCY0IjOhuYIMLGN8kU8S"}],"orderReports":[{"symbol":"BTCUSDT","orderId":2,"orderListId":0,"clientOrderId":"JX6xfdjo0wysiGumfHNmPu","transactTime":1762998011671,"price":"102264.00000000","origQty":"0.00060000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1762998011671,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":3,"orderListId":0,"clientOrderId":"2ZJCY0IjOhuYIMLGN8kU8S","transactTime":1762998011671,"price":"0.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"MARKET","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOpoParams params{.symbol = "BNBUSDT",
                                    .working_type = OrderListOpoWorkingTypeEnum::Limit,
                                    .working_side = OrderListOpoWorkingSideEnum::Buy,
                                    .working_price = common::Decimal("1"),
                                    .working_quantity = common::Decimal("1"),
                                    .pending_type = OrderListOpoPendingTypeEnum::Limit,
                                    .pending_side = OrderListOpoPendingSideEnum::Buy};
    const auto res = api.order_list_opo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/orderList/opo");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOpoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"H94qCqO27P74OEiO4X8HOG","transactionTime":1762998011671,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":2,"clientOrderId":"JX6xfdjo0wysiGumfHNmPu"},{"symbol":"BTCUSDT","orderId":3,"clientOrderId":"2ZJCY0IjOhuYIMLGN8kU8S"}],"orderReports":[{"symbol":"BTCUSDT","orderId":2,"orderListId":0,"clientOrderId":"JX6xfdjo0wysiGumfHNmPu","transactTime":1762998011671,"price":"102264.00000000","origQty":"0.00060000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1762998011671,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":3,"orderListId":0,"clientOrderId":"2ZJCY0IjOhuYIMLGN8kU8S","transactTime":1762998011671,"price":"0.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"MARKET","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOpoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListOpoWorkingTypeEnum::Limit,
        .working_side = OrderListOpoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_type = OrderListOpoPendingTypeEnum::Limit,
        .pending_side = OrderListOpoPendingSideEnum::Buy,
        .list_client_order_id = "H94qCqO27P74OEiO4X8HOG",
        .new_order_resp_type = OrderListOpoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListOpoSelfTradePreventionModeEnum::None_,
        .working_client_order_id = "workingOrder1",
        .working_iceberg_qty = common::Decimal("1"),
        .working_time_in_force = OrderListOpoWorkingTimeInForceEnum::Gtc,
        .working_strategy_id = 1,
        .working_strategy_type = 1,
        .working_peg_price_type = OrderListOpoWorkingPegPriceTypeEnum::PrimaryPeg,
        .working_peg_offset_type = OrderListOpoWorkingPegOffsetTypeEnum::PriceLevel,
        .working_peg_offset_value = 1,
        .pending_client_order_id = "pendingOrder1",
        .pending_price = common::Decimal("1"),
        .pending_stop_price = common::Decimal("1"),
        .pending_trailing_delta = common::Decimal("1"),
        .pending_iceberg_qty = common::Decimal("1"),
        .pending_time_in_force = OrderListOpoPendingTimeInForceEnum::Gtc,
        .pending_strategy_id = 1,
        .pending_strategy_type = 1,
        .pending_peg_price_type = OrderListOpoPendingPegPriceTypeEnum::PrimaryPeg,
        .pending_peg_offset_type = OrderListOpoPendingPegOffsetTypeEnum::PriceLevel,
        .pending_peg_offset_value = 1,
        .working_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_opo(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingPegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingPegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingPegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOpoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderListOpoParams params{.symbol = "BNBUSDT",
                                    .working_type = OrderListOpoWorkingTypeEnum::Limit,
                                    .working_side = OrderListOpoWorkingSideEnum::Buy,
                                    .working_price = common::Decimal("1"),
                                    .working_quantity = common::Decimal("1"),
                                    .pending_type = OrderListOpoPendingTypeEnum::Limit,
                                    .pending_side = OrderListOpoPendingSideEnum::Buy};
    EXPECT_THROW((void)api.order_list_opo(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderListOpoco) {
    const std::string example =
        R"json({"orderListId":2,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"bcedxMpQG6nFrZUPQyshoL","transactionTime":1763000506354,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":9,"clientOrderId":"OLSBhMWaIlLSzZ9Zm7fnKB"},{"symbol":"BTCUSDT","orderId":10,"clientOrderId":"mfif39yPTHsB3C0FIXznR2"},{"symbol":"BTCUSDT","orderId":11,"clientOrderId":"yINkaXSJeoi3bU5vWMY8Z8"}],"orderReports":[{"symbol":"BTCUSDT","orderId":9,"orderListId":2,"clientOrderId":"OLSBhMWaIlLSzZ9Zm7fnKB","transactTime":1763000506354,"price":"102496.00000000","origQty":"0.00170000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1763000506354,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":10,"orderListId":2,"clientOrderId":"mfif39yPTHsB3C0FIXznR2","transactTime":1763000506354,"price":"101613.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"10100.00000000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":11,"orderListId":2,"clientOrderId":"yINkaXSJeoi3bU5vWMY8Z8","transactTime":1763000506354,"price":"104261.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOpocoParams params{.symbol = "BNBUSDT",
                                      .working_type = OrderListOpocoWorkingTypeEnum::Limit,
                                      .working_side = OrderListOpocoWorkingSideEnum::Buy,
                                      .working_price = common::Decimal("1"),
                                      .working_quantity = common::Decimal("1"),
                                      .pending_side = OrderListOpocoPendingSideEnum::Buy,
                                      .pending_above_type =
                                          OrderListOpocoPendingAboveTypeEnum::StopLossLimit};
    const auto res = api.order_list_opoco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/orderList/opoco");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOpocoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":2,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"bcedxMpQG6nFrZUPQyshoL","transactionTime":1763000506354,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":9,"clientOrderId":"OLSBhMWaIlLSzZ9Zm7fnKB"},{"symbol":"BTCUSDT","orderId":10,"clientOrderId":"mfif39yPTHsB3C0FIXznR2"},{"symbol":"BTCUSDT","orderId":11,"clientOrderId":"yINkaXSJeoi3bU5vWMY8Z8"}],"orderReports":[{"symbol":"BTCUSDT","orderId":9,"orderListId":2,"clientOrderId":"OLSBhMWaIlLSzZ9Zm7fnKB","transactTime":1763000506354,"price":"102496.00000000","origQty":"0.00170000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1763000506354,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":10,"orderListId":2,"clientOrderId":"mfif39yPTHsB3C0FIXznR2","transactTime":1763000506354,"price":"101613.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"10100.00000000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"BTCUSDT","orderId":11,"orderListId":2,"clientOrderId":"yINkaXSJeoi3bU5vWMY8Z8","transactTime":1763000506354,"price":"104261.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"SELL","workingTime":-1,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOpocoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListOpocoWorkingTypeEnum::Limit,
        .working_side = OrderListOpocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_side = OrderListOpocoPendingSideEnum::Buy,
        .pending_above_type = OrderListOpocoPendingAboveTypeEnum::StopLossLimit,
        .list_client_order_id = "bcedxMpQG6nFrZUPQyshoL",
        .new_order_resp_type = OrderListOpocoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListOpocoSelfTradePreventionModeEnum::None_,
        .working_client_order_id = "workingOrder1",
        .working_iceberg_qty = common::Decimal("1"),
        .working_time_in_force = OrderListOpocoWorkingTimeInForceEnum::Gtc,
        .working_strategy_id = 1,
        .working_strategy_type = 1,
        .working_peg_price_type = OrderListOpocoWorkingPegPriceTypeEnum::PrimaryPeg,
        .working_peg_offset_type = OrderListOpocoWorkingPegOffsetTypeEnum::PriceLevel,
        .working_peg_offset_value = 1,
        .pending_above_client_order_id = "pendingAboveOrder1",
        .pending_above_price = common::Decimal("1"),
        .pending_above_stop_price = common::Decimal("1"),
        .pending_above_trailing_delta = common::Decimal("1"),
        .pending_above_iceberg_qty = common::Decimal("1"),
        .pending_above_time_in_force = OrderListOpocoPendingAboveTimeInForceEnum::Gtc,
        .pending_above_strategy_id = 1,
        .pending_above_strategy_type = 1,
        .pending_above_peg_price_type = OrderListOpocoPendingAbovePegPriceTypeEnum::PrimaryPeg,
        .pending_above_peg_offset_type = OrderListOpocoPendingAbovePegOffsetTypeEnum::PriceLevel,
        .pending_above_peg_offset_value = 1,
        .pending_below_type = OrderListOpocoPendingBelowTypeEnum::StopLoss,
        .pending_below_client_order_id = "pendingBelowOrder1",
        .pending_below_price = common::Decimal("1"),
        .pending_below_stop_price = common::Decimal("1"),
        .pending_below_trailing_delta = common::Decimal("1"),
        .pending_below_iceberg_qty = common::Decimal("1"),
        .pending_below_time_in_force = OrderListOpocoPendingBelowTimeInForceEnum::Gtc,
        .pending_below_strategy_id = 1,
        .pending_below_strategy_type = 1,
        .pending_below_peg_price_type = OrderListOpocoPendingBelowPegPriceTypeEnum::PrimaryPeg,
        .pending_below_peg_offset_type = OrderListOpocoPendingBelowPegOffsetTypeEnum::PriceLevel,
        .pending_below_peg_offset_value = 1,
        .working_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_opoco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAbovePrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAbovePegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAbovePegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAbovePegOffsetValue="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowPegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowPegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowPegOffsetValue="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOpocoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderListOpocoParams params{.symbol = "BNBUSDT",
                                      .working_type = OrderListOpocoWorkingTypeEnum::Limit,
                                      .working_side = OrderListOpocoWorkingSideEnum::Buy,
                                      .working_price = common::Decimal("1"),
                                      .working_quantity = common::Decimal("1"),
                                      .pending_side = OrderListOpocoPendingSideEnum::Buy,
                                      .pending_above_type =
                                          OrderListOpocoPendingAboveTypeEnum::StopLossLimit};
    EXPECT_THROW((void)api.order_list_opoco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderListOto) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"yl2ERtcar1o25zcWtqVBTC","transactionTime":1712289389158,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"Bq17mn9fP6vyCn75Jw1xya"},{"symbol":"LTCBTC","orderId":5,"clientOrderId":"arLFo0zGJVDE69cvGBaU0d"}],"orderReports":[{"symbol":"LTCBTC","orderId":4,"orderListId":0,"clientOrderId":"Bq17mn9fP6vyCn75Jw1xya","transactTime":1712289389158,"price":"1.00000000","origQty":"1.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1712289389158,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":5,"orderListId":0,"clientOrderId":"arLFo0zGJVDE69cvGBaU0d","transactTime":1712289389158,"price":"0.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"MARKET","side":"BUY","workingTime":-1,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOtoParams params{.symbol = "BNBUSDT",
                                    .working_type = OrderListOtoWorkingTypeEnum::Limit,
                                    .working_side = OrderListOtoWorkingSideEnum::Buy,
                                    .working_price = common::Decimal("1"),
                                    .working_quantity = common::Decimal("1"),
                                    .pending_type = OrderListOtoPendingTypeEnum::Limit,
                                    .pending_side = OrderListOtoPendingSideEnum::Buy,
                                    .pending_quantity = common::Decimal("1")};
    const auto res = api.order_list_oto(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/orderList/oto");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuantity="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOtoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"yl2ERtcar1o25zcWtqVBTC","transactionTime":1712289389158,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"Bq17mn9fP6vyCn75Jw1xya"},{"symbol":"LTCBTC","orderId":5,"clientOrderId":"arLFo0zGJVDE69cvGBaU0d"}],"orderReports":[{"symbol":"LTCBTC","orderId":4,"orderListId":0,"clientOrderId":"Bq17mn9fP6vyCn75Jw1xya","transactTime":1712289389158,"price":"1.00000000","origQty":"1.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1712289389158,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":5,"orderListId":0,"clientOrderId":"arLFo0zGJVDE69cvGBaU0d","transactTime":1712289389158,"price":"0.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"MARKET","side":"BUY","workingTime":-1,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOtoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListOtoWorkingTypeEnum::Limit,
        .working_side = OrderListOtoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_type = OrderListOtoPendingTypeEnum::Limit,
        .pending_side = OrderListOtoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1"),
        .list_client_order_id = "yl2ERtcar1o25zcWtqVBTC",
        .new_order_resp_type = OrderListOtoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListOtoSelfTradePreventionModeEnum::None_,
        .working_client_order_id = "workingOrder1",
        .working_iceberg_qty = common::Decimal("1"),
        .working_time_in_force = OrderListOtoWorkingTimeInForceEnum::Gtc,
        .working_strategy_id = 1,
        .working_strategy_type = 1,
        .working_peg_price_type = OrderListOtoWorkingPegPriceTypeEnum::PrimaryPeg,
        .working_peg_offset_type = OrderListOtoWorkingPegOffsetTypeEnum::PriceLevel,
        .working_peg_offset_value = 1,
        .pending_client_order_id = "pendingOrder1",
        .pending_price = common::Decimal("1"),
        .pending_stop_price = common::Decimal("1"),
        .pending_trailing_delta = common::Decimal("1"),
        .pending_iceberg_qty = common::Decimal("1"),
        .pending_time_in_force = OrderListOtoPendingTimeInForceEnum::Gtc,
        .pending_strategy_id = 1,
        .pending_strategy_type = 1,
        .pending_peg_price_type = OrderListOtoPendingPegPriceTypeEnum::PrimaryPeg,
        .pending_peg_offset_type = OrderListOtoPendingPegOffsetTypeEnum::PriceLevel,
        .pending_peg_offset_value = 1,
        .working_quote_notional_limit = common::Decimal("100"),
        .pending_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_oto(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingPegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingPegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingPegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOtoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderListOtoParams params{.symbol = "BNBUSDT",
                                    .working_type = OrderListOtoWorkingTypeEnum::Limit,
                                    .working_side = OrderListOtoWorkingSideEnum::Buy,
                                    .working_price = common::Decimal("1"),
                                    .working_quantity = common::Decimal("1"),
                                    .pending_type = OrderListOtoPendingTypeEnum::Limit,
                                    .pending_side = OrderListOtoPendingSideEnum::Buy,
                                    .pending_quantity = common::Decimal("1")};
    EXPECT_THROW((void)api.order_list_oto(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderListOtoco) {
    const std::string example =
        R"json({"orderListId":1,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"RumwQpBaDctlUu5jyG5rs0","transactionTime":1712291372842,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":6,"clientOrderId":"fM9Y4m23IFJVCQmIrlUmMK"},{"symbol":"LTCBTC","orderId":7,"clientOrderId":"6pcQbFIzTXGZQ1e2MkGDq4"},{"symbol":"LTCBTC","orderId":8,"clientOrderId":"r4JMv9cwAYYUwwBZfbussx"}],"orderReports":[{"symbol":"LTCBTC","orderId":6,"orderListId":1,"clientOrderId":"fM9Y4m23IFJVCQmIrlUmMK","transactTime":1712291372842,"price":"1.00000000","origQty":"1.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1712291372842,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":7,"orderListId":1,"clientOrderId":"6pcQbFIzTXGZQ1e2MkGDq4","transactTime":1712291372842,"price":"1.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"IOC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"6.00000000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":8,"orderListId":1,"clientOrderId":"r4JMv9cwAYYUwwBZfbussx","transactTime":1712291372842,"price":"3.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","workingTime":-1,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOtocoParams params{.symbol = "BNBUSDT",
                                      .working_type = OrderListOtocoWorkingTypeEnum::Limit,
                                      .working_side = OrderListOtocoWorkingSideEnum::Buy,
                                      .working_price = common::Decimal("1"),
                                      .working_quantity = common::Decimal("1"),
                                      .pending_side = OrderListOtocoPendingSideEnum::Buy,
                                      .pending_quantity = common::Decimal("1"),
                                      .pending_above_type =
                                          OrderListOtocoPendingAboveTypeEnum::StopLossLimit};
    const auto res = api.order_list_otoco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/orderList/otoco");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOtocoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":1,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"RumwQpBaDctlUu5jyG5rs0","transactionTime":1712291372842,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":6,"clientOrderId":"fM9Y4m23IFJVCQmIrlUmMK"},{"symbol":"LTCBTC","orderId":7,"clientOrderId":"6pcQbFIzTXGZQ1e2MkGDq4"},{"symbol":"LTCBTC","orderId":8,"clientOrderId":"r4JMv9cwAYYUwwBZfbussx"}],"orderReports":[{"symbol":"LTCBTC","orderId":6,"orderListId":1,"clientOrderId":"fM9Y4m23IFJVCQmIrlUmMK","transactTime":1712291372842,"price":"1.00000000","origQty":"1.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","workingTime":1712291372842,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":7,"orderListId":1,"clientOrderId":"6pcQbFIzTXGZQ1e2MkGDq4","transactTime":1712291372842,"price":"1.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"IOC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"6.00000000","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":8,"orderListId":1,"clientOrderId":"r4JMv9cwAYYUwwBZfbussx","transactTime":1712291372842,"price":"3.00000000","origQty":"5.00000000","executedQty":"0.00000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.00000000","status":"PENDING_NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","workingTime":-1,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderListOtocoParams params{
        .symbol = "BNBUSDT",
        .working_type = OrderListOtocoWorkingTypeEnum::Limit,
        .working_side = OrderListOtocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1"),
        .working_quantity = common::Decimal("1"),
        .pending_side = OrderListOtocoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1"),
        .pending_above_type = OrderListOtocoPendingAboveTypeEnum::StopLossLimit,
        .list_client_order_id = "RumwQpBaDctlUu5jyG5rs0",
        .new_order_resp_type = OrderListOtocoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderListOtocoSelfTradePreventionModeEnum::None_,
        .working_client_order_id = "workingOrder1",
        .working_iceberg_qty = common::Decimal("1"),
        .working_time_in_force = OrderListOtocoWorkingTimeInForceEnum::Gtc,
        .working_strategy_id = 1,
        .working_strategy_type = 1,
        .working_peg_price_type = OrderListOtocoWorkingPegPriceTypeEnum::PrimaryPeg,
        .working_peg_offset_type = OrderListOtocoWorkingPegOffsetTypeEnum::PriceLevel,
        .working_peg_offset_value = 1,
        .pending_above_client_order_id = "pendingAboveOrder1",
        .pending_above_price = common::Decimal("1"),
        .pending_above_stop_price = common::Decimal("1"),
        .pending_above_trailing_delta = common::Decimal("1"),
        .pending_above_iceberg_qty = common::Decimal("1"),
        .pending_above_time_in_force = OrderListOtocoPendingAboveTimeInForceEnum::Gtc,
        .pending_above_strategy_id = 1,
        .pending_above_strategy_type = 1,
        .pending_above_peg_price_type = OrderListOtocoPendingAbovePegPriceTypeEnum::PrimaryPeg,
        .pending_above_peg_offset_type = OrderListOtocoPendingAbovePegOffsetTypeEnum::PriceLevel,
        .pending_above_peg_offset_value = 1,
        .pending_below_type = OrderListOtocoPendingBelowTypeEnum::StopLoss,
        .pending_below_client_order_id = "pendingBelowOrder1",
        .pending_below_price = common::Decimal("1"),
        .pending_below_stop_price = common::Decimal("1"),
        .pending_below_trailing_delta = common::Decimal("1"),
        .pending_below_iceberg_qty = common::Decimal("1"),
        .pending_below_time_in_force = OrderListOtocoPendingBelowTimeInForceEnum::Gtc,
        .pending_below_strategy_id = 1,
        .pending_below_strategy_type = 1,
        .pending_below_peg_price_type = OrderListOtocoPendingBelowPegPriceTypeEnum::PrimaryPeg,
        .pending_below_peg_offset_type = OrderListOtocoPendingBelowPegOffsetTypeEnum::PriceLevel,
        .pending_below_peg_offset_value = 1,
        .working_quote_notional_limit = common::Decimal("100"),
        .pending_above_quote_notional_limit = common::Decimal("100"),
        .pending_below_quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_otoco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAbovePrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAbovePegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAbovePegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAbovePegOffsetValue="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowPegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowPegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowPegOffsetValue="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveQuoteNotionalLimit="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowQuoteNotionalLimit="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderListOtocoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderListOtocoParams params{.symbol = "BNBUSDT",
                                      .working_type = OrderListOtocoWorkingTypeEnum::Limit,
                                      .working_side = OrderListOtocoWorkingSideEnum::Buy,
                                      .working_price = common::Decimal("1"),
                                      .working_quantity = common::Decimal("1"),
                                      .pending_side = OrderListOtocoPendingSideEnum::Buy,
                                      .pending_quantity = common::Decimal("1"),
                                      .pending_above_type =
                                          OrderListOtocoPendingAboveTypeEnum::StopLossLimit};
    EXPECT_THROW((void)api.order_list_otoco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderOco) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"JYVpp3F0f5CAG15DhtrqLp","transactionTime":1563417480525,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos"},{"symbol":"LTCBTC","orderId":3,"clientOrderId":"xTXKaGYd4bluPVp78IVRvl"}],"orderReports":[{"symbol":"LTCBTC","orderId":2,"orderListId":0,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos","transactTime":1563417480525,"price":"0.000000","origQty":"0.624363","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS","side":"BUY","stopPrice":"0.960664","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":3,"orderListId":0,"clientOrderId":"xTXKaGYd4bluPVp78IVRvl","transactTime":1563417480525,"price":"0.036435","origQty":"0.624363","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","workingTime":1563417480525,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderOcoParams params{.symbol = "BNBUSDT",
                                .side = OrderOcoSideEnum::Buy,
                                .quantity = common::Decimal("1"),
                                .price = common::Decimal("1"),
                                .stop_price = common::Decimal("1")};
    const auto res = api.order_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/order/oco");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderOcoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"JYVpp3F0f5CAG15DhtrqLp","transactionTime":1563417480525,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos"},{"symbol":"LTCBTC","orderId":3,"clientOrderId":"xTXKaGYd4bluPVp78IVRvl"}],"orderReports":[{"symbol":"LTCBTC","orderId":2,"orderListId":0,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos","transactTime":1563417480525,"price":"0.000000","origQty":"0.624363","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS","side":"BUY","stopPrice":"0.960664","workingTime":-1,"selfTradePreventionMode":"NONE"},{"symbol":"LTCBTC","orderId":3,"orderListId":0,"clientOrderId":"xTXKaGYd4bluPVp78IVRvl","transactTime":1563417480525,"price":"0.036435","origQty":"0.624363","executedQty":"0.000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"LIMIT_MAKER","side":"BUY","workingTime":1563417480525,"selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderOcoParams params{
        .symbol = "BNBUSDT",
        .side = OrderOcoSideEnum::Buy,
        .quantity = common::Decimal("1"),
        .price = common::Decimal("1"),
        .stop_price = common::Decimal("1"),
        .list_client_order_id = "JYVpp3F0f5CAG15DhtrqLp",
        .limit_client_order_id = "limitOrder1",
        .limit_strategy_id = 1,
        .limit_strategy_type = 1,
        .limit_iceberg_qty = common::Decimal("1"),
        .trailing_delta = 1,
        .stop_client_order_id = "stopOrder1",
        .stop_strategy_id = 1,
        .stop_strategy_type = 1,
        .stop_limit_price = common::Decimal("1"),
        .stop_iceberg_qty = common::Decimal("1"),
        .stop_limit_time_in_force = OrderOcoStopLimitTimeInForceEnum::Gtc,
        .new_order_resp_type = OrderOcoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderOcoSelfTradePreventionModeEnum::None_,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_oco(params);
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
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("trailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopStrategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopStrategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopLimitPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopLimitTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderOcoParams params{.symbol = "BNBUSDT",
                                .side = OrderOcoSideEnum::Buy,
                                .quantity = common::Decimal("1"),
                                .price = common::Decimal("1"),
                                .stop_price = common::Decimal("1")};
    EXPECT_THROW((void)api.order_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OrderTest) {
    const std::string example =
        R"json({"standardCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"specialCommissionForOrder":{"maker":"0.05000000","taker":"0.06000000"},"taxCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.25000000"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderTestParams params{
        .symbol = "BNBUSDT", .side = OrderTestSideEnum::Buy, .type = OrderTestTypeEnum::Market};
    const auto res = api.order_test(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/order/test");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderTestWithOptionalParams) {
    const std::string example =
        R"json({"standardCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"specialCommissionForOrder":{"maker":"0.05000000","taker":"0.06000000"},"taxCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.25000000"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderTestParams params{
        .symbol = "BNBUSDT",
        .side = OrderTestSideEnum::Buy,
        .type = OrderTestTypeEnum::Market,
        .compute_commission_rates = false,
        .time_in_force = OrderTestTimeInForceEnum::Gtc,
        .quantity = common::Decimal("1"),
        .quote_order_qty = common::Decimal("1"),
        .price = common::Decimal("400"),
        .new_client_order_id = "myOrder1",
        .strategy_id = 1,
        .strategy_type = 1,
        .stop_price = common::Decimal("1"),
        .trailing_delta = 1,
        .iceberg_qty = common::Decimal("1"),
        .new_order_resp_type = OrderTestNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = OrderTestSelfTradePreventionModeEnum::None_,
        .peg_price_type = OrderTestPegPriceTypeEnum::PrimaryPeg,
        .peg_offset_value = 1,
        .peg_offset_type = OrderTestPegOffsetTypeEnum::PriceLevel,
        .quote_notional_limit = common::Decimal("100"),
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_test(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("computeCommissionRates="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteOrderQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("trailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("icebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pegPriceType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pegOffsetValue="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pegOffsetType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteNotionalLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OrderTestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderTestParams params{
        .symbol = "BNBUSDT", .side = OrderTestSideEnum::Buy, .type = OrderTestTypeEnum::Market};
    EXPECT_THROW((void)api.order_test(params), common::BadRequestError);
}

TEST(RestApiTradeApi, SorOrder) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","orderId":2,"orderListId":-1,"clientOrderId":"sBI1KM6nNtOfj5tccZSKly","transactTime":1689149087774,"price":"31000.00000000","origQty":"0.50000000","executedQty":"0.50000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"14000.00000000","status":"FILLED","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1689149087774,"fills":[{"matchType":"ONE_PARTY_TRADE_REPORT","price":"28000.00000000","qty":"0.50000000","commission":"0.00000000","commissionAsset":"BTC","tradeId":-1,"allocId":0}],"workingFloor":"SOR","selfTradePreventionMode":"NONE","usedSor":true,"stopPrice":"0.00000000","trailingDelta":10,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SorOrderParams params{.symbol = "BNBUSDT",
                                .side = SorOrderSideEnum::Buy,
                                .type = SorOrderTypeEnum::Market,
                                .quantity = common::Decimal("1")};
    const auto res = api.sor_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/sor/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SorOrderWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","orderId":2,"orderListId":-1,"clientOrderId":"sBI1KM6nNtOfj5tccZSKly","transactTime":1689149087774,"price":"31000.00000000","origQty":"0.50000000","executedQty":"0.50000000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"14000.00000000","status":"FILLED","timeInForce":"GTC","type":"LIMIT","side":"BUY","workingTime":1689149087774,"fills":[{"matchType":"ONE_PARTY_TRADE_REPORT","price":"28000.00000000","qty":"0.50000000","commission":"0.00000000","commissionAsset":"BTC","tradeId":-1,"allocId":0}],"workingFloor":"SOR","selfTradePreventionMode":"NONE","usedSor":true,"stopPrice":"0.00000000","trailingDelta":10,"icebergQty":"0.00000000","strategyId":1,"strategyType":1000000,"preventedMatchId":0,"preventedQuantity":"1.200000","trailingTime":-1,"pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SorOrderParams params{
        .symbol = "BNBUSDT",
        .side = SorOrderSideEnum::Buy,
        .type = SorOrderTypeEnum::Market,
        .quantity = common::Decimal("1"),
        .time_in_force = SorOrderTimeInForceEnum::Gtc,
        .price = common::Decimal("400"),
        .new_client_order_id = "myOrder1",
        .strategy_id = 1,
        .strategy_type = 1,
        .iceberg_qty = common::Decimal("1"),
        .new_order_resp_type = SorOrderNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = SorOrderSelfTradePreventionModeEnum::None_,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.sor_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("icebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SorOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SorOrderParams params{.symbol = "BNBUSDT",
                                .side = SorOrderSideEnum::Buy,
                                .type = SorOrderTypeEnum::Market,
                                .quantity = common::Decimal("1")};
    EXPECT_THROW((void)api.sor_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, SorOrderTest) {
    const std::string example =
        R"json({"standardCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"taxCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.25000000"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SorOrderTestParams params{.symbol = "BNBUSDT",
                                    .side = SorOrderTestSideEnum::Buy,
                                    .type = SorOrderTestTypeEnum::Market,
                                    .quantity = common::Decimal("1")};
    const auto res = api.sor_order_test(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/api/v3/sor/order/test");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SorOrderTestWithOptionalParams) {
    const std::string example =
        R"json({"standardCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"taxCommissionForOrder":{"maker":"0.00000112","taker":"0.00000114"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.25000000"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SorOrderTestParams params{
        .symbol = "BNBUSDT",
        .side = SorOrderTestSideEnum::Buy,
        .type = SorOrderTestTypeEnum::Market,
        .quantity = common::Decimal("1"),
        .compute_commission_rates = false,
        .time_in_force = SorOrderTestTimeInForceEnum::Gtc,
        .price = common::Decimal("400"),
        .new_client_order_id = "myOrder1",
        .strategy_id = 1,
        .strategy_type = 1,
        .iceberg_qty = common::Decimal("1"),
        .new_order_resp_type = SorOrderTestNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = SorOrderTestSelfTradePreventionModeEnum::None_,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.sor_order_test(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("computeCommissionRates="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("strategyType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("icebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SorOrderTestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SorOrderTestParams params{.symbol = "BNBUSDT",
                                    .side = SorOrderTestSideEnum::Buy,
                                    .type = SorOrderTestTypeEnum::Market,
                                    .quantity = common::Decimal("1")};
    EXPECT_THROW((void)api.sor_order_test(params), common::BadRequestError);
}
