//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/query_user_universal_transfer_history_response_rows_inner.hpp>

namespace binance::wallet::rest_api {

QueryUserUniversalTransferHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryUserUniversalTransferHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryUserUniversalTransferHistoryResponseRowsInner");
    QueryUserUniversalTransferHistoryResponseRowsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUserUniversalTransferHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::wallet::rest_api
