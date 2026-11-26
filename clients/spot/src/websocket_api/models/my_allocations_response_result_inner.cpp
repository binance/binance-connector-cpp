//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/my_allocations_response_result_inner.hpp>

namespace binance::spot::websocket_api {

MyAllocationsResponseResultInner
tag_invoke(boost::json::value_to_tag<MyAllocationsResponseResultInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MyAllocationsResponseResultInner");
    MyAllocationsResponseResultInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "allocationId", out.allocation_id);
    common::detail::json::read(obj, "allocationType", out.allocation_type);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "orderListId", out.order_list_id);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "quoteQty", out.quote_qty);
    common::detail::json::read(obj, "commission", out.commission);
    common::detail::json::read(obj, "commissionAsset", out.commission_asset);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "isBuyer", out.is_buyer);
    common::detail::json::read(obj, "isMaker", out.is_maker);
    common::detail::json::read(obj, "isAllocator", out.is_allocator);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MyAllocationsResponseResultInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "allocationId", v.allocation_id);
    common::detail::json::write(obj, "allocationType", v.allocation_type);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "orderListId", v.order_list_id);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "quoteQty", v.quote_qty);
    common::detail::json::write(obj, "commission", v.commission);
    common::detail::json::write(obj, "commissionAsset", v.commission_asset);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "isBuyer", v.is_buyer);
    common::detail::json::write(obj, "isMaker", v.is_maker);
    common::detail::json::write(obj, "isAllocator", v.is_allocator);
}

} // namespace binance::spot::websocket_api
