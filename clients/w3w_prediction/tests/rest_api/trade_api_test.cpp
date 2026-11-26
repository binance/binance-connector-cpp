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
#include <binance/w3w_prediction/rest_api/trade_api.hpp>

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

TradeApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return TradeApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiTradeApi, BatchCancelOrders) {
    const std::string example =
        R"json({"canceled":["54124"],"failed":[{"orderId":"54126","reason":"ORDER_NOT_FOUND"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BatchCancelOrdersParams params{.wallet_address =
                                             "0x12e32db8817e292508c34111cbc4b23340df542c",
                                         .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20"};
    const auto res = api.batch_cancel_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/trade/batch-cancel");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, BatchCancelOrdersWithOptionalParams) {
    const std::string example =
        R"json({"canceled":["54124"],"failed":[{"orderId":"54126","reason":"ORDER_NOT_FOUND"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BatchCancelOrdersParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
        .cancel_info_list = std::vector<BatchCancelOrdersCancelInfoListParameterInner>{},
    };
    const auto res = api.batch_cancel_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, BatchCancelOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const BatchCancelOrdersParams params{.wallet_address =
                                             "0x12e32db8817e292508c34111cbc4b23340df542c",
                                         .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20"};
    EXPECT_THROW((void)api.batch_cancel_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, GetQuote) {
    const std::string example =
        R"json({"quoteId":"q_20260525_abc123xyz","tokenId":"112233","chance":"0.52","vendor":"PREDICT_FUN","marketTitle":"UP","marketExtId":"ext_001","side":"BUY","amountIn":"1000000000000000000","amountOut":"1923070000000000000","isMinAmountOut":false,"feeAmount":"20000000000000000","feeDiscountBps":"0","averagePrice":0.52,"lastPrice":0.52,"priceImpact":0.001,"timestamp":1748131500000,"chainId":"56","userId":100103755893,"walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","orderType":"MARKET","slippageBps":1200,"feeRateBps":200,"minReceive":"1900000000000000000","expireAt":1748131800000,"priceLimit":"priceLimit"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetQuoteParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
                                .token_id = "112233",
                                .side = GetQuoteSideEnum::Buy,
                                .amount_in = "1000000000000000000",
                                .order_type = GetQuoteOrderTypeEnum::Market,
                                .slippage_bps = 1200};
    const auto res = api.get_quote(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/trade/get-quote");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amountIn="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("slippageBps="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetQuoteWithOptionalParams) {
    const std::string example =
        R"json({"quoteId":"q_20260525_abc123xyz","tokenId":"112233","chance":"0.52","vendor":"PREDICT_FUN","marketTitle":"UP","marketExtId":"ext_001","side":"BUY","amountIn":"1000000000000000000","amountOut":"1923070000000000000","isMinAmountOut":false,"feeAmount":"20000000000000000","feeDiscountBps":"0","averagePrice":0.52,"lastPrice":0.52,"priceImpact":0.001,"timestamp":1748131500000,"chainId":"56","userId":100103755893,"walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","orderType":"MARKET","slippageBps":1200,"feeRateBps":200,"minReceive":"1900000000000000000","expireAt":1748131800000,"priceLimit":"priceLimit"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetQuoteParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .token_id = "112233",
        .side = GetQuoteSideEnum::Buy,
        .amount_in = "1000000000000000000",
        .order_type = GetQuoteOrderTypeEnum::Market,
        .slippage_bps = 1200,
        .price_limit = "0.5",
        .chain_id = "56",
        .fee_rate_bps = 200,
        .funding_source = GetQuoteFundingSourceEnum::Mpc,
        .fund_transfer_amount = "1000000000000000000",
    };
    const auto res = api.get_quote(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("side="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amountIn="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("slippageBps="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("chainId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("feeRateBps="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fundingSource="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fundTransferAmount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, GetQuoteBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetQuoteParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
                                .token_id = "112233",
                                .side = GetQuoteSideEnum::Buy,
                                .amount_in = "1000000000000000000",
                                .order_type = GetQuoteOrderTypeEnum::Market,
                                .slippage_bps = 1200};
    EXPECT_THROW((void)api.get_quote(params), common::BadRequestError);
}

TEST(RestApiTradeApi, PlaceOrder) {
    const std::string example = R"json({"orderId":"54124"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceOrderParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
                                  .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
                                  .quote_id = "q_20260525_abc123xyz",
                                  .time_in_force = "FOK",
                                  .account_type = PlaceOrderAccountTypeEnum::Spot,
                                  .order_type = PlaceOrderOrderTypeEnum::Market,
                                  .slippage_bps = 1200};
    const auto res = api.place_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/trade/place-order-bundle");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("slippageBps="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceOrderWithOptionalParams) {
    const std::string example = R"json({"orderId":"54124"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const PlaceOrderParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
        .quote_id = "q_20260525_abc123xyz",
        .time_in_force = "FOK",
        .account_type = PlaceOrderAccountTypeEnum::Spot,
        .order_type = PlaceOrderOrderTypeEnum::Market,
        .slippage_bps = 1200,
        .price_limit = "0.5",
        .funding_source = PlaceOrderFundingSourceEnum::Mpc,
        .fund_transfer_amount = "1000000000000000000",
    };
    const auto res = api.place_order(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("timeInForce="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("slippageBps="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("priceLimit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fundingSource="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fundTransferAmount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, PlaceOrderBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const PlaceOrderParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
                                  .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
                                  .quote_id = "q_20260525_abc123xyz",
                                  .time_in_force = "FOK",
                                  .account_type = PlaceOrderAccountTypeEnum::Spot,
                                  .order_type = PlaceOrderOrderTypeEnum::Market,
                                  .slippage_bps = 1200};
    EXPECT_THROW((void)api.place_order(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryActiveOrders) {
    const std::string example =
        R"json({"total":2,"offset":0,"limit":20,"orders":[{"orderId":"54124","vendorOrderId":"0x1234abcd...","vendor":"PREDICT_FUN","marketTopicId":4229564,"slug":"btc-price-1h-up-or-down","marketTopicTitle":"BTC Price 1h Up or Down?","marketId":5567895,"marketTitle":"UP","outcome":"YES","outcomeIndex":0,"status":"OPENING","side":"BUY","orderType":"LIMIT","createTime":1748131500000,"modifyTime":1748131500000,"makerUsdtAmount":"1.00","makerShareQty":"2000.00","filledUsdtAmount":"0.00","filledShareQty":"0.00","fillPercentage":"0.00","price":"0.50","marketProviderFee":"0.02","networkFee":"0.000001"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryActiveOrdersParams params{.wallet_address =
                                             "0x12e32db8817e292508c34111cbc4b23340df542c"};
    const auto res = api.query_active_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/order/list");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryActiveOrdersWithOptionalParams) {
    const std::string example =
        R"json({"total":2,"offset":0,"limit":20,"orders":[{"orderId":"54124","vendorOrderId":"0x1234abcd...","vendor":"PREDICT_FUN","marketTopicId":4229564,"slug":"btc-price-1h-up-or-down","marketTopicTitle":"BTC Price 1h Up or Down?","marketId":5567895,"marketTitle":"UP","outcome":"YES","outcomeIndex":0,"status":"OPENING","side":"BUY","orderType":"LIMIT","createTime":1748131500000,"modifyTime":1748131500000,"makerUsdtAmount":"1.00","makerShareQty":"2000.00","filledUsdtAmount":"0.00","filledShareQty":"0.00","fillPercentage":"0.00","price":"0.50","marketProviderFee":"0.02","networkFee":"0.000001"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryActiveOrdersParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .trade_side = QueryActiveOrdersTradeSideEnum::Buy,
        .l1_category = "crypto",
        .market_id = 5567895,
        .offset = 0,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.query_active_orders(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tradeSide="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("l1Category="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marketId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryActiveOrdersBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryActiveOrdersParams params{.wallet_address =
                                             "0x12e32db8817e292508c34111cbc4b23340df542c"};
    EXPECT_THROW((void)api.query_active_orders(params), common::BadRequestError);
}

TEST(RestApiTradeApi, QueryOrderHistory) {
    const std::string example =
        R"json({"total":15,"offset":0,"limit":20,"orders":[{"orderId":"54100","vendorOrderId":"0xabcd5678...","vendor":"PREDICT_FUN","marketTopicId":4229500,"slug":"btc-price-1h-up-or-down-prev","marketTopicTitle":"BTC Price 1h Up or Down?","marketId":5567800,"marketTitle":"UP","outcome":"YES","outcomeIndex":0,"status":"CLOSED","side":"BUY","orderType":"MARKET","createTime":1748045100000,"modifyTime":1748045101000,"terminalTime":1748045101000,"makerUsdtAmount":"1.00","makerShareQty":"1923.07","filledUsdtAmount":"1.00","filledShareQty":"1923.07","fillPercentage":"1.00","price":"0.52","marketProviderFee":"0.02","networkFee":"0.000001"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOrderHistoryParams params{.wallet_address =
                                             "0x12e32db8817e292508c34111cbc4b23340df542c"};
    const auto res = api.query_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/order/history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":15,"offset":0,"limit":20,"orders":[{"orderId":"54100","vendorOrderId":"0xabcd5678...","vendor":"PREDICT_FUN","marketTopicId":4229500,"slug":"btc-price-1h-up-or-down-prev","marketTopicTitle":"BTC Price 1h Up or Down?","marketId":5567800,"marketTitle":"UP","outcome":"YES","outcomeIndex":0,"status":"CLOSED","side":"BUY","orderType":"MARKET","createTime":1748045100000,"modifyTime":1748045101000,"terminalTime":1748045101000,"makerUsdtAmount":"1.00","makerShareQty":"1923.07","filledUsdtAmount":"1.00","filledShareQty":"1923.07","fillPercentage":"1.00","price":"0.52","marketProviderFee":"0.02","networkFee":"0.000001"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryOrderHistoryParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .l1_category = "crypto",
        .order_type = QueryOrderHistoryOrderTypeEnum::Market,
        .status = "CLOSED",
        .start_date = "2026-05-01",
        .end_date = "2026-05-25",
        .offset = 0,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.query_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("l1Category="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("orderType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTradeApi, QueryOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryOrderHistoryParams params{.wallet_address =
                                             "0x12e32db8817e292508c34111cbc4b23340df542c"};
    EXPECT_THROW((void)api.query_order_history(params), common::BadRequestError);
}
