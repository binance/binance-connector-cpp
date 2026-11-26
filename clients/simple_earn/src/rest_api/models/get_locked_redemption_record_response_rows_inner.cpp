//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_redemption_record_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetLockedRedemptionRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetLockedRedemptionRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetLockedRedemptionRecordResponseRowsInner");
    GetLockedRedemptionRecordResponseRowsInner out;
    common::detail::json::read(obj, "positionId", out.position_id);
    common::detail::json::read(obj, "redeemId", out.redeem_id);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "lockPeriod", out.lock_period);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "originalAmount", out.original_amount);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "deliverDate", out.deliver_date);
    common::detail::json::read(obj, "lossAmount", out.loss_amount);
    common::detail::json::read(obj, "isComplete", out.is_complete);
    common::detail::json::read(obj, "rewardAsset", out.reward_asset);
    common::detail::json::read(obj, "rewardAmt", out.reward_amt);
    common::detail::json::read(obj, "extraRewardAsset", out.extra_reward_asset);
    common::detail::json::read(obj, "estExtraRewardAmt", out.est_extra_reward_amt);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetLockedRedemptionRecordResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "positionId", v.position_id);
    common::detail::json::write(obj, "redeemId", v.redeem_id);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "lockPeriod", v.lock_period);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "originalAmount", v.original_amount);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "deliverDate", v.deliver_date);
    common::detail::json::write(obj, "lossAmount", v.loss_amount);
    common::detail::json::write(obj, "isComplete", v.is_complete);
    common::detail::json::write(obj, "rewardAsset", v.reward_asset);
    common::detail::json::write(obj, "rewardAmt", v.reward_amt);
    common::detail::json::write(obj, "extraRewardAsset", v.extra_reward_asset);
    common::detail::json::write(obj, "estExtraRewardAmt", v.est_extra_reward_amt);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::simple_earn::rest_api
