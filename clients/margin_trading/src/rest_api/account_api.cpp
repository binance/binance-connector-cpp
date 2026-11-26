//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/account_api.hpp>

namespace binance::margin_trading::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(QueryCrossIsolatedMarginCapitalFlowTypeEnum value) noexcept {
    switch (value) {
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::Transfer:
        return "TRANSFER";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::Borrow:
        return "BORROW";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::Repay:
        return "REPAY";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::BuyIncome:
        return "BUY_INCOME";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::BuyExpense:
        return "BUY_EXPENSE";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::SellIncome:
        return "SELL_INCOME";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::SellExpense:
        return "SELL_EXPENSE";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::TradingCommission:
        return "TRADING_COMMISSION";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::BuyLiquidation:
        return "BUY_LIQUIDATION";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::SellLiquidation:
        return "SELL_LIQUIDATION";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::RepayLiquidation:
        return "REPAY_LIQUIDATION";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::OtherLiquidation:
        return "OTHER_LIQUIDATION";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::LiquidationFee:
        return "LIQUIDATION_FEE";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::SmallBalanceConvert:
        return "SMALL_BALANCE_CONVERT";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::CommissionReturn:
        return "COMMISSION_RETURN";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::SmallConvert:
        return "SMALL_CONVERT";
    case QueryCrossIsolatedMarginCapitalFlowTypeEnum::Unknown:
        break;
    }
    return "";
}

