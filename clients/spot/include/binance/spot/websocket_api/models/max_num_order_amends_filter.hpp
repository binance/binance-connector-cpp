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

struct MaxNumOrderAmendsFilter {
    std::optional<std::string> filter_type;
    std::optional<std::int64_t> max_num_order_amends;

    bool operator==(const MaxNumOrderAmendsFilter& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MaxNumOrderAmendsFilter tag_invoke(
    boost::json::value_to_tag<MaxNumOrderAmendsFilter> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MaxNumOrderAmendsFilter& v);

} // namespace binance::spot::websocket_api
