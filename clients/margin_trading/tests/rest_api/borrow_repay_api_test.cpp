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
#include <binance/margin_trading/rest_api/borrow_repay_api.hpp>

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

BorrowRepayApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return BorrowRepayApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiBorrowRepayApi, GetFutureHourlyInterestRate) {
    const std::string example =
        R"json([{"asset":"BTC","nextHourlyInterestRate":"0.00000571"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFutureHourlyInterestRateParams params{
        .assets = "BTC,ETH", .is_isolated = GetFutureHourlyInterestRateIsIsolatedEnum::True_};
    const auto res = api.get_future_hourly_interest_rate(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/next-hourly-interest-rate");
    EXPECT_NE((rec.query() + "&" + rec.body).find("assets="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, GetFutureHourlyInterestRateBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFutureHourlyInterestRateParams params{
        .assets = "BTC,ETH", .is_isolated = GetFutureHourlyInterestRateIsIsolatedEnum::True_};
    EXPECT_THROW((void)api.get_future_hourly_interest_rate(params), common::BadRequestError);
}

TEST(RestApiBorrowRepayApi, GetInterestHistory) {
    const std::string example =
        R"json({"rows":[{"txId":1352286576452864800,"interestAccuredTime":1672160400000,"asset":"USDT","rawAsset":"USDT","principal":"45.3313","interest":"0.00024995","interestRate":"0.00013233","type":"ON_BORROW","isolatedSymbol":"BNBUSDT"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetInterestHistoryParams params{};
    const auto res = api.get_interest_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/interestHistory");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, GetInterestHistoryWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"txId":1352286576452864800,"interestAccuredTime":1672160400000,"asset":"USDT","rawAsset":"USDT","principal":"45.3313","interest":"0.00024995","interestRate":"0.00013233","type":"ON_BORROW","isolatedSymbol":"BNBUSDT"}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetInterestHistoryParams params{
        .asset = "USDT",
        .isolated_symbol = "BNBUSDT",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_interest_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isolatedSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, GetInterestHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetInterestHistoryParams params{};
    EXPECT_THROW((void)api.get_interest_history(params), common::BadRequestError);
}

TEST(RestApiBorrowRepayApi, MarginAccountBorrowRepay) {
    const std::string example = R"json({"tranId":100000001})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountBorrowRepayParams params{.asset = "USDT",
                                                .is_isolated =
                                                    MarginAccountBorrowRepayIsIsolatedEnum::True_,
                                                .amount = "1.0",
                                                .type = MarginAccountBorrowRepayTypeEnum::Borrow};
    const auto res = api.margin_account_borrow_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/borrow-repay");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, MarginAccountBorrowRepayWithOptionalParams) {
    const std::string example = R"json({"tranId":100000001})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountBorrowRepayParams params{
        .asset = "USDT",
        .is_isolated = MarginAccountBorrowRepayIsIsolatedEnum::True_,
        .amount = "1.0",
        .type = MarginAccountBorrowRepayTypeEnum::Borrow,
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.margin_account_borrow_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, MarginAccountBorrowRepayBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountBorrowRepayParams params{.asset = "USDT",
                                                .is_isolated =
                                                    MarginAccountBorrowRepayIsIsolatedEnum::True_,
                                                .amount = "1.0",
                                                .type = MarginAccountBorrowRepayTypeEnum::Borrow};
    EXPECT_THROW((void)api.margin_account_borrow_repay(params), common::BadRequestError);
}

TEST(RestApiBorrowRepayApi, QueryBorrowRepayRecordsInMarginAccount) {
    const std::string example =
        R"json({"rows":[{"type":"AUTO","isolatedSymbol":"BNBUSDT","amount":"14.00000000","asset":"BNB","interest":"0.01866667","principal":"13.98133333","status":"CONFIRMED","timestamp":1563438204000,"txId":2970933056}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryBorrowRepayRecordsInMarginAccountParams params{
        .type = QueryBorrowRepayRecordsInMarginAccountTypeEnum::Borrow};
    const auto res = api.query_borrow_repay_records_in_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/borrow-repay");
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, QueryBorrowRepayRecordsInMarginAccountWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"type":"AUTO","isolatedSymbol":"BNBUSDT","amount":"14.00000000","asset":"BNB","interest":"0.01866667","principal":"13.98133333","status":"CONFIRMED","timestamp":1563438204000,"txId":2970933056}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryBorrowRepayRecordsInMarginAccountParams params{
        .type = QueryBorrowRepayRecordsInMarginAccountTypeEnum::Borrow,
        .asset = "BNB",
        .isolated_symbol = "BNBUSDT",
        .tx_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_borrow_repay_records_in_margin_account(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isolatedSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, QueryBorrowRepayRecordsInMarginAccountBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryBorrowRepayRecordsInMarginAccountParams params{
        .type = QueryBorrowRepayRecordsInMarginAccountTypeEnum::Borrow};
    EXPECT_THROW((void)api.query_borrow_repay_records_in_margin_account(params),
                 common::BadRequestError);
}

TEST(RestApiBorrowRepayApi, QueryMarginInterestRateHistory) {
    const std::string example =
        R"json([{"asset":"BTC","dailyInterestRate":"0.00025000","timestamp":1611544731000,"vipLevel":1}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginInterestRateHistoryParams params{.asset = "BTC"};
    const auto res = api.query_margin_interest_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/interestRateHistory");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, QueryMarginInterestRateHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"BTC","dailyInterestRate":"0.00025000","timestamp":1611544731000,"vipLevel":1}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginInterestRateHistoryParams params{
        .asset = "BTC",
        .vip_level = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.query_margin_interest_rate_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("vipLevel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, QueryMarginInterestRateHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginInterestRateHistoryParams params{.asset = "BTC"};
    EXPECT_THROW((void)api.query_margin_interest_rate_history(params), common::BadRequestError);
}

TEST(RestApiBorrowRepayApi, QueryMaxBorrow) {
    const std::string example = R"json({"amount":"1.69248805","borrowLimit":"60"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMaxBorrowParams params{.asset = "BTC"};
    const auto res = api.query_max_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/maxBorrowable");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, QueryMaxBorrowWithOptionalParams) {
    const std::string example = R"json({"amount":"1.69248805","borrowLimit":"60"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMaxBorrowParams params{
        .asset = "BTC",
        .isolated_symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_max_borrow(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isolatedSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiBorrowRepayApi, QueryMaxBorrowBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMaxBorrowParams params{.asset = "BTC"};
    EXPECT_THROW((void)api.query_max_borrow(params), common::BadRequestError);
}
