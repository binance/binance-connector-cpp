//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/account_api.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetIncomeHistoryIncomeTypeEnum value) noexcept {
    switch (value) {
    case GetIncomeHistoryIncomeTypeEnum::Transfer:
        return "TRANSFER";
    case GetIncomeHistoryIncomeTypeEnum::WelcomeBonus:
        return "WELCOME_BONUS";
    case GetIncomeHistoryIncomeTypeEnum::RealizedPnl:
        return "REALIZED_PNL";
    case GetIncomeHistoryIncomeTypeEnum::FundingFee:
        return "FUNDING_FEE";
    case GetIncomeHistoryIncomeTypeEnum::Commission:
        return "COMMISSION";
    case GetIncomeHistoryIncomeTypeEnum::InsuranceClear:
        return "INSURANCE_CLEAR";
    case GetIncomeHistoryIncomeTypeEnum::ReferralKickback:
        return "REFERRAL_KICKBACK";
    case GetIncomeHistoryIncomeTypeEnum::CommissionRebate:
        return "COMMISSION_REBATE";
    case GetIncomeHistoryIncomeTypeEnum::ApiRebate:
        return "API_REBATE";
    case GetIncomeHistoryIncomeTypeEnum::ContestReward:
        return "CONTEST_REWARD";
    case GetIncomeHistoryIncomeTypeEnum::CrossCollateralTransfer:
        return "CROSS_COLLATERAL_TRANSFER";
    case GetIncomeHistoryIncomeTypeEnum::OptionsPremiumFee:
        return "OPTIONS_PREMIUM_FEE";
    case GetIncomeHistoryIncomeTypeEnum::OptionsSettleProfit:
        return "OPTIONS_SETTLE_PROFIT";
    case GetIncomeHistoryIncomeTypeEnum::InternalTransfer:
        return "INTERNAL_TRANSFER";
    case GetIncomeHistoryIncomeTypeEnum::AutoExchange:
        return "AUTO_EXCHANGE";
    case GetIncomeHistoryIncomeTypeEnum::DeliveredSettelment:
        return "DELIVERED_SETTELMENT";
    case GetIncomeHistoryIncomeTypeEnum::CoinSwapDeposit:
        return "COIN_SWAP_DEPOSIT";
    case GetIncomeHistoryIncomeTypeEnum::CoinSwapWithdraw:
        return "COIN_SWAP_WITHDRAW";
    case GetIncomeHistoryIncomeTypeEnum::PositionLimitIncreaseFee:
        return "POSITION_LIMIT_INCREASE_FEE";
    case GetIncomeHistoryIncomeTypeEnum::StrategyUmfuturesTransfer:
        return "STRATEGY_UMFUTURES_TRANSFER";
    case GetIncomeHistoryIncomeTypeEnum::FeeReturn:
        return "FEE_RETURN";
    case GetIncomeHistoryIncomeTypeEnum::BfusdReward:
        return "BFUSD_REWARD";
    case GetIncomeHistoryIncomeTypeEnum::SpecialFundingFee:
        return "SPECIAL_FUNDING_FEE";
    case GetIncomeHistoryIncomeTypeEnum::Unknown:
        break;
    }
    return "";
}

