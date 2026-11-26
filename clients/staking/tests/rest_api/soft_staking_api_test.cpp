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
#include <binance/staking/rest_api/soft_staking_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::staking::rest_api;
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

SoftStakingApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return SoftStakingApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiSoftStakingApi, GetSoftStakingProductList) {
    const std::string example =
        R"json({"status":true,"totalRewardsUsdt":"3.09827182","rows":[{"asset":"BNB","minAmount":"0.5","maxCap":"1000","apr":"0.0015","stakedAmount":"2.14","totalProfit":"0.00171234"}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSoftStakingProductListParams params{};
    const auto res = api.get_soft_staking_product_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/soft-staking/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSoftStakingApi, GetSoftStakingProductListWithOptionalParams) {
    const std::string example =
        R"json({"status":true,"totalRewardsUsdt":"3.09827182","rows":[{"asset":"BNB","minAmount":"0.5","maxCap":"1000","apr":"0.0015","stakedAmount":"2.14","totalProfit":"0.00171234"}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSoftStakingProductListParams params{
        .asset = "BTC",
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_soft_staking_product_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSoftStakingApi, GetSoftStakingProductListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSoftStakingProductListParams params{};
    EXPECT_THROW((void)api.get_soft_staking_product_list(params), common::BadRequestError);
}

TEST(RestApiSoftStakingApi, GetSoftStakingRewardsHistory) {
    const std::string example =
        R"json({"rows":[{"asset":"BNB","rewards":"0.00000557","rewardAsset":"BNB","avgAmount":"2.14","time":1754007978000}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSoftStakingRewardsHistoryParams params{};
    const auto res = api.get_soft_staking_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/soft-staking/history/rewardsRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSoftStakingApi, GetSoftStakingRewardsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"asset":"BNB","rewards":"0.00000557","rewardAsset":"BNB","avgAmount":"2.14","time":1754007978000}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSoftStakingRewardsHistoryParams params{
        .asset = "BTC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_soft_staking_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSoftStakingApi, GetSoftStakingRewardsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSoftStakingRewardsHistoryParams params{};
    EXPECT_THROW((void)api.get_soft_staking_rewards_history(params), common::BadRequestError);
}

TEST(RestApiSoftStakingApi, SetSoftStaking) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetSoftStakingParams params{.soft_staking = true};
    const auto res = api.set_soft_staking(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/soft-staking/set");
    EXPECT_NE((rec.query() + "&" + rec.body).find("softStaking="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSoftStakingApi, SetSoftStakingWithOptionalParams) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetSoftStakingParams params{
        .soft_staking = true,
        .recv_window = 5000,
    };
    const auto res = api.set_soft_staking(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("softStaking="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSoftStakingApi, SetSoftStakingBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SetSoftStakingParams params{.soft_staking = true};
    EXPECT_THROW((void)api.set_soft_staking(params), common::BadRequestError);
}
