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

namespace binance::spot::rest_api {

struct RateLimitOrderResponseInner {
    std::optional<std::string> rate_limit_type;
    std::optional<std::string> interval;
    std::optional<std::int64_t> interval_num;
    std::optional<std::int64_t> limit;
    std::optional<std::int64_t> count;

    bool operator==(const RateLimitOrderResponseInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT RateLimitOrderResponseInner tag_invoke(
    boost::json::value_to_tag<RateLimitOrderResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const RateLimitOrderResponseInner& v);

} // namespace binance::spot::rest_api
