//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_product_list_response.hpp>

namespace binance::staking::rest_api {

GetSoftStakingProductListResponse
tag_invoke(boost::json::value_to_tag<GetSoftStakingProductListResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetSoftStakingProductListResponse");
    GetSoftStakingProductListResponse out;
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "totalRewardsUsdt", out.total_rewards_usdt);
    common::detail::json::read(obj, "rows", out.rows);
    common::detail::json::read(obj, "total", out.total);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSoftStakingProductListResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "totalRewardsUsdt", v.total_rewards_usdt);
    common::detail::json::write(obj, "rows", v.rows);
    common::detail::json::write(obj, "total", v.total);
}

} // namespace binance::staking::rest_api
