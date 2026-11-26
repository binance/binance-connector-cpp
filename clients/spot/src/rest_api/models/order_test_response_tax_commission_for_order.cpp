//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/order_test_response_tax_commission_for_order.hpp>

namespace binance::spot::rest_api {

OrderTestResponseTaxCommissionForOrder
tag_invoke(boost::json::value_to_tag<OrderTestResponseTaxCommissionForOrder> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OrderTestResponseTaxCommissionForOrder");
    OrderTestResponseTaxCommissionForOrder out;
    common::detail::json::read(obj, "maker", out.maker);
    common::detail::json::read(obj, "taker", out.taker);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderTestResponseTaxCommissionForOrder& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "maker", v.maker);
    common::detail::json::write(obj, "taker", v.taker);
}

} // namespace binance::spot::rest_api
