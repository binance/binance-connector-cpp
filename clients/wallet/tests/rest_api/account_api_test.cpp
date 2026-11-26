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
#include <binance/wallet/rest_api/account_api.hpp>

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

AccountApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return AccountApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiAccountApi, AccountApiTradingStatus) {
    const std::string example =
        R"json({"data":{"isLocked":false,"plannedRecoverTime":0,"triggerCondition":{"GCR":150,"IFER":150,"UFR":300},"updateTime":1547630471725}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountApiTradingStatusParams params{};
    const auto res = api.account_api_trading_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/account/apiTradingStatus");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountApiTradingStatusWithOptionalParams) {
    const std::string example =
        R"json({"data":{"isLocked":false,"plannedRecoverTime":0,"triggerCondition":{"GCR":150,"IFER":150,"UFR":300},"updateTime":1547630471725}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountApiTradingStatusParams params{
        .recv_window = 5000,
    };
    const auto res = api.account_api_trading_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountApiTradingStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountApiTradingStatusParams params{};
    EXPECT_THROW((void)api.account_api_trading_status(params), common::BadRequestError);
}

TEST(RestApiAccountApi, AccountInfo) {
    const std::string example =
        R"json({"vipLevel":0,"isMarginEnabled":true,"isFutureEnabled":true,"isOptionsEnabled":true,"isPortfolioMarginRetailEnabled":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInfoParams params{};
    const auto res = api.account_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/account/info");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInfoWithOptionalParams) {
    const std::string example =
        R"json({"vipLevel":0,"isMarginEnabled":true,"isFutureEnabled":true,"isOptionsEnabled":true,"isPortfolioMarginRetailEnabled":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInfoParams params{
        .recv_window = 5000,
    };
    const auto res = api.account_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountInfoParams params{};
    EXPECT_THROW((void)api.account_info(params), common::BadRequestError);
}

TEST(RestApiAccountApi, AccountStatus) {
    const std::string example = R"json({"data":"Normal"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountStatusParams params{};
    const auto res = api.account_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/account/status");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountStatusWithOptionalParams) {
    const std::string example = R"json({"data":"Normal"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountStatusParams params{
        .recv_window = 5000,
    };
    const auto res = api.account_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountStatusParams params{};
    EXPECT_THROW((void)api.account_status(params), common::BadRequestError);
}

TEST(RestApiAccountApi, DailyAccountSnapshot) {
    const std::string example =
        R"json({"code":200,"msg":"","snapshotVos":[{"data":{"balances":[{"asset":"BTC","free":"0.09905021","locked":"0.00000000"}],"totalAssetOfBtc":"0.09942700","marginLevel":"2748.02909813","totalLiabilityOfBtc":"0.00000100","totalNetAssetOfBtc":"0.00274750","userAssets":[{"asset":"XRP","borrowed":"0.00000000","free":"1.00000000","interest":"0.00000000","locked":"0.00000000","netAsset":"1.00000000"}],"assets":[{"asset":"USDT","marginBalance":"118.99782335","walletBalance":"120.23811389"}],"position":[{"entryPrice":"7130.41000000","markPrice":"7257.66239673","positionAmt":"0.01000000","symbol":"BTCUSDT","unRealizedProfit":"1.24029054"}]},"type":"spot","updateTime":1576281599000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DailyAccountSnapshotParams params{.type = DailyAccountSnapshotTypeEnum::Spot};
    const auto res = api.daily_account_snapshot(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/accountSnapshot");
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, DailyAccountSnapshotWithOptionalParams) {
    const std::string example =
        R"json({"code":200,"msg":"","snapshotVos":[{"data":{"balances":[{"asset":"BTC","free":"0.09905021","locked":"0.00000000"}],"totalAssetOfBtc":"0.09942700","marginLevel":"2748.02909813","totalLiabilityOfBtc":"0.00000100","totalNetAssetOfBtc":"0.00274750","userAssets":[{"asset":"XRP","borrowed":"0.00000000","free":"1.00000000","interest":"0.00000000","locked":"0.00000000","netAsset":"1.00000000"}],"assets":[{"asset":"USDT","marginBalance":"118.99782335","walletBalance":"120.23811389"}],"position":[{"entryPrice":"7130.41000000","markPrice":"7257.66239673","positionAmt":"0.01000000","symbol":"BTCUSDT","unRealizedProfit":"1.24029054"}]},"type":"spot","updateTime":1576281599000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DailyAccountSnapshotParams params{
        .type = DailyAccountSnapshotTypeEnum::Spot,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 7,
        .recv_window = 5000,
    };
    const auto res = api.daily_account_snapshot(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, DailyAccountSnapshotBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DailyAccountSnapshotParams params{.type = DailyAccountSnapshotTypeEnum::Spot};
    EXPECT_THROW((void)api.daily_account_snapshot(params), common::BadRequestError);
}

TEST(RestApiAccountApi, DisableFastWithdrawSwitch) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DisableFastWithdrawSwitchParams params{};
    const auto res = api.disable_fast_withdraw_switch(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/account/disableFastWithdrawSwitch");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, DisableFastWithdrawSwitchWithOptionalParams) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DisableFastWithdrawSwitchParams params{
        .recv_window = 5000,
    };
    const auto res = api.disable_fast_withdraw_switch(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, DisableFastWithdrawSwitchBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DisableFastWithdrawSwitchParams params{};
    EXPECT_THROW((void)api.disable_fast_withdraw_switch(params), common::BadRequestError);
}

TEST(RestApiAccountApi, EnableFastWithdrawSwitch) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EnableFastWithdrawSwitchParams params{};
    const auto res = api.enable_fast_withdraw_switch(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/account/enableFastWithdrawSwitch");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, EnableFastWithdrawSwitchWithOptionalParams) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EnableFastWithdrawSwitchParams params{
        .recv_window = 5000,
    };
    const auto res = api.enable_fast_withdraw_switch(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, EnableFastWithdrawSwitchBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EnableFastWithdrawSwitchParams params{};
    EXPECT_THROW((void)api.enable_fast_withdraw_switch(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetApiKeyPermission) {
    const std::string example =
        R"json({"ipRestrict":false,"createTime":1623840271000,"enableReading":true,"enableWithdrawals":false,"enableInternalTransfer":true,"enableMargin":false,"enableFutures":false,"permitsUniversalTransfer":true,"enableVanillaOptions":false,"enableFixApiTrade":false,"enableFixReadOnly":true,"enableSpotAndMarginTrading":false,"enablePortfolioMarginTrading":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetApiKeyPermissionParams params{};
    const auto res = api.get_api_key_permission(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/account/apiRestrictions");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetApiKeyPermissionWithOptionalParams) {
    const std::string example =
        R"json({"ipRestrict":false,"createTime":1623840271000,"enableReading":true,"enableWithdrawals":false,"enableInternalTransfer":true,"enableMargin":false,"enableFutures":false,"permitsUniversalTransfer":true,"enableVanillaOptions":false,"enableFixApiTrade":false,"enableFixReadOnly":true,"enableSpotAndMarginTrading":false,"enablePortfolioMarginTrading":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetApiKeyPermissionParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_api_key_permission(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetApiKeyPermissionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetApiKeyPermissionParams params{};
    EXPECT_THROW((void)api.get_api_key_permission(params), common::BadRequestError);
}
