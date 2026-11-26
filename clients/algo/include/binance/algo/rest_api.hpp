//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <string_view>

#include <binance/algo/export.hpp>
#include <binance/algo/rest_api/rest_api.hpp>
#include <binance/common/config.hpp>

namespace binance::algo {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Algo REST API client, created with `AlgoRestApi::production(config)`
/// and the other factories of `rest_api::RestApi`.
using AlgoRestApi = rest_api::RestApi;

} // namespace binance::algo
