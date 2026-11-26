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

struct GetOnChainYieldsLockedRedemptionRecordResponseRowsInner {
    std::optional<std::string> position_id;
    std::optional<std::int64_t> redeem_id;
    std::optional<std::int64_t> time;
    std::optional<std::string> asset;
    std::optional<std::string> lock_period;
    std::optional<std::string> amount;
    std::optional<std::string> original_amount;
    /// NORMAL for normal maturity redemption, EARLY for early redemption, CONVERT for redeem to
    /// simple earn flexible
    std::optional<std::string> type;
    /// Redemption date
    std::optional<std::string> deliver_date;
    /// Loss of profit on early redemption
    std::optional<std::string> loss_amount;
    std::optional<bool> is_complete;
    std::optional<std::string> reward_asset;
    std::optional<std::string> reward_amt;
    /// CREATED/PAID
    std::optional<std::string> status;

    bool operator==(
        const GetOnChainYieldsLockedRedemptionRecordResponseRowsInner& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedRedemptionRecordResponseRowsInner tag_invoke(
    boost::json::value_to_tag<GetOnChainYieldsLockedRedemptionRecordResponseRowsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_STAKING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetOnChainYieldsLockedRedemptionRecordResponseRowsInner& v);

} // namespace binance::staking::rest_api
