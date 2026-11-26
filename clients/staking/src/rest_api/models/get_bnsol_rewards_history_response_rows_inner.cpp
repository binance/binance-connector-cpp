//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_bnsol_rewards_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetBnsolRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetBnsolRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetBnsolRewardsHistoryResponseRowsInner");
    GetBnsolRewardsHistoryResponseRowsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "amountInSOL", out.amount_in_sol);
    common::detail::json::read(obj, "holding", out.holding);
    common::detail::json::read(obj, "holdingInSOL", out.holding_in_sol);
    common::detail::json::read(obj, "annualPercentageRate", out.annual_percentage_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBnsolRewardsHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "amountInSOL", v.amount_in_sol);
    common::detail::json::write(obj, "holding", v.holding);
    common::detail::json::write(obj, "holdingInSOL", v.holding_in_sol);
    common::detail::json::write(obj, "annualPercentageRate", v.annual_percentage_rate);
}

} // namespace binance::staking::rest_api
