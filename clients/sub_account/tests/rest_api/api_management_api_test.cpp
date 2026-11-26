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
#include <binance/sub_account/rest_api/api_management_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::sub_account::rest_api;
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

ApiManagementApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return ApiManagementApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiApiManagementApi, AddIpRestrictionForSubAccountApiKey) {
    const std::string example =
        R"json({"status":"2","ipList":["69.210.67.14"],"updateTime":1636371437000,"apiKey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AddIpRestrictionForSubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .status = 1};
    const auto res = api.add_ip_restriction_for_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v2/sub-account/subAccountApi/ipRestriction");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, AddIpRestrictionForSubAccountApiKeyWithOptionalParams) {
    const std::string example =
        R"json({"status":"2","ipList":["69.210.67.14"],"updateTime":1636371437000,"apiKey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AddIpRestrictionForSubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .status = 1,
        .ip_address = "69.210.67.14",
        .recv_window = 5000,
    };
    const auto res = api.add_ip_restriction_for_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("ipAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, AddIpRestrictionForSubAccountApiKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AddIpRestrictionForSubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .status = 1};
    EXPECT_THROW((void)api.add_ip_restriction_for_sub_account_api_key(params),
                 common::BadRequestError);
}

TEST(RestApiApiManagementApi, CreateSubAccountApiKey) {
    const std::string example =
        R"json({"apiName":"myKey","apiKey":"vmPUZE6mv9SD5VNHk4HlWFsOr6aKE2zvsw0MuIgwCIPy6utIco14y7Ju91duEh8A","secretKey":"NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j","canTrade":true,"canMarginLoanRepay":false,"canFuturesTrade":false,"canUniversalTransfer":false,"canVanillaOptions":false,"canFixApiTrading":true,"canFixApiReading":false,"status":2,"ipList":["69.210.67.14"]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateSubAccountApiKeyParams params{
        .email = "123@test.com", .api_name = "myKey", .status = 2};
    const auto res = api.create_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/subAccountApi");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, CreateSubAccountApiKeyWithOptionalParams) {
    const std::string example =
        R"json({"apiName":"myKey","apiKey":"vmPUZE6mv9SD5VNHk4HlWFsOr6aKE2zvsw0MuIgwCIPy6utIco14y7Ju91duEh8A","secretKey":"NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j","canTrade":true,"canMarginLoanRepay":false,"canFuturesTrade":false,"canUniversalTransfer":false,"canVanillaOptions":false,"canFixApiTrading":true,"canFixApiReading":false,"status":2,"ipList":["69.210.67.14"]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateSubAccountApiKeyParams params{
        .email = "123@test.com",
        .api_name = "myKey",
        .status = 2,
        .can_trade = true,
        .can_margin_loan_repay = false,
        .can_futures_trade = false,
        .can_universal_transfer = false,
        .can_vanilla_options = false,
        .can_fix_api_trading = true,
        .can_fix_api_reading = false,
        .ip_address = "69.210.67.14",
        .third_party_name = "thirdParty",
        .public_key = "string",
        .recv_window = 5000,
    };
    const auto res = api.create_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canTrade="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canMarginLoanRepay="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canFuturesTrade="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canUniversalTransfer="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canVanillaOptions="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canFixApiTrading="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canFixApiReading="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("ipAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("thirdPartyName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("publicKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, CreateSubAccountApiKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateSubAccountApiKeyParams params{
        .email = "123@test.com", .api_name = "myKey", .status = 2};
    EXPECT_THROW((void)api.create_sub_account_api_key(params), common::BadRequestError);
}

TEST(RestApiApiManagementApi, DeleteSubAccountApiKey) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteSubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"};
    const auto res = api.delete_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/subAccountApi");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, DeleteSubAccountApiKeyWithOptionalParams) {
    const std::string example = R"json()json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteSubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .recv_window = 5000,
    };
    const auto res = api.delete_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, DeleteSubAccountApiKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DeleteSubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"};
    EXPECT_THROW((void)api.delete_sub_account_api_key(params), common::BadRequestError);
}

