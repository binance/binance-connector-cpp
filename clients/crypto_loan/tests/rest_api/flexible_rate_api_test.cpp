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
#include <binance/crypto_loan/rest_api/flexible_rate_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::crypto_loan::rest_api;
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

FlexibleRateApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return FlexibleRateApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiFlexibleRateApi, CheckCollateralRepayRate) {
    const std::string example =
        R"json({"loanCoin":"BUSD","collateralCoin":"BNB","rate":"300.36781234"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CheckCollateralRepayRateParams params{.loan_coin = "BUSD", .collateral_coin = "BNB"};
    const auto res = api.check_collateral_repay_rate(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/repay/rate");
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, CheckCollateralRepayRateWithOptionalParams) {
    const std::string example =
        R"json({"loanCoin":"BUSD","collateralCoin":"BNB","rate":"300.36781234"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CheckCollateralRepayRateParams params{
        .loan_coin = "BUSD",
        .collateral_coin = "BNB",
        .recv_window = 5000,
    };
    const auto res = api.check_collateral_repay_rate(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, CheckCollateralRepayRateBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CheckCollateralRepayRateParams params{.loan_coin = "BUSD", .collateral_coin = "BNB"};
    EXPECT_THROW((void)api.check_collateral_repay_rate(params), common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, FlexibleLoanAdjustLtv) {
    const std::string example =
        R"json({"loanCoin":"BUSD","collateralCoin":"BNB","direction":"ADDITIONAL","adjustmentAmount":"5.235","currentLTV":"0.52","status":"Succeeds"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FlexibleLoanAdjustLtvParams params{.loan_coin = "BUSD",
                                             .collateral_coin = "BNB",
                                             .adjustment_amount = common::Decimal("1"),
                                             .direction =
                                                 FlexibleLoanAdjustLtvDirectionEnum::Additional};
    const auto res = api.flexible_loan_adjust_ltv(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/adjust/ltv");
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("adjustmentAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("direction="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, FlexibleLoanAdjustLtvWithOptionalParams) {
    const std::string example =
        R"json({"loanCoin":"BUSD","collateralCoin":"BNB","direction":"ADDITIONAL","adjustmentAmount":"5.235","currentLTV":"0.52","status":"Succeeds"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FlexibleLoanAdjustLtvParams params{
        .loan_coin = "BUSD",
        .collateral_coin = "BNB",
        .adjustment_amount = common::Decimal("1"),
        .direction = FlexibleLoanAdjustLtvDirectionEnum::Additional,
        .recv_window = 5000,
    };
    const auto res = api.flexible_loan_adjust_ltv(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("adjustmentAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("direction="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, FlexibleLoanAdjustLtvBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FlexibleLoanAdjustLtvParams params{.loan_coin = "BUSD",
                                             .collateral_coin = "BNB",
                                             .adjustment_amount = common::Decimal("1"),
                                             .direction =
                                                 FlexibleLoanAdjustLtvDirectionEnum::Additional};
    EXPECT_THROW((void)api.flexible_loan_adjust_ltv(params), common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, FlexibleLoanBorrow) {
    const std::string example =
        R"json({"loanCoin":"BUSD","loanAmount":"100.5","collateralCoin":"BNB","collateralAmount":"50.5","status":"Succeeds"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FlexibleLoanBorrowParams params{.loan_coin = "BUSD", .collateral_coin = "BNB"};
    const auto res = api.flexible_loan_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/borrow");
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, FlexibleLoanBorrowWithOptionalParams) {
    const std::string example =
        R"json({"loanCoin":"BUSD","loanAmount":"100.5","collateralCoin":"BNB","collateralAmount":"50.5","status":"Succeeds"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FlexibleLoanBorrowParams params{
        .loan_coin = "BUSD",
        .collateral_coin = "BNB",
        .loan_amount = common::Decimal("1"),
        .collateral_amount = common::Decimal("1"),
        .recv_window = 5000,
    };
    const auto res = api.flexible_loan_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, FlexibleLoanBorrowBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FlexibleLoanBorrowParams params{.loan_coin = "BUSD", .collateral_coin = "BNB"};
    EXPECT_THROW((void)api.flexible_loan_borrow(params), common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, FlexibleLoanRepay) {
    const std::string example =
        R"json({"loanCoin":"BUSD","collateralCoin":"BNB","remainingDebt":"100.5","remainingCollateral":"5.253","fullRepayment":false,"currentLTV":"0.25","repayStatus":"REPAID"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FlexibleLoanRepayParams params{
        .loan_coin = "BUSD", .collateral_coin = "BNB", .repay_amount = common::Decimal("1")};
    const auto res = api.flexible_loan_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/repay");
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("repayAmount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, FlexibleLoanRepayWithOptionalParams) {
    const std::string example =
        R"json({"loanCoin":"BUSD","collateralCoin":"BNB","remainingDebt":"100.5","remainingCollateral":"5.253","fullRepayment":false,"currentLTV":"0.25","repayStatus":"REPAID"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FlexibleLoanRepayParams params{
        .loan_coin = "BUSD",
        .collateral_coin = "BNB",
        .repay_amount = common::Decimal("1"),
        .collateral_return = true,
        .full_repayment = false,
        .repayment_type = FlexibleLoanRepayRepaymentTypeEnum::RepaymentType1,
        .recv_window = 5000,
    };
    const auto res = api.flexible_loan_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("repayAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralReturn="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fullRepayment="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("repaymentType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, FlexibleLoanRepayBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FlexibleLoanRepayParams params{
        .loan_coin = "BUSD", .collateral_coin = "BNB", .repay_amount = common::Decimal("1")};
    EXPECT_THROW((void)api.flexible_loan_repay(params), common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanAssetsData) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","flexibleInterestRate":"0.00000491","flexibleMinLimit":"100","flexibleMaxLimit":"1000000"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanAssetsDataParams params{};
    const auto res = api.get_flexible_loan_assets_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/loanable/data");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanAssetsDataWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","flexibleInterestRate":"0.00000491","flexibleMinLimit":"100","flexibleMaxLimit":"1000000"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanAssetsDataParams params{
        .loan_coin = "BUSD",
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_loan_assets_data(params);
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

TEST(RestApiFlexibleRateApi, GetFlexibleLoanAssetsDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleLoanAssetsDataParams params{};
    EXPECT_THROW((void)api.get_flexible_loan_assets_data(params), common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanBorrowHistory) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","initialLoanAmount":"10000","collateralCoin":"BNB","initialCollateralAmount":"49.27565492","borrowTime":1575018510000,"status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanBorrowHistoryParams params{};
    const auto res = api.get_flexible_loan_borrow_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/borrow/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanBorrowHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","initialLoanAmount":"10000","collateralCoin":"BNB","initialCollateralAmount":"49.27565492","borrowTime":1575018510000,"status":"SUCCESS"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanBorrowHistoryParams params{
        .loan_coin = "BUSD",
        .collateral_coin = "BNB",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_loan_borrow_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanBorrowHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleLoanBorrowHistoryParams params{};
    EXPECT_THROW((void)api.get_flexible_loan_borrow_history(params), common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanCollateralAssetsData) {
    const std::string example =
        R"json({"rows":[{"collateralCoin":"BNB","initialLTV":"0.65","marginCallLTV":"0.75","liquidationLTV":"0.83","maxLimit":"1000000"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanCollateralAssetsDataParams params{};
    const auto res = api.get_flexible_loan_collateral_assets_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/collateral/data");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanCollateralAssetsDataWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"collateralCoin":"BNB","initialLTV":"0.65","marginCallLTV":"0.75","liquidationLTV":"0.83","maxLimit":"1000000"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanCollateralAssetsDataParams params{
        .collateral_coin = "BNB",
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_loan_collateral_assets_data(params);
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

TEST(RestApiFlexibleRateApi, GetFlexibleLoanCollateralAssetsDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleLoanCollateralAssetsDataParams params{};
    EXPECT_THROW((void)api.get_flexible_loan_collateral_assets_data(params),
                 common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanInterestRateHistory) {
    const std::string example =
        R"json({"rows":[{"coin":"USDT","annualizedInterestRate":"0.0647","time":1575018510000}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanInterestRateHistoryParams params{.coin = "USDT", .recv_window = 5000};
    const auto res = api.get_flexible_loan_interest_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/interestRateHistory");
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanInterestRateHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"coin":"USDT","annualizedInterestRate":"0.0647","time":1575018510000}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanInterestRateHistoryParams params{
        .coin = "USDT",
        .recv_window = 5000,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .limit = 10,
    };
    const auto res = api.get_flexible_loan_interest_rate_history(params);
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

TEST(RestApiFlexibleRateApi, GetFlexibleLoanInterestRateHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleLoanInterestRateHistoryParams params{.coin = "USDT", .recv_window = 5000};
    EXPECT_THROW((void)api.get_flexible_loan_interest_rate_history(params),
                 common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanLiquidationHistory) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","liquidationDebt":"10000","collateralCoin":"BNB","liquidationCollateralAmount":"123","returnCollateralAmount":"0.2","liquidationFee":"1.2","liquidationStartingPrice":"49.27565492","liquidationStartingTime":1575018510000,"status":"Liquidated"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanLiquidationHistoryParams params{};
    const auto res = api.get_flexible_loan_liquidation_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/liquidation/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanLiquidationHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","liquidationDebt":"10000","collateralCoin":"BNB","liquidationCollateralAmount":"123","returnCollateralAmount":"0.2","liquidationFee":"1.2","liquidationStartingPrice":"49.27565492","liquidationStartingTime":1575018510000,"status":"Liquidated"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanLiquidationHistoryParams params{
        .loan_coin = "BUSD",
        .collateral_coin = "BNB",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_loan_liquidation_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanLiquidationHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleLoanLiquidationHistoryParams params{};
    EXPECT_THROW((void)api.get_flexible_loan_liquidation_history(params), common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanLtvAdjustmentHistory) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","collateralCoin":"BNB","direction":"ADDITIONAL","collateralAmount":"5.235","preLTV":"0.78","afterLTV":"0.56","adjustTime":1575018510000}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanLtvAdjustmentHistoryParams params{};
    const auto res = api.get_flexible_loan_ltv_adjustment_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/ltv/adjustment/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanLtvAdjustmentHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","collateralCoin":"BNB","direction":"ADDITIONAL","collateralAmount":"5.235","preLTV":"0.78","afterLTV":"0.56","adjustTime":1575018510000}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanLtvAdjustmentHistoryParams params{
        .loan_coin = "BUSD",
        .collateral_coin = "BNB",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_loan_ltv_adjustment_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanLtvAdjustmentHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleLoanLtvAdjustmentHistoryParams params{};
    EXPECT_THROW((void)api.get_flexible_loan_ltv_adjustment_history(params),
                 common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanOngoingOrders) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","totalDebt":"10000","collateralCoin":"BNB","collateralAmount":"49.27565492","currentLTV":"0.57"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanOngoingOrdersParams params{};
    const auto res = api.get_flexible_loan_ongoing_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/ongoing/orders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanOngoingOrdersWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","totalDebt":"10000","collateralCoin":"BNB","collateralAmount":"49.27565492","currentLTV":"0.57"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanOngoingOrdersParams params{
        .loan_coin = "BUSD",
        .collateral_coin = "BNB",
        .current = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_loan_ongoing_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanOngoingOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleLoanOngoingOrdersParams params{};
    EXPECT_THROW((void)api.get_flexible_loan_ongoing_orders(params), common::BadRequestError);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanRepaymentHistory) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","repayAmount":"10000","collateralCoin":"BNB","collateralReturn":"49.27565492","repayStatus":"REPAID","repayTime":1575018510000}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanRepaymentHistoryParams params{};
    const auto res = api.get_flexible_loan_repayment_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/loan/flexible/repay/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanRepaymentHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","repayAmount":"10000","collateralCoin":"BNB","collateralReturn":"49.27565492","repayStatus":"REPAID","repayTime":1575018510000}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFlexibleLoanRepaymentHistoryParams params{
        .loan_coin = "BUSD",
        .collateral_coin = "BNB",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_flexible_loan_repayment_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiFlexibleRateApi, GetFlexibleLoanRepaymentHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFlexibleLoanRepaymentHistoryParams params{};
    EXPECT_THROW((void)api.get_flexible_loan_repayment_history(params), common::BadRequestError);
}
