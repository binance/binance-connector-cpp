//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/dustlog_response_user_asset_dribblets_inner.hpp>

namespace binance::wallet::rest_api {

DustlogResponseUserAssetDribbletsInner
tag_invoke(boost::json::value_to_tag<DustlogResponseUserAssetDribbletsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "DustlogResponseUserAssetDribbletsInner");
    DustlogResponseUserAssetDribbletsInner out;
    common::detail::json::read(obj, "operateTime", out.operate_time);
    common::detail::json::read(obj, "totalTransferedAmount", out.total_transfered_amount);
    common::detail::json::read(obj, "totalServiceChargeAmount", out.total_service_charge_amount);
    common::detail::json::read(obj, "transId", out.trans_id);
    common::detail::json::read(obj, "userAssetDribbletDetails", out.user_asset_dribblet_details);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DustlogResponseUserAssetDribbletsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "operateTime", v.operate_time);
    common::detail::json::write(obj, "totalTransferedAmount", v.total_transfered_amount);
    common::detail::json::write(obj, "totalServiceChargeAmount", v.total_service_charge_amount);
    common::detail::json::write(obj, "transId", v.trans_id);
    common::detail::json::write(obj, "userAssetDribbletDetails", v.user_asset_dribblet_details);
}

} // namespace binance::wallet::rest_api
