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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct AccountUpdate {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    /// Account equity in USDT
    std::optional<std::string> eq;
    /// Account adjusted equity in USDT
    std::optional<std::string> aeq;
    /// Account wallet balance in USDT
    std::optional<std::string> b;
    /// Position value
    std::optional<std::string> m;
    /// Unrealized PnL
    std::optional<std::string> u;
    /// Initial margin in USDT
    std::optional<std::string> i;
    /// Maintenance margin in USDT
    std::optional<std::string> m_uppercase;

    bool operator==(const AccountUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT AccountUpdate
tag_invoke(boost::json::value_to_tag<AccountUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const AccountUpdate& v);

} // namespace binance::derivatives_trading_options::websocket_streams
