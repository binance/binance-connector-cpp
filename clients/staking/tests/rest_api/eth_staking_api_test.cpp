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
#include <binance/staking/rest_api/eth_staking_api.hpp>

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

EthStakingApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return EthStakingApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiEthStakingApi, EthStakingAccount) {
    const std::string example =
        R"json({"holdingInETH":"1.22330928","holdings":{"wbethAmount":"1.10928781","bethAmount":"1.90002112"},"thirtyDaysProfitInETH":"0.22330928","profit":{"amountFromWBETH":"0.12330928","amountFromBETH":"0.1"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EthStakingAccountParams params{};
    const auto res = api.eth_staking_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/eth-staking/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, EthStakingAccountWithOptionalParams) {
    const std::string example =
        R"json({"holdingInETH":"1.22330928","holdings":{"wbethAmount":"1.10928781","bethAmount":"1.90002112"},"thirtyDaysProfitInETH":"0.22330928","profit":{"amountFromWBETH":"0.12330928","amountFromBETH":"0.1"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EthStakingAccountParams params{
        .recv_window = 5000,
    };
    const auto res = api.eth_staking_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, EthStakingAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EthStakingAccountParams params{};
    EXPECT_THROW((void)api.eth_staking_account(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, GetCurrentEthStakingQuota) {
    const std::string example =
        R"json({"leftStakingPersonalQuota":"1000","leftRedemptionPersonalQuota":"1000","minStakeAmount":"0.00010000","minRedeemAmount":"0.00000001","redeemPeriod":20,"stakeable":true,"redeemable":true,"commissionFee":"0.05000000","calculating":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCurrentEthStakingQuotaParams params{};
    const auto res = api.get_current_eth_staking_quota(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/eth-staking/eth/quota");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, GetCurrentEthStakingQuotaWithOptionalParams) {
    const std::string example =
        R"json({"leftStakingPersonalQuota":"1000","leftRedemptionPersonalQuota":"1000","minStakeAmount":"0.00010000","minRedeemAmount":"0.00000001","redeemPeriod":20,"stakeable":true,"redeemable":true,"commissionFee":"0.05000000","calculating":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCurrentEthStakingQuotaParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_current_eth_staking_quota(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, GetCurrentEthStakingQuotaBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCurrentEthStakingQuotaParams params{};
    EXPECT_THROW((void)api.get_current_eth_staking_quota(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, GetEthRedemptionHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"arrivalTime":1575018510000,"asset":"WBETH","amount":"21312.23223","distributeAsset":"ETH","distributeAmount":"21338.0699","conversionRatio":"1.00121234","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetEthRedemptionHistoryParams params{};
    const auto res = api.get_eth_redemption_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/eth-staking/eth/history/redemptionHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, GetEthRedemptionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"arrivalTime":1575018510000,"asset":"WBETH","amount":"21312.23223","distributeAsset":"ETH","distributeAmount":"21338.0699","conversionRatio":"1.00121234","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetEthRedemptionHistoryParams params{
        .redeem_id = 1234567,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_eth_redemption_history(params);
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

TEST(RestApiEthStakingApi, GetEthRedemptionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetEthRedemptionHistoryParams params{};
    EXPECT_THROW((void)api.get_eth_redemption_history(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, GetEthStakingHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"ETH","amount":"21312.23223","distributeAsset":"WBETH","distributeAmount":"21286.42584","conversionRatio":"1.00121234","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetEthStakingHistoryParams params{};
    const auto res = api.get_eth_staking_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/eth-staking/eth/history/stakingHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, GetEthStakingHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"asset":"ETH","amount":"21312.23223","distributeAsset":"WBETH","distributeAmount":"21286.42584","conversionRatio":"1.00121234","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetEthStakingHistoryParams params{
        .purchase_id = 1234567,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_eth_staking_history(params);
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

TEST(RestApiEthStakingApi, GetEthStakingHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetEthStakingHistoryParams params{};
    EXPECT_THROW((void)api.get_eth_staking_history(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, GetWbethRateHistory) {
    const std::string example =
        R"json({"rows":[{"annualPercentageRate":"0.00006408","exchangeRate":"1.00121234","time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetWbethRateHistoryParams params{};
    const auto res = api.get_wbeth_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/eth-staking/eth/history/rateHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, GetWbethRateHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"annualPercentageRate":"0.00006408","exchangeRate":"1.00121234","time":1577233578000}],"total":"1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetWbethRateHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_wbeth_rate_history(params);
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

TEST(RestApiEthStakingApi, GetWbethRateHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetWbethRateHistoryParams params{};
    EXPECT_THROW((void)api.get_wbeth_rate_history(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, GetWbethRewardsHistory) {
    const std::string example =
        R"json({"estRewardsInETH":"1.23230920","rows":[{"time":1575018510000,"amountInETH":"0.23223","holding":"2.3223","holdingInETH":"2.4231","annualPercentageRate":"0.5"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetWbethRewardsHistoryParams params{};
    const auto res = api.get_wbeth_rewards_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/eth-staking/eth/history/wbethRewardsHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, GetWbethRewardsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"estRewardsInETH":"1.23230920","rows":[{"time":1575018510000,"amountInETH":"0.23223","holding":"2.3223","holdingInETH":"2.4231","annualPercentageRate":"0.5"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetWbethRewardsHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_wbeth_rewards_history(params);
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

TEST(RestApiEthStakingApi, GetWbethRewardsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetWbethRewardsHistoryParams params{};
    EXPECT_THROW((void)api.get_wbeth_rewards_history(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, GetWbethUnwrapHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"fromAsset":"WBETH","fromAmount":"21312.23223","toAsset":"BETH","toAmount":"21312.23223","exchangeRate":"1.01243253","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetWbethUnwrapHistoryParams params{};
    const auto res = api.get_wbeth_unwrap_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/eth-staking/wbeth/history/unwrapHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, GetWbethUnwrapHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"fromAsset":"WBETH","fromAmount":"21312.23223","toAsset":"BETH","toAmount":"21312.23223","exchangeRate":"1.01243253","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetWbethUnwrapHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_wbeth_unwrap_history(params);
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

TEST(RestApiEthStakingApi, GetWbethUnwrapHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetWbethUnwrapHistoryParams params{};
    EXPECT_THROW((void)api.get_wbeth_unwrap_history(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, GetWbethWrapHistory) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"fromAsset":"BETH","fromAmount":"21312.23223","toAsset":"WBETH","toAmount":"21312.23223","exchangeRate":"1.01243253","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetWbethWrapHistoryParams params{};
    const auto res = api.get_wbeth_wrap_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/eth-staking/wbeth/history/wrapHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, GetWbethWrapHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"time":1575018510000,"fromAsset":"BETH","fromAmount":"21312.23223","toAsset":"WBETH","toAmount":"21312.23223","exchangeRate":"1.01243253","status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetWbethWrapHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_wbeth_wrap_history(params);
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

TEST(RestApiEthStakingApi, GetWbethWrapHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetWbethWrapHistoryParams params{};
    EXPECT_THROW((void)api.get_wbeth_wrap_history(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, RedeemEth) {
    const std::string example =
        R"json({"success":true,"ethAmount":"0.23092091","redeemId":1234567,"conversionRatio":"1.00121234","arrivalTime":1575018510000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemEthParams params{.amount = common::Decimal("1.0")};
    const auto res = api.redeem_eth(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/eth-staking/eth/redeem");
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, RedeemEthWithOptionalParams) {
    const std::string example =
        R"json({"success":true,"ethAmount":"0.23092091","redeemId":1234567,"conversionRatio":"1.00121234","arrivalTime":1575018510000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RedeemEthParams params{
        .amount = common::Decimal("1.0"),
        .asset = RedeemEthAssetEnum::Wbeth,
        .recv_window = 5000,
    };
    const auto res = api.redeem_eth(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, RedeemEthBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RedeemEthParams params{.amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.redeem_eth(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, SubscribeEthStaking) {
    const std::string example =
        R"json({"success":true,"wbethAmount":"0.23092091","purchaseId":1234567,"conversionRatio":"1.001212342342"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeEthStakingParams params{.amount = common::Decimal("1.0")};
    const auto res = api.subscribe_eth_staking(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v2/eth-staking/eth/stake");
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, SubscribeEthStakingWithOptionalParams) {
    const std::string example =
        R"json({"success":true,"wbethAmount":"0.23092091","purchaseId":1234567,"conversionRatio":"1.001212342342"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeEthStakingParams params{
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.subscribe_eth_staking(params);
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

TEST(RestApiEthStakingApi, SubscribeEthStakingBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubscribeEthStakingParams params{.amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.subscribe_eth_staking(params), common::BadRequestError);
}

TEST(RestApiEthStakingApi, WrapBeth) {
    const std::string example =
        R"json({"success":true,"wbethAmount":"0.23092091","exchangeRate":"1.001212343432"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WrapBethParams params{.amount = common::Decimal("1.0")};
    const auto res = api.wrap_beth(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/eth-staking/wbeth/wrap");
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiEthStakingApi, WrapBethWithOptionalParams) {
    const std::string example =
        R"json({"success":true,"wbethAmount":"0.23092091","exchangeRate":"1.001212343432"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WrapBethParams params{
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.wrap_beth(params);
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

TEST(RestApiEthStakingApi, WrapBethBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const WrapBethParams params{.amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.wrap_beth(params), common::BadRequestError);
}
