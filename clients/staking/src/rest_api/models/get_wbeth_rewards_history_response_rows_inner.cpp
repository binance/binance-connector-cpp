//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rewards_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetWbethRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetWbethRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetWbethRewardsHistoryResponseRowsInner");
    GetWbethRewardsHistoryResponseRowsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "amountInETH", out.amount_in_eth);
    common::detail::json::read(obj, "holding", out.holding);
    common::detail::json::read(obj, "holdingInETH", out.holding_in_eth);
    common::detail::json::read(obj, "annualPercentageRate", out.annual_percentage_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetWbethRewardsHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "amountInETH", v.amount_in_eth);
    common::detail::json::write(obj, "holding", v.holding);
    common::detail::json::write(obj, "holdingInETH", v.holding_in_eth);
    common::detail::json::write(obj, "annualPercentageRate", v.annual_percentage_rate);
}

} // namespace binance::staking::rest_api
