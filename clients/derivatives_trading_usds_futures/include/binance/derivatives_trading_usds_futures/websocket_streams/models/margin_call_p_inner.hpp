//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

struct MarginCallPInner {
    /// Symbol
    std::optional<std::string> s;
    /// Position Side
    std::optional<std::string> ps;
    /// Position Amount
    std::optional<std::string> pa;
    /// Margin Type
    std::optional<std::string> mt;
    /// Isolated Wallet (if isolated position)
    std::optional<std::string> iw;
    /// Mark Price
    std::optional<std::string> mp;
    /// Unrealized PnL
    std::optional<std::string> up;
    /// Maintenance Margin Required
    std::optional<std::string> mm;

    bool operator==(const MarginCallPInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarginCallPInner
tag_invoke(boost::json::value_to_tag<MarginCallPInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const MarginCallPInner& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
