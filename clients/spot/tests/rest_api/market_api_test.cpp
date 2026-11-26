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
#include <binance/spot/rest_api/market_api.hpp>

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

MarketApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return MarketApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiMarketApi, AggTrades) {
    const std::string example =
        R"json([{"a":26129,"p":"0.01633102","q":"4.70443515","f":27781,"l":27781,"T":1498793709153,"m":true,"M":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AggTradesParams params{.symbol = "BNBUSDT"};
    const auto res = api.agg_trades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/aggTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, AggTradesWithOptionalParams) {
    const std::string example =
        R"json([{"a":26129,"p":"0.01633102","q":"4.70443515","f":27781,"l":27781,"T":1498793709153,"m":true,"M":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AggTradesParams params{
        .symbol = "BNBUSDT",
        .from_id = 1,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .limit = 1,
    };
    const auto res = api.agg_trades(params);
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
}

TEST(RestApiMarketApi, AggTradesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AggTradesParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.agg_trades(params), common::BadRequestError);
}

TEST(RestApiMarketApi, AvgPrice) {
    const std::string example =
        R"json({"mins":5,"price":"9.35751834","closeTime":1694061154503})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AvgPriceParams params{.symbol = "BNBUSDT"};
    const auto res = api.avg_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/avgPrice");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, AvgPriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AvgPriceParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.avg_price(params), common::BadRequestError);
}

TEST(RestApiMarketApi, Depth) {
    const std::string example =
        R"json({"lastUpdateId":1027024,"bids":[["4.00000000","431.00000000"]],"asks":[["4.00000200","12.00000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepthParams params{.symbol = "BNBUSDT"};
    const auto res = api.depth(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/depth");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, DepthWithOptionalParams) {
    const std::string example =
        R"json({"lastUpdateId":1027024,"bids":[["4.00000000","431.00000000"]],"asks":[["4.00000200","12.00000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepthParams params{
        .symbol = "BNBUSDT",
        .limit = 1,
        .symbol_status = DepthSymbolStatusEnum::Trading,
    };
    const auto res = api.depth(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbolStatus="), std::string::npos);
}

TEST(RestApiMarketApi, DepthBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DepthParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.depth(params), common::BadRequestError);
}

TEST(RestApiMarketApi, GetTrades) {
    const std::string example =
        R"json([{"id":28457,"price":"4.00000100","qty":"12.00000000","quoteQty":"48.000012","time":1499865549590,"isBuyerMaker":true,"isBestMatch":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetTradesParams params{.symbol = "BNBUSDT"};
    const auto res = api.get_trades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/trades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, GetTradesWithOptionalParams) {
    const std::string example =
        R"json([{"id":28457,"price":"4.00000100","qty":"12.00000000","quoteQty":"48.000012","time":1499865549590,"isBuyerMaker":true,"isBestMatch":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetTradesParams params{
        .symbol = "BNBUSDT",
        .limit = 1,
    };
    const auto res = api.get_trades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketApi, GetTradesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetTradesParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.get_trades(params), common::BadRequestError);
}

TEST(RestApiMarketApi, HistoricalBlockTrades) {
    const std::string example =
        R"json([{"id":582,"price":"0.052","qty":"5838","quoteQty":"303.576","time":1772506983321,"isBuyerMaker":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HistoricalBlockTradesParams params{.symbol = "BNBBTC", .from_id = 582};
    const auto res = api.historical_block_trades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/historicalBlockTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, HistoricalBlockTradesWithOptionalParams) {
    const std::string example =
        R"json([{"id":582,"price":"0.052","qty":"5838","quoteQty":"303.576","time":1772506983321,"isBuyerMaker":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HistoricalBlockTradesParams params{
        .symbol = "BNBBTC",
        .from_id = 582,
        .limit = 500,
    };
    const auto res = api.historical_block_trades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketApi, HistoricalBlockTradesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const HistoricalBlockTradesParams params{.symbol = "BNBBTC", .from_id = 582};
    EXPECT_THROW((void)api.historical_block_trades(params), common::BadRequestError);
}

TEST(RestApiMarketApi, HistoricalTrades) {
    const std::string example =
        R"json([{"id":28457,"price":"4.00000100","qty":"12.00000000","quoteQty":"48.000012","time":1499865549590,"isBuyerMaker":true,"isBestMatch":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HistoricalTradesParams params{.symbol = "BNBUSDT"};
    const auto res = api.historical_trades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/historicalTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, HistoricalTradesWithOptionalParams) {
    const std::string example =
        R"json([{"id":28457,"price":"4.00000100","qty":"12.00000000","quoteQty":"48.000012","time":1499865549590,"isBuyerMaker":true,"isBestMatch":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HistoricalTradesParams params{
        .symbol = "BNBUSDT",
        .limit = 1,
        .from_id = 1,
    };
    const auto res = api.historical_trades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
}

TEST(RestApiMarketApi, HistoricalTradesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const HistoricalTradesParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.historical_trades(params), common::BadRequestError);
}

