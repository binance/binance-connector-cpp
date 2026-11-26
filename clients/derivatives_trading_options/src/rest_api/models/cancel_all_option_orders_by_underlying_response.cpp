//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/cancel_all_option_orders_by_underlying_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

CancelAllOptionOrdersByUnderlyingResponse
tag_invoke(boost::json::value_to_tag<CancelAllOptionOrdersByUnderlyingResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "CancelAllOptionOrdersByUnderlyingResponse");
    CancelAllOptionOrdersByUnderlyingResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CancelAllOptionOrdersByUnderlyingResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::derivatives_trading_options::rest_api
