//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_list_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetOnChainYieldsLockedProductListResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetOnChainYieldsLockedProductListResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetOnChainYieldsLockedProductListResponseRowsInner");
    GetOnChainYieldsLockedProductListResponseRowsInner out;
    common::detail::json::read(obj, "projectId", out.project_id);
    common::detail::json::read(obj, "detail", out.detail);
    common::detail::json::read(obj, "quota", out.quota);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOnChainYieldsLockedProductListResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "projectId", v.project_id);
    common::detail::json::write(obj, "detail", v.detail);
    common::detail::json::write(obj, "quota", v.quota);
}

} // namespace binance::staking::rest_api
