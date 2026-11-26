//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_list_response_rows_inner_quota.hpp>

namespace binance::staking::rest_api {

GetOnChainYieldsLockedProductListResponseRowsInnerQuota tag_invoke(
    boost::json::value_to_tag<GetOnChainYieldsLockedProductListResponseRowsInnerQuota> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetOnChainYieldsLockedProductListResponseRowsInnerQuota");
    GetOnChainYieldsLockedProductListResponseRowsInnerQuota out;
    common::detail::json::read(obj, "totalPersonalQuota", out.total_personal_quota);
    common::detail::json::read(obj, "minimum", out.minimum);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOnChainYieldsLockedProductListResponseRowsInnerQuota& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalPersonalQuota", v.total_personal_quota);
    common::detail::json::write(obj, "minimum", v.minimum);
}

} // namespace binance::staking::rest_api
