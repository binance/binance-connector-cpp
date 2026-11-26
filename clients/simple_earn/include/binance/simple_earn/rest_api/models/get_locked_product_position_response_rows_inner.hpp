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

#include <binance/simple_earn/export.hpp>

namespace binance::simple_earn::rest_api {

struct GetLockedProductPositionResponseRowsInner {
    /// Locked position ID
    std::optional<std::int64_t> position_id;
    /// Parent position ID
    std::optional<std::int64_t> parent_position_id;
    /// Locked project ID
    std::optional<std::string> project_id;
    /// Locked asset
    std::optional<std::string> asset;
    /// Locked Amount
    std::optional<std::string> amount;
    /// Subscription time
    std::optional<std::int64_t> purchase_time;
    /// Lock period(days)
    std::optional<std::string> duration;
    /// Accrue days
    std::optional<std::string> accrual_days;
    /// Earned asset
    std::optional<std::string> reward_asset;
    std::optional<std::string> apy;
    /// Earned amount
    std::optional<std::string> reward_amt;
    /// Rewards assets of extra staking type
    std::optional<std::string> extra_reward_asset;
    /// APR of extra staking type
    std::optional<std::string> extra_reward_apr;
    /// Rewards of extra staking type, distribute when order expires
    std::optional<std::string> est_extra_reward_amt;
    std::optional<std::string> boost_reward_asset;
    std::optional<std::string> boost_apr;
    std::optional<std::string> total_boost_reward_amt;
    /// Next estimated rewards payment
    std::optional<std::string> next_pay;
    /// Next rewards payment date
    std::optional<std::int64_t> next_pay_date;
    /// Payment cycle
    std::optional<std::string> pay_period;
    /// Early redemption amount
    std::optional<std::string> redeem_amount_early;
    /// Rewards accrual end date
    std::optional<std::int64_t> rewards_end_date;
    /// Redemption arrival time
    std::optional<std::int64_t> deliver_date;
    /// Redemption interval
    std::optional<std::string> redeem_period;
    /// Amount under redemption
    std::optional<std::string> redeeming_amt;
    /// Redeem to Flexible product or Spot wallet
    std::optional<std::string> redeem_to;
    /// Arrival time of partial redemption amount of order
    std::optional<std::int64_t> partial_amt_deliver_date;
    /// When it is true, early redemption can be operated
    std::optional<bool> can_redeem_early;
    /// When it is true, fast redemption can be operated
    std::optional<bool> can_fast_redemption;
    /// When it is true, auto staking can be operated
    std::optional<bool> auto_subscribe;
    /// Order type is auto subscribe or normal
    std::optional<std::string> type;
    std::optional<std::string> status;
    std::optional<bool> can_re_stake;

    bool operator==(const GetLockedProductPositionResponseRowsInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetLockedProductPositionResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetLockedProductPositionResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetLockedProductPositionResponseRowsInner& v);

} // namespace binance::simple_earn::rest_api
