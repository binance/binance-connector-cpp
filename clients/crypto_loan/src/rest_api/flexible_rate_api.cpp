//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/flexible_rate_api.hpp>

namespace binance::crypto_loan::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(FlexibleLoanAdjustLtvDirectionEnum value) noexcept {
    switch (value) {
    case FlexibleLoanAdjustLtvDirectionEnum::Additional:
        return "ADDITIONAL";
    case FlexibleLoanAdjustLtvDirectionEnum::Reduced:
        return "REDUCED";
    case FlexibleLoanAdjustLtvDirectionEnum::Unknown:
        break;
    }
    return "";
}

FlexibleLoanAdjustLtvDirectionEnum
tag_invoke(boost::json::value_to_tag<FlexibleLoanAdjustLtvDirectionEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ADDITIONAL") {
        return FlexibleLoanAdjustLtvDirectionEnum::Additional;
    }
    if (s == "REDUCED") {
        return FlexibleLoanAdjustLtvDirectionEnum::Reduced;
    }
    return FlexibleLoanAdjustLtvDirectionEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                FlexibleLoanAdjustLtvDirectionEnum value) {
    if (value == FlexibleLoanAdjustLtvDirectionEnum::Unknown) {
        throw std::invalid_argument("FlexibleLoanAdjustLtvDirectionEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(FlexibleLoanRepayRepaymentTypeEnum value) noexcept {
    switch (value) {
    case FlexibleLoanRepayRepaymentTypeEnum::RepaymentType1:
        return "1";
    case FlexibleLoanRepayRepaymentTypeEnum::RepaymentType2:
        return "2";
    case FlexibleLoanRepayRepaymentTypeEnum::Unknown:
        break;
    }
    return "";
}

FlexibleLoanRepayRepaymentTypeEnum
tag_invoke(boost::json::value_to_tag<FlexibleLoanRepayRepaymentTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1") {
        return FlexibleLoanRepayRepaymentTypeEnum::RepaymentType1;
    }
    if (s == "2") {
        return FlexibleLoanRepayRepaymentTypeEnum::RepaymentType2;
    }
    return FlexibleLoanRepayRepaymentTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                FlexibleLoanRepayRepaymentTypeEnum value) {
    if (value == FlexibleLoanRepayRepaymentTypeEnum::Unknown) {
        throw std::invalid_argument("FlexibleLoanRepayRepaymentTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

FlexibleRateApi::FlexibleRateApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest FlexibleRateApi::check_collateral_repay_rate_request(
    const CheckCollateralRepayRateParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/loan/flexible/repay/rate";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CheckCollateralRepayRateResponse>
FlexibleRateApi::check_collateral_repay_rate(const CheckCollateralRepayRateParams& params) const {
    return common::send<CheckCollateralRepayRateResponse>(
        *client_, check_collateral_repay_rate_request(params));
}

common::RestRequest
FlexibleRateApi::flexible_loan_adjust_ltv_request(const FlexibleLoanAdjustLtvParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v2/loan/flexible/adjust/ltv";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "adjustmentAmount", params.adjustment_amount);
    common::detail::json::set_param(req.query, "direction", params.direction);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FlexibleLoanAdjustLtvResponse>
FlexibleRateApi::flexible_loan_adjust_ltv(const FlexibleLoanAdjustLtvParams& params) const {
    return common::send<FlexibleLoanAdjustLtvResponse>(*client_,
                                                       flexible_loan_adjust_ltv_request(params));
}

common::RestRequest
FlexibleRateApi::flexible_loan_borrow_request(const FlexibleLoanBorrowParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v2/loan/flexible/borrow";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "loanAmount", params.loan_amount);
    common::detail::json::set_param(req.query, "collateralAmount", params.collateral_amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FlexibleLoanBorrowResponse>
FlexibleRateApi::flexible_loan_borrow(const FlexibleLoanBorrowParams& params) const {
    return common::send<FlexibleLoanBorrowResponse>(*client_, flexible_loan_borrow_request(params));
}

common::RestRequest
FlexibleRateApi::flexible_loan_repay_request(const FlexibleLoanRepayParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v2/loan/flexible/repay";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "repayAmount", params.repay_amount);
    common::detail::json::set_param(req.query, "collateralReturn", params.collateral_return);
    common::detail::json::set_param(req.query, "fullRepayment", params.full_repayment);
    common::detail::json::set_param(req.query, "repaymentType", params.repayment_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FlexibleLoanRepayResponse>
FlexibleRateApi::flexible_loan_repay(const FlexibleLoanRepayParams& params) const {
    return common::send<FlexibleLoanRepayResponse>(*client_, flexible_loan_repay_request(params));
}

common::RestRequest FlexibleRateApi::get_flexible_loan_assets_data_request(
    const GetFlexibleLoanAssetsDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/loan/flexible/loanable/data";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleLoanAssetsDataResponse>
FlexibleRateApi::get_flexible_loan_assets_data(
    const GetFlexibleLoanAssetsDataParams& params) const {
    return common::send<GetFlexibleLoanAssetsDataResponse>(
        *client_, get_flexible_loan_assets_data_request(params));
}

common::RestRequest FlexibleRateApi::get_flexible_loan_borrow_history_request(
    const GetFlexibleLoanBorrowHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/loan/flexible/borrow/history";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleLoanBorrowHistoryResponse>
FlexibleRateApi::get_flexible_loan_borrow_history(
    const GetFlexibleLoanBorrowHistoryParams& params) const {
    return common::send<GetFlexibleLoanBorrowHistoryResponse>(
        *client_, get_flexible_loan_borrow_history_request(params));
}

common::RestRequest FlexibleRateApi::get_flexible_loan_collateral_assets_data_request(
    const GetFlexibleLoanCollateralAssetsDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/loan/flexible/collateral/data";
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleLoanCollateralAssetsDataResponse>
FlexibleRateApi::get_flexible_loan_collateral_assets_data(
    const GetFlexibleLoanCollateralAssetsDataParams& params) const {
    return common::send<GetFlexibleLoanCollateralAssetsDataResponse>(
        *client_, get_flexible_loan_collateral_assets_data_request(params));
}

common::RestRequest FlexibleRateApi::get_flexible_loan_interest_rate_history_request(
    const GetFlexibleLoanInterestRateHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/loan/interestRateHistory";
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleLoanInterestRateHistoryResponse>
FlexibleRateApi::get_flexible_loan_interest_rate_history(
    const GetFlexibleLoanInterestRateHistoryParams& params) const {
    return common::send<GetFlexibleLoanInterestRateHistoryResponse>(
        *client_, get_flexible_loan_interest_rate_history_request(params));
}

common::RestRequest FlexibleRateApi::get_flexible_loan_liquidation_history_request(
    const GetFlexibleLoanLiquidationHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/loan/flexible/liquidation/history";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleLoanLiquidationHistoryResponse>
FlexibleRateApi::get_flexible_loan_liquidation_history(
    const GetFlexibleLoanLiquidationHistoryParams& params) const {
    return common::send<GetFlexibleLoanLiquidationHistoryResponse>(
        *client_, get_flexible_loan_liquidation_history_request(params));
}

common::RestRequest FlexibleRateApi::get_flexible_loan_ltv_adjustment_history_request(
    const GetFlexibleLoanLtvAdjustmentHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/loan/flexible/ltv/adjustment/history";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleLoanLtvAdjustmentHistoryResponse>
FlexibleRateApi::get_flexible_loan_ltv_adjustment_history(
    const GetFlexibleLoanLtvAdjustmentHistoryParams& params) const {
    return common::send<GetFlexibleLoanLtvAdjustmentHistoryResponse>(
        *client_, get_flexible_loan_ltv_adjustment_history_request(params));
}

common::RestRequest FlexibleRateApi::get_flexible_loan_ongoing_orders_request(
    const GetFlexibleLoanOngoingOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/loan/flexible/ongoing/orders";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleLoanOngoingOrdersResponse>
FlexibleRateApi::get_flexible_loan_ongoing_orders(
    const GetFlexibleLoanOngoingOrdersParams& params) const {
    return common::send<GetFlexibleLoanOngoingOrdersResponse>(
        *client_, get_flexible_loan_ongoing_orders_request(params));
}

common::RestRequest FlexibleRateApi::get_flexible_loan_repayment_history_request(
    const GetFlexibleLoanRepaymentHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/loan/flexible/repay/history";
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFlexibleLoanRepaymentHistoryResponse>
FlexibleRateApi::get_flexible_loan_repayment_history(
    const GetFlexibleLoanRepaymentHistoryParams& params) const {
    return common::send<GetFlexibleLoanRepaymentHistoryResponse>(
        *client_, get_flexible_loan_repayment_history_request(params));
}

} // namespace binance::crypto_loan::rest_api
