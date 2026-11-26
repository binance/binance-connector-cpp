//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_futures_asset_details_response_snapshot_vos_inner_data_assets_inner.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_futures_asset_details_response_snapshot_vos_inner_data_position_inner.hpp>

namespace binance::sub_account::rest_api {

struct QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData {
    std::optional<std::vector<
        QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerDataAssetsInner>>
        assets;
    std::optional<std::vector<
        QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerDataPositionInner>>
        position;

    bool operator==(
        const QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerData& v);

} // namespace binance::sub_account::rest_api
