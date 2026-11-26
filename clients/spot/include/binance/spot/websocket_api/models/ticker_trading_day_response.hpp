//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/ticker_trading_day_response1.hpp>
#include <binance/spot/websocket_api/models/ticker_trading_day_response2.hpp>

namespace binance::spot::websocket_api {

struct TickerTradingDayResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<TickerTradingDayResponse1, TickerTradingDayResponse2, boost::json::value> value;

    bool operator==(const TickerTradingDayResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerTradingDayResponse tag_invoke(
    boost::json::value_to_tag<TickerTradingDayResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerTradingDayResponse& v);

} // namespace binance::spot::websocket_api
