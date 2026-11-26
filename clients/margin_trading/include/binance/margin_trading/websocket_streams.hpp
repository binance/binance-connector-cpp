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
#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/websocket_streams/websocket_streams.hpp>

namespace binance::margin_trading {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Margin Trading WebSocket streams client, created with
/// `MarginTradingWebsocketStreams::production(config)` and the other factories of
/// `websocket_streams::WebsocketStreams`.
using MarginTradingWebsocketStreams = websocket_streams::WebsocketStreams;
using MarginTradingWebsocketStreamsConnection = websocket_streams::WebsocketStreamsConnection;
using MarginTradingWsStreams = MarginTradingWebsocketStreams;
using MarginTradingWsStreamsConnection = MarginTradingWebsocketStreamsConnection;

} // namespace binance::margin_trading
