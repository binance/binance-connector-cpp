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
#include <binance/mining/rest_api/api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::mining::rest_api;
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

Api api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return Api(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiDefaultApi, AccountList) {
    const std::string example =
        R"json({"code":0,"msg":"","data":[{"type":"H_hashrate","userName":"test","list":[{"time":1585267200000,"hashrate":"0.00000000","reject":"0.00000000"}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountListParams params{.algo = "sha256", .user_name = "test"};
    const auto res = api.account_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/statistics/user/list");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, AccountListWithOptionalParams) {
    const std::string example =
        R"json({"code":0,"msg":"","data":[{"type":"H_hashrate","userName":"test","list":[{"time":1585267200000,"hashrate":"0.00000000","reject":"0.00000000"}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AccountListParams params{
        .algo = "sha256",
        .user_name = "test",
        .recv_window = 5000,
    };
    const auto res = api.account_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, AccountListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AccountListParams params{.algo = "sha256", .user_name = "test"};
    EXPECT_THROW((void)api.account_list(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, AcquiringAlgorithm) {
    const std::string example =
        R"json({"code":0,"msg":"","data":[{"algoName":"SHA256-BTC","algoId":1,"poolIndex":100,"unit":"h/s"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.acquiring_algorithm();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/pub/algoList");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, AcquiringAlgorithmBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.acquiring_algorithm(), common::BadRequestError);
}

TEST(RestApiDefaultApi, AcquiringCoinname) {
    const std::string example =
        R"json({"code":0,"msg":"","data":[{"coinName":"BTC","coinId":1,"poolIndex":0,"algoId":1,"algoName":"SHA256-BTC"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.acquiring_coinname();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/pub/coinList");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, AcquiringCoinnameBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.acquiring_coinname(), common::BadRequestError);
}

