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
#include <binance/derivatives_trading_coin_futures/rest_api/market_data_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_coin_futures::rest_api;
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

TEST(RestApiMarketDataApi, Basis) {
    const std::string example =
        R"json([{"indexPrice":"29269.93972727","contractType":"CURRENT_QUARTER","basisRate":"0.0024","futuresPrice":"29341.3","annualizedBasisRate":"0.0283","basis":"71.36027273","pair":"BTCUSD","timestamp":1653381600000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BasisParams params{.pair = "pair_example",
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
        R"json([{"indexPrice":"29269.93972727","contractType":"CURRENT_QUARTER","basisRate":"0.0024","futuresPrice":"29341.3","annualizedBasisRate":"0.0283","basis":"71.36027273","pair":"BTCUSD","timestamp":1653381600000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BasisParams params{
        .pair = "pair_example",
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
    const BasisParams params{.pair = "pair_example",
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
    EXPECT_EQ(rec.path(), "/dapi/v1/time");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CheckServerTimeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.check_server_time(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, CompressedAggregateTradesList) {
    const std::string example =
        R"json([{"a":416690,"p":"9642.4","q":"3","f":595259,"l":595259,"T":1591250548649,"m":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CompressedAggregateTradesListParams params{.symbol = "symbol_example"};
    const auto res = api.compressed_aggregate_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/aggTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, CompressedAggregateTradesListWithOptionalParams) {
    const std::string example =
        R"json([{"a":416690,"p":"9642.4","q":"3","f":595259,"l":595259,"T":1591250548649,"m":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CompressedAggregateTradesListParams params{
        .symbol = "symbol_example",
        .from_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
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
    const CompressedAggregateTradesListParams params{.symbol = "symbol_example"};
    EXPECT_THROW((void)api.compressed_aggregate_trades_list(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, ContinuousContractKlineCandlestickData) {
    const std::string example = R"json([[1591258320000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ContinuousContractKlineCandlestickDataParams params{
        .pair = "BTCUSD",
        .contract_type = ContinuousContractKlineCandlestickDataContractTypeEnum::Perpetual,
        .interval = ContinuousContractKlineCandlestickDataIntervalEnum::Interval1m};
    const auto res = api.continuous_contract_kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/continuousKlines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ContinuousContractKlineCandlestickDataWithOptionalParams) {
    const std::string example = R"json([[1591258320000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ContinuousContractKlineCandlestickDataParams params{
        .pair = "BTCUSD",
        .contract_type = ContinuousContractKlineCandlestickDataContractTypeEnum::Perpetual,
        .interval = ContinuousContractKlineCandlestickDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
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
        .pair = "BTCUSD",
        .contract_type = ContinuousContractKlineCandlestickDataContractTypeEnum::Perpetual,
        .interval = ContinuousContractKlineCandlestickDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.continuous_contract_kline_candlestick_data(params),
                 common::BadRequestError);
}

TEST(RestApiMarketDataApi, ExchangeInformation) {
    const std::string example =
        R"json({"rateLimits":[{"interval":"MINUTE","intervalNum":1,"limit":2400,"rateLimitType":"REQUEST_WEIGHT"}],"serverTime":1565613908500,"symbols":[{"filters":[{"filterType":"PRICE_FILTER","maxPrice":"100000","minPrice":"0.1","tickSize":"0.1","maxQty":"100000","minQty":"1","stepSize":"1","limit":200,"multiplierUp":"1.0500","multiplierDown":"0.9500","multiplierDecimal":"4"}],"orderTypes":["LIMIT"],"timeInForce":["GTC"],"liquidationFee":"0.010000","marketTakeBound":"0.30","symbol":"BTCUSD_200925","pair":"BTCUSD","contractType":"CURRENT_QUARTER","deliveryDate":1601020800000,"onboardDate":1590739200000,"contractStatus":"TRADING","contractSize":100,"quoteAsset":"USD","baseAsset":"BTC","marginAsset":"BTC","pricePrecision":1,"quantityPrecision":0,"baseAssetPrecision":8,"quotePrecision":8,"equalQtyPrecision":4,"triggerProtect":"0.0500","maintMarginPercent":"2.5000","requiredMarginPercent":"5.0000","underlyingType":"COIN"}],"timezone":"UTC"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.exchange_information();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/exchangeInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, ExchangeInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.exchange_information(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetFundingRateHistoryOfPerpetualFutures) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_PERP","fundingTime":1596038400000,"fundingRate":"-0.00300000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFundingRateHistoryOfPerpetualFuturesParams params{.symbol = "symbol_example"};
    const auto res = api.get_funding_rate_history_of_perpetual_futures(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/fundingRate");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetFundingRateHistoryOfPerpetualFuturesWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_PERP","fundingTime":1596038400000,"fundingRate":"-0.00300000"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFundingRateHistoryOfPerpetualFuturesParams params{
        .symbol = "symbol_example",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
    };
    const auto res = api.get_funding_rate_history_of_perpetual_futures(params);
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

TEST(RestApiMarketDataApi, GetFundingRateHistoryOfPerpetualFuturesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFundingRateHistoryOfPerpetualFuturesParams params{.symbol = "symbol_example"};
    EXPECT_THROW((void)api.get_funding_rate_history_of_perpetual_futures(params),
                 common::BadRequestError);
}

TEST(RestApiMarketDataApi, GetFundingRateInfo) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_PERP","adjustedFundingRateCap":"0.02500000","adjustedFundingRateFloor":"-0.02500000","fundingIntervalHours":8,"disclaimer":false}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.get_funding_rate_info();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/fundingInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, GetFundingRateInfoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.get_funding_rate_info(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, IndexPriceAndMarkPrice) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_PERP","pair":"BTCUSD","markPrice":"11029.69574559","indexPrice":"10979.14437500","estimatedSettlePrice":"10981.74168236","lastFundingRate":"0.00071003","interestRate":"0.00010000","nextFundingTime":1596096000000,"time":1596094042000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const IndexPriceAndMarkPriceParams params{};
    const auto res = api.index_price_and_mark_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/premiumIndex");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, IndexPriceAndMarkPriceWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_PERP","pair":"BTCUSD","markPrice":"11029.69574559","indexPrice":"10979.14437500","estimatedSettlePrice":"10981.74168236","lastFundingRate":"0.00071003","interestRate":"0.00010000","nextFundingTime":1596096000000,"time":1596094042000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const IndexPriceAndMarkPriceParams params{
        .symbol = "BTCUSD_PERP",
        .pair = "BTCUSD",
    };
    const auto res = api.index_price_and_mark_price(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
}

TEST(RestApiMarketDataApi, IndexPriceAndMarkPriceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const IndexPriceAndMarkPriceParams params{};
    EXPECT_THROW((void)api.index_price_and_mark_price(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, IndexPriceKlineCandlestickData) {
    const std::string example = R"json([[1591256400000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const IndexPriceKlineCandlestickDataParams params{
        .pair = "BTCUSD", .interval = IndexPriceKlineCandlestickDataIntervalEnum::Interval1m};
    const auto res = api.index_price_kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/indexPriceKlines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, IndexPriceKlineCandlestickDataWithOptionalParams) {
    const std::string example = R"json([[1591256400000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const IndexPriceKlineCandlestickDataParams params{
        .pair = "BTCUSD",
        .interval = IndexPriceKlineCandlestickDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
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
        .pair = "BTCUSD", .interval = IndexPriceKlineCandlestickDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.index_price_kline_candlestick_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, KlineCandlestickData) {
    const std::string example = R"json([[1591258320000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlineCandlestickDataParams params{
        .symbol = "BTCUSD", .interval = KlineCandlestickDataIntervalEnum::Interval1m};
    const auto res = api.kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/klines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, KlineCandlestickDataWithOptionalParams) {
    const std::string example = R"json([[1591258320000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const KlineCandlestickDataParams params{
        .symbol = "BTCUSD",
        .interval = KlineCandlestickDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
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
        .symbol = "BTCUSD", .interval = KlineCandlestickDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.kline_candlestick_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, LongShortRatio) {
    const std::string example =
        R"json([{"pair":"BTCUSD","longShortRatio":"0.1960","longAccount":"0.6622","shortAccount":"0.3378","timestamp":1583139600000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const LongShortRatioParams params{.pair = "pair_example",
                                      .period = LongShortRatioPeriodEnum::Period5m};
    const auto res = api.long_short_ratio(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/globalLongShortAccountRatio");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, LongShortRatioWithOptionalParams) {
    const std::string example =
        R"json([{"pair":"BTCUSD","longShortRatio":"0.1960","longAccount":"0.6622","shortAccount":"0.3378","timestamp":1583139600000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const LongShortRatioParams params{
        .pair = "pair_example",
        .period = LongShortRatioPeriodEnum::Period5m,
        .contract_type = LongShortRatioContractTypeEnum::Perpetual,
        .limit = 30,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.long_short_ratio(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, LongShortRatioBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const LongShortRatioParams params{.pair = "pair_example",
                                      .period = LongShortRatioPeriodEnum::Period5m};
    EXPECT_THROW((void)api.long_short_ratio(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, MarkPriceKlineCandlestickData) {
    const std::string example = R"json([[1591256400000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarkPriceKlineCandlestickDataParams params{
        .symbol = "BTCUSD", .interval = MarkPriceKlineCandlestickDataIntervalEnum::Interval1m};
    const auto res = api.mark_price_kline_candlestick_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/markPriceKlines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, MarkPriceKlineCandlestickDataWithOptionalParams) {
    const std::string example = R"json([[1591256400000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarkPriceKlineCandlestickDataParams params{
        .symbol = "BTCUSD",
        .interval = MarkPriceKlineCandlestickDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
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
        .symbol = "BTCUSD", .interval = MarkPriceKlineCandlestickDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.mark_price_kline_candlestick_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OldTradesLookup) {
    const std::string example =
        R"json([{"id":595103,"price":"9642.2","qty":"1","baseQty":"0.01037108","time":1499865549590,"isBuyerMaker":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OldTradesLookupParams params{.symbol = "symbol_example"};
    const auto res = api.old_trades_lookup(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/historicalTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OldTradesLookupWithOptionalParams) {
    const std::string example =
        R"json([{"id":595103,"price":"9642.2","qty":"1","baseQty":"0.01037108","time":1499865549590,"isBuyerMaker":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OldTradesLookupParams params{
        .symbol = "symbol_example",
        .limit = 30,
        .from_id = 595103,
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
    const OldTradesLookupParams params{.symbol = "symbol_example"};
    EXPECT_THROW((void)api.old_trades_lookup(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OpenInterest) {
    const std::string example =
        R"json({"symbol":"BTCUSD_200626","pair":"BTCUSD","openInterest":"15004","contractType":"CURRENT_QUARTER","time":1591261042378})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OpenInterestParams params{.symbol = "BTCUSD_200626"};
    const auto res = api.open_interest(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/openInterest");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OpenInterestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OpenInterestParams params{.symbol = "BTCUSD_200626"};
    EXPECT_THROW((void)api.open_interest(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OpenInterestStatistics) {
    const std::string example =
        R"json([{"pair":"BTCUSD","contractType":"CURRENT_QUARTER","sumOpenInterest":"20403","sumOpenInterestValue":"176196512.23400000","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OpenInterestStatisticsParams params{.pair = "BTCUSD",
                                              .period = OpenInterestStatisticsPeriodEnum::Period5m};
    const auto res = api.open_interest_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/openInterestHist");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OpenInterestStatisticsWithOptionalParams) {
    const std::string example =
        R"json([{"pair":"BTCUSD","contractType":"CURRENT_QUARTER","sumOpenInterest":"20403","sumOpenInterestValue":"176196512.23400000","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OpenInterestStatisticsParams params{
        .pair = "BTCUSD",
        .period = OpenInterestStatisticsPeriodEnum::Period5m,
        .contract_type = OpenInterestStatisticsContractTypeEnum::Perpetual,
        .limit = 30,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.open_interest_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, OpenInterestStatisticsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OpenInterestStatisticsParams params{.pair = "BTCUSD",
                                              .period = OpenInterestStatisticsPeriodEnum::Period5m};
    EXPECT_THROW((void)api.open_interest_statistics(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, OrderBook) {
    const std::string example =
        R"json({"lastUpdateId":16769853,"symbol":"BTCUSD_PERP","pair":"BTCUSD","E":1591250106370,"T":1591250106368,"bids":[["9638.00000000","431.00000000"]],"asks":[["9638.20000000","12.00000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderBookParams params{.symbol = "BTCUSD_PERP"};
    const auto res = api.order_book(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/depth");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, OrderBookWithOptionalParams) {
    const std::string example =
        R"json({"lastUpdateId":16769853,"symbol":"BTCUSD_PERP","pair":"BTCUSD","E":1591250106370,"T":1591250106368,"bids":[["9638.00000000","431.00000000"]],"asks":[["9638.20000000","12.00000000"]]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderBookParams params{
        .symbol = "BTCUSD_PERP",
        .limit = 500,
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
    const OrderBookParams params{.symbol = "BTCUSD_PERP"};
    EXPECT_THROW((void)api.order_book(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, PremiumIndexKlineData) {
    const std::string example = R"json([[1691603820000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PremiumIndexKlineDataParams params{
        .symbol = "BTCUSD", .interval = PremiumIndexKlineDataIntervalEnum::Interval1m};
    const auto res = api.premium_index_kline_data(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/premiumIndexKlines");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interval="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, PremiumIndexKlineDataWithOptionalParams) {
    const std::string example = R"json([[1691603820000]])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PremiumIndexKlineDataParams params{
        .symbol = "BTCUSD",
        .interval = PremiumIndexKlineDataIntervalEnum::Interval1m,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
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
        .symbol = "BTCUSD", .interval = PremiumIndexKlineDataIntervalEnum::Interval1m};
    EXPECT_THROW((void)api.premium_index_kline_data(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, QueryIndexPriceConstituents) {
    const std::string example =
        R"json({"symbol":"BTCUSD","time":1697422647853,"constituents":[{"exchange":"bitstamp","symbol":"btcusd","price":"94057.03000000","weight":"0.25000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryIndexPriceConstituentsParams params{.symbol = "BTCUSD"};
    const auto res = api.query_index_price_constituents(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/constituents");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, QueryIndexPriceConstituentsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryIndexPriceConstituentsParams params{.symbol = "BTCUSD"};
    EXPECT_THROW((void)api.query_index_price_constituents(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, RecentTradesList) {
    const std::string example =
        R"json([{"id":28457,"price":"9635.0","qty":"1","baseQty":"0.01037883","time":1591250192508,"isBuyerMaker":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RecentTradesListParams params{.symbol = "BTCUSD"};
    const auto res = api.recent_trades_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/trades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, RecentTradesListWithOptionalParams) {
    const std::string example =
        R"json([{"id":28457,"price":"9635.0","qty":"1","baseQty":"0.01037883","time":1591250192508,"isBuyerMaker":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RecentTradesListParams params{
        .symbol = "BTCUSD",
        .limit = 30,
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
    const RecentTradesListParams params{.symbol = "BTCUSD"};
    EXPECT_THROW((void)api.recent_trades_list(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, SymbolOrderBookTicker) {
    const std::string example =
        R"json([{"lastUpdateId":1027024,"symbol":"BTCUSD_200626","pair":"BTCUSD","bidPrice":"9650.1","bidQty":"16","askPrice":"9650.3","askQty":"7","time":1591257300345}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolOrderBookTickerParams params{};
    const auto res = api.symbol_order_book_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/ticker/bookTicker");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolOrderBookTickerWithOptionalParams) {
    const std::string example =
        R"json([{"lastUpdateId":1027024,"symbol":"BTCUSD_200626","pair":"BTCUSD","bidPrice":"9650.1","bidQty":"16","askPrice":"9650.3","askQty":"7","time":1591257300345}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolOrderBookTickerParams params{
        .symbol = "BTCUSD_200626",
        .pair = "BTCUSD",
    };
    const auto res = api.symbol_order_book_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolOrderBookTickerBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SymbolOrderBookTickerParams params{};
    EXPECT_THROW((void)api.symbol_order_book_ticker(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, SymbolPriceTicker) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200626","ps":"BTCUSD","price":"9647.8","time":1591257246176}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolPriceTickerParams params{};
    const auto res = api.symbol_price_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/ticker/price");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolPriceTickerWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200626","ps":"BTCUSD","price":"9647.8","time":1591257246176}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SymbolPriceTickerParams params{
        .symbol = "BTCUSD_200626",
        .pair = "BTCUSD",
    };
    const auto res = api.symbol_price_ticker(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
}

TEST(RestApiMarketDataApi, SymbolPriceTickerBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SymbolPriceTickerParams params{};
    EXPECT_THROW((void)api.symbol_price_ticker(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TakerBuySellVolume) {
    const std::string example =
        R"json([{"pair":"BTCUSD","contractType":"CURRENT_QUARTER","takerBuyVol":"387","takerSellVol":"248","takerBuyVolValue":"2342.1220","takerSellVolValue":"4213.9800","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TakerBuySellVolumeParams params{.pair = "BTCUSD",
                                          .contract_type = TakerBuySellVolumeContractTypeEnum::All,
                                          .period = TakerBuySellVolumePeriodEnum::Period5m};
    const auto res = api.taker_buy_sell_volume(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/takerBuySellVol");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TakerBuySellVolumeWithOptionalParams) {
    const std::string example =
        R"json([{"pair":"BTCUSD","contractType":"CURRENT_QUARTER","takerBuyVol":"387","takerSellVol":"248","takerBuyVolValue":"2342.1220","takerSellVolValue":"4213.9800","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TakerBuySellVolumeParams params{
        .pair = "BTCUSD",
        .contract_type = TakerBuySellVolumeContractTypeEnum::All,
        .period = TakerBuySellVolumePeriodEnum::Period5m,
        .limit = 30,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.taker_buy_sell_volume(params);
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

TEST(RestApiMarketDataApi, TakerBuySellVolumeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TakerBuySellVolumeParams params{.pair = "BTCUSD",
                                          .contract_type = TakerBuySellVolumeContractTypeEnum::All,
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
    EXPECT_EQ(rec.path(), "/dapi/v1/ping");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TestConnectivityBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.test_connectivity(), common::BadRequestError);
}

TEST(RestApiMarketDataApi, Ticker24hrPriceChangeStatistics) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200925","pair":"BTCUSD","priceChange":"136.6","priceChangePercent":"1.436","weightedAvgPrice":"9547.3","lastPrice":"9651.6","lastQty":"1","openPrice":"9515.0","highPrice":"9687.0","lowPrice":"9499.5","volume":"494109","baseVolume":"5192.94797687","openTime":1591170300000,"closeTime":1591256718418,"firstId":600507,"lastId":697803,"count":97297}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const Ticker24hrPriceChangeStatisticsParams params{};
    const auto res = api.ticker24hr_price_change_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/ticker/24hr");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, Ticker24hrPriceChangeStatisticsWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_200925","pair":"BTCUSD","priceChange":"136.6","priceChangePercent":"1.436","weightedAvgPrice":"9547.3","lastPrice":"9651.6","lastQty":"1","openPrice":"9515.0","highPrice":"9687.0","lowPrice":"9499.5","volume":"494109","baseVolume":"5192.94797687","openTime":1591170300000,"closeTime":1591256718418,"firstId":600507,"lastId":697803,"count":97297}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const Ticker24hrPriceChangeStatisticsParams params{
        .symbol = "BTCUSD_200925",
        .pair = "BTCUSD",
    };
    const auto res = api.ticker24hr_price_change_statistics(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
}

TEST(RestApiMarketDataApi, Ticker24hrPriceChangeStatisticsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const Ticker24hrPriceChangeStatisticsParams params{};
    EXPECT_THROW((void)api.ticker24hr_price_change_statistics(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioAccounts) {
    const std::string example =
        R"json([{"pair":"BTCUSD","longShortRatio":"1.8105","longAccount":"0.6442","shortAccount":"0.3558","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TopTraderLongShortRatioAccountsParams params{
        .pair = "BTCUSD", .period = TopTraderLongShortRatioAccountsPeriodEnum::Period5m};
    const auto res = api.top_trader_long_short_ratio_accounts(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/topLongShortAccountRatio");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioAccountsWithOptionalParams) {
    const std::string example =
        R"json([{"pair":"BTCUSD","longShortRatio":"1.8105","longAccount":"0.6442","shortAccount":"0.3558","timestamp":1591261042378}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TopTraderLongShortRatioAccountsParams params{
        .pair = "BTCUSD",
        .period = TopTraderLongShortRatioAccountsPeriodEnum::Period5m,
        .contract_type = TopTraderLongShortRatioAccountsContractTypeEnum::Perpetual,
        .limit = 30,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.top_trader_long_short_ratio_accounts(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioAccountsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TopTraderLongShortRatioAccountsParams params{
        .pair = "BTCUSD", .period = TopTraderLongShortRatioAccountsPeriodEnum::Period5m};
    EXPECT_THROW((void)api.top_trader_long_short_ratio_accounts(params), common::BadRequestError);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioPositions) {
    const std::string example =
        R"json([{"pair":"BTCUSD","longShortRatio":"0.7869","longPosition":"0.6442","shortPosition":"0.4404","timestamp":1592870400000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TopTraderLongShortRatioPositionsParams params{
        .pair = "BTCUSD", .period = TopTraderLongShortRatioPositionsPeriodEnum::Period5m};
    const auto res = api.top_trader_long_short_ratio_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/futures/data/topLongShortPositionRatio");
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioPositionsWithOptionalParams) {
    const std::string example =
        R"json([{"pair":"BTCUSD","longShortRatio":"0.7869","longPosition":"0.6442","shortPosition":"0.4404","timestamp":1592870400000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TopTraderLongShortRatioPositionsParams params{
        .pair = "BTCUSD",
        .period = TopTraderLongShortRatioPositionsPeriodEnum::Period5m,
        .contract_type = TopTraderLongShortRatioPositionsContractTypeEnum::Perpetual,
        .limit = 30,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
    };
    const auto res = api.top_trader_long_short_ratio_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("period="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("contractType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
}

TEST(RestApiMarketDataApi, TopTraderLongShortRatioPositionsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TopTraderLongShortRatioPositionsParams params{
        .pair = "BTCUSD", .period = TopTraderLongShortRatioPositionsPeriodEnum::Period5m};
    EXPECT_THROW((void)api.top_trader_long_short_ratio_positions(params), common::BadRequestError);
}
