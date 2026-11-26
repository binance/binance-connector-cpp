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
#include <binance/spot/rest_api/models/delete_order_list_response_order_reports_inner.hpp>
#include <binance/spot/rest_api/models/delete_order_list_response_orders_inner.hpp>

namespace binance::spot::rest_api {

struct DeleteOrderListResponse {
    std::optional<std::int64_t> order_list_id;
    std::optional<std::string> contingency_type;
    std::optional<std::string> list_status_type;
    std::optional<std::string> list_order_status;
    std::optional<std::string> list_client_order_id;
    std::optional<std::int64_t> transaction_time;
    std::optional<std::string> symbol;
    std::optional<std::vector<DeleteOrderListResponseOrdersInner>> orders;
    std::optional<std::vector<DeleteOrderListResponseOrderReportsInner>> order_reports;

    bool operator==(const DeleteOrderListResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT DeleteOrderListResponse tag_invoke(
    boost::json::value_to_tag<DeleteOrderListResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const DeleteOrderListResponse& v);

} // namespace binance::spot::rest_api
