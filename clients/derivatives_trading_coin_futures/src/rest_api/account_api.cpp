//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/account_api.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetIncomeHistoryIncomeTypeEnum value) noexcept {
    switch (value) {
    case GetIncomeHistoryIncomeTypeEnum::Transfer:
        return "TRANSFER";
    case GetIncomeHistoryIncomeTypeEnum::WelcomeBonus:
        return "WELCOME_BONUS";
    case GetIncomeHistoryIncomeTypeEnum::FundingFee:
        return "FUNDING_FEE";
    case GetIncomeHistoryIncomeTypeEnum::RealizedPnl:
        return "REALIZED_PNL";
    case GetIncomeHistoryIncomeTypeEnum::Commission:
        return "COMMISSION";
    case GetIncomeHistoryIncomeTypeEnum::InsuranceClear:
        return "INSURANCE_CLEAR";
    case GetIncomeHistoryIncomeTypeEnum::DeliveredSettelment:
        return "DELIVERED_SETTELMENT";
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
    if (s == "FUNDING_FEE") {
        return GetIncomeHistoryIncomeTypeEnum::FundingFee;
    }
    if (s == "REALIZED_PNL") {
        return GetIncomeHistoryIncomeTypeEnum::RealizedPnl;
    }
    if (s == "COMMISSION") {
        return GetIncomeHistoryIncomeTypeEnum::Commission;
    }
    if (s == "INSURANCE_CLEAR") {
        return GetIncomeHistoryIncomeTypeEnum::InsuranceClear;
    }
    if (s == "DELIVERED_SETTELMENT") {
        return GetIncomeHistoryIncomeTypeEnum::DeliveredSettelment;
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
AccountApi::account_information_request(const AccountInformationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AccountInformationResponse>
AccountApi::account_information(const AccountInformationParams& params) const {
    return common::send<AccountInformationResponse>(*client_, account_information_request(params));
}

common::RestRequest
AccountApi::futures_account_balance_request(const FuturesAccountBalanceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/balance";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<FuturesAccountBalanceResponseInner>>
AccountApi::futures_account_balance(const FuturesAccountBalanceParams& params) const {
    return common::send<std::vector<FuturesAccountBalanceResponseInner>>(
        *client_, futures_account_balance_request(params));
}

common::RestRequest
AccountApi::get_current_position_mode_request(const GetCurrentPositionModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/positionSide/dual";
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
    req.endpoint = "/dapi/v1/order/asyn";
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
    req.endpoint = "/dapi/v1/trade/asyn";
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
    req.endpoint = "/dapi/v1/income/asyn";
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
    req.endpoint = "/dapi/v1/order/asyn/id";
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
    req.endpoint = "/dapi/v1/trade/asyn/id";
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
    req.endpoint = "/dapi/v1/income/asyn/id";
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
    req.endpoint = "/dapi/v1/income";
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

common::RestRequest
AccountApi::notional_bracket_for_pair_request(const NotionalBracketForPairParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/leverageBracket";
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<NotionalBracketForPairResponseInner>>
AccountApi::notional_bracket_for_pair(const NotionalBracketForPairParams& params) const {
    return common::send<std::vector<NotionalBracketForPairResponseInner>>(
        *client_, notional_bracket_for_pair_request(params));
}

common::RestRequest AccountApi::notional_bracket_for_symbol_request(
    const NotionalBracketForSymbolParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v2/leverageBracket";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<NotionalBracketForSymbolResponseInner>>
AccountApi::notional_bracket_for_symbol(const NotionalBracketForSymbolParams& params) const {
    return common::send<std::vector<NotionalBracketForSymbolResponseInner>>(
        *client_, notional_bracket_for_symbol_request(params));
}

common::RestRequest
AccountApi::user_commission_rate_request(const UserCommissionRateParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/commissionRate";
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

} // namespace binance::derivatives_trading_coin_futures::rest_api
