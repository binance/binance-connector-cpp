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

namespace binance::spot::rest_api {

struct TickerResponse1 {
    std::optional<std::string> symbol;
    /// Absolute price change
    std::optional<std::string> price_change;
    /// Relative price change in percent
    std::optional<std::string> price_change_percent;
    /// QuoteVolume / Volume
    std::optional<std::string> weighted_avg_price;
    std::optional<std::string> open_price;
    std::optional<std::string> high_price;
    std::optional<std::string> low_price;
    std::optional<std::string> last_price;
    std::optional<std::string> volume;
    /// Sum of (price * volume) for all trades
    std::optional<std::string> quote_volume;
    /// Open time for ticker window
    std::optional<std::int64_t> open_time;
    /// Close time for ticker window
    std::optional<std::int64_t> close_time;
    /// Trade IDs
    std::optional<std::int64_t> first_id;
    std::optional<std::int64_t> last_id;
    /// Number of trades in the interval
    std::optional<std::int64_t> count;

    bool operator==(const TickerResponse1& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerResponse1 tag_invoke(boost::json::value_to_tag<TickerResponse1> /*tag*/,
                                               const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerResponse1& v);

} // namespace binance::spot::rest_api
