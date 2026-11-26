//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_transfer_list_response.hpp>

namespace binance::w3w_prediction::rest_api {

QueryTransferListResponse tag_invoke(boost::json::value_to_tag<QueryTransferListResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryTransferListResponse");
    QueryTransferListResponse out;
    common::detail::json::read(obj, "transfers", out.transfers);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryTransferListResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "transfers", v.transfers);
}

} // namespace binance::w3w_prediction::rest_api