TEST(RestApiApiManagementApi, QuerySubAccountApiKey) {
    const std::string example =
        R"json({"total":1,"rows":[{"email":"123@test.com","apiName":"myKey","apikey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf","canTrade":true,"canMarginLoanRepay":false,"canFuturesTrade":false,"canUniversalTransfer":false,"canVanillaOptions":false,"canFixApiTrading":true,"canFixApiReading":false,"timestamp":1640000000000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountApiKeyParams params{.email = "123@test.com"};
    const auto res = api.query_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/subAccountApi");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, QuerySubAccountApiKeyWithOptionalParams) {
    const std::string example =
        R"json({"total":1,"rows":[{"email":"123@test.com","apiName":"myKey","apikey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf","canTrade":true,"canMarginLoanRepay":false,"canFuturesTrade":false,"canUniversalTransfer":false,"canVanillaOptions":false,"canFixApiTrading":true,"canFixApiReading":false,"timestamp":1640000000000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QuerySubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .page = 1,
        .size = 30,
        .recv_window = 5000,
    };
    const auto res = api.query_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("page="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, QuerySubAccountApiKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QuerySubAccountApiKeyParams params{.email = "123@test.com"};
    EXPECT_THROW((void)api.query_sub_account_api_key(params), common::BadRequestError);
}

TEST(RestApiApiManagementApi, CreateSubAccountApiKeyV2) {
    const std::string example =
        R"json({"apiName":"myKey","apiKey":"vmPUZE6mv9SD5VNHk4HlWFsOr6aKE2zvsw0MuIgwCIPy6utIco14y7Ju91duEh8A","secretKey":"NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j","canTrade":true,"canMarginLoanRepay":false,"canFuturesTrade":false,"canUniversalTransfer":false,"canVanillaOptions":false,"canFixApiTrading":true,"canFixApiReading":false,"status":2,"ipList":["69.210.67.14"]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateSubAccountApiKeyV2Params params{
        .email = "123@test.com", .api_name = "my-fix-api", .status = 2};
    const auto res = api.create_sub_account_api_key_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v2/sub-account/subAccountApi");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, CreateSubAccountApiKeyV2WithOptionalParams) {
    const std::string example =
        R"json({"apiName":"myKey","apiKey":"vmPUZE6mv9SD5VNHk4HlWFsOr6aKE2zvsw0MuIgwCIPy6utIco14y7Ju91duEh8A","secretKey":"NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j","canTrade":true,"canMarginLoanRepay":false,"canFuturesTrade":false,"canUniversalTransfer":false,"canVanillaOptions":false,"canFixApiTrading":true,"canFixApiReading":false,"status":2,"ipList":["69.210.67.14"]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateSubAccountApiKeyV2Params params{
        .email = "123@test.com",
        .api_name = "my-fix-api",
        .status = 2,
        .can_trade = true,
        .can_margin_loan_repay = false,
        .can_futures_trade = false,
        .can_universal_transfer = false,
        .can_vanilla_options = false,
        .can_fix_api_trading = true,
        .can_fix_api_reading = true,
        .ip_address = "1.2.3.4",
        .third_party_name = "thirdParty",
        .public_key = "-----BEGIN PUBLIC "
                      "KEY-----\nMCowBQYDK2VwAyEAptEM59ao3nOD2baduIA830qZU4k4mqfvv7PwHVAfZhg=\n----"
                      "-END PUBLIC KEY-----",
        .recv_window = 5000,
    };
    const auto res = api.create_sub_account_api_key_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("apiName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canTrade="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canMarginLoanRepay="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canFuturesTrade="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canUniversalTransfer="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canVanillaOptions="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canFixApiTrading="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canFixApiReading="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("ipAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("thirdPartyName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("publicKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, CreateSubAccountApiKeyV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateSubAccountApiKeyV2Params params{
        .email = "123@test.com", .api_name = "my-fix-api", .status = 2};
    EXPECT_THROW((void)api.create_sub_account_api_key_v2(params), common::BadRequestError);
}

TEST(RestApiApiManagementApi, DeleteIpListForASubAccountApiKey) {
    const std::string example =
        R"json({"ipRestrict":"true","ipList":["69.210.67.14"],"updateTime":1636371437000,"apiKey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteIpListForASubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .ip_address = "69.210.67.14"};
    const auto res = api.delete_ip_list_for_a_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/subAccountApi/ipRestriction/ipList");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("ipAddress="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, DeleteIpListForASubAccountApiKeyWithOptionalParams) {
    const std::string example =
        R"json({"ipRestrict":"true","ipList":["69.210.67.14"],"updateTime":1636371437000,"apiKey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DeleteIpListForASubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .ip_address = "69.210.67.14",
        .recv_window = 5000,
    };
    const auto res = api.delete_ip_list_for_a_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "DELETE");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("ipAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, DeleteIpListForASubAccountApiKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DeleteIpListForASubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .ip_address = "69.210.67.14"};
    EXPECT_THROW((void)api.delete_ip_list_for_a_sub_account_api_key(params),
                 common::BadRequestError);
}

