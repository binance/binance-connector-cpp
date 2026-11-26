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
#include <binance/simple_earn/rest_api/bfusd_api.hpp>

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

BfusdApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return BfusdApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiBfusdApi, GetBfusdAccount) {
    const std::string example =
        R"json({"bfusdAmount":"100","usdtProfit":"11.00","bfusdProfit":"1.81"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdAccountParams params{};
    const auto res = api.get_bfusd_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/bfusd/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdAccountWithOptionalParams) {
    const std::string example =
        R"json({"bfusdAmount":"100","usdtProfit":"11.00","bfusdProfit":"1.81"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdAccountParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_bfusd_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBfusdAccountParams params{};
    EXPECT_THROW((void)api.get_bfusd_account(params), common::BadRequestError);
}

TEST(RestApiBfusdApi, GetBfusdQuotaDetails) {
    const std::string example =
        R"json({"subscriptionQuota":{"leftQuota":"1000"},"fastRedemptionQuota":{"leftQuota":"2","minimum":"0.1","fee":"0.001","freeQuota":"100"},"standardRedemptionQuota":{"leftQuota":"2","minimum":"0.1","fee":"0.0005","redeemPeriod":3}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdQuotaDetailsParams params{};
    const auto res = api.get_bfusd_quota_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/bfusd/quota");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdQuotaDetailsWithOptionalParams) {
    const std::string example =
        R"json({"subscriptionQuota":{"leftQuota":"1000"},"fastRedemptionQuota":{"leftQuota":"2","minimum":"0.1","fee":"0.001","freeQuota":"100"},"standardRedemptionQuota":{"leftQuota":"2","minimum":"0.1","fee":"0.0005","redeemPeriod":3}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdQuotaDetailsParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_bfusd_quota_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdQuotaDetailsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBfusdQuotaDetailsParams params{};
    EXPECT_THROW((void)api.get_bfusd_quota_details(params), common::BadRequestError);
}

TEST(RestApiBfusdApi, GetBfusdRateHistory) {
    const std::string example =
        R"json({"rows":[{"annualPercentageRate":"0.0418","time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdRateHistoryParams params{};
    const auto res = api.get_bfusd_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/bfusd/history/rateHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdRateHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"annualPercentageRate":"0.0418","time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdRateHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_bfusd_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdRateHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBfusdRateHistoryParams params{};
    EXPECT_THROW((void)api.get_bfusd_rate_history(params), common::BadRequestError);
}

TEST(RestApiBfusdApi, GetBfusdRedemptionHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"BFUSD","amount":"51","receiveAsset":"USDT","receiveAmount":"50","fee":"1","arrivalTime":1575018510000,"status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdRedemptionHistoryParams params{};
    const auto res = api.get_bfusd_redemption_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/bfusd/history/redemptionHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdRedemptionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"BFUSD","amount":"51","receiveAsset":"USDT","receiveAmount":"50","fee":"1","arrivalTime":1575018510000,"status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdRedemptionHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_bfusd_redemption_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdRedemptionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBfusdRedemptionHistoryParams params{};
    EXPECT_THROW((void)api.get_bfusd_redemption_history(params), common::BadRequestError);
}

TEST(RestApiBfusdApi, GetBfusdRewardsHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"rewardAsset":"BFUSD","rewardsAmount":"1","BFUSDPosition":"100","annualPercentageRate":"0.0418"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdRewardsHistoryParams params{};
    const auto res = api.get_bfusd_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/bfusd/history/rewardsHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdRewardsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"rewardAsset":"BFUSD","rewardsAmount":"1","BFUSDPosition":"100","annualPercentageRate":"0.0418"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdRewardsHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_bfusd_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdRewardsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBfusdRewardsHistoryParams params{};
    EXPECT_THROW((void)api.get_bfusd_rewards_history(params), common::BadRequestError);
}

TEST(RestApiBfusdApi, GetBfusdSubscriptionHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"USDT","amount":"100","receiveAsset":"BFUSD","receiveAmount":"100","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdSubscriptionHistoryParams params{};
    const auto res = api.get_bfusd_subscription_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/bfusd/history/subscriptionHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, GetBfusdSubscriptionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"USDT","amount":"100","receiveAsset":"BFUSD","receiveAmount":"100","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBfusdSubscriptionHistoryParams params{
        .asset = GetBfusdSubscriptionHistoryAssetEnum::Usdc,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_bfusd_subscription_history(params);
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

TEST(RestApiBfusdApi, GetBfusdSubscriptionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBfusdSubscriptionHistoryParams params{};
    EXPECT_THROW((void)api.get_bfusd_subscription_history(params), common::BadRequestError);
}

TEST(RestApiBfusdApi, RedeemBfusd) {
    const std::string example =
        R"json({"success":true,"receiveAmount":"0.23092091","fee":"0.00000012","arrivalTime":1575018510000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemBfusdParams params{.amount = common::Decimal("1.0"),
                                   .type = RedeemBfusdTypeEnum::Fast};
    const auto res = api.redeem_bfusd(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/bfusd/redeem");
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, RedeemBfusdWithOptionalParams) {
    const std::string example =
        R"json({"success":true,"receiveAmount":"0.23092091","fee":"0.00000012","arrivalTime":1575018510000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemBfusdParams params{
        .amount = common::Decimal("1.0"),
        .type = RedeemBfusdTypeEnum::Fast,
        .recv_window = 5000,
    };
    const auto res = api.redeem_bfusd(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, RedeemBfusdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RedeemBfusdParams params{.amount = common::Decimal("1.0"),
                                   .type = RedeemBfusdTypeEnum::Fast};
    EXPECT_THROW((void)api.redeem_bfusd(params), common::BadRequestError);
}

TEST(RestApiBfusdApi, SubscribeBfusd) {
    const std::string example = R"json({"success":true,"bfusdAmount":"0.22091092"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeBfusdParams params{.asset = "USDT", .amount = common::Decimal("1.0")};
    const auto res = api.subscribe_bfusd(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/bfusd/subscribe");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, SubscribeBfusdWithOptionalParams) {
    const std::string example = R"json({"success":true,"bfusdAmount":"0.22091092"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeBfusdParams params{
        .asset = "USDT",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.subscribe_bfusd(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBfusdApi, SubscribeBfusdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubscribeBfusdParams params{.asset = "USDT", .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.subscribe_bfusd(params), common::BadRequestError);
}
