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
#include <binance/derivatives_trading_options/rest_api/market_data_api.hpp>

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

MarketDataApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return MarketDataApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiMarketDataApi, CheckServerTime) {
    const std::string example = R"json({"serverTime":1592387156596})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.check_server_time();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/time");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CheckServerTimeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.check_server_time(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, ExchangeInformation) {
    const std::string example =
        R"json({"timezone":"UTC","serverTime":1592387337630,"optionContracts":[{"baseAsset":"BTC","quoteAsset":"USDT","underlying":"BTCUSDT","settleAsset":"USDT"}],"optionAssets":[{"name":"USDT"}],"optionSymbols":[{"expiryDate":1660521600000,"filters":[{"filterType":"PRICE_FILTER","minPrice":"0.02","maxPrice":"80000.01","tickSize":"0.01","minQty":"0.01","maxQty":"100","stepSize":"0.01"}],"symbol":"BTC-220815-50000-C","side":"CALL","strikePrice":"50000","underlying":"BTCUSDT","unit":1,"liquidationFeeRate":"0.0019000","minQty":"0.01","maxQty":"100","initialMargin":"0.15","maintenanceMargin":"0.075","minInitialMargin":"0.1","minMaintenanceMargin":"0.05","priceScale":2,"quantityScale":2,"quoteAsset":"USDT","contractType":"CRYPTO_OPTIONS","underlyingType":"CRYPTO","nakedSell":false,"status":"TRADING"}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.exchange_information();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/exchangeInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ExchangeInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.exchange_information(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, HistoricalExerciseRecords) {
    const std::string example =
        R"json([{"symbol":"BTC-220121-60000-P","strikePrice":"60000","realStrikePrice":"38844.69652571","expiryDate":1642752000000,"strikeResult":"REALISTIC_VALUE_STRICKEN"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HistoricalExerciseRecordsParams params{};
    const auto res = api.historical_exercise_records(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/exerciseHistory");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, HistoricalExerciseRecordsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTC-220121-60000-P","strikePrice":"60000","realStrikePrice":"38844.69652571","expiryDate":1642752000000,"strikeResult":"REALISTIC_VALUE_STRICKEN"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HistoricalExerciseRecordsParams params{
        .underlying = "BTCUSDT",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 20,
    };
    const auto res = api.historical_exercise_records(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, HistoricalExerciseRecordsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const HistoricalExerciseRecordsParams params{};
    EXPECT_THROW((void)api.historical_exercise_records(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, IndexPrice) {
    const std::string example = R"json({"time":1656647305000,"indexPrice":"105917.75"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const IndexPriceParams params{.underlying = "BTCUSDT"};
    const auto res = api.index_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/index");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, IndexPriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const IndexPriceParams params{.underlying = "BTCUSDT"};
    EXPECT_THROW((void)api.index_price(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, KlineCandlestickData) {
    const std::string example = R"json([[1762779600000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlineCandlestickDataParams params{
        .symbol = "BTC-200730-9000-C", .interval = KlineCandlestickDataIntervalEnum::Interval1m};
    const auto res = api.kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/klines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, KlineCandlestickDataWithOptionalParams) {
    const std::string example = R"json([[1762779600000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlineCandlestickDataParams params{
        .symbol = "BTC-200730-9000-C",
        .interval = KlineCandlestickDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 20,
    };
    const auto res = api.kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, KlineCandlestickDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const KlineCandlestickDataParams params{
        .symbol = "BTC-200730-9000-C", .interval = KlineCandlestickDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.kline_candlestick_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OpenInterest) {
    const std::string example =
        R"json([{"symbol":"ETH-221119-1175-P","sumOpenInterest":"4.01","sumOpenInterestUsd":"4880.2985615624","timestamp":"1668754020000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OpenInterestParams params{.underlying_asset = "ETH/BTC", .expiration = "221225"};
    const auto res = api.open_interest(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/openInterest");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("expiration="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OpenInterestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OpenInterestParams params{.underlying_asset = "ETH/BTC", .expiration = "221225"};
    EXPECT_THROW((void)api.open_interest(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OptionMarkPrice) {
    const std::string example =
        R"json([{"symbol":"BTC-200730-9000-C","markPrice":"1343.2883","bidIV":"1.40000077","askIV":"1.50000153","markIV":"1.45000000","delta":"0.55937056","theta":"3739.82509871","gamma":"0.00010969","vega":"978.58874732","highPriceLimit":"1618.241","lowPriceLimit":"1068.3356","riskFreeInterest":"0.1"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionMarkPriceParams params{};
    const auto res = api.option_mark_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/mark");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OptionMarkPriceWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTC-200730-9000-C","markPrice":"1343.2883","bidIV":"1.40000077","askIV":"1.50000153","markIV":"1.45000000","delta":"0.55937056","theta":"3739.82509871","gamma":"0.00010969","vega":"978.58874732","highPriceLimit":"1618.241","lowPriceLimit":"1068.3356","riskFreeInterest":"0.1"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionMarkPriceParams params{
        .symbol = "BTC-200730-9000-C",
    };
    const auto res = api.option_mark_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, OptionMarkPriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionMarkPriceParams params{};
    EXPECT_THROW((void)api.option_mark_price(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OrderBook) {
    const std::string example =
        R"json({"bids":[["1000.000","0.1000"]],"asks":[["1900.000","0.1000"]],"T":1762780909676,"lastUpdateId":361})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderBookParams params{.symbol = "BTC-200730-9000-C"};
    const auto res = api.order_book(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/depth");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OrderBookWithOptionalParams) {
    const std::string example =
        R"json({"bids":[["1000.000","0.1000"]],"asks":[["1900.000","0.1000"]],"T":1762780909676,"lastUpdateId":361})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderBookParams params{
        .symbol = "BTC-200730-9000-C",
        .limit = 20,
    };
    const auto res = api.order_book(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, OrderBookBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderBookParams params{.symbol = "BTC-200730-9000-C"};
    EXPECT_THROW((void)api.order_book(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, RecentBlockTradesList) {
    const std::string example =
        R"json([{"id":1125899906901081100,"tradeId":389,"symbol":"ETH-250725-1200-P","price":"342.40","qty":"-2167.20","quoteQty":"-4.90","side":-1,"time":1733950676483}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RecentBlockTradesListParams params{};
    const auto res = api.recent_block_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/blockTrades");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, RecentBlockTradesListWithOptionalParams) {
    const std::string example =
        R"json([{"id":1125899906901081100,"tradeId":389,"symbol":"ETH-250725-1200-P","price":"342.40","qty":"-2167.20","quoteQty":"-4.90","side":-1,"time":1733950676483}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RecentBlockTradesListParams params{
        .symbol = "BTC-200730-9000-C",
        .limit = 20,
    };
    const auto res = api.recent_block_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, RecentBlockTradesListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RecentBlockTradesListParams params{};
    EXPECT_THROW((void)api.recent_block_trades_list(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, RecentTradesList) {
    const std::string example =
        R"json([{"id":2323857420768529000,"tradeId":1,"symbol":"BTC-251123-126000-C","price":"1300","qty":"0.1","quoteQty":"130","side":-1,"time":1762780453623}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RecentTradesListParams params{.symbol = "BTC-200730-9000-C"};
    const auto res = api.recent_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/trades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, RecentTradesListWithOptionalParams) {
    const std::string example =
        R"json([{"id":2323857420768529000,"tradeId":1,"symbol":"BTC-251123-126000-C","price":"1300","qty":"0.1","quoteQty":"130","side":-1,"time":1762780453623}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RecentTradesListParams params{
        .symbol = "BTC-200730-9000-C",
        .limit = 20,
    };
    const auto res = api.recent_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, RecentTradesListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RecentTradesListParams params{.symbol = "BTC-200730-9000-C"};
    EXPECT_THROW((void)api.recent_trades_list(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TestConnectivity) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.test_connectivity();
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/ping");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TestConnectivityBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.test_connectivity(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, Ticker24hrPriceChangeStatistics) {
    const std::string example =
        R"json([{"symbol":"BTC-200730-9000-C","priceChange":"-16.2038","priceChangePercent":"-0.0162","lastPrice":"1000","lastQty":"1000","open":"1016.2038","high":"1016.2038","low":"0","volume":"5","amount":"1","bidPrice":"999.34","askPrice":"1000.23","openTime":1592317127349,"closeTime":1592380593516,"firstTradeId":1,"tradeCount":5,"strikePrice":"9000","exercisePrice":"3000.3356"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const Ticker24hrPriceChangeStatisticsParams params{};
    const auto res = api.ticker24hr_price_change_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/ticker");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, Ticker24hrPriceChangeStatisticsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTC-200730-9000-C","priceChange":"-16.2038","priceChangePercent":"-0.0162","lastPrice":"1000","lastQty":"1000","open":"1016.2038","high":"1016.2038","low":"0","volume":"5","amount":"1","bidPrice":"999.34","askPrice":"1000.23","openTime":1592317127349,"closeTime":1592380593516,"firstTradeId":1,"tradeCount":5,"strikePrice":"9000","exercisePrice":"3000.3356"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const Ticker24hrPriceChangeStatisticsParams params{
        .symbol = "BTC-200730-9000-C",
    };
    const auto res = api.ticker24hr_price_change_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, Ticker24hrPriceChangeStatisticsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const Ticker24hrPriceChangeStatisticsParams params{};
    EXPECT_THROW((void)api.ticker24hr_price_change_statistics(params), common::BadRequestError);
}
