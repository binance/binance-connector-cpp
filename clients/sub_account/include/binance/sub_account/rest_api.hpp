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
#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/rest_api.hpp>

namespace binance::sub_account {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_SUB_ACCOUNT_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Sub Account REST API client, created with `SubAccountRestApi::production(config)`
/// and the other factories of `rest_api::RestApi`.
using SubAccountRestApi = rest_api::RestApi;

} // namespace binance::sub_account
