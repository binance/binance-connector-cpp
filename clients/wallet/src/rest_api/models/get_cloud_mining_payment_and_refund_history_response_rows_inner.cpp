//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_cloud_mining_payment_and_refund_history_response_rows_inner.hpp>

namespace binance::wallet::rest_api {

GetCloudMiningPaymentAndRefundHistoryResponseRowsInner tag_invoke(
    boost::json::value_to_tag<GetCloudMiningPaymentAndRefundHistoryResponseRowsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetCloudMiningPaymentAndRefundHistoryResponseRowsInner");
    GetCloudMiningPaymentAndRefundHistoryResponseRowsInner out;
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetCloudMiningPaymentAndRefundHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::wallet::rest_api
