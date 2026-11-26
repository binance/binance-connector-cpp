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
#include <binance/w3w_prediction/rest_api/position_api.hpp>

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

PositionApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return PositionApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiPositionApi, GetPositionByToken) {
    const std::string example =
        R"json({"position":{"positionId":1001,"vendor":"PREDICT_FUN","chainId":"56","tokenId":"112233","collateralSymbol":"USDT","topicType":"FLAT","marketTopicId":4229564,"marketId":5567895,"marketTopicTitle":"BTC Price 1h Up or Down?","marketTitle":"UP","outcomeName":"YES","outcomeIndex":0,"shares":"1923.07","avgPrice":"0.52","totalCost":"1.00","value":"1.06","currentPrice":"0.55","positionStatus":"OPEN","endDate":1748134800000,"unrealizedPnl":"0.06","realizedPnl":"0.00","pnl":"0.06","createdTime":1748131500000,"updatedTime":1748132000000}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPositionByTokenParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c", .token_id = "112233"};
    const auto res = api.get_position_by_token(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/position/token");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPositionApi, GetPositionByTokenWithOptionalParams) {
    const std::string example =
        R"json({"position":{"positionId":1001,"vendor":"PREDICT_FUN","chainId":"56","tokenId":"112233","collateralSymbol":"USDT","topicType":"FLAT","marketTopicId":4229564,"marketId":5567895,"marketTopicTitle":"BTC Price 1h Up or Down?","marketTitle":"UP","outcomeName":"YES","outcomeIndex":0,"shares":"1923.07","avgPrice":"0.52","totalCost":"1.00","value":"1.06","currentPrice":"0.55","positionStatus":"OPEN","endDate":1748134800000,"unrealizedPnl":"0.06","realizedPnl":"0.00","pnl":"0.06","createdTime":1748131500000,"updatedTime":1748132000000}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetPositionByTokenParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .token_id = "112233",
        .recv_window = 5000,
    };
    const auto res = api.get_position_by_token(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPositionApi, GetPositionByTokenBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetPositionByTokenParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c", .token_id = "112233"};
    EXPECT_THROW((void)api.get_position_by_token(params), common::BadRequestError);
}

TEST(RestApiPositionApi, QueryPnL) {
    const std::string example =
        R"json({"chainId":"56","walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","pnl":{},"pnlList":[{"id":10001,"walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","marketTopicId":4229564,"marketId":5567895,"tokenId":"112233","vendor":"PREDICT_FUN","currentShares":"1923.07","avgPrice":"0.52","currentPrice":"0.55","realizedPnl":"0.00","unrealizedPnl":"0.06","totalPnl":"0.06","pnlPercentage":"6.00","isResolved":false}],"totalCount":1,"totalRealizedPnl":"0.00","totalUnrealizedPnl":"0.06","totalPnl":"0.06"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPnLParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c"};
    const auto res = api.query_pnl(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/pnl/query");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPositionApi, QueryPnLWithOptionalParams) {
    const std::string example =
        R"json({"chainId":"56","walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","pnl":{},"pnlList":[{"id":10001,"walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","marketTopicId":4229564,"marketId":5567895,"tokenId":"112233","vendor":"PREDICT_FUN","currentShares":"1923.07","avgPrice":"0.52","currentPrice":"0.55","realizedPnl":"0.00","unrealizedPnl":"0.06","totalPnl":"0.06","pnlPercentage":"6.00","isResolved":false}],"totalCount":1,"totalRealizedPnl":"0.00","totalUnrealizedPnl":"0.06","totalPnl":"0.06"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPnLParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .token_id = "112233",
        .market_id = 5567895,
        .market_topic_id = 4229564,
        .active_only = false,
        .recv_window = 5000,
    };
    const auto res = api.query_pnl(params);
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

TEST(RestApiPositionApi, QueryPnLBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPnLParams params{.wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c"};
    EXPECT_THROW((void)api.query_pnl(params), common::BadRequestError);
}

TEST(RestApiPositionApi, QueryPositions) {
    const std::string example =
        R"json({"summary":{"totalValue":"1523.45","positionValue":"523.45","walletBalance":"1000.00","totalClaimableAmount":"50.00","todayRealizedPnl":"15.30","todayRealizedPnlPercent":"3.10","todayTotalCost":"493.55"},"counts":{"ongoingCount":3,"endedCount":12,"pendingClaimCount":1},"positions":[{"positionId":1001,"vendor":"PREDICT_FUN","chainId":"56","tokenId":"112233","collateralSymbol":"USDT","topicType":"FLAT","marketTopicId":4229564,"marketId":5567895,"marketTopicTitle":"BTC Price 1h Up or Down?","marketTitle":"UP","outcomeName":"YES","outcomeIndex":0,"shares":"1923.07","avgPrice":"0.52","totalCost":"1.00","value":"1.06","currentPrice":"0.55","toWin":"1923.07","positionStatus":"OPEN","canClaim":false,"endDate":1748134800000,"unrealizedPnl":"0.06","unrealizedPnlPercent":"6.00","realizedPnl":"0.00","pnl":"0.06","createdTime":1748131500000,"updatedTime":1748132000000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPositionsParams params{.wallet_address =
                                          "0x12e32db8817e292508c34111cbc4b23340df542c"};
    const auto res = api.query_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/position/list");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPositionApi, QueryPositionsWithOptionalParams) {
    const std::string example =
        R"json({"summary":{"totalValue":"1523.45","positionValue":"523.45","walletBalance":"1000.00","totalClaimableAmount":"50.00","todayRealizedPnl":"15.30","todayRealizedPnlPercent":"3.10","todayTotalCost":"493.55"},"counts":{"ongoingCount":3,"endedCount":12,"pendingClaimCount":1},"positions":[{"positionId":1001,"vendor":"PREDICT_FUN","chainId":"56","tokenId":"112233","collateralSymbol":"USDT","topicType":"FLAT","marketTopicId":4229564,"marketId":5567895,"marketTopicTitle":"BTC Price 1h Up or Down?","marketTitle":"UP","outcomeName":"YES","outcomeIndex":0,"shares":"1923.07","avgPrice":"0.52","totalCost":"1.00","value":"1.06","currentPrice":"0.55","toWin":"1923.07","positionStatus":"OPEN","canClaim":false,"endDate":1748134800000,"unrealizedPnl":"0.06","unrealizedPnlPercent":"6.00","realizedPnl":"0.00","pnl":"0.06","createdTime":1748131500000,"updatedTime":1748132000000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPositionsParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .tab = "ONGOING",
        .offset = 0,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.query_positions(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tab="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPositionApi, QueryPositionsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPositionsParams params{.wallet_address =
                                          "0x12e32db8817e292508c34111cbc4b23340df542c"};
    EXPECT_THROW((void)api.query_positions(params), common::BadRequestError);
}

