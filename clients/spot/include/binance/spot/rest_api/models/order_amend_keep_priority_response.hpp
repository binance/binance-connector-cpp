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
#include <binance/spot/rest_api/models/order_amend_keep_priority_response_amended_order.hpp>
#include <binance/spot/rest_api/models/order_amend_keep_priority_response_list_status.hpp>

namespace binance::spot::rest_api {

struct OrderAmendKeepPriorityResponse {
    std::optional<std::int64_t> transact_time;
    std::optional<std::int64_t> execution_id;
    std::optional<OrderAmendKeepPriorityResponseAmendedOrder> amended_order;
    std::optional<OrderAmendKeepPriorityResponseListStatus> list_status;

    bool operator==(const OrderAmendKeepPriorityResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderAmendKeepPriorityResponse
tag_invoke(boost::json::value_to_tag<OrderAmendKeepPriorityResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderAmendKeepPriorityResponse& v);

} // namespace binance::spot::rest_api
