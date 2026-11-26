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
#include <binance/alpha/rest_api/rest_api.hpp>
#include <binance/common/config.hpp>

namespace binance::alpha {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_ALPHA_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Alpha REST API client, created with `AlphaRestApi::production(config)`
/// and the other factories of `rest_api::RestApi`.
using AlphaRestApi = rest_api::RestApi;

} // namespace binance::alpha
