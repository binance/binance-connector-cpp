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
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/websocket_api.hpp>

namespace binance::derivatives_trading_usds_futures {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Derivatives Trading Usds Futures WebSocket API client, created with
/// `DerivativesTradingUsdsFuturesWebsocketApi::production(config)` and the other factories of
/// `websocket_api::WebsocketApi`.
using DerivativesTradingUsdsFuturesWebsocketApi = websocket_api::WebsocketApi;
using DerivativesTradingUsdsFuturesWebsocketApiConnection = websocket_api::WebsocketApiConnection;
using DerivativesTradingUsdsFuturesWsApi = DerivativesTradingUsdsFuturesWebsocketApi;
using DerivativesTradingUsdsFuturesWsApiConnection =
    DerivativesTradingUsdsFuturesWebsocketApiConnection;

} // namespace binance::derivatives_trading_usds_futures
