//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/dustlog_response_user_asset_dribblets_inner_user_asset_dribblet_details_inner.hpp>

namespace binance::wallet::rest_api {

DustlogResponseUserAssetDribbletsInnerUserAssetDribbletDetailsInner
tag_invoke(boost::json::value_to_tag<
               DustlogResponseUserAssetDribbletsInnerUserAssetDribbletDetailsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "DustlogResponseUserAssetDribbletsInnerUserAssetDribbletDetailsInner");
    DustlogResponseUserAssetDribbletsInnerUserAssetDribbletDetailsInner out;
    common::detail::json::read(obj, "transId", out.trans_id);
    common::detail::json::read(obj, "serviceChargeAmount", out.service_charge_amount);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "operateTime", out.operate_time);
    common::detail::json::read(obj, "transferedAmount", out.transfered_amount);
    common::detail::json::read(obj, "fromAsset", out.from_asset);
    common::detail::json::read(obj, "targetAsset", out.target_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DustlogResponseUserAssetDribbletsInnerUserAssetDribbletDetailsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "transId", v.trans_id);
    common::detail::json::write(obj, "serviceChargeAmount", v.service_charge_amount);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "operateTime", v.operate_time);
    common::detail::json::write(obj, "transferedAmount", v.transfered_amount);
    common::detail::json::write(obj, "fromAsset", v.from_asset);
    common::detail::json::write(obj, "targetAsset", v.target_asset);
}

} // namespace binance::wallet::rest_api
