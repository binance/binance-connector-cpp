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
#include <binance/derivatives_trading_coin_futures/rest_api/account_api.hpp>

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

AccountApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return AccountApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiAccountApi, AccountInformation) {
    const std::string example =
        R"json({"assets":[{"asset":"BTC","walletBalance":"0.00241969","unrealizedProfit":"0.00000000","marginBalance":"0.00241969","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","maxWithdrawAmount":"0.00241969","crossWalletBalance":"0.00241969","crossUnPnl":"0.00000000","availableBalance":"0.00241969","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSD_201225","positionAmt":"0","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"125","isolated":false,"positionSide":"BOTH","entryPrice":"0.0","breakEvenPrice":"0.0","maxQty":"50","updateTime":0,"notionalValue":"0"}],"canDeposit":true,"canTrade":true,"canWithdraw":true,"feeTier":2,"updateTime":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInformationParams params{};
    const auto res = api.account_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/account");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInformationWithOptionalParams) {
    const std::string example =
        R"json({"assets":[{"asset":"BTC","walletBalance":"0.00241969","unrealizedProfit":"0.00000000","marginBalance":"0.00241969","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","maxWithdrawAmount":"0.00241969","crossWalletBalance":"0.00241969","crossUnPnl":"0.00000000","availableBalance":"0.00241969","updateTime":1625474304765}],"positions":[{"symbol":"BTCUSD_201225","positionAmt":"0","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"125","isolated":false,"positionSide":"BOTH","entryPrice":"0.0","breakEvenPrice":"0.0","maxQty":"50","updateTime":0,"notionalValue":"0"}],"canDeposit":true,"canTrade":true,"canWithdraw":true,"feeTier":2,"updateTime":0})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountInformationParams params{
        .recv_window = 5000,
    };
    const auto res = api.account_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, AccountInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountInformationParams params{};
    EXPECT_THROW((void)api.account_information(params), common::BadRequestError);
}

