//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_boost_rewards_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetBoostRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetBoostRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetBoostRewardsHistoryResponseRowsInner");
    GetBoostRewardsHistoryResponseRowsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "token", out.token);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "bnsolHolding", out.bnsol_holding);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBoostRewardsHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "token", v.token);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "bnsolHolding", v.bnsol_holding);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::staking::rest_api
