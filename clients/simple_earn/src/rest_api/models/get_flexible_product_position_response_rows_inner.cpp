//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_product_position_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetFlexibleProductPositionResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleProductPositionResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleProductPositionResponseRowsInner");
    GetFlexibleProductPositionResponseRowsInner out;
    common::detail::json::read(obj, "totalAmount", out.total_amount);
    common::detail::json::read(obj, "tierAnnualPercentageRate", out.tier_annual_percentage_rate);
    common::detail::json::read(obj, "latestAnnualPercentageRate",
                               out.latest_annual_percentage_rate);
    common::detail::json::read(obj, "yesterdayAirdropPercentageRate",
                               out.yesterday_airdrop_percentage_rate);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "airDropAsset", out.air_drop_asset);
    common::detail::json::read(obj, "canRedeem", out.can_redeem);
    common::detail::json::read(obj, "collateralAmount", out.collateral_amount);
    common::detail::json::read(obj, "productId", out.product_id);
    common::detail::json::read(obj, "yesterdayRealTimeRewards", out.yesterday_real_time_rewards);
    common::detail::json::read(obj, "cumulativeBonusRewards", out.cumulative_bonus_rewards);
    common::detail::json::read(obj, "cumulativeRealTimeRewards", out.cumulative_real_time_rewards);
    common::detail::json::read(obj, "cumulativeTotalRewards", out.cumulative_total_rewards);
    common::detail::json::read(obj, "autoSubscribe", out.auto_subscribe);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleProductPositionResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalAmount", v.total_amount);
    common::detail::json::write(obj, "tierAnnualPercentageRate", v.tier_annual_percentage_rate);
    common::detail::json::write(obj, "latestAnnualPercentageRate", v.latest_annual_percentage_rate);
    common::detail::json::write(obj, "yesterdayAirdropPercentageRate",
                                v.yesterday_airdrop_percentage_rate);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "airDropAsset", v.air_drop_asset);
    common::detail::json::write(obj, "canRedeem", v.can_redeem);
    common::detail::json::write(obj, "collateralAmount", v.collateral_amount);
    common::detail::json::write(obj, "productId", v.product_id);
    common::detail::json::write(obj, "yesterdayRealTimeRewards", v.yesterday_real_time_rewards);
    common::detail::json::write(obj, "cumulativeBonusRewards", v.cumulative_bonus_rewards);
    common::detail::json::write(obj, "cumulativeRealTimeRewards", v.cumulative_real_time_rewards);
    common::detail::json::write(obj, "cumulativeTotalRewards", v.cumulative_total_rewards);
    common::detail::json::write(obj, "autoSubscribe", v.auto_subscribe);
}

} // namespace binance::simple_earn::rest_api
