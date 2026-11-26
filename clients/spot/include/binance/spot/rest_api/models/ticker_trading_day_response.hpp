//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/ticker_trading_day_response1.hpp>
#include <binance/spot/rest_api/models/ticker_trading_day_response2_inner.hpp>

namespace binance::spot::rest_api {

struct TickerTradingDayResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<TickerTradingDayResponse1, std::vector<TickerTradingDayResponse2Inner>,
                 boost::json::value>
        value;

    bool operator==(const TickerTradingDayResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerTradingDayResponse tag_invoke(
    boost::json::value_to_tag<TickerTradingDayResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerTradingDayResponse& v);

} // namespace binance::spot::rest_api
