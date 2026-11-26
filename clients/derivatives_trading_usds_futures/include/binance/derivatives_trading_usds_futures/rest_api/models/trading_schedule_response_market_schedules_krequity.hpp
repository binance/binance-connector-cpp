//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules_krequity_sessions_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct TradingScheduleResponseMarketSchedulesKREQUITY {
    std::optional<std::vector<TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner>>
        sessions;

    bool
    operator==(const TradingScheduleResponseMarketSchedulesKREQUITY& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TradingScheduleResponseMarketSchedulesKREQUITY
tag_invoke(boost::json::value_to_tag<TradingScheduleResponseMarketSchedulesKREQUITY> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const TradingScheduleResponseMarketSchedulesKREQUITY& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
