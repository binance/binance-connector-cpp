//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_settled_position_history_response.hpp>

namespace binance::w3w_prediction::rest_api {

QuerySettledPositionHistoryResponse
tag_invoke(boost::json::value_to_tag<QuerySettledPositionHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QuerySettledPositionHistoryResponse");
    QuerySettledPositionHistoryResponse out;
    common::detail::json::read(obj, "totalCount", out.total_count);
    common::detail::json::read(obj, "positions", out.positions);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySettledPositionHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalCount", v.total_count);
    common::detail::json::write(obj, "positions", v.positions);
}

} // namespace binance::w3w_prediction::rest_api
