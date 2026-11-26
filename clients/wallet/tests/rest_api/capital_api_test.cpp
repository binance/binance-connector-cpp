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
#include <binance/wallet/rest_api/capital_api.hpp>

#include "support/mock_server.hpp"

using namespace binance;
using namespace binance::wallet::rest_api;
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

CapitalApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return CapitalApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiCapitalApi, AllCoinsInformation) {
    const std::string example =
        R"json([{"coin":"1MBABYDOGE","depositAllEnable":true,"withdrawAllEnable":true,"name":"1M x BABYDOGE","free":"34941.1","locked":"0","freeze":"0","withdrawing":"0","ipoing":"0","ipoable":"0","storage":"0","isLegalMoney":false,"trading":true,"networkList":[{"network":"BSC","coin":"1MBABYDOGE","withdrawIntegerMultiple":"0.01","isDefault":false,"depositEnable":true,"withdrawEnable":true,"depositDesc":"","withdrawDesc":"","specialTips":"","specialWithdrawTips":"","name":"BNB Smart Chain (BEP20)","resetAddressStatus":false,"addressRegex":"^(0x)[0-9A-Fa-f]{40}$","memoRegex":"","withdrawFee":"10","withdrawMin":"20","withdrawMax":"9999999999","withdrawInternalMin":"0.01","depositDust":"0.01","minConfirm":5,"unLockConfirm":0,"sameAddress":false,"withdrawTag":false,"estimatedArrivalTime":1,"busy":false,"contractAddressUrl":"https://bscscan.com/token/","contractAddress":"0xc748673057861a797275cd8a068abb95a902e8de","denomination":1000000}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllCoinsInformationParams params{};
    const auto res = api.all_coins_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/config/getall");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, AllCoinsInformationWithOptionalParams) {
    const std::string example =
        R"json([{"coin":"1MBABYDOGE","depositAllEnable":true,"withdrawAllEnable":true,"name":"1M x BABYDOGE","free":"34941.1","locked":"0","freeze":"0","withdrawing":"0","ipoing":"0","ipoable":"0","storage":"0","isLegalMoney":false,"trading":true,"networkList":[{"network":"BSC","coin":"1MBABYDOGE","withdrawIntegerMultiple":"0.01","isDefault":false,"depositEnable":true,"withdrawEnable":true,"depositDesc":"","withdrawDesc":"","specialTips":"","specialWithdrawTips":"","name":"BNB Smart Chain (BEP20)","resetAddressStatus":false,"addressRegex":"^(0x)[0-9A-Fa-f]{40}$","memoRegex":"","withdrawFee":"10","withdrawMin":"20","withdrawMax":"9999999999","withdrawInternalMin":"0.01","depositDust":"0.01","minConfirm":5,"unLockConfirm":0,"sameAddress":false,"withdrawTag":false,"estimatedArrivalTime":1,"busy":false,"contractAddressUrl":"https://bscscan.com/token/","contractAddress":"0xc748673057861a797275cd8a068abb95a902e8de","denomination":1000000}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AllCoinsInformationParams params{
        .recv_window = 5000,
    };
    const auto res = api.all_coins_information(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, AllCoinsInformationBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AllCoinsInformationParams params{};
    EXPECT_THROW((void)api.all_coins_information(params), common::BadRequestError);
}

