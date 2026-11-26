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

#include <binance/alpha/websocket_streams.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::alpha::websocket_streams;
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
    return alpha::AlphaWebsocketStreams::from_config(std::move(cfg)).connect();
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

TEST(WebsocketStreamsDefaultApi, AggregateTradeStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AggregateTradeStreamParams params{.symbol = "alpha_116usdt"};
    auto stream = client.aggregate_trade_stream(params);
    EXPECT_EQ(subscribed_stream(server), "alpha_116usdt@aggTrade");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"aggTrade","E":1771828569861,"T":1771828569702,"a":2684294,"f":2684294,"l":2684294,"m":false,"p":"0.08530000","q":"879.24000000","s":"ALPHA_474USDT"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllBookTickerStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllBookTickerStreamParams params{};
    auto stream = client.all_book_ticker_stream(params);
    EXPECT_EQ(subscribed_stream(server), "!bookTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"bookTicker","E":1773108379067,"T":1773108379054,"u":6663207693,"s":"ALPHA_116USDT","b":"8.30000000","B":"0.91076900","a":"9.30000000","A":"2.00353200"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllMiniTickerStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllMiniTickerStreamParams params{};
    auto stream = client.all_mini_ticker_stream(params);
    EXPECT_EQ(subscribed_stream(server), "!miniTicker@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrMiniTicker","E":1773109449908,"s":"ALPHA_116USDT","c":"8.40000000","o":"8.40000000","h":"8.50000000","l":"8.30000000","v":"64739.03978900","q":"543810.36005090"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllTickerStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllTickerStreamParams params{};
    auto stream = client.all_ticker_stream(params);
    EXPECT_EQ(subscribed_stream(server), "!ticker@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrTicker","E":1773109631569,"s":"ALPHA_116USDT","p":"0.00000000","P":"0.00","w":"8.40003127","c":"8.40000000","Q":"0.49293200","o":"8.40000000","h":"8.50000000","l":"8.30000000","v":"64750.63418500","q":"543907.35169250","O":1773023220000,"C":1773109631555,"F":19847634,"L":19911287,"n":217505})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllTokens24hTickerStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllTokens24hTickerStreamParams params{};
    auto stream = client.all_tokens24h_ticker_stream(params);
    EXPECT_EQ(subscribed_stream(server), "came@allTokens@ticker24");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"tickerList","d":[{"ca":"0x8fce...@56","cnt24":10426,"fdv":"72834145.18711072","hc":"6822","liq":"1442996.98151177662835","mc":"13542034.24008014","p":"0.072849536538593663","pc24":"-2.32","s":"1","t":1771825733000,"vol24":"12930712.213702157742688594285"}]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, BookTickerStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const BookTickerStreamParams params{.symbol = "alpha_116usdt"};
    auto stream = client.book_ticker_stream(params);
    EXPECT_EQ(subscribed_stream(server), "alpha_116usdt@bookTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"bookTicker","E":1773108379067,"T":1773108379054,"u":6663207693,"s":"ALPHA_116USDT","b":"8.30000000","B":"0.91076900","a":"9.30000000","A":"2.00353200"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, ContractKlineStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const ContractKlineStreamParams params{.contract_address =
                                               "G7vQWurMkMMm2dU3iZpXYFTHT9Biio4F4gZCrwFpKNwG",
                                           .chain_id = "CT_501",
                                           .interval = ContractKlineStreamIntervalEnum::Interval1s};
    auto stream = client.contract_kline_stream(params);
    EXPECT_EQ(subscribed_stream(server),
              "came@G7vQWurMkMMm2dU3iZpXYFTHT9Biio4F4gZCrwFpKNwG@CT_501@kline_1s");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"ca":"G7vQW...@CT_501","e":"kline","k":{"o":"0.15584372258086979622","c":"0.15584957424118055058","h":"0.15584957424118055058","l":"0.15584372258086979622","v":"2.8584092999332775480","ot":1771828655000,"ct":1771828656000,"i":"1s"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, FullDepthStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const FullDepthStreamParams params{.symbol = "alpha_116usdt",
                                       .interval = FullDepthStreamIntervalEnum::Interval0ms};
    auto stream = client.full_depth_stream(params);
    EXPECT_EQ(subscribed_stream(server), "alpha_116usdt@fulldepth@0ms");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":1771828614381,"T":1771828614258,"U":42648947917,"u":42648948229,"pu":42648947321,"s":"ALPHA_474USDT","b":[["0.16479999","0"],["0.16480000","18.68000000"]],"a":[["0.16490000","500.00000000"],["0.16500000","0"]]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, KlineStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const KlineStreamParams params{.symbol = "alpha_116usdt",
                                   .interval = KlineStreamIntervalEnum::Interval1m};
    auto stream = client.kline_stream(params);
    EXPECT_EQ(subscribed_stream(server), "alpha_116usdt@kline_1m");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"kline","E":1773111055144,"s":"ALPHA_116USDT","k":{"t":1773111000000,"T":1773111059999,"s":"ALPHA_116USDT","i":"1m","f":19912696,"L":19912765,"o":"8.40000000","c":"8.40000000","h":"8.40000000","l":"8.40000000","v":"63.64876300","n":218,"x":false,"q":"534.64960920","V":"63.64876300","Q":"534.64960920","B":"0"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MiniTickerStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const MiniTickerStreamParams params{.symbol = "alpha_116usdt"};
    auto stream = client.mini_ticker_stream(params);
    EXPECT_EQ(subscribed_stream(server), "alpha_116usdt@miniTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrMiniTicker","E":1773109449908,"s":"ALPHA_116USDT","c":"8.40000000","o":"8.40000000","h":"8.50000000","l":"8.30000000","v":"64739.03978900","q":"543810.36005090"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, PartialDepthStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const PartialDepthStreamParams params{.symbol = "alpha_116usdt",
                                          .levels = PartialDepthStreamLevelsEnum::Levels5,
                                          .interval = PartialDepthStreamIntervalEnum::Interval0ms};
    auto stream = client.partial_depth_stream(params);
    EXPECT_EQ(subscribed_stream(server), "alpha_116usdt@depth5@0ms");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":1773110222878,"T":1773110222767,"U":6663367135,"u":6663367147,"pu":6663366971,"s":"ALPHA_116USDT","b":[["0.16479999","0"],["0.16480000","18.68000000"]],"a":[["0.16490000","500.00000000"],["0.16500000","0"]]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, TickerStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const TickerStreamParams params{.symbol = "alpha_116usdt"};
    auto stream = client.ticker_stream(params);
    EXPECT_EQ(subscribed_stream(server), "alpha_116usdt@ticker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrTicker","E":1773109631569,"s":"ALPHA_116USDT","p":"0.00000000","P":"0.00","w":"8.40003127","c":"8.40000000","Q":"0.49293200","o":"8.40000000","h":"8.50000000","l":"8.30000000","v":"64750.63418500","q":"543907.35169250","O":1773023220000,"C":1773109631555,"F":19847634,"L":19911287,"n":217505})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, TradeStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const TradeStreamParams params{.symbol = "alpha_116usdt"};
    auto stream = client.trade_stream(params);
    EXPECT_EQ(subscribed_stream(server), "alpha_116usdt@trade");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"trade","E":1773110023891,"T":1773110023877,"s":"ALPHA_116USDT","t":19911650,"p":"8.40000000","q":"0.97915700","m":false})json"));
    client.disconnect();
}
