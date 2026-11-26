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
#include <binance/simple_earn/rest_api/rwusd_api.hpp>

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

RwusdApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return RwusdApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiRwusdApi, GetRwusdAccount) {
    const std::string example = R"json({"rwusdAmount":"100","totalProfit":"12.81"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdAccountParams params{};
    const auto res = api.get_rwusd_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/rwusd/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, GetRwusdAccountWithOptionalParams) {
    const std::string example = R"json({"rwusdAmount":"100","totalProfit":"12.81"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdAccountParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_rwusd_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, GetRwusdAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetRwusdAccountParams params{};
    EXPECT_THROW((void)api.get_rwusd_account(params), common::BadRequestError);
}

TEST(RestApiRwusdApi, GetRwusdQuotaDetails) {
    const std::string example =
        R"json({"subscriptionQuota":{"assets":["USDT"],"leftQuota":"1000","minimum":"0.10000000"},"fastRedemptionQuota":{"leftQuota":"2","minimum":"0.1","fee":"0.0005","freeQuota":"100"},"standardRedemptionQuota":{"leftQuota":"2","minimum":"0.1","fee":"0.001","redeemPeriod":3},"subscribeEnable":true,"redeemEnable":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdQuotaDetailsParams params{};
    const auto res = api.get_rwusd_quota_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/rwusd/quota");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, GetRwusdQuotaDetailsWithOptionalParams) {
    const std::string example =
        R"json({"subscriptionQuota":{"assets":["USDT"],"leftQuota":"1000","minimum":"0.10000000"},"fastRedemptionQuota":{"leftQuota":"2","minimum":"0.1","fee":"0.0005","freeQuota":"100"},"standardRedemptionQuota":{"leftQuota":"2","minimum":"0.1","fee":"0.001","redeemPeriod":3},"subscribeEnable":true,"redeemEnable":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdQuotaDetailsParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_rwusd_quota_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, GetRwusdQuotaDetailsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetRwusdQuotaDetailsParams params{};
    EXPECT_THROW((void)api.get_rwusd_quota_details(params), common::BadRequestError);
}

TEST(RestApiRwusdApi, GetRwusdRateHistory) {
    const std::string example =
        R"json({"rows":[{"annualPercentageRate":"0.0418","time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdRateHistoryParams params{};
    const auto res = api.get_rwusd_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/rwusd/history/rateHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, GetRwusdRateHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"annualPercentageRate":"0.0418","time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdRateHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_rwusd_rate_history(params);
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

TEST(RestApiRwusdApi, GetRwusdRateHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetRwusdRateHistoryParams params{};
    EXPECT_THROW((void)api.get_rwusd_rate_history(params), common::BadRequestError);
}

TEST(RestApiRwusdApi, GetRwusdRedemptionHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"RWUSD","amount":"51","receiveAsset":"USDC","receiveAmount":"50","fee":"1","arrivalTime":1575018510000,"status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdRedemptionHistoryParams params{};
    const auto res = api.get_rwusd_redemption_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/rwusd/history/redemptionHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, GetRwusdRedemptionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"RWUSD","amount":"51","receiveAsset":"USDC","receiveAmount":"50","fee":"1","arrivalTime":1575018510000,"status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdRedemptionHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_rwusd_redemption_history(params);
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

TEST(RestApiRwusdApi, GetRwusdRedemptionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetRwusdRedemptionHistoryParams params{};
    EXPECT_THROW((void)api.get_rwusd_redemption_history(params), common::BadRequestError);
}

TEST(RestApiRwusdApi, GetRwusdRewardsHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"rewardsAmount":"1","rwusdPosition":"100","annualPercentageRate":"0.0418"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdRewardsHistoryParams params{};
    const auto res = api.get_rwusd_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/rwusd/history/rewardsHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, GetRwusdRewardsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"rewardsAmount":"1","rwusdPosition":"100","annualPercentageRate":"0.0418"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdRewardsHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_rwusd_rewards_history(params);
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

TEST(RestApiRwusdApi, GetRwusdRewardsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetRwusdRewardsHistoryParams params{};
    EXPECT_THROW((void)api.get_rwusd_rewards_history(params), common::BadRequestError);
}

TEST(RestApiRwusdApi, GetRwusdSubscriptionHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"USDC","amount":"100","receiveAsset":"RWUSD","receiveAmount":"100","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdSubscriptionHistoryParams params{};
    const auto res = api.get_rwusd_subscription_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/rwusd/history/subscriptionHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, GetRwusdSubscriptionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"USDC","amount":"100","receiveAsset":"RWUSD","receiveAmount":"100","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRwusdSubscriptionHistoryParams params{
        .asset = GetRwusdSubscriptionHistoryAssetEnum::Usdc,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_rwusd_subscription_history(params);
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

TEST(RestApiRwusdApi, GetRwusdSubscriptionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetRwusdSubscriptionHistoryParams params{};
    EXPECT_THROW((void)api.get_rwusd_subscription_history(params), common::BadRequestError);
}

TEST(RestApiRwusdApi, RedeemRwusd) {
    const std::string example =
        R"json({"success":true,"receiveAmount":"0.23092091","fee":"0.00000012","arrivalTime":1575018510000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemRwusdParams params{.amount = common::Decimal("1.0"),
                                   .type = RedeemRwusdTypeEnum::Fast};
    const auto res = api.redeem_rwusd(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/rwusd/redeem");
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, RedeemRwusdWithOptionalParams) {
    const std::string example =
        R"json({"success":true,"receiveAmount":"0.23092091","fee":"0.00000012","arrivalTime":1575018510000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemRwusdParams params{
        .amount = common::Decimal("1.0"),
        .type = RedeemRwusdTypeEnum::Fast,
        .recv_window = 5000,
    };
    const auto res = api.redeem_rwusd(params);
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

TEST(RestApiRwusdApi, RedeemRwusdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RedeemRwusdParams params{.amount = common::Decimal("1.0"),
                                   .type = RedeemRwusdTypeEnum::Fast};
    EXPECT_THROW((void)api.redeem_rwusd(params), common::BadRequestError);
}

TEST(RestApiRwusdApi, SubscribeRwusd) {
    const std::string example = R"json({"success":true,"rwusdAmount":"0.22091092"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeRwusdParams params{.asset = SubscribeRwusdAssetEnum::Usdt,
                                      .amount = common::Decimal("1.0")};
    const auto res = api.subscribe_rwusd(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/rwusd/subscribe");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiRwusdApi, SubscribeRwusdWithOptionalParams) {
    const std::string example = R"json({"success":true,"rwusdAmount":"0.22091092"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeRwusdParams params{
        .asset = SubscribeRwusdAssetEnum::Usdt,
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.subscribe_rwusd(params);
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

TEST(RestApiRwusdApi, SubscribeRwusdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubscribeRwusdParams params{.asset = SubscribeRwusdAssetEnum::Usdt,
                                      .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.subscribe_rwusd(params), common::BadRequestError);
}
