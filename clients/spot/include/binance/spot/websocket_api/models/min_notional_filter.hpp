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

struct MinNotionalFilter {
    std::optional<std::string> filter_type;
    std::optional<std::int64_t> price_exponent;
    std::optional<std::string> min_notional;
    std::optional<bool> apply_to_market;
    std::optional<std::int64_t> avg_price_mins;

    bool operator==(const MinNotionalFilter& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MinNotionalFilter
tag_invoke(boost::json::value_to_tag<MinNotionalFilter> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MinNotionalFilter& v);

} // namespace binance::spot::websocket_api
