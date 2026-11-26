//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_list_response.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountListResponse
tag_invoke(boost::json::value_to_tag<QueryManagedSubAccountListResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryManagedSubAccountListResponse");
    QueryManagedSubAccountListResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "managerSubUserInfoVoList", out.manager_sub_user_info_vo_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountListResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "managerSubUserInfoVoList", v.manager_sub_user_info_vo_list);
}

} // namespace binance::sub_account::rest_api
