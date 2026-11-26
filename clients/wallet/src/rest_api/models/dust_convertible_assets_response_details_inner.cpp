//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/dust_convertible_assets_response_details_inner.hpp>

namespace binance::wallet::rest_api {

DustConvertibleAssetsResponseDetailsInner
tag_invoke(boost::json::value_to_tag<DustConvertibleAssetsResponseDetailsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "DustConvertibleAssetsResponseDetailsInner");
    DustConvertibleAssetsResponseDetailsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "assetFullName", out.asset_full_name);
    common::detail::json::read(obj, "amountFree", out.amount_free);
    common::detail::json::read(obj, "exchange", out.exchange);
    common::detail::json::read(obj, "toQuotaAssetAmount", out.to_quota_asset_amount);
    common::detail::json::read(obj, "toTargetAssetAmount", out.to_target_asset_amount);
    common::detail::json::read(obj, "toTargetAssetOffExchange", out.to_target_asset_off_exchange);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DustConvertibleAssetsResponseDetailsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "assetFullName", v.asset_full_name);
    common::detail::json::write(obj, "amountFree", v.amount_free);
    common::detail::json::write(obj, "exchange", v.exchange);
    common::detail::json::write(obj, "toQuotaAssetAmount", v.to_quota_asset_amount);
    common::detail::json::write(obj, "toTargetAssetAmount", v.to_target_asset_amount);
    common::detail::json::write(obj, "toTargetAssetOffExchange", v.to_target_asset_off_exchange);
}

} // namespace binance::wallet::rest_api
