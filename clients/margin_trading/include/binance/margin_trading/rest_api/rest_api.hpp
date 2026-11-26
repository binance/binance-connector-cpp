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
#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/account_api.hpp>
#include <binance/margin_trading/rest_api/borrow_repay_api.hpp>
#include <binance/margin_trading/rest_api/market_data_api.hpp>
#include <binance/margin_trading/rest_api/models.hpp>
#include <binance/margin_trading/rest_api/trade_api.hpp>
#include <binance/margin_trading/rest_api/transfer_api.hpp>
#include <binance/margin_trading/rest_api/user_data_stream_api.hpp>

namespace binance::margin_trading::rest_api {

/// MarginTrading REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_MARGIN_TRADING_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Margin Trading REST API).
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

    /// Adjust cross margin max leverage (USER_DATA)
    ///
    /// POST /sapi/v1/margin/max-leverage.
    ///
    /// Adjust cross margin max leverage
    ///
    /// Weight(UID): 3000, 1 times/min per IP
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The margin level need higher than the initial risk ratio of adjusted leverage, the initial
    /// risk ratio of 3x is 1.5 , the initial risk ratio of 5x is 1.25; The detail conditions on how
    /// to switch between Cross Margin Classic and Cross Margin Pro can refer to the FAQ.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#adjust-cross-margin-max-leverage
    [[nodiscard]] common::RestApiResponse<AdjustCrossMarginMaxLeverageResponse>
    adjust_cross_margin_max_leverage(const AdjustCrossMarginMaxLeverageParams& params) const {
        return account_api_.adjust_cross_margin_max_leverage(params);
    }
    /// Asynchronous `adjust_cross_margin_max_leverage()`.
    template <class CompletionToken>
    auto async_adjust_cross_margin_max_leverage(const AdjustCrossMarginMaxLeverageParams& params,
                                                CompletionToken&& token) const {
        return account_api_.async_adjust_cross_margin_max_leverage(
            params, std::forward<CompletionToken>(token));
    }

