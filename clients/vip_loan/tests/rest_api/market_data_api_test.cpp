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
#include <binance/vip_loan/rest_api/market_data_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::vip_loan::rest_api;
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

MarketDataApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return MarketDataApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiMarketDataApi, GetBorrowInterestRate) {
    const std::string example =
        R"json([{"asset":"BUSD","flexibleDailyInterestRate":"0.001503","flexibleYearlyInterestRate":"0.548595","time":1577233578000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBorrowInterestRateParams params{.loan_coin = "BTC"};
    const auto res = api.get_borrow_interest_rate(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/request/interestRate");
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetBorrowInterestRateWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"BUSD","flexibleDailyInterestRate":"0.001503","flexibleYearlyInterestRate":"0.548595","time":1577233578000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetBorrowInterestRateParams params{
        .loan_coin = "BTC",
        .recv_window = 5000,
    };
    const auto res = api.get_borrow_interest_rate(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetBorrowInterestRateBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetBorrowInterestRateParams params{.loan_coin = "BTC"};
    EXPECT_THROW((void)api.get_borrow_interest_rate(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetCollateralAssetData) {
    const std::string example =
        R"json({"rows":[{"collateralCoin":"BUSD","_1stCollateralRatio":"100%","_1stCollateralRange":"1-10000000","_2ndCollateralRatio":"80%","_2ndCollateralRange":"10000000-100000000","_3rdCollateralRatio":"60%","_3rdCollateralRange":"100000000-1000000000","_4thCollateralRatio":"0%","_4thCollateralRange":">10000000000"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCollateralAssetDataParams params{};
    const auto res = api.get_collateral_asset_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/collateral/data");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetCollateralAssetDataWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"collateralCoin":"BUSD","_1stCollateralRatio":"100%","_1stCollateralRange":"1-10000000","_2ndCollateralRatio":"80%","_2ndCollateralRange":"10000000-100000000","_3rdCollateralRatio":"60%","_3rdCollateralRange":"100000000-1000000000","_4thCollateralRatio":"0%","_4thCollateralRange":">10000000000"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCollateralAssetDataParams params{
        .collateral_coin = "BUSD",
        .recv_window = 5000,
    };
    const auto res = api.get_collateral_asset_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetCollateralAssetDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCollateralAssetDataParams params{};
    EXPECT_THROW((void)api.get_collateral_asset_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetLoanableAssetsData) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","_flexibleDailyInterestRate":"0.001503","_flexibleYearlyInterestRate":"0.548595","_30dDailyInterestRate":"0.000136","_30dYearlyInterestRate":"0.03450","_60dDailyInterestRate":"0.000145","_60dYearlyInterestRate":"0.04103","minLimit":"100","maxLimit":"1000000","vipLevel":1}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLoanableAssetsDataParams params{};
    const auto res = api.get_loanable_assets_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/loanable/data");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetLoanableAssetsDataWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","_flexibleDailyInterestRate":"0.001503","_flexibleYearlyInterestRate":"0.548595","_30dDailyInterestRate":"0.000136","_30dYearlyInterestRate":"0.03450","_60dDailyInterestRate":"0.000145","_60dYearlyInterestRate":"0.04103","minLimit":"100","maxLimit":"1000000","vipLevel":1}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetLoanableAssetsDataParams params{
        .loan_coin = "BUSD",
        .vip_level = 1,
        .recv_window = 5000,
    };
    const auto res = api.get_loanable_assets_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("vipLevel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetLoanableAssetsDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetLoanableAssetsDataParams params{};
    EXPECT_THROW((void)api.get_loanable_assets_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetVIPLoanInterestRateHistory) {
    const std::string example =
        R"json({"rows":[{"coin":"USDT","annualizedInterestRate":"0.0647","time":1575018510000}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetVIPLoanInterestRateHistoryParams params{.coin = "USDT", .recv_window = 5000};
    const auto res = api.get_vip_loan_interest_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/interestRateHistory");
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetVIPLoanInterestRateHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"coin":"USDT","annualizedInterestRate":"0.0647","time":1575018510000}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetVIPLoanInterestRateHistoryParams params{
        .coin = "USDT",
        .recv_window = 5000,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .limit = 10,
    };
    const auto res = api.get_vip_loan_interest_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetVIPLoanInterestRateHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetVIPLoanInterestRateHistoryParams params{.coin = "USDT", .recv_window = 5000};
    EXPECT_THROW((void)api.get_vip_loan_interest_rate_history(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryVIPLoanFixedRateMarket) {
    const std::string example =
        R"json({"total":25,"rows":[{"requestId":1234567890,"requestNo":100001,"coin":"USDT","interestRate":"0.05","duration":30,"minimumAmount":"100","availableAmount":"1000000","estimatedInterest":"4109.59"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryVIPLoanFixedRateMarketParams params{.loan_coin = "USDT"};
    const auto res = api.query_vip_loan_fixed_rate_market(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/fixed/market");
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryVIPLoanFixedRateMarketWithOptionalParams) {
    const std::string example =
        R"json({"total":25,"rows":[{"requestId":1234567890,"requestNo":100001,"coin":"USDT","interestRate":"0.05","duration":30,"minimumAmount":"100","availableAmount":"1000000","estimatedInterest":"4109.59"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryVIPLoanFixedRateMarketParams params{
        .loan_coin = "USDT",
        .duration = 30,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_vip_loan_fixed_rate_market(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("duration="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryVIPLoanFixedRateMarketBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryVIPLoanFixedRateMarketParams params{.loan_coin = "USDT"};
    EXPECT_THROW((void)api.query_vip_loan_fixed_rate_market(params), common::BadRequestError);
}
