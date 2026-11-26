//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data.hpp>

namespace binance::wallet::rest_api {

struct DailyAccountSnapshotResponseSnapshotVosInner {
    std::optional<DailyAccountSnapshotResponseSnapshotVosInnerData> data;
    std::optional<std::string> type;
    std::optional<std::int64_t> update_time;

    bool operator==(const DailyAccountSnapshotResponseSnapshotVosInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DailyAccountSnapshotResponseSnapshotVosInner
tag_invoke(boost::json::value_to_tag<DailyAccountSnapshotResponseSnapshotVosInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DailyAccountSnapshotResponseSnapshotVosInner& v);

} // namespace binance::wallet::rest_api
