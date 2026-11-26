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

#include <binance/staking/export.hpp>

namespace binance::staking::rest_api {

struct GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner {
    std::optional<std::string> position_id;
    std::optional<std::string> purchase_id;
    std::optional<std::string> project_id;
    std::optional<std::string> client_id;
    std::optional<std::int64_t> time;
    std::optional<std::string> asset;
    std::optional<std::string> amount;
    std::optional<std::string> lock_period;
    /// NORMAL for normal staking, AUTO for auto-subscription order
    std::optional<std::string> type;
    /// SPOT, FUNDING, SPOTANDFUNDING
    std::optional<std::string> source_account;
    /// Display if sourceAccount is SPOTANDFUNDING
    std::optional<std::string> amt_from_spot;
    /// Display if sourceAccount is SPOTANDFUNDING
    std::optional<std::string> amt_from_funding;
    /// PURCHASING/SUCCESS/FAILED
    std::optional<std::string> status;

    bool operator==(
        const GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner tag_invoke(
    boost::json::value_to_tag<GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_STAKING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner& v);

} // namespace binance::staking::rest_api
