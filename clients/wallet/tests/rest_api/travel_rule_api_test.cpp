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
#include <binance/wallet/rest_api/travel_rule_api.hpp>

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

TravelRuleApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return TravelRuleApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiTravelRuleApi, BrokerWithdraw) {
    const std::string example =
        R"json({"trId":123456,"accepted":true,"info":"Withdraw request accepted"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BrokerWithdrawParams params{.address = "address_example",
                                      .coin = "BTC",
                                      .amount = common::Decimal("1.0"),
                                      .withdraw_order_id = "1",
                                      .questionnaire = "questionnaire_example",
                                      .originator_pii = "originatorPii_example"};
    const auto res = api.broker_withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/broker/withdraw/apply");
    EXPECT_NE((rec.query() + "&" + rec.body).find("address="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("withdrawOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("questionnaire="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("originatorPii="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, BrokerWithdrawWithOptionalParams) {
    const std::string example =
        R"json({"trId":123456,"accepted":true,"info":"Withdraw request accepted"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const BrokerWithdrawParams params{
        .address = "address_example",
        .coin = "BTC",
        .amount = common::Decimal("1.0"),
        .withdraw_order_id = "1",
        .questionnaire = "questionnaire_example",
        .originator_pii = "originatorPii_example",
        .address_tag = "addressTag_example",
        .network = "network_example",
        .address_name = "addressName_example",
        .transaction_fee_flag = true,
        .wallet_type = 0,
    };
    const auto res = api.broker_withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("address="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("withdrawOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("questionnaire="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("originatorPii="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("addressTag="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("addressName="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transactionFeeFlag="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, BrokerWithdrawBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const BrokerWithdrawParams params{.address = "address_example",
                                      .coin = "BTC",
                                      .amount = common::Decimal("1.0"),
                                      .withdraw_order_id = "1",
                                      .questionnaire = "questionnaire_example",
                                      .originator_pii = "originatorPii_example"};
    EXPECT_THROW((void)api.broker_withdraw(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, CheckQuestionnaireRequirements) {
    const std::string example = R"json({"questionnaireCountryCode":"AE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CheckQuestionnaireRequirementsParams params{};
    const auto res = api.check_questionnaire_requirements(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/questionnaire-requirements");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, CheckQuestionnaireRequirementsWithOptionalParams) {
    const std::string example = R"json({"questionnaireCountryCode":"AE"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CheckQuestionnaireRequirementsParams params{
        .recv_window = 5000,
    };
    const auto res = api.check_questionnaire_requirements(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, CheckQuestionnaireRequirementsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CheckQuestionnaireRequirementsParams params{};
    EXPECT_THROW((void)api.check_questionnaire_requirements(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, DepositHistoryTravelRule) {
    const std::string example =
        R"json([{"trId":123451123,"tranId":17644346245865,"amount":"0.001","coin":"BNB","network":"BNB","depositStatus":0,"travelRuleStatus":1,"travelRuleStatusV2":"PENDING","address":"bnb136ns6lfw4zs5hg4n85vdthaad7hq5m4gtkgf23","addressTag":"101764890","txId":"98A3EA560C6B3336D348B6C83F0F95ECE4F1F5919E94BD006E5BF3BF264FACFC","insertTime":1661493146000,"completeTime":1661493206000,"transferType":0,"confirmTimes":"1/1","requireQuestionnaire":false,"questionnaire":"{\"question1\":\"answer1\",\"question2\":\"answer2\"}"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositHistoryTravelRuleParams params{};
    const auto res = api.deposit_history_travel_rule(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/deposit/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, DepositHistoryTravelRuleWithOptionalParams) {
    const std::string example =
        R"json([{"trId":123451123,"tranId":17644346245865,"amount":"0.001","coin":"BNB","network":"BNB","depositStatus":0,"travelRuleStatus":1,"travelRuleStatusV2":"PENDING","address":"bnb136ns6lfw4zs5hg4n85vdthaad7hq5m4gtkgf23","addressTag":"101764890","txId":"98A3EA560C6B3336D348B6C83F0F95ECE4F1F5919E94BD006E5BF3BF264FACFC","insertTime":1661493146000,"completeTime":1661493206000,"transferType":0,"confirmTimes":"1/1","requireQuestionnaire":false,"questionnaire":"{\"question1\":\"answer1\",\"question2\":\"answer2\"}"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositHistoryTravelRuleParams params{
        .tr_id = "1",
        .tx_id = "1",
        .tran_id = "1",
        .network = "network_example",
        .coin = "BTC",
        .travel_rule_status = 0,
        .pending_questionnaire = true,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .offset = 789,
        .limit = 1000,
    };
    const auto res = api.deposit_history_travel_rule(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("trId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tranId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("travelRuleStatus="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("pendingQuestionnaire="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, DepositHistoryTravelRuleBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DepositHistoryTravelRuleParams params{};
    EXPECT_THROW((void)api.deposit_history_travel_rule(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, DepositHistoryV2) {
    const std::string example =
        R"json([{"depositId":"4615328107052018945","amount":"0.01","network":"AVAXC","coin":"AVAX","depositStatus":1,"travelRuleReqStatus":0,"address":"0x0010627ab66d69232f4080d54e0f838b4dc3894a","addressTag":"","txId":"0xdde578983015741eed764e7ca10defb5a2caafdca3db5f92872d24a96beb1879","transferType":0,"confirmTimes":"12/12","requireQuestionnaire":false,"questionnaire":{"vaspName":"BINANCE","depositOriginator":0},"insertTime":1753053392000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositHistoryV2Params params{};
    const auto res = api.deposit_history_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/localentity/deposit/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, DepositHistoryV2WithOptionalParams) {
    const std::string example =
        R"json([{"depositId":"4615328107052018945","amount":"0.01","network":"AVAXC","coin":"AVAX","depositStatus":1,"travelRuleReqStatus":0,"address":"0x0010627ab66d69232f4080d54e0f838b4dc3894a","addressTag":"","txId":"0xdde578983015741eed764e7ca10defb5a2caafdca3db5f92872d24a96beb1879","transferType":0,"confirmTimes":"12/12","requireQuestionnaire":false,"questionnaire":{"vaspName":"BINANCE","depositOriginator":0},"insertTime":1753053392000}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DepositHistoryV2Params params{
        .deposit_id = 1,
        .tx_id = "1",
        .network = "network_example",
        .coin = "BTC",
        .retrieve_questionnaire = true,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .offset = 0,
        .limit = 1000,
    };
    const auto res = api.deposit_history_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("depositId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("retrieveQuestionnaire="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, DepositHistoryV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DepositHistoryV2Params params{};
    EXPECT_THROW((void)api.deposit_history_v2(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, FetchAddressVerificationList) {
    const std::string example =
        R"json([{"status":"PENDING","token":"AVAX","network":"AVAXC","walletAddress":"0xc03a6aa728a8dde7464c33828424ede7553a0021","addressQuestionnaire":{"sendTo":1,"satoshiToken":"AVAX","isAddressOwner":1,"verifyMethod":1}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FetchAddressVerificationListParams params{};
    const auto res = api.fetch_address_verification_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/addressVerify/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, FetchAddressVerificationListWithOptionalParams) {
    const std::string example =
        R"json([{"status":"PENDING","token":"AVAX","network":"AVAXC","walletAddress":"0xc03a6aa728a8dde7464c33828424ede7553a0021","addressQuestionnaire":{"sendTo":1,"satoshiToken":"AVAX","isAddressOwner":1,"verifyMethod":1}}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FetchAddressVerificationListParams params{
        .recv_window = 5000,
    };
    const auto res = api.fetch_address_verification_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, FetchAddressVerificationListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FetchAddressVerificationListParams params{};
    EXPECT_THROW((void)api.fetch_address_verification_list(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, GetCountryList) {
    const std::string example =
        R"json({"countries":[{"countryCode":"au","countryName":"Australia","blockType":"supported","depositAllowed":true,"withdrawalAllowed":true,"hasRegionRestrictions":false}],"lastUpdated":1716300000000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCountryListParams params{};
    const auto res = api.get_country_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/country/list");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, GetCountryListWithOptionalParams) {
    const std::string example =
        R"json({"countries":[{"countryCode":"au","countryName":"Australia","blockType":"supported","depositAllowed":true,"withdrawalAllowed":true,"hasRegionRestrictions":false}],"lastUpdated":1716300000000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCountryListParams params{
        .recv_window = 5000,
    };
    const auto res = api.get_country_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, GetCountryListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCountryListParams params{};
    EXPECT_THROW((void)api.get_country_list(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, GetRegionList) {
    const std::string example =
        R"json({"countryCode":"au","regions":[{"regionName":"New South Wales","blockType":"supported","depositAllowed":true,"withdrawalAllowed":true}],"lastUpdated":1716300000000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRegionListParams params{.country_code = "au"};
    const auto res = api.get_region_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/region/list");
    EXPECT_NE((rec.query() + "&" + rec.body).find("countryCode="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, GetRegionListWithOptionalParams) {
    const std::string example =
        R"json({"countryCode":"au","regions":[{"regionName":"New South Wales","blockType":"supported","depositAllowed":true,"withdrawalAllowed":true}],"lastUpdated":1716300000000})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetRegionListParams params{
        .country_code = "au",
        .recv_window = 5000,
    };
    const auto res = api.get_region_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("countryCode="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, GetRegionListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetRegionListParams params{.country_code = "au"};
    EXPECT_THROW((void)api.get_region_list(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, SubmitDepositQuestionnaire) {
    const std::string example =
        R"json({"trId":765127651,"accepted":true,"info":"Deposit questionnaire accepted."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubmitDepositQuestionnaireParams params{.sub_account_id = "1",
                                                  .deposit_id = 1,
                                                  .questionnaire = "questionnaire_example",
                                                  .beneficiary_pii = "beneficiaryPii_example"};
    const auto res = api.submit_deposit_questionnaire(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/broker/deposit/provide-info");
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("depositId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("questionnaire="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("beneficiaryPii="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, SubmitDepositQuestionnaireWithOptionalParams) {
    const std::string example =
        R"json({"trId":765127651,"accepted":true,"info":"Deposit questionnaire accepted."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubmitDepositQuestionnaireParams params{
        .sub_account_id = "1",
        .deposit_id = 1,
        .questionnaire = "questionnaire_example",
        .beneficiary_pii = "beneficiaryPii_example",
        .network = "network_example",
        .coin = "BTC",
        .amount = common::Decimal("1.0"),
        .address = "address_example",
        .address_tag = "addressTag_example",
    };
    const auto res = api.submit_deposit_questionnaire(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("subAccountId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("depositId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("questionnaire="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("beneficiaryPii="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("address="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("addressTag="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, SubmitDepositQuestionnaireBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubmitDepositQuestionnaireParams params{.sub_account_id = "1",
                                                  .deposit_id = 1,
                                                  .questionnaire = "questionnaire_example",
                                                  .beneficiary_pii = "beneficiaryPii_example"};
    EXPECT_THROW((void)api.submit_deposit_questionnaire(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, SubmitDepositQuestionnaireTravelRule) {
    const std::string example =
        R"json({"trId":765127651,"accepted":true,"info":"Deposit questionnaire accepted."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubmitDepositQuestionnaireTravelRuleParams params{
        .tran_id = 1, .questionnaire = "questionnaire_example"};
    const auto res = api.submit_deposit_questionnaire_travel_rule(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/deposit/provide-info");
    EXPECT_NE((rec.query() + "&" + rec.body).find("tranId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("questionnaire="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, SubmitDepositQuestionnaireTravelRuleBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubmitDepositQuestionnaireTravelRuleParams params{
        .tran_id = 1, .questionnaire = "questionnaire_example"};
    EXPECT_THROW((void)api.submit_deposit_questionnaire_travel_rule(params),
                 common::BadRequestError);
}

TEST(RestApiTravelRuleApi, SubmitDepositQuestionnaireV2) {
    const std::string example =
        R"json({"trId":765127651,"accepted":true,"info":"Deposit questionnaire accepted."})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const SubmitDepositQuestionnaireV2Params params{.deposit_id = 1,
                                                    .questionnaire = "questionnaire_example"};
    const auto res = api.submit_deposit_questionnaire_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "PUT");
    EXPECT_EQ(rec.path(), "/sapi/v2/localentity/deposit/provide-info");
    EXPECT_NE((rec.query() + "&" + rec.body).find("depositId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("questionnaire="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, SubmitDepositQuestionnaireV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const SubmitDepositQuestionnaireV2Params params{.deposit_id = 1,
                                                    .questionnaire = "questionnaire_example"};
    EXPECT_THROW((void)api.submit_deposit_questionnaire_v2(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, VaspList) {
    const std::string example =
        R"json([{"vaspName":"Binance","vaspCode":"BINANCE","identifier":"xxx"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VaspListParams params{};
    const auto res = api.vasp_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/vasp");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, VaspListWithOptionalParams) {
    const std::string example =
        R"json([{"vaspName":"Binance","vaspCode":"BINANCE","identifier":"xxx"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const VaspListParams params{
        .recv_window = 5000,
    };
    const auto res = api.vasp_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, VaspListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const VaspListParams params{};
    EXPECT_THROW((void)api.vasp_list(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, WithdrawHistoryV1) {
    const std::string example =
        R"json([{"id":"b6ae22b3aa844210a7041aee7589627c","trId":1234456,"amount":"8.91000000","transactionFee":"0.004","coin":"USDT","withdrawalStatus":6,"travelRuleStatus":0,"address":"0x94df8b352de7f46f64b01d3666bf6e936e44ce60","txId":"0xb5ef8c13b968a406cc62a93a8bd80f9e9a906ef1b3fcf20a2e48573c17659268","applyTime":"2019-10-12 11:12:02","network":"ETH","transferType":0,"withdrawOrderId":"WITHDRAWtest123","info":"The address is not valid. Please confirm with the recipient","confirmNo":3,"walletType":1,"txKey":"","questionnaire":"{\"question1\":\"answer1\",\"question2\":\"answer2\"}","completeTime":"2023-03-23 16:52:41"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawHistoryV1Params params{};
    const auto res = api.withdraw_history_v1(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/withdraw/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, WithdrawHistoryV1WithOptionalParams) {
    const std::string example =
        R"json([{"id":"b6ae22b3aa844210a7041aee7589627c","trId":1234456,"amount":"8.91000000","transactionFee":"0.004","coin":"USDT","withdrawalStatus":6,"travelRuleStatus":0,"address":"0x94df8b352de7f46f64b01d3666bf6e936e44ce60","txId":"0xb5ef8c13b968a406cc62a93a8bd80f9e9a906ef1b3fcf20a2e48573c17659268","applyTime":"2019-10-12 11:12:02","network":"ETH","transferType":0,"withdrawOrderId":"WITHDRAWtest123","info":"The address is not valid. Please confirm with the recipient","confirmNo":3,"walletType":1,"txKey":"","questionnaire":"{\"question1\":\"answer1\",\"question2\":\"answer2\"}","completeTime":"2023-03-23 16:52:41"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawHistoryV1Params params{
        .tr_id = "1",
        .tx_id = "1",
        .withdraw_order_id = "1",
        .network = "network_example",
        .coin = "BTC",
        .travel_rule_status = 0,
        .offset = 0,
        .limit = 1000,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.withdraw_history_v1(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("trId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("withdrawOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("travelRuleStatus="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, WithdrawHistoryV1BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const WithdrawHistoryV1Params params{};
    EXPECT_THROW((void)api.withdraw_history_v1(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, WithdrawHistoryV2) {
    const std::string example =
        R"json([{"id":"b6ae22b3aa844210a7041aee7589627c","trId":1234456,"amount":"8.91000000","transactionFee":"0.004","coin":"USDT","withdrawalStatus":6,"travelRuleStatus":0,"address":"0x94df8b352de7f46f64b01d3666bf6e936e44ce60","txId":"0xb5ef8c13b968a406cc62a93a8bd80f9e9a906ef1b3fcf20a2e48573c17659268","applyTime":"2019-10-12 11:12:02","network":"ETH","transferType":0,"withdrawOrderId":"WITHDRAWtest123","info":"The address is not valid. Please confirm with the recipient","confirmNo":3,"walletType":1,"txKey":"","questionnaire":"{\"question1\":\"answer1\",\"question2\":\"answer2\"}","completeTime":"2023-03-23 16:52:41"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawHistoryV2Params params{};
    const auto res = api.withdraw_history_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v2/localentity/withdraw/history");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, WithdrawHistoryV2WithOptionalParams) {
    const std::string example =
        R"json([{"id":"b6ae22b3aa844210a7041aee7589627c","trId":1234456,"amount":"8.91000000","transactionFee":"0.004","coin":"USDT","withdrawalStatus":6,"travelRuleStatus":0,"address":"0x94df8b352de7f46f64b01d3666bf6e936e44ce60","txId":"0xb5ef8c13b968a406cc62a93a8bd80f9e9a906ef1b3fcf20a2e48573c17659268","applyTime":"2019-10-12 11:12:02","network":"ETH","transferType":0,"withdrawOrderId":"WITHDRAWtest123","info":"The address is not valid. Please confirm with the recipient","confirmNo":3,"walletType":1,"txKey":"","questionnaire":"{\"question1\":\"answer1\",\"question2\":\"answer2\"}","completeTime":"2023-03-23 16:52:41"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawHistoryV2Params params{
        .tr_id = "1",
        .tx_id = "1",
        .withdraw_order_id = "1",
        .network = "network_example",
        .coin = "coin_example",
        .travel_rule_status = 0,
        .offset = 0,
        .limit = 1000,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.withdraw_history_v2(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("trId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("txId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("withdrawOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("travelRuleStatus="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, WithdrawHistoryV2BadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const WithdrawHistoryV2Params params{};
    EXPECT_THROW((void)api.withdraw_history_v2(params), common::BadRequestError);
}

TEST(RestApiTravelRuleApi, WithdrawTravelRule) {
    const std::string example =
        R"json({"trId":123456,"accepted":true,"info":"Withdraw request accepted"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawTravelRuleParams params{.coin = "BTC",
                                          .address = "address_example",
                                          .amount = common::Decimal("1.0"),
                                          .questionnaire = "questionnaire_example"};
    const auto res = api.withdraw_travel_rule(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/localentity/withdraw/apply");
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("address="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("questionnaire="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTravelRuleApi, WithdrawTravelRuleWithOptionalParams) {
    const std::string example =
        R"json({"trId":123456,"accepted":true,"info":"Withdraw request accepted"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const WithdrawTravelRuleParams params{
        .coin = "BTC",
        .address = "address_example",
        .amount = common::Decimal("1.0"),
        .questionnaire = "questionnaire_example",
        .withdraw_order_id = "1",
        .network = "network_example",
        .address_tag = "addressTag_example",
        .transaction_fee_flag = true,
        .name = "name_example",
        .wallet_type = 0,
        .recv_window = 5000,
    };
    const auto res = api.withdraw_travel_rule(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("address="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("questionnaire="), std::string::npos);
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

TEST(RestApiTravelRuleApi, WithdrawTravelRuleBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const WithdrawTravelRuleParams params{.coin = "BTC",
                                          .address = "address_example",
                                          .amount = common::Decimal("1.0"),
                                          .questionnaire = "questionnaire_example"};
    EXPECT_THROW((void)api.withdraw_travel_rule(params), common::BadRequestError);
}
