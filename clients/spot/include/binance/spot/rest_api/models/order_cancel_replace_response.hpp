//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/order_cancel_replace_response_cancel_response.hpp>
#include <binance/spot/rest_api/models/order_cancel_replace_response_new_order_response.hpp>

namespace binance::spot::rest_api {

/// Both the cancel and the new order placement succeeded, and the account has not exceeded its
/// unfilled order count:
struct OrderCancelReplaceResponse {
    std::optional<std::string> cancel_result;
    std::optional<std::string> new_order_result;
    std::optional<OrderCancelReplaceResponseCancelResponse> cancel_response;
    std::optional<OrderCancelReplaceResponseNewOrderResponse> new_order_response;

    bool operator==(const OrderCancelReplaceResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderCancelReplaceResponse tag_invoke(
    boost::json::value_to_tag<OrderCancelReplaceResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderCancelReplaceResponse& v);

} // namespace binance::spot::rest_api
