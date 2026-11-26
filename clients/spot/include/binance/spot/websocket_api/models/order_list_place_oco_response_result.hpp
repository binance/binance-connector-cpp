//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/order_list_place_oco_response_result_order_reports_inner.hpp>
#include <binance/spot/websocket_api/models/order_list_place_oco_response_result_orders_inner.hpp>

namespace binance::spot::websocket_api {

struct OrderListPlaceOcoResponseResult {
    std::optional<std::int64_t> order_list_id;
    std::optional<std::string> contingency_type;
    std::optional<std::string> list_status_type;
    std::optional<std::string> list_order_status;
    std::optional<std::string> list_client_order_id;
    std::optional<std::int64_t> transaction_time;
    std::optional<std::string> symbol;
    std::optional<std::vector<OrderListPlaceOcoResponseResultOrdersInner>> orders;
    std::optional<std::vector<OrderListPlaceOcoResponseResultOrderReportsInner>> order_reports;

    bool operator==(const OrderListPlaceOcoResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderListPlaceOcoResponseResult
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoResponseResult> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderListPlaceOcoResponseResult& v);

} // namespace binance::spot::websocket_api
