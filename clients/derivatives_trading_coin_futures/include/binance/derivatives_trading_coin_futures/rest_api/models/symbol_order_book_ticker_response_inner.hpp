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

struct SymbolOrderBookTickerResponseInner {
    /// Last update ID.
    std::optional<std::int64_t> last_update_id;
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Pair
    std::optional<std::string> pair;
    /// Best bid price.
    std::optional<std::string> bid_price;
    /// Best bid quantity.
    std::optional<std::string> bid_qty;
    /// Best ask price.
    std::optional<std::string> ask_price;
    /// Best ask quantity.
    std::optional<std::string> ask_qty;
    /// Time
    std::optional<std::int64_t> time;

    bool operator==(const SymbolOrderBookTickerResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT SymbolOrderBookTickerResponseInner
tag_invoke(boost::json::value_to_tag<SymbolOrderBookTickerResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const SymbolOrderBookTickerResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
