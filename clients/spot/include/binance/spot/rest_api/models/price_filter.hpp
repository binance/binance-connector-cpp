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

struct PriceFilter {
    std::optional<std::string> filter_type;
    std::optional<std::int64_t> price_exponent;
    std::optional<std::string> min_price;
    std::optional<std::string> max_price;
    std::optional<std::string> tick_size;

    bool operator==(const PriceFilter& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT PriceFilter tag_invoke(boost::json::value_to_tag<PriceFilter> /*tag*/,
                                           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const PriceFilter& v);

} // namespace binance::spot::rest_api
