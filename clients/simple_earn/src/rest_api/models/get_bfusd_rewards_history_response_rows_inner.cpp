//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_rewards_history_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetBfusdRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetBfusdRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetBfusdRewardsHistoryResponseRowsInner");
    GetBfusdRewardsHistoryResponseRowsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "rewardAsset", out.reward_asset);
    common::detail::json::read(obj, "rewardsAmount", out.rewards_amount);
    common::detail::json::read(obj, "BFUSDPosition", out.bfusd_position);
    common::detail::json::read(obj, "annualPercentageRate", out.annual_percentage_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBfusdRewardsHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "rewardAsset", v.reward_asset);
    common::detail::json::write(obj, "rewardsAmount", v.rewards_amount);
    common::detail::json::write(obj, "BFUSDPosition", v.bfusd_position);
    common::detail::json::write(obj, "annualPercentageRate", v.annual_percentage_rate);
}

} // namespace binance::simple_earn::rest_api
