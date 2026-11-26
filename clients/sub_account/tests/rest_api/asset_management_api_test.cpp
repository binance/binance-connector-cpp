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
#include <binance/sub_account/rest_api/asset_management_api.hpp>

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

AssetManagementApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return AssetManagementApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiAssetManagementApi, FuturesTransferForSubAccount) {
    const std::string example = R"json({"txnId":"2966662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesTransferForSubAccountParams params{
        .email = "123@test.com", .asset = "USDT", .amount = common::Decimal("1.0"), .type = 1};
    const auto res = api.futures_transfer_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/futures/transfer");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, FuturesTransferForSubAccountWithOptionalParams) {
    const std::string example = R"json({"txnId":"2966662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesTransferForSubAccountParams params{
        .email = "123@test.com",
        .asset = "USDT",
        .amount = common::Decimal("1.0"),
        .type = 1,
        .recv_window = 5000,
    };
    const auto res = api.futures_transfer_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, FuturesTransferForSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FuturesTransferForSubAccountParams params{
        .email = "123@test.com", .asset = "USDT", .amount = common::Decimal("1.0"), .type = 1};
    EXPECT_THROW((void)api.futures_transfer_for_sub_account(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, GetDetailOnSubAccountsFuturesAccount) {
    const std::string example =
        R"json({"email":"abc@test.com","asset":"USDT","assets":[{"asset":"USDT","initialMargin":"0.00000000","maintenanceMargin":"0.00000000","marginBalance":"0.88308000","maxWithdrawAmount":"0.88308000","openOrderInitialMargin":"0.00000000","positionInitialMargin":"0.00000000","unrealizedProfit":"0.00000000","walletBalance":"0.88308000"}],"canDeposit":true,"canTrade":true,"canWithdraw":true,"feeTier":2,"maxWithdrawAmount":"0.88308000","totalInitialMargin":"0.00000000","totalMaintenanceMargin":"0.00000000","totalMarginBalance":"0.88308000","totalOpenOrderInitialMargin":"0.00000000","totalPositionInitialMargin":"0.00000000","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"0.88308000","updateTime":1576756674610})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDetailOnSubAccountsFuturesAccountParams params{.email = "123@test.com"};
    const auto res = api.get_detail_on_sub_accounts_futures_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/futures/account");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetDetailOnSubAccountsFuturesAccountWithOptionalParams) {
    const std::string example =
        R"json({"email":"abc@test.com","asset":"USDT","assets":[{"asset":"USDT","initialMargin":"0.00000000","maintenanceMargin":"0.00000000","marginBalance":"0.88308000","maxWithdrawAmount":"0.88308000","openOrderInitialMargin":"0.00000000","positionInitialMargin":"0.00000000","unrealizedProfit":"0.00000000","walletBalance":"0.88308000"}],"canDeposit":true,"canTrade":true,"canWithdraw":true,"feeTier":2,"maxWithdrawAmount":"0.88308000","totalInitialMargin":"0.00000000","totalMaintenanceMargin":"0.00000000","totalMarginBalance":"0.88308000","totalOpenOrderInitialMargin":"0.00000000","totalPositionInitialMargin":"0.00000000","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"0.88308000","updateTime":1576756674610})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDetailOnSubAccountsFuturesAccountParams params{
        .email = "123@test.com",
        .recv_window = 5000,
    };
    const auto res = api.get_detail_on_sub_accounts_futures_account(params);
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

