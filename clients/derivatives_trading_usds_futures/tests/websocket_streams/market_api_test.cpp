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

TEST(WebsocketStreamsMarketApi, AggregateTradeStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AggregateTradeStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.aggregate_trade_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@aggTrade");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"aggTrade","E":123456789,"s":"BNBUSDT","a":5933014,"p":"0.001","q":"100","nq":"100","f":100,"l":105,"T":123456785,"m":true,"st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, AllMarketLiquidationOrderStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllMarketLiquidationOrderStreamsParams params{};
    auto stream = client.all_market_liquidation_order_streams(params);
    EXPECT_EQ(subscribed_stream(server), "!forceOrder@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"forceOrder","E":1568014460893,"o":{"s":"BTCUSDT","S":"SELL","o":"LIMIT","f":"IOC","q":"0.014","p":"9910","ap":"9910","X":"FILLED","l":"0.014","z":"0.014","T":1568014460893},"ps":"BTCUSDT","st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, AllMarketMiniTickersStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllMarketMiniTickersStreamParams params{};
    auto stream = client.all_market_mini_tickers_stream(params);
    EXPECT_EQ(subscribed_stream(server), "!miniTicker@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"24hrMiniTicker","E":123456789,"s":"BNBUSDT","c":"0.0025","o":"0.0010","h":"0.0025","l":"0.0010","v":"10000","q":"18","ps":"BTCUSDT","st":1}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, AllMarketTickersStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AllMarketTickersStreamsParams params{};
    auto stream = client.all_market_tickers_streams(params);
    EXPECT_EQ(subscribed_stream(server), "!ticker@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"24hrTicker","E":123456789,"s":"BNBUSDT","p":"0.0015","P":"250.00","w":"0.0018","c":"0.0025","Q":"10","o":"0.0010","h":"0.0025","l":"0.0010","v":"10000","q":"18","O":0,"C":86400000,"F":0,"L":18150,"n":18151,"ps":"BTCUSDT","st":1}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, AssetIndex) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const AssetIndexParams params{};
    auto stream = client.asset_index(params);
    EXPECT_EQ(subscribed_stream(server), "!assetIndex@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"assetIndexUpdate","E":1686749230000,"s":"ADAUSD","i":"0.27462452","b":"0.10000000","a":"0.10000000","B":"0.24716207","A":"0.30208698","q":"0.05000000","g":"0.05000000","Q":"0.26089330","G":"0.28835575"}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, CompositeIndexSymbolInformationStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const CompositeIndexSymbolInformationStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.composite_index_symbol_information_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@compositeIndex");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"compositeIndex","E":1602310596000,"s":"DEFIUSDT","p":"554.41604065","C":"baseAsset","c":[{"b":"BAL","q":"USDT","w":"1.04884844","W":"0.01457800","i":"24.33521021"}]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, ContinuousContractKlineCandlestickStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const ContinuousContractKlineCandlestickStreamsParams params{
        .pair = "btcusdt",
        .contract_type = ContinuousContractKlineCandlestickStreamsContractTypeEnum::Perpetual,
        .interval = ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1s};
    auto stream = client.continuous_contract_kline_candlestick_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt_perpetual@continuousKline_1s");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"continuous_kline","E":1607443058651,"ps":"BTCUSDT","ct":"PERPETUAL","k":{"t":1607443020000,"T":1607443079999,"i":"1m","f":116467658886,"L":116468012423,"o":"18787.00","c":"18804.04","h":"18804.04","l":"18786.54","v":"197.664","n":543,"x":false,"q":"3715253.19494","V":"184.769","Q":"3472925.84746","B":"0"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, ContractInfoStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const ContractInfoStreamParams params{};
    auto stream = client.contract_info_stream(params);
    EXPECT_EQ(subscribed_stream(server), "!contractInfo");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"contractInfo","E":1669356423908,"s":"IOTAUSDT","ct":"PERPETUAL","dt":4133404800000,"ot":1569398400000,"cs":"TRADING","bks":[{"bs":1,"bnf":0,"bnc":5000,"mmr":0.01,"cf":0,"mi":21,"ma":50}],"st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, IndividualSymbolMiniTickerStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const IndividualSymbolMiniTickerStreamParams params{.symbol = "btcusdt"};
    auto stream = client.individual_symbol_mini_ticker_stream(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@miniTicker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrMiniTicker","E":123456789,"s":"BNBUSDT","c":"0.0025","o":"0.0010","h":"0.0025","l":"0.0010","v":"10000","q":"18","ps":"BTCUSDT","st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, IndividualSymbolTickerStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const IndividualSymbolTickerStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.individual_symbol_ticker_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@ticker");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"24hrTicker","E":123456789,"s":"BNBUSDT","p":"0.0015","P":"250.00","w":"0.0018","c":"0.0025","Q":"10","o":"0.0010","h":"0.0025","l":"0.0010","v":"10000","q":"18","O":0,"C":86400000,"F":0,"L":18150,"n":18151,"ps":"BTCUSDT","st":1})json"));
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
        R"json({"e":"kline","E":1638747660000,"s":"BTCUSDT","k":{"t":1638747660000,"T":1638747719999,"s":"BTCUSDT","i":"1m","f":100,"L":200,"o":"0.0010","c":"0.0020","h":"0.0025","l":"0.0015","v":"1000","n":100,"x":false,"q":"1.0000","V":"500","Q":"0.500","B":"123456"}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, LiquidationOrderStreams) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const LiquidationOrderStreamsParams params{.symbol = "btcusdt"};
    auto stream = client.liquidation_order_streams(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@forceOrder");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"forceOrder","E":1568014460893,"o":{"s":"BTCUSDT","S":"SELL","o":"LIMIT","f":"IOC","q":"0.014","p":"9910","ap":"9910","X":"FILLED","l":"0.014","z":"0.014","T":1568014460893}})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, MarkPriceStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const MarkPriceStreamParams params{.symbol = "btcusdt"};
    auto stream = client.mark_price_stream(params);
    EXPECT_EQ(subscribed_stream(server), "btcusdt@markPrice");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"markPriceUpdate","E":1562305380000,"s":"BTCUSDT","p":"11794.15000000","i":"11784.62659091","P":"11784.25641265","r":"0.00038167","ap":"11794.15000000","T":1562306400000,"st":1})json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, MarkPriceStreamForAllMarket) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const MarkPriceStreamForAllMarketParams params{};
    auto stream = client.mark_price_stream_for_all_market(params);
    EXPECT_EQ(subscribed_stream(server), "!markPrice@arr");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json([{"e":"markPriceUpdate","E":1562305380000,"s":"BTCUSDT","p":"11185.87786614","i":"11784.62659091","P":"11784.25641265","r":"0.00030000","ap":"11185.87786614","T":1562306400000,"st":1}])json"));
    client.disconnect();
}

TEST(WebsocketStreamsMarketApi, TradingSessionStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const TradingSessionStreamParams params{};
    auto stream = client.trading_session_stream(params);
    EXPECT_EQ(subscribed_stream(server), "tradingSession");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"EquityUpdate","E":1765244143062,"t":1765242000000,"T":1765270800000,"S":"OVERNIGHT"})json"));
    client.disconnect();
}
