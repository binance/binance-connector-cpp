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
#include <binance/spot/websocket_api/account_api.hpp>

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

AccountApi api_for(const MockWsServer& server) {
    common::WebsocketApiConfig cfg;
    cfg.url = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    cfg.proxy_from_env = false;
    auto client = std::make_shared<common::WebsocketApi>(std::move(cfg));
    client->connect();
    return AccountApi(std::move(client));
}

boost::json::object first_request(const MockWsServer& server) {
    return boost::json::parse(server.sessions().front().received.front()).as_object();
}

} // namespace

TEST(WebsocketApiAccountApi, AccountCommission) {
    MockWsServer server(reply(
        R"json({"id":"d3df8a61-98ea-4fe0-8f4e-0fcea5d418b0","status":200,"result":{"symbol":"BTCUSDT","standardCommission":{"maker":"0.00000010","taker":"0.00000020","buyer":"0.00000030","seller":"0.00000040"},"specialCommission":{"maker":"0.01000000","taker":"0.02000000","buyer":"0.03000000","seller":"0.04000000"},"taxCommission":{"maker":"0.00000112","taker":"0.00000114","buyer":"0.00000118","seller":"0.00000116"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.75000000"}},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const AccountCommissionParams params{.symbol = "BNBUSDT"};
    const auto res = api.account_commission(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.commission");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountCommissionWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"d3df8a61-98ea-4fe0-8f4e-0fcea5d418b0","status":200,"result":{"symbol":"BTCUSDT","standardCommission":{"maker":"0.00000010","taker":"0.00000020","buyer":"0.00000030","seller":"0.00000040"},"specialCommission":{"maker":"0.01000000","taker":"0.02000000","buyer":"0.03000000","seller":"0.04000000"},"taxCommission":{"maker":"0.00000112","taker":"0.00000114","buyer":"0.00000118","seller":"0.00000116"},"discount":{"enabledForAccount":true,"enabledForSymbol":true,"discountAsset":"BNB","discount":"0.75000000"}},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const AccountCommissionParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
    };
    const auto res = api.account_commission(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.commission");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountCommissionErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const AccountCommissionParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.account_commission(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, AccountRateLimitsOrders) {
    MockWsServer server(reply(
        R"json({"id":"d3783d8d-f8d1-4d2c-b8a0-b7596af5a664","status":200,"result":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":0},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":0}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":40}]})json"));
    const auto api = api_for(server);
    const AccountRateLimitsOrdersParams params{};
    const auto res = api.account_rate_limits_orders(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.rateLimits.orders");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountRateLimitsOrdersWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"d3783d8d-f8d1-4d2c-b8a0-b7596af5a664","status":200,"result":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":0},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000,"count":0}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":40}]})json"));
    const auto api = api_for(server);
    const AccountRateLimitsOrdersParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.account_rate_limits_orders(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.rateLimits.orders");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountRateLimitsOrdersErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const AccountRateLimitsOrdersParams params{};
    EXPECT_THROW((void)api.account_rate_limits_orders(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, AccountStatus) {
    MockWsServer server(reply(
        R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":{"makerCommission":15,"takerCommission":15,"buyerCommission":0,"sellerCommission":0,"canTrade":true,"canWithdraw":true,"canDeposit":true,"commissionRates":{"maker":"0.00150000","taker":"0.00150000","buyer":"0.00000000","seller":"0.00000000"},"brokered":false,"requireSelfTradePrevention":false,"preventSor":false,"updateTime":1660801833000,"accountType":"SPOT","balances":[{"asset":"BNB","free":"0.00000000","locked":"0.00000000"},{"asset":"BTC","free":"1.3447112","locked":"0.08600000"},{"asset":"USDT","free":"1021.21000000","locked":"0.00000000"}],"permissions":["SPOT"],"uid":354937868},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const AccountStatusParams params{};
    const auto res = api.account_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.status");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountStatusWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":{"makerCommission":15,"takerCommission":15,"buyerCommission":0,"sellerCommission":0,"canTrade":true,"canWithdraw":true,"canDeposit":true,"commissionRates":{"maker":"0.00150000","taker":"0.00150000","buyer":"0.00000000","seller":"0.00000000"},"brokered":false,"requireSelfTradePrevention":false,"preventSor":false,"updateTime":1660801833000,"accountType":"SPOT","balances":[{"asset":"BNB","free":"0.00000000","locked":"0.00000000"},{"asset":"BTC","free":"1.3447112","locked":"0.08600000"},{"asset":"USDT","free":"1021.21000000","locked":"0.00000000"}],"permissions":["SPOT"],"uid":354937868},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const AccountStatusParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .omit_zero_balances = false,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.account_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.status");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("omitZeroBalances"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountStatusErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const AccountStatusParams params{};
    EXPECT_THROW((void)api.account_status(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, AllOrderLists) {
    MockWsServer server(reply(
        R"json({"id":"8617b7b3-1b3d-4dec-94cd-eefd929b8ceb","status":200,"result":[{"orderListId":1274512,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"08985fedd9ea2cf6b28996","transactionTime":1660801713793,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569138901,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU"},{"symbol":"BTCUSDT","orderId":12569138902,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us"}]}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const AllOrderListsParams params{};
    const auto res = api.all_order_lists(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "allOrderLists");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, AllOrderListsWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"8617b7b3-1b3d-4dec-94cd-eefd929b8ceb","status":200,"result":[{"orderListId":1274512,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"08985fedd9ea2cf6b28996","transactionTime":1660801713793,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569138901,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU"},{"symbol":"BTCUSDT","orderId":12569138902,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us"}]}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const AllOrderListsParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .from_id = 1,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.all_order_lists(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "allOrderLists");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("fromId"));
    EXPECT_TRUE(sent.contains("startTime"));
    EXPECT_TRUE(sent.contains("endTime"));
    EXPECT_TRUE(sent.contains("limit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, AllOrderListsErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const AllOrderListsParams params{};
    EXPECT_THROW((void)api.all_order_lists(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, AllOrders) {
    MockWsServer server(reply(
        R"json({"id":"734235c2-13d2-4574-be68-723e818c08f3","status":200,"result":[{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"4d96324ff9d44481926157","price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00847000","cummulativeQuoteQty":"198.33521500","status":"FILLED","timeInForce":"GTC","type":"LIMIT","side":"SELL","time":1660801715639,"updateTime":1660801717945,"isWorking":true,"workingTime":1660801715639,"origQuoteOrderQty":"0.000000","selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","icebergQty":"0.00000000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const AllOrdersParams params{.symbol = "BNBUSDT"};
    const auto res = api.all_orders(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "allOrders");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, AllOrdersWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"734235c2-13d2-4574-be68-723e818c08f3","status":200,"result":[{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"4d96324ff9d44481926157","price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00847000","cummulativeQuoteQty":"198.33521500","status":"FILLED","timeInForce":"GTC","type":"LIMIT","side":"SELL","time":1660801715639,"updateTime":1660801717945,"isWorking":true,"workingTime":1660801715639,"origQuoteOrderQty":"0.000000","selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","icebergQty":"0.00000000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const AllOrdersParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .order_id = 1,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.all_orders(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "allOrders");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("orderId"));
    EXPECT_TRUE(sent.contains("startTime"));
    EXPECT_TRUE(sent.contains("endTime"));
    EXPECT_TRUE(sent.contains("limit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, AllOrdersErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const AllOrdersParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.all_orders(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, MyAllocations) {
    MockWsServer server(reply(
        R"json({"id":"g4ce6a53-a39d-4f71-823b-4ab5r391d6y8","status":200,"result":[{"symbol":"BTCUSDT","allocationId":0,"allocationType":"SOR","orderId":500,"orderListId":-1,"price":"1.00000000","qty":"0.10000000","quoteQty":"0.10000000","commission":"0.00000000","commissionAsset":"BTC","time":1687319487614,"isBuyer":false,"isMaker":false,"isAllocator":false}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const MyAllocationsParams params{.symbol = "BNBUSDT"};
    const auto res = api.my_allocations(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "myAllocations");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, MyAllocationsWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"g4ce6a53-a39d-4f71-823b-4ab5r391d6y8","status":200,"result":[{"symbol":"BTCUSDT","allocationId":0,"allocationType":"SOR","orderId":500,"orderListId":-1,"price":"1.00000000","qty":"0.10000000","quoteQty":"0.10000000","commission":"0.00000000","commissionAsset":"BTC","time":1687319487614,"isBuyer":false,"isMaker":false,"isAllocator":false}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const MyAllocationsParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .from_allocation_id = 1,
        .limit = 1,
        .order_id = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.my_allocations(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "myAllocations");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("startTime"));
    EXPECT_TRUE(sent.contains("endTime"));
    EXPECT_TRUE(sent.contains("fromAllocationId"));
    EXPECT_TRUE(sent.contains("limit"));
    EXPECT_TRUE(sent.contains("orderId"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, MyAllocationsErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const MyAllocationsParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.my_allocations(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, MyFilters) {
    MockWsServer server(reply(
        R"json({"id":"1758009606869","status":200,"result":{"exchangeFilters":[{"filterType":"EXCHANGE_MAX_NUM_ORDERS","maxNumOrders":1000}],"symbolFilters":[{"filterType":"PRICE_FILTER","priceExponent":8,"minPrice":"0.00000100","maxPrice":"100000.00000000","tickSize":"0.00000100"}],"assetFilters":[{"filterType":"MAX_ASSET","qtyExponent":8,"limit":"1000000.00000000","asset":"JPY"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":40}]}})json"));
    const auto api = api_for(server);
    const MyFiltersParams params{.symbol = "BNBUSDT"};
    const auto res = api.my_filters(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "myFilters");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, MyFiltersWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"1758009606869","status":200,"result":{"exchangeFilters":[{"filterType":"EXCHANGE_MAX_NUM_ORDERS","maxNumOrders":1000}],"symbolFilters":[{"filterType":"PRICE_FILTER","priceExponent":8,"minPrice":"0.00000100","maxPrice":"100000.00000000","tickSize":"0.00000100"}],"assetFilters":[{"filterType":"MAX_ASSET","qtyExponent":8,"limit":"1000000.00000000","asset":"JPY"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":40}]}})json"));
    const auto api = api_for(server);
    const MyFiltersParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.my_filters(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "myFilters");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, MyFiltersErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const MyFiltersParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.my_filters(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, MyPreventedMatches) {
    MockWsServer server(reply(
        R"json({"id":"g4ce6a53-a39d-4f71-823b-4ab5r391d6y8","status":200,"result":[{"symbol":"BTCUSDT","preventedMatchId":1,"takerOrderId":5,"makerSymbol":"BTCUSDT","makerOrderId":3,"tradeGroupId":1,"selfTradePreventionMode":"EXPIRE_MAKER","price":"1.100000","makerPreventedQuantity":"1.300000","transactTime":1669101687094}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const MyPreventedMatchesParams params{.symbol = "BNBUSDT"};
    const auto res = api.my_prevented_matches(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "myPreventedMatches");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, MyPreventedMatchesWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"g4ce6a53-a39d-4f71-823b-4ab5r391d6y8","status":200,"result":[{"symbol":"BTCUSDT","preventedMatchId":1,"takerOrderId":5,"makerSymbol":"BTCUSDT","makerOrderId":3,"tradeGroupId":1,"selfTradePreventionMode":"EXPIRE_MAKER","price":"1.100000","makerPreventedQuantity":"1.300000","transactTime":1669101687094}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const MyPreventedMatchesParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .prevented_match_id = 1,
        .order_id = 1,
        .from_prevented_match_id = 1,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.my_prevented_matches(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "myPreventedMatches");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("preventedMatchId"));
    EXPECT_TRUE(sent.contains("orderId"));
    EXPECT_TRUE(sent.contains("fromPreventedMatchId"));
    EXPECT_TRUE(sent.contains("limit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, MyPreventedMatchesErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const MyPreventedMatchesParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.my_prevented_matches(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, MyTrades) {
    MockWsServer server(reply(
        R"json({"id":"f4ce6a53-a29d-4f70-823b-4ab59391d6e8","status":200,"result":[{"symbol":"BTCUSDT","id":1650422481,"orderId":12569099453,"orderListId":-1,"price":"23416.10000000","qty":"0.00635000","quoteQty":"148.69223500","commission":"0.00000000","commissionAsset":"BNB","time":1660801715793,"isBuyer":false,"isMaker":true,"isBestMatch":true},{"symbol":"BTCUSDT","id":1650422482,"orderId":12569099453,"orderListId":-1,"price":"23416.50000000","qty":"0.00212000","quoteQty":"49.64298000","commission":"0.00000000","commissionAsset":"BNB","time":1660801715793,"isBuyer":false,"isMaker":true,"isBestMatch":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const MyTradesParams params{.symbol = "BNBUSDT"};
    const auto res = api.my_trades(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "myTrades");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, MyTradesWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"f4ce6a53-a29d-4f70-823b-4ab59391d6e8","status":200,"result":[{"symbol":"BTCUSDT","id":1650422481,"orderId":12569099453,"orderListId":-1,"price":"23416.10000000","qty":"0.00635000","quoteQty":"148.69223500","commission":"0.00000000","commissionAsset":"BNB","time":1660801715793,"isBuyer":false,"isMaker":true,"isBestMatch":true},{"symbol":"BTCUSDT","id":1650422482,"orderId":12569099453,"orderListId":-1,"price":"23416.50000000","qty":"0.00212000","quoteQty":"49.64298000","commission":"0.00000000","commissionAsset":"BNB","time":1660801715793,"isBuyer":false,"isMaker":true,"isBestMatch":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const MyTradesParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .order_id = 1,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .from_id = 1,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.my_trades(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "myTrades");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("orderId"));
    EXPECT_TRUE(sent.contains("startTime"));
    EXPECT_TRUE(sent.contains("endTime"));
    EXPECT_TRUE(sent.contains("fromId"));
    EXPECT_TRUE(sent.contains("limit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, MyTradesErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const MyTradesParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.my_trades(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, OpenOrderListsStatus) {
    MockWsServer server(reply(
        R"json({"id":"3a4437e2-41a3-4c19-897c-9cadc5dce8b6","status":200,"result":[{"orderListId":0,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"08985fedd9ea2cf6b28996","transactionTime":1660801713793,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":4,"clientOrderId":"CUhLgTXnX5n2c0gWiLpV4d"},{"symbol":"BTCUSDT","orderId":5,"clientOrderId":"1ZqG7bBuYwaF4SU8CwnwHm"}]}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":6}]})json"));
    const auto api = api_for(server);
    const OpenOrderListsStatusParams params{};
    const auto res = api.open_order_lists_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "openOrderLists.status");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, OpenOrderListsStatusWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"3a4437e2-41a3-4c19-897c-9cadc5dce8b6","status":200,"result":[{"orderListId":0,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"08985fedd9ea2cf6b28996","transactionTime":1660801713793,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":4,"clientOrderId":"CUhLgTXnX5n2c0gWiLpV4d"},{"symbol":"BTCUSDT","orderId":5,"clientOrderId":"1ZqG7bBuYwaF4SU8CwnwHm"}]}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":6}]})json"));
    const auto api = api_for(server);
    const OpenOrderListsStatusParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.open_order_lists_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "openOrderLists.status");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, OpenOrderListsStatusErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OpenOrderListsStatusParams params{};
    EXPECT_THROW((void)api.open_order_lists_status(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, OpenOrdersStatus) {
    MockWsServer server(reply(
        R"json({"id":"55f07876-4f6f-4c47-87dc-43e5fff3f2e7","status":200,"result":[{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"4d96324ff9d44481926157","price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00720000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"172.43931000","status":"PARTIALLY_FILLED","timeInForce":"GTC","type":"LIMIT","side":"SELL","time":1660801715639,"updateTime":1660801717945,"isWorking":true,"workingTime":1660801715639,"selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":6}]})json"));
    const auto api = api_for(server);
    const OpenOrdersStatusParams params{};
    const auto res = api.open_orders_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "openOrders.status");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, OpenOrdersStatusWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"55f07876-4f6f-4c47-87dc-43e5fff3f2e7","status":200,"result":[{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"4d96324ff9d44481926157","price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00720000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"172.43931000","status":"PARTIALLY_FILLED","timeInForce":"GTC","type":"LIMIT","side":"SELL","time":1660801715639,"updateTime":1660801717945,"isWorking":true,"workingTime":1660801715639,"selfTradePreventionMode":"NONE","icebergQty":"0.00000000","preventedMatchId":0,"preventedQuantity":"1.200000","stopPrice":"0.00000000","strategyId":1,"strategyType":1000000,"trailingDelta":10,"trailingTime":-1,"usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":6}]})json"));
    const auto api = api_for(server);
    const OpenOrdersStatusParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .symbol = "BNBUSDT",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.open_orders_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "openOrders.status");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, OpenOrdersStatusErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OpenOrdersStatusParams params{};
    EXPECT_THROW((void)api.open_orders_status(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, OrderAmendments) {
    MockWsServer server(reply(
        R"json({"id":"6f5ebe91-01d9-43ac-be99-57cf062e0e30","status":200,"result":[{"symbol":"BTCUSDT","orderId":23,"executionId":60,"origClientOrderId":"my_pending_order","newClientOrderId":"xbxXh5SSwaHS7oUEOCI88B","origQty":"7.00000000","newQty":"5.00000000","time":1741924229819}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const OrderAmendmentsParams params{.symbol = "BNBUSDT", .order_id = 1};
    const auto res = api.order_amendments(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.amendments");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, OrderAmendmentsWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"6f5ebe91-01d9-43ac-be99-57cf062e0e30","status":200,"result":[{"symbol":"BTCUSDT","orderId":23,"executionId":60,"origClientOrderId":"my_pending_order","newClientOrderId":"xbxXh5SSwaHS7oUEOCI88B","origQty":"7.00000000","newQty":"5.00000000","time":1741924229819}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const OrderAmendmentsParams params{
        .symbol = "BNBUSDT",
        .order_id = 1,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .from_execution_id = 1,
        .limit = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_amendments(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.amendments");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("orderId"));

    EXPECT_TRUE(sent.contains("fromExecutionId"));
    EXPECT_TRUE(sent.contains("limit"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, OrderAmendmentsErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderAmendmentsParams params{.symbol = "BNBUSDT", .order_id = 1};
    EXPECT_THROW((void)api.order_amendments(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, OrderListStatus) {
    MockWsServer server(reply(
        R"json({"id":"b53fd5ff-82c7-4a04-bd64-5f9dc42c2100","status":200,"result":{"orderListId":1274512,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"08985fedd9ea2cf6b28996","transactionTime":1660801713793,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569138901,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU"},{"symbol":"BTCUSDT","orderId":12569138902,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us"}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const OrderListStatusParams params{};
    const auto res = api.order_list_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.status");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, OrderListStatusWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"b53fd5ff-82c7-4a04-bd64-5f9dc42c2100","status":200,"result":{"orderListId":1274512,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"08985fedd9ea2cf6b28996","transactionTime":1660801713793,"symbol":"BTCUSDT","orders":[{"symbol":"BTCUSDT","orderId":12569138901,"clientOrderId":"BqtFCj5odMoWtSqGk2X9tU"},{"symbol":"BTCUSDT","orderId":12569138902,"clientOrderId":"jLnZpj5enfMXTuhKB1d0us"}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const OrderListStatusParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .orig_client_order_id = "08985fedd9ea2cf6b28996",
        .order_list_id = 1,
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_list_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "orderList.status");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("origClientOrderId"));
    EXPECT_TRUE(sent.contains("orderListId"));
    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, OrderListStatusErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderListStatusParams params{};
    EXPECT_THROW((void)api.order_list_status(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, OrderStatus) {
    MockWsServer server(reply(
        R"json({"id":"aa62318a-5a97-4f3b-bdc7-640bbe33b291","status":200,"result":{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"4d96324ff9d44481926157","price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00847000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"198.33521500","status":"FILLED","timeInForce":"GTC","type":"LIMIT","side":"SELL","stopPrice":"0.00000000","trailingDelta":10,"trailingTime":-1,"icebergQty":"0.00000000","time":1660801715639,"updateTime":1660801717945,"isWorking":true,"workingTime":1660801715639,"strategyId":37463720,"strategyType":1000000,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const OrderStatusParams params{.symbol = "BNBUSDT"};
    const auto res = api.order_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "order.status");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, OrderStatusWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"aa62318a-5a97-4f3b-bdc7-640bbe33b291","status":200,"result":{"symbol":"BTCUSDT","orderId":12569099453,"orderListId":-1,"clientOrderId":"4d96324ff9d44481926157","price":"23416.10000000","origQty":"0.00847000","executedQty":"0.00847000","origQuoteOrderQty":"0.000000","cummulativeQuoteQty":"198.33521500","status":"FILLED","timeInForce":"GTC","type":"LIMIT","side":"SELL","stopPrice":"0.00000000","trailingDelta":10,"trailingTime":-1,"icebergQty":"0.00000000","time":1660801715639,"updateTime":1660801717945,"isWorking":true,"workingTime":1660801715639,"strategyId":37463720,"strategyType":1000000,"selfTradePreventionMode":"NONE","preventedMatchId":0,"preventedQuantity":"1.200000","usedSor":true,"workingFloor":"SOR","pegPriceType":"PRIMARY_PEG","pegOffsetType":"PRICE_LEVEL","pegOffsetValue":5,"peggedPrice":"87523.83710000","expiryReason":"INSUFFICIENT_LIQUIDITY"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const OrderStatusParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .order_id = 1,
        .orig_client_order_id = "myOrder1",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.order_status(params);
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

TEST(WebsocketApiAccountApi, OrderStatusErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderStatusParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.order_status(params), common::WebsocketResponseError);
}
