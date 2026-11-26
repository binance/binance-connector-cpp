//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rewards_history_response.hpp>

namespace binance::staking::rest_api {

GetWbethRewardsHistoryResponse
tag_invoke(boost::json::value_to_tag<GetWbethRewardsHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetWbethRewardsHistoryResponse");
    GetWbethRewardsHistoryResponse out;
    common::detail::json::read(obj, "estRewardsInETH", out.est_rewards_in_eth);
    common::detail::json::read(obj, "rows", out.rows);
    common::detail::json::read(obj, "total", out.total);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetWbethRewardsHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "estRewardsInETH", v.est_rewards_in_eth);
    common::detail::json::write(obj, "rows", v.rows);
    common::detail::json::write(obj, "total", v.total);
}

} // namespace binance::staking::rest_api
