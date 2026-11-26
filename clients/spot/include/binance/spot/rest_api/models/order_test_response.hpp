//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/order_test_response_discount.hpp>
#include <binance/spot/rest_api/models/order_test_response_special_commission_for_order.hpp>
#include <binance/spot/rest_api/models/order_test_response_standard_commission_for_order.hpp>
#include <binance/spot/rest_api/models/order_test_response_tax_commission_for_order.hpp>

namespace binance::spot::rest_api {

struct OrderTestResponse {
    std::optional<OrderTestResponseStandardCommissionForOrder> standard_commission_for_order;
    std::optional<OrderTestResponseSpecialCommissionForOrder> special_commission_for_order;
    std::optional<OrderTestResponseTaxCommissionForOrder> tax_commission_for_order;
    std::optional<OrderTestResponseDiscount> discount;

    bool operator==(const OrderTestResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderTestResponse
tag_invoke(boost::json::value_to_tag<OrderTestResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderTestResponse& v);

} // namespace binance::spot::rest_api
