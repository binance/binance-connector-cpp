//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <string>
#include <utility>

#include <binance/common/config.hpp>
#include <binance/common/rest.hpp>
#include <binance/crypto_loan/export.hpp>
#include <binance/crypto_loan/rest_api/flexible_rate_api.hpp>
#include <binance/crypto_loan/rest_api/models.hpp>

namespace binance::crypto_loan::rest_api {

/// CryptoLoan REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_CRYPTO_LOAN_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Crypto Loan REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);

    [[nodiscard]] const common::RestApiConfig& configuration() const noexcept;

    /// Calls an endpoint the SDK does not wrap yet. `T` may be `boost::json::value`.
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                 common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), false));
    }

    /// Like `send_request`, but signed (adds `timestamp` and `signature`).
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_signed_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                        common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), true));
    }

    template <class T, class CompletionToken>
    auto async_send_request(std::string endpoint, common::HttpMethod method, common::Params query,
                            common::Params body, CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), false),
            std::forward<CompletionToken>(token));
    }

    template <class T, class CompletionToken>
    auto async_send_signed_request(std::string endpoint, common::HttpMethod method,
                                   common::Params query, common::Params body,
                                   CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), true),
            std::forward<CompletionToken>(token));
    }

    // FlexibleRateApi

    /// Check Collateral Flexible Repay Rate (USER_DATA)
    ///
    /// GET /sapi/v2/loan/flexible/repay/rate.
    ///
    /// Get the latest rate of collateral coin/loan coin when using collateral repay.
    ///
    /// Weight(IP): 6000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#check-collateral-repay-rate
    [[nodiscard]] common::RestApiResponse<CheckCollateralRepayRateResponse>
    check_collateral_repay_rate(const CheckCollateralRepayRateParams& params) const {
        return flexible_rate_api_.check_collateral_repay_rate(params);
    }
    /// Asynchronous `check_collateral_repay_rate()`.
    template <class CompletionToken>
    auto async_check_collateral_repay_rate(const CheckCollateralRepayRateParams& params,
                                           CompletionToken&& token) const {
        return flexible_rate_api_.async_check_collateral_repay_rate(
            params, std::forward<CompletionToken>(token));
    }

    /// Flexible Loan Adjust LTV (TRADE)
    ///
    /// POST /sapi/v2/loan/flexible/adjust/ltv.
    ///
    /// Flexible Loan Adjust LTV
    ///
    /// Weight(UID): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - API key needs Spot & Margin Trading permission for this endpoint.
    /// - Rate limit: 1 request per second per loan position (account + loan coin + collateral coin
    /// combination).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#flexible-loan-adjust-ltv
    [[nodiscard]] common::RestApiResponse<FlexibleLoanAdjustLtvResponse>
    flexible_loan_adjust_ltv(const FlexibleLoanAdjustLtvParams& params) const {
        return flexible_rate_api_.flexible_loan_adjust_ltv(params);
    }
    /// Asynchronous `flexible_loan_adjust_ltv()`.
    template <class CompletionToken>
    auto async_flexible_loan_adjust_ltv(const FlexibleLoanAdjustLtvParams& params,
                                        CompletionToken&& token) const {
        return flexible_rate_api_.async_flexible_loan_adjust_ltv(
            params, std::forward<CompletionToken>(token));
    }

    /// Flexible Loan Borrow (TRADE)
    ///
    /// POST /sapi/v2/loan/flexible/borrow.
    ///
    /// Borrow Flexible Loan
    ///
    /// Weight(IP): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - This endpoint is available for both master and sub-accounts.
    /// - You can customize LTV by entering `loanAmount` and `collateralAmount`.
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#flexible-loan-borrow
    [[nodiscard]] common::RestApiResponse<FlexibleLoanBorrowResponse>
    flexible_loan_borrow(const FlexibleLoanBorrowParams& params) const {
        return flexible_rate_api_.flexible_loan_borrow(params);
    }
    /// Asynchronous `flexible_loan_borrow()`.
    template <class CompletionToken>
    auto async_flexible_loan_borrow(const FlexibleLoanBorrowParams& params,
                                    CompletionToken&& token) const {
        return flexible_rate_api_.async_flexible_loan_borrow(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Flexible Loan Repay (TRADE)
    ///
    /// POST /sapi/v2/loan/flexible/repay.
    ///
    /// Flexible Loan Repay
    ///
    /// Weight(IP): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - `repayAmount` is mandatory even when `fullRepayment = FALSE`.
    /// - Rate limit: 1 request per second per loan position (account + loan coin + collateral coin
    /// combination).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#flexible-loan-repay
    [[nodiscard]] common::RestApiResponse<FlexibleLoanRepayResponse>
    flexible_loan_repay(const FlexibleLoanRepayParams& params) const {
        return flexible_rate_api_.flexible_loan_repay(params);
    }
    /// Asynchronous `flexible_loan_repay()`.
    template <class CompletionToken>
    auto async_flexible_loan_repay(const FlexibleLoanRepayParams& params,
                                   CompletionToken&& token) const {
        return flexible_rate_api_.async_flexible_loan_repay(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Get Flexible Loan Assets Data (USER_DATA)
    ///
    /// GET /sapi/v2/loan/flexible/loanable/data.
    ///
    /// Get interest rate and borrow limit of flexible loanable assets. The borrow limit is shown in
    /// USD value.
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#get-flexible-loan-assets-data
    [[nodiscard]] common::RestApiResponse<GetFlexibleLoanAssetsDataResponse>
    get_flexible_loan_assets_data(const GetFlexibleLoanAssetsDataParams& params = {}) const {
        return flexible_rate_api_.get_flexible_loan_assets_data(params);
    }
    /// Asynchronous `get_flexible_loan_assets_data()`.
    template <class CompletionToken>
    auto async_get_flexible_loan_assets_data(const GetFlexibleLoanAssetsDataParams& params,
                                             CompletionToken&& token) const {
        return flexible_rate_api_.async_get_flexible_loan_assets_data(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Flexible Loan Borrow History (USER_DATA)
    ///
    /// GET /sapi/v2/loan/flexible/borrow/history.
    ///
    /// Get Flexible Loan Borrow History.
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, the recent 90-day data is returned.
    /// - The max interval between `startTime` and `endTime` is 180 days.
    /// - Rate limit: 5 requests per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#get-flexible-loan-borrow-history
    [[nodiscard]] common::RestApiResponse<GetFlexibleLoanBorrowHistoryResponse>
    get_flexible_loan_borrow_history(const GetFlexibleLoanBorrowHistoryParams& params = {}) const {
        return flexible_rate_api_.get_flexible_loan_borrow_history(params);
    }
    /// Asynchronous `get_flexible_loan_borrow_history()`.
    template <class CompletionToken>
    auto async_get_flexible_loan_borrow_history(const GetFlexibleLoanBorrowHistoryParams& params,
                                                CompletionToken&& token) const {
        return flexible_rate_api_.async_get_flexible_loan_borrow_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Flexible Loan Collateral Assets Data (USER_DATA)
    ///
    /// GET /sapi/v2/loan/flexible/collateral/data.
    ///
    /// Get LTV information and collateral limit of flexible loan's collateral assets. The
    /// collateral limit is shown in USD value.
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#get-flexible-loan-collateral-assets-data
    [[nodiscard]] common::RestApiResponse<GetFlexibleLoanCollateralAssetsDataResponse>
    get_flexible_loan_collateral_assets_data(
        const GetFlexibleLoanCollateralAssetsDataParams& params = {}) const {
        return flexible_rate_api_.get_flexible_loan_collateral_assets_data(params);
    }
    /// Asynchronous `get_flexible_loan_collateral_assets_data()`.
    template <class CompletionToken>
    auto async_get_flexible_loan_collateral_assets_data(
        const GetFlexibleLoanCollateralAssetsDataParams& params, CompletionToken&& token) const {
        return flexible_rate_api_.async_get_flexible_loan_collateral_assets_data(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Flexible Loan Interest Rate History (USER_DATA)
    ///
    /// GET /sapi/v2/loan/interestRateHistory.
    ///
    /// Check Flexible Loan interest rate history
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, the recent 90-day data is returned.
    /// - The max interval between `startTime` and `endTime` is 90 days.
    /// - Time is based on UTC+0.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#get-flexible-loan-interest-rate-history
    [[nodiscard]] common::RestApiResponse<GetFlexibleLoanInterestRateHistoryResponse>
    get_flexible_loan_interest_rate_history(
        const GetFlexibleLoanInterestRateHistoryParams& params) const {
        return flexible_rate_api_.get_flexible_loan_interest_rate_history(params);
    }
    /// Asynchronous `get_flexible_loan_interest_rate_history()`.
    template <class CompletionToken>
    auto async_get_flexible_loan_interest_rate_history(
        const GetFlexibleLoanInterestRateHistoryParams& params, CompletionToken&& token) const {
        return flexible_rate_api_.async_get_flexible_loan_interest_rate_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Flexible Loan Liquidation History (USER_DATA)
    ///
    /// GET /sapi/v2/loan/flexible/liquidation/history.
    ///
    /// Get Flexible Loan Liquidation History
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#get-flexible-loan-liquidation-history
    [[nodiscard]] common::RestApiResponse<GetFlexibleLoanLiquidationHistoryResponse>
    get_flexible_loan_liquidation_history(
        const GetFlexibleLoanLiquidationHistoryParams& params = {}) const {
        return flexible_rate_api_.get_flexible_loan_liquidation_history(params);
    }
    /// Asynchronous `get_flexible_loan_liquidation_history()`.
    template <class CompletionToken>
    auto async_get_flexible_loan_liquidation_history(
        const GetFlexibleLoanLiquidationHistoryParams& params, CompletionToken&& token) const {
        return flexible_rate_api_.async_get_flexible_loan_liquidation_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Flexible Loan LTV Adjustment History (USER_DATA)
    ///
    /// GET /sapi/v2/loan/flexible/ltv/adjustment/history.
    ///
    /// Get Flexible Loan LTV Adjustment History.
    ///
    /// Weight(UID): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, the recent 90-day data is returned.
    /// - The max interval between `startTime` and `endTime` is 180 days.
    /// - Rate limit: 5 requests per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#get-flexible-loan-ltv-adjustment-history
    [[nodiscard]] common::RestApiResponse<GetFlexibleLoanLtvAdjustmentHistoryResponse>
    get_flexible_loan_ltv_adjustment_history(
        const GetFlexibleLoanLtvAdjustmentHistoryParams& params = {}) const {
        return flexible_rate_api_.get_flexible_loan_ltv_adjustment_history(params);
    }
    /// Asynchronous `get_flexible_loan_ltv_adjustment_history()`.
    template <class CompletionToken>
    auto async_get_flexible_loan_ltv_adjustment_history(
        const GetFlexibleLoanLtvAdjustmentHistoryParams& params, CompletionToken&& token) const {
        return flexible_rate_api_.async_get_flexible_loan_ltv_adjustment_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Flexible Loan Ongoing Orders (USER_DATA)
    ///
    /// GET /sapi/v2/loan/flexible/ongoing/orders.
    ///
    /// Get Flexible Loan Ongoing Orders
    ///
    /// Weight(IP): 300
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 10 requests per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#get-flexible-loan-ongoing-orders
    [[nodiscard]] common::RestApiResponse<GetFlexibleLoanOngoingOrdersResponse>
    get_flexible_loan_ongoing_orders(const GetFlexibleLoanOngoingOrdersParams& params = {}) const {
        return flexible_rate_api_.get_flexible_loan_ongoing_orders(params);
    }
    /// Asynchronous `get_flexible_loan_ongoing_orders()`.
    template <class CompletionToken>
    auto async_get_flexible_loan_ongoing_orders(const GetFlexibleLoanOngoingOrdersParams& params,
                                                CompletionToken&& token) const {
        return flexible_rate_api_.async_get_flexible_loan_ongoing_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Flexible Loan Repayment History (USER_DATA)
    ///
    /// GET /sapi/v2/loan/flexible/repay/history.
    ///
    /// Get Flexible Loan Repayment History.
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, the recent 90-day data is returned.
    /// - The max interval between `startTime` and `endTime` is 180 days.
    /// - Rate limit: 5 requests per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-crypto-loan/api/rest-api/flexible-rate#get-flexible-loan-repayment-history
    [[nodiscard]] common::RestApiResponse<GetFlexibleLoanRepaymentHistoryResponse>
    get_flexible_loan_repayment_history(
        const GetFlexibleLoanRepaymentHistoryParams& params = {}) const {
        return flexible_rate_api_.get_flexible_loan_repayment_history(params);
    }
    /// Asynchronous `get_flexible_loan_repayment_history()`.
    template <class CompletionToken>
    auto
    async_get_flexible_loan_repayment_history(const GetFlexibleLoanRepaymentHistoryParams& params,
                                              CompletionToken&& token) const {
        return flexible_rate_api_.async_get_flexible_loan_repayment_history(
            params, std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::RestRequest make_request(std::string endpoint,
                                                          common::HttpMethod method,
                                                          common::Params query, common::Params body,
                                                          bool is_signed) {
        common::RestRequest req;
        req.method = method;
        req.endpoint = std::move(endpoint);
        req.query = std::move(query);
        req.body = std::move(body);
        req.is_signed = is_signed;
        return req;
    }

    std::shared_ptr<common::RestClient> client_;
    FlexibleRateApi flexible_rate_api_;
};

} // namespace binance::crypto_loan::rest_api
