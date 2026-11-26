//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules_krequity.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

TradingScheduleResponseMarketSchedulesKREQUITY
tag_invoke(boost::json::value_to_tag<TradingScheduleResponseMarketSchedulesKREQUITY> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "TradingScheduleResponseMarketSchedulesKREQUITY");
    TradingScheduleResponseMarketSchedulesKREQUITY out;
    common::detail::json::read(obj, "sessions", out.sessions);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradingScheduleResponseMarketSchedulesKREQUITY& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "sessions", v.sessions);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
