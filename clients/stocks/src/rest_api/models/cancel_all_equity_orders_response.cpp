//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/cancel_all_equity_orders_response.hpp>

namespace binance::stocks::rest_api {

CancelAllEquityOrdersResponse
tag_invoke(boost::json::value_to_tag<CancelAllEquityOrdersResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CancelAllEquityOrdersResponse");
    CancelAllEquityOrdersResponse out;
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CancelAllEquityOrdersResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::stocks::rest_api
