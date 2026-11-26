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

#include <binance/stock_options/websocket_streams.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::stock_options::websocket_streams;
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
    return stock_options::StockOptionsWebsocketStreams::from_config(std::move(cfg)).connect();
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

TEST(WebsocketStreamsUserStreamsApi, OrderReportV2Stream) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const OrderReportV2StreamParams params{.listen_key = "3f9a1c2e-7b4d-4e8a-9c61-0d2f5b7e8a13"};
    auto stream = client.order_report_v2_stream(params);
    EXPECT_EQ(subscribed_stream(server), "3f9a1c2e-7b4d-4e8a-9c61-0d2f5b7e8a13@orderReportV2");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"e":"orderReportV2","E":1792679109312,"x":"ORDER_UPDATE","i":"b0b6dd9d-8b9b-48a9-ba46-b9d54906e415","ci":"6a1f3c2e-90b4-4d7e-a1c5-2f8e7d6b5a40","ai":"8d3f2a61-5c7e-4b90-9e1d-3a6c4f2b7e18","b":"EQ_SPCX","q":"USDC","S":"buy","o":"limit","p":0.57,"Q":1,"N":1,"fq":0,"FN":0,"tc":57.66,"Z":0,"n":"RTH","s":"accepted","T":1792679109000,"U":1792679109000,"ac":"us_option","os":"SPCX261023C00005000","u":"SPCX","rs":"SPCX","ct":"CALL","sp":5,"ed":1792771200000,"m":100,"pi":"buy_to_open"})json"));
    client.disconnect();
}
