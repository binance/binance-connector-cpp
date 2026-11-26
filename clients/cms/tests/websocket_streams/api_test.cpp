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

#include <binance/cms/websocket_streams.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::cms::websocket_streams;
using binance::test::MockWsServer;

namespace {

// Acknowledges the SUBSCRIBE and UNSUBSCRIBE commands.
void ack(MockWsServer::Session& s, const std::string& text) {
    const auto req = boost::json::parse(text).as_object();
    s.send(boost::json::serialize(boost::json::object{
        {"type", "COMMAND"}, {"subType", req.at("command")}, {"data", "SUCCESS"}}));
}

WebsocketStreamsConnection streams_for(const MockWsServer& server) {
    common::WebsocketStreamsConfig cfg;
    cfg.url = server.url();
    cfg.proxy_from_env = false;
    cfg.api_key = "test-api-key";
    cfg.api_secret = "test-api-secret";
    return cms::CmsWebsocketStreams::from_config(std::move(cfg)).connect();
}

// The first stream the client subscribed to, or an empty string after a timeout.
std::string subscribed_stream(const MockWsServer& server) {
    std::string name;
    (void)server.wait([&](const auto& sessions) {
        for (const auto& session : sessions) {
            for (const auto& text : session.received) {
                const auto req = boost::json::parse(text).as_object();
                if (req.at("command").as_string() == "SUBSCRIBE") {
                    const std::string topics(req.at("value").as_string());
                    name = topics.substr(0, topics.find('|'));
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
    // Signed streams deliver the event as a JSON-encoded string.
    server.broadcast(boost::json::serialize(boost::json::object{
        {"type", "DATA"}, {"topic", name}, {"data", boost::json::serialize(event)}}));
    const bool ok =
        received.get_future().wait_for(std::chrono::seconds(5)) == std::future_status::ready;
    stream.on_message([](const auto&) {});
    return ok;
}

} // namespace

TEST(WebsocketStreamsDefaultApi, ComAnnouncementEn) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.com_announcement_en();
    EXPECT_EQ(subscribed_stream(server), "com_announcement_en");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"catalogId":161,"catalogName":"Delisting","publishDate":1753257631403,"title":"Notice of...","body":"This is...","disclaimer":"Trade on-the-go..."})json"));
    client.disconnect();
}
