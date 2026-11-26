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
#include <binance/spot/websocket_api/models/order_cancel_replace_response_result_cancel_response.hpp>
#include <binance/spot/websocket_api/models/order_cancel_replace_response_result_new_order_response.hpp>

namespace binance::spot::websocket_api {

struct OrderCancelReplaceResponseResult {
    std::optional<std::string> cancel_result;
    std::optional<std::string> new_order_result;
    std::optional<OrderCancelReplaceResponseResultCancelResponse> cancel_response;
    std::optional<OrderCancelReplaceResponseResultNewOrderResponse> new_order_response;

    bool operator==(const OrderCancelReplaceResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderCancelReplaceResponseResult
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceResponseResult> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderCancelReplaceResponseResult& v);

} // namespace binance::spot::websocket_api
