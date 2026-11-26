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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/account_update_ab_inner.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/account_update_ap_inner.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

/// Update Data
struct AccountUpdateA {
    /// Event reason type
    std::optional<std::string> m;
    /// Balances
    std::optional<std::vector<AccountUpdateABInner>> b_uppercase;
    std::optional<std::vector<AccountUpdateAPInner>> p_uppercase;
    /// Symbol associated with FUNDING_FEE event
    std::optional<std::string> s_uppercase;

    bool operator==(const AccountUpdateA& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AccountUpdateA
tag_invoke(boost::json::value_to_tag<AccountUpdateA> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const AccountUpdateA& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
