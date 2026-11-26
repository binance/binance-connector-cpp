//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_futures_asset_details_response_snapshot_vos_inner_data.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData");
    QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData out;
    common::detail::json::read(obj, "assets", out.assets);
    common::detail::json::read(obj, "position", out.position);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "assets", v.assets);
    common::detail::json::write(obj, "position", v.position);
}

} // namespace binance::sub_account::rest_api
