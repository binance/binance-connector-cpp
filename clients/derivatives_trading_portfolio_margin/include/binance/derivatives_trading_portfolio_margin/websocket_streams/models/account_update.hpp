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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/account_update_a.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

struct AccountUpdate {
    /// Event business unit. 'UM' for USDS-M futures and 'CM' for COIN-M futures
    std::optional<std::string> fs;
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Transaction
    std::optional<std::int64_t> t_uppercase;
    /// Account Alias, ignore for UM
    std::optional<std::string> i;
    std::optional<AccountUpdateA> a;

    bool operator==(const AccountUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT AccountUpdate
tag_invoke(boost::json::value_to_tag<AccountUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const AccountUpdate& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
