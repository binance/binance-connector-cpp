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

struct AvgPriceResponseResult {
    /// Average price interval (in minutes)
    std::optional<std::int64_t> mins;
    /// Average price
    std::optional<std::string> price;
    /// Last trade time
    std::optional<std::int64_t> close_time;

    bool operator==(const AvgPriceResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AvgPriceResponseResult
tag_invoke(boost::json::value_to_tag<AvgPriceResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AvgPriceResponseResult& v);

} // namespace binance::spot::websocket_api
