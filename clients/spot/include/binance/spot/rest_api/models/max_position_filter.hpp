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

struct MaxPositionFilter {
    std::optional<std::string> filter_type;
    std::optional<std::int64_t> qty_exponent;
    std::optional<std::string> max_position;

    bool operator==(const MaxPositionFilter& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MaxPositionFilter
tag_invoke(boost::json::value_to_tag<MaxPositionFilter> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MaxPositionFilter& v);

} // namespace binance::spot::rest_api
