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
#include <binance/convert/rest_api/market_data_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::convert::rest_api;
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

TEST(RestApiMarketDataApi, ListAllConvertPairs) {
    const std::string example =
        R"json([{"fromAsset":"BTC","toAsset":"USDT","fromAssetMinAmount":"0.0004","fromAssetMaxAmount":"50","toAssetMinAmount":"20","toAssetMaxAmount":"2500000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ListAllConvertPairsParams params{};
    const auto res = api.list_all_convert_pairs(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/convert/exchangeInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ListAllConvertPairsWithOptionalParams) {
    const std::string example =
        R"json([{"fromAsset":"BTC","toAsset":"USDT","fromAssetMinAmount":"0.0004","fromAssetMaxAmount":"50","toAssetMinAmount":"20","toAssetMaxAmount":"2500000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ListAllConvertPairsParams params{
        .from_asset = "BTC",
        .to_asset = "USDT",
    };
    const auto res = api.list_all_convert_pairs(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toAsset="), std::string::npos);
}

TEST(RestApiMarketDataApi, ListAllConvertPairsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ListAllConvertPairsParams params{};
    EXPECT_THROW((void)api.list_all_convert_pairs(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryOrderQuantityPrecisionPerAsset) {
    const std::string example = R"json([{"asset":"BTC","fraction":8}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOrderQuantityPrecisionPerAssetParams params{};
    const auto res = api.query_order_quantity_precision_per_asset(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/convert/assetInfo");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryOrderQuantityPrecisionPerAssetWithOptionalParams) {
    const std::string example = R"json([{"asset":"BTC","fraction":8}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOrderQuantityPrecisionPerAssetParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_order_quantity_precision_per_asset(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryOrderQuantityPrecisionPerAssetBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryOrderQuantityPrecisionPerAssetParams params{};
    EXPECT_THROW((void)api.query_order_quantity_precision_per_asset(params),
                 common::BadRequestError);
}
