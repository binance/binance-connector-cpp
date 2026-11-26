//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/reset_market_maker_protection_config_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

ResetMarketMakerProtectionConfigResponse
tag_invoke(boost::json::value_to_tag<ResetMarketMakerProtectionConfigResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ResetMarketMakerProtectionConfigResponse");
    ResetMarketMakerProtectionConfigResponse out;
    common::detail::json::read(obj, "underlyingId", out.underlying_id);
    common::detail::json::read(obj, "underlying", out.underlying);
    common::detail::json::read(obj, "windowTimeInMilliseconds", out.window_time_in_milliseconds);
    common::detail::json::read(obj, "frozenTimeInMilliseconds", out.frozen_time_in_milliseconds);
    common::detail::json::read(obj, "qtyLimit", out.qty_limit);
    common::detail::json::read(obj, "deltaLimit", out.delta_limit);
    common::detail::json::read(obj, "lastTriggerTime", out.last_trigger_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ResetMarketMakerProtectionConfigResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "underlyingId", v.underlying_id);
    common::detail::json::write(obj, "underlying", v.underlying);
    common::detail::json::write(obj, "windowTimeInMilliseconds", v.window_time_in_milliseconds);
    common::detail::json::write(obj, "frozenTimeInMilliseconds", v.frozen_time_in_milliseconds);
    common::detail::json::write(obj, "qtyLimit", v.qty_limit);
    common::detail::json::write(obj, "deltaLimit", v.delta_limit);
    common::detail::json::write(obj, "lastTriggerTime", v.last_trigger_time);
}

} // namespace binance::derivatives_trading_options::rest_api
