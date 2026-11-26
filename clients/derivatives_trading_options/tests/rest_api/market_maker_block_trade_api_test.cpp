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
#include <binance/derivatives_trading_options/rest_api/market_maker_block_trade_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_options::rest_api;
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

MarketMakerBlockTradeApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return MarketMakerBlockTradeApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiMarketMakerBlockTradeApi, AcceptBlockTradeOrder) {
    const std::string example =
        R"json({"blockTradeSettlementKey":"7d046e6e-a429-4335-ab9d-6a681febcde5","expireTime":1730172115801,"liquidity":"MAKER","status":"ACCEPTED","createTime":1730170315803,"legs":[{"symbol":"BNB-241101-700-C","side":"SELL","quantity":"1.2","price":"2.8"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AcceptBlockTradeOrderParams params{.block_order_matching_key =
                                                 "7d046e6e-a429-4335-ab9d-6a681febcde5"};
    const auto res = api.accept_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/eapi/v1/block/order/execute");
    EXPECT_NE((rec.query() + "&" + rec.body).find("blockOrderMatchingKey="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, AcceptBlockTradeOrderWithOptionalParams) {
    const std::string example =
        R"json({"blockTradeSettlementKey":"7d046e6e-a429-4335-ab9d-6a681febcde5","expireTime":1730172115801,"liquidity":"MAKER","status":"ACCEPTED","createTime":1730170315803,"legs":[{"symbol":"BNB-241101-700-C","side":"SELL","quantity":"1.2","price":"2.8"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AcceptBlockTradeOrderParams params{
        .block_order_matching_key = "7d046e6e-a429-4335-ab9d-6a681febcde5",
        .recv_window = 5000,
    };
    const auto res = api.accept_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("blockOrderMatchingKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, AcceptBlockTradeOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AcceptBlockTradeOrderParams params{.block_order_matching_key =
                                                 "7d046e6e-a429-4335-ab9d-6a681febcde5"};
    EXPECT_THROW((void)api.accept_block_trade_order(params), common::BadRequestError);
}

