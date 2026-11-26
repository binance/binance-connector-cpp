//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/account_update.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/balance_position_update.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/greek_update.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/listen_key_expired.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/order_trade_update.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/risk_level_change.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct UserDataStreamEventsResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<AccountUpdate, BalancePositionUpdate, GreekUpdate, ListenKeyExpired,
                 OrderTradeUpdate, RiskLevelChange, boost::json::value>
        value;

    bool operator==(const UserDataStreamEventsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT UserDataStreamEventsResponse tag_invoke(
    boost::json::value_to_tag<UserDataStreamEventsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const UserDataStreamEventsResponse& v);

} // namespace binance::derivatives_trading_options::websocket_streams