GetIncomeHistoryIncomeTypeEnum
tag_invoke(boost::json::value_to_tag<GetIncomeHistoryIncomeTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRANSFER") {
        return GetIncomeHistoryIncomeTypeEnum::Transfer;
    }
    if (s == "WELCOME_BONUS") {
        return GetIncomeHistoryIncomeTypeEnum::WelcomeBonus;
    }
    if (s == "REALIZED_PNL") {
        return GetIncomeHistoryIncomeTypeEnum::RealizedPnl;
    }
    if (s == "FUNDING_FEE") {
        return GetIncomeHistoryIncomeTypeEnum::FundingFee;
    }
    if (s == "COMMISSION") {
        return GetIncomeHistoryIncomeTypeEnum::Commission;
    }
    if (s == "INSURANCE_CLEAR") {
        return GetIncomeHistoryIncomeTypeEnum::InsuranceClear;
    }
    if (s == "REFERRAL_KICKBACK") {
        return GetIncomeHistoryIncomeTypeEnum::ReferralKickback;
    }
    if (s == "COMMISSION_REBATE") {
        return GetIncomeHistoryIncomeTypeEnum::CommissionRebate;
    }
    if (s == "API_REBATE") {
        return GetIncomeHistoryIncomeTypeEnum::ApiRebate;
    }
    if (s == "CONTEST_REWARD") {
        return GetIncomeHistoryIncomeTypeEnum::ContestReward;
    }
    if (s == "CROSS_COLLATERAL_TRANSFER") {
        return GetIncomeHistoryIncomeTypeEnum::CrossCollateralTransfer;
    }
    if (s == "OPTIONS_PREMIUM_FEE") {
        return GetIncomeHistoryIncomeTypeEnum::OptionsPremiumFee;
    }
    if (s == "OPTIONS_SETTLE_PROFIT") {
        return GetIncomeHistoryIncomeTypeEnum::OptionsSettleProfit;
    }
    if (s == "INTERNAL_TRANSFER") {
        return GetIncomeHistoryIncomeTypeEnum::InternalTransfer;
    }
    if (s == "AUTO_EXCHANGE") {
        return GetIncomeHistoryIncomeTypeEnum::AutoExchange;
    }
    if (s == "DELIVERED_SETTELMENT") {
        return GetIncomeHistoryIncomeTypeEnum::DeliveredSettelment;
    }
    if (s == "COIN_SWAP_DEPOSIT") {
        return GetIncomeHistoryIncomeTypeEnum::CoinSwapDeposit;
    }
    if (s == "COIN_SWAP_WITHDRAW") {
        return GetIncomeHistoryIncomeTypeEnum::CoinSwapWithdraw;
    }
    if (s == "POSITION_LIMIT_INCREASE_FEE") {
        return GetIncomeHistoryIncomeTypeEnum::PositionLimitIncreaseFee;
    }
    if (s == "STRATEGY_UMFUTURES_TRANSFER") {
        return GetIncomeHistoryIncomeTypeEnum::StrategyUmfuturesTransfer;
    }
    if (s == "FEE_RETURN") {
        return GetIncomeHistoryIncomeTypeEnum::FeeReturn;
    }
    if (s == "BFUSD_REWARD") {
        return GetIncomeHistoryIncomeTypeEnum::BfusdReward;
    }
    if (s == "SPECIAL_FUNDING_FEE") {
        return GetIncomeHistoryIncomeTypeEnum::SpecialFundingFee;
    }
    return GetIncomeHistoryIncomeTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetIncomeHistoryIncomeTypeEnum value) {
    if (value == GetIncomeHistoryIncomeTypeEnum::Unknown) {
        throw std::invalid_argument("GetIncomeHistoryIncomeTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

AccountApi::AccountApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
AccountApi::account_information_v2_request(const AccountInformationV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v2/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountInformationV2Response>
AccountApi::account_information_v2(const AccountInformationV2Params& params) const {
    return common::send<AccountInformationV2Response>(*client_,
                                                      account_information_v2_request(params));
}

common::RestRequest
AccountApi::account_information_v3_request(const AccountInformationV3Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v3/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountInformationV3Response>
AccountApi::account_information_v3(const AccountInformationV3Params& params) const {
    return common::send<AccountInformationV3Response>(*client_,
                                                      account_information_v3_request(params));
}

common::RestRequest
AccountApi::futures_account_balance_v2_request(const FuturesAccountBalanceV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v2/balance";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<FuturesAccountBalanceV2ResponseInner>>
AccountApi::futures_account_balance_v2(const FuturesAccountBalanceV2Params& params) const {
    return common::send<std::vector<FuturesAccountBalanceV2ResponseInner>>(
        *client_, futures_account_balance_v2_request(params));
}

common::RestRequest
AccountApi::futures_account_balance_v3_request(const FuturesAccountBalanceV3Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v3/balance";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<FuturesAccountBalanceV2ResponseInner>>
AccountApi::futures_account_balance_v3(const FuturesAccountBalanceV3Params& params) const {
    return common::send<std::vector<FuturesAccountBalanceV2ResponseInner>>(
        *client_, futures_account_balance_v3_request(params));
}

common::RestRequest AccountApi::futures_account_configuration_request(
    const FuturesAccountConfigurationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/accountConfig";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FuturesAccountConfigurationResponse>
AccountApi::futures_account_configuration(const FuturesAccountConfigurationParams& params) const {
    return common::send<FuturesAccountConfigurationResponse>(
        *client_, futures_account_configuration_request(params));
}

common::RestRequest AccountApi::futures_trading_quantitative_rules_indicators_request(
    const FuturesTradingQuantitativeRulesIndicatorsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/apiTradingStatus";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FuturesTradingQuantitativeRulesIndicatorsResponse>
AccountApi::futures_trading_quantitative_rules_indicators(
    const FuturesTradingQuantitativeRulesIndicatorsParams& params) const {
    return common::send<FuturesTradingQuantitativeRulesIndicatorsResponse>(
        *client_, futures_trading_quantitative_rules_indicators_request(params));
}

common::RestRequest
AccountApi::get_bnb_burn_status_request(const GetBnbBurnStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/feeBurn";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBnbBurnStatusResponse>
AccountApi::get_bnb_burn_status(const GetBnbBurnStatusParams& params) const {
    return common::send<GetBnbBurnStatusResponse>(*client_, get_bnb_burn_status_request(params));
}

common::RestRequest AccountApi::toggle_bnb_burn_on_futures_trade_request(
    const ToggleBnbBurnOnFuturesTradeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/feeBurn";
    common::detail::json::set_param(req.query, "feeBurn", params.fee_burn);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ToggleBnbBurnOnFuturesTradeResponse>
AccountApi::toggle_bnb_burn_on_futures_trade(
    const ToggleBnbBurnOnFuturesTradeParams& params) const {
    return common::send<ToggleBnbBurnOnFuturesTradeResponse>(
        *client_, toggle_bnb_burn_on_futures_trade_request(params));
}

common::RestRequest AccountApi::get_current_multi_assets_mode_request(
    const GetCurrentMultiAssetsModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/multiAssetsMargin";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCurrentMultiAssetsModeResponse>
AccountApi::get_current_multi_assets_mode(const GetCurrentMultiAssetsModeParams& params) const {
    return common::send<GetCurrentMultiAssetsModeResponse>(
        *client_, get_current_multi_assets_mode_request(params));
}

common::RestRequest
AccountApi::get_current_position_mode_request(const GetCurrentPositionModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/positionSide/dual";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCurrentPositionModeResponse>
AccountApi::get_current_position_mode(const GetCurrentPositionModeParams& params) const {
    return common::send<GetCurrentPositionModeResponse>(*client_,
                                                        get_current_position_mode_request(params));
}

common::RestRequest AccountApi::get_download_id_for_futures_order_history_request(
    const GetDownloadIdForFuturesOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/order/asyn";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDownloadIdForFuturesOrderHistoryResponse>
AccountApi::get_download_id_for_futures_order_history(
    const GetDownloadIdForFuturesOrderHistoryParams& params) const {
    return common::send<GetDownloadIdForFuturesOrderHistoryResponse>(
        *client_, get_download_id_for_futures_order_history_request(params));
}

common::RestRequest AccountApi::get_download_id_for_futures_trade_history_request(
    const GetDownloadIdForFuturesTradeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/trade/asyn";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDownloadIdForFuturesTradeHistoryResponse>
AccountApi::get_download_id_for_futures_trade_history(
    const GetDownloadIdForFuturesTradeHistoryParams& params) const {
    return common::send<GetDownloadIdForFuturesTradeHistoryResponse>(
        *client_, get_download_id_for_futures_trade_history_request(params));
}

common::RestRequest AccountApi::get_download_id_for_futures_transaction_history_request(
    const GetDownloadIdForFuturesTransactionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/income/asyn";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDownloadIdForFuturesTransactionHistoryResponse>
AccountApi::get_download_id_for_futures_transaction_history(
    const GetDownloadIdForFuturesTransactionHistoryParams& params) const {
    return common::send<GetDownloadIdForFuturesTransactionHistoryResponse>(
        *client_, get_download_id_for_futures_transaction_history_request(params));
}

common::RestRequest AccountApi::get_futures_order_history_download_link_by_id_request(
    const GetFuturesOrderHistoryDownloadLinkByIdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/order/asyn/id";
    common::detail::json::set_param(req.query, "downloadId", params.download_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFuturesOrderHistoryDownloadLinkByIdResponse>
AccountApi::get_futures_order_history_download_link_by_id(
    const GetFuturesOrderHistoryDownloadLinkByIdParams& params) const {
    return common::send<GetFuturesOrderHistoryDownloadLinkByIdResponse>(
        *client_, get_futures_order_history_download_link_by_id_request(params));
}

common::RestRequest AccountApi::get_futures_trade_download_link_by_id_request(
    const GetFuturesTradeDownloadLinkByIdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/trade/asyn/id";
    common::detail::json::set_param(req.query, "downloadId", params.download_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFuturesTradeDownloadLinkByIdResponse>
AccountApi::get_futures_trade_download_link_by_id(
    const GetFuturesTradeDownloadLinkByIdParams& params) const {
    return common::send<GetFuturesTradeDownloadLinkByIdResponse>(
        *client_, get_futures_trade_download_link_by_id_request(params));
}

common::RestRequest AccountApi::get_futures_transaction_history_download_link_by_id_request(
    const GetFuturesTransactionHistoryDownloadLinkByIdParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/income/asyn/id";
    common::detail::json::set_param(req.query, "downloadId", params.download_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFuturesTransactionHistoryDownloadLinkByIdResponse>
AccountApi::get_futures_transaction_history_download_link_by_id(
    const GetFuturesTransactionHistoryDownloadLinkByIdParams& params) const {
    return common::send<GetFuturesTransactionHistoryDownloadLinkByIdResponse>(
        *client_, get_futures_transaction_history_download_link_by_id_request(params));
}

common::RestRequest
AccountApi::get_income_history_request(const GetIncomeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/income";
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

common::RestApiResponse<std::vector<GetIncomeHistoryResponseInner>>
AccountApi::get_income_history(const GetIncomeHistoryParams& params) const {
    return common::send<std::vector<GetIncomeHistoryResponseInner>>(
        *client_, get_income_history_request(params));
}

common::RestRequest AccountApi::notional_and_leverage_brackets_request(
    const NotionalAndLeverageBracketsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/leverageBracket";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<NotionalAndLeverageBracketsResponse>
AccountApi::notional_and_leverage_brackets(const NotionalAndLeverageBracketsParams& params) const {
    return common::send<NotionalAndLeverageBracketsResponse>(
        *client_, notional_and_leverage_brackets_request(params));
}

common::RestRequest
AccountApi::query_user_rate_limit_request(const QueryUserRateLimitParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/rateLimit/order";
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

common::RestRequest
AccountApi::symbol_configuration_request(const SymbolConfigurationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/symbolConfig";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<SymbolConfigurationResponseInner>>
AccountApi::symbol_configuration(const SymbolConfigurationParams& params) const {
    return common::send<std::vector<SymbolConfigurationResponseInner>>(
        *client_, symbol_configuration_request(params));
}

common::RestRequest
AccountApi::user_commission_rate_request(const UserCommissionRateParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/commissionRate";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<UserCommissionRateResponse>
AccountApi::user_commission_rate(const UserCommissionRateParams& params) const {
    return common::send<UserCommissionRateResponse>(*client_, user_commission_rate_request(params));
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