TEST(RestApiMarketApi, Klines) {
    const std::string example = R"json([[1499040000000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlinesParams params{.symbol = "BNBUSDT", .interval = KlinesIntervalEnum::Interval1s};
    const auto res = api.klines(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/klines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, KlinesWithOptionalParams) {
    const std::string example = R"json([[1499040000000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlinesParams params{
        .symbol = "BNBUSDT",
        .interval = KlinesIntervalEnum::Interval1s,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .time_zone = "0",
        .limit = 1,
    };
    const auto res = api.klines(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeZone="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketApi, KlinesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const KlinesParams params{.symbol = "BNBUSDT", .interval = KlinesIntervalEnum::Interval1s};
    EXPECT_THROW((void)api.klines(params), common::BadRequestError);
}

TEST(RestApiMarketApi, ReferencePrice) {
    const std::string example =
        R"json({"symbol":"BAZUSD","referencePrice":"10.00","timestamp":1770736694138})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ReferencePriceParams params{.symbol = "BNBUSDT"};
    const auto res = api.reference_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/referencePrice");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, ReferencePriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ReferencePriceParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.reference_price(params), common::BadRequestError);
}

TEST(RestApiMarketApi, ReferencePriceCalculation) {
    const std::string example =
        R"json({"symbol":"BAZUSD","calculationType":"ARITHMETIC_MEAN","bucketCount":10,"bucketWidthMs":1000,"externalCalculationId":42})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ReferencePriceCalculationParams params{.symbol = "BNBUSDT"};
    const auto res = api.reference_price_calculation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/referencePrice/calculation");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, ReferencePriceCalculationWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BAZUSD","calculationType":"ARITHMETIC_MEAN","bucketCount":10,"bucketWidthMs":1000,"externalCalculationId":42})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ReferencePriceCalculationParams params{
        .symbol = "BNBUSDT",
        .symbol_status = ReferencePriceCalculationSymbolStatusEnum::Trading,
    };
    const auto res = api.reference_price_calculation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbolStatus="), std::string::npos);
}

TEST(RestApiMarketApi, ReferencePriceCalculationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ReferencePriceCalculationParams params{.symbol = "BNBUSDT"};
    EXPECT_THROW((void)api.reference_price_calculation(params), common::BadRequestError);
}

TEST(RestApiMarketApi, Ticker) {
    const std::string example =
        R"json({"symbol":"LTCBTC","priceChange":"-8.00000000","priceChangePercent":"-88.889","weightedAvgPrice":"2.60427807","openPrice":"0.10000000","highPrice":"2.00000000","lowPrice":"0.10000000","lastPrice":"2.00000000","volume":"39.00000000","quoteVolume":"13.40000000","openTime":1656986580000,"closeTime":1657001016795,"firstId":0,"lastId":34,"count":35})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TickerParams params{};
    const auto res = api.ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/ticker");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, TickerWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"LTCBTC","priceChange":"-8.00000000","priceChangePercent":"-88.889","weightedAvgPrice":"2.60427807","openPrice":"0.10000000","highPrice":"2.00000000","lowPrice":"0.10000000","lastPrice":"2.00000000","volume":"39.00000000","quoteVolume":"13.40000000","openTime":1656986580000,"closeTime":1657001016795,"firstId":0,"lastId":34,"count":35})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TickerParams params{
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .window_size = TickerWindowSizeEnum::WindowSize1m,
        .type = TickerTypeEnum::Full,
        .symbol_status = TickerSymbolStatusEnum::Trading,
    };
    const auto res = api.ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("windowSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbolStatus="), std::string::npos);
}

TEST(RestApiMarketApi, TickerBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TickerParams params{};
    EXPECT_THROW((void)api.ticker(params), common::BadRequestError);
}

TEST(RestApiMarketApi, Ticker24hr) {
    const std::string example =
        R"json({"symbol":"BNBBTC","priceChange":"-94.99999800","priceChangePercent":"-95.960","weightedAvgPrice":"0.29628482","prevClosePrice":"0.10002000","lastPrice":"4.00000200","lastQty":"200.00000000","bidPrice":"4.00000000","bidQty":"100.00000000","askPrice":"4.00000200","askQty":"100.00000000","openPrice":"99.00000000","highPrice":"100.00000000","lowPrice":"0.10000000","volume":"8913.30000000","quoteVolume":"15.30000000","openTime":1499783499040,"closeTime":1499869899040,"firstId":28385,"lastId":28460,"count":76})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const Ticker24hrParams params{};
    const auto res = api.ticker24hr(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/ticker/24hr");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, Ticker24hrWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BNBBTC","priceChange":"-94.99999800","priceChangePercent":"-95.960","weightedAvgPrice":"0.29628482","prevClosePrice":"0.10002000","lastPrice":"4.00000200","lastQty":"200.00000000","bidPrice":"4.00000000","bidQty":"100.00000000","askPrice":"4.00000200","askQty":"100.00000000","openPrice":"99.00000000","highPrice":"100.00000000","lowPrice":"0.10000000","volume":"8913.30000000","quoteVolume":"15.30000000","openTime":1499783499040,"closeTime":1499869899040,"firstId":28385,"lastId":28460,"count":76})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const Ticker24hrParams params{
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .type = Ticker24hrTypeEnum::Full,
        .symbol_status = Ticker24hrSymbolStatusEnum::Trading,
    };
    const auto res = api.ticker24hr(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbolStatus="), std::string::npos);
}

