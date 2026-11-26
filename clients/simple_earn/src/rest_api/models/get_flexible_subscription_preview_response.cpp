//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_subscription_preview_response.hpp>

namespace binance::simple_earn::rest_api {

GetFlexibleSubscriptionPreviewResponse
tag_invoke(boost::json::value_to_tag<GetFlexibleSubscriptionPreviewResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetFlexibleSubscriptionPreviewResponse");
    GetFlexibleSubscriptionPreviewResponse out;
    common::detail::json::read(obj, "totalAmount", out.total_amount);
    common::detail::json::read(obj, "rewardAsset", out.reward_asset);
    common::detail::json::read(obj, "airDropAsset", out.air_drop_asset);
    common::detail::json::read(obj, "estDailyBonusRewards", out.est_daily_bonus_rewards);
    common::detail::json::read(obj, "estDailyRealTimeRewards", out.est_daily_real_time_rewards);
    common::detail::json::read(obj, "estDailyAirdropRewards", out.est_daily_airdrop_rewards);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleSubscriptionPreviewResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalAmount", v.total_amount);
    common::detail::json::write(obj, "rewardAsset", v.reward_asset);
    common::detail::json::write(obj, "airDropAsset", v.air_drop_asset);
    common::detail::json::write(obj, "estDailyBonusRewards", v.est_daily_bonus_rewards);
    common::detail::json::write(obj, "estDailyRealTimeRewards", v.est_daily_real_time_rewards);
    common::detail::json::write(obj, "estDailyAirdropRewards", v.est_daily_airdrop_rewards);
}

} // namespace binance::simple_earn::rest_api
