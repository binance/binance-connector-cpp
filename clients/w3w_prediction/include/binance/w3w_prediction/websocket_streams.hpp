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
#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/websocket_streams/websocket_streams.hpp>

namespace binance::w3w_prediction {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The W3w Prediction WebSocket streams client, created with
/// `W3WPredictionWebsocketStreams::production(config)` and the other factories of
/// `websocket_streams::WebsocketStreams`.
using W3WPredictionWebsocketStreams = websocket_streams::WebsocketStreams;
using W3WPredictionWebsocketStreamsConnection = websocket_streams::WebsocketStreamsConnection;
using W3WPredictionWsStreams = W3WPredictionWebsocketStreams;
using W3WPredictionWsStreamsConnection = W3WPredictionWebsocketStreamsConnection;

} // namespace binance::w3w_prediction
