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
#include <binance/staking/rest_api/on_chain_yields_api.hpp>

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

OnChainYieldsApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return OnChainYieldsApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedPersonalLeftQuota) {
    const std::string example = R"json({"leftPersonalQuota":"1000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedPersonalLeftQuotaParams params{.project_id = "1"};
    const auto res = api.get_on_chain_yields_locked_personal_left_quota(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/personalLeftQuota");
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedPersonalLeftQuotaWithOptionalParams) {
    const std::string example = R"json({"leftPersonalQuota":"1000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedPersonalLeftQuotaParams params{
        .project_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.get_on_chain_yields_locked_personal_left_quota(params);
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

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedPersonalLeftQuotaBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedPersonalLeftQuotaParams params{.project_id = "1"};
    EXPECT_THROW((void)api.get_on_chain_yields_locked_personal_left_quota(params),
                 common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedProductList) {
    const std::string example =
        R"json({"rows":[{"projectId":"Solv-60d","detail":{"asset":"BTC","rewardAsset":"SOLV","duration":60,"renewable":true,"isSoldOut":true,"apr":"0.039","status":"PREHEATING","subscriptionStartTime":1646182276000,"canRedeemToFlex":true},"quota":{"totalPersonalQuota":"2","minimum":"0.001"}}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedProductListParams params{};
    const auto res = api.get_on_chain_yields_locked_product_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedProductListWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"projectId":"Solv-60d","detail":{"asset":"BTC","rewardAsset":"SOLV","duration":60,"renewable":true,"isSoldOut":true,"apr":"0.039","status":"PREHEATING","subscriptionStartTime":1646182276000,"canRedeemToFlex":true},"quota":{"totalPersonalQuota":"2","minimum":"0.001"}}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedProductListParams params{
        .asset = "SOL",
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_on_chain_yields_locked_product_list(params);
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

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedProductListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedProductListParams params{};
    EXPECT_THROW((void)api.get_on_chain_yields_locked_product_list(params),
                 common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedProductPosition) {
    const std::string example =
        R"json({"rows":[{"positionId":"123123","projectId":"Solv-60d","asset":"BTC","amount":"122.09202928","purchaseTime":"1646182276000","duration":"60","accrualDays":"4","rewardAsset":"SOLV","APY":"0.039","rewardAmt":"5.17181528","nextPay":"1.29295383","nextPayDate":"1646697600000","payPeriod":"1","rewardsPayDate":"1646697600000","rewardsEndDate":"1651449600000","deliverDate":"1651536000000","nextSubscriptionDate":"1651536000000","redeemingAmt":"232.2323","redeemTo":"FLEXIBLE","canRedeemEarly":true,"autoSubscribe":true,"type":"AUTO","status":"HOLDING"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedProductPositionParams params{};
    const auto res = api.get_on_chain_yields_locked_product_position(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/position");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedProductPositionWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"positionId":"123123","projectId":"Solv-60d","asset":"BTC","amount":"122.09202928","purchaseTime":"1646182276000","duration":"60","accrualDays":"4","rewardAsset":"SOLV","APY":"0.039","rewardAmt":"5.17181528","nextPay":"1.29295383","nextPayDate":"1646697600000","payPeriod":"1","rewardsPayDate":"1646697600000","rewardsEndDate":"1651449600000","deliverDate":"1651536000000","nextSubscriptionDate":"1651536000000","redeemingAmt":"232.2323","redeemTo":"FLEXIBLE","canRedeemEarly":true,"autoSubscribe":true,"type":"AUTO","status":"HOLDING"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedProductPositionParams params{
        .asset = "BTC",
        .position_id = "1",
        .project_id = "1",
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_on_chain_yields_locked_product_position(params);
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

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedProductPositionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedProductPositionParams params{};
    EXPECT_THROW((void)api.get_on_chain_yields_locked_product_position(params),
                 common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedRedemptionRecord) {
    const std::string example =
        R"json({"rows":[{"positionId":"123123","redeemId":40607,"time":1575018510000,"asset":"BTC","lockPeriod":"30","amount":"21312.23223","originalAmount":"21312.23223","type":"NORMAL","deliverDate":"1575018510000","lossAmount":"0.00001232","isComplete":true,"rewardAsset":"SOLV","rewardAmt":"5.17181528","status":"PAID"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedRedemptionRecordParams params{};
    const auto res = api.get_on_chain_yields_locked_redemption_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/history/redemptionRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedRedemptionRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"positionId":"123123","redeemId":40607,"time":1575018510000,"asset":"BTC","lockPeriod":"30","amount":"21312.23223","originalAmount":"21312.23223","type":"NORMAL","deliverDate":"1575018510000","lossAmount":"0.00001232","isComplete":true,"rewardAsset":"SOLV","rewardAmt":"5.17181528","status":"PAID"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedRedemptionRecordParams params{
        .position_id = "1",
        .redeem_id = "1",
        .asset = "BTC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_on_chain_yields_locked_redemption_record(params);
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

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedRedemptionRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedRedemptionRecordParams params{};
    EXPECT_THROW((void)api.get_on_chain_yields_locked_redemption_record(params),
                 common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedRewardsHistory) {
    const std::string example =
        R"json({"rows":[{"positionId":"123123","time":1575018510000,"asset":"BNB","lockPeriod":"30","amount":"21312.23223"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedRewardsHistoryParams params{};
    const auto res = api.get_on_chain_yields_locked_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/history/rewardsRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedRewardsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"positionId":"123123","time":1575018510000,"asset":"BNB","lockPeriod":"30","amount":"21312.23223"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedRewardsHistoryParams params{
        .position_id = "1",
        .asset = "BTC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_on_chain_yields_locked_rewards_history(params);
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

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedRewardsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedRewardsHistoryParams params{};
    EXPECT_THROW((void)api.get_on_chain_yields_locked_rewards_history(params),
                 common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedSubscriptionPreview) {
    const std::string example =
        R"json({"rewardAsset":"SOLV","totalRewardAmt":"5.17181528","nextPay":"1.29295383","nextPayDate":"1646697600000","rewardsPayDate":"1646697600000","valueDate":"1646697600000","rewardsEndDate":"1651449600000","deliverDate":"1651536000000","nextSubscriptionDate":"1651536000000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedSubscriptionPreviewParams params{.project_id = "1",
                                                                 .amount = common::Decimal("1.0")};
    const auto res = api.get_on_chain_yields_locked_subscription_preview(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/subscriptionPreview");
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedSubscriptionPreviewWithOptionalParams) {
    const std::string example =
        R"json({"rewardAsset":"SOLV","totalRewardAmt":"5.17181528","nextPay":"1.29295383","nextPayDate":"1646697600000","rewardsPayDate":"1646697600000","valueDate":"1646697600000","rewardsEndDate":"1651449600000","deliverDate":"1651536000000","nextSubscriptionDate":"1651536000000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedSubscriptionPreviewParams params{
        .project_id = "1",
        .amount = common::Decimal("1.0"),
        .auto_subscribe = true,
        .recv_window = 5000,
    };
    const auto res = api.get_on_chain_yields_locked_subscription_preview(params);
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

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedSubscriptionPreviewBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedSubscriptionPreviewParams params{.project_id = "1",
                                                                 .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.get_on_chain_yields_locked_subscription_preview(params),
                 common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedSubscriptionRecord) {
    const std::string example =
        R"json({"rows":[{"positionId":"123123","purchaseId":"26055","projectId":"Solv-60d","clientId":"ABC","time":1575018510000,"asset":"BTC","amount":"21312.23223","lockPeriod":"30","type":"AUTO","sourceAccount":"SPOT","amtFromSpot":"30","amtFromFunding":"70","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedSubscriptionRecordParams params{};
    const auto res = api.get_on_chain_yields_locked_subscription_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/history/subscriptionRecord");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedSubscriptionRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"positionId":"123123","purchaseId":"26055","projectId":"Solv-60d","clientId":"ABC","time":1575018510000,"asset":"BTC","amount":"21312.23223","lockPeriod":"30","type":"AUTO","sourceAccount":"SPOT","amtFromSpot":"30","amtFromFunding":"70","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedSubscriptionRecordParams params{
        .purchase_id = "1",
        .client_id = "1",
        .asset = "BTC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_on_chain_yields_locked_subscription_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("purchaseId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, GetOnChainYieldsLockedSubscriptionRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOnChainYieldsLockedSubscriptionRecordParams params{};
    EXPECT_THROW((void)api.get_on_chain_yields_locked_subscription_record(params),
                 common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, OnChainYieldsAccount) {
    const std::string example =
        R"json({"totalAmountInBTC":"0.01067982","totalAmountInUSDT":"77.13289230","totalFlexibleAmountInBTC":"0.00000000","totalFlexibleAmountInUSDT":"0.00000000","totalLockedInBTC":"0.01067982","totalLockedInUSDT":"77.13289230"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OnChainYieldsAccountParams params{};
    const auto res = api.on_chain_yields_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, OnChainYieldsAccountWithOptionalParams) {
    const std::string example =
        R"json({"totalAmountInBTC":"0.01067982","totalAmountInUSDT":"77.13289230","totalFlexibleAmountInBTC":"0.00000000","totalFlexibleAmountInUSDT":"0.00000000","totalLockedInBTC":"0.01067982","totalLockedInUSDT":"77.13289230"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OnChainYieldsAccountParams params{
        .recv_window = 5000,
    };
    const auto res = api.on_chain_yields_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, OnChainYieldsAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OnChainYieldsAccountParams params{};
    EXPECT_THROW((void)api.on_chain_yields_account(params), common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, RedeemOnChainYieldsLockedProduct) {
    const std::string example = R"json({"redeemId":40607,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemOnChainYieldsLockedProductParams params{.position_id = "1"};
    const auto res = api.redeem_on_chain_yields_locked_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/redeem");
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, RedeemOnChainYieldsLockedProductWithOptionalParams) {
    const std::string example = R"json({"redeemId":40607,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemOnChainYieldsLockedProductParams params{
        .position_id = "1",
        .channel_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.redeem_on_chain_yields_locked_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("channelId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, RedeemOnChainYieldsLockedProductBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RedeemOnChainYieldsLockedProductParams params{.position_id = "1"};
    EXPECT_THROW((void)api.redeem_on_chain_yields_locked_product(params), common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, SetOnChainYieldsLockedAutoSubscribe) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetOnChainYieldsLockedAutoSubscribeParams params{.position_id = "1",
                                                           .auto_subscribe = true};
    const auto res = api.set_on_chain_yields_locked_auto_subscribe(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/setAutoSubscribe");
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoSubscribe="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, SetOnChainYieldsLockedAutoSubscribeWithOptionalParams) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetOnChainYieldsLockedAutoSubscribeParams params{
        .position_id = "1",
        .auto_subscribe = true,
        .recv_window = 5000,
    };
    const auto res = api.set_on_chain_yields_locked_auto_subscribe(params);
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

TEST(RestApiOnChainYieldsApi, SetOnChainYieldsLockedAutoSubscribeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SetOnChainYieldsLockedAutoSubscribeParams params{.position_id = "1",
                                                           .auto_subscribe = true};
    EXPECT_THROW((void)api.set_on_chain_yields_locked_auto_subscribe(params),
                 common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, SetOnChainYieldsLockedProductRedeemOption) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetOnChainYieldsLockedProductRedeemOptionParams params{
        .position_id = "1",
        .redeem_to = SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Spot};
    const auto res = api.set_on_chain_yields_locked_product_redeem_option(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/setRedeemOption");
    EXPECT_NE((rec.query() + "&" + rec.body).find("positionId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("redeemTo="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, SetOnChainYieldsLockedProductRedeemOptionWithOptionalParams) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetOnChainYieldsLockedProductRedeemOptionParams params{
        .position_id = "1",
        .redeem_to = SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Spot,
        .recv_window = 5000,
    };
    const auto res = api.set_on_chain_yields_locked_product_redeem_option(params);
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

TEST(RestApiOnChainYieldsApi, SetOnChainYieldsLockedProductRedeemOptionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SetOnChainYieldsLockedProductRedeemOptionParams params{
        .position_id = "1",
        .redeem_to = SetOnChainYieldsLockedProductRedeemOptionRedeemToEnum::Spot};
    EXPECT_THROW((void)api.set_on_chain_yields_locked_product_redeem_option(params),
                 common::BadRequestError);
}

TEST(RestApiOnChainYieldsApi, SubscribeOnChainYieldsLockedProduct) {
    const std::string example =
        R"json({"purchaseId":40607,"positionId":"12345","amount":"75.46000000","success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeOnChainYieldsLockedProductParams params{.project_id = "1",
                                                           .amount = common::Decimal("1.0")};
    const auto res = api.subscribe_on_chain_yields_locked_product(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/onchain-yields/locked/subscribe");
    EXPECT_NE((rec.query() + "&" + rec.body).find("projectId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, SubscribeOnChainYieldsLockedProductWithOptionalParams) {
    const std::string example =
        R"json({"purchaseId":40607,"positionId":"12345","amount":"75.46000000","success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeOnChainYieldsLockedProductParams params{
        .project_id = "1",
        .amount = common::Decimal("1.0"),
        .auto_subscribe = false,
        .source_account = SubscribeOnChainYieldsLockedProductSourceAccountEnum::Spot,
        .redeem_to = SubscribeOnChainYieldsLockedProductRedeemToEnum::Spot,
        .channel_id = "1",
        .client_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.subscribe_on_chain_yields_locked_product(params);
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
    EXPECT_NE((rec.query() + "&" + rec.body).find("channelId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOnChainYieldsApi, SubscribeOnChainYieldsLockedProductBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubscribeOnChainYieldsLockedProductParams params{.project_id = "1",
                                                           .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.subscribe_on_chain_yields_locked_product(params),
                 common::BadRequestError);
}
