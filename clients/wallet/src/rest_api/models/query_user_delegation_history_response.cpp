//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/query_user_delegation_history_response.hpp>

namespace binance::wallet::rest_api {

QueryUserDelegationHistoryResponse
tag_invoke(boost::json::value_to_tag<QueryUserDelegationHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryUserDelegationHistoryResponse");
    QueryUserDelegationHistoryResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "rows", out.rows);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUserDelegationHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "rows", v.rows);
}

} // namespace binance::wallet::rest_api
