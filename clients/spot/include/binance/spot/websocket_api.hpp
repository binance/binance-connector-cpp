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
#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/websocket_api.hpp>

namespace binance::spot {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Spot WebSocket API client, created with `SpotWebsocketApi::production(config)`
/// and the other factories of `websocket_api::WebsocketApi`.
using SpotWebsocketApi = websocket_api::WebsocketApi;
using SpotWebsocketApiConnection = websocket_api::WebsocketApiConnection;
using SpotWsApi = SpotWebsocketApi;
using SpotWsApiConnection = SpotWebsocketApiConnection;

} // namespace binance::spot
