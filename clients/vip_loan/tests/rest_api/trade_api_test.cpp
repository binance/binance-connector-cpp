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
#include <binance/vip_loan/rest_api/trade_api.hpp>

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

TradeApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return TradeApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiTradeApi, VipLoanBorrow) {
    const std::string example =
        R"json({"loanAccountId":"12345678","requestId":"12345678","loanCoin":"BTC","isFlexibleRate":"Yes","loanAmount":"100.55","collateralAccountId":"12345678,12345678,12345678","collateralCoin":"BUSD,USDT,USDT-Earn,ETH","loanTerm":"30"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VipLoanBorrowParams params{.loan_account_id = 1,
                                     .loan_coin = "BTC",
                                     .loan_amount = common::Decimal("1.0"),
                                     .collateral_account_id = "12345678,12345678,12345678",
                                     .collateral_coin = "BUSD,USDT,USDT-Earn,ETH",
                                     .is_flexible_rate = true};
    const auto res = api.vip_loan_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/borrow");
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isFlexibleRate="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, VipLoanBorrowWithOptionalParams) {
    const std::string example =
        R"json({"loanAccountId":"12345678","requestId":"12345678","loanCoin":"BTC","isFlexibleRate":"Yes","loanAmount":"100.55","collateralAccountId":"12345678,12345678,12345678","collateralCoin":"BUSD,USDT,USDT-Earn,ETH","loanTerm":"30"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VipLoanBorrowParams params{
        .loan_account_id = 1,
        .loan_coin = "BTC",
        .loan_amount = common::Decimal("1.0"),
        .collateral_account_id = "12345678,12345678,12345678",
        .collateral_coin = "BUSD,USDT,USDT-Earn,ETH",
        .is_flexible_rate = true,
        .loan_term = 30,
        .recv_window = 5000,
    };
    const auto res = api.vip_loan_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isFlexibleRate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanTerm="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, VipLoanBorrowBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const VipLoanBorrowParams params{.loan_account_id = 1,
                                     .loan_coin = "BTC",
                                     .loan_amount = common::Decimal("1.0"),
                                     .collateral_account_id = "12345678,12345678,12345678",
                                     .collateral_coin = "BUSD,USDT,USDT-Earn,ETH",
                                     .is_flexible_rate = true};
    EXPECT_THROW((void)api.vip_loan_borrow(params), common::BadRequestError);
}

TEST(RestApiTradeApi, VipLoanFixedRateBorrow) {
    const std::string example =
        R"json({"borrowCoin":"BUSD","borrowAmount":"100.5","actualReceivedAmount":"98.75","collateralCoin":"BNB,BNB-Earn,ETH,BTC","collateralAccountId":"12345,67890,13579","borrowInterestRate":"0.01501231","duration":"30Days","autoRepay":true,"orderId":123456789,"status":"Succeeds"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VipLoanFixedRateBorrowParams params{.supply_request = "1212:0.12:100;3434:0.13:50",
                                              .borrow_coin = "BUSD",
                                              .loan_term = 30,
                                              .borrow_uid = 12345678,
                                              .collateral_coin = "BNB,BNB-Earn,ETH,BTC",
                                              .collateral_account_id = "12345,67890,13579"};
    const auto res = api.vip_loan_fixed_rate_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/fixed/borrow");
    EXPECT_NE((rec.query() + "&" + rec.body).find("supplyRequest="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("borrowCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanTerm="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("borrowUid="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralAccountId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, VipLoanFixedRateBorrowWithOptionalParams) {
    const std::string example =
        R"json({"borrowCoin":"BUSD","borrowAmount":"100.5","actualReceivedAmount":"98.75","collateralCoin":"BNB,BNB-Earn,ETH,BTC","collateralAccountId":"12345,67890,13579","borrowInterestRate":"0.01501231","duration":"30Days","autoRepay":true,"orderId":123456789,"status":"Succeeds"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VipLoanFixedRateBorrowParams params{
        .supply_request = "1212:0.12:100;3434:0.13:50",
        .borrow_coin = "BUSD",
        .loan_term = 30,
        .borrow_uid = 12345678,
        .collateral_coin = "BNB,BNB-Earn,ETH,BTC",
        .collateral_account_id = "12345,67890,13579",
        .auto_repay = true,
        .recv_window = 5000,
    };
    const auto res = api.vip_loan_fixed_rate_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("supplyRequest="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("borrowCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanTerm="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("borrowUid="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("collateralAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoRepay="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, VipLoanFixedRateBorrowBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const VipLoanFixedRateBorrowParams params{.supply_request = "1212:0.12:100;3434:0.13:50",
                                              .borrow_coin = "BUSD",
                                              .loan_term = 30,
                                              .borrow_uid = 12345678,
                                              .collateral_coin = "BNB,BNB-Earn,ETH,BTC",
                                              .collateral_account_id = "12345,67890,13579"};
    EXPECT_THROW((void)api.vip_loan_fixed_rate_borrow(params), common::BadRequestError);
}

TEST(RestApiTradeApi, VipLoanRenew) {
    const std::string example =
        R"json({"loanAccountId":"12345678","loanCoin":"BTC","loanAmount":"100.55","collateralAccountId":"12345677,12345678,12345679","collateralCoin":"BUSD,USDT,ETH","loanTerm":"30"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VipLoanRenewParams params{.order_id = 1, .loan_term = 30};
    const auto res = api.vip_loan_renew(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/renew");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanTerm="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, VipLoanRenewWithOptionalParams) {
    const std::string example =
        R"json({"loanAccountId":"12345678","loanCoin":"BTC","loanAmount":"100.55","collateralAccountId":"12345677,12345678,12345679","collateralCoin":"BUSD,USDT,ETH","loanTerm":"30"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VipLoanRenewParams params{
        .order_id = 1,
        .loan_term = 30,
        .recv_window = 5000,
    };
    const auto res = api.vip_loan_renew(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("loanTerm="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, VipLoanRenewBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const VipLoanRenewParams params{.order_id = 1, .loan_term = 30};
    EXPECT_THROW((void)api.vip_loan_renew(params), common::BadRequestError);
}

TEST(RestApiTradeApi, VipLoanRepay) {
    const std::string example =
        R"json({"loanCoin":"BUSD","repayAmount":"200.5","remainingPrincipal":"100.5","remainingInterest":"0","collateralCoin":"BNB,BTC,ETH","currentLTV":"0.25","repayStatus":"Repaid"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VipLoanRepayParams params{.order_id = 1, .amount = common::Decimal("1.0")};
    const auto res = api.vip_loan_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/loan/vip/repay");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, VipLoanRepayWithOptionalParams) {
    const std::string example =
        R"json({"loanCoin":"BUSD","repayAmount":"200.5","remainingPrincipal":"100.5","remainingInterest":"0","collateralCoin":"BNB,BTC,ETH","currentLTV":"0.25","repayStatus":"Repaid"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VipLoanRepayParams params{
        .order_id = 1,
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.vip_loan_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, VipLoanRepayBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const VipLoanRepayParams params{.order_id = 1, .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.vip_loan_repay(params), common::BadRequestError);
}
