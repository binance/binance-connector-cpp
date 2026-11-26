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
#include <binance/w3w_prediction/rest_api/market_data_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::w3w_prediction::rest_api;
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

TEST(RestApiMarketDataApi, GetMarketDetail) {
    const std::string example =
        R"json({"marketTopicId":4229564,"vendor":"PREDICT_FUN","chainId":"56","slug":"btc-price-1h-up-or-down","title":"BTC Price 1h Up or Down?","question":"Will BTC price go UP in the next 1 hour?","description":"Resolves YES if BTC spot price is higher than the starting price at resolution time.","imageUrl":"https://cdn.example.com/prediction/btc-1h.png","topicType":"FLAT","chartType":"CRYPTO_UP_DOWN","symbol":"BTCUSDT","variantData":{"type":"CRYPTO_UP_DOWN","startPrice":"67890.12","endPrice":"endPrice","priceFeedId":"0xpricefeedid123","priceFeedProvider":"BINANCE","priceFeedSymbol":"BTCUSDT"},"participantCount":3420,"collateral":"USDT","feeRateBps":200,"slippageBps":1200,"isYieldBearing":false,"tradeVolume":"158234.56","liquidity":"45000.00","publishedAt":1748100000000,"startDate":1748131200000,"endDate":1748134800000,"status":"REGISTERED","timeline":[{"marketTopicId":4229560,"startDate":1748127600000,"endDate":1748131200000}],"markets":[{"marketId":5567895,"externalId":"ext_001","title":"UP","question":"Will BTC go UP?","description":"Resolves YES if BTC price increases.","conditionId":"0xabc123","status":"REGISTERED","tradingStatus":"OPEN","tradeVolume":"90000.00","liquidity":"25000.00","decimalPrecision":2,"outcomes":[{"name":"YES","price":"0.52","chance":"0.52","index":0,"tokenId":"112233","winner":true}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetMarketDetailParams params{.market_topic_id = 4229564};
    const auto res = api.get_market_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/market/detail");
    EXPECT_NE((rec.query() + "&" + rec.body).find("marketTopicId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetMarketDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetMarketDetailParams params{.market_topic_id = 4229564};
    EXPECT_THROW((void)api.get_market_detail(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, ListPredictionCategories) {
    const std::string example =
        R"json({"categories":[{"id":"crypto","name":"Crypto","icon":"crypto_icon","order":1,"subcategories":[{"id":"up-down","name":"Up/Down","icon":"updown_icon","order":1}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.list_prediction_categories();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/category/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ListPredictionCategoriesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.list_prediction_categories(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, ListPredictionMarkets) {
    const std::string example =
        R"json({"marketTopics":[{"marketTopicId":4229564,"vendor":"PREDICT_FUN","chainId":"56","slug":"btc-price-1h-up-or-down","title":"BTC Price 1h Up or Down?","question":"Will BTC price go UP in the next 1 hour?","description":"Resolves YES if BTC spot price is higher than the starting price at resolution time.","imageUrl":"https://cdn.example.com/prediction/btc-1h.png","topicType":"FLAT","chartType":"CRYPTO_UP_DOWN","symbol":"BTCUSDT","participantCount":3420,"collateral":"USDT","feeRateBps":200,"slippageBps":1200,"isYieldBearing":false,"tradeVolume":"158234.56","liquidity":"45000.00","publishedAt":1748100000000,"startDate":1748131200000,"endDate":1748134800000,"status":"REGISTERED","markets":[{}]}],"total":128,"offset":0,"limit":20,"hasMore":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ListPredictionMarketsParams params{};
    const auto res = api.list_prediction_markets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/market/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ListPredictionMarketsWithOptionalParams) {
    const std::string example =
        R"json({"marketTopics":[{"marketTopicId":4229564,"vendor":"PREDICT_FUN","chainId":"56","slug":"btc-price-1h-up-or-down","title":"BTC Price 1h Up or Down?","question":"Will BTC price go UP in the next 1 hour?","description":"Resolves YES if BTC spot price is higher than the starting price at resolution time.","imageUrl":"https://cdn.example.com/prediction/btc-1h.png","topicType":"FLAT","chartType":"CRYPTO_UP_DOWN","symbol":"BTCUSDT","participantCount":3420,"collateral":"USDT","feeRateBps":200,"slippageBps":1200,"isYieldBearing":false,"tradeVolume":"158234.56","liquidity":"45000.00","publishedAt":1748100000000,"startDate":1748131200000,"endDate":1748134800000,"status":"REGISTERED","markets":[{}]}],"total":128,"offset":0,"limit":20,"hasMore":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ListPredictionMarketsParams params{
        .l1_category = "crypto",
        .l2_category = "up-down",
        .sort_by = ListPredictionMarketsSortByEnum::Recommended,
        .order_by = ListPredictionMarketsOrderByEnum::Asc,
        .offset = 0,
        .limit = 20,
    };
    const auto res = api.list_prediction_markets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("l1Category="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("l2Category="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sortBy="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderBy="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ListPredictionMarketsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ListPredictionMarketsParams params{};
    EXPECT_THROW((void)api.list_prediction_markets(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, MarketSearch) {
    const std::string example =
        R"json([{"marketTopicId":4229564,"vendor":"PREDICT_FUN","chainId":"56","slug":"btc-price-1h-up-or-down","title":"BTC Price 1h Up or Down?","question":"Will BTC price go UP in the next 1 hour?","description":"Resolves YES if BTC spot price is higher than the starting price.","topicType":"FLAT","chartType":"CRYPTO_UP_DOWN","symbol":"BTCUSDT","participantCount":3420,"collateral":"USDT","tradeVolume":"158234.56","liquidity":"45000.00","startDate":1748131200000,"endDate":1748134800000,"status":"REGISTERED","markets":[{}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarketSearchParams params{.query = "BTC price"};
    const auto res = api.market_search(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/market/search");
    EXPECT_NE((rec.query() + "&" + rec.body).find("query="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, MarketSearchWithOptionalParams) {
    const std::string example =
        R"json([{"marketTopicId":4229564,"vendor":"PREDICT_FUN","chainId":"56","slug":"btc-price-1h-up-or-down","title":"BTC Price 1h Up or Down?","question":"Will BTC price go UP in the next 1 hour?","description":"Resolves YES if BTC spot price is higher than the starting price.","topicType":"FLAT","chartType":"CRYPTO_UP_DOWN","symbol":"BTCUSDT","participantCount":3420,"collateral":"USDT","tradeVolume":"158234.56","liquidity":"45000.00","startDate":1748131200000,"endDate":1748134800000,"status":"REGISTERED","markets":[{}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarketSearchParams params{
        .query = "BTC price",
        .top_k = 20,
    };
    const auto res = api.market_search(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("query="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("topK="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, MarketSearchBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarketSearchParams params{.query = "BTC price"};
    EXPECT_THROW((void)api.market_search(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryLastTradePrice) {
    const std::string example = R"json({"marketId":5567895,"lastTradePrice":"0.52"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryLastTradePriceParams params{.market_id = 5567895};
    const auto res = api.query_last_trade_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/order-book/last-trade-price");
    EXPECT_NE((rec.query() + "&" + rec.body).find("marketId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryLastTradePriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryLastTradePriceParams params{.market_id = 5567895};
    EXPECT_THROW((void)api.query_last_trade_price(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryOrderBook) {
    const std::string example =
        R"json({"outcome":"YES","tokenId":"112233","timestamp":1748131800000,"bids":[{"price":"0.51","size":"5000.00"}],"asks":[{"price":"0.52","size":"3000.00"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOrderBookParams params{
        .vendor = "predict_fun", .market_id = 5567895, .token_id = "112233"};
    const auto res = api.query_order_book(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/order-book");
    EXPECT_NE((rec.query() + "&" + rec.body).find("vendor="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marketId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryOrderBookBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryOrderBookParams params{
        .vendor = "predict_fun", .market_id = 5567895, .token_id = "112233"};
    EXPECT_THROW((void)api.query_order_book(params), common::BadRequestError);
}
