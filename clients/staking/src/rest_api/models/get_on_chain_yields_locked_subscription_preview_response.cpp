//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_subscription_preview_response.hpp>

namespace binance::staking::rest_api {

GetOnChainYieldsLockedSubscriptionPreviewResponse
tag_invoke(boost::json::value_to_tag<GetOnChainYieldsLockedSubscriptionPreviewResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetOnChainYieldsLockedSubscriptionPreviewResponse");
    GetOnChainYieldsLockedSubscriptionPreviewResponse out;
    common::detail::json::read(obj, "rewardAsset", out.reward_asset);
    common::detail::json::read(obj, "totalRewardAmt", out.total_reward_amt);
    common::detail::json::read(obj, "nextPay", out.next_pay);
    common::detail::json::read(obj, "nextPayDate", out.next_pay_date);
    common::detail::json::read(obj, "rewardsPayDate", out.rewards_pay_date);
    common::detail::json::read(obj, "valueDate", out.value_date);
    common::detail::json::read(obj, "rewardsEndDate", out.rewards_end_date);
    common::detail::json::read(obj, "deliverDate", out.deliver_date);
    common::detail::json::read(obj, "nextSubscriptionDate", out.next_subscription_date);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOnChainYieldsLockedSubscriptionPreviewResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "rewardAsset", v.reward_asset);
    common::detail::json::write(obj, "totalRewardAmt", v.total_reward_amt);
    common::detail::json::write(obj, "nextPay", v.next_pay);
    common::detail::json::write(obj, "nextPayDate", v.next_pay_date);
    common::detail::json::write(obj, "rewardsPayDate", v.rewards_pay_date);
    common::detail::json::write(obj, "valueDate", v.value_date);
    common::detail::json::write(obj, "rewardsEndDate", v.rewards_end_date);
    common::detail::json::write(obj, "deliverDate", v.deliver_date);
    common::detail::json::write(obj, "nextSubscriptionDate", v.next_subscription_date);
}

} // namespace binance::staking::rest_api
