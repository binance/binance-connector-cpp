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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner.hpp>

namespace binance::wallet::rest_api {

struct DailyAccountSnapshotResponse {
    /// 200 for success; others are error codes
    std::optional<std::int64_t> code;
    /// error message
    std::optional<std::string> msg;
    std::optional<std::vector<DailyAccountSnapshotResponseSnapshotVosInner>> snapshot_vos;

    bool operator==(const DailyAccountSnapshotResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DailyAccountSnapshotResponse tag_invoke(
    boost::json::value_to_tag<DailyAccountSnapshotResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DailyAccountSnapshotResponse& v);

} // namespace binance::wallet::rest_api
