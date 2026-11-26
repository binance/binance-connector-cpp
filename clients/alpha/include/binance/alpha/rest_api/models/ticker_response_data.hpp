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

#include <binance/alpha/export.hpp>

namespace binance::alpha::rest_api {

/// 24-hour rolling window ticker statistics.
struct TickerResponseData {
    /// Trading pair symbol.
    std::optional<std::string> symbol;
    /// Absolute price change in the 24h window.
    std::optional<std::string> price_change;
    /// Percentage price change in the 24h window.
    std::optional<std::string> price_change_percent;
    /// Weighted average price in the 24h window.
    std::optional<std::string> weighted_avg_price;
    /// Latest traded price.
    std::optional<std::string> last_price;
    /// Quantity of the latest trade.
    std::optional<std::string> last_qty;
    /// Opening price of the 24h window.
    std::optional<std::string> open_price;
    /// Highest price in the 24h window.
    std::optional<std::string> high_price;
    /// Lowest price in the 24h window.
    std::optional<std::string> low_price;
    /// Base asset volume in the 24h window.
    std::optional<std::string> volume;
    /// Quote asset volume in the 24h window.
    std::optional<std::string> quote_volume;
    /// Start time of the 24h window (milliseconds).
    std::optional<std::int64_t> open_time;
    /// End time of the 24h window (milliseconds).
    std::optional<std::int64_t> close_time;
    /// First trade ID in the 24h window.
    std::optional<std::int64_t> first_id;
    /// Last trade ID in the 24h window.
    std::optional<std::int64_t> last_id;
    /// Total number of trades in the 24h window.
    std::optional<std::int64_t> count;

    bool operator==(const TickerResponseData& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT TickerResponseData
tag_invoke(boost::json::value_to_tag<TickerResponseData> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const TickerResponseData& v);

} // namespace binance::alpha::rest_api
