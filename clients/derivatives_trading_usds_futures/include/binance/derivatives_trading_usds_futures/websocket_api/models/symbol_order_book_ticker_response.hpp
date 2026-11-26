//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_order_book_ticker_response1.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_order_book_ticker_response2.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct SymbolOrderBookTickerResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<SymbolOrderBookTickerResponse1, SymbolOrderBookTickerResponse2, boost::json::value>
        value;

    bool operator==(const SymbolOrderBookTickerResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT SymbolOrderBookTickerResponse tag_invoke(
    boost::json::value_to_tag<SymbolOrderBookTickerResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const SymbolOrderBookTickerResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
