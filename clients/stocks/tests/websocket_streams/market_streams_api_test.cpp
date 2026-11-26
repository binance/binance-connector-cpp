//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <atomic>
#include <chrono>
#include <future>
#include <string>

#include <boost/json/parse.hpp>
#include <boost/json/serialize.hpp>
#include <gtest/gtest.h>

#include <binance/stocks/websocket_streams.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::stocks::websocket_streams;
using binance::test::MockWsServer;

namespace {

// Acknowledges SUBSCRIBE and UNSUBSCRIBE requests.
void ack(MockWsServer::Session& s, const std::string& text) {
    const auto req = boost::json::parse(text).as_object();
    s.send(boost::json::serialize(boost::json::object{{"result", nullptr}, {"id", req.at("id")}}));
}

WebsocketStreamsConnection streams_for(const MockWsServer& server) {
    common::WebsocketStreamsConfig cfg;
    cfg.url = server.url();
    cfg.proxy_from_env = false;
    return stocks::StocksWebsocketStreams::from_config(std::move(cfg)).connect();
}

// The first stream the client subscribed to, or an empty string after a timeout.
std::string subscribed_stream(const MockWsServer& server) {
    std::string name;
    (void)server.wait([&](const auto& sessions) {
        for (const auto& session : sessions) {
            for (const auto& text : session.received) {
                const auto req = boost::json::parse(text).as_object();
                if (req.at("method").as_string() == "SUBSCRIBE") {
                    name = req.at("params").as_array().at(0).as_string();
                    return true;
                }
            }
        }
        return false;
    });
    return name;
}

// Pushes `example` (a spec event, or an empty object) on `stream`, and waits until `stream`
// delivers it parsed.
template <class Stream>
bool delivers(MockWsServer& server, Stream& stream, const std::string& example) {
    std::promise<void> received;
    std::atomic<bool> once{false};
    stream.on_message([&](const auto&) {
        if (!once.exchange(true)) {
            received.set_value();
        }
    });
    const auto name = subscribed_stream(server);
    if (name.empty()) {
        return false;
    }
    const auto event = boost::json::parse(example.empty() ? "{}" : example);
    server.broadcast(
        boost::json::serialize(boost::json::object{{"stream", name}, {"data", event}}));
    const bool ok =
        received.get_future().wait_for(std::chrono::seconds(5)) == std::future_status::ready;
    stream.on_message([](const auto&) {});
    return ok;
}

} // namespace

TEST(WebsocketStreamsMarketStreamsApi, CalendarStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const CalendarStreamParams params{};
    auto stream = client.calendar_stream(params);
    EXPECT_EQ(subscribed_stream(server), "calendar");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"calendar","from":"PRE_MARKET","to":"MARKET_OPEN","ts":1710334200000})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketStreamsApi, KlineStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const KlineStreamParams params{.symbol = "AAPL", .interval = "5m"};
    auto stream = client.kline_stream(params);
    EXPECT_EQ(subscribed_stream(server), "AAPL@kline_5m");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"kline","E":1710320400000,"s":"AAPL","k":{"t":1710316800000,"ct":1710317099999,"s":"AAPL","i":"5m","o":"182.50","c":"183.20","h":"183.50","l":"182.30","v":"15000","n":120,"x":false,"vw":"182.95"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketStreamsApi, PriceStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const PriceStreamParams params{};
    auto stream = client.price_stream(params);
    EXPECT_EQ(subscribed_stream(server), "price");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"price","rates":[{"s":"AAPL","ac":"EQ_AAPL","p":"182.5","t":1710320400000,"pc":"181.2000","tc":"182.0000","lrc":"182.0000","prc":"181.2000","mp":"O"}]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketStreamsApi, QuoteStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const QuoteStreamParams params{.symbol = "AAPL"};
    auto stream = client.quote_stream(params);
    EXPECT_EQ(subscribed_stream(server), "AAPL@quote");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"quote","E":1710320400000,"s":"AAPL","bp":"182.50","ap":"182.55","bs":100,"as":200,"T":1710320399500})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketStreamsApi, TradabilityStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const TradabilityStreamParams params{.symbol = "AAPL"};
    auto stream = client.tradability_stream(params);
    EXPECT_EQ(subscribed_stream(server), "AAPL@tradability");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"tradability","symbol":"AAPL","assetCode":"EQ_AAPL","tradability":"BUY_SELL","t":1712345678000})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketStreamsApi, TradingStatusStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const TradingStatusStreamParams params{.symbol = "AAPL"};
    auto stream = client.trading_status_stream(params);
    EXPECT_EQ(subscribed_stream(server), "AAPL@tradingStatus");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"tradingStatus","symbol":"AAPL","assetCode":"EQ_AAPL","status":"TRADING_HALTED","msg":"MATERIAL_NEWS","time":1614021300000,"z":"C","tradability":"NONE"})json"));
    client.disconnect();
}
