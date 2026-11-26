//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include <boost/asio/append.hpp>
#include <boost/asio/async_result.hpp>

#include <binance/common/config.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/account_api.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/market_data_api.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/trade_api.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/user_data_streams_api.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

class WebsocketApi;

/// A connection to the DerivativesTradingUsdsFutures WebSocket API, returned connected by
/// `WebsocketApi::connect()`. Cheap to copy: copies share one `common::WebsocketApi` (connection
/// pool and executor), which reconnects and renews its connections until `disconnect()`.
///
/// Every method has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT WebsocketApiConnection {
public:
    [[nodiscard]] const common::WebsocketApiConfig& configuration() const noexcept {
        return client_->configuration();
    }

    void disconnect() { client_->disconnect(); }
    template <class CompletionToken> auto async_disconnect(CompletionToken&& token) {
        return client_->async_disconnect(std::forward<CompletionToken>(token));
    }
    [[nodiscard]] bool is_connected() const { return client_->is_connected(); }
    /// Sends a ping frame on every open connection.
    void ping_server() { client_->ping_server(); }
    /// Registers a lifecycle callback (`common::WebsocketEvent`). Destroying the returned
    /// subscription removes it.
    template <class F> common::Subscription on_event(F&& callback) {
        return client_->on_event(std::forward<F>(callback));
    }

    /// Calls a method the SDK does not wrap yet. `T` may be `boost::json::value`.
    template <class T>
    [[nodiscard]] common::WebsocketApiResponse<T> send_message(std::string method,
                                                               common::Params payload = {}) const {
        return common::send<T>(*client_, std::move(method), std::move(payload));
    }

    /// Like `send_message`, but signed (adds `apiKey`, `timestamp` and `signature`).
    template <class T>
    [[nodiscard]] common::WebsocketApiResponse<T>
    send_signed_message(std::string method, common::Params payload = {}) const {
        return common::send<T>(*client_, std::move(method), std::move(payload), signed_options());
    }

    template <class T, class CompletionToken>
    auto async_send_message(std::string method, common::Params payload,
                            CompletionToken&& token) const {
        return common::async_send<T>(client_, std::move(method), std::move(payload), {},
                                     std::forward<CompletionToken>(token));
    }

    template <class T, class CompletionToken>
    auto async_send_signed_message(std::string method, common::Params payload,
                                   CompletionToken&& token) const {
        return common::async_send<T>(client_, std::move(method), std::move(payload),
                                     signed_options(), std::forward<CompletionToken>(token));
    }

    // AccountApi

    /// Account Information (USER_DATA)
    ///
    /// `account.status`.
    ///
    /// Get current account information. User in single-asset/ multi-assets mode will see different
    /// value, see comments in response section for detail.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/account#account-information
    [[nodiscard]] common::WebsocketApiResponse<AccountInformationResponseResult>
    account_information(const AccountInformationParams& params = {}) const {
        return account_api_.account_information(params);
    }
    template <class CompletionToken>
    auto async_account_information(const AccountInformationParams& params,
                                   CompletionToken&& token) const {
        return account_api_.async_account_information(params, std::forward<CompletionToken>(token));
    }

    /// Account Information V2 (USER_DATA)
    ///
    /// `v2/account.status`.
    ///
    /// Get current account information. User in single-asset/ multi-assets mode will see different
    /// value, see comments in response section for detail.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/account#account-information-v2
    [[nodiscard]] common::WebsocketApiResponse<AccountInformationV2ResponseResult>
    account_information_v2(const AccountInformationV2Params& params = {}) const {
        return account_api_.account_information_v2(params);
    }
    template <class CompletionToken>
    auto async_account_information_v2(const AccountInformationV2Params& params,
                                      CompletionToken&& token) const {
        return account_api_.async_account_information_v2(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Futures Account Balance (USER_DATA)
    ///
    /// `account.balance`.
    ///
    /// Futures Account Balance
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/account#futures-account-balance
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<FuturesAccountBalanceResponseResultInner>>
    futures_account_balance(const FuturesAccountBalanceParams& params = {}) const {
        return account_api_.futures_account_balance(params);
    }
    template <class CompletionToken>
    auto async_futures_account_balance(const FuturesAccountBalanceParams& params,
                                       CompletionToken&& token) const {
        return account_api_.async_futures_account_balance(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Futures Account Balance V2 (USER_DATA)
    ///
    /// `v2/account.balance`.
    ///
    /// Futures Account Balance V2
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/account#futures-account-balance-v2
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<FuturesAccountBalanceResponseResultInner>>
    futures_account_balance_v2(const FuturesAccountBalanceV2Params& params = {}) const {
        return account_api_.futures_account_balance_v2(params);
    }
    template <class CompletionToken>
    auto async_futures_account_balance_v2(const FuturesAccountBalanceV2Params& params,
                                          CompletionToken&& token) const {
        return account_api_.async_futures_account_balance_v2(params,
                                                             std::forward<CompletionToken>(token));
    }

    // MarketDataApi

    /// Order Book
    ///
    /// `depth`.
    ///
    /// Get current order book. Note that this request returns limited market
    /// depth.
    ///
    /// If you need to continuously monitor order book updates, please consider
    /// using Websocket Market Streams:
    ///   * `<symbol>@depth<levels>`
    ///   * `<symbol>@depth`
    ///
    /// You can use `depth` request together with `<symbol>@depth` streams to
    /// maintain a local order book.
    ///
    /// **Note:**
    ///
    /// - Retail Price Improvement(RPI) orders are not visible and excluded in
    /// the response message.
    ///
    /// Weight: Adjusted based on the limit:
    ///
    /// | Limit         | Weight |
    /// | ------------- | ------ |
    /// | 5, 10, 20, 50 | 2      |
    /// | 100           | 5      |
    /// | 500           | 10     |
    /// | 1000          | 20     |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/market-data#order-book
    [[nodiscard]] common::WebsocketApiResponse<OrderBookResponseResult>
    order_book(const OrderBookParams& params) const {
        return market_data_api_.order_book(params);
    }
    template <class CompletionToken>
    auto async_order_book(const OrderBookParams& params, CompletionToken&& token) const {
        return market_data_api_.async_order_book(params, std::forward<CompletionToken>(token));
    }

    /// Symbol Order Book Ticker
    ///
    /// `ticker.book`.
    ///
    /// Best price/qty on the order book for a symbol or symbols.
    ///
    /// **Note:**
    ///
    /// - Retail Price Improvement(RPI) orders are not visible and excluded in
    /// the response message.
    ///
    /// Weight: **2** for a single symbol;
    /// **5** when the symbol parameter is omitted
    ///
    /// Notes:
    /// - If the symbol is not sent, bookTickers for all symbols will be
    /// returned in an array.
    ///
    /// - The field `X-MBX-USED-WEIGHT-1M` in response header is not accurate
    /// from this endpoint, please ignore.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/market-data#symbol-order-book-ticker
    [[nodiscard]] common::WebsocketApiResponse<
        std::variant<SymbolOrderBookTickerResponse1Result,
                     std::vector<SymbolOrderBookTickerResponse2ResultInner>, boost::json::value>>
    symbol_order_book_ticker(const SymbolOrderBookTickerParams& params = {}) const {
        return market_data_api_.symbol_order_book_ticker(params);
    }
    template <class CompletionToken>
    auto async_symbol_order_book_ticker(const SymbolOrderBookTickerParams& params,
                                        CompletionToken&& token) const {
        return market_data_api_.async_symbol_order_book_ticker(
            params, std::forward<CompletionToken>(token));
    }

    /// Symbol Price Ticker
    ///
    /// `ticker.price`.
    ///
    /// Latest price for a symbol or symbols.
    ///
    /// Weight: **1** for a single symbol;
    /// **2** when the symbol parameter is omitted
    ///
    /// Notes:
    /// - If the symbol is not sent, prices for all symbols will be returned in an array.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/market-data#symbol-price-ticker
    [[nodiscard]] common::WebsocketApiResponse<
        std::variant<SymbolPriceTickerResponse1Result,
                     std::vector<SymbolPriceTickerResponse2ResultInner>, boost::json::value>>
    symbol_price_ticker(const SymbolPriceTickerParams& params = {}) const {
        return market_data_api_.symbol_price_ticker(params);
    }
    template <class CompletionToken>
    auto async_symbol_price_ticker(const SymbolPriceTickerParams& params,
                                   CompletionToken&& token) const {
        return market_data_api_.async_symbol_price_ticker(params,
                                                          std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// Cancel Algo Order (TRADE)
    ///
    /// `algoOrder.cancel`.
    ///
    /// Cancel an active algo order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `algoId` or `clientAlgoId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#cancel-algo-order
    [[nodiscard]] common::WebsocketApiResponse<CancelAlgoOrderResponseResult>
    cancel_algo_order(const CancelAlgoOrderParams& params = {}) const {
        return trade_api_.cancel_algo_order(params);
    }
    template <class CompletionToken>
    auto async_cancel_algo_order(const CancelAlgoOrderParams& params,
                                 CompletionToken&& token) const {
        return trade_api_.async_cancel_algo_order(params, std::forward<CompletionToken>(token));
    }

    /// Cancel Order (TRADE)
    ///
    /// `order.cancel`.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#cancel-order
    [[nodiscard]] common::WebsocketApiResponse<CancelOrderResponseResult>
    cancel_order(const CancelOrderParams& params) const {
        return trade_api_.cancel_order(params);
    }
    template <class CompletionToken>
    auto async_cancel_order(const CancelOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_cancel_order(params, std::forward<CompletionToken>(token));
    }

    /// Modify Order (TRADE)
    ///
    /// `order.modify`.
    ///
    /// Order modify function, currently only LIMIT order modification is supported, modified orders
    /// will be reordered in the match queue
    ///
    /// Weight: 1 on 10s order rate limit(X-MBX-ORDER-COUNT-10S);
    /// 1 on 1min order rate limit(X-MBX-ORDER-COUNT-1M);
    /// 0 on IP rate limit(x-mbx-used-weight-1m)
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the
    /// `orderId` will prevail if both are sent.
    ///
    /// - Both `quantity` and `price` must be sent. *(After CM migration, the dapi modify order
    /// endpoint follows the same rule.)*
    ///
    /// - When the new `quantity` or `price` doesn't satisfy PRICE_FILTER /
    /// PERCENT_FILTER / LOT_SIZE, amendment will be rejected and the order will
    /// stay as it is.
    ///
    /// - However the order will be cancelled by the amendment in the following
    /// situations:
    ///
    /// - when the order is in partially filled status and the new `quantity` <=
    /// `executedQty`
    ///
    /// - When the order is `GTX` and the new price will cause it to be executed
    /// immediately
    ///
    /// - One order can only be modfied for less than 10000 times
    ///
    /// - `reduceOnly` behavior:
    ///   - `false` or omitted: behave as today — `min_notional` is enforced on the modified order.
    ///   - `true` and the original order's `reduceOnly` attribute is also `true` (consistent): the
    ///   `min_notional` check is skipped on the modified order, matching placement semantics.
    ///   - `true` but the original order's `reduceOnly` attribute is `false` (inconsistent): the
    ///   modify request is rejected with error code `-5047`, "The original order is not a
    ///   reduce-only order".
    ///   - `reduceOnly` is used purely for validation — passing `true` does not change the original
    ///   order's `reduceOnly` attribute; that flag remains whatever it was set to at placement
    ///   time.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#modify-order
    [[nodiscard]] common::WebsocketApiResponse<ModifyOrderResponseResult>
    modify_order(const ModifyOrderParams& params) const {
        return trade_api_.modify_order(params);
    }
    template <class CompletionToken>
    auto async_modify_order(const ModifyOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_modify_order(params, std::forward<CompletionToken>(token));
    }

    /// New Algo Order (TRADE)
    ///
    /// `algoOrder.place`.
    ///
    /// Send in a new algo order.
    ///
    /// Weight(IP): 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Condition orders will be triggered when:
    ///
    /// >
    ///
    /// - If parameter`priceProtect`is sent as true:
    ///
    /// - when price reaches the `triggerPrice` ，the difference rate between
    /// "MARK_PRICE" and "CONTRACT_PRICE" cannot be larger than the
    /// "triggerProtect" of the symbol
    ///
    /// - "triggerProtect" of a symbol can be got from `GET
    /// /fapi/v1/exchangeInfo`
    ///
    /// >
    ///
    /// - `STOP`, `STOP_MARKET`:
    ///
    /// - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `triggerPrice`
    ///
    /// - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <=
    /// `triggerPrice`
    ///
    /// - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`:
    ///
    /// - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `triggerPrice`
    ///
    /// - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >=
    /// `triggerPrice`
    ///
    /// - `TRAILING_STOP_MARKET`:
    ///
    /// - BUY: the lowest price after order placed <= `activatePrice`, and the
    /// latest price >= the lowest price * (1 + `callbackRate`)
    ///
    /// - SELL: the highest price after order placed >= `activatePrice`, and the
    /// latest price <= the highest price * (1 - `callbackRate`)
    ///
    /// >
    ///
    /// - For `TRAILING_STOP_MARKET`, if you got such error code.
    ///
    /// >   ``{"code": -2021, "msg": "Order would immediately trigger."}``
    ///
    /// >   means that the parameters you send do not meet the following
    /// requirements:
    ///
    /// - BUY: `activatePrice` should be smaller than latest price.
    ///
    /// - SELL: `activatePrice` should be larger than latest price.
    ///
    /// >
    ///
    /// - `STOP_MARKET`, `TAKE_PROFIT_MARKET` with `closePosition`=`true`:
    ///
    /// - Follow the same rules for condition orders.
    ///
    /// - If triggered，**close all** current long position( if `SELL`) or
    /// current short position( if `BUY`).
    ///
    /// - Cannot be used with `quantity` paremeter
    ///
    /// - Cannot be used with `reduceOnly` parameter
    ///
    /// - In Hedge Mode,cannot be used with `BUY` orders in `LONG` position
    /// side. and cannot be used with `SELL` orders in `SHORT` position side
    ///
    /// - `selfTradePreventionMode` is only effective when `timeInForce` set to
    /// `IOC` or `GTC` or `GTD`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#new-algo-order
    [[nodiscard]] common::WebsocketApiResponse<NewAlgoOrderResponseResult>
    new_algo_order(const NewAlgoOrderParams& params) const {
        return trade_api_.new_algo_order(params);
    }
    template <class CompletionToken>
    auto async_new_algo_order(const NewAlgoOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_new_algo_order(params, std::forward<CompletionToken>(token));
    }

    /// New Order (TRADE)
    ///
    /// `order.place`.
    ///
    /// Send in a new order.
    ///
    /// Weight(IP): 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// Additional mandatory parameters based on `type`:
    ///
    /// - `LIMIT`: `timeInForce`, `quantity`, `price`
    /// - `MARKET`: `quantity`
    ///
    /// > * If `newOrderRespType` is sent as `RESULT`:
    /// >   * `MARKET` order: the final FILLED result of the order will be return directly.
    /// >   * `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED
    /// or EXPIRED) will be returned directly.
    /// >
    /// > * `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC` or
    /// `GTD`. > * In extreme market conditions, timeInForce `GTD` order auto cancel time might be
    /// delayed comparing to `goodTillDate`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#new-order
    [[nodiscard]] common::WebsocketApiResponse<NewOrderResponseResult>
    new_order(const NewOrderParams& params) const {
        return trade_api_.new_order(params);
    }
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_new_order(params, std::forward<CompletionToken>(token));
    }

    /// Position Information (USER_DATA)
    ///
    /// `account.position`.
    ///
    /// Get current position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please use with user data stream `ACCOUNT_UPDATE` to meet your
    /// timeliness and accuracy needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#position-information
    [[nodiscard]] common::WebsocketApiResponse<std::vector<PositionInformationResponseResultInner>>
    position_information(const PositionInformationParams& params = {}) const {
        return trade_api_.position_information(params);
    }
    template <class CompletionToken>
    auto async_position_information(const PositionInformationParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_position_information(params, std::forward<CompletionToken>(token));
    }

    /// Position Information V2 (USER_DATA)
    ///
    /// `v2/account.position`.
    ///
    /// Get current position information(only symbol that has position or open
    /// orders will be returned).
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please use with user data stream `ACCOUNT_UPDATE` to meet your
    /// timeliness and accuracy needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#position-information-v2
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<PositionInformationV2ResponseResultInner>>
    position_information_v2(const PositionInformationV2Params& params = {}) const {
        return trade_api_.position_information_v2(params);
    }
    template <class CompletionToken>
    auto async_position_information_v2(const PositionInformationV2Params& params,
                                       CompletionToken&& token) const {
        return trade_api_.async_position_information_v2(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Query Order (USER_DATA)
    ///
    /// `order.status`.
    ///
    /// Check an order's status.
    ///
    /// * These orders will not be found:
    ///   * order status is `CANCELED` or `EXPIRED` **AND** order has NO filled trade **AND**
    ///   created time + 3 days < current time
    ///   * order create time + 90 days < current time
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - `orderId` is self-increment for each specific `symbol`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#query-order
    [[nodiscard]] common::WebsocketApiResponse<QueryOrderResponseResult>
    query_order(const QueryOrderParams& params) const {
        return trade_api_.query_order(params);
    }
    template <class CompletionToken>
    auto async_query_order(const QueryOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_query_order(params, std::forward<CompletionToken>(token));
    }

    // UserDataStreamsApi

    /// Close User Data Stream (USER_STREAM)
    ///
    /// `userDataStream.stop`.
    ///
    /// Close out a user data stream.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/user-data-streams#close-user-data-stream
    [[nodiscard]] common::WebsocketApiResponse<boost::json::value>
    close_user_data_stream(const CloseUserDataStreamParams& params = {}) const {
        return user_data_streams_api_.close_user_data_stream(params);
    }
    template <class CompletionToken>
    auto async_close_user_data_stream(const CloseUserDataStreamParams& params,
                                      CompletionToken&& token) const {
        return user_data_streams_api_.async_close_user_data_stream(
            params, std::forward<CompletionToken>(token));
    }

    /// Keepalive User Data Stream (USER_STREAM)
    ///
    /// `userDataStream.ping`.
    ///
    /// Keepalive a user data stream to prevent a time out. User data streams will close after 60
    /// minutes. It's recommended to send a ping about every 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/user-data-streams#keepalive-user-data-stream
    [[nodiscard]] common::WebsocketApiResponse<KeepaliveUserDataStreamResponseResult>
    keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params = {}) const {
        return user_data_streams_api_.keepalive_user_data_stream(params);
    }
    template <class CompletionToken>
    auto async_keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params,
                                          CompletionToken&& token) const {
        return user_data_streams_api_.async_keepalive_user_data_stream(
            params, std::forward<CompletionToken>(token));
    }

    /// Start User Data Stream (USER_STREAM)
    ///
    /// `userDataStream.start`.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/user-data-streams#start-user-data-stream
    [[nodiscard]] common::WebsocketApiResponse<StartUserDataStreamResponseResult>
    start_user_data_stream(const StartUserDataStreamParams& params = {}) const {
        return user_data_streams_api_.start_user_data_stream(params);
    }
    template <class CompletionToken>
    auto async_start_user_data_stream(const StartUserDataStreamParams& params,
                                      CompletionToken&& token) const {
        return user_data_streams_api_.async_start_user_data_stream(
            params, std::forward<CompletionToken>(token));
    }

private:
    friend class WebsocketApi;

    /// Not connected yet: `WebsocketApi::connect()` creates and connects one. Throws
    /// `common::ConfigError` if the configuration is invalid.
    explicit WebsocketApiConnection(common::WebsocketApiConfig configuration);

    [[nodiscard]] const std::shared_ptr<common::WebsocketApi>& client() const noexcept {
        return client_;
    }

    [[nodiscard]] static common::WebsocketMessageSendOptions signed_options() {
        common::WebsocketMessageSendOptions options;
        options.is_signed = true;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
    AccountApi account_api_;
    MarketDataApi market_data_api_;
    TradeApi trade_api_;
    UserDataStreamsApi user_data_streams_api_;
};

/// DerivativesTradingUsdsFutures WebSocket API client: holds the configuration, and `connect()`
/// opens a new connection with it, like the `connect()` of the other Binance connectors. Every call
/// returns an independent connection.
class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT WebsocketApi {
public:
    explicit WebsocketApi(common::WebsocketApiConfig configuration);

    /// A client for `config.url`, production when it is not set.
    [[nodiscard]] static WebsocketApi from_config(common::WebsocketApiConfig config);
    /// A client for production (Derivatives Trading Usds Futures WebSocket API).
    [[nodiscard]] static WebsocketApi production(common::WebsocketApiConfig config);
    /// A client for the testnet.
    [[nodiscard]] static WebsocketApi testnet(common::WebsocketApiConfig config);

    [[nodiscard]] const common::WebsocketApiConfig& configuration() const noexcept {
        return configuration_;
    }

    /// Opens a connection (a pool of them with `mode`, overriding the configuration) and returns
    /// it once connected. Throws `common::ConfigError` if the configuration is invalid, and the
    /// error of the first connection that fails to open.
    [[nodiscard]] WebsocketApiConnection
    connect(std::optional<common::WebsocketMode> mode = {}) const {
        WebsocketApiConnection connection(configuration_for(mode));
        connection.client()->connect();
        return connection;
    }

    /// Asynchronous `connect()`, completing with `void(std::exception_ptr,
    /// WebsocketApiConnection)`.
    template <class CompletionToken> auto async_connect(CompletionToken&& token) const {
        return async_connect(std::nullopt, std::forward<CompletionToken>(token));
    }
    template <class CompletionToken>
    auto async_connect(std::optional<common::WebsocketMode> mode, CompletionToken&& token) const {
        return boost::asio::async_initiate<CompletionToken,
                                           void(std::exception_ptr, WebsocketApiConnection)>(
            [](auto handler, WebsocketApiConnection connection) {
                const auto client = connection.client();
                client->async_connect(
                    boost::asio::append(std::move(handler), std::move(connection)));
            },
            token, WebsocketApiConnection(configuration_for(mode)));
    }

private:
    [[nodiscard]] common::WebsocketApiConfig
    configuration_for(std::optional<common::WebsocketMode> mode) const {
        auto configuration = configuration_;
        if (mode) {
            configuration.mode = *mode;
        }
        return configuration;
    }

    common::WebsocketApiConfig configuration_;
};

} // namespace binance::derivatives_trading_usds_futures::websocket_api
