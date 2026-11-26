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

struct MyFiltersResponseRateLimitsInner {
    std::optional<std::string> rate_limit_type;
    std::optional<std::string> interval;
    std::optional<std::int64_t> interval_num;
    std::optional<std::int64_t> limit;
    std::optional<std::int64_t> count;

    bool operator==(const MyFiltersResponseRateLimitsInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MyFiltersResponseRateLimitsInner
tag_invoke(boost::json::value_to_tag<MyFiltersResponseRateLimitsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MyFiltersResponseRateLimitsInner& v);

} // namespace binance::spot::rest_api
