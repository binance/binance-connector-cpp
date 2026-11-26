//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_list_response_sub_accounts_inner.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountListResponseSubAccountsInner
tag_invoke(boost::json::value_to_tag<QuerySubAccountListResponseSubAccountsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QuerySubAccountListResponseSubAccountsInner");
    QuerySubAccountListResponseSubAccountsInner out;
    common::detail::json::read(obj, "subUserId", out.sub_user_id);
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "remark", out.remark);
    common::detail::json::read(obj, "isFreeze", out.is_freeze);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "isManagedSubAccount", out.is_managed_sub_account);
    common::detail::json::read(obj, "isAssetManagementSubAccount",
                               out.is_asset_management_sub_account);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountListResponseSubAccountsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "subUserId", v.sub_user_id);
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "remark", v.remark);
    common::detail::json::write(obj, "isFreeze", v.is_freeze);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "isManagedSubAccount", v.is_managed_sub_account);
    common::detail::json::write(obj, "isAssetManagementSubAccount",
                                v.is_asset_management_sub_account);
}

} // namespace binance::sub_account::rest_api
