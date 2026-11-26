//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_universal_transfer_history_response_result_inner.hpp>

namespace binance::sub_account::rest_api {

QueryUniversalTransferHistoryResponseResultInner
tag_invoke(boost::json::value_to_tag<QueryUniversalTransferHistoryResponseResultInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryUniversalTransferHistoryResponseResultInner");
    QueryUniversalTransferHistoryResponseResultInner out;
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "fromEmail", out.from_email);
    common::detail::json::read(obj, "toEmail", out.to_email);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "createTimeStamp", out.create_time_stamp);
    common::detail::json::read(obj, "fromAccountType", out.from_account_type);
    common::detail::json::read(obj, "toAccountType", out.to_account_type);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "clientTranId", out.client_tran_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUniversalTransferHistoryResponseResultInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "fromEmail", v.from_email);
    common::detail::json::write(obj, "toEmail", v.to_email);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "createTimeStamp", v.create_time_stamp);
    common::detail::json::write(obj, "fromAccountType", v.from_account_type);
    common::detail::json::write(obj, "toAccountType", v.to_account_type);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "clientTranId", v.client_tran_id);
}

} // namespace binance::sub_account::rest_api
