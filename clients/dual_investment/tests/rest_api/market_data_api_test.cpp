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
#include <binance/dual_investment/rest_api/market_data_api.hpp>

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

MarketDataApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return MarketDataApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiMarketDataApi, GetDualInvestmentProductList) {
    const std::string example =
        R"json({"total":1,"list":[{"id":"741590","investCoin":"USDT","exercisedCoin":"BNB","strikePrice":"380","duration":4,"settleDate":1709020800000,"purchaseDecimal":8,"purchaseEndTime":1708934400000,"canPurchase":true,"apr":"0.6076","orderId":8257205859,"minAmount":"0.1","maxAmount":"25265.7","createTimestamp":1708560084000,"optionType":"PUT","isAutoCompoundEnable":true,"autoCompoundPlanList":["STANDARD","ADVANCE"]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDualInvestmentProductListParams params{
        .option_type = GetDualInvestmentProductListOptionTypeEnum::Call,
        .exercised_coin = "USDT",
        .invest_coin = "BNB"};
    const auto res = api.get_dual_investment_product_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/dci/product/list");
    EXPECT_NE((rec.query() + "&" + rec.body).find("optionType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("exercisedCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("investCoin="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetDualInvestmentProductListWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"list":[{"id":"741590","investCoin":"USDT","exercisedCoin":"BNB","strikePrice":"380","duration":4,"settleDate":1709020800000,"purchaseDecimal":8,"purchaseEndTime":1708934400000,"canPurchase":true,"apr":"0.6076","orderId":8257205859,"minAmount":"0.1","maxAmount":"25265.7","createTimestamp":1708560084000,"optionType":"PUT","isAutoCompoundEnable":true,"autoCompoundPlanList":["STANDARD","ADVANCE"]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDualInvestmentProductListParams params{
        .option_type = GetDualInvestmentProductListOptionTypeEnum::Call,
        .exercised_coin = "USDT",
        .invest_coin = "BNB",
        .page_size = 10,
        .page_index = 1,
        .recv_window = 5000,
    };
    const auto res = api.get_dual_investment_product_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("optionType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("exercisedCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("investCoin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageIndex="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetDualInvestmentProductListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDualInvestmentProductListParams params{
        .option_type = GetDualInvestmentProductListOptionTypeEnum::Call,
        .exercised_coin = "USDT",
        .invest_coin = "BNB"};
    EXPECT_THROW((void)api.get_dual_investment_product_list(params), common::BadRequestError);
}
