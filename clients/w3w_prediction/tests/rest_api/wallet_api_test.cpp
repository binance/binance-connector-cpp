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
#include <binance/w3w_prediction/rest_api/wallet_api.hpp>

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

WalletApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return WalletApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiWalletApi, GetPortfolio) {
    const std::string example =
        R"json({"chainId":"56","walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","activePositionsCount":3,"totalRealizedPnl":"120.50","totalUnrealizedPnl":"15.30","totalPnl":"135.80","totalCostBasis":"450.00","totalCurrentValue":"465.30","positions":[{"id":10001,"walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","marketTopicId":4229564,"marketId":5567895,"tokenId":"112233","vendor":"PREDICT_FUN","currentShares":"1923.07","avgPrice":"0.52","currentPrice":"0.55","realizedPnl":"0.00","unrealizedPnl":"0.06","totalPnl":"0.06","pnlPercentage":"6.00","isResolved":false}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPortfolioParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c"};
    const auto res = api.get_portfolio(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/pnl/portfolio");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiWalletApi, GetPortfolioWithOptionalParams) {
    const std::string example =
        R"json({"chainId":"56","walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","activePositionsCount":3,"totalRealizedPnl":"120.50","totalUnrealizedPnl":"15.30","totalPnl":"135.80","totalCostBasis":"450.00","totalCurrentValue":"465.30","positions":[{"id":10001,"walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","marketTopicId":4229564,"marketId":5567895,"tokenId":"112233","vendor":"PREDICT_FUN","currentShares":"1923.07","avgPrice":"0.52","currentPrice":"0.55","realizedPnl":"0.00","unrealizedPnl":"0.06","totalPnl":"0.06","pnlPercentage":"6.00","isResolved":false}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPortfolioParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .token_id = "112233",
        .market_id = 5567895,
        .market_topic_id = 4229564,
        .active_only = false,
        .recv_window = 5000,
    };
    const auto res = api.get_portfolio(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marketId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marketTopicId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("activeOnly="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiWalletApi, GetPortfolioBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetPortfolioParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c"};
    EXPECT_THROW((void)api.get_portfolio(params), common::BadRequestError);
}

TEST(RestApiWalletApi, GetQuotaStatus) {
    const std::string example =
        R"json({"dailyLimit":"10000.00","remainingDailyLimit":"8500.00"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetQuotaStatusParams params{};
    const auto res = api.get_quota_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/quota/limit/status");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiWalletApi, GetQuotaStatusWithOptionalParams) {
    const std::string example =
        R"json({"dailyLimit":"10000.00","remainingDailyLimit":"8500.00"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetQuotaStatusParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_quota_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiWalletApi, GetQuotaStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetQuotaStatusParams params{};
    EXPECT_THROW((void)api.get_quota_status(params), common::BadRequestError);
}

TEST(RestApiWalletApi, ListPredictionWallets) {
    const std::string example =
        R"json({"wallets":[{"walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","walletId":"5b5c1ec3be4e4416a5872b21c1ca5d20","registeredTime":1748000000000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ListPredictionWalletsParams params{};
    const auto res = api.list_prediction_wallets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/wallet/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiWalletApi, ListPredictionWalletsWithOptionalParams) {
    const std::string example =
        R"json({"wallets":[{"walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","walletId":"5b5c1ec3be4e4416a5872b21c1ca5d20","registeredTime":1748000000000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ListPredictionWalletsParams params{
        .recv_window = 5000,
    };
    const auto res = api.list_prediction_wallets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiWalletApi, ListPredictionWalletsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ListPredictionWalletsParams params{};
    EXPECT_THROW((void)api.list_prediction_wallets(params), common::BadRequestError);
}

TEST(RestApiWalletApi, QueryPaymentOptionBalances) {
    const std::string example =
        R"json({"items":[{"accountType":"SPOT","availableBalanceDisplay":"1000.00","enabled":true}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPaymentOptionBalancesParams params{};
    const auto res = api.query_payment_option_balances(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/balance/payment-options");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiWalletApi, QueryPaymentOptionBalancesWithOptionalParams) {
    const std::string example =
        R"json({"items":[{"accountType":"SPOT","availableBalanceDisplay":"1000.00","enabled":true}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPaymentOptionBalancesParams params{
        .recv_window = 5000,
    };
    const auto res = api.query_payment_option_balances(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiWalletApi, QueryPaymentOptionBalancesBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPaymentOptionBalancesParams params{};
    EXPECT_THROW((void)api.query_payment_option_balances(params), common::BadRequestError);
}
