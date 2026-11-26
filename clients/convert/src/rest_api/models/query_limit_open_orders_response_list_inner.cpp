//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/convert/rest_api/models/query_limit_open_orders_response_list_inner.hpp>

namespace binance::convert::rest_api {

QueryLimitOpenOrdersResponseListInner
tag_invoke(boost::json::value_to_tag<QueryLimitOpenOrdersResponseListInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryLimitOpenOrdersResponseListInner");
    QueryLimitOpenOrdersResponseListInner out;
    common::detail::json::read(obj, "quoteId", out.quote_id);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "orderStatus", out.order_status);
    common::detail::json::read(obj, "fromAsset", out.from_asset);
    common::detail::json::read(obj, "fromAmount", out.from_amount);
    common::detail::json::read(obj, "toAsset", out.to_asset);
    common::detail::json::read(obj, "toAmount", out.to_amount);
    common::detail::json::read(obj, "ratio", out.ratio);
    common::detail::json::read(obj, "inverseRatio", out.inverse_ratio);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "expiredTimestamp", out.expired_timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryLimitOpenOrdersResponseListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "quoteId", v.quote_id);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "orderStatus", v.order_status);
    common::detail::json::write(obj, "fromAsset", v.from_asset);
    common::detail::json::write(obj, "fromAmount", v.from_amount);
    common::detail::json::write(obj, "toAsset", v.to_asset);
    common::detail::json::write(obj, "toAmount", v.to_amount);
    common::detail::json::write(obj, "ratio", v.ratio);
    common::detail::json::write(obj, "inverseRatio", v.inverse_ratio);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "expiredTimestamp", v.expired_timestamp);
}

} // namespace binance::convert::rest_api
