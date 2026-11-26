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

struct QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner {
    std::optional<std::string> entry_price;
    std::optional<std::string> mark_price;
    std::optional<std::string> position_amt;
    std::optional<std::string> symbol;
    /// Only show the value at the time of opening the position
    std::optional<std::string> un_realized_profit;

    bool operator==(
        const QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner& v);

} // namespace binance::sub_account::rest_api
