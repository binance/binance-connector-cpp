//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_assets_asset_management_response_balances_inner.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountAssetsAssetManagementResponseBalancesInner tag_invoke(
    boost::json::value_to_tag<QuerySubAccountAssetsAssetManagementResponseBalancesInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QuerySubAccountAssetsAssetManagementResponseBalancesInner");
    QuerySubAccountAssetsAssetManagementResponseBalancesInner out;
    common::detail::json::read(obj, "freeze", out.freeze);
    common::detail::json::read(obj, "withdrawing", out.withdrawing);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "free", out.free);
    common::detail::json::read(obj, "locked", out.locked);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountAssetsAssetManagementResponseBalancesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "freeze", v.freeze);
    common::detail::json::write(obj, "withdrawing", v.withdrawing);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "free", v.free);
    common::detail::json::write(obj, "locked", v.locked);
}

} // namespace binance::sub_account::rest_api