TEST(RestApiMarketApi, Ticker24hrBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const Ticker24hrParams params{};
    EXPECT_THROW((void)api.ticker24hr(params), common::BadRequestError);
}

TEST(RestApiMarketApi, TickerBookTicker) {
    const std::string example =
        R"json({"symbol":"LTCBTC","bidPrice":"4.00000000","bidQty":"431.00000000","askPrice":"4.00000200","askQty":"9.00000000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TickerBookTickerParams params{};
    const auto res = api.ticker_book_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/ticker/bookTicker");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, TickerBookTickerWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"LTCBTC","bidPrice":"4.00000000","bidQty":"431.00000000","askPrice":"4.00000200","askQty":"9.00000000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TickerBookTickerParams params{
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .symbol_status = TickerBookTickerSymbolStatusEnum::Trading,
    };
    const auto res = api.ticker_book_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbolStatus="), std::string::npos);
}

TEST(RestApiMarketApi, TickerBookTickerBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TickerBookTickerParams params{};
    EXPECT_THROW((void)api.ticker_book_ticker(params), common::BadRequestError);
}

TEST(RestApiMarketApi, TickerPrice) {
    const std::string example = R"json({"symbol":"LTCBTC","price":"4.00000200"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TickerPriceParams params{};
    const auto res = api.ticker_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/ticker/price");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, TickerPriceWithOptionalParams) {
    const std::string example = R"json({"symbol":"LTCBTC","price":"4.00000200"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TickerPriceParams params{
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .symbol_status = TickerPriceSymbolStatusEnum::Trading,
    };
    const auto res = api.ticker_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbolStatus="), std::string::npos);
}

TEST(RestApiMarketApi, TickerPriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TickerPriceParams params{};
    EXPECT_THROW((void)api.ticker_price(params), common::BadRequestError);
}

TEST(RestApiMarketApi, TickerTradingDay) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","priceChange":"-83.13000000","priceChangePercent":"-0.317","weightedAvgPrice":"26234.58803036","openPrice":"26304.80000000","highPrice":"26397.46000000","lowPrice":"26088.34000000","lastPrice":"26221.67000000","volume":"18495.35066000","quoteVolume":"485217905.04210480","openTime":1695686400000,"closeTime":1695772799999,"firstId":3220151555,"lastId":3220849281,"count":697727})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TickerTradingDayParams params{};
    const auto res = api.ticker_trading_day(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/ticker/tradingDay");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, TickerTradingDayWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","priceChange":"-83.13000000","priceChangePercent":"-0.317","weightedAvgPrice":"26234.58803036","openPrice":"26304.80000000","highPrice":"26397.46000000","lowPrice":"26088.34000000","lastPrice":"26221.67000000","volume":"18495.35066000","quoteVolume":"485217905.04210480","openTime":1695686400000,"closeTime":1695772799999,"firstId":3220151555,"lastId":3220849281,"count":697727})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TickerTradingDayParams params{
        .symbol = "BNBUSDT",
        .symbols = std::vector<std::string>{},
        .time_zone = "0",
        .type = TickerTradingDayTypeEnum::Full,
        .symbol_status = TickerTradingDaySymbolStatusEnum::Trading,
    };
    const auto res = api.ticker_trading_day(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeZone="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbolStatus="), std::string::npos);
}

TEST(RestApiMarketApi, TickerTradingDayBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TickerTradingDayParams params{};
    EXPECT_THROW((void)api.ticker_trading_day(params), common::BadRequestError);
}

TEST(RestApiMarketApi, UiKlines) {
    const std::string example = R"json([[1499040000000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UiKlinesParams params{.symbol = "BNBUSDT", .interval = UiKlinesIntervalEnum::Interval1s};
    const auto res = api.ui_klines(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/api/v3/uiKlines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketApi, UiKlinesWithOptionalParams) {
    const std::string example = R"json([[1499040000000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UiKlinesParams params{
        .symbol = "BNBUSDT",
        .interval = UiKlinesIntervalEnum::Interval1s,
        .start_time = 1735693200000,
        .end_time = 1735693200000,
        .time_zone = "0",
        .limit = 1,
    };
    const auto res = api.ui_klines(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeZone="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketApi, UiKlinesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UiKlinesParams params{.symbol = "BNBUSDT", .interval = UiKlinesIntervalEnum::Interval1s};
    EXPECT_THROW((void)api.ui_klines(params), common::BadRequestError);
}
