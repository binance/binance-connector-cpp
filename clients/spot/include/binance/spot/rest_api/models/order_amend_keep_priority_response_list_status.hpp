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
#include <binance/spot/rest_api/models/order_amend_keep_priority_response_list_status_orders_inner.hpp>

namespace binance::spot::rest_api {

struct OrderAmendKeepPriorityResponseListStatus {
    std::optional<std::int64_t> order_list_id;
    std::optional<std::string> contingency_type;
    std::optional<std::string> list_order_status;
    std::optional<std::string> list_client_order_id;
    std::optional<std::string> symbol;
    std::optional<std::vector<OrderAmendKeepPriorityResponseListStatusOrdersInner>> orders;

    bool operator==(const OrderAmendKeepPriorityResponseListStatus& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderAmendKeepPriorityResponseListStatus
tag_invoke(boost::json::value_to_tag<OrderAmendKeepPriorityResponseListStatus> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderAmendKeepPriorityResponseListStatus& v);

} // namespace binance::spot::rest_api
