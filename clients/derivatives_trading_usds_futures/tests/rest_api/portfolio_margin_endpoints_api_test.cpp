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
#include <binance/derivatives_trading_usds_futures/rest_api/portfolio_margin_endpoints_api.hpp>

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

PortfolioMarginEndpointsApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return PortfolioMarginEndpointsApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiPortfolioMarginEndpointsApi, ClassicPortfolioMarginAccountInformation) {
    const std::string example =
        R"json({"maxWithdrawAmountUSD":"1627523.32459208","asset":"BTC","maxWithdrawAmount":"27.43689636"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ClassicPortfolioMarginAccountInformationParams params{.asset = "BTC"};
    const auto res = api.classic_portfolio_margin_account_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/pmAccountInfo");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPortfolioMarginEndpointsApi,
     ClassicPortfolioMarginAccountInformationWithOptionalParams) {
    const std::string example =
        R"json({"maxWithdrawAmountUSD":"1627523.32459208","asset":"BTC","maxWithdrawAmount":"27.43689636"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ClassicPortfolioMarginAccountInformationParams params{
        .asset = "BTC",
        .recv_window = 5000,
    };
    const auto res = api.classic_portfolio_margin_account_information(params);
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

TEST(RestApiPortfolioMarginEndpointsApi, ClassicPortfolioMarginAccountInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ClassicPortfolioMarginAccountInformationParams params{.asset = "BTC"};
    EXPECT_THROW((void)api.classic_portfolio_margin_account_information(params),
                 common::BadRequestError);
}
