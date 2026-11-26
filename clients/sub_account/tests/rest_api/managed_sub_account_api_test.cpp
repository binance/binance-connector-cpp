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
#include <binance/sub_account/rest_api/managed_sub_account_api.hpp>

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

ManagedSubAccountApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return ManagedSubAccountApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiManagedSubAccountApi, DepositAssetsIntoTheManagedSubAccount) {
    const std::string example = R"json({"tranId":66157362489})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositAssetsIntoTheManagedSubAccountParams params{
        .to_email = "abc@test.com", .asset = "BTC", .amount = common::Decimal("1.0")};
    const auto res = api.deposit_assets_into_the_managed_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/deposit");
    EXPECT_NE((rec.query() + "&" + rec.body).find("toEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, DepositAssetsIntoTheManagedSubAccountWithOptionalParams) {
    const std::string example = R"json({"tranId":66157362489})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositAssetsIntoTheManagedSubAccountParams params{
        .to_email = "abc@test.com",
        .asset = "BTC",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.deposit_assets_into_the_managed_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, DepositAssetsIntoTheManagedSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DepositAssetsIntoTheManagedSubAccountParams params{
        .to_email = "abc@test.com", .asset = "BTC", .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.deposit_assets_into_the_managed_sub_account(params),
                 common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, GetManagedSubAccountDepositAddress) {
    const std::string example =
        R"json({"coin":"USDT","address":"0x206c22d833bb0bb2102da6b7c7d4c3eb14bcf73d","tag":"","url":"https://etherscan.io/address/0x206c22d833bb0bb2102da6b7c7d4c3eb14bcf73d"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetManagedSubAccountDepositAddressParams params{.email = "abc@test.com", .coin = "USDT"};
    const auto res = api.get_managed_sub_account_deposit_address(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/deposit/address");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, GetManagedSubAccountDepositAddressWithOptionalParams) {
    const std::string example =
        R"json({"coin":"USDT","address":"0x206c22d833bb0bb2102da6b7c7d4c3eb14bcf73d","tag":"","url":"https://etherscan.io/address/0x206c22d833bb0bb2102da6b7c7d4c3eb14bcf73d"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetManagedSubAccountDepositAddressParams params{
        .email = "abc@test.com",
        .coin = "USDT",
        .network = "LIGHTNING",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.get_managed_sub_account_deposit_address(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, GetManagedSubAccountDepositAddressBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetManagedSubAccountDepositAddressParams params{.email = "abc@test.com", .coin = "USDT"};
    EXPECT_THROW((void)api.get_managed_sub_account_deposit_address(params),
                 common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountAssetDetails) {
    const std::string example =
        R"json([{"coin":"INJ","name":"Injective Protocol","totalBalance":"0","availableBalance":"0","inOrder":"0","btcValue":"0"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountAssetDetailsParams params{.email = "abc@test.com"};
    const auto res = api.query_managed_sub_account_asset_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/asset");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountAssetDetailsWithOptionalParams) {
    const std::string example =
        R"json([{"coin":"INJ","name":"Injective Protocol","totalBalance":"0","availableBalance":"0","inOrder":"0","btcValue":"0"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountAssetDetailsParams params{
        .email = "abc@test.com",
        .recv_window = 5000,
    };
    const auto res = api.query_managed_sub_account_asset_details(params);
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

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountAssetDetailsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryManagedSubAccountAssetDetailsParams params{.email = "abc@test.com"};
    EXPECT_THROW((void)api.query_managed_sub_account_asset_details(params),
                 common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountFuturesAssetDetails) {
    const std::string example =
        R"json({"code":"200","message":"OK","snapshotVos":[{"type":"FUTURES","updateTime":1672893855394,"data":{"assets":[{"asset":"USDT","marginBalance":100,"walletBalance":120}],"position":[{"symbol":"BTCUSDT","entryPrice":17000,"markPrice":17000,"positionAmt":1.0E-4}]}}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountFuturesAssetDetailsParams params{.email = "abc@test.com"};
    const auto res = api.query_managed_sub_account_futures_asset_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/fetch-future-asset");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountFuturesAssetDetailsWithOptionalParams) {
    const std::string example =
        R"json({"code":"200","message":"OK","snapshotVos":[{"type":"FUTURES","updateTime":1672893855394,"data":{"assets":[{"asset":"USDT","marginBalance":100,"walletBalance":120}],"position":[{"symbol":"BTCUSDT","entryPrice":17000,"markPrice":17000,"positionAmt":1.0E-4}]}}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountFuturesAssetDetailsParams params{
        .email = "abc@test.com",
        .account_type = "MARGIN",
    };
    const auto res = api.query_managed_sub_account_futures_asset_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountFuturesAssetDetailsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryManagedSubAccountFuturesAssetDetailsParams params{.email = "abc@test.com"};
    EXPECT_THROW((void)api.query_managed_sub_account_futures_asset_details(params),
                 common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountList) {
    const std::string example =
        R"json({"total":3,"managerSubUserInfoVoList":[{"rootUserId":1000138475670,"managersubUserId":1000137842513,"bindParentUserId":1000138475669,"email":"test_0_virtual@kq3kno9imanagedsub.com","insertTimeStamp":1678435149000,"bindParentEmail":"wdyw8xsh8pey@test.com","isSubUserEnabled":true,"isUserActive":true,"isMarginEnabled":false,"isFutureEnabled":false,"isSignedLVTRiskAgreement":false}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountListParams params{};
    const auto res = api.query_managed_sub_account_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/info");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountListWithOptionalParams) {
    const std::string example =
        R"json({"total":3,"managerSubUserInfoVoList":[{"rootUserId":1000138475670,"managersubUserId":1000137842513,"bindParentUserId":1000138475669,"email":"test_0_virtual@kq3kno9imanagedsub.com","insertTimeStamp":1678435149000,"bindParentEmail":"wdyw8xsh8pey@test.com","isSubUserEnabled":true,"isUserActive":true,"isMarginEnabled":false,"isFutureEnabled":false,"isSignedLVTRiskAgreement":false}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountListParams params{
        .email = "abc@test.com",
        .page = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_managed_sub_account_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryManagedSubAccountListParams params{};
    EXPECT_THROW((void)api.query_managed_sub_account_list(params), common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountMarginAssetDetails) {
    const std::string example =
        R"json({"marginLevel":"999","totalAssetOfBtc":"0","totalLiabilityOfBtc":"0","totalNetAssetOfBtc":"0","userAssets":[{"asset":"MATIC","borrowed":"0","free":"0","interest":"0","locked":"0","netAsset":"0"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountMarginAssetDetailsParams params{.email = "abc@test.com"};
    const auto res = api.query_managed_sub_account_margin_asset_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/marginAsset");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountMarginAssetDetailsWithOptionalParams) {
    const std::string example =
        R"json({"marginLevel":"999","totalAssetOfBtc":"0","totalLiabilityOfBtc":"0","totalNetAssetOfBtc":"0","userAssets":[{"asset":"MATIC","borrowed":"0","free":"0","interest":"0","locked":"0","netAsset":"0"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountMarginAssetDetailsParams params{
        .email = "abc@test.com",
        .account_type = "MARGIN",
    };
    const auto res = api.query_managed_sub_account_margin_asset_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountMarginAssetDetailsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryManagedSubAccountMarginAssetDetailsParams params{.email = "abc@test.com"};
    EXPECT_THROW((void)api.query_managed_sub_account_margin_asset_details(params),
                 common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountSnapshot) {
    const std::string example =
        R"json({"code":200,"msg":"","snapshotVos":[{"data":{"balances":[{"asset":"BTC","free":"0.09905021","locked":"0.00000000"}],"totalAssetOfBtc":"0.09942700","marginLevel":"2748.02909813","totalLiabilityOfBtc":"0.00000100","totalNetAssetOfBtc":"0.00274750","userAssets":[{"asset":"XRP","borrowed":"0.00000000","free":"1.00000000","interest":"0.00000000","locked":"0.00000000","netAsset":"1.00000000"}],"assets":[{"asset":"USDT","marginBalance":"118.99782335","walletBalance":"120.23811389"}],"position":[{"entryPrice":"7130.41000000","markPrice":"7257.66239673","positionAmt":"0.01000000","symbol":"BTCUSDT","unRealizedProfit":"1.24029054"}]},"type":"spot","updateTime":1576281599000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountSnapshotParams params{
        .email = "abc@test.com", .type = QueryManagedSubAccountSnapshotTypeEnum::Spot};
    const auto res = api.query_managed_sub_account_snapshot(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/accountSnapshot");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountSnapshotWithOptionalParams) {
    const std::string example =
        R"json({"code":200,"msg":"","snapshotVos":[{"data":{"balances":[{"asset":"BTC","free":"0.09905021","locked":"0.00000000"}],"totalAssetOfBtc":"0.09942700","marginLevel":"2748.02909813","totalLiabilityOfBtc":"0.00000100","totalNetAssetOfBtc":"0.00274750","userAssets":[{"asset":"XRP","borrowed":"0.00000000","free":"1.00000000","interest":"0.00000000","locked":"0.00000000","netAsset":"1.00000000"}],"assets":[{"asset":"USDT","marginBalance":"118.99782335","walletBalance":"120.23811389"}],"position":[{"entryPrice":"7130.41000000","markPrice":"7257.66239673","positionAmt":"0.01000000","symbol":"BTCUSDT","unRealizedProfit":"1.24029054"}]},"type":"spot","updateTime":1576281599000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountSnapshotParams params{
        .email = "abc@test.com",
        .type = QueryManagedSubAccountSnapshotTypeEnum::Spot,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_managed_sub_account_snapshot(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountSnapshotBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryManagedSubAccountSnapshotParams params{
        .email = "abc@test.com", .type = QueryManagedSubAccountSnapshotTypeEnum::Spot};
    EXPECT_THROW((void)api.query_managed_sub_account_snapshot(params), common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountTransferLogMasterAccountInvestor) {
    const std::string example =
        R"json({"managerSubTransferHistoryVos":[{"fromEmail":"test_0_virtual@kq3kno9imanagedsub.com","fromAccountType":"SPOT","toEmail":"wdywl0lddakh@test.com","toAccountType":"SPOT","asset":"BNB","amount":"0.01","scheduledData":1679416673000,"createTime":1679416673000,"status":"SUCCESS","tranId":91077779}],"count":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountTransferLogMasterAccountInvestorParams params{
        .email = "abc@test.com",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 1};
    const auto res = api.query_managed_sub_account_transfer_log_master_account_investor(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/queryTransLogForInvestor");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi,
     QueryManagedSubAccountTransferLogMasterAccountInvestorWithOptionalParams) {
    const std::string example =
        R"json({"managerSubTransferHistoryVos":[{"fromEmail":"test_0_virtual@kq3kno9imanagedsub.com","fromAccountType":"SPOT","toEmail":"wdywl0lddakh@test.com","toAccountType":"SPOT","asset":"BNB","amount":"0.01","scheduledData":1679416673000,"createTime":1679416673000,"status":"SUCCESS","tranId":91077779}],"count":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountTransferLogMasterAccountInvestorParams params{
        .email = "abc@test.com",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 1,
        .transfers = "transfers_example",
        .transfer_function_account_type =
            QueryManagedSubAccountTransferLogMasterAccountInvestorTransferFunctionAccountTypeEnum::
                Spot,
    };
    const auto res = api.query_managed_sub_account_transfer_log_master_account_investor(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transfers="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferFunctionAccountType="),
              std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi,
     QueryManagedSubAccountTransferLogMasterAccountInvestorBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryManagedSubAccountTransferLogMasterAccountInvestorParams params{
        .email = "abc@test.com",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 1};
    EXPECT_THROW((void)api.query_managed_sub_account_transfer_log_master_account_investor(params),
                 common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountTransferLogMasterAccountTrading) {
    const std::string example =
        R"json({"managerSubTransferHistoryVos":[{"fromEmail":"test_0_virtual@kq3kno9imanagedsub.com","fromAccountType":"SPOT","toEmail":"wdywl0lddakh@test.com","toAccountType":"SPOT","asset":"BNB","amount":"0.01","scheduledData":1679416673000,"createTime":1679416673000,"status":"SUCCESS","tranId":91077779}],"count":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountTransferLogMasterAccountTradingParams params{
        .email = "abc@test.com",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 10};
    const auto res = api.query_managed_sub_account_transfer_log_master_account_trading(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/queryTransLogForTradeParent");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi,
     QueryManagedSubAccountTransferLogMasterAccountTradingWithOptionalParams) {
    const std::string example =
        R"json({"managerSubTransferHistoryVos":[{"fromEmail":"test_0_virtual@kq3kno9imanagedsub.com","fromAccountType":"SPOT","toEmail":"wdywl0lddakh@test.com","toAccountType":"SPOT","asset":"BNB","amount":"0.01","scheduledData":1679416673000,"createTime":1679416673000,"status":"SUCCESS","tranId":91077779}],"count":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountTransferLogMasterAccountTradingParams params{
        .email = "abc@test.com",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 10,
        .transfers = "transfers_example",
        .transfer_function_account_type =
            QueryManagedSubAccountTransferLogMasterAccountTradingTransferFunctionAccountTypeEnum::
                Spot,
    };
    const auto res = api.query_managed_sub_account_transfer_log_master_account_trading(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transfers="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferFunctionAccountType="),
              std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountTransferLogMasterAccountTradingBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryManagedSubAccountTransferLogMasterAccountTradingParams params{
        .email = "abc@test.com",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 10};
    EXPECT_THROW((void)api.query_managed_sub_account_transfer_log_master_account_trading(params),
                 common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountTransferLogSubAccountTrading) {
    const std::string example =
        R"json({"managerSubTransferHistoryVos":[{"fromEmail":"test_0_virtual@kq3kno9imanagedsub.com","fromAccountType":"SPOT","toEmail":"wdywl0lddakh@test.com","toAccountType":"SPOT","asset":"BNB","amount":"0.01","scheduledData":1679416673000,"createTime":1679416673000,"status":"SUCCESS","tranId":91077779}],"count":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountTransferLogSubAccountTradingParams params{
        .start_time = 1623319461670, .end_time = 1641782889000, .page = 1, .limit = 10};
    const auto res = api.query_managed_sub_account_transfer_log_sub_account_trading(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/query-trans-log");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi,
     QueryManagedSubAccountTransferLogSubAccountTradingWithOptionalParams) {
    const std::string example =
        R"json({"managerSubTransferHistoryVos":[{"fromEmail":"test_0_virtual@kq3kno9imanagedsub.com","fromAccountType":"SPOT","toEmail":"wdywl0lddakh@test.com","toAccountType":"SPOT","asset":"BNB","amount":"0.01","scheduledData":1679416673000,"createTime":1679416673000,"status":"SUCCESS","tranId":91077779}],"count":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryManagedSubAccountTransferLogSubAccountTradingParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 10,
        .transfers = "transfers_example",
        .transfer_function_account_type =
            QueryManagedSubAccountTransferLogSubAccountTradingTransferFunctionAccountTypeEnum::Spot,
        .recv_window = 5000,
    };
    const auto res = api.query_managed_sub_account_transfer_log_sub_account_trading(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transfers="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferFunctionAccountType="),
              std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, QueryManagedSubAccountTransferLogSubAccountTradingBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryManagedSubAccountTransferLogSubAccountTradingParams params{
        .start_time = 1623319461670, .end_time = 1641782889000, .page = 1, .limit = 10};
    EXPECT_THROW((void)api.query_managed_sub_account_transfer_log_sub_account_trading(params),
                 common::BadRequestError);
}

TEST(RestApiManagedSubAccountApi, WithdrawlAssetsFromTheManagedSubAccount) {
    const std::string example = R"json({"tranId":66157362489})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawlAssetsFromTheManagedSubAccountParams params{
        .from_email = "from@test.com", .asset = "BTC", .amount = common::Decimal("1.0")};
    const auto res = api.withdrawl_assets_from_the_managed_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/managed-subaccount/withdraw");
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, WithdrawlAssetsFromTheManagedSubAccountWithOptionalParams) {
    const std::string example = R"json({"tranId":66157362489})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawlAssetsFromTheManagedSubAccountParams params{
        .from_email = "from@test.com",
        .asset = "BTC",
        .amount = common::Decimal("1.0"),
        .transfer_date = 789,
        .recv_window = 5000,
    };
    const auto res = api.withdrawl_assets_from_the_managed_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiManagedSubAccountApi, WithdrawlAssetsFromTheManagedSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const WithdrawlAssetsFromTheManagedSubAccountParams params{
        .from_email = "from@test.com", .asset = "BTC", .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.withdrawl_assets_from_the_managed_sub_account(params),
                 common::BadRequestError);
}