TEST(RestApiCapitalApi, DepositAddress) {
    const std::string example =
        R"json({"address":"1HPn8Rx2y6nNSfagQBKy27GB99Vbzg89wv","coin":"BTC","tag":"","url":"https://btc.com/1HPn8Rx2y6nNSfagQBKy27GB99Vbzg89wv"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositAddressParams params{.coin = "BTC"};
    const auto res = api.deposit_address(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/deposit/address");
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, DepositAddressWithOptionalParams) {
    const std::string example =
        R"json({"address":"1HPn8Rx2y6nNSfagQBKy27GB99Vbzg89wv","coin":"BTC","tag":"","url":"https://btc.com/1HPn8Rx2y6nNSfagQBKy27GB99Vbzg89wv"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositAddressParams params{
        .coin = "BTC",
        .network = "network_example",
        .amount = common::Decimal("1.0"),
        .recv_window = 5000,
    };
    const auto res = api.deposit_address(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, DepositAddressBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DepositAddressParams params{.coin = "BTC"};
    EXPECT_THROW((void)api.deposit_address(params), common::BadRequestError);
}

TEST(RestApiCapitalApi, DepositHistory) {
    const std::string example =
        R"json([{"id":"769800519366885376","amount":"0.001","coin":"BNB","network":"BNB","status":1,"address":"bnb136ns6lfw4zs5hg4n85vdthaad7hq5m4gtkgf23","addressTag":"101764890","txId":"98A3EA560C6B3336D348B6C83F0F95ECE4F1F5919E94BD006E5BF3BF264FACFC","insertTime":1661493146000,"completeTime":1661493146000,"transferType":0,"confirmTimes":"1/1","unlockConfirm":0,"walletType":0,"travelRuleStatus":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositHistoryParams params{};
    const auto res = api.deposit_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/deposit/hisrec");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, DepositHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"id":"769800519366885376","amount":"0.001","coin":"BNB","network":"BNB","status":1,"address":"bnb136ns6lfw4zs5hg4n85vdthaad7hq5m4gtkgf23","addressTag":"101764890","txId":"98A3EA560C6B3336D348B6C83F0F95ECE4F1F5919E94BD006E5BF3BF264FACFC","insertTime":1661493146000,"completeTime":1661493146000,"transferType":0,"confirmTimes":"1/1","unlockConfirm":0,"walletType":0,"travelRuleStatus":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositHistoryParams params{
        .include_source = false,
        .coin = "BTC",
        .status = DepositHistoryStatusEnum::Status0,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .offset = 0,
        .limit = 1000,
        .recv_window = 5000,
        .tx_id = "1",
    };
    const auto res = api.deposit_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("includeSource="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, DepositHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DepositHistoryParams params{};
    EXPECT_THROW((void)api.deposit_history(params), common::BadRequestError);
}

TEST(RestApiCapitalApi, FetchDepositAddressListWithNetwork) {
    const std::string example =
        R"json([{"coin":"ETH","address":"0xD316E95Fd9E8E237Cb11f8200Babbc5D8D177BA4","tag":"","isDefault":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FetchDepositAddressListWithNetworkParams params{.coin = "BTC"};
    const auto res = api.fetch_deposit_address_list_with_network(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/deposit/address/list");
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, FetchDepositAddressListWithNetworkWithOptionalParams) {
    const std::string example =
        R"json([{"coin":"ETH","address":"0xD316E95Fd9E8E237Cb11f8200Babbc5D8D177BA4","tag":"","isDefault":0}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FetchDepositAddressListWithNetworkParams params{
        .coin = "BTC",
        .network = "network_example",
    };
    const auto res = api.fetch_deposit_address_list_with_network(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, FetchDepositAddressListWithNetworkBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FetchDepositAddressListWithNetworkParams params{.coin = "BTC"};
    EXPECT_THROW((void)api.fetch_deposit_address_list_with_network(params),
                 common::BadRequestError);
}

TEST(RestApiCapitalApi, FetchWithdrawAddressList) {
    const std::string example =
        R"json([{"address":"1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa","addressTag":"","coin":"BTC","name":"Satoshi","network":"BTC","origin":"bla","originType":"others","whiteStatus":true}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.fetch_withdraw_address_list();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/withdraw/address/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, FetchWithdrawAddressListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.fetch_withdraw_address_list(), common::BadRequestError);
}

TEST(RestApiCapitalApi, FetchWithdrawQuota) {
    const std::string example = R"json({"wdQuota":"10000","usedWdQuota":"1000"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.fetch_withdraw_quota();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/withdraw/quota");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, FetchWithdrawQuotaBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.fetch_withdraw_quota(), common::BadRequestError);
}

