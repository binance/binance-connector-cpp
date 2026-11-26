//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/account_api.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

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

std::string_view to_string(SwitchDeltaModeDeltaEnabledEnum value) noexcept {
    switch (value) {
    case SwitchDeltaModeDeltaEnabledEnum::True_:
        return "true";
    case SwitchDeltaModeDeltaEnabledEnum::False_:
        return "false";
    case SwitchDeltaModeDeltaEnabledEnum::Unknown:
        break;
    }
    return "";
}

SwitchDeltaModeDeltaEnabledEnum
tag_invoke(boost::json::value_to_tag<SwitchDeltaModeDeltaEnabledEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return SwitchDeltaModeDeltaEnabledEnum::True_;
    }
    if (s == "false") {
        return SwitchDeltaModeDeltaEnabledEnum::False_;
    }
    return SwitchDeltaModeDeltaEnabledEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SwitchDeltaModeDeltaEnabledEnum value) {
    if (value == SwitchDeltaModeDeltaEnabledEnum::Unknown) {
        throw std::invalid_argument("SwitchDeltaModeDeltaEnabledEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum value) noexcept {
    switch (value) {
    case GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::EarnToFuture:
        return "EARN_TO_FUTURE";
    case GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::FutureToEarn:
        return "FUTURE_TO_EARN";
    case GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::Unknown:
        break;
    }
    return "";
}

GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum
tag_invoke(boost::json::value_to_tag<
               GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "EARN_TO_FUTURE") {
        return GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::EarnToFuture;
    }
    if (s == "FUTURE_TO_EARN") {
        return GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::FutureToEarn;
    }
    return GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum value) {
    if (value == GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::Unknown) {
        throw std::invalid_argument("GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeE"
                                    "num::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TransferLdusdtRwusdForPortfolioMarginAssetEnum value) noexcept {
    switch (value) {
    case TransferLdusdtRwusdForPortfolioMarginAssetEnum::Ldusdt:
        return "LDUSDT";
    case TransferLdusdtRwusdForPortfolioMarginAssetEnum::Rwusd:
        return "RWUSD";
    case TransferLdusdtRwusdForPortfolioMarginAssetEnum::Unknown:
        break;
    }
    return "";
}

TransferLdusdtRwusdForPortfolioMarginAssetEnum
tag_invoke(boost::json::value_to_tag<TransferLdusdtRwusdForPortfolioMarginAssetEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LDUSDT") {
        return TransferLdusdtRwusdForPortfolioMarginAssetEnum::Ldusdt;
    }
    if (s == "RWUSD") {
        return TransferLdusdtRwusdForPortfolioMarginAssetEnum::Rwusd;
    }
    return TransferLdusdtRwusdForPortfolioMarginAssetEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TransferLdusdtRwusdForPortfolioMarginAssetEnum value) {
    if (value == TransferLdusdtRwusdForPortfolioMarginAssetEnum::Unknown) {
        throw std::invalid_argument(
            "TransferLdusdtRwusdForPortfolioMarginAssetEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum value) noexcept {
    switch (value) {
    case TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::EarnToFuture:
        return "EARN_TO_FUTURE";
    case TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::FutureToEarn:
        return "FUTURE_TO_EARN";
    case TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::Unknown:
        break;
    }
    return "";
}

TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum
tag_invoke(boost::json::value_to_tag<TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "EARN_TO_FUTURE") {
        return TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::EarnToFuture;
    }
    if (s == "FUTURE_TO_EARN") {
        return TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::FutureToEarn;
    }
    return TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum value) {
    if (value == TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::Unknown) {
        throw std::invalid_argument(
            "TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

AccountApi::AccountApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest AccountApi::bnb_transfer_request(const BnbTransferParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/portfolio/bnb-transfer";
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
    req.endpoint = "/sapi/v1/portfolio/repay-futures-switch";
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
    req.endpoint = "/sapi/v1/portfolio/repay-futures-switch";
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
AccountApi::delete_margin_call_level_request(const DeleteMarginCallLevelParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/portfolio/margin-call-level";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DeleteMarginCallLevelResponse>
AccountApi::delete_margin_call_level(const DeleteMarginCallLevelParams& params) const {
    return common::send<DeleteMarginCallLevelResponse>(*client_,
                                                       delete_margin_call_level_request(params));
}

common::RestRequest
AccountApi::get_margin_call_level_request(const GetMarginCallLevelParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/margin-call-level";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetMarginCallLevelResponse>
AccountApi::get_margin_call_level(const GetMarginCallLevelParams& params) const {
    return common::send<GetMarginCallLevelResponse>(*client_,
                                                    get_margin_call_level_request(params));
}

common::RestRequest
AccountApi::set_margin_call_level_request(const SetMarginCallLevelParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/portfolio/margin-call-level";
    common::detail::json::set_param(req.query, "marginCallLevel", params.margin_call_level);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SetMarginCallLevelResponse>
AccountApi::set_margin_call_level(const SetMarginCallLevelParams& params) const {
    return common::send<SetMarginCallLevelResponse>(*client_,
                                                    set_margin_call_level_request(params));
}

common::RestRequest
AccountApi::fund_auto_collection_request(const FundAutoCollectionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/portfolio/auto-collection";
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
    req.endpoint = "/sapi/v1/portfolio/asset-collection";
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
AccountApi::get_delta_mode_status_request(const GetDeltaModeStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/delta-mode";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDeltaModeStatusResponse>
AccountApi::get_delta_mode_status(const GetDeltaModeStatusParams& params) const {
    return common::send<GetDeltaModeStatusResponse>(*client_,
                                                    get_delta_mode_status_request(params));
}

common::RestRequest
AccountApi::switch_delta_mode_request(const SwitchDeltaModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/portfolio/delta-mode";
    common::detail::json::set_param(req.query, "deltaEnabled", params.delta_enabled);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SwitchDeltaModeResponse>
AccountApi::switch_delta_mode(const SwitchDeltaModeParams& params) const {
    return common::send<SwitchDeltaModeResponse>(*client_, switch_delta_mode_request(params));
}

common::RestRequest AccountApi::get_portfolio_margin_pro_account_balance_request(
    const GetPortfolioMarginProAccountBalanceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/balance";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetPortfolioMarginProAccountBalanceResponseInner>>
AccountApi::get_portfolio_margin_pro_account_balance(
    const GetPortfolioMarginProAccountBalanceParams& params) const {
    return common::send<std::vector<GetPortfolioMarginProAccountBalanceResponseInner>>(
        *client_, get_portfolio_margin_pro_account_balance_request(params));
}

common::RestRequest AccountApi::get_portfolio_margin_pro_account_info_request(
    const GetPortfolioMarginProAccountInfoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetPortfolioMarginProAccountInfoResponse>
AccountApi::get_portfolio_margin_pro_account_info(
    const GetPortfolioMarginProAccountInfoParams& params) const {
    return common::send<GetPortfolioMarginProAccountInfoResponse>(
        *client_, get_portfolio_margin_pro_account_info_request(params));
}

common::RestRequest AccountApi::get_portfolio_margin_pro_span_account_info_request(
    const GetPortfolioMarginProSpanAccountInfoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/portfolio/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetPortfolioMarginProSpanAccountInfoResponse>
AccountApi::get_portfolio_margin_pro_span_account_info(
    const GetPortfolioMarginProSpanAccountInfoParams& params) const {
    return common::send<GetPortfolioMarginProSpanAccountInfoResponse>(
        *client_, get_portfolio_margin_pro_span_account_info_request(params));
}

common::RestRequest AccountApi::get_transferable_earn_asset_balance_for_portfolio_margin_request(
    const GetTransferableEarnAssetBalanceForPortfolioMarginParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/earn-asset-balance";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "transferType", params.transfer_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetTransferableEarnAssetBalanceForPortfolioMarginResponse>
AccountApi::get_transferable_earn_asset_balance_for_portfolio_margin(
    const GetTransferableEarnAssetBalanceForPortfolioMarginParams& params) const {
    return common::send<GetTransferableEarnAssetBalanceForPortfolioMarginResponse>(
        *client_, get_transferable_earn_asset_balance_for_portfolio_margin_request(params));
}

common::RestRequest AccountApi::portfolio_margin_pro_bankruptcy_loan_repay_request(
    const PortfolioMarginProBankruptcyLoanRepayParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/portfolio/repay";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<PortfolioMarginProBankruptcyLoanRepayResponse>
AccountApi::portfolio_margin_pro_bankruptcy_loan_repay(
    const PortfolioMarginProBankruptcyLoanRepayParams& params) const {
    return common::send<PortfolioMarginProBankruptcyLoanRepayResponse>(
        *client_, portfolio_margin_pro_bankruptcy_loan_repay_request(params));
}

common::RestRequest AccountApi::query_portfolio_margin_pro_bankruptcy_loan_amount_request(
    const QueryPortfolioMarginProBankruptcyLoanAmountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/pmLoan";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryPortfolioMarginProBankruptcyLoanAmountResponse>
AccountApi::query_portfolio_margin_pro_bankruptcy_loan_amount(
    const QueryPortfolioMarginProBankruptcyLoanAmountParams& params) const {
    return common::send<QueryPortfolioMarginProBankruptcyLoanAmountResponse>(
        *client_, query_portfolio_margin_pro_bankruptcy_loan_amount_request(params));
}

common::RestRequest AccountApi::query_portfolio_margin_pro_bankruptcy_loan_repay_history_request(
    const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/pmloan-history";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse>
AccountApi::query_portfolio_margin_pro_bankruptcy_loan_repay_history(
    const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams& params) const {
    return common::send<QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse>(
        *client_, query_portfolio_margin_pro_bankruptcy_loan_repay_history_request(params));
}

common::RestRequest
AccountApi::query_portfolio_margin_pro_negative_balance_interest_history_request(
    const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/interest-history";
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
    std::vector<QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner>>
AccountApi::query_portfolio_margin_pro_negative_balance_interest_history(
    const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams& params) const {
    return common::send<
        std::vector<QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner>>(
        *client_, query_portfolio_margin_pro_negative_balance_interest_history_request(params));
}

common::RestRequest AccountApi::repay_futures_negative_balance_request(
    const RepayFuturesNegativeBalanceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/portfolio/repay-futures-negative-balance";
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

common::RestRequest AccountApi::transfer_ldusdt_rwusd_for_portfolio_margin_request(
    const TransferLdusdtRwusdForPortfolioMarginParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/portfolio/earn-asset-transfer";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "transferType", params.transfer_type);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TransferLdusdtRwusdForPortfolioMarginResponse>
AccountApi::transfer_ldusdt_rwusd_for_portfolio_margin(
    const TransferLdusdtRwusdForPortfolioMarginParams& params) const {
    return common::send<TransferLdusdtRwusdForPortfolioMarginResponse>(
        *client_, transfer_ldusdt_rwusd_for_portfolio_margin_request(params));
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
