//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/dust_convertible_assets_response.hpp>

namespace binance::wallet::rest_api {

DustConvertibleAssetsResponse
tag_invoke(boost::json::value_to_tag<DustConvertibleAssetsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "DustConvertibleAssetsResponse");
    DustConvertibleAssetsResponse out;
    common::detail::json::read(obj, "dribbletPercentage", out.dribblet_percentage);
    common::detail::json::read(obj, "totalTransferQuotaAssetAmount",
                               out.total_transfer_quota_asset_amount);
    common::detail::json::read(obj, "totalTransferTargetAssetAmount",
                               out.total_transfer_target_asset_amount);
    common::detail::json::read(obj, "dribbletBase", out.dribblet_base);
    common::detail::json::read(obj, "details", out.details);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DustConvertibleAssetsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "dribbletPercentage", v.dribblet_percentage);
    common::detail::json::write(obj, "totalTransferQuotaAssetAmount",
                                v.total_transfer_quota_asset_amount);
    common::detail::json::write(obj, "totalTransferTargetAssetAmount",
                                v.total_transfer_target_asset_amount);
    common::detail::json::write(obj, "dribbletBase", v.dribblet_base);
    common::detail::json::write(obj, "details", v.details);
}

} // namespace binance::wallet::rest_api
