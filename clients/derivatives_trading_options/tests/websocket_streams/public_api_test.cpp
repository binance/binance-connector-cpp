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

#include <binance/derivatives_trading_options/websocket_streams.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_options::websocket_streams;
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
    return derivatives_trading_options::DerivativesTradingOptionsWebsocketStreams::from_config(
               std::move(cfg))
        .connect();
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

TEST(WebsocketStreamsPublicApi, DiffBookDepthStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const DiffBookDepthStreamsParams params{
        .symbol = "btcusdt", .update_speed = DiffBookDepthStreamsUpdateSpeedEnum::UpdateSpeed100ms};
    auto stream = client.diff_book_depth_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@depth@100ms");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":1762866729459,"T":1762866729358,"s":"BTC-251123-126000-C","U":465,"u":465,"pu":464,"b":[["1100.000","0.6000"]],"a":[["1300.000","0.6000"]]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsPublicApi, Hour24Ticker) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const Hour24TickerParams params{.symbol = "btcusdt"};
    auto stream = client.hour24_ticker(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@optionTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrTicker","E":1764080707933,"s":"ETH-251226-3000-C","p":"0.0000","P":"0.00","w":"200.0000","c":"200.0000","Q":"1.0000","o":"200.0000","h":"200.0000","l":"200.0000","v":"9.0000","q":"1800.0000","O":1764051060000,"C":1764080707933,"F":1,"L":22,"n":9})json"));
    client.disconnect();
}

TEST(WebsocketStreamsPublicApi, IndividualSymbolBookTickerStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const IndividualSymbolBookTickerStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.individual_symbol_book_ticker_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@bookTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"bookTicker","u":2472,"s":"BTC-251226-110000-C","b":"5000.000","B":"0.2000","a":"5100.000","A":"0.1000","T":1763041762942,"E":1763041762942})json"));
    client.disconnect();
}

TEST(WebsocketStreamsPublicApi, PartialBookDepthStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const PartialBookDepthStreamsParams params{
        .symbol = "btcusdt",
        .level = PartialBookDepthStreamsLevelEnum::Level5,
        .update_speed = PartialBookDepthStreamsUpdateSpeedEnum::UpdateSpeed100ms};
    auto stream = client.partial_book_depth_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@depth5@100ms");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":1762866729459,"T":1762866729358,"s":"BTC-251123-126000-C","U":465,"u":465,"pu":464,"b":[["1100.000"]],"a":[["1300.000"]]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsPublicApi, TradeStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const TradeStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.trade_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@optionTrade");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"trade","E":1762856064204,"T":1762856064203,"s":"BTC-251123-126000-C","t":4,"p":"1300.000","q":"0.1000","X":"MARKET","S":"BUY","m":false})json"));
    client.disconnect();
}
