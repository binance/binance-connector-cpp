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

#include <binance/derivatives_trading_usds_futures/websocket_streams.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_usds_futures::websocket_streams;
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
    return derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesWebsocketStreams::
        from_config(std::move(cfg))
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

TEST(WebsocketStreamsPublicApi, AllBookTickersStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllBookTickersStreamParams params{};
    auto stream = client.all_book_tickers_stream(params);
    EXPECT_EQ(subscribed_stream(server), "!bookTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"bookTicker","u":400900217,"E":1568014460893,"T":1568014460891,"s":"BNBUSDT","b":"25.35190000","B":"31.21000000","a":"25.36520000","A":"40.66000000","ps":"BTCUSDT","st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsPublicApi, DiffBookDepthStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const DiffBookDepthStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.diff_book_depth_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@depth");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":123456789,"T":123456788,"s":"BNBUSDT","U":157,"u":160,"pu":149,"b":[["0.0024","10"]],"a":[["0.0026","100"]],"ps":"BTCUSDT","st":1})json"));
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
        R"json({"e":"bookTicker","u":400900217,"E":1568014460893,"T":1568014460891,"s":"BNBUSDT","ps":"BNBUSDT","b":"25.35190000","B":"31.21000000","a":"25.36520000","A":"40.66000000","st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsPublicApi, PartialBookDepthStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const PartialBookDepthStreamsParams params{
        .symbol = "btcusdt", .levels = PartialBookDepthStreamsLevelsEnum::Levels5};
    auto stream = client.partial_book_depth_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@depth5");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":1571889248277,"T":1571889248276,"s":"BTCUSDT","U":390497796,"u":390497878,"pu":390497794,"b":[["7403.89"]],"a":[["7405.96"]],"ps":"BTCUSDT","st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsPublicApi, RpiDiffBookDepthStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const RpiDiffBookDepthStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.rpi_diff_book_depth_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@rpiDepth@500ms");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":123456789,"T":123456788,"s":"BNBUSDT","U":157,"u":160,"pu":149,"b":[["0.0024","10"]],"a":[["0.0026","100"]],"ps":"BTCUSDT","st":1})json"));
    client.disconnect();
}
