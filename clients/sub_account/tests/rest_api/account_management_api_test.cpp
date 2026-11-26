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
#include <binance/sub_account/rest_api/account_management_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::sub_account::rest_api;
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

AccountManagementApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return AccountManagementApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiAccountManagementApi, CreateAVirtualSubAccount) {
    const std::string example = R"json({"email":"addsdd_virtual@aasaixwqnoemail.com"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateAVirtualSubAccountParams params{.sub_account_string = "testSubAccount"};
    const auto res = api.create_a_virtual_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/virtualSubAccount");
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountString="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, CreateAVirtualSubAccountWithOptionalParams) {
    const std::string example = R"json({"email":"addsdd_virtual@aasaixwqnoemail.com"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateAVirtualSubAccountParams params{
        .sub_account_string = "testSubAccount",
        .recv_window = 5000,
    };
    const auto res = api.create_a_virtual_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountString="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, CreateAVirtualSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateAVirtualSubAccountParams params{.sub_account_string = "testSubAccount"};
    EXPECT_THROW((void)api.create_a_virtual_sub_account(params), common::BadRequestError);
}

TEST(RestApiAccountManagementApi, EnableFuturesForSubAccount) {
    const std::string example = R"json({"email":"123@test.com","isFuturesEnabled":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EnableFuturesForSubAccountParams params{.email = "123@test.com"};
    const auto res = api.enable_futures_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/futures/enable");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, EnableFuturesForSubAccountWithOptionalParams) {
    const std::string example = R"json({"email":"123@test.com","isFuturesEnabled":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EnableFuturesForSubAccountParams params{
        .email = "123@test.com",
        .recv_window = 5000,
    };
    const auto res = api.enable_futures_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, EnableFuturesForSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EnableFuturesForSubAccountParams params{.email = "123@test.com"};
    EXPECT_THROW((void)api.enable_futures_for_sub_account(params), common::BadRequestError);
}

TEST(RestApiAccountManagementApi, EnableOptionsForSubAccount) {
    const std::string example = R"json({"email":"123@test.com","isEOptionsEnabled":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EnableOptionsForSubAccountParams params{.email = "123@test.com"};
    const auto res = api.enable_options_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/eoptions/enable");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, EnableOptionsForSubAccountWithOptionalParams) {
    const std::string example = R"json({"email":"123@test.com","isEOptionsEnabled":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EnableOptionsForSubAccountParams params{
        .email = "123@test.com",
        .recv_window = 5000,
    };
    const auto res = api.enable_options_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, EnableOptionsForSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EnableOptionsForSubAccountParams params{.email = "123@test.com"};
    EXPECT_THROW((void)api.enable_options_for_sub_account(params), common::BadRequestError);
}

TEST(RestApiAccountManagementApi, GetFuturesPositionRiskOfSubAccount) {
    const std::string example =
        R"json([{"entryPrice":"9975.12000","leverage":"50","maxNotional":"1000000","liquidationPrice":"7963.54","markPrice":"9973.50770517","positionAmount":"0.010","symbol":"BTCUSDT","unrealizedProfit":"-0.01612295"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesPositionRiskOfSubAccountParams params{.email = "123@test.com"};
    const auto res = api.get_futures_position_risk_of_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/futures/positionRisk");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, GetFuturesPositionRiskOfSubAccountWithOptionalParams) {
    const std::string example =
        R"json([{"entryPrice":"9975.12000","leverage":"50","maxNotional":"1000000","liquidationPrice":"7963.54","markPrice":"9973.50770517","positionAmount":"0.010","symbol":"BTCUSDT","unrealizedProfit":"-0.01612295"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesPositionRiskOfSubAccountParams params{
        .email = "123@test.com",
        .recv_window = 5000,
    };
    const auto res = api.get_futures_position_risk_of_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, GetFuturesPositionRiskOfSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesPositionRiskOfSubAccountParams params{.email = "123@test.com"};
    EXPECT_THROW((void)api.get_futures_position_risk_of_sub_account(params),
                 common::BadRequestError);
}

