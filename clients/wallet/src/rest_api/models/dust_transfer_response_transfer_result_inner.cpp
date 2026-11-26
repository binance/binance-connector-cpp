//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/dust_transfer_response_transfer_result_inner.hpp>

namespace binance::wallet::rest_api {

DustTransferResponseTransferResultInner
tag_invoke(boost::json::value_to_tag<DustTransferResponseTransferResultInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "DustTransferResponseTransferResultInner");
    DustTransferResponseTransferResultInner out;
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "fromAsset", out.from_asset);
    common::detail::json::read(obj, "operateTime", out.operate_time);
    common::detail::json::read(obj, "serviceChargeAmount", out.service_charge_amount);
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "transferedAmount", out.transfered_amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DustTransferResponseTransferResultInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "fromAsset", v.from_asset);
    common::detail::json::write(obj, "operateTime", v.operate_time);
    common::detail::json::write(obj, "serviceChargeAmount", v.service_charge_amount);
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "transferedAmount", v.transfered_amount);
}

} // namespace binance::wallet::rest_api
