//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_transfer_log_master_account_investor_response_manager_sub_transfer_history_vos_inner.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner
tag_invoke(
    boost::json::value_to_tag<
        QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner> /*tag*/
    ,
    const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryManagedSubAccountTransferLogMasterAccountInvestor"
                                            "ResponseManagerSubTransferHistoryVosInner");
    QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner
        out;
    common::detail::json::read(obj, "fromEmail", out.from_email);
    common::detail::json::read(obj, "fromAccountType", out.from_account_type);
    common::detail::json::read(obj, "toEmail", out.to_email);
    common::detail::json::read(obj, "toAccountType", out.to_account_type);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "scheduledData", out.scheduled_data);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "tranId", out.tran_id);
    return out;
}

void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner&
        v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "fromEmail", v.from_email);
    common::detail::json::write(obj, "fromAccountType", v.from_account_type);
    common::detail::json::write(obj, "toEmail", v.to_email);
    common::detail::json::write(obj, "toAccountType", v.to_account_type);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "scheduledData", v.scheduled_data);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "tranId", v.tran_id);
}

} // namespace binance::sub_account::rest_api
