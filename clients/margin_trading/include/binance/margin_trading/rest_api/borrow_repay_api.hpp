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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/get_future_hourly_interest_rate_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/get_interest_history_response.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_borrow_repay_response.hpp>
#include <binance/margin_trading/rest_api/models/query_borrow_repay_records_in_margin_account_response.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_interest_rate_history_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_max_borrow_response.hpp>

namespace binance::margin_trading::rest_api {

enum class GetFutureHourlyInterestRateIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(GetFutureHourlyInterestRateIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT GetFutureHourlyInterestRateIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<GetFutureHourlyInterestRateIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              GetFutureHourlyInterestRateIsIsolatedEnum value);

enum class MarginAccountBorrowRepayIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountBorrowRepayIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountBorrowRepayIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountBorrowRepayIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountBorrowRepayIsIsolatedEnum value);

enum class MarginAccountBorrowRepayTypeEnum {
    Borrow,
    Repay,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountBorrowRepayTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountBorrowRepayTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountBorrowRepayTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountBorrowRepayTypeEnum value);

enum class QueryBorrowRepayRecordsInMarginAccountTypeEnum {
    Borrow,
    Repay,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryBorrowRepayRecordsInMarginAccountTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryBorrowRepayRecordsInMarginAccountTypeEnum
tag_invoke(boost::json::value_to_tag<QueryBorrowRepayRecordsInMarginAccountTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryBorrowRepayRecordsInMarginAccountTypeEnum value);

struct GetFutureHourlyInterestRateParams {
    common::Required<std::string> assets;
    common::Required<GetFutureHourlyInterestRateIsIsolatedEnum> is_isolated;
};

struct GetInterestHistoryParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::string> isolated_symbol = std::nullopt;
    /// Only supports querying data from the past 90 days.
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountBorrowRepayParams {
    common::Required<std::string> asset;
    /// `TRUE` for Isolated Margin, `FALSE` for Cross Margin
    common::Required<MarginAccountBorrowRepayIsIsolatedEnum> is_isolated;
    common::Required<std::string> amount;
    common::Required<MarginAccountBorrowRepayTypeEnum> type;
    /// Only for Isolated margin
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryBorrowRepayRecordsInMarginAccountParams {
    common::Required<QueryBorrowRepayRecordsInMarginAccountTypeEnum> type;
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::string> isolated_symbol = std::nullopt;
    std::optional<std::int64_t> tx_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginInterestRateHistoryParams {
    common::Required<std::string> asset;
    std::optional<std::int64_t> vip_level = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMaxBorrowParams {
    common::Required<std::string> asset;
    std::optional<std::string> isolated_symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_MARGIN_TRADING_EXPORT BorrowRepayApi {
public:
    explicit BorrowRepayApi(std::shared_ptr<common::RestClient> client);

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
    get_future_hourly_interest_rate(const GetFutureHourlyInterestRateParams& params) const;

    /// Asynchronous `get_future_hourly_interest_rate()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetFutureHourlyInterestRateResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_future_hourly_interest_rate(const GetFutureHourlyInterestRateParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<GetFutureHourlyInterestRateResponseInner>>(
            client_, get_future_hourly_interest_rate_request(params),
            std::forward<CompletionToken>(token));
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
    get_interest_history(const GetInterestHistoryParams& params = {}) const;

    /// Asynchronous `get_interest_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetInterestHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_interest_history(const GetInterestHistoryParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<GetInterestHistoryResponse>(
            client_, get_interest_history_request(params), std::forward<CompletionToken>(token));
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
    margin_account_borrow_repay(const MarginAccountBorrowRepayParams& params) const;

    /// Asynchronous `margin_account_borrow_repay()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountBorrowRepayResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_borrow_repay(const MarginAccountBorrowRepayParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<MarginAccountBorrowRepayResponse>(
            client_, margin_account_borrow_repay_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryBorrowRepayRecordsInMarginAccountParams& params) const;

    /// Asynchronous `query_borrow_repay_records_in_margin_account()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryBorrowRepayRecordsInMarginAccountResponse>)`.
    template <class CompletionToken>
    auto async_query_borrow_repay_records_in_margin_account(
        const QueryBorrowRepayRecordsInMarginAccountParams& params, CompletionToken&& token) const {
        return common::async_send<QueryBorrowRepayRecordsInMarginAccountResponse>(
            client_, query_borrow_repay_records_in_margin_account_request(params),
            std::forward<CompletionToken>(token));
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
    query_margin_interest_rate_history(const QueryMarginInterestRateHistoryParams& params) const;

    /// Asynchronous `query_margin_interest_rate_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryMarginInterestRateHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_query_margin_interest_rate_history(const QueryMarginInterestRateHistoryParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<QueryMarginInterestRateHistoryResponseInner>>(
            client_, query_margin_interest_rate_history_request(params),
            std::forward<CompletionToken>(token));
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
    query_max_borrow(const QueryMaxBorrowParams& params) const;

    /// Asynchronous `query_max_borrow()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMaxBorrowResponse>)`.
    template <class CompletionToken>
    auto async_query_max_borrow(const QueryMaxBorrowParams& params, CompletionToken&& token) const {
        return common::async_send<QueryMaxBorrowResponse>(client_, query_max_borrow_request(params),
                                                          std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_future_hourly_interest_rate_request(const GetFutureHourlyInterestRateParams& params) const;
    [[nodiscard]] common::RestRequest
    get_interest_history_request(const GetInterestHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_borrow_repay_request(const MarginAccountBorrowRepayParams& params) const;
    [[nodiscard]] common::RestRequest query_borrow_repay_records_in_margin_account_request(
        const QueryBorrowRepayRecordsInMarginAccountParams& params) const;
    [[nodiscard]] common::RestRequest query_margin_interest_rate_history_request(
        const QueryMarginInterestRateHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_max_borrow_request(const QueryMaxBorrowParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::margin_trading::rest_api
