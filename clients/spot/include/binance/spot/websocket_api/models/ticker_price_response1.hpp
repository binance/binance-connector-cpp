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
#include <binance/spot/websocket_api/models/ticker_price_response1_result.hpp>

namespace binance::spot::websocket_api {

struct TickerPriceResponse1 {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<TickerPriceResponse1Result> result;
    std::optional<std::vector<AvgPriceResponseRateLimitsInner>> rate_limits;

    bool operator==(const TickerPriceResponse1& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerPriceResponse1
tag_invoke(boost::json::value_to_tag<TickerPriceResponse1> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerPriceResponse1& v);

} // namespace binance::spot::websocket_api
