//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_current_eth_staking_quota_response.hpp>

namespace binance::staking::rest_api {

GetCurrentEthStakingQuotaResponse
tag_invoke(boost::json::value_to_tag<GetCurrentEthStakingQuotaResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetCurrentEthStakingQuotaResponse");
    GetCurrentEthStakingQuotaResponse out;
    common::detail::json::read(obj, "leftStakingPersonalQuota", out.left_staking_personal_quota);
    common::detail::json::read(obj, "leftRedemptionPersonalQuota",
                               out.left_redemption_personal_quota);
    common::detail::json::read(obj, "minStakeAmount", out.min_stake_amount);
    common::detail::json::read(obj, "minRedeemAmount", out.min_redeem_amount);
    common::detail::json::read(obj, "redeemPeriod", out.redeem_period);
    common::detail::json::read(obj, "stakeable", out.stakeable);
    common::detail::json::read(obj, "redeemable", out.redeemable);
    common::detail::json::read(obj, "commissionFee", out.commission_fee);
    common::detail::json::read(obj, "calculating", out.calculating);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetCurrentEthStakingQuotaResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "leftStakingPersonalQuota", v.left_staking_personal_quota);
    common::detail::json::write(obj, "leftRedemptionPersonalQuota",
                                v.left_redemption_personal_quota);
    common::detail::json::write(obj, "minStakeAmount", v.min_stake_amount);
    common::detail::json::write(obj, "minRedeemAmount", v.min_redeem_amount);
    common::detail::json::write(obj, "redeemPeriod", v.redeem_period);
    common::detail::json::write(obj, "stakeable", v.stakeable);
    common::detail::json::write(obj, "redeemable", v.redeemable);
    common::detail::json::write(obj, "commissionFee", v.commission_fee);
    common::detail::json::write(obj, "calculating", v.calculating);
}

} // namespace binance::staking::rest_api
