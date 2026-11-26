//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string>

#include <boost/json/parse.hpp>
#include <boost/json/serialize.hpp>
#include <gtest/gtest.h>

#include <binance/common/errors.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/account_api.hpp>

#include "support/mock_ws_server.hpp"

using namespace binance;
using namespace binance::derivatives_trading_usds_futures::websocket_api;
using binance::test::MockWsServer;

namespace {

// Answers every request with `example` (a spec response envelope, or an empty result), or with
// an error envelope when `status` is not 200, under the request's id.
MockWsServer::Handler reply(std::string example, int status = 200) {
    return
        [example = std::move(example), status](MockWsServer::Session& s, const std::string& text) {
            const auto req = boost::json::parse(text).as_object();
            boost::json::object res;
            if (status != 200) {
                res["status"] = status;
                res["error"] = {{"code", -1102}, {"msg", "Mandatory parameter was not sent."}};
            } else if (example.empty()) {
                res["status"] = 200;
                res["result"] = boost::json::object{};
            } else {
                res = boost::json::parse(example).as_object();
            }
            res["id"] = req.at("id");
            s.send(boost::json::serialize(res));
        };
}

AccountApi api_for(const MockWsServer& server) {
    common::WebsocketApiConfig cfg;
    cfg.url = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    cfg.proxy_from_env = false;
    auto client = std::make_shared<common::WebsocketApi>(std::move(cfg));
    client->connect();
    return AccountApi(std::move(client));
}

boost::json::object first_request(const MockWsServer& server) {
    return boost::json::parse(server.sessions().front().received.front()).as_object();
}

} // namespace

