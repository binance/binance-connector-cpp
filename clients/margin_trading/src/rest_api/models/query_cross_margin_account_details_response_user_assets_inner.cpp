//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_cross_margin_account_details_response_user_assets_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryCrossMarginAccountDetailsResponseUserAssetsInner
tag_invoke(boost::json::value_to_tag<QueryCrossMarginAccountDetailsResponseUserAssetsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryCrossMarginAccountDetailsResponseUserAssetsInner");
    QueryCrossMarginAccountDetailsResponseUserAssetsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "borrowed", out.borrowed);
    common::detail::json::read(obj, "free", out.free);
    common::detail::json::read(obj, "interest", out.interest);
    common::detail::json::read(obj, "locked", out.locked);
    common::detail::json::read(obj, "netAsset", out.net_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryCrossMarginAccountDetailsResponseUserAssetsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "borrowed", v.borrowed);
    common::detail::json::write(obj, "free", v.free);
    common::detail::json::write(obj, "interest", v.interest);
    common::detail::json::write(obj, "locked", v.locked);
    common::detail::json::write(obj, "netAsset", v.net_asset);
}

} // namespace binance::margin_trading::rest_api
