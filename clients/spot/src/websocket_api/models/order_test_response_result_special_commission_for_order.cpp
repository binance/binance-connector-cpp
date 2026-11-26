//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/order_test_response_result_special_commission_for_order.hpp>

namespace binance::spot::websocket_api {

OrderTestResponseResultSpecialCommissionForOrder
tag_invoke(boost::json::value_to_tag<OrderTestResponseResultSpecialCommissionForOrder> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "OrderTestResponseResultSpecialCommissionForOrder");
    OrderTestResponseResultSpecialCommissionForOrder out;
    common::detail::json::read(obj, "maker", out.maker);
    common::detail::json::read(obj, "taker", out.taker);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderTestResponseResultSpecialCommissionForOrder& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "maker", v.maker);
    common::detail::json::write(obj, "taker", v.taker);
}

} // namespace binance::spot::websocket_api
