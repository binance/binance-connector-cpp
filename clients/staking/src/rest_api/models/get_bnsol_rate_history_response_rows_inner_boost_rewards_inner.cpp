//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_bnsol_rate_history_response_rows_inner_boost_rewards_inner.hpp>

namespace binance::staking::rest_api {

GetBnsolRateHistoryResponseRowsInnerBoostRewardsInner
tag_invoke(boost::json::value_to_tag<GetBnsolRateHistoryResponseRowsInnerBoostRewardsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetBnsolRateHistoryResponseRowsInnerBoostRewardsInner");
    GetBnsolRateHistoryResponseRowsInnerBoostRewardsInner out;
    common::detail::json::read(obj, "boostAPR", out.boost_apr);
    common::detail::json::read(obj, "rewardsAsset", out.rewards_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBnsolRateHistoryResponseRowsInnerBoostRewardsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "boostAPR", v.boost_apr);
    common::detail::json::write(obj, "rewardsAsset", v.rewards_asset);
}

} // namespace binance::staking::rest_api
