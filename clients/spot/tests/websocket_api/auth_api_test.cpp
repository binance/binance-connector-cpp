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
#include <binance/spot/websocket_api/auth_api.hpp>

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

AuthApi api_for(const MockWsServer& server) {
    common::WebsocketApiConfig cfg;
    cfg.url = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    cfg.proxy_from_env = false;
    auto client = std::make_shared<common::WebsocketApi>(std::move(cfg));
    client->connect();
    return AuthApi(std::move(client));
}

boost::json::object first_request(const MockWsServer& server) {
    return boost::json::parse(server.sessions().front().received.front()).as_object();
}

} // namespace

TEST(WebsocketApiAuthApi, SessionLogon) {
    MockWsServer server(reply(
        R"json({"id":"c174a2b1-3f51-4580-b200-8528bd237cb7","status":200,"result":{"apiKey":"YOUR_API_KEY","authorizedSince":1649729878532,"connectedSince":1649729873021,"returnRateLimits":false,"serverTime":1649729878630,"userDataStream":false}})json"));
    const auto api = api_for(server);
    const SessionLogonParams params{};
    const auto res = api.session_logon(params);
    ASSERT_FALSE(res.empty());
    EXPECT_NO_THROW((void)res.front().data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "session.logon");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAuthApi, SessionLogonWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"c174a2b1-3f51-4580-b200-8528bd237cb7","status":200,"result":{"apiKey":"YOUR_API_KEY","authorizedSince":1649729878532,"connectedSince":1649729873021,"returnRateLimits":false,"serverTime":1649729878630,"userDataStream":false}})json"));
    const auto api = api_for(server);
    const SessionLogonParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
        .recv_window = common::Decimal("5000"),
    };
    const auto res = api.session_logon(params);
    ASSERT_FALSE(res.empty());
    EXPECT_NO_THROW((void)res.front().data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "session.logon");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAuthApi, SessionLogonErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const SessionLogonParams params{};
    EXPECT_THROW((void)api.session_logon(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAuthApi, SessionLogout) {
    MockWsServer server(reply(
        R"json({"id":"c174a2b1-3f51-4580-b200-8528bd237cb7","status":200,"result":{"apiKey":"apiKey","authorizedSince":1,"connectedSince":1649729873021,"returnRateLimits":false,"serverTime":1649730611671,"userDataStream":false}})json"));
    const auto api = api_for(server);
    const SessionLogoutParams params{};
    const auto res = api.session_logout(params);
    ASSERT_FALSE(res.empty());
    EXPECT_NO_THROW((void)res.front().data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "session.logout");
}

TEST(WebsocketApiAuthApi, SessionLogoutWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"c174a2b1-3f51-4580-b200-8528bd237cb7","status":200,"result":{"apiKey":"apiKey","authorizedSince":1,"connectedSince":1649729873021,"returnRateLimits":false,"serverTime":1649730611671,"userDataStream":false}})json"));
    const auto api = api_for(server);
    const SessionLogoutParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
    };
    const auto res = api.session_logout(params);
    ASSERT_FALSE(res.empty());
    EXPECT_NO_THROW((void)res.front().data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "session.logout");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
}

TEST(WebsocketApiAuthApi, SessionLogoutErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const SessionLogoutParams params{};
    EXPECT_THROW((void)api.session_logout(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAuthApi, SessionStatus) {
    MockWsServer server(reply(
        R"json({"id":"b50c16cd-62c9-4e29-89e4-37f10111f5bf","status":200,"result":{"apiKey":"YOUR_API_KEY","authorizedSince":1649729878532,"connectedSince":1649729873021,"returnRateLimits":false,"serverTime":1649730611671,"userDataStream":true}})json"));
    const auto api = api_for(server);
    const SessionStatusParams params{};
    const auto res = api.session_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "session.status");
}

TEST(WebsocketApiAuthApi, SessionStatusWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"b50c16cd-62c9-4e29-89e4-37f10111f5bf","status":200,"result":{"apiKey":"YOUR_API_KEY","authorizedSince":1649729878532,"connectedSince":1649729873021,"returnRateLimits":false,"serverTime":1649730611671,"userDataStream":true}})json"));
    const auto api = api_for(server);
    const SessionStatusParams params{
        .id = "5494febb-d167-46a2-996d-70533eb4d976",
    };
    const auto res = api.session_status(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "session.status");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();
}

TEST(WebsocketApiAuthApi, SessionStatusErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const SessionStatusParams params{};
    EXPECT_THROW((void)api.session_status(params), common::WebsocketResponseError);
}