TEST(RestApiDefaultApi, CancelHashrateResaleConfiguration) {
    const std::string example = R"json({"code":0,"msg":"","data":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelHashrateResaleConfigurationParams params{.config_id = 168, .user_name = "test"};
    const auto res = api.cancel_hashrate_resale_configuration(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/hash-transfer/config/cancel");
    EXPECT_NE((rec.query() + "&" + rec.body).find("configId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, CancelHashrateResaleConfigurationWithOptionalParams) {
    const std::string example = R"json({"code":0,"msg":"","data":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CancelHashrateResaleConfigurationParams params{
        .config_id = 168,
        .user_name = "test",
        .recv_window = 5000,
    };
    const auto res = api.cancel_hashrate_resale_configuration(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("configId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, CancelHashrateResaleConfigurationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CancelHashrateResaleConfigurationParams params{.config_id = 168, .user_name = "test"};
    EXPECT_THROW((void)api.cancel_hashrate_resale_configuration(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, EarningsList) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"accountProfits":[{"time":1586188800000,"type":31,"hashTransfer":200000000000,"transferAmount":0.02180958,"dayHashRate":129129903378244,"profitAmount":8.6083060304,"coinName":"BTC","status":2}],"totalNum":3,"pageSize":20}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EarningsListParams params{.algo = "sha256", .user_name = "test"};
    const auto res = api.earnings_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/payment/list");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, EarningsListWithOptionalParams) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"accountProfits":[{"time":1586188800000,"type":31,"hashTransfer":200000000000,"transferAmount":0.02180958,"dayHashRate":129129903378244,"profitAmount":8.6083060304,"coinName":"BTC","status":2}],"totalNum":3,"pageSize":20}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const EarningsListParams params{
        .algo = "sha256",
        .user_name = "test",
        .coin = "BTC",
        .start_date = 1770736694138,
        .end_date = 1770736694138,
        .page_index = 1,
        .page_size = 10,
        .recv_window = 5000,
    };
    const auto res = api.earnings_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageIndex="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, EarningsListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const EarningsListParams params{.algo = "sha256", .user_name = "test"};
    EXPECT_THROW((void)api.earnings_list(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, ExtraBonusList) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"otherProfits":[{"time":1607443200000,"coinName":"BTC","type":4,"profitAmount":0.0011859,"status":2}],"totalNum":3,"pageSize":20}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExtraBonusListParams params{.algo = "sha256", .user_name = "test"};
    const auto res = api.extra_bonus_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/payment/other");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, ExtraBonusListWithOptionalParams) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"otherProfits":[{"time":1607443200000,"coinName":"BTC","type":4,"profitAmount":0.0011859,"status":2}],"totalNum":3,"pageSize":20}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ExtraBonusListParams params{
        .algo = "sha256",
        .user_name = "test",
        .coin = "BTC",
        .start_date = 1770736694138,
        .end_date = 1770736694138,
        .page_index = 1,
        .page_size = 10,
        .recv_window = 5000,
    };
    const auto res = api.extra_bonus_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageIndex="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, ExtraBonusListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ExtraBonusListParams params{.algo = "sha256", .user_name = "test"};
    EXPECT_THROW((void)api.extra_bonus_list(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, HashrateResaleDetail) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"profitTransferDetails":[{"poolUsername":"test4001","toPoolUsername":"pop","algoName":"sha256","hashRate":200000000000,"day":20201213,"amount":0.2256872,"coinName":"BTC"}],"totalNum":8,"pageSize":200}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HashrateResaleDetailParams params{.config_id = 168};
    const auto res = api.hashrate_resale_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/hash-transfer/profit/details");
    EXPECT_NE((rec.query() + "&" + rec.body).find("configId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, HashrateResaleDetailWithOptionalParams) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"profitTransferDetails":[{"poolUsername":"test4001","toPoolUsername":"pop","algoName":"sha256","hashRate":200000000000,"day":20201213,"amount":0.2256872,"coinName":"BTC"}],"totalNum":8,"pageSize":200}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HashrateResaleDetailParams params{
        .config_id = 168,
        .page_index = 1,
        .page_size = 10,
        .recv_window = 5000,
    };
    const auto res = api.hashrate_resale_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("configId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageIndex="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, HashrateResaleDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const HashrateResaleDetailParams params{.config_id = 168};
    EXPECT_THROW((void)api.hashrate_resale_detail(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, HashrateResaleList) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"configDetails":[{"configId":168,"poolUsername":"123","toPoolUsername":"user1","algoName":"Ethash","hashRate":5000000,"startDay":20201210,"endDay":20210405,"status":1,"type":0}],"totalNum":21,"pageSize":200}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HashrateResaleListParams params{};
    const auto res = api.hashrate_resale_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/hash-transfer/config/details/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, HashrateResaleListWithOptionalParams) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"configDetails":[{"configId":168,"poolUsername":"123","toPoolUsername":"user1","algoName":"Ethash","hashRate":5000000,"startDay":20201210,"endDay":20210405,"status":1,"type":0}],"totalNum":21,"pageSize":200}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HashrateResaleListParams params{
        .page_index = 1,
        .page_size = 10,
        .recv_window = 5000,
    };
    const auto res = api.hashrate_resale_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageIndex="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, HashrateResaleListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const HashrateResaleListParams params{};
    EXPECT_THROW((void)api.hashrate_resale_list(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, HashrateResaleRequest) {
    const std::string example = R"json({"code":0,"msg":"","data":171})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HashrateResaleRequestParams params{.user_name = "test",
                                             .algo = "sha256",
                                             .end_date = 1770736694138,
                                             .start_date = 1770736694138,
                                             .to_pool_user = "S19pro",
                                             .hash_rate = 100000000};
    const auto res = api.hashrate_resale_request(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/hash-transfer/config");
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toPoolUser="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("hashRate="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, HashrateResaleRequestWithOptionalParams) {
    const std::string example = R"json({"code":0,"msg":"","data":171})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const HashrateResaleRequestParams params{
        .user_name = "test",
        .algo = "sha256",
        .end_date = 1770736694138,
        .start_date = 1770736694138,
        .to_pool_user = "S19pro",
        .hash_rate = 100000000,
        .recv_window = 5000,
    };
    const auto res = api.hashrate_resale_request(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toPoolUser="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("hashRate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, HashrateResaleRequestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const HashrateResaleRequestParams params{.user_name = "test",
                                             .algo = "sha256",
                                             .end_date = 1770736694138,
                                             .start_date = 1770736694138,
                                             .to_pool_user = "S19pro",
                                             .hash_rate = 100000000};
    EXPECT_THROW((void)api.hashrate_resale_request(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, MiningAccountEarning) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"accountProfits":[{"time":1607443200000,"coinName":"BTC","type":2,"puid":59985472,"subName":"vdvaghani","amount":0.09186957}],"totalNum":3,"pageSize":20}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MiningAccountEarningParams params{.algo = "sha256"};
    const auto res = api.mining_account_earning(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/payment/uid");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, MiningAccountEarningWithOptionalParams) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"accountProfits":[{"time":1607443200000,"coinName":"BTC","type":2,"puid":59985472,"subName":"vdvaghani","amount":0.09186957}],"totalNum":3,"pageSize":20}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const MiningAccountEarningParams params{
        .algo = "sha256",
        .start_date = 1770736694138,
        .end_date = 1770736694138,
        .page_index = 1,
        .page_size = 10,
        .recv_window = 5000,
    };
    const auto res = api.mining_account_earning(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageIndex="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageSize="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, MiningAccountEarningBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const MiningAccountEarningParams params{.algo = "sha256"};
    EXPECT_THROW((void)api.mining_account_earning(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, RequestForDetailMinerList) {
    const std::string example =
        R"json({"code":0,"msg":"","data":[{"workerName":"bhdc1.16A10404B","type":"H_hashrate","hashrateDatas":[{"time":1587902400000,"hashrate":"0","reject":0}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RequestForDetailMinerListParams params{
        .algo = "sha256", .user_name = "test", .worker_name = "bhdc1.16A10404B"};
    const auto res = api.request_for_detail_miner_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/worker/detail");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workerName="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, RequestForDetailMinerListWithOptionalParams) {
    const std::string example =
        R"json({"code":0,"msg":"","data":[{"workerName":"bhdc1.16A10404B","type":"H_hashrate","hashrateDatas":[{"time":1587902400000,"hashrate":"0","reject":0}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RequestForDetailMinerListParams params{
        .algo = "sha256",
        .user_name = "test",
        .worker_name = "bhdc1.16A10404B",
        .recv_window = 5000,
    };
    const auto res = api.request_for_detail_miner_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workerName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, RequestForDetailMinerListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RequestForDetailMinerListParams params{
        .algo = "sha256", .user_name = "test", .worker_name = "bhdc1.16A10404B"};
    EXPECT_THROW((void)api.request_for_detail_miner_list(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, RequestForMinerList) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"workerDatas":[{"workerId":"1420554439452400131","workerName":"2X73","status":3,"hashRate":0,"dayHashRate":1.269778129801366E13,"rejectRate":0,"lastShareTime":1587712919000}],"totalNum":18530,"pageSize":20}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RequestForMinerListParams params{.algo = "sha256", .user_name = "test"};
    const auto res = api.request_for_miner_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/worker/list");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, RequestForMinerListWithOptionalParams) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"workerDatas":[{"workerId":"1420554439452400131","workerName":"2X73","status":3,"hashRate":0,"dayHashRate":1.269778129801366E13,"rejectRate":0,"lastShareTime":1587712919000}],"totalNum":18530,"pageSize":20}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const RequestForMinerListParams params{
        .algo = "sha256",
        .user_name = "test",
        .page_index = 1,
        .sort = 0,
        .sort_column = 1,
        .worker_status = 0,
        .recv_window = 5000,
    };
    const auto res = api.request_for_miner_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pageIndex="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sort="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sortColumn="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("workerStatus="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, RequestForMinerListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const RequestForMinerListParams params{.algo = "sha256", .user_name = "test"};
    EXPECT_THROW((void)api.request_for_miner_list(params), common::BadRequestError);
}

TEST(RestApiDefaultApi, StatisticList) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"fifteenMinHashRate":"457835490067496409.00000000","dayHashRate":"214289268068874127.65000000","validNum":0,"invalidNum":17562,"profitToday":{"BTC":"0.00314332","BSV":"56.17055953","BCH":"106.61586001"},"profitYesterday":{"BTC":"0.00314332","BSV":"56.17055953","BCH":"106.61586001"},"userName":"test","unit":"h/s","algo":"sha256"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const StatisticListParams params{.algo = "sha256", .user_name = "test"};
    const auto res = api.statistic_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/mining/statistics/user/status");
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, StatisticListWithOptionalParams) {
    const std::string example =
        R"json({"code":0,"msg":"","data":{"fifteenMinHashRate":"457835490067496409.00000000","dayHashRate":"214289268068874127.65000000","validNum":0,"invalidNum":17562,"profitToday":{"BTC":"0.00314332","BSV":"56.17055953","BCH":"106.61586001"},"profitYesterday":{"BTC":"0.00314332","BSV":"56.17055953","BCH":"106.61586001"},"userName":"test","unit":"h/s","algo":"sha256"}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const StatisticListParams params{
        .algo = "sha256",
        .user_name = "test",
        .recv_window = 5000,
    };
    const auto res = api.statistic_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("algo="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("userName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, StatisticListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const StatisticListParams params{.algo = "sha256", .user_name = "test"};
    EXPECT_THROW((void)api.statistic_list(params), common::BadRequestError);
}
