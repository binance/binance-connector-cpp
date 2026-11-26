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
#include <binance/spot/websocket_api/models/avg_price_response_rate_limits_inner.hpp>
#include <binance/spot/websocket_api/models/ticker24hr_response2_result_inner.hpp>

namespace binance::spot::websocket_api {

/// If more than one symbol is requested, response returns an array:
struct Ticker24hrResponse2 {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<std::vector<Ticker24hrResponse2ResultInner>> result;
    std::optional<std::vector<AvgPriceResponseRateLimitsInner>> rate_limits;

    bool operator==(const Ticker24hrResponse2& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT Ticker24hrResponse2
tag_invoke(boost::json::value_to_tag<Ticker24hrResponse2> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const Ticker24hrResponse2& v);

} // namespace binance::spot::websocket_api
