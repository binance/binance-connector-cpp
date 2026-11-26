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
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/account_api.hpp>
#include <binance/derivatives_trading_options/rest_api/market_data_api.hpp>
#include <binance/derivatives_trading_options/rest_api/market_maker_block_trade_api.hpp>
#include <binance/derivatives_trading_options/rest_api/market_maker_endpoints_api.hpp>
#include <binance/derivatives_trading_options/rest_api/models.hpp>
#include <binance/derivatives_trading_options/rest_api/trade_api.hpp>
#include <binance/derivatives_trading_options/rest_api/user_data_streams_api.hpp>

namespace binance::derivatives_trading_options::rest_api {

/// DerivativesTradingOptions REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Derivatives Trading Options REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);
    /// A client for the testnet.
    [[nodiscard]] static RestApi testnet(common::RestApiConfig config);

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

    /// Account Funding Flow (USER_DATA)
    ///
    /// GET /eapi/v1/bill.
    ///
    /// Query account funding flows.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Only support querying data in the past 3 months
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/account#account-funding-flow
    [[nodiscard]] common::RestApiResponse<std::vector<AccountFundingFlowResponseInner>>
    account_funding_flow(const AccountFundingFlowParams& params) const {
        return account_api_.account_funding_flow(params);
    }
    /// Asynchronous `account_funding_flow()`.
    template <class CompletionToken>
    auto async_account_funding_flow(const AccountFundingFlowParams& params,
                                    CompletionToken&& token) const {
        return account_api_.async_account_funding_flow(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Option Margin Account Information (USER_DATA)
    ///
    /// GET /eapi/v1/marginAccount.
    ///
    /// Get current account information.
    ///
    /// Weight(IP): 3
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/account#option-margin-account-information
    [[nodiscard]] common::RestApiResponse<OptionMarginAccountInformationResponse>
    option_margin_account_information(
        const OptionMarginAccountInformationParams& params = {}) const {
        return account_api_.option_margin_account_information(params);
    }
    /// Asynchronous `option_margin_account_information()`.
    template <class CompletionToken>
    auto async_option_margin_account_information(const OptionMarginAccountInformationParams& params,
                                                 CompletionToken&& token) const {
        return account_api_.async_option_margin_account_information(
            params, std::forward<CompletionToken>(token));
    }

    // MarketDataApi

    /// Check Server Time
    ///
    /// GET /eapi/v1/time.
    ///
    /// Test connectivity to the Rest API and get the current server time.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#check-server-time
    [[nodiscard]] common::RestApiResponse<CheckServerTimeResponse> check_server_time() const {
        return market_data_api_.check_server_time();
    }
    /// Asynchronous `check_server_time()`.
    template <class CompletionToken> auto async_check_server_time(CompletionToken&& token) const {
        return market_data_api_.async_check_server_time(std::forward<CompletionToken>(token));
    }

    /// Exchange Information
    ///
    /// GET /eapi/v1/exchangeInfo.
    ///
    /// Current exchange trading rules and symbol information
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#exchange-information
    [[nodiscard]] common::RestApiResponse<ExchangeInformationResponse>
    exchange_information() const {
        return market_data_api_.exchange_information();
    }
    /// Asynchronous `exchange_information()`.
    template <class CompletionToken>
    auto async_exchange_information(CompletionToken&& token) const {
        return market_data_api_.async_exchange_information(std::forward<CompletionToken>(token));
    }

    /// Historical Exercise Records
    ///
    /// GET /eapi/v1/exerciseHistory.
    ///
    /// Get historical exercise records.
    ///
    /// * REALISTIC_VALUE_STRICKEN -> Exercised
    /// * EXTRINSIC_VALUE_EXPIRED -> Expired OTM
    ///
    /// Weight(IP): 3
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#historical-exercise-records
    [[nodiscard]] common::RestApiResponse<std::vector<HistoricalExerciseRecordsResponseInner>>
    historical_exercise_records(const HistoricalExerciseRecordsParams& params = {}) const {
        return market_data_api_.historical_exercise_records(params);
    }
    /// Asynchronous `historical_exercise_records()`.
    template <class CompletionToken>
    auto async_historical_exercise_records(const HistoricalExerciseRecordsParams& params,
                                           CompletionToken&& token) const {
        return market_data_api_.async_historical_exercise_records(
            params, std::forward<CompletionToken>(token));
    }

    /// Index Price
    ///
    /// GET /eapi/v1/index.
    ///
    /// Get spot index price for option underlying.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#index-price
    [[nodiscard]] common::RestApiResponse<IndexPriceResponse>
    index_price(const IndexPriceParams& params) const {
        return market_data_api_.index_price(params);
    }
    /// Asynchronous `index_price()`.
    template <class CompletionToken>
    auto async_index_price(const IndexPriceParams& params, CompletionToken&& token) const {
        return market_data_api_.async_index_price(params, std::forward<CompletionToken>(token));
    }

    /// Kline/Candlestick Data
    ///
    /// GET /eapi/v1/klines.
    ///
    /// Kline/candlestick bars for an option symbol. Klines are uniquely identified by their open
    /// time.
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent klines are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<std::vector<std::vector<KlineCandlestickDataItemInner>>>
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

    /// Open Interest
    ///
    /// GET /eapi/v1/openInterest.
    ///
    /// Get open interest for specific underlying asset on specific expiration date.
    ///
    /// Weight(IP): 0
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#open-interest
    [[nodiscard]] common::RestApiResponse<std::vector<OpenInterestResponseInner>>
    open_interest(const OpenInterestParams& params) const {
        return market_data_api_.open_interest(params);
    }
    /// Asynchronous `open_interest()`.
    template <class CompletionToken>
    auto async_open_interest(const OpenInterestParams& params, CompletionToken&& token) const {
        return market_data_api_.async_open_interest(params, std::forward<CompletionToken>(token));
    }

    /// Option Mark Price
    ///
    /// GET /eapi/v1/mark.
    ///
    /// Option mark price and greek info.
    ///
    /// Weight(IP): 5
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#option-mark-price
    [[nodiscard]] common::RestApiResponse<std::vector<OptionMarkPriceResponseInner>>
    option_mark_price(const OptionMarkPriceParams& params = {}) const {
        return market_data_api_.option_mark_price(params);
    }
    /// Asynchronous `option_mark_price()`.
    template <class CompletionToken>
    auto async_option_mark_price(const OptionMarkPriceParams& params,
                                 CompletionToken&& token) const {
        return market_data_api_.async_option_mark_price(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Order Book
    ///
    /// GET /eapi/v1/depth.
    ///
    /// Check orderbook depth on specific symbol
    ///
    /// Weight: limit         | weight
    /// ------------  | ------------
    /// 5, 10, 20, 50 | 1
    /// 100           | 5
    /// 500           | 10
    /// 1000          | 20
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#order-book
    [[nodiscard]] common::RestApiResponse<OrderBookResponse>
    order_book(const OrderBookParams& params) const {
        return market_data_api_.order_book(params);
    }
    /// Asynchronous `order_book()`.
    template <class CompletionToken>
    auto async_order_book(const OrderBookParams& params, CompletionToken&& token) const {
        return market_data_api_.async_order_book(params, std::forward<CompletionToken>(token));
    }

    /// Recent Block Trades List
    ///
    /// GET /eapi/v1/blockTrades.
    ///
    /// Get recent block trades
    ///
    /// Weight(IP): 5
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#recent-block-trades-list
    [[nodiscard]] common::RestApiResponse<std::vector<RecentBlockTradesListResponseInner>>
    recent_block_trades_list(const RecentBlockTradesListParams& params = {}) const {
        return market_data_api_.recent_block_trades_list(params);
    }
    /// Asynchronous `recent_block_trades_list()`.
    template <class CompletionToken>
    auto async_recent_block_trades_list(const RecentBlockTradesListParams& params,
                                        CompletionToken&& token) const {
        return market_data_api_.async_recent_block_trades_list(
            params, std::forward<CompletionToken>(token));
    }

    /// Recent Trades List
    ///
    /// GET /eapi/v1/trades.
    ///
    /// Get recent market trades
    ///
    /// Weight(IP): 5
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#recent-trades-list
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

    /// Test Connectivity
    ///
    /// GET /eapi/v1/ping.
    ///
    /// Test connectivity to the Rest API.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#test-connectivity
    [[nodiscard]] common::RestApiResponse<boost::json::value> test_connectivity() const {
        return market_data_api_.test_connectivity();
    }
    /// Asynchronous `test_connectivity()`.
    template <class CompletionToken> auto async_test_connectivity(CompletionToken&& token) const {
        return market_data_api_.async_test_connectivity(std::forward<CompletionToken>(token));
    }

    /// 24hr Ticker Price Change Statistics
    ///
    /// GET /eapi/v1/ticker.
    ///
    /// 24 hour rolling window price change statistics.
    ///
    /// Weight: 1 for a single symbol; 40 when the symbol parameter is omitted
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#ticker24hr-price-change-statistics
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

    // MarketMakerBlockTradeApi

    /// Accept Block Trade Order (TRADE)
    ///
    /// POST /eapi/v1/block/order/execute.
    ///
    /// Accept a block trade order
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#accept-block-trade-order
    [[nodiscard]] common::RestApiResponse<AcceptBlockTradeOrderResponse>
    accept_block_trade_order(const AcceptBlockTradeOrderParams& params) const {
        return market_maker_block_trade_api_.accept_block_trade_order(params);
    }
    /// Asynchronous `accept_block_trade_order()`.
    template <class CompletionToken>
    auto async_accept_block_trade_order(const AcceptBlockTradeOrderParams& params,
                                        CompletionToken&& token) const {
        return market_maker_block_trade_api_.async_accept_block_trade_order(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Block Trade Details (USER_DATA)
    ///
    /// GET /eapi/v1/block/order/execute.
    ///
    /// Query block trade details; returns block trade details from counterparty's perspective.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#query-block-trade-details
    [[nodiscard]] common::RestApiResponse<QueryBlockTradeDetailsResponse>
    query_block_trade_details(const QueryBlockTradeDetailsParams& params) const {
        return market_maker_block_trade_api_.query_block_trade_details(params);
    }
    /// Asynchronous `query_block_trade_details()`.
    template <class CompletionToken>
    auto async_query_block_trade_details(const QueryBlockTradeDetailsParams& params,
                                         CompletionToken&& token) const {
        return market_maker_block_trade_api_.async_query_block_trade_details(
            params, std::forward<CompletionToken>(token));
    }

    /// Account Block Trade List (USER_DATA)
    ///
    /// GET /eapi/v1/block/user-trades.
    ///
    /// Gets block trades for a specific account.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#account-block-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<AccountBlockTradeListResponseInner>>
    account_block_trade_list(const AccountBlockTradeListParams& params = {}) const {
        return market_maker_block_trade_api_.account_block_trade_list(params);
    }
    /// Asynchronous `account_block_trade_list()`.
    template <class CompletionToken>
    auto async_account_block_trade_list(const AccountBlockTradeListParams& params,
                                        CompletionToken&& token) const {
        return market_maker_block_trade_api_.async_account_block_trade_list(
            params, std::forward<CompletionToken>(token));
    }

    /// Cancel Block Trade Order (TRADE)
    ///
    /// DELETE /eapi/v1/block/order/create.
    ///
    /// Cancel a block trade order.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#cancel-block-trade-order
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    cancel_block_trade_order(const CancelBlockTradeOrderParams& params) const {
        return market_maker_block_trade_api_.cancel_block_trade_order(params);
    }
    /// Asynchronous `cancel_block_trade_order()`.
    template <class CompletionToken>
    auto async_cancel_block_trade_order(const CancelBlockTradeOrderParams& params,
                                        CompletionToken&& token) const {
        return market_maker_block_trade_api_.async_cancel_block_trade_order(
            params, std::forward<CompletionToken>(token));
    }

    /// Extend Block Trade Order (TRADE)
    ///
    /// PUT /eapi/v1/block/order/create.
    ///
    /// Extends a block trade expire time by 30 mins from the current time.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#extend-block-trade-order
    [[nodiscard]] common::RestApiResponse<ExtendBlockTradeOrderResponse>
    extend_block_trade_order(const ExtendBlockTradeOrderParams& params) const {
        return market_maker_block_trade_api_.extend_block_trade_order(params);
    }
    /// Asynchronous `extend_block_trade_order()`.
    template <class CompletionToken>
    auto async_extend_block_trade_order(const ExtendBlockTradeOrderParams& params,
                                        CompletionToken&& token) const {
        return market_maker_block_trade_api_.async_extend_block_trade_order(
            params, std::forward<CompletionToken>(token));
    }

    /// New Block Trade Order (TRADE)
    ///
    /// POST /eapi/v1/block/order/create.
    ///
    /// Send in a new block trade order.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#new-block-trade-order
    [[nodiscard]] common::RestApiResponse<NewBlockTradeOrderResponse>
    new_block_trade_order(const NewBlockTradeOrderParams& params) const {
        return market_maker_block_trade_api_.new_block_trade_order(params);
    }
    /// Asynchronous `new_block_trade_order()`.
    template <class CompletionToken>
    auto async_new_block_trade_order(const NewBlockTradeOrderParams& params,
                                     CompletionToken&& token) const {
        return market_maker_block_trade_api_.async_new_block_trade_order(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Block Trade Order (TRADE)
    ///
    /// GET /eapi/v1/block/order/orders.
    ///
    /// Check block trade order status.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#query-block-trade-order
    [[nodiscard]] common::RestApiResponse<std::vector<QueryBlockTradeOrderResponseInner>>
    query_block_trade_order(const QueryBlockTradeOrderParams& params = {}) const {
        return market_maker_block_trade_api_.query_block_trade_order(params);
    }
    /// Asynchronous `query_block_trade_order()`.
    template <class CompletionToken>
    auto async_query_block_trade_order(const QueryBlockTradeOrderParams& params,
                                       CompletionToken&& token) const {
        return market_maker_block_trade_api_.async_query_block_trade_order(
            params, std::forward<CompletionToken>(token));
    }

    // MarketMakerEndpointsApi

    /// Auto-Cancel All Open Orders (Kill-Switch) Heartbeat (TRADE)
    ///
    /// POST /eapi/v1/countdownCancelAllHeartBeat.
    ///
    /// This endpoint resets the time from which the countdown will begin to the time this messaged
    /// is received.  It should be called repeatedly as heartbeats.  Multiple heartbeats can be
    /// updated at once by specifying the underlying symbols as a list (ex. BTCUSDT,ETHUSDT) in the
    /// underlyings parameter.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - The response will only include underlying symbols where the heartbeat has been
    /// successfully updated.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#auto-cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<AutoCancelAllOpenOrdersResponse>
    auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params) const {
        return market_maker_endpoints_api_.auto_cancel_all_open_orders(params);
    }
    /// Asynchronous `auto_cancel_all_open_orders()`.
    template <class CompletionToken>
    auto async_auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params,
                                           CompletionToken&& token) const {
        return market_maker_endpoints_api_.async_auto_cancel_all_open_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Auto-Cancel All Open Orders (Kill-Switch) Config (TRADE)
    ///
    /// GET /eapi/v1/countdownCancelAll.
    ///
    /// This endpoint returns the auto-cancel parameters for each underlying symbol. Note only
    /// active auto-cancel parameters will be returned, if countdownTime is set to 0 (ie.
    /// countdownTime has been turned off), the underlying symbol and corresponding countdownTime
    /// parameter will not be returned in the response.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - countdownTime = 0 means the function is disabled.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#get-auto-cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<GetAutoCancelAllOpenOrdersResponse>
    get_auto_cancel_all_open_orders(const GetAutoCancelAllOpenOrdersParams& params = {}) const {
        return market_maker_endpoints_api_.get_auto_cancel_all_open_orders(params);
    }
    /// Asynchronous `get_auto_cancel_all_open_orders()`.
    template <class CompletionToken>
    auto async_get_auto_cancel_all_open_orders(const GetAutoCancelAllOpenOrdersParams& params,
                                               CompletionToken&& token) const {
        return market_maker_endpoints_api_.async_get_auto_cancel_all_open_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Set Auto-Cancel All Open Orders (Kill-Switch) Config (TRADE)
    ///
    /// POST /eapi/v1/countdownCancelAll.
    ///
    /// This endpoint sets the parameters of the auto-cancel feature which cancels all open orders
    /// (both market maker protection and non market maker protection order types) of the underlying
    /// symbol at the end of the specified countdown time period if no heartbeat message is sent.
    /// After the countdown time period, all open orders will be cancelled. The auto-cancel feature
    /// can be turned off by setting countdownTime to 0.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - This rest endpoint sets up the parameters to cancel your open orders in case of an outage
    /// or disconnection.
    /// - Example usage: > Call this endpoint with a countdownTime value of 10000 (10 seconds) to
    /// turn on the auto-cancel feature. If the corresponding countdownCancelAllHeartBeat endpoint
    /// is not called within 10 seconds with the specified underlying symbol, all open orders of the
    /// specified symbol will be automatically canceled. If this endpoint is called with an
    /// countdownTime of 0, the countdown timer will be stopped.
    /// - The system will check all countdowns approximately every 100 milliseconds, **please note
    /// that sufficient redundancy should be considered when using this function**. We do not
    /// recommend setting the countdown time to be too precise or too small.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#set-auto-cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<SetAutoCancelAllOpenOrdersResponse>
    set_auto_cancel_all_open_orders(const SetAutoCancelAllOpenOrdersParams& params) const {
        return market_maker_endpoints_api_.set_auto_cancel_all_open_orders(params);
    }
    /// Asynchronous `set_auto_cancel_all_open_orders()`.
    template <class CompletionToken>
    auto async_set_auto_cancel_all_open_orders(const SetAutoCancelAllOpenOrdersParams& params,
                                               CompletionToken&& token) const {
        return market_maker_endpoints_api_.async_set_auto_cancel_all_open_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Market Maker Protection Config (TRADE)
    ///
    /// GET /eapi/v1/mmp.
    ///
    /// Get config for MMP.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#get-market-maker-protection-config
    [[nodiscard]] common::RestApiResponse<GetMarketMakerProtectionConfigResponse>
    get_market_maker_protection_config(const GetMarketMakerProtectionConfigParams& params) const {
        return market_maker_endpoints_api_.get_market_maker_protection_config(params);
    }
    /// Asynchronous `get_market_maker_protection_config()`.
    template <class CompletionToken>
    auto
    async_get_market_maker_protection_config(const GetMarketMakerProtectionConfigParams& params,
                                             CompletionToken&& token) const {
        return market_maker_endpoints_api_.async_get_market_maker_protection_config(
            params, std::forward<CompletionToken>(token));
    }

    /// Reset Market Maker Protection Config (TRADE)
    ///
    /// POST /eapi/v1/mmpReset.
    ///
    /// Reset MMP, start MMP order again.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#reset-market-maker-protection-config
    [[nodiscard]] common::RestApiResponse<ResetMarketMakerProtectionConfigResponse>
    reset_market_maker_protection_config(
        const ResetMarketMakerProtectionConfigParams& params) const {
        return market_maker_endpoints_api_.reset_market_maker_protection_config(params);
    }
    /// Asynchronous `reset_market_maker_protection_config()`.
    template <class CompletionToken>
    auto
    async_reset_market_maker_protection_config(const ResetMarketMakerProtectionConfigParams& params,
                                               CompletionToken&& token) const {
        return market_maker_endpoints_api_.async_reset_market_maker_protection_config(
            params, std::forward<CompletionToken>(token));
    }

    /// Set Market Maker Protection Config (TRADE)
    ///
    /// POST /eapi/v1/mmpSet.
    ///
    /// Set config for MMP. Market Maker Protection(MMP) is a set of protection mechanism for option
    /// market maker, this mechanism is able to prevent mass trading in short period time. Once
    /// market maker's account branches the threshold, the Market Maker Protection will be
    /// triggered. When Market Maker Protection triggers, all the current MMP orders will be
    /// canceled, new MMP orders will be rejected. Market maker can use this time to reevaluate
    /// market and modify order price.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#set-market-maker-protection-config
    [[nodiscard]] common::RestApiResponse<SetMarketMakerProtectionConfigResponse>
    set_market_maker_protection_config(const SetMarketMakerProtectionConfigParams& params) const {
        return market_maker_endpoints_api_.set_market_maker_protection_config(params);
    }
    /// Asynchronous `set_market_maker_protection_config()`.
    template <class CompletionToken>
    auto
    async_set_market_maker_protection_config(const SetMarketMakerProtectionConfigParams& params,
                                             CompletionToken&& token) const {
        return market_maker_endpoints_api_.async_set_market_maker_protection_config(
            params, std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// Account Trade List (USER_DATA)
    ///
    /// GET /eapi/v1/userTrades.
    ///
    /// Get trades for a specific account and symbol. Only supports querying trades in the past 3
    /// months; a `startTime`/`endTime` outside that window returns `-6073
    /// SEARCH_WINDOW_RESTRICTED`.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<AccountTradeListResponseInner>>
    account_trade_list(const AccountTradeListParams& params) const {
        return trade_api_.account_trade_list(params);
    }
    /// Asynchronous `account_trade_list()`.
    template <class CompletionToken>
    auto async_account_trade_list(const AccountTradeListParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_account_trade_list(params, std::forward<CompletionToken>(token));
    }

    /// Cancel All Option Orders By Underlying (TRADE)
    ///
    /// DELETE /eapi/v1/allOpenOrdersByUnderlying.
    ///
    /// Cancel all active orders on specified underlying.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#cancel-all-option-orders-by-underlying
    [[nodiscard]] common::RestApiResponse<CancelAllOptionOrdersByUnderlyingResponse>
    cancel_all_option_orders_by_underlying(
        const CancelAllOptionOrdersByUnderlyingParams& params) const {
        return trade_api_.cancel_all_option_orders_by_underlying(params);
    }
    /// Asynchronous `cancel_all_option_orders_by_underlying()`.
    template <class CompletionToken>
    auto async_cancel_all_option_orders_by_underlying(
        const CancelAllOptionOrdersByUnderlyingParams& params, CompletionToken&& token) const {
        return trade_api_.async_cancel_all_option_orders_by_underlying(
            params, std::forward<CompletionToken>(token));
    }

    /// Cancel all Option orders on specific symbol (TRADE)
    ///
    /// DELETE /eapi/v1/allOpenOrders.
    ///
    /// Cancel all active order on a symbol.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#cancel-all-option-orders-on-specific-symbol
    [[nodiscard]] common::RestApiResponse<CancelAllOptionOrdersOnSpecificSymbolResponse>
    cancel_all_option_orders_on_specific_symbol(
        const CancelAllOptionOrdersOnSpecificSymbolParams& params) const {
        return trade_api_.cancel_all_option_orders_on_specific_symbol(params);
    }
    /// Asynchronous `cancel_all_option_orders_on_specific_symbol()`.
    template <class CompletionToken>
    auto async_cancel_all_option_orders_on_specific_symbol(
        const CancelAllOptionOrdersOnSpecificSymbolParams& params, CompletionToken&& token) const {
        return trade_api_.async_cancel_all_option_orders_on_specific_symbol(
            params, std::forward<CompletionToken>(token));
    }

    /// Cancel Multiple Option Orders (TRADE)
    ///
    /// DELETE /eapi/v1/batchOrders.
    ///
    /// Cancel multiple orders.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - At least one instance of `orderId` and `clientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#cancel-multiple-option-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CancelMultipleOptionOrdersResponseInner>>
    cancel_multiple_option_orders(const CancelMultipleOptionOrdersParams& params) const {
        return trade_api_.cancel_multiple_option_orders(params);
    }
    /// Asynchronous `cancel_multiple_option_orders()`.
    template <class CompletionToken>
    auto async_cancel_multiple_option_orders(const CancelMultipleOptionOrdersParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_cancel_multiple_option_orders(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Place Multiple Orders (TRADE)
    ///
    /// POST /eapi/v1/batchOrders.
    ///
    /// Send multiple option orders.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// Some parameters are mandatory depending on the order type as follows:
    ///
    /// Type | Mandatory parameters
    /// ------------ | ------------
    /// LIMIT | timeInForce, quantity, price
    ///
    /// - Parameter rules are same with New Order
    /// - Batch orders are processed concurrently, and the order of matching is not guaranteed.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#place-multiple-orders
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

    /// Cancel Option Order (TRADE)
    ///
    /// DELETE /eapi/v1/order.
    ///
    /// Cancel an active order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - At least one instance of `orderId` and `clientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#cancel-option-order
    [[nodiscard]] common::RestApiResponse<CancelOptionOrderResponse>
    cancel_option_order(const CancelOptionOrderParams& params) const {
        return trade_api_.cancel_option_order(params);
    }
    /// Asynchronous `cancel_option_order()`.
    template <class CompletionToken>
    auto async_cancel_option_order(const CancelOptionOrderParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_cancel_option_order(params, std::forward<CompletionToken>(token));
    }

    /// New Order (TRADE)
    ///
    /// POST /eapi/v1/order.
    ///
    /// Send a new order.
    ///
    /// Weight(IP): 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// Some parameters are mandatory depending on the order type as follows:
    ///
    /// Type | Mandatory parameters
    /// ------------ | ------------
    /// LIMIT | timeInForce, quantity, price
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#new-order
    [[nodiscard]] common::RestApiResponse<NewOrderResponse>
    new_order(const NewOrderParams& params) const {
        return trade_api_.new_order(params);
    }
    /// Asynchronous `new_order()`.
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_new_order(params, std::forward<CompletionToken>(token));
    }

    /// Query Single Order (TRADE)
    ///
    /// GET /eapi/v1/order.
    ///
    /// Check an order status.
    ///
    /// * These orders will not be found:
    ///   * order status is `CANCELED` or `REJECTED`, **AND**
    ///   * order has NO filled trade, **AND**
    ///   * created time + 3 days < current time
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `clientOrderId ` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#query-single-order
    [[nodiscard]] common::RestApiResponse<QuerySingleOrderResponse>
    query_single_order(const QuerySingleOrderParams& params) const {
        return trade_api_.query_single_order(params);
    }
    /// Asynchronous `query_single_order()`.
    template <class CompletionToken>
    auto async_query_single_order(const QuerySingleOrderParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_query_single_order(params, std::forward<CompletionToken>(token));
    }

    /// Option Position Information (USER_DATA)
    ///
    /// GET /eapi/v1/position.
    ///
    /// Get current position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#option-position-information
    [[nodiscard]] common::RestApiResponse<std::vector<OptionPositionInformationResponseInner>>
    option_position_information(const OptionPositionInformationParams& params = {}) const {
        return trade_api_.option_position_information(params);
    }
    /// Asynchronous `option_position_information()`.
    template <class CompletionToken>
    auto async_option_position_information(const OptionPositionInformationParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_option_position_information(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Query Current Open Option Orders (USER_DATA)
    ///
    /// GET /eapi/v1/openOrders.
    ///
    /// Query current all open orders, status: ACCEPTED PARTIALLY_FILLED
    ///
    /// Weight: 1 for a single symbol; 40 when the symbol parameter is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#query-current-open-option-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryCurrentOpenOptionOrdersResponseInner>>
    query_current_open_option_orders(const QueryCurrentOpenOptionOrdersParams& params = {}) const {
        return trade_api_.query_current_open_option_orders(params);
    }
    /// Asynchronous `query_current_open_option_orders()`.
    template <class CompletionToken>
    auto async_query_current_open_option_orders(const QueryCurrentOpenOptionOrdersParams& params,
                                                CompletionToken&& token) const {
        return trade_api_.async_query_current_open_option_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Option Order History (TRADE)
    ///
    /// GET /eapi/v1/historyOrders.
    ///
    /// Query all finished orders within 5 days, finished status: CANCELLED FILLED REJECTED.
    ///
    /// Weight(IP): 3
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#query-option-order-history
    [[nodiscard]] common::RestApiResponse<std::vector<QueryOptionOrderHistoryResponseInner>>
    query_option_order_history(const QueryOptionOrderHistoryParams& params) const {
        return trade_api_.query_option_order_history(params);
    }
    /// Asynchronous `query_option_order_history()`.
    template <class CompletionToken>
    auto async_query_option_order_history(const QueryOptionOrderHistoryParams& params,
                                          CompletionToken&& token) const {
        return trade_api_.async_query_option_order_history(params,
                                                           std::forward<CompletionToken>(token));
    }

    /// TradFi Options Contract (USER_DATA)
    ///
    /// POST /eapi/v1/stock/contract.
    ///
    /// Sign TradFi Options agreement contract
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#tradfi-options-contract
    [[nodiscard]] common::RestApiResponse<TradfiOptionsContractResponse>
    tradfi_options_contract(const TradfiOptionsContractParams& params = {}) const {
        return trade_api_.tradfi_options_contract(params);
    }
    /// Asynchronous `tradfi_options_contract()`.
    template <class CompletionToken>
    auto async_tradfi_options_contract(const TradfiOptionsContractParams& params,
                                       CompletionToken&& token) const {
        return trade_api_.async_tradfi_options_contract(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// User Commission (USER_DATA)
    ///
    /// GET /eapi/v1/commission.
    ///
    /// Get account commission.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#user-commission
    [[nodiscard]] common::RestApiResponse<UserCommissionResponse>
    user_commission(const UserCommissionParams& params = {}) const {
        return trade_api_.user_commission(params);
    }
    /// Asynchronous `user_commission()`.
    template <class CompletionToken>
    auto async_user_commission(const UserCommissionParams& params, CompletionToken&& token) const {
        return trade_api_.async_user_commission(params, std::forward<CompletionToken>(token));
    }

    /// User Exercise Record (USER_DATA)
    ///
    /// GET /eapi/v1/exerciseRecord.
    ///
    /// Get account exercise records.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#user-exercise-record
    [[nodiscard]] common::RestApiResponse<std::vector<UserExerciseRecordResponseInner>>
    user_exercise_record(const UserExerciseRecordParams& params = {}) const {
        return trade_api_.user_exercise_record(params);
    }
    /// Asynchronous `user_exercise_record()`.
    template <class CompletionToken>
    auto async_user_exercise_record(const UserExerciseRecordParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_user_exercise_record(params, std::forward<CompletionToken>(token));
    }

    // UserDataStreamsApi

    /// Close User Data Stream (USER_STREAM)
    ///
    /// DELETE /eapi/v1/listenKey.
    ///
    /// Close out a user data stream.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/user-data-streams#close-user-data-stream
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
    /// PUT /eapi/v1/listenKey.
    ///
    /// Keepalive a user data stream to prevent a time out. User data streams
    /// will close after 60 minutes. It's recommended to send a ping about every
    /// 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/user-data-streams#keepalive-user-data-stream
    [[nodiscard]] common::RestApiResponse<boost::json::value> keepalive_user_data_stream() const {
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
    /// POST /eapi/v1/listenKey.
    ///
    /// Start a new user data stream. The stream will close after 60 minutes unless a keepalive is
    /// sent. If the account has an active `listenKey`, that `listenKey` will be returned and its
    /// validity will be extended for 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/user-data-streams#start-user-data-stream
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
    MarketMakerBlockTradeApi market_maker_block_trade_api_;
    MarketMakerEndpointsApi market_maker_endpoints_api_;
    TradeApi trade_api_;
    UserDataStreamsApi user_data_streams_api_;
};

} // namespace binance::derivatives_trading_options::rest_api
