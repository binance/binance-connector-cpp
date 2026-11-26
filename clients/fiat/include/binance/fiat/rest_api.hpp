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
#include <binance/fiat/export.hpp>
#include <binance/fiat/rest_api/rest_api.hpp>

namespace binance::fiat {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_FIAT_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Fiat REST API client, created with `FiatRestApi::production(config)`
/// and the other factories of `rest_api::RestApi`.
using FiatRestApi = rest_api::RestApi;

} // namespace binance::fiat