TEST(RestApiAccountManagementApi, GetFuturesPositionRiskOfSubAccountV2) {
    const std::string example =
        R"json({"futurePositionRiskVos":[{"entryPrice":"9975.12000","leverage":"50","maxNotional":"1000000","liquidationPrice":"7963.54","markPrice":"9973.50770517","positionAmount":"0.010","symbol":"BTCUSDT","unrealizedProfit":"-0.01612295"}],"deliveryPositionRiskVos":[{"entryPrice":"9975.12000","markPrice":"9973.50770517","leverage":"20","isolated":"false","isolatedWallet":"9973.50770517","isolatedMargin":"0.00000000","isAutoAddMargin":"false","positionSide":"BOTH","positionAmount":"1.230","symbol":"BTCUSD_201225","unrealizedProfit":"-0.01612295"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesPositionRiskOfSubAccountV2Params params{.email = "123@test.com",
                                                            .futures_type = 1};
    const auto res = api.get_futures_position_risk_of_sub_account_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/sub-account/futures/positionRisk");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("futuresType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, GetFuturesPositionRiskOfSubAccountV2WithOptionalParams) {
    const std::string example =
        R"json({"futurePositionRiskVos":[{"entryPrice":"9975.12000","leverage":"50","maxNotional":"1000000","liquidationPrice":"7963.54","markPrice":"9973.50770517","positionAmount":"0.010","symbol":"BTCUSDT","unrealizedProfit":"-0.01612295"}],"deliveryPositionRiskVos":[{"entryPrice":"9975.12000","markPrice":"9973.50770517","leverage":"20","isolated":"false","isolatedWallet":"9973.50770517","isolatedMargin":"0.00000000","isAutoAddMargin":"false","positionSide":"BOTH","positionAmount":"1.230","symbol":"BTCUSD_201225","unrealizedProfit":"-0.01612295"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesPositionRiskOfSubAccountV2Params params{
        .email = "123@test.com",
        .futures_type = 1,
        .recv_window = 5000,
    };
    const auto res = api.get_futures_position_risk_of_sub_account_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("futuresType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, GetFuturesPositionRiskOfSubAccountV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesPositionRiskOfSubAccountV2Params params{.email = "123@test.com",
                                                            .futures_type = 1};
    EXPECT_THROW((void)api.get_futures_position_risk_of_sub_account_v2(params),
                 common::BadRequestError);
}

TEST(RestApiAccountManagementApi, GetSubAccountsStatusOnMarginOrFutures) {
    const std::string example =
        R"json([{"email":"123@test.com","isSubUserEnabled":true,"isUserActive":true,"insertTime":1570791523523,"isMarginEnabled":true,"isFutureEnabled":true,"mobile":1570791523523}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSubAccountsStatusOnMarginOrFuturesParams params{};
    const auto res = api.get_sub_accounts_status_on_margin_or_futures(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/status");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, GetSubAccountsStatusOnMarginOrFuturesWithOptionalParams) {
    const std::string example =
        R"json([{"email":"123@test.com","isSubUserEnabled":true,"isUserActive":true,"insertTime":1570791523523,"isMarginEnabled":true,"isFutureEnabled":true,"mobile":1570791523523}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSubAccountsStatusOnMarginOrFuturesParams params{
        .email = "123@test.com",
        .recv_window = 5000,
    };
    const auto res = api.get_sub_accounts_status_on_margin_or_futures(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, GetSubAccountsStatusOnMarginOrFuturesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSubAccountsStatusOnMarginOrFuturesParams params{};
    EXPECT_THROW((void)api.get_sub_accounts_status_on_margin_or_futures(params),
                 common::BadRequestError);
}

TEST(RestApiAccountManagementApi, QuerySubAccountList) {
    const std::string example =
        R"json({"subAccounts":[{"subUserId":123456,"email":"testsub@gmail.com","remark":"remark","isFreeze":false,"createTime":1544433328000,"isManagedSubAccount":false,"isAssetManagementSubAccount":false}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountListParams params{};
    const auto res = api.query_sub_account_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, QuerySubAccountListWithOptionalParams) {
    const std::string example =
        R"json({"subAccounts":[{"subUserId":123456,"email":"testsub@gmail.com","remark":"remark","isFreeze":false,"createTime":1544433328000,"isManagedSubAccount":false,"isAssetManagementSubAccount":false}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountListParams params{
        .email = "123@test.com",
        .is_freeze = "true",
        .page = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_sub_account_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isFreeze="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, QuerySubAccountListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubAccountListParams params{};
    EXPECT_THROW((void)api.query_sub_account_list(params), common::BadRequestError);
}

TEST(RestApiAccountManagementApi, QuerySubAccountTransactionStatistics) {
    const std::string example =
        R"json({"recent30BtcTotal":"0","recent30BtcFuturesTotal":"0","recent30BtcMarginTotal":"0","recent30BusdTotal":"0","recent30BusdFuturesTotal":"0","recent30BusdMarginTotal":"0","tradeInfoVos":[{"userId":1000138138384,"btc":0,"btcFutures":0,"btcMargin":0,"busd":0,"busdFutures":0,"busdMargin":0,"date":1676851200000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountTransactionStatisticsParams params{};
    const auto res = api.query_sub_account_transaction_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/transaction-statistics");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, QuerySubAccountTransactionStatisticsWithOptionalParams) {
    const std::string example =
        R"json({"recent30BtcTotal":"0","recent30BtcFuturesTotal":"0","recent30BtcMarginTotal":"0","recent30BusdTotal":"0","recent30BusdFuturesTotal":"0","recent30BusdMarginTotal":"0","tradeInfoVos":[{"userId":1000138138384,"btc":0,"btcFutures":0,"btcMargin":0,"busd":0,"busdFutures":0,"busdMargin":0,"date":1676851200000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountTransactionStatisticsParams params{
        .email = "abc@test.com",
        .recv_window = 5000,
    };
    const auto res = api.query_sub_account_transaction_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountManagementApi, QuerySubAccountTransactionStatisticsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubAccountTransactionStatisticsParams params{};
    EXPECT_THROW((void)api.query_sub_account_transaction_statistics(params),
                 common::BadRequestError);
}
