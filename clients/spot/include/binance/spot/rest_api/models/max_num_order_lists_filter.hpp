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

struct MaxNumOrderListsFilter {
    std::optional<std::string> filter_type;
    std::optional<std::int64_t> max_num_order_lists;

    bool operator==(const MaxNumOrderListsFilter& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MaxNumOrderListsFilter
tag_invoke(boost::json::value_to_tag<MaxNumOrderListsFilter> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MaxNumOrderListsFilter& v);

} // namespace binance::spot::rest_api
