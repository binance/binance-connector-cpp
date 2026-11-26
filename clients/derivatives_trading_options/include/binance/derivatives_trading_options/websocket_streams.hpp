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
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/websocket_streams/websocket_streams.hpp>

namespace binance::derivatives_trading_options {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Derivatives Trading Options WebSocket streams client, created with
/// `DerivativesTradingOptionsWebsocketStreams::production(config)` and the other factories of
/// `websocket_streams::WebsocketStreams`.
using DerivativesTradingOptionsWebsocketStreams = websocket_streams::WebsocketStreams;
using DerivativesTradingOptionsWebsocketStreamsConnection =
    websocket_streams::WebsocketStreamsConnection;
using DerivativesTradingOptionsWsStreams = DerivativesTradingOptionsWebsocketStreams;
using DerivativesTradingOptionsWsStreamsConnection =
    DerivativesTradingOptionsWebsocketStreamsConnection;

} // namespace binance::derivatives_trading_options
