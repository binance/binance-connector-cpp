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
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/market_data_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_portfolio_margin_pro::rest_api;
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

TEST(RestApiMarketDataApi, GetPortfolioMarginAssetLeverage) {
    const std::string example = R"json([{"asset":"USDC","leverage":10}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.get_portfolio_margin_asset_leverage();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/margin-asset-leverage");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetPortfolioMarginAssetLeverageBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.get_portfolio_margin_asset_leverage(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetPortfolioMarginTieredCollateralRates) {
    const std::string example =
        R"json([{"asset":"BNB","collateralInfo":[{"tierFloor":"0.0000","tierCap":"1000.0000","collateralRate":"1.0000","cum":"0.0000"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.get_portfolio_margin_tiered_collateral_rates();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/portfolio/retail/collateralRate");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetPortfolioMarginTieredCollateralRatesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.get_portfolio_margin_tiered_collateral_rates(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, PortfolioMarginCollateralRate) {
    const std::string example = R"json([{"asset":"USDC","collateralRate":"1.0000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.portfolio_margin_collateral_rate();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/collateralRate");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, PortfolioMarginCollateralRateBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.portfolio_margin_collateral_rate(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, PortfolioMarginProTieredCollateralRate) {
    const std::string example =
        R"json([{"asset":"BNB","collateralInfo":[{"tierFloor":"0.0000","tierCap":"1000.0000","collateralRate":"1.0000","cum":"0.0000"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PortfolioMarginProTieredCollateralRateParams params{};
    const auto res = api.portfolio_margin_pro_tiered_collateral_rate(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/portfolio/collateralRate");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, PortfolioMarginProTieredCollateralRateWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"BNB","collateralInfo":[{"tierFloor":"0.0000","tierCap":"1000.0000","collateralRate":"1.0000","cum":"0.0000"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PortfolioMarginProTieredCollateralRateParams params{
        .recv_window = 5000,
    };
    const auto res = api.portfolio_margin_pro_tiered_collateral_rate(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, PortfolioMarginProTieredCollateralRateBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PortfolioMarginProTieredCollateralRateParams params{};
    EXPECT_THROW((void)api.portfolio_margin_pro_tiered_collateral_rate(params),
                 common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryPortfolioMarginAssetIndexPrice) {
    const std::string example =
        R"json([{"asset":"BTC","assetIndexPrice":"28251.9136906","time":1683518338121}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginAssetIndexPriceParams params{};
    const auto res = api.query_portfolio_margin_asset_index_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/portfolio/asset-index-price");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryPortfolioMarginAssetIndexPriceWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"BTC","assetIndexPrice":"28251.9136906","time":1683518338121}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPortfolioMarginAssetIndexPriceParams params{
        .asset = "BTC",
    };
    const auto res = api.query_portfolio_margin_asset_index_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryPortfolioMarginAssetIndexPriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPortfolioMarginAssetIndexPriceParams params{};
    EXPECT_THROW((void)api.query_portfolio_margin_asset_index_price(params),
                 common::BadRequestError);
}
