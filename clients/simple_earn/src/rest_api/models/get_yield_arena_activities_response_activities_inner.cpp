//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_yield_arena_activities_response_activities_inner.hpp>

namespace binance::simple_earn::rest_api {

GetYieldArenaActivitiesResponseActivitiesInner
tag_invoke(boost::json::value_to_tag<GetYieldArenaActivitiesResponseActivitiesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetYieldArenaActivitiesResponseActivitiesInner");
    GetYieldArenaActivitiesResponseActivitiesInner out;
    common::detail::json::read(obj, "activityId", out.activity_id);
    common::detail::json::read(obj, "activityType", out.activity_type);
    common::detail::json::read(obj, "title", out.title);
    common::detail::json::read(obj, "description", out.description);
    common::detail::json::read(obj, "rewardPoolInUsd", out.reward_pool_in_usd);
    common::detail::json::read(obj, "rewardToken", out.reward_token);
    common::detail::json::read(obj, "redirectUrl", out.redirect_url);
    common::detail::json::read(obj, "startTime", out.start_time);
    common::detail::json::read(obj, "endTime", out.end_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetYieldArenaActivitiesResponseActivitiesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "activityId", v.activity_id);
    common::detail::json::write(obj, "activityType", v.activity_type);
    common::detail::json::write(obj, "title", v.title);
    common::detail::json::write(obj, "description", v.description);
    common::detail::json::write(obj, "rewardPoolInUsd", v.reward_pool_in_usd);
    common::detail::json::write(obj, "rewardToken", v.reward_token);
    common::detail::json::write(obj, "redirectUrl", v.redirect_url);
    common::detail::json::write(obj, "startTime", v.start_time);
    common::detail::json::write(obj, "endTime", v.end_time);
}

} // namespace binance::simple_earn::rest_api
