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
#include <binance/rebate/rest_api/api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::rebate::rest_api;
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

TEST(RestApiDefaultApi, GetSpotRebateHistoryRecords) {
    const std::string example =
        R"json({"status":"OK","type":"GENERAL","code":"000000000","data":{"page":1,"totalRecords":2,"totalPageNum":1,"data":[{"asset":"USDT","type":1,"amount":"0.0001126","updateTime":1637651320000}]}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSpotRebateHistoryRecordsParams params{};
    const auto res = api.get_spot_rebate_history_records(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/rebate/taxQuery");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetSpotRebateHistoryRecordsWithOptionalParams) {
    const std::string example =
        R"json({"status":"OK","type":"GENERAL","code":"000000000","data":{"page":1,"totalRecords":2,"totalPageNum":1,"data":[{"asset":"USDT","type":1,"amount":"0.0001126","updateTime":1637651320000}]}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSpotRebateHistoryRecordsParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .page = 1,
        .recv_window = 5000,
    };
    const auto res = api.get_spot_rebate_history_records(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiDefaultApi, GetSpotRebateHistoryRecordsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSpotRebateHistoryRecordsParams params{};
    EXPECT_THROW((void)api.get_spot_rebate_history_records(params), common::BadRequestError);
}
