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
#include <binance/spot/rest_api/general_api.hpp>

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

GeneralApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return GeneralApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiGeneralApi, ExchangeInfo) {
    const std::string example =
        R"json({"timezone":"UTC","serverTime":1565246363776,"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":321}],"exchangeFilters":[{"filterType":"EXCHANGE_MAX_NUM_ORDERS","maxNumOrders":1000}],"symbols":[{"symbol":"ETHBTC","status":"TRADING","baseAsset":"ETH","baseAssetPrecision":8,"quoteAsset":"BTC","quotePrecision":8,"quoteAssetPrecision":8,"baseCommissionPrecision":8,"quoteCommissionPrecision":8,"orderTypes":["LIMIT","LIMIT_MAKER","MARKET","STOP_LOSS","STOP_LOSS_LIMIT","TAKE_PROFIT","TAKE_PROFIT_LIMIT"],"icebergAllowed":true,"ocoAllowed":true,"otoAllowed":true,"opoAllowed":true,"quoteOrderQtyMarketAllowed":true,"allowTrailingStop":false,"cancelReplaceAllowed":false,"amendAllowed":false,"pegInstructionsAllowed":true,"marketQuoteNotionalLimitAllowed":true,"limitQuoteNotionalLimitAllowed":true,"isSpotTradingAllowed":true,"isMarginTradingAllowed":true,"filters":[{"filterType":"PRICE_FILTER","priceExponent":8,"minPrice":"0.00000100","maxPrice":"100000.00000000","tickSize":"0.00000100"}],"permissions":["undefined"],"permissionSets":[["SPOT"]],"defaultSelfTradePreventionMode":"NONE","allowedSelfTradePreventionModes":["NONE"]}],"sors":[{"baseAsset":"BTC","symbols":["BTCUSDT"]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExchangeInfoParams params{};
    const auto res = api.exchange_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/exchangeInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiGeneralApi, ExchangeInfoWithOptionalParams) {
    const std::string example =
        R"json({"timezone":"UTC","serverTime":1565246363776,"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":321}],"exchangeFilters":[{"filterType":"EXCHANGE_MAX_NUM_ORDERS","maxNumOrders":1000}],"symbols":[{"symbol":"ETHBTC","status":"TRADING","baseAsset":"ETH","baseAssetPrecision":8,"quoteAsset":"BTC","quotePrecision":8,"quoteAssetPrecision":8,"baseCommissionPrecision":8,"quoteCommissionPrecision":8,"orderTypes":["LIMIT","LIMIT_MAKER","MARKET","STOP_LOSS","STOP_LOSS_LIMIT","TAKE_PROFIT","TAKE_PROFIT_LIMIT"],"icebergAllowed":true,"ocoAllowed":true,"otoAllowed":true,"opoAllowed":true,"quoteOrderQtyMarketAllowed":true,"allowTrailingStop":false,"cancelReplaceAllowed":false,"amendAllowed":false,"pegInstructionsAllowed":true,"marketQuoteNotionalLimitAllowed":true,"limitQuoteNotionalLimitAllowed":true,"isSpotTradingAllowed":true,"isMarginTradingAllowed":true,"filters":[{"filterType":"PRICE_FILTER","priceExponent":8,"minPrice":"0.00000100","maxPrice":"100000.00000000","tickSize":"0.00000100"}],"permissions":["undefined"],"permissionSets":[["SPOT"]],"defaultSelfTradePreventionMode":"NONE","allowedSelfTradePreventionModes":["NONE"]}],"sors":[{"baseAsset":"BTC","symbols":["BTCUSDT"]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExchangeInfoParams params{
        .symbol = "ETHBTC",
        .symbols = std::vector<std::string>{},
        .permissions = std::vector<ExchangeInfoPermissionsEnum>{ExchangeInfoPermissionsEnum::Spot},
        .show_permission_sets = false,
        .symbol_status = ExchangeInfoSymbolStatusEnum::Trading,
    };
    const auto res = api.exchange_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    // An array of enums is sent as a JSON array.
    EXPECT_NE((rec.query() + "&" + rec.body).find("permissions=%5B%22SPOT%22%5D"),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("showPermissionSets="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbolStatus="), std::string::npos);
}

TEST(RestApiGeneralApi, ExchangeInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ExchangeInfoParams params{};
    EXPECT_THROW((void)api.exchange_info(params), common::BadRequestError);
}

TEST(RestApiGeneralApi, ExecutionRules) {
    const std::string example =
        R"json({"symbolRules":[{"symbol":"BAZUSD","rules":[{"ruleType":"PRICE_RANGE","bidLimitMultUp":"1.0001","bidLimitMultDown":"0.9999","askLimitMultUp":"1.0001","askLimitMultDown":"0.9999"}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExecutionRulesParams params{};
    const auto res = api.execution_rules(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/executionRules");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiGeneralApi, ExecutionRulesWithOptionalParams) {
    const std::string example =
        R"json({"symbolRules":[{"symbol":"BAZUSD","rules":[{"ruleType":"PRICE_RANGE","bidLimitMultUp":"1.0001","bidLimitMultDown":"0.9999","askLimitMultUp":"1.0001","askLimitMultDown":"0.9999"}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExecutionRulesParams params{
        .symbol = "BAZUSD",
        .symbols = std::vector<std::string>{},
        .symbol_status = ExecutionRulesSymbolStatusEnum::Trading,
    };
    const auto res = api.execution_rules(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbolStatus="), std::string::npos);
}

TEST(RestApiGeneralApi, ExecutionRulesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ExecutionRulesParams params{};
    EXPECT_THROW((void)api.execution_rules(params), common::BadRequestError);
}

TEST(RestApiGeneralApi, Ping) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.ping();
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/ping");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiGeneralApi, PingBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.ping(), common::BadRequestError);
}

TEST(RestApiGeneralApi, Time) {
    const std::string example = R"json({"serverTime":1499827319559})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.time();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/time");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiGeneralApi, TimeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.time(), common::BadRequestError);
}
