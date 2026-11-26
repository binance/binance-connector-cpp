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
#include <binance/derivatives_trading_coin_futures/rest_api/rest_api.hpp>

namespace binance::derivatives_trading_coin_futures {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Derivatives Trading Coin Futures REST API client, created with
/// `DerivativesTradingCoinFuturesRestApi::production(config)` and the other factories of
/// `rest_api::RestApi`.
using DerivativesTradingCoinFuturesRestApi = rest_api::RestApi;

} // namespace binance::derivatives_trading_coin_futures
