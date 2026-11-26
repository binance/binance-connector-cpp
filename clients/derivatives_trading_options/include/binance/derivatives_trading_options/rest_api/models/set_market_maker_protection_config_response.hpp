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

struct SetMarketMakerProtectionConfigResponse {
    /// underlying Id
    std::optional<std::int64_t> underlying_id;
    /// underlying
    std::optional<std::string> underlying;
    /// window Time In Milliseconds
    std::optional<std::int64_t> window_time_in_milliseconds;
    /// frozen Time In Milliseconds
    std::optional<std::int64_t> frozen_time_in_milliseconds;
    /// qty Limit
    std::optional<std::string> qty_limit;
    /// delta Limit
    std::optional<std::string> delta_limit;
    /// last Trigger Time
    std::optional<std::int64_t> last_trigger_time;

    bool operator==(const SetMarketMakerProtectionConfigResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT SetMarketMakerProtectionConfigResponse
tag_invoke(boost::json::value_to_tag<SetMarketMakerProtectionConfigResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const SetMarketMakerProtectionConfigResponse& v);

} // namespace binance::derivatives_trading_options::rest_api
