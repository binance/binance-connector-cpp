//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_locked_product_list_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetSimpleEarnLockedProductListResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetSimpleEarnLockedProductListResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSimpleEarnLockedProductListResponseRowsInner");
    GetSimpleEarnLockedProductListResponseRowsInner out;
    common::detail::json::read(obj, "projectId", out.project_id);
    common::detail::json::read(obj, "detail", out.detail);
    common::detail::json::read(obj, "quota", out.quota);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSimpleEarnLockedProductListResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "projectId", v.project_id);
    common::detail::json::write(obj, "detail", v.detail);
    common::detail::json::write(obj, "quota", v.quota);
}

} // namespace binance::simple_earn::rest_api
