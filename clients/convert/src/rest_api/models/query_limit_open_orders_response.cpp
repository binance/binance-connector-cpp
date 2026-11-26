//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/convert/rest_api/models/query_limit_open_orders_response.hpp>

namespace binance::convert::rest_api {

QueryLimitOpenOrdersResponse
tag_invoke(boost::json::value_to_tag<QueryLimitOpenOrdersResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryLimitOpenOrdersResponse");
    QueryLimitOpenOrdersResponse out;
    common::detail::json::read(obj, "list", out.list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryLimitOpenOrdersResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "list", v.list);
}

} // namespace binance::convert::rest_api
