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
#include <binance/margin_trading/rest_api/models/adjust_cross_margin_max_leverage_response.hpp>
#include <binance/margin_trading/rest_api/models/disable_isolated_margin_account_response.hpp>
#include <binance/margin_trading/rest_api/models/enable_isolated_margin_account_response.hpp>
#include <binance/margin_trading/rest_api/models/get_bnb_burn_status_response.hpp>
#include <binance/margin_trading/rest_api/models/get_summary_of_margin_account_response.hpp>
#include <binance/margin_trading/rest_api/models/query_cross_isolated_margin_capital_flow_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_cross_margin_account_details_response.hpp>
#include <binance/margin_trading/rest_api/models/query_cross_margin_fee_data_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_enabled_isolated_margin_account_limit_response.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_account_info_response.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_fee_data_response_inner.hpp>

namespace binance::margin_trading::rest_api {

enum class QueryCrossIsolatedMarginCapitalFlowTypeEnum {
    Transfer,
    Borrow,
    Repay,
    BuyIncome,
    BuyExpense,
    SellIncome,
    SellExpense,
    TradingCommission,
    BuyLiquidation,
    SellLiquidation,
    RepayLiquidation,
    OtherLiquidation,
    LiquidationFee,
    SmallBalanceConvert,
    CommissionReturn,
    SmallConvert,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryCrossIsolatedMarginCapitalFlowTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryCrossIsolatedMarginCapitalFlowTypeEnum
tag_invoke(boost::json::value_to_tag<QueryCrossIsolatedMarginCapitalFlowTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryCrossIsolatedMarginCapitalFlowTypeEnum value);

struct AdjustCrossMarginMaxLeverageParams {
    /// Can only adjust 3 , 5 or 10，Example: maxLeverage = 5 or 3 for Cross Margin Classic;
    /// maxLeverage=10 for Cross Margin Pro 10x leverage or 20x if compliance allows.
    common::Required<std::int64_t> max_leverage;
};

struct DisableIsolatedMarginAccountParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct EnableIsolatedMarginAccountParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryIsolatedMarginAccountInfoParams {
    std::optional<std::string> symbols = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBnbBurnStatusParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSummaryOfMarginAccountParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCrossIsolatedMarginCapitalFlowParams {
    std::optional<std::string> asset = std::nullopt;
    /// Mandatory for Isolated data
    std::optional<std::string> symbol = std::nullopt;
    std::optional<QueryCrossIsolatedMarginCapitalFlowTypeEnum> type = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> from_id = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCrossMarginAccountDetailsParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCrossMarginFeeDataParams {
    /// User's current specific margin data will be returned if vipLevel is omitted
    std::optional<std::int64_t> vip_level = std::nullopt;
    std::optional<std::string> coin = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryEnabledIsolatedMarginAccountLimitParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryIsolatedMarginFeeDataParams {
    std::optional<std::int64_t> vip_level = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_MARGIN_TRADING_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::RestClient> client);

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
    adjust_cross_margin_max_leverage(const AdjustCrossMarginMaxLeverageParams& params) const;

    /// Asynchronous `adjust_cross_margin_max_leverage()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AdjustCrossMarginMaxLeverageResponse>)`.
    template <class CompletionToken>
    auto async_adjust_cross_margin_max_leverage(const AdjustCrossMarginMaxLeverageParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<AdjustCrossMarginMaxLeverageResponse>(
            client_, adjust_cross_margin_max_leverage_request(params),
            std::forward<CompletionToken>(token));
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
    disable_isolated_margin_account(const DisableIsolatedMarginAccountParams& params) const;

    /// Asynchronous `disable_isolated_margin_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DisableIsolatedMarginAccountResponse>)`.
    template <class CompletionToken>
    auto async_disable_isolated_margin_account(const DisableIsolatedMarginAccountParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<DisableIsolatedMarginAccountResponse>(
            client_, disable_isolated_margin_account_request(params),
            std::forward<CompletionToken>(token));
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
    enable_isolated_margin_account(const EnableIsolatedMarginAccountParams& params) const;

    /// Asynchronous `enable_isolated_margin_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<EnableIsolatedMarginAccountResponse>)`.
    template <class CompletionToken>
    auto async_enable_isolated_margin_account(const EnableIsolatedMarginAccountParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<EnableIsolatedMarginAccountResponse>(
            client_, enable_isolated_margin_account_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryIsolatedMarginAccountInfoParams& params = {}) const;

    /// Asynchronous `query_isolated_margin_account_info()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryIsolatedMarginAccountInfoResponse>)`.
    template <class CompletionToken>
    auto
    async_query_isolated_margin_account_info(const QueryIsolatedMarginAccountInfoParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<QueryIsolatedMarginAccountInfoResponse>(
            client_, query_isolated_margin_account_info_request(params),
            std::forward<CompletionToken>(token));
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
    get_bnb_burn_status(const GetBnbBurnStatusParams& params = {}) const;

    /// Asynchronous `get_bnb_burn_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBnbBurnStatusResponse>)`.
    template <class CompletionToken>
    auto async_get_bnb_burn_status(const GetBnbBurnStatusParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<GetBnbBurnStatusResponse>(
            client_, get_bnb_burn_status_request(params), std::forward<CompletionToken>(token));
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
    get_summary_of_margin_account(const GetSummaryOfMarginAccountParams& params = {}) const;

    /// Asynchronous `get_summary_of_margin_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetSummaryOfMarginAccountResponse>)`.
    template <class CompletionToken>
    auto async_get_summary_of_margin_account(const GetSummaryOfMarginAccountParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetSummaryOfMarginAccountResponse>(
            client_, get_summary_of_margin_account_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryCrossIsolatedMarginCapitalFlowParams& params = {}) const;

    /// Asynchronous `query_cross_isolated_margin_capital_flow()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryCrossIsolatedMarginCapitalFlowResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_cross_isolated_margin_capital_flow(
        const QueryCrossIsolatedMarginCapitalFlowParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<QueryCrossIsolatedMarginCapitalFlowResponseInner>>(
            client_, query_cross_isolated_margin_capital_flow_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryCrossMarginAccountDetailsParams& params = {}) const;

    /// Asynchronous `query_cross_margin_account_details()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryCrossMarginAccountDetailsResponse>)`.
    template <class CompletionToken>
    auto
    async_query_cross_margin_account_details(const QueryCrossMarginAccountDetailsParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<QueryCrossMarginAccountDetailsResponse>(
            client_, query_cross_margin_account_details_request(params),
            std::forward<CompletionToken>(token));
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
    query_cross_margin_fee_data(const QueryCrossMarginFeeDataParams& params = {}) const;

    /// Asynchronous `query_cross_margin_fee_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryCrossMarginFeeDataResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_cross_margin_fee_data(const QueryCrossMarginFeeDataParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<std::vector<QueryCrossMarginFeeDataResponseInner>>(
            client_, query_cross_margin_fee_data_request(params),
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
        const QueryEnabledIsolatedMarginAccountLimitParams& params = {}) const;

    /// Asynchronous `query_enabled_isolated_margin_account_limit()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryEnabledIsolatedMarginAccountLimitResponse>)`.
    template <class CompletionToken>
    auto async_query_enabled_isolated_margin_account_limit(
        const QueryEnabledIsolatedMarginAccountLimitParams& params, CompletionToken&& token) const {
        return common::async_send<QueryEnabledIsolatedMarginAccountLimitResponse>(
            client_, query_enabled_isolated_margin_account_limit_request(params),
            std::forward<CompletionToken>(token));
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
    query_isolated_margin_fee_data(const QueryIsolatedMarginFeeDataParams& params = {}) const;

    /// Asynchronous `query_isolated_margin_fee_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryIsolatedMarginFeeDataResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_isolated_margin_fee_data(const QueryIsolatedMarginFeeDataParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<std::vector<QueryIsolatedMarginFeeDataResponseInner>>(
            client_, query_isolated_margin_fee_data_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest adjust_cross_margin_max_leverage_request(
        const AdjustCrossMarginMaxLeverageParams& params) const;
    [[nodiscard]] common::RestRequest
    disable_isolated_margin_account_request(const DisableIsolatedMarginAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    enable_isolated_margin_account_request(const EnableIsolatedMarginAccountParams& params) const;
    [[nodiscard]] common::RestRequest query_isolated_margin_account_info_request(
        const QueryIsolatedMarginAccountInfoParams& params) const;
    [[nodiscard]] common::RestRequest
    get_bnb_burn_status_request(const GetBnbBurnStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    get_summary_of_margin_account_request(const GetSummaryOfMarginAccountParams& params) const;
    [[nodiscard]] common::RestRequest query_cross_isolated_margin_capital_flow_request(
        const QueryCrossIsolatedMarginCapitalFlowParams& params) const;
    [[nodiscard]] common::RestRequest query_cross_margin_account_details_request(
        const QueryCrossMarginAccountDetailsParams& params) const;
    [[nodiscard]] common::RestRequest
    query_cross_margin_fee_data_request(const QueryCrossMarginFeeDataParams& params) const;
    [[nodiscard]] common::RestRequest query_enabled_isolated_margin_account_limit_request(
        const QueryEnabledIsolatedMarginAccountLimitParams& params) const;
    [[nodiscard]] common::RestRequest
    query_isolated_margin_fee_data_request(const QueryIsolatedMarginFeeDataParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::margin_trading::rest_api
