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
#include <binance/spot/websocket_api/general_api.hpp>

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

GeneralApi api_for(const MockWsServer& server) {
    common::WebsocketApiConfig cfg;
    cfg.url = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    cfg.proxy_from_env = false;
    auto client = std::make_shared<common::WebsocketApi>(std::move(cfg));
    client->connect();
    return GeneralApi(std::move(client));
}

boost::json::object first_request(const MockWsServer& server) {
    return boost::json::parse(server.sessions().front().received.front()).as_object();
}

} // namespace

TEST(WebsocketApiGeneralApi, ExchangeInfo) {
    MockWsServer server(reply(
        R"json({"id":"5494febb-d167-46a2-996d-70533eb4d976","status":200,"result":{"timezone":"UTC","serverTime":1655969291181,"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000},{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000},{"rateLimitType":"CONNECTIONS","interval":"MINUTE","intervalNum":5,"limit":300}],"exchangeFilters":[{"filterType":"EXCHANGE_MAX_NUM_ORDERS","maxNumOrders":1000}],"symbols":[{"symbol":"BNBBTC","status":"TRADING","baseAsset":"BNB","baseAssetPrecision":8,"quoteAsset":"BTC","quotePrecision":8,"quoteAssetPrecision":8,"baseCommissionPrecision":8,"quoteCommissionPrecision":8,"orderTypes":["LIMIT","LIMIT_MAKER","MARKET","STOP_LOSS_LIMIT","TAKE_PROFIT_LIMIT"],"icebergAllowed":true,"ocoAllowed":true,"otoAllowed":true,"opoAllowed":true,"quoteOrderQtyMarketAllowed":true,"allowTrailingStop":true,"cancelReplaceAllowed":true,"amendAllowed":false,"pegInstructionsAllowed":true,"marketQuoteNotionalLimitAllowed":true,"limitQuoteNotionalLimitAllowed":true,"isSpotTradingAllowed":true,"isMarginTradingAllowed":true,"filters":[{"filterType":"PRICE_FILTER","minPrice":"0.00000100","maxPrice":"100000.00000000","tickSize":"0.00000100"},{"filterType":"LOT_SIZE","minQty":"0.00100000","maxQty":"100000.00000000","stepSize":"0.00100000"}],"permissions":["SPOT"],"permissionSets":[["SPOT","MARGIN","TRD_GRP_004"]],"defaultSelfTradePreventionMode":"NONE","allowedSelfTradePreventionModes":["NONE"]}],"sors":[{"baseAsset":"BTC","symbols":["BTCUSDT","BTCUSDC"]}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const ExchangeInfoParams params{};
    const auto res = api.exchange_info(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "exchangeInfo");
}

TEST(WebsocketApiGeneralApi, ExchangeInfoWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"5494febb-d167-46a2-996d-70533eb4d976","status":200,"result":{"timezone":"UTC","serverTime":1655969291181,"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000},{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50},{"rateLimitType":"ORDERS","interval":"DAY","intervalNum":1,"limit":160000},{"rateLimitType":"CONNECTIONS","interval":"MINUTE","intervalNum":5,"limit":300}],"exchangeFilters":[{"filterType":"EXCHANGE_MAX_NUM_ORDERS","maxNumOrders":1000}],"symbols":[{"symbol":"BNBBTC","status":"TRADING","baseAsset":"BNB","baseAssetPrecision":8,"quoteAsset":"BTC","quotePrecision":8,"quoteAssetPrecision":8,"baseCommissionPrecision":8,"quoteCommissionPrecision":8,"orderTypes":["LIMIT","LIMIT_MAKER","MARKET","STOP_LOSS_LIMIT","TAKE_PROFIT_LIMIT"],"icebergAllowed":true,"ocoAllowed":true,"otoAllowed":true,"opoAllowed":true,"quoteOrderQtyMarketAllowed":true,"allowTrailingStop":true,"cancelReplaceAllowed":true,"amendAllowed":false,"pegInstructionsAllowed":true,"marketQuoteNotionalLimitAllowed":true,"limitQuoteNotionalLimitAllowed":true,"isSpotTradingAllowed":true,"isMarginTradingAllowed":true,"filters":[{"filterType":"PRICE_FILTER","minPrice":"0.00000100","maxPrice":"100000.00000000","tickSize":"0.00000100"},{"filterType":"LOT_SIZE","minQty":"0.00100000","maxQty":"100000.00000000","stepSize":"0.00100000"}],"permissions":["SPOT"],"permissionSets":[["SPOT","MARGIN","TRD_GRP_004"]],"defaultSelfTradePreventionMode":"NONE","allowedSelfTradePreventionModes":["NONE"]}],"sors":[{"baseAsset":"BTC","symbols":["BTCUSDT","BTCUSDC"]}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":20}]})json"));
    const auto api = api_for(server);
    const ExchangeInfoParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .permissions = std::vector<std::string>{},
        .show_permission_sets = true,
        .symbol_status = ExchangeInfoSymbolStatusEnum::Trading,
    };
    const auto res = api.exchange_info(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "exchangeInfo");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("showPermissionSets"));
    EXPECT_TRUE(sent.contains("symbolStatus"));
}

