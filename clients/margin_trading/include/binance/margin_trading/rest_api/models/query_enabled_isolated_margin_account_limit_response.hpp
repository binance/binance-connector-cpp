//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryEnabledIsolatedMarginAccountLimitResponse {
    /// enabled Account.
    std::optional<std::int64_t> enabled_account;
    /// max Account.
    std::optional<std::int64_t> max_account;

    bool
    operator==(const QueryEnabledIsolatedMarginAccountLimitResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryEnabledIsolatedMarginAccountLimitResponse
tag_invoke(boost::json::value_to_tag<QueryEnabledIsolatedMarginAccountLimitResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryEnabledIsolatedMarginAccountLimitResponse& v);

} // namespace binance::margin_trading::rest_api
