//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/rest.hpp>
#include <binance/vip_loan/export.hpp>
#include <binance/vip_loan/rest_api/models/check_vip_loan_collateral_account_response.hpp>
#include <binance/vip_loan/rest_api/models/get_vip_loan_accrued_interest_response.hpp>
#include <binance/vip_loan/rest_api/models/get_vip_loan_ongoing_orders_response.hpp>
#include <binance/vip_loan/rest_api/models/get_vip_loan_repayment_history_response.hpp>
#include <binance/vip_loan/rest_api/models/query_application_status_response.hpp>

namespace binance::vip_loan::rest_api {

struct CheckVIPLoanCollateralAccountParams {
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::int64_t> collateral_account_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetVIPLoanAccruedInterestParams {
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> loan_coin = std::nullopt;
    /// If both startTime and endTime are omitted, the most recent 90 days are returned.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Maximum interval between startTime and endTime is 90 days.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current page number, starting from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of records per page.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetVIPLoanOngoingOrdersParams {
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::int64_t> collateral_account_id = std::nullopt;
    std::optional<std::string> loan_coin = std::nullopt;
    std::optional<std::string> collateral_coin = std::nullopt;
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetVIPLoanRepaymentHistoryParams {
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> loan_coin = std::nullopt;
    /// If both startTime and endTime are omitted, the most recent 90 days are returned.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Maximum interval between startTime and endTime is 180 days.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current page number, starting from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of records per page.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryApplicationStatusParams {
    /// Current page number, starting from 1.
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_VIP_LOAN_EXPORT UserInformationApi {
public:
    explicit UserInformationApi(std::shared_ptr<common::RestClient> client);

    /// Check VIP Loan Collateral Account (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/collateral/account.
    ///
    /// VIP loan is available for VIP users only
    ///
    /// Weight(IP): 6000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If the logged-in account is a borrowing account, all collateral accounts bound to that
    /// borrowing account can be queried.
    /// - If the logged-in account is a collateral account, only collateral assets under that
    /// account can be queried.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/user-information#check-viploan-collateral-account
    [[nodiscard]] common::RestApiResponse<CheckVIPLoanCollateralAccountResponse>
    check_vip_loan_collateral_account(const CheckVIPLoanCollateralAccountParams& params = {}) const;

    /// Asynchronous `check_vip_loan_collateral_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CheckVIPLoanCollateralAccountResponse>)`.
    template <class CompletionToken>
    auto async_check_vip_loan_collateral_account(const CheckVIPLoanCollateralAccountParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<CheckVIPLoanCollateralAccountResponse>(
            client_, check_vip_loan_collateral_account_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get VIP Loan Accrued Interest (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/accruedInterest.
    ///
    /// Check VIP Loan interest record
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, recent 90-day data is returned.
    /// - The maximum interval between `startTime` and `endTime` is 90 days.
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/user-information#get-viploan-accrued-interest
    [[nodiscard]] common::RestApiResponse<GetVIPLoanAccruedInterestResponse>
    get_vip_loan_accrued_interest(const GetVIPLoanAccruedInterestParams& params = {}) const;

    /// Asynchronous `get_vip_loan_accrued_interest()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetVIPLoanAccruedInterestResponse>)`.
    template <class CompletionToken>
    auto async_get_vip_loan_accrued_interest(const GetVIPLoanAccruedInterestParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetVIPLoanAccruedInterestResponse>(
            client_, get_vip_loan_accrued_interest_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get VIP Loan Ongoing Orders (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/ongoing/orders.
    ///
    /// VIP loan is available for VIP users only.
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/user-information#get-viploan-ongoing-orders
    [[nodiscard]] common::RestApiResponse<GetVIPLoanOngoingOrdersResponse>
    get_vip_loan_ongoing_orders(const GetVIPLoanOngoingOrdersParams& params = {}) const;

    /// Asynchronous `get_vip_loan_ongoing_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetVIPLoanOngoingOrdersResponse>)`.
    template <class CompletionToken>
    auto async_get_vip_loan_ongoing_orders(const GetVIPLoanOngoingOrdersParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<GetVIPLoanOngoingOrdersResponse>(
            client_, get_vip_loan_ongoing_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get VIP Loan Repayment History (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/repay/history.
    ///
    /// VIP Loans are available only to VIP users.
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, recent 90-day data is returned.
    /// - The maximum interval between `startTime` and `endTime` is 180 days.
    /// - Rate limit: 1 request per second per account, shared with repayment history queries on the
    /// Binance website.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/user-information#get-viploan-repayment-history
    [[nodiscard]] common::RestApiResponse<GetVIPLoanRepaymentHistoryResponse>
    get_vip_loan_repayment_history(const GetVIPLoanRepaymentHistoryParams& params = {}) const;

    /// Asynchronous `get_vip_loan_repayment_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetVIPLoanRepaymentHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_vip_loan_repayment_history(const GetVIPLoanRepaymentHistoryParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetVIPLoanRepaymentHistoryResponse>(
            client_, get_vip_loan_repayment_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Application Status (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/request/data.
    ///
    /// Query Application Status
    ///
    /// Weight(UID): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/user-information#query-application-status
    [[nodiscard]] common::RestApiResponse<QueryApplicationStatusResponse>
    query_application_status(const QueryApplicationStatusParams& params = {}) const;

    /// Asynchronous `query_application_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryApplicationStatusResponse>)`.
    template <class CompletionToken>
    auto async_query_application_status(const QueryApplicationStatusParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<QueryApplicationStatusResponse>(
            client_, query_application_status_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest check_vip_loan_collateral_account_request(
        const CheckVIPLoanCollateralAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    get_vip_loan_accrued_interest_request(const GetVIPLoanAccruedInterestParams& params) const;
    [[nodiscard]] common::RestRequest
    get_vip_loan_ongoing_orders_request(const GetVIPLoanOngoingOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    get_vip_loan_repayment_history_request(const GetVIPLoanRepaymentHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_application_status_request(const QueryApplicationStatusParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::vip_loan::rest_api
