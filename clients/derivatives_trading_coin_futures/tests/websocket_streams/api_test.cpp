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

#include <binance/derivatives_trading_coin_futures/websocket_streams.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_coin_futures::websocket_streams;
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
    return derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketStreams::
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

TEST(WebsocketStreamsDefaultApi, AggregateTradeStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AggregateTradeStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.aggregate_trade_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@aggTrade");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"aggTrade","E":1591261134288,"a":424951,"s":"BTCUSD_200626","p":"9643.5","q":"2","f":606073,"l":606073,"T":1591261134199,"m":false,"st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllBookTickersStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllBookTickersStreamParams params{};
    auto stream = client.all_book_tickers_stream(params);
    EXPECT_EQ(subscribed_stream(server), "!bookTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"bookTicker","u":17242169,"s":"BTCUSD_200626","b":"9548.1","B":"52","a":"9548.5","A":"11","T":1591268628155,"E":1591268628166,"ps":"BTCUSD","st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllMarketLiquidationOrderStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllMarketLiquidationOrderStreamsParams params{};
    auto stream = client.all_market_liquidation_order_streams(params);
    EXPECT_EQ(subscribed_stream(server), "!forceOrder@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"forceOrder","E":1591154240950,"o":{"s":"BTCUSD_200925","ps":"BTCUSD","S":"SELL","o":"LIMIT","f":"IOC","q":"1","p":"9425.5","ap":"9496.5","X":"FILLED","l":"1","z":"1","T":1591154240949},"st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllMarketMiniTickersStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllMarketMiniTickersStreamParams params{};
    auto stream = client.all_market_mini_tickers_stream(params);
    EXPECT_EQ(subscribed_stream(server), "!miniTicker@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"24hrMiniTicker","E":1591267704450,"s":"BTCUSD_200626","ps":"BTCUSD","c":"9561.7","o":"9580.9","h":"10000.0","l":"7000.0","v":"487476","q":"33264343847.22378500","st":1}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, AllMarketTickersStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllMarketTickersStreamsParams params{};
    auto stream = client.all_market_tickers_streams(params);
    EXPECT_EQ(subscribed_stream(server), "!ticker@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"24hrTicker","E":1591268262453,"s":"BTCUSD_200626","p":"-43.4","P":"-0.452","w":"0.00147974","c":"9548.5","Q":"2","o":"9591.9","h":"10000.0","l":"7000.0","v":"487850","q":"32968676323.46222700","O":1591181820000,"C":1591268262442,"F":512014,"L":615289,"n":103272,"ps":"BTCUSD","st":1}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, ContinuousContractKlineCandlestickStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const ContinuousContractKlineCandlestickStreamsParams params{
        .pair = "btcusdt",
        .contract_type = ContinuousContractKlineCandlestickStreamsContractTypeEnum::Perpetual,
        .interval = ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1m};
    auto stream = client.continuous_contract_kline_candlestick_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt_perpetual@continuousKline_1m");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"continuous_kline","E":1591261542539,"ps":"BTCUSD","ct":"NEXT_QUARTER","k":{"t":1591261500000,"T":1591261559999,"i":"1m","f":606400,"L":606430,"o":"9638.9","c":"9639.8","h":"9639.8","l":"9638.6","v":"156","n":31,"x":false,"q":"1.61836886","V":"73","Q":"0.75731156","B":"0"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, ContractInfoStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const ContractInfoStreamParams params{};
    auto stream = client.contract_info_stream(params);
    EXPECT_EQ(subscribed_stream(server), "!contractInfo");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"contractInfo","E":1669647330375,"s":"APTUSD_PERP","ps":"APTUSD","ct":"PERPETUAL","dt":4133404800000,"ot":1666594800000,"cs":"TRADING","bks":[{"bs":1,"bnf":0,"bnc":500000,"mmr":0.0065,"cf":75,"mi":51,"ma":75}],"st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, DiffBookDepthStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const DiffBookDepthStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.diff_book_depth_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@depth");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":1591270260907,"T":1591270260891,"s":"BTCUSD_200626","ps":"BTCUSD","U":17285681,"u":17285702,"pu":17285675,"b":[["9517.6","10"]],"a":[["9518.5","45"]],"st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, IndexKlineCandlestickStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const IndexKlineCandlestickStreamsParams params{
        .pair = "btcusdt", .interval = IndexKlineCandlestickStreamsIntervalEnum::Interval1m};
    auto stream = client.index_kline_candlestick_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@indexPriceKline_1m");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"indexPrice_kline","E":1591267070033,"ps":"BTCUSD","k":{"t":1591267020000,"T":1591267079999,"s":"0","i":"1m","f":1591267020000,"L":1591267070000,"o":"9542.21900000","c":"9542.50440000","h":"9542.71640000","l":"9542.21040000","v":"0","n":51,"x":false,"q":"0","V":"0","Q":"0","B":"0"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, IndexPriceStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const IndexPriceStreamParams params{.pair = "btcusdt"};
    auto stream = client.index_price_stream(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@indexPrice");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"indexPriceUpdate","E":1591261236000,"i":"BTCUSD","p":"9636.57860000"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, IndividualSymbolBookTickerStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const IndividualSymbolBookTickerStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.individual_symbol_book_ticker_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@bookTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"bookTicker","u":17242169,"s":"BTCUSD_200626","b":"9548.1","B":"52","a":"9548.5","A":"11","T":1591268628155,"E":1591268628166,"ps":"BTCUSD","st":2})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, IndividualSymbolMiniTickerStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const IndividualSymbolMiniTickerStreamParams params{.symbol = "btcusdt"};
    auto stream = client.individual_symbol_mini_ticker_stream(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@miniTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrMiniTicker","E":1591267704450,"s":"BTCUSD_200626","ps":"BTCUSD","c":"9561.7","o":"9580.9","h":"10000.0","l":"7000.0","v":"487476","q":"33264343847.22378500","st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, IndividualSymbolTickerStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const IndividualSymbolTickerStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.individual_symbol_ticker_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@ticker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrTicker","E":1591268262453,"s":"BTCUSD_200626","p":"-43.4","P":"-0.452","w":"0.00147974","c":"9548.5","Q":"2","o":"9591.9","h":"10000.0","l":"7000.0","v":"487850","q":"32968676323.46222700","O":1591181820000,"C":1591268262442,"F":512014,"L":615289,"n":103272,"ps":"BTCUSD","st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, KlineCandlestickStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const KlineCandlestickStreamsParams params{
        .symbol = "btcusdt", .interval = KlineCandlestickStreamsIntervalEnum::Interval1m};
    auto stream = client.kline_candlestick_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@kline_1m");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"kline","E":1591261542539,"s":"BTCUSD_200626","k":{"t":1591261500000,"T":1591261559999,"s":"BTCUSD_200626","i":"1m","f":606400,"L":606430,"o":"9638.9","c":"9639.8","h":"9639.8","l":"9638.6","v":"156","n":31,"x":false,"q":"1.61836886","V":"73","Q":"0.75731156","B":"0"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MarkPriceKlineCandlestickStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const MarkPriceKlineCandlestickStreamsParams params{
        .symbol = "btcusdt", .interval = MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1m};
    auto stream = client.mark_price_kline_candlestick_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@markPriceKline_1m");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"markPrice_kline","E":1591267398004,"ps":"BTCUSD","k":{"t":1591267380000,"T":1591267439999,"s":"BTCUSD_200626","i":"1m","f":1591267380000,"L":1591267398000,"o":"9539.67161333","c":"9540.82761333","h":"9540.82761333","l":"9539.66961333","v":"0","n":19,"x":false,"q":"0","V":"0","Q":"0","B":"0"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MarkPriceOfAllSymbolsOfAPair) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const MarkPriceOfAllSymbolsOfAPairParams params{.pair = "btcusdt"};
    auto stream = client.mark_price_of_all_symbols_of_a_pair(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@markPrice");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"markPriceUpdate","E":1596095725000,"s":"BTCUSD_201225","p":"10934.62615417","P":"10962.17178236","i":"10933.62615417","r":"","T":0,"st":1}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MarkPriceStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const MarkPriceStreamParams params{.symbol = "btcusdt"};
    auto stream = client.mark_price_stream(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@markPrice");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"markPriceUpdate","E":1596095725000,"s":"BTCUSD_201225","p":"10934.62615417","P":"10962.17178236","i":"10933.62615417","r":"","T":0,"st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MarketLiquidationOrderStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const MarketLiquidationOrderStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.market_liquidation_order_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@forceOrder");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"forceOrder","E":1591154240950,"o":{"s":"BTCUSD_200925","ps":"BTCUSD","S":"SELL","o":"LIMIT","f":"IOC","q":"1","p":"9425.5","ap":"9496.5","X":"FILLED","l":"1","z":"1","T":1591154240949}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, PartialBookDepthStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const PartialBookDepthStreamsParams params{
        .symbol = "btcusdt", .levels = PartialBookDepthStreamsLevelsEnum::Levels5};
    auto stream = client.partial_book_depth_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@depth5");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"depthUpdate","E":1591269996801,"T":1591269996646,"s":"BTCUSD_200626","ps":"BTCUSD","U":17276694,"u":17276701,"pu":17276678,"b":[["9523.0"]],"a":[["9524.6"]],"st":1})json"));
    client.disconnect();
}
