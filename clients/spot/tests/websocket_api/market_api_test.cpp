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
#include <binance/spot/websocket_api/market_api.hpp>

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

MarketApi api_for(const MockWsServer& server) {
    common::WebsocketApiConfig cfg;
    cfg.url = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    cfg.proxy_from_env = false;
    auto client = std::make_shared<common::WebsocketApi>(std::move(cfg));
    client->connect();
    return MarketApi(std::move(client));
}

boost::json::object first_request(const MockWsServer& server) {
    return boost::json::parse(server.sessions().front().received.front()).as_object();
}

} // namespace

TEST(WebsocketApiMarketApi, AvgPrice) {
    MockWsServer server(reply(
        R"json({"id":"ddbfb65f-9ebf-42ec-8240-8f0f91de0867","status":200,"result":{"mins":5,"price":"0.01378135","closeTime":1694061154503},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const AvgPriceParams params{.symbol = "BNBUSDT"};
    const auto res = api.avg_price(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "avgPrice");
}

TEST(WebsocketApiMarketApi, AvgPriceWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"ddbfb65f-9ebf-42ec-8240-8f0f91de0867","status":200,"result":{"mins":5,"price":"0.01378135","closeTime":1694061154503},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const AvgPriceParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
    };
    const auto res = api.avg_price(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "avgPrice");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
}

TEST(WebsocketApiMarketApi, AvgPriceErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const AvgPriceParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.avg_price(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, BlockTradesHistorical) {
    MockWsServer server(reply(
        R"json({"id":"cffc9c7d-4efc-4ce0-b587-6b87448f052a","status":200,"result":[{"id":582,"price":"0.052","qty":"5838","quoteQty":"303.576","time":1772506983321,"isBuyerMaker":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":10}]})json"));
    const auto api = api_for(server);
    const BlockTradesHistoricalParams params{.symbol = "BNBBTC", .from_id = 582};
    const auto res = api.block_trades_historical(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "blockTrades.historical");
}

TEST(WebsocketApiMarketApi, BlockTradesHistoricalWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"cffc9c7d-4efc-4ce0-b587-6b87448f052a","status":200,"result":[{"id":582,"price":"0.052","qty":"5838","quoteQty":"303.576","time":1772506983321,"isBuyerMaker":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":10}]})json"));
    const auto api = api_for(server);
    const BlockTradesHistoricalParams params{
        .symbol = "BNBBTC",
        .from_id = 582,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .limit = 500,
    };
    const auto res = api.block_trades_historical(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "blockTrades.historical");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("fromId"));

    EXPECT_TRUE(sent.contains("limit"));
}

