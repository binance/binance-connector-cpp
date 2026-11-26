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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner {
    std::optional<std::string> asset;
    std::optional<std::string> free;
    std::optional<std::string> locked;

    bool operator==(
        const QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner& v);

} // namespace binance::sub_account::rest_api
