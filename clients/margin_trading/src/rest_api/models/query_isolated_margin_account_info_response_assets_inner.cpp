//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_account_info_response_assets_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryIsolatedMarginAccountInfoResponseAssetsInner
tag_invoke(boost::json::value_to_tag<QueryIsolatedMarginAccountInfoResponseAssetsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryIsolatedMarginAccountInfoResponseAssetsInner");
    QueryIsolatedMarginAccountInfoResponseAssetsInner out;
    common::detail::json::read(obj, "baseAsset", out.base_asset);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "isolatedCreated", out.isolated_created);
    common::detail::json::read(obj, "enabled", out.enabled);
    common::detail::json::read(obj, "marginLevel", out.margin_level);
    common::detail::json::read(obj, "marginLevelStatus", out.margin_level_status);
    common::detail::json::read(obj, "marginRatio", out.margin_ratio);
    common::detail::json::read(obj, "indexPrice", out.index_price);
    common::detail::json::read(obj, "liquidatePrice", out.liquidate_price);
    common::detail::json::read(obj, "liquidateRate", out.liquidate_rate);
    common::detail::json::read(obj, "tradeEnabled", out.trade_enabled);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryIsolatedMarginAccountInfoResponseAssetsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "baseAsset", v.base_asset);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "isolatedCreated", v.isolated_created);
    common::detail::json::write(obj, "enabled", v.enabled);
    common::detail::json::write(obj, "marginLevel", v.margin_level);
    common::detail::json::write(obj, "marginLevelStatus", v.margin_level_status);
    common::detail::json::write(obj, "marginRatio", v.margin_ratio);
    common::detail::json::write(obj, "indexPrice", v.index_price);
    common::detail::json::write(obj, "liquidatePrice", v.liquidate_price);
    common::detail::json::write(obj, "liquidateRate", v.liquidate_rate);
    common::detail::json::write(obj, "tradeEnabled", v.trade_enabled);
}

} // namespace binance::margin_trading::rest_api
