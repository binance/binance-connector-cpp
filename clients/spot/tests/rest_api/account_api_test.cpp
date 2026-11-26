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
#include <binance/spot/rest_api/account_api.hpp>

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

AccountApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return AccountApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiAccountApi, AccountCommission) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","standardCommission":{"maker":"0.00000010","taker":"0.00000020","buyer":"0.00000030","seller":"0.00000040"},"specialCommission":{"maker":"0.01000000","taker":"0.02000000","buyer":"0.03000000","seller":"0.04000000"},"taxCommission":{"maker":"0.00000112","taker":"0.00000114","buyer":"0.00000118","seller":"0.00000116"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.75000000"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountCommissionParams params{.symbol = "BTCUSDT"};
    const auto res = api.account_commission(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/account/commission");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountCommissionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountCommissionParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.account_commission(params), common::BadRequestError);
}

TEST(RestApiAccountApi, AllOrderList) {
    const std::string example =
        R"json([{"orderListId":29,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"amEEAXryFzFwYF1FeRpUoZ","transactionTime":1565245913483,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"oD7aesZqjEGlZrbtRpy5zB"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllOrderListParams params{};
    const auto res = api.all_order_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/allOrderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AllOrderListWithOptionalParams) {
    const std::string example =
        R"json([{"orderListId":29,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"amEEAXryFzFwYF1FeRpUoZ","transactionTime":1565245913483,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"oD7aesZqjEGlZrbtRpy5zB"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllOrderListParams params{
        .from_id = 1,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.all_order_list(params);
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

TEST(RestApiAccountApi, AllOrderListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AllOrderListParams params{};
    EXPECT_THROW((void)api.all_order_list(params), common::BadRequestError);
}

TEST(RestApiAccountApi, AllOrders) {
    const std::string example =
        R"json([{"symbol":"LTCBTC","orderId":1,"orderListId":-1,"clientOrderId":"myOrder1","price":"0.1","origQty":"1.0","executedQty":"0.0","cummulativeQuoteQty":"0.0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","stopPrice":"0.00000000","icebergQty":"0.00000000","time":1499827319559,"updateTime":1499827319559,"isWorking":true,"origQuoteOrderQty":"0.000000","workingTime":1499827319559,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllOrdersParams params{.symbol = "LTCBTC"};
    const auto res = api.all_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/allOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AllOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"LTCBTC","orderId":1,"orderListId":-1,"clientOrderId":"myOrder1","price":"0.1","origQty":"1.0","executedQty":"0.0","cummulativeQuoteQty":"0.0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","stopPrice":"0.00000000","icebergQty":"0.00000000","time":1499827319559,"updateTime":1499827319559,"isWorking":true,"origQuoteOrderQty":"0.000000","workingTime":1499827319559,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllOrdersParams params{
        .symbol = "LTCBTC",
        .order_id = 1,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
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

TEST(RestApiAccountApi, AllOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AllOrdersParams params{.symbol = "LTCBTC"};
    EXPECT_THROW((void)api.all_orders(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetAccount) {
    const std::string example =
        R"json({"makerCommission":15,"takerCommission":15,"buyerCommission":0,"sellerCommission":0,"commissionRates":{"maker":"0.00150000","taker":"0.00150000","buyer":"0.00000000","seller":"0.00000000"},"canTrade":true,"canWithdraw":true,"canDeposit":true,"brokered":false,"requireSelfTradePrevention":false,"preventSor":false,"updateTime":123456789,"accountType":"SPOT","balances":[{"asset":"BTC","free":"4723846.89208129","locked":"0.00000000"},{"asset":"LTC","free":"4763368.68006011","locked":"0.00000000"}],"permissions":["SPOT"],"uid":354937868})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAccountParams params{};
    const auto res = api.get_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetAccountWithOptionalParams) {
    const std::string example =
        R"json({"makerCommission":15,"takerCommission":15,"buyerCommission":0,"sellerCommission":0,"commissionRates":{"maker":"0.00150000","taker":"0.00150000","buyer":"0.00000000","seller":"0.00000000"},"canTrade":true,"canWithdraw":true,"canDeposit":true,"brokered":false,"requireSelfTradePrevention":false,"preventSor":false,"updateTime":123456789,"accountType":"SPOT","balances":[{"asset":"BTC","free":"4723846.89208129","locked":"0.00000000"},{"asset":"LTC","free":"4763368.68006011","locked":"0.00000000"}],"permissions":["SPOT"],"uid":354937868})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAccountParams params{
        .omit_zero_balances = false,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.get_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("omitZeroBalances="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetAccountParams params{};
    EXPECT_THROW((void)api.get_account(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetOpenOrders) {
    const std::string example =
        R"json([{"symbol":"LTCBTC","orderId":1,"orderListId":-1,"clientOrderId":"myOrder1","price":"0.1","origQty":"1.0","executedQty":"0.0","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","stopPrice":"0.00000000","icebergQty":"0.00000000","time":1499827319559,"updateTime":1499827319559,"isWorking":true,"workingTime":1499827319559,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOpenOrdersParams params{};
    const auto res = api.get_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"LTCBTC","orderId":1,"orderListId":-1,"clientOrderId":"myOrder1","price":"0.1","origQty":"1.0","executedQty":"0.0","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","stopPrice":"0.00000000","icebergQty":"0.00000000","time":1499827319559,"updateTime":1499827319559,"isWorking":true,"workingTime":1499827319559,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOpenOrdersParams params{
        .symbol = "LTCBTC",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.get_open_orders(params);
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

TEST(RestApiAccountApi, GetOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOpenOrdersParams params{};
    EXPECT_THROW((void)api.get_open_orders(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetOrder) {
    const std::string example =
        R"json({"symbol":"LTCBTC","orderId":1,"orderListId":-1,"clientOrderId":"myOrder1","price":"0.1","origQty":"1.0","executedQty":"0.0","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","stopPrice":"0.00000000","icebergQty":"0.00000000","time":1499827319559,"updateTime":1499827319559,"isWorking":true,"workingTime":1499827319559,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderParams params{.symbol = "LTCBTC"};
    const auto res = api.get_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetOrderWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"LTCBTC","orderId":1,"orderListId":-1,"clientOrderId":"myOrder1","price":"0.1","origQty":"1.0","executedQty":"0.0","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"0.0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","stopPrice":"0.00000000","icebergQty":"0.00000000","time":1499827319559,"updateTime":1499827319559,"isWorking":true,"workingTime":1499827319559,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderParams params{
        .symbol = "LTCBTC",
        .order_id = 1,
        .orig_client_order_id = "myOrder1",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.get_order(params);
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

TEST(RestApiAccountApi, GetOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOrderParams params{.symbol = "LTCBTC"};
    EXPECT_THROW((void)api.get_order(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetOrderList) {
    const std::string example =
        R"json({"orderListId":27,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"h2USkA5YQpaXHPIrkd96xE","transactionTime":1565245656253,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"qD1gy3kc3Gx0rihm9Y3xwS"},{"symbol":"LTCBTC","orderId":5,"clientOrderId":"ARzZ9I00CPM8i3NhmU9Ega"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderListParams params{};
    const auto res = api.get_order_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/orderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetOrderListWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":27,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"h2USkA5YQpaXHPIrkd96xE","transactionTime":1565245656253,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"qD1gy3kc3Gx0rihm9Y3xwS"},{"symbol":"LTCBTC","orderId":5,"clientOrderId":"ARzZ9I00CPM8i3NhmU9Ega"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderListParams params{
        .order_list_id = 27,
        .orig_client_order_id = "1",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.get_order_list(params);
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

TEST(RestApiAccountApi, GetOrderListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOrderListParams params{};
    EXPECT_THROW((void)api.get_order_list(params), common::BadRequestError);
}

TEST(RestApiAccountApi, MyAllocations) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","allocationId":0,"allocationType":"SOR","orderId":1,"orderListId":-1,"price":"1.00000000","qty":"5.00000000","quoteQty":"5.00000000","commission":"0.00000000","commissionAsset":"BTC","time":1687506878118,"isBuyer":true,"isMaker":false,"isAllocator":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MyAllocationsParams params{.symbol = "BTCUSDT"};
    const auto res = api.my_allocations(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/myAllocations");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, MyAllocationsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","allocationId":0,"allocationType":"SOR","orderId":1,"orderListId":-1,"price":"1.00000000","qty":"5.00000000","quoteQty":"5.00000000","commission":"0.00000000","commissionAsset":"BTC","time":1687506878118,"isBuyer":true,"isMaker":false,"isAllocator":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MyAllocationsParams params{
        .symbol = "BTCUSDT",
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .from_allocation_id = 0,
        .limit = 1,
        .order_id = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.my_allocations(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAllocationId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, MyAllocationsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MyAllocationsParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.my_allocations(params), common::BadRequestError);
}

TEST(RestApiAccountApi, MyFilters) {
    const std::string example =
        R"json({"exchangeFilters":[{"filterType":"EXCHANGE_MAX_NUM_ORDERS","maxNumOrders":1000}],"symbolFilters":[{"filterType":"PRICE_FILTER","priceExponent":8,"minPrice":"0.00000100","maxPrice":"100000.00000000","tickSize":"0.00000100"}],"assetFilters":[{"filterType":"MAX_ASSET","qtyExponent":8,"limit":"100.00000000","asset":"BNB"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":321}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MyFiltersParams params{.symbol = "BNBUSDT"};
    const auto res = api.my_filters(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/myFilters");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, MyFiltersWithOptionalParams) {
    const std::string example =
        R"json({"exchangeFilters":[{"filterType":"EXCHANGE_MAX_NUM_ORDERS","maxNumOrders":1000}],"symbolFilters":[{"filterType":"PRICE_FILTER","priceExponent":8,"minPrice":"0.00000100","maxPrice":"100000.00000000","tickSize":"0.00000100"}],"assetFilters":[{"filterType":"MAX_ASSET","qtyExponent":8,"limit":"100.00000000","asset":"BNB"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":321}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MyFiltersParams params{
        .symbol = "BNBUSDT",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.my_filters(params);
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

TEST(RestApiAccountApi, MyFiltersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MyFiltersParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.my_filters(params), common::BadRequestError);
}

TEST(RestApiAccountApi, MyPreventedMatches) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","preventedMatchId":1,"takerOrderId":5,"makerSymbol":"BTCUSDT","makerOrderId":3,"tradeGroupId":1,"selfTradePreventionMode":"EXPIRE_MAKER","price":"1.100000","makerPreventedQuantity":"1.300000","transactTime":1669101687094}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MyPreventedMatchesParams params{.symbol = "BTCUSDT"};
    const auto res = api.my_prevented_matches(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/myPreventedMatches");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, MyPreventedMatchesWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","preventedMatchId":1,"takerOrderId":5,"makerSymbol":"BTCUSDT","makerOrderId":3,"tradeGroupId":1,"selfTradePreventionMode":"EXPIRE_MAKER","price":"1.100000","makerPreventedQuantity":"1.300000","transactTime":1669101687094}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MyPreventedMatchesParams params{
        .symbol = "BTCUSDT",
        .prevented_match_id = 1,
        .order_id = 1,
        .from_prevented_match_id = 1,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.my_prevented_matches(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("preventedMatchId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromPreventedMatchId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, MyPreventedMatchesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MyPreventedMatchesParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.my_prevented_matches(params), common::BadRequestError);
}

TEST(RestApiAccountApi, MyTrades) {
    const std::string example =
        R"json([{"symbol":"BNBBTC","id":28457,"orderId":100234,"orderListId":-1,"price":"4.00000100","qty":"12.00000000","quoteQty":"48.000012","commission":"10.10000000","commissionAsset":"BNB","time":1499865549590,"isBuyer":true,"isMaker":false,"isBestMatch":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MyTradesParams params{.symbol = "BNBBTC"};
    const auto res = api.my_trades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/myTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, MyTradesWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BNBBTC","id":28457,"orderId":100234,"orderListId":-1,"price":"4.00000100","qty":"12.00000000","quoteQty":"48.000012","commission":"10.10000000","commissionAsset":"BNB","time":1499865549590,"isBuyer":true,"isMaker":false,"isBestMatch":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MyTradesParams params{
        .symbol = "BNBBTC",
        .order_id = 100234,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .from_id = 1,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.my_trades(params);
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

TEST(RestApiAccountApi, MyTradesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MyTradesParams params{.symbol = "BNBBTC"};
    EXPECT_THROW((void)api.my_trades(params), common::BadRequestError);
}

TEST(RestApiAccountApi, OpenOrderList) {
    const std::string example =
        R"json([{"orderListId":31,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"wuB13fmulKj3YjdqWEcsnp","transactionTime":1565246080644,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"r3EH2N76dHfLoSZWIUw1bT"},{"symbol":"LTCBTC","orderId":5,"clientOrderId":"Cv1SnyPD3qhqpbjpYEHbd2"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OpenOrderListParams params{};
    const auto res = api.open_order_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/openOrderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, OpenOrderListWithOptionalParams) {
    const std::string example =
        R"json([{"orderListId":31,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"wuB13fmulKj3YjdqWEcsnp","transactionTime":1565246080644,"symbol":"LTCBTC","orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"r3EH2N76dHfLoSZWIUw1bT"},{"symbol":"LTCBTC","orderId":5,"clientOrderId":"Cv1SnyPD3qhqpbjpYEHbd2"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OpenOrderListParams params{
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.open_order_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, OpenOrderListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OpenOrderListParams params{};
    EXPECT_THROW((void)api.open_order_list(params), common::BadRequestError);
}

TEST(RestApiAccountApi, OrderAmendments) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","orderId":9,"executionId":22,"origClientOrderId":"W0fJ9fiLKHOJutovPK3oJp","newClientOrderId":"UQ1Np3bmQ71jJzsSDW9Vpi","origQty":"5.00000000","newQty":"4.00000000","time":1741669661670}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderAmendmentsParams params{.symbol = "BTCUSDT", .order_id = 9};
    const auto res = api.order_amendments(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/order/amendments");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, OrderAmendmentsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","orderId":9,"executionId":22,"origClientOrderId":"W0fJ9fiLKHOJutovPK3oJp","newClientOrderId":"UQ1Np3bmQ71jJzsSDW9Vpi","origQty":"5.00000000","newQty":"4.00000000","time":1741669661670}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderAmendmentsParams params{
        .symbol = "BTCUSDT",
        .order_id = 9,
        .from_execution_id = 22,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_amendments(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromExecutionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, OrderAmendmentsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderAmendmentsParams params{.symbol = "BTCUSDT", .order_id = 9};
    EXPECT_THROW((void)api.order_amendments(params), common::BadRequestError);
}

TEST(RestApiAccountApi, RateLimitOrder) {
    const std::string example =
        R"json([{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RateLimitOrderParams params{};
    const auto res = api.rate_limit_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/rateLimit/order");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, RateLimitOrderWithOptionalParams) {
    const std::string example =
        R"json([{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RateLimitOrderParams params{
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.rate_limit_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, RateLimitOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RateLimitOrderParams params{};
    EXPECT_THROW((void)api.rate_limit_order(params), common::BadRequestError);
}
