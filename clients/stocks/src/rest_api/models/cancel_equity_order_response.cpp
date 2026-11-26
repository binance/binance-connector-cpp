//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/cancel_equity_order_response.hpp>

namespace binance::stocks::rest_api {

CancelEquityOrderResponse tag_invoke(boost::json::value_to_tag<CancelEquityOrderResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CancelEquityOrderResponse");
    CancelEquityOrderResponse out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CancelEquityOrderResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::stocks::rest_api