TEST(RestApiMarketMakerBlockTradeApi, QueryBlockTradeDetails) {
    const std::string example =
        R"json({"blockTradeSettlementKey":"12b96c28-ba05-8906-c89t-703215cfb2e6","expireTime":1730171860460,"liquidity":"MAKER","status":"RECEIVED","createTime":1730170060462,"legs":[{"symbol":"BNB-241101-700-C","side":"SELL","quantity":"1.66","price":"20"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryBlockTradeDetailsParams params{.block_order_matching_key =
                                                  "12b96c28-ba05-8906-c89t-703215cfb2e6"};
    const auto res = api.query_block_trade_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/block/order/execute");
    EXPECT_NE((rec.query() + "&" + rec.body).find("blockOrderMatchingKey="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, QueryBlockTradeDetailsWithOptionalParams) {
    const std::string example =
        R"json({"blockTradeSettlementKey":"12b96c28-ba05-8906-c89t-703215cfb2e6","expireTime":1730171860460,"liquidity":"MAKER","status":"RECEIVED","createTime":1730170060462,"legs":[{"symbol":"BNB-241101-700-C","side":"SELL","quantity":"1.66","price":"20"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryBlockTradeDetailsParams params{
        .block_order_matching_key = "12b96c28-ba05-8906-c89t-703215cfb2e6",
        .recv_window = 5000,
    };
    const auto res = api.query_block_trade_details(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("blockOrderMatchingKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, QueryBlockTradeDetailsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryBlockTradeDetailsParams params{.block_order_matching_key =
                                                  "12b96c28-ba05-8906-c89t-703215cfb2e6"};
    EXPECT_THROW((void)api.query_block_trade_details(params), common::BadRequestError);
}

TEST(RestApiMarketMakerBlockTradeApi, AccountBlockTradeList) {
    const std::string example =
        R"json([{"parentOrderId":"4675011431944499201","crossType":"USER_BLOCK","legs":[{"createTime":1730170445600,"updateTime":1730170445600,"symbol":"BNB-241101-700-C","orderId":"4675011431944499203","orderPrice":2.8,"orderQuantity":1.2,"orderStatus":"FILLED","executedQty":1.2,"executedAmount":3.36,"fee":0.336,"orderType":"PREV_QUOTED","orderSide":"BUY","id":"1125899906900937837","tradeId":1,"tradePrice":2.8,"tradeQty":1.2,"tradeTime":1730170445600,"liquidity":"TAKER","commission":0.336}],"blockTradeSettlementKey":"7d085e6e-a229-2335-ab9d-6a581febcd25"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountBlockTradeListParams params{};
    const auto res = api.account_block_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/block/user-trades");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, AccountBlockTradeListWithOptionalParams) {
    const std::string example =
        R"json([{"parentOrderId":"4675011431944499201","crossType":"USER_BLOCK","legs":[{"createTime":1730170445600,"updateTime":1730170445600,"symbol":"BNB-241101-700-C","orderId":"4675011431944499203","orderPrice":2.8,"orderQuantity":1.2,"orderStatus":"FILLED","executedQty":1.2,"executedAmount":3.36,"fee":0.336,"orderType":"PREV_QUOTED","orderSide":"BUY","id":"1125899906900937837","tradeId":1,"tradePrice":2.8,"tradeQty":1.2,"tradeTime":1730170445600,"liquidity":"TAKER","commission":0.336}],"blockTradeSettlementKey":"7d085e6e-a229-2335-ab9d-6a581febcd25"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountBlockTradeListParams params{
        .end_time = 1641782889000,
        .start_time = 1623319461670,
        .underlying = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.account_block_trade_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, AccountBlockTradeListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountBlockTradeListParams params{};
    EXPECT_THROW((void)api.account_block_trade_list(params), common::BadRequestError);
}

TEST(RestApiMarketMakerBlockTradeApi, CancelBlockTradeOrder) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelBlockTradeOrderParams params{.block_order_matching_key =
                                                 "7d046e6e-a429-4335-ab9d-6a681febcde5"};
    const auto res = api.cancel_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/eapi/v1/block/order/create");
    EXPECT_NE((rec.query() + "&" + rec.body).find("blockOrderMatchingKey="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, CancelBlockTradeOrderWithOptionalParams) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelBlockTradeOrderParams params{
        .block_order_matching_key = "7d046e6e-a429-4335-ab9d-6a681febcde5",
        .recv_window = 5000,
    };
    const auto res = api.cancel_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("blockOrderMatchingKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, CancelBlockTradeOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelBlockTradeOrderParams params{.block_order_matching_key =
                                                 "7d046e6e-a429-4335-ab9d-6a681febcde5"};
    EXPECT_THROW((void)api.cancel_block_trade_order(params), common::BadRequestError);
}

TEST(RestApiMarketMakerBlockTradeApi, ExtendBlockTradeOrder) {
    const std::string example =
        R"json({"blockTradeSettlementKey":"3668822b8-1baa-6a2f-adb8-d3de6289b361","expireTime":1730172007000,"liquidity":"TAKER","status":"RECEIVED","createTime":1730170088111,"legs":[{"symbol":"BNB-241101-700-C","side":"BUY","quantity":"1.2","price":"2.8"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExtendBlockTradeOrderParams params{.block_order_matching_key =
                                                 "3668822b8-1baa-6a2f-adb8-d3de6289b361"};
    const auto res = api.extend_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/eapi/v1/block/order/create");
    EXPECT_NE((rec.query() + "&" + rec.body).find("blockOrderMatchingKey="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, ExtendBlockTradeOrderWithOptionalParams) {
    const std::string example =
        R"json({"blockTradeSettlementKey":"3668822b8-1baa-6a2f-adb8-d3de6289b361","expireTime":1730172007000,"liquidity":"TAKER","status":"RECEIVED","createTime":1730170088111,"legs":[{"symbol":"BNB-241101-700-C","side":"BUY","quantity":"1.2","price":"2.8"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExtendBlockTradeOrderParams params{
        .block_order_matching_key = "3668822b8-1baa-6a2f-adb8-d3de6289b361",
        .recv_window = 5000,
    };
    const auto res = api.extend_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("blockOrderMatchingKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, ExtendBlockTradeOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ExtendBlockTradeOrderParams params{.block_order_matching_key =
                                                 "3668822b8-1baa-6a2f-adb8-d3de6289b361"};
    EXPECT_THROW((void)api.extend_block_trade_order(params), common::BadRequestError);
}

TEST(RestApiMarketMakerBlockTradeApi, NewBlockTradeOrder) {
    const std::string example =
        R"json({"blockTradeSettlementKey":"3668822b8-1baa-6a2f-adb8-d3de6289b361","expireTime":1730171888109,"liquidity":"TAKER","status":"RECEIVED","legs":[{"symbol":"BNB-241101-700-C","side":"BUY","quantity":"1.2","price":"2.8"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewBlockTradeOrderParams params{.liquidity = NewBlockTradeOrderLiquidityEnum::Maker,
                                          .legs =
                                              std::vector<NewBlockTradeOrderLegsParameterInner>{}};
    const auto res = api.new_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/eapi/v1/block/order/create");
    EXPECT_NE((rec.query() + "&" + rec.body).find("liquidity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("legs="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, NewBlockTradeOrderWithOptionalParams) {
    const std::string example =
        R"json({"blockTradeSettlementKey":"3668822b8-1baa-6a2f-adb8-d3de6289b361","expireTime":1730171888109,"liquidity":"TAKER","status":"RECEIVED","legs":[{"symbol":"BNB-241101-700-C","side":"BUY","quantity":"1.2","price":"2.8"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NewBlockTradeOrderParams params{
        .liquidity = NewBlockTradeOrderLiquidityEnum::Maker,
        .legs = std::vector<NewBlockTradeOrderLegsParameterInner>{},
        .recv_window = 5000,
    };
    const auto res = api.new_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("liquidity="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, NewBlockTradeOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NewBlockTradeOrderParams params{.liquidity = NewBlockTradeOrderLiquidityEnum::Maker,
                                          .legs =
                                              std::vector<NewBlockTradeOrderLegsParameterInner>{}};
    EXPECT_THROW((void)api.new_block_trade_order(params), common::BadRequestError);
}

TEST(RestApiMarketMakerBlockTradeApi, QueryBlockTradeOrder) {
    const std::string example =
        R"json([{"blockTradeSettlementKey":"7d046e6e-a429-4335-ab9d-6a681febcde5","expireTime":1730172115801,"liquidity":"TAKER","status":"RECEIVED","createTime":1730170315803,"legs":[{"symbol":"BNB-241101-700-C","side":"BUY","quantity":"1.2","price":"2.8"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryBlockTradeOrderParams params{};
    const auto res = api.query_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/eapi/v1/block/order/orders");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, QueryBlockTradeOrderWithOptionalParams) {
    const std::string example =
        R"json([{"blockTradeSettlementKey":"7d046e6e-a429-4335-ab9d-6a681febcde5","expireTime":1730172115801,"liquidity":"TAKER","status":"RECEIVED","createTime":1730170315803,"legs":[{"symbol":"BNB-241101-700-C","side":"BUY","quantity":"1.2","price":"2.8"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryBlockTradeOrderParams params{
        .block_order_matching_key = "7d046e6e-a429-4335-ab9d-6a681febcde5",
        .end_time = 1641782889000,
        .start_time = 1623319461670,
        .underlying = "BTCUSDT",
        .recv_window = 5000,
    };
    const auto res = api.query_block_trade_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("blockOrderMatchingKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("underlying="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiMarketMakerBlockTradeApi, QueryBlockTradeOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryBlockTradeOrderParams params{};
    EXPECT_THROW((void)api.query_block_trade_order(params), common::BadRequestError);
}
