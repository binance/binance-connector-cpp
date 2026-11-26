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
#include <binance/vip_loan/rest_api/user_information_api.hpp>

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

UserInformationApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return UserInformationApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiUserInformationApi, CheckVIPLoanCollateralAccount) {
    const std::string example =
        R"json({"rows":[{"collateralAccountId":"12345678","collateralCoin":"BNB,BTC,ETH"}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CheckVIPLoanCollateralAccountParams params{};
    const auto res = api.check_vip_loan_collateral_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/collateral/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, CheckVIPLoanCollateralAccountWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"collateralAccountId":"12345678","collateralCoin":"BNB,BTC,ETH"}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CheckVIPLoanCollateralAccountParams params{
        .order_id = 1,
        .collateral_account_id = 1,
        .recv_window = 5000,
    };
    const auto res = api.check_vip_loan_collateral_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, CheckVIPLoanCollateralAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CheckVIPLoanCollateralAccountParams params{};
    EXPECT_THROW((void)api.check_vip_loan_collateral_account(params), common::BadRequestError);
}

TEST(RestApiUserInformationApi, GetVIPLoanAccruedInterest) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"USDT","principalAmount":"10000","interestAmount":"1.2","annualInterestRate":"0.001273","accrualTime":1575018510000,"orderId":756783308056935400}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetVIPLoanAccruedInterestParams params{};
    const auto res = api.get_vip_loan_accrued_interest(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/accruedInterest");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, GetVIPLoanAccruedInterestWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"USDT","principalAmount":"10000","interestAmount":"1.2","annualInterestRate":"0.001273","accrualTime":1575018510000,"orderId":756783308056935400}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetVIPLoanAccruedInterestParams params{
        .order_id = 1,
        .loan_coin = "BTC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_vip_loan_accrued_interest(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, GetVIPLoanAccruedInterestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetVIPLoanAccruedInterestParams params{};
    EXPECT_THROW((void)api.get_vip_loan_accrued_interest(params), common::BadRequestError);
}

TEST(RestApiUserInformationApi, GetVIPLoanOngoingOrders) {
    const std::string example =
        R"json({"rows":[{"orderId":100000001,"loanCoin":"BUSD","totalDebt":"10000","loanRate":"0.0123","residualInterest":"10.27687923","collateralAccountId":"12345678,23456789","collateralCoin":"BNB,BNB-Earn,BTC,ETH","totalCollateralValueAfterHaircut":"25000.27565492","lockedCollateralValue":"25000.27565492","currentLTV":"0.57","expirationTime":1575018510000,"loanDate":"1676851200000","loanTerm":"30days"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetVIPLoanOngoingOrdersParams params{};
    const auto res = api.get_vip_loan_ongoing_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/ongoing/orders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, GetVIPLoanOngoingOrdersWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"orderId":100000001,"loanCoin":"BUSD","totalDebt":"10000","loanRate":"0.0123","residualInterest":"10.27687923","collateralAccountId":"12345678,23456789","collateralCoin":"BNB,BNB-Earn,BTC,ETH","totalCollateralValueAfterHaircut":"25000.27565492","lockedCollateralValue":"25000.27565492","currentLTV":"0.57","expirationTime":1575018510000,"loanDate":"1676851200000","loanTerm":"30days"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetVIPLoanOngoingOrdersParams params{
        .order_id = 1,
        .collateral_account_id = 1,
        .loan_coin = "BUSD",
        .collateral_coin = "BNB,BTC,ETH",
        .current = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_vip_loan_ongoing_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, GetVIPLoanOngoingOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetVIPLoanOngoingOrdersParams params{};
    EXPECT_THROW((void)api.get_vip_loan_ongoing_orders(params), common::BadRequestError);
}

TEST(RestApiUserInformationApi, GetVIPLoanRepaymentHistory) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","repayAmount":"10000","repayPrincipal":"9500","repayInterest":"500","collateralCoin":"BNB,BTC,ETH","repayStatus":"Repaid","loanDate":"1676851200000","repayTime":"1575018510000","orderId":"756783308056935434"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetVIPLoanRepaymentHistoryParams params{};
    const auto res = api.get_vip_loan_repayment_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/repay/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, GetVIPLoanRepaymentHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanCoin":"BUSD","repayAmount":"10000","repayPrincipal":"9500","repayInterest":"500","collateralCoin":"BNB,BTC,ETH","repayStatus":"Repaid","loanDate":"1676851200000","repayTime":"1575018510000","orderId":"756783308056935434"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetVIPLoanRepaymentHistoryParams params{
        .order_id = 1,
        .loan_coin = "BUSD",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_vip_loan_repayment_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, GetVIPLoanRepaymentHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetVIPLoanRepaymentHistoryParams params{};
    EXPECT_THROW((void)api.get_vip_loan_repayment_history(params), common::BadRequestError);
}

TEST(RestApiUserInformationApi, QueryApplicationStatus) {
    const std::string example =
        R"json({"rows":[{"loanAccountId":"12345678","orderId":"12345678","requestId":"12345678","loanCoin":"BTC","loanAmount":"100.55","collateralAccountId":"12345678,12345678,12345678","collateralCoin":"BUSD,USDT,USDT-Earn,ETH","loanTerm":"30","status":"Repaid","loanDate":"1676851200000"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryApplicationStatusParams params{};
    const auto res = api.query_application_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/request/data");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, QueryApplicationStatusWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"loanAccountId":"12345678","orderId":"12345678","requestId":"12345678","loanCoin":"BTC","loanAmount":"100.55","collateralAccountId":"12345678,12345678,12345678","collateralCoin":"BUSD,USDT,USDT-Earn,ETH","loanTerm":"30","status":"Repaid","loanDate":"1676851200000"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryApplicationStatusParams params{
        .current = 1,
        .limit = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_application_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiUserInformationApi, QueryApplicationStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryApplicationStatusParams params{};
    EXPECT_THROW((void)api.query_application_status(params), common::BadRequestError);
}
