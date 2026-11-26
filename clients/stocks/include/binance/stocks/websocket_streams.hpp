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
#include <binance/stocks/export.hpp>
#include <binance/stocks/websocket_streams/websocket_streams.hpp>

namespace binance::stocks {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Stocks WebSocket streams client, created with `StocksWebsocketStreams::production(config)`
/// and the other factories of `websocket_streams::WebsocketStreams`.
using StocksWebsocketStreams = websocket_streams::WebsocketStreams;
using StocksWebsocketStreamsConnection = websocket_streams::WebsocketStreamsConnection;
using StocksWsStreams = StocksWebsocketStreams;
using StocksWsStreamsConnection = StocksWebsocketStreamsConnection;

} // namespace binance::stocks
