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
#include <string_view>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/crypto_loan/export.hpp>
#include <binance/crypto_loan/rest_api/models/check_collateral_repay_rate_response.hpp>
#include <binance/crypto_loan/rest_api/models/flexible_loan_adjust_ltv_response.hpp>
#include <binance/crypto_loan/rest_api/models/flexible_loan_borrow_response.hpp>
#include <binance/crypto_loan/rest_api/models/flexible_loan_repay_response.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_assets_data_response.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_borrow_history_response.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_collateral_assets_data_response.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_interest_rate_history_response.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_liquidation_history_response.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_ltv_adjustment_history_response.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_ongoing_orders_response.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_repayment_history_response.hpp>

namespace binance::crypto_loan::rest_api {

enum class FlexibleLoanAdjustLtvDirectionEnum {
    Additional,
    Reduced,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_CRYPTO_LOAN_EXPORT std::string_view
to_string(FlexibleLoanAdjustLtvDirectionEnum value) noexcept;
BINANCE_CRYPTO_LOAN_EXPORT FlexibleLoanAdjustLtvDirectionEnum
tag_invoke(boost::json::value_to_tag<FlexibleLoanAdjustLtvDirectionEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           FlexibleLoanAdjustLtvDirectionEnum value);

enum class FlexibleLoanRepayRepaymentTypeEnum {
    RepaymentType1,
    RepaymentType2,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_CRYPTO_LOAN_EXPORT std::string_view
to_string(FlexibleLoanRepayRepaymentTypeEnum value) noexcept;
BINANCE_CRYPTO_LOAN_EXPORT FlexibleLoanRepayRepaymentTypeEnum
tag_invoke(boost::json::value_to_tag<FlexibleLoanRepayRepaymentTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           FlexibleLoanRepayRepaymentTypeEnum value);

struct CheckCollateralRepayRateParams {
    common::Required<std::string> loan_coin;
    common::Required<std::string> collateral_coin;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FlexibleLoanAdjustLtvParams {
    common::Required<std::string> loan_coin;
    common::Required<std::string> collateral_coin;
    common::Required<common::Decimal> adjustment_amount;
    common::Required<FlexibleLoanAdjustLtvDirectionEnum> direction;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FlexibleLoanBorrowParams {
    common::Required<std::string> loan_coin;
    common::Required<std::string> collateral_coin;
    /// Mandatory when collateralAmount is empty
    std::optional<common::Decimal> loan_amount = std::nullopt;
    /// Mandatory when loanAmount is empty
    std::optional<common::Decimal> collateral_amount = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FlexibleLoanRepayParams {
    common::Required<std::string> loan_coin;
    common::Required<std::string> collateral_coin;
    common::Required<common::Decimal> repay_amount;
    /// TRUE: Return extra collateral to spot account; FALSE: Keep extra collateral in the order and
    /// lower LTV.
    std::optional<bool> collateral_return = std::nullopt;
    /// TRUE: Full repayment; FALSE: Partial repayment based on loan amount
    std::optional<bool> full_repayment = std::nullopt;
    /// 1: Repayment with loan asset; 2: Repayment with collateral
    std::optional<FlexibleLoanRepayRepaymentTypeEnum> repayment_type = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleLoanAssetsDataParams {
    std::optional<std::string> loan_coin = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleLoanBorrowHistoryParams {
    std::optional<std::string> loan_coin = std::nullopt;
    std::optional<std::string> collateral_coin = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of records to return
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleLoanCollateralAssetsDataParams {
    std::optional<std::string> collateral_coin = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleLoanInterestRateHistoryParams {
    common::Required<std::string> coin;
    /// Request validity window in milliseconds
    common::Required<std::int64_t> recv_window;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of records to return
    std::optional<std::int64_t> limit = std::nullopt;
};

struct GetFlexibleLoanLiquidationHistoryParams {
    std::optional<std::string> loan_coin = std::nullopt;
    std::optional<std::string> collateral_coin = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of records to return
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleLoanLtvAdjustmentHistoryParams {
    std::optional<std::string> loan_coin = std::nullopt;
    std::optional<std::string> collateral_coin = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of records to return
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleLoanOngoingOrdersParams {
    std::optional<std::string> loan_coin = std::nullopt;
    std::optional<std::string> collateral_coin = std::nullopt;
    /// Current querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of records to return
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFlexibleLoanRepaymentHistoryParams {
    std::optional<std::string> loan_coin = std::nullopt;
    std::optional<std::string> collateral_coin = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current querying page
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of records to return
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_CRYPTO_LOAN_EXPORT FlexibleRateApi {
public:
    explicit FlexibleRateApi(std::shared_ptr<common::RestClient> client);

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
    check_collateral_repay_rate(const CheckCollateralRepayRateParams& params) const;

    /// Asynchronous `check_collateral_repay_rate()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CheckCollateralRepayRateResponse>)`.
    template <class CompletionToken>
    auto async_check_collateral_repay_rate(const CheckCollateralRepayRateParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<CheckCollateralRepayRateResponse>(
            client_, check_collateral_repay_rate_request(params),
            std::forward<CompletionToken>(token));
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
    flexible_loan_adjust_ltv(const FlexibleLoanAdjustLtvParams& params) const;

    /// Asynchronous `flexible_loan_adjust_ltv()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FlexibleLoanAdjustLtvResponse>)`.
    template <class CompletionToken>
    auto async_flexible_loan_adjust_ltv(const FlexibleLoanAdjustLtvParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<FlexibleLoanAdjustLtvResponse>(
            client_, flexible_loan_adjust_ltv_request(params),
            std::forward<CompletionToken>(token));
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
    flexible_loan_borrow(const FlexibleLoanBorrowParams& params) const;

    /// Asynchronous `flexible_loan_borrow()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FlexibleLoanBorrowResponse>)`.
    template <class CompletionToken>
    auto async_flexible_loan_borrow(const FlexibleLoanBorrowParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<FlexibleLoanBorrowResponse>(
            client_, flexible_loan_borrow_request(params), std::forward<CompletionToken>(token));
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
    flexible_loan_repay(const FlexibleLoanRepayParams& params) const;

    /// Asynchronous `flexible_loan_repay()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FlexibleLoanRepayResponse>)`.
    template <class CompletionToken>
    auto async_flexible_loan_repay(const FlexibleLoanRepayParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<FlexibleLoanRepayResponse>(
            client_, flexible_loan_repay_request(params), std::forward<CompletionToken>(token));
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
    get_flexible_loan_assets_data(const GetFlexibleLoanAssetsDataParams& params = {}) const;

    /// Asynchronous `get_flexible_loan_assets_data()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFlexibleLoanAssetsDataResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_loan_assets_data(const GetFlexibleLoanAssetsDataParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetFlexibleLoanAssetsDataResponse>(
            client_, get_flexible_loan_assets_data_request(params),
            std::forward<CompletionToken>(token));
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
    get_flexible_loan_borrow_history(const GetFlexibleLoanBorrowHistoryParams& params = {}) const;

    /// Asynchronous `get_flexible_loan_borrow_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFlexibleLoanBorrowHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_loan_borrow_history(const GetFlexibleLoanBorrowHistoryParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<GetFlexibleLoanBorrowHistoryResponse>(
            client_, get_flexible_loan_borrow_history_request(params),
            std::forward<CompletionToken>(token));
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
        const GetFlexibleLoanCollateralAssetsDataParams& params = {}) const;

    /// Asynchronous `get_flexible_loan_collateral_assets_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFlexibleLoanCollateralAssetsDataResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_loan_collateral_assets_data(
        const GetFlexibleLoanCollateralAssetsDataParams& params, CompletionToken&& token) const {
        return common::async_send<GetFlexibleLoanCollateralAssetsDataResponse>(
            client_, get_flexible_loan_collateral_assets_data_request(params),
            std::forward<CompletionToken>(token));
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
        const GetFlexibleLoanInterestRateHistoryParams& params) const;

    /// Asynchronous `get_flexible_loan_interest_rate_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFlexibleLoanInterestRateHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_loan_interest_rate_history(
        const GetFlexibleLoanInterestRateHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetFlexibleLoanInterestRateHistoryResponse>(
            client_, get_flexible_loan_interest_rate_history_request(params),
            std::forward<CompletionToken>(token));
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
        const GetFlexibleLoanLiquidationHistoryParams& params = {}) const;

    /// Asynchronous `get_flexible_loan_liquidation_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFlexibleLoanLiquidationHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_loan_liquidation_history(
        const GetFlexibleLoanLiquidationHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetFlexibleLoanLiquidationHistoryResponse>(
            client_, get_flexible_loan_liquidation_history_request(params),
            std::forward<CompletionToken>(token));
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
        const GetFlexibleLoanLtvAdjustmentHistoryParams& params = {}) const;

    /// Asynchronous `get_flexible_loan_ltv_adjustment_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFlexibleLoanLtvAdjustmentHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_loan_ltv_adjustment_history(
        const GetFlexibleLoanLtvAdjustmentHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetFlexibleLoanLtvAdjustmentHistoryResponse>(
            client_, get_flexible_loan_ltv_adjustment_history_request(params),
            std::forward<CompletionToken>(token));
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
    get_flexible_loan_ongoing_orders(const GetFlexibleLoanOngoingOrdersParams& params = {}) const;

    /// Asynchronous `get_flexible_loan_ongoing_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFlexibleLoanOngoingOrdersResponse>)`.
    template <class CompletionToken>
    auto async_get_flexible_loan_ongoing_orders(const GetFlexibleLoanOngoingOrdersParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<GetFlexibleLoanOngoingOrdersResponse>(
            client_, get_flexible_loan_ongoing_orders_request(params),
            std::forward<CompletionToken>(token));
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
        const GetFlexibleLoanRepaymentHistoryParams& params = {}) const;

    /// Asynchronous `get_flexible_loan_repayment_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFlexibleLoanRepaymentHistoryResponse>)`.
    template <class CompletionToken>
    auto
    async_get_flexible_loan_repayment_history(const GetFlexibleLoanRepaymentHistoryParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetFlexibleLoanRepaymentHistoryResponse>(
            client_, get_flexible_loan_repayment_history_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    check_collateral_repay_rate_request(const CheckCollateralRepayRateParams& params) const;
    [[nodiscard]] common::RestRequest
    flexible_loan_adjust_ltv_request(const FlexibleLoanAdjustLtvParams& params) const;
    [[nodiscard]] common::RestRequest
    flexible_loan_borrow_request(const FlexibleLoanBorrowParams& params) const;
    [[nodiscard]] common::RestRequest
    flexible_loan_repay_request(const FlexibleLoanRepayParams& params) const;
    [[nodiscard]] common::RestRequest
    get_flexible_loan_assets_data_request(const GetFlexibleLoanAssetsDataParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_loan_borrow_history_request(
        const GetFlexibleLoanBorrowHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_loan_collateral_assets_data_request(
        const GetFlexibleLoanCollateralAssetsDataParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_loan_interest_rate_history_request(
        const GetFlexibleLoanInterestRateHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_loan_liquidation_history_request(
        const GetFlexibleLoanLiquidationHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_loan_ltv_adjustment_history_request(
        const GetFlexibleLoanLtvAdjustmentHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_loan_ongoing_orders_request(
        const GetFlexibleLoanOngoingOrdersParams& params) const;
    [[nodiscard]] common::RestRequest get_flexible_loan_repayment_history_request(
        const GetFlexibleLoanRepaymentHistoryParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::crypto_loan::rest_api
