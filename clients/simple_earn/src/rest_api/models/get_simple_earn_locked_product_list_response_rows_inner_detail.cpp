//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_locked_product_list_response_rows_inner_detail.hpp>

namespace binance::simple_earn::rest_api {

GetSimpleEarnLockedProductListResponseRowsInnerDetail
tag_invoke(boost::json::value_to_tag<GetSimpleEarnLockedProductListResponseRowsInnerDetail> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetSimpleEarnLockedProductListResponseRowsInnerDetail");
    GetSimpleEarnLockedProductListResponseRowsInnerDetail out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "rewardAsset", out.reward_asset);
    common::detail::json::read(obj, "duration", out.duration);
    common::detail::json::read(obj, "renewable", out.renewable);
    common::detail::json::read(obj, "isSoldOut", out.is_sold_out);
    common::detail::json::read(obj, "apr", out.apr);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "subscriptionStartTime", out.subscription_start_time);
    common::detail::json::read(obj, "extraRewardAsset", out.extra_reward_asset);
    common::detail::json::read(obj, "extraRewardAPR", out.extra_reward_apr);
    common::detail::json::read(obj, "boostRewardAsset", out.boost_reward_asset);
    common::detail::json::read(obj, "boostApr", out.boost_apr);
    common::detail::json::read(obj, "boostEndTime", out.boost_end_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSimpleEarnLockedProductListResponseRowsInnerDetail& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "rewardAsset", v.reward_asset);
    common::detail::json::write(obj, "duration", v.duration);
    common::detail::json::write(obj, "renewable", v.renewable);
    common::detail::json::write(obj, "isSoldOut", v.is_sold_out);
    common::detail::json::write(obj, "apr", v.apr);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "subscriptionStartTime", v.subscription_start_time);
    common::detail::json::write(obj, "extraRewardAsset", v.extra_reward_asset);
    common::detail::json::write(obj, "extraRewardAPR", v.extra_reward_apr);
    common::detail::json::write(obj, "boostRewardAsset", v.boost_reward_asset);
    common::detail::json::write(obj, "boostApr", v.boost_apr);
    common::detail::json::write(obj, "boostEndTime", v.boost_end_time);
}

} // namespace binance::simple_earn::rest_api
