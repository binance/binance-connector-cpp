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
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_price_ticker_response1.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_price_ticker_response2.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct SymbolPriceTickerResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<SymbolPriceTickerResponse1, SymbolPriceTickerResponse2, boost::json::value> value;

    bool operator==(const SymbolPriceTickerResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT SymbolPriceTickerResponse tag_invoke(
    boost::json::value_to_tag<SymbolPriceTickerResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const SymbolPriceTickerResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
