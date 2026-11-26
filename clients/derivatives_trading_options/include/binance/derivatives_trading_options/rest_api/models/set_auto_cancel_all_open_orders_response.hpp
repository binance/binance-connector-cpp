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
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct SetAutoCancelAllOpenOrdersResponse {
    /// underlying
    std::optional<std::string> underlying;
    /// countdown Time
    std::optional<std::int64_t> countdown_time;

    bool operator==(const SetAutoCancelAllOpenOrdersResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT SetAutoCancelAllOpenOrdersResponse
tag_invoke(boost::json::value_to_tag<SetAutoCancelAllOpenOrdersResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const SetAutoCancelAllOpenOrdersResponse& v);

} // namespace binance::derivatives_trading_options::rest_api
