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
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/account_api.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/market_data_api.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/trade_api.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/user_data_streams_api.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

/// DerivativesTradingCoinFutures REST API client. Cheap to copy: copies share one
/// `common::RestClient` (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Derivatives Trading Coin Futures REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);
    /// A client for the testnet.
    [[nodiscard]] static RestApi testnet(common::RestApiConfig config);
    /// A client for the demo environment.
    [[nodiscard]] static RestApi demo(common::RestApiConfig config);

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
    account_information(const AccountInformationParams& params = {}) const {
        return account_api_.account_information(params);
    }
    /// Asynchronous `account_information()`.
    template <class CompletionToken>
    auto async_account_information(const AccountInformationParams& params,
                                   CompletionToken&& token) const {
        return account_api_.async_account_information(params, std::forward<CompletionToken>(token));
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
    futures_account_balance(const FuturesAccountBalanceParams& params = {}) const {
        return account_api_.futures_account_balance(params);
    }
    /// Asynchronous `futures_account_balance()`.
    template <class CompletionToken>
    auto async_futures_account_balance(const FuturesAccountBalanceParams& params,
                                       CompletionToken&& token) const {
        return account_api_.async_futures_account_balance(params,
                                                          std::forward<CompletionToken>(token));
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
    get_current_position_mode(const GetCurrentPositionModeParams& params = {}) const {
        return account_api_.get_current_position_mode(params);
    }
    /// Asynchronous `get_current_position_mode()`.
    template <class CompletionToken>
    auto async_get_current_position_mode(const GetCurrentPositionModeParams& params,
                                         CompletionToken&& token) const {
        return account_api_.async_get_current_position_mode(params,
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
        const GetDownloadIdForFuturesOrderHistoryParams& params) const {
        return account_api_.get_download_id_for_futures_order_history(params);
    }
    /// Asynchronous `get_download_id_for_futures_order_history()`.
    template <class CompletionToken>
    auto async_get_download_id_for_futures_order_history(
        const GetDownloadIdForFuturesOrderHistoryParams& params, CompletionToken&& token) const {
        return account_api_.async_get_download_id_for_futures_order_history(
            params, std::forward<CompletionToken>(token));
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
        const GetDownloadIdForFuturesTradeHistoryParams& params) const {
        return account_api_.get_download_id_for_futures_trade_history(params);
    }
    /// Asynchronous `get_download_id_for_futures_trade_history()`.
    template <class CompletionToken>
    auto async_get_download_id_for_futures_trade_history(
        const GetDownloadIdForFuturesTradeHistoryParams& params, CompletionToken&& token) const {
        return account_api_.async_get_download_id_for_futures_trade_history(
            params, std::forward<CompletionToken>(token));
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
        const GetDownloadIdForFuturesTransactionHistoryParams& params) const {
        return account_api_.get_download_id_for_futures_transaction_history(params);
    }
    /// Asynchronous `get_download_id_for_futures_transaction_history()`.
    template <class CompletionToken>
    auto async_get_download_id_for_futures_transaction_history(
        const GetDownloadIdForFuturesTransactionHistoryParams& params,
        CompletionToken&& token) const {
        return account_api_.async_get_download_id_for_futures_transaction_history(
            params, std::forward<CompletionToken>(token));
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
        const GetFuturesOrderHistoryDownloadLinkByIdParams& params) const {
        return account_api_.get_futures_order_history_download_link_by_id(params);
    }
    /// Asynchronous `get_futures_order_history_download_link_by_id()`.
    template <class CompletionToken>
    auto async_get_futures_order_history_download_link_by_id(
        const GetFuturesOrderHistoryDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return account_api_.async_get_futures_order_history_download_link_by_id(
            params, std::forward<CompletionToken>(token));
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
        const GetFuturesTradeDownloadLinkByIdParams& params) const {
        return account_api_.get_futures_trade_download_link_by_id(params);
    }
    /// Asynchronous `get_futures_trade_download_link_by_id()`.
    template <class CompletionToken>
    auto
    async_get_futures_trade_download_link_by_id(const GetFuturesTradeDownloadLinkByIdParams& params,
                                                CompletionToken&& token) const {
        return account_api_.async_get_futures_trade_download_link_by_id(
            params, std::forward<CompletionToken>(token));
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
        const GetFuturesTransactionHistoryDownloadLinkByIdParams& params) const {
        return account_api_.get_futures_transaction_history_download_link_by_id(params);
    }
    /// Asynchronous `get_futures_transaction_history_download_link_by_id()`.
    template <class CompletionToken>
    auto async_get_futures_transaction_history_download_link_by_id(
        const GetFuturesTransactionHistoryDownloadLinkByIdParams& params,
        CompletionToken&& token) const {
        return account_api_.async_get_futures_transaction_history_download_link_by_id(
            params, std::forward<CompletionToken>(token));
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
    get_income_history(const GetIncomeHistoryParams& params = {}) const {
        return account_api_.get_income_history(params);
    }
    /// Asynchronous `get_income_history()`.
    template <class CompletionToken>
    auto async_get_income_history(const GetIncomeHistoryParams& params,
                                  CompletionToken&& token) const {
        return account_api_.async_get_income_history(params, std::forward<CompletionToken>(token));
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
    notional_bracket_for_pair(const NotionalBracketForPairParams& params = {}) const {
        return account_api_.notional_bracket_for_pair(params);
    }
    /// Asynchronous `notional_bracket_for_pair()`.
    template <class CompletionToken>
    auto async_notional_bracket_for_pair(const NotionalBracketForPairParams& params,
                                         CompletionToken&& token) const {
        return account_api_.async_notional_bracket_for_pair(params,
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
    notional_bracket_for_symbol(const NotionalBracketForSymbolParams& params = {}) const {
        return account_api_.notional_bracket_for_symbol(params);
    }
    /// Asynchronous `notional_bracket_for_symbol()`.
    template <class CompletionToken>
    auto async_notional_bracket_for_symbol(const NotionalBracketForSymbolParams& params,
                                           CompletionToken&& token) const {
        return account_api_.async_notional_bracket_for_symbol(params,
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
    user_commission_rate(const UserCommissionRateParams& params) const {
        return account_api_.user_commission_rate(params);
    }
    /// Asynchronous `user_commission_rate()`.
    template <class CompletionToken>
    auto async_user_commission_rate(const UserCommissionRateParams& params,
                                    CompletionToken&& token) const {
        return account_api_.async_user_commission_rate(params,
                                                       std::forward<CompletionToken>(token));
    }

    // MarketDataApi

    /// Basis
    ///
    /// GET /futures/data/basis.
    ///
    /// Query basis
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#basis
    [[nodiscard]] common::RestApiResponse<std::vector<BasisResponseInner>>
    basis(const BasisParams& params) const {
        return market_data_api_.basis(params);
    }
    /// Asynchronous `basis()`.
    template <class CompletionToken>
    auto async_basis(const BasisParams& params, CompletionToken&& token) const {
        return market_data_api_.async_basis(params, std::forward<CompletionToken>(token));
    }

    /// Check Server time
    ///
    /// GET /dapi/v1/time.
    ///
    /// Test connectivity to the Rest API and get the current server time.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#check-server-time
    [[nodiscard]] common::RestApiResponse<CheckServerTimeResponse> check_server_time() const {
        return market_data_api_.check_server_time();
    }
    /// Asynchronous `check_server_time()`.
    template <class CompletionToken> auto async_check_server_time(CompletionToken&& token) const {
        return market_data_api_.async_check_server_time(std::forward<CompletionToken>(token));
    }

    /// Compressed/Aggregate Trades List
    ///
    /// GET /dapi/v1/aggTrades.
    ///
    /// Get compressed, aggregate trades. Market trades that fill in 100ms with
    /// the same price and the same taking side will have the quantity
    /// aggregated.
    ///
    /// Weight(IP): 20
    ///
    /// Notes:
    /// - only trade histories within the past 48 hours (counted from now) can be queried
    /// - If both `startTime` and `endTime` are sent, time between `startTime` and `endTime` must be
    /// less than 1 hour.
    /// - If `fromId`, `startTime`, and `endTime` are not sent, the most recent aggregate trades
    /// will be returned.
    /// - Only market trades will be aggregated and returned, which means the insurance fund trades
    /// and ADL trades won't be aggregated.
    /// - Sending both `startTime`/`endTime` and `fromId` might cause response timeout, please send
    /// either `fromId` or `startTime`/`endTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#compressed-aggregate-trades-list
    [[nodiscard]] common::RestApiResponse<std::vector<CompressedAggregateTradesListResponseInner>>
    compressed_aggregate_trades_list(const CompressedAggregateTradesListParams& params) const {
        return market_data_api_.compressed_aggregate_trades_list(params);
    }
    /// Asynchronous `compressed_aggregate_trades_list()`.
    template <class CompletionToken>
    auto async_compressed_aggregate_trades_list(const CompressedAggregateTradesListParams& params,
                                                CompletionToken&& token) const {
        return market_data_api_.async_compressed_aggregate_trades_list(
            params, std::forward<CompletionToken>(token));
    }

    /// Continuous Contract Kline/Candlestick Data
    ///
    /// GET /dapi/v1/continuousKlines.
    ///
    /// Kline/candlestick bars for a specific contract type. Klines are uniquely identified by their
    /// open time.
    ///
    /// Weight: based on parameter `LIMIT`
    ///
    /// | LIMIT | weight |
    /// | --- | --- |
    /// | [1,100) | 1 |
    /// | [100, 500) | 2 |
    /// | [500, 1000] | 5 |
    /// | > 1000 | 10 |
    ///
    /// Notes:
    /// - The difference between `startTime` and `endTime` can only be up to 200 days
    /// - Between `startTime` and `endTime`, the most recent `limit` data from `endTime` will be
    /// returned:
    ///   - If `startTime` and `endTime` are not sent, current timestamp will be set as `endTime`,
    ///   and the most recent data will be returned.
    ///   - If `startTime` is sent only, the timestamp of 200 days after `startTime` will be set as
    ///   `endTime`(up to the current time)
    ///   - If `endTime` is sent only, the timestamp of 200 days before `endTime` will be set as
    ///   `startTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#continuous-contract-kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<
        std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>
    continuous_contract_kline_candlestick_data(
        const ContinuousContractKlineCandlestickDataParams& params) const {
        return market_data_api_.continuous_contract_kline_candlestick_data(params);
    }
    /// Asynchronous `continuous_contract_kline_candlestick_data()`.
    template <class CompletionToken>
    auto async_continuous_contract_kline_candlestick_data(
        const ContinuousContractKlineCandlestickDataParams& params, CompletionToken&& token) const {
        return market_data_api_.async_continuous_contract_kline_candlestick_data(
            params, std::forward<CompletionToken>(token));
    }

    /// Exchange Information
    ///
    /// GET /dapi/v1/exchangeInfo.
    ///
    /// Current exchange trading rules and symbol information
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#exchange-information
    [[nodiscard]] common::RestApiResponse<ExchangeInformationResponse>
    exchange_information() const {
        return market_data_api_.exchange_information();
    }
    /// Asynchronous `exchange_information()`.
    template <class CompletionToken>
    auto async_exchange_information(CompletionToken&& token) const {
        return market_data_api_.async_exchange_information(std::forward<CompletionToken>(token));
    }

    /// Get Funding Rate History of Perpetual Futures
    ///
    /// GET /dapi/v1/fundingRate.
    ///
    /// Get Funding Rate History of Perpetual Futures
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - empty array will be returned for delivery symbols.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#get-funding-rate-history-of-perpetual-futures
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetFundingRateHistoryOfPerpetualFuturesResponseInner>>
    get_funding_rate_history_of_perpetual_futures(
        const GetFundingRateHistoryOfPerpetualFuturesParams& params) const {
        return market_data_api_.get_funding_rate_history_of_perpetual_futures(params);
    }
    /// Asynchronous `get_funding_rate_history_of_perpetual_futures()`.
    template <class CompletionToken>
    auto async_get_funding_rate_history_of_perpetual_futures(
        const GetFundingRateHistoryOfPerpetualFuturesParams& params,
        CompletionToken&& token) const {
        return market_data_api_.async_get_funding_rate_history_of_perpetual_futures(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Funding Rate Info
    ///
    /// GET /dapi/v1/fundingInfo.
    ///
    /// Query funding rate info for symbols that had
    /// FundingRateCap/FundingRateFloor/fundingIntervalHours adjustment
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#get-funding-rate-info
    [[nodiscard]] common::RestApiResponse<std::vector<GetFundingRateInfoResponseInner>>
    get_funding_rate_info() const {
        return market_data_api_.get_funding_rate_info();
    }
    /// Asynchronous `get_funding_rate_info()`.
    template <class CompletionToken>
    auto async_get_funding_rate_info(CompletionToken&& token) const {
        return market_data_api_.async_get_funding_rate_info(std::forward<CompletionToken>(token));
    }

    /// Index Price and Mark Price
    ///
    /// GET /dapi/v1/premiumIndex.
    ///
    /// Query index price and mark price
    ///
    /// Weight(IP): 10
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#index-price-and-mark-price
    [[nodiscard]] common::RestApiResponse<std::vector<IndexPriceAndMarkPriceResponseInner>>
    index_price_and_mark_price(const IndexPriceAndMarkPriceParams& params = {}) const {
        return market_data_api_.index_price_and_mark_price(params);
    }
    /// Asynchronous `index_price_and_mark_price()`.
    template <class CompletionToken>
    auto async_index_price_and_mark_price(const IndexPriceAndMarkPriceParams& params,
                                          CompletionToken&& token) const {
        return market_data_api_.async_index_price_and_mark_price(
            params, std::forward<CompletionToken>(token));
    }

    /// Index Price Kline/Candlestick Data
    ///
    /// GET /dapi/v1/indexPriceKlines.
    ///
    /// Kline/candlestick bars for the index price of a pair. Klines are uniquely identified by
    /// their open time.
    ///
    /// Weight: Based on parameter `LIMIT`
    ///
    /// | LIMIT | weight |
    /// | --- | --- |
    /// | [1,100) | 1 |
    /// | [100, 500) | 2 |
    /// | [500, 1000] | 5 |
    /// | > 1000 | 10 |
    ///
    /// Notes:
    /// - The difference between `startTime` and `endTime` can only be up to 200 days
    /// - Between `startTime` and `endTime`, the most recent `limit` data from `endTime` will be
    /// returned:
    ///   - If `startTime` and `endTime` are not sent, current timestamp will be set as `endTime`,
    ///   and the most recent data will be returned.
    ///   - If `startTime` is sent only, the timestamp of 200 days after `startTime` will be set as
    ///   `endTime`(up to the current time)
    ///   - If `endTime` is sent only, the timestamp of 200 days before `endTime` will be set as
    ///   `startTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#index-price-kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<
        std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>
    index_price_kline_candlestick_data(const IndexPriceKlineCandlestickDataParams& params) const {
        return market_data_api_.index_price_kline_candlestick_data(params);
    }
    /// Asynchronous `index_price_kline_candlestick_data()`.
    template <class CompletionToken>
    auto
    async_index_price_kline_candlestick_data(const IndexPriceKlineCandlestickDataParams& params,
                                             CompletionToken&& token) const {
        return market_data_api_.async_index_price_kline_candlestick_data(
            params, std::forward<CompletionToken>(token));
    }

    /// Kline/Candlestick Data
    ///
    /// GET /dapi/v1/klines.
    ///
    /// Kline/candlestick bars for a symbol. Klines are uniquely identified by their open time.
    ///
    /// Weight: Based on parameter `LIMIT`
    ///
    /// | LIMIT | weight |
    /// | --- | --- |
    /// | [1,100) | 1 |
    /// | [100, 500) | 2 |
    /// | [500, 1000] | 5 |
    /// | > 1000 | 10 |
    ///
    /// Notes:
    /// - The difference between `startTime` and `endTime` can only be up to 200 days
    /// - Between `startTime` and `endTime`, the most recent `limit` data from `endTime` will be
    /// returned:
    ///   - If `startTime` and `endTime` are not sent, current timestamp will be set as `endTime`,
    ///   and the most recent data will be returned.
    ///   - If `startTime` is sent only, the timestamp of 200 days after `startTime` will be set as
    ///   `endTime`(up to the current time)
    ///   - If `endTime` is sent only, the timestamp of 200 days before `endTime` will be set as
    ///   `startTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<
        std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>
    kline_candlestick_data(const KlineCandlestickDataParams& params) const {
        return market_data_api_.kline_candlestick_data(params);
    }
    /// Asynchronous `kline_candlestick_data()`.
    template <class CompletionToken>
    auto async_kline_candlestick_data(const KlineCandlestickDataParams& params,
                                      CompletionToken&& token) const {
        return market_data_api_.async_kline_candlestick_data(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Long/Short Ratio
    ///
    /// GET /futures/data/globalLongShortAccountRatio.
    ///
    /// Query symbol Long/Short Ratio
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#long-short-ratio
    [[nodiscard]] common::RestApiResponse<std::vector<LongShortRatioResponseInner>>
    long_short_ratio(const LongShortRatioParams& params) const {
        return market_data_api_.long_short_ratio(params);
    }
    /// Asynchronous `long_short_ratio()`.
    template <class CompletionToken>
    auto async_long_short_ratio(const LongShortRatioParams& params, CompletionToken&& token) const {
        return market_data_api_.async_long_short_ratio(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Mark Price Kline/Candlestick Data
    ///
    /// GET /dapi/v1/markPriceKlines.
    ///
    /// Kline/candlestick bars for the mark price of a symbol. Klines are uniquely identified by
    /// their open time.
    ///
    /// Weight: Based on parameter `LIMIT`
    ///
    /// | LIMIT | weight |
    /// | --- | --- |
    /// | [1,100) | 1 |
    /// | [100, 500) | 2 |
    /// | [500, 1000] | 5 |
    /// | > 1000 | 10 |
    ///
    /// Notes:
    /// - The difference between `startTime` and `endTime` can only be up to 200 days
    /// - Between `startTime` and `endTime`, the most recent `limit` data from `endTime` will be
    /// returned:
    ///   - If `startTime` and `endTime` are not sent, current timestamp will be set as `endTime`,
    ///   and the most recent data will be returned.
    ///   - If `startTime` is sent only, the timestamp of 200 days after `startTime` will be set as
    ///   `endTime`(up to the current time)
    ///   - If `endTime` is sent only, the timestamp of 200 days before `endTime` will be set as
    ///   `startTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#mark-price-kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<
        std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>
    mark_price_kline_candlestick_data(const MarkPriceKlineCandlestickDataParams& params) const {
        return market_data_api_.mark_price_kline_candlestick_data(params);
    }
    /// Asynchronous `mark_price_kline_candlestick_data()`.
    template <class CompletionToken>
    auto async_mark_price_kline_candlestick_data(const MarkPriceKlineCandlestickDataParams& params,
                                                 CompletionToken&& token) const {
        return market_data_api_.async_mark_price_kline_candlestick_data(
            params, std::forward<CompletionToken>(token));
    }

    /// Old Trades Lookup (MARKET_DATA)
    ///
    /// GET /dapi/v1/historicalTrades.
    ///
    /// Get older market historical trades.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: MARKET_DATA
    ///
    /// Notes:
    /// - Market trades means trades filled in the order book. Only market trades will be returned,
    /// which means the insurance fund trades and ADL trades won't be returned.
    /// - Only supports data from within the last one month
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#old-trades-lookup
    [[nodiscard]] common::RestApiResponse<std::vector<OldTradesLookupResponseInner>>
    old_trades_lookup(const OldTradesLookupParams& params) const {
        return market_data_api_.old_trades_lookup(params);
    }
    /// Asynchronous `old_trades_lookup()`.
    template <class CompletionToken>
    auto async_old_trades_lookup(const OldTradesLookupParams& params,
                                 CompletionToken&& token) const {
        return market_data_api_.async_old_trades_lookup(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Open Interest
    ///
    /// GET /dapi/v1/openInterest.
    ///
    /// Get present open interest of a specific symbol.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#open-interest
    [[nodiscard]] common::RestApiResponse<OpenInterestResponse>
    open_interest(const OpenInterestParams& params) const {
        return market_data_api_.open_interest(params);
    }
    /// Asynchronous `open_interest()`.
    template <class CompletionToken>
    auto async_open_interest(const OpenInterestParams& params, CompletionToken&& token) const {
        return market_data_api_.async_open_interest(params, std::forward<CompletionToken>(token));
    }

    /// Open Interest Statistics
    ///
    /// GET /futures/data/openInterestHist.
    ///
    /// Query open interest stats
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#open-interest-statistics
    [[nodiscard]] common::RestApiResponse<std::vector<OpenInterestStatisticsResponseInner>>
    open_interest_statistics(const OpenInterestStatisticsParams& params) const {
        return market_data_api_.open_interest_statistics(params);
    }
    /// Asynchronous `open_interest_statistics()`.
    template <class CompletionToken>
    auto async_open_interest_statistics(const OpenInterestStatisticsParams& params,
                                        CompletionToken&& token) const {
        return market_data_api_.async_open_interest_statistics(
            params, std::forward<CompletionToken>(token));
    }

    /// Order Book
    ///
    /// GET /dapi/v1/depth.
    ///
    /// Query orderbook on specific symbol
    ///
    /// Weight: Adjusted based on the limit:
    ///
    /// | Limit | Weight |
    /// | ------------ | ------------ |
    /// | 5, 10, 20, 50 | 2 |
    /// | 100 | 5 |
    /// | 500 | 10 |
    /// | 1000 | 20 |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#order-book
    [[nodiscard]] common::RestApiResponse<OrderBookResponse>
    order_book(const OrderBookParams& params) const {
        return market_data_api_.order_book(params);
    }
    /// Asynchronous `order_book()`.
    template <class CompletionToken>
    auto async_order_book(const OrderBookParams& params, CompletionToken&& token) const {
        return market_data_api_.async_order_book(params, std::forward<CompletionToken>(token));
    }

    /// Premium index Kline Data
    ///
    /// GET /dapi/v1/premiumIndexKlines.
    ///
    /// Premium index kline bars of a symbol. Klines are uniquely identified by their open time.
    ///
    /// Weight: Based on parameter `LIMIT`
    ///
    /// | LIMIT       | weight |
    /// | ----------- | ------ |
    /// | [1,100)     | 1      |
    /// | [100, 500)  | 2      |
    /// | [500, 1000] | 5      |
    /// | > 1000      | 10     |
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent klines are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#premium-index-kline-data
    [[nodiscard]] common::RestApiResponse<std::vector<std::vector<PremiumIndexKlineDataItemInner>>>
    premium_index_kline_data(const PremiumIndexKlineDataParams& params) const {
        return market_data_api_.premium_index_kline_data(params);
    }
    /// Asynchronous `premium_index_kline_data()`.
    template <class CompletionToken>
    auto async_premium_index_kline_data(const PremiumIndexKlineDataParams& params,
                                        CompletionToken&& token) const {
        return market_data_api_.async_premium_index_kline_data(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Index Price Constituents
    ///
    /// GET /dapi/v1/constituents.
    ///
    /// Query index price constituents
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#query-index-price-constituents
    [[nodiscard]] common::RestApiResponse<QueryIndexPriceConstituentsResponse>
    query_index_price_constituents(const QueryIndexPriceConstituentsParams& params) const {
        return market_data_api_.query_index_price_constituents(params);
    }
    /// Asynchronous `query_index_price_constituents()`.
    template <class CompletionToken>
    auto async_query_index_price_constituents(const QueryIndexPriceConstituentsParams& params,
                                              CompletionToken&& token) const {
        return market_data_api_.async_query_index_price_constituents(
            params, std::forward<CompletionToken>(token));
    }

    /// Recent Trades List
    ///
    /// GET /dapi/v1/trades.
    ///
    /// Get recent market trades
    ///
    /// Weight(IP): 5
    ///
    /// Notes:
    /// - Market trades means trades filled in the order book. Only market trades will be returned,
    /// which means the insurance fund trades and ADL trades won't be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#recent-trades-list
    [[nodiscard]] common::RestApiResponse<std::vector<RecentTradesListResponseInner>>
    recent_trades_list(const RecentTradesListParams& params) const {
        return market_data_api_.recent_trades_list(params);
    }
    /// Asynchronous `recent_trades_list()`.
    template <class CompletionToken>
    auto async_recent_trades_list(const RecentTradesListParams& params,
                                  CompletionToken&& token) const {
        return market_data_api_.async_recent_trades_list(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Symbol Order Book Ticker
    ///
    /// GET /dapi/v1/ticker/bookTicker.
    ///
    /// Best price/qty on the order book for a symbol or symbols.
    ///
    /// Weight: **2** for a single symbol, **5** when the symbol parameter is omitted
    ///
    /// Notes:
    /// - Symbol and pair cannot be sent together
    /// - If a pair is sent,tickers for all symbols of the pair will be returned
    /// - If either a pair or symbol is sent, tickers for all symbols of all pairs will be returned
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#symbol-order-book-ticker
    [[nodiscard]] common::RestApiResponse<std::vector<SymbolOrderBookTickerResponseInner>>
    symbol_order_book_ticker(const SymbolOrderBookTickerParams& params = {}) const {
        return market_data_api_.symbol_order_book_ticker(params);
    }
    /// Asynchronous `symbol_order_book_ticker()`.
    template <class CompletionToken>
    auto async_symbol_order_book_ticker(const SymbolOrderBookTickerParams& params,
                                        CompletionToken&& token) const {
        return market_data_api_.async_symbol_order_book_ticker(
            params, std::forward<CompletionToken>(token));
    }

    /// Symbol Price Ticker
    ///
    /// GET /dapi/v1/ticker/price.
    ///
    /// Latest price for a symbol or symbols.
    ///
    /// Weight: **1** for a single symbol, **2** when the symbol parameter is omitted
    ///
    /// Notes:
    /// - Symbol and pair cannot be sent together
    /// - If a pair is sent,tickers for all symbols of the pair will be returned
    /// - If either a pair or symbol is sent, tickers for all symbols of all pairs will be returned
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#symbol-price-ticker
    [[nodiscard]] common::RestApiResponse<std::vector<SymbolPriceTickerResponseInner>>
    symbol_price_ticker(const SymbolPriceTickerParams& params = {}) const {
        return market_data_api_.symbol_price_ticker(params);
    }
    /// Asynchronous `symbol_price_ticker()`.
    template <class CompletionToken>
    auto async_symbol_price_ticker(const SymbolPriceTickerParams& params,
                                   CompletionToken&& token) const {
        return market_data_api_.async_symbol_price_ticker(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Taker Buy/Sell Volume
    ///
    /// GET /futures/data/takerBuySellVol.
    ///
    /// Taker Buy Volume: the total volume of buy orders filled by takers within
    /// the period.
    ///
    /// Taker Sell Volume: the total volume of sell orders filled by takers
    /// within the period.
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#taker-buy-sell-volume
    [[nodiscard]] common::RestApiResponse<std::vector<TakerBuySellVolumeResponseInner>>
    taker_buy_sell_volume(const TakerBuySellVolumeParams& params) const {
        return market_data_api_.taker_buy_sell_volume(params);
    }
    /// Asynchronous `taker_buy_sell_volume()`.
    template <class CompletionToken>
    auto async_taker_buy_sell_volume(const TakerBuySellVolumeParams& params,
                                     CompletionToken&& token) const {
        return market_data_api_.async_taker_buy_sell_volume(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Test Connectivity
    ///
    /// GET /dapi/v1/ping.
    ///
    /// Test connectivity to the Rest API.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#test-connectivity
    [[nodiscard]] common::RestApiResponse<boost::json::value> test_connectivity() const {
        return market_data_api_.test_connectivity();
    }
    /// Asynchronous `test_connectivity()`.
    template <class CompletionToken> auto async_test_connectivity(CompletionToken&& token) const {
        return market_data_api_.async_test_connectivity(std::forward<CompletionToken>(token));
    }

    /// 24hr Ticker Price Change Statistics
    ///
    /// GET /dapi/v1/ticker/24hr.
    ///
    /// 24 hour rolling window price change statistics.
    ///
    /// Weight: **1** for a single symbol, **40** when the symbol parameter is omitted
    /// **Careful** when accessing this with no symbol.
    ///
    /// Notes:
    /// - Symbol and pair cannot be sent together
    /// - If a pair is sent,tickers for all symbols of the pair will be returned
    /// - If either a pair or symbol is sent, tickers for all symbols of all pairs will be returned
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#ticker24hr-price-change-statistics
    [[nodiscard]] common::RestApiResponse<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>
    ticker24hr_price_change_statistics(
        const Ticker24hrPriceChangeStatisticsParams& params = {}) const {
        return market_data_api_.ticker24hr_price_change_statistics(params);
    }
    /// Asynchronous `ticker24hr_price_change_statistics()`.
    template <class CompletionToken>
    auto
    async_ticker24hr_price_change_statistics(const Ticker24hrPriceChangeStatisticsParams& params,
                                             CompletionToken&& token) const {
        return market_data_api_.async_ticker24hr_price_change_statistics(
            params, std::forward<CompletionToken>(token));
    }

    /// Top Trader Long/Short Account Ratio
    ///
    /// GET /futures/data/topLongShortAccountRatio.
    ///
    /// The proportion of net long and net short accounts to total accounts of
    /// the top 20% users with the highest margin balance. Each account is
    /// counted once only.
    ///
    /// Long Account % = Accounts of top traders with net long positions / Total
    /// accounts of top traders with open positions
    ///
    /// Short Account % = Accounts of top traders with net short positions /
    /// Total accounts of top traders with open positions
    ///
    /// Long/Short Ratio (Accounts) = Long Account % / Short Account %
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: Accounts
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#top-trader-long-short-ratio-accounts
    [[nodiscard]] common::RestApiResponse<std::vector<TopTraderLongShortRatioAccountsResponseInner>>
    top_trader_long_short_ratio_accounts(
        const TopTraderLongShortRatioAccountsParams& params) const {
        return market_data_api_.top_trader_long_short_ratio_accounts(params);
    }
    /// Asynchronous `top_trader_long_short_ratio_accounts()`.
    template <class CompletionToken>
    auto
    async_top_trader_long_short_ratio_accounts(const TopTraderLongShortRatioAccountsParams& params,
                                               CompletionToken&& token) const {
        return market_data_api_.async_top_trader_long_short_ratio_accounts(
            params, std::forward<CompletionToken>(token));
    }

    /// Top Trader Long/Short Position Ratio
    ///
    /// GET /futures/data/topLongShortPositionRatio.
    ///
    /// The proportion of net long and net short positions to total open
    /// positions of the top 20% users with the highest margin balance.
    ///
    /// Long Position % = Long positions of top traders / Total open positions
    /// of top traders
    ///
    /// Short Position % = Short positions of top traders / Total open positions
    /// of top traders
    ///
    /// Long/Short Ratio (Positions) = Long Position % / Short Position %
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: Positions
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#top-trader-long-short-ratio-positions
    [[nodiscard]] common::RestApiResponse<
        std::vector<TopTraderLongShortRatioPositionsResponseInner>>
    top_trader_long_short_ratio_positions(
        const TopTraderLongShortRatioPositionsParams& params) const {
        return market_data_api_.top_trader_long_short_ratio_positions(params);
    }
    /// Asynchronous `top_trader_long_short_ratio_positions()`.
    template <class CompletionToken>
    auto async_top_trader_long_short_ratio_positions(
        const TopTraderLongShortRatioPositionsParams& params, CompletionToken&& token) const {
        return market_data_api_.async_top_trader_long_short_ratio_positions(
            params, std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// Account Trade List (USER_DATA)
    ///
    /// GET /dapi/v1/userTrades.
    ///
    /// Get trades for a specific account and symbol.
    ///
    /// Weight: **20** with symbol，**40** with pair (after CM migration: **5** flat)
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either symbol or pair must be sent
    /// - Symbol and pair cannot be sent together
    /// - Pair and fromId cannot be sent together
    /// - OrderId can only be sent together with symbol
    /// - If a pair is sent,tickers for all symbols of the pair will be returned
    /// - The parameter `fromId` cannot be sent with `startTime` or `endTime`
    /// - If startTime and endTime are both not sent, then the last 7 days' data will be returned.
    /// - The time between startTime and endTime cannot be longer than 7 days.
    /// - Only support querying trade in the past 3 months
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<AccountTradeListResponseInner>>
    account_trade_list(const AccountTradeListParams& params = {}) const {
        return trade_api_.account_trade_list(params);
    }
    /// Asynchronous `account_trade_list()`.
    template <class CompletionToken>
    auto async_account_trade_list(const AccountTradeListParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_account_trade_list(params, std::forward<CompletionToken>(token));
    }

    /// All Orders (USER_DATA)
    ///
    /// GET /dapi/v1/allOrders.
    ///
    /// Get all account orders; active, canceled, or filled.
    ///
    /// * These orders will not be found:
    ///   * order status is CANCELED or EXPIRED AND order has NO filled trade AND created time + 3
    ///   days < current time
    ///   * order create time + 90 days < current time
    ///
    /// Weight: **20** with symbol, **40** with pair (after CM migration: **5** flat)
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `symbol` or `pair` must be sent.
    /// - `pair` can't be sent with `orderId`
    /// - If `orderId` is set, it will get orders >= that `orderId`. Otherwise most recent orders
    /// are returned.
    /// - If orderId is set, it will get orders >= that orderId. Otherwise most recent orders are
    /// returned.
    /// - The query time period must be less then 7 days( default as the recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#all-orders
    [[nodiscard]] common::RestApiResponse<std::vector<AllOrdersResponseInner>>
    all_orders(const AllOrdersParams& params = {}) const {
        return trade_api_.all_orders(params);
    }
    /// Asynchronous `all_orders()`.
    template <class CompletionToken>
    auto async_all_orders(const AllOrdersParams& params, CompletionToken&& token) const {
        return trade_api_.async_all_orders(params, std::forward<CompletionToken>(token));
    }

    /// Auto-Cancel All Open Orders (TRADE)
    ///
    /// POST /dapi/v1/countdownCancelAll.
    ///
    /// Cancel all open orders of the specified symbol at the end of the
    /// specified countdown. This rest endpoint means to ensure your open orders
    /// are canceled in case of an outage. The endpoint should be called
    /// repeatedly as heartbeats so that the existing countdown time can be
    /// canceled and repalced by a new one. The system will check all countdowns
    /// **approximately every 10 milliseconds**, so please note that sufficient
    /// redundancy should be considered when using this function. We do not
    /// recommend setting the countdown time to be too precise or too small.
    ///
    /// * Example usage:
    ///
    /// Call this endpoint at 30s intervals with an countdownTime of 120000
    /// (120s).
    ///
    /// If this endpoint is not called within 120 seconds, all your orders of
    /// the specified symbol will be automatically canceled.
    ///
    /// If this endpoint is called with an countdownTime of 0, the countdown
    /// timer will be stopped.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#auto-cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<AutoCancelAllOpenOrdersResponse>
    auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params) const {
        return trade_api_.auto_cancel_all_open_orders(params);
    }
    /// Asynchronous `auto_cancel_all_open_orders()`.
    template <class CompletionToken>
    auto async_auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_auto_cancel_all_open_orders(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Cancel All Open Orders (TRADE)
    ///
    /// DELETE /dapi/v1/allOpenOrders.
    ///
    /// Cancel All Open Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllOpenOrdersResponse>
    cancel_all_open_orders(const CancelAllOpenOrdersParams& params) const {
        return trade_api_.cancel_all_open_orders(params);
    }
    /// Asynchronous `cancel_all_open_orders()`.
    template <class CompletionToken>
    auto async_cancel_all_open_orders(const CancelAllOpenOrdersParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_cancel_all_open_orders(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Cancel Multiple Orders (TRADE)
    ///
    /// DELETE /dapi/v1/batchOrders.
    ///
    /// Cancel Multiple Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderIdList` or `origClientOrderIdList ` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#cancel-multiple-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CancelMultipleOrdersResponseInner>>
    cancel_multiple_orders(const CancelMultipleOrdersParams& params) const {
        return trade_api_.cancel_multiple_orders(params);
    }
    /// Asynchronous `cancel_multiple_orders()`.
    template <class CompletionToken>
    auto async_cancel_multiple_orders(const CancelMultipleOrdersParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_cancel_multiple_orders(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Modify Multiple Orders (TRADE)
    ///
    /// PUT /dapi/v1/batchOrders.
    ///
    /// Modify Multiple Orders
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Parameter rules are same with `Modify Order`
    /// - Batch modify orders are processed concurrently, and the order of matching is not
    /// guaranteed.
    /// - The order of returned contents for batch modify orders is the same as the order of the
    /// order list.
    /// - One order can only be modfied for less than 10000 times
    /// - `modifyId` is an optional user-defined identifier passed through as-is; the server does
    /// not validate its uniqueness. If omitted, it is not included in the response.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#modify-multiple-orders
    [[nodiscard]] common::RestApiResponse<std::vector<ModifyMultipleOrdersResponseInner>>
    modify_multiple_orders(const ModifyMultipleOrdersParams& params) const {
        return trade_api_.modify_multiple_orders(params);
    }
    /// Asynchronous `modify_multiple_orders()`.
    template <class CompletionToken>
    auto async_modify_multiple_orders(const ModifyMultipleOrdersParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_modify_multiple_orders(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Place Multiple Orders (TRADE)
    ///
    /// POST /dapi/v1/batchOrders.
    ///
    /// Place multiple orders
    ///
    /// * Parameter rules are same with `New Order`
    /// * Batch orders are processed concurrently, and the order of matching is not guaranteed.
    /// * The order of returned contents for batch orders is the same as the order of the order
    /// list.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - `batchOrders` must be a JSON array of order parameter objects.
    /// - Example:
    ///   `/dapi/v1/batchOrders?batchOrders=[{"type":"LIMIT","timeInForce":"GTC","symbol":"BTCUSD_PERP","side":"BUY","price":"10001","quantity":"1"}]`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#place-multiple-orders
    [[nodiscard]] common::RestApiResponse<std::vector<PlaceMultipleOrdersResponseInner>>
    place_multiple_orders(const PlaceMultipleOrdersParams& params) const {
        return trade_api_.place_multiple_orders(params);
    }
    /// Asynchronous `place_multiple_orders()`.
    template <class CompletionToken>
    auto async_place_multiple_orders(const PlaceMultipleOrdersParams& params,
                                     CompletionToken&& token) const {
        return trade_api_.async_place_multiple_orders(params, std::forward<CompletionToken>(token));
    }

    /// Cancel Order (TRADE)
    ///
    /// DELETE /dapi/v1/order.
    ///
    /// Cancel an active order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#cancel-order
    [[nodiscard]] common::RestApiResponse<CancelOrderResponse>
    cancel_order(const CancelOrderParams& params) const {
        return trade_api_.cancel_order(params);
    }
    /// Asynchronous `cancel_order()`.
    template <class CompletionToken>
    auto async_cancel_order(const CancelOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_cancel_order(params, std::forward<CompletionToken>(token));
    }

    /// Modify Order (TRADE)
    ///
    /// PUT /dapi/v1/order.
    ///
    /// Order modify function, currently only LIMIT order modification is supported, modified orders
    /// will be reordered in the match queue
    ///
    /// Weight(IP): 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    /// - Either `quantity` or `price` must be sent. *(After CM migration, both `quantity` and
    /// `price` are required.)*
    /// - When the new `quantity` or `price` doesn't satisfy PRICE_FILTER / PERCENT_FILTER /
    /// LOT_SIZE, amendment will be rejected and the order will stay as it is.
    /// - However the order will be cancelled by the amendment in the following situations:
    ///   - when the order is in partially filled status and the new `quantity` <= `executedQty`
    ///   - When the order is `GTX` and the new price will cause it to be executed immediately
    /// - One order can only be modfied for less than 10000 times
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#modify-order
    [[nodiscard]] common::RestApiResponse<ModifyOrderResponse>
    modify_order(const ModifyOrderParams& params) const {
        return trade_api_.modify_order(params);
    }
    /// Asynchronous `modify_order()`.
    template <class CompletionToken>
    auto async_modify_order(const ModifyOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_modify_order(params, std::forward<CompletionToken>(token));
    }

    /// New Order (TRADE)
    ///
    /// POST /dapi/v1/order.
    ///
    /// Send in a new order.
    ///
    /// Weight: 1 on 1min order rate limit(X-MBX-ORDER-COUNT-1M)
    /// 0 on IP rate limit(x-mbx-used-weight-1m)
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional mandatory parameters based on `type`:
    ///   - Order with type `STOP`, parameter `timeInForce` can be sent ( default `GTC`).
    ///   - Order with type `TAKE_PROFIT`, parameter `timeInForce` can be sent ( default `GTC`).
    ///   - Condition orders will be triggered when:
    ///   - If parameter`priceProtect`is sent as true:
    ///   - when price reaches the `stopPrice` ，the difference rate between "MARK_PRICE" and
    ///   "CONTRACT_PRICE" cannot be larger than the "triggerProtect" of the symbol
    ///   - "triggerProtect" of a symbol can be got from `GET /dapi/v1/exchangeInfo`
    ///   - `STOP`, `STOP_MARKET`:
    ///   - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `stopPrice`
    ///   - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `stopPrice`
    ///   - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`:
    ///   - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `stopPrice`
    ///   - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `stopPrice`
    ///   - `TRAILING_STOP_MARKET`:
    ///   - BUY: the lowest price after order placed <= `activationPrice`, and the latest price >=
    ///   the lowest price * (1 + `callbackRate`)
    ///   - SELL: the highest price after order placed >= `activationPrice`, and the latest price <=
    ///   the highest price * (1 - `callbackRate`)
    ///
    ///   - For `TRAILING_STOP_MARKET`, if you got such error code. > `{"code": -2021, "msg": "Order
    ///   would immediately trigger."}` > means that the parameters you send do not meet the
    ///   following requirements:
    ///   - BUY: `activationPrice` should be smaller than latest price.
    ///   - SELL: `activationPrice` should be larger than latest price.
    ///   - If `newOrderRespType ` is sent as `RESULT` :
    ///   - `MARKET` order: the final FILLED result of the order will be return directly.
    ///   - `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED or
    ///   EXPIRED) will be returned directly.
    ///   - `STOP_MARKET`, `TAKE_PROFIT_MARKET` with `closePosition`=`true`:
    ///   - Follow the same rules for condition orders.
    ///   - If triggered,**close all** current long position( if `SELL`) or current short position(
    ///   if `BUY`).
    ///   - Cannot be used with `quantity` parameter
    ///   - Cannot be used with `reduceOnly` parameter
    ///   - In Hedge Mode,cannot be used with `BUY` orders in `LONG` position side. and cannot be
    ///   used with `SELL` orders in `SHORT` position side
    ///
    ///   - `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#new-order
    [[nodiscard]] common::RestApiResponse<NewOrderResponse>
    new_order(const NewOrderParams& params) const {
        return trade_api_.new_order(params);
    }
    /// Asynchronous `new_order()`.
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_new_order(params, std::forward<CompletionToken>(token));
    }

    /// Query Order (USER_DATA)
    ///
    /// GET /dapi/v1/order.
    ///
    /// Check an order's status.
    ///
    /// * These orders will not be found:
    ///   * order status is CANCELED or EXPIRED AND order has NO filled trade AND created time + 3
    ///   days < current time
    ///   * order create time + 90 days < current time
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#query-order
    [[nodiscard]] common::RestApiResponse<QueryOrderResponse>
    query_order(const QueryOrderParams& params) const {
        return trade_api_.query_order(params);
    }
    /// Asynchronous `query_order()`.
    template <class CompletionToken>
    auto async_query_order(const QueryOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_query_order(params, std::forward<CompletionToken>(token));
    }

    /// Change Initial Leverage (TRADE)
    ///
    /// POST /dapi/v1/leverage.
    ///
    /// Change user's initial leverage in the specific symbol market.
    ///
    /// For Hedge Mode, LONG and SHORT positions of one symbol use the same
    /// initial leverage and share a total notional value.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#change-initial-leverage
    [[nodiscard]] common::RestApiResponse<ChangeInitialLeverageResponse>
    change_initial_leverage(const ChangeInitialLeverageParams& params) const {
        return trade_api_.change_initial_leverage(params);
    }
    /// Asynchronous `change_initial_leverage()`.
    template <class CompletionToken>
    auto async_change_initial_leverage(const ChangeInitialLeverageParams& params,
                                       CompletionToken&& token) const {
        return trade_api_.async_change_initial_leverage(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Change Margin Type (TRADE)
    ///
    /// POST /dapi/v1/marginType.
    ///
    /// Change user's margin type in the specific symbol market.For Hedge Mode,
    /// LONG and SHORT positions of one symbol use the same margin type.
    ///
    /// With ISOLATED margin type, margins of the LONG and SHORT positions are
    /// isolated from each other.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#change-margin-type
    [[nodiscard]] common::RestApiResponse<ChangeMarginTypeResponse>
    change_margin_type(const ChangeMarginTypeParams& params) const {
        return trade_api_.change_margin_type(params);
    }
    /// Asynchronous `change_margin_type()`.
    template <class CompletionToken>
    auto async_change_margin_type(const ChangeMarginTypeParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_change_margin_type(params, std::forward<CompletionToken>(token));
    }

    /// Change Position Mode (TRADE)
    ///
    /// POST /dapi/v1/positionSide/dual.
    ///
    /// Change user's position mode (Hedge Mode or One-way Mode ) on ***EVERY symbol***.
    ///
    /// **After CM migration**, UM and CM share the **same** `dualSidePosition` setting. Calling
    /// this endpoint flips both UM and CM at once. If either side has any open order or open
    /// position, the change is rejected:
    /// - `-4067` (open orders exist)
    /// - `-4068` (open position exists)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#change-position-mode
    [[nodiscard]] common::RestApiResponse<ChangePositionModeResponse>
    change_position_mode(const ChangePositionModeParams& params) const {
        return trade_api_.change_position_mode(params);
    }
    /// Asynchronous `change_position_mode()`.
    template <class CompletionToken>
    auto async_change_position_mode(const ChangePositionModeParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_change_position_mode(params, std::forward<CompletionToken>(token));
    }

    /// Current All Open Orders (USER_DATA)
    ///
    /// GET /dapi/v1/openOrders.
    ///
    /// Get all open orders on a symbol. **Careful** when accessing this with no symbol.
    ///
    /// Weight(IP): null
    ///
    /// Weight: **1** for a single symbol, **40** for mutltiple symbols
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#current-all-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CurrentAllOpenOrdersResponseInner>>
    current_all_open_orders(const CurrentAllOpenOrdersParams& params = {}) const {
        return trade_api_.current_all_open_orders(params);
    }
    /// Asynchronous `current_all_open_orders()`.
    template <class CompletionToken>
    auto async_current_all_open_orders(const CurrentAllOpenOrdersParams& params,
                                       CompletionToken&& token) const {
        return trade_api_.async_current_all_open_orders(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Get Order Modify History (USER_DATA)
    ///
    /// GET /dapi/v1/orderAmendment.
    ///
    /// Get order modification history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    /// - Order modify history longer than 3 month is not avaliable
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#get-order-modify-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetOrderModifyHistoryResponseInner>>
    get_order_modify_history(const GetOrderModifyHistoryParams& params) const {
        return trade_api_.get_order_modify_history(params);
    }
    /// Asynchronous `get_order_modify_history()`.
    template <class CompletionToken>
    auto async_get_order_modify_history(const GetOrderModifyHistoryParams& params,
                                        CompletionToken&& token) const {
        return trade_api_.async_get_order_modify_history(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Get Position Margin Change History (TRADE)
    ///
    /// GET /dapi/v1/positionMargin/history.
    ///
    /// Get position margin change history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#get-position-margin-change-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetPositionMarginChangeHistoryResponseInner>>
    get_position_margin_change_history(const GetPositionMarginChangeHistoryParams& params) const {
        return trade_api_.get_position_margin_change_history(params);
    }
    /// Asynchronous `get_position_margin_change_history()`.
    template <class CompletionToken>
    auto
    async_get_position_margin_change_history(const GetPositionMarginChangeHistoryParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_get_position_margin_change_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Modify Isolated Position Margin (TRADE)
    ///
    /// POST /dapi/v1/positionMargin.
    ///
    /// Modify Isolated Position Margin
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Only for isolated symbol
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#modify-isolated-position-margin
    [[nodiscard]] common::RestApiResponse<ModifyIsolatedPositionMarginResponse>
    modify_isolated_position_margin(const ModifyIsolatedPositionMarginParams& params) const {
        return trade_api_.modify_isolated_position_margin(params);
    }
    /// Asynchronous `modify_isolated_position_margin()`.
    template <class CompletionToken>
    auto async_modify_isolated_position_margin(const ModifyIsolatedPositionMarginParams& params,
                                               CompletionToken&& token) const {
        return trade_api_.async_modify_isolated_position_margin(
            params, std::forward<CompletionToken>(token));
    }

    /// Position ADL Quantile Estimation (USER_DATA)
    ///
    /// GET /dapi/v1/adlQuantile.
    ///
    /// Query position ADL quantile estimation
    ///
    /// * Values update every 30s.
    /// * Values 0, 1, 2, 3, 4 shows the queue position and possibility of ADL from low to high.
    /// * For positions of the symbol are in One-way Mode or isolated margined in Hedge Mode,
    /// "LONG", "SHORT", and "BOTH" will be returned to show the positions' adl quantiles of
    /// different position sides.
    /// * If the positions of the symbol are crossed margined in Hedge Mode:
    ///   * "HEDGE" as a sign will be returned instead of "BOTH";
    ///   * A same value caculated on unrealized pnls on long and short sides' positions will be
    ///   shown for "LONG" and "SHORT" when there are positions in both of long and short sides.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#position-adl-quantile-estimation
    [[nodiscard]] common::RestApiResponse<std::vector<PositionAdlQuantileEstimationResponseInner>>
    position_adl_quantile_estimation(const PositionAdlQuantileEstimationParams& params = {}) const {
        return trade_api_.position_adl_quantile_estimation(params);
    }
    /// Asynchronous `position_adl_quantile_estimation()`.
    template <class CompletionToken>
    auto async_position_adl_quantile_estimation(const PositionAdlQuantileEstimationParams& params,
                                                CompletionToken&& token) const {
        return trade_api_.async_position_adl_quantile_estimation(
            params, std::forward<CompletionToken>(token));
    }

    /// Position Information (USER_DATA)
    ///
    /// GET /dapi/v1/positionRisk.
    ///
    /// Get current account information.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If neither `marginAsset` nor `pair` is sent, positions of all symbols with `TRADING`
    /// status will be returned.
    /// - for One-way Mode user, the response will only show the "BOTH" positions
    /// - for Hedge Mode user, the response will show "BOTH", "LONG", and "SHORT" positions.
    /// **Note** > Please use with user data stream `ACCOUNT_UPDATE` to meet your timeliness and
    /// accuracy needs.
    /// - Please use with user data stream ACCOUNT_UPDATE to meet your timeliness and accuracy
    /// needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#position-information
    [[nodiscard]] common::RestApiResponse<std::vector<PositionInformationResponseInner>>
    position_information(const PositionInformationParams& params = {}) const {
        return trade_api_.position_information(params);
    }
    /// Asynchronous `position_information()`.
    template <class CompletionToken>
    auto async_position_information(const PositionInformationParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_position_information(params, std::forward<CompletionToken>(token));
    }

    /// Query Current Open Order (USER_DATA)
    ///
    /// GET /dapi/v1/openOrder.
    ///
    /// Query Current Open Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either`orderId` or `origClientOrderId` must be sent
    /// - If the queried order has been filled or cancelled, the error message "Order does not
    /// exist" will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#query-current-open-order
    [[nodiscard]] common::RestApiResponse<QueryCurrentOpenOrderResponse>
    query_current_open_order(const QueryCurrentOpenOrderParams& params) const {
        return trade_api_.query_current_open_order(params);
    }
    /// Asynchronous `query_current_open_order()`.
    template <class CompletionToken>
    auto async_query_current_open_order(const QueryCurrentOpenOrderParams& params,
                                        CompletionToken&& token) const {
        return trade_api_.async_query_current_open_order(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// User's Force Orders (USER_DATA)
    ///
    /// GET /dapi/v1/forceOrders.
    ///
    /// User's Force Orders
    ///
    /// Weight: **20** (after CM migration: **20** with symbol / **50** without symbol)
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If "autoCloseType" is not sent, orders with both of the types will be returned
    /// - Only support querying data in the past 90 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#users-force-orders
    [[nodiscard]] common::RestApiResponse<std::vector<UsersForceOrdersResponseInner>>
    users_force_orders(const UsersForceOrdersParams& params = {}) const {
        return trade_api_.users_force_orders(params);
    }
    /// Asynchronous `users_force_orders()`.
    template <class CompletionToken>
    auto async_users_force_orders(const UsersForceOrdersParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_users_force_orders(params, std::forward<CompletionToken>(token));
    }

    // UserDataStreamsApi

    /// Close User Data Stream (USER_STREAM)
    ///
    /// DELETE /dapi/v1/listenKey.
    ///
    /// Close out a user data stream.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/user-data-streams#close-user-data-stream
    [[nodiscard]] common::RestApiResponse<boost::json::value> close_user_data_stream() const {
        return user_data_streams_api_.close_user_data_stream();
    }
    /// Asynchronous `close_user_data_stream()`.
    template <class CompletionToken>
    auto async_close_user_data_stream(CompletionToken&& token) const {
        return user_data_streams_api_.async_close_user_data_stream(
            std::forward<CompletionToken>(token));
    }

    /// Keepalive User Data Stream (USER_STREAM)
    ///
    /// PUT /dapi/v1/listenKey.
    ///
    /// Keepalive a user data stream to prevent a time out. User data streams
    /// will close after 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/user-data-streams#keepalive-user-data-stream
    [[nodiscard]] common::RestApiResponse<KeepaliveUserDataStreamResponse>
    keepalive_user_data_stream() const {
        return user_data_streams_api_.keepalive_user_data_stream();
    }
    /// Asynchronous `keepalive_user_data_stream()`.
    template <class CompletionToken>
    auto async_keepalive_user_data_stream(CompletionToken&& token) const {
        return user_data_streams_api_.async_keepalive_user_data_stream(
            std::forward<CompletionToken>(token));
    }

    /// Start User Data Stream (USER_STREAM)
    ///
    /// POST /dapi/v1/listenKey.
    ///
    /// Start a new user data stream. The stream will close after 60 minutes
    /// unless a keepalive is sent. If the account has an active `listenKey`,
    /// that `listenKey` will be returned and its validity will be extended for
    /// 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/user-data-streams#start-user-data-stream
    [[nodiscard]] common::RestApiResponse<StartUserDataStreamResponse>
    start_user_data_stream() const {
        return user_data_streams_api_.start_user_data_stream();
    }
    /// Asynchronous `start_user_data_stream()`.
    template <class CompletionToken>
    auto async_start_user_data_stream(CompletionToken&& token) const {
        return user_data_streams_api_.async_start_user_data_stream(
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
    MarketDataApi market_data_api_;
    TradeApi trade_api_;
    UserDataStreamsApi user_data_streams_api_;
};

} // namespace binance::derivatives_trading_coin_futures::rest_api
