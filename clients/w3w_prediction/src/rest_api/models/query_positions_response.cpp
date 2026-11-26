//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response.hpp>

namespace binance::w3w_prediction::rest_api {

QueryPositionsResponse tag_invoke(boost::json::value_to_tag<QueryPositionsResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryPositionsResponse");
    QueryPositionsResponse out;
    common::detail::json::read(obj, "summary", out.summary);
    common::detail::json::read(obj, "counts", out.counts);
    common::detail::json::read(obj, "positions", out.positions);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPositionsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "summary", v.summary);
    common::detail::json::write(obj, "counts", v.counts);
    common::detail::json::write(obj, "positions", v.positions);
}

} // namespace binance::w3w_prediction::rest_api