QueryCrossIsolatedMarginCapitalFlowTypeEnum
tag_invoke(boost::json::value_to_tag<QueryCrossIsolatedMarginCapitalFlowTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRANSFER") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::Transfer;
    }
    if (s == "BORROW") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::Borrow;
    }
    if (s == "REPAY") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::Repay;
    }
    if (s == "BUY_INCOME") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::BuyIncome;
    }
    if (s == "BUY_EXPENSE") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::BuyExpense;
    }
    if (s == "SELL_INCOME") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::SellIncome;
    }
    if (s == "SELL_EXPENSE") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::SellExpense;
    }
    if (s == "TRADING_COMMISSION") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::TradingCommission;
    }
    if (s == "BUY_LIQUIDATION") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::BuyLiquidation;
    }
    if (s == "SELL_LIQUIDATION") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::SellLiquidation;
    }
    if (s == "REPAY_LIQUIDATION") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::RepayLiquidation;
    }
    if (s == "OTHER_LIQUIDATION") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::OtherLiquidation;
    }
    if (s == "LIQUIDATION_FEE") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::LiquidationFee;
    }
    if (s == "SMALL_BALANCE_CONVERT") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::SmallBalanceConvert;
    }
    if (s == "COMMISSION_RETURN") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::CommissionReturn;
    }
    if (s == "SMALL_CONVERT") {
        return QueryCrossIsolatedMarginCapitalFlowTypeEnum::SmallConvert;
    }
    return QueryCrossIsolatedMarginCapitalFlowTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryCrossIsolatedMarginCapitalFlowTypeEnum value) {
    if (value == QueryCrossIsolatedMarginCapitalFlowTypeEnum::Unknown) {
        throw std::invalid_argument(
            "QueryCrossIsolatedMarginCapitalFlowTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

AccountApi::AccountApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest AccountApi::adjust_cross_margin_max_leverage_request(
    const AdjustCrossMarginMaxLeverageParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/max-leverage";
    common::detail::json::set_param(req.query, "maxLeverage", params.max_leverage);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AdjustCrossMarginMaxLeverageResponse>
AccountApi::adjust_cross_margin_max_leverage(
    const AdjustCrossMarginMaxLeverageParams& params) const {
    return common::send<AdjustCrossMarginMaxLeverageResponse>(
        *client_, adjust_cross_margin_max_leverage_request(params));
}

common::RestRequest AccountApi::disable_isolated_margin_account_request(
    const DisableIsolatedMarginAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/margin/isolated/account";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DisableIsolatedMarginAccountResponse>
AccountApi::disable_isolated_margin_account(
    const DisableIsolatedMarginAccountParams& params) const {
    return common::send<DisableIsolatedMarginAccountResponse>(
        *client_, disable_isolated_margin_account_request(params));
}

common::RestRequest AccountApi::enable_isolated_margin_account_request(
    const EnableIsolatedMarginAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/isolated/account";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<EnableIsolatedMarginAccountResponse>
AccountApi::enable_isolated_margin_account(const EnableIsolatedMarginAccountParams& params) const {
    return common::send<EnableIsolatedMarginAccountResponse>(
        *client_, enable_isolated_margin_account_request(params));
}

common::RestRequest AccountApi::query_isolated_margin_account_info_request(
    const QueryIsolatedMarginAccountInfoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/isolated/account";
    common::detail::json::set_param(req.query, "symbols", params.symbols);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryIsolatedMarginAccountInfoResponse>
AccountApi::query_isolated_margin_account_info(
    const QueryIsolatedMarginAccountInfoParams& params) const {
    return common::send<QueryIsolatedMarginAccountInfoResponse>(
        *client_, query_isolated_margin_account_info_request(params));
}

common::RestRequest
AccountApi::get_bnb_burn_status_request(const GetBnbBurnStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/bnbBurn";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetBnbBurnStatusResponse>
AccountApi::get_bnb_burn_status(const GetBnbBurnStatusParams& params) const {
    return common::send<GetBnbBurnStatusResponse>(*client_, get_bnb_burn_status_request(params));
}

common::RestRequest AccountApi::get_summary_of_margin_account_request(
    const GetSummaryOfMarginAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/tradeCoeff";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSummaryOfMarginAccountResponse>
AccountApi::get_summary_of_margin_account(const GetSummaryOfMarginAccountParams& params) const {
    return common::send<GetSummaryOfMarginAccountResponse>(
        *client_, get_summary_of_margin_account_request(params));
}

common::RestRequest AccountApi::query_cross_isolated_margin_capital_flow_request(
    const QueryCrossIsolatedMarginCapitalFlowParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/capital-flow";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryCrossIsolatedMarginCapitalFlowResponseInner>>
AccountApi::query_cross_isolated_margin_capital_flow(
    const QueryCrossIsolatedMarginCapitalFlowParams& params) const {
    return common::send<std::vector<QueryCrossIsolatedMarginCapitalFlowResponseInner>>(
        *client_, query_cross_isolated_margin_capital_flow_request(params));
}

common::RestRequest AccountApi::query_cross_margin_account_details_request(
    const QueryCrossMarginAccountDetailsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/account";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCrossMarginAccountDetailsResponse>
AccountApi::query_cross_margin_account_details(
    const QueryCrossMarginAccountDetailsParams& params) const {
    return common::send<QueryCrossMarginAccountDetailsResponse>(
        *client_, query_cross_margin_account_details_request(params));
}

common::RestRequest
AccountApi::query_cross_margin_fee_data_request(const QueryCrossMarginFeeDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/crossMarginData";
    common::detail::json::set_param(req.query, "vipLevel", params.vip_level);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryCrossMarginFeeDataResponseInner>>
AccountApi::query_cross_margin_fee_data(const QueryCrossMarginFeeDataParams& params) const {
    return common::send<std::vector<QueryCrossMarginFeeDataResponseInner>>(
        *client_, query_cross_margin_fee_data_request(params));
}

common::RestRequest AccountApi::query_enabled_isolated_margin_account_limit_request(
    const QueryEnabledIsolatedMarginAccountLimitParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/isolated/accountLimit";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryEnabledIsolatedMarginAccountLimitResponse>
AccountApi::query_enabled_isolated_margin_account_limit(
    const QueryEnabledIsolatedMarginAccountLimitParams& params) const {
    return common::send<QueryEnabledIsolatedMarginAccountLimitResponse>(
        *client_, query_enabled_isolated_margin_account_limit_request(params));
}

common::RestRequest AccountApi::query_isolated_margin_fee_data_request(
    const QueryIsolatedMarginFeeDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/isolatedMarginData";
    common::detail::json::set_param(req.query, "vipLevel", params.vip_level);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryIsolatedMarginFeeDataResponseInner>>
AccountApi::query_isolated_margin_fee_data(const QueryIsolatedMarginFeeDataParams& params) const {
    return common::send<std::vector<QueryIsolatedMarginFeeDataResponseInner>>(
        *client_, query_isolated_margin_fee_data_request(params));
}

} // namespace binance::margin_trading::rest_api
