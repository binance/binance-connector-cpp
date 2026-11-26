//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_order_book_ticker_response1_rate_limits_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_order_book_ticker_response1_result.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct SymbolOrderBookTickerResponse1 {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<SymbolOrderBookTickerResponse1Result> result;
    std::optional<std::vector<SymbolOrderBookTickerResponse1RateLimitsInner>> rate_limits;

    bool operator==(const SymbolOrderBookTickerResponse1& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT SymbolOrderBookTickerResponse1
tag_invoke(boost::json::value_to_tag<SymbolOrderBookTickerResponse1> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const SymbolOrderBookTickerResponse1& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
