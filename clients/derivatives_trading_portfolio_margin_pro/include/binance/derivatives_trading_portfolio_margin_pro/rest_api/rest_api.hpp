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
#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/account_api.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/market_data_api.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

/// DerivativesTradingPortfolioMarginPro REST API client. Cheap to copy: copies share one
/// `common::RestClient` (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Derivatives Trading Portfolio Margin Pro REST API).
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

    // AccountApi

    /// BNB transfer (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/bnb-transfer.
    ///
    /// BNB transfer can be between Margin Account and USDM Account
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You can only use this function 2 times per 10 minutes in a rolling manner
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#bnb-transfer
    [[nodiscard]] common::RestApiResponse<BnbTransferResponse>
    bnb_transfer(const BnbTransferParams& params) const {
        return account_api_.bnb_transfer(params);
    }
    /// Asynchronous `bnb_transfer()`.
    template <class CompletionToken>
    auto async_bnb_transfer(const BnbTransferParams& params, CompletionToken&& token) const {
        return account_api_.async_bnb_transfer(params, std::forward<CompletionToken>(token));
    }

    /// Change Auto-repay-futures Status (TRADE)
    ///
    /// POST /sapi/v1/portfolio/repay-futures-switch.
    ///
    /// Change Auto-repay-futures Status
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#change-auto-repay-futures-status
    [[nodiscard]] common::RestApiResponse<ChangeAutoRepayFuturesStatusResponse>
    change_auto_repay_futures_status(const ChangeAutoRepayFuturesStatusParams& params) const {
        return account_api_.change_auto_repay_futures_status(params);
    }
    /// Asynchronous `change_auto_repay_futures_status()`.
    template <class CompletionToken>
    auto async_change_auto_repay_futures_status(const ChangeAutoRepayFuturesStatusParams& params,
                                                CompletionToken&& token) const {
        return account_api_.async_change_auto_repay_futures_status(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Auto-repay-futures Status (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/repay-futures-switch.
    ///
    /// Query Auto-repay-futures Status
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-auto-repay-futures-status
    [[nodiscard]] common::RestApiResponse<GetAutoRepayFuturesStatusResponse>
    get_auto_repay_futures_status(const GetAutoRepayFuturesStatusParams& params = {}) const {
        return account_api_.get_auto_repay_futures_status(params);
    }
    /// Asynchronous `get_auto_repay_futures_status()`.
    template <class CompletionToken>
    auto async_get_auto_repay_futures_status(const GetAutoRepayFuturesStatusParams& params,
                                             CompletionToken&& token) const {
        return account_api_.async_get_auto_repay_futures_status(
            params, std::forward<CompletionToken>(token));
    }

    /// Delete Margin Call Level (USER_DATA)
    ///
    /// DELETE /sapi/v1/portfolio/margin-call-level.
    ///
    /// Delete the margin call level for a Portfolio Margin account.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#delete-margin-call-level
    [[nodiscard]] common::RestApiResponse<DeleteMarginCallLevelResponse>
    delete_margin_call_level(const DeleteMarginCallLevelParams& params = {}) const {
        return account_api_.delete_margin_call_level(params);
    }
    /// Asynchronous `delete_margin_call_level()`.
    template <class CompletionToken>
    auto async_delete_margin_call_level(const DeleteMarginCallLevelParams& params,
                                        CompletionToken&& token) const {
        return account_api_.async_delete_margin_call_level(params,
                                                           std::forward<CompletionToken>(token));
    }

    /// Get Margin Call Level (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/margin-call-level.
    ///
    /// Get the margin call level for a Portfolio Margin account.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-margin-call-level
    [[nodiscard]] common::RestApiResponse<GetMarginCallLevelResponse>
    get_margin_call_level(const GetMarginCallLevelParams& params = {}) const {
        return account_api_.get_margin_call_level(params);
    }
    /// Asynchronous `get_margin_call_level()`.
    template <class CompletionToken>
    auto async_get_margin_call_level(const GetMarginCallLevelParams& params,
                                     CompletionToken&& token) const {
        return account_api_.async_get_margin_call_level(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Set Margin Call Level (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/margin-call-level.
    ///
    /// Set the margin call level for a Portfolio Margin account. When the account's uniMMR drops to
    /// the specified level, a notification will be sent via email and push/inbox.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#set-margin-call-level
    [[nodiscard]] common::RestApiResponse<SetMarginCallLevelResponse>
    set_margin_call_level(const SetMarginCallLevelParams& params) const {
        return account_api_.set_margin_call_level(params);
    }
    /// Asynchronous `set_margin_call_level()`.
    template <class CompletionToken>
    auto async_set_margin_call_level(const SetMarginCallLevelParams& params,
                                     CompletionToken&& token) const {
        return account_api_.async_set_margin_call_level(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Fund Auto-collection (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/auto-collection.
    ///
    /// Transfers all assets from Futures Account to Margin account
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The BNB would not be collected from UM-PM account to the Portfolio Margin account.
    /// - You can only use this function 500 times per hour in a rolling manner.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#fund-auto-collection
    [[nodiscard]] common::RestApiResponse<FundAutoCollectionResponse>
    fund_auto_collection(const FundAutoCollectionParams& params = {}) const {
        return account_api_.fund_auto_collection(params);
    }
    /// Asynchronous `fund_auto_collection()`.
    template <class CompletionToken>
    auto async_fund_auto_collection(const FundAutoCollectionParams& params,
                                    CompletionToken&& token) const {
        return account_api_.async_fund_auto_collection(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Fund Collection by Asset (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/asset-collection.
    ///
    /// Transfers specific asset from Futures Account to Margin account
    ///
    /// Weight(IP): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The BNB transfer is not be supported
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#fund-collection-by-asset
    [[nodiscard]] common::RestApiResponse<FundCollectionByAssetResponse>
    fund_collection_by_asset(const FundCollectionByAssetParams& params) const {
        return account_api_.fund_collection_by_asset(params);
    }
    /// Asynchronous `fund_collection_by_asset()`.
    template <class CompletionToken>
    auto async_fund_collection_by_asset(const FundCollectionByAssetParams& params,
                                        CompletionToken&& token) const {
        return account_api_.async_fund_collection_by_asset(params,
                                                           std::forward<CompletionToken>(token));
    }

    /// Get Delta Mode Status (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/delta-mode.
    ///
    /// Query the Delta mode status of current account.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-delta-mode-status
    [[nodiscard]] common::RestApiResponse<GetDeltaModeStatusResponse>
    get_delta_mode_status(const GetDeltaModeStatusParams& params = {}) const {
        return account_api_.get_delta_mode_status(params);
    }
    /// Asynchronous `get_delta_mode_status()`.
    template <class CompletionToken>
    auto async_get_delta_mode_status(const GetDeltaModeStatusParams& params,
                                     CompletionToken&& token) const {
        return account_api_.async_get_delta_mode_status(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Switch Delta Mode (TRADE)
    ///
    /// POST /sapi/v1/portfolio/delta-mode.
    ///
    /// Switch the Delta mode for existing PM PRO / PM RETAIL accounts.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#switch-delta-mode
    [[nodiscard]] common::RestApiResponse<SwitchDeltaModeResponse>
    switch_delta_mode(const SwitchDeltaModeParams& params) const {
        return account_api_.switch_delta_mode(params);
    }
    /// Asynchronous `switch_delta_mode()`.
    template <class CompletionToken>
    auto async_switch_delta_mode(const SwitchDeltaModeParams& params,
                                 CompletionToken&& token) const {
        return account_api_.async_switch_delta_mode(params, std::forward<CompletionToken>(token));
    }

    /// Get Portfolio Margin Pro Account Balance (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/balance.
    ///
    /// Query Portfolio Margin Pro account balance
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-portfolio-margin-pro-account-balance
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetPortfolioMarginProAccountBalanceResponseInner>>
    get_portfolio_margin_pro_account_balance(
        const GetPortfolioMarginProAccountBalanceParams& params = {}) const {
        return account_api_.get_portfolio_margin_pro_account_balance(params);
    }
    /// Asynchronous `get_portfolio_margin_pro_account_balance()`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_pro_account_balance(
        const GetPortfolioMarginProAccountBalanceParams& params, CompletionToken&& token) const {
        return account_api_.async_get_portfolio_margin_pro_account_balance(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Portfolio Margin Pro Account Info (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/account.
    ///
    /// Get Portfolio Margin Pro Account Info
    ///
    /// Weight(UID): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-portfolio-margin-pro-account-info
    [[nodiscard]] common::RestApiResponse<GetPortfolioMarginProAccountInfoResponse>
    get_portfolio_margin_pro_account_info(
        const GetPortfolioMarginProAccountInfoParams& params = {}) const {
        return account_api_.get_portfolio_margin_pro_account_info(params);
    }
    /// Asynchronous `get_portfolio_margin_pro_account_info()`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_pro_account_info(
        const GetPortfolioMarginProAccountInfoParams& params, CompletionToken&& token) const {
        return account_api_.async_get_portfolio_margin_pro_account_info(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Portfolio Margin Pro SPAN Account Info (USER_DATA)
    ///
    /// GET /sapi/v2/portfolio/account.
    ///
    /// Get Portfolio Margin Pro SPAN Account Info (For Portfolio Margin Pro SPAN users only)
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-portfolio-margin-pro-span-account-info
    [[nodiscard]] common::RestApiResponse<GetPortfolioMarginProSpanAccountInfoResponse>
    get_portfolio_margin_pro_span_account_info(
        const GetPortfolioMarginProSpanAccountInfoParams& params = {}) const {
        return account_api_.get_portfolio_margin_pro_span_account_info(params);
    }
    /// Asynchronous `get_portfolio_margin_pro_span_account_info()`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_pro_span_account_info(
        const GetPortfolioMarginProSpanAccountInfoParams& params, CompletionToken&& token) const {
        return account_api_.async_get_portfolio_margin_pro_span_account_info(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Transferable Earn Asset Balance for Portfolio Margin (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/earn-asset-balance.
    ///
    /// Get transferable earn asset balance for all types of Portfolio Margin account
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-transferable-earn-asset-balance-for-portfolio-margin
    [[nodiscard]] common::RestApiResponse<GetTransferableEarnAssetBalanceForPortfolioMarginResponse>
    get_transferable_earn_asset_balance_for_portfolio_margin(
        const GetTransferableEarnAssetBalanceForPortfolioMarginParams& params) const {
        return account_api_.get_transferable_earn_asset_balance_for_portfolio_margin(params);
    }
    /// Asynchronous `get_transferable_earn_asset_balance_for_portfolio_margin()`.
    template <class CompletionToken>
    auto async_get_transferable_earn_asset_balance_for_portfolio_margin(
        const GetTransferableEarnAssetBalanceForPortfolioMarginParams& params,
        CompletionToken&& token) const {
        return account_api_.async_get_transferable_earn_asset_balance_for_portfolio_margin(
            params, std::forward<CompletionToken>(token));
    }

    /// Portfolio Margin Pro Bankruptcy Loan Repay (TRADE)
    ///
    /// POST /sapi/v1/portfolio/repay.
    ///
    /// Repay Portfolio Margin Pro Bankruptcy Loan
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Please note that the API Key has enabled Spot & Margin Trading permissions to access this
    /// endpoint.
    /// - USDT is taken from the Spot account and transferred to the Cross Margin account to repay
    /// the loan.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#portfolio-margin-pro-bankruptcy-loan-repay
    [[nodiscard]] common::RestApiResponse<PortfolioMarginProBankruptcyLoanRepayResponse>
    portfolio_margin_pro_bankruptcy_loan_repay(
        const PortfolioMarginProBankruptcyLoanRepayParams& params = {}) const {
        return account_api_.portfolio_margin_pro_bankruptcy_loan_repay(params);
    }
    /// Asynchronous `portfolio_margin_pro_bankruptcy_loan_repay()`.
    template <class CompletionToken>
    auto async_portfolio_margin_pro_bankruptcy_loan_repay(
        const PortfolioMarginProBankruptcyLoanRepayParams& params, CompletionToken&& token) const {
        return account_api_.async_portfolio_margin_pro_bankruptcy_loan_repay(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Portfolio Margin Pro Bankruptcy Loan Amount (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/pmLoan.
    ///
    /// Query Portfolio Margin Pro Bankruptcy Loan Amount
    ///
    /// Weight(UID): 500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If there’s no classic portfolio margin bankruptcy loan, the amount would be 0
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#query-portfolio-margin-pro-bankruptcy-loan-amount
    [[nodiscard]] common::RestApiResponse<QueryPortfolioMarginProBankruptcyLoanAmountResponse>
    query_portfolio_margin_pro_bankruptcy_loan_amount(
        const QueryPortfolioMarginProBankruptcyLoanAmountParams& params = {}) const {
        return account_api_.query_portfolio_margin_pro_bankruptcy_loan_amount(params);
    }
    /// Asynchronous `query_portfolio_margin_pro_bankruptcy_loan_amount()`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_pro_bankruptcy_loan_amount(
        const QueryPortfolioMarginProBankruptcyLoanAmountParams& params,
        CompletionToken&& token) const {
        return account_api_.async_query_portfolio_margin_pro_bankruptcy_loan_amount(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Portfolio Margin Pro Bankruptcy Loan Repay History (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/pmloan-history.
    ///
    /// Query repay history of pmloan for portfolio margin pro.
    ///
    /// Weight(IP): 500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `startTime` and `endTime` cannot be longer than 360 days
    /// - If `startTime` and `endTime` not sent, return records of the last 30 days by default.
    /// - If `startTime`is sent and `endTime` is not sent, return records of [startTime,
    /// startTime+30d].
    /// - If `startTime` is not sent and `endTime` is sent, return records of [endTime-30d,
    /// endTime].
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#query-portfolio-margin-pro-bankruptcy-loan-repay-history
    [[nodiscard]] common::RestApiResponse<QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse>
    query_portfolio_margin_pro_bankruptcy_loan_repay_history(
        const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams& params = {}) const {
        return account_api_.query_portfolio_margin_pro_bankruptcy_loan_repay_history(params);
    }
    /// Asynchronous `query_portfolio_margin_pro_bankruptcy_loan_repay_history()`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_pro_bankruptcy_loan_repay_history(
        const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams& params,
        CompletionToken&& token) const {
        return account_api_.async_query_portfolio_margin_pro_bankruptcy_loan_repay_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Portfolio Margin Pro Negative Balance Interest History (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/interest-history.
    ///
    /// Query interest history of negative balance for portfolio margin.
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#query-portfolio-margin-pro-negative-balance-interest-history
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner>>
    query_portfolio_margin_pro_negative_balance_interest_history(
        const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams& params = {}) const {
        return account_api_.query_portfolio_margin_pro_negative_balance_interest_history(params);
    }
    /// Asynchronous `query_portfolio_margin_pro_negative_balance_interest_history()`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_pro_negative_balance_interest_history(
        const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams& params,
        CompletionToken&& token) const {
        return account_api_.async_query_portfolio_margin_pro_negative_balance_interest_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Repay futures Negative Balance (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/repay-futures-negative-balance.
    ///
    /// Repay futures Negative Balance
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The negative balance is repaid from the Cross Margin account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#repay-futures-negative-balance
    [[nodiscard]] common::RestApiResponse<RepayFuturesNegativeBalanceResponse>
    repay_futures_negative_balance(const RepayFuturesNegativeBalanceParams& params = {}) const {
        return account_api_.repay_futures_negative_balance(params);
    }
    /// Asynchronous `repay_futures_negative_balance()`.
    template <class CompletionToken>
    auto async_repay_futures_negative_balance(const RepayFuturesNegativeBalanceParams& params,
                                              CompletionToken&& token) const {
        return account_api_.async_repay_futures_negative_balance(
            params, std::forward<CompletionToken>(token));
    }

    /// Transfer LDUSDT/RWUSD for Portfolio Margin (TRADE)
    ///
    /// POST /sapi/v1/portfolio/earn-asset-transfer.
    ///
    /// Transfer LDUSDT/RWUSD as collateral for all types of Portfolio Margin account
    ///
    /// Weight(UID): 1500
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#transfer-ldusdt-rwusd-for-portfolio-margin
    [[nodiscard]] common::RestApiResponse<TransferLdusdtRwusdForPortfolioMarginResponse>
    transfer_ldusdt_rwusd_for_portfolio_margin(
        const TransferLdusdtRwusdForPortfolioMarginParams& params) const {
        return account_api_.transfer_ldusdt_rwusd_for_portfolio_margin(params);
    }
    /// Asynchronous `transfer_ldusdt_rwusd_for_portfolio_margin()`.
    template <class CompletionToken>
    auto async_transfer_ldusdt_rwusd_for_portfolio_margin(
        const TransferLdusdtRwusdForPortfolioMarginParams& params, CompletionToken&& token) const {
        return account_api_.async_transfer_ldusdt_rwusd_for_portfolio_margin(
            params, std::forward<CompletionToken>(token));
    }

    // MarketDataApi

    /// Get Portfolio Margin Asset Leverage (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/margin-asset-leverage.
    ///
    /// Get Portfolio Margin Asset Leverage
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#get-portfolio-margin-asset-leverage
    [[nodiscard]] common::RestApiResponse<std::vector<GetPortfolioMarginAssetLeverageResponseInner>>
    get_portfolio_margin_asset_leverage() const {
        return market_data_api_.get_portfolio_margin_asset_leverage();
    }
    /// Asynchronous `get_portfolio_margin_asset_leverage()`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_asset_leverage(CompletionToken&& token) const {
        return market_data_api_.async_get_portfolio_margin_asset_leverage(
            std::forward<CompletionToken>(token));
    }

    /// Get Portfolio Margin Tiered Collateral Rates (MARKET_DATA)
    ///
    /// GET /sapi/v2/portfolio/retail/collateralRate.
    ///
    /// Query the tiered collateral rate configurations for Portfolio Margin assets.
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#get-portfolio-margin-tiered-collateral-rates
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetPortfolioMarginTieredCollateralRatesResponseInner>>
    get_portfolio_margin_tiered_collateral_rates() const {
        return market_data_api_.get_portfolio_margin_tiered_collateral_rates();
    }
    /// Asynchronous `get_portfolio_margin_tiered_collateral_rates()`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_tiered_collateral_rates(CompletionToken&& token) const {
        return market_data_api_.async_get_portfolio_margin_tiered_collateral_rates(
            std::forward<CompletionToken>(token));
    }

    /// Portfolio Margin Collateral Rate (MARKET_DATA)
    ///
    /// GET /sapi/v1/portfolio/collateralRate.
    ///
    /// Portfolio Margin Collateral Rate
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#portfolio-margin-collateral-rate
    [[nodiscard]] common::RestApiResponse<std::vector<PortfolioMarginCollateralRateResponseInner>>
    portfolio_margin_collateral_rate() const {
        return market_data_api_.portfolio_margin_collateral_rate();
    }
    /// Asynchronous `portfolio_margin_collateral_rate()`.
    template <class CompletionToken>
    auto async_portfolio_margin_collateral_rate(CompletionToken&& token) const {
        return market_data_api_.async_portfolio_margin_collateral_rate(
            std::forward<CompletionToken>(token));
    }

    /// Portfolio Margin Pro Tiered Collateral Rate (USER_DATA)
    ///
    /// GET /sapi/v2/portfolio/collateralRate.
    ///
    /// Portfolio Margin PRO Tiered Collateral Rate
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#portfolio-margin-pro-tiered-collateral-rate
    [[nodiscard]] common::RestApiResponse<
        std::vector<PortfolioMarginProTieredCollateralRateResponseInner>>
    portfolio_margin_pro_tiered_collateral_rate(
        const PortfolioMarginProTieredCollateralRateParams& params = {}) const {
        return market_data_api_.portfolio_margin_pro_tiered_collateral_rate(params);
    }
    /// Asynchronous `portfolio_margin_pro_tiered_collateral_rate()`.
    template <class CompletionToken>
    auto async_portfolio_margin_pro_tiered_collateral_rate(
        const PortfolioMarginProTieredCollateralRateParams& params, CompletionToken&& token) const {
        return market_data_api_.async_portfolio_margin_pro_tiered_collateral_rate(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Portfolio Margin Asset Index Price (MARKET_DATA)
    ///
    /// GET /sapi/v1/portfolio/asset-index-price.
    ///
    /// Query Portfolio Margin Asset Index Price
    ///
    /// Weight: - 1 if `asset` is sent
    /// - 50 if `asset` is not sent
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#query-portfolio-margin-asset-index-price
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryPortfolioMarginAssetIndexPriceResponseInner>>
    query_portfolio_margin_asset_index_price(
        const QueryPortfolioMarginAssetIndexPriceParams& params = {}) const {
        return market_data_api_.query_portfolio_margin_asset_index_price(params);
    }
    /// Asynchronous `query_portfolio_margin_asset_index_price()`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_asset_index_price(
        const QueryPortfolioMarginAssetIndexPriceParams& params, CompletionToken&& token) const {
        return market_data_api_.async_query_portfolio_margin_asset_index_price(
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
    AccountApi account_api_;
    MarketDataApi market_data_api_;
};

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