TEST(WebsocketApiMarketApi, BlockTradesHistoricalErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const BlockTradesHistoricalParams params{.symbol = "BNBBTC", .from_id = 582};
    EXPECT_THROW((void)api.block_trades_historical(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, Depth) {
    MockWsServer server(reply(
        R"json({"id":"51e2affb-0aba-4821-ba75-f2625006eb43","status":200,"result":{"lastUpdateId":2731179239,"bids":[["0.01379900","3.43200000"],["0.01379800","3.24300000"],["0.01379700","10.45500000"],["0.01379600","3.82100000"],["0.01379500","10.26200000"]],"asks":[["0.01380000","5.91700000"],["0.01380100","6.01400000"],["0.01380200","0.26800000"],["0.01380300","0.33800000"],["0.01380400","0.26800000"]]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const DepthParams params{.symbol = "BNBUSDT"};
    const auto res = api.depth(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "depth");
}

TEST(WebsocketApiMarketApi, DepthWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"51e2affb-0aba-4821-ba75-f2625006eb43","status":200,"result":{"lastUpdateId":2731179239,"bids":[["0.01379900","3.43200000"],["0.01379800","3.24300000"],["0.01379700","10.45500000"],["0.01379600","3.82100000"],["0.01379500","10.26200000"]],"asks":[["0.01380000","5.91700000"],["0.01380100","6.01400000"],["0.01380200","0.26800000"],["0.01380300","0.33800000"],["0.01380400","0.26800000"]]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const DepthParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .limit = 1,
        .symbol_status = DepthSymbolStatusEnum::Trading,
    };
    const auto res = api.depth(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "depth");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("limit"));
    EXPECT_TRUE(sent.contains("symbolStatus"));
}

TEST(WebsocketApiMarketApi, DepthErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const DepthParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.depth(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, Klines) {
    MockWsServer server(reply(
        R"json({"id":"1dbbeb56-8eea-466a-8f6e-86bdcfa2fc0b","status":200,"result":[[1499040000000]],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const KlinesParams params{.symbol = "BNBUSDT", .interval = KlinesIntervalEnum::Interval1s};
    const auto res = api.klines(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "klines");
}

TEST(WebsocketApiMarketApi, KlinesWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"1dbbeb56-8eea-466a-8f6e-86bdcfa2fc0b","status":200,"result":[[1499040000000]],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const KlinesParams params{
        .symbol = "BNBUSDT",
        .interval = KlinesIntervalEnum::Interval1s,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .time_zone = "0",
        .limit = 1,
    };
    const auto res = api.klines(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "klines");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("interval"));

    EXPECT_TRUE(sent.contains("startTime"));
    EXPECT_TRUE(sent.contains("endTime"));
    EXPECT_TRUE(sent.contains("timeZone"));
    EXPECT_TRUE(sent.contains("limit"));
}

TEST(WebsocketApiMarketApi, KlinesErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const KlinesParams params{.symbol = "BNBUSDT", .interval = KlinesIntervalEnum::Interval1s};
    EXPECT_THROW((void)api.klines(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, ReferencePrice) {
    MockWsServer server(reply(
        R"json({"id":"ddbfb65f-9ebf-42ec-8240-8f0f91de0867","status":200,"result":{"symbol":"BAZUSD","referencePrice":"0.00501900","timestamp":1770946889251,"code":-2043,"msg":"This symbol doesn't have a reference price."},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const ReferencePriceParams params{.symbol = "BAZUSD"};
    const auto res = api.reference_price(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "referencePrice");
}

TEST(WebsocketApiMarketApi, ReferencePriceWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"ddbfb65f-9ebf-42ec-8240-8f0f91de0867","status":200,"result":{"symbol":"BAZUSD","referencePrice":"0.00501900","timestamp":1770946889251,"code":-2043,"msg":"This symbol doesn't have a reference price."},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const ReferencePriceParams params{
        .symbol = "BAZUSD",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
    };
    const auto res = api.reference_price(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "referencePrice");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
}

TEST(WebsocketApiMarketApi, ReferencePriceErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const ReferencePriceParams params{.symbol = "BAZUSD"};
    EXPECT_THROW((void)api.reference_price(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, ReferencePriceCalculation) {
    MockWsServer server(reply(
        R"json({"id":"ddbfb65f-9ebf-42ec-8240-8f0f91de0867","status":200,"result":{"symbol":"BAZUSD","calculationType":"ARITHMETIC_MEAN","bucketCount":10,"bucketWidthMs":1000,"externalCalculationId":42},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const ReferencePriceCalculationParams params{.symbol = "BAZUSD"};
    const auto res = api.reference_price_calculation(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "referencePrice.calculation");
}

TEST(WebsocketApiMarketApi, ReferencePriceCalculationWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"ddbfb65f-9ebf-42ec-8240-8f0f91de0867","status":200,"result":{"symbol":"BAZUSD","calculationType":"ARITHMETIC_MEAN","bucketCount":10,"bucketWidthMs":1000,"externalCalculationId":42},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const ReferencePriceCalculationParams params{
        .symbol = "BAZUSD",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .symbol_status = ReferencePriceCalculationSymbolStatusEnum::Trading,
    };
    const auto res = api.reference_price_calculation(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "referencePrice.calculation");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("symbolStatus"));
}

TEST(WebsocketApiMarketApi, ReferencePriceCalculationErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const ReferencePriceCalculationParams params{.symbol = "BAZUSD"};
    EXPECT_THROW((void)api.reference_price_calculation(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, Ticker) {
    MockWsServer server(reply(
        R"json({"id":"bdb7c503-542c-495c-b797-4d2ee2e91173","status":200,"result":{"symbol":"BNBBTC","priceChange":"0.00061500","priceChangePercent":"4.735","weightedAvgPrice":"0.01368242","openPrice":"0.01298900","highPrice":"0.01418800","lowPrice":"0.01296000","lastPrice":"0.01360400","volume":"587179.23900000","quoteVolume":"8034.03382165","openTime":1659580020000,"closeTime":1660184865291,"firstId":192977765,"lastId":195365758,"count":2387994},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const TickerParams params{};
    const auto res = api.ticker(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker");
}

TEST(WebsocketApiMarketApi, TickerWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"bdb7c503-542c-495c-b797-4d2ee2e91173","status":200,"result":{"symbol":"BNBBTC","priceChange":"0.00061500","priceChangePercent":"4.735","weightedAvgPrice":"0.01368242","openPrice":"0.01298900","highPrice":"0.01418800","lowPrice":"0.01296000","lastPrice":"0.01360400","volume":"587179.23900000","quoteVolume":"8034.03382165","openTime":1659580020000,"closeTime":1660184865291,"firstId":192977765,"lastId":195365758,"count":2387994},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const TickerParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .type = TickerTypeEnum::Full,
        .window_size = TickerWindowSizeEnum::WindowSize1m,
        .symbol_status = TickerSymbolStatusEnum::Trading,
    };
    const auto res = api.ticker(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("type"));
    EXPECT_TRUE(sent.contains("windowSize"));
    EXPECT_TRUE(sent.contains("symbolStatus"));
}

TEST(WebsocketApiMarketApi, TickerErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const TickerParams params{};
    EXPECT_THROW((void)api.ticker(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, Ticker24hr) {
    MockWsServer server(reply(
        R"json({"id":"9fa2a91b-3fca-4ed7-a9ad-58e3b67483de","status":200,"result":{"symbol":"BNBBTC","priceChange":"0.00013900","priceChangePercent":"1.020","weightedAvgPrice":"0.01382453","prevClosePrice":"0.01362800","lastPrice":"0.01376700","lastQty":"1.78800000","bidPrice":"0.01376700","bidQty":"4.64600000","askPrice":"0.01376800","askQty":"14.31400000","openPrice":"0.01362800","highPrice":"0.01414900","lowPrice":"0.01346600","volume":"69412.40500000","quoteVolume":"959.59411487","openTime":1660014164909,"closeTime":1660100564909,"firstId":194696115,"lastId":194968287,"count":272173},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const Ticker24hrParams params{};
    const auto res = api.ticker24hr(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.24hr");
}

TEST(WebsocketApiMarketApi, Ticker24hrWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"9fa2a91b-3fca-4ed7-a9ad-58e3b67483de","status":200,"result":{"symbol":"BNBBTC","priceChange":"0.00013900","priceChangePercent":"1.020","weightedAvgPrice":"0.01382453","prevClosePrice":"0.01362800","lastPrice":"0.01376700","lastQty":"1.78800000","bidPrice":"0.01376700","bidQty":"4.64600000","askPrice":"0.01376800","askQty":"14.31400000","openPrice":"0.01362800","highPrice":"0.01414900","lowPrice":"0.01346600","volume":"69412.40500000","quoteVolume":"959.59411487","openTime":1660014164909,"closeTime":1660100564909,"firstId":194696115,"lastId":194968287,"count":272173},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const Ticker24hrParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .type = Ticker24hrTypeEnum::Full,
        .symbol_status = Ticker24hrSymbolStatusEnum::Trading,
    };
    const auto res = api.ticker24hr(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.24hr");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("type"));
    EXPECT_TRUE(sent.contains("symbolStatus"));
}

TEST(WebsocketApiMarketApi, Ticker24hrErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const Ticker24hrParams params{};
    EXPECT_THROW((void)api.ticker24hr(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, TickerBook) {
    MockWsServer server(reply(
        R"json({"id":"9d32157c-a556-4d27-9866-66760a174b57","status":200,"result":{"symbol":"BNBBTC","bidPrice":"0.01358000","bidQty":"12.53400000","askPrice":"0.01358100","askQty":"17.83700000"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const TickerBookParams params{};
    const auto res = api.ticker_book(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.book");
}

TEST(WebsocketApiMarketApi, TickerBookWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"9d32157c-a556-4d27-9866-66760a174b57","status":200,"result":{"symbol":"BNBBTC","bidPrice":"0.01358000","bidQty":"12.53400000","askPrice":"0.01358100","askQty":"17.83700000"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const TickerBookParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .symbol_status = TickerBookSymbolStatusEnum::Trading,
    };
    const auto res = api.ticker_book(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.book");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("symbolStatus"));
}

TEST(WebsocketApiMarketApi, TickerBookErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const TickerBookParams params{};
    EXPECT_THROW((void)api.ticker_book(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, TickerPrice) {
    MockWsServer server(reply(
        R"json({"id":"043a7cf2-bde3-4888-9604-c8ac41fcba4d","status":200,"result":{"symbol":"BNBBTC","price":"0.01361900"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const TickerPriceParams params{};
    const auto res = api.ticker_price(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.price");
}

TEST(WebsocketApiMarketApi, TickerPriceWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"043a7cf2-bde3-4888-9604-c8ac41fcba4d","status":200,"result":{"symbol":"BNBBTC","price":"0.01361900"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const TickerPriceParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .symbol_status = TickerPriceSymbolStatusEnum::Trading,
    };
    const auto res = api.ticker_price(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.price");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("symbolStatus"));
}

TEST(WebsocketApiMarketApi, TickerPriceErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const TickerPriceParams params{};
    EXPECT_THROW((void)api.ticker_price(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, TickerTradingDay) {
    MockWsServer server(reply(
        R"json({"id":"f4b3b507-c8f2-442a-81a6-b2f12daa030f","status":200,"result":{"symbol":"BTCUSDT","priceChange":"-83.13000000","priceChangePercent":"-0.317","weightedAvgPrice":"26234.58803036","openPrice":"26304.80000000","highPrice":"26397.46000000","lowPrice":"26088.34000000","lastPrice":"26221.67000000","volume":"18495.35066000","quoteVolume":"485217905.04210480","openTime":1695686400000,"closeTime":1695772799999,"firstId":3220151555,"lastId":3220849281,"count":697727},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const TickerTradingDayParams params{};
    const auto res = api.ticker_trading_day(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.tradingDay");
}

TEST(WebsocketApiMarketApi, TickerTradingDayWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"f4b3b507-c8f2-442a-81a6-b2f12daa030f","status":200,"result":{"symbol":"BTCUSDT","priceChange":"-83.13000000","priceChangePercent":"-0.317","weightedAvgPrice":"26234.58803036","openPrice":"26304.80000000","highPrice":"26397.46000000","lowPrice":"26088.34000000","lastPrice":"26221.67000000","volume":"18495.35066000","quoteVolume":"485217905.04210480","openTime":1695686400000,"closeTime":1695772799999,"firstId":3220151555,"lastId":3220849281,"count":697727},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const TickerTradingDayParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .time_zone = "0",
        .type = TickerTradingDayTypeEnum::Full,
        .symbol_status = TickerTradingDaySymbolStatusEnum::Trading,
    };
    const auto res = api.ticker_trading_day(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.tradingDay");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("timeZone"));
    EXPECT_TRUE(sent.contains("type"));
    EXPECT_TRUE(sent.contains("symbolStatus"));
}

TEST(WebsocketApiMarketApi, TickerTradingDayErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const TickerTradingDayParams params{};
    EXPECT_THROW((void)api.ticker_trading_day(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, TradesAggregate) {
    MockWsServer server(reply(
        R"json({"id":"189da436-d4bd-48ca-9f95-9f613d621717","status":200,"result":[{"a":50000000,"p":"0.00274100","q":"57.19000000","f":59120167,"l":59120170,"T":1565877971222,"m":true,"M":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const TradesAggregateParams params{.symbol = "BNBUSDT"};
    const auto res = api.trades_aggregate(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "trades.aggregate");
}

TEST(WebsocketApiMarketApi, TradesAggregateWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"189da436-d4bd-48ca-9f95-9f613d621717","status":200,"result":[{"a":50000000,"p":"0.00274100","q":"57.19000000","f":59120167,"l":59120170,"T":1565877971222,"m":true,"M":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":4}]})json"));
    const auto api = api_for(server);
    const TradesAggregateParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .from_id = 1,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .limit = 1,
    };
    const auto res = api.trades_aggregate(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "trades.aggregate");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("fromId"));
    EXPECT_TRUE(sent.contains("startTime"));
    EXPECT_TRUE(sent.contains("endTime"));
    EXPECT_TRUE(sent.contains("limit"));
}

TEST(WebsocketApiMarketApi, TradesAggregateErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const TradesAggregateParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.trades_aggregate(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, TradesHistorical) {
    MockWsServer server(reply(
        R"json({"id":"cffc9c7d-4efc-4ce0-b587-6b87448f052a","status":200,"result":[{"id":0,"price":"0.00005000","qty":"40.00000000","quoteQty":"0.00200000","time":1500004800376,"isBuyerMaker":true,"isBestMatch":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":25}]})json"));
    const auto api = api_for(server);
    const TradesHistoricalParams params{.symbol = "BNBUSDT"};
    const auto res = api.trades_historical(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "trades.historical");
}

TEST(WebsocketApiMarketApi, TradesHistoricalWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"cffc9c7d-4efc-4ce0-b587-6b87448f052a","status":200,"result":[{"id":0,"price":"0.00005000","qty":"40.00000000","quoteQty":"0.00200000","time":1500004800376,"isBuyerMaker":true,"isBestMatch":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":25}]})json"));
    const auto api = api_for(server);
    const TradesHistoricalParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .from_id = 1,
        .limit = 1,
    };
    const auto res = api.trades_historical(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "trades.historical");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("fromId"));
    EXPECT_TRUE(sent.contains("limit"));
}

TEST(WebsocketApiMarketApi, TradesHistoricalErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const TradesHistoricalParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.trades_historical(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, TradesRecent) {
    MockWsServer server(reply(
        R"json({"id":"409a20bd-253d-41db-a6dd-687862a5882f","status":200,"result":[{"id":194686783,"price":"0.01361000","qty":"0.01400000","quoteQty":"0.00019054","time":1660009530807,"isBuyerMaker":true,"isBestMatch":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":25}]})json"));
    const auto api = api_for(server);
    const TradesRecentParams params{.symbol = "BNBUSDT"};
    const auto res = api.trades_recent(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "trades.recent");
}

TEST(WebsocketApiMarketApi, TradesRecentWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"409a20bd-253d-41db-a6dd-687862a5882f","status":200,"result":[{"id":194686783,"price":"0.01361000","qty":"0.01400000","quoteQty":"0.00019054","time":1660009530807,"isBuyerMaker":true,"isBestMatch":true}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":25}]})json"));
    const auto api = api_for(server);
    const TradesRecentParams params{
        .symbol = "BNBUSDT",
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .limit = 1,
    };
    const auto res = api.trades_recent(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "trades.recent");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("limit"));
}

TEST(WebsocketApiMarketApi, TradesRecentErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const TradesRecentParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.trades_recent(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketApi, UiKlines) {
    MockWsServer server(reply(
        R"json({"id":"b137468a-fb20-4c06-bd6b-625148eec958","status":200,"result":[[1499040000000]],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const UiKlinesParams params{.symbol = "BNBUSDT", .interval = UiKlinesIntervalEnum::Interval1s};
    const auto res = api.ui_klines(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "uiKlines");
}

TEST(WebsocketApiMarketApi, UiKlinesWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"b137468a-fb20-4c06-bd6b-625148eec958","status":200,"result":[[1499040000000]],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":6000,"count":2}]})json"));
    const auto api = api_for(server);
    const UiKlinesParams params{
        .symbol = "BNBUSDT",
        .interval = UiKlinesIntervalEnum::Interval1s,
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .time_zone = "0",
        .limit = 1,
    };
    const auto res = api.ui_klines(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "uiKlines");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));
    EXPECT_TRUE(sent.contains("interval"));

    EXPECT_TRUE(sent.contains("startTime"));
    EXPECT_TRUE(sent.contains("endTime"));
    EXPECT_TRUE(sent.contains("timeZone"));
    EXPECT_TRUE(sent.contains("limit"));
}

TEST(WebsocketApiMarketApi, UiKlinesErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const UiKlinesParams params{.symbol = "BNBUSDT", .interval = UiKlinesIntervalEnum::Interval1s};
    EXPECT_THROW((void)api.ui_klines(params), common::WebsocketResponseError);
}
