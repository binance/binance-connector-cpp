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

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data_assets_inner.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data_balances_inner.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data_position_inner.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data_user_assets_inner.hpp>

namespace binance::wallet::rest_api {

struct DailyAccountSnapshotResponseSnapshotVosInnerData {
    std::optional<std::vector<DailyAccountSnapshotResponseSnapshotVosInnerDataBalancesInner>>
        balances;
    std::optional<std::string> total_asset_of_btc;
    std::optional<std::string> margin_level;
    std::optional<std::string> total_liability_of_btc;
    std::optional<std::string> total_net_asset_of_btc;
    std::optional<std::vector<DailyAccountSnapshotResponseSnapshotVosInnerDataUserAssetsInner>>
        user_assets;
    std::optional<std::vector<DailyAccountSnapshotResponseSnapshotVosInnerDataAssetsInner>> assets;
    std::optional<std::vector<DailyAccountSnapshotResponseSnapshotVosInnerDataPositionInner>>
        position;

    bool
    operator==(const DailyAccountSnapshotResponseSnapshotVosInnerData& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DailyAccountSnapshotResponseSnapshotVosInnerData
tag_invoke(boost::json::value_to_tag<DailyAccountSnapshotResponseSnapshotVosInnerData> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DailyAccountSnapshotResponseSnapshotVosInnerData& v);

} // namespace binance::wallet::rest_api
