//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_subscription_record_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner tag_invoke(
    boost::json::value_to_tag<GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner");
    GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner out;
    common::detail::json::read(obj, "positionId", out.position_id);
    common::detail::json::read(obj, "purchaseId", out.purchase_id);
    common::detail::json::read(obj, "projectId", out.project_id);
    common::detail::json::read(obj, "clientId", out.client_id);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "lockPeriod", out.lock_period);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "sourceAccount", out.source_account);
    common::detail::json::read(obj, "amtFromSpot", out.amt_from_spot);
    common::detail::json::read(obj, "amtFromFunding", out.amt_from_funding);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "positionId", v.position_id);
    common::detail::json::write(obj, "purchaseId", v.purchase_id);
    common::detail::json::write(obj, "projectId", v.project_id);
    common::detail::json::write(obj, "clientId", v.client_id);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "lockPeriod", v.lock_period);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "sourceAccount", v.source_account);
    common::detail::json::write(obj, "amtFromSpot", v.amt_from_spot);
    common::detail::json::write(obj, "amtFromFunding", v.amt_from_funding);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::staking::rest_api
