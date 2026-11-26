//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string>

#include <gtest/gtest.h>

#include <binance/common/errors.hpp>
#include <binance/common/rest.hpp>
#include <binance/margin_trading/rest_api/user_data_stream_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::margin_trading::rest_api;
using binance::test::MockResponse;
using binance::test::MockServer;
using binance::test::RecordedRequest;

namespace {

MockServer::Handler reply(std::string body, unsigned status = 200) {
    return [body = std::move(body), status](const RecordedRequest&) {
        MockResponse r;
        r.status = status;
        r.body = body.empty() ? "{}" : body;
        return r;
    };
}

UserDataStreamApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return UserDataStreamApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiUserDataStreamApi, CloseUserDataStream) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.close_user_data_stream();
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/listen-key");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataStreamApi, CloseUserDataStreamBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.close_user_data_stream(), common::BadRequestError);
}

TEST(RestApiUserDataStreamApi, KeepaliveUserDataStream) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KeepaliveUserDataStreamParams params{.listen_key = "listenKey_example"};
    const auto res = api.keepalive_user_data_stream(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/listen-key");
    EXPECT_NE((rec.query() + "&" + rec.body).find("listenKey="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataStreamApi, KeepaliveUserDataStreamBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const KeepaliveUserDataStreamParams params{.listen_key = "listenKey_example"};
    EXPECT_THROW((void)api.keepalive_user_data_stream(params), common::BadRequestError);
}

TEST(RestApiUserDataStreamApi, StartUserDataStream) {
    const std::string example =
        R"json({"listenKey":"T3ee22BIYuWqmvne0HNq2A2WsFlEtLhvWCtItw6ffhhd"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.start_user_data_stream();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/listen-key");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataStreamApi, StartUserDataStreamBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.start_user_data_stream(), common::BadRequestError);
}

TEST(RestApiUserDataStreamApi, CloseUserDataStreamV2) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.close_user_data_stream_v2();
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v2/margin/listen-key");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataStreamApi, CloseUserDataStreamV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.close_user_data_stream_v2(), common::BadRequestError);
}

TEST(RestApiUserDataStreamApi, KeepaliveUserDataStreamV2) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KeepaliveUserDataStreamV2Params params{.listen_key = "listenKey_example"};
    const auto res = api.keepalive_user_data_stream_v2(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/sapi/v2/margin/listen-key");
    EXPECT_NE((rec.query() + "&" + rec.body).find("listenKey="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataStreamApi, KeepaliveUserDataStreamV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const KeepaliveUserDataStreamV2Params params{.listen_key = "listenKey_example"};
    EXPECT_THROW((void)api.keepalive_user_data_stream_v2(params), common::BadRequestError);
}

TEST(RestApiUserDataStreamApi, StartUserDataStreamV2) {
    const std::string example =
        R"json({"listenKey":"T3ee22BIYuWqmvne0HNq2A2WsFlEtLhvWCtItw6ffhhd"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.start_user_data_stream_v2();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v2/margin/listen-key");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataStreamApi, StartUserDataStreamV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.start_user_data_stream_v2(), common::BadRequestError);
}
