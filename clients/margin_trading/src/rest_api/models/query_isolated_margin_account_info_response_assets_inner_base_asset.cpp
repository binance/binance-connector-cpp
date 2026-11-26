//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_account_info_response_assets_inner_base_asset.hpp>

namespace binance::margin_trading::rest_api {

QueryIsolatedMarginAccountInfoResponseAssetsInnerBaseAsset tag_invoke(
    boost::json::value_to_tag<QueryIsolatedMarginAccountInfoResponseAssetsInnerBaseAsset> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryIsolatedMarginAccountInfoResponseAssetsInnerBaseAsset");
    QueryIsolatedMarginAccountInfoResponseAssetsInnerBaseAsset out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "borrowEnabled", out.borrow_enabled);
    common::detail::json::read(obj, "borrowed", out.borrowed);
    common::detail::json::read(obj, "free", out.free);
    common::detail::json::read(obj, "interest", out.interest);
    common::detail::json::read(obj, "locked", out.locked);
    common::detail::json::read(obj, "netAsset", out.net_asset);
    common::detail::json::read(obj, "netAssetOfBtc", out.net_asset_of_btc);
    common::detail::json::read(obj, "repayEnabled", out.repay_enabled);
    common::detail::json::read(obj, "totalAsset", out.total_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryIsolatedMarginAccountInfoResponseAssetsInnerBaseAsset& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "borrowEnabled", v.borrow_enabled);
    common::detail::json::write(obj, "borrowed", v.borrowed);
    common::detail::json::write(obj, "free", v.free);
    common::detail::json::write(obj, "interest", v.interest);
    common::detail::json::write(obj, "locked", v.locked);
    common::detail::json::write(obj, "netAsset", v.net_asset);
    common::detail::json::write(obj, "netAssetOfBtc", v.net_asset_of_btc);
    common::detail::json::write(obj, "repayEnabled", v.repay_enabled);
    common::detail::json::write(obj, "totalAsset", v.total_asset);
}

} // namespace binance::margin_trading::rest_api
