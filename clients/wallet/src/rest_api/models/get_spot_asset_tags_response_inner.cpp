//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_spot_asset_tags_response_inner.hpp>

namespace binance::wallet::rest_api {

GetSpotAssetTagsResponseInner
tag_invoke(boost::json::value_to_tag<GetSpotAssetTagsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetSpotAssetTagsResponseInner");
    GetSpotAssetTagsResponseInner out;
    common::detail::json::read(obj, "assetCode", out.asset_code);
    common::detail::json::read(obj, "assetName", out.asset_name);
    common::detail::json::read(obj, "trading", out.trading);
    common::detail::json::read(obj, "tags", out.tags);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSpotAssetTagsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "assetCode", v.asset_code);
    common::detail::json::write(obj, "assetName", v.asset_name);
    common::detail::json::write(obj, "trading", v.trading);
    common::detail::json::write(obj, "tags", v.tags);
}

} // namespace binance::wallet::rest_api
