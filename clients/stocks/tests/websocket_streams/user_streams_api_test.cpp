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

TEST(WebsocketStreamsUserStreamsApi, OrderReportStream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const OrderReportStreamParams params{
        .listen_key = "pqia91ma19a5s61cv6a81va65sdf19v8a65a1a5s6af0dkfj2a97b8a91d"};
    auto stream = client.order_report_stream(params);
    EXPECT_EQ(subscribed_stream(server),
              "pqia91ma19a5s61cv6a81va65sdf19v8a65a1a5s6af0dkfj2a97b8a91d@orderReport");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"orderReport","E":1710000000000,"x":"ORDER_UPDATE","i":"b0b6dd9d-8b9b-48a9-ba46-b9d54906e415","ai":"4ce9353c-66d1-46c2-898f-fce867ab0247","b":"EQ_AAPL","q":"USD","S":"buy","o":"limit","p":185.5,"Q":10,"N":1,"fq":5,"FN":927.5,"tc":1856.2,"Z":50,"n":"Regular","s":"partially_filled","T":1710000000000,"U":1710000060000})json"));
    client.disconnect();
}
