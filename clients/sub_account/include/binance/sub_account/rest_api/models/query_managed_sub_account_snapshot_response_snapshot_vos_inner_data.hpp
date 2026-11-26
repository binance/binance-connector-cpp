//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response_snapshot_vos_inner_data_assets_inner.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response_snapshot_vos_inner_data_balances_inner.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response_snapshot_vos_inner_data_position_inner.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response_snapshot_vos_inner_data_user_assets_inner.hpp>

namespace binance::sub_account::rest_api {

struct QueryManagedSubAccountSnapshotResponseSnapshotVosInnerData {
    std::optional<
        std::vector<QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner>>
        balances;
    std::optional<std::string> total_asset_of_btc;
    std::optional<std::string> margin_level;
    std::optional<std::string> total_liability_of_btc;
    std::optional<std::string> total_net_asset_of_btc;
    std::optional<
        std::vector<QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataUserAssetsInner>>
        user_assets;
    std::optional<
        std::vector<QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataAssetsInner>>
        assets;
    std::optional<
        std::vector<QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner>>
        position;

    bool operator==(const QueryManagedSubAccountSnapshotResponseSnapshotVosInnerData& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountSnapshotResponseSnapshotVosInnerData tag_invoke(
    boost::json::value_to_tag<QueryManagedSubAccountSnapshotResponseSnapshotVosInnerData> /*tag*/,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountSnapshotResponseSnapshotVosInnerData& v);

} // namespace binance::sub_account::rest_api
