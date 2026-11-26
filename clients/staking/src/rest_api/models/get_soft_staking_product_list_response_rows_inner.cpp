//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_product_list_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetSoftStakingProductListResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetSoftStakingProductListResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSoftStakingProductListResponseRowsInner");
    GetSoftStakingProductListResponseRowsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "minAmount", out.min_amount);
    common::detail::json::read(obj, "maxCap", out.max_cap);
    common::detail::json::read(obj, "apr", out.apr);
    common::detail::json::read(obj, "stakedAmount", out.staked_amount);
    common::detail::json::read(obj, "totalProfit", out.total_profit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSoftStakingProductListResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "minAmount", v.min_amount);
    common::detail::json::write(obj, "maxCap", v.max_cap);
    common::detail::json::write(obj, "apr", v.apr);
    common::detail::json::write(obj, "stakedAmount", v.staked_amount);
    common::detail::json::write(obj, "totalProfit", v.total_profit);
}

} // namespace binance::staking::rest_api