TEST(WebsocketApiAccountApi, AccountInformation) {
    MockWsServer server(reply(R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":{"feeTier":0,"canTrade":true,"canDeposit":true,"canWithdraw":true,"updateTime":0,"multiAssetsMargin":true,"tradeGroupId":-1,"totalInitialMargin":"0.00000000","totalMaintMargin":"0.00000000","totalWalletBalance":"126.72469206","totalUnrealizedProfit":"0.00000000","totalMarginBalance":"126.72469206","totalPositionInitialMargin":"0.00000000","totalOpenOrderInitialMargin":"0.00000000","totalCrossWalletBalance":"126.72469206","totalCrossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"126.72469206","assets":[{"asset":"USDT","walletBalance":"23.72469206","unrealizedProfit":"0.00000000","marginBalance":"23.72469206","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"100","isolated":true,"entryPrice":"0.00000","maxNotional":"250000","bidNotional":"0","askNotional":"0","positionSide":"BOTH","positionAmt":"0","updateTime":0,"breakEvenPrice":"0.0"}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":20}]})json"));
    const auto api = api_for(server);
    const AccountInformationParams params{};
    const auto res = api.account_information(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.status");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountInformationWithOptionalParams) {
    MockWsServer server(reply(R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":{"feeTier":0,"canTrade":true,"canDeposit":true,"canWithdraw":true,"updateTime":0,"multiAssetsMargin":true,"tradeGroupId":-1,"totalInitialMargin":"0.00000000","totalMaintMargin":"0.00000000","totalWalletBalance":"126.72469206","totalUnrealizedProfit":"0.00000000","totalMarginBalance":"126.72469206","totalPositionInitialMargin":"0.00000000","totalOpenOrderInitialMargin":"0.00000000","totalCrossWalletBalance":"126.72469206","totalCrossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"126.72469206","assets":[{"asset":"USDT","walletBalance":"23.72469206","unrealizedProfit":"0.00000000","marginBalance":"23.72469206","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","initialMargin":"0","maintMargin":"0","unrealizedProfit":"0.00000000","positionInitialMargin":"0","openOrderInitialMargin":"0","leverage":"100","isolated":true,"entryPrice":"0.00000","maxNotional":"250000","bidNotional":"0","askNotional":"0","positionSide":"BOTH","positionAmt":"0","updateTime":0,"breakEvenPrice":"0.0"}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":20}]})json"));
    const auto api = api_for(server);
    const AccountInformationParams params{
        .id = "e9d6b4349871b40611412680b3445fac",
        .recv_window = 5000,
    };
    const auto res = api.account_information(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.status");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountInformationErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const AccountInformationParams params{};
    EXPECT_THROW((void)api.account_information(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, AccountInformationV2) {
    MockWsServer server(reply(
        R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":{"totalInitialMargin":"0.00000000","totalMaintMargin":"0.00000000","totalWalletBalance":"126.72469206","totalUnrealizedProfit":"0.00000000","totalMarginBalance":"126.72469206","totalPositionInitialMargin":"0.00000000","totalOpenOrderInitialMargin":"0.00000000","totalCrossWalletBalance":"126.72469206","totalCrossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"126.72469206","assets":[{"asset":"USDT","walletBalance":"23.72469206","unrealizedProfit":"0.00000000","marginBalance":"23.72469206","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","positionSide":"BOTH","positionAmt":"1.000","unrealizedProfit":"0.00000000","isolatedMargin":"0.00000000","notional":"0","isolatedWallet":"0","initialMargin":"0","maintMargin":"0","updateTime":0}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":20}]})json"));
    const auto api = api_for(server);
    const AccountInformationV2Params params{};
    const auto res = api.account_information_v2(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "v2/account.status");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountInformationV2WithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":{"totalInitialMargin":"0.00000000","totalMaintMargin":"0.00000000","totalWalletBalance":"126.72469206","totalUnrealizedProfit":"0.00000000","totalMarginBalance":"126.72469206","totalPositionInitialMargin":"0.00000000","totalOpenOrderInitialMargin":"0.00000000","totalCrossWalletBalance":"126.72469206","totalCrossUnPnl":"0.00000000","availableBalance":"126.72469206","maxWithdrawAmount":"126.72469206","assets":[{"asset":"USDT","walletBalance":"23.72469206","unrealizedProfit":"0.00000000","marginBalance":"23.72469206","maintMargin":"0.00000000","initialMargin":"0.00000000","positionInitialMargin":"0.00000000","openOrderInitialMargin":"0.00000000","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1625474304765}],"positions":[{"symbol":"BTCUSDT","positionSide":"BOTH","positionAmt":"1.000","unrealizedProfit":"0.00000000","isolatedMargin":"0.00000000","notional":"0","isolatedWallet":"0","initialMargin":"0","maintMargin":"0","updateTime":0}]},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":20}]})json"));
    const auto api = api_for(server);
    const AccountInformationV2Params params{
        .id = "e9d6b4349871b40611412680b3445fac",
        .recv_window = 5000,
    };
    const auto res = api.account_information_v2(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "v2/account.status");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, AccountInformationV2ErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const AccountInformationV2Params params{};
    EXPECT_THROW((void)api.account_information_v2(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, FuturesAccountBalance) {
    MockWsServer server(reply(
        R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":[{"accountAlias":"SgsR","asset":"USDT","balance":"122607.35137903","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1617939110373}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":20}]})json"));
    const auto api = api_for(server);
    const FuturesAccountBalanceParams params{};
    const auto res = api.futures_account_balance(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.balance");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, FuturesAccountBalanceWithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":[{"accountAlias":"SgsR","asset":"USDT","balance":"122607.35137903","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1617939110373}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":20}]})json"));
    const auto api = api_for(server);
    const FuturesAccountBalanceParams params{
        .id = "e9d6b4349871b40611412680b3445fac",
        .recv_window = 5000,
    };
    const auto res = api.futures_account_balance(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "account.balance");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, FuturesAccountBalanceErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const FuturesAccountBalanceParams params{};
    EXPECT_THROW((void)api.futures_account_balance(params), common::WebsocketResponseError);
}

TEST(WebsocketApiAccountApi, FuturesAccountBalanceV2) {
    MockWsServer server(reply(
        R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":[{"accountAlias":"SgsR","asset":"USDT","balance":"122607.35137903","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1617939110373}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":20}]})json"));
    const auto api = api_for(server);
    const FuturesAccountBalanceV2Params params{};
    const auto res = api.futures_account_balance_v2(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "v2/account.balance");
    EXPECT_TRUE(req.at("params").as_object().contains("signature"));
}

TEST(WebsocketApiAccountApi, FuturesAccountBalanceV2WithOptionalParams) {
    MockWsServer server(reply(
        R"json({"id":"605a6d20-6588-4cb9-afa0-b0ab087507ba","status":200,"result":[{"accountAlias":"SgsR","asset":"USDT","balance":"122607.35137903","crossWalletBalance":"23.72469206","crossUnPnl":"0.00000000","availableBalance":"23.72469206","maxWithdrawAmount":"23.72469206","marginAvailable":true,"updateTime":1617939110373}],"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":20}]})json"));
    const auto api = api_for(server);
    const FuturesAccountBalanceV2Params params{
        .id = "e9d6b4349871b40611412680b3445fac",
        .recv_window = 5000,
    };
    const auto res = api.futures_account_balance_v2(params);
    EXPECT_NO_THROW((void)res.data());

    const auto req = first_request(server);
    EXPECT_EQ(req.at("method").as_string(), "v2/account.balance");
    [[maybe_unused]] const auto& sent = req.at("params").as_object();

    EXPECT_TRUE(sent.contains("recvWindow"));
    EXPECT_TRUE(sent.contains("signature"));
}

TEST(WebsocketApiAccountApi, FuturesAccountBalanceV2ErrorResponse) {
    MockWsServer server(reply({}, 400));
    const auto api = api_for(server);
    const FuturesAccountBalanceV2Params params{};
    EXPECT_THROW((void)api.futures_account_balance_v2(params), common::WebsocketResponseError);
}
