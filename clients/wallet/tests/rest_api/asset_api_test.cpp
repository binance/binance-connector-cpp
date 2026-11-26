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
#include <binance/wallet/rest_api/asset_api.hpp>

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

AssetApi api_for(const MockServer& server) {
    common::RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.api_key = "key";
    cfg.api_secret = "secret";
    return AssetApi(std::make_shared<common::RestClient>(std::move(cfg)));
}

constexpr const char* kBadRequest = R"({"code":-1102,"msg":"Mandatory parameter was not sent."})";

} // namespace

TEST(RestApiAssetApi, AssetDetail) {
    const std::string example =
        R"json({"CTR":{"minWithdrawAmount":"70.00000000","depositStatus":false,"withdrawFee":35,"withdrawStatus":true,"depositTip":"Delisted, Deposit Suspended"},"SKY":{"minWithdrawAmount":"0.02000000","depositStatus":true,"withdrawFee":0.01,"withdrawStatus":true}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AssetDetailParams params{};
    const auto res = api.asset_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/assetDetail");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, AssetDetailWithOptionalParams) {
    const std::string example =
        R"json({"CTR":{"minWithdrawAmount":"70.00000000","depositStatus":false,"withdrawFee":35,"withdrawStatus":true,"depositTip":"Delisted, Deposit Suspended"},"SKY":{"minWithdrawAmount":"0.02000000","depositStatus":true,"withdrawFee":0.01,"withdrawStatus":true}})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AssetDetailParams params{
        .asset = "BTC",
        .recv_window = 5000,
    };
    const auto res = api.asset_detail(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, AssetDetailBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AssetDetailParams params{};
    EXPECT_THROW((void)api.asset_detail(params), common::BadRequestError);
}

