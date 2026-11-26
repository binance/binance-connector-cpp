//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <string_view>

#include <binance/c2c/export.hpp>
#include <binance/c2c/rest_api/rest_api.hpp>
#include <binance/common/config.hpp>

namespace binance::c2c {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_C2C_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The C2c REST API client, created with `C2CRestApi::production(config)`
/// and the other factories of `rest_api::RestApi`.
using C2CRestApi = rest_api::RestApi;

} // namespace binance::c2c
