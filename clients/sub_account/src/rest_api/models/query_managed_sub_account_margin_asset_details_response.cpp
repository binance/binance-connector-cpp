//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_margin_asset_details_response.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountMarginAssetDetailsResponse
tag_invoke(boost::json::value_to_tag<QueryManagedSubAccountMarginAssetDetailsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryManagedSubAccountMarginAssetDetailsResponse");
    QueryManagedSubAccountMarginAssetDetailsResponse out;
    common::detail::json::read(obj, "marginLevel", out.margin_level);
    common::detail::json::read(obj, "totalAssetOfBtc", out.total_asset_of_btc);
    common::detail::json::read(obj, "totalLiabilityOfBtc", out.total_liability_of_btc);
    common::detail::json::read(obj, "totalNetAssetOfBtc", out.total_net_asset_of_btc);
    common::detail::json::read(obj, "userAssets", out.user_assets);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountMarginAssetDetailsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "marginLevel", v.margin_level);
    common::detail::json::write(obj, "totalAssetOfBtc", v.total_asset_of_btc);
    common::detail::json::write(obj, "totalLiabilityOfBtc", v.total_liability_of_btc);
    common::detail::json::write(obj, "totalNetAssetOfBtc", v.total_net_asset_of_btc);
    common::detail::json::write(obj, "userAssets", v.user_assets);
}

} // namespace binance::sub_account::rest_api