TEST(RestApiPositionApi, QueryPositionsByFilter) {
    const std::string example =
        R"json({"positions":[{"positionId":1001,"vendor":"PREDICT_FUN","chainId":"56","tokenId":"112233","collateralSymbol":"USDT","topicType":"FLAT","marketTopicId":4229564,"marketId":5567895,"marketTopicTitle":"BTC Price 1h Up or Down?","marketTitle":"UP","outcomeName":"YES","outcomeIndex":0,"shares":"1923.07","avgPrice":"0.52","totalCost":"1.00","value":"1.06","currentPrice":"0.55","positionStatus":"OPEN","endDate":1748134800000,"unrealizedPnl":"0.06","realizedPnl":"0.00","pnl":"0.06","createdTime":1748131500000,"updatedTime":1748132000000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPositionsByFilterParams params{};
    const auto res = api.query_positions_by_filter(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/position/filter");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPositionApi, QueryPositionsByFilterWithOptionalParams) {
    const std::string example =
        R"json({"positions":[{"positionId":1001,"vendor":"PREDICT_FUN","chainId":"56","tokenId":"112233","collateralSymbol":"USDT","topicType":"FLAT","marketTopicId":4229564,"marketId":5567895,"marketTopicTitle":"BTC Price 1h Up or Down?","marketTitle":"UP","outcomeName":"YES","outcomeIndex":0,"shares":"1923.07","avgPrice":"0.52","totalCost":"1.00","value":"1.06","currentPrice":"0.55","positionStatus":"OPEN","endDate":1748134800000,"unrealizedPnl":"0.06","realizedPnl":"0.00","pnl":"0.06","createdTime":1748131500000,"updatedTime":1748132000000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryPositionsByFilterParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .market_topic_id = 4229564,
        .recv_window = 5000,
    };
    const auto res = api.query_positions_by_filter(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("marketTopicId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPositionApi, QueryPositionsByFilterBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryPositionsByFilterParams params{};
    EXPECT_THROW((void)api.query_positions_by_filter(params), common::BadRequestError);
}

TEST(RestApiPositionApi, QuerySettledPositionHistory) {
    const std::string example =
        R"json({"totalCount":5,"positions":[{"positionId":998,"vendor":"PREDICT_FUN","chainId":"56","tokenId":"112200","collateralSymbol":"USDT","topicType":"FLAT","marketTopicId":4229500,"marketId":5567800,"marketTopicTitle":"BTC Price 1h Up or Down?","marketTitle":"UP","outcomeName":"YES","outcomeIndex":0,"shares":"5000.00","avgPrice":"0.30","totalCost":"1.50","value":"5000.00","currentPrice":"1.00","toWin":"5000.00","positionStatus":"CLAIMED","isWinner":true,"redeemStatus":"CONFIRMED","endDate":1748040000000,"finalOutcome":"YES","realizedPnl":"4998.50","pnl":"4998.50","claimAmount":"5000.00","settledDate":1748040000000,"createdTime":1748020000000,"updatedTime":1748040500000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySettledPositionHistoryParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c"};
    const auto res = api.query_settled_position_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/position/settled-history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPositionApi, QuerySettledPositionHistoryWithOptionalParams) {
    const std::string example =
        R"json({"totalCount":5,"positions":[{"positionId":998,"vendor":"PREDICT_FUN","chainId":"56","tokenId":"112200","collateralSymbol":"USDT","topicType":"FLAT","marketTopicId":4229500,"marketId":5567800,"marketTopicTitle":"BTC Price 1h Up or Down?","marketTitle":"UP","outcomeName":"YES","outcomeIndex":0,"shares":"5000.00","avgPrice":"0.30","totalCost":"1.50","value":"5000.00","currentPrice":"1.00","toWin":"5000.00","positionStatus":"CLAIMED","isWinner":true,"redeemStatus":"CONFIRMED","endDate":1748040000000,"finalOutcome":"YES","realizedPnl":"4998.50","pnl":"4998.50","claimAmount":"5000.00","settledDate":1748040000000,"createdTime":1748020000000,"updatedTime":1748040500000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySettledPositionHistoryParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .l1_category = "crypto",
        .result = 1,
        .start_date = "2026-05-01",
        .end_date = "2026-05-25",
        .offset = 0,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.query_settled_position_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("l1Category="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("result="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiPositionApi, QuerySettledPositionHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySettledPositionHistoryParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c"};
    EXPECT_THROW((void)api.query_settled_position_history(params), common::BadRequestError);
}
