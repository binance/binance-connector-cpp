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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

struct TradeLite {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Original Quantity
    std::optional<std::string> q;
    /// Original Price
    std::optional<std::string> p;
    /// Is this trade the maker side?
    std::optional<bool> m;
    /// Client Order Id
    std::optional<std::string> c;
    /// Side
    std::optional<std::string> s_uppercase;
    /// Last Filled Price
    std::optional<std::string> l_uppercase;
    /// Order Last Filled Quantity
    std::optional<std::string> l;
    /// Trade Id
    std::optional<std::int64_t> t;
    /// Order Id
    std::optional<std::int64_t> i;

    bool operator==(const TradeLite& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TradeLite
tag_invoke(boost::json::value_to_tag<TradeLite> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const TradeLite& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
