//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/order_test_response_standard_commission_for_order.hpp>

namespace binance::spot::rest_api {

OrderTestResponseStandardCommissionForOrder
tag_invoke(boost::json::value_to_tag<OrderTestResponseStandardCommissionForOrder> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "OrderTestResponseStandardCommissionForOrder");
    OrderTestResponseStandardCommissionForOrder out;
    common::detail::json::read(obj, "maker", out.maker);
    common::detail::json::read(obj, "taker", out.taker);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderTestResponseStandardCommissionForOrder& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "maker", v.maker);
    common::detail::json::write(obj, "taker", v.taker);
}

} // namespace binance::spot::rest_api
