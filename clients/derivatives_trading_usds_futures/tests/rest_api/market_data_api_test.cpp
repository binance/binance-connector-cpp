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
#include <binance/derivatives_trading_usds_futures/rest_api/market_data_api.hpp>

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

MarketDataApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return MarketDataApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiMarketDataApi, AdlRisk) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","adlRisk":"low","updateTime":1597370495002})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AdlRiskParams params{};
    const auto res = api.adl_risk(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/symbolAdlRisk");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, AdlRiskWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","adlRisk":"low","updateTime":1597370495002})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AdlRiskParams params{
        .symbol = "BTCUSDT",
    };
    const auto res = api.adl_risk(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, AdlRiskBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AdlRiskParams params{};
    EXPECT_THROW((void)api.adl_risk(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, AssetIndex) {
    const std::string example =
        R"json({"symbol":"ADAUSD","time":1635740268004,"index":"1.92957370","bidBuffer":"0.10000000","askBuffer":"0.10000000","bidRate":"1.73661633","askRate":"2.12253107","autoExchangeBidBuffer":"0.05000000","autoExchangeAskBuffer":"0.05000000","autoExchangeBidRate":"1.83309501","autoExchangeAskRate":"2.02605238"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AssetIndexParams params{};
    const auto res = api.asset_index(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/assetIndex");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, AssetIndexWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"ADAUSD","time":1635740268004,"index":"1.92957370","bidBuffer":"0.10000000","askBuffer":"0.10000000","bidRate":"1.73661633","askRate":"2.12253107","autoExchangeBidBuffer":"0.05000000","autoExchangeAskBuffer":"0.05000000","autoExchangeBidRate":"1.83309501","autoExchangeAskRate":"2.02605238"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AssetIndexParams params{
        .symbol = "ADAUSD",
    };
    const auto res = api.asset_index(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, AssetIndexBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AssetIndexParams params{};
    EXPECT_THROW((void)api.asset_index(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, Basis) {
    const std::string example =
        R"json([{"indexPrice":"34400.15945055","contractType":"PERPETUAL","basisRate":"0.0004","futuresPrice":"34414.10","annualizedBasisRate":"","basis":"13.94054945","pair":"BTCUSDT","timestamp":1698742800000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BasisParams params{.pair = "BTCUSDT",
                             .contract_type = BasisContractTypeEnum::Perpetual,
                             .period = BasisPeriodEnum::Period5m};
    const auto res = api.basis(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/basis");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, BasisWithOptionalParams) {
    const std::string example =
        R"json([{"indexPrice":"34400.15945055","contractType":"PERPETUAL","basisRate":"0.0004","futuresPrice":"34414.10","annualizedBasisRate":"","basis":"13.94054945","pair":"BTCUSDT","timestamp":1698742800000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BasisParams params{
        .pair = "BTCUSDT",
        .contract_type = BasisContractTypeEnum::Perpetual,
        .period = BasisPeriodEnum::Period5m,
        .limit = 30,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.basis(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, BasisBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const BasisParams params{.pair = "BTCUSDT",
                             .contract_type = BasisContractTypeEnum::Perpetual,
                             .period = BasisPeriodEnum::Period5m};
    EXPECT_THROW((void)api.basis(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, CheckServerTime) {
    const std::string example = R"json({"serverTime":1499827319559})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.check_server_time();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/time");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CheckServerTimeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.check_server_time(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, CompositeIndexSymbolInformation) {
    const std::string example =
        R"json([{"symbol":"DEFIUSDT","time":1589437530011,"component":"baseAsset","baseAssetList":[]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CompositeIndexSymbolInformationParams params{};
    const auto res = api.composite_index_symbol_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/indexInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CompositeIndexSymbolInformationWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"DEFIUSDT","time":1589437530011,"component":"baseAsset","baseAssetList":[]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CompositeIndexSymbolInformationParams params{
        .symbol = "DEFIUSDT",
    };
    const auto res = api.composite_index_symbol_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, CompositeIndexSymbolInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CompositeIndexSymbolInformationParams params{};
    EXPECT_THROW((void)api.composite_index_symbol_information(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, CompressedAggregateTradesList) {
    const std::string example =
        R"json([{"a":26129,"p":"0.01633102","q":"4.70443515","nq":"100","f":27781,"l":27781,"T":1498793709153,"m":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CompressedAggregateTradesListParams params{.symbol = "BTCUSDT"};
    const auto res = api.compressed_aggregate_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/aggTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CompressedAggregateTradesListWithOptionalParams) {
    const std::string example =
        R"json([{"a":26129,"p":"0.01633102","q":"4.70443515","nq":"100","f":27781,"l":27781,"T":1498793709153,"m":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CompressedAggregateTradesListParams params{
        .symbol = "BTCUSDT",
        .from_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
    };
    const auto res = api.compressed_aggregate_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, CompressedAggregateTradesListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CompressedAggregateTradesListParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.compressed_aggregate_trades_list(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, ContinuousContractKlineCandlestickData) {
    const std::string example = R"json([[1607444700000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ContinuousContractKlineCandlestickDataParams params{
        .pair = "BTCUSDT",
        .contract_type = ContinuousContractKlineCandlestickDataContractTypeEnum::Perpetual,
        .interval = ContinuousContractKlineCandlestickDataIntervalEnum::Interval1s};
    const auto res = api.continuous_contract_kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/continuousKlines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ContinuousContractKlineCandlestickDataWithOptionalParams) {
    const std::string example = R"json([[1607444700000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ContinuousContractKlineCandlestickDataParams params{
        .pair = "BTCUSDT",
        .contract_type = ContinuousContractKlineCandlestickDataContractTypeEnum::Perpetual,
        .interval = ContinuousContractKlineCandlestickDataIntervalEnum::Interval1s,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
    };
    const auto res = api.continuous_contract_kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, ContinuousContractKlineCandlestickDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ContinuousContractKlineCandlestickDataParams params{
        .pair = "BTCUSDT",
        .contract_type = ContinuousContractKlineCandlestickDataContractTypeEnum::Perpetual,
        .interval = ContinuousContractKlineCandlestickDataIntervalEnum::Interval1s};
    EXPECT_THROW((void)api.continuous_contract_kline_candlestick_data(params),
                 common::BadRequestError);
}

TEST(RestApiMarketDataApi, ExchangeInformation) {
    const std::string example =
        R"json({"exchangeFilters":[""],"rateLimits":[{"interval":"MINUTE","intervalNum":1,"limit":2400,"rateLimitType":"REQUEST_WEIGHT"}],"serverTime":1565613908500,"assets":[{"asset":"BTC","marginAvailable":true,"autoAssetExchange":"-0.10"}],"symbols":[{"symbol":"BLZUSDT","pair":"BLZUSDT","contractType":"PERPETUAL","deliveryDate":4133404800000,"onboardDate":1598252400000,"status":"TRADING","maintMarginPercent":"2.5000","requiredMarginPercent":"5.0000","baseAsset":"BLZ","quoteAsset":"USDT","marginAsset":"USDT","pricePrecision":5,"quantityPrecision":0,"baseAssetPrecision":8,"quotePrecision":8,"underlyingType":"COIN","underlyingSubType":["STORAGE"],"settlePlan":0,"triggerProtect":"0.15","filters":[{"filterType":"PRICE_FILTER","maxPrice":"300","minPrice":"0.0001","tickSize":"0.0001","maxQty":"10000000","minQty":"1","stepSize":"1","limit":200,"notional":"5.0","multiplierUp":"1.1500","multiplierDown":"0.8500","multiplierDecimal":"4"}],"orderTypes":["LIMIT"],"timeInForce":["GTC"],"liquidationFee":"0.010000","marketTakeBound":"0.30"}],"timezone":"UTC"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.exchange_information();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/exchangeInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ExchangeInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.exchange_information(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetFundingRateHistory) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","fundingRate":"-0.03750000","fundingTime":1570608000000,"markPrice":"34287.54619963","rateType":"Regular"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFundingRateHistoryParams params{};
    const auto res = api.get_funding_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/fundingRate");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetFundingRateHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","fundingRate":"-0.03750000","fundingTime":1570608000000,"markPrice":"34287.54619963","rateType":"Regular"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFundingRateHistoryParams params{
        .symbol = "BTCUSDT",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
    };
    const auto res = api.get_funding_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetFundingRateHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFundingRateHistoryParams params{};
    EXPECT_THROW((void)api.get_funding_rate_history(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetFundingRateInfo) {
    const std::string example =
        R"json([{"symbol":"BLZUSDT","adjustedFundingRateCap":"0.02500000","adjustedFundingRateFloor":"-0.02500000","fundingIntervalHours":8,"disclaimer":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.get_funding_rate_info();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/fundingInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetFundingRateInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.get_funding_rate_info(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, IndexPriceKlineCandlestickData) {
    const std::string example = R"json([[1591256400000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const IndexPriceKlineCandlestickDataParams params{
        .pair = "BTCUSDT", .interval = IndexPriceKlineCandlestickDataIntervalEnum::Interval1m};
    const auto res = api.index_price_kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/indexPriceKlines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, IndexPriceKlineCandlestickDataWithOptionalParams) {
    const std::string example = R"json([[1591256400000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const IndexPriceKlineCandlestickDataParams params{
        .pair = "BTCUSDT",
        .interval = IndexPriceKlineCandlestickDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
    };
    const auto res = api.index_price_kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, IndexPriceKlineCandlestickDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const IndexPriceKlineCandlestickDataParams params{
        .pair = "BTCUSDT", .interval = IndexPriceKlineCandlestickDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.index_price_kline_candlestick_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, KlineCandlestickData) {
    const std::string example = R"json([[1499040000000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlineCandlestickDataParams params{
        .symbol = "BTCUSDT", .interval = KlineCandlestickDataIntervalEnum::Interval1m};
    const auto res = api.kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/klines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, KlineCandlestickDataWithOptionalParams) {
    const std::string example = R"json([[1499040000000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlineCandlestickDataParams params{
        .symbol = "BTCUSDT",
        .interval = KlineCandlestickDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
    };
    const auto res = api.kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, KlineCandlestickDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const KlineCandlestickDataParams params{
        .symbol = "BTCUSDT", .interval = KlineCandlestickDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.kline_candlestick_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, LongShortRatio) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","longShortRatio":"0.1960","longAccount":"0.6622","shortAccount":"0.3378","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const LongShortRatioParams params{.symbol = "BTCUSDT",
                                      .period = LongShortRatioPeriodEnum::Period5m};
    const auto res = api.long_short_ratio(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/globalLongShortAccountRatio");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, LongShortRatioWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","longShortRatio":"0.1960","longAccount":"0.6622","shortAccount":"0.3378","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const LongShortRatioParams params{
        .symbol = "BTCUSDT",
        .period = LongShortRatioPeriodEnum::Period5m,
        .limit = 50,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.long_short_ratio(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, LongShortRatioBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const LongShortRatioParams params{.symbol = "BTCUSDT",
                                      .period = LongShortRatioPeriodEnum::Period5m};
    EXPECT_THROW((void)api.long_short_ratio(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, MarkPrice) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","markPrice":"11793.63104562","indexPrice":"11781.80495970","estimatedSettlePrice":"11781.16138815","lastFundingRate":"0.00038246","interestRate":"0.00010000","nextFundingTime":1597392000000,"time":1597370495002})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarkPriceParams params{};
    const auto res = api.mark_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/premiumIndex");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, MarkPriceWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","markPrice":"11793.63104562","indexPrice":"11781.80495970","estimatedSettlePrice":"11781.16138815","lastFundingRate":"0.00038246","interestRate":"0.00010000","nextFundingTime":1597392000000,"time":1597370495002})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarkPriceParams params{
        .symbol = "BTCUSDT",
    };
    const auto res = api.mark_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, MarkPriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarkPriceParams params{};
    EXPECT_THROW((void)api.mark_price(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, MarkPriceKlineCandlestickData) {
    const std::string example = R"json([[1591256460000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarkPriceKlineCandlestickDataParams params{
        .symbol = "BTCUSDT", .interval = MarkPriceKlineCandlestickDataIntervalEnum::Interval1m};
    const auto res = api.mark_price_kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/markPriceKlines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, MarkPriceKlineCandlestickDataWithOptionalParams) {
    const std::string example = R"json([[1591256460000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarkPriceKlineCandlestickDataParams params{
        .symbol = "BTCUSDT",
        .interval = MarkPriceKlineCandlestickDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
    };
    const auto res = api.mark_price_kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, MarkPriceKlineCandlestickDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarkPriceKlineCandlestickDataParams params{
        .symbol = "BTCUSDT", .interval = MarkPriceKlineCandlestickDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.mark_price_kline_candlestick_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OldTradesLookup) {
    const std::string example =
        R"json([{"id":28457,"price":"4.00000100","qty":"12.00000000","quoteQty":"8000.00","time":1499865549590,"isBuyerMaker":true,"isRPITrade":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OldTradesLookupParams params{.symbol = "BTCUSDT"};
    const auto res = api.old_trades_lookup(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/historicalTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OldTradesLookupWithOptionalParams) {
    const std::string example =
        R"json([{"id":28457,"price":"4.00000100","qty":"12.00000000","quoteQty":"8000.00","time":1499865549590,"isBuyerMaker":true,"isRPITrade":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OldTradesLookupParams params{
        .symbol = "BTCUSDT",
        .limit = 50,
        .from_id = 1,
    };
    const auto res = api.old_trades_lookup(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
}

TEST(RestApiMarketDataApi, OldTradesLookupBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OldTradesLookupParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.old_trades_lookup(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OpenInterest) {
    const std::string example =
        R"json({"openInterest":"10659.509","symbol":"BTCUSDT","time":1589437530011})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OpenInterestParams params{.symbol = "BTCUSDT"};
    const auto res = api.open_interest(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/openInterest");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OpenInterestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OpenInterestParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.open_interest(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OpenInterestStatistics) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","sumOpenInterest":"20403.12345678","sumOpenInterestValue":"176196512.12345678","CMCCirculatingSupply":"165880.538","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OpenInterestStatisticsParams params{.symbol = "BTCUSDT",
                                              .period = OpenInterestStatisticsPeriodEnum::Period5m};
    const auto res = api.open_interest_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/openInterestHist");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OpenInterestStatisticsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","sumOpenInterest":"20403.12345678","sumOpenInterestValue":"176196512.12345678","CMCCirculatingSupply":"165880.538","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OpenInterestStatisticsParams params{
        .symbol = "BTCUSDT",
        .period = OpenInterestStatisticsPeriodEnum::Period5m,
        .limit = 50,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.open_interest_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, OpenInterestStatisticsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OpenInterestStatisticsParams params{.symbol = "BTCUSDT",
                                              .period = OpenInterestStatisticsPeriodEnum::Period5m};
    EXPECT_THROW((void)api.open_interest_statistics(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OrderBook) {
    const std::string example =
        R"json({"lastUpdateId":1027024,"E":1589436922972,"T":1589436922959,"bids":[["4.00000000","431.00000000"]],"asks":[["4.00000200","12.00000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderBookParams params{.symbol = "BTCUSDT"};
    const auto res = api.order_book(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/depth");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OrderBookWithOptionalParams) {
    const std::string example =
        R"json({"lastUpdateId":1027024,"E":1589436922972,"T":1589436922959,"bids":[["4.00000000","431.00000000"]],"asks":[["4.00000200","12.00000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderBookParams params{
        .symbol = "BTCUSDT",
        .limit = 50,
    };
    const auto res = api.order_book(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, OrderBookBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderBookParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.order_book(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, PremiumIndexKlineData) {
    const std::string example = R"json([[1691603820000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PremiumIndexKlineDataParams params{
        .symbol = "BTCUSDT", .interval = PremiumIndexKlineDataIntervalEnum::Interval1m};
    const auto res = api.premium_index_kline_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/premiumIndexKlines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, PremiumIndexKlineDataWithOptionalParams) {
    const std::string example = R"json([[1691603820000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PremiumIndexKlineDataParams params{
        .symbol = "BTCUSDT",
        .interval = PremiumIndexKlineDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 50,
    };
    const auto res = api.premium_index_kline_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, PremiumIndexKlineDataBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PremiumIndexKlineDataParams params{
        .symbol = "BTCUSDT", .interval = PremiumIndexKlineDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.premium_index_kline_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QuarterlyContractSettlementPrice) {
    const std::string example = R"json([{"deliveryTime":1695945600000,"deliveryPrice":27103}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuarterlyContractSettlementPriceParams params{.pair = "BTCUSDT"};
    const auto res = api.quarterly_contract_settlement_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/delivery-price");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QuarterlyContractSettlementPriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuarterlyContractSettlementPriceParams params{.pair = "BTCUSDT"};
    EXPECT_THROW((void)api.quarterly_contract_settlement_price(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryIndexPriceConstituents) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","time":1745401553408,"constituents":[]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryIndexPriceConstituentsParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_index_price_constituents(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/constituents");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryIndexPriceConstituentsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryIndexPriceConstituentsParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_index_price_constituents(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryInsuranceFundBalanceSnapshot) {
    const std::string example = R"json({"symbols":[],"assets":[]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryInsuranceFundBalanceSnapshotParams params{};
    const auto res = api.query_insurance_fund_balance_snapshot(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/insuranceBalance");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryInsuranceFundBalanceSnapshotWithOptionalParams) {
    const std::string example = R"json({"symbols":[],"assets":[]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryInsuranceFundBalanceSnapshotParams params{
        .symbol = "BNBUSDT",
    };
    const auto res = api.query_insurance_fund_balance_snapshot(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryInsuranceFundBalanceSnapshotBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryInsuranceFundBalanceSnapshotParams params{};
    EXPECT_THROW((void)api.query_insurance_fund_balance_snapshot(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, RecentTradesList) {
    const std::string example =
        R"json([{"id":28457,"price":"4.00000100","qty":"12.00000000","quoteQty":"48.00","time":1499865549590,"isBuyerMaker":true,"isRPITrade":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RecentTradesListParams params{.symbol = "BTCUSDT"};
    const auto res = api.recent_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/trades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, RecentTradesListWithOptionalParams) {
    const std::string example =
        R"json([{"id":28457,"price":"4.00000100","qty":"12.00000000","quoteQty":"48.00","time":1499865549590,"isBuyerMaker":true,"isRPITrade":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RecentTradesListParams params{
        .symbol = "BTCUSDT",
        .limit = 50,
    };
    const auto res = api.recent_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, RecentTradesListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RecentTradesListParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.recent_trades_list(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, RpiOrderBook) {
    const std::string example =
        R"json({"lastUpdateId":1027024,"E":1589436922972,"T":1589436922959,"bids":[["4.00000000","431.00000000"]],"asks":[["4.00000200","12.00000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RpiOrderBookParams params{.symbol = "BTCUSDT"};
    const auto res = api.rpi_order_book(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/rpiDepth");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, RpiOrderBookWithOptionalParams) {
    const std::string example =
        R"json({"lastUpdateId":1027024,"E":1589436922972,"T":1589436922959,"bids":[["4.00000000","431.00000000"]],"asks":[["4.00000200","12.00000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RpiOrderBookParams params{
        .symbol = "BTCUSDT",
        .limit = 1000,
    };
    const auto res = api.rpi_order_book(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
}

TEST(RestApiMarketDataApi, RpiOrderBookBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RpiOrderBookParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.rpi_order_book(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, SymbolOrderBookTicker) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","bidPrice":"4.00000000","bidQty":"431.00000000","askPrice":"4.00000200","askQty":"9.00000000","time":1589437530011})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolOrderBookTickerParams params{};
    const auto res = api.symbol_order_book_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/ticker/bookTicker");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolOrderBookTickerWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","bidPrice":"4.00000000","bidQty":"431.00000000","askPrice":"4.00000200","askQty":"9.00000000","time":1589437530011})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolOrderBookTickerParams params{
        .symbol = "BTCUSDT",
    };
    const auto res = api.symbol_order_book_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolOrderBookTickerBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SymbolOrderBookTickerParams params{};
    EXPECT_THROW((void)api.symbol_order_book_ticker(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, SymbolPriceTicker) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","price":"6000.01","time":1589437530011})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolPriceTickerParams params{};
    const auto res = api.symbol_price_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/ticker/price");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolPriceTickerWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","price":"6000.01","time":1589437530011})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolPriceTickerParams params{
        .symbol = "BTCUSDT",
    };
    const auto res = api.symbol_price_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolPriceTickerBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SymbolPriceTickerParams params{};
    EXPECT_THROW((void)api.symbol_price_ticker(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, SymbolPriceTickerV2) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","price":"6000.01","time":1589437530011})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolPriceTickerV2Params params{};
    const auto res = api.symbol_price_ticker_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v2/ticker/price");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolPriceTickerV2WithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","price":"6000.01","time":1589437530011})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolPriceTickerV2Params params{
        .symbol = "BTCUSDT",
    };
    const auto res = api.symbol_price_ticker_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolPriceTickerV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SymbolPriceTickerV2Params params{};
    EXPECT_THROW((void)api.symbol_price_ticker_v2(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TakerBuySellVolume) {
    const std::string example =
        R"json([{"buySellRatio":"1.5586","buyVol":"387.3300","sellVol":"248.5030","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TakerBuySellVolumeParams params{.symbol = "BTCUSDT",
                                          .period = TakerBuySellVolumePeriodEnum::Period5m};
    const auto res = api.taker_buy_sell_volume(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/takerlongshortRatio");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TakerBuySellVolumeWithOptionalParams) {
    const std::string example =
        R"json([{"buySellRatio":"1.5586","buyVol":"387.3300","sellVol":"248.5030","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TakerBuySellVolumeParams params{
        .symbol = "BTCUSDT",
        .period = TakerBuySellVolumePeriodEnum::Period5m,
        .limit = 50,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.taker_buy_sell_volume(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, TakerBuySellVolumeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TakerBuySellVolumeParams params{.symbol = "BTCUSDT",
                                          .period = TakerBuySellVolumePeriodEnum::Period5m};
    EXPECT_THROW((void)api.taker_buy_sell_volume(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TestConnectivity) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.test_connectivity();
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/ping");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TestConnectivityBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.test_connectivity(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, Ticker24hrPriceChangeStatistics) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","priceChange":"-94.99999800","priceChangePercent":"-95.960","weightedAvgPrice":"0.29628482","lastPrice":"4.00000200","lastQty":"200.00000000","openPrice":"99.00000000","highPrice":"100.00000000","lowPrice":"0.10000000","volume":"8913.30000000","quoteVolume":"15.30000000","openTime":1499783499040,"closeTime":1499869899040,"firstId":28385,"lastId":28460,"count":76})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const Ticker24hrPriceChangeStatisticsParams params{};
    const auto res = api.ticker24hr_price_change_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/ticker/24hr");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, Ticker24hrPriceChangeStatisticsWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","priceChange":"-94.99999800","priceChangePercent":"-95.960","weightedAvgPrice":"0.29628482","lastPrice":"4.00000200","lastQty":"200.00000000","openPrice":"99.00000000","highPrice":"100.00000000","lowPrice":"0.10000000","volume":"8913.30000000","quoteVolume":"15.30000000","openTime":1499783499040,"closeTime":1499869899040,"firstId":28385,"lastId":28460,"count":76})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const Ticker24hrPriceChangeStatisticsParams params{
        .symbol = "BTCUSDT",
    };
    const auto res = api.ticker24hr_price_change_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
}

TEST(RestApiMarketDataApi, Ticker24hrPriceChangeStatisticsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const Ticker24hrPriceChangeStatisticsParams params{};
    EXPECT_THROW((void)api.ticker24hr_price_change_statistics(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioAccounts) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","longShortRatio":"1.8105","longAccount":"0.6442","shortAccount":"0.3558","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TopTraderLongShortRatioAccountsParams params{
        .symbol = "BTCUSDT", .period = TopTraderLongShortRatioAccountsPeriodEnum::Period5m};
    const auto res = api.top_trader_long_short_ratio_accounts(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/topLongShortAccountRatio");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioAccountsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","longShortRatio":"1.8105","longAccount":"0.6442","shortAccount":"0.3558","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TopTraderLongShortRatioAccountsParams params{
        .symbol = "BTCUSDT",
        .period = TopTraderLongShortRatioAccountsPeriodEnum::Period5m,
        .limit = 50,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.top_trader_long_short_ratio_accounts(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioAccountsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TopTraderLongShortRatioAccountsParams params{
        .symbol = "BTCUSDT", .period = TopTraderLongShortRatioAccountsPeriodEnum::Period5m};
    EXPECT_THROW((void)api.top_trader_long_short_ratio_accounts(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioPositions) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","longShortRatio":"1.4342","longAccount":"0.5344","shortAccount":"0.4238","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TopTraderLongShortRatioPositionsParams params{
        .symbol = "BTCUSDT", .period = TopTraderLongShortRatioPositionsPeriodEnum::Period5m};
    const auto res = api.top_trader_long_short_ratio_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/topLongShortPositionRatio");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioPositionsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","longShortRatio":"1.4342","longAccount":"0.5344","shortAccount":"0.4238","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TopTraderLongShortRatioPositionsParams params{
        .symbol = "BTCUSDT",
        .period = TopTraderLongShortRatioPositionsPeriodEnum::Period5m,
        .limit = 50,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.top_trader_long_short_ratio_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioPositionsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TopTraderLongShortRatioPositionsParams params{
        .symbol = "BTCUSDT", .period = TopTraderLongShortRatioPositionsPeriodEnum::Period5m};
    EXPECT_THROW((void)api.top_trader_long_short_ratio_positions(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TradingSchedule) {
    const std::string example = R"json({"updateTime":1761286643918,"marketSchedules":{}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.trading_schedule();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/tradingSchedule");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TradingScheduleBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.trading_schedule(), common::BadRequestError);
}
