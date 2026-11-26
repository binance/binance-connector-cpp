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
#include <binance/w3w_prediction/rest_api/otc_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::w3w_prediction::rest_api;
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

OtcApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return OtcApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiOtcApi, CreateOtcBlocktrade) {
    const std::string example =
        R"json({"orderId":"26080500000001234567","secretToken":"a1b2c3d4-e5f6-7890-abcd-ef1234567890"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateOtcBlocktradeParams params{
        .market_id = "123",
        .token_id = "71321045679252212594626385532706912750332728571942532289631379312455583992563",
        .side = CreateOtcBlocktradeSideEnum::Buy,
        .maker_amount = "600000000000000000000",
        .taker_amount = "1000000000000000000000",
        .price_per_share = "0.65",
        .expiration = 1790000000};
    const auto res = api.create_otc_blocktrade(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/create");
    EXPECT_NE((rec.query() + "&" + rec.body).find("marketId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("makerAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("takerAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pricePerShare="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("expiration="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, CreateOtcBlocktradeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateOtcBlocktradeParams params{
        .market_id = "123",
        .token_id = "71321045679252212594626385532706912750332728571942532289631379312455583992563",
        .side = CreateOtcBlocktradeSideEnum::Buy,
        .maker_amount = "600000000000000000000",
        .taker_amount = "1000000000000000000000",
        .price_per_share = "0.65",
        .expiration = 1790000000};
    EXPECT_THROW((void)api.create_otc_blocktrade(params), common::BadRequestError);
}

TEST(RestApiOtcApi, FulfilOtcBlocktrade) {
    const std::string example = R"json({"orderId":"26080500000001234568"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FulfilOtcBlocktradeParams params{.order_id = "26080500000001234567",
                                           .secret_token = "a1b2c3d4-e5f6-7890-abcd-ef1234567890"};
    const auto res = api.fulfil_otc_blocktrade(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/fulfil");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("secretToken="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, FulfilOtcBlocktradeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FulfilOtcBlocktradeParams params{.order_id = "26080500000001234567",
                                           .secret_token = "a1b2c3d4-e5f6-7890-abcd-ef1234567890"};
    EXPECT_THROW((void)api.fulfil_otc_blocktrade(params), common::BadRequestError);
}

TEST(RestApiOtcApi, GetOtcBlocktradeDetail) {
    const std::string example =
        R"json({"orderId":"26080500000001234567","status":"OPEN","orderData":{"status":"OPEN","marketId":"123","tokenId":"71321045679252212594626385532706912750332728571942532289631379312455583992563","side":0,"maker":"0x12e32db8817e292508c34111cbc4b23340df542c","taker":"taker","makerAmount":"600000000000000000000","takerAmount":"1000000000000000000000","price":0.65,"orderType":"GTD","timeInForce":"GTD","expiration":1790000000,"filledAmount":"0","quoteType":"Bid","createdAt":"2026-08-05T10:30:00.000Z","isNegRisk":false,"isYieldBearing":false,"secretToken":"a1b2c3d4-e5f6-7890-abcd-ef1234567890"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOtcBlocktradeDetailParams params{.order_id = "26080500000001234567"};
    const auto res = api.get_otc_blocktrade_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/detail");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, GetOtcBlocktradeDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOtcBlocktradeDetailParams params{.order_id = "26080500000001234567"};
    EXPECT_THROW((void)api.get_otc_blocktrade_detail(params), common::BadRequestError);
}

TEST(RestApiOtcApi, GetOtcBlocktradeEvents) {
    const std::string example =
        R"json({"cursor":"next-cursor-string","events":[{"event":"CREATE","blocktradeId":"pf-bt-001","orderId":"26080500000001234567","marketId":123,"amount":"600000000000000000000","fee":"1000000000000000","effectiveFee":"1000000000000000","price":"650000000000000000","transactionHash":"transactionHash","reason":"reason","isMaker":true,"timestamp":"2026-08-05T10:30:00.000Z"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOtcBlocktradeEventsParams params{};
    const auto res = api.get_otc_blocktrade_events(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/events");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, GetOtcBlocktradeEventsWithOptionalParams) {
    const std::string example =
        R"json({"cursor":"next-cursor-string","events":[{"event":"CREATE","blocktradeId":"pf-bt-001","orderId":"26080500000001234567","marketId":123,"amount":"600000000000000000000","fee":"1000000000000000","effectiveFee":"1000000000000000","price":"650000000000000000","transactionHash":"transactionHash","reason":"reason","isMaker":true,"timestamp":"2026-08-05T10:30:00.000Z"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOtcBlocktradeEventsParams params{
        .first = 20,
        .after = "next-cursor-string",
        .event_types = std::vector<std::string>{},
        .market_id = 123,
    };
    const auto res = api.get_otc_blocktrade_events(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("first="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("after="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marketId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, GetOtcBlocktradeEventsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOtcBlocktradeEventsParams params{};
    EXPECT_THROW((void)api.get_otc_blocktrade_events(params), common::BadRequestError);
}

TEST(RestApiOtcApi, GetOtcReservedBalances) {
    const std::string example =
        R"json({"balances":[{"type":"USDT","tokenId":"tokenId","amount":"500000000000000000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetOtcReservedBalancesParams params{
        .assets = std::vector<GetOtcReservedBalancesAssetsParameterInner>{}};
    const auto res = api.get_otc_reserved_balances(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/reserved-balances");
    EXPECT_NE((rec.query() + "&" + rec.body).find("assets="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, GetOtcReservedBalancesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetOtcReservedBalancesParams params{
        .assets = std::vector<GetOtcReservedBalancesAssetsParameterInner>{}};
    EXPECT_THROW((void)api.get_otc_reserved_balances(params), common::BadRequestError);
}

TEST(RestApiOtcApi, ListOtcBlocktrades) {
    const std::string example =
        R"json({"cursor":"next-cursor-string","blocktrades":[{"status":"OPEN","marketId":"123","tokenId":"71321045679252212594626385532706912750332728571942532289631379312455583992563","side":0,"maker":"0x12e32db8817e292508c34111cbc4b23340df542c","makerAmount":"600000000000000000000","takerAmount":"1000000000000000000000","price":0.65,"quoteType":"Bid","createdAt":"2026-08-05T10:30:00.000Z","secretToken":"a1b2c3d4-e5f6-7890-abcd-ef1234567890"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ListOtcBlocktradesParams params{};
    const auto res = api.list_otc_blocktrades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, ListOtcBlocktradesWithOptionalParams) {
    const std::string example =
        R"json({"cursor":"next-cursor-string","blocktrades":[{"status":"OPEN","marketId":"123","tokenId":"71321045679252212594626385532706912750332728571942532289631379312455583992563","side":0,"maker":"0x12e32db8817e292508c34111cbc4b23340df542c","makerAmount":"600000000000000000000","takerAmount":"1000000000000000000000","price":0.65,"quoteType":"Bid","createdAt":"2026-08-05T10:30:00.000Z","secretToken":"a1b2c3d4-e5f6-7890-abcd-ef1234567890"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ListOtcBlocktradesParams params{
        .first = 20,
        .after = "next-cursor-string",
        .status = ListOtcBlocktradesStatusEnum::Open,
    };
    const auto res = api.list_otc_blocktrades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("first="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("after="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, ListOtcBlocktradesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ListOtcBlocktradesParams params{};
    EXPECT_THROW((void)api.list_otc_blocktrades(params), common::BadRequestError);
}

TEST(RestApiOtcApi, PreviewOtcBlocktrade) {
    const std::string example =
        R"json({"orderId":"orderId","status":"OPEN","orderData":{"status":"OPEN","marketId":"123","tokenId":"71321045679252212594626385532706912750332728571942532289631379312455583992563","side":0,"maker":"0x12e32db8817e292508c34111cbc4b23340df542c","taker":"taker","makerAmount":"600000000000000000000","takerAmount":"1000000000000000000000","price":0.65,"orderType":"GTD","timeInForce":"GTD","expiration":1790000000,"filledAmount":"0","quoteType":"Bid","createdAt":"2026-08-05T10:30:00.000Z","isNegRisk":false,"isYieldBearing":false}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PreviewOtcBlocktradeParams params{.secret_token = "a1b2c3d4-e5f6-7890-abcd-ef1234567890"};
    const auto res = api.preview_otc_blocktrade(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/preview");
    EXPECT_NE((rec.query() + "&" + rec.body).find("secretToken="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, PreviewOtcBlocktradeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PreviewOtcBlocktradeParams params{.secret_token = "a1b2c3d4-e5f6-7890-abcd-ef1234567890"};
    EXPECT_THROW((void)api.preview_otc_blocktrade(params), common::BadRequestError);
}

TEST(RestApiOtcApi, RemoveOtcBlocktrades) {
    const std::string example =
        R"json({"removed":["26080500000001234567"],"noop":["26080500000001234568"]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RemoveOtcBlocktradesParams params{.order_ids = std::vector<std::string>{}};
    const auto res = api.remove_otc_blocktrades(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/remove");
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderIds="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiOtcApi, RemoveOtcBlocktradesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RemoveOtcBlocktradesParams params{.order_ids = std::vector<std::string>{}};
    EXPECT_THROW((void)api.remove_otc_blocktrades(params), common::BadRequestError);
}
