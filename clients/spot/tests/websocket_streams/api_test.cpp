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

#include <binance/spot/websocket_streams.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::spot::websocket_streams;
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
    return spot::SpotWebsocketStreams::from_config(std::move(cfg)).connect();
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

TEST(WebsocketStreamsDefaultApi, AggTrade) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AggTradeParams params{.symbol = "bnbusdt"};
    auto stream = client.agg_trade(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@aggTrade");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"aggTrade","E":1672515782136,"s":"BNBBTC","a":12345,"p":"0.001","q":"100","f":100,"l":105,"T":1672515782136,"m":true,"M":true})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllMarketRollingWindowTicker) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllMarketRollingWindowTickerParams params{
        .window_size = AllMarketRollingWindowTickerWindowSizeEnum::WindowSize1h};
    auto stream = client.all_market_rolling_window_ticker(params);
    EXPECT_EQ(subscribed_stream(server), "!ticker_1h@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"1hTicker","E":1672515782136,"s":"BNBBTC","p":"0.0015","P":"250.00","o":"0.0010","h":"0.0025","l":"0.0010","c":"0.0025","w":"0.0018","v":"10000","q":"18","O":0,"C":1675216573749,"F":0,"L":18150,"n":18151}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllMiniTicker) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllMiniTickerParams params{};
    auto stream = client.all_mini_ticker(params);
    EXPECT_EQ(subscribed_stream(server), "!miniTicker@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"24hrMiniTicker","E":1672515782136,"s":"BNBBTC","c":"0.0025","o":"0.0010","h":"0.0025","l":"0.0010","v":"10000","q":"18"}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AvgPrice) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AvgPriceParams params{.symbol = "bnbusdt"};
    auto stream = client.avg_price(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@avgPrice");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"avgPrice","E":1693907033000,"s":"BTCUSDT","i":"5m","w":"25776.86000000","T":1693907032213})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, BlockTrade) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const BlockTradeParams params{.symbol = "bnbusdt"};
    auto stream = client.block_trade(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@blockTrade");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"blockTrade","E":1772506983582,"s":"BNBBTC","t":582,"p":"0.052","q":"5838","T":1772506983321,"m":true})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, BookTicker) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const BookTickerParams params{.symbol = "bnbusdt"};
    auto stream = client.book_ticker(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@bookTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"u":400900217,"s":"BNBUSDT","b":"25.35190000","B":"31.21000000","a":"25.36520000","A":"40.66000000"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, DiffBookDepth) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const DiffBookDepthParams params{.symbol = "bnbusdt"};
    auto stream = client.diff_book_depth(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@depth");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":1672515782136,"s":"BNBBTC","U":157,"u":160,"b":[["0.0024","10"]],"a":[["0.0026","100"]]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, Kline) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const KlineParams params{.symbol = "bnbusdt", .interval = KlineIntervalEnum::Interval1s};
    auto stream = client.kline(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@kline_1s");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"kline","E":1672515782136,"s":"BNBBTC","k":{"t":1672515780000,"T":1672515839999,"s":"BNBBTC","i":"1m","f":100,"L":200,"o":"0.0010","c":"0.0020","h":"0.0025","l":"0.0015","v":"1000","n":100,"x":false,"q":"1.0000","V":"500","Q":"0.500","B":"123456"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, KlineOffset) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const KlineOffsetParams params{.symbol = "bnbusdt",
                                   .interval = KlineOffsetIntervalEnum::Interval1s};
    auto stream = client.kline_offset(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@kline_1s@+08:00");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"kline","E":1672515782136,"s":"BNBBTC","k":{"t":1672515780000,"T":1672515839999,"s":"BNBBTC","i":"1m","f":100,"L":200,"o":"0.0010","c":"0.0020","h":"0.0025","l":"0.0015","v":"1000","n":100,"x":false,"q":"1.0000","V":"500","Q":"0.500","B":"123456"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MiniTicker) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const MiniTickerParams params{.symbol = "bnbusdt"};
    auto stream = client.mini_ticker(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@miniTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrMiniTicker","E":1672515782136,"s":"BNBBTC","c":"0.0025","o":"0.0010","h":"0.0025","l":"0.0010","v":"10000","q":"18"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, PartialBookDepth) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const PartialBookDepthParams params{.symbol = "bnbusdt",
                                        .levels = PartialBookDepthLevelsEnum::Levels5};
    auto stream = client.partial_book_depth(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@depth5");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"lastUpdateId":160,"bids":[["0.0024","10"]],"asks":[["0.0026","100"]]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, ReferencePrice) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const ReferencePriceParams params{.symbol = "bazusd"};
    auto stream = client.reference_price(params);
    EXPECT_EQ(subscribed_stream(server), "bazusd@referencePrice");
    EXPECT_TRUE(
        delivers(server, stream,
                 R"json({"e":"referencePrice","s":"BAZUSD","r":"1.00","t":1770313263917})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, RollingWindowTicker) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const RollingWindowTickerParams params{
        .symbol = "bnbusdt", .window_size = RollingWindowTickerWindowSizeEnum::WindowSize1h};
    auto stream = client.rolling_window_ticker(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@ticker_1h");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"1hTicker","E":1672515782136,"s":"BNBBTC","p":"0.0015","P":"250.00","o":"0.0010","h":"0.0025","l":"0.0010","c":"0.0025","w":"0.0018","v":"10000","q":"18","O":0,"C":1675216573749,"F":0,"L":18150,"n":18151})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, Ticker) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const TickerParams params{.symbol = "bnbusdt"};
    auto stream = client.ticker(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@ticker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrTicker","E":1672515782136,"s":"BNBBTC","p":"0.0015","P":"250.00","w":"0.0018","x":"0.0009","c":"0.0025","Q":"10","b":"0.0024","B":"10","a":"0.0026","A":"100","o":"0.0010","h":"0.0025","l":"0.0010","v":"10000","q":"18","O":0,"C":1675216573749,"F":0,"L":18150,"n":18151})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, Trade) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const TradeParams params{.symbol = "bnbusdt"};
    auto stream = client.trade(params);
    EXPECT_EQ(subscribed_stream(server), "bnbusdt@trade");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"trade","E":1672515782136,"s":"BNBBTC","t":12345,"p":"0.001","q":"100","T":1672515782136,"m":true,"M":true})json"));
    client.disconnect();
}
