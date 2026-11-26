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

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response_snapshot_vos_inner_data.hpp>

namespace binance::sub_account::rest_api {

struct QueryManagedSubAccountSnapshotResponseSnapshotVosInner {
    std::optional<QueryManagedSubAccountSnapshotResponseSnapshotVosInnerData> data;
    std::optional<std::string> type;
    std::optional<std::int64_t> update_time;

    bool operator==(const QueryManagedSubAccountSnapshotResponseSnapshotVosInner& /*other*/) const =
        default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountSnapshotResponseSnapshotVosInner tag_invoke(
    boost::json::value_to_tag<QueryManagedSubAccountSnapshotResponseSnapshotVosInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountSnapshotResponseSnapshotVosInner& v);

} // namespace binance::sub_account::rest_api
