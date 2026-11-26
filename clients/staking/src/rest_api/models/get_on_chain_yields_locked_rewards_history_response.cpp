//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_rewards_history_response.hpp>

namespace binance::staking::rest_api {

GetOnChainYieldsLockedRewardsHistoryResponse
tag_invoke(boost::json::value_to_tag<GetOnChainYieldsLockedRewardsHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetOnChainYieldsLockedRewardsHistoryResponse");
    GetOnChainYieldsLockedRewardsHistoryResponse out;
    common::detail::json::read(obj, "rows", out.rows);
    common::detail::json::read(obj, "total", out.total);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOnChainYieldsLockedRewardsHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "rows", v.rows);
    common::detail::json::write(obj, "total", v.total);
}

} // namespace binance::staking::rest_api
