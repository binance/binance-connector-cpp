//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_by_filter_response.hpp>

namespace binance::w3w_prediction::rest_api {

QueryPositionsByFilterResponse
tag_invoke(boost::json::value_to_tag<QueryPositionsByFilterResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryPositionsByFilterResponse");
    QueryPositionsByFilterResponse out;
    common::detail::json::read(obj, "positions", out.positions);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPositionsByFilterResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "positions", v.positions);
}

} // namespace binance::w3w_prediction::rest_api
