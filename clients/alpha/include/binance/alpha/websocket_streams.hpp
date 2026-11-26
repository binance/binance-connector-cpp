//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <string_view>

#include <binance/alpha/export.hpp>
#include <binance/alpha/websocket_streams/websocket_streams.hpp>
#include <binance/common/config.hpp>

namespace binance::alpha {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_ALPHA_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Alpha WebSocket streams client, created with `AlphaWebsocketStreams::production(config)`
/// and the other factories of `websocket_streams::WebsocketStreams`.
using AlphaWebsocketStreams = websocket_streams::WebsocketStreams;
using AlphaWebsocketStreamsConnection = websocket_streams::WebsocketStreamsConnection;
using AlphaWsStreams = AlphaWebsocketStreams;
using AlphaWsStreamsConnection = AlphaWebsocketStreamsConnection;

} // namespace binance::alpha
