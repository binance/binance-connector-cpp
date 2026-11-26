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
#include <utility>
#include <variant>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/order_book_response_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_order_book_ticker_response1_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_order_book_ticker_response2_result_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_price_ticker_response1_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_price_ticker_response2_result_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct OrderBookParams {
    /// Symbol.
    common::Required<std::string> symbol;
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Valid limits:[5, 10, 20, 50, 100, 500, 1000]
    std::optional<std::int64_t> limit = std::nullopt;
};

struct SymbolOrderBookTickerParams {
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Symbol.
    std::optional<std::string> symbol = std::nullopt;
};

struct SymbolPriceTickerParams {
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Symbol.
    std::optional<std::string> symbol = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::WebsocketApi> client);

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
    order_book(const OrderBookParams& params) const;

    /// Asynchronous `order_book()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderBookResponseResult>)`.
    template <class CompletionToken>
    auto async_order_book(const OrderBookParams& params, CompletionToken&& token) const {
        return common::async_send<OrderBookResponseResult>(
            client_, "depth", order_book_payload(params), make_options(false, false, false, false),
            std::forward<CompletionToken>(token));
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
    symbol_order_book_ticker(const SymbolOrderBookTickerParams& params = {}) const;

    /// Asynchronous `symbol_order_book_ticker()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::variant<SymbolOrderBookTickerResponse1Result,
    /// std::vector<SymbolOrderBookTickerResponse2ResultInner>, boost::json::value>>)`.
    template <class CompletionToken>
    auto async_symbol_order_book_ticker(const SymbolOrderBookTickerParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::variant<
            SymbolOrderBookTickerResponse1Result,
            std::vector<SymbolOrderBookTickerResponse2ResultInner>, boost::json::value>>(
            client_, "ticker.book", symbol_order_book_ticker_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
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
    symbol_price_ticker(const SymbolPriceTickerParams& params = {}) const;

    /// Asynchronous `symbol_price_ticker()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::variant<SymbolPriceTickerResponse1Result,
    /// std::vector<SymbolPriceTickerResponse2ResultInner>, boost::json::value>>)`.
    template <class CompletionToken>
    auto async_symbol_price_ticker(const SymbolPriceTickerParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<
            std::variant<SymbolPriceTickerResponse1Result,
                         std::vector<SymbolPriceTickerResponse2ResultInner>, boost::json::value>>(
            client_, "ticker.price", symbol_price_ticker_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params order_book_payload(const OrderBookParams& params);
    [[nodiscard]] static common::Params
    symbol_order_book_ticker_payload(const SymbolOrderBookTickerParams& params);
    [[nodiscard]] static common::Params
    symbol_price_ticker_payload(const SymbolPriceTickerParams& params);
    [[nodiscard]] static common::WebsocketMessageSendOptions
    make_options(bool with_api_key, bool is_signed, bool is_session_logon, bool is_session_logout) {
        common::WebsocketMessageSendOptions options;
        options.with_api_key = with_api_key;
        options.is_signed = is_signed;
        options.is_session_logon = is_session_logon;
        options.is_session_logout = is_session_logout;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
};

} // namespace binance::derivatives_trading_usds_futures::websocket_api
