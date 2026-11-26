//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules_krequity_sessions_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner tag_invoke(
    boost::json::value_to_tag<TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner");
    TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner out;
    common::detail::json::read(obj, "startTime", out.start_time);
    common::detail::json::read(obj, "endTime", out.end_time);
    common::detail::json::read(obj, "type", out.type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradingScheduleResponseMarketSchedulesKREQUITYSessionsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "startTime", v.start_time);
    common::detail::json::write(obj, "endTime", v.end_time);
    common::detail::json::write(obj, "type", v.type);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
