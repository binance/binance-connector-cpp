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
#include <binance/w3w_prediction/rest_api/transfer_api.hpp>

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

TransferApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return TransferApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiTransferApi, ApplyMmDeposit) {
    const std::string example =
        R"json({"transferId":"26080400000000454343","status":"PROCESSING"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ApplyMmDepositParams params{.from_token = "USDT",
                                      .from_token_amount = "1000000000000000000",
                                      .to_token = "USDT",
                                      .account_type = ApplyMmDepositAccountTypeEnum::Spot};
    const auto res = api.apply_mm_deposit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/deposit/apply");
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromTokenAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, ApplyMmDepositWithOptionalParams) {
    const std::string example =
        R"json({"transferId":"26080400000000454343","status":"PROCESSING"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ApplyMmDepositParams params{
        .from_token = "USDT",
        .from_token_amount = "1000000000000000000",
        .to_token = "USDT",
        .account_type = ApplyMmDepositAccountTypeEnum::Spot,
        .chain_id = "56",
    };
    const auto res = api.apply_mm_deposit(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromTokenAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("chainId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, ApplyMmDepositBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ApplyMmDepositParams params{.from_token = "USDT",
                                      .from_token_amount = "1000000000000000000",
                                      .to_token = "USDT",
                                      .account_type = ApplyMmDepositAccountTypeEnum::Spot};
    EXPECT_THROW((void)api.apply_mm_deposit(params), common::BadRequestError);
}

TEST(RestApiTransferApi, ApplyMmWithdraw) {
    const std::string example =
        R"json({"id":"123456789","walletId":"0ecd3be8e3674b54b1258e24f9c3706b","walletAddress":"0x2ac3a1fb164da5c4e76f67ae6dbe6be821c000c8","transferId":"26080400000000454344"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ApplyMmWithdrawParams params{.coin = "USDT", .network = "BEP20", .amount = "100.00"};
    const auto res = api.apply_mm_withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/withdraw/apply");
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, ApplyMmWithdrawWithOptionalParams) {
    const std::string example =
        R"json({"id":"123456789","walletId":"0ecd3be8e3674b54b1258e24f9c3706b","walletAddress":"0x2ac3a1fb164da5c4e76f67ae6dbe6be821c000c8","transferId":"26080400000000454344"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ApplyMmWithdrawParams params{
        .coin = "USDT",
        .network = "BEP20",
        .amount = "100.00",
        .withdraw_order_id = "wd_20260814_001",
        .wallet_type = ApplyMmWithdrawWalletTypeEnum::WalletType0,
        .name = "MM withdraw",
    };
    const auto res = api.apply_mm_withdraw(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("coin="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("network="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("withdrawOrderId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("name="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, ApplyMmWithdrawBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ApplyMmWithdrawParams params{.coin = "USDT", .network = "BEP20", .amount = "100.00"};
    EXPECT_THROW((void)api.apply_mm_withdraw(params), common::BadRequestError);
}

TEST(RestApiTransferApi, CreateInboundTransfer) {
    const std::string example =
        R"json({"transferId":"tf_20260525_in_001","status":"PROCESSING"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateInboundTransferParams params{
        .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .from_token_amount = "1000000000000000000",
        .account_type = CreateInboundTransferAccountTypeEnum::Spot};
    const auto res = api.create_inbound_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/transfer/inbound");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromTokenAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, CreateInboundTransferWithOptionalParams) {
    const std::string example =
        R"json({"transferId":"tf_20260525_in_001","status":"PROCESSING"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateInboundTransferParams params{
        .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .from_token_amount = "1000000000000000000",
        .account_type = CreateInboundTransferAccountTypeEnum::Spot,
        .from_token = "USDT",
        .to_token = "USDT",
        .chain_id = "56",
    };
    const auto res = api.create_inbound_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromTokenAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("chainId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, CreateInboundTransferBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateInboundTransferParams params{
        .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .from_token_amount = "1000000000000000000",
        .account_type = CreateInboundTransferAccountTypeEnum::Spot};
    EXPECT_THROW((void)api.create_inbound_transfer(params), common::BadRequestError);
}

TEST(RestApiTransferApi, CreateOutboundTransfer) {
    const std::string example =
        R"json({"transferId":"tf_20260525_out_001","status":"PROCESSING"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateOutboundTransferParams params{
        .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .from_token_amount = "1000000000000000000",
        .account_type = CreateOutboundTransferAccountTypeEnum::Spot,
        .source_biz = CreateOutboundTransferSourceBizEnum::UserTransfer};
    const auto res = api.create_outbound_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/transfer/outbound");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromTokenAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sourceBiz="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, CreateOutboundTransferWithOptionalParams) {
    const std::string example =
        R"json({"transferId":"tf_20260525_out_001","status":"PROCESSING"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const CreateOutboundTransferParams params{
        .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .from_token_amount = "1000000000000000000",
        .account_type = CreateOutboundTransferAccountTypeEnum::Spot,
        .source_biz = CreateOutboundTransferSourceBizEnum::UserTransfer,
        .from_token = "USDT",
        .to_token = "USDT",
        .chain_id = "56",
    };
    const auto res = api.create_outbound_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromTokenAmount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("sourceBiz="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toToken="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("chainId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, CreateOutboundTransferBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const CreateOutboundTransferParams params{
        .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20",
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .from_token_amount = "1000000000000000000",
        .account_type = CreateOutboundTransferAccountTypeEnum::Spot,
        .source_biz = CreateOutboundTransferSourceBizEnum::UserTransfer};
    EXPECT_THROW((void)api.create_outbound_transfer(params), common::BadRequestError);
}

