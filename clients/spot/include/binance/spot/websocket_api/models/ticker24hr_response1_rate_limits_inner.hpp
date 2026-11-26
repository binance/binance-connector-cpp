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

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

struct Ticker24hrResponse1RateLimitsInner {
    std::optional<std::string> rate_limit_type;
    std::optional<std::string> interval;
    std::optional<std::int64_t> interval_num;
    std::optional<std::int64_t> limit;
    /// Number of trades
    std::optional<std::int64_t> count;

    bool operator==(const Ticker24hrResponse1RateLimitsInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT Ticker24hrResponse1RateLimitsInner
tag_invoke(boost::json::value_to_tag<Ticker24hrResponse1RateLimitsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const Ticker24hrResponse1RateLimitsInner& v);

} // namespace binance::spot::websocket_api
