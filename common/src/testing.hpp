//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

// Test hooks: exported by the library but not installed.

#include <chrono>

#include <binance/common/export.hpp>

namespace binance::common::detail {

/// Replaces the 23-hour renewal interval of connections opened afterwards, in every client of
/// the process. Zero restores the default.
BINANCE_COMMON_EXPORT void
set_renewal_interval_for_testing(std::chrono::milliseconds interval) noexcept;

/// Replaces the 30 s PING interval of signed streams for connections opened afterwards. Zero
/// restores the default.
BINANCE_COMMON_EXPORT void
set_signed_ping_interval_for_testing(std::chrono::milliseconds interval) noexcept;

} // namespace binance::common::detail
