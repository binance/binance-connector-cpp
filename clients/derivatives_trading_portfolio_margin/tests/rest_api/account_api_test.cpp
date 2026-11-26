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
#include <binance/derivatives_trading_portfolio_margin/rest_api/account_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_portfolio_margin::rest_api;
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

TEST(RestApiAccountApi, AccountBalance) {
    const std::string example =
        R"json([{"asset":"USDT","totalWalletBalance":"126.72469206","crossMarginAsset":"103.00000000","crossMarginBorrowed":"10.00000000","crossMarginFree":"100.00000000","crossMarginInterest":"0.72469206","crossMarginLocked":"3.00000000","umWalletBalance":"0.00000000","umUnrealizedPNL":"23.72469206","cmWalletBalance":"23.72469206","cmUnrealizedPNL":"","updateTime":1617939110373,"negativeBalance":"0"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountBalanceParams params{};
    const auto res = api.account_balance(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/balance");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountBalanceWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"USDT","totalWalletBalance":"126.72469206","crossMarginAsset":"103.00000000","crossMarginBorrowed":"10.00000000","crossMarginFree":"100.00000000","crossMarginInterest":"0.72469206","crossMarginLocked":"3.00000000","umWalletBalance":"0.00000000","umUnrealizedPNL":"23.72469206","cmWalletBalance":"23.72469206","cmUnrealizedPNL":"","updateTime":1617939110373,"negativeBalance":"0"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountBalanceParams params{
        .asset = "USDT",
        .recv_window = 5000,
    };
    const auto res = api.account_balance(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountBalanceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountBalanceParams params{};
    EXPECT_THROW((void)api.account_balance(params), common::BadRequestError);
}

TEST(RestApiAccountApi, AccountInformation) {
    const std::string example =
        R"json({"uniMMR":"5167.92171923","accountEquity":"73.47428058","actualEquity":"122607.35137903","accountInitialMargin":"23.72469206","accountMaintMargin":"23.72469206","accountStatus":"NORMAL","virtualMaxWithdrawAmount":"1627523.32459208","totalAvailableBalance":"","totalMarginOpenLoss":"","updateTime":1657707212154})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInformationParams params{};
    const auto res = api.account_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInformationWithOptionalParams) {
    const std::string example =
        R"json({"uniMMR":"5167.92171923","accountEquity":"73.47428058","actualEquity":"122607.35137903","accountInitialMargin":"23.72469206","accountMaintMargin":"23.72469206","accountStatus":"NORMAL","virtualMaxWithdrawAmount":"1627523.32459208","totalAvailableBalance":"","totalMarginOpenLoss":"","updateTime":1657707212154})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInformationParams params{
        .recv_window = 5000,
    };
    const auto res = api.account_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountInformationParams params{};
    EXPECT_THROW((void)api.account_information(params), common::BadRequestError);
}

TEST(RestApiAccountApi, BnbTransfer) {
    const std::string example = R"json({"tranId":100000001})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BnbTransferParams params{.amount = common::Decimal("1.0"),
                                   .transfer_side = BnbTransferTransferSideEnum::ToUm};
    const auto res = api.bnb_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/bnb-transfer");
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferSide="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, BnbTransferWithOptionalParams) {
    const std::string example = R"json({"tranId":100000001})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BnbTransferParams params{
        .amount = common::Decimal("1.0"),
        .transfer_side = BnbTransferTransferSideEnum::ToUm,
        .recv_window = 5000,
    };
    const auto res = api.bnb_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, BnbTransferBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const BnbTransferParams params{.amount = common::Decimal("1.0"),
                                   .transfer_side = BnbTransferTransferSideEnum::ToUm};
    EXPECT_THROW((void)api.bnb_transfer(params), common::BadRequestError);
}

