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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct Ticker24hrPriceChangeStatisticsResponseInner {
    /// symbol
    std::optional<std::string> symbol;
    /// 24-hour price change
    std::optional<std::string> price_change;
    /// 24-hour percent price change
    std::optional<std::string> price_change_percent;
    /// Last trade price
    std::optional<std::string> last_price;
    /// Last trade amount
    std::optional<std::string> last_qty;
    /// 24-hour open price
    std::optional<std::string> open;
    /// 24-hour high
    std::optional<std::string> high;
    /// 24-hour low
    std::optional<std::string> low;
    /// Trading volume(contracts)
    std::optional<std::string> volume;
    /// Trade amount(in quote asset)
    std::optional<std::string> amount;
    /// The best buy price
    std::optional<std::string> bid_price;
    /// The best sell price
    std::optional<std::string> ask_price;
    /// Time the first trade occurred within the last 24 hours
    std::optional<std::int64_t> open_time;
    /// Time the last trade occurred within the last 24 hours
    std::optional<std::int64_t> close_time;
    /// First trade ID
    std::optional<std::int64_t> first_trade_id;
    /// Number of trades
    std::optional<std::int64_t> trade_count;
    /// Strike price
    std::optional<std::string> strike_price;
    /// return estimated settlement price one hour before exercise, return index price at other
    /// times
    std::optional<std::string> exercise_price;

    bool operator==(const Ticker24hrPriceChangeStatisticsResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT Ticker24hrPriceChangeStatisticsResponseInner
tag_invoke(boost::json::value_to_tag<Ticker24hrPriceChangeStatisticsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const Ticker24hrPriceChangeStatisticsResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
