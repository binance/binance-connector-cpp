//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/convert/export.hpp>
#include <binance/convert/rest_api/models/query_limit_open_orders_response_list_inner.hpp>

namespace binance::convert::rest_api {

struct QueryLimitOpenOrdersResponse {
    std::optional<std::vector<QueryLimitOpenOrdersResponseListInner>> list;

    bool operator==(const QueryLimitOpenOrdersResponse& /*other*/) const = default;
};

BINANCE_CONVERT_EXPORT QueryLimitOpenOrdersResponse tag_invoke(
    boost::json::value_to_tag<QueryLimitOpenOrdersResponse> /*tag*/, const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const QueryLimitOpenOrdersResponse& v);

} // namespace binance::convert::rest_api
