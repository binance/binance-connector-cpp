//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_unclaimed_rewards_response_inner.hpp>

namespace binance::staking::rest_api {

GetUnclaimedRewardsResponseInner
tag_invoke(boost::json::value_to_tag<GetUnclaimedRewardsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetUnclaimedRewardsResponseInner");
    GetUnclaimedRewardsResponseInner out;
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "rewardsAsset", out.rewards_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetUnclaimedRewardsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "rewardsAsset", v.rewards_asset);
}

} // namespace binance::staking::rest_api
