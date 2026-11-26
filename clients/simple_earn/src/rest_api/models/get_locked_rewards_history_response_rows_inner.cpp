//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_rewards_history_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetLockedRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetLockedRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetLockedRewardsHistoryResponseRowsInner");
    GetLockedRewardsHistoryResponseRowsInner out;
    common::detail::json::read(obj, "positionId", out.position_id);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "lockPeriod", out.lock_period);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "type", out.type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetLockedRewardsHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "positionId", v.position_id);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "lockPeriod", v.lock_period);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "type", v.type);
}

} // namespace binance::simple_earn::rest_api
