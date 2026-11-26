//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_list_response.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountListResponse
tag_invoke(boost::json::value_to_tag<QuerySubAccountListResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QuerySubAccountListResponse");
    QuerySubAccountListResponse out;
    common::detail::json::read(obj, "subAccounts", out.sub_accounts);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountListResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "subAccounts", v.sub_accounts);
}

} // namespace binance::sub_account::rest_api
