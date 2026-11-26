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

#include <binance/staking/export.hpp>

namespace binance::staking::rest_api {

struct GetOnChainYieldsLockedProductPositionResponseRowsInner {
    /// Locked position ID
    std::optional<std::string> position_id;
    /// Locked project ID
    std::optional<std::string> project_id;
    /// Locked asset
    std::optional<std::string> asset;
    /// Locked Amount
    std::optional<std::string> amount;
    /// Subscription time
    std::optional<std::string> purchase_time;
    /// Lock period(days)
    std::optional<std::string> duration;
    /// Accrue days
    std::optional<std::string> accrual_days;
    /// Earned asset
    std::optional<std::string> reward_asset;
    std::optional<std::string> apy;
    /// Earned amount
    std::optional<std::string> reward_amt;
    /// Next estimated rewards payment
    std::optional<std::string> next_pay;
    /// Next rewards payment date
    std::optional<std::string> next_pay_date;
    /// Payment cycle
    std::optional<std::string> pay_period;
    /// Rewards payment date when maturity
    std::optional<std::string> rewards_pay_date;
    /// Rewards accrual end date
    std::optional<std::string> rewards_end_date;
    /// Redemption arrival time(include early redemption or natural maturity; if auto-subscribe is
    /// on, not response this one)
    std::optional<std::string> deliver_date;
    /// Response when auto-subscribe on
    std::optional<std::string> next_subscription_date;
    /// Amount under redemption when auto-subsceibe is on but left quota is less than stake amount
    std::optional<std::string> redeeming_amt;
    /// Redeem to simple earn Flexible product or Spot wallet, "SPOT":spot wallet
    std::optional<std::string> redeem_to;
    /// When it is true, early redemption can be operated
    std::optional<bool> can_redeem_early;
    /// When it is true, auto subscribe can be operated
    std::optional<bool> auto_subscribe;
    /// AUTO：auto-subscribe order； NORMAL：normal-subscribe order
    std::optional<std::string> type;
    /// HOLDING,REDEEMING,RENEWING:auto subscribing,NEW_TRANSFERRING:Redeeming to Simple Earn
    /// flexible
    std::optional<std::string> status;

    bool operator==(const GetOnChainYieldsLockedProductPositionResponseRowsInner& /*other*/) const =
        default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedProductPositionResponseRowsInner tag_invoke(
    boost::json::value_to_tag<GetOnChainYieldsLockedProductPositionResponseRowsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_STAKING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetOnChainYieldsLockedProductPositionResponseRowsInner& v);

} // namespace binance::staking::rest_api
