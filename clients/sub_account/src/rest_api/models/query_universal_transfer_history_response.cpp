//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_universal_transfer_history_response.hpp>

namespace binance::sub_account::rest_api {

QueryUniversalTransferHistoryResponse
tag_invoke(boost::json::value_to_tag<QueryUniversalTransferHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryUniversalTransferHistoryResponse");
    QueryUniversalTransferHistoryResponse out;
    common::detail::json::read(obj, "result", out.result);
    common::detail::json::read(obj, "totalCount", out.total_count);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUniversalTransferHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "result", v.result);
    common::detail::json::write(obj, "totalCount", v.total_count);
}

} // namespace binance::sub_account::rest_api
