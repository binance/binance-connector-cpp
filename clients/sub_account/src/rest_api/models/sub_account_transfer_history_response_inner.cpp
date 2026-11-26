//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/sub_account_transfer_history_response_inner.hpp>

namespace binance::sub_account::rest_api {

SubAccountTransferHistoryResponseInner
tag_invoke(boost::json::value_to_tag<SubAccountTransferHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SubAccountTransferHistoryResponseInner");
    SubAccountTransferHistoryResponseInner out;
    common::detail::json::read(obj, "counterParty", out.counter_party);
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "fromAccountType", out.from_account_type);
    common::detail::json::read(obj, "toAccountType", out.to_account_type);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SubAccountTransferHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "counterParty", v.counter_party);
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "fromAccountType", v.from_account_type);
    common::detail::json::write(obj, "toAccountType", v.to_account_type);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::sub_account::rest_api
