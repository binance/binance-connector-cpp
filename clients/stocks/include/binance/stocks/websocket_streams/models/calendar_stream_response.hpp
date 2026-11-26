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

#include <binance/stocks/export.hpp>

namespace binance::stocks::websocket_streams {

struct CalendarStreamResponse {
    /// Event type, always `"calendar"`.
    std::optional<std::string> e;
    /// Previous market phase.
    std::optional<std::string> from;
    /// New market phase.
    std::optional<std::string> to;
    /// Event timestamp (epoch milliseconds UTC) when the transition was detected.
    std::optional<std::int64_t> ts;

    bool operator==(const CalendarStreamResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT CalendarStreamResponse
tag_invoke(boost::json::value_to_tag<CalendarStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const CalendarStreamResponse& v);

} // namespace binance::stocks::websocket_streams