TEST(RestApiAccountApi, FuturesAccountBalance) {
    const std::string example =
        R"json([{"accountAlias":"SgsR","asset":"BTC","balance":"0.00250000","withdrawAvailable":"0.00250000","crossWalletBalance":"0.00241969","crossUnPnl":"0.00000000","availableBalance":"0.00241969","updateTime":1592468353979}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesAccountBalanceParams params{};
    const auto res = api.futures_account_balance(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/balance");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FuturesAccountBalanceWithOptionalParams) {
    const std::string example =
        R"json([{"accountAlias":"SgsR","asset":"BTC","balance":"0.00250000","withdrawAvailable":"0.00250000","crossWalletBalance":"0.00241969","crossUnPnl":"0.00000000","availableBalance":"0.00241969","updateTime":1592468353979}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FuturesAccountBalanceParams params{
        .recv_window = 5000,
    };
    const auto res = api.futures_account_balance(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, FuturesAccountBalanceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FuturesAccountBalanceParams params{};
    EXPECT_THROW((void)api.futures_account_balance(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetCurrentPositionMode) {
    const std::string example = R"json({"dualSidePosition":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCurrentPositionModeParams params{};
    const auto res = api.get_current_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/positionSide/dual");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCurrentPositionModeWithOptionalParams) {
    const std::string example = R"json({"dualSidePosition":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCurrentPositionModeParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_current_position_mode(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetCurrentPositionModeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCurrentPositionModeParams params{};
    EXPECT_THROW((void)api.get_current_position_mode(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesOrderHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesOrderHistoryParams params{.start_time = 1623319461670,
                                                           .end_time = 1641782889000};
    const auto res = api.get_download_id_for_futures_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/order/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesOrderHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesOrderHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_futures_order_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesOrderHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesOrderHistoryParams params{.start_time = 1623319461670,
                                                           .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_futures_order_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTradeHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTradeHistoryParams params{.start_time = 1623319461670,
                                                           .end_time = 1641782889000};
    const auto res = api.get_download_id_for_futures_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/trade/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTradeHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTradeHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_futures_trade_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTradeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTradeHistoryParams params{.start_time = 1623319461670,
                                                           .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_futures_trade_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTransactionHistory) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTransactionHistoryParams params{.start_time = 1623319461670,
                                                                 .end_time = 1641782889000};
    const auto res = api.get_download_id_for_futures_transaction_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/income/asyn");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTransactionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"avgCostTimestampOfLast30d":7241837,"downloadId":"546975389218332672"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTransactionHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.get_download_id_for_futures_transaction_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetDownloadIdForFuturesTransactionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetDownloadIdForFuturesTransactionHistoryParams params{.start_time = 1623319461670,
                                                                 .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_download_id_for_futures_transaction_history(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetFuturesOrderHistoryDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesOrderHistoryDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    const auto res = api.get_futures_order_history_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/order/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetFuturesOrderHistoryDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesOrderHistoryDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_futures_order_history_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetFuturesOrderHistoryDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesOrderHistoryDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    EXPECT_THROW((void)api.get_futures_order_history_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetFuturesTradeDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesTradeDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    const auto res = api.get_futures_trade_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/trade/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetFuturesTradeDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesTradeDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_futures_trade_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetFuturesTradeDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesTradeDownloadLinkByIdParams params{.download_id = "545923594199212032"};
    EXPECT_THROW((void)api.get_futures_trade_download_link_by_id(params), common::BadRequestError);
}

TEST(RestApiAccountApi, GetFuturesTransactionHistoryDownloadLinkById) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesTransactionHistoryDownloadLinkByIdParams params{.download_id =
                                                                        "545923594199212032"};
    const auto res = api.get_futures_transaction_history_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/income/asyn/id");
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetFuturesTransactionHistoryDownloadLinkByIdWithOptionalParams) {
    const std::string example =
        R"json({"downloadId":"545923594199212032","status":"processing","url":"","notified":false,"expirationTimestamp":-1,"isExpired":"null"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetFuturesTransactionHistoryDownloadLinkByIdParams params{
        .download_id = "545923594199212032",
        .recv_window = 5000,
    };
    const auto res = api.get_futures_transaction_history_download_link_by_id(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("downloadId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetFuturesTransactionHistoryDownloadLinkByIdBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetFuturesTransactionHistoryDownloadLinkByIdParams params{.download_id =
                                                                        "545923594199212032"};
    EXPECT_THROW((void)api.get_futures_transaction_history_download_link_by_id(params),
                 common::BadRequestError);
}

TEST(RestApiAccountApi, GetIncomeHistory) {
    const std::string example =
        R"json([{"symbol":"","incomeType":"TRANSFER","income":"-0.37500000","asset":"BTC","info":"WITHDRAW","time":1570608000000,"tranId":"9689322392","tradeId":""}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetIncomeHistoryParams params{};
    const auto res = api.get_income_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/income");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetIncomeHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"","incomeType":"TRANSFER","income":"-0.37500000","asset":"BTC","info":"WITHDRAW","time":1570608000000,"tranId":"9689322392","tradeId":""}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetIncomeHistoryParams params{
        .symbol = "BTCUSDT",
        .income_type = GetIncomeHistoryIncomeTypeEnum::Transfer,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 30,
        .recv_window = 5000,
    };
    const auto res = api.get_income_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("incomeType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, GetIncomeHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetIncomeHistoryParams params{};
    EXPECT_THROW((void)api.get_income_history(params), common::BadRequestError);
}

TEST(RestApiAccountApi, NotionalBracketForPair) {
    const std::string example =
        R"json([{"pair":"BTCUSD","brackets":[{"bracket":1,"initialLeverage":125,"qtyCap":50,"qtylFloor":0,"maintMarginRatio":0.004,"cum":0}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NotionalBracketForPairParams params{};
    const auto res = api.notional_bracket_for_pair(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/leverageBracket");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, NotionalBracketForPairWithOptionalParams) {
    const std::string example =
        R"json([{"pair":"BTCUSD","brackets":[{"bracket":1,"initialLeverage":125,"qtyCap":50,"qtylFloor":0,"maintMarginRatio":0.004,"cum":0}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NotionalBracketForPairParams params{
        .pair = "BTCUSD",
        .recv_window = 5000,
    };
    const auto res = api.notional_bracket_for_pair(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pair="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, NotionalBracketForPairBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NotionalBracketForPairParams params{};
    EXPECT_THROW((void)api.notional_bracket_for_pair(params), common::BadRequestError);
}

TEST(RestApiAccountApi, NotionalBracketForSymbol) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_PERP","notionalCoef":1.5,"brackets":[{"bracket":1,"initialLeverage":125,"qtyCap":50,"qtylFloor":0,"maintMarginRatio":0.004,"cum":0}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NotionalBracketForSymbolParams params{};
    const auto res = api.notional_bracket_for_symbol(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v2/leverageBracket");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, NotionalBracketForSymbolWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"BTCUSD_PERP","notionalCoef":1.5,"brackets":[{"bracket":1,"initialLeverage":125,"qtyCap":50,"qtylFloor":0,"maintMarginRatio":0.004,"cum":0}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const NotionalBracketForSymbolParams params{
        .symbol = "BTCUSD_PERP",
        .recv_window = 5000,
    };
    const auto res = api.notional_bracket_for_symbol(params);
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

TEST(RestApiAccountApi, NotionalBracketForSymbolBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const NotionalBracketForSymbolParams params{};
    EXPECT_THROW((void)api.notional_bracket_for_symbol(params), common::BadRequestError);
}

TEST(RestApiAccountApi, UserCommissionRate) {
    const std::string example =
        R"json({"symbol":"BTCUSD_PERP","makerCommissionRate":"0.00015","takerCommissionRate":"0.00040"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserCommissionRateParams params{.symbol = "BTCUSD_PERP"};
    const auto res = api.user_commission_rate(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/dapi/v1/commissionRate");
    EXPECT_NE((rec.query() + "&" + rec.body).find("symbol="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAccountApi, UserCommissionRateWithOptionalParams) {
    const std::string example =
        R"json({"symbol":"BTCUSD_PERP","makerCommissionRate":"0.00015","takerCommissionRate":"0.00040"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserCommissionRateParams params{
        .symbol = "BTCUSD_PERP",
        .recv_window = 5000,
    };
    const auto res = api.user_commission_rate(params);
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

TEST(RestApiAccountApi, UserCommissionRateBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UserCommissionRateParams params{.symbol = "BTCUSD_PERP"};
    EXPECT_THROW((void)api.user_commission_rate(params), common::BadRequestError);
}
