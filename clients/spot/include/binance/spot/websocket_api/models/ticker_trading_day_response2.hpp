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
#include <binance/spot/websocket_api/models/ticker_response2_rate_limits_inner.hpp>
#include <binance/spot/websocket_api/models/ticker_trading_day_response2_result_inner.hpp>

namespace binance::spot::websocket_api {

struct TickerTradingDayResponse2 {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<std::vector<TickerTradingDayResponse2ResultInner>> result;
    std::optional<std::vector<TickerResponse2RateLimitsInner>> rate_limits;

    bool operator==(const TickerTradingDayResponse2& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerTradingDayResponse2 tag_invoke(
    boost::json::value_to_tag<TickerTradingDayResponse2> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerTradingDayResponse2& v);

} // namespace binance::spot::websocket_api
