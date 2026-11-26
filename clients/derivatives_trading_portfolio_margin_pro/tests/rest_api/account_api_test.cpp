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
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/account_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_portfolio_margin_pro::rest_api;
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
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/bnb-transfer");
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
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/repay-futures-switch");
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
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/repay-futures-switch");
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

TEST(RestApiAccountApi, DeleteMarginCallLevel) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteMarginCallLevelParams params{};
    const auto res = api.delete_margin_call_level(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/margin-call-level");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, DeleteMarginCallLevelWithOptionalParams) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteMarginCallLevelParams params{
        .recv_window = 5000,
    };
    const auto res = api.delete_margin_call_level(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, DeleteMarginCallLevelBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DeleteMarginCallLevelParams params{};
    EXPECT_THROW((void)api.delete_margin_call_level(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetMarginCallLevel) {
    const std::string example = R"json({"marginCallLevel":"1.67354637"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetMarginCallLevelParams params{};
    const auto res = api.get_margin_call_level(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/margin-call-level");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetMarginCallLevelWithOptionalParams) {
    const std::string example = R"json({"marginCallLevel":"1.67354637"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetMarginCallLevelParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_margin_call_level(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetMarginCallLevelBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetMarginCallLevelParams params{};
    EXPECT_THROW((void)api.get_margin_call_level(params), common::BadRequestError);
}

TEST(RestApiAccountApi, SetMarginCallLevel) {
    const std::string example = R"json({"marginCallLevel":"1.67354637"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetMarginCallLevelParams params{.margin_call_level = common::Decimal("1.5")};
    const auto res = api.set_margin_call_level(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/margin-call-level");
    EXPECT_NE((rec.query() + "&" + rec.body).find("marginCallLevel="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, SetMarginCallLevelWithOptionalParams) {
    const std::string example = R"json({"marginCallLevel":"1.67354637"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SetMarginCallLevelParams params{
        .margin_call_level = common::Decimal("1.5"),
        .recv_window = 5000,
    };
    const auto res = api.set_margin_call_level(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marginCallLevel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, SetMarginCallLevelBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SetMarginCallLevelParams params{.margin_call_level = common::Decimal("1.5")};
    EXPECT_THROW((void)api.set_margin_call_level(params), common::BadRequestError);
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
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/auto-collection");
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
    const FundCollectionByAssetParams params{.asset = "USDT"};
    const auto res = api.fund_collection_by_asset(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/asset-collection");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FundCollectionByAssetWithOptionalParams) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FundCollectionByAssetParams params{
        .asset = "USDT",
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
    const FundCollectionByAssetParams params{.asset = "USDT"};
    EXPECT_THROW((void)api.fund_collection_by_asset(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetDeltaModeStatus) {
    const std::string example = R"json({"deltaEnabled":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDeltaModeStatusParams params{};
    const auto res = api.get_delta_mode_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/delta-mode");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDeltaModeStatusWithOptionalParams) {
    const std::string example = R"json({"deltaEnabled":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDeltaModeStatusParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_delta_mode_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDeltaModeStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDeltaModeStatusParams params{};
    EXPECT_THROW((void)api.get_delta_mode_status(params), common::BadRequestError);
}

TEST(RestApiAccountApi, SwitchDeltaMode) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SwitchDeltaModeParams params{.delta_enabled = SwitchDeltaModeDeltaEnabledEnum::True_};
    const auto res = api.switch_delta_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/delta-mode");
    EXPECT_NE((rec.query() + "&" + rec.body).find("deltaEnabled="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, SwitchDeltaModeWithOptionalParams) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SwitchDeltaModeParams params{
        .delta_enabled = SwitchDeltaModeDeltaEnabledEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.switch_delta_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("deltaEnabled="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, SwitchDeltaModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SwitchDeltaModeParams params{.delta_enabled = SwitchDeltaModeDeltaEnabledEnum::True_};
    EXPECT_THROW((void)api.switch_delta_mode(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetPortfolioMarginProAccountBalance) {
    const std::string example =
        R"json([{"asset":"USDT","totalWalletBalance":"122607.35137903","crossMarginAsset":"92.27530794","crossMarginBorrowed":"10.00000000","crossMarginFree":"100.00000000","crossMarginInterest":"0.72469206","crossMarginLocked":"3.00000000","umWalletBalance":"0.00000000","umUnrealizedPNL":"23.72469206","cmWalletBalance":"23.72469206","cmUnrealizedPNL":"","updateTime":1617939110373,"negativeBalance":"0","optionWalletBalance":"0","optionEquity":"0"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPortfolioMarginProAccountBalanceParams params{};
    const auto res = api.get_portfolio_margin_pro_account_balance(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/balance");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetPortfolioMarginProAccountBalanceWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"USDT","totalWalletBalance":"122607.35137903","crossMarginAsset":"92.27530794","crossMarginBorrowed":"10.00000000","crossMarginFree":"100.00000000","crossMarginInterest":"0.72469206","crossMarginLocked":"3.00000000","umWalletBalance":"0.00000000","umUnrealizedPNL":"23.72469206","cmWalletBalance":"23.72469206","cmUnrealizedPNL":"","updateTime":1617939110373,"negativeBalance":"0","optionWalletBalance":"0","optionEquity":"0"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPortfolioMarginProAccountBalanceParams params{
        .asset = "BTC",
        .recv_window = 5000,
    };
    const auto res = api.get_portfolio_margin_pro_account_balance(params);
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

TEST(RestApiAccountApi, GetPortfolioMarginProAccountBalanceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetPortfolioMarginProAccountBalanceParams params{};
    EXPECT_THROW((void)api.get_portfolio_margin_pro_account_balance(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetPortfolioMarginProAccountInfo) {
    const std::string example =
        R"json({"uniMMR":"5167.92171923","accountEquity":"122607.35137903","actualEquity":"142607.35137903","accountMaintMargin":"23.72469206","accountInitialMargin":"47.44938412","totalAvailableBalance":"122,559.90199491","accountStatus":"NORMAL","accountType":"PM_1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPortfolioMarginProAccountInfoParams params{};
    const auto res = api.get_portfolio_margin_pro_account_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetPortfolioMarginProAccountInfoWithOptionalParams) {
    const std::string example =
        R"json({"uniMMR":"5167.92171923","accountEquity":"122607.35137903","actualEquity":"142607.35137903","accountMaintMargin":"23.72469206","accountInitialMargin":"47.44938412","totalAvailableBalance":"122,559.90199491","accountStatus":"NORMAL","accountType":"PM_1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPortfolioMarginProAccountInfoParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_portfolio_margin_pro_account_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetPortfolioMarginProAccountInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetPortfolioMarginProAccountInfoParams params{};
    EXPECT_THROW((void)api.get_portfolio_margin_pro_account_info(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetPortfolioMarginProSpanAccountInfo) {
    const std::string example =
        R"json({"uniMMR":"5167.92171923","accountEquity":"122607.35137903","actualEquity":"142607.35137903","accountMaintMargin":"23.72469206","riskUnitMMList":[{"asset":"BTC","uniMaintainUsd":"23.72469206"}],"marginMM":"0.00000000","otherMM":"0.00000000","accountStatus":"NORMAL","accountType":"PM_3"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPortfolioMarginProSpanAccountInfoParams params{};
    const auto res = api.get_portfolio_margin_pro_span_account_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/portfolio/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetPortfolioMarginProSpanAccountInfoWithOptionalParams) {
    const std::string example =
        R"json({"uniMMR":"5167.92171923","accountEquity":"122607.35137903","actualEquity":"142607.35137903","accountMaintMargin":"23.72469206","riskUnitMMList":[{"asset":"BTC","uniMaintainUsd":"23.72469206"}],"marginMM":"0.00000000","otherMM":"0.00000000","accountStatus":"NORMAL","accountType":"PM_3"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPortfolioMarginProSpanAccountInfoParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_portfolio_margin_pro_span_account_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetPortfolioMarginProSpanAccountInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetPortfolioMarginProSpanAccountInfoParams params{};
    EXPECT_THROW((void)api.get_portfolio_margin_pro_span_account_info(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetTransferableEarnAssetBalanceForPortfolioMargin) {
    const std::string example = R"json({"asset":"LDUSDT","amount":"0.55"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetTransferableEarnAssetBalanceForPortfolioMarginParams params{
        .asset = "LDUSDT",
        .transfer_type =
            GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::EarnToFuture};
    const auto res = api.get_transferable_earn_asset_balance_for_portfolio_margin(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/earn-asset-balance");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetTransferableEarnAssetBalanceForPortfolioMarginWithOptionalParams) {
    const std::string example = R"json({"asset":"LDUSDT","amount":"0.55"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetTransferableEarnAssetBalanceForPortfolioMarginParams params{
        .asset = "LDUSDT",
        .transfer_type =
            GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::EarnToFuture,
        .recv_window = 5000,
    };
    const auto res = api.get_transferable_earn_asset_balance_for_portfolio_margin(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetTransferableEarnAssetBalanceForPortfolioMarginBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetTransferableEarnAssetBalanceForPortfolioMarginParams params{
        .asset = "LDUSDT",
        .transfer_type =
            GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::EarnToFuture};
    EXPECT_THROW((void)api.get_transferable_earn_asset_balance_for_portfolio_margin(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, PortfolioMarginProBankruptcyLoanRepay) {
    const std::string example = R"json({"tranId":58203331886213500})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PortfolioMarginProBankruptcyLoanRepayParams params{};
    const auto res = api.portfolio_margin_pro_bankruptcy_loan_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/repay");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, PortfolioMarginProBankruptcyLoanRepayWithOptionalParams) {
    const std::string example = R"json({"tranId":58203331886213500})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PortfolioMarginProBankruptcyLoanRepayParams params{
        .recv_window = 5000,
    };
    const auto res = api.portfolio_margin_pro_bankruptcy_loan_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, PortfolioMarginProBankruptcyLoanRepayBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PortfolioMarginProBankruptcyLoanRepayParams params{};
    EXPECT_THROW((void)api.portfolio_margin_pro_bankruptcy_loan_repay(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, QueryPortfolioMarginProBankruptcyLoanAmount) {
    const std::string example = R"json({"asset":"BUSD","amount":"579.45"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginProBankruptcyLoanAmountParams params{};
    const auto res = api.query_portfolio_margin_pro_bankruptcy_loan_amount(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/pmLoan");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryPortfolioMarginProBankruptcyLoanAmountWithOptionalParams) {
    const std::string example = R"json({"asset":"BUSD","amount":"579.45"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginProBankruptcyLoanAmountParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_portfolio_margin_pro_bankruptcy_loan_amount(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryPortfolioMarginProBankruptcyLoanAmountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPortfolioMarginProBankruptcyLoanAmountParams params{};
    EXPECT_THROW((void)api.query_portfolio_margin_pro_bankruptcy_loan_amount(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, QueryPortfolioMarginProBankruptcyLoanRepayHistory) {
    const std::string example =
        R"json({"total":3,"rows":[{"asset":"USDT","amount":"404.80294503","repayTime":1731336427804}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams params{};
    const auto res = api.query_portfolio_margin_pro_bankruptcy_loan_repay_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/pmloan-history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryPortfolioMarginProBankruptcyLoanRepayHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":3,"rows":[{"asset":"USDT","amount":"404.80294503","repayTime":1731336427804}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .size = 10,
        .current = 1,
        .recv_window = 5000,
    };
    const auto res = api.query_portfolio_margin_pro_bankruptcy_loan_repay_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryPortfolioMarginProBankruptcyLoanRepayHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams params{};
    EXPECT_THROW((void)api.query_portfolio_margin_pro_bankruptcy_loan_repay_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, QueryPortfolioMarginProNegativeBalanceInterestHistory) {
    const std::string example =
        R"json([{"asset":"USDT","interest":"24.4440","interestAccruedTime":1670227200000,"interestRate":"0.0001164","principal":"210000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams params{};
    const auto res = api.query_portfolio_margin_pro_negative_balance_interest_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/interest-history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryPortfolioMarginProNegativeBalanceInterestHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"USDT","interest":"24.4440","interestAccruedTime":1670227200000,"interestRate":"0.0001164","principal":"210000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams params{
        .asset = "USDT",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_portfolio_margin_pro_negative_balance_interest_history(params);
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

TEST(RestApiAccountApi, QueryPortfolioMarginProNegativeBalanceInterestHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams params{};
    EXPECT_THROW((void)api.query_portfolio_margin_pro_negative_balance_interest_history(params),
                 common::BadRequestError);
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
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/repay-futures-negative-balance");
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

TEST(RestApiAccountApi, TransferLdusdtRwusdForPortfolioMargin) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TransferLdusdtRwusdForPortfolioMarginParams params{
        .asset = TransferLdusdtRwusdForPortfolioMarginAssetEnum::Ldusdt,
        .transfer_type = TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::EarnToFuture,
        .amount = common::Decimal("1")};
    const auto res = api.transfer_ldusdt_rwusd_for_portfolio_margin(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/earn-asset-transfer");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, TransferLdusdtRwusdForPortfolioMarginWithOptionalParams) {
    const std::string example = R"json({"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TransferLdusdtRwusdForPortfolioMarginParams params{
        .asset = TransferLdusdtRwusdForPortfolioMarginAssetEnum::Ldusdt,
        .transfer_type = TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::EarnToFuture,
        .amount = common::Decimal("1"),
        .recv_window = 5000,
    };
    const auto res = api.transfer_ldusdt_rwusd_for_portfolio_margin(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, TransferLdusdtRwusdForPortfolioMarginBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TransferLdusdtRwusdForPortfolioMarginParams params{
        .asset = TransferLdusdtRwusdForPortfolioMarginAssetEnum::Ldusdt,
        .transfer_type = TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::EarnToFuture,
        .amount = common::Decimal("1")};
    EXPECT_THROW((void)api.transfer_ldusdt_rwusd_for_portfolio_margin(params),
                 common::BadRequestError);
}
