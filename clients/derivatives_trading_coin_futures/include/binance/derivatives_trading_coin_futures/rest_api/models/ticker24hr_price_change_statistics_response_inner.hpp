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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct Ticker24hrPriceChangeStatisticsResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Pair
    std::optional<std::string> pair;
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
    /// Base asset volume.
    std::optional<std::string> base_volume;
    /// Start time of the 24h window (milliseconds).
    std::optional<std::int64_t> open_time;
    /// End time of the 24h window (milliseconds).
    std::optional<std::int64_t> close_time;
    /// First tradeId
    std::optional<std::int64_t> first_id;
    /// Last tradeId
    std::optional<std::int64_t> last_id;
    /// Total number of trades in the 24h window.
    std::optional<std::int64_t> count;

    bool operator==(const Ticker24hrPriceChangeStatisticsResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT Ticker24hrPriceChangeStatisticsResponseInner
tag_invoke(boost::json::value_to_tag<Ticker24hrPriceChangeStatisticsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const Ticker24hrPriceChangeStatisticsResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
