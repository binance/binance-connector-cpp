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

struct BalancePositionUpdateBInner {
    /// Margin asset
    std::optional<std::string> a;
    /// Account balance
    std::optional<std::string> b;
    /// Balance Change except PnL and Commission
    std::optional<std::string> bc;

    bool operator==(const BalancePositionUpdateBInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT BalancePositionUpdateBInner tag_invoke(
    boost::json::value_to_tag<BalancePositionUpdateBInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const BalancePositionUpdateBInner& v);

} // namespace binance::derivatives_trading_options::websocket_streams