TEST(RestApiCapitalApi, OneClickArrivalDepositApply) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":true,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OneClickArrivalDepositApplyParams params{};
    const auto res = api.one_click_arrival_deposit_apply(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/deposit/credit-apply");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, OneClickArrivalDepositApplyWithOptionalParams) {
    const std::string example =
        R"json({"code":"000000","message":"success","data":true,"success":true})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const OneClickArrivalDepositApplyParams params{
        .deposit_id = 1,
        .tx_id = "1",
        .sub_account_id = "1",
        .sub_user_id = 1,
    };
    const auto res = api.one_click_arrival_deposit_apply(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("depositId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subUserId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, OneClickArrivalDepositApplyBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const OneClickArrivalDepositApplyParams params{};
    EXPECT_THROW((void)api.one_click_arrival_deposit_apply(params), common::BadRequestError);
}

TEST(RestApiCapitalApi, Withdraw) {
    const std::string example = R"json({"id":"7213fea8e94b4a5593d507237e5a555b"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawParams params{
        .coin = "BTC", .address = "address_example", .amount = common::Decimal("1.0")};
    const auto res = api.withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/withdraw/apply");
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("address="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, WithdrawWithOptionalParams) {
    const std::string example = R"json({"id":"7213fea8e94b4a5593d507237e5a555b"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawParams params{
        .coin = "BTC",
        .address = "address_example",
        .amount = common::Decimal("1.0"),
        .withdraw_order_id = "1",
        .network = "network_example",
        .address_tag = "addressTag_example",
        .transaction_fee_flag = true,
        .name = "name_example",
        .wallet_type = 0,
        .recv_window = 5000,
    };
    const auto res = api.withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("address="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("withdrawOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("addressTag="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transactionFeeFlag="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("name="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, WithdrawBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const WithdrawParams params{
        .coin = "BTC", .address = "address_example", .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.withdraw(params), common::BadRequestError);
}

TEST(RestApiCapitalApi, WithdrawHistory) {
    const std::string example =
        R"json([{"id":"b6ae22b3aa844210a7041aee7589627c","amount":"8.91000000","transactionFee":"0.004","coin":"USDT","status":6,"address":"0x94df8b352de7f46f64b01d3666bf6e936e44ce60","txId":"0xb5ef8c13b968a406cc62a93a8bd80f9e9a906ef1b3fcf20a2e48573c17659268","applyTime":"2019-10-12 11:12:02","network":"ETH","transferType":0,"withdrawOrderId":"WITHDRAWtest123","info":"The address is not valid. Please confirm with the recipient","confirmNo":3,"walletType":1,"txKey":"","completeTime":"2023-03-23 16:52:41"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawHistoryParams params{};
    const auto res = api.withdraw_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/capital/withdraw/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, WithdrawHistoryWithOptionalParams) {
    const std::string example =
        R"json([{"id":"b6ae22b3aa844210a7041aee7589627c","amount":"8.91000000","transactionFee":"0.004","coin":"USDT","status":6,"address":"0x94df8b352de7f46f64b01d3666bf6e936e44ce60","txId":"0xb5ef8c13b968a406cc62a93a8bd80f9e9a906ef1b3fcf20a2e48573c17659268","applyTime":"2019-10-12 11:12:02","network":"ETH","transferType":0,"withdrawOrderId":"WITHDRAWtest123","info":"The address is not valid. Please confirm with the recipient","confirmNo":3,"walletType":1,"txKey":"","completeTime":"2023-03-23 16:52:41"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawHistoryParams params{
        .coin = "BTC",
        .withdraw_order_id = "1",
        .status = 0,
        .offset = 0,
        .limit = 1000,
        .id_list = "idList_example",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.withdraw_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("withdrawOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("status="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("idList="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiCapitalApi, WithdrawHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const WithdrawHistoryParams params{};
    EXPECT_THROW((void)api.withdraw_history(params), common::BadRequestError);
}
