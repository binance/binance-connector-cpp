//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules_commodity.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules_equity.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules_fx.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules_hkequity.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules_krequity.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct TradingScheduleResponseMarketSchedules {
    std::optional<TradingScheduleResponseMarketSchedulesEQUITY> equity;
    std::optional<TradingScheduleResponseMarketSchedulesCOMMODITY> commodity;
    std::optional<TradingScheduleResponseMarketSchedulesKREQUITY> kr_equity;
    std::optional<TradingScheduleResponseMarketSchedulesHKEQUITY> hk_equity;
    std::optional<TradingScheduleResponseMarketSchedulesHKEQUITY> cn_equity;
    std::optional<TradingScheduleResponseMarketSchedulesFX> fx_uppercase;

    bool operator==(const TradingScheduleResponseMarketSchedules& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TradingScheduleResponseMarketSchedules
tag_invoke(boost::json::value_to_tag<TradingScheduleResponseMarketSchedules> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const TradingScheduleResponseMarketSchedules& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
