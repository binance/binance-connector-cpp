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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/ticker24hr_response1_rate_limits_inner.hpp>
#include <binance/spot/websocket_api/models/ticker24hr_response1_result.hpp>

namespace binance::spot::websocket_api {

struct Ticker24hrResponse1 {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<Ticker24hrResponse1Result> result;
    std::optional<std::vector<Ticker24hrResponse1RateLimitsInner>> rate_limits;

    bool operator==(const Ticker24hrResponse1& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT Ticker24hrResponse1
tag_invoke(boost::json::value_to_tag<Ticker24hrResponse1> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const Ticker24hrResponse1& v);

} // namespace binance::spot::websocket_api
