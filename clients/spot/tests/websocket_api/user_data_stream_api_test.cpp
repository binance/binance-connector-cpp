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
#include <binance/spot/websocket_api/user_data_stream_api.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::spot::websocket_api;
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

UserDataStreamApi api_for(const MockWsServer& server) {
    common::WebsocketApiConfig cfg;
    cfg.url = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    cfg.proxy_from_env = false;
    auto client = std::make_shared<common::WebsocketApi>(std::move(cfg));
    client->connect();
    return UserDataStreamApi(std::move(client));
}

boost::json::object first_request(const MockWsServer& server) {
    return boost::json::parse(server.sessions().front().received.front()).as_object();
}

} // namespace

TEST(WebsocketApiUserDataStreamApi, SessionSubscriptions) {
    MockWsServer server(reply(
        R"json({"id":"d3df5a22-88ea-4fe0-9f4e-0fcea5d418b7","status":200,"result":[{"subscriptionId":0},{"subscriptionId":1}]})json"));
    const auto api = api_for(server);
    const SessionSubscriptionsParams params{};
    const auto res = api.session_subscriptions(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "session.subscriptions");
}

TEST(WebsocketApiUserDataStreamApi, SessionSubscriptionsWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"d3df5a22-88ea-4fe0-9f4e-0fcea5d418b7","status":200,"result":[{"subscriptionId":0},{"subscriptionId":1}]})json"));
    const auto api = api_for(server);
    const SessionSubscriptionsParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
    };
    const auto res = api.session_subscriptions(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "session.subscriptions");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
}

TEST(WebsocketApiUserDataStreamApi, SessionSubscriptionsErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const SessionSubscriptionsParams params{};
    EXPECT_THROW((void)api.session_subscriptions(params), common::WebsocketResponseError);
}

TEST(WebsocketApiUserDataStreamApi, UserDataStreamSubscribe) {
    MockWsServer server(reply(
        R"json({"id":"d3df8a21-98ea-4fe0-8f4e-0fcea5d418b7","status":200,"result":{"subscriptionId":0}})json"));
    const auto api = api_for(server);
    const UserDataStreamSubscribeParams params{};
    const auto res = api.user_data_stream_subscribe(params);
    EXPECT_NO_THROW((void)res.response.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.subscribe");
}

TEST(WebsocketApiUserDataStreamApi, UserDataStreamSubscribeWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"d3df8a21-98ea-4fe0-8f4e-0fcea5d418b7","status":200,"result":{"subscriptionId":0}})json"));
    const auto api = api_for(server);
    const UserDataStreamSubscribeParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .filter = boost::json::object{},
    };
    const auto res = api.user_data_stream_subscribe(params);
    EXPECT_NO_THROW((void)res.response.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.subscribe");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("filter"));
}

TEST(WebsocketApiUserDataStreamApi, UserDataStreamSubscribeErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const UserDataStreamSubscribeParams params{};
    EXPECT_THROW((void)api.user_data_stream_subscribe(params), common::WebsocketResponseError);
}

TEST(WebsocketApiUserDataStreamApi, UserDataStreamSubscribeSignature) {
    MockWsServer server(reply(
        R"json({"id":"d3df8a22-98ea-4fe0-9f4e-0fcea5d418b7","status":200,"result":{"subscriptionId":0}})json"));
    const auto api = api_for(server);
    const UserDataStreamSubscribeSignatureParams params{};
    const auto res = api.user_data_stream_subscribe_signature(params);
    EXPECT_NO_THROW((void)res.response.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.subscribe.signature");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiUserDataStreamApi, UserDataStreamSubscribeSignatureWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"d3df8a22-98ea-4fe0-9f4e-0fcea5d418b7","status":200,"result":{"subscriptionId":0}})json"));
    const auto api = api_for(server);
    const UserDataStreamSubscribeSignatureParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .recv_window = common::Decimal("5000"),
        .filter = boost::json::object{},
    };
    const auto res = api.user_data_stream_subscribe_signature(params);
    EXPECT_NO_THROW((void)res.response.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.subscribe.signature");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("filter"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiUserDataStreamApi, UserDataStreamSubscribeSignatureErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const UserDataStreamSubscribeSignatureParams params{};
    EXPECT_THROW((void)api.user_data_stream_subscribe_signature(params),
                 common::WebsocketResponseError);
}

TEST(WebsocketApiUserDataStreamApi, UserDataStreamUnsubscribe) {
    MockWsServer server(
        reply(R"json({"id":"d3df8a21-98ea-4fe0-8f4e-0fcea5d418b7","status":200,"result":{}})json"));
    const auto api = api_for(server);
    const UserDataStreamUnsubscribeParams params{};
    const auto res = api.user_data_stream_unsubscribe(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.unsubscribe");
}

TEST(WebsocketApiUserDataStreamApi, UserDataStreamUnsubscribeWithOptionalParams) {
    MockWsServer server(
        reply(R"json({"id":"d3df8a21-98ea-4fe0-8f4e-0fcea5d418b7","status":200,"result":{}})json"));
    const auto api = api_for(server);
    const UserDataStreamUnsubscribeParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .subscription_id = 1,
    };
    const auto res = api.user_data_stream_unsubscribe(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "userDataStream.unsubscribe");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("subscriptionId"));
}

TEST(WebsocketApiUserDataStreamApi, UserDataStreamUnsubscribeErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const UserDataStreamUnsubscribeParams params{};
    EXPECT_THROW((void)api.user_data_stream_unsubscribe(params), common::WebsocketResponseError);
}