    /// Disable Isolated Margin Account (TRADE)
    ///
    /// DELETE /sapi/v1/margin/isolated/account.
    ///
    /// Disable isolated margin account for a specific symbol. Each trading pair can only be
    /// deactivated once every 24 hours.
    ///
    /// Weight(UID): 300
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#disable-isolated-margin-account
    [[nodiscard]] common::RestApiResponse<DisableIsolatedMarginAccountResponse>
    disable_isolated_margin_account(const DisableIsolatedMarginAccountParams& params) const {
        return account_api_.disable_isolated_margin_account(params);
    }
    /// Asynchronous `disable_isolated_margin_account()`.
    template <class CompletionToken>
    auto async_disable_isolated_margin_account(const DisableIsolatedMarginAccountParams& params,
                                               CompletionToken&& token) const {
        return account_api_.async_disable_isolated_margin_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Enable Isolated Margin Account (TRADE)
    ///
    /// POST /sapi/v1/margin/isolated/account.
    ///
    /// Enable isolated margin account for a specific symbol(Only supports activation of previously
    /// disabled accounts).
    ///
    /// Weight(UID): 300
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#enable-isolated-margin-account
    [[nodiscard]] common::RestApiResponse<EnableIsolatedMarginAccountResponse>
    enable_isolated_margin_account(const EnableIsolatedMarginAccountParams& params) const {
        return account_api_.enable_isolated_margin_account(params);
    }
    /// Asynchronous `enable_isolated_margin_account()`.
    template <class CompletionToken>
    auto async_enable_isolated_margin_account(const EnableIsolatedMarginAccountParams& params,
                                              CompletionToken&& token) const {
        return account_api_.async_enable_isolated_margin_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Isolated Margin Account Info (USER_DATA)
    ///
    /// GET /sapi/v1/margin/isolated/account.
    ///
    /// Query Isolated Margin Account Info
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If "symbols" is not sent, all isolated assets will be returned.
    ///
    /// - If "symbols" is sent, only the isolated assets of the sent symbols
    /// will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#query-isolated-margin-account-info
    [[nodiscard]] common::RestApiResponse<QueryIsolatedMarginAccountInfoResponse>
    query_isolated_margin_account_info(
        const QueryIsolatedMarginAccountInfoParams& params = {}) const {
        return account_api_.query_isolated_margin_account_info(params);
    }
    /// Asynchronous `query_isolated_margin_account_info()`.
    template <class CompletionToken>
    auto
    async_query_isolated_margin_account_info(const QueryIsolatedMarginAccountInfoParams& params,
                                             CompletionToken&& token) const {
        return account_api_.async_query_isolated_margin_account_info(
            params, std::forward<CompletionToken>(token));
    }

    /// Get BNB Burn Status (USER_DATA)
    ///
    /// GET /sapi/v1/bnbBurn.
    ///
    /// Get BNB Burn Status
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#get-bnb-burn-status
    [[nodiscard]] common::RestApiResponse<GetBnbBurnStatusResponse>
    get_bnb_burn_status(const GetBnbBurnStatusParams& params = {}) const {
        return account_api_.get_bnb_burn_status(params);
    }
    /// Asynchronous `get_bnb_burn_status()`.
    template <class CompletionToken>
    auto async_get_bnb_burn_status(const GetBnbBurnStatusParams& params,
                                   CompletionToken&& token) const {
        return account_api_.async_get_bnb_burn_status(params, std::forward<CompletionToken>(token));
    }

    /// Get Summary of Margin account (USER_DATA)
    ///
    /// GET /sapi/v1/margin/tradeCoeff.
    ///
    /// Get personal margin level information
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#get-summary-of-margin-account
    [[nodiscard]] common::RestApiResponse<GetSummaryOfMarginAccountResponse>
    get_summary_of_margin_account(const GetSummaryOfMarginAccountParams& params = {}) const {
        return account_api_.get_summary_of_margin_account(params);
    }
    /// Asynchronous `get_summary_of_margin_account()`.
    template <class CompletionToken>
    auto async_get_summary_of_margin_account(const GetSummaryOfMarginAccountParams& params,
                                             CompletionToken&& token) const {
        return account_api_.async_get_summary_of_margin_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Cross Isolated Margin Capital Flow (USER_DATA)
    ///
    /// GET /sapi/v1/margin/capital-flow.
    ///
    /// Query Cross Isolated Margin Capital Flow
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Only supports querying the data of the last 90 days
    ///
    /// - The time between startTime and endTime cannot be longer than 7 days.
    ///
    /// - If both startTime and endTime are omitted, the most recent 7 days are
    /// queried (endTime defaults to the current time, and startTime to the
    /// current time minus 7 days).
    ///
    /// - If startTime is provided without endTime, endTime defaults to
    /// startTime plus 7 days.
    ///
    /// - If endTime is provided without startTime, startTime defaults to
    /// endTime minus 7 days.
    ///
    /// - If fromId is set, the data with id > fromId within the queried time
    /// range will be returned. Otherwise the latest data within that range will
    /// be returned. fromId does not extend the time range; to retrieve older
    /// records, move startTime and endTime backwards in windows of up to 7
    /// days.
    ///
    /// - To query isolated data, Symbol needs to be entered.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#query-cross-isolated-margin-capital-flow
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryCrossIsolatedMarginCapitalFlowResponseInner>>
    query_cross_isolated_margin_capital_flow(
        const QueryCrossIsolatedMarginCapitalFlowParams& params = {}) const {
        return account_api_.query_cross_isolated_margin_capital_flow(params);
    }
    /// Asynchronous `query_cross_isolated_margin_capital_flow()`.
    template <class CompletionToken>
    auto async_query_cross_isolated_margin_capital_flow(
        const QueryCrossIsolatedMarginCapitalFlowParams& params, CompletionToken&& token) const {
        return account_api_.async_query_cross_isolated_margin_capital_flow(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Cross Margin Account Details (USER_DATA)
    ///
    /// GET /sapi/v1/margin/account.
    ///
    /// Query Cross Margin Account Details
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#query-cross-margin-account-details
    [[nodiscard]] common::RestApiResponse<QueryCrossMarginAccountDetailsResponse>
    query_cross_margin_account_details(
        const QueryCrossMarginAccountDetailsParams& params = {}) const {
        return account_api_.query_cross_margin_account_details(params);
    }
    /// Asynchronous `query_cross_margin_account_details()`.
    template <class CompletionToken>
    auto
    async_query_cross_margin_account_details(const QueryCrossMarginAccountDetailsParams& params,
                                             CompletionToken&& token) const {
        return account_api_.async_query_cross_margin_account_details(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Cross Margin Fee Data (USER_DATA)
    ///
    /// GET /sapi/v1/margin/crossMarginData.
    ///
    /// Get cross margin fee data collection with any vip level or user's current specific data as
    /// https://www.binance.com/en/margin-fee
    ///
    /// Weight: 1 when coin is specified;(IP) 5 when the coin parameter is omitted(IP)
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#query-cross-margin-fee-data
    [[nodiscard]] common::RestApiResponse<std::vector<QueryCrossMarginFeeDataResponseInner>>
    query_cross_margin_fee_data(const QueryCrossMarginFeeDataParams& params = {}) const {
        return account_api_.query_cross_margin_fee_data(params);
    }
    /// Asynchronous `query_cross_margin_fee_data()`.
    template <class CompletionToken>
    auto async_query_cross_margin_fee_data(const QueryCrossMarginFeeDataParams& params,
                                           CompletionToken&& token) const {
        return account_api_.async_query_cross_margin_fee_data(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Query Enabled Isolated Margin Account Limit (USER_DATA)
    ///
    /// GET /sapi/v1/margin/isolated/accountLimit.
    ///
    /// Query enabled isolated margin account limit.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#query-enabled-isolated-margin-account-limit
    [[nodiscard]] common::RestApiResponse<QueryEnabledIsolatedMarginAccountLimitResponse>
    query_enabled_isolated_margin_account_limit(
        const QueryEnabledIsolatedMarginAccountLimitParams& params = {}) const {
        return account_api_.query_enabled_isolated_margin_account_limit(params);
    }
    /// Asynchronous `query_enabled_isolated_margin_account_limit()`.
    template <class CompletionToken>
    auto async_query_enabled_isolated_margin_account_limit(
        const QueryEnabledIsolatedMarginAccountLimitParams& params, CompletionToken&& token) const {
        return account_api_.async_query_enabled_isolated_margin_account_limit(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Isolated Margin Fee Data (USER_DATA)
    ///
    /// GET /sapi/v1/margin/isolatedMarginData.
    ///
    /// Get isolated margin fee data collection with any vip level or user's current specific data
    /// as https://www.binance.com/en/margin-fee
    ///
    /// Weight: 1 when a single is specified;(IP) 10 when the symbol parameter is omitted(IP)
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/account#query-isolated-margin-fee-data
    [[nodiscard]] common::RestApiResponse<std::vector<QueryIsolatedMarginFeeDataResponseInner>>
    query_isolated_margin_fee_data(const QueryIsolatedMarginFeeDataParams& params = {}) const {
        return account_api_.query_isolated_margin_fee_data(params);
    }
    /// Asynchronous `query_isolated_margin_fee_data()`.
    template <class CompletionToken>
    auto async_query_isolated_margin_fee_data(const QueryIsolatedMarginFeeDataParams& params,
                                              CompletionToken&& token) const {
        return account_api_.async_query_isolated_margin_fee_data(
            params, std::forward<CompletionToken>(token));
    }

    // BorrowRepayApi

    /// Get future hourly interest rate (USER_DATA)
    ///
    /// GET /sapi/v1/margin/next-hourly-interest-rate.
    ///
    /// Get future hourly interest rate
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/borrow-repay#get-future-hourly-interest-rate
    [[nodiscard]] common::RestApiResponse<std::vector<GetFutureHourlyInterestRateResponseInner>>
    get_future_hourly_interest_rate(const GetFutureHourlyInterestRateParams& params) const {
        return borrow_repay_api_.get_future_hourly_interest_rate(params);
    }
    /// Asynchronous `get_future_hourly_interest_rate()`.
    template <class CompletionToken>
    auto async_get_future_hourly_interest_rate(const GetFutureHourlyInterestRateParams& params,
                                               CompletionToken&& token) const {
        return borrow_repay_api_.async_get_future_hourly_interest_rate(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Interest History (USER_DATA)
    ///
    /// GET /sapi/v1/margin/interestHistory.
    ///
    /// Get Interest History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Response in descending order
    ///
    /// - If isolatedSymbol is not sent, crossed margin data will be returned
    ///
    /// - The max interval between `startTime` and `endTime` is 30 days. It is a
    /// MUST to ensure data correctness.
    ///
    /// - If `startTime`and `endTime` not sent, return records of the last 7
    /// days by default.
    ///
    /// - If `startTime` is sent and `endTime` is not sent, return records of
    /// [max(`startTime`, now-30d), now].
    ///
    /// - If `startTime` is not sent and `endTime` is sent, return records of
    /// [`endTime`-7, `endTime`]
    ///
    /// - `type` in response has 4 enums:
    ///
    /// - `PERIODIC` interest charged per hour
    ///
    /// - `ON_BORROW` first interest charged on borrow
    ///
    /// - `PERIODIC_CONVERTED` interest charged per hour converted into BNB
    ///
    /// - `ON_BORROW_CONVERTED` first interest charged on borrow converted into
    /// BNB
    ///
    /// - `PORTFOLIO` interest charged daily on the portfolio margin negative
    /// balance
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/borrow-repay#get-interest-history
    [[nodiscard]] common::RestApiResponse<GetInterestHistoryResponse>
    get_interest_history(const GetInterestHistoryParams& params = {}) const {
        return borrow_repay_api_.get_interest_history(params);
    }
    /// Asynchronous `get_interest_history()`.
    template <class CompletionToken>
    auto async_get_interest_history(const GetInterestHistoryParams& params,
                                    CompletionToken&& token) const {
        return borrow_repay_api_.async_get_interest_history(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Margin account borrow/repay (USER_DATA)
    ///
    /// POST /sapi/v1/margin/borrow-repay.
    ///
    /// Margin account borrow/repay
    ///
    /// Weight(UID): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `-3045 INSUFFICIENT_INVENTORY`: returned when system borrowable inventory is below the
    /// requested amount, or when inventory is severely insufficient (all borrow requests rejected
    /// regardless of size). Monitor system asset availability and adjust borrow strategy
    /// accordingly.
    /// - `-3006 EXCEED_MAX_BORROWABLE`: borrow amount exceeds your current max borrowable limit.
    /// Query `GET /sapi/v1/margin/maxBorrowable` and adjust the request.
    /// - `-3012 ASSET_ADMIN_BAN_BORROW`: this asset does not currently support borrowing. Query
    /// `GET /sapi/v1/margin/allAssets` for asset borrow availability.
    /// - `-3015 REPAY_EXCEED_LIABILITY`: returned in two scenarios — (1) repay amount exceeds your
    /// outstanding liability, or (2) the remaining unpaid debt after this repayment would fall
    /// below Binance's minimum threshold. Adjust the repay amount accordingly.
    /// - `-3007 HAS_PENDING_TRANSACTION`: a borrow/repay transaction is already in progress on this
    /// account. Requests are processed in submission order across all assets, and an in-flight
    /// request briefly blocks subsequent ones. Typical processing time is ~100ms; space consecutive
    /// requests by at least 100ms. Auto-repay orders can also fail silently for this reason —
    /// verify outstanding liability after an auto-repay executes.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/borrow-repay#margin-account-borrow-repay
    [[nodiscard]] common::RestApiResponse<MarginAccountBorrowRepayResponse>
    margin_account_borrow_repay(const MarginAccountBorrowRepayParams& params) const {
        return borrow_repay_api_.margin_account_borrow_repay(params);
    }
    /// Asynchronous `margin_account_borrow_repay()`.
    template <class CompletionToken>
    auto async_margin_account_borrow_repay(const MarginAccountBorrowRepayParams& params,
                                           CompletionToken&& token) const {
        return borrow_repay_api_.async_margin_account_borrow_repay(
            params, std::forward<CompletionToken>(token));
    }

    /// Query borrow/repay records in Margin account (USER_DATA)
    ///
    /// GET /sapi/v1/margin/borrow-repay.
    ///
    /// Query borrow/repay records in Margin account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `txId` or `startTime` must be sent. `txId` takes precedence.
    ///
    /// - Response in descending order
    ///
    /// - If an asset is sent, data within 30 days before `endTime`; If an asset is not sent, data
    /// within 7 days before `endTime`
    ///
    /// - If neither `startTime` nor `endTime` is sent, the recent 7-day data will be returned.
    ///
    /// - `startTime` set as `endTime` - 7 days by default, `endTime` set as current time by default
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/borrow-repay#query-borrow-repay-records-in-margin-account
    [[nodiscard]] common::RestApiResponse<QueryBorrowRepayRecordsInMarginAccountResponse>
    query_borrow_repay_records_in_margin_account(
        const QueryBorrowRepayRecordsInMarginAccountParams& params) const {
        return borrow_repay_api_.query_borrow_repay_records_in_margin_account(params);
    }
    /// Asynchronous `query_borrow_repay_records_in_margin_account()`.
    template <class CompletionToken>
    auto async_query_borrow_repay_records_in_margin_account(
        const QueryBorrowRepayRecordsInMarginAccountParams& params, CompletionToken&& token) const {
        return borrow_repay_api_.async_query_borrow_repay_records_in_margin_account(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Margin Interest Rate History (USER_DATA)
    ///
    /// GET /sapi/v1/margin/interestRateHistory.
    ///
    /// Query Margin Interest Rate History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/borrow-repay#query-margin-interest-rate-history
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginInterestRateHistoryResponseInner>>
    query_margin_interest_rate_history(const QueryMarginInterestRateHistoryParams& params) const {
        return borrow_repay_api_.query_margin_interest_rate_history(params);
    }
    /// Asynchronous `query_margin_interest_rate_history()`.
    template <class CompletionToken>
    auto
    async_query_margin_interest_rate_history(const QueryMarginInterestRateHistoryParams& params,
                                             CompletionToken&& token) const {
        return borrow_repay_api_.async_query_margin_interest_rate_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Max Borrow (USER_DATA)
    ///
    /// GET /sapi/v1/margin/maxBorrowable.
    ///
    /// Query Max Borrow
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If isolatedSymbol is not sent, crossed margin data will be sent.
    /// - `borrowLimit` is also available from https://www.binance.com/en/margin-fee
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/borrow-repay#query-max-borrow
    [[nodiscard]] common::RestApiResponse<QueryMaxBorrowResponse>
    query_max_borrow(const QueryMaxBorrowParams& params) const {
        return borrow_repay_api_.query_max_borrow(params);
    }
    /// Asynchronous `query_max_borrow()`.
    template <class CompletionToken>
    auto async_query_max_borrow(const QueryMaxBorrowParams& params, CompletionToken&& token) const {
        return borrow_repay_api_.async_query_max_borrow(params,
                                                        std::forward<CompletionToken>(token));
    }

    // MarketDataApi

    /// Cross margin collateral ratio (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/crossMarginCollateralRatio.
    ///
    /// Cross margin collateral ratio
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#cross-margin-collateral-ratio
    [[nodiscard]] common::RestApiResponse<std::vector<CrossMarginCollateralRatioResponseInner>>
    cross_margin_collateral_ratio() const {
        return market_data_api_.cross_margin_collateral_ratio();
    }
    /// Asynchronous `cross_margin_collateral_ratio()`.
    template <class CompletionToken>
    auto async_cross_margin_collateral_ratio(CompletionToken&& token) const {
        return market_data_api_.async_cross_margin_collateral_ratio(
            std::forward<CompletionToken>(token));
    }

    /// Get All Cross Margin Pairs (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/allPairs.
    ///
    /// Get All Cross Margin Pairs
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-all-cross-margin-pairs
    [[nodiscard]] common::RestApiResponse<std::vector<GetAllCrossMarginPairsResponseInner>>
    get_all_cross_margin_pairs(const GetAllCrossMarginPairsParams& params = {}) const {
        return market_data_api_.get_all_cross_margin_pairs(params);
    }
    /// Asynchronous `get_all_cross_margin_pairs()`.
    template <class CompletionToken>
    auto async_get_all_cross_margin_pairs(const GetAllCrossMarginPairsParams& params,
                                          CompletionToken&& token) const {
        return market_data_api_.async_get_all_cross_margin_pairs(
            params, std::forward<CompletionToken>(token));
    }

    /// Get All Isolated Margin Symbol (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/isolated/allPairs.
    ///
    /// Get All Isolated Margin Symbol
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-all-isolated-margin-symbol
    [[nodiscard]] common::RestApiResponse<std::vector<GetAllIsolatedMarginSymbolResponseInner>>
    get_all_isolated_margin_symbol(const GetAllIsolatedMarginSymbolParams& params = {}) const {
        return market_data_api_.get_all_isolated_margin_symbol(params);
    }
    /// Asynchronous `get_all_isolated_margin_symbol()`.
    template <class CompletionToken>
    auto async_get_all_isolated_margin_symbol(const GetAllIsolatedMarginSymbolParams& params,
                                              CompletionToken&& token) const {
        return market_data_api_.async_get_all_isolated_margin_symbol(
            params, std::forward<CompletionToken>(token));
    }

    /// Get All Margin Assets (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/allAssets.
    ///
    /// Get All Margin Assets.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-all-margin-assets
    [[nodiscard]] common::RestApiResponse<std::vector<GetAllMarginAssetsResponseInner>>
    get_all_margin_assets(const GetAllMarginAssetsParams& params = {}) const {
        return market_data_api_.get_all_margin_assets(params);
    }
    /// Asynchronous `get_all_margin_assets()`.
    template <class CompletionToken>
    auto async_get_all_margin_assets(const GetAllMarginAssetsParams& params,
                                     CompletionToken&& token) const {
        return market_data_api_.async_get_all_margin_assets(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Get Delist Schedule (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/delist-schedule.
    ///
    /// Get tokens or symbols delist schedule for cross margin and isolated margin
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-delist-schedule
    [[nodiscard]] common::RestApiResponse<std::vector<GetDelistScheduleResponseInner>>
    get_delist_schedule(const GetDelistScheduleParams& params = {}) const {
        return market_data_api_.get_delist_schedule(params);
    }
    /// Asynchronous `get_delist_schedule()`.
    template <class CompletionToken>
    auto async_get_delist_schedule(const GetDelistScheduleParams& params,
                                   CompletionToken&& token) const {
        return market_data_api_.async_get_delist_schedule(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Get Limit Price Pairs (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/limit-price-pairs.
    ///
    /// Query trading pairs with restriction on limit price range.
    ///
    /// In margin trading, you can place orders with limit price. Limit price
    /// should be within (-15%, 15%) of current index price for a list of margin
    /// trading pairs. This rule only impacts limit sell orders with limit price
    /// that is lower than current index price and limit buy orders with limit
    /// price that is higher than current index price.
    ///
    /// - Buy order: Your order will be rejected with an error message
    /// notification if the limit price is 15% above the index price.
    ///
    /// - Sell order: Your order will be rejected with an error message
    /// notification if the limit price is 15% below the index price.
    ///
    /// Please review the limit price order placing strategy, backtest and
    /// calibrate the planned order size with the trading volume and order book
    /// depth to prevent trading loss.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-limit-price-pairs
    [[nodiscard]] common::RestApiResponse<GetLimitPricePairsResponse>
    get_limit_price_pairs() const {
        return market_data_api_.get_limit_price_pairs();
    }
    /// Asynchronous `get_limit_price_pairs()`.
    template <class CompletionToken>
    auto async_get_limit_price_pairs(CompletionToken&& token) const {
        return market_data_api_.async_get_limit_price_pairs(std::forward<CompletionToken>(token));
    }

    /// Get list Schedule (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/list-schedule.
    ///
    /// Get the upcoming tokens or symbols listing schedule for Cross Margin and Isolated Margin.
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-list-schedule
    [[nodiscard]] common::RestApiResponse<std::vector<GetListScheduleResponseInner>>
    get_list_schedule(const GetListScheduleParams& params = {}) const {
        return market_data_api_.get_list_schedule(params);
    }
    /// Asynchronous `get_list_schedule()`.
    template <class CompletionToken>
    auto async_get_list_schedule(const GetListScheduleParams& params,
                                 CompletionToken&& token) const {
        return market_data_api_.async_get_list_schedule(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Get Margin Asset Risk-Based Liquidation Ratio (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/risk-based-liquidation-ratio.
    ///
    /// Get Margin Asset Risk-Based Liquidation Ratio
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-margin-asset-risk-based-liquidation-ratio
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetMarginAssetRiskBasedLiquidationRatioResponseInner>>
    get_margin_asset_risk_based_liquidation_ratio() const {
        return market_data_api_.get_margin_asset_risk_based_liquidation_ratio();
    }
    /// Asynchronous `get_margin_asset_risk_based_liquidation_ratio()`.
    template <class CompletionToken>
    auto async_get_margin_asset_risk_based_liquidation_ratio(CompletionToken&& token) const {
        return market_data_api_.async_get_margin_asset_risk_based_liquidation_ratio(
            std::forward<CompletionToken>(token));
    }

    /// Get Margin Restricted Assets (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/restricted-asset.
    ///
    /// Get the list of margin-restricted assets.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-margin-restricted-assets
    [[nodiscard]] common::RestApiResponse<GetMarginRestrictedAssetsResponse>
    get_margin_restricted_assets() const {
        return market_data_api_.get_margin_restricted_assets();
    }
    /// Asynchronous `get_margin_restricted_assets()`.
    template <class CompletionToken>
    auto async_get_margin_restricted_assets(CompletionToken&& token) const {
        return market_data_api_.async_get_margin_restricted_assets(
            std::forward<CompletionToken>(token));
    }

    /// Query Isolated Margin Tier Data (USER_DATA)
    ///
    /// GET /sapi/v1/margin/isolatedMarginTier.
    ///
    /// Get isolated margin tier data collection with any tier as
    /// https://www.binance.com/en/margin-data
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#query-isolated-margin-tier-data
    [[nodiscard]] common::RestApiResponse<std::vector<QueryIsolatedMarginTierDataResponseInner>>
    query_isolated_margin_tier_data(const QueryIsolatedMarginTierDataParams& params) const {
        return market_data_api_.query_isolated_margin_tier_data(params);
    }
    /// Asynchronous `query_isolated_margin_tier_data()`.
    template <class CompletionToken>
    auto async_query_isolated_margin_tier_data(const QueryIsolatedMarginTierDataParams& params,
                                               CompletionToken&& token) const {
        return market_data_api_.async_query_isolated_margin_tier_data(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Liability Coin Leverage Bracket in Cross Margin Pro Mode (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/leverageBracket.
    ///
    /// Liability Coin Leverage Bracket in Cross Margin Pro Mode
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#query-liability-coin-leverage-bracket-in-cross-margin-pro-mode
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner>>
    query_liability_coin_leverage_bracket_in_cross_margin_pro_mode() const {
        return market_data_api_.query_liability_coin_leverage_bracket_in_cross_margin_pro_mode();
    }
    /// Asynchronous `query_liability_coin_leverage_bracket_in_cross_margin_pro_mode()`.
    template <class CompletionToken>
    auto async_query_liability_coin_leverage_bracket_in_cross_margin_pro_mode(
        CompletionToken&& token) const {
        return market_data_api_
            .async_query_liability_coin_leverage_bracket_in_cross_margin_pro_mode(
                std::forward<CompletionToken>(token));
    }

    /// Query Margin Available Inventory (USER_DATA)
    ///
    /// GET /sapi/v1/margin/available-inventory.
    ///
    /// Margin available Inventory query
    ///
    /// Weight(UID): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#query-margin-available-inventory
    [[nodiscard]] common::RestApiResponse<QueryMarginAvailableInventoryResponse>
    query_margin_available_inventory(const QueryMarginAvailableInventoryParams& params) const {
        return market_data_api_.query_margin_available_inventory(params);
    }
    /// Asynchronous `query_margin_available_inventory()`.
    template <class CompletionToken>
    auto async_query_margin_available_inventory(const QueryMarginAvailableInventoryParams& params,
                                                CompletionToken&& token) const {
        return market_data_api_.async_query_margin_available_inventory(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Margin PriceIndex (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/priceIndex.
    ///
    /// Query Margin PriceIndex
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#query-margin-priceindex
    [[nodiscard]] common::RestApiResponse<QueryMarginPriceindexResponse>
    query_margin_priceindex(const QueryMarginPriceindexParams& params) const {
        return market_data_api_.query_margin_priceindex(params);
    }
    /// Asynchronous `query_margin_priceindex()`.
    template <class CompletionToken>
    auto async_query_margin_priceindex(const QueryMarginPriceindexParams& params,
                                       CompletionToken&& token) const {
        return market_data_api_.async_query_margin_priceindex(params,
                                                              std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// Create Special Key(Low-Latency Trading) (TRADE)
    ///
    /// POST /sapi/v1/margin/apiKey.
    ///
    /// **Eligibility**
    ///
    /// - Binance Margin offers low-latency trading through a special key, available exclusively to
    /// users with VIP level 7 or higher.
    /// - If you are VIP level 6 or below, please contact your VIP manager for eligibility
    /// criterias.
    /// - All new Margin Special Key users are required to read, understand, and agree to the Margin
    /// Special Key Supplemental Product Terms at the master account level before creating a Margin
    /// Special Key.
    /// - Once signed at the master account level, the agreement applies to all sub-accounts. The
    /// master account and all sub-accounts (Cross Margin Classic and Portfolio Margin Pro) are
    /// authorized to create a Margin Special Key and are subject to the LiquidationLoan policy.
    ///
    /// For more information, please refer to FAQ.
    ///
    /// **Supported Products:**
    ///
    /// - Cross Margin
    /// - Isolated Margin
    /// - Portfolio Margin Pro
    ///
    /// **Unsupported Products:**
    ///
    /// - Portfolio Margin
    ///
    /// We support several types of API keys:
    ///
    /// * Ed25519 (recommended)
    /// * HMAC
    /// * RSA
    ///
    /// We recommend to **use Ed25519 API keys** as it should provide the best performance and
    /// security out of all supported key types. We accept PKCS#8 (BEGIN PUBLIC KEY). For how to
    /// generate an RSA key pair to send API requests on Binance. Please refer to the document below
    /// FAQ .
    ///
    /// **How to use the Margin Special Key**
    /// - Use the below `sapi` endpoint to create your margin special API Key.
    /// - For accessing the Cross Margin account, do not send the `symbol` parameter.
    /// - For accessing the Isolated Margin account(s), pass the relevant `symbol` parameter in the
    /// API Key creation request.
    /// - Use the generated API Key (and Secret key, if applicable) to perform margin trading and
    /// listenKey generation via **Spot** REST API (`https://api.binance.com/api/v3/*`) endpoints.
    ///
    /// Read REST API or WebSocket API documentation to learn how to use different API keys
    ///
    /// You need to enable Permits “Enable Spot & Margin Trading” option for the API Key which
    /// requests this endpoint.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// Response Notes:
    /// - Error Code Description
    ///
    /// - **UNSUPPORTED_OPERATION** : Portfolio Margin is an unsupported
    /// product, please change the account type to a supported margin product.
    ///
    /// - **Forbidden**:  Cross Margin Pro accounts require additional
    /// agreements, please contact your relationship manager.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#create-special-key
    [[nodiscard]] common::RestApiResponse<CreateSpecialKeyResponse>
    create_special_key(const CreateSpecialKeyParams& params) const {
        return trade_api_.create_special_key(params);
    }
    /// Asynchronous `create_special_key()`.
    template <class CompletionToken>
    auto async_create_special_key(const CreateSpecialKeyParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_create_special_key(params, std::forward<CompletionToken>(token));
    }

    /// Delete Special Key(Low-Latency Trading) (TRADE)
    ///
    /// DELETE /sapi/v1/margin/apiKey.
    ///
    /// Deleting your Margin Special Key alone does not exit you from the Margin Special Key
    /// framework or discharge your obligations under the Margin Special Key Supplemental Product
    /// Terms. To fully exit, you must:
    ///
    /// 1. Delete your Margin Special Key.
    /// 2. Ensure there are no outstanding liabilities on the account.
    /// 3. Call the Exit Margin Special Key API endpoint.
    /// 4. Confirm the exit status via the API response.
    ///
    /// Only after step 4 is completed and the exit status is confirmed by Binance will your account
    /// revert to standard liquidation logic and no longer be subject to the Margin Special Key
    /// Supplemental Product Terms.
    ///
    /// If apiKey is given, apiName will be ignored. If apiName is given with no
    /// apiKey, all apikeys with given apiName will be deleted.
    ///
    /// You need to enable Permits “Enable Spot & Margin” option for the API Key
    /// which requests this endpoint.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#delete-special-key
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    delete_special_key(const DeleteSpecialKeyParams& params = {}) const {
        return trade_api_.delete_special_key(params);
    }
    /// Asynchronous `delete_special_key()`.
    template <class CompletionToken>
    auto async_delete_special_key(const DeleteSpecialKeyParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_delete_special_key(params, std::forward<CompletionToken>(token));
    }

    /// Query Special key(Low Latency Trading) (TRADE)
    ///
    /// GET /sapi/v1/margin/apiKey.
    ///
    /// Query Special Key Information.
    ///
    /// This only applies to Special Key for Low Latency Trading.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-special-key
    [[nodiscard]] common::RestApiResponse<QuerySpecialKeyResponse>
    query_special_key(const QuerySpecialKeyParams& params = {}) const {
        return trade_api_.query_special_key(params);
    }
    /// Asynchronous `query_special_key()`.
    template <class CompletionToken>
    auto async_query_special_key(const QuerySpecialKeyParams& params,
                                 CompletionToken&& token) const {
        return trade_api_.async_query_special_key(params, std::forward<CompletionToken>(token));
    }

    /// Edit ip for Special Key(Low-Latency Trading) (TRADE)
    ///
    /// PUT /sapi/v1/margin/apiKey/ip.
    ///
    /// Edit ip restriction. This only applies to Special Key for Low Latency
    /// Trading.
    ///
    /// You need to enable Permits “Enable Spot & Margin” option for the API Key
    /// which requests this endpoint.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#edit-ip-for-special-key
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    edit_ip_for_special_key(const EditIpForSpecialKeyParams& params) const {
        return trade_api_.edit_ip_for_special_key(params);
    }
    /// Asynchronous `edit_ip_for_special_key()`.
    template <class CompletionToken>
    auto async_edit_ip_for_special_key(const EditIpForSpecialKeyParams& params,
                                       CompletionToken&& token) const {
        return trade_api_.async_edit_ip_for_special_key(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Exit Special Key Mode (TRADE)
    ///
    /// POST /sapi/v1/margin/exit-special-key-mode.
    ///
    /// Exit the Margin Special Key mode for Cross Margin Classic accounts.
    ///
    /// **All outstanding liabilities under the Cross Margin Classic account must be fully repaid
    /// before calling this endpoint.** Deleting the Margin Special Key alone does not constitute a
    /// valid exit.
    ///
    /// When a user creates a Margin Special API Key, the account enters "Special Key Mode". Upon a
    /// successful request, the following actions will be performed atomically:
    ///
    /// 1. All existing Margin Special API Keys under the Cross Margin Classic mode account will be
    /// deleted.
    /// 2. All pre-execution margin checks (including Open-order-loss calculation) will revert to
    /// standard mode.
    /// 3. A cooldown period (default: 24 hours) will be enforced, during which the account will not
    /// be permitted to create new Margin Special API Keys.
    ///
    /// For more information, please refer to FAQ.
    ///
    /// **Preconditions:**
    ///
    /// The following conditions must be met; otherwise the request will be rejected:
    ///
    /// - Account type must be **Cross Margin Classic**.
    /// - Account must currently be in **Special Key Mode**. If not, the request silently succeeds.
    /// - Account must **not be in liquidation**.
    /// - Account must **have no liability**.
    ///
    /// You need to enable "Permits Enable Spot & Margin Trading" option for the API Key which
    /// requests this endpoint.
    ///
    /// Weight(UID): 10
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#exit-special-key-mode
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    exit_special_key_mode(const ExitSpecialKeyModeParams& params = {}) const {
        return trade_api_.exit_special_key_mode(params);
    }
    /// Asynchronous `exit_special_key_mode()`.
    template <class CompletionToken>
    auto async_exit_special_key_mode(const ExitSpecialKeyModeParams& params,
                                     CompletionToken&& token) const {
        return trade_api_.async_exit_special_key_mode(params, std::forward<CompletionToken>(token));
    }

    /// Get Force Liquidation Record (USER_DATA)
    ///
    /// GET /sapi/v1/margin/forceLiquidationRec.
    ///
    /// Get Force Liquidation Record
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Response in descending order
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#get-force-liquidation-record
    [[nodiscard]] common::RestApiResponse<GetForceLiquidationRecordResponse>
    get_force_liquidation_record(const GetForceLiquidationRecordParams& params = {}) const {
        return trade_api_.get_force_liquidation_record(params);
    }
    /// Asynchronous `get_force_liquidation_record()`.
    template <class CompletionToken>
    auto async_get_force_liquidation_record(const GetForceLiquidationRecordParams& params,
                                            CompletionToken&& token) const {
        return trade_api_.async_get_force_liquidation_record(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Get Small Liability Exchange Coin List (USER_DATA)
    ///
    /// GET /sapi/v1/margin/exchange-small-liability.
    ///
    /// Query the coins which can be small liability exchange
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#get-small-liability-exchange-coin-list
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetSmallLiabilityExchangeCoinListResponseInner>>
    get_small_liability_exchange_coin_list(
        const GetSmallLiabilityExchangeCoinListParams& params = {}) const {
        return trade_api_.get_small_liability_exchange_coin_list(params);
    }
    /// Asynchronous `get_small_liability_exchange_coin_list()`.
    template <class CompletionToken>
    auto async_get_small_liability_exchange_coin_list(
        const GetSmallLiabilityExchangeCoinListParams& params, CompletionToken&& token) const {
        return trade_api_.async_get_small_liability_exchange_coin_list(
            params, std::forward<CompletionToken>(token));
    }

    /// Small Liability Exchange (MARGIN)
    ///
    /// POST /sapi/v1/margin/exchange-small-liability.
    ///
    /// Small Liability Exchange
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: MARGIN
    ///
    /// Notes:
    /// - Only convert once within 6 hours
    /// - Only liability valuation less than 10 USDT are supported
    /// - The maximum number of coin is 10
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#small-liability-exchange
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    small_liability_exchange(const SmallLiabilityExchangeParams& params) const {
        return trade_api_.small_liability_exchange(params);
    }
    /// Asynchronous `small_liability_exchange()`.
    template <class CompletionToken>
    auto async_small_liability_exchange(const SmallLiabilityExchangeParams& params,
                                        CompletionToken&& token) const {
        return trade_api_.async_small_liability_exchange(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Get Small Liability Exchange History (USER_DATA)
    ///
    /// GET /sapi/v1/margin/exchange-small-liability-history.
    ///
    /// Get Small liability Exchange History
    ///
    /// Weight(UID): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#get-small-liability-exchange-history
    [[nodiscard]] common::RestApiResponse<GetSmallLiabilityExchangeHistoryResponse>
    get_small_liability_exchange_history(
        const GetSmallLiabilityExchangeHistoryParams& params) const {
        return trade_api_.get_small_liability_exchange_history(params);
    }
    /// Asynchronous `get_small_liability_exchange_history()`.
    template <class CompletionToken>
    auto
    async_get_small_liability_exchange_history(const GetSmallLiabilityExchangeHistoryParams& params,
                                               CompletionToken&& token) const {
        return trade_api_.async_get_small_liability_exchange_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Liquidation Loan Repay (MARGIN)
    ///
    /// POST /sapi/v1/margin/liquidation-loan/repay.
    ///
    /// Repays the outstanding cross-margin liquidation loan from the user's spot wallet. A
    /// liquidation loan represents the account deficit incurred when account equity turns negative
    /// during liquidation (bankruptcy). The repayment amount must be greater than 0 and cannot
    /// exceed the remaining loan balance. If the Spot Account has insufficient USDC balance, the
    /// repayment will fail.
    ///
    /// Weight(UID): 100
    ///
    /// Security Type: MARGIN
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#liquidation-loan-repay
    [[nodiscard]] common::RestApiResponse<LiquidationLoanRepayResponse>
    liquidation_loan_repay(const LiquidationLoanRepayParams& params) const {
        return trade_api_.liquidation_loan_repay(params);
    }
    /// Asynchronous `liquidation_loan_repay()`.
    template <class CompletionToken>
    auto async_liquidation_loan_repay(const LiquidationLoanRepayParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_liquidation_loan_repay(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Margin Account Cancel all Open Orders on a Symbol (TRADE)
    ///
    /// DELETE /sapi/v1/margin/openOrders.
    ///
    /// Cancels all active orders on a symbol for margin account.
    ///
    /// This includes OCO orders.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-cancel-all-open-orders-on-asymbol
    [[nodiscard]] common::RestApiResponse<
        std::vector<MarginAccountCancelAllOpenOrdersOnASymbolResponseInner>>
    margin_account_cancel_all_open_orders_on_a_symbol(
        const MarginAccountCancelAllOpenOrdersOnASymbolParams& params) const {
        return trade_api_.margin_account_cancel_all_open_orders_on_a_symbol(params);
    }
    /// Asynchronous `margin_account_cancel_all_open_orders_on_a_symbol()`.
    template <class CompletionToken>
    auto async_margin_account_cancel_all_open_orders_on_a_symbol(
        const MarginAccountCancelAllOpenOrdersOnASymbolParams& params,
        CompletionToken&& token) const {
        return trade_api_.async_margin_account_cancel_all_open_orders_on_a_symbol(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Open Orders (USER_DATA)
    ///
    /// GET /sapi/v1/margin/openOrders.
    ///
    /// Query Margin Account's Open Orders
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If the symbol is not sent, orders for all symbols will be returned in
    /// an array.
    ///
    /// - When all symbols are returned, the number of requests counted against
    /// the rate limiter is equal to the number of symbols currently trading on
    /// the exchange.
    ///
    /// - If isIsolated ="TRUE", symbol must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsOpenOrdersResponseInner>>
    query_margin_accounts_open_orders(
        const QueryMarginAccountsOpenOrdersParams& params = {}) const {
        return trade_api_.query_margin_accounts_open_orders(params);
    }
    /// Asynchronous `query_margin_accounts_open_orders()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_open_orders(const QueryMarginAccountsOpenOrdersParams& params,
                                                 CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_open_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Margin Account Cancel OCO (TRADE)
    ///
    /// DELETE /sapi/v1/margin/orderList.
    ///
    /// Cancel an entire Order List for a margin account.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Canceling an individual leg will cancel the entire OCO
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-cancel-oco
    [[nodiscard]] common::RestApiResponse<MarginAccountCancelOcoResponse>
    margin_account_cancel_oco(const MarginAccountCancelOcoParams& params) const {
        return trade_api_.margin_account_cancel_oco(params);
    }
    /// Asynchronous `margin_account_cancel_oco()`.
    template <class CompletionToken>
    auto async_margin_account_cancel_oco(const MarginAccountCancelOcoParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_margin_account_cancel_oco(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's OCO (USER_DATA)
    ///
    /// GET /sapi/v1/margin/orderList.
    ///
    /// Retrieves a specific OCO based on provided optional parameters
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-oco
    [[nodiscard]] common::RestApiResponse<QueryMarginAccountsOcoResponse>
    query_margin_accounts_oco(const QueryMarginAccountsOcoParams& params = {}) const {
        return trade_api_.query_margin_accounts_oco(params);
    }
    /// Asynchronous `query_margin_accounts_oco()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_oco(const QueryMarginAccountsOcoParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_oco(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Margin Account Cancel Order (TRADE)
    ///
    /// DELETE /sapi/v1/margin/order.
    ///
    /// Cancel an active order for margin account.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either orderId or origClientOrderId must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-cancel-order
    [[nodiscard]] common::RestApiResponse<MarginAccountCancelOrderResponse>
    margin_account_cancel_order(const MarginAccountCancelOrderParams& params) const {
        return trade_api_.margin_account_cancel_order(params);
    }
    /// Asynchronous `margin_account_cancel_order()`.
    template <class CompletionToken>
    auto async_margin_account_cancel_order(const MarginAccountCancelOrderParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_margin_account_cancel_order(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Margin Account New Order (TRADE)
    ///
    /// POST /sapi/v1/margin/order.
    ///
    /// Post a new order for margin account.
    ///
    /// Weight: 6(UID) or 1500(UID) when sideEffectType is MARGIN_BUY or AUTO_BORROW_REPAY
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - autoRepayAtCancel is suggested to set as “FALSE” to keep liability unrepaid under high
    /// frequent new order/cancel order execution
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-new-order
    [[nodiscard]] common::RestApiResponse<MarginAccountNewOrderResponse>
    margin_account_new_order(const MarginAccountNewOrderParams& params) const {
        return trade_api_.margin_account_new_order(params);
    }
    /// Asynchronous `margin_account_new_order()`.
    template <class CompletionToken>
    auto async_margin_account_new_order(const MarginAccountNewOrderParams& params,
                                        CompletionToken&& token) const {
        return trade_api_.async_margin_account_new_order(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Order (USER_DATA)
    ///
    /// GET /sapi/v1/margin/order.
    ///
    /// Query Margin Account's Order
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either orderId or origClientOrderId must be sent.
    ///
    /// - For some historical orders cummulativeQuoteQty will be < 0, meaning
    /// the data is not available at this time.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-order
    [[nodiscard]] common::RestApiResponse<QueryMarginAccountsOrderResponse>
    query_margin_accounts_order(const QueryMarginAccountsOrderParams& params) const {
        return trade_api_.query_margin_accounts_order(params);
    }
    /// Asynchronous `query_margin_accounts_order()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_order(const QueryMarginAccountsOrderParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_order(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Margin Account New OCO (TRADE)
    ///
    /// POST /sapi/v1/margin/order/oco.
    ///
    /// Send in a new OCO for a margin account
    ///
    /// Weight: 6(UID) or 1500(UID) when sideEffectType is MARGIN_BUY or AUTO_BORROW_REPAY
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - autoRepayAtCancel is suggested to set as “FALSE” to keep liability unrepaid under high
    /// frequent new order/cancel order execution
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-new-oco
    [[nodiscard]] common::RestApiResponse<MarginAccountNewOcoResponse>
    margin_account_new_oco(const MarginAccountNewOcoParams& params) const {
        return trade_api_.margin_account_new_oco(params);
    }
    /// Asynchronous `margin_account_new_oco()`.
    template <class CompletionToken>
    auto async_margin_account_new_oco(const MarginAccountNewOcoParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_margin_account_new_oco(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Margin Account New OTO (TRADE)
    ///
    /// POST /sapi/v1/margin/order/oto.
    ///
    /// Post a new OTO order for margin account:
    ///
    /// - An OTO (One-Triggers-the-Other) is an order list comprised of 2
    /// orders.
    ///
    /// - The first order is called the **working order** and must be `LIMIT` or
    /// `LIMIT_MAKER`. Initially, only the working order goes on the order book.
    ///
    /// - The second order is called the **pending order**. It can be any order
    /// type except for `MARKET` orders using parameter `quoteOrderQty`. The
    /// pending order is only placed on the order book when the working order
    /// gets **fully filled**.
    ///
    /// - If either the working order or the pending order is cancelled
    /// individually, the other order in the order list will also be canceled or
    /// expired.
    ///
    /// - When the order list is placed, if the working order gets **immediately
    /// fully filled**, the placement response will show the working order as
    /// `FILLED` but the pending order will still appear as `PENDING_NEW`. You
    /// need to query the status of the pending order again to see its updated
    /// status.
    ///
    /// - OTOs add **2 orders** to the unfilled order count,
    /// `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS` filter.
    ///
    /// Weight: 6(UID) or 1500(UID) when sideEffectType is MARGIN_BUY or AUTO_BORROW_REPAY
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - autoRepayAtCancel is suggested to set as “FALSE” to keep liability unrepaid under high
    /// frequent new order/cancel order execution
    /// - Depending on the `pendingType` or `workingType`, some optional parameters will become
    /// mandatory:
    ///
    /// | Type | Additional mandatory parameters | Additional information |
    /// | --- | --- | --- |
    /// | `workingType` = `LIMIT` | `workingTimeInForce` | |
    /// | `pendingType` = `LIMIT` | `pendingPrice`, `pendingTimeInForce` | |
    /// | `pendingType` = `STOP_LOSS` or `TAKE_PROFIT` | `pendingStopPrice` and/or
    /// `pendingTrailingDelta` | | | `pendingType` = `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT` |
    /// `pendingPrice`, `pendingStopPrice` and/or `pendingTrailingDelta`, `pendingTimeInForce` | |
    /// | `pendingTrailingDelta` is provided | `pendingPrice` | |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-new-oto
    [[nodiscard]] common::RestApiResponse<MarginAccountNewOtoResponse>
    margin_account_new_oto(const MarginAccountNewOtoParams& params) const {
        return trade_api_.margin_account_new_oto(params);
    }
    /// Asynchronous `margin_account_new_oto()`.
    template <class CompletionToken>
    auto async_margin_account_new_oto(const MarginAccountNewOtoParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_margin_account_new_oto(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Margin Account New OTOCO (TRADE)
    ///
    /// POST /sapi/v1/margin/order/otoco.
    ///
    /// Post a new OTOCO order for margin account：
    ///
    /// - An OTOCO (One-Triggers-One-Cancels-the-Other) is an order list
    /// comprised of 3 orders.
    ///
    /// - The first order is called the **working order** and must be `LIMIT` or
    /// `LIMIT_MAKER`. Initially, only the working order goes on the order book.
    ///   - The behavior of the working order is the same as the OTO.
    /// - OTOCO has 2 pending orders (pending above and pending below), forming
    /// an OCO pair. The pending orders are only placed on the order book when
    /// the working order gets **fully filled**.
    ///   - The rules of the pending above and pending below follow the same rules as the Order List
    ///   OCO.
    /// - OTOCOs add **3 orders** against the unfilled order count,
    /// `EXCHANGE_MAX_NUM_ORDERS` filter, and `MAX_NUM_ORDERS` filter.
    ///
    /// Weight: 6(UID) or 1500(UID) when sideEffectType is MARGIN_BUY or AUTO_BORROW_REPAY
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - autoRepayAtCancel is suggested to set as “FALSE” to keep liability unrepaid under high
    /// frequent new order/cancel order execution
    /// - Depending on the `pendingAboveType`/`pendingBelowType` or `workingType`, some optional
    /// parameters will become mandatory: | Type                                 | Additional
    /// mandatory parameters                              | Additional information | |
    /// ------------------------------------ |
    /// ------------------------------------------------------------ | ---------------------- | |
    /// `workingType` = `LIMIT`              | `workingTimeInForce` |                        | |
    /// `pendingAboveType`= `LIMIT_MAKER`    | `pendingAbovePrice` |                        | |
    /// `pendingAboveType`= `STOP_LOSS`      | `pendingAboveStopPrice` and/or
    /// `pendingAboveTrailingDelta`   |                        | |
    /// `pendingAboveType`=`STOP_LOSS_LIMIT` | `pendingAbovePrice`, `pendingAboveStopPrice` and/or
    /// `pendingAboveTrailingDelta`, `pendingAboveTimeInForce` |                        | |
    /// `pendingBelowType`= `LIMIT_MAKER`    | `pendingBelowPrice` |                        | |
    /// `pendingBelowType`= `STOP_LOSS`      | `pendingBelowStopPrice` and/or
    /// `pendingBelowTrailingDelta`   |                        | |
    /// `pendingBelowType`=`STOP_LOSS_LIMIT` | `pendingBelowPrice`, `pendingBelowStopPrice` and/or
    /// `pendingBelowTrailingDelta`, `pendingBelowTimeInForce` |                        | |
    /// `pendingAboveTrailingDelta` is provided | `pendingAbovePrice` |                        | |
    /// `pendingBelowTrailingDelta` is provided | `pendingBelowPrice` |                        |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-new-otoco
    [[nodiscard]] common::RestApiResponse<MarginAccountNewOtocoResponse>
    margin_account_new_otoco(const MarginAccountNewOtocoParams& params) const {
        return trade_api_.margin_account_new_otoco(params);
    }
    /// Asynchronous `margin_account_new_otoco()`.
    template <class CompletionToken>
    auto async_margin_account_new_otoco(const MarginAccountNewOtocoParams& params,
                                        CompletionToken&& token) const {
        return trade_api_.async_margin_account_new_otoco(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Margin Manual Liquidation (TRADE)
    ///
    /// POST /sapi/v1/margin/manual-liquidation.
    ///
    /// Margin Manual Liquidation
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - This endpoint supports Cross Margin Classic Mode and Pro Mode.
    /// - Isolated Margin is only supported in restricted regions.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-manual-liquidation
    [[nodiscard]] common::RestApiResponse<MarginManualLiquidationResponse>
    margin_manual_liquidation(const MarginManualLiquidationParams& params) const {
        return trade_api_.margin_manual_liquidation(params);
    }
    /// Asynchronous `margin_manual_liquidation()`.
    template <class CompletionToken>
    auto async_margin_manual_liquidation(const MarginManualLiquidationParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_margin_manual_liquidation(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Query Current Margin Order Count Usage (TRADE)
    ///
    /// GET /sapi/v1/margin/rateLimit/order.
    ///
    /// Displays the user's current margin order count usage for all intervals.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-current-margin-order-count-usage
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryCurrentMarginOrderCountUsageResponseInner>>
    query_current_margin_order_count_usage(
        const QueryCurrentMarginOrderCountUsageParams& params = {}) const {
        return trade_api_.query_current_margin_order_count_usage(params);
    }
    /// Asynchronous `query_current_margin_order_count_usage()`.
    template <class CompletionToken>
    auto async_query_current_margin_order_count_usage(
        const QueryCurrentMarginOrderCountUsageParams& params, CompletionToken&& token) const {
        return trade_api_.async_query_current_margin_order_count_usage(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Liquidation Loan (USER_DATA)
    ///
    /// GET /sapi/v1/margin/liquidation-loan.
    ///
    /// Query the current user's cross-margin liquidation loan information, including the original
    /// loan amount, repaid amount, and remaining amount. When a cross-margin account is liquidated
    /// and the account equity turns negative (bankruptcy), the system generates a liquidation loan
    /// record representing the deficit. This represents the shortfall amount denominated in USDC.
    ///
    /// Weight(UID): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-liquidation-loan
    [[nodiscard]] common::RestApiResponse<QueryLiquidationLoanResponse>
    query_liquidation_loan(const QueryLiquidationLoanParams& params = {}) const {
        return trade_api_.query_liquidation_loan(params);
    }
    /// Asynchronous `query_liquidation_loan()`.
    template <class CompletionToken>
    auto async_query_liquidation_loan(const QueryLiquidationLoanParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_query_liquidation_loan(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Query Liquidation Loan Repay History (USER_DATA)
    ///
    /// GET /sapi/v1/margin/liquidation-loan/repay-history.
    ///
    /// Query the repayment history of cross-margin liquidation loans (deficit caused by bankruptcy
    /// during liquidation). Supports time-range filtering and pagination.
    ///
    /// Weight(UID): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The maximum query range is 90 days. If `startTime` is earlier than 90 days ago, it will be
    /// clamped to 90 days ago.
    /// - Only records with status `SUCCESS` or `PENDING` are returned. Failed repayment records are
    /// excluded.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-liquidation-loan-repay-history
    [[nodiscard]] common::RestApiResponse<QueryLiquidationLoanRepayHistoryResponse>
    query_liquidation_loan_repay_history(
        const QueryLiquidationLoanRepayHistoryParams& params = {}) const {
        return trade_api_.query_liquidation_loan_repay_history(params);
    }
    /// Asynchronous `query_liquidation_loan_repay_history()`.
    template <class CompletionToken>
    auto
    async_query_liquidation_loan_repay_history(const QueryLiquidationLoanRepayHistoryParams& params,
                                               CompletionToken&& token) const {
        return trade_api_.async_query_liquidation_loan_repay_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's all OCO (USER_DATA)
    ///
    /// GET /sapi/v1/margin/allOrderList.
    ///
    /// Retrieves all OCO for a specific margin account based on provided optional parameters
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-all-oco
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsAllOcoResponseInner>>
    query_margin_accounts_all_oco(const QueryMarginAccountsAllOcoParams& params = {}) const {
        return trade_api_.query_margin_accounts_all_oco(params);
    }
    /// Asynchronous `query_margin_accounts_all_oco()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_all_oco(const QueryMarginAccountsAllOcoParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_all_oco(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's All Orders (USER_DATA)
    ///
    /// GET /sapi/v1/margin/allOrders.
    ///
    /// Query Margin Account's All Orders
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If orderId is set, it will get orders >= that orderId. Otherwise the
    /// orders within 24 hours are returned.
    ///
    /// - For some historical orders cummulativeQuoteQty will be < 0, meaning
    /// the data is not available at this time.
    ///
    /// - Less than 24 hours between startTime and endTime.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-all-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsAllOrdersResponseInner>>
    query_margin_accounts_all_orders(const QueryMarginAccountsAllOrdersParams& params) const {
        return trade_api_.query_margin_accounts_all_orders(params);
    }
    /// Asynchronous `query_margin_accounts_all_orders()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_all_orders(const QueryMarginAccountsAllOrdersParams& params,
                                                CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_all_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Open OCO (USER_DATA)
    ///
    /// GET /sapi/v1/margin/openOrderList.
    ///
    /// Query Margin Account's Open OCO
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-open-oco
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsOpenOcoResponseInner>>
    query_margin_accounts_open_oco(const QueryMarginAccountsOpenOcoParams& params = {}) const {
        return trade_api_.query_margin_accounts_open_oco(params);
    }
    /// Asynchronous `query_margin_accounts_open_oco()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_open_oco(const QueryMarginAccountsOpenOcoParams& params,
                                              CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_open_oco(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Open OTO/OTOCO Order Lists (USER_DATA)
    ///
    /// GET /sapi/v1/margin/oto/openOrderList.
    ///
    /// Retrieves all open OTO / OTOCO order lists of the margin account.
    ///
    /// Notes:
    /// - The returned list contains order lists whose `listOrderStatus` is `EXECUTING`, i.e. at
    /// least one order of the list is still open (`NEW` / `PARTIALLY_FILLED`).
    /// - For OTO, the `orders` array contains 2 orders: the working order and the pending order.
    /// - For OTOCO, the `orders` array contains 3 orders: the working order and the two pending
    /// orders (pending above / pending below).
    ///
    /// Weight(UID): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-open-otootoco-order-lists
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryMarginAccountsOpenOtootocoOrderListsResponseInner>>
    query_margin_accounts_open_otootoco_order_lists(
        const QueryMarginAccountsOpenOtootocoOrderListsParams& params = {}) const {
        return trade_api_.query_margin_accounts_open_otootoco_order_lists(params);
    }
    /// Asynchronous `query_margin_accounts_open_otootoco_order_lists()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_open_otootoco_order_lists(
        const QueryMarginAccountsOpenOtootocoOrderListsParams& params,
        CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_open_otootoco_order_lists(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Trade List (USER_DATA)
    ///
    /// GET /sapi/v1/margin/myTrades.
    ///
    /// Query Margin Account's Trade List
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If fromId is set, it will get trades >= that fromId. Otherwise the
    /// trades within 24 hours are returned.
    ///
    /// - Less than 24 hours between startTime and endTime.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsTradeListResponseInner>>
    query_margin_accounts_trade_list(const QueryMarginAccountsTradeListParams& params) const {
        return trade_api_.query_margin_accounts_trade_list(params);
    }
    /// Asynchronous `query_margin_accounts_trade_list()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_trade_list(const QueryMarginAccountsTradeListParams& params,
                                                CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_trade_list(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Prevented Matches (USER_DATA)
    ///
    /// GET /sapi/v1/margin/myPreventedMatches.
    ///
    /// Displays the list of orders that were expired due to STP. (Self-Trade Prevention).
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Supported parameter combinations:
    ///
    /// - `symbol` + `preventedMatchId`
    ///
    /// - `symbol` + `orderId`
    ///
    /// - `symbol` + `orderId` + `fromPreventedMatchId`
    ///
    /// - If `orderId` is provided, all prevented matches for that order will be
    /// returned.
    ///
    /// - If `preventedMatchId` is provided, the specific prevented match will
    /// be returned.
    ///
    /// - A single request returns a maximum of 500 records. If there are more
    /// than 500 records, use `symbol` + `orderId` + `fromPreventedMatchId`
    /// combination for pagination.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-prevented-matches
    [[nodiscard]] common::RestApiResponse<std::vector<QueryPreventedMatchesResponseInner>>
    query_prevented_matches(const QueryPreventedMatchesParams& params) const {
        return trade_api_.query_prevented_matches(params);
    }
    /// Asynchronous `query_prevented_matches()`.
    template <class CompletionToken>
    auto async_query_prevented_matches(const QueryPreventedMatchesParams& params,
                                       CompletionToken&& token) const {
        return trade_api_.async_query_prevented_matches(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Query Special key List(Low Latency Trading) (TRADE)
    ///
    /// GET /sapi/v1/margin/api-key-list.
    ///
    /// This only applies to Special Key for Low Latency Trading.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-special-key-list
    [[nodiscard]] common::RestApiResponse<std::vector<QuerySpecialKeyListResponseInner>>
    query_special_key_list(const QuerySpecialKeyListParams& params = {}) const {
        return trade_api_.query_special_key_list(params);
    }
    /// Asynchronous `query_special_key_list()`.
    template <class CompletionToken>
    auto async_query_special_key_list(const QuerySpecialKeyListParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_query_special_key_list(params,
                                                       std::forward<CompletionToken>(token));
    }

    // TransferApi

    /// Get Cross Margin Transfer History (USER_DATA)
    ///
    /// GET /sapi/v1/margin/transfer.
    ///
    /// Get Cross Margin Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Response in descending order
    /// - The max interval between `startTime` and `endTime` is 30 days.
    /// - Returns data for last 7 days by default
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/transfer#get-cross-margin-transfer-history
    [[nodiscard]] common::RestApiResponse<GetCrossMarginTransferHistoryResponse>
    get_cross_margin_transfer_history(
        const GetCrossMarginTransferHistoryParams& params = {}) const {
        return transfer_api_.get_cross_margin_transfer_history(params);
    }
    /// Asynchronous `get_cross_margin_transfer_history()`.
    template <class CompletionToken>
    auto async_get_cross_margin_transfer_history(const GetCrossMarginTransferHistoryParams& params,
                                                 CompletionToken&& token) const {
        return transfer_api_.async_get_cross_margin_transfer_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Max Transfer-Out Amount (USER_DATA)
    ///
    /// GET /sapi/v1/margin/maxTransferable.
    ///
    /// Query Max Transfer-Out Amount
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If isolatedSymbol is not sent, crossed margin data will be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/transfer#query-max-transfer-out-amount
    [[nodiscard]] common::RestApiResponse<QueryMaxTransferOutAmountResponse>
    query_max_transfer_out_amount(const QueryMaxTransferOutAmountParams& params) const {
        return transfer_api_.query_max_transfer_out_amount(params);
    }
    /// Asynchronous `query_max_transfer_out_amount()`.
    template <class CompletionToken>
    auto async_query_max_transfer_out_amount(const QueryMaxTransferOutAmountParams& params,
                                             CompletionToken&& token) const {
        return transfer_api_.async_query_max_transfer_out_amount(
            params, std::forward<CompletionToken>(token));
    }

    // UserDataStreamApi

    /// Close User Data Stream (USER_STREAM)
    ///
    /// DELETE /sapi/v1/margin/listen-key.
    ///
    /// Close out a user data stream.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#close-user-data-stream
    [[nodiscard]] common::RestApiResponse<boost::json::value> close_user_data_stream() const {
        return user_data_stream_api_.close_user_data_stream();
    }
    /// Asynchronous `close_user_data_stream()`.
    template <class CompletionToken>
    auto async_close_user_data_stream(CompletionToken&& token) const {
        return user_data_stream_api_.async_close_user_data_stream(
            std::forward<CompletionToken>(token));
    }

    /// Keepalive User Data Stream (USER_STREAM)
    ///
    /// PUT /sapi/v1/margin/listen-key.
    ///
    /// Keepalive a user data stream to prevent a time out.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#keepalive-user-data-stream
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params) const {
        return user_data_stream_api_.keepalive_user_data_stream(params);
    }
    /// Asynchronous `keepalive_user_data_stream()`.
    template <class CompletionToken>
    auto async_keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params,
                                          CompletionToken&& token) const {
        return user_data_stream_api_.async_keepalive_user_data_stream(
            params, std::forward<CompletionToken>(token));
    }

    /// Start User Data Stream (USER_STREAM)
    ///
    /// POST /sapi/v1/margin/listen-key.
    ///
    /// Start a new user data stream.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#start-user-data-stream
    [[nodiscard]] common::RestApiResponse<StartUserDataStreamResponse>
    start_user_data_stream() const {
        return user_data_stream_api_.start_user_data_stream();
    }
    /// Asynchronous `start_user_data_stream()`.
    template <class CompletionToken>
    auto async_start_user_data_stream(CompletionToken&& token) const {
        return user_data_stream_api_.async_start_user_data_stream(
            std::forward<CompletionToken>(token));
    }

    /// Close User Data Stream V2 (USER_STREAM)
    ///
    /// DELETE /sapi/v2/margin/listen-key.
    ///
    /// Close out a user data stream.
    ///
    /// **Note:** After this request, you will receive another WebSocket message:
    ///
    /// ```json
    /// {
    ///   "e": "eventStreamTerminated",
    ///   "E": 1793646860552
    /// }
    /// ```
    ///
    /// - `e` (string): event type. Example: `eventStreamTerminated`
    /// - `E` (integer): current timestamp. Example: `1793646860552`
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#close-user-data-stream-v2
    [[nodiscard]] common::RestApiResponse<boost::json::value> close_user_data_stream_v2() const {
        return user_data_stream_api_.close_user_data_stream_v2();
    }
    /// Asynchronous `close_user_data_stream_v2()`.
    template <class CompletionToken>
    auto async_close_user_data_stream_v2(CompletionToken&& token) const {
        return user_data_stream_api_.async_close_user_data_stream_v2(
            std::forward<CompletionToken>(token));
    }

    /// Keepalive User Data Stream V2 (USER_STREAM)
    ///
    /// PUT /sapi/v2/margin/listen-key.
    ///
    /// Keep alive a user data stream to prevent a timeout. Each successful request extends the
    /// listen key validity for 1 hour.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#keepalive-user-data-stream-v2
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    keepalive_user_data_stream_v2(const KeepaliveUserDataStreamV2Params& params) const {
        return user_data_stream_api_.keepalive_user_data_stream_v2(params);
    }
    /// Asynchronous `keepalive_user_data_stream_v2()`.
    template <class CompletionToken>
    auto async_keepalive_user_data_stream_v2(const KeepaliveUserDataStreamV2Params& params,
                                             CompletionToken&& token) const {
        return user_data_stream_api_.async_keepalive_user_data_stream_v2(
            params, std::forward<CompletionToken>(token));
    }

    /// Start User Data Stream V2 (USER_STREAM)
    ///
    /// POST /sapi/v2/margin/listen-key.
    ///
    /// Start a new user data stream.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#start-user-data-stream-v2
    [[nodiscard]] common::RestApiResponse<StartUserDataStreamV2Response>
    start_user_data_stream_v2() const {
        return user_data_stream_api_.start_user_data_stream_v2();
    }
    /// Asynchronous `start_user_data_stream_v2()`.
    template <class CompletionToken>
    auto async_start_user_data_stream_v2(CompletionToken&& token) const {
        return user_data_stream_api_.async_start_user_data_stream_v2(
            std::forward<CompletionToken>(token));
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
    BorrowRepayApi borrow_repay_api_;
    MarketDataApi market_data_api_;
    TradeApi trade_api_;
    TransferApi transfer_api_;
    UserDataStreamApi user_data_stream_api_;
};

} // namespace binance::margin_trading::rest_api
