//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_active_orders_response.hpp>

namespace binance::w3w_prediction::rest_api {

QueryActiveOrdersResponse tag_invoke(boost::json::value_to_tag<QueryActiveOrdersResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryActiveOrdersResponse");
    QueryActiveOrdersResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "offset", out.offset);
    common::detail::json::read(obj, "limit", out.limit);
    common::detail::json::read(obj, "orders", out.orders);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryActiveOrdersResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "offset", v.offset);
    common::detail::json::write(obj, "limit", v.limit);
    common::detail::json::write(obj, "orders", v.orders);
}

} // namespace binance::w3w_prediction::rest_api
