//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_position_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetOnChainYieldsLockedProductPositionResponseRowsInner tag_invoke(
    boost::json::value_to_tag<GetOnChainYieldsLockedProductPositionResponseRowsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetOnChainYieldsLockedProductPositionResponseRowsInner");
    GetOnChainYieldsLockedProductPositionResponseRowsInner out;
    common::detail::json::read(obj, "positionId", out.position_id);
    common::detail::json::read(obj, "projectId", out.project_id);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "purchaseTime", out.purchase_time);
    common::detail::json::read(obj, "duration", out.duration);
    common::detail::json::read(obj, "accrualDays", out.accrual_days);
    common::detail::json::read(obj, "rewardAsset", out.reward_asset);
    common::detail::json::read(obj, "APY", out.apy);
    common::detail::json::read(obj, "rewardAmt", out.reward_amt);
    common::detail::json::read(obj, "nextPay", out.next_pay);
    common::detail::json::read(obj, "nextPayDate", out.next_pay_date);
    common::detail::json::read(obj, "payPeriod", out.pay_period);
    common::detail::json::read(obj, "rewardsPayDate", out.rewards_pay_date);
    common::detail::json::read(obj, "rewardsEndDate", out.rewards_end_date);
    common::detail::json::read(obj, "deliverDate", out.deliver_date);
    common::detail::json::read(obj, "nextSubscriptionDate", out.next_subscription_date);
    common::detail::json::read(obj, "redeemingAmt", out.redeeming_amt);
    common::detail::json::read(obj, "redeemTo", out.redeem_to);
    common::detail::json::read(obj, "canRedeemEarly", out.can_redeem_early);
    common::detail::json::read(obj, "autoSubscribe", out.auto_subscribe);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOnChainYieldsLockedProductPositionResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "positionId", v.position_id);
    common::detail::json::write(obj, "projectId", v.project_id);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "purchaseTime", v.purchase_time);
    common::detail::json::write(obj, "duration", v.duration);
    common::detail::json::write(obj, "accrualDays", v.accrual_days);
    common::detail::json::write(obj, "rewardAsset", v.reward_asset);
    common::detail::json::write(obj, "APY", v.apy);
    common::detail::json::write(obj, "rewardAmt", v.reward_amt);
    common::detail::json::write(obj, "nextPay", v.next_pay);
    common::detail::json::write(obj, "nextPayDate", v.next_pay_date);
    common::detail::json::write(obj, "payPeriod", v.pay_period);
    common::detail::json::write(obj, "rewardsPayDate", v.rewards_pay_date);
    common::detail::json::write(obj, "rewardsEndDate", v.rewards_end_date);
    common::detail::json::write(obj, "deliverDate", v.deliver_date);
    common::detail::json::write(obj, "nextSubscriptionDate", v.next_subscription_date);
    common::detail::json::write(obj, "redeemingAmt", v.redeeming_amt);
    common::detail::json::write(obj, "redeemTo", v.redeem_to);
    common::detail::json::write(obj, "canRedeemEarly", v.can_redeem_early);
    common::detail::json::write(obj, "autoSubscribe", v.auto_subscribe);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::staking::rest_api
