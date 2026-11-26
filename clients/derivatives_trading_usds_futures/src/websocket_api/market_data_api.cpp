//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/market_data_api.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

MarketDataApi::MarketDataApi(std::shared_ptr<common::WebsocketApi> client)
    : client_(std::move(client)) {}

common::Params MarketDataApi::order_book_payload(const OrderBookParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "limit", params.limit);
    return p;
}

common::WebsocketApiResponse<OrderBookResponseResult>
MarketDataApi::order_book(const OrderBookParams& params) const {
    return common::send<OrderBookResponseResult>(*client_, "depth", order_book_payload(params),
                                                 make_options(false, false, false, false));
}

common::Params
MarketDataApi::symbol_order_book_ticker_payload(const SymbolOrderBookTickerParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "symbol", params.symbol);
    return p;
}

common::WebsocketApiResponse<
    std::variant<SymbolOrderBookTickerResponse1Result,
                 std::vector<SymbolOrderBookTickerResponse2ResultInner>, boost::json::value>>
MarketDataApi::symbol_order_book_ticker(const SymbolOrderBookTickerParams& params) const {
    return common::send<
        std::variant<SymbolOrderBookTickerResponse1Result,
                     std::vector<SymbolOrderBookTickerResponse2ResultInner>, boost::json::value>>(
        *client_, "ticker.book", symbol_order_book_ticker_payload(params),
        make_options(false, false, false, false));
}

common::Params MarketDataApi::symbol_price_ticker_payload(const SymbolPriceTickerParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "symbol", params.symbol);
    return p;
}

common::WebsocketApiResponse<
    std::variant<SymbolPriceTickerResponse1Result,
                 std::vector<SymbolPriceTickerResponse2ResultInner>, boost::json::value>>
MarketDataApi::symbol_price_ticker(const SymbolPriceTickerParams& params) const {
    return common::send<
        std::variant<SymbolPriceTickerResponse1Result,
                     std::vector<SymbolPriceTickerResponse2ResultInner>, boost::json::value>>(
        *client_, "ticker.price", symbol_price_ticker_payload(params),
        make_options(false, false, false, false));
}

} // namespace binance::derivatives_trading_usds_futures::websocket_api
