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
#include <binance/staking/rest_api/sol_staking_api.hpp>

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

SolStakingApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return SolStakingApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiSolStakingApi, ClaimBoostRewards) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ClaimBoostRewardsParams params{};
    const auto res = api.claim_boost_rewards(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/claim");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, ClaimBoostRewardsWithOptionalParams) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ClaimBoostRewardsParams params{
        .recv_window = 5000,
    };
    const auto res = api.claim_boost_rewards(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, ClaimBoostRewardsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ClaimBoostRewardsParams params{};
    EXPECT_THROW((void)api.claim_boost_rewards(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, GetBnsolRateHistory) {
    const std::string example =
        R"json({"rows":[{"annualPercentageRate":"0.00006408","exchangeRate":"1.001212343432","boostRewards":[{"boostAPR":"0.12000000","rewardsAsset":"SOL"}],"time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBnsolRateHistoryParams params{};
    const auto res = api.get_bnsol_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/history/rateHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetBnsolRateHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"annualPercentageRate":"0.00006408","exchangeRate":"1.001212343432","boostRewards":[{"boostAPR":"0.12000000","rewardsAsset":"SOL"}],"time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBnsolRateHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_bnsol_rate_history(params);
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

TEST(RestApiSolStakingApi, GetBnsolRateHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBnsolRateHistoryParams params{};
    EXPECT_THROW((void)api.get_bnsol_rate_history(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, GetBnsolRewardsHistory) {
    const std::string example =
        R"json({"estRewardsInSOL":"1.23230920","rows":[{"time":1575018510000,"amountInSOL":"0.23223","holding":"2.3223","holdingInSOL":"2.4231","annualPercentageRate":"0.5"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBnsolRewardsHistoryParams params{};
    const auto res = api.get_bnsol_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/history/bnsolRewardsHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetBnsolRewardsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"estRewardsInSOL":"1.23230920","rows":[{"time":1575018510000,"amountInSOL":"0.23223","holding":"2.3223","holdingInSOL":"2.4231","annualPercentageRate":"0.5"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBnsolRewardsHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_bnsol_rewards_history(params);
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

TEST(RestApiSolStakingApi, GetBnsolRewardsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBnsolRewardsHistoryParams params{};
    EXPECT_THROW((void)api.get_bnsol_rewards_history(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, GetBoostRewardsHistory) {
    const std::string example =
        R"json({"rows":[{"time":1729520680,"token":"SOL","amount":"1.20291028","bnsolHolding":"2.0928798","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBoostRewardsHistoryParams params{.type = GetBoostRewardsHistoryTypeEnum::Claim};
    const auto res = api.get_boost_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/history/boostRewardsHistory");
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetBoostRewardsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1729520680,"token":"SOL","amount":"1.20291028","bnsolHolding":"2.0928798","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBoostRewardsHistoryParams params{
        .type = GetBoostRewardsHistoryTypeEnum::Claim,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_boost_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetBoostRewardsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBoostRewardsHistoryParams params{.type = GetBoostRewardsHistoryTypeEnum::Claim};
    EXPECT_THROW((void)api.get_boost_rewards_history(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, GetSolRedemptionHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"arrivalTime":1575018510000,"asset":"BNSOL","amount":"21312.23223","distributeAsset":"SOL","distributeAmount":"21338.0699","exchangeRate":"1.00121234","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSolRedemptionHistoryParams params{};
    const auto res = api.get_sol_redemption_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/history/redemptionHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetSolRedemptionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"arrivalTime":1575018510000,"asset":"BNSOL","amount":"21312.23223","distributeAsset":"SOL","distributeAmount":"21338.0699","exchangeRate":"1.00121234","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSolRedemptionHistoryParams params{
        .redeem_id = 1234567,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_sol_redemption_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("redeemId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetSolRedemptionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSolRedemptionHistoryParams params{};
    EXPECT_THROW((void)api.get_sol_redemption_history(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, GetSolStakingHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"SOL","amount":"21312.23223","distributeAsset":"BNSOL","distributeAmount":"21286.42584","exchangeRate":"1.00121234","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSolStakingHistoryParams params{};
    const auto res = api.get_sol_staking_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/history/stakingHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetSolStakingHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"SOL","amount":"21312.23223","distributeAsset":"BNSOL","distributeAmount":"21286.42584","exchangeRate":"1.00121234","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSolStakingHistoryParams params{
        .purchase_id = 1234567,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_sol_staking_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("purchaseId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetSolStakingHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSolStakingHistoryParams params{};
    EXPECT_THROW((void)api.get_sol_staking_history(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, GetSolStakingQuotaDetails) {
    const std::string example =
        R"json({"leftStakingPersonalQuota":"1000","leftRedemptionPersonalQuota":"1000","minStakeAmount":"0.01000000","minRedeemAmount":"0.00000001","redeemPeriod":4,"stakeable":true,"redeemable":true,"soldOut":false,"commissionFee":"0.25000000","nextEpochTime":725993969475,"calculating":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSolStakingQuotaDetailsParams params{};
    const auto res = api.get_sol_staking_quota_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/quota");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetSolStakingQuotaDetailsWithOptionalParams) {
    const std::string example =
        R"json({"leftStakingPersonalQuota":"1000","leftRedemptionPersonalQuota":"1000","minStakeAmount":"0.01000000","minRedeemAmount":"0.00000001","redeemPeriod":4,"stakeable":true,"redeemable":true,"soldOut":false,"commissionFee":"0.25000000","nextEpochTime":725993969475,"calculating":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSolStakingQuotaDetailsParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_sol_staking_quota_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetSolStakingQuotaDetailsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSolStakingQuotaDetailsParams params{};
    EXPECT_THROW((void)api.get_sol_staking_quota_details(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, GetUnclaimedRewards) {
    const std::string example = R"json([{"amount":"1.00000011","rewardsAsset":"SOL"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUnclaimedRewardsParams params{};
    const auto res = api.get_unclaimed_rewards(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/history/unclaimedRewards");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetUnclaimedRewardsWithOptionalParams) {
    const std::string example = R"json([{"amount":"1.00000011","rewardsAsset":"SOL"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUnclaimedRewardsParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_unclaimed_rewards(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, GetUnclaimedRewardsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUnclaimedRewardsParams params{};
    EXPECT_THROW((void)api.get_unclaimed_rewards(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, RedeemSol) {
    const std::string example =
        R"json({"success":true,"solAmount":"0.23092091","redeemId":1234567,"exchangeRate":"1.00121234","arrivalTime":1575018510000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemSolParams params{.amount = common::Decimal("1.0")};
    const auto res = api.redeem_sol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/redeem");
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, RedeemSolWithOptionalParams) {
    const std::string example =
        R"json({"success":true,"solAmount":"0.23092091","redeemId":1234567,"exchangeRate":"1.00121234","arrivalTime":1575018510000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemSolParams params{
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.redeem_sol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, RedeemSolBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RedeemSolParams params{.amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.redeem_sol(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, SolStakingAccount) {
    const std::string example =
        R"json({"bnsolAmount":"1.10928781","holdingInSOL":"1.22330928","thirtyDaysProfitInSOL":"0.22330928"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SolStakingAccountParams params{};
    const auto res = api.sol_staking_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, SolStakingAccountWithOptionalParams) {
    const std::string example =
        R"json({"bnsolAmount":"1.10928781","holdingInSOL":"1.22330928","thirtyDaysProfitInSOL":"0.22330928"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SolStakingAccountParams params{
        .recv_window = 5000,
    };
    const auto res = api.sol_staking_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, SolStakingAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SolStakingAccountParams params{};
    EXPECT_THROW((void)api.sol_staking_account(params), common::BadRequestError);
}

TEST(RestApiSolStakingApi, SubscribeSolStaking) {
    const std::string example =
        R"json({"success":true,"bnsolAmount":"0.23092091","purchaseId":1234567,"exchangeRate":"1.001212342342"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeSolStakingParams params{.amount = common::Decimal("1.0")};
    const auto res = api.subscribe_sol_staking(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sol-staking/sol/stake");
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, SubscribeSolStakingWithOptionalParams) {
    const std::string example =
        R"json({"success":true,"bnsolAmount":"0.23092091","purchaseId":1234567,"exchangeRate":"1.001212342342"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeSolStakingParams params{
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.subscribe_sol_staking(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiSolStakingApi, SubscribeSolStakingBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubscribeSolStakingParams params{.amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.subscribe_sol_staking(params), common::BadRequestError);
}
