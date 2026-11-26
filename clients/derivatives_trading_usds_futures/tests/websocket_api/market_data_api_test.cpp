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
#include <binance/derivatives_trading_usds_futures/websocket_api/market_data_api.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_usds_futures::websocket_api;
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

MarketDataApi api_for(const MockWsServer& server) {
    common::WebsocketApiConfig cfg;
    cfg.url = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    cfg.proxy_from_env = false;
    auto client = std::make_shared<common::WebsocketApi>(std::move(cfg));
    client->connect();
    return MarketDataApi(std::move(client));
}

boost::json::object first_request(const MockWsServer& server) {
    return boost::json::parse(server.sessions().front().received.front()).as_object();
}

} // namespace

TEST(WebsocketApiMarketDataApi, OrderBook) {
    MockWsServer server(reply(
        R"json({"id":"51e2affb-0aba-4821-ba75-f2625006eb43","status":200,"result":{"lastUpdateId":1027024,"E":1589436922972,"T":1589436922959},"bids":[["4.00000000","431.00000000"]],"asks":[["4.00000200","12.00000000"]],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":5}]})json"));
    const auto api = api_for(server);
    const OrderBookParams params{.symbol = "BTCUSDT"};
    const auto res = api.order_book(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "depth");
}

TEST(WebsocketApiMarketDataApi, OrderBookWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"51e2affb-0aba-4821-ba75-f2625006eb43","status":200,"result":{"lastUpdateId":1027024,"E":1589436922972,"T":1589436922959},"bids":[["4.00000000","431.00000000"]],"asks":[["4.00000200","12.00000000"]],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":5}]})json"));
    const auto api = api_for(server);
    const OrderBookParams params{
        .symbol = "BTCUSDT",
        .id = "e9d6b4349871b40611412680b3445fac",
        .limit = 10,
    };
    const auto res = api.order_book(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "depth");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
    EXPECT_TRUE(sent.contains("symbol"));

    EXPECT_TRUE(sent.contains("limit"));
}

TEST(WebsocketApiMarketDataApi, OrderBookErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const OrderBookParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.order_book(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketDataApi, SymbolOrderBookTicker) {
    MockWsServer server(reply(
        R"json({"id":"9d32157c-a556-4d27-9866-66760a174b57","status":200,"result":{"lastUpdateId":1027024,"symbol":"BTCUSDT","bidPrice":"4.00000000","bidQty":"431.00000000","askPrice":"4.00000200","askQty":"9.00000000","time":1589437530011},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const SymbolOrderBookTickerParams params{};
    const auto res = api.symbol_order_book_ticker(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.book");
}

TEST(WebsocketApiMarketDataApi, SymbolOrderBookTickerWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"9d32157c-a556-4d27-9866-66760a174b57","status":200,"result":{"lastUpdateId":1027024,"symbol":"BTCUSDT","bidPrice":"4.00000000","bidQty":"431.00000000","askPrice":"4.00000200","askQty":"9.00000000","time":1589437530011},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const SymbolOrderBookTickerParams params{
        .id = "e9d6b4349871b40611412680b3445fac",
        .symbol = "BTCUSDT",
    };
    const auto res = api.symbol_order_book_ticker(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.book");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
}

TEST(WebsocketApiMarketDataApi, SymbolOrderBookTickerErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const SymbolOrderBookTickerParams params{};
    EXPECT_THROW((void)api.symbol_order_book_ticker(params), common::WebsocketResponseError);
}

TEST(WebsocketApiMarketDataApi, SymbolPriceTicker) {
    MockWsServer server(reply(
        R"json({"id":"9d32157c-a556-4d27-9866-66760a174b57","status":200,"result":{"symbol":"BTCUSDT","price":"6000.01","time":1589437530011},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const SymbolPriceTickerParams params{};
    const auto res = api.symbol_price_ticker(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.price");
}

TEST(WebsocketApiMarketDataApi, SymbolPriceTickerWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"9d32157c-a556-4d27-9866-66760a174b57","status":200,"result":{"symbol":"BTCUSDT","price":"6000.01","time":1589437530011},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const SymbolPriceTickerParams params{
        .id = "e9d6b4349871b40611412680b3445fac",
        .symbol = "BTCUSDT",
    };
    const auto res = api.symbol_price_ticker(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "ticker.price");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("symbol"));
}

TEST(WebsocketApiMarketDataApi, SymbolPriceTickerErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const SymbolPriceTickerParams params{};
    EXPECT_THROW((void)api.symbol_price_ticker(params), common::WebsocketResponseError);
}
