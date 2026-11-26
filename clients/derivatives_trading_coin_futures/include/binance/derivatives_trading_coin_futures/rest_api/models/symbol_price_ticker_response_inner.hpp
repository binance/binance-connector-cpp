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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct SymbolPriceTickerResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Pair
    std::optional<std::string> ps;
    /// Latest token price.
    std::optional<std::string> price;
    /// Time
    std::optional<std::int64_t> time;

    bool operator==(const SymbolPriceTickerResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT SymbolPriceTickerResponseInner
tag_invoke(boost::json::value_to_tag<SymbolPriceTickerResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const SymbolPriceTickerResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
