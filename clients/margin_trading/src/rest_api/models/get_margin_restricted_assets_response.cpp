//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_margin_restricted_assets_response.hpp>

namespace binance::margin_trading::rest_api {

GetMarginRestrictedAssetsResponse
tag_invoke(boost::json::value_to_tag<GetMarginRestrictedAssetsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetMarginRestrictedAssetsResponse");
    GetMarginRestrictedAssetsResponse out;
    common::detail::json::read(obj, "openLongRestrictedAsset", out.open_long_restricted_asset);
    common::detail::json::read(obj, "maxCollateralExceededAsset",
                               out.max_collateral_exceeded_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetMarginRestrictedAssetsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "openLongRestrictedAsset", v.open_long_restricted_asset);
    common::detail::json::write(obj, "maxCollateralExceededAsset", v.max_collateral_exceeded_asset);
}

} // namespace binance::margin_trading::rest_api