TEST(RestApiAssetManagementApi, GetDetailOnSubAccountsFuturesAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDetailOnSubAccountsFuturesAccountParams params{.email = "123@test.com"};
    EXPECT_THROW((void)api.get_detail_on_sub_accounts_futures_account(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, GetDetailOnSubAccountsFuturesAccountV2) {
    const std::string example =
        R"json({"futureAccountResp":{"email":"abc@test.com","assets":[{"asset":"USDT","initialMargin":"0.00000000","maintenanceMargin":"0.00000000","marginBalance":"0.88308000","maxWithdrawAmount":"0.88308000","openOrderInitialMargin":"0.00000000","positionInitialMargin":"0.00000000","unrealizedProfit":"0.00000000","walletBalance":"0.88308000"}],"canDeposit":true,"canTrade":true,"canWithdraw":true,"feeTier":2,"maxWithdrawAmount":"0.88308000","totalInitialMargin":"0.00000000","totalMaintenanceMargin":"0.00000000","totalMarginBalance":"0.88308000","totalOpenOrderInitialMargin":"0.00000000","totalPositionInitialMargin":"0.00000000","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"0.88308000","updateTime":1576756674610},"deliveryAccountResp":{"email":"abc@test.com","assets":[{"asset":"BTC","initialMargin":"0.00000000","maintenanceMargin":"0.00000000","marginBalance":"0.88308000","maxWithdrawAmount":"0.88308000","openOrderInitialMargin":"0.00000000","positionInitialMargin":"0.00000000","unrealizedProfit":"0.00000000","walletBalance":"0.88308000"}],"canDeposit":true,"canTrade":true,"canWithdraw":true,"feeTier":2,"updateTime":1598959682001}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDetailOnSubAccountsFuturesAccountV2Params params{.email = "123@test.com",
                                                              .futures_type = 1};
    const auto res = api.get_detail_on_sub_accounts_futures_account_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/sub-account/futures/account");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("futuresType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetDetailOnSubAccountsFuturesAccountV2WithOptionalParams) {
    const std::string example =
        R"json({"futureAccountResp":{"email":"abc@test.com","assets":[{"asset":"USDT","initialMargin":"0.00000000","maintenanceMargin":"0.00000000","marginBalance":"0.88308000","maxWithdrawAmount":"0.88308000","openOrderInitialMargin":"0.00000000","positionInitialMargin":"0.00000000","unrealizedProfit":"0.00000000","walletBalance":"0.88308000"}],"canDeposit":true,"canTrade":true,"canWithdraw":true,"feeTier":2,"maxWithdrawAmount":"0.88308000","totalInitialMargin":"0.00000000","totalMaintenanceMargin":"0.00000000","totalMarginBalance":"0.88308000","totalOpenOrderInitialMargin":"0.00000000","totalPositionInitialMargin":"0.00000000","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"0.88308000","updateTime":1576756674610},"deliveryAccountResp":{"email":"abc@test.com","assets":[{"asset":"BTC","initialMargin":"0.00000000","maintenanceMargin":"0.00000000","marginBalance":"0.88308000","maxWithdrawAmount":"0.88308000","openOrderInitialMargin":"0.00000000","positionInitialMargin":"0.00000000","unrealizedProfit":"0.00000000","walletBalance":"0.88308000"}],"canDeposit":true,"canTrade":true,"canWithdraw":true,"feeTier":2,"updateTime":1598959682001}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDetailOnSubAccountsFuturesAccountV2Params params{
        .email = "123@test.com",
        .futures_type = 1,
        .recv_window = 5000,
    };
    const auto res = api.get_detail_on_sub_accounts_futures_account_v2(params);
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

TEST(RestApiAssetManagementApi, GetDetailOnSubAccountsFuturesAccountV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDetailOnSubAccountsFuturesAccountV2Params params{.email = "123@test.com",
                                                              .futures_type = 1};
    EXPECT_THROW((void)api.get_detail_on_sub_accounts_futures_account_v2(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, GetDetailOnSubAccountsMarginAccount) {
    const std::string example =
        R"json({"email":"123@test.com","marginLevel":"11.64405625","totalAssetOfBtc":"6.82728457","totalLiabilityOfBtc":"0.58633215","totalNetAssetOfBtc":"6.24095242","marginTradeCoeffVo":{"forceLiquidationBar":"1.10000000","marginCallBar":"1.50000000","normalBar":"2.00000000"},"marginUserAssetVoList":[{"asset":"BTC","borrowed":"0.00000000","free":"0.00499500","interest":"0.00000000","locked":"0.00000000","netAsset":"0.00499500"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDetailOnSubAccountsMarginAccountParams params{.email = "123@test.com"};
    const auto res = api.get_detail_on_sub_accounts_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/margin/account");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetDetailOnSubAccountsMarginAccountWithOptionalParams) {
    const std::string example =
        R"json({"email":"123@test.com","marginLevel":"11.64405625","totalAssetOfBtc":"6.82728457","totalLiabilityOfBtc":"0.58633215","totalNetAssetOfBtc":"6.24095242","marginTradeCoeffVo":{"forceLiquidationBar":"1.10000000","marginCallBar":"1.50000000","normalBar":"2.00000000"},"marginUserAssetVoList":[{"asset":"BTC","borrowed":"0.00000000","free":"0.00499500","interest":"0.00000000","locked":"0.00000000","netAsset":"0.00499500"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDetailOnSubAccountsMarginAccountParams params{
        .email = "123@test.com",
        .recv_window = 5000,
    };
    const auto res = api.get_detail_on_sub_accounts_margin_account(params);
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

TEST(RestApiAssetManagementApi, GetDetailOnSubAccountsMarginAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDetailOnSubAccountsMarginAccountParams params{.email = "123@test.com"};
    EXPECT_THROW((void)api.get_detail_on_sub_accounts_margin_account(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, GetMovePositionHistoryForSubAccount) {
    const std::string example =
        R"json({"total":3,"futureMovePositionOrderVoList":[{"fromUserEmail":"testFrom@google.com","toUserEmail":"testTo@google.com","productType":"UM","symbol":"BTCUSDT","price":"105025.50981609","quantity":"0.00100000","positionSide":"BOTH","side":"SELL","timeStamp":1737544712000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetMovePositionHistoryForSubAccountParams params{
        .symbol = "BTCUSDT", .page = 1, .rows = 1};
    const auto res = api.get_move_position_history_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/futures/move-position");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("rows="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetMovePositionHistoryForSubAccountWithOptionalParams) {
    const std::string example =
        R"json({"total":3,"futureMovePositionOrderVoList":[{"fromUserEmail":"testFrom@google.com","toUserEmail":"testTo@google.com","productType":"UM","symbol":"BTCUSDT","price":"105025.50981609","quantity":"0.00100000","positionSide":"BOTH","side":"SELL","timeStamp":1737544712000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetMovePositionHistoryForSubAccountParams params{
        .symbol = "BTCUSDT",
        .page = 1,
        .rows = 1,
        .product_type = GetMovePositionHistoryForSubAccountProductTypeEnum::Um,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_move_position_history_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("rows="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetMovePositionHistoryForSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetMovePositionHistoryForSubAccountParams params{
        .symbol = "BTCUSDT", .page = 1, .rows = 1};
    EXPECT_THROW((void)api.get_move_position_history_for_sub_account(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, MovePositionForSubAccount) {
    const std::string example =
        R"json({"movePositionOrders":[{"fromUserEmail":"testFrom@google.com","toUserEmail":"testTo@google.com","productType":"UM","symbol":"BTCUSDT","priceType":"MARK_PRICE","price":"97139.00000000","quantity":"0.001","positionSide":"BOTH","side":"BUY","success":true}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MovePositionForSubAccountParams params{
        .from_user_email = "testFrom@google.com",
        .to_user_email = "testTo@google.com",
        .product_type = MovePositionForSubAccountProductTypeEnum::Um,
        .order_args = std::vector<MovePositionForSubAccountOrderArgsParameterInner>{}};
    const auto res = api.move_position_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/futures/move-position");
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromUserEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toUserEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderArgs="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, MovePositionForSubAccountWithOptionalParams) {
    const std::string example =
        R"json({"movePositionOrders":[{"fromUserEmail":"testFrom@google.com","toUserEmail":"testTo@google.com","productType":"UM","symbol":"BTCUSDT","priceType":"MARK_PRICE","price":"97139.00000000","quantity":"0.001","positionSide":"BOTH","side":"BUY","success":true}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MovePositionForSubAccountParams params{
        .from_user_email = "testFrom@google.com",
        .to_user_email = "testTo@google.com",
        .product_type = MovePositionForSubAccountProductTypeEnum::Um,
        .order_args = std::vector<MovePositionForSubAccountOrderArgsParameterInner>{},
        .recv_window = 5000,
    };
    const auto res = api.move_position_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromUserEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toUserEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("productType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, MovePositionForSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MovePositionForSubAccountParams params{
        .from_user_email = "testFrom@google.com",
        .to_user_email = "testTo@google.com",
        .product_type = MovePositionForSubAccountProductTypeEnum::Um,
        .order_args = std::vector<MovePositionForSubAccountOrderArgsParameterInner>{}};
    EXPECT_THROW((void)api.move_position_for_sub_account(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, GetSubAccountDepositAddress) {
    const std::string example =
        R"json({"address":"TDunhSa7jkTNuKrusUTU1MUHtqXoBPKETV","coin":"USDT","tag":"","url":"https://tronscan.org/#/address/TDunhSa7jkTNuKrusUTU1MUHtqXoBPKETV"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSubAccountDepositAddressParams params{.email = "123@test.com", .coin = "BTC"};
    const auto res = api.get_sub_account_deposit_address(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/deposit/subAddress");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetSubAccountDepositAddressWithOptionalParams) {
    const std::string example =
        R"json({"address":"TDunhSa7jkTNuKrusUTU1MUHtqXoBPKETV","coin":"USDT","tag":"","url":"https://tronscan.org/#/address/TDunhSa7jkTNuKrusUTU1MUHtqXoBPKETV"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSubAccountDepositAddressParams params{
        .email = "123@test.com",
        .coin = "BTC",
        .network = "network_example",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.get_sub_account_deposit_address(params);
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

TEST(RestApiAssetManagementApi, GetSubAccountDepositAddressBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSubAccountDepositAddressParams params{.email = "123@test.com", .coin = "BTC"};
    EXPECT_THROW((void)api.get_sub_account_deposit_address(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, GetSubAccountDepositHistory) {
    const std::string example =
        R"json([{"id":"769800519366885376","amount":"0.001","coin":"BNB","network":"BNB","status":0,"address":"bnb136ns6lfw4zs5hg4n85vdthaad7hq5m4gtkgf23","addressTag":"101764890","txId":"98A3EA560C6B3336D348B6C83F0F95ECE4F1F5919E94BD006E5BF3BF264FACFC","insertTime":1661493146000,"transferType":0,"confirmTimes":"1/1","unlockConfirm":0,"walletType":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSubAccountDepositHistoryParams params{.email = "123@test.com"};
    const auto res = api.get_sub_account_deposit_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/deposit/subHisrec");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetSubAccountDepositHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"id":"769800519366885376","amount":"0.001","coin":"BNB","network":"BNB","status":0,"address":"bnb136ns6lfw4zs5hg4n85vdthaad7hq5m4gtkgf23","addressTag":"101764890","txId":"98A3EA560C6B3336D348B6C83F0F95ECE4F1F5919E94BD006E5BF3BF264FACFC","insertTime":1661493146000,"transferType":0,"confirmTimes":"1/1","unlockConfirm":0,"walletType":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSubAccountDepositHistoryParams params{
        .email = "123@test.com",
        .include_source = false,
        .coin = "BTC",
        .status = 0,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 1,
        .offset = 0,
        .recv_window = 5000,
        .tx_id = "1",
    };
    const auto res = api.get_sub_account_deposit_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("includeSource="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetSubAccountDepositHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSubAccountDepositHistoryParams params{.email = "123@test.com"};
    EXPECT_THROW((void)api.get_sub_account_deposit_history(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, GetSummaryOfSubAccountsFuturesAccount) {
    const std::string example =
        R"json({"totalInitialMargin":"9.83137400","totalMaintenanceMargin":"0.41568700","totalMarginBalance":"23.03235621","totalOpenOrderInitialMargin":"9.00000000","totalPositionInitialMargin":"0.83137400","totalUnrealizedProfit":"0.03219710","totalWalletBalance":"22.15879444","asset":"USD","subAccountList":[{"email":"123@test.com","totalInitialMargin":"9.00000000","totalMaintenanceMargin":"0.00000000","totalMarginBalance":"22.12659734","totalOpenOrderInitialMargin":"9.00000000","totalPositionInitialMargin":"0.00000000","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"22.12659734","asset":"USD"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSummaryOfSubAccountsFuturesAccountParams params{.page = 1, .limit = 1};
    const auto res = api.get_summary_of_sub_accounts_futures_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/futures/accountSummary");
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetSummaryOfSubAccountsFuturesAccountWithOptionalParams) {
    const std::string example =
        R"json({"totalInitialMargin":"9.83137400","totalMaintenanceMargin":"0.41568700","totalMarginBalance":"23.03235621","totalOpenOrderInitialMargin":"9.00000000","totalPositionInitialMargin":"0.83137400","totalUnrealizedProfit":"0.03219710","totalWalletBalance":"22.15879444","asset":"USD","subAccountList":[{"email":"123@test.com","totalInitialMargin":"9.00000000","totalMaintenanceMargin":"0.00000000","totalMarginBalance":"22.12659734","totalOpenOrderInitialMargin":"9.00000000","totalPositionInitialMargin":"0.00000000","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"22.12659734","asset":"USD"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSummaryOfSubAccountsFuturesAccountParams params{
        .page = 1,
        .limit = 1,
        .recv_window = 5000,
    };
    const auto res = api.get_summary_of_sub_accounts_futures_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetSummaryOfSubAccountsFuturesAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSummaryOfSubAccountsFuturesAccountParams params{.page = 1, .limit = 1};
    EXPECT_THROW((void)api.get_summary_of_sub_accounts_futures_account(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, GetSummaryOfSubAccountsFuturesAccountV2) {
    const std::string example =
        R"json({"futureAccountSummaryResp":{"totalInitialMargin":"9.83137400","totalMaintenanceMargin":"0.41568700","totalMarginBalance":"23.03235621","totalOpenOrderInitialMargin":"9.00000000","totalPositionInitialMargin":"0.83137400","totalUnrealizedProfit":"0.03219710","totalWalletBalance":"22.15879444","asset":"USD","subAccountList":[{"email":"123@test.com","totalInitialMargin":"9.00000000","totalMaintenanceMargin":"0.00000000","totalMarginBalance":"22.12659734","totalOpenOrderInitialMargin":"9.00000000","totalPositionInitialMargin":"0.00000000","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"22.12659734","asset":"USD"}]},"deliveryAccountSummaryResp":{"totalMarginBalanceOfBTC":"25.03221121","totalUnrealizedProfitOfBTC":"0.12233410","totalWalletBalanceOfBTC":"22.15879444","asset":"BTC","subAccountList":[{"email":"123@test.com","totalMarginBalance":"22.12659734","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"22.12659734","asset":"BTC"}]}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSummaryOfSubAccountsFuturesAccountV2Params params{.futures_type = 1};
    const auto res = api.get_summary_of_sub_accounts_futures_account_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/sub-account/futures/accountSummary");
    EXPECT_NE((rec.query() + "&" + rec.body).find("futuresType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetSummaryOfSubAccountsFuturesAccountV2WithOptionalParams) {
    const std::string example =
        R"json({"futureAccountSummaryResp":{"totalInitialMargin":"9.83137400","totalMaintenanceMargin":"0.41568700","totalMarginBalance":"23.03235621","totalOpenOrderInitialMargin":"9.00000000","totalPositionInitialMargin":"0.83137400","totalUnrealizedProfit":"0.03219710","totalWalletBalance":"22.15879444","asset":"USD","subAccountList":[{"email":"123@test.com","totalInitialMargin":"9.00000000","totalMaintenanceMargin":"0.00000000","totalMarginBalance":"22.12659734","totalOpenOrderInitialMargin":"9.00000000","totalPositionInitialMargin":"0.00000000","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"22.12659734","asset":"USD"}]},"deliveryAccountSummaryResp":{"totalMarginBalanceOfBTC":"25.03221121","totalUnrealizedProfitOfBTC":"0.12233410","totalWalletBalanceOfBTC":"22.15879444","asset":"BTC","subAccountList":[{"email":"123@test.com","totalMarginBalance":"22.12659734","totalUnrealizedProfit":"0.00000000","totalWalletBalance":"22.12659734","asset":"BTC"}]}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSummaryOfSubAccountsFuturesAccountV2Params params{
        .futures_type = 1,
        .page = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_summary_of_sub_accounts_futures_account_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("futuresType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetSummaryOfSubAccountsFuturesAccountV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSummaryOfSubAccountsFuturesAccountV2Params params{.futures_type = 1};
    EXPECT_THROW((void)api.get_summary_of_sub_accounts_futures_account_v2(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, GetSummaryOfSubAccountsMarginAccount) {
    const std::string example =
        R"json({"totalAssetOfBtc":"4.33333333","totalLiabilityOfBtc":"2.11111112","totalNetAssetOfBtc":"2.22222221","subAccountList":[{"email":"123@test.com","totalAssetOfBtc":"2.11111111","totalLiabilityOfBtc":"1.11111111","totalNetAssetOfBtc":"1.00000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSummaryOfSubAccountsMarginAccountParams params{};
    const auto res = api.get_summary_of_sub_accounts_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/margin/accountSummary");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetSummaryOfSubAccountsMarginAccountWithOptionalParams) {
    const std::string example =
        R"json({"totalAssetOfBtc":"4.33333333","totalLiabilityOfBtc":"2.11111112","totalNetAssetOfBtc":"2.22222221","subAccountList":[{"email":"123@test.com","totalAssetOfBtc":"2.11111111","totalLiabilityOfBtc":"1.11111111","totalNetAssetOfBtc":"1.00000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSummaryOfSubAccountsMarginAccountParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_summary_of_sub_accounts_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, GetSummaryOfSubAccountsMarginAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSummaryOfSubAccountsMarginAccountParams params{};
    EXPECT_THROW((void)api.get_summary_of_sub_accounts_margin_account(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, MarginTransferForSubAccount) {
    const std::string example = R"json({"txnId":"2966662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginTransferForSubAccountParams params{
        .email = "123@test.com", .asset = "BTC", .amount = common::Decimal("1.0"), .type = 1};
    const auto res = api.margin_transfer_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/margin/transfer");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, MarginTransferForSubAccountWithOptionalParams) {
    const std::string example = R"json({"txnId":"2966662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginTransferForSubAccountParams params{
        .email = "123@test.com",
        .asset = "BTC",
        .amount = common::Decimal("1.0"),
        .type = 1,
        .recv_window = 5000,
    };
    const auto res = api.margin_transfer_for_sub_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, MarginTransferForSubAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginTransferForSubAccountParams params{
        .email = "123@test.com", .asset = "BTC", .amount = common::Decimal("1.0"), .type = 1};
    EXPECT_THROW((void)api.margin_transfer_for_sub_account(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, QuerySubAccountAssets) {
    const std::string example =
        R"json({"balances":[{"freeze":0,"withdrawing":0,"asset":"ADA","free":11467.6399,"locked":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountAssetsParams params{.email = "123@test.com"};
    const auto res = api.query_sub_account_assets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v3/sub-account/assets");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QuerySubAccountAssetsWithOptionalParams) {
    const std::string example =
        R"json({"balances":[{"freeze":0,"withdrawing":0,"asset":"ADA","free":11467.6399,"locked":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountAssetsParams params{
        .email = "123@test.com",
        .recv_window = 5000,
    };
    const auto res = api.query_sub_account_assets(params);
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

TEST(RestApiAssetManagementApi, QuerySubAccountAssetsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubAccountAssetsParams params{.email = "123@test.com"};
    EXPECT_THROW((void)api.query_sub_account_assets(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, QuerySubAccountAssetsAssetManagement) {
    const std::string example =
        R"json({"balances":[{"freeze":"0","withdrawing":"0","asset":"ADA","free":"10000","locked":"0"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountAssetsAssetManagementParams params{.email = "123@test.com"};
    const auto res = api.query_sub_account_assets_asset_management(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v4/sub-account/assets");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QuerySubAccountAssetsAssetManagementWithOptionalParams) {
    const std::string example =
        R"json({"balances":[{"freeze":"0","withdrawing":"0","asset":"ADA","free":"10000","locked":"0"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountAssetsAssetManagementParams params{
        .email = "123@test.com",
        .recv_window = 5000,
    };
    const auto res = api.query_sub_account_assets_asset_management(params);
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

TEST(RestApiAssetManagementApi, QuerySubAccountAssetsAssetManagementBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubAccountAssetsAssetManagementParams params{.email = "123@test.com"};
    EXPECT_THROW((void)api.query_sub_account_assets_asset_management(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, QuerySubAccountFuturesAssetTransferHistory) {
    const std::string example =
        R"json({"success":true,"futuresType":2,"transfers":[{"from":"aaa@test.com","to":"bbb@test.com","asset":"BTC","qty":"1","tranId":11897001102,"time":1544433328000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountFuturesAssetTransferHistoryParams params{.email = "123@test.com",
                                                                  .futures_type = 1};
    const auto res = api.query_sub_account_futures_asset_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/futures/internalTransfer");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("futuresType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QuerySubAccountFuturesAssetTransferHistoryWithOptionalParams) {
    const std::string example =
        R"json({"success":true,"futuresType":2,"transfers":[{"from":"aaa@test.com","to":"bbb@test.com","asset":"BTC","qty":"1","tranId":11897001102,"time":1544433328000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountFuturesAssetTransferHistoryParams params{
        .email = "123@test.com",
        .futures_type = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_sub_account_futures_asset_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("futuresType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QuerySubAccountFuturesAssetTransferHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubAccountFuturesAssetTransferHistoryParams params{.email = "123@test.com",
                                                                  .futures_type = 1};
    EXPECT_THROW((void)api.query_sub_account_futures_asset_transfer_history(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, SubAccountFuturesAssetTransfer) {
    const std::string example = R"json({"success":true,"txnId":"2934662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubAccountFuturesAssetTransferParams params{.from_email = "abc@test.com",
                                                      .to_email = "def@test.com",
                                                      .futures_type = 1,
                                                      .asset = "BTC",
                                                      .amount = common::Decimal("1.0")};
    const auto res = api.sub_account_futures_asset_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/futures/internalTransfer");
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("futuresType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, SubAccountFuturesAssetTransferWithOptionalParams) {
    const std::string example = R"json({"success":true,"txnId":"2934662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubAccountFuturesAssetTransferParams params{
        .from_email = "abc@test.com",
        .to_email = "def@test.com",
        .futures_type = 1,
        .asset = "BTC",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.sub_account_futures_asset_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("futuresType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, SubAccountFuturesAssetTransferBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubAccountFuturesAssetTransferParams params{.from_email = "abc@test.com",
                                                      .to_email = "def@test.com",
                                                      .futures_type = 1,
                                                      .asset = "BTC",
                                                      .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.sub_account_futures_asset_transfer(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, QuerySubAccountSpotAssetTransferHistory) {
    const std::string example =
        R"json([{"from":"aaa@test.com","to":"bbb@test.com","asset":"BTC","qty":"10","status":"SUCCESS","tranId":6489943656,"time":1544433328000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountSpotAssetTransferHistoryParams params{};
    const auto res = api.query_sub_account_spot_asset_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/sub/transfer/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QuerySubAccountSpotAssetTransferHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"from":"aaa@test.com","to":"bbb@test.com","asset":"BTC","qty":"10","status":"SUCCESS","tranId":6489943656,"time":1544433328000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountSpotAssetTransferHistoryParams params{
        .from_email = "aaa@test.com",
        .to_email = "bbb@test.com",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_sub_account_spot_asset_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QuerySubAccountSpotAssetTransferHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubAccountSpotAssetTransferHistoryParams params{};
    EXPECT_THROW((void)api.query_sub_account_spot_asset_transfer_history(params),
                 common::BadRequestError);
}

TEST(RestApiAssetManagementApi, QuerySubAccountSpotAssetsSummary) {
    const std::string example =
        R"json({"totalCount":2,"masterAccountTotalAsset":"0.23231201","spotSubUserAssetBtcVoList":[{"email":"sub123@test.com","totalAsset":"9999.00000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountSpotAssetsSummaryParams params{};
    const auto res = api.query_sub_account_spot_assets_summary(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/spotSummary");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QuerySubAccountSpotAssetsSummaryWithOptionalParams) {
    const std::string example =
        R"json({"totalCount":2,"masterAccountTotalAsset":"0.23231201","spotSubUserAssetBtcVoList":[{"email":"sub123@test.com","totalAsset":"9999.00000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountSpotAssetsSummaryParams params{
        .email = "123@test.com",
        .page = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_sub_account_spot_assets_summary(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QuerySubAccountSpotAssetsSummaryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubAccountSpotAssetsSummaryParams params{};
    EXPECT_THROW((void)api.query_sub_account_spot_assets_summary(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, QueryUniversalTransferHistory) {
    const std::string example =
        R"json({"result":[{"tranId":92275823339,"fromEmail":"abctest@gmail.com","toEmail":"deftest@gmail.com","asset":"BNB","amount":"0.01","createTimeStamp":1640317374000,"fromAccountType":"USDT_FUTURE","toAccountType":"SPOT","status":"SUCCESS","clientTranId":"test"}],"totalCount":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUniversalTransferHistoryParams params{};
    const auto res = api.query_universal_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/universalTransfer");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QueryUniversalTransferHistoryWithOptionalParams) {
    const std::string example =
        R"json({"result":[{"tranId":92275823339,"fromEmail":"abctest@gmail.com","toEmail":"deftest@gmail.com","asset":"BNB","amount":"0.01","createTimeStamp":1640317374000,"fromAccountType":"USDT_FUTURE","toAccountType":"SPOT","status":"SUCCESS","clientTranId":"test"}],"totalCount":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUniversalTransferHistoryParams params{
        .from_email = "abctest@gmail.com",
        .to_email = "deftest@gmail.com",
        .client_tran_id = "1",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_universal_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientTranId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, QueryUniversalTransferHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUniversalTransferHistoryParams params{};
    EXPECT_THROW((void)api.query_universal_transfer_history(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, UniversalTransfer) {
    const std::string example = R"json({"tranId":11945860693,"clientTranId":"test"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UniversalTransferParams params{
        .from_account_type = UniversalTransferFromAccountTypeEnum::Spot,
        .to_account_type = UniversalTransferToAccountTypeEnum::Spot,
        .asset = "BTC",
        .amount = common::Decimal("1.0")};
    const auto res = api.universal_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/universalTransfer");
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAccountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toAccountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, UniversalTransferWithOptionalParams) {
    const std::string example = R"json({"tranId":11945860693,"clientTranId":"test"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UniversalTransferParams params{
        .from_account_type = UniversalTransferFromAccountTypeEnum::Spot,
        .to_account_type = UniversalTransferToAccountTypeEnum::Spot,
        .asset = "BTC",
        .amount = common::Decimal("1.0"),
        .from_email = "abc@test.com",
        .to_email = "def@test.com",
        .client_tran_id = "1",
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.universal_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAccountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toAccountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientTranId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, UniversalTransferBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UniversalTransferParams params{
        .from_account_type = UniversalTransferFromAccountTypeEnum::Spot,
        .to_account_type = UniversalTransferToAccountTypeEnum::Spot,
        .asset = "BTC",
        .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.universal_transfer(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, SubAccountTransferHistory) {
    const std::string example =
        R"json([{"counterParty":"master","email":"master@test.com","type":1,"asset":"BTC","qty":"1","fromAccountType":"SPOT","toAccountType":"SPOT","status":"SUCCESS","tranId":11798835829,"time":1544433325000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubAccountTransferHistoryParams params{};
    const auto res = api.sub_account_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/transfer/subUserHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, SubAccountTransferHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"counterParty":"master","email":"master@test.com","type":1,"asset":"BTC","qty":"1","fromAccountType":"SPOT","toAccountType":"SPOT","status":"SUCCESS","tranId":11798835829,"time":1544433325000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubAccountTransferHistoryParams params{
        .asset = "BTC",
        .type = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 10,
        .return_fail_history = false,
        .recv_window = 5000,
    };
    const auto res = api.sub_account_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("returnFailHistory="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, SubAccountTransferHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubAccountTransferHistoryParams params{};
    EXPECT_THROW((void)api.sub_account_transfer_history(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, TransferToMaster) {
    const std::string example = R"json({"txnId":"2966662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TransferToMasterParams params{.asset = "BTC", .amount = common::Decimal("1.0")};
    const auto res = api.transfer_to_master(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/transfer/subToMaster");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, TransferToMasterWithOptionalParams) {
    const std::string example = R"json({"txnId":"2966662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TransferToMasterParams params{
        .asset = "BTC",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.transfer_to_master(params);
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

TEST(RestApiAssetManagementApi, TransferToMasterBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TransferToMasterParams params{.asset = "BTC", .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.transfer_to_master(params), common::BadRequestError);
}

TEST(RestApiAssetManagementApi, TransferToSubAccountOfSameMaster) {
    const std::string example = R"json({"txnId":"2966662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TransferToSubAccountOfSameMasterParams params{
        .to_email = "abc@test.com", .asset = "BTC", .amount = common::Decimal("1.0")};
    const auto res = api.transfer_to_sub_account_of_same_master(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/transfer/subToSub");
    EXPECT_NE((rec.query() + "&" + rec.body).find("toEmail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetManagementApi, TransferToSubAccountOfSameMasterWithOptionalParams) {
    const std::string example = R"json({"txnId":"2966662589"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TransferToSubAccountOfSameMasterParams params{
        .to_email = "abc@test.com",
        .asset = "BTC",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.transfer_to_sub_account_of_same_master(params);
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

TEST(RestApiAssetManagementApi, TransferToSubAccountOfSameMasterBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TransferToSubAccountOfSameMasterParams params{
        .to_email = "abc@test.com", .asset = "BTC", .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.transfer_to_sub_account_of_same_master(params), common::BadRequestError);
}
