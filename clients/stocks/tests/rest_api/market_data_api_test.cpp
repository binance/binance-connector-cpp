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
#include <binance/stocks/rest_api/market_data_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::stocks::rest_api;
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

TEST(RestApiMarketDataApi, ExchangeInfo) {
    const std::string example =
        R"json({"timezone":"UTC","symbols":[{"symbol":"AAPL","tradability":"BUY_SELL","tradabilityUpdateTime":1735900000000,"overnightSupported":true,"fractionable":true,"fractionableEh":false,"extendedSession":true,"maxNumOrders":200,"stepSize":"0.000000001","multiplierUp":"1.10","multiplierDown":"0.90","minQty":"0.000000001","maxQty":"100000.00000000","minNotional":"1.00","maxNotional":"1000000.00","listingTime":1700000000000,"delistingTime":1}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExchangeInfoParams params{};
    const auto res = api.exchange_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/market/exchangeInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ExchangeInfoWithOptionalParams) {
    const std::string example =
        R"json({"timezone":"UTC","symbols":[{"symbol":"AAPL","tradability":"BUY_SELL","tradabilityUpdateTime":1735900000000,"overnightSupported":true,"fractionable":true,"fractionableEh":false,"extendedSession":true,"maxNumOrders":200,"stepSize":"0.000000001","multiplierUp":"1.10","multiplierDown":"0.90","minQty":"0.000000001","maxQty":"100000.00000000","minNotional":"1.00","maxNotional":"1000000.00","listingTime":1700000000000,"delistingTime":1}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExchangeInfoParams params{
        .symbol = "AAPL",
    };
    const auto res = api.exchange_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, ExchangeInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ExchangeInfoParams params{};
    EXPECT_THROW((void)api.exchange_info(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, LatestQuote) {
    const std::string example =
        R"json({"symbol":"AAPL","bidPrice":"180.50","askPrice":"180.52","bidSize":100,"askSize":200})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const LatestQuoteParams params{.symbol = "AAPL"};
    const auto res = api.latest_quote(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/market/quote");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, LatestQuoteBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const LatestQuoteParams params{.symbol = "AAPL"};
    EXPECT_THROW((void)api.latest_quote(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TokenizedAssets) {
    const std::string example =
        R"json([{"assetCode":"AAPLB","assetName":"Apple Inc. Tokenized Stock","underlyingEquitySymbol":"AAPL","multiplier":"1","multiplierValid":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.tokenized_assets();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/market/tokenized-assets");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TokenizedAssetsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.tokenized_assets(), common::BadRequestError);
}
