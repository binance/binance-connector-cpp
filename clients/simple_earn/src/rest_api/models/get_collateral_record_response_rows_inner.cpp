//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_collateral_record_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetCollateralRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetCollateralRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetCollateralRecordResponseRowsInner");
    GetCollateralRecordResponseRowsInner out;
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "productId", out.product_id);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "productName", out.product_name);
    common::detail::json::read(obj, "orderId", out.order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetCollateralRecordResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "productId", v.product_id);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "productName", v.product_name);
    common::detail::json::write(obj, "orderId", v.order_id);
}

} // namespace binance::simple_earn::rest_api
