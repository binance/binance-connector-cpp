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
#include <binance/spot/websocket_api/models/order_test_response_result_discount.hpp>
#include <binance/spot/websocket_api/models/order_test_response_result_standard_commission_for_order.hpp>
#include <binance/spot/websocket_api/models/order_test_response_result_tax_commission_for_order.hpp>

namespace binance::spot::websocket_api {

struct SorOrderTestResponseResult {
    std::optional<OrderTestResponseResultStandardCommissionForOrder> standard_commission_for_order;
    std::optional<OrderTestResponseResultTaxCommissionForOrder> tax_commission_for_order;
    std::optional<OrderTestResponseResultDiscount> discount;

    bool operator==(const SorOrderTestResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT SorOrderTestResponseResult tag_invoke(
    boost::json::value_to_tag<SorOrderTestResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const SorOrderTestResponseResult& v);

} // namespace binance::spot::websocket_api
