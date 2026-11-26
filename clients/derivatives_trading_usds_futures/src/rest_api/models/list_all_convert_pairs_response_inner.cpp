//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/list_all_convert_pairs_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

ListAllConvertPairsResponseInner
tag_invoke(boost::json::value_to_tag<ListAllConvertPairsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ListAllConvertPairsResponseInner");
    ListAllConvertPairsResponseInner out;
    common::detail::json::read(obj, "fromAsset", out.from_asset);
    common::detail::json::read(obj, "toAsset", out.to_asset);
    common::detail::json::read(obj, "fromAssetMinAmount", out.from_asset_min_amount);
    common::detail::json::read(obj, "fromAssetMaxAmount", out.from_asset_max_amount);
    common::detail::json::read(obj, "toAssetMinAmount", out.to_asset_min_amount);
    common::detail::json::read(obj, "toAssetMaxAmount", out.to_asset_max_amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ListAllConvertPairsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "fromAsset", v.from_asset);
    common::detail::json::write(obj, "toAsset", v.to_asset);
    common::detail::json::write(obj, "fromAssetMinAmount", v.from_asset_min_amount);
    common::detail::json::write(obj, "fromAssetMaxAmount", v.from_asset_max_amount);
    common::detail::json::write(obj, "toAssetMinAmount", v.to_asset_min_amount);
    common::detail::json::write(obj, "toAssetMaxAmount", v.to_asset_max_amount);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
