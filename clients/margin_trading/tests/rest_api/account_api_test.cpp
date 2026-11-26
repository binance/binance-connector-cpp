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
#include <binance/margin_trading/rest_api/account_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::margin_trading::rest_api;
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

TEST(RestApiAccountApi, AdjustCrossMarginMaxLeverage) {
    const std::string example = R"json({"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AdjustCrossMarginMaxLeverageParams params{.max_leverage = 3};
    const auto res = api.adjust_cross_margin_max_leverage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/max-leverage");
    EXPECT_NE((rec.query() + "&" + rec.body).find("maxLeverage="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AdjustCrossMarginMaxLeverageBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AdjustCrossMarginMaxLeverageParams params{.max_leverage = 3};
    EXPECT_THROW((void)api.adjust_cross_margin_max_leverage(params), common::BadRequestError);
}

TEST(RestApiAccountApi, DisableIsolatedMarginAccount) {
    const std::string example = R"json({"success":true,"symbol":"BTCUSDT"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DisableIsolatedMarginAccountParams params{.symbol = "BTCUSDT"};
    const auto res = api.disable_isolated_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/isolated/account");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, DisableIsolatedMarginAccountWithOptionalParams) {
    const std::string example = R"json({"success":true,"symbol":"BTCUSDT"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DisableIsolatedMarginAccountParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.disable_isolated_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, DisableIsolatedMarginAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DisableIsolatedMarginAccountParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.disable_isolated_margin_account(params), common::BadRequestError);
}

TEST(RestApiAccountApi, EnableIsolatedMarginAccount) {
    const std::string example = R"json({"success":true,"symbol":"BTCUSDT"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EnableIsolatedMarginAccountParams params{.symbol = "BTCUSDT"};
    const auto res = api.enable_isolated_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/isolated/account");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, EnableIsolatedMarginAccountWithOptionalParams) {
    const std::string example = R"json({"success":true,"symbol":"BTCUSDT"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EnableIsolatedMarginAccountParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.enable_isolated_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, EnableIsolatedMarginAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EnableIsolatedMarginAccountParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.enable_isolated_margin_account(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryIsolatedMarginAccountInfo) {
    const std::string example =
        R"json({"assets":[{"baseAsset":{"asset":"BTC","borrowEnabled":true,"borrowed":"0.00000000","free":"0.00000000","interest":"0.00000000","locked":"0.00000000","netAsset":"0.00000000","netAssetOfBtc":"0.00000000","repayEnabled":true,"totalAsset":"0.00000000"},"quoteAsset":{"asset":"USDT","borrowEnabled":true,"borrowed":"0.00000000","free":"0.00000000","interest":"0.00000000","locked":"0.00000000","netAsset":"0.00000000","netAssetOfBtc":"0.00000000","repayEnabled":true,"totalAsset":"0.00000000"},"symbol":"BTCUSDT","isolatedCreated":true,"enabled":true,"marginLevel":"0.00000000","marginLevelStatus":"EXCESSIVE","marginRatio":"0.00000000","indexPrice":"10000.00000000","liquidatePrice":"1000.00000000","liquidateRate":"1.00000000","tradeEnabled":true}],"totalAssetOfBtc":"0.00000000","totalLiabilityOfBtc":"0.00000000","totalNetAssetOfBtc":"0.00000000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryIsolatedMarginAccountInfoParams params{};
    const auto res = api.query_isolated_margin_account_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/isolated/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryIsolatedMarginAccountInfoWithOptionalParams) {
    const std::string example =
        R"json({"assets":[{"baseAsset":{"asset":"BTC","borrowEnabled":true,"borrowed":"0.00000000","free":"0.00000000","interest":"0.00000000","locked":"0.00000000","netAsset":"0.00000000","netAssetOfBtc":"0.00000000","repayEnabled":true,"totalAsset":"0.00000000"},"quoteAsset":{"asset":"USDT","borrowEnabled":true,"borrowed":"0.00000000","free":"0.00000000","interest":"0.00000000","locked":"0.00000000","netAsset":"0.00000000","netAssetOfBtc":"0.00000000","repayEnabled":true,"totalAsset":"0.00000000"},"symbol":"BTCUSDT","isolatedCreated":true,"enabled":true,"marginLevel":"0.00000000","marginLevelStatus":"EXCESSIVE","marginRatio":"0.00000000","indexPrice":"10000.00000000","liquidatePrice":"1000.00000000","liquidateRate":"1.00000000","tradeEnabled":true}],"totalAssetOfBtc":"0.00000000","totalLiabilityOfBtc":"0.00000000","totalNetAssetOfBtc":"0.00000000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryIsolatedMarginAccountInfoParams params{
        .symbols = "BTCUSDT,BNBUSDT,ADAUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_isolated_margin_account_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbols="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryIsolatedMarginAccountInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryIsolatedMarginAccountInfoParams params{};
    EXPECT_THROW((void)api.query_isolated_margin_account_info(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetBnbBurnStatus) {
    const std::string example = R"json({"spotBNBBurn":true,"interestBNBBurn":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBnbBurnStatusParams params{};
    const auto res = api.get_bnb_burn_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/bnbBurn");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetBnbBurnStatusWithOptionalParams) {
    const std::string example = R"json({"spotBNBBurn":true,"interestBNBBurn":false})json";
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

TEST(RestApiAccountApi, GetSummaryOfMarginAccount) {
    const std::string example =
        R"json({"normalBar":"1.5","marginCallBar":"1.3","forceLiquidationBar":"1.1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSummaryOfMarginAccountParams params{};
    const auto res = api.get_summary_of_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/tradeCoeff");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetSummaryOfMarginAccountWithOptionalParams) {
    const std::string example =
        R"json({"normalBar":"1.5","marginCallBar":"1.3","forceLiquidationBar":"1.1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSummaryOfMarginAccountParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_summary_of_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetSummaryOfMarginAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSummaryOfMarginAccountParams params{};
    EXPECT_THROW((void)api.get_summary_of_margin_account(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryCrossIsolatedMarginCapitalFlow) {
    const std::string example =
        R"json([{"id":123456,"tranId":123123,"timestamp":1691116657000,"asset":"USDT","symbol":"BTCUSDT","type":"BORROW","amount":"101","note":"INSTITUTIONAL_LOAN_TRANSFER"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCrossIsolatedMarginCapitalFlowParams params{};
    const auto res = api.query_cross_isolated_margin_capital_flow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/capital-flow");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryCrossIsolatedMarginCapitalFlowWithOptionalParams) {
    const std::string example =
        R"json([{"id":123456,"tranId":123123,"timestamp":1691116657000,"asset":"USDT","symbol":"BTCUSDT","type":"BORROW","amount":"101","note":"INSTITUTIONAL_LOAN_TRANSFER"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCrossIsolatedMarginCapitalFlowParams params{
        .asset = "USDT",
        .symbol = "BTCUSDT",
        .type = QueryCrossIsolatedMarginCapitalFlowTypeEnum::Transfer,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .from_id = 1,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_cross_isolated_margin_capital_flow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryCrossIsolatedMarginCapitalFlowBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCrossIsolatedMarginCapitalFlowParams params{};
    EXPECT_THROW((void)api.query_cross_isolated_margin_capital_flow(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, QueryCrossMarginAccountDetails) {
    const std::string example =
        R"json({"created":true,"borrowEnabled":true,"marginLevel":"11.64405625","collateralMarginLevel":"3.2","totalAssetOfBtc":"6.82728457","totalLiabilityOfBtc":"0.58633215","totalNetAssetOfBtc":"6.24095242","TotalCollateralValueInUSDT":"5.82728457","tradeEnabled":true,"transferInEnabled":true,"transferOutEnabled":true,"accountType":"MARGIN_1","userAssets":[{"asset":"BTC","borrowed":"0.00000000","free":"0.00499500","interest":"0.00000000","locked":"0.00000000","netAsset":"0.00499500"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCrossMarginAccountDetailsParams params{};
    const auto res = api.query_cross_margin_account_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryCrossMarginAccountDetailsWithOptionalParams) {
    const std::string example =
        R"json({"created":true,"borrowEnabled":true,"marginLevel":"11.64405625","collateralMarginLevel":"3.2","totalAssetOfBtc":"6.82728457","totalLiabilityOfBtc":"0.58633215","totalNetAssetOfBtc":"6.24095242","TotalCollateralValueInUSDT":"5.82728457","tradeEnabled":true,"transferInEnabled":true,"transferOutEnabled":true,"accountType":"MARGIN_1","userAssets":[{"asset":"BTC","borrowed":"0.00000000","free":"0.00499500","interest":"0.00000000","locked":"0.00000000","netAsset":"0.00499500"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCrossMarginAccountDetailsParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_cross_margin_account_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryCrossMarginAccountDetailsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCrossMarginAccountDetailsParams params{};
    EXPECT_THROW((void)api.query_cross_margin_account_details(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryCrossMarginFeeData) {
    const std::string example =
        R"json([{"vipLevel":0,"coin":"BTC","transferIn":true,"borrowable":true,"dailyInterest":"0.00026125","yearlyInterest":"0.0953","borrowLimit":"180","marginablePairs":["BNBBTC"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCrossMarginFeeDataParams params{};
    const auto res = api.query_cross_margin_fee_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/crossMarginData");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryCrossMarginFeeDataWithOptionalParams) {
    const std::string example =
        R"json([{"vipLevel":0,"coin":"BTC","transferIn":true,"borrowable":true,"dailyInterest":"0.00026125","yearlyInterest":"0.0953","borrowLimit":"180","marginablePairs":["BNBBTC"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCrossMarginFeeDataParams params{
        .vip_level = 1,
        .coin = "BTC",
        .recv_window = 5000,
    };
    const auto res = api.query_cross_margin_fee_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("vipLevel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryCrossMarginFeeDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCrossMarginFeeDataParams params{};
    EXPECT_THROW((void)api.query_cross_margin_fee_data(params), common::BadRequestError);
}

TEST(RestApiAccountApi, QueryEnabledIsolatedMarginAccountLimit) {
    const std::string example = R"json({"enabledAccount":5,"maxAccount":20})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryEnabledIsolatedMarginAccountLimitParams params{};
    const auto res = api.query_enabled_isolated_margin_account_limit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/isolated/accountLimit");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryEnabledIsolatedMarginAccountLimitWithOptionalParams) {
    const std::string example = R"json({"enabledAccount":5,"maxAccount":20})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryEnabledIsolatedMarginAccountLimitParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_enabled_isolated_margin_account_limit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryEnabledIsolatedMarginAccountLimitBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryEnabledIsolatedMarginAccountLimitParams params{};
    EXPECT_THROW((void)api.query_enabled_isolated_margin_account_limit(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, QueryIsolatedMarginFeeData) {
    const std::string example =
        R"json([{"vipLevel":0,"symbol":"BTCUSDT","leverage":"10","data":[{"coin":"BTC","dailyInterest":"0.00026125","borrowLimit":"270"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryIsolatedMarginFeeDataParams params{};
    const auto res = api.query_isolated_margin_fee_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/isolatedMarginData");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryIsolatedMarginFeeDataWithOptionalParams) {
    const std::string example =
        R"json([{"vipLevel":0,"symbol":"BTCUSDT","leverage":"10","data":[{"coin":"BTC","dailyInterest":"0.00026125","borrowLimit":"270"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryIsolatedMarginFeeDataParams params{
        .vip_level = 1,
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_isolated_margin_fee_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("vipLevel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, QueryIsolatedMarginFeeDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryIsolatedMarginFeeDataParams params{};
    EXPECT_THROW((void)api.query_isolated_margin_fee_data(params), common::BadRequestError);
}
