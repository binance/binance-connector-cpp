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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/account_config_update.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/account_update.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/algo_order_update.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/balance_update.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/conditional_order_trade_update.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/execution_report.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/liability_change.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/listen_key_expired.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/open_order_loss.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/order_trade_update.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/outbound_account_position.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/risk_level_change.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

struct UserDataStreamEventsResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<AccountConfigUpdate, AccountUpdate, AlgoOrderUpdate, BalanceUpdate,
                 ConditionalOrderTradeUpdate, ExecutionReport, LiabilityChange, ListenKeyExpired,
                 OpenOrderLoss, OrderTradeUpdate, OutboundAccountPosition, RiskLevelChange,
                 boost::json::value>
        value;

    bool operator==(const UserDataStreamEventsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT UserDataStreamEventsResponse tag_invoke(
    boost::json::value_to_tag<UserDataStreamEventsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UserDataStreamEventsResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
