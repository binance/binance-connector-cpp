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

#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/account_config_update.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/account_update.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/algo_update.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/conditional_order_trigger_reject.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/grid_update.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/listen_key_expired.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/margin_call.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/order_trade_update.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/strategy_update.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct UserDataStreamEventsResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<AccountConfigUpdate, AccountUpdate, AlgoUpdate, ConditionalOrderTriggerReject,
                 GridUpdate, ListenKeyExpired, MarginCall, OrderTradeUpdate, StrategyUpdate,
                 boost::json::value>
        value;

    bool operator==(const UserDataStreamEventsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT UserDataStreamEventsResponse tag_invoke(
    boost::json::value_to_tag<UserDataStreamEventsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UserDataStreamEventsResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
