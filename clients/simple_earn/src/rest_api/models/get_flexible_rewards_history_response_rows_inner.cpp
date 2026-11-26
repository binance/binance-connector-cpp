//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_rewards_history_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetFlexibleRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleRewardsHistoryResponseRowsInner");
    GetFlexibleRewardsHistoryResponseRowsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "rewards", out.rewards);
    common::detail::json::read(obj, "projectId", out.project_id);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleRewardsHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "rewards", v.rewards);
    common::detail::json::write(obj, "projectId", v.project_id);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::simple_earn::rest_api