TEST(WebsocketApiGeneralApi, ExchangeInfoErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const ExchangeInfoParams params{};
    EXPECT_THROW((void)api.exchange_info(params), common::WebsocketResponseError);
}

TEST(WebsocketApiGeneralApi, ExecutionRules) {
    MockWsServer server(reply(
        R"json({"id":"5162affb-0aba-4821-b475-f2625006eb43","status":200,"result":{"symbolRules":[{"symbol":"BAZUSD","rules":[{"ruleType":"PRICE_RANGE","bidLimitMultUp":"1.0001","bidLimitMultDown":"0.9999","askLimitMultUp":"1.0001","askLimitMultDown":"0.9999"}]}]}})json"));
    const auto api = api_for(server);
    const ExecutionRulesParams params{};
    const auto res = api.execution_rules(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "executionRules");
}

TEST(WebsocketApiGeneralApi, ExecutionRulesWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"5162affb-0aba-4821-b475-f2625006eb43","status":200,"result":{"symbolRules":[{"symbol":"BAZUSD","rules":[{"ruleType":"PRICE_RANGE","bidLimitMultUp":"1.0001","bidLimitMultDown":"0.9999","askLimitMultUp":"1.0001","askLimitMultDown":"0.9999"}]}]}})json"));
    const auto api = api_for(server);
    const ExecutionRulesParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .symbol = "BAZUSD",
        .symbols = std::vector<std::string>{},
        .symbol_status = ExecutionRulesSymbolStatusEnum::Trading,
    };
    const auto res = api.execution_rules(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "executionRules");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("symbolStatus"));
}

TEST(WebsocketApiGeneralApi, ExecutionRulesErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const ExecutionRulesParams params{};
    EXPECT_THROW((void)api.execution_rules(params), common::WebsocketResponseError);
}

TEST(WebsocketApiGeneralApi, Ping) {
    MockWsServer server(reply(
        R"json({"id":"922bcc6e-9de8-440d-9e84-7c80933a8d0d","status":200,"result":{},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const PingParams params{};
    const auto res = api.ping(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ping");
}

TEST(WebsocketApiGeneralApi, PingWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"922bcc6e-9de8-440d-9e84-7c80933a8d0d","status":200,"result":{},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const PingParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
    };
    const auto res = api.ping(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ping");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
}

TEST(WebsocketApiGeneralApi, PingErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const PingParams params{};
    EXPECT_THROW((void)api.ping(params), common::WebsocketResponseError);
}

TEST(WebsocketApiGeneralApi, Time) {
    MockWsServer server(reply(
        R"json({"id":"187d3cb2-942d-484c-8271-4e2141bbadb1","status":200,"result":{"serverTime":1656400526260},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const TimeParams params{};
    const auto res = api.time(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "time");
}

TEST(WebsocketApiGeneralApi, TimeWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"187d3cb2-942d-484c-8271-4e2141bbadb1","status":200,"result":{"serverTime":1656400526260},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":1}]})json"));
    const auto api = api_for(server);
    const TimeParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
    };
    const auto res = api.time(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "time");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
}

TEST(WebsocketApiGeneralApi, TimeErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const TimeParams params{};
    EXPECT_THROW((void)api.time(params), common::WebsocketResponseError);
}
