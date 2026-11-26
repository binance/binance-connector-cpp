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
#include <binance/stock_options/export.hpp>
#include <binance/stock_options/websocket_streams/websocket_streams.hpp>

namespace binance::stock_options {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_STOCK_OPTIONS_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Stock Options WebSocket streams client, created with
/// `StockOptionsWebsocketStreams::production(config)` and the other factories of
/// `websocket_streams::WebsocketStreams`.
using StockOptionsWebsocketStreams = websocket_streams::WebsocketStreams;
using StockOptionsWebsocketStreamsConnection = websocket_streams::WebsocketStreamsConnection;
using StockOptionsWsStreams = StockOptionsWebsocketStreams;
using StockOptionsWsStreamsConnection = StockOptionsWebsocketStreamsConnection;

} // namespace binance::stock_options