TEST(RestApiAssetApi, AssetDividendRecord) {
    const std::string example =
        R"json({"rows":[{"id":1637366104,"amount":"10.00000000","asset":"BHFT","divTime":1563189166000,"enInfo":"BHFT distribution","tranId":2968885920,"direction":1}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AssetDividendRecordParams params{};
    const auto res = api.asset_dividend_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/assetDividend");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, AssetDividendRecordWithOptionalParams) {
    const std::string example =
        R"json({"rows":[{"id":1637366104,"amount":"10.00000000","asset":"BHFT","divTime":1563189166000,"enInfo":"BHFT distribution","tranId":2968885920,"direction":1}],"total":2})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const AssetDividendRecordParams params{
        .asset = "BTC",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .limit = 20,
        .recv_window = 5000,
    };
    const auto res = api.asset_dividend_record(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("limit="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, AssetDividendRecordBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const AssetDividendRecordParams params{};
    EXPECT_THROW((void)api.asset_dividend_record(params), common::BadRequestError);
}

TEST(RestApiAssetApi, DustConvert) {
    const std::string example =
        R"json({"totalTransfered":"3.5971223","totalServiceCharge":"0.0794964","transferResult":[{"tranId":2987331510,"fromAsset":"USDT","amount":"1","transferedAmount":"3.5971223","serviceChargeAmount":"0.0794964","operateTime":1765212029749}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DustConvertParams params{.asset = "USDT"};
    const auto res = api.dust_convert(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/dust-convert/convert");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, DustConvertWithOptionalParams) {
    const std::string example =
        R"json({"totalTransfered":"3.5971223","totalServiceCharge":"0.0794964","transferResult":[{"tranId":2987331510,"fromAsset":"USDT","amount":"1","transferedAmount":"3.5971223","serviceChargeAmount":"0.0794964","operateTime":1765212029749}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DustConvertParams params{
        .asset = "USDT",
        .account_type = "SPOT",
        .client_id = "1",
        .target_asset = "BTC",
        .third_party_client_id = "1",
        .dust_quota_asset_to_target_asset_price = common::Decimal("1.0"),
    };
    const auto res = api.dust_convert(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("targetAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("thirdPartyClientId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("dustQuotaAssetToTargetAssetPrice="),
              std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, DustConvertBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DustConvertParams params{.asset = "USDT"};
    EXPECT_THROW((void)api.dust_convert(params), common::BadRequestError);
}

TEST(RestApiAssetApi, DustConvertibleAssets) {
    const std::string example =
        R"json({"dribbletPercentage":"0.02","totalTransferQuotaAssetAmount":"0.7899968","totalTransferTargetAssetAmount":"0.7899968","dribbletBase":"10","details":[{"asset":"AR","assetFullName":"AR","amountFree":"0.00856","exchange":"0.00073616","toQuotaAssetAmount":"0.036808","toTargetAssetAmount":"0.036808","toTargetAssetOffExchange":"0.03607184"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DustConvertibleAssetsParams params{.target_asset = "BTC"};
    const auto res = api.dust_convertible_assets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/dust-convert/query-convertible-assets");
    EXPECT_NE((rec.query() + "&" + rec.body).find("targetAsset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, DustConvertibleAssetsWithOptionalParams) {
    const std::string example =
        R"json({"dribbletPercentage":"0.02","totalTransferQuotaAssetAmount":"0.7899968","totalTransferTargetAssetAmount":"0.7899968","dribbletBase":"10","details":[{"asset":"AR","assetFullName":"AR","amountFree":"0.00856","exchange":"0.00073616","toQuotaAssetAmount":"0.036808","toTargetAssetAmount":"0.036808","toTargetAssetOffExchange":"0.03607184"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DustConvertibleAssetsParams params{
        .target_asset = "BTC",
        .account_type = "SPOT",
        .dust_quota_asset_to_target_asset_price = common::Decimal("1.0"),
    };
    const auto res = api.dust_convertible_assets(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("targetAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("dustQuotaAssetToTargetAssetPrice="),
              std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, DustConvertibleAssetsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DustConvertibleAssetsParams params{.target_asset = "BTC"};
    EXPECT_THROW((void)api.dust_convertible_assets(params), common::BadRequestError);
}

TEST(RestApiAssetApi, DustTransfer) {
    const std::string example =
        R"json({"totalServiceCharge":"0.02102542","totalTransfered":"1.05127099","transferResult":[{"amount":"0.03000000","fromAsset":"ETH","operateTime":1563368549307,"serviceChargeAmount":"0.00500000","tranId":2970932918,"transferedAmount":"0.25000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DustTransferParams params{.asset = "BTC"};
    const auto res = api.dust_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/dust");
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, DustTransferWithOptionalParams) {
    const std::string example =
        R"json({"totalServiceCharge":"0.02102542","totalTransfered":"1.05127099","transferResult":[{"amount":"0.03000000","fromAsset":"ETH","operateTime":1563368549307,"serviceChargeAmount":"0.00500000","tranId":2970932918,"transferedAmount":"0.25000000"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DustTransferParams params{
        .asset = "BTC",
        .account_type = DustTransferAccountTypeEnum::Spot,
        .recv_window = 5000,
    };
    const auto res = api.dust_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, DustTransferBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DustTransferParams params{.asset = "BTC"};
    EXPECT_THROW((void)api.dust_transfer(params), common::BadRequestError);
}

TEST(RestApiAssetApi, Dustlog) {
    const std::string example =
        R"json({"total":8,"userAssetDribblets":[{"operateTime":1615985535000,"totalTransferedAmount":"0.00132256","totalServiceChargeAmount":"0.00002699","transId":45178372831,"userAssetDribbletDetails":[{"transId":4359321,"serviceChargeAmount":"0.000009","amount":"0.0009","operateTime":1615985535000,"transferedAmount":"0.000441","fromAsset":"USDT","targetAsset":"BNB"}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DustlogParams params{};
    const auto res = api.dustlog(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/dribblet");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, DustlogWithOptionalParams) {
    const std::string example =
        R"json({"total":8,"userAssetDribblets":[{"operateTime":1615985535000,"totalTransferedAmount":"0.00132256","totalServiceChargeAmount":"0.00002699","transId":45178372831,"userAssetDribbletDetails":[{"transId":4359321,"serviceChargeAmount":"0.000009","amount":"0.0009","operateTime":1615985535000,"transferedAmount":"0.000441","fromAsset":"USDT","targetAsset":"BNB"}]}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const DustlogParams params{
        .account_type = DustlogAccountTypeEnum::Spot,
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .recv_window = 5000,
    };
    const auto res = api.dustlog(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, DustlogBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const DustlogParams params{};
    EXPECT_THROW((void)api.dustlog(params), common::BadRequestError);
}

TEST(RestApiAssetApi, FundingWallet) {
    const std::string example =
        R"json([{"asset":"USDT","free":"1","locked":"0","freeze":"0","withdrawing":"0","btcValuation":"0.00000091"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FundingWalletParams params{};
    const auto res = api.funding_wallet(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/get-funding-asset");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, FundingWalletWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"USDT","free":"1","locked":"0","freeze":"0","withdrawing":"0","btcValuation":"0.00000091"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const FundingWalletParams params{
        .asset = "BTC",
        .need_btc_valuation = true,
        .recv_window = 5000,
    };
    const auto res = api.funding_wallet(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("needBtcValuation="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, FundingWalletBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const FundingWalletParams params{};
    EXPECT_THROW((void)api.funding_wallet(params), common::BadRequestError);
}

TEST(RestApiAssetApi, GetAssetsThatCanBeConvertedIntoBnb) {
    const std::string example =
        R"json({"details":[{"asset":"ADA","assetFullName":"ADA","amountFree":"6.21","toBTC":"0.00016848","toBNB":"0.01777302","toBNBOffExchange":"0.01741756","exchange":"0.00035546"}],"totalTransferBtc":"0.00016848","totalTransferBNB":"0.01777302","dribbletPercentage":"0.02"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAssetsThatCanBeConvertedIntoBnbParams params{};
    const auto res = api.get_assets_that_can_be_converted_into_bnb(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/dust-btc");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, GetAssetsThatCanBeConvertedIntoBnbWithOptionalParams) {
    const std::string example =
        R"json({"details":[{"asset":"ADA","assetFullName":"ADA","amountFree":"6.21","toBTC":"0.00016848","toBNB":"0.01777302","toBNBOffExchange":"0.01741756","exchange":"0.00035546"}],"totalTransferBtc":"0.00016848","totalTransferBNB":"0.01777302","dribbletPercentage":"0.02"})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetAssetsThatCanBeConvertedIntoBnbParams params{
        .account_type = GetAssetsThatCanBeConvertedIntoBnbAccountTypeEnum::Spot,
        .recv_window = 5000,
    };
    const auto res = api.get_assets_that_can_be_converted_into_bnb(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("accountType="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, GetAssetsThatCanBeConvertedIntoBnbBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetAssetsThatCanBeConvertedIntoBnbParams params{};
    EXPECT_THROW((void)api.get_assets_that_can_be_converted_into_bnb(params),
                 common::BadRequestError);
}

TEST(RestApiAssetApi, GetCloudMiningPaymentAndRefundHistory) {
    const std::string example =
        R"json({"total":5,"rows":[{"createTime":1667880112000,"tranId":121230610120,"type":248,"asset":"USDT","amount":"25.0068","status":"S"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCloudMiningPaymentAndRefundHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    const auto res = api.get_cloud_mining_payment_and_refund_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/ledger-transfer/cloud-mining/queryByPage");
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, GetCloudMiningPaymentAndRefundHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":5,"rows":[{"createTime":1667880112000,"tranId":121230610120,"type":248,"asset":"USDT","amount":"25.0068","status":"S"}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetCloudMiningPaymentAndRefundHistoryParams params{
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .tran_id = 1,
        .client_tran_id = "1",
        .asset = "BTC",
        .current = 1,
        .size = 10,
    };
    const auto res = api.get_cloud_mining_payment_and_refund_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tranId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("clientTranId="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, GetCloudMiningPaymentAndRefundHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetCloudMiningPaymentAndRefundHistoryParams params{.start_time = 1623319461670,
                                                             .end_time = 1641782889000};
    EXPECT_THROW((void)api.get_cloud_mining_payment_and_refund_history(params),
                 common::BadRequestError);
}

TEST(RestApiAssetApi, GetOpenSymbolList) {
    const std::string example = R"json([{"openTime":1686161202000,"symbols":["BNBBTC"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const auto res = api.get_open_symbol_list();
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/spot/open-symbol-list");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, GetOpenSymbolListBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    EXPECT_THROW((void)api.get_open_symbol_list(), common::BadRequestError);
}

TEST(RestApiAssetApi, GetSpotAssetTags) {
    const std::string example =
        R"json([{"assetCode":"BNB","assetName":"BNB","trading":true,"tags":["Layer1_Layer2","BSC"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSpotAssetTagsParams params{};
    const auto res = api.get_spot_asset_tags(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/spot/asset/tags");
    EXPECT_EQ((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, GetSpotAssetTagsWithOptionalParams) {
    const std::string example =
        R"json([{"assetCode":"BNB","assetName":"BNB","trading":true,"tags":["Layer1_Layer2","BSC"]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const GetSpotAssetTagsParams params{
        .tag = "Layer1_Layer2,BSC",
    };
    const auto res = api.get_spot_asset_tags(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("tag="), std::string::npos);
}

TEST(RestApiAssetApi, GetSpotAssetTagsBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const GetSpotAssetTagsParams params{};
    EXPECT_THROW((void)api.get_spot_asset_tags(params), common::BadRequestError);
}

TEST(RestApiAssetApi, QueryUserDelegationHistory) {
    const std::string example =
        R"json({"total":3316,"rows":[{"clientTranId":"293915932290879488","transferType":"Undelegate","asset":"ETH","amount":"1","time":1695205406000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserDelegationHistoryParams params{
        .email = "abc@test.com", .start_time = 1623319461670, .end_time = 1641782889000};
    const auto res = api.query_user_delegation_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/custody/transfer-history");
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, QueryUserDelegationHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":3316,"rows":[{"clientTranId":"293915932290879488","transferType":"Undelegate","asset":"ETH","amount":"1","time":1695205406000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserDelegationHistoryParams params{
        .email = "abc@test.com",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .type = QueryUserDelegationHistoryTypeEnum::Delegate,
        .asset = "BTC",
        .current = 1,
        .size = 10,
        .recv_window = 5000,
    };
    const auto res = api.query_user_delegation_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("email="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, QueryUserDelegationHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUserDelegationHistoryParams params{
        .email = "abc@test.com", .start_time = 1623319461670, .end_time = 1641782889000};
    EXPECT_THROW((void)api.query_user_delegation_history(params), common::BadRequestError);
}

TEST(RestApiAssetApi, QueryUserUniversalTransferHistory) {
    const std::string example =
        R"json({"total":2,"rows":[{"asset":"USDT","amount":"1","type":"MAIN_UMFUTURE","status":"CONFIRMED","tranId":11415955596,"timestamp":1544433328000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserUniversalTransferHistoryParams params{.type = "type_example"};
    const auto res = api.query_user_universal_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/transfer");
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, QueryUserUniversalTransferHistoryWithOptionalParams) {
    const std::string example =
        R"json({"total":2,"rows":[{"asset":"USDT","amount":"1","type":"MAIN_UMFUTURE","status":"CONFIRMED","tranId":11415955596,"timestamp":1544433328000}]})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserUniversalTransferHistoryParams params{
        .type = "type_example",
        .start_time = 1623319461670,
        .end_time = 1641782889000,
        .current = 1,
        .size = 10,
        .from_symbol = QueryUserUniversalTransferHistoryFromSymbolEnum::IsolatedmarginMargin,
        .to_symbol = QueryUserUniversalTransferHistoryToSymbolEnum::MarginIsolatedmargin,
        .recv_window = 5000,
    };
    const auto res = api.query_user_universal_transfer_history(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("startTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("endTime="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("current="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("size="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, QueryUserUniversalTransferHistoryBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUserUniversalTransferHistoryParams params{.type = "type_example"};
    EXPECT_THROW((void)api.query_user_universal_transfer_history(params), common::BadRequestError);
}

TEST(RestApiAssetApi, UserUniversalTransfer) {
    const std::string example = R"json({"tranId":13526853623})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserUniversalTransferParams params{.type = UserUniversalTransferTypeEnum::MainUmfuture,
                                             .asset = "BTC",
                                             .amount = common::Decimal("1.0")};
    const auto res = api.user_universal_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/transfer");
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, UserUniversalTransferWithOptionalParams) {
    const std::string example = R"json({"tranId":13526853623})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserUniversalTransferParams params{
        .type = UserUniversalTransferTypeEnum::MainUmfuture,
        .asset = "BTC",
        .amount = common::Decimal("1.0"),
        .from_symbol = UserUniversalTransferFromSymbolEnum::IsolatedmarginMargin,
        .to_symbol = UserUniversalTransferToSymbolEnum::MarginIsolatedmargin,
        .recv_window = 5000,
    };
    const auto res = api.user_universal_transfer(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("type="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("amount="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("fromSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("toSymbol="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, UserUniversalTransferBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UserUniversalTransferParams params{.type = UserUniversalTransferTypeEnum::MainUmfuture,
                                             .asset = "BTC",
                                             .amount = common::Decimal("1.0")};
    EXPECT_THROW((void)api.user_universal_transfer(params), common::BadRequestError);
}

TEST(RestApiAssetApi, QueryUserWalletBalance) {
    const std::string example =
        R"json([{"activate":true,"balance":"0","walletName":"Spot","assetBalances":[{"asset":"USDT","assetName":"TetherUS","free":"6.238383","locked":"0","freeze":"0","withdrawing":"0","btcValuation":"6.238383"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserWalletBalanceParams params{};
    const auto res = api.query_user_wallet_balance(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/wallet/balance");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, QueryUserWalletBalanceWithOptionalParams) {
    const std::string example =
        R"json([{"activate":true,"balance":"0","walletName":"Spot","assetBalances":[{"asset":"USDT","assetName":"TetherUS","free":"6.238383","locked":"0","freeze":"0","withdrawing":"0","btcValuation":"6.238383"}]}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const QueryUserWalletBalanceParams params{
        .quote_asset = "BTC",
        .need_balance_detail = false,
        .recv_window = 5000,
    };
    const auto res = api.query_user_wallet_balance(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("quoteAsset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("needBalanceDetail="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, QueryUserWalletBalanceBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const QueryUserWalletBalanceParams params{};
    EXPECT_THROW((void)api.query_user_wallet_balance(params), common::BadRequestError);
}

TEST(RestApiAssetApi, ToggleBnbBurnOnSpotTradeAndMarginInterest) {
    const std::string example = R"json({"spotBNBBurn":true,"interestBNBBurn":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ToggleBnbBurnOnSpotTradeAndMarginInterestParams params{};
    const auto res = api.toggle_bnb_burn_on_spot_trade_and_margin_interest(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v1/bnbBurn");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, ToggleBnbBurnOnSpotTradeAndMarginInterestWithOptionalParams) {
    const std::string example = R"json({"spotBNBBurn":true,"interestBNBBurn":false})json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const ToggleBnbBurnOnSpotTradeAndMarginInterestParams params{
        .spot_bnb_burn = "true",
        .interest_bnb_burn = "true",
        .recv_window = 5000,
    };
    const auto res = api.toggle_bnb_burn_on_spot_trade_and_margin_interest(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("spotBNBBurn="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("interestBNBBurn="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, ToggleBnbBurnOnSpotTradeAndMarginInterestBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const ToggleBnbBurnOnSpotTradeAndMarginInterestParams params{};
    EXPECT_THROW((void)api.toggle_bnb_burn_on_spot_trade_and_margin_interest(params),
                 common::BadRequestError);
}

TEST(RestApiAssetApi, TradeFee) {
    const std::string example =
        R"json([{"symbol":"ADABNB","makerCommission":"0.001","takerCommission":"0.001"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TradeFeeParams params{};
    const auto res = api.trade_fee(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "GET");
    EXPECT_EQ(rec.path(), "/sapi/v1/asset/tradeFee");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, TradeFeeWithOptionalParams) {
    const std::string example =
        R"json([{"symbol":"ADABNB","makerCommission":"0.001","takerCommission":"0.001"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const TradeFeeParams params{
        .symbol = "ADABNB",
        .recv_window = 5000,
    };
    const auto res = api.trade_fee(params);
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

TEST(RestApiAssetApi, TradeFeeBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const TradeFeeParams params{};
    EXPECT_THROW((void)api.trade_fee(params), common::BadRequestError);
}

TEST(RestApiAssetApi, UserAsset) {
    const std::string example =
        R"json([{"asset":"AVAX","free":"1","locked":"0","freeze":"0","withdrawing":"0","ipoable":"0","btcValuation":"0"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserAssetParams params{};
    const auto res = api.user_asset(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path(), "/sapi/v3/asset/getUserAsset");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, UserAssetWithOptionalParams) {
    const std::string example =
        R"json([{"asset":"AVAX","free":"1","locked":"0","freeze":"0","withdrawing":"0","ipoable":"0","btcValuation":"0"}])json";
    MockServer server(reply(example));
    const auto api = api_for(server);
    const UserAssetParams params{
        .asset = "BTC",
        .need_btc_valuation = true,
        .recv_window = 5000,
    };
    const auto res = api.user_asset(params);
    EXPECT_EQ(res.status(), 200);

    EXPECT_NO_THROW((void)res.data());

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.path().find('{'), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("asset="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("needBtcValuation="), std::string::npos);
    EXPECT_NE((rec.query() + "&" + rec.body).find("recvWindow="), std::string::npos);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "key");
    EXPECT_NE((rec.query() + rec.body).find("signature="), std::string::npos);
}

TEST(RestApiAssetApi, UserAssetBadRequest) {
    MockServer server(reply(kBadRequest, 400));
    const auto api = api_for(server);
    const UserAssetParams params{};
    EXPECT_THROW((void)api.user_asset(params), common::BadRequestError);
}
