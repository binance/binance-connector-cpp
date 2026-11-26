//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_assets_asset_management_response.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountAssetsAssetManagementResponse
tag_invoke(boost::json::value_to_tag<QuerySubAccountAssetsAssetManagementResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QuerySubAccountAssetsAssetManagementResponse");
    QuerySubAccountAssetsAssetManagementResponse out;
    common::detail::json::read(obj, "balances", out.balances);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountAssetsAssetManagementResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "balances", v.balances);
}

} // namespace binance::sub_account::rest_api
