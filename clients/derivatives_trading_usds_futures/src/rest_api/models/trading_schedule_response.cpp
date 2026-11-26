//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

TradingScheduleResponse tag_invoke(boost::json::value_to_tag<TradingScheduleResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradingScheduleResponse");
    TradingScheduleResponse out;
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "marketSchedules", out.market_schedules);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradingScheduleResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "marketSchedules", v.market_schedules);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
