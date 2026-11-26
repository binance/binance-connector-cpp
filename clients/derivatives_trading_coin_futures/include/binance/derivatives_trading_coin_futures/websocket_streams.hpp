//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <string_view>

#include <binance/common/config.hpp>
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/websocket_streams.hpp>

namespace binance::derivatives_trading_coin_futures {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Derivatives Trading Coin Futures WebSocket streams client, created with
/// `DerivativesTradingCoinFuturesWebsocketStreams::production(config)` and the other factories of
/// `websocket_streams::WebsocketStreams`.
using DerivativesTradingCoinFuturesWebsocketStreams = websocket_streams::WebsocketStreams;
using DerivativesTradingCoinFuturesWebsocketStreamsConnection =
    websocket_streams::WebsocketStreamsConnection;
using DerivativesTradingCoinFuturesWsStreams = DerivativesTradingCoinFuturesWebsocketStreams;
using DerivativesTradingCoinFuturesWsStreamsConnection =
    DerivativesTradingCoinFuturesWebsocketStreamsConnection;

} // namespace binance::derivatives_trading_coin_futures
