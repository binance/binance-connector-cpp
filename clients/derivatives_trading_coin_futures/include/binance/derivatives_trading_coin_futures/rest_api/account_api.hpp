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
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/account_information_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/futures_account_balance_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_current_position_mode_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_download_id_for_futures_order_history_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_download_id_for_futures_trade_history_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_download_id_for_futures_transaction_history_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_futures_order_history_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_futures_trade_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_futures_transaction_history_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_income_history_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/notional_bracket_for_pair_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/notional_bracket_for_symbol_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/user_commission_rate_response.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

enum class GetIncomeHistoryIncomeTypeEnum {
    Transfer,
    WelcomeBonus,
    FundingFee,
    RealizedPnl,
    Commission,
    InsuranceClear,
    DeliveredSettelment,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(GetIncomeHistoryIncomeTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT GetIncomeHistoryIncomeTypeEnum
tag_invoke(boost::json::value_to_tag<GetIncomeHistoryIncomeTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           GetIncomeHistoryIncomeTypeEnum value);

struct AccountInformationParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FuturesAccountBalanceParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCurrentPositionModeParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForFuturesOrderHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForFuturesTradeHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForFuturesTransactionHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFuturesOrderHistoryDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFuturesTradeDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFuturesTransactionHistoryDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetIncomeHistoryParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
    /// Income type.
    std::optional<GetIncomeHistoryIncomeTypeEnum> income_type = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NotionalBracketForPairParams {
    std::optional<std::string> pair = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NotionalBracketForSymbolParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UserCommissionRateParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::RestClient> client);

    /// Account Information (USER_DATA)
    ///
    /// GET /dapi/v1/account.
    ///
    /// Get current account information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - for One-way Mode user, the "positions" will only show the "BOTH" positions
    /// - for Hedge Mode user, the "positions" will show "BOTH", "LONG", and "SHORT" positions.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#account-information
    [[nodiscard]] common::RestApiResponse<AccountInformationResponse>
    account_information(const AccountInformationParams& params = {}) const;

    /// Asynchronous `account_information()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountInformationResponse>)`.
    template <class CompletionToken>
    auto async_account_information(const AccountInformationParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<AccountInformationResponse>(
            client_, account_information_request(params), std::forward<CompletionToken>(token));
    }

    /// Futures Account Balance (USER_DATA)
    ///
    /// GET /dapi/v1/balance.
    ///
    /// Check futures account balance
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#futures-account-balance
    [[nodiscard]] common::RestApiResponse<std::vector<FuturesAccountBalanceResponseInner>>
    futures_account_balance(const FuturesAccountBalanceParams& params = {}) const;

    /// Asynchronous `futures_account_balance()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<FuturesAccountBalanceResponseInner>>)`.
    template <class CompletionToken>
    auto async_futures_account_balance(const FuturesAccountBalanceParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<FuturesAccountBalanceResponseInner>>(
            client_, futures_account_balance_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Current Position Mode (USER_DATA)
    ///
    /// GET /dapi/v1/positionSide/dual.
    ///
    /// Get user's position mode (Hedge Mode or One-way Mode ) on ***EVERY symbol***
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#get-current-position-mode
    [[nodiscard]] common::RestApiResponse<GetCurrentPositionModeResponse>
    get_current_position_mode(const GetCurrentPositionModeParams& params = {}) const;

    /// Asynchronous `get_current_position_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCurrentPositionModeResponse>)`.
    template <class CompletionToken>
    auto async_get_current_position_mode(const GetCurrentPositionModeParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetCurrentPositionModeResponse>(
            client_, get_current_position_mode_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For Futures Order History (USER_DATA)
    ///
    /// GET /dapi/v1/order/asyn.
    ///
    /// Get Download Id For Futures Order History
    ///
    /// Weight(IP): 1000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 8 times per month, shared by front end download page and rest api
    /// - This endpoint uses the IP rate limit bucket and costs 1000 weight per call. The maximum is
    /// 2 calls per minute; the 3rd call within the same minute will trigger a ban.
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#get-download-id-for-futures-order-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForFuturesOrderHistoryResponse>
    get_download_id_for_futures_order_history(
        const GetDownloadIdForFuturesOrderHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_futures_order_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForFuturesOrderHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_futures_order_history(
        const GetDownloadIdForFuturesOrderHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForFuturesOrderHistoryResponse>(
            client_, get_download_id_for_futures_order_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For Futures Trade History (USER_DATA)
    ///
    /// GET /dapi/v1/trade/asyn.
    ///
    /// Get download id for futures trade history
    ///
    /// Weight(IP): 1000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 8 times per month, shared by front end download page and rest api
    /// - This endpoint uses the IP rate limit bucket and costs 1000 weight per call. The maximum is
    /// 2 calls per minute; the 3rd call within the same minute will trigger a ban.
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#get-download-id-for-futures-trade-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForFuturesTradeHistoryResponse>
    get_download_id_for_futures_trade_history(
        const GetDownloadIdForFuturesTradeHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_futures_trade_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForFuturesTradeHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_futures_trade_history(
        const GetDownloadIdForFuturesTradeHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForFuturesTradeHistoryResponse>(
            client_, get_download_id_for_futures_trade_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For Futures Transaction History (USER_DATA)
    ///
    /// GET /dapi/v1/income/asyn.
    ///
    /// Get download id for futures transaction history
    ///
    /// Weight(IP): 1000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The request limit is 100 times per month, shared across the front end download page and
    /// rest api, as well as between USDⓈ-M and COIN-M contracts.
    /// - This endpoint uses the IP rate limit bucket and costs 1000 weight per call. The maximum is
    /// 2 calls per minute; the 3rd call within the same minute will trigger a ban.
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#get-download-id-for-futures-transaction-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForFuturesTransactionHistoryResponse>
    get_download_id_for_futures_transaction_history(
        const GetDownloadIdForFuturesTransactionHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_futures_transaction_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForFuturesTransactionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_futures_transaction_history(
        const GetDownloadIdForFuturesTransactionHistoryParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForFuturesTransactionHistoryResponse>(
            client_, get_download_id_for_futures_transaction_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Futures Order History Download Link by Id (USER_DATA)
    ///
    /// GET /dapi/v1/order/asyn/id.
    ///
    /// Get futures order history download link by Id
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#get-futures-order-history-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetFuturesOrderHistoryDownloadLinkByIdResponse>
    get_futures_order_history_download_link_by_id(
        const GetFuturesOrderHistoryDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_futures_order_history_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFuturesOrderHistoryDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_futures_order_history_download_link_by_id(
        const GetFuturesOrderHistoryDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return common::async_send<GetFuturesOrderHistoryDownloadLinkByIdResponse>(
            client_, get_futures_order_history_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Futures Trade Download Link by Id (USER_DATA)
    ///
    /// GET /dapi/v1/trade/asyn/id.
    ///
    /// Get futures trade download link by Id
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#get-futures-trade-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetFuturesTradeDownloadLinkByIdResponse>
    get_futures_trade_download_link_by_id(
        const GetFuturesTradeDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_futures_trade_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFuturesTradeDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto
    async_get_futures_trade_download_link_by_id(const GetFuturesTradeDownloadLinkByIdParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<GetFuturesTradeDownloadLinkByIdResponse>(
            client_, get_futures_trade_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Futures Transaction History Download Link by Id (USER_DATA)
    ///
    /// GET /dapi/v1/income/asyn/id.
    ///
    /// Get futures transaction history download link by Id
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#get-futures-transaction-history-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetFuturesTransactionHistoryDownloadLinkByIdResponse>
    get_futures_transaction_history_download_link_by_id(
        const GetFuturesTransactionHistoryDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_futures_transaction_history_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFuturesTransactionHistoryDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_futures_transaction_history_download_link_by_id(
        const GetFuturesTransactionHistoryDownloadLinkByIdParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetFuturesTransactionHistoryDownloadLinkByIdResponse>(
            client_, get_futures_transaction_history_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Income History (USER_DATA)
    ///
    /// GET /dapi/v1/income.
    ///
    /// Get income history
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `incomeType ` is not sent, all kinds of flow will be returned
    /// - "trandId" is unique in the same "incomeType" for a user
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#get-income-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetIncomeHistoryResponseInner>>
    get_income_history(const GetIncomeHistoryParams& params = {}) const;

    /// Asynchronous `get_income_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetIncomeHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_income_history(const GetIncomeHistoryParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<GetIncomeHistoryResponseInner>>(
            client_, get_income_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Notional Bracket for Pair (USER_DATA)
    ///
    /// GET /dapi/v1/leverageBracket.
    ///
    /// **Not recommended to continue using this v1 endpoint**
    ///
    /// Get the pair's default notional bracket list, may return ambiguous
    /// values when there have been multiple different `symbol` brackets under
    /// the `pair`, suggest using the following `GET /dapi/v2/leverageBracket`
    /// query instead to get the specific `symbol` notional bracket list.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#notional-bracket-for-pair
    [[nodiscard]] common::RestApiResponse<std::vector<NotionalBracketForPairResponseInner>>
    notional_bracket_for_pair(const NotionalBracketForPairParams& params = {}) const;

    /// Asynchronous `notional_bracket_for_pair()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<NotionalBracketForPairResponseInner>>)`.
    template <class CompletionToken>
    auto async_notional_bracket_for_pair(const NotionalBracketForPairParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<std::vector<NotionalBracketForPairResponseInner>>(
            client_, notional_bracket_for_pair_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Notional Bracket for Symbol (USER_DATA)
    ///
    /// GET /dapi/v2/leverageBracket.
    ///
    /// Get the symbol's notional bracket list.
    ///
    /// Weight: 1 (after CM migration: 1 with `symbol` / 2 without `symbol`)
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#notional-bracket-for-symbol
    [[nodiscard]] common::RestApiResponse<std::vector<NotionalBracketForSymbolResponseInner>>
    notional_bracket_for_symbol(const NotionalBracketForSymbolParams& params = {}) const;

    /// Asynchronous `notional_bracket_for_symbol()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<NotionalBracketForSymbolResponseInner>>)`.
    template <class CompletionToken>
    auto async_notional_bracket_for_symbol(const NotionalBracketForSymbolParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<std::vector<NotionalBracketForSymbolResponseInner>>(
            client_, notional_bracket_for_symbol_request(params),
            std::forward<CompletionToken>(token));
    }

    /// User Commission Rate (USER_DATA)
    ///
    /// GET /dapi/v1/commissionRate.
    ///
    /// Query user commission rate
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/account#user-commission-rate
    [[nodiscard]] common::RestApiResponse<UserCommissionRateResponse>
    user_commission_rate(const UserCommissionRateParams& params) const;

    /// Asynchronous `user_commission_rate()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<UserCommissionRateResponse>)`.
    template <class CompletionToken>
    auto async_user_commission_rate(const UserCommissionRateParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<UserCommissionRateResponse>(
            client_, user_commission_rate_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    account_information_request(const AccountInformationParams& params) const;
    [[nodiscard]] common::RestRequest
    futures_account_balance_request(const FuturesAccountBalanceParams& params) const;
    [[nodiscard]] common::RestRequest
    get_current_position_mode_request(const GetCurrentPositionModeParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_futures_order_history_request(
        const GetDownloadIdForFuturesOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_futures_trade_history_request(
        const GetDownloadIdForFuturesTradeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_futures_transaction_history_request(
        const GetDownloadIdForFuturesTransactionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_futures_order_history_download_link_by_id_request(
        const GetFuturesOrderHistoryDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest get_futures_trade_download_link_by_id_request(
        const GetFuturesTradeDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest get_futures_transaction_history_download_link_by_id_request(
        const GetFuturesTransactionHistoryDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest
    get_income_history_request(const GetIncomeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    notional_bracket_for_pair_request(const NotionalBracketForPairParams& params) const;
    [[nodiscard]] common::RestRequest
    notional_bracket_for_symbol_request(const NotionalBracketForSymbolParams& params) const;
    [[nodiscard]] common::RestRequest
    user_commission_rate_request(const UserCommissionRateParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_coin_futures::rest_api
