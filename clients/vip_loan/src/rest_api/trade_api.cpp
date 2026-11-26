//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/trade_api.hpp>

namespace binance::vip_loan::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest TradeApi::vip_loan_borrow_request(const VipLoanBorrowParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/loan/vip/borrow";
    common::detail::json::set_param(req.query, "loanAccountId", params.loan_account_id);
    common::detail::json::set_param(req.query, "loanCoin", params.loan_coin);
    common::detail::json::set_param(req.query, "loanAmount", params.loan_amount);
    common::detail::json::set_param(req.query, "collateralAccountId", params.collateral_account_id);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "isFlexibleRate", params.is_flexible_rate);
    common::detail::json::set_param(req.query, "loanTerm", params.loan_term);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<VipLoanBorrowResponse>
TradeApi::vip_loan_borrow(const VipLoanBorrowParams& params) const {
    return common::send<VipLoanBorrowResponse>(*client_, vip_loan_borrow_request(params));
}

common::RestRequest
TradeApi::vip_loan_fixed_rate_borrow_request(const VipLoanFixedRateBorrowParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/loan/vip/fixed/borrow";
    common::detail::json::set_param(req.query, "supplyRequest", params.supply_request);
    common::detail::json::set_param(req.query, "borrowCoin", params.borrow_coin);
    common::detail::json::set_param(req.query, "loanTerm", params.loan_term);
    common::detail::json::set_param(req.query, "borrowUid", params.borrow_uid);
    common::detail::json::set_param(req.query, "collateralCoin", params.collateral_coin);
    common::detail::json::set_param(req.query, "collateralAccountId", params.collateral_account_id);
    common::detail::json::set_param(req.query, "autoRepay", params.auto_repay);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<VipLoanFixedRateBorrowResponse>
TradeApi::vip_loan_fixed_rate_borrow(const VipLoanFixedRateBorrowParams& params) const {
    return common::send<VipLoanFixedRateBorrowResponse>(*client_,
                                                        vip_loan_fixed_rate_borrow_request(params));
}

common::RestRequest TradeApi::vip_loan_renew_request(const VipLoanRenewParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/loan/vip/renew";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "loanTerm", params.loan_term);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<VipLoanRenewResponse>
TradeApi::vip_loan_renew(const VipLoanRenewParams& params) const {
    return common::send<VipLoanRenewResponse>(*client_, vip_loan_renew_request(params));
}

common::RestRequest TradeApi::vip_loan_repay_request(const VipLoanRepayParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/loan/vip/repay";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<VipLoanRepayResponse>
TradeApi::vip_loan_repay(const VipLoanRepayParams& params) const {
    return common::send<VipLoanRepayResponse>(*client_, vip_loan_repay_request(params));
}

} // namespace binance::vip_loan::rest_api
