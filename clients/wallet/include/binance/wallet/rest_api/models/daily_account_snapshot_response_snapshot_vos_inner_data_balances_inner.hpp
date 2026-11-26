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

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct DailyAccountSnapshotResponseSnapshotVosInnerDataBalancesInner {
    std::optional<std::string> asset;
    std::optional<std::string> free;
    std::optional<std::string> locked;

    bool operator==(const DailyAccountSnapshotResponseSnapshotVosInnerDataBalancesInner& /*other*/)
        const = default;
};

BINANCE_WALLET_EXPORT DailyAccountSnapshotResponseSnapshotVosInnerDataBalancesInner
tag_invoke(boost::json::value_to_tag<
               DailyAccountSnapshotResponseSnapshotVosInnerDataBalancesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const DailyAccountSnapshotResponseSnapshotVosInnerDataBalancesInner& v);

} // namespace binance::wallet::rest_api
