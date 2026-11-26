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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

struct TimeResponse {
    std::optional<std::int64_t> server_time;

    bool operator==(const TimeResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TimeResponse tag_invoke(boost::json::value_to_tag<TimeResponse> /*tag*/,
                                            const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TimeResponse& v);

} // namespace binance::spot::rest_api
