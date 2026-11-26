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
#include <binance/wallet/rest_api/others_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::wallet::rest_api;
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

OthersApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return OthersApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiOthersApi, GetSymbolsDelistScheduleForSpot) {
    const std::string example = R"json([{"delistTime":1686161202000,"symbols":["ADAUSDT"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSymbolsDelistScheduleForSpotParams params{};
    const auto res = api.get_symbols_delist_schedule_for_spot(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/spot/delist-schedule");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOthersApi, GetSymbolsDelistScheduleForSpotWithOptionalParams) {
    const std::string example = R"json([{"delistTime":1686161202000,"symbols":["ADAUSDT"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSymbolsDelistScheduleForSpotParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_symbols_delist_schedule_for_spot(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
}

TEST(RestApiOthersApi, GetSymbolsDelistScheduleForSpotBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSymbolsDelistScheduleForSpotParams params{};
    EXPECT_THROW((void)api.get_symbols_delist_schedule_for_spot(params), common::BadRequestError);
}

TEST(RestApiOthersApi, SystemStatus) {
    const std::string example = R"json({"status":0,"msg":"normal"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.system_status();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/system/status");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOthersApi, SystemStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.system_status(), common::BadRequestError);
}
