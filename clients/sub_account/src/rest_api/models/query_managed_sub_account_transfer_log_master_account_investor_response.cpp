//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_transfer_log_master_account_investor_response.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountTransferLogMasterAccountInvestorResponse
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountTransferLogMasterAccountInvestorResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryManagedSubAccountTransferLogMasterAccountInvestorResponse");
    QueryManagedSubAccountTransferLogMasterAccountInvestorResponse out;
    common::detail::json::read(obj, "managerSubTransferHistoryVos",
                               out.manager_sub_transfer_history_vos);
    common::detail::json::read(obj, "count", out.count);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountTransferLogMasterAccountInvestorResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "managerSubTransferHistoryVos",
                                v.manager_sub_transfer_history_vos);
    common::detail::json::write(obj, "count", v.count);
}

} // namespace binance::sub_account::rest_api
