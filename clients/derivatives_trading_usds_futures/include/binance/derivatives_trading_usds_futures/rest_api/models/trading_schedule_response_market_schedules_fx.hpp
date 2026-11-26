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
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules_fx_sessions_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct TradingScheduleResponseMarketSchedulesFX {
    std::optional<std::vector<TradingScheduleResponseMarketSchedulesFXSessionsInner>> sessions;

    bool operator==(const TradingScheduleResponseMarketSchedulesFX& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TradingScheduleResponseMarketSchedulesFX
tag_invoke(boost::json::value_to_tag<TradingScheduleResponseMarketSchedulesFX> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const TradingScheduleResponseMarketSchedulesFX& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
