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
#include <binance/stock_options/rest_api/market_data_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::stock_options::rest_api;
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

TEST(RestApiMarketDataApi, OptionContracts) {
    const std::string example =
        R"json([{"symbol":"NVDA260930C00100000","contractType":"CALL","strikePrice":"100","multiplier":"100","contractSize":100,"expirationDate":"2026-09-30","status":"OPEN_CLOSE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionContractsParams params{.underlying_symbol = "NVDA",
                                       .expiration_date = "2026-09-30"};
    const auto res = api.option_contracts(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/market/contracts");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("expirationDate="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OptionContractsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"NVDA260930C00100000","contractType":"CALL","strikePrice":"100","multiplier":"100","contractSize":100,"expirationDate":"2026-09-30","status":"OPEN_CLOSE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionContractsParams params{
        .underlying_symbol = "NVDA",
        .expiration_date = "2026-09-30",
        .root_symbol = "NVDA",
    };
    const auto res = api.option_contracts(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("expirationDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("rootSymbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, OptionContractsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionContractsParams params{.underlying_symbol = "NVDA",
                                       .expiration_date = "2026-09-30"};
    EXPECT_THROW((void)api.option_contracts(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OptionExchangeInfo) {
    const std::string example =
        R"json({"timezone":"UTC","symbols":[{"symbol":"NVDA260930C00100000","underlyingSymbol":"NVDA","rootSymbol":"NVDA","contractType":"CALL","status":"OPEN_CLOSE","strikePrice":"100","expirationDate":1790784000000,"multiplier":"100","contractSize":100,"tickSize":"0.01","stepSize":"1","minQty":"1","maxQty":"100000","minNotional":"1","maxNotional":"500000","optionsLateClose":false,"pennyProgram":true,"deliverables":[{"type":"EQUITY","symbol":"NVDA","amount":"100"}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionExchangeInfoParams params{.symbol = "NVDA260930C00100000"};
    const auto res = api.option_exchange_info(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/market/exchangeInfo");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OptionExchangeInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionExchangeInfoParams params{.symbol = "NVDA260930C00100000"};
    EXPECT_THROW((void)api.option_exchange_info(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OptionExpirations) {
    const std::string example = R"json([{"expirationDate":"2026-09-30","rootSymbol":"NVDA"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OptionExpirationsParams params{.underlying_symbol = "NVDA"};
    const auto res = api.option_expirations(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/equity/option/market/expirations");
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlyingSymbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OptionExpirationsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OptionExpirationsParams params{.underlying_symbol = "NVDA"};
    EXPECT_THROW((void)api.option_expirations(params), common::BadRequestError);
}
