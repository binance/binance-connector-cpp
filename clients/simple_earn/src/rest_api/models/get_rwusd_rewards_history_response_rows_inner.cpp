//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_rewards_history_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetRwusdRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetRwusdRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetRwusdRewardsHistoryResponseRowsInner");
    GetRwusdRewardsHistoryResponseRowsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "rewardsAmount", out.rewards_amount);
    common::detail::json::read(obj, "rwusdPosition", out.rwusd_position);
    common::detail::json::read(obj, "annualPercentageRate", out.annual_percentage_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetRwusdRewardsHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "rewardsAmount", v.rewards_amount);
    common::detail::json::write(obj, "rwusdPosition", v.rwusd_position);
    common::detail::json::write(obj, "annualPercentageRate", v.annual_percentage_rate);
}

} // namespace binance::simple_earn::rest_api
