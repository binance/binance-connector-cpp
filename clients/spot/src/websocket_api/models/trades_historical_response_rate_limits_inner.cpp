//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/trades_historical_response_rate_limits_inner.hpp>

namespace binance::spot::websocket_api {

TradesHistoricalResponseRateLimitsInner
tag_invoke(boost::json::value_to_tag<TradesHistoricalResponseRateLimitsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "TradesHistoricalResponseRateLimitsInner");
    TradesHistoricalResponseRateLimitsInner out;
    common::detail::json::read(obj, "rateLimitType", out.rate_limit_type);
    common::detail::json::read(obj, "interval", out.interval);
    common::detail::json::read(obj, "intervalNum", out.interval_num);
    common::detail::json::read(obj, "limit", out.limit);
    common::detail::json::read(obj, "count", out.count);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradesHistoricalResponseRateLimitsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "rateLimitType", v.rate_limit_type);
    common::detail::json::write(obj, "interval", v.interval);
    common::detail::json::write(obj, "intervalNum", v.interval_num);
    common::detail::json::write(obj, "limit", v.limit);
    common::detail::json::write(obj, "count", v.count);
}

} // namespace binance::spot::websocket_api
