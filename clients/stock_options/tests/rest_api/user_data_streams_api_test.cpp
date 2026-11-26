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
#include <binance/stock_options/rest_api/user_data_streams_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::stock_options::rest_api;
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

UserDataStreamsApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return UserDataStreamsApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiUserDataStreamsApi, CreateRenewListenKey) {
    const std::string example = R"json({"listenKey":"3f9a1c2e-7b4d-4e8a-9c61-0d2f5b7e8a13"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateRenewListenKeyParams params{};
    const auto res = api.create_renew_listen_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/listenKey");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserDataStreamsApi, CreateRenewListenKeyWithOptionalParams) {
    const std::string example = R"json({"listenKey":"3f9a1c2e-7b4d-4e8a-9c61-0d2f5b7e8a13"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateRenewListenKeyParams params{
        .recv_window = 5000,
    };
    const auto res = api.create_renew_listen_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
}

TEST(RestApiUserDataStreamsApi, CreateRenewListenKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateRenewListenKeyParams params{};
    EXPECT_THROW((void)api.create_renew_listen_key(params), common::BadRequestError);
}
