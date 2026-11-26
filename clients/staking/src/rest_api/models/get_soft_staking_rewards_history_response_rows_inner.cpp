//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_rewards_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetSoftStakingRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetSoftStakingRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSoftStakingRewardsHistoryResponseRowsInner");
    GetSoftStakingRewardsHistoryResponseRowsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "rewards", out.rewards);
    common::detail::json::read(obj, "rewardAsset", out.reward_asset);
    common::detail::json::read(obj, "avgAmount", out.avg_amount);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSoftStakingRewardsHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "rewards", v.rewards);
    common::detail::json::write(obj, "rewardAsset", v.reward_asset);
    common::detail::json::write(obj, "avgAmount", v.avg_amount);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::staking::rest_api
