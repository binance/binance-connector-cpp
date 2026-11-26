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

struct DailyAccountSnapshotResponseSnapshotVosInnerDataPositionInner {
    std::optional<std::string> entry_price;
    std::optional<std::string> mark_price;
    std::optional<std::string> position_amt;
    std::optional<std::string> symbol;
    /// Only show the value at the time of opening the position
    std::optional<std::string> un_realized_profit;

    bool operator==(const DailyAccountSnapshotResponseSnapshotVosInnerDataPositionInner& /*other*/)
        const = default;
};

BINANCE_WALLET_EXPORT DailyAccountSnapshotResponseSnapshotVosInnerDataPositionInner
tag_invoke(boost::json::value_to_tag<
               DailyAccountSnapshotResponseSnapshotVosInnerDataPositionInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const DailyAccountSnapshotResponseSnapshotVosInnerDataPositionInner& v);

} // namespace binance::wallet::rest_api
