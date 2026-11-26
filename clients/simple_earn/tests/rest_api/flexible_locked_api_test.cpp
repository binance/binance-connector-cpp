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
#include <binance/simple_earn/rest_api/flexible_locked_api.hpp>

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

FlexibleLockedApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return FlexibleLockedApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiFlexibleLockedApi, GetCollateralRecord) {
    const std::string example =
        R"json({"rows":[{"amount":"100.00000000","productId":"BUSD001","asset":"USDT","createTime":1575018510000,"type":"REPAY","productName":"USDT","orderId":26055}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCollateralRecordParams params{};
    const auto res = api.get_collateral_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/history/collateralRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetCollateralRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"amount":"100.00000000","productId":"BUSD001","asset":"USDT","createTime":1575018510000,"type":"REPAY","productName":"USDT","orderId":26055}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCollateralRecordParams params{
        .product_id = "1",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_collateral_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetCollateralRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCollateralRecordParams params{};
    EXPECT_THROW((void)api.get_collateral_record(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetFlexiblePersonalLeftQuota) {
    const std::string example = R"json({"leftPersonalQuota":"1000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexiblePersonalLeftQuotaParams params{.product_id = "1"};
    const auto res = api.get_flexible_personal_left_quota(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/personalLeftQuota");
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexiblePersonalLeftQuotaWithOptionalParams) {
    const std::string example = R"json({"leftPersonalQuota":"1000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexiblePersonalLeftQuotaParams params{
        .product_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_personal_left_quota(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexiblePersonalLeftQuotaBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexiblePersonalLeftQuotaParams params{.product_id = "1"};
    EXPECT_THROW((void)api.get_flexible_personal_left_quota(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleProductPosition) {
    const std::string example =
        R"json({"rows":[{"totalAmount":"75.46000000","tierAnnualPercentageRate":{"0-5BTC":0.05,"5-10BTC":0.03},"latestAnnualPercentageRate":"0.02599895","yesterdayAirdropPercentageRate":"0.02599895","asset":"USDT","airDropAsset":"BETH","canRedeem":true,"collateralAmount":"232.23123213","productId":"USDT001","yesterdayRealTimeRewards":"0.10293829","cumulativeBonusRewards":"0.22759183","cumulativeRealTimeRewards":"0.22759183","cumulativeTotalRewards":"0.45459183","autoSubscribe":true}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleProductPositionParams params{};
    const auto res = api.get_flexible_product_position(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/position");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleProductPositionWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"totalAmount":"75.46000000","tierAnnualPercentageRate":{"0-5BTC":0.05,"5-10BTC":0.03},"latestAnnualPercentageRate":"0.02599895","yesterdayAirdropPercentageRate":"0.02599895","asset":"USDT","airDropAsset":"BETH","canRedeem":true,"collateralAmount":"232.23123213","productId":"USDT001","yesterdayRealTimeRewards":"0.10293829","cumulativeBonusRewards":"0.22759183","cumulativeRealTimeRewards":"0.22759183","cumulativeTotalRewards":"0.45459183","autoSubscribe":true}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleProductPositionParams params{
        .asset = "USDC",
        .product_id = "1",
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_product_position(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleProductPositionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleProductPositionParams params{};
    EXPECT_THROW((void)api.get_flexible_product_position(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleRedemptionRecord) {
    const std::string example =
        R"json({"rows":[{"amount":"10.54000000","asset":"USDT","time":1577257222000,"projectId":"USDT001","redeemId":40607,"destAccount":"SPOT","status":"PAID"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleRedemptionRecordParams params{};
    const auto res = api.get_flexible_redemption_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/history/redemptionRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleRedemptionRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"amount":"10.54000000","asset":"USDT","time":1577257222000,"projectId":"USDT001","redeemId":40607,"destAccount":"SPOT","status":"PAID"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleRedemptionRecordParams params{
        .product_id = "1",
        .redeem_id = "1",
        .asset = "USDC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_redemption_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("redeemId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleRedemptionRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleRedemptionRecordParams params{};
    EXPECT_THROW((void)api.get_flexible_redemption_record(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleRewardsHistory) {
    const std::string example =
        R"json({"rows":[{"asset":"BUSD","rewards":"0.00006408","projectId":"USDT001","type":"BONUS","time":1577233578000}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleRewardsHistoryParams params{};
    const auto res = api.get_flexible_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/history/rewardsRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleRewardsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"asset":"BUSD","rewards":"0.00006408","projectId":"USDT001","type":"BONUS","time":1577233578000}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleRewardsHistoryParams params{
        .product_id = "1",
        .asset = "USDC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .type = GetFlexibleRewardsHistoryTypeEnum::Bonus,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleRewardsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleRewardsHistoryParams params{};
    EXPECT_THROW((void)api.get_flexible_rewards_history(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleSubscriptionPreview) {
    const std::string example =
        R"json({"totalAmount":"1232.32230982","rewardAsset":"BUSD","airDropAsset":"BETH","estDailyBonusRewards":"0.22759183","estDailyRealTimeRewards":"0.22759183","estDailyAirdropRewards":"0.22759183"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleSubscriptionPreviewParams params{.product_id = "1",
                                                      .amount = common::Decimal("1.0")};
    const auto res = api.get_flexible_subscription_preview(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/subscriptionPreview");
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleSubscriptionPreviewWithOptionalParams) {
    const std::string example =
        R"json({"totalAmount":"1232.32230982","rewardAsset":"BUSD","airDropAsset":"BETH","estDailyBonusRewards":"0.22759183","estDailyRealTimeRewards":"0.22759183","estDailyAirdropRewards":"0.22759183"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleSubscriptionPreviewParams params{
        .product_id = "1",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_subscription_preview(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleSubscriptionPreviewBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleSubscriptionPreviewParams params{.product_id = "1",
                                                      .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.get_flexible_subscription_preview(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleSubscriptionRecord) {
    const std::string example =
        R"json({"rows":[{"amount":"100.00000000","asset":"USDT","time":1575018510000,"purchaseId":26055,"productId":"USDT001","type":"AUTO","sourceAccount":"SPOT","amtFromSpot":"30","amtFromFunding":"70","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleSubscriptionRecordParams params{};
    const auto res = api.get_flexible_subscription_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/history/subscriptionRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleSubscriptionRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"amount":"100.00000000","asset":"USDT","time":1575018510000,"purchaseId":26055,"productId":"USDT001","type":"AUTO","sourceAccount":"SPOT","amtFromSpot":"30","amtFromFunding":"70","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleSubscriptionRecordParams params{
        .product_id = "1",
        .purchase_id = "1",
        .asset = "USDC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_subscription_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("purchaseId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetFlexibleSubscriptionRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleSubscriptionRecordParams params{};
    EXPECT_THROW((void)api.get_flexible_subscription_record(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetLockedPersonalLeftQuota) {
    const std::string example = R"json({"leftPersonalQuota":"1000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedPersonalLeftQuotaParams params{.project_id = "1"};
    const auto res = api.get_locked_personal_left_quota(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/personalLeftQuota");
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedPersonalLeftQuotaWithOptionalParams) {
    const std::string example = R"json({"leftPersonalQuota":"1000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedPersonalLeftQuotaParams params{
        .project_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.get_locked_personal_left_quota(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedPersonalLeftQuotaBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetLockedPersonalLeftQuotaParams params{.project_id = "1"};
    EXPECT_THROW((void)api.get_locked_personal_left_quota(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetLockedProductPosition) {
    const std::string example =
        R"json({"rows":[{"positionId":123123,"parentPositionId":123122,"projectId":"Axs*90","asset":"AXS","amount":"122.09202928","purchaseTime":1646182276000,"duration":"60","accrualDays":"4","rewardAsset":"AXS","APY":"0.2032","rewardAmt":"5.17181528","extraRewardAsset":"BNB","extraRewardAPR":"0.0203","estExtraRewardAmt":"5.17181528","boostRewardAsset":"AXS","boostApr":"0.0121","totalBoostRewardAmt":"3.98201829","nextPay":"1.29295383","nextPayDate":1646697600000,"payPeriod":"1","redeemAmountEarly":"2802.24068892","rewardsEndDate":1651449600000,"deliverDate":1651536000000,"redeemPeriod":"1","redeemingAmt":"232.2323","redeemTo":"FLEXIBLE","partialAmtDeliverDate":1651536000000,"canRedeemEarly":true,"canFastRedemption":true,"autoSubscribe":true,"type":"AUTO","status":"HOLDING","canReStake":true}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedProductPositionParams params{};
    const auto res = api.get_locked_product_position(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/position");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedProductPositionWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"positionId":123123,"parentPositionId":123122,"projectId":"Axs*90","asset":"AXS","amount":"122.09202928","purchaseTime":1646182276000,"duration":"60","accrualDays":"4","rewardAsset":"AXS","APY":"0.2032","rewardAmt":"5.17181528","extraRewardAsset":"BNB","extraRewardAPR":"0.0203","estExtraRewardAmt":"5.17181528","boostRewardAsset":"AXS","boostApr":"0.0121","totalBoostRewardAmt":"3.98201829","nextPay":"1.29295383","nextPayDate":1646697600000,"payPeriod":"1","redeemAmountEarly":"2802.24068892","rewardsEndDate":1651449600000,"deliverDate":1651536000000,"redeemPeriod":"1","redeemingAmt":"232.2323","redeemTo":"FLEXIBLE","partialAmtDeliverDate":1651536000000,"canRedeemEarly":true,"canFastRedemption":true,"autoSubscribe":true,"type":"AUTO","status":"HOLDING","canReStake":true}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedProductPositionParams params{
        .asset = "USDC",
        .position_id = "1",
        .project_id = "1",
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_locked_product_position(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedProductPositionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetLockedProductPositionParams params{};
    EXPECT_THROW((void)api.get_locked_product_position(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetLockedRedemptionRecord) {
    const std::string example =
        R"json({"rows":[{"positionId":123123,"redeemId":40607,"time":1575018510000,"asset":"BNB","lockPeriod":"30","amount":"21312.23223","originalAmount":"21312.23223","type":"MATURE","deliverDate":1575018510000,"lossAmount":"0.00001232","isComplete":true,"rewardAsset":"AXS","rewardAmt":"5.17181528","extraRewardAsset":"BNB","estExtraRewardAmt":"5.17181528","status":"PAID"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedRedemptionRecordParams params{};
    const auto res = api.get_locked_redemption_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/history/redemptionRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedRedemptionRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"positionId":123123,"redeemId":40607,"time":1575018510000,"asset":"BNB","lockPeriod":"30","amount":"21312.23223","originalAmount":"21312.23223","type":"MATURE","deliverDate":1575018510000,"lossAmount":"0.00001232","isComplete":true,"rewardAsset":"AXS","rewardAmt":"5.17181528","extraRewardAsset":"BNB","estExtraRewardAmt":"5.17181528","status":"PAID"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedRedemptionRecordParams params{
        .position_id = "1",
        .redeem_id = "1",
        .asset = "USDC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_locked_redemption_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("redeemId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedRedemptionRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetLockedRedemptionRecordParams params{};
    EXPECT_THROW((void)api.get_locked_redemption_record(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetLockedRewardsHistory) {
    const std::string example =
        R"json({"rows":[{"positionId":123123,"time":1575018510000,"asset":"BNB","lockPeriod":"30","amount":"21312.23223","type":"Locked Rewards"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedRewardsHistoryParams params{};
    const auto res = api.get_locked_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/history/rewardsRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedRewardsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"positionId":123123,"time":1575018510000,"asset":"BNB","lockPeriod":"30","amount":"21312.23223","type":"Locked Rewards"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedRewardsHistoryParams params{
        .position_id = "1",
        .asset = "USDC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_locked_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedRewardsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetLockedRewardsHistoryParams params{};
    EXPECT_THROW((void)api.get_locked_rewards_history(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetLockedSubscriptionPreview) {
    const std::string example =
        R"json([{"rewardAsset":"AXS","totalRewardAmt":"5.17181528","extraRewardAsset":"BNB","estTotalExtraRewardAmt":"5.17181528","boostRewardAsset":"AXS","estDailyRewardAmt":"1.20928901","nextPay":"1.29295383","nextPayDate":1646697600000,"valueDate":1646697600000,"rewardsEndDate":1651449600000,"deliverDate":1651536000000,"nextSubscriptionDate":1651536000000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedSubscriptionPreviewParams params{.project_id = "1",
                                                    .amount = common::Decimal("1.0")};
    const auto res = api.get_locked_subscription_preview(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/subscriptionPreview");
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedSubscriptionPreviewWithOptionalParams) {
    const std::string example =
        R"json([{"rewardAsset":"AXS","totalRewardAmt":"5.17181528","extraRewardAsset":"BNB","estTotalExtraRewardAmt":"5.17181528","boostRewardAsset":"AXS","estDailyRewardAmt":"1.20928901","nextPay":"1.29295383","nextPayDate":1646697600000,"valueDate":1646697600000,"rewardsEndDate":1651449600000,"deliverDate":1651536000000,"nextSubscriptionDate":1651536000000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedSubscriptionPreviewParams params{
        .project_id = "1",
        .amount = common::Decimal("1.0"),
        .auto_subscribe = true,
        .recv_window = 5000,
    };
    const auto res = api.get_locked_subscription_preview(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoSubscribe="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedSubscriptionPreviewBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetLockedSubscriptionPreviewParams params{.project_id = "1",
                                                    .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.get_locked_subscription_preview(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetLockedSubscriptionRecord) {
    const std::string example =
        R"json({"rows":[{"positionId":123123,"purchaseId":"26055","projectId":"Axs*90","time":1575018510000,"asset":"BNB","amount":"21312.23223","lockPeriod":"30","type":"AUTO","sourceAccount":"SPOT","amtFromSpot":"30","amtFromFunding":"70","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedSubscriptionRecordParams params{};
    const auto res = api.get_locked_subscription_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/history/subscriptionRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedSubscriptionRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"positionId":123123,"purchaseId":"26055","projectId":"Axs*90","time":1575018510000,"asset":"BNB","amount":"21312.23223","lockPeriod":"30","type":"AUTO","sourceAccount":"SPOT","amtFromSpot":"30","amtFromFunding":"70","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLockedSubscriptionRecordParams params{
        .purchase_id = "1",
        .asset = "USDC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_locked_subscription_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("purchaseId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetLockedSubscriptionRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetLockedSubscriptionRecordParams params{};
    EXPECT_THROW((void)api.get_locked_subscription_record(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetRateHistory) {
    const std::string example =
        R"json({"rows":[{"productId":"BUSD001","asset":"BUSD","annualPercentageRate":"0.00006408","time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRateHistoryParams params{.product_id = "1"};
    const auto res = api.get_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/history/rateHistory");
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetRateHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"productId":"BUSD001","asset":"BUSD","annualPercentageRate":"0.00006408","time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRateHistoryParams params{
        .product_id = "1",
        .apr_period = GetRateHistoryAprPeriodEnum::Day,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("aprPeriod="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetRateHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetRateHistoryParams params{.product_id = "1"};
    EXPECT_THROW((void)api.get_rate_history(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetSimpleEarnFlexibleProductList) {
    const std::string example =
        R"json({"rows":[{"asset":"BTC","latestAnnualPercentageRate":"0.05000000","tierAnnualPercentageRate":{"0-5BTC":0.05,"5-10BTC":0.03},"airDropPercentageRate":"0.05000000","canPurchase":true,"canRedeem":true,"isSoldOut":true,"hot":true,"minPurchaseAmount":"0.01000000","productId":"BTC001","subscriptionStartTime":1646182276000,"status":"PURCHASING"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSimpleEarnFlexibleProductListParams params{};
    const auto res = api.get_simple_earn_flexible_product_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetSimpleEarnFlexibleProductListWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"asset":"BTC","latestAnnualPercentageRate":"0.05000000","tierAnnualPercentageRate":{"0-5BTC":0.05,"5-10BTC":0.03},"airDropPercentageRate":"0.05000000","canPurchase":true,"canRedeem":true,"isSoldOut":true,"hot":true,"minPurchaseAmount":"0.01000000","productId":"BTC001","subscriptionStartTime":1646182276000,"status":"PURCHASING"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSimpleEarnFlexibleProductListParams params{
        .asset = "USDC",
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_simple_earn_flexible_product_list(params);
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

TEST(RestApiFlexibleLockedApi, GetSimpleEarnFlexibleProductListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSimpleEarnFlexibleProductListParams params{};
    EXPECT_THROW((void)api.get_simple_earn_flexible_product_list(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, GetSimpleEarnLockedProductList) {
    const std::string example =
        R"json({"rows":[{"projectId":"Axs*90","detail":{"asset":"AXS","rewardAsset":"AXS","duration":90,"renewable":true,"isSoldOut":true,"apr":"1.2069","status":"CREATED","subscriptionStartTime":1646182276000,"extraRewardAsset":"BNB","extraRewardAPR":"0.23","boostRewardAsset":"AXS","boostApr":"0.0121","boostEndTime":1646182276000},"quota":{"totalPersonalQuota":"2","minimum":"0.001"}}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSimpleEarnLockedProductListParams params{};
    const auto res = api.get_simple_earn_locked_product_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, GetSimpleEarnLockedProductListWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"projectId":"Axs*90","detail":{"asset":"AXS","rewardAsset":"AXS","duration":90,"renewable":true,"isSoldOut":true,"apr":"1.2069","status":"CREATED","subscriptionStartTime":1646182276000,"extraRewardAsset":"BNB","extraRewardAPR":"0.23","boostRewardAsset":"AXS","boostApr":"0.0121","boostEndTime":1646182276000},"quota":{"totalPersonalQuota":"2","minimum":"0.001"}}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSimpleEarnLockedProductListParams params{
        .asset = "USDC",
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_simple_earn_locked_product_list(params);
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

TEST(RestApiFlexibleLockedApi, GetSimpleEarnLockedProductListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSimpleEarnLockedProductListParams params{};
    EXPECT_THROW((void)api.get_simple_earn_locked_product_list(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, RedeemFlexibleProduct) {
    const std::string example = R"json({"redeemId":40607,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemFlexibleProductParams params{.product_id = "1"};
    const auto res = api.redeem_flexible_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/redeem");
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, RedeemFlexibleProductWithOptionalParams) {
    const std::string example = R"json({"redeemId":40607,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemFlexibleProductParams params{
        .product_id = "1",
        .redeem_all = false,
        .amount = common::Decimal("1.0"),
        .dest_account = RedeemFlexibleProductDestAccountEnum::Spot,
        .recv_window = 5000,
    };
    const auto res = api.redeem_flexible_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("redeemAll="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("destAccount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, RedeemFlexibleProductBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RedeemFlexibleProductParams params{.product_id = "1"};
    EXPECT_THROW((void)api.redeem_flexible_product(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, RedeemLockedProduct) {
    const std::string example = R"json({"redeemId":40607,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemLockedProductParams params{.position_id = "1"};
    const auto res = api.redeem_locked_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/redeem");
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, RedeemLockedProductWithOptionalParams) {
    const std::string example = R"json({"redeemId":40607,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemLockedProductParams params{
        .position_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.redeem_locked_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, RedeemLockedProductBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RedeemLockedProductParams params{.position_id = "1"};
    EXPECT_THROW((void)api.redeem_locked_product(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, SetFlexibleAutoSubscribe) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetFlexibleAutoSubscribeParams params{.product_id = "1", .auto_subscribe = true};
    const auto res = api.set_flexible_auto_subscribe(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/setAutoSubscribe");
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoSubscribe="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SetFlexibleAutoSubscribeWithOptionalParams) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetFlexibleAutoSubscribeParams params{
        .product_id = "1",
        .auto_subscribe = true,
        .recv_window = 5000,
    };
    const auto res = api.set_flexible_auto_subscribe(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoSubscribe="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SetFlexibleAutoSubscribeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SetFlexibleAutoSubscribeParams params{.product_id = "1", .auto_subscribe = true};
    EXPECT_THROW((void)api.set_flexible_auto_subscribe(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, SetLockedAutoSubscribe) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetLockedAutoSubscribeParams params{.position_id = "1", .auto_subscribe = true};
    const auto res = api.set_locked_auto_subscribe(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/setAutoSubscribe");
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoSubscribe="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SetLockedAutoSubscribeWithOptionalParams) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetLockedAutoSubscribeParams params{
        .position_id = "1",
        .auto_subscribe = true,
        .recv_window = 5000,
    };
    const auto res = api.set_locked_auto_subscribe(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoSubscribe="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SetLockedAutoSubscribeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SetLockedAutoSubscribeParams params{.position_id = "1", .auto_subscribe = true};
    EXPECT_THROW((void)api.set_locked_auto_subscribe(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, SetLockedProductRedeemOption) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetLockedProductRedeemOptionParams params{
        .position_id = "1", .redeem_to = SetLockedProductRedeemOptionRedeemToEnum::Spot};
    const auto res = api.set_locked_product_redeem_option(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/setRedeemOption");
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("redeemTo="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SetLockedProductRedeemOptionWithOptionalParams) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetLockedProductRedeemOptionParams params{
        .position_id = "1",
        .redeem_to = SetLockedProductRedeemOptionRedeemToEnum::Spot,
        .recv_window = 5000,
    };
    const auto res = api.set_locked_product_redeem_option(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("redeemTo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SetLockedProductRedeemOptionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SetLockedProductRedeemOptionParams params{
        .position_id = "1", .redeem_to = SetLockedProductRedeemOptionRedeemToEnum::Spot};
    EXPECT_THROW((void)api.set_locked_product_redeem_option(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, SimpleAccount) {
    const std::string example =
        R"json({"totalAmountInBTC":"0.01067982","totalAmountInUSDT":"77.13289230","totalFlexibleAmountInBTC":"0.00000000","totalFlexibleAmountInUSDT":"0.00000000","totalLockedInBTC":"0.01067982","totalLockedInUSDT":"77.13289230"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SimpleAccountParams params{};
    const auto res = api.simple_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SimpleAccountWithOptionalParams) {
    const std::string example =
        R"json({"totalAmountInBTC":"0.01067982","totalAmountInUSDT":"77.13289230","totalFlexibleAmountInBTC":"0.00000000","totalFlexibleAmountInUSDT":"0.00000000","totalLockedInBTC":"0.01067982","totalLockedInUSDT":"77.13289230"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SimpleAccountParams params{
        .recv_window = 5000,
    };
    const auto res = api.simple_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SimpleAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SimpleAccountParams params{};
    EXPECT_THROW((void)api.simple_account(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, SubscribeFlexibleProduct) {
    const std::string example = R"json({"purchaseId":40607,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeFlexibleProductParams params{.product_id = "1",
                                                .amount = common::Decimal("1.0")};
    const auto res = api.subscribe_flexible_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/flexible/subscribe");
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SubscribeFlexibleProductWithOptionalParams) {
    const std::string example = R"json({"purchaseId":40607,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeFlexibleProductParams params{
        .product_id = "1",
        .amount = common::Decimal("1.0"),
        .auto_subscribe = true,
        .source_account = SubscribeFlexibleProductSourceAccountEnum::Spot,
        .recv_window = 5000,
    };
    const auto res = api.subscribe_flexible_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoSubscribe="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sourceAccount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SubscribeFlexibleProductBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubscribeFlexibleProductParams params{.product_id = "1",
                                                .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.subscribe_flexible_product(params), common::BadRequestError);
}

TEST(RestApiFlexibleLockedApi, SubscribeLockedProduct) {
    const std::string example =
        R"json({"purchaseId":40607,"positionId":"12345","success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeLockedProductParams params{.project_id = "1", .amount = common::Decimal("1.0")};
    const auto res = api.subscribe_locked_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/simple-earn/locked/subscribe");
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SubscribeLockedProductWithOptionalParams) {
    const std::string example =
        R"json({"purchaseId":40607,"positionId":"12345","success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeLockedProductParams params{
        .project_id = "1",
        .amount = common::Decimal("1.0"),
        .auto_subscribe = false,
        .source_account = SubscribeLockedProductSourceAccountEnum::Spot,
        .redeem_to = SubscribeLockedProductRedeemToEnum::Spot,
        .recv_window = 5000,
    };
    const auto res = api.subscribe_locked_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoSubscribe="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sourceAccount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("redeemTo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleLockedApi, SubscribeLockedProductBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubscribeLockedProductParams params{.project_id = "1", .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.subscribe_locked_product(params), common::BadRequestError);
}
