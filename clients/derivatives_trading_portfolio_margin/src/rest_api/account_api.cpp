//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/account_api.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(BnbTransferTransferSideEnum value) noexcept {
    switch (value) {
    case BnbTransferTransferSideEnum::ToUm:
        return "TO_UM";
    case BnbTransferTransferSideEnum::FromUm:
        return "FROM_UM";
    case BnbTransferTransferSideEnum::Unknown:
        break;
    }
    return "";
}

BnbTransferTransferSideEnum
tag_invoke(boost::json::value_to_tag<BnbTransferTransferSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TO_UM") {
        return BnbTransferTransferSideEnum::ToUm;
    }
    if (s == "FROM_UM") {
        return BnbTransferTransferSideEnum::FromUm;
    }
    return BnbTransferTransferSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                BnbTransferTransferSideEnum value) {
    if (value == BnbTransferTransferSideEnum::Unknown) {
        throw std::invalid_argument("BnbTransferTransferSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ChangeAutoRepayFuturesStatusAutoRepayEnum value) noexcept {
    switch (value) {
    case ChangeAutoRepayFuturesStatusAutoRepayEnum::True_:
        return "true";
    case ChangeAutoRepayFuturesStatusAutoRepayEnum::False_:
        return "false";
    case ChangeAutoRepayFuturesStatusAutoRepayEnum::Unknown:
        break;
    }
    return "";
}

ChangeAutoRepayFuturesStatusAutoRepayEnum
tag_invoke(boost::json::value_to_tag<ChangeAutoRepayFuturesStatusAutoRepayEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return ChangeAutoRepayFuturesStatusAutoRepayEnum::True_;
    }
    if (s == "false") {
        return ChangeAutoRepayFuturesStatusAutoRepayEnum::False_;
    }
    return ChangeAutoRepayFuturesStatusAutoRepayEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ChangeAutoRepayFuturesStatusAutoRepayEnum value) {
    if (value == ChangeAutoRepayFuturesStatusAutoRepayEnum::Unknown) {
        throw std::invalid_argument(
            "ChangeAutoRepayFuturesStatusAutoRepayEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ChangeCmPositionModeDualSidePositionEnum value) noexcept {
    switch (value) {
    case ChangeCmPositionModeDualSidePositionEnum::True_:
        return "true";
    case ChangeCmPositionModeDualSidePositionEnum::False_:
        return "false";
    case ChangeCmPositionModeDualSidePositionEnum::Unknown:
        break;
    }
    return "";
}

ChangeCmPositionModeDualSidePositionEnum
tag_invoke(boost::json::value_to_tag<ChangeCmPositionModeDualSidePositionEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return ChangeCmPositionModeDualSidePositionEnum::True_;
    }
    if (s == "false") {
        return ChangeCmPositionModeDualSidePositionEnum::False_;
    }
    return ChangeCmPositionModeDualSidePositionEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ChangeCmPositionModeDualSidePositionEnum value) {
    if (value == ChangeCmPositionModeDualSidePositionEnum::Unknown) {
        throw std::invalid_argument(
            "ChangeCmPositionModeDualSidePositionEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ChangeUmPositionModeDualSidePositionEnum value) noexcept {
    switch (value) {
    case ChangeUmPositionModeDualSidePositionEnum::True_:
        return "true";
    case ChangeUmPositionModeDualSidePositionEnum::False_:
        return "false";
    case ChangeUmPositionModeDualSidePositionEnum::Unknown:
        break;
    }
    return "";
}

ChangeUmPositionModeDualSidePositionEnum
tag_invoke(boost::json::value_to_tag<ChangeUmPositionModeDualSidePositionEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return ChangeUmPositionModeDualSidePositionEnum::True_;
    }
    if (s == "false") {
        return ChangeUmPositionModeDualSidePositionEnum::False_;
    }
    return ChangeUmPositionModeDualSidePositionEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ChangeUmPositionModeDualSidePositionEnum value) {
    if (value == ChangeUmPositionModeDualSidePositionEnum::Unknown) {
        throw std::invalid_argument(
            "ChangeUmPositionModeDualSidePositionEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(FundCollectionByAssetFutureTypeEnum value) noexcept {
    switch (value) {
    case FundCollectionByAssetFutureTypeEnum::Um:
        return "UM";
    case FundCollectionByAssetFutureTypeEnum::Cm:
        return "CM";
    case FundCollectionByAssetFutureTypeEnum::Option:
        return "OPTION";
    case FundCollectionByAssetFutureTypeEnum::Unknown:
        break;
    }
    return "";
}

FundCollectionByAssetFutureTypeEnum
tag_invoke(boost::json::value_to_tag<FundCollectionByAssetFutureTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "UM") {
        return FundCollectionByAssetFutureTypeEnum::Um;
    }
    if (s == "CM") {
        return FundCollectionByAssetFutureTypeEnum::Cm;
    }
    if (s == "OPTION") {
        return FundCollectionByAssetFutureTypeEnum::Option;
    }
    return FundCollectionByAssetFutureTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                FundCollectionByAssetFutureTypeEnum value) {
    if (value == FundCollectionByAssetFutureTypeEnum::Unknown) {
        throw std::invalid_argument("FundCollectionByAssetFutureTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(GetCmIncomeHistoryIncomeTypeEnum value) noexcept {
    switch (value) {
    case GetCmIncomeHistoryIncomeTypeEnum::Transfer:
        return "TRANSFER";
    case GetCmIncomeHistoryIncomeTypeEnum::WelcomeBonus:
        return "WELCOME_BONUS";
    case GetCmIncomeHistoryIncomeTypeEnum::FundingFee:
        return "FUNDING_FEE";
    case GetCmIncomeHistoryIncomeTypeEnum::RealizedPnl:
        return "REALIZED_PNL";
    case GetCmIncomeHistoryIncomeTypeEnum::Commission:
        return "COMMISSION";
    case GetCmIncomeHistoryIncomeTypeEnum::InsuranceClear:
        return "INSURANCE_CLEAR";
    case GetCmIncomeHistoryIncomeTypeEnum::DeliveredSettelment:
        return "DELIVERED_SETTELMENT";
    case GetCmIncomeHistoryIncomeTypeEnum::Unknown:
        break;
    }
    return "";
}

GetCmIncomeHistoryIncomeTypeEnum
tag_invoke(boost::json::value_to_tag<GetCmIncomeHistoryIncomeTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRANSFER") {
        return GetCmIncomeHistoryIncomeTypeEnum::Transfer;
    }
    if (s == "WELCOME_BONUS") {
        return GetCmIncomeHistoryIncomeTypeEnum::WelcomeBonus;
    }
    if (s == "FUNDING_FEE") {
        return GetCmIncomeHistoryIncomeTypeEnum::FundingFee;
    }
    if (s == "REALIZED_PNL") {
        return GetCmIncomeHistoryIncomeTypeEnum::RealizedPnl;
    }
    if (s == "COMMISSION") {
        return GetCmIncomeHistoryIncomeTypeEnum::Commission;
    }
    if (s == "INSURANCE_CLEAR") {
        return GetCmIncomeHistoryIncomeTypeEnum::InsuranceClear;
    }
    if (s == "DELIVERED_SETTELMENT") {
        return GetCmIncomeHistoryIncomeTypeEnum::DeliveredSettelment;
    }
    return GetCmIncomeHistoryIncomeTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetCmIncomeHistoryIncomeTypeEnum value) {
    if (value == GetCmIncomeHistoryIncomeTypeEnum::Unknown) {
        throw std::invalid_argument("GetCmIncomeHistoryIncomeTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(GetMarginBorrowLoanInterestHistoryArchivedEnum value) noexcept {
    switch (value) {
    case GetMarginBorrowLoanInterestHistoryArchivedEnum::True_:
        return "true";
    case GetMarginBorrowLoanInterestHistoryArchivedEnum::False_:
        return "false";
    case GetMarginBorrowLoanInterestHistoryArchivedEnum::Unknown:
        break;
    }
    return "";
}

GetMarginBorrowLoanInterestHistoryArchivedEnum
tag_invoke(boost::json::value_to_tag<GetMarginBorrowLoanInterestHistoryArchivedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return GetMarginBorrowLoanInterestHistoryArchivedEnum::True_;
    }
    if (s == "false") {
        return GetMarginBorrowLoanInterestHistoryArchivedEnum::False_;
    }
    return GetMarginBorrowLoanInterestHistoryArchivedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetMarginBorrowLoanInterestHistoryArchivedEnum value) {
    if (value == GetMarginBorrowLoanInterestHistoryArchivedEnum::Unknown) {
        throw std::invalid_argument(
            "GetMarginBorrowLoanInterestHistoryArchivedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(GetUmIncomeHistoryIncomeTypeEnum value) noexcept {
    switch (value) {
    case GetUmIncomeHistoryIncomeTypeEnum::Transfer:
        return "TRANSFER";
    case GetUmIncomeHistoryIncomeTypeEnum::WelcomeBonus:
        return "WELCOME_BONUS";
    case GetUmIncomeHistoryIncomeTypeEnum::RealizedPnl:
        return "REALIZED_PNL";
    case GetUmIncomeHistoryIncomeTypeEnum::FundingFee:
        return "FUNDING_FEE";
    case GetUmIncomeHistoryIncomeTypeEnum::Commission:
        return "COMMISSION";
    case GetUmIncomeHistoryIncomeTypeEnum::InsuranceClear:
        return "INSURANCE_CLEAR";
    case GetUmIncomeHistoryIncomeTypeEnum::ReferralKickback:
        return "REFERRAL_KICKBACK";
    case GetUmIncomeHistoryIncomeTypeEnum::CommissionRebate:
        return "COMMISSION_REBATE";
    case GetUmIncomeHistoryIncomeTypeEnum::ApiRebate:
        return "API_REBATE";
    case GetUmIncomeHistoryIncomeTypeEnum::ContestReward:
        return "CONTEST_REWARD";
    case GetUmIncomeHistoryIncomeTypeEnum::CrossCollateralTransfer:
        return "CROSS_COLLATERAL_TRANSFER";
    case GetUmIncomeHistoryIncomeTypeEnum::OptionsPremiumFee:
        return "OPTIONS_PREMIUM_FEE";
    case GetUmIncomeHistoryIncomeTypeEnum::OptionsSettleProfit:
        return "OPTIONS_SETTLE_PROFIT";
    case GetUmIncomeHistoryIncomeTypeEnum::InternalTransfer:
        return "INTERNAL_TRANSFER";
    case GetUmIncomeHistoryIncomeTypeEnum::DeliveredSettelment:
        return "DELIVERED_SETTELMENT";
    case GetUmIncomeHistoryIncomeTypeEnum::CoinSwapDeposit:
        return "COIN_SWAP_DEPOSIT";
    case GetUmIncomeHistoryIncomeTypeEnum::CoinSwapWithdraw:
        return "COIN_SWAP_WITHDRAW";
    case GetUmIncomeHistoryIncomeTypeEnum::PositionLimitIncreaseFee:
        return "POSITION_LIMIT_INCREASE_FEE";
    case GetUmIncomeHistoryIncomeTypeEnum::Unknown:
        break;
    }
    return "";
}

GetUmIncomeHistoryIncomeTypeEnum
tag_invoke(boost::json::value_to_tag<GetUmIncomeHistoryIncomeTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRANSFER") {
        return GetUmIncomeHistoryIncomeTypeEnum::Transfer;
    }
    if (s == "WELCOME_BONUS") {
        return GetUmIncomeHistoryIncomeTypeEnum::WelcomeBonus;
    }
    if (s == "REALIZED_PNL") {
        return GetUmIncomeHistoryIncomeTypeEnum::RealizedPnl;
    }
    if (s == "FUNDING_FEE") {
        return GetUmIncomeHistoryIncomeTypeEnum::FundingFee;
    }
    if (s == "COMMISSION") {
        return GetUmIncomeHistoryIncomeTypeEnum::Commission;
    }
    if (s == "INSURANCE_CLEAR") {
        return GetUmIncomeHistoryIncomeTypeEnum::InsuranceClear;
    }
    if (s == "REFERRAL_KICKBACK") {
        return GetUmIncomeHistoryIncomeTypeEnum::ReferralKickback;
    }
    if (s == "COMMISSION_REBATE") {
        return GetUmIncomeHistoryIncomeTypeEnum::CommissionRebate;
    }
    if (s == "API_REBATE") {
        return GetUmIncomeHistoryIncomeTypeEnum::ApiRebate;
    }
    if (s == "CONTEST_REWARD") {
        return GetUmIncomeHistoryIncomeTypeEnum::ContestReward;
    }
    if (s == "CROSS_COLLATERAL_TRANSFER") {
        return GetUmIncomeHistoryIncomeTypeEnum::CrossCollateralTransfer;
    }
    if (s == "OPTIONS_PREMIUM_FEE") {
        return GetUmIncomeHistoryIncomeTypeEnum::OptionsPremiumFee;
    }
    if (s == "OPTIONS_SETTLE_PROFIT") {
        return GetUmIncomeHistoryIncomeTypeEnum::OptionsSettleProfit;
    }
    if (s == "INTERNAL_TRANSFER") {
        return GetUmIncomeHistoryIncomeTypeEnum::InternalTransfer;
    }
    if (s == "DELIVERED_SETTELMENT") {
        return GetUmIncomeHistoryIncomeTypeEnum::DeliveredSettelment;
    }
    if (s == "COIN_SWAP_DEPOSIT") {
        return GetUmIncomeHistoryIncomeTypeEnum::CoinSwapDeposit;
    }
    if (s == "COIN_SWAP_WITHDRAW") {
        return GetUmIncomeHistoryIncomeTypeEnum::CoinSwapWithdraw;
    }
    if (s == "POSITION_LIMIT_INCREASE_FEE") {
        return GetUmIncomeHistoryIncomeTypeEnum::PositionLimitIncreaseFee;
    }
    return GetUmIncomeHistoryIncomeTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetUmIncomeHistoryIncomeTypeEnum value) {
    if (value == GetUmIncomeHistoryIncomeTypeEnum::Unknown) {
        throw std::invalid_argument("GetUmIncomeHistoryIncomeTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryMarginLoanRecordArchivedEnum value) noexcept {
    switch (value) {
    case QueryMarginLoanRecordArchivedEnum::True_:
        return "true";
    case QueryMarginLoanRecordArchivedEnum::False_:
        return "false";
    case QueryMarginLoanRecordArchivedEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginLoanRecordArchivedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginLoanRecordArchivedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return QueryMarginLoanRecordArchivedEnum::True_;
    }
    if (s == "false") {
        return QueryMarginLoanRecordArchivedEnum::False_;
    }
    return QueryMarginLoanRecordArchivedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginLoanRecordArchivedEnum value) {
    if (value == QueryMarginLoanRecordArchivedEnum::Unknown) {
        throw std::invalid_argument("QueryMarginLoanRecordArchivedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryMarginRepayRecordArchivedEnum value) noexcept {
    switch (value) {
    case QueryMarginRepayRecordArchivedEnum::True_:
        return "true";
    case QueryMarginRepayRecordArchivedEnum::False_:
        return "false";
    case QueryMarginRepayRecordArchivedEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginRepayRecordArchivedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginRepayRecordArchivedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return QueryMarginRepayRecordArchivedEnum::True_;
    }
    if (s == "false") {
        return QueryMarginRepayRecordArchivedEnum::False_;
    }
    return QueryMarginRepayRecordArchivedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginRepayRecordArchivedEnum value) {
    if (value == QueryMarginRepayRecordArchivedEnum::Unknown) {
        throw std::invalid_argument("QueryMarginRepayRecordArchivedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

AccountApi::AccountApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest AccountApi::account_balance_request(const AccountBalanceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/balance";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountBalanceResponse>
AccountApi::account_balance(const AccountBalanceParams& params) const {
    return common::send<AccountBalanceResponse>(*client_, account_balance_request(params));
}

common::RestRequest
AccountApi::account_information_request(const AccountInformationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountInformationResponse>
AccountApi::account_information(const AccountInformationParams& params) const {
    return common::send<AccountInformationResponse>(*client_, account_information_request(params));
}

common::RestRequest AccountApi::bnb_transfer_request(const BnbTransferParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/bnb-transfer";
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "transferSide", params.transfer_side);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<BnbTransferResponse>
AccountApi::bnb_transfer(const BnbTransferParams& params) const {
    return common::send<BnbTransferResponse>(*client_, bnb_transfer_request(params));
}

common::RestRequest AccountApi::change_auto_repay_futures_status_request(
    const ChangeAutoRepayFuturesStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/repay-futures-switch";
    common::detail::json::set_param(req.query, "autoRepay", params.auto_repay);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeAutoRepayFuturesStatusResponse>
AccountApi::change_auto_repay_futures_status(
    const ChangeAutoRepayFuturesStatusParams& params) const {
    return common::send<ChangeAutoRepayFuturesStatusResponse>(
        *client_, change_auto_repay_futures_status_request(params));
}

common::RestRequest AccountApi::get_auto_repay_futures_status_request(
    const GetAutoRepayFuturesStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/repay-futures-switch";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetAutoRepayFuturesStatusResponse>
AccountApi::get_auto_repay_futures_status(const GetAutoRepayFuturesStatusParams& params) const {
    return common::send<GetAutoRepayFuturesStatusResponse>(
        *client_, get_auto_repay_futures_status_request(params));
}

common::RestRequest
AccountApi::change_cm_initial_leverage_request(const ChangeCmInitialLeverageParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/cm/leverage";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "leverage", params.leverage);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeCmInitialLeverageResponse>
AccountApi::change_cm_initial_leverage(const ChangeCmInitialLeverageParams& params) const {
    return common::send<ChangeCmInitialLeverageResponse>(
        *client_, change_cm_initial_leverage_request(params));
}

common::RestRequest
AccountApi::change_cm_position_mode_request(const ChangeCmPositionModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/cm/positionSide/dual";
    common::detail::json::set_param(req.query, "dualSidePosition", params.dual_side_position);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeCmPositionModeResponse>
AccountApi::change_cm_position_mode(const ChangeCmPositionModeParams& params) const {
    return common::send<ChangeCmPositionModeResponse>(*client_,
                                                      change_cm_position_mode_request(params));
}

common::RestRequest AccountApi::get_cm_current_position_mode_request(
    const GetCmCurrentPositionModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/positionSide/dual";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCmCurrentPositionModeResponse>
AccountApi::get_cm_current_position_mode(const GetCmCurrentPositionModeParams& params) const {
    return common::send<GetCmCurrentPositionModeResponse>(
        *client_, get_cm_current_position_mode_request(params));
}

common::RestRequest
AccountApi::change_um_initial_leverage_request(const ChangeUmInitialLeverageParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/um/leverage";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "leverage", params.leverage);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeUmInitialLeverageResponse>
AccountApi::change_um_initial_leverage(const ChangeUmInitialLeverageParams& params) const {
    return common::send<ChangeUmInitialLeverageResponse>(
        *client_, change_um_initial_leverage_request(params));
}

common::RestRequest
AccountApi::change_um_position_mode_request(const ChangeUmPositionModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/um/positionSide/dual";
    common::detail::json::set_param(req.query, "dualSidePosition", params.dual_side_position);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeUmPositionModeResponse>
AccountApi::change_um_position_mode(const ChangeUmPositionModeParams& params) const {
    return common::send<ChangeUmPositionModeResponse>(*client_,
                                                      change_um_position_mode_request(params));
}

common::RestRequest AccountApi::get_um_current_position_mode_request(
    const GetUmCurrentPositionModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/positionSide/dual";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetUmCurrentPositionModeResponse>
AccountApi::get_um_current_position_mode(const GetUmCurrentPositionModeParams& params) const {
    return common::send<GetUmCurrentPositionModeResponse>(
        *client_, get_um_current_position_mode_request(params));
}

common::RestRequest AccountApi::cm_notional_and_leverage_brackets_request(
    const CmNotionalAndLeverageBracketsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/leverageBracket";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CmNotionalAndLeverageBracketsResponseInner>>
AccountApi::cm_notional_and_leverage_brackets(
    const CmNotionalAndLeverageBracketsParams& params) const {
    return common::send<std::vector<CmNotionalAndLeverageBracketsResponseInner>>(
        *client_, cm_notional_and_leverage_brackets_request(params));
}

common::RestRequest
AccountApi::fund_auto_collection_request(const FundAutoCollectionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/auto-collection";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FundAutoCollectionResponse>
AccountApi::fund_auto_collection(const FundAutoCollectionParams& params) const {
    return common::send<FundAutoCollectionResponse>(*client_, fund_auto_collection_request(params));
}

common::RestRequest
AccountApi::fund_collection_by_asset_request(const FundCollectionByAssetParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/asset-collection";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "futureType", params.future_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FundCollectionByAssetResponse>
AccountApi::fund_collection_by_asset(const FundCollectionByAssetParams& params) const {
    return common::send<FundCollectionByAssetResponse>(*client_,
                                                       fund_collection_by_asset_request(params));
}

common::RestRequest
AccountApi::get_cm_account_detail_request(const GetCmAccountDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCmAccountDetailResponse>
AccountApi::get_cm_account_detail(const GetCmAccountDetailParams& params) const {
    return common::send<GetCmAccountDetailResponse>(*client_,
                                                    get_cm_account_detail_request(params));
}

common::RestRequest AccountApi::get_cm_futures_order_download_link_by_id_request(
    const GetCmFuturesOrderDownloadLinkByIdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/order/asyn/id";
    common::detail::json::set_param(req.query, "downloadId", params.download_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCmFuturesOrderDownloadLinkByIdResponse>
AccountApi::get_cm_futures_order_download_link_by_id(
    const GetCmFuturesOrderDownloadLinkByIdParams& params) const {
    return common::send<GetCmFuturesOrderDownloadLinkByIdResponse>(
        *client_, get_cm_futures_order_download_link_by_id_request(params));
}

common::RestRequest AccountApi::get_cm_futures_trade_download_link_by_id_request(
    const GetCmFuturesTradeDownloadLinkByIdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/trade/asyn/id";
    common::detail::json::set_param(req.query, "downloadId", params.download_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCmFuturesTradeDownloadLinkByIdResponse>
AccountApi::get_cm_futures_trade_download_link_by_id(
    const GetCmFuturesTradeDownloadLinkByIdParams& params) const {
    return common::send<GetCmFuturesTradeDownloadLinkByIdResponse>(
        *client_, get_cm_futures_trade_download_link_by_id_request(params));
}

common::RestRequest AccountApi::get_cm_futures_transaction_download_link_by_id_request(
    const GetCmFuturesTransactionDownloadLinkByIdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/income/asyn/id";
    common::detail::json::set_param(req.query, "downloadId", params.download_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCmFuturesTransactionDownloadLinkByIdResponse>
AccountApi::get_cm_futures_transaction_download_link_by_id(
    const GetCmFuturesTransactionDownloadLinkByIdParams& params) const {
    return common::send<GetCmFuturesTransactionDownloadLinkByIdResponse>(
        *client_, get_cm_futures_transaction_download_link_by_id_request(params));
}

common::RestRequest
AccountApi::get_cm_income_history_request(const GetCmIncomeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/income";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "incomeType", params.income_type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetCmIncomeHistoryResponseInner>>
AccountApi::get_cm_income_history(const GetCmIncomeHistoryParams& params) const {
    return common::send<std::vector<GetCmIncomeHistoryResponseInner>>(
        *client_, get_cm_income_history_request(params));
}

common::RestRequest AccountApi::get_download_id_for_cm_futures_order_history_request(
    const GetDownloadIdForCmFuturesOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/order/asyn";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDownloadIdForCmFuturesOrderHistoryResponse>
AccountApi::get_download_id_for_cm_futures_order_history(
    const GetDownloadIdForCmFuturesOrderHistoryParams& params) const {
    return common::send<GetDownloadIdForCmFuturesOrderHistoryResponse>(
        *client_, get_download_id_for_cm_futures_order_history_request(params));
}

common::RestRequest AccountApi::get_download_id_for_cm_futures_trade_history_request(
    const GetDownloadIdForCmFuturesTradeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/trade/asyn";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDownloadIdForCmFuturesTradeHistoryResponse>
AccountApi::get_download_id_for_cm_futures_trade_history(
    const GetDownloadIdForCmFuturesTradeHistoryParams& params) const {
    return common::send<GetDownloadIdForCmFuturesTradeHistoryResponse>(
        *client_, get_download_id_for_cm_futures_trade_history_request(params));
}

common::RestRequest AccountApi::get_download_id_for_cm_futures_transaction_history_request(
    const GetDownloadIdForCmFuturesTransactionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/income/asyn";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDownloadIdForCmFuturesTransactionHistoryResponse>
AccountApi::get_download_id_for_cm_futures_transaction_history(
    const GetDownloadIdForCmFuturesTransactionHistoryParams& params) const {
    return common::send<GetDownloadIdForCmFuturesTransactionHistoryResponse>(
        *client_, get_download_id_for_cm_futures_transaction_history_request(params));
}

common::RestRequest AccountApi::get_download_id_for_um_futures_order_history_request(
    const GetDownloadIdForUmFuturesOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/order/asyn";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDownloadIdForUmFuturesOrderHistoryResponse>
AccountApi::get_download_id_for_um_futures_order_history(
    const GetDownloadIdForUmFuturesOrderHistoryParams& params) const {
    return common::send<GetDownloadIdForUmFuturesOrderHistoryResponse>(
        *client_, get_download_id_for_um_futures_order_history_request(params));
}

common::RestRequest AccountApi::get_download_id_for_um_futures_trade_history_request(
    const GetDownloadIdForUmFuturesTradeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/trade/asyn";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDownloadIdForUmFuturesTradeHistoryResponse>
AccountApi::get_download_id_for_um_futures_trade_history(
    const GetDownloadIdForUmFuturesTradeHistoryParams& params) const {
    return common::send<GetDownloadIdForUmFuturesTradeHistoryResponse>(
        *client_, get_download_id_for_um_futures_trade_history_request(params));
}

common::RestRequest AccountApi::get_download_id_for_um_futures_transaction_history_request(
    const GetDownloadIdForUmFuturesTransactionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/income/asyn";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDownloadIdForUmFuturesTransactionHistoryResponse>
AccountApi::get_download_id_for_um_futures_transaction_history(
    const GetDownloadIdForUmFuturesTransactionHistoryParams& params) const {
    return common::send<GetDownloadIdForUmFuturesTransactionHistoryResponse>(
        *client_, get_download_id_for_um_futures_transaction_history_request(params));
}

common::RestRequest AccountApi::get_margin_borrow_loan_interest_history_request(
    const GetMarginBorrowLoanInterestHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/marginInterestHistory";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "archived", params.archived);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetMarginBorrowLoanInterestHistoryResponse>
AccountApi::get_margin_borrow_loan_interest_history(
    const GetMarginBorrowLoanInterestHistoryParams& params) const {
    return common::send<GetMarginBorrowLoanInterestHistoryResponse>(
        *client_, get_margin_borrow_loan_interest_history_request(params));
}

common::RestRequest
AccountApi::get_um_account_detail_request(const GetUmAccountDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetUmAccountDetailResponse>
AccountApi::get_um_account_detail(const GetUmAccountDetailParams& params) const {
    return common::send<GetUmAccountDetailResponse>(*client_,
                                                    get_um_account_detail_request(params));
}

common::RestRequest
AccountApi::get_um_account_detail_v2_request(const GetUmAccountDetailV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v2/um/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetUmAccountDetailV2Response>
AccountApi::get_um_account_detail_v2(const GetUmAccountDetailV2Params& params) const {
    return common::send<GetUmAccountDetailV2Response>(*client_,
                                                      get_um_account_detail_v2_request(params));
}

common::RestRequest AccountApi::get_um_futures_order_download_link_by_id_request(
    const GetUmFuturesOrderDownloadLinkByIdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/order/asyn/id";
    common::detail::json::set_param(req.query, "downloadId", params.download_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetUmFuturesOrderDownloadLinkByIdResponse>
AccountApi::get_um_futures_order_download_link_by_id(
    const GetUmFuturesOrderDownloadLinkByIdParams& params) const {
    return common::send<GetUmFuturesOrderDownloadLinkByIdResponse>(
        *client_, get_um_futures_order_download_link_by_id_request(params));
}

common::RestRequest AccountApi::get_um_futures_trade_download_link_by_id_request(
    const GetUmFuturesTradeDownloadLinkByIdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/trade/asyn/id";
    common::detail::json::set_param(req.query, "downloadId", params.download_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetUmFuturesTradeDownloadLinkByIdResponse>
AccountApi::get_um_futures_trade_download_link_by_id(
    const GetUmFuturesTradeDownloadLinkByIdParams& params) const {
    return common::send<GetUmFuturesTradeDownloadLinkByIdResponse>(
        *client_, get_um_futures_trade_download_link_by_id_request(params));
}

common::RestRequest AccountApi::get_um_futures_transaction_download_link_by_id_request(
    const GetUmFuturesTransactionDownloadLinkByIdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/income/asyn/id";
    common::detail::json::set_param(req.query, "downloadId", params.download_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetUmFuturesTransactionDownloadLinkByIdResponse>
AccountApi::get_um_futures_transaction_download_link_by_id(
    const GetUmFuturesTransactionDownloadLinkByIdParams& params) const {
    return common::send<GetUmFuturesTransactionDownloadLinkByIdResponse>(
        *client_, get_um_futures_transaction_download_link_by_id_request(params));
}

common::RestRequest
AccountApi::get_um_income_history_request(const GetUmIncomeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/income";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "incomeType", params.income_type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetUmIncomeHistoryResponseInner>>
AccountApi::get_um_income_history(const GetUmIncomeHistoryParams& params) const {
    return common::send<std::vector<GetUmIncomeHistoryResponseInner>>(
        *client_, get_um_income_history_request(params));
}

common::RestRequest AccountApi::get_user_commission_rate_for_cm_request(
    const GetUserCommissionRateForCmParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/commissionRate";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetUserCommissionRateForCmResponse>
AccountApi::get_user_commission_rate_for_cm(const GetUserCommissionRateForCmParams& params) const {
    return common::send<GetUserCommissionRateForCmResponse>(
        *client_, get_user_commission_rate_for_cm_request(params));
}

common::RestRequest AccountApi::get_user_commission_rate_for_um_request(
    const GetUserCommissionRateForUmParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/commissionRate";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetUserCommissionRateForUmResponse>
AccountApi::get_user_commission_rate_for_um(const GetUserCommissionRateForUmParams& params) const {
    return common::send<GetUserCommissionRateForUmResponse>(
        *client_, get_user_commission_rate_for_um_request(params));
}

common::RestRequest
AccountApi::margin_max_borrow_request(const MarginMaxBorrowParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/maxBorrowable";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginMaxBorrowResponse>
AccountApi::margin_max_borrow(const MarginMaxBorrowParams& params) const {
    return common::send<MarginMaxBorrowResponse>(*client_, margin_max_borrow_request(params));
}

common::RestRequest AccountApi::portfolio_margin_um_trading_quantitative_rules_indicators_request(
    const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/apiTradingStatus";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse>
AccountApi::portfolio_margin_um_trading_quantitative_rules_indicators(
    const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams& params) const {
    return common::send<PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse>(
        *client_, portfolio_margin_um_trading_quantitative_rules_indicators_request(params));
}

common::RestRequest AccountApi::query_cm_position_information_request(
    const QueryCmPositionInformationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/positionRisk";
    common::detail::json::set_param(req.query, "marginAsset", params.margin_asset);
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryCmPositionInformationResponseInner>>
AccountApi::query_cm_position_information(const QueryCmPositionInformationParams& params) const {
    return common::send<std::vector<QueryCmPositionInformationResponseInner>>(
        *client_, query_cm_position_information_request(params));
}

common::RestRequest
AccountApi::query_margin_loan_record_request(const QueryMarginLoanRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/marginLoan";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "archived", params.archived);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryMarginLoanRecordResponse>
AccountApi::query_margin_loan_record(const QueryMarginLoanRecordParams& params) const {
    return common::send<QueryMarginLoanRecordResponse>(*client_,
                                                       query_margin_loan_record_request(params));
}

common::RestRequest
AccountApi::query_margin_max_withdraw_request(const QueryMarginMaxWithdrawParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/maxWithdraw";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryMarginMaxWithdrawResponse>
AccountApi::query_margin_max_withdraw(const QueryMarginMaxWithdrawParams& params) const {
    return common::send<QueryMarginMaxWithdrawResponse>(*client_,
                                                        query_margin_max_withdraw_request(params));
}

common::RestRequest
AccountApi::query_margin_repay_record_request(const QueryMarginRepayRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/repayLoan";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "archived", params.archived);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryMarginRepayRecordResponse>
AccountApi::query_margin_repay_record(const QueryMarginRepayRecordParams& params) const {
    return common::send<QueryMarginRepayRecordResponse>(*client_,
                                                        query_margin_repay_record_request(params));
}

common::RestRequest AccountApi::query_portfolio_margin_negative_balance_interest_history_request(
    const QueryPortfolioMarginNegativeBalanceInterestHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/portfolio/interest-history";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<
    std::vector<QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner>>
AccountApi::query_portfolio_margin_negative_balance_interest_history(
    const QueryPortfolioMarginNegativeBalanceInterestHistoryParams& params) const {
    return common::send<
        std::vector<QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner>>(
        *client_, query_portfolio_margin_negative_balance_interest_history_request(params));
}

common::RestRequest AccountApi::query_um_position_information_request(
    const QueryUmPositionInformationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/positionRisk";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryUmPositionInformationResponseInner>>
AccountApi::query_um_position_information(const QueryUmPositionInformationParams& params) const {
    return common::send<std::vector<QueryUmPositionInformationResponseInner>>(
        *client_, query_um_position_information_request(params));
}

common::RestRequest AccountApi::query_user_negative_balance_auto_exchange_record_request(
    const QueryUserNegativeBalanceAutoExchangeRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/portfolio/negative-balance-exchange-record";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryUserNegativeBalanceAutoExchangeRecordResponse>
AccountApi::query_user_negative_balance_auto_exchange_record(
    const QueryUserNegativeBalanceAutoExchangeRecordParams& params) const {
    return common::send<QueryUserNegativeBalanceAutoExchangeRecordResponse>(
        *client_, query_user_negative_balance_auto_exchange_record_request(params));
}

common::RestRequest
AccountApi::query_user_rate_limit_request(const QueryUserRateLimitParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/rateLimit/order";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryUserRateLimitResponseInner>>
AccountApi::query_user_rate_limit(const QueryUserRateLimitParams& params) const {
    return common::send<std::vector<QueryUserRateLimitResponseInner>>(
        *client_, query_user_rate_limit_request(params));
}

common::RestRequest AccountApi::repay_futures_negative_balance_request(
    const RepayFuturesNegativeBalanceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/repay-futures-negative-balance";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RepayFuturesNegativeBalanceResponse>
AccountApi::repay_futures_negative_balance(const RepayFuturesNegativeBalanceParams& params) const {
    return common::send<RepayFuturesNegativeBalanceResponse>(
        *client_, repay_futures_negative_balance_request(params));
}

common::RestRequest AccountApi::um_futures_account_configuration_request(
    const UmFuturesAccountConfigurationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/accountConfig";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<UmFuturesAccountConfigurationResponse>
AccountApi::um_futures_account_configuration(
    const UmFuturesAccountConfigurationParams& params) const {
    return common::send<UmFuturesAccountConfigurationResponse>(
        *client_, um_futures_account_configuration_request(params));
}

common::RestRequest AccountApi::um_futures_symbol_configuration_request(
    const UmFuturesSymbolConfigurationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/symbolConfig";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<UmFuturesSymbolConfigurationResponseInner>>
AccountApi::um_futures_symbol_configuration(
    const UmFuturesSymbolConfigurationParams& params) const {
    return common::send<std::vector<UmFuturesSymbolConfigurationResponseInner>>(
        *client_, um_futures_symbol_configuration_request(params));
}

common::RestRequest AccountApi::um_notional_and_leverage_brackets_request(
    const UmNotionalAndLeverageBracketsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/leverageBracket";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<UmNotionalAndLeverageBracketsResponseInner>>
AccountApi::um_notional_and_leverage_brackets(
    const UmNotionalAndLeverageBracketsParams& params) const {
    return common::send<std::vector<UmNotionalAndLeverageBracketsResponseInner>>(
        *client_, um_notional_and_leverage_brackets_request(params));
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
