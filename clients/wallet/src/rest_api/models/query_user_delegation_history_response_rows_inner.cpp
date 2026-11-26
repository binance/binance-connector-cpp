//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/query_user_delegation_history_response_rows_inner.hpp>

namespace binance::wallet::rest_api {

QueryUserDelegationHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryUserDelegationHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryUserDelegationHistoryResponseRowsInner");
    QueryUserDelegationHistoryResponseRowsInner out;
    common::detail::json::read(obj, "clientTranId", out.client_tran_id);
    common::detail::json::read(obj, "transferType", out.transfer_type);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUserDelegationHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "clientTranId", v.client_tran_id);
    common::detail::json::write(obj, "transferType", v.transfer_type);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::wallet::rest_api
