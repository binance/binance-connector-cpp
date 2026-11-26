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

#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/balance_position_update_b_inner.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/balance_position_update_p_inner.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct BalancePositionUpdate {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    /// Event reason type
    std::optional<std::string> m;
    /// Balances
    std::optional<std::vector<BalancePositionUpdateBInner>> b_uppercase;
    /// Positions
    std::optional<std::vector<BalancePositionUpdatePInner>> p_uppercase;

    bool operator==(const BalancePositionUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT BalancePositionUpdate
tag_invoke(boost::json::value_to_tag<BalancePositionUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const BalancePositionUpdate& v);

} // namespace binance::derivatives_trading_options::websocket_streams
