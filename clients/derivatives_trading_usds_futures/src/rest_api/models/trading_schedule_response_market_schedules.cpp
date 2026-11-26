//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response_market_schedules.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

TradingScheduleResponseMarketSchedules
tag_invoke(boost::json::value_to_tag<TradingScheduleResponseMarketSchedules> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradingScheduleResponseMarketSchedules");
    TradingScheduleResponseMarketSchedules out;
    common::detail::json::read(obj, "EQUITY", out.equity);
    common::detail::json::read(obj, "COMMODITY", out.commodity);
    common::detail::json::read(obj, "KR_EQUITY", out.kr_equity);
    common::detail::json::read(obj, "HK_EQUITY", out.hk_equity);
    common::detail::json::read(obj, "CN_EQUITY", out.cn_equity);
    common::detail::json::read(obj, "FX", out.fx_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradingScheduleResponseMarketSchedules& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "EQUITY", v.equity);
    common::detail::json::write(obj, "COMMODITY", v.commodity);
    common::detail::json::write(obj, "KR_EQUITY", v.kr_equity);
    common::detail::json::write(obj, "HK_EQUITY", v.hk_equity);
    common::detail::json::write(obj, "CN_EQUITY", v.cn_equity);
    common::detail::json::write(obj, "FX", v.fx_uppercase);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
