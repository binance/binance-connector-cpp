//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string>

#include <gtest/gtest.h>

#include <binance/alpha/rest_api/market_data_api.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/rest.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::alpha::rest_api;
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

TEST(RestApiMarketDataApi, AggregatedTrades) {
    const std::string example =
        R"json({"code":"000000","message":"","messageDetail":"","data":[{"a":58470,"p":"1.00","q":"1.00","f":58470,"l":58665,"T":1752568680000,"m":true}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AggregatedTradesParams params{.symbol = "ALPHA_118USDC"};
    const auto res = api.aggregated_trades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/bapi/defi/v1/public/alpha-trade/agg-trades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, AggregatedTradesWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"","messageDetail":"","data":[{"a":58470,"p":"1.00","q":"1.00","f":58470,"l":58665,"T":1752568680000,"m":true}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AggregatedTradesParams params{
        .symbol = "ALPHA_118USDC",
        .from_id = 58470,
        .start_time = 1752568680000,
        .end_time = 1752572280000,
        .limit = 500,
    };
    const auto res = api.aggregated_trades(params);
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

TEST(RestApiMarketDataApi, AggregatedTradesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AggregatedTradesParams params{.symbol = "ALPHA_118USDC"};
    EXPECT_THROW((void)api.aggregated_trades(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, FullDepth) {
    const std::string example =
        R"json({"code":"000000","message":"message","messageDetail":"messageDetail","success":true,"data":{"lastUpdateId":47534656223,"symbol":"ALPHA_175USDT","bids":[["0.00040161","365980.85000000"]],"asks":[["0.00046996","61994.70000000"]],"E":1775027836086,"T":1775027836072}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FullDepthParams params{.symbol = "ALPHA_175USDT"};
    const auto res = api.full_depth(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/bapi/defi/v1/public/alpha-trade/fullDepth");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, FullDepthWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"message","messageDetail":"messageDetail","success":true,"data":{"lastUpdateId":47534656223,"symbol":"ALPHA_175USDT","bids":[["0.00040161","365980.85000000"]],"asks":[["0.00046996","61994.70000000"]],"E":1775027836086,"T":1775027836072}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FullDepthParams params{
        .symbol = "ALPHA_175USDT",
        .limit = FullDepthLimitEnum::Limit5,
    };
    const auto res = api.full_depth(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, FullDepthBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FullDepthParams params{.symbol = "ALPHA_175USDT"};
    EXPECT_THROW((void)api.full_depth(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetExchangeInfo) {
    const std::string example =
        R"json({"code":"000000","message":"","messageDetail":"","success":true,"data":{"timezone":"UTC","assets":[{"asset":"USDT"}],"symbols":[{"symbol":"ALPHA_105USDT","status":"TRADING","baseAsset":"ALPHA_105","quoteAsset":"USDT","pricePrecision":8,"quantityPrecision":8,"baseAssetPrecision":8,"quotePrecision":8,"filters":[{"filterType":"PRICE_FILTER","minPrice":"0.00000001","maxPrice":"1000","tickSize":"0.00000001","stepSize":"0.01000000","maxQty":"277778","minQty":"0.01000000","limit":200,"minNotional":"0.1","maxNotional":"1000000","multiplierDown":"0.20000","multiplierUp":"5","bidMultiplierUp":"5","askMultiplierUp":"5","bidMultiplierDown":"0.20000","askMultiplierDown":"0.20000"}],"orderTypes":["LIMIT"]}],"orderTypes":""}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.get_exchange_info();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/bapi/defi/v1/public/alpha-trade/get-exchange-info");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetExchangeInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.get_exchange_info(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, Klines) {
    const std::string example =
        R"json({"code":"000000","message":"","messageDetail":"","success":true,"data":[["1752642000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlinesParams params{.symbol = "ALPHA_175USDT",
                              .interval = KlinesIntervalEnum::Interval1s};
    const auto res = api.klines(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/bapi/defi/v1/public/alpha-trade/klines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, KlinesWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"","messageDetail":"","success":true,"data":[["1752642000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlinesParams params{
        .symbol = "ALPHA_175USDT",
        .interval = KlinesIntervalEnum::Interval1s,
        .limit = 500,
        .start_time = 1752642000000,
        .end_time = 1752645599999,
    };
    const auto res = api.klines(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, KlinesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const KlinesParams params{.symbol = "ALPHA_175USDT",
                              .interval = KlinesIntervalEnum::Interval1s};
    EXPECT_THROW((void)api.klines(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, Ticker) {
    const std::string example =
        R"json({"code":"000000","message":"","messageDetail":"","data":{"symbol":"ALPHA_175USDT","priceChange":"-0.00007172","priceChangePercent":"-8.841","weightedAvgPrice":"0.00079608","lastPrice":"0.00073954","lastQty":"12600.43000000","openPrice":"0.00081126","highPrice":"0.00081126","lowPrice":"0.00073954","volume":"1204754.30000000","quoteVolume":"959.07729927","openTime":1768808100000,"closeTime":1768893244772,"firstId":93742,"lastId":93768,"count":38},"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TickerParams params{.symbol = "ALPHA_175USDT"};
    const auto res = api.ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/bapi/defi/v1/public/alpha-trade/ticker");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TickerBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TickerParams params{.symbol = "ALPHA_175USDT"};
    EXPECT_THROW((void)api.ticker(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TokenList) {
    const std::string example =
        R"json({"code":"000000","message":"","messageDetail":"","success":true,"data":[{"tokenId":"3F350C8B3621770A673159B7A19BC034","chainId":"56","chainIconUrl":"https://bin.bnbstatic.com/image/admin_mgs_image_upload/20250228/d0216ce4-a3e9-4bda-8937-4a6aa943ccf2.png","chainName":"BSC","contractAddress":"0xcf640fdf9b3d9e45cbd69fda91d7e22579c14444","name":"gorilla","symbol":"gorilla","iconUrl":"https://bin.bnbstatic.com/images/web3-data/public/token/logos/248b5406f88a4ee28913a29107875339.png","price":"0.00080595003978242023","percentChange24h":"-7.42","volume24h":"14847.711222633409558029675","marketCap":"805950.03978242","fdv":"805950.03978242","liquidity":"263192.72813121626034","totalSupply":"1000000000","circulatingSupply":"1000000000","holders":"7120","decimals":18,"listingCex":false,"hotTag":false,"cexCoinName":"","canTransfer":false,"denomination":1,"offline":false,"tradeDecimal":8,"alphaId":"ALPHA_175","offsell":false,"priceHigh24h":"0.00088873864475645879","priceLow24h":"0.0008020805165487083","count24h":"166","onlineTge":false,"onlineAirdrop":false,"score":1,"cexOffDisplay":false,"stockState":false,"listingTime":1746686700000,"mulPoint":1,"bnExclusiveState":false}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.token_list();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/bapi/defi/v1/public/wallet-direct/buw/wallet/cex/alpha/all/token/list");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TokenListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.token_list(), common::BadRequestError);
}
