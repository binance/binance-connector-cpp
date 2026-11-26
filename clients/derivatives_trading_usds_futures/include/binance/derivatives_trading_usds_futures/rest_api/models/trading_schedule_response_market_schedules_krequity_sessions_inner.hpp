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

struct TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner {
    std::optional<std::int64_t> start_time;
    std::optional<std::int64_t> end_time;
    std::optional<std::string> type;

    bool operator==(const TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner tag_invoke(
    boost::json::value_to_tag<TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
