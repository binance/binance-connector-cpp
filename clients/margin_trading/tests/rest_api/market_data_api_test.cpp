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
#include <binance/margin_trading/rest_api/market_data_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::margin_trading::rest_api;
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

TEST(RestApiMarketDataApi, CrossMarginCollateralRatio) {
    const std::string example =
        R"json([{"collaterals":[{"minUsdValue":"0","maxUsdValue":"13000000","discountRate":"1"}],"assetNames":["BNX"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.cross_margin_collateral_ratio();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/crossMarginCollateralRatio");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CrossMarginCollateralRatioBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.cross_margin_collateral_ratio(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetAllCrossMarginPairs) {
    const std::string example =
        R"json([{"base":"BNB","id":351637150141315840,"isBuyAllowed":true,"isMarginTrade":true,"isSellAllowed":true,"quote":"BTC","symbol":"BNBBTC","delistTime":1704973040}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAllCrossMarginPairsParams params{};
    const auto res = api.get_all_cross_margin_pairs(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/allPairs");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetAllCrossMarginPairsWithOptionalParams) {
    const std::string example =
        R"json([{"base":"BNB","id":351637150141315840,"isBuyAllowed":true,"isMarginTrade":true,"isSellAllowed":true,"quote":"BTC","symbol":"BNBBTC","delistTime":1704973040}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAllCrossMarginPairsParams params{
        .symbol = "BNBBTC",
    };
    const auto res = api.get_all_cross_margin_pairs(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetAllCrossMarginPairsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetAllCrossMarginPairsParams params{};
    EXPECT_THROW((void)api.get_all_cross_margin_pairs(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetAllIsolatedMarginSymbol) {
    const std::string example =
        R"json([{"base":"BNB","isBuyAllowed":true,"isMarginTrade":true,"isSellAllowed":true,"quote":"BTC","symbol":"BNBBTC"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAllIsolatedMarginSymbolParams params{};
    const auto res = api.get_all_isolated_margin_symbol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/isolated/allPairs");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetAllIsolatedMarginSymbolWithOptionalParams) {
    const std::string example =
        R"json([{"base":"BNB","isBuyAllowed":true,"isMarginTrade":true,"isSellAllowed":true,"quote":"BTC","symbol":"BNBBTC"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAllIsolatedMarginSymbolParams params{
        .symbol = "BNBBTC",
        .recv_window = 5000,
    };
    const auto res = api.get_all_isolated_margin_symbol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetAllIsolatedMarginSymbolBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetAllIsolatedMarginSymbolParams params{};
    EXPECT_THROW((void)api.get_all_isolated_margin_symbol(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetAllMarginAssets) {
    const std::string example =
        R"json([{"assetFullName":"USD coin","assetName":"USDC","isBorrowable":true,"isMortgageable":true,"userMinBorrow":"5.00000000","userMinRepay":"0.00000000","delistTime":1704973040000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAllMarginAssetsParams params{};
    const auto res = api.get_all_margin_assets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/allAssets");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetAllMarginAssetsWithOptionalParams) {
    const std::string example =
        R"json([{"assetFullName":"USD coin","assetName":"USDC","isBorrowable":true,"isMortgageable":true,"userMinBorrow":"5.00000000","userMinRepay":"0.00000000","delistTime":1704973040000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAllMarginAssetsParams params{
        .asset = "USDC",
    };
    const auto res = api.get_all_margin_assets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetAllMarginAssetsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetAllMarginAssetsParams params{};
    EXPECT_THROW((void)api.get_all_margin_assets(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetDelistSchedule) {
    const std::string example =
        R"json([{"delistTime":1686161202000,"crossMarginAssets":["BTC"],"isolatedMarginSymbols":["ADAUSDT"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDelistScheduleParams params{};
    const auto res = api.get_delist_schedule(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/delist-schedule");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetDelistScheduleWithOptionalParams) {
    const std::string example =
        R"json([{"delistTime":1686161202000,"crossMarginAssets":["BTC"],"isolatedMarginSymbols":["ADAUSDT"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDelistScheduleParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_delist_schedule(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetDelistScheduleBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDelistScheduleParams params{};
    EXPECT_THROW((void)api.get_delist_schedule(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetLimitPricePairs) {
    const std::string example = R"json({"crossMarginSymbols":["BLURUSDC"]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.get_limit_price_pairs();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/limit-price-pairs");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetLimitPricePairsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.get_limit_price_pairs(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetListSchedule) {
    const std::string example =
        R"json([{"listTime":1686161202000,"crossMarginAssets":["BTC"],"isolatedMarginSymbols":["ADAUSDT"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetListScheduleParams params{};
    const auto res = api.get_list_schedule(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/list-schedule");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetListScheduleWithOptionalParams) {
    const std::string example =
        R"json([{"listTime":1686161202000,"crossMarginAssets":["BTC"],"isolatedMarginSymbols":["ADAUSDT"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetListScheduleParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_list_schedule(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetListScheduleBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetListScheduleParams params{};
    EXPECT_THROW((void)api.get_list_schedule(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetMarginAssetRiskBasedLiquidationRatio) {
    const std::string example = R"json([{"asset":"USDC","riskBasedLiquidationRatio":"0.01"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.get_margin_asset_risk_based_liquidation_ratio();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/risk-based-liquidation-ratio");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetMarginAssetRiskBasedLiquidationRatioBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.get_margin_asset_risk_based_liquidation_ratio(),
                 common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetMarginRestrictedAssets) {
    const std::string example =
        R"json({"openLongRestrictedAsset":["ADA"],"maxCollateralExceededAsset":["ACH"]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.get_margin_restricted_assets();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/restricted-asset");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetMarginRestrictedAssetsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.get_margin_restricted_assets(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryIsolatedMarginTierData) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","tier":1,"effectiveMultiple":"10","initialRiskRatio":"1.111","liquidationRiskRatio":"1.05","baseAssetMaxBorrowable":"9","quoteAssetMaxBorrowable":"70000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryIsolatedMarginTierDataParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_isolated_margin_tier_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/isolatedMarginTier");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryIsolatedMarginTierDataWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","tier":1,"effectiveMultiple":"10","initialRiskRatio":"1.111","liquidationRiskRatio":"1.05","baseAssetMaxBorrowable":"9","quoteAssetMaxBorrowable":"70000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryIsolatedMarginTierDataParams params{
        .symbol = "BTCUSDT",
        .tier = 1,
        .recv_window = 5000,
    };
    const auto res = api.query_isolated_margin_tier_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tier="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryIsolatedMarginTierDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryIsolatedMarginTierDataParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_isolated_margin_tier_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryLiabilityCoinLeverageBracketInCrossMarginProMode) {
    const std::string example =
        R"json([{"assetNames":["SHIB"],"rank":1,"brackets":[{"leverage":10,"maxDebt":1000000,"maintenanceMarginRate":0.02,"initialMarginRate":0.1112,"fastNum":60000}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.query_liability_coin_leverage_bracket_in_cross_margin_pro_mode();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/leverageBracket");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryLiabilityCoinLeverageBracketInCrossMarginProModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.query_liability_coin_leverage_bracket_in_cross_margin_pro_mode(),
                 common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryMarginAvailableInventory) {
    const std::string example =
        R"json({"assets":{"MATIC":"200","STPT":"30000","TVK":"10000","SHIB":"4000000"},"updateTime":1699272487})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAvailableInventoryParams params{
        .type = QueryMarginAvailableInventoryTypeEnum::Margin};
    const auto res = api.query_margin_available_inventory(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/available-inventory");
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryMarginAvailableInventoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAvailableInventoryParams params{
        .type = QueryMarginAvailableInventoryTypeEnum::Margin};
    EXPECT_THROW((void)api.query_margin_available_inventory(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryMarginPriceindex) {
    const std::string example =
        R"json({"calcTime":1562046418000,"price":"0.00333930","symbol":"BNBBTC"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginPriceindexParams params{.symbol = "BNBBTC"};
    const auto res = api.query_margin_priceindex(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/priceIndex");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryMarginPriceindexBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginPriceindexParams params{.symbol = "BNBBTC"};
    EXPECT_THROW((void)api.query_margin_priceindex(params), common::BadRequestError);
}
