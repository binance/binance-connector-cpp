//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response_counts.hpp>

namespace binance::w3w_prediction::rest_api {

QueryPositionsResponseCounts
tag_invoke(boost::json::value_to_tag<QueryPositionsResponseCounts> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryPositionsResponseCounts");
    QueryPositionsResponseCounts out;
    common::detail::json::read(obj, "ongoingCount", out.ongoing_count);
    common::detail::json::read(obj, "endedCount", out.ended_count);
    common::detail::json::read(obj, "pendingClaimCount", out.pending_claim_count);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPositionsResponseCounts& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "ongoingCount", v.ongoing_count);
    common::detail::json::write(obj, "endedCount", v.ended_count);
    common::detail::json::write(obj, "pendingClaimCount", v.pending_claim_count);
}

} // namespace binance::w3w_prediction::rest_api
