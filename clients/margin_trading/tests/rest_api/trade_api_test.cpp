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
#include <binance/margin_trading/rest_api/trade_api.hpp>

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

TradeApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return TradeApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiTradeApi, CreateSpecialKey) {
    const std::string example =
        R"json({"apiKey":"npOzOAeLVgr2TuxWfNo43AaPWpBbJEoKezh1o8mSQb6ryE2odE11A4AoVlJbQoGx","secretKey":"87ssWB7azoy6ACRfyp6OVOL5U3rtZptX31QWw2kWjl1jHEYRbyM1pd6qykRBQw8p","type":"HMAC_SHA256"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateSpecialKeyParams params{.api_name = "apiName"};
    const auto res = api.create_special_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/apiKey");
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiName="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CreateSpecialKeyWithOptionalParams) {
    const std::string example =
        R"json({"apiKey":"npOzOAeLVgr2TuxWfNo43AaPWpBbJEoKezh1o8mSQb6ryE2odE11A4AoVlJbQoGx","secretKey":"87ssWB7azoy6ACRfyp6OVOL5U3rtZptX31QWw2kWjl1jHEYRbyM1pd6qykRBQw8p","type":"HMAC_SHA256"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateSpecialKeyParams params{
        .api_name = "apiName",
        .symbol = "BTCUSDT",
        .ip = "69.210.67.14,69.210.67.15",
        .public_key = "publicKey",
        .permission_mode = CreateSpecialKeyPermissionModeEnum::Trade,
        .recv_window = 5000,
    };
    const auto res = api.create_special_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("ip="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("publicKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("permissionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, CreateSpecialKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateSpecialKeyParams params{.api_name = "apiName"};
    EXPECT_THROW((void)api.create_special_key(params), common::BadRequestError);
}

TEST(RestApiTradeApi, DeleteSpecialKey) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteSpecialKeyParams params{};
    const auto res = api.delete_special_key(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/apiKey");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, DeleteSpecialKeyWithOptionalParams) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteSpecialKeyParams params{
        .api_name = "apiName",
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.delete_special_key(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, DeleteSpecialKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DeleteSpecialKeyParams params{};
    EXPECT_THROW((void)api.delete_special_key(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QuerySpecialKey) {
    const std::string example =
        R"json({"apiKey":"npOzOAeLVgr2TuxWfNo43AaPWpBbJEoKezh1o8mSQb6ryE2odE11A4AoVlJbQoGx","ip":"0.0.0.0,192.168.0.1,192.168.0.2","apiName":"testName","type":"RSA","permissionMode":"TRADE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySpecialKeyParams params{};
    const auto res = api.query_special_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/apiKey");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QuerySpecialKeyWithOptionalParams) {
    const std::string example =
        R"json({"apiKey":"npOzOAeLVgr2TuxWfNo43AaPWpBbJEoKezh1o8mSQb6ryE2odE11A4AoVlJbQoGx","ip":"0.0.0.0,192.168.0.1,192.168.0.2","apiName":"testName","type":"RSA","permissionMode":"TRADE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySpecialKeyParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_special_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QuerySpecialKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySpecialKeyParams params{};
    EXPECT_THROW((void)api.query_special_key(params), common::BadRequestError);
}

TEST(RestApiTradeApi, EditIpForSpecialKey) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EditIpForSpecialKeyParams params{.ip = "24.156.99.202"};
    const auto res = api.edit_ip_for_special_key(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/apiKey/ip");
    EXPECT_NE((rec.query() + "&" + rec.body).find("ip="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, EditIpForSpecialKeyWithOptionalParams) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EditIpForSpecialKeyParams params{
        .ip = "24.156.99.202",
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.edit_ip_for_special_key(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("ip="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, EditIpForSpecialKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EditIpForSpecialKeyParams params{.ip = "24.156.99.202"};
    EXPECT_THROW((void)api.edit_ip_for_special_key(params), common::BadRequestError);
}

TEST(RestApiTradeApi, ExitSpecialKeyMode) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExitSpecialKeyModeParams params{};
    const auto res = api.exit_special_key_mode(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/exit-special-key-mode");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ExitSpecialKeyModeWithOptionalParams) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExitSpecialKeyModeParams params{
        .recv_window = 5000,
    };
    const auto res = api.exit_special_key_mode(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, ExitSpecialKeyModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ExitSpecialKeyModeParams params{};
    EXPECT_THROW((void)api.exit_special_key_mode(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetForceLiquidationRecord) {
    const std::string example =
        R"json({"rows":[{"avgPrice":"0.00388359","executedQty":"31.39000000","orderId":180015097,"price":"0.00388110","qty":"31.39000000","side":"SELL","symbol":"BNBBTC","timeInForce":"GTC","isIsolated":true,"updatedTime":1558941374745}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetForceLiquidationRecordParams params{};
    const auto res = api.get_force_liquidation_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/forceLiquidationRec");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetForceLiquidationRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"avgPrice":"0.00388359","executedQty":"31.39000000","orderId":180015097,"price":"0.00388110","qty":"31.39000000","side":"SELL","symbol":"BNBBTC","timeInForce":"GTC","isIsolated":true,"updatedTime":1558941374745}],"total":1})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetForceLiquidationRecordParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .isolated_symbol = "BTCUSDT",
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.get_force_liquidation_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isolatedSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetForceLiquidationRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetForceLiquidationRecordParams params{};
    EXPECT_THROW((void)api.get_force_liquidation_record(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetSmallLiabilityExchangeCoinList) {
    const std::string example =
        R"json([{"asset":"ETH","interest":"0.00083334","principal":"0.001","liabilityAsset":"USDT","liabilityQty":0.3552}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSmallLiabilityExchangeCoinListParams params{};
    const auto res = api.get_small_liability_exchange_coin_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/exchange-small-liability");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetSmallLiabilityExchangeCoinListWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"ETH","interest":"0.00083334","principal":"0.001","liabilityAsset":"USDT","liabilityQty":0.3552}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSmallLiabilityExchangeCoinListParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_small_liability_exchange_coin_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetSmallLiabilityExchangeCoinListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSmallLiabilityExchangeCoinListParams params{};
    EXPECT_THROW((void)api.get_small_liability_exchange_coin_list(params), common::BadRequestError);
}

TEST(RestApiTradeApi, SmallLiabilityExchange) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SmallLiabilityExchangeParams params{.asset_names = "BTC,ETH"};
    const auto res = api.small_liability_exchange(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/exchange-small-liability");
    EXPECT_NE((rec.query() + "&" + rec.body).find("assetNames="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SmallLiabilityExchangeWithOptionalParams) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SmallLiabilityExchangeParams params{
        .asset_names = "BTC,ETH",
        .recv_window = 5000,
    };
    const auto res = api.small_liability_exchange(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("assetNames="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, SmallLiabilityExchangeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SmallLiabilityExchangeParams params{.asset_names = "BTC,ETH"};
    EXPECT_THROW((void)api.small_liability_exchange(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetSmallLiabilityExchangeHistory) {
    const std::string example =
        R"json({"total":1,"rows":[{"asset":"ETH","amount":"0.00083434","targetAsset":"BUSD","targetAmount":"1.37576819","bizType":"EXCHANGE_SMALL_LIABILITY","timestamp":1672801339253}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSmallLiabilityExchangeHistoryParams params{.current = 1, .size = 10};
    const auto res = api.get_small_liability_exchange_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/exchange-small-liability-history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetSmallLiabilityExchangeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"rows":[{"asset":"ETH","amount":"0.00083434","targetAsset":"BUSD","targetAmount":"1.37576819","bizType":"EXCHANGE_SMALL_LIABILITY","timestamp":1672801339253}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSmallLiabilityExchangeHistoryParams params{
        .current = 1,
        .size = 10,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_small_liability_exchange_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetSmallLiabilityExchangeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSmallLiabilityExchangeHistoryParams params{.current = 1, .size = 10};
    EXPECT_THROW((void)api.get_small_liability_exchange_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, LiquidationLoanRepay) {
    const std::string example =
        R"json({"repayId":12345678,"asset":"USDT","amount":"300.00000000","status":"SUCCESS","createTime":1714492800000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const LiquidationLoanRepayParams params{.asset = "USDT", .amount = common::Decimal("300.00")};
    const auto res = api.liquidation_loan_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/liquidation-loan/repay");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, LiquidationLoanRepayWithOptionalParams) {
    const std::string example =
        R"json({"repayId":12345678,"asset":"USDT","amount":"300.00000000","status":"SUCCESS","createTime":1714492800000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const LiquidationLoanRepayParams params{
        .asset = "USDT",
        .amount = common::Decimal("300.00"),
        .recv_window = 5000,
    };
    const auto res = api.liquidation_loan_repay(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, LiquidationLoanRepayBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const LiquidationLoanRepayParams params{.asset = "USDT", .amount = common::Decimal("300.00")};
    EXPECT_THROW((void)api.liquidation_loan_repay(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountCancelAllOpenOrdersOnASymbol) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","isIsolated":true,"origClientOrderId":"E6APeyTJvkMvLMYMqu1KQ4","orderId":11,"orderListId":-1,"clientOrderId":"pXLV6Hz6mprAcVYpVMTGgx","price":"0.089853","origQty":"0.178622","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"BUY","selfTradePreventionMode":"NONE","contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"2inzWQdDvZLHbbAmAozX2N","transactionTime":1585230948299,"orders":[{"symbol":"BTCUSDT","orderId":20,"clientOrderId":"CwOOIPHSmYywx6jZX77TdL"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"CwOOIPHSmYywx6jZX77TdL","orderId":20,"orderListId":1929,"clientOrderId":"pXLV6Hz6mprAcVYpVMTGgx","price":"0.668611","origQty":"0.690354","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"0.378131","icebergQty":"0.017083"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountCancelAllOpenOrdersOnASymbolParams params{.symbol = "BTCUSDT"};
    const auto res = api.margin_account_cancel_all_open_orders_on_a_symbol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/openOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountCancelAllOpenOrdersOnASymbolWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","isIsolated":true,"origClientOrderId":"E6APeyTJvkMvLMYMqu1KQ4","orderId":11,"orderListId":-1,"clientOrderId":"pXLV6Hz6mprAcVYpVMTGgx","price":"0.089853","origQty":"0.178622","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"BUY","selfTradePreventionMode":"NONE","contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"2inzWQdDvZLHbbAmAozX2N","transactionTime":1585230948299,"orders":[{"symbol":"BTCUSDT","orderId":20,"clientOrderId":"CwOOIPHSmYywx6jZX77TdL"}],"orderReports":[{"symbol":"BTCUSDT","origClientOrderId":"CwOOIPHSmYywx6jZX77TdL","orderId":20,"orderListId":1929,"clientOrderId":"pXLV6Hz6mprAcVYpVMTGgx","price":"0.668611","origQty":"0.690354","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"BUY","stopPrice":"0.378131","icebergQty":"0.017083"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountCancelAllOpenOrdersOnASymbolParams params{
        .symbol = "BTCUSDT",
        .is_isolated = MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.margin_account_cancel_all_open_orders_on_a_symbol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountCancelAllOpenOrdersOnASymbolBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountCancelAllOpenOrdersOnASymbolParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.margin_account_cancel_all_open_orders_on_a_symbol(params),
                 common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOrders) {
    const std::string example =
        R"json([{"clientOrderId":"qhcZw71gAkCCTv0t0k8LUK","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":true,"orderId":211842552,"origQty":"0.30000000","price":"0.00475010","side":"SELL","status":"NEW","stopPrice":"0.00000000","symbol":"BNBBTC","isIsolated":true,"time":1562040170089,"timeInForce":"GTC","type":"LIMIT","selfTradePreventionMode":"NONE","updateTime":1562040170089}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOrdersParams params{};
    const auto res = api.query_margin_accounts_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/openOrders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"clientOrderId":"qhcZw71gAkCCTv0t0k8LUK","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":true,"orderId":211842552,"origQty":"0.30000000","price":"0.00475010","side":"SELL","status":"NEW","stopPrice":"0.00000000","symbol":"BNBBTC","isIsolated":true,"time":1562040170089,"timeInForce":"GTC","type":"LIMIT","selfTradePreventionMode":"NONE","updateTime":1562040170089}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOrdersParams params{
        .symbol = "BNBBTC",
        .is_isolated = QueryMarginAccountsOpenOrdersIsIsolatedEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_open_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOrdersParams params{};
    EXPECT_THROW((void)api.query_margin_accounts_open_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountCancelOco) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"C3wyj4WVEktd7u9aVBRXcN","transactionTime":1574040868128,"symbol":"LTCBTC","isIsolated":false,"orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"pO9ufTiFGg3nw2fOdgeOXa"}],"orderReports":[{"symbol":"LTCBTC","origClientOrderId":"pO9ufTiFGg3nw2fOdgeOXa","orderId":2,"orderListId":0,"clientOrderId":"unfWT8ig8i0uj6lPuYLez6","price":"1.00000000","origQty":"10.00000000","executedQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"1.00000000","selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountCancelOcoParams params{.symbol = "BTCUSDT"};
    const auto res = api.margin_account_cancel_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/orderList");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountCancelOcoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"ALL_DONE","listOrderStatus":"ALL_DONE","listClientOrderId":"C3wyj4WVEktd7u9aVBRXcN","transactionTime":1574040868128,"symbol":"LTCBTC","isIsolated":false,"orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"pO9ufTiFGg3nw2fOdgeOXa"}],"orderReports":[{"symbol":"LTCBTC","origClientOrderId":"pO9ufTiFGg3nw2fOdgeOXa","orderId":2,"orderListId":0,"clientOrderId":"unfWT8ig8i0uj6lPuYLez6","price":"1.00000000","origQty":"10.00000000","executedQty":"0.00000000","cummulativeQuoteQty":"0.00000000","status":"CANCELED","timeInForce":"GTC","type":"STOP_LOSS_LIMIT","side":"SELL","stopPrice":"1.00000000","selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountCancelOcoParams params{
        .symbol = "BTCUSDT",
        .is_isolated = MarginAccountCancelOcoIsIsolatedEnum::True_,
        .order_list_id = 1,
        .list_client_order_id = "1",
        .new_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.margin_account_cancel_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderListId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountCancelOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountCancelOcoParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.margin_account_cancel_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsOco) {
    const std::string example =
        R"json({"orderListId":27,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"h2USkA5YQpaXHPIrkd96xE","transactionTime":1565245656253,"symbol":"LTCBTC","isIsolated":true,"orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"qD1gy3kc3Gx0rihm9Y3xwS"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOcoParams params{};
    const auto res = api.query_margin_accounts_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/orderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOcoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":27,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"h2USkA5YQpaXHPIrkd96xE","transactionTime":1565245656253,"symbol":"LTCBTC","isIsolated":true,"orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"qD1gy3kc3Gx0rihm9Y3xwS"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOcoParams params{
        .is_isolated = QueryMarginAccountsOcoIsIsolatedEnum::True_,
        .symbol = "LTCBTC",
        .order_list_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderListId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsOcoParams params{};
    EXPECT_THROW((void)api.query_margin_accounts_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountCancelOrder) {
    const std::string example =
        R"json({"symbol":"LTCBTC","orderId":"28","origClientOrderId":"myOrder1","clientOrderId":"cancelMyOrder1","price":"1.00000000","origQty":"10.00000000","executedQty":"8.00000000","cummulativeQuoteQty":"8.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","isIsolated":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountCancelOrderParams params{.symbol = "LTCBTC"};
    const auto res = api.margin_account_cancel_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountCancelOrderWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"LTCBTC","orderId":"28","origClientOrderId":"myOrder1","clientOrderId":"cancelMyOrder1","price":"1.00000000","origQty":"10.00000000","executedQty":"8.00000000","cummulativeQuoteQty":"8.00000000","status":"CANCELED","timeInForce":"GTC","type":"LIMIT","side":"SELL","isIsolated":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountCancelOrderParams params{
        .symbol = "LTCBTC",
        .is_isolated = MarginAccountCancelOrderIsIsolatedEnum::True_,
        .order_id = 1,
        .orig_client_order_id = "1",
        .new_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.margin_account_cancel_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountCancelOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountCancelOrderParams params{.symbol = "LTCBTC"};
    EXPECT_THROW((void)api.margin_account_cancel_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountNewOrder) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","orderId":26769564559,"clientOrderId":"E156O3KP4gOif65bjuUK5V","isIsolated":false,"transactTime":1713873075893,"price":"0","origQty":"0.001","executedQty":"0.001","cummulativeQuoteQty":"65.98253","status":"FILLED","timeInForce":"GTC","type":"MARKET","side":"SELL","selfTradePreventionMode":"EXPIRE_MAKER","marginBuyBorrowAmount":5,"marginBuyBorrowAsset":"BTC","fills":[{"price":"65982.53","qty":"0.001","commission":"0.06598253","commissionAsset":"USDT","tradeId":3570680726}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOrderParams params{.symbol = "BTCUSDT",
                                             .side = MarginAccountNewOrderSideEnum::Buy,
                                             .type = MarginAccountNewOrderTypeEnum::Limit};
    const auto res = api.margin_account_new_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOrderWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSDT","orderId":26769564559,"clientOrderId":"E156O3KP4gOif65bjuUK5V","isIsolated":false,"transactTime":1713873075893,"price":"0","origQty":"0.001","executedQty":"0.001","cummulativeQuoteQty":"65.98253","status":"FILLED","timeInForce":"GTC","type":"MARKET","side":"SELL","selfTradePreventionMode":"EXPIRE_MAKER","marginBuyBorrowAmount":5,"marginBuyBorrowAsset":"BTC","fills":[{"price":"65982.53","qty":"0.001","commission":"0.06598253","commissionAsset":"USDT","tradeId":3570680726}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOrderParams params{
        .symbol = "BTCUSDT",
        .side = MarginAccountNewOrderSideEnum::Buy,
        .type = MarginAccountNewOrderTypeEnum::Limit,
        .is_isolated = MarginAccountNewOrderIsIsolatedEnum::True_,
        .quantity = common::Decimal("1.0"),
        .quote_order_qty = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .stop_price = common::Decimal("1.0"),
        .new_client_order_id = "1",
        .iceberg_qty = common::Decimal("1.0"),
        .new_order_resp_type = MarginAccountNewOrderNewOrderRespTypeEnum::Ack,
        .side_effect_type = MarginAccountNewOrderSideEffectTypeEnum::NoSideEffect,
        .time_in_force = MarginAccountNewOrderTimeInForceEnum::Gtc,
        .self_trade_prevention_mode = MarginAccountNewOrderSelfTradePreventionModeEnum::ExpireTaker,
        .trailing_delta = 100,
        .auto_repay_at_cancel = true,
        .recv_window = 5000,
    };
    const auto res = api.margin_account_new_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteOrderQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("icebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sideEffectType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("trailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoRepayAtCancel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountNewOrderParams params{.symbol = "BTCUSDT",
                                             .side = MarginAccountNewOrderSideEnum::Buy,
                                             .type = MarginAccountNewOrderTypeEnum::Limit};
    EXPECT_THROW((void)api.margin_account_new_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsOrder) {
    const std::string example =
        R"json({"clientOrderId":"ZwfQzuDIGpceVhKW5DvCmO","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":true,"orderId":213205622,"origQty":"0.30000000","price":"0.00493630","side":"SELL","status":"NEW","stopPrice":"0.00000000","symbol":"BNBBTC","isIsolated":true,"time":1562133008725,"timeInForce":"GTC","type":"LIMIT","selfTradePreventionMode":"NONE","updateTime":1562133008725})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOrderParams params{.symbol = "BNBBTC"};
    const auto res = api.query_margin_accounts_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/order");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOrderWithOptionalParams) {
    const std::string example =
        R"json({"clientOrderId":"ZwfQzuDIGpceVhKW5DvCmO","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":true,"orderId":213205622,"origQty":"0.30000000","price":"0.00493630","side":"SELL","status":"NEW","stopPrice":"0.00000000","symbol":"BNBBTC","isIsolated":true,"time":1562133008725,"timeInForce":"GTC","type":"LIMIT","selfTradePreventionMode":"NONE","updateTime":1562133008725})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOrderParams params{
        .symbol = "BNBBTC",
        .is_isolated = QueryMarginAccountsOrderIsIsolatedEnum::True_,
        .order_id = 1,
        .orig_client_order_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("origClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsOrderParams params{.symbol = "BNBBTC"};
    EXPECT_THROW((void)api.query_margin_accounts_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountNewOco) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"JYVpp3F0f5CAG15DhtrqLp","transactionTime":1563417480525,"symbol":"LTCBTC","marginBuyBorrowAmount":"5","marginBuyBorrowAsset":"BTC","isIsolated":false,"orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos"}],"orderReports":[{"symbol":"LTCBTC","orderId":2,"orderListId":0,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos","transactTime":1563417480525,"price":"0.000000","origQty":"0.624363","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS","side":"BUY","stopPrice":"0.960664","selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOcoParams params{.symbol = "LTCBTC",
                                           .side = MarginAccountNewOcoSideEnum::Buy,
                                           .quantity = common::Decimal("1.0"),
                                           .price = common::Decimal("1.0"),
                                           .stop_price = common::Decimal("1.0")};
    const auto res = api.margin_account_new_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/order/oco");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOcoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":0,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"JYVpp3F0f5CAG15DhtrqLp","transactionTime":1563417480525,"symbol":"LTCBTC","marginBuyBorrowAmount":"5","marginBuyBorrowAsset":"BTC","isIsolated":false,"orders":[{"symbol":"LTCBTC","orderId":2,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos"}],"orderReports":[{"symbol":"LTCBTC","orderId":2,"orderListId":0,"clientOrderId":"Kk7sqHb9J6mJWTMDVW7Vos","transactTime":1563417480525,"price":"0.000000","origQty":"0.624363","executedQty":"0.000000","cummulativeQuoteQty":"0.000000","status":"NEW","timeInForce":"GTC","type":"STOP_LOSS","side":"BUY","stopPrice":"0.960664","selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOcoParams params{
        .symbol = "LTCBTC",
        .side = MarginAccountNewOcoSideEnum::Buy,
        .quantity = common::Decimal("1.0"),
        .price = common::Decimal("1.0"),
        .stop_price = common::Decimal("1.0"),
        .is_isolated = MarginAccountNewOcoIsIsolatedEnum::True_,
        .list_client_order_id = "1",
        .limit_client_order_id = "1",
        .limit_iceberg_qty = common::Decimal("1.0"),
        .stop_client_order_id = "1",
        .stop_limit_price = common::Decimal("1.0"),
        .stop_iceberg_qty = common::Decimal("1.0"),
        .stop_limit_time_in_force = MarginAccountNewOcoStopLimitTimeInForceEnum::Gtc,
        .new_order_resp_type = MarginAccountNewOcoNewOrderRespTypeEnum::Ack,
        .side_effect_type = MarginAccountNewOcoSideEffectTypeEnum::NoSideEffect,
        .self_trade_prevention_mode = MarginAccountNewOcoSelfTradePreventionModeEnum::ExpireTaker,
        .auto_repay_at_cancel = false,
        .recv_window = 5000,
    };
    const auto res = api.margin_account_new_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("price="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limitIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopLimitPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("stopLimitTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sideEffectType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoRepayAtCancel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountNewOcoParams params{.symbol = "LTCBTC",
                                           .side = MarginAccountNewOcoSideEnum::Buy,
                                           .quantity = common::Decimal("1.0"),
                                           .price = common::Decimal("1.0"),
                                           .stop_price = common::Decimal("1.0")};
    EXPECT_THROW((void)api.margin_account_new_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountNewOto) {
    const std::string example =
        R"json({"orderListId":13551,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"JDuOrsu0Ge8GTyvx8J7VTD","transactionTime":1725521998054,"symbol":"BTCUSDT","isIsolated":false,"orders":[{"symbol":"BTCUSDT","orderId":29896699,"clientOrderId":"y8RB6tQEMuHUXybqbtzTxk"}],"orderReports":[{"symbol":"BTCUSDT","orderId":29896699,"orderListId":13551,"clientOrderId":"y8RB6tQEMuHUXybqbtzTxk","transactTime":1725521998054,"price":"80000.00000000","origQty":"0.02000000","executedQty":"0","cummulativeQuoteQty":"0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOtoParams params{
        .symbol = "BTCUSDT",
        .working_type = MarginAccountNewOtoWorkingTypeEnum::Limit,
        .working_side = MarginAccountNewOtoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1.0"),
        .working_quantity = common::Decimal("1.0"),
        .working_iceberg_qty = common::Decimal("1.0"),
        .pending_type = MarginAccountNewOtoPendingTypeEnum::Limit,
        .pending_side = MarginAccountNewOtoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1.0")};
    const auto res = api.margin_account_new_oto(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/order/oto");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuantity="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOtoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":13551,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"JDuOrsu0Ge8GTyvx8J7VTD","transactionTime":1725521998054,"symbol":"BTCUSDT","isIsolated":false,"orders":[{"symbol":"BTCUSDT","orderId":29896699,"clientOrderId":"y8RB6tQEMuHUXybqbtzTxk"}],"orderReports":[{"symbol":"BTCUSDT","orderId":29896699,"orderListId":13551,"clientOrderId":"y8RB6tQEMuHUXybqbtzTxk","transactTime":1725521998054,"price":"80000.00000000","origQty":"0.02000000","executedQty":"0","cummulativeQuoteQty":"0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"SELL","selfTradePreventionMode":"NONE"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOtoParams params{
        .symbol = "BTCUSDT",
        .working_type = MarginAccountNewOtoWorkingTypeEnum::Limit,
        .working_side = MarginAccountNewOtoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1.0"),
        .working_quantity = common::Decimal("1.0"),
        .working_iceberg_qty = common::Decimal("1.0"),
        .pending_type = MarginAccountNewOtoPendingTypeEnum::Limit,
        .pending_side = MarginAccountNewOtoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1.0"),
        .is_isolated = MarginAccountNewOtoIsIsolatedEnum::True_,
        .list_client_order_id = "1",
        .new_order_resp_type = MarginAccountNewOtoNewOrderRespTypeEnum::Ack,
        .side_effect_type = MarginAccountNewOtoSideEffectTypeEnum::NoSideEffect,
        .self_trade_prevention_mode = MarginAccountNewOtoSelfTradePreventionModeEnum::ExpireTaker,
        .auto_repay_at_cancel = true,
        .working_client_order_id = "1",
        .working_time_in_force = MarginAccountNewOtoWorkingTimeInForceEnum::Gtc,
        .pending_client_order_id = "1",
        .pending_price = common::Decimal("1.0"),
        .pending_stop_price = common::Decimal("1.0"),
        .pending_trailing_delta = common::Decimal("1.0"),
        .pending_iceberg_qty = common::Decimal("1.0"),
        .pending_time_in_force = MarginAccountNewOtoPendingTimeInForceEnum::Gtc,
    };
    const auto res = api.margin_account_new_oto(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sideEffectType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoRepayAtCancel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingTimeInForce="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOtoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountNewOtoParams params{
        .symbol = "BTCUSDT",
        .working_type = MarginAccountNewOtoWorkingTypeEnum::Limit,
        .working_side = MarginAccountNewOtoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1.0"),
        .working_quantity = common::Decimal("1.0"),
        .working_iceberg_qty = common::Decimal("1.0"),
        .pending_type = MarginAccountNewOtoPendingTypeEnum::Limit,
        .pending_side = MarginAccountNewOtoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1.0")};
    EXPECT_THROW((void)api.margin_account_new_oto(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginAccountNewOtoco) {
    const std::string example =
        R"json({"orderListId":13509,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"u2AUo48LLef5qVenRtwJZy","transactionTime":1725521881300,"symbol":"BNBUSDT","isIsolated":false,"orders":[{"symbol":"BNBUSDT","orderId":28282534,"clientOrderId":"IfYDxvrZI4kiyqYpRH13iI"}],"orderReports":[{"symbol":"BNBUSDT","orderId":28282534,"orderListId":13509,"clientOrderId":"IfYDxvrZI4kiyqYpRH13iI","transactTime":1725521881300,"price":"300.00000000","origQty":"1.00000000","executedQty":"0","cummulativeQuoteQty":"0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","selfTradePreventionMode":"NONE","stopPrice":"299.00000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOtocoParams params{
        .symbol = "BTCUSDT",
        .working_type = MarginAccountNewOtocoWorkingTypeEnum::Limit,
        .working_side = MarginAccountNewOtocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1.0"),
        .working_quantity = common::Decimal("1.0"),
        .pending_side = MarginAccountNewOtocoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1.0"),
        .pending_above_type = MarginAccountNewOtocoPendingAboveTypeEnum::LimitMaker};
    const auto res = api.margin_account_new_otoco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/order/otoco");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOtocoWithOptionalParams) {
    const std::string example =
        R"json({"orderListId":13509,"contingencyType":"OTO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"u2AUo48LLef5qVenRtwJZy","transactionTime":1725521881300,"symbol":"BNBUSDT","isIsolated":false,"orders":[{"symbol":"BNBUSDT","orderId":28282534,"clientOrderId":"IfYDxvrZI4kiyqYpRH13iI"}],"orderReports":[{"symbol":"BNBUSDT","orderId":28282534,"orderListId":13509,"clientOrderId":"IfYDxvrZI4kiyqYpRH13iI","transactTime":1725521881300,"price":"300.00000000","origQty":"1.00000000","executedQty":"0","cummulativeQuoteQty":"0","status":"NEW","timeInForce":"GTC","type":"LIMIT","side":"BUY","selfTradePreventionMode":"NONE","stopPrice":"299.00000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginAccountNewOtocoParams params{
        .symbol = "BTCUSDT",
        .working_type = MarginAccountNewOtocoWorkingTypeEnum::Limit,
        .working_side = MarginAccountNewOtocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1.0"),
        .working_quantity = common::Decimal("1.0"),
        .pending_side = MarginAccountNewOtocoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1.0"),
        .pending_above_type = MarginAccountNewOtocoPendingAboveTypeEnum::LimitMaker,
        .is_isolated = MarginAccountNewOtocoIsIsolatedEnum::True_,
        .side_effect_type = MarginAccountNewOtocoSideEffectTypeEnum::NoSideEffect,
        .auto_repay_at_cancel = true,
        .list_client_order_id = "1",
        .new_order_resp_type = MarginAccountNewOtocoNewOrderRespTypeEnum::Ack,
        .self_trade_prevention_mode = MarginAccountNewOtocoSelfTradePreventionModeEnum::ExpireTaker,
        .working_client_order_id = "1",
        .working_iceberg_qty = common::Decimal("1.0"),
        .working_time_in_force = MarginAccountNewOtocoWorkingTimeInForceEnum::Gtc,
        .pending_above_client_order_id = "1",
        .pending_above_price = common::Decimal("1.0"),
        .pending_above_stop_price = common::Decimal("1.0"),
        .pending_above_trailing_delta = common::Decimal("1.0"),
        .pending_above_iceberg_qty = common::Decimal("1.0"),
        .pending_above_time_in_force = MarginAccountNewOtocoPendingAboveTimeInForceEnum::Gtc,
        .pending_below_type = MarginAccountNewOtocoPendingBelowTypeEnum::LimitMaker,
        .pending_below_client_order_id = "1",
        .pending_below_price = common::Decimal("1.0"),
        .pending_below_stop_price = common::Decimal("1.0"),
        .pending_below_trailing_delta = common::Decimal("1.0"),
        .pending_below_iceberg_qty = common::Decimal("1.0"),
        .pending_below_time_in_force = MarginAccountNewOtocoPendingBelowTimeInForceEnum::Gtc,
    };
    const auto res = api.margin_account_new_otoco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuantity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sideEffectType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("autoRepayAtCancel="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("listClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("newOrderRespType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("selfTradePreventionMode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workingTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAbovePrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingAboveTimeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowClientOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowStopPrice="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowTrailingDelta="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowIcebergQty="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingBelowTimeInForce="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginAccountNewOtocoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginAccountNewOtocoParams params{
        .symbol = "BTCUSDT",
        .working_type = MarginAccountNewOtocoWorkingTypeEnum::Limit,
        .working_side = MarginAccountNewOtocoWorkingSideEnum::Buy,
        .working_price = common::Decimal("1.0"),
        .working_quantity = common::Decimal("1.0"),
        .pending_side = MarginAccountNewOtocoPendingSideEnum::Buy,
        .pending_quantity = common::Decimal("1.0"),
        .pending_above_type = MarginAccountNewOtocoPendingAboveTypeEnum::LimitMaker};
    EXPECT_THROW((void)api.margin_account_new_otoco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, MarginManualLiquidation) {
    const std::string example =
        R"json({"asset":"ETH","interest":"0.00083334","principal":"0.001","liabilityAsset":"USDT","liabilityQty":0.3552})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginManualLiquidationParams params{.type = MarginManualLiquidationTypeEnum::Margin};
    const auto res = api.margin_manual_liquidation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/manual-liquidation");
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginManualLiquidationWithOptionalParams) {
    const std::string example =
        R"json({"asset":"ETH","interest":"0.00083334","principal":"0.001","liabilityAsset":"USDT","liabilityQty":0.3552})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MarginManualLiquidationParams params{
        .type = MarginManualLiquidationTypeEnum::Margin,
        .symbol = "ETHUSDT",
        .recv_window = 5000,
    };
    const auto res = api.margin_manual_liquidation(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, MarginManualLiquidationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MarginManualLiquidationParams params{.type = MarginManualLiquidationTypeEnum::Margin};
    EXPECT_THROW((void)api.margin_manual_liquidation(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryCurrentMarginOrderCountUsage) {
    const std::string example =
        R"json([{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":10000,"count":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentMarginOrderCountUsageParams params{};
    const auto res = api.query_current_margin_order_count_usage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/rateLimit/order");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentMarginOrderCountUsageWithOptionalParams) {
    const std::string example =
        R"json([{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":10000,"count":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryCurrentMarginOrderCountUsageParams params{
        .is_isolated = QueryCurrentMarginOrderCountUsageIsIsolatedEnum::True_,
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_current_margin_order_count_usage(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryCurrentMarginOrderCountUsageBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryCurrentMarginOrderCountUsageParams params{};
    EXPECT_THROW((void)api.query_current_margin_order_count_usage(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryLiquidationLoan) {
    const std::string example =
        R"json({"asset":"USDC","amount":"1000.00000000","repaidAmount":"300.00000000","remainingAmount":"700.00000000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryLiquidationLoanParams params{};
    const auto res = api.query_liquidation_loan(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/liquidation-loan");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryLiquidationLoanWithOptionalParams) {
    const std::string example =
        R"json({"asset":"USDC","amount":"1000.00000000","repaidAmount":"300.00000000","remainingAmount":"700.00000000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryLiquidationLoanParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_liquidation_loan(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryLiquidationLoanBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryLiquidationLoanParams params{};
    EXPECT_THROW((void)api.query_liquidation_loan(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryLiquidationLoanRepayHistory) {
    const std::string example =
        R"json({"total":2,"rows":[{"repayId":12345678,"asset":"USDC","amount":"300.00000000","status":"SUCCESS","createTime":1714492800000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryLiquidationLoanRepayHistoryParams params{};
    const auto res = api.query_liquidation_loan_repay_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/liquidation-loan/repay-history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryLiquidationLoanRepayHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":2,"rows":[{"repayId":12345678,"asset":"USDC","amount":"300.00000000","status":"SUCCESS","createTime":1714492800000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryLiquidationLoanRepayHistoryParams params{
        .start_time = 1714492800000,
        .end_time = 1714579200000,
        .current = 1,
        .size = 50,
        .recv_window = 5000,
    };
    const auto res = api.query_liquidation_loan_repay_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryLiquidationLoanRepayHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryLiquidationLoanRepayHistoryParams params{};
    EXPECT_THROW((void)api.query_liquidation_loan_repay_history(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsAllOco) {
    const std::string example =
        R"json([{"orderListId":29,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"amEEAXryFzFwYF1FeRpUoZ","transactionTime":1565245913483,"symbol":"LTCBTC","isIsolated":true,"orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"oD7aesZqjEGlZrbtRpy5zB"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsAllOcoParams params{};
    const auto res = api.query_margin_accounts_all_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/allOrderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsAllOcoWithOptionalParams) {
    const std::string example =
        R"json([{"orderListId":29,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"amEEAXryFzFwYF1FeRpUoZ","transactionTime":1565245913483,"symbol":"LTCBTC","isIsolated":true,"orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"oD7aesZqjEGlZrbtRpy5zB"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsAllOcoParams params{
        .is_isolated = QueryMarginAccountsAllOcoIsIsolatedEnum::True_,
        .symbol = "LTCBTC",
        .from_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 100,
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_all_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsAllOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsAllOcoParams params{};
    EXPECT_THROW((void)api.query_margin_accounts_all_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsAllOrders) {
    const std::string example =
        R"json([{"clientOrderId":"D2KDy4DIeS56PvkM13f8cP","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":false,"orderId":41295,"origQty":"5.31000000","price":"0.22500000","side":"SELL","status":"CANCELED","stopPrice":"0.18000000","symbol":"BNBBTC","isIsolated":false,"time":1565769338806,"timeInForce":"GTC","type":"TAKE_PROFIT_LIMIT","selfTradePreventionMode":"NONE","updateTime":1565769342148}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsAllOrdersParams params{.symbol = "BNBBTC"};
    const auto res = api.query_margin_accounts_all_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/allOrders");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsAllOrdersWithOptionalParams) {
    const std::string example =
        R"json([{"clientOrderId":"D2KDy4DIeS56PvkM13f8cP","cummulativeQuoteQty":"0.00000000","executedQty":"0.00000000","icebergQty":"0.00000000","isWorking":false,"orderId":41295,"origQty":"5.31000000","price":"0.22500000","side":"SELL","status":"CANCELED","stopPrice":"0.18000000","symbol":"BNBBTC","isIsolated":false,"time":1565769338806,"timeInForce":"GTC","type":"TAKE_PROFIT_LIMIT","selfTradePreventionMode":"NONE","updateTime":1565769342148}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsAllOrdersParams params{
        .symbol = "BNBBTC",
        .is_isolated = QueryMarginAccountsAllOrdersIsIsolatedEnum::True_,
        .order_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 100,
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_all_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsAllOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsAllOrdersParams params{.symbol = "BNBBTC"};
    EXPECT_THROW((void)api.query_margin_accounts_all_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOco) {
    const std::string example =
        R"json([{"orderListId":31,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"wuB13fmulKj3YjdqWEcsnp","transactionTime":1565246080644,"symbol":"LTCBTC","isIsolated":true,"orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"r3EH2N76dHfLoSZWIUw1bT"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOcoParams params{};
    const auto res = api.query_margin_accounts_open_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/openOrderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOcoWithOptionalParams) {
    const std::string example =
        R"json([{"orderListId":31,"contingencyType":"OCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"wuB13fmulKj3YjdqWEcsnp","transactionTime":1565246080644,"symbol":"LTCBTC","isIsolated":true,"orders":[{"symbol":"LTCBTC","orderId":4,"clientOrderId":"r3EH2N76dHfLoSZWIUw1bT"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOcoParams params{
        .is_isolated = QueryMarginAccountsOpenOcoIsIsolatedEnum::True_,
        .symbol = "LTCBTC",
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_open_oco(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOcoBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOcoParams params{};
    EXPECT_THROW((void)api.query_margin_accounts_open_oco(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOtootocoOrderLists) {
    const std::string example =
        R"json([{"orderListId":24867326110,"contingencyType":"OTOCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"web_6324e98951224f96b8a24f312abe5067","transactionTime":1790063061632,"symbol":"ASTERUSDT","orders":[{"symbol":"ASTERUSDT","orderId":499470863,"status":"NEW","clientOrderId":"web_f8890794e27b42a1a2ef6b5aef79a949"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOtootocoOrderListsParams params{};
    const auto res = api.query_margin_accounts_open_otootoco_order_lists(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/oto/openOrderList");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOtootocoOrderListsWithOptionalParams) {
    const std::string example =
        R"json([{"orderListId":24867326110,"contingencyType":"OTOCO","listStatusType":"EXEC_STARTED","listOrderStatus":"EXECUTING","listClientOrderId":"web_6324e98951224f96b8a24f312abe5067","transactionTime":1790063061632,"symbol":"ASTERUSDT","orders":[{"symbol":"ASTERUSDT","orderId":499470863,"status":"NEW","clientOrderId":"web_f8890794e27b42a1a2ef6b5aef79a949"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOtootocoOrderListsParams params{
        .symbol = "ASTERUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_open_otootoco_order_lists(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsOpenOtootocoOrderListsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsOpenOtootocoOrderListsParams params{};
    EXPECT_THROW((void)api.query_margin_accounts_open_otootoco_order_lists(params),
                 common::BadRequestError);
}

TEST(RestApiTradeApi, QueryMarginAccountsTradeList) {
    const std::string example =
        R"json([{"commission":"0.00006000","commissionAsset":"BTC","id":34,"isBestMatch":true,"isBuyer":false,"isMaker":false,"orderId":39324,"price":"0.02000000","qty":"3.00000000","symbol":"BNBBTC","isIsolated":false,"time":1561973357171}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsTradeListParams params{.symbol = "BNBBTC"};
    const auto res = api.query_margin_accounts_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/myTrades");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsTradeListWithOptionalParams) {
    const std::string example =
        R"json([{"commission":"0.00006000","commissionAsset":"BTC","id":34,"isBestMatch":true,"isBuyer":false,"isMaker":false,"orderId":39324,"price":"0.02000000","qty":"3.00000000","symbol":"BNBBTC","isIsolated":false,"time":1561973357171}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryMarginAccountsTradeListParams params{
        .symbol = "BNBBTC",
        .is_isolated = QueryMarginAccountsTradeListIsIsolatedEnum::True_,
        .order_id = 1,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .from_id = 1,
        .limit = 500,
        .recv_window = 5000,
    };
    const auto res = api.query_margin_accounts_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryMarginAccountsTradeListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryMarginAccountsTradeListParams params{.symbol = "BNBBTC"};
    EXPECT_THROW((void)api.query_margin_accounts_trade_list(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryPreventedMatches) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","preventedMatchId":1,"takerOrderId":5,"makerSymbol":"BTCUSDT","makerOrderId":3,"tradeGroupId":1,"selfTradePreventionMode":"EXPIRE_MAKER","price":"1.100000","makerPreventedQuantity":"1.300000","transactTime":1669101687094}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPreventedMatchesParams params{.symbol = "BTCUSDT"};
    const auto res = api.query_prevented_matches(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/myPreventedMatches");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryPreventedMatchesWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSDT","preventedMatchId":1,"takerOrderId":5,"makerSymbol":"BTCUSDT","makerOrderId":3,"tradeGroupId":1,"selfTradePreventionMode":"EXPIRE_MAKER","price":"1.100000","makerPreventedQuantity":"1.300000","transactTime":1669101687094}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPreventedMatchesParams params{
        .symbol = "BTCUSDT",
        .prevented_match_id = 1,
        .order_id = 1,
        .from_prevented_match_id = 1,
        .is_isolated = QueryPreventedMatchesIsIsolatedEnum::True_,
        .recv_window = 5000,
    };
    const auto res = api.query_prevented_matches(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("preventedMatchId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromPreventedMatchId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("isIsolated="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryPreventedMatchesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPreventedMatchesParams params{.symbol = "BTCUSDT"};
    EXPECT_THROW((void)api.query_prevented_matches(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QuerySpecialKeyList) {
    const std::string example =
        R"json([{"apiName":"testName1","apiKey":"znpOzOAeLVgr2TuxWfNo43AaPWpBbJEoKezh1o8mSQb6ryE2odE11A4AoVlJbQoG","ip":"192.168.0.1,192.168.0.2","type":"RSA","permissionMode":"TRADE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySpecialKeyListParams params{};
    const auto res = api.query_special_key_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/margin/api-key-list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QuerySpecialKeyListWithOptionalParams) {
    const std::string example =
        R"json([{"apiName":"testName1","apiKey":"znpOzOAeLVgr2TuxWfNo43AaPWpBbJEoKezh1o8mSQb6ryE2odE11A4AoVlJbQoG","ip":"192.168.0.1,192.168.0.2","type":"RSA","permissionMode":"TRADE"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySpecialKeyListParams params{
        .symbol = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_special_key_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QuerySpecialKeyListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySpecialKeyListParams params{};
    EXPECT_THROW((void)api.query_special_key_list(params), common::BadRequestError);
}