TEST(RestApiApiManagementApi, GetIpRestrictionForASubAccountApiKey) {
    const std::string example =
        R"json({"ipRestrict":"true","ipList":["69.210.67.14"],"updateTime":1636371437000,"apiKey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetIpRestrictionForASubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"};
    const auto res = api.get_ip_restriction_for_a_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/subAccountApi/ipRestriction");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, GetIpRestrictionForASubAccountApiKeyWithOptionalParams) {
    const std::string example =
        R"json({"ipRestrict":"true","ipList":["69.210.67.14"],"updateTime":1636371437000,"apiKey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetIpRestrictionForASubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .recv_window = 5000,
    };
    const auto res = api.get_ip_restriction_for_a_sub_account_api_key(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, GetIpRestrictionForASubAccountApiKeyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetIpRestrictionForASubAccountApiKeyParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"};
    EXPECT_THROW((void)api.get_ip_restriction_for_a_sub_account_api_key(params),
                 common::BadRequestError);
}

TEST(RestApiApiManagementApi, ModifySubAccountApiKeyPermission) {
    const std::string example =
        R"json({"apiName":"myKey","apikey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf","canTrade":true,"canMarginLoanRepay":false,"canFuturesTrade":true,"canUniversalTransfer":false,"canVanillaOptions":false,"canFixApiTrading":true,"canFixApiReading":false,"timestamp":1640000000000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifySubAccountApiKeyPermissionParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"};
    const auto res = api.modify_sub_account_api_key_permission(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/sub-account/subAccountApiPermission");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, ModifySubAccountApiKeyPermissionWithOptionalParams) {
    const std::string example =
        R"json({"apiName":"myKey","apikey":"k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf","canTrade":true,"canMarginLoanRepay":false,"canFuturesTrade":true,"canUniversalTransfer":false,"canVanillaOptions":false,"canFixApiTrading":true,"canFixApiReading":false,"timestamp":1640000000000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ModifySubAccountApiKeyPermissionParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
        .can_trade = true,
        .can_margin_loan_repay = false,
        .can_futures_trade = true,
        .can_universal_transfer = false,
        .can_vanilla_options = false,
        .can_fix_api_trading = true,
        .can_fix_api_reading = false,
        .recv_window = 5000,
    };
    const auto res = api.modify_sub_account_api_key_permission(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountApiKey="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canTrade="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canMarginLoanRepay="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canFuturesTrade="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canUniversalTransfer="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canVanillaOptions="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canFixApiTrading="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("canFixApiReading="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiApiManagementApi, ModifySubAccountApiKeyPermissionBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ModifySubAccountApiKeyPermissionParams params{
        .email = "123@test.com",
        .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf"};
    EXPECT_THROW((void)api.modify_sub_account_api_key_permission(params), common::BadRequestError);
}
