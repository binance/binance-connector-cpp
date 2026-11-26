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
#include <binance/simple_earn/rest_api/yield_arena_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::simple_earn::rest_api;
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

YieldArenaApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return YieldArenaApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiYieldArenaApi, GetYieldArenaActivities) {
    const std::string example =
        R"json({"activities":[{"activityId":10001,"activityType":"AIRDROP","title":"Hold FDUSD & Earn BNB Airdrop","description":"Subscribe to FDUSD Flexible and earn bonus BNB airdrop.","rewardPoolInUsd":"50000","rewardToken":["BNB"],"redirectUrl":"https://www.binance.com/en/earn/arena/airdrop-123","startTime":1713052800000,"endTime":1713657600000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetYieldArenaActivitiesParams params{};
    const auto res = api.get_yield_arena_activities(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/earn/arena/activities");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiYieldArenaApi, GetYieldArenaActivitiesWithOptionalParams) {
    const std::string example =
        R"json({"activities":[{"activityId":10001,"activityType":"AIRDROP","title":"Hold FDUSD & Earn BNB Airdrop","description":"Subscribe to FDUSD Flexible and earn bonus BNB airdrop.","rewardPoolInUsd":"50000","rewardToken":["BNB"],"redirectUrl":"https://www.binance.com/en/earn/arena/airdrop-123","startTime":1713052800000,"endTime":1713657600000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetYieldArenaActivitiesParams params{
        .lang = "en",
        .recv_window = 5000,
    };
    const auto res = api.get_yield_arena_activities(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_TRUE(rec.has_header("lang"));
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiYieldArenaApi, GetYieldArenaActivitiesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetYieldArenaActivitiesParams params{};
    EXPECT_THROW((void)api.get_yield_arena_activities(params), common::BadRequestError);
}
