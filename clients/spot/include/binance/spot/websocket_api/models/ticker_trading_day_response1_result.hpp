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

struct TickerTradingDayResponse1Result {
    std::optional<std::string> symbol;
    /// Absolute price change
    std::optional<std::string> price_change;
    /// Relative price change in percent
    std::optional<std::string> price_change_percent;
    /// quoteVolume / volume
    std::optional<std::string> weighted_avg_price;
    std::optional<std::string> open_price;
    std::optional<std::string> high_price;
    std::optional<std::string> low_price;
    std::optional<std::string> last_price;
    /// Volume in base asset
    std::optional<std::string> volume;
    /// Volume in quote asset
    std::optional<std::string> quote_volume;
    std::optional<std::int64_t> open_time;
    std::optional<std::int64_t> close_time;
    /// Trade ID of the first trade in the interval
    std::optional<std::int64_t> first_id;
    /// Trade ID of the last trade in the interval
    std::optional<std::int64_t> last_id;
    /// Number of trades in the interval
    std::optional<std::int64_t> count;

    bool operator==(const TickerTradingDayResponse1Result& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerTradingDayResponse1Result
tag_invoke(boost::json::value_to_tag<TickerTradingDayResponse1Result> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerTradingDayResponse1Result& v);

} // namespace binance::spot::websocket_api