TEST(RestApiAccountApi, ChangeAutoRepayFuturesStatus) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeAutoRepayFuturesStatusParams params{
        .auto_repay = ChangeAutoRepayFuturesStatusAutoRepayEnum::True_};
    const auto res = api.change_auto_repay_futures_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/repay-futures-switch");
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoRepay="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeAutoRepayFuturesStatusWithOptionalParams) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeAutoRepayFuturesStatusParams params{
        .auto_repay = ChangeAutoRepayFuturesStatusAutoRepayEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.change_auto_repay_futures_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoRepay="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeAutoRepayFuturesStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ChangeAutoRepayFuturesStatusParams params{
        .auto_repay = ChangeAutoRepayFuturesStatusAutoRepayEnum::True_};
    EXPECT_THROW((void)api.change_auto_repay_futures_status(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetAutoRepayFuturesStatus) {
    const std::string example = R"json({"autoRepay":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAutoRepayFuturesStatusParams params{};
    const auto res = api.get_auto_repay_futures_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/repay-futures-switch");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetAutoRepayFuturesStatusWithOptionalParams) {
    const std::string example = R"json({"autoRepay":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAutoRepayFuturesStatusParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_auto_repay_futures_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetAutoRepayFuturesStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetAutoRepayFuturesStatusParams params{};
    EXPECT_THROW((void)api.get_auto_repay_futures_status(params), common::BadRequestError);
}

TEST(RestApiAccountApi, ChangeCmInitialLeverage) {
    const std::string example =
        R"json({"leverage":21,"maxQty":"1000","symbol":"BTCUSD_200925"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeCmInitialLeverageParams params{.symbol = "BTCUSD_200925", .leverage = 21};
    const auto res = api.change_cm_initial_leverage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/leverage");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("leverage="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeCmInitialLeverageWithOptionalParams) {
    const std::string example =
        R"json({"leverage":21,"maxQty":"1000","symbol":"BTCUSD_200925"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeCmInitialLeverageParams params{
        .symbol = "BTCUSD_200925",
        .leverage = 21,
        .recv_window = 5000,
    };
    const auto res = api.change_cm_initial_leverage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("leverage="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeCmInitialLeverageBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ChangeCmInitialLeverageParams params{.symbol = "BTCUSD_200925", .leverage = 21};
    EXPECT_THROW((void)api.change_cm_initial_leverage(params), common::BadRequestError);
}

TEST(RestApiAccountApi, ChangeCmPositionMode) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeCmPositionModeParams params{.dual_side_position =
                                                ChangeCmPositionModeDualSidePositionEnum::True_};
    const auto res = api.change_cm_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/positionSide/dual");
    EXPECT_NE((rec.query() + "&" + rec.body).find("dualSidePosition="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeCmPositionModeWithOptionalParams) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeCmPositionModeParams params{
        .dual_side_position = ChangeCmPositionModeDualSidePositionEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.change_cm_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("dualSidePosition="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeCmPositionModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ChangeCmPositionModeParams params{.dual_side_position =
                                                ChangeCmPositionModeDualSidePositionEnum::True_};
    EXPECT_THROW((void)api.change_cm_position_mode(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetCmCurrentPositionMode) {
    const std::string example = R"json({"dualSidePosition":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmCurrentPositionModeParams params{};
    const auto res = api.get_cm_current_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/positionSide/dual");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmCurrentPositionModeWithOptionalParams) {
    const std::string example = R"json({"dualSidePosition":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmCurrentPositionModeParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_cm_current_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmCurrentPositionModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCmCurrentPositionModeParams params{};
    EXPECT_THROW((void)api.get_cm_current_position_mode(params), common::BadRequestError);
}

TEST(RestApiAccountApi, ChangeUmInitialLeverage) {
    const std::string example =
        R"json({"leverage":21,"maxNotionalValue":"1000000","symbol":"BTCUSDT"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeUmInitialLeverageParams params{.symbol = "BTCUSDT", .leverage = 21};
    const auto res = api.change_um_initial_leverage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/um/leverage");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("leverage="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeUmInitialLeverageWithOptionalParams) {
    const std::string example =
        R"json({"leverage":21,"maxNotionalValue":"1000000","symbol":"BTCUSDT"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeUmInitialLeverageParams params{
        .symbol = "BTCUSDT",
        .leverage = 21,
        .recv_window = 5000,
    };
    const auto res = api.change_um_initial_leverage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("leverage="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeUmInitialLeverageBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ChangeUmInitialLeverageParams params{.symbol = "BTCUSDT", .leverage = 21};
    EXPECT_THROW((void)api.change_um_initial_leverage(params), common::BadRequestError);
}

TEST(RestApiAccountApi, ChangeUmPositionMode) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeUmPositionModeParams params{.dual_side_position =
                                                ChangeUmPositionModeDualSidePositionEnum::True_};
    const auto res = api.change_um_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/um/positionSide/dual");
    EXPECT_NE((rec.query() + "&" + rec.body).find("dualSidePosition="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeUmPositionModeWithOptionalParams) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ChangeUmPositionModeParams params{
        .dual_side_position = ChangeUmPositionModeDualSidePositionEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.change_um_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("dualSidePosition="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ChangeUmPositionModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ChangeUmPositionModeParams params{.dual_side_position =
                                                ChangeUmPositionModeDualSidePositionEnum::True_};
    EXPECT_THROW((void)api.change_um_position_mode(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetUmCurrentPositionMode) {
    const std::string example = R"json({"dualSidePosition":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmCurrentPositionModeParams params{};
    const auto res = api.get_um_current_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/positionSide/dual");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmCurrentPositionModeWithOptionalParams) {
    const std::string example = R"json({"dualSidePosition":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmCurrentPositionModeParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_um_current_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmCurrentPositionModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUmCurrentPositionModeParams params{};
    EXPECT_THROW((void)api.get_um_current_position_mode(params), common::BadRequestError);
}

TEST(RestApiAccountApi, CmNotionalAndLeverageBrackets) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_PERP","brackets":[{"bracket":1,"initialLeverage":125,"qtyCap":50,"qtyFloor":0,"maintMarginRatio":0.004,"cum":0}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CmNotionalAndLeverageBracketsParams params{};
    const auto res = api.cm_notional_and_leverage_brackets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/leverageBracket");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, CmNotionalAndLeverageBracketsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_PERP","brackets":[{"bracket":1,"initialLeverage":125,"qtyCap":50,"qtyFloor":0,"maintMarginRatio":0.004,"cum":0}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CmNotionalAndLeverageBracketsParams params{
        .symbol = "BTCUSD_PERP",
        .recv_window = 5000,
    };
    const auto res = api.cm_notional_and_leverage_brackets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, CmNotionalAndLeverageBracketsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CmNotionalAndLeverageBracketsParams params{};
    EXPECT_THROW((void)api.cm_notional_and_leverage_brackets(params), common::BadRequestError);
}

TEST(RestApiAccountApi, FundAutoCollection) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FundAutoCollectionParams params{};
    const auto res = api.fund_auto_collection(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/auto-collection");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FundAutoCollectionWithOptionalParams) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FundAutoCollectionParams params{
        .recv_window = 5000,
    };
    const auto res = api.fund_auto_collection(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FundAutoCollectionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FundAutoCollectionParams params{};
    EXPECT_THROW((void)api.fund_auto_collection(params), common::BadRequestError);
}

TEST(RestApiAccountApi, FundCollectionByAsset) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FundCollectionByAssetParams params{.asset = "BTC"};
    const auto res = api.fund_collection_by_asset(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/asset-collection");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FundCollectionByAssetWithOptionalParams) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FundCollectionByAssetParams params{
        .asset = "BTC",
        .amount = common::Decimal("10"),
        .future_type = FundCollectionByAssetFutureTypeEnum::Um,
        .recv_window = 5000,
    };
    const auto res = api.fund_collection_by_asset(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("futureType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FundCollectionByAssetBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FundCollectionByAssetParams params{.asset = "BTC"};
    EXPECT_THROW((void)api.fund_collection_by_asset(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetCmAccountDetail) {
    const std::string example =
        R"json({"assets":[{"asset":"BTC","crossWalletBalance":"0.00241969","crossUnPnl":"0.00000000","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSD_201225","positionAmt":"0","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"125","positionSide":"BOTH","entryPrice":"0.0","maxQty":"50","updateTime":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmAccountDetailParams params{};
    const auto res = api.get_cm_account_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmAccountDetailWithOptionalParams) {
    const std::string example =
        R"json({"assets":[{"asset":"BTC","crossWalletBalance":"0.00241969","crossUnPnl":"0.00000000","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSD_201225","positionAmt":"0","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"125","positionSide":"BOTH","entryPrice":"0.0","maxQty":"50","updateTime":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmAccountDetailParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_cm_account_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmAccountDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCmAccountDetailParams params{};
    EXPECT_THROW((void)api.get_cm_account_detail(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetCmFuturesOrderDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmFuturesOrderDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    const auto res = api.get_cm_futures_order_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/order/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmFuturesOrderDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmFuturesOrderDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_cm_futures_order_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmFuturesOrderDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCmFuturesOrderDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    EXPECT_THROW((void)api.get_cm_futures_order_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetCmFuturesTradeDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmFuturesTradeDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    const auto res = api.get_cm_futures_trade_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/trade/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmFuturesTradeDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmFuturesTradeDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_cm_futures_trade_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmFuturesTradeDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCmFuturesTradeDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    EXPECT_THROW((void)api.get_cm_futures_trade_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetCmFuturesTransactionDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmFuturesTransactionDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    const auto res = api.get_cm_futures_transaction_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/income/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmFuturesTransactionDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmFuturesTransactionDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_cm_futures_transaction_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmFuturesTransactionDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCmFuturesTransactionDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    EXPECT_THROW((void)api.get_cm_futures_transaction_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetCmIncomeHistory) {
    const std::string example =
        R"json([{"symbol":"","incomeType":"TRANSFER","income":"-0.37500000","asset":"BTC","info":"WITHDRAW","time":1570608000000,"tranId":"9689322392","tradeId":""}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmIncomeHistoryParams params{};
    const auto res = api.get_cm_income_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/income");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmIncomeHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"","incomeType":"TRANSFER","income":"-0.37500000","asset":"BTC","info":"WITHDRAW","time":1570608000000,"tranId":"9689322392","tradeId":""}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCmIncomeHistoryParams params{
        .symbol = "BTCUSD_200925",
        .income_type = GetCmIncomeHistoryIncomeTypeEnum::Transfer,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 100,
        .recv_window = 5000,
    };
    const auto res = api.get_cm_income_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("incomeType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCmIncomeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCmIncomeHistoryParams params{};
    EXPECT_THROW((void)api.get_cm_income_history(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForCmFuturesOrderHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForCmFuturesOrderHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    const auto res = api.get_download_id_for_cm_futures_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/order/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForCmFuturesOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForCmFuturesOrderHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_cm_futures_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForCmFuturesOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForCmFuturesOrderHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_cm_futures_order_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForCmFuturesTradeHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForCmFuturesTradeHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    const auto res = api.get_download_id_for_cm_futures_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/trade/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForCmFuturesTradeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForCmFuturesTradeHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_cm_futures_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForCmFuturesTradeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForCmFuturesTradeHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_cm_futures_trade_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForCmFuturesTransactionHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForCmFuturesTransactionHistoryParams params{.start_time = 1623319461670,
                                                                   .end_time = 1641782889000};
    const auto res = api.get_download_id_for_cm_futures_transaction_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/income/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForCmFuturesTransactionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForCmFuturesTransactionHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_cm_futures_transaction_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForCmFuturesTransactionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForCmFuturesTransactionHistoryParams params{.start_time = 1623319461670,
                                                                   .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_cm_futures_transaction_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForUmFuturesOrderHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForUmFuturesOrderHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    const auto res = api.get_download_id_for_um_futures_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/order/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForUmFuturesOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForUmFuturesOrderHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_um_futures_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForUmFuturesOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForUmFuturesOrderHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_um_futures_order_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForUmFuturesTradeHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForUmFuturesTradeHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    const auto res = api.get_download_id_for_um_futures_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/trade/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForUmFuturesTradeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForUmFuturesTradeHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_um_futures_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForUmFuturesTradeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForUmFuturesTradeHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_um_futures_trade_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForUmFuturesTransactionHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForUmFuturesTransactionHistoryParams params{.start_time = 1623319461670,
                                                                   .end_time = 1641782889000};
    const auto res = api.get_download_id_for_um_futures_transaction_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/income/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForUmFuturesTransactionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForUmFuturesTransactionHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_um_futures_transaction_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForUmFuturesTransactionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForUmFuturesTransactionHistoryParams params{.start_time = 1623319461670,
                                                                   .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_um_futures_transaction_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetMarginBorrowLoanInterestHistory) {
    const std::string example =
        R"json({"rows":[{"txId":1352286576452864800,"interestAccuredTime":1672160400000,"asset":"USDT","rawAsset":"USDT","principal":"45.3313","interest":"0.00024995","interestRate":"0.00013233","type":"ON_BORROW"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetMarginBorrowLoanInterestHistoryParams params{};
    const auto res = api.get_margin_borrow_loan_interest_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/marginInterestHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetMarginBorrowLoanInterestHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"txId":1352286576452864800,"interestAccuredTime":1672160400000,"asset":"USDT","rawAsset":"USDT","principal":"45.3313","interest":"0.00024995","interestRate":"0.00013233","type":"ON_BORROW"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetMarginBorrowLoanInterestHistoryParams params{
        .asset = "USDT",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .archived = GetMarginBorrowLoanInterestHistoryArchivedEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.get_margin_borrow_loan_interest_history(params);
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
    EXPECT_NE((rec.query() + "&" + rec.body).find("archived="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetMarginBorrowLoanInterestHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetMarginBorrowLoanInterestHistoryParams params{};
    EXPECT_THROW((void)api.get_margin_borrow_loan_interest_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetUmAccountDetail) {
    const std::string example =
        R"json({"assets":[{"asset":"USDT","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"100","entryPrice":"0.00000","maxNotional":"250000","bidNotional":"0","askNotional":"0","positionSide":"BOTH","positionAmt":"0","updateTime":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmAccountDetailParams params{};
    const auto res = api.get_um_account_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmAccountDetailWithOptionalParams) {
    const std::string example =
        R"json({"assets":[{"asset":"USDT","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"100","entryPrice":"0.00000","maxNotional":"250000","bidNotional":"0","askNotional":"0","positionSide":"BOTH","positionAmt":"0","updateTime":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmAccountDetailParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_um_account_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmAccountDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUmAccountDetailParams params{};
    EXPECT_THROW((void)api.get_um_account_detail(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetUmAccountDetailV2) {
    const std::string example =
        R"json({"assets":[{"asset":"USDT","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionSide":"BOTH","positionAmt":"0","updateTime":0,"notional":"86.98650000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmAccountDetailV2Params params{};
    const auto res = api.get_um_account_detail_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v2/um/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmAccountDetailV2WithOptionalParams) {
    const std::string example =
        R"json({"assets":[{"asset":"USDT","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionSide":"BOTH","positionAmt":"0","updateTime":0,"notional":"86.98650000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmAccountDetailV2Params params{
        .recv_window = 5000,
    };
    const auto res = api.get_um_account_detail_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmAccountDetailV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUmAccountDetailV2Params params{};
    EXPECT_THROW((void)api.get_um_account_detail_v2(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetUmFuturesOrderDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmFuturesOrderDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    const auto res = api.get_um_futures_order_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/order/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmFuturesOrderDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmFuturesOrderDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_um_futures_order_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmFuturesOrderDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUmFuturesOrderDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    EXPECT_THROW((void)api.get_um_futures_order_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetUmFuturesTradeDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmFuturesTradeDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    const auto res = api.get_um_futures_trade_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/trade/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmFuturesTradeDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmFuturesTradeDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_um_futures_trade_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmFuturesTradeDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUmFuturesTradeDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    EXPECT_THROW((void)api.get_um_futures_trade_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetUmFuturesTransactionDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmFuturesTransactionDownloadLinkByIdParams params{.download_id = "1"};
    const auto res = api.get_um_futures_transaction_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/income/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmFuturesTransactionDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","s3Link":"null","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmFuturesTransactionDownloadLinkByIdParams params{
        .download_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.get_um_futures_transaction_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmFuturesTransactionDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUmFuturesTransactionDownloadLinkByIdParams params{.download_id = "1"};
    EXPECT_THROW((void)api.get_um_futures_transaction_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetUmIncomeHistory) {
    const std::string example =
        R"json([{"symbol":"","incomeType":"TRANSFER","income":"-0.37500000","asset":"USDT","info":"TRANSFER","time":1570608000000,"tranId":"9689322392","tradeId":""}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmIncomeHistoryParams params{};
    const auto res = api.get_um_income_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/income");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmIncomeHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"","incomeType":"TRANSFER","income":"-0.37500000","asset":"USDT","info":"TRANSFER","time":1570608000000,"tranId":"9689322392","tradeId":""}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUmIncomeHistoryParams params{
        .symbol = "symbol_example",
        .income_type = GetUmIncomeHistoryIncomeTypeEnum::Transfer,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 100,
        .recv_window = 5000,
    };
    const auto res = api.get_um_income_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("incomeType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUmIncomeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUmIncomeHistoryParams params{};
    EXPECT_THROW((void)api.get_um_income_history(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetUserCommissionRateForCm) {
    const std::string example =
        R"json({"symbol":"BTCUSD_PERP","makerCommissionRate":"0.00015","takerCommissionRate":"0.00040"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUserCommissionRateForCmParams params{.symbol = "BTCUSD_PERP"};
    const auto res = api.get_user_commission_rate_for_cm(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/commissionRate");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUserCommissionRateForCmWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSD_PERP","makerCommissionRate":"0.00015","takerCommissionRate":"0.00040"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUserCommissionRateForCmParams params{
        .symbol = "BTCUSD_PERP",
        .recv_window = 5000,
    };
    const auto res = api.get_user_commission_rate_for_cm(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUserCommissionRateForCmBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUserCommissionRateForCmParams params{.symbol = "BTCUSD_PERP"};
    EXPECT_THROW((void)api.get_user_commission_rate_for_cm(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetUserCommissionRateForUm) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","makerCommissionRate":"0.0002","takerCommissionRate":"0.0004"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUserCommissionRateForUmParams params{.symbol = "BTCUSDT"};
    const auto res = api.get_user_commission_rate_for_um(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/commissionRate");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUserCommissionRateForUmWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","makerCommissionRate":"0.0002","takerCommissionRate":"0.0004"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetUserCommissionRateForUmParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.get_user_commission_rate_for_um(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetUserCommissionRateForUmBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetUserCommissionRateForUmParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.get_user_commission_rate_for_um(params), common::BadRequestError);
}

TEST(RestApiAccountApi, MarginMaxBorrow) {
    const std::string example = R"json({"amount":"1.69248805","borrowLimit":"60"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginMaxBorrowParams params{.asset = "USDT"};
    const auto res = api.margin_max_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/maxBorrowable");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, MarginMaxBorrowWithOptionalParams) {
    const std::string example = R"json({"amount":"1.69248805","borrowLimit":"60"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginMaxBorrowParams params{
        .asset = "USDT",
        .recv_window = 5000,
    };
    const auto res = api.margin_max_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, MarginMaxBorrowBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginMaxBorrowParams params{.asset = "USDT"};
    EXPECT_THROW((void)api.margin_max_borrow(params), common::BadRequestError);
}

TEST(RestApiAccountApi, PortfolioMarginUmTradingQuantitativeRulesIndicators) {
    const std::string example =
        R"json({"indicators":{"BTCUSDT":[{"isLocked":true,"plannedRecoverTime":1545741270000,"indicator":"UFR","value":0.05,"triggerValue":0.995}],"ACCOUNT":[{"indicator":"TMV","value":10,"triggerValue":1,"plannedRecoverTime":1644919865000,"isLocked":true}]},"updateTime":1644913304748})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams params{};
    const auto res = api.portfolio_margin_um_trading_quantitative_rules_indicators(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/apiTradingStatus");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, PortfolioMarginUmTradingQuantitativeRulesIndicatorsWithOptionalParams) {
    const std::string example =
        R"json({"indicators":{"BTCUSDT":[{"isLocked":true,"plannedRecoverTime":1545741270000,"indicator":"UFR","value":0.05,"triggerValue":0.995}],"ACCOUNT":[{"indicator":"TMV","value":10,"triggerValue":1,"plannedRecoverTime":1644919865000,"isLocked":true}]},"updateTime":1644913304748})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.portfolio_margin_um_trading_quantitative_rules_indicators(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, PortfolioMarginUmTradingQuantitativeRulesIndicatorsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams params{};
    EXPECT_THROW((void)api.portfolio_margin_um_trading_quantitative_rules_indicators(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, QueryCmPositionInformation) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_201225","positionAmt":"0","entryPrice":"0.0","markPrice":"0.00000000","unRealizedProfit":"0.00000000","liquidationPrice":"6170.20509059","leverage":"125","positionSide":"BOTH","updateTime":0,"maxQty":"50","notionalValue":"0.00084827"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCmPositionInformationParams params{};
    const auto res = api.query_cm_position_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/cm/positionRisk");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryCmPositionInformationWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_201225","positionAmt":"0","entryPrice":"0.0","markPrice":"0.00000000","unRealizedProfit":"0.00000000","liquidationPrice":"6170.20509059","leverage":"125","positionSide":"BOTH","updateTime":0,"maxQty":"50","notionalValue":"0.00084827"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCmPositionInformationParams params{
        .margin_asset = "USDT",
        .pair = "BTCUSD_201225",
        .recv_window = 5000,
    };
    const auto res = api.query_cm_position_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marginAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryCmPositionInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCmPositionInformationParams params{};
    EXPECT_THROW((void)api.query_cm_position_information(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryMarginLoanRecord) {
    const std::string example =
        R"json({"rows":[{"txId":12807067523,"asset":"BNB","principal":"0.84624403","timestamp":1555056425000,"status":"CONFIRMED"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginLoanRecordParams params{.asset = "USDT"};
    const auto res = api.query_margin_loan_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/marginLoan");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryMarginLoanRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"txId":12807067523,"asset":"BNB","principal":"0.84624403","timestamp":1555056425000,"status":"CONFIRMED"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginLoanRecordParams params{
        .asset = "USDT",
        .tx_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .archived = QueryMarginLoanRecordArchivedEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.query_margin_loan_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("archived="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryMarginLoanRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginLoanRecordParams params{.asset = "USDT"};
    EXPECT_THROW((void)api.query_margin_loan_record(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryMarginMaxWithdraw) {
    const std::string example = R"json({"amount":"60"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginMaxWithdrawParams params{.asset = "USDT"};
    const auto res = api.query_margin_max_withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/maxWithdraw");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryMarginMaxWithdrawWithOptionalParams) {
    const std::string example = R"json({"amount":"60"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginMaxWithdrawParams params{
        .asset = "USDT",
        .recv_window = 5000,
    };
    const auto res = api.query_margin_max_withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryMarginMaxWithdrawBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginMaxWithdrawParams params{.asset = "USDT"};
    EXPECT_THROW((void)api.query_margin_max_withdraw(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryMarginRepayRecord) {
    const std::string example =
        R"json({"rows":[{"amount":"14.00000000","asset":"BNB","interest":"0.01866667","principal":"13.98133333","status":"CONFIRMED","timestamp":1563438204000,"txId":2970933056}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginRepayRecordParams params{.asset = "USDT"};
    const auto res = api.query_margin_repay_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/margin/repayLoan");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryMarginRepayRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"amount":"14.00000000","asset":"BNB","interest":"0.01866667","principal":"13.98133333","status":"CONFIRMED","timestamp":1563438204000,"txId":2970933056}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginRepayRecordParams params{
        .asset = "USDT",
        .tx_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .archived = QueryMarginRepayRecordArchivedEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.query_margin_repay_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("archived="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryMarginRepayRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginRepayRecordParams params{.asset = "USDT"};
    EXPECT_THROW((void)api.query_margin_repay_record(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryPortfolioMarginNegativeBalanceInterestHistory) {
    const std::string example =
        R"json([{"asset":"USDT","interest":"24.4440","interestAccuredTime":1670227200000,"interestRate":"0.0001164","principal":"210000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginNegativeBalanceInterestHistoryParams params{};
    const auto res = api.query_portfolio_margin_negative_balance_interest_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/portfolio/interest-history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryPortfolioMarginNegativeBalanceInterestHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"USDT","interest":"24.4440","interestAccuredTime":1670227200000,"interestRate":"0.0001164","principal":"210000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginNegativeBalanceInterestHistoryParams params{
        .asset = "USDT",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_portfolio_margin_negative_balance_interest_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryPortfolioMarginNegativeBalanceInterestHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPortfolioMarginNegativeBalanceInterestHistoryParams params{};
    EXPECT_THROW((void)api.query_portfolio_margin_negative_balance_interest_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, QueryUmPositionInformation) {
    const std::string example =
        R"json([{"entryPrice":"0.00000","leverage":"10","markPrice":"6679.50671178","maxNotionalValue":"20000000","positionAmt":"0.000","notional":"0","symbol":"BTCUSDT","unRealizedProfit":"0.00000000","liquidationPrice":"6170.20509059","positionSide":"BOTH","updateTime":1625474304765}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUmPositionInformationParams params{};
    const auto res = api.query_um_position_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/positionRisk");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryUmPositionInformationWithOptionalParams) {
    const std::string example =
        R"json([{"entryPrice":"0.00000","leverage":"10","markPrice":"6679.50671178","maxNotionalValue":"20000000","positionAmt":"0.000","notional":"0","symbol":"BTCUSDT","unRealizedProfit":"0.00000000","liquidationPrice":"6170.20509059","positionSide":"BOTH","updateTime":1625474304765}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUmPositionInformationParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_um_position_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryUmPositionInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUmPositionInformationParams params{};
    EXPECT_THROW((void)api.query_um_position_information(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryUserNegativeBalanceAutoExchangeRecord) {
    const std::string example =
        R"json({"total":2,"rows":[{"startTime":1736263046841,"endTime":1736263248179,"details":[{"asset":"ETH","negativeBalance":1.10264488,"negativeMaxThreshold":5}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserNegativeBalanceAutoExchangeRecordParams params{.start_time = 1623319461670,
                                                                  .end_time = 1641782889000};
    const auto res = api.query_user_negative_balance_auto_exchange_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/portfolio/negative-balance-exchange-record");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryUserNegativeBalanceAutoExchangeRecordWithOptionalParams) {
    const std::string example =
        R"json({"total":2,"rows":[{"startTime":1736263046841,"endTime":1736263248179,"details":[{"asset":"ETH","negativeBalance":1.10264488,"negativeMaxThreshold":5}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserNegativeBalanceAutoExchangeRecordParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.query_user_negative_balance_auto_exchange_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryUserNegativeBalanceAutoExchangeRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUserNegativeBalanceAutoExchangeRecordParams params{.start_time = 1623319461670,
                                                                  .end_time = 1641782889000};
    EXPECT_THROW((void)api.query_user_negative_balance_auto_exchange_record(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, QueryUserRateLimit) {
    const std::string example =
        R"json([{"rateLimitType":"ORDERS","interval":"MINUTE","intervalNum":1,"limit":1200}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserRateLimitParams params{};
    const auto res = api.query_user_rate_limit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/rateLimit/order");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryUserRateLimitWithOptionalParams) {
    const std::string example =
        R"json([{"rateLimitType":"ORDERS","interval":"MINUTE","intervalNum":1,"limit":1200}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserRateLimitParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_user_rate_limit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryUserRateLimitBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUserRateLimitParams params{};
    EXPECT_THROW((void)api.query_user_rate_limit(params), common::BadRequestError);
}

TEST(RestApiAccountApi, RepayFuturesNegativeBalance) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RepayFuturesNegativeBalanceParams params{};
    const auto res = api.repay_futures_negative_balance(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/papi/v1/repay-futures-negative-balance");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, RepayFuturesNegativeBalanceWithOptionalParams) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RepayFuturesNegativeBalanceParams params{
        .recv_window = 5000,
    };
    const auto res = api.repay_futures_negative_balance(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, RepayFuturesNegativeBalanceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RepayFuturesNegativeBalanceParams params{};
    EXPECT_THROW((void)api.repay_futures_negative_balance(params), common::BadRequestError);
}

TEST(RestApiAccountApi, UmFuturesAccountConfiguration) {
    const std::string example =
        R"json({"feeTier":0,"canTrade":true,"canDeposit":true,"canWithdraw":true,"dualSidePosition":true,"updateTime":1724416653850,"multiAssetsMargin":false,"tradeGroupId":-1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmFuturesAccountConfigurationParams params{};
    const auto res = api.um_futures_account_configuration(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/accountConfig");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, UmFuturesAccountConfigurationWithOptionalParams) {
    const std::string example =
        R"json({"feeTier":0,"canTrade":true,"canDeposit":true,"canWithdraw":true,"dualSidePosition":true,"updateTime":1724416653850,"multiAssetsMargin":false,"tradeGroupId":-1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmFuturesAccountConfigurationParams params{
        .recv_window = 5000,
    };
    const auto res = api.um_futures_account_configuration(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, UmFuturesAccountConfigurationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UmFuturesAccountConfigurationParams params{};
    EXPECT_THROW((void)api.um_futures_account_configuration(params), common::BadRequestError);
}

TEST(RestApiAccountApi, UmFuturesSymbolConfiguration) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","marginType":"CROSSED","isAutoAddMargin":"false","leverage":21,"maxNotionalValue":"1000000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmFuturesSymbolConfigurationParams params{};
    const auto res = api.um_futures_symbol_configuration(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/symbolConfig");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, UmFuturesSymbolConfigurationWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","marginType":"CROSSED","isAutoAddMargin":"false","leverage":21,"maxNotionalValue":"1000000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmFuturesSymbolConfigurationParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.um_futures_symbol_configuration(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, UmFuturesSymbolConfigurationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UmFuturesSymbolConfigurationParams params{};
    EXPECT_THROW((void)api.um_futures_symbol_configuration(params), common::BadRequestError);
}

TEST(RestApiAccountApi, UmNotionalAndLeverageBrackets) {
    const std::string example =
        R"json([{"symbol":"ETHUSDT","notionalCoef":"4.0","brackets":[{"bracket":1,"initialLeverage":75,"notionalCap":10000,"notionalFloor":0,"maintMarginRatio":0.0065,"cum":0}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmNotionalAndLeverageBracketsParams params{};
    const auto res = api.um_notional_and_leverage_brackets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/papi/v1/um/leverageBracket");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, UmNotionalAndLeverageBracketsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"ETHUSDT","notionalCoef":"4.0","brackets":[{"bracket":1,"initialLeverage":75,"notionalCap":10000,"notionalFloor":0,"maintMarginRatio":0.0065,"cum":0}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UmNotionalAndLeverageBracketsParams params{
        .symbol = "ETHUSDT",
        .recv_window = 5000,
    };
    const auto res = api.um_notional_and_leverage_brackets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, UmNotionalAndLeverageBracketsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UmNotionalAndLeverageBracketsParams params{};
    EXPECT_THROW((void)api.um_notional_and_leverage_brackets(params), common::BadRequestError);
}
