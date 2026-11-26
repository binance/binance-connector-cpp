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

struct GetOnChainYieldsLockedSubscriptionPreviewResponse {
    /// Earned asset
    std::optional<std::string> reward_asset;
    /// Earned amount total in locked period
    std::optional<std::string> total_reward_amt;
    /// Next estimated rewards payment
    std::optional<std::string> next_pay;
    /// Next rewards payment date
    std::optional<std::string> next_pay_date;
    /// Rewards payment date
    std::optional<std::string> rewards_pay_date;
    std::optional<std::string> value_date;
    /// Rewards accrual end date
    std::optional<std::string> rewards_end_date;
    /// Redemption arrival time(if auto-subscribe is true, not response this one)
    std::optional<std::string> deliver_date;
    /// Response if autoSubscribe is true
    std::optional<std::string> next_subscription_date;

    bool
    operator==(const GetOnChainYieldsLockedSubscriptionPreviewResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedSubscriptionPreviewResponse
tag_invoke(boost::json::value_to_tag<GetOnChainYieldsLockedSubscriptionPreviewResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetOnChainYieldsLockedSubscriptionPreviewResponse& v);

} // namespace binance::staking::rest_api
