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
#include <binance/derivatives_trading_usds_futures/rest_api/account_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_usds_futures::rest_api;
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

TEST(RestApiAccountApi, AccountInformationV2) {
    const std::string example =
        R"json({"feeTier":0,"feeBurn":true,"canTrade":true,"canDeposit":true,"canWithdraw":true,"updateTime":0,"multiAssetsMargin":true,"tradeGroupId":-1,"totalInitialMargin":"0.00000000","totalMaintMargin":"0.00000000","totalWalletBalance":"126.72469206","totalUnrealizedProfit":"0.00000000","totalMarginBalance":"126.72469206","totalPositionInitialMargin":"0.00000000","totalOpenOrderInitialMargin":"0.00000000","totalCrossWalletBalance":"126.72469206","totalCrossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"126.72469206","assets":[{"asset":"USDT","walletBalance":"23.72469206","unrealizedProfit":"0.00000000","marginBalance":"23.72469206","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"100","isolated":true,"entryPrice":"0.00000","maxNotional":"250000","bidNotional":"0","askNotional":"0","positionSide":"BOTH","positionAmt":"0","updateTime":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInformationV2Params params{};
    const auto res = api.account_information_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v2/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInformationV2WithOptionalParams) {
    const std::string example =
        R"json({"feeTier":0,"feeBurn":true,"canTrade":true,"canDeposit":true,"canWithdraw":true,"updateTime":0,"multiAssetsMargin":true,"tradeGroupId":-1,"totalInitialMargin":"0.00000000","totalMaintMargin":"0.00000000","totalWalletBalance":"126.72469206","totalUnrealizedProfit":"0.00000000","totalMarginBalance":"126.72469206","totalPositionInitialMargin":"0.00000000","totalOpenOrderInitialMargin":"0.00000000","totalCrossWalletBalance":"126.72469206","totalCrossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"126.72469206","assets":[{"asset":"USDT","walletBalance":"23.72469206","unrealizedProfit":"0.00000000","marginBalance":"23.72469206","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"100","isolated":true,"entryPrice":"0.00000","maxNotional":"250000","bidNotional":"0","askNotional":"0","positionSide":"BOTH","positionAmt":"0","updateTime":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInformationV2Params params{
        .recv_window = 5000,
    };
    const auto res = api.account_information_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInformationV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountInformationV2Params params{};
    EXPECT_THROW((void)api.account_information_v2(params), common::BadRequestError);
}

TEST(RestApiAccountApi, AccountInformationV3) {
    const std::string example =
        R"json({"totalInitialMargin":"0.00000000","totalMaintMargin":"0.00000000","totalWalletBalance":"126.72469206","totalUnrealizedProfit":"0.00000000","totalMarginBalance":"126.72469206","totalPositionInitialMargin":"0.00000000","totalOpenOrderInitialMargin":"0.00000000","totalCrossWalletBalance":"126.72469206","totalCrossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"126.72469206","assets":[{"asset":"USDT","walletBalance":"23.72469206","unrealizedProfit":"0.00000000","marginBalance":"23.72469206","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","positionSide":"BOTH","positionAmt":"1.000","unrealizedProfit":"0.00000000","isolatedMargin":"0.00000000","notional":"0","isolatedWallet":"0","initialMargin":"0","maintMargin":"0","updateTime":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInformationV3Params params{};
    const auto res = api.account_information_v3(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v3/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInformationV3WithOptionalParams) {
    const std::string example =
        R"json({"totalInitialMargin":"0.00000000","totalMaintMargin":"0.00000000","totalWalletBalance":"126.72469206","totalUnrealizedProfit":"0.00000000","totalMarginBalance":"126.72469206","totalPositionInitialMargin":"0.00000000","totalOpenOrderInitialMargin":"0.00000000","totalCrossWalletBalance":"126.72469206","totalCrossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"126.72469206","assets":[{"asset":"USDT","walletBalance":"23.72469206","unrealizedProfit":"0.00000000","marginBalance":"23.72469206","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","positionSide":"BOTH","positionAmt":"1.000","unrealizedProfit":"0.00000000","isolatedMargin":"0.00000000","notional":"0","isolatedWallet":"0","initialMargin":"0","maintMargin":"0","updateTime":0}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInformationV3Params params{
        .recv_window = 5000,
    };
    const auto res = api.account_information_v3(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInformationV3BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountInformationV3Params params{};
    EXPECT_THROW((void)api.account_information_v3(params), common::BadRequestError);
}

TEST(RestApiAccountApi, FuturesAccountBalanceV2) {
    const std::string example =
        R"json([{"accountAlias":"SgsR","asset":"USDT","balance":"122607.35137903","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1617939110373}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesAccountBalanceV2Params params{};
    const auto res = api.futures_account_balance_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v2/balance");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FuturesAccountBalanceV2WithOptionalParams) {
    const std::string example =
        R"json([{"accountAlias":"SgsR","asset":"USDT","balance":"122607.35137903","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1617939110373}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesAccountBalanceV2Params params{
        .recv_window = 5000,
    };
    const auto res = api.futures_account_balance_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FuturesAccountBalanceV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FuturesAccountBalanceV2Params params{};
    EXPECT_THROW((void)api.futures_account_balance_v2(params), common::BadRequestError);
}

TEST(RestApiAccountApi, FuturesAccountBalanceV3) {
    const std::string example =
        R"json([{"accountAlias":"SgsR","asset":"USDT","balance":"122607.35137903","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1617939110373}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesAccountBalanceV3Params params{};
    const auto res = api.futures_account_balance_v3(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v3/balance");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FuturesAccountBalanceV3WithOptionalParams) {
    const std::string example =
        R"json([{"accountAlias":"SgsR","asset":"USDT","balance":"122607.35137903","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1617939110373}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesAccountBalanceV3Params params{
        .recv_window = 5000,
    };
    const auto res = api.futures_account_balance_v3(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FuturesAccountBalanceV3BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FuturesAccountBalanceV3Params params{};
    EXPECT_THROW((void)api.futures_account_balance_v3(params), common::BadRequestError);
}

TEST(RestApiAccountApi, FuturesAccountConfiguration) {
    const std::string example =
        R"json({"feeTier":0,"canTrade":true,"canDeposit":true,"canWithdraw":true,"dualSidePosition":true,"updateTime":0,"multiAssetsMargin":false,"tradeGroupId":-1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesAccountConfigurationParams params{};
    const auto res = api.futures_account_configuration(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/accountConfig");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FuturesAccountConfigurationWithOptionalParams) {
    const std::string example =
        R"json({"feeTier":0,"canTrade":true,"canDeposit":true,"canWithdraw":true,"dualSidePosition":true,"updateTime":0,"multiAssetsMargin":false,"tradeGroupId":-1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesAccountConfigurationParams params{
        .recv_window = 5000,
    };
    const auto res = api.futures_account_configuration(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FuturesAccountConfigurationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FuturesAccountConfigurationParams params{};
    EXPECT_THROW((void)api.futures_account_configuration(params), common::BadRequestError);
}

TEST(RestApiAccountApi, FuturesTradingQuantitativeRulesIndicators) {
    const std::string example =
        R"json({"indicators":{"BTCUSDT":[{"isLocked":true,"plannedRecoverTime":1545741270000,"indicator":"UFR","value":0.05,"triggerValue":0.995}],"ETHUSDT":[{"isLocked":true,"plannedRecoverTime":1545741270000,"indicator":"UFR","value":0.05,"triggerValue":0.995}],"ACCOUNT":[{"indicator":"TMV","value":10,"triggerValue":1,"plannedRecoverTime":1644919865000,"isLocked":true}]},"updateTime":1644913304748})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesTradingQuantitativeRulesIndicatorsParams params{};
    const auto res = api.futures_trading_quantitative_rules_indicators(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/apiTradingStatus");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FuturesTradingQuantitativeRulesIndicatorsWithOptionalParams) {
    const std::string example =
        R"json({"indicators":{"BTCUSDT":[{"isLocked":true,"plannedRecoverTime":1545741270000,"indicator":"UFR","value":0.05,"triggerValue":0.995}],"ETHUSDT":[{"isLocked":true,"plannedRecoverTime":1545741270000,"indicator":"UFR","value":0.05,"triggerValue":0.995}],"ACCOUNT":[{"indicator":"TMV","value":10,"triggerValue":1,"plannedRecoverTime":1644919865000,"isLocked":true}]},"updateTime":1644913304748})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesTradingQuantitativeRulesIndicatorsParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.futures_trading_quantitative_rules_indicators(params);
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

TEST(RestApiAccountApi, FuturesTradingQuantitativeRulesIndicatorsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FuturesTradingQuantitativeRulesIndicatorsParams params{};
    EXPECT_THROW((void)api.futures_trading_quantitative_rules_indicators(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetBnbBurnStatus) {
    const std::string example = R"json({"feeBurn":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBnbBurnStatusParams params{};
    const auto res = api.get_bnb_burn_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/feeBurn");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetBnbBurnStatusWithOptionalParams) {
    const std::string example = R"json({"feeBurn":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBnbBurnStatusParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_bnb_burn_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetBnbBurnStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBnbBurnStatusParams params{};
    EXPECT_THROW((void)api.get_bnb_burn_status(params), common::BadRequestError);
}

TEST(RestApiAccountApi, ToggleBnbBurnOnFuturesTrade) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ToggleBnbBurnOnFuturesTradeParams params{.fee_burn = "true"};
    const auto res = api.toggle_bnb_burn_on_futures_trade(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/feeBurn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("feeBurn="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ToggleBnbBurnOnFuturesTradeWithOptionalParams) {
    const std::string example = R"json({"code":200,"msg":"success"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ToggleBnbBurnOnFuturesTradeParams params{
        .fee_burn = "true",
        .recv_window = 5000,
    };
    const auto res = api.toggle_bnb_burn_on_futures_trade(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("feeBurn="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, ToggleBnbBurnOnFuturesTradeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ToggleBnbBurnOnFuturesTradeParams params{.fee_burn = "true"};
    EXPECT_THROW((void)api.toggle_bnb_burn_on_futures_trade(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetCurrentMultiAssetsMode) {
    const std::string example = R"json({"multiAssetsMargin":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCurrentMultiAssetsModeParams params{};
    const auto res = api.get_current_multi_assets_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/multiAssetsMargin");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCurrentMultiAssetsModeWithOptionalParams) {
    const std::string example = R"json({"multiAssetsMargin":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCurrentMultiAssetsModeParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_current_multi_assets_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCurrentMultiAssetsModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCurrentMultiAssetsModeParams params{};
    EXPECT_THROW((void)api.get_current_multi_assets_mode(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetCurrentPositionMode) {
    const std::string example = R"json({"dualSidePosition":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCurrentPositionModeParams params{};
    const auto res = api.get_current_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/positionSide/dual");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCurrentPositionModeWithOptionalParams) {
    const std::string example = R"json({"dualSidePosition":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCurrentPositionModeParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_current_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCurrentPositionModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCurrentPositionModeParams params{};
    EXPECT_THROW((void)api.get_current_position_mode(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesOrderHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesOrderHistoryParams params{.start_time = 1623319461670,
                                                           .end_time = 1641782889000};
    const auto res = api.get_download_id_for_futures_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/order/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesOrderHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_futures_order_history(params);
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

TEST(RestApiAccountApi, GetDownloadIdForFuturesOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesOrderHistoryParams params{.start_time = 1623319461670,
                                                           .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_futures_order_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTradeHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTradeHistoryParams params{.start_time = 1623319461670,
                                                           .end_time = 1641782889000};
    const auto res = api.get_download_id_for_futures_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/trade/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTradeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTradeHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_futures_trade_history(params);
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

TEST(RestApiAccountApi, GetDownloadIdForFuturesTradeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTradeHistoryParams params{.start_time = 1623319461670,
                                                           .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_futures_trade_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTransactionHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTransactionHistoryParams params{.start_time = 1623319461670,
                                                                 .end_time = 1641782889000};
    const auto res = api.get_download_id_for_futures_transaction_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/income/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTransactionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTransactionHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_futures_transaction_history(params);
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

TEST(RestApiAccountApi, GetDownloadIdForFuturesTransactionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTransactionHistoryParams params{.start_time = 1623319461670,
                                                                 .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_futures_transaction_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetFuturesOrderHistoryDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesOrderHistoryDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    const auto res = api.get_futures_order_history_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/order/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetFuturesOrderHistoryDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesOrderHistoryDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_futures_order_history_download_link_by_id(params);
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

TEST(RestApiAccountApi, GetFuturesOrderHistoryDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesOrderHistoryDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    EXPECT_THROW((void)api.get_futures_order_history_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetFuturesTradeDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"www.binance.com","notified":false,"expirationTimestamp":1645009771000,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesTradeDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    const auto res = api.get_futures_trade_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/trade/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetFuturesTradeDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"www.binance.com","notified":false,"expirationTimestamp":1645009771000,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesTradeDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_futures_trade_download_link_by_id(params);
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

TEST(RestApiAccountApi, GetFuturesTradeDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesTradeDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    EXPECT_THROW((void)api.get_futures_trade_download_link_by_id(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetFuturesTransactionHistoryDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"www.binance.com","notified":false,"expirationTimestamp":1645009771000,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesTransactionHistoryDownloadLinkByIdParams params{.download_id =
                                                                        "545923594199212032"};
    const auto res = api.get_futures_transaction_history_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/income/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetFuturesTransactionHistoryDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"www.binance.com","notified":false,"expirationTimestamp":1645009771000,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesTransactionHistoryDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_futures_transaction_history_download_link_by_id(params);
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

TEST(RestApiAccountApi, GetFuturesTransactionHistoryDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesTransactionHistoryDownloadLinkByIdParams params{.download_id =
                                                                        "545923594199212032"};
    EXPECT_THROW((void)api.get_futures_transaction_history_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetIncomeHistory) {
    const std::string example =
        R"json([{"symbol":"","incomeType":"TRANSFER","income":"-0.37500000","asset":"USDT","info":"TRANSFER","time":1570608000000,"tranId":9689322392,"tradeId":""}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetIncomeHistoryParams params{};
    const auto res = api.get_income_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/income");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetIncomeHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"","incomeType":"TRANSFER","income":"-0.37500000","asset":"USDT","info":"TRANSFER","time":1570608000000,"tranId":9689322392,"tradeId":""}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetIncomeHistoryParams params{
        .symbol = "BTCUSDT",
        .income_type = GetIncomeHistoryIncomeTypeEnum::Transfer,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
        .recv_window = 5000,
    };
    const auto res = api.get_income_history(params);
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

TEST(RestApiAccountApi, GetIncomeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetIncomeHistoryParams params{};
    EXPECT_THROW((void)api.get_income_history(params), common::BadRequestError);
}

TEST(RestApiAccountApi, NotionalAndLeverageBrackets) {
    const std::string example =
        R"json([{"symbol":"ETHUSDT","notionalCoef":1.5,"brackets":[]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NotionalAndLeverageBracketsParams params{};
    const auto res = api.notional_and_leverage_brackets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/leverageBracket");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, NotionalAndLeverageBracketsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"ETHUSDT","notionalCoef":1.5,"brackets":[]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NotionalAndLeverageBracketsParams params{
        .symbol = "ETHUSDT",
        .recv_window = 5000,
    };
    const auto res = api.notional_and_leverage_brackets(params);
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

TEST(RestApiAccountApi, NotionalAndLeverageBracketsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NotionalAndLeverageBracketsParams params{};
    EXPECT_THROW((void)api.notional_and_leverage_brackets(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryUserRateLimit) {
    const std::string example =
        R"json([{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":10000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserRateLimitParams params{};
    const auto res = api.query_user_rate_limit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/rateLimit/order");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryUserRateLimitWithOptionalParams) {
    const std::string example =
        R"json([{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":10000}])json";
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

TEST(RestApiAccountApi, SymbolConfiguration) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","marginType":"CROSSED","isAutoAddMargin":false,"leverage":21,"maxNotionalValue":"1000000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolConfigurationParams params{};
    const auto res = api.symbol_configuration(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/symbolConfig");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, SymbolConfigurationWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","marginType":"CROSSED","isAutoAddMargin":false,"leverage":21,"maxNotionalValue":"1000000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolConfigurationParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.symbol_configuration(params);
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

TEST(RestApiAccountApi, SymbolConfigurationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SymbolConfigurationParams params{};
    EXPECT_THROW((void)api.symbol_configuration(params), common::BadRequestError);
}

TEST(RestApiAccountApi, UserCommissionRate) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","makerCommissionRate":"0.0002","takerCommissionRate":"0.0004","rpiCommissionRate":"0.00005"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserCommissionRateParams params{.symbol = "BTCUSDT"};
    const auto res = api.user_commission_rate(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/commissionRate");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, UserCommissionRateWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","makerCommissionRate":"0.0002","takerCommissionRate":"0.0004","rpiCommissionRate":"0.00005"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserCommissionRateParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.user_commission_rate(params);
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

TEST(RestApiAccountApi, UserCommissionRateBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UserCommissionRateParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.user_commission_rate(params), common::BadRequestError);
}
