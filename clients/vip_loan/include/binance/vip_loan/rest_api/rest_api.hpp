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
#include <binance/vip_loan/export.hpp>
#include <binance/vip_loan/rest_api/market_data_api.hpp>
#include <binance/vip_loan/rest_api/models.hpp>
#include <binance/vip_loan/rest_api/trade_api.hpp>
#include <binance/vip_loan/rest_api/user_information_api.hpp>

namespace binance::vip_loan::rest_api {

/// VipLoan REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_VIP_LOAN_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Vip Loan REST API).
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

    // MarketDataApi

    /// Get Borrow Interest Rate (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/request/interestRate.
    ///
    /// Get Borrow Interest Rate
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#get-borrow-interest-rate
    [[nodiscard]] common::RestApiResponse<std::vector<GetBorrowInterestRateResponseInner>>
    get_borrow_interest_rate(const GetBorrowInterestRateParams& params) const {
        return market_data_api_.get_borrow_interest_rate(params);
    }
    /// Asynchronous `get_borrow_interest_rate()`.
    template <class CompletionToken>
    auto async_get_borrow_interest_rate(const GetBorrowInterestRateParams& params,
                                        CompletionToken&& token) const {
        return market_data_api_.async_get_borrow_interest_rate(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Collateral Asset Data (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/collateral/data.
    ///
    /// Get Collateral Asset Data
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#get-collateral-asset-data
    [[nodiscard]] common::RestApiResponse<GetCollateralAssetDataResponse>
    get_collateral_asset_data(const GetCollateralAssetDataParams& params = {}) const {
        return market_data_api_.get_collateral_asset_data(params);
    }
    /// Asynchronous `get_collateral_asset_data()`.
    template <class CompletionToken>
    auto async_get_collateral_asset_data(const GetCollateralAssetDataParams& params,
                                         CompletionToken&& token) const {
        return market_data_api_.async_get_collateral_asset_data(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Loanable Assets Data (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/loanable/data.
    ///
    /// Get interest rate and borrow limit of loanable assets. The borrow limit is shown in USD
    /// value.
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#get-loanable-assets-data
    [[nodiscard]] common::RestApiResponse<GetLoanableAssetsDataResponse>
    get_loanable_assets_data(const GetLoanableAssetsDataParams& params = {}) const {
        return market_data_api_.get_loanable_assets_data(params);
    }
    /// Asynchronous `get_loanable_assets_data()`.
    template <class CompletionToken>
    auto async_get_loanable_assets_data(const GetLoanableAssetsDataParams& params,
                                        CompletionToken&& token) const {
        return market_data_api_.async_get_loanable_assets_data(
            params, std::forward<CompletionToken>(token));
    }

    /// Get VIP Loan Interest Rate History (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/interestRateHistory.
    ///
    /// Check VIP Loan flexible interest rate history
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, recent 90-day data is returned.
    /// - The maximum interval between `startTime` and `endTime` is 180 days.
    /// - Time is based on UTC+0.
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#get-viploan-interest-rate-history
    [[nodiscard]] common::RestApiResponse<GetVIPLoanInterestRateHistoryResponse>
    get_vip_loan_interest_rate_history(const GetVIPLoanInterestRateHistoryParams& params) const {
        return market_data_api_.get_vip_loan_interest_rate_history(params);
    }
    /// Asynchronous `get_vip_loan_interest_rate_history()`.
    template <class CompletionToken>
    auto async_get_vip_loan_interest_rate_history(const GetVIPLoanInterestRateHistoryParams& params,
                                                  CompletionToken&& token) const {
        return market_data_api_.async_get_vip_loan_interest_rate_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Query VIP Loan Fixed Rate Market (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/fixed/market.
    ///
    /// Query the VIP Loan fixed rate market. Returns a paginated list of fixed-rate supply orders.
    ///
    /// Weight(IP): 6000
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#query-viploan-fixed-rate-market
    [[nodiscard]] common::RestApiResponse<QueryVIPLoanFixedRateMarketResponse>
    query_vip_loan_fixed_rate_market(const QueryVIPLoanFixedRateMarketParams& params) const {
        return market_data_api_.query_vip_loan_fixed_rate_market(params);
    }
    /// Asynchronous `query_vip_loan_fixed_rate_market()`.
    template <class CompletionToken>
    auto async_query_vip_loan_fixed_rate_market(const QueryVIPLoanFixedRateMarketParams& params,
                                                CompletionToken&& token) const {
        return market_data_api_.async_query_vip_loan_fixed_rate_market(
            params, std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// VIP Loan Borrow (TRADE)
    ///
    /// POST /sapi/v1/loan/vip/borrow.
    ///
    /// VIP loan is available for VIP users only.
    ///
    /// Weight(UID): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - `loanAccountId` refers to the loan receiving account.
    /// - Only master account applications are supported.
    /// - `loanAccountId` and `collateralAccountId` must be under the same master account.
    /// - `loanTerm` is mandatory if the user chooses a fixed rate (`isFlexibleRate = FALSE`).
    /// - Every coin in `collateralCoin` is pledged from every account in `collateralAccountId`.
    /// - To pledge a Simple Earn Flexible position, add `<ASSET>-Earn` (e.g. `USDT-Earn`) to
    /// `collateralCoin` together with its Spot asset (e.g. `USDT,USDT-Earn`). Sending
    /// `<ASSET>-Earn` without its Spot asset returns `-10213`.
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/trade#vip-loan-borrow
    [[nodiscard]] common::RestApiResponse<VipLoanBorrowResponse>
    vip_loan_borrow(const VipLoanBorrowParams& params) const {
        return trade_api_.vip_loan_borrow(params);
    }
    /// Asynchronous `vip_loan_borrow()`.
    template <class CompletionToken>
    auto async_vip_loan_borrow(const VipLoanBorrowParams& params, CompletionToken&& token) const {
        return trade_api_.async_vip_loan_borrow(params, std::forward<CompletionToken>(token));
    }

    /// VIP Loan Fixed Rate Borrow (TRADE)
    ///
    /// POST /sapi/v1/loan/vip/fixed/borrow.
    ///
    /// Submit a fixed rate borrow request by matching market supply orders.
    ///
    /// Weight(UID): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - **Rate limit:** 2 requests per second per account.
    /// - When multiple `supplyRequest` entries are provided, all `requestId` values must correspond
    /// to the same `borrowCoin` and `loanTerm` (validated by collateral facade).
    /// - Every coin in `collateralCoin` is pledged from every account in `collateralAccountId`.
    /// - To pledge a Simple Earn Flexible position, add `<ASSET>-Earn` (e.g. `BNB-Earn`) to
    /// `collateralCoin` together with its Spot asset (e.g. `BNB,BNB-Earn`). Sending `<ASSET>-Earn`
    /// without its Spot asset returns `-10213`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/trade#vip-loan-fixed-rate-borrow
    [[nodiscard]] common::RestApiResponse<VipLoanFixedRateBorrowResponse>
    vip_loan_fixed_rate_borrow(const VipLoanFixedRateBorrowParams& params) const {
        return trade_api_.vip_loan_fixed_rate_borrow(params);
    }
    /// Asynchronous `vip_loan_fixed_rate_borrow()`.
    template <class CompletionToken>
    auto async_vip_loan_fixed_rate_borrow(const VipLoanFixedRateBorrowParams& params,
                                          CompletionToken&& token) const {
        return trade_api_.async_vip_loan_fixed_rate_borrow(params,
                                                           std::forward<CompletionToken>(token));
    }

    /// VIP Loan Renew (TRADE)
    ///
    /// POST /sapi/v1/loan/vip/renew.
    ///
    /// VIP loan is available for VIP users only.
    ///
    /// Weight(UID): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/trade#vip-loan-renew
    [[nodiscard]] common::RestApiResponse<VipLoanRenewResponse>
    vip_loan_renew(const VipLoanRenewParams& params) const {
        return trade_api_.vip_loan_renew(params);
    }
    /// Asynchronous `vip_loan_renew()`.
    template <class CompletionToken>
    auto async_vip_loan_renew(const VipLoanRenewParams& params, CompletionToken&& token) const {
        return trade_api_.async_vip_loan_renew(params, std::forward<CompletionToken>(token));
    }

    /// VIP Loan Repay (TRADE)
    ///
    /// POST /sapi/v1/loan/vip/repay.
    ///
    /// VIP loan is available for VIP users only.
    ///
    /// Weight(UID): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/trade#vip-loan-repay
    [[nodiscard]] common::RestApiResponse<VipLoanRepayResponse>
    vip_loan_repay(const VipLoanRepayParams& params) const {
        return trade_api_.vip_loan_repay(params);
    }
    /// Asynchronous `vip_loan_repay()`.
    template <class CompletionToken>
    auto async_vip_loan_repay(const VipLoanRepayParams& params, CompletionToken&& token) const {
        return trade_api_.async_vip_loan_repay(params, std::forward<CompletionToken>(token));
    }

    // UserInformationApi

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
    check_vip_loan_collateral_account(
        const CheckVIPLoanCollateralAccountParams& params = {}) const {
        return user_information_api_.check_vip_loan_collateral_account(params);
    }
    /// Asynchronous `check_vip_loan_collateral_account()`.
    template <class CompletionToken>
    auto async_check_vip_loan_collateral_account(const CheckVIPLoanCollateralAccountParams& params,
                                                 CompletionToken&& token) const {
        return user_information_api_.async_check_vip_loan_collateral_account(
            params, std::forward<CompletionToken>(token));
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
    get_vip_loan_accrued_interest(const GetVIPLoanAccruedInterestParams& params = {}) const {
        return user_information_api_.get_vip_loan_accrued_interest(params);
    }
    /// Asynchronous `get_vip_loan_accrued_interest()`.
    template <class CompletionToken>
    auto async_get_vip_loan_accrued_interest(const GetVIPLoanAccruedInterestParams& params,
                                             CompletionToken&& token) const {
        return user_information_api_.async_get_vip_loan_accrued_interest(
            params, std::forward<CompletionToken>(token));
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
    get_vip_loan_ongoing_orders(const GetVIPLoanOngoingOrdersParams& params = {}) const {
        return user_information_api_.get_vip_loan_ongoing_orders(params);
    }
    /// Asynchronous `get_vip_loan_ongoing_orders()`.
    template <class CompletionToken>
    auto async_get_vip_loan_ongoing_orders(const GetVIPLoanOngoingOrdersParams& params,
                                           CompletionToken&& token) const {
        return user_information_api_.async_get_vip_loan_ongoing_orders(
            params, std::forward<CompletionToken>(token));
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
    get_vip_loan_repayment_history(const GetVIPLoanRepaymentHistoryParams& params = {}) const {
        return user_information_api_.get_vip_loan_repayment_history(params);
    }
    /// Asynchronous `get_vip_loan_repayment_history()`.
    template <class CompletionToken>
    auto async_get_vip_loan_repayment_history(const GetVIPLoanRepaymentHistoryParams& params,
                                              CompletionToken&& token) const {
        return user_information_api_.async_get_vip_loan_repayment_history(
            params, std::forward<CompletionToken>(token));
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
    query_application_status(const QueryApplicationStatusParams& params = {}) const {
        return user_information_api_.query_application_status(params);
    }
    /// Asynchronous `query_application_status()`.
    template <class CompletionToken>
    auto async_query_application_status(const QueryApplicationStatusParams& params,
                                        CompletionToken&& token) const {
        return user_information_api_.async_query_application_status(
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
    MarketDataApi market_data_api_;
    TradeApi trade_api_;
    UserInformationApi user_information_api_;
};

} // namespace binance::vip_loan::rest_api
