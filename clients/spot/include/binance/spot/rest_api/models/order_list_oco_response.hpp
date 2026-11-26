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
#include <binance/spot/rest_api/models/order_list_oco_response_order_reports_inner.hpp>
#include <binance/spot/rest_api/models/order_list_oco_response_orders_inner.hpp>

namespace binance::spot::rest_api {

struct OrderListOcoResponse {
    std::optional<std::int64_t> order_list_id;
    std::optional<std::string> contingency_type;
    std::optional<std::string> list_status_type;
    std::optional<std::string> list_order_status;
    std::optional<std::string> list_client_order_id;
    std::optional<std::int64_t> transaction_time;
    std::optional<std::string> symbol;
    std::optional<std::vector<OrderListOcoResponseOrdersInner>> orders;
    std::optional<std::vector<OrderListOcoResponseOrderReportsInner>> order_reports;

    bool operator==(const OrderListOcoResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderListOcoResponse
tag_invoke(boost::json::value_to_tag<OrderListOcoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderListOcoResponse& v);

} // namespace binance::spot::rest_api
