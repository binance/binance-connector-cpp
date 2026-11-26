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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/order_amend_keep_priority_response_result_amended_order.hpp>
#include <binance/spot/websocket_api/models/order_amend_keep_priority_response_result_list_status.hpp>

namespace binance::spot::websocket_api {

struct OrderAmendKeepPriorityResponseResult {
    std::optional<std::int64_t> transact_time;
    std::optional<std::int64_t> execution_id;
    std::optional<OrderAmendKeepPriorityResponseResultAmendedOrder> amended_order;
    std::optional<OrderAmendKeepPriorityResponseResultListStatus> list_status;

    bool operator==(const OrderAmendKeepPriorityResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderAmendKeepPriorityResponseResult
tag_invoke(boost::json::value_to_tag<OrderAmendKeepPriorityResponseResult> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderAmendKeepPriorityResponseResult& v);

} // namespace binance::spot::websocket_api
