//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_list_response_manager_sub_user_info_vo_list_inner.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner");
    QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner out;
    common::detail::json::read(obj, "rootUserId", out.root_user_id);
    common::detail::json::read(obj, "managersubUserId", out.managersub_user_id);
    common::detail::json::read(obj, "bindParentUserId", out.bind_parent_user_id);
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "insertTimeStamp", out.insert_time_stamp);
    common::detail::json::read(obj, "bindParentEmail", out.bind_parent_email);
    common::detail::json::read(obj, "isSubUserEnabled", out.is_sub_user_enabled);
    common::detail::json::read(obj, "isUserActive", out.is_user_active);
    common::detail::json::read(obj, "isMarginEnabled", out.is_margin_enabled);
    common::detail::json::read(obj, "isFutureEnabled", out.is_future_enabled);
    common::detail::json::read(obj, "isSignedLVTRiskAgreement", out.is_signed_lvt_risk_agreement);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "rootUserId", v.root_user_id);
    common::detail::json::write(obj, "managersubUserId", v.managersub_user_id);
    common::detail::json::write(obj, "bindParentUserId", v.bind_parent_user_id);
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "insertTimeStamp", v.insert_time_stamp);
    common::detail::json::write(obj, "bindParentEmail", v.bind_parent_email);
    common::detail::json::write(obj, "isSubUserEnabled", v.is_sub_user_enabled);
    common::detail::json::write(obj, "isUserActive", v.is_user_active);
    common::detail::json::write(obj, "isMarginEnabled", v.is_margin_enabled);
    common::detail::json::write(obj, "isFutureEnabled", v.is_future_enabled);
    common::detail::json::write(obj, "isSignedLVTRiskAgreement", v.is_signed_lvt_risk_agreement);
}

} // namespace binance::sub_account::rest_api
