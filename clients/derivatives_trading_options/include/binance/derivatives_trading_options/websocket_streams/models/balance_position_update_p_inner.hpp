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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct BalancePositionUpdatePInner {
    /// Symbol
    std::optional<std::string> s;
    /// Position quantity
    std::optional<std::string> c;
    /// Position value
    std::optional<std::string> p;
    /// Average entry price
    std::optional<std::string> a;

    bool operator==(const BalancePositionUpdatePInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT BalancePositionUpdatePInner tag_invoke(
    boost::json::value_to_tag<BalancePositionUpdatePInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const BalancePositionUpdatePInner& v);

} // namespace binance::derivatives_trading_options::websocket_streams
