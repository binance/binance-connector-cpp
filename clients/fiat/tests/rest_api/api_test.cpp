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
#include <binance/fiat/rest_api/api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::fiat::rest_api;
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

Api api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return Api(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiDefaultApi, Deposit) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"orderId":"04595xxxxxxxxx37"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositParams params{.currency = "currency_example",
                               .api_payment_method = DepositApiPaymentMethodEnum::Pix,
                               .amount = "amount_example"};
    const auto res = api.deposit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/fiat/deposit");
    EXPECT_NE((rec.query() + "&" + rec.body).find("currency="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiPaymentMethod="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, DepositWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"orderId":"04595xxxxxxxxx37"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositParams params{
        .currency = "currency_example",
        .api_payment_method = DepositApiPaymentMethodEnum::Pix,
        .amount = "amount_example",
        .recv_window = 5000,
        .ext = boost::json::object{},
    };
    const auto res = api.deposit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("currency="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiPaymentMethod="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("ext="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, DepositBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DepositParams params{.currency = "currency_example",
                               .api_payment_method = DepositApiPaymentMethodEnum::Pix,
                               .amount = "amount_example"};
    EXPECT_THROW((void)api.deposit(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, FiatWithdraw) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"orderId":"04595xxxxxxxxx37"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FiatWithdrawParams params{.currency = "currency_example",
                                    .api_payment_method =
                                        FiatWithdrawApiPaymentMethodEnum::BankTransfer,
                                    .amount = 789,
                                    .account_info = FiatWithdrawRequestAccountInfo{}};
    const auto res = api.fiat_withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v2/fiat/withdraw");
    EXPECT_NE((rec.query() + "&" + rec.body).find("currency="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiPaymentMethod="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountInfo="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, FiatWithdrawWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"orderId":"04595xxxxxxxxx37"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FiatWithdrawParams params{
        .currency = "currency_example",
        .api_payment_method = FiatWithdrawApiPaymentMethodEnum::BankTransfer,
        .amount = 789,
        .account_info = FiatWithdrawRequestAccountInfo{},
        .recv_window = 5000,
        .ext = boost::json::object{},
    };
    const auto res = api.fiat_withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("currency="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiPaymentMethod="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountInfo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("ext="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, FiatWithdrawBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FiatWithdrawParams params{.currency = "currency_example",
                                    .api_payment_method =
                                        FiatWithdrawApiPaymentMethodEnum::BankTransfer,
                                    .amount = 789,
                                    .account_info = FiatWithdrawRequestAccountInfo{}};
    EXPECT_THROW((void)api.fiat_withdraw(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, GetFiatDepositWithdrawHistory) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"orderNo":"7d76d611-0568-4f43-afb6-24cac7767365","fiatCurrency":"BRL","indicatedAmount":"10.00","amount":"10.00","totalFee":"0.00","method":"BankAccount","status":"Expired","createTime":1626144956000,"updateTime":1626400907000}],"total":1,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFiatDepositWithdrawHistoryParams params{.transaction_type = "0"};
    const auto res = api.get_fiat_deposit_withdraw_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/fiat/orders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("transactionType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetFiatDepositWithdrawHistoryWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"orderNo":"7d76d611-0568-4f43-afb6-24cac7767365","fiatCurrency":"BRL","indicatedAmount":"10.00","amount":"10.00","totalFee":"0.00","method":"BankAccount","status":"Expired","createTime":1626144956000,"updateTime":1626400907000}],"total":1,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFiatDepositWithdrawHistoryParams params{
        .transaction_type = "0",
        .begin_time = 1641782889000,
        .end_time = 1641782889000,
        .page = 1,
        .rows = 100,
        .recv_window = 5000,
    };
    const auto res = api.get_fiat_deposit_withdraw_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transactionType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("beginTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("rows="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetFiatDepositWithdrawHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFiatDepositWithdrawHistoryParams params{.transaction_type = "0"};
    EXPECT_THROW((void)api.get_fiat_deposit_withdraw_history(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, GetFiatPaymentsHistory) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"orderNo":"353fca443f06466db0c4dc89f94f027a","sourceAmount":"20.0","fiatCurrency":"EUR","obtainAmount":"4.462","cryptoCurrency":"LUNA","totalFee":"0.2","price":"4.437472","status":"Failed","paymentMethod":"Credit Card","createTime":1624529919000,"updateTime":1624529919000}],"total":1,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFiatPaymentsHistoryParams params{.transaction_type = "0"};
    const auto res = api.get_fiat_payments_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/fiat/payments");
    EXPECT_NE((rec.query() + "&" + rec.body).find("transactionType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetFiatPaymentsHistoryWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":[{"orderNo":"353fca443f06466db0c4dc89f94f027a","sourceAmount":"20.0","fiatCurrency":"EUR","obtainAmount":"4.462","cryptoCurrency":"LUNA","totalFee":"0.2","price":"4.437472","status":"Failed","paymentMethod":"Credit Card","createTime":1624529919000,"updateTime":1624529919000}],"total":1,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFiatPaymentsHistoryParams params{
        .transaction_type = "0",
        .begin_time = 1641782889000,
        .end_time = 1641782889000,
        .page = 1,
        .rows = 100,
        .recv_window = 5000,
    };
    const auto res = api.get_fiat_payments_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transactionType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("beginTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("rows="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetFiatPaymentsHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFiatPaymentsHistoryParams params{.transaction_type = "0"};
    EXPECT_THROW((void)api.get_fiat_payments_history(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, GetOrderDetail) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"orderId":"036752*678","orderStatus":"ORDER_INITIAL","amount":"4.33","fee":"0.43","fiatCurrency":"***","errorCode":"","errorMessage":"","ext":{}}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderDetailParams params{.order_no = "036752*678"};
    const auto res = api.get_order_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/fiat/get-order-detail");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderNo="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetOrderDetailWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":{"orderId":"036752*678","orderStatus":"ORDER_INITIAL","amount":"4.33","fee":"0.43","fiatCurrency":"***","errorCode":"","errorMessage":"","ext":{}}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOrderDetailParams params{
        .order_no = "036752*678",
        .recv_window = 5000,
    };
    const auto res = api.get_order_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderNo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetOrderDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOrderDetailParams params{.order_no = "036752*678"};
    EXPECT_THROW((void)api.get_order_detail(params), common::BadRequestError);
}
