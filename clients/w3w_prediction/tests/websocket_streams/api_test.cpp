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

#include <binance/w3w_prediction/websocket_streams.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::w3w_prediction::websocket_streams;
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
    return w3w_prediction::W3WPredictionWebsocketStreams::from_config(std::move(cfg)).connect();
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

TEST(WebsocketStreamsDefaultApi, BatchClaimPartiallySucceeded) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.batch_claim_partially_succeeded();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_claim_partial_success");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_CLAIM_BATCH_20260528003_pm_claim_partial_success_e1f2a3b4"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, FundTransferFailed) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.fund_transfer_failed();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_transfer_fail");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_TRANSFER_20260528002_pm_transfer_fail_a3b4c5d6","amount":"100.00"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, FundTransferSucceeded) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.fund_transfer_succeeded();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_transfer_success");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_TRANSFER_20260528001_pm_transfer_success_f2a3b4c5","amount":"100.00"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, LimitOrderFullyFilled) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.limit_order_fully_filled();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_limit_order_filled");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_PM2026052812347_pm_limit_order_filled_a7b8c9d0","amount":"100.00","topic":"BTC will hi.."})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, LimitOrderPartiallyFilled) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.limit_order_partially_filled();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_limit_order_partial_fill");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_PM2026052812347_pm_limit_order_partial_fill_b8c9d0e1","amount":"30.00","topic":"BTC will hi.."})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, LimitOrderSubmissionFailed) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.limit_order_submission_failed();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_limit_submit_fail");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_PM2026052812347_pm_limit_submit_fail_f6a7b8c9","topic":"BTC will hi.."})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, LimitOrderSubmittedSuccessfully) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.limit_order_submitted_successfully();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_limit_submit_success");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_PM2026052812347_pm_limit_submit_success_e5f6a7b8","amount":"100.00","topic":"BTC will hi.."})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MarketBuyOrderFailed) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.market_buy_order_failed();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_market_buy_fail");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_PM2026052812345_pm_market_buy_fail_b2c3d4e5","amount":"12.34","topic":"BTC will hi.."})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MarketBuyOrderFullyFilled) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.market_buy_order_fully_filled();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_market_buy_success");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_PM2026052812345_pm_market_buy_success_a1b2c3d4","amount":"12.34","topic":"BTC will hi.."})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MarketResolutionNotification) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.market_resolution_notification();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_market_close");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_8859231_pm_market_close_b4c5d6e7","topic":"BTC will hi.."})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MarketSellOrderFailedExpired) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.market_sell_order_failed_expired();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_market_sell_fail");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_PM2026052812346_pm_market_sell_fail_d4e5f6a7","amount":"10.50","topic":"ETH price.."})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, MarketSellOrderFullyFilled) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.market_sell_order_fully_filled();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_market_sell_success");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_PM2026052812346_pm_market_sell_success_c3d4e5f6","amount":"10.50","topic":"ETH price.."})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, PredictionOrderBookByMarketId) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    const PredictionOrderBookByMarketIdParams params{.market_id = "8859231"};
    auto stream = client.prediction_order_book_by_market_id(params);
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_orderbook_8859231");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"msgType":"orderbook","marketId":8859231,"updateTimestampMs":1717420800123,"asks":[[0.32,500],[0.33,1200.5]],"bids":[[0.31,800],[0.3,2000]]})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, RewardClaimFailed) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.reward_claim_failed();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_claim_fail");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_CLAIM_BATCH_20260528002_pm_claim_fail_d0e1f2a3","amount":"10.00","outcome":"Yes"})json"));
    client.disconnect();
}

TEST(WebsocketStreamsDefaultApi, RewardClaimSucceeded) {
    MockWsServer server(ack);
    auto client = streams_for(server);
    auto stream = client.reward_claim_succeeded();
    EXPECT_EQ(subscribed_stream(server), "web3_prediction_pm_claim_success");
    EXPECT_TRUE(delivers(
        server, stream,
        R"json({"pushId":"pm_CLAIM_BATCH_20260528001_pm_claim_success_c9d0e1f2","amount":"50.00"})json"));
    client.disconnect();
}
