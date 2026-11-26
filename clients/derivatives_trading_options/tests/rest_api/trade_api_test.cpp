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
#include <binance/derivatives_trading_options/rest_api/trade_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_options::rest_api;
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
        R"json([{"id":4611875134427365000,"tradeId":239,"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","fee":"-1.04378629","realizedProfit":"0.00000000","side":"BUY","type":"LIMIT","liquidity":"TAKER","time":1592465880683,"priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountTradeListParams params{.symbol = "BTC-200730-9000-C"};
    const auto res = api.account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/userTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AccountTradeListWithOptionalParams) {
    const std::string example =
        R"json([{"id":4611875134427365000,"tradeId":239,"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","fee":"-1.04378629","realizedProfit":"0.00000000","side":"BUY","type":"LIMIT","liquidity":"TAKER","time":1592465880683,"priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountTradeListParams params{
        .symbol = "BTC-200730-9000-C",
        .from_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.account_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, AccountTradeListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountTradeListParams params{.symbol = "BTC-200730-9000-C"};
    EXPECT_THROW((void)api.account_trade_list(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelAllOptionOrdersByUnderlying) {
    const std::string example = R"json({"code":0,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllOptionOrdersByUnderlyingParams params{.underlying = "BTCUSDT"};
    const auto res = api.cancel_all_option_orders_by_underlying(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/eapi/v1/allOpenOrdersByUnderlying");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllOptionOrdersByUnderlyingWithOptionalParams) {
    const std::string example = R"json({"code":0,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllOptionOrdersByUnderlyingParams params{
        .underlying = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_option_orders_by_underlying(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllOptionOrdersByUnderlyingBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllOptionOrdersByUnderlyingParams params{.underlying = "BTCUSDT"};
    EXPECT_THROW((void)api.cancel_all_option_orders_by_underlying(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelAllOptionOrdersOnSpecificSymbol) {
    const std::string example = R"json({"code":"0","msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllOptionOrdersOnSpecificSymbolParams params{.symbol = "BTC-200730-9000-C"};
    const auto res = api.cancel_all_option_orders_on_specific_symbol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/eapi/v1/allOpenOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelAllOptionOrdersOnSpecificSymbolWithOptionalParams) {
    const std::string example = R"json({"code":"0","msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelAllOptionOrdersOnSpecificSymbolParams params{
        .symbol = "BTC-200730-9000-C",
        .recv_window = 5000,
    };
    const auto res = api.cancel_all_option_orders_on_specific_symbol(params);
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

TEST(RestApiTradeApi, CancelAllOptionOrdersOnSpecificSymbolBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelAllOptionOrdersOnSpecificSymbolParams params{.symbol = "BTC-200730-9000-C"};
    EXPECT_THROW((void)api.cancel_all_option_orders_on_specific_symbol(params),
                 common::BadRequestError);
}

TEST(RestApiTradeApi, CancelMultipleOptionOrders) {
    const std::string example =
        R"json([{"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","fee":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"createTime":1592465880683,"updateTime":1566818724722,"status":"ACCEPTED","avgPrice":"0","clientOrderId":"","priceScale":3,"quantityScale":4,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"source":"API","selfTradePreventionMode":"EXPIRE_MAKER"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMultipleOptionOrdersParams params{.symbol = "BTC-200730-9000-C"};
    const auto res = api.cancel_multiple_option_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/eapi/v1/batchOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelMultipleOptionOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","fee":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"createTime":1592465880683,"updateTime":1566818724722,"status":"ACCEPTED","avgPrice":"0","clientOrderId":"","priceScale":3,"quantityScale":4,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"source":"API","selfTradePreventionMode":"EXPIRE_MAKER"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelMultipleOptionOrdersParams params{
        .symbol = "BTC-200730-9000-C",
        .order_ids = std::vector<std::int64_t>{},
        .client_order_ids = std::vector<std::string>{},
        .recv_window = 5000,
    };
    const auto res = api.cancel_multiple_option_orders(params);
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

TEST(RestApiTradeApi, CancelMultipleOptionOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelMultipleOptionOrdersParams params{.symbol = "BTC-200730-9000-C"};
    EXPECT_THROW((void)api.cancel_multiple_option_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, PlaceMultipleOrders) {
    const std::string example =
        R"json([{"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","fee":0,"side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"postOnly":false,"createTime":1592465880683,"updateTime":1566818724722,"status":"NEW","avgPrice":"0","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER","source":"API"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceMultipleOrdersParams params{
        .orders = std::vector<PlaceMultipleOrdersOrdersParameterInner>{}};
    const auto res = api.place_multiple_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/eapi/v1/batchOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orders="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceMultipleOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","fee":0,"side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"postOnly":false,"createTime":1592465880683,"updateTime":1566818724722,"status":"NEW","avgPrice":"0","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER","source":"API"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceMultipleOrdersParams params{
        .orders = std::vector<PlaceMultipleOrdersOrdersParameterInner>{},
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
        .orders = std::vector<PlaceMultipleOrdersOrdersParameterInner>{}};
    EXPECT_THROW((void)api.place_multiple_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, CancelOptionOrder) {
    const std::string example =
        R"json({"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"createDate":1592465880683,"updateTime":1566818724722,"status":"ACCEPTED","avgPrice":"0","source":"API","clientOrderId":"","priceScale":4,"quantityScale":4,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelOptionOrderParams params{.symbol = "BTC-200730-9000-C"};
    const auto res = api.cancel_option_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/eapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelOptionOrderWithOptionalParams) {
    const std::string example =
        R"json({"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"createDate":1592465880683,"updateTime":1566818724722,"status":"ACCEPTED","avgPrice":"0","source":"API","clientOrderId":"","priceScale":4,"quantityScale":4,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelOptionOrderParams params{
        .symbol = "BTC-200730-9000-C",
        .order_id = 4611875134427365000,
        .client_order_id = "10000",
        .recv_window = 5000,
    };
    const auto res = api.cancel_option_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CancelOptionOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelOptionOrderParams params{.symbol = "BTC-200730-9000-C"};
    EXPECT_THROW((void)api.cancel_option_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, NewOrder) {
    const std::string example =
        R"json({"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","fee":0,"side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"postOnly":false,"createTime":1592465880683,"updateTime":1566818724722,"status":"NEW","avgPrice":"0","source":"API","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewOrderParams params{.symbol = "BTC-200730-9000-C",
                                .side = NewOrderSideEnum::Buy,
                                .type = NewOrderTypeEnum::Limit,
                                .quantity = common::Decimal("1.0")};
    const auto res = api.new_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/eapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewOrderWithOptionalParams) {
    const std::string example =
        R"json({"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","fee":0,"side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"postOnly":false,"createTime":1592465880683,"updateTime":1566818724722,"status":"NEW","avgPrice":"0","source":"API","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewOrderParams params{
        .symbol = "BTC-200730-9000-C",
        .side = NewOrderSideEnum::Buy,
        .type = NewOrderTypeEnum::Limit,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .time_in_force = NewOrderTimeInForceEnum::Gtc,
        .reduce_only = false,
        .post_only = false,
        .new_order_resp_type = NewOrderNewOrderRespTypeEnum::Ack,
        .client_order_id = "1",
        .is_mmp = true,
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
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("reduceOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("postOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isMmp="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, NewOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewOrderParams params{.symbol = "BTC-200730-9000-C",
                                .side = NewOrderSideEnum::Buy,
                                .type = NewOrderTypeEnum::Limit,
                                .quantity = common::Decimal("1.0")};
    EXPECT_THROW((void)api.new_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QuerySingleOrder) {
    const std::string example =
        R"json({"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"postOnly":false,"createTime":1592465880683,"updateTime":1566818724722,"status":"NEW","avgPrice":"0","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySingleOrderParams params{.symbol = "BTC-200730-9000-C"};
    const auto res = api.query_single_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QuerySingleOrderWithOptionalParams) {
    const std::string example =
        R"json({"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"postOnly":false,"createTime":1592465880683,"updateTime":1566818724722,"status":"NEW","avgPrice":"0","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySingleOrderParams params{
        .symbol = "BTC-200730-9000-C",
        .order_id = 4611875134427365000,
        .client_order_id = "abc123",
        .recv_window = 5000,
    };
    const auto res = api.query_single_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QuerySingleOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySingleOrderParams params{.symbol = "BTC-200730-9000-C"};
    EXPECT_THROW((void)api.query_single_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, OptionPositionInformation) {
    const std::string example =
        R"json([{"entryPrice":"1000","symbol":"BTC-200730-9000-C","side":"SHORT","quantity":"-0.1","markValue":"105.00138","unrealizedPNL":"-5.00138","markPrice":"1050.0138","strikePrice":"9000","expiryDate":1593511200000,"priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","time":1762872654561,"bidQuantity":"0.0000","askQuantity":"0.0000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionPositionInformationParams params{};
    const auto res = api.option_position_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/position");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, OptionPositionInformationWithOptionalParams) {
    const std::string example =
        R"json([{"entryPrice":"1000","symbol":"BTC-200730-9000-C","side":"SHORT","quantity":"-0.1","markValue":"105.00138","unrealizedPNL":"-5.00138","markPrice":"1050.0138","strikePrice":"9000","expiryDate":1593511200000,"priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","time":1762872654561,"bidQuantity":"0.0000","askQuantity":"0.0000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionPositionInformationParams params{
        .symbol = "BTC-200730-9000-C",
        .recv_window = 5000,
    };
    const auto res = api.option_position_information(params);
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

TEST(RestApiTradeApi, OptionPositionInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionPositionInformationParams params{};
    EXPECT_THROW((void)api.option_position_information(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCurrentOpenOptionOrders) {
    const std::string example =
        R"json([{"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"createTime":1592465880683,"updateTime":1592465880683,"status":"NEW","avgPrice":"0","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentOpenOptionOrdersParams params{};
    const auto res = api.query_current_open_option_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentOpenOptionOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"createTime":1592465880683,"updateTime":1592465880683,"status":"NEW","avgPrice":"0","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false,"selfTradePreventionMode":"EXPIRE_MAKER"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentOpenOptionOrdersParams params{
        .symbol = "BTC-200730-9000-C",
        .order_id = 4611875134427365000,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.query_current_open_option_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentOpenOptionOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentOpenOptionOrdersParams params{};
    EXPECT_THROW((void)api.query_current_open_option_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryOptionOrderHistory) {
    const std::string example =
        R"json([{"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"createTime":1592465880683,"updateTime":1592465880683,"status":"ACCEPTED","avgPrice":"0","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOptionOrderHistoryParams params{.symbol = "BTC-200730-9000-C"};
    const auto res = api.query_option_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/historyOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryOptionOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"orderId":4611875134427365000,"symbol":"BTC-200730-9000-C","price":"100","quantity":"1","executedQty":"0","side":"BUY","type":"LIMIT","timeInForce":"GTC","reduceOnly":false,"createTime":1592465880683,"updateTime":1592465880683,"status":"ACCEPTED","avgPrice":"0","clientOrderId":"","priceScale":2,"quantityScale":2,"optionSide":"CALL","quoteAsset":"USDT","mmp":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOptionOrderHistoryParams params{
        .symbol = "BTC-200730-9000-C",
        .order_id = 4611875134427365000,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.query_option_order_history(params);
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

TEST(RestApiTradeApi, QueryOptionOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryOptionOrderHistoryParams params{.symbol = "BTC-200730-9000-C"};
    EXPECT_THROW((void)api.query_option_order_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, TradfiOptionsContract) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TradfiOptionsContractParams params{};
    const auto res = api.tradfi_options_contract(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/eapi/v1/stock/contract");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, TradfiOptionsContractWithOptionalParams) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TradfiOptionsContractParams params{
        .recv_window = 5000,
    };
    const auto res = api.tradfi_options_contract(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, TradfiOptionsContractBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TradfiOptionsContractParams params{};
    EXPECT_THROW((void)api.tradfi_options_contract(params), common::BadRequestError);
}

TEST(RestApiTradeApi, UserCommission) {
    const std::string example =
        R"json({"commissions":[{"underlying":"BTCUSDT","makerFee":"0.000240","takerFee":"0.000240"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserCommissionParams params{};
    const auto res = api.user_commission(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/commission");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UserCommissionWithOptionalParams) {
    const std::string example =
        R"json({"commissions":[{"underlying":"BTCUSDT","makerFee":"0.000240","takerFee":"0.000240"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserCommissionParams params{
        .recv_window = 5000,
    };
    const auto res = api.user_commission(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UserCommissionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UserCommissionParams params{};
    EXPECT_THROW((void)api.user_commission(params), common::BadRequestError);
}

TEST(RestApiTradeApi, UserExerciseRecord) {
    const std::string example =
        R"json([{"id":"1125899906842624042","currency":"USDT","symbol":"BTC-220721-25000-C","exercisePrice":"25000.00000000","quantity":"1.00000000","amount":"0.00000000","fee":"0.00000000","createDate":1658361600000,"priceScale":2,"quantityScale":2,"optionSide":"CALL","positionSide":"LONG","quoteAsset":"USDT"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserExerciseRecordParams params{};
    const auto res = api.user_exercise_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/exerciseRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UserExerciseRecordWithOptionalParams) {
    const std::string example =
        R"json([{"id":"1125899906842624042","currency":"USDT","symbol":"BTC-220721-25000-C","exercisePrice":"25000.00000000","quantity":"1.00000000","amount":"0.00000000","fee":"0.00000000","createDate":1658361600000,"priceScale":2,"quantityScale":2,"optionSide":"CALL","positionSide":"LONG","quoteAsset":"USDT"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserExerciseRecordParams params{
        .symbol = "BTC-200730-9000-C",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.user_exercise_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, UserExerciseRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UserExerciseRecordParams params{};
    EXPECT_THROW((void)api.user_exercise_record(params), common::BadRequestError);
}
