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

TEST(WebsocketStreamsMarketApi, IndexPriceStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const IndexPriceStreamsParams params{};
    auto stream = client.index_price_streams(params);
    EXPECT_EQ(subscribed_stream(server), "!index@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"indexPrice","E":1763092572229,"s":"ETHUSDT","p":"3224.51976744"}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, KlineCandlestickStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const KlineCandlestickStreamsParams params{
        .symbol = "btcusdt", .interval = KlineCandlestickStreamsIntervalEnum::Interval1m};
    auto stream = client.kline_candlestick_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@kline_1m");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"kline","E":1638747660000,"s":"BTC-200630-9000-P","k":{"t":1638747660000,"T":1638747719999,"s":"BTC-200630-9000-P","i":"1m","f":0,"L":0,"o":"1000","c":"1000","h":"1000","l":"1000","v":"0","n":0,"x":false,"q":"0","V":"0","Q":"0"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, NewSymbolInfo) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const NewSymbolInfoParams params{};
    auto stream = client.new_symbol_info(params);
    EXPECT_EQ(subscribed_stream(server), "!optionSymbol");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"optionSymbol","E":1669356423908,"s":"BTC-250926-140000-C","ps":"BTCUSDT","qa":"USDT","d":"CALL","sp":"21000","dt":4133404800000,"u":1,"ot":1569398400000,"cs":"TRADING"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, OpenInterest) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const OpenInterestParams params{.underlying = "btcusdt", .expiration_date = "220930"};
    auto stream = client.open_interest(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@optionOpenInterest@220930");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"openInterest","E":1668759300045,"s":"ETH-221125-2700-C","o":"1580.87","h":"1912992.178168204"}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, OptionMarkPrice) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const OptionMarkPriceParams params{.underlying = "btcusdt"};
    auto stream = client.option_mark_price(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@optionMarkPrice");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"s":"BTC-251120-126000-C","mp":"770.543","E":1762867543321,"e":"markPrice","i":"104334.60217391","P":"0.000","bo":"0.000","ao":"900.000","bq":"0.0000","aq":"0.2000","b":"-1.0","a":"0.98161161","hl":"924.652","ll":"616.435","vo":"0.9408058","rf":"0.0","d":"0.11111964","t":"-164.26702615","g":"0.00001245","v":"30.63855919"}])json"));
    client.disconnect();
}