TEST(RestApiTransferApi, QueryTransferList) {
    const std::string example =
        R"json({"transfers":[{"transferId":"tf_20260525_out_001","direction":"OUTBOUND","status":"SUCCESS","walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","fromToken":"USDT","fromTokenAmount":"100.00","toToken":"USDT","toTokenAmount":"100.00","errorCode":"errorCode","errorMessage":"errorMessage","createTime":"2026-05-25T04:00:00.000+00:00","updateTime":"2026-05-25T04:00:05.000+00:00","completeAt":"2026-05-25T04:00:05.000+00:00"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryTransferListParams params{.wallet_address =
                                             "0x12e32db8817e292508c34111cbc4b23340df542c",
                                         .start_date = "2026-05-01",
                                         .end_date = "2026-05-25"};
    const auto res = api.query_transfer_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/transfer/list");
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endDate="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, QueryTransferListWithOptionalParams) {
    const std::string example =
        R"json({"transfers":[{"transferId":"tf_20260525_out_001","direction":"OUTBOUND","status":"SUCCESS","walletAddress":"0x12e32db8817e292508c34111cbc4b23340df542c","fromToken":"USDT","fromTokenAmount":"100.00","toToken":"USDT","toTokenAmount":"100.00","errorCode":"errorCode","errorMessage":"errorMessage","createTime":"2026-05-25T04:00:00.000+00:00","updateTime":"2026-05-25T04:00:05.000+00:00","completeAt":"2026-05-25T04:00:05.000+00:00"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryTransferListParams params{
        .wallet_address = "0x12e32db8817e292508c34111cbc4b23340df542c",
        .start_date = "2026-05-01",
        .end_date = "2026-05-25",
        .token_symbol = "USDT",
        .direction = QueryTransferListDirectionEnum::Inbound,
        .offset = 0,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.query_transfer_list(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("walletAddress="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endDate="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tokenSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("direction="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("offset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, QueryTransferListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryTransferListParams params{.wallet_address =
                                             "0x12e32db8817e292508c34111cbc4b23340df542c",
                                         .start_date = "2026-05-01",
                                         .end_date = "2026-05-25"};
    EXPECT_THROW((void)api.query_transfer_list(params), common::BadRequestError);
}

TEST(RestApiTransferApi, QueryTransferStatus) {
    const std::string example =
        R"json({"transferId":"tf_20260525_out_001","direction":"OUTBOUND","status":"COMPLETED","fromToken":"USDT","fromTokenAmount":"100.00","toToken":"USDT","toTokenAmount":"100.00","errorCode":"errorCode","errorMessage":"errorMessage","createTime":"2026-05-25T04:00:00.000+00:00","updateTime":"2026-05-25T04:00:05.000+00:00"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryTransferStatusParams params{.transfer_id = "tf_20260525_out_001"};
    const auto res = api.query_transfer_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/w3w/wallet/prediction/transfer/status");
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferId="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, QueryTransferStatusWithOptionalParams) {
    const std::string example =
        R"json({"transferId":"tf_20260525_out_001","direction":"OUTBOUND","status":"COMPLETED","fromToken":"USDT","fromTokenAmount":"100.00","toToken":"USDT","toTokenAmount":"100.00","errorCode":"errorCode","errorMessage":"errorMessage","createTime":"2026-05-25T04:00:00.000+00:00","updateTime":"2026-05-25T04:00:05.000+00:00"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryTransferStatusParams params{
        .transfer_id = "tf_20260525_out_001",
        .recv_window = 5000,
    };
    const auto res = api.query_transfer_status(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("transferId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiTransferApi, QueryTransferStatusBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryTransferStatusParams params{.transfer_id = "tf_20260525_out_001"};
    EXPECT_THROW((void)api.query_transfer_status(params), common::BadRequestError);
}
