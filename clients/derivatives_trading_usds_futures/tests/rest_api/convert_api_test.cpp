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
#include <binance/derivatives_trading_usds_futures/rest_api/convert_api.hpp>

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

ConvertApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return ConvertApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiConvertApi, AcceptTheOfferedQuote) {
    const std::string example =
        R"json({"orderId":"933256278426274426","createTime":1623381330472,"orderStatus":"PROCESS"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AcceptTheOfferedQuoteParams params{.quote_id = "1"};
    const auto res = api.accept_the_offered_quote(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/convert/acceptQuote");
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiConvertApi, AcceptTheOfferedQuoteWithOptionalParams) {
    const std::string example =
        R"json({"orderId":"933256278426274426","createTime":1623381330472,"orderStatus":"PROCESS"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AcceptTheOfferedQuoteParams params{
        .quote_id = "1",
        .recv_window = 5000,
    };
    const auto res = api.accept_the_offered_quote(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiConvertApi, AcceptTheOfferedQuoteBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AcceptTheOfferedQuoteParams params{.quote_id = "1"};
    EXPECT_THROW((void)api.accept_the_offered_quote(params), common::BadRequestError);
}

TEST(RestApiConvertApi, ListAllConvertPairs) {
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
    EXPECT_EQ(rec.path(), "/fapi/v1/convert/exchangeInfo");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiConvertApi, ListAllConvertPairsWithOptionalParams) {
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

TEST(RestApiConvertApi, ListAllConvertPairsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ListAllConvertPairsParams params{};
    EXPECT_THROW((void)api.list_all_convert_pairs(params), common::BadRequestError);
}

TEST(RestApiConvertApi, OrderStatus) {
    const std::string example =
        R"json({"orderId":933256278426274400,"orderStatus":"SUCCESS","fromAsset":"BTC","fromAmount":"0.00054414","toAsset":"USDT","toAmount":"20","ratio":"36755","inverseRatio":"0.00002721","createTime":1623381330472})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderStatusParams params{};
    const auto res = api.order_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/fapi/v1/convert/orderStatus");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiConvertApi, OrderStatusWithOptionalParams) {
    const std::string example =
        R"json({"orderId":933256278426274400,"orderStatus":"SUCCESS","fromAsset":"BTC","fromAmount":"0.00054414","toAsset":"USDT","toAmount":"20","ratio":"36755","inverseRatio":"0.00002721","createTime":1623381330472})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OrderStatusParams params{
        .order_id = "933256278426274400",
        .quote_id = "1",
    };
    const auto res = api.order_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiConvertApi, OrderStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OrderStatusParams params{};
    EXPECT_THROW((void)api.order_status(params), common::BadRequestError);
}

TEST(RestApiConvertApi, SendQuoteRequest) {
    const std::string example =
        R"json({"quoteId":"12415572564","ratio":"38163.7","inverseRatio":"0.0000262","validTimestamp":1623319461670,"toAmount":"3816.37","fromAmount":"0.1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SendQuoteRequestParams params{.from_asset = "BTC", .to_asset = "USDT"};
    const auto res = api.send_quote_request(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/fapi/v1/convert/getQuote");
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toAsset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiConvertApi, SendQuoteRequestWithOptionalParams) {
    const std::string example =
        R"json({"quoteId":"12415572564","ratio":"38163.7","inverseRatio":"0.0000262","validTimestamp":1623319461670,"toAmount":"3816.37","fromAmount":"0.1"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SendQuoteRequestParams params{
        .from_asset = "BTC",
        .to_asset = "USDT",
        .from_amount = common::Decimal("1.0"),
        .to_amount = common::Decimal("1.0"),
        .valid_time = "10s",
        .recv_window = 5000,
    };
    const auto res = api.send_quote_request(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("validTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiConvertApi, SendQuoteRequestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SendQuoteRequestParams params{.from_asset = "BTC", .to_asset = "USDT"};
    EXPECT_THROW((void)api.send_quote_request(params), common::BadRequestError);
}
