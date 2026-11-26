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

struct Ticker24hrResponse2ResultInner {
    /// Symbol Name
    std::optional<std::string> symbol;
    std::optional<std::string> price_change;
    std::optional<std::string> price_change_percent;
    std::optional<std::string> weighted_avg_price;
    std::optional<std::string> prev_close_price;
    /// Closing price of the interval
    std::optional<std::string> last_price;
    std::optional<std::string> last_qty;
    std::optional<std::string> bid_price;
    std::optional<std::string> bid_qty;
    std::optional<std::string> ask_price;
    std::optional<std::string> ask_qty;
    /// Opening price of the Interval
    std::optional<std::string> open_price;
    /// Highest price in the interval
    std::optional<std::string> high_price;
    /// Lowest  price in the interval
    std::optional<std::string> low_price;
    /// Total trade volume (in base asset)
    std::optional<std::string> volume;
    /// Total trade volume (in quote asset)
    std::optional<std::string> quote_volume;
    /// Start of the ticker interval
    std::optional<std::int64_t> open_time;
    /// End of the ticker interval
    std::optional<std::int64_t> close_time;
    /// First tradeId
    std::optional<std::int64_t> first_id;
    /// Last tradeId
    std::optional<std::int64_t> last_id;
    /// Trade count
    std::optional<std::int64_t> count;

    bool operator==(const Ticker24hrResponse2ResultInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT Ticker24hrResponse2ResultInner
tag_invoke(boost::json::value_to_tag<Ticker24hrResponse2ResultInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const Ticker24hrResponse2ResultInner& v);

} // namespace binance::spot::websocket_api
