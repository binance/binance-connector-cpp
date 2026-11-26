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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct Ticker24hrPriceChangeStatisticsResponse2Inner {
    std::optional<std::string> symbol;
    /// Price Change.
    std::optional<std::string> price_change;
    /// Price Change Percent.
    std::optional<std::string> price_change_percent;
    /// Weighted Avg Price.
    std::optional<std::string> weighted_avg_price;
    /// Last Price.
    std::optional<std::string> last_price;
    /// Last Qty.
    std::optional<std::string> last_qty;
    /// Open Price.
    std::optional<std::string> open_price;
    /// High Price.
    std::optional<std::string> high_price;
    /// Low Price.
    std::optional<std::string> low_price;
    /// Volume.
    std::optional<std::string> volume;
    /// Quote Volume.
    std::optional<std::string> quote_volume;
    /// Open Time.
    std::optional<std::int64_t> open_time;
    /// Close Time.
    std::optional<std::int64_t> close_time;
    /// First tradeId
    std::optional<std::int64_t> first_id;
    /// Last tradeId
    std::optional<std::int64_t> last_id;
    /// Trade count
    std::optional<std::int64_t> count;

    bool operator==(const Ticker24hrPriceChangeStatisticsResponse2Inner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT Ticker24hrPriceChangeStatisticsResponse2Inner
tag_invoke(boost::json::value_to_tag<Ticker24hrPriceChangeStatisticsResponse2Inner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const Ticker24hrPriceChangeStatisticsResponse2Inner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
