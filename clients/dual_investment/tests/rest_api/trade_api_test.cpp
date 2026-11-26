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
#include <binance/dual_investment/rest_api/trade_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::dual_investment::rest_api;
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

TEST(RestApiTradeApi, CheckDualInvestmentAccounts) {
    const std::string example =
        R"json({"totalAmountInBTC":"0.01067982","totalAmountInUSDT":"77.13289230"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CheckDualInvestmentAccountsParams params{};
    const auto res = api.check_dual_investment_accounts(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/dci/product/accounts");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CheckDualInvestmentAccountsWithOptionalParams) {
    const std::string example =
        R"json({"totalAmountInBTC":"0.01067982","totalAmountInUSDT":"77.13289230"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CheckDualInvestmentAccountsParams params{
        .recv_window = 5000,
    };
    const auto res = api.check_dual_investment_accounts(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CheckDualInvestmentAccountsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CheckDualInvestmentAccountsParams params{};
    EXPECT_THROW((void)api.check_dual_investment_accounts(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetDualInvestmentPositions) {
    const std::string example =
        R"json({"total":1,"list":[{"id":"10160533","investCoin":"USDT","exercisedCoin":"BNB","subscriptionAmount":"0.5","strikePrice":"330","duration":4,"settleDate":1708416000000,"purchaseStatus":"PURCHASE_SUCCESS","apr":"0.0365","orderId":7973677530,"purchaseEndTime":1708329600000,"optionType":"PUT","autoCompoundPlan":"STANDARD","subscriptionTime":1708243200000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDualInvestmentPositionsParams params{};
    const auto res = api.get_dual_investment_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/dci/product/positions");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetDualInvestmentPositionsWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"list":[{"id":"10160533","investCoin":"USDT","exercisedCoin":"BNB","subscriptionAmount":"0.5","strikePrice":"330","duration":4,"settleDate":1708416000000,"purchaseStatus":"PURCHASE_SUCCESS","apr":"0.0365","orderId":7973677530,"purchaseEndTime":1708329600000,"optionType":"PUT","autoCompoundPlan":"STANDARD","subscriptionTime":1708243200000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDualInvestmentPositionsParams params{
        .status = GetDualInvestmentPositionsStatusEnum::Pending,
        .page_size = 10,
        .page_index = 1,
        .recv_window = 5000,
    };
    const auto res = api.get_dual_investment_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageIndex="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetDualInvestmentPositionsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDualInvestmentPositionsParams params{};
    EXPECT_THROW((void)api.get_dual_investment_positions(params), common::BadRequestError);
}

TEST(RestApiTradeApi, SubscribeDualInvestmentProducts) {
    const std::string example =
        R"json({"positionId":10208824,"investCoin":"BNB","exercisedCoin":"USDT","subscriptionAmount":"0.002","duration":4,"autoCompoundPlan":"STANDARD","strikePrice":"380","settleDate":1709020800000,"purchaseStatus":"PURCHASE_SUCCESS","apr":"0.7397","orderId":8259117597,"purchaseTime":1708677583874,"optionType":"CALL"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeDualInvestmentProductsParams params{
        .id = "741590", .order_id = "8257205859", .deposit_amount = common::Decimal("1")};
    const auto res = api.subscribe_dual_investment_products(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/dci/product/subscribe");
    EXPECT_NE((rec.query() + "&" + rec.body).find("id="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("depositAmount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SubscribeDualInvestmentProductsWithOptionalParams) {
    const std::string example =
        R"json({"positionId":10208824,"investCoin":"BNB","exercisedCoin":"USDT","subscriptionAmount":"0.002","duration":4,"autoCompoundPlan":"STANDARD","strikePrice":"380","settleDate":1709020800000,"purchaseStatus":"PURCHASE_SUCCESS","apr":"0.7397","orderId":8259117597,"purchaseTime":1708677583874,"optionType":"CALL"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubscribeDualInvestmentProductsParams params{
        .id = "741590",
        .order_id = "8257205859",
        .deposit_amount = common::Decimal("1"),
        .recv_window = 5000,
    };
    const auto res = api.subscribe_dual_investment_products(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("id="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("depositAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SubscribeDualInvestmentProductsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubscribeDualInvestmentProductsParams params{
        .id = "741590", .order_id = "8257205859", .deposit_amount = common::Decimal("1")};
    EXPECT_THROW((void)api.subscribe_dual_investment_products(params), common::BadRequestError);
}
