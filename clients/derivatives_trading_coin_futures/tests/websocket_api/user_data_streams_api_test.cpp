//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string>

#include <boost/json/parse.hpp>
#include <boost/json/serialize.hpp>
#include <gtest/gtest.h>

#include <binance/common/errors.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/user_data_streams_api.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_coin_futures::websocket_api;
using binance::test::MockWsServer;

namespace {

// Answers every request with `example` (a spec response envelope, or an empty result), or with
// an error envelope when `status` is not 200, under the request's id.
MockWsServer::Handler reply(std::string example, int status = 200) {
    return
        [example = std::move(example), status](MockWsServer::Session& s, const std::string& text) {
            const auto req = boost::json::parse(text).as_object();
            boost::json::object res;
            if (status != 200) {
                res["status"] = status;
                res["error"] = {{"code", -1102}, {"msg", "Mandatory parameter was not sent."}};
            } else if (example.empty()) {
                res["status"] = 200;
                res["result"] = boost::json::object{};
            } else {
                res = boost::json::parse(example).as_object();
            }
            res["id"] = req.at("id");
            s.send(boost::json::serialize(res));
        };
}

UserDataStreamsApi api_for(const MockWsServer& server) {
    common::WebsocketApiConfig cfg;
    cfg.url = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    cfg.proxy_from_env = false;
    auto client = std::make_shared<common::WebsocketApi>(std::move(cfg));
    client->connect();
    return UserDataStreamsApi(std::move(client));
}

boost::json::object first_request(const MockWsServer& server) {
    return boost::json::parse(server.sessions().front().received.front()).as_object();
}

} // namespace

TEST(WebsocketApiUserDataStreamsApi, CloseUserDataStream) {
    MockWsServer server(reply(
        R"json({"id":"819e1b1b-8c06-485b-a13e-131326c69599","status":200,"result":{},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const CloseUserDataStreamParams params{};
    const auto res = api.close_user_data_stream(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.stop");
}

TEST(WebsocketApiUserDataStreamsApi, CloseUserDataStreamWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"819e1b1b-8c06-485b-a13e-131326c69599","status":200,"result":{},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const CloseUserDataStreamParams params{
        .id = "e9d6b4349871b40611412680b3445fac",
    };
    const auto res = api.close_user_data_stream(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.stop");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
}

TEST(WebsocketApiUserDataStreamsApi, CloseUserDataStreamErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const CloseUserDataStreamParams params{};
    EXPECT_THROW((void)api.close_user_data_stream(params), common::WebsocketResponseError);
}

TEST(WebsocketApiUserDataStreamsApi, KeepaliveUserDataStream) {
    MockWsServer server(reply(
        R"json({"id":"815d5fce-0880-4287-a567-80badf004c74","status":200,"result":{"listenKey":"3HBntNTepshgEdjIwSUIBgB9keLyOCg5qv3n6bYAtktG8ejcaW5HXz9Vx1JgIieg"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const KeepaliveUserDataStreamParams params{};
    const auto res = api.keepalive_user_data_stream(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.ping");
}

TEST(WebsocketApiUserDataStreamsApi, KeepaliveUserDataStreamWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"815d5fce-0880-4287-a567-80badf004c74","status":200,"result":{"listenKey":"3HBntNTepshgEdjIwSUIBgB9keLyOCg5qv3n6bYAtktG8ejcaW5HXz9Vx1JgIieg"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const KeepaliveUserDataStreamParams params{
        .id = "e9d6b4349871b40611412680b3445fac",
    };
    const auto res = api.keepalive_user_data_stream(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.ping");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
}

TEST(WebsocketApiUserDataStreamsApi, KeepaliveUserDataStreamErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const KeepaliveUserDataStreamParams params{};
    EXPECT_THROW((void)api.keepalive_user_data_stream(params), common::WebsocketResponseError);
}

TEST(WebsocketApiUserDataStreamsApi, StartUserDataStream) {
    MockWsServer server(reply(
        R"json({"id":"d3df8a61-98ea-4fe0-8f4e-0fcea5d418b0","status":200,"result":{"listenKey":"xs0mRXdAKlIPDRFrlPcw0qI41Eh3ixNntmymGyhrhgqo7L6FuLaWArTD7RLP"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const StartUserDataStreamParams params{};
    const auto res = api.start_user_data_stream(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.start");
}

TEST(WebsocketApiUserDataStreamsApi, StartUserDataStreamWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"d3df8a61-98ea-4fe0-8f4e-0fcea5d418b0","status":200,"result":{"listenKey":"xs0mRXdAKlIPDRFrlPcw0qI41Eh3ixNntmymGyhrhgqo7L6FuLaWArTD7RLP"},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":2}]})json"));
    const auto api = api_for(server);
    const StartUserDataStreamParams params{
        .id = "e9d6b4349871b40611412680b3445fac",
    };
    const auto res = api.start_user_data_stream(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.start");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
}

TEST(WebsocketApiUserDataStreamsApi, StartUserDataStreamErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const StartUserDataStreamParams params{};
    EXPECT_THROW((void)api.start_user_data_stream(params), common::WebsocketResponseError);
}
