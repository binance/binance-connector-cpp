//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/open_order_lists_status_response.hpp>

namespace binance::spot::websocket_api {

OpenOrderListsStatusResponse
tag_invoke(boost::json::value_to_tag<OpenOrderListsStatusResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OpenOrderListsStatusResponse");
    OpenOrderListsStatusResponse out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "result", out.result);
    common::detail::json::read(obj, "rateLimits", out.rate_limits);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OpenOrderListsStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "result", v.result);
    common::detail::json::write(obj, "rateLimits", v.rate_limits);
}

} // namespace binance::spot::websocket_api
