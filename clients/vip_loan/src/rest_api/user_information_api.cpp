//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/user_information_api.hpp>

namespace binance::vip_loan::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

UserInformationApi::UserInformationApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest UserInformationApi::check_vip_loan_collateral_account_request(
    const CheckVIPLoanCollateralAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/collateral/account";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "collateralAccountId", params.collateral_account_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CheckVIPLoanCollateralAccountResponse>
UserInformationApi::check_vip_loan_collateral_account(
    const CheckVIPLoanCollateralAccountParams& params) const {
    return common::send<CheckVIPLoanCollateralAccountResponse>(
        *client_, check_vip_loan_collateral_account_request(params));
}

common::RestRequest UserInformationApi::get_vip_loan_accrued_interest_request(
    const GetVIPLoanAccruedInterestParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/accruedInterest";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetVIPLoanAccruedInterestResponse>
UserInformationApi::get_vip_loan_accrued_interest(
    const GetVIPLoanAccruedInterestParams& params) const {
    return common::send<GetVIPLoanAccruedInterestResponse>(
        *client_, get_vip_loan_accrued_interest_request(params));
}

common::RestRequest UserInformationApi::get_vip_loan_ongoing_orders_request(
    const GetVIPLoanOngoingOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/ongoing/orders";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "collateralAccountId", params.collateral_account_id);
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetVIPLoanOngoingOrdersResponse>
UserInformationApi::get_vip_loan_ongoing_orders(const GetVIPLoanOngoingOrdersParams& params) const {
    return common::send<GetVIPLoanOngoingOrdersResponse>(
        *client_, get_vip_loan_ongoing_orders_request(params));
}

common::RestRequest UserInformationApi::get_vip_loan_repayment_history_request(
    const GetVIPLoanRepaymentHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/repay/history";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetVIPLoanRepaymentHistoryResponse>
UserInformationApi::get_vip_loan_repayment_history(
    const GetVIPLoanRepaymentHistoryParams& params) const {
    return common::send<GetVIPLoanRepaymentHistoryResponse>(
        *client_, get_vip_loan_repayment_history_request(params));
}

common::RestRequest UserInformationApi::query_application_status_request(
    const QueryApplicationStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/loan/vip/request/data";
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryApplicationStatusResponse>
UserInformationApi::query_application_status(const QueryApplicationStatusParams& params) const {
    return common::send<QueryApplicationStatusResponse>(*client_,
                                                        query_application_status_request(params));
}

} // namespace binance::vip_loan::rest_api
