//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/set_auto_cancel_all_open_orders_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

SetAutoCancelAllOpenOrdersResponse
tag_invoke(boost::json::value_to_tag<SetAutoCancelAllOpenOrdersResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SetAutoCancelAllOpenOrdersResponse");
    SetAutoCancelAllOpenOrdersResponse out;
    common::detail::json::read(obj, "underlying", out.underlying);
    common::detail::json::read(obj, "countdownTime", out.countdown_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SetAutoCancelAllOpenOrdersResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "underlying", v.underlying);
    common::detail::json::write(obj, "countdownTime", v.countdown_time);
}

} // namespace binance::derivatives_trading_options::rest_api
