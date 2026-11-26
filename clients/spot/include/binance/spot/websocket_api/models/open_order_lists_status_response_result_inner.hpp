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
#include <binance/spot/websocket_api/models/open_order_lists_status_response_result_inner_orders_inner.hpp>

namespace binance::spot::websocket_api {

struct OpenOrderListsStatusResponseResultInner {
    std::optional<std::int64_t> order_list_id;
    std::optional<std::string> contingency_type;
    std::optional<std::string> list_status_type;
    std::optional<std::string> list_order_status;
    std::optional<std::string> list_client_order_id;
    std::optional<std::int64_t> transaction_time;
    std::optional<std::string> symbol;
    std::optional<std::vector<OpenOrderListsStatusResponseResultInnerOrdersInner>> orders;

    bool operator==(const OpenOrderListsStatusResponseResultInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OpenOrderListsStatusResponseResultInner
tag_invoke(boost::json::value_to_tag<OpenOrderListsStatusResponseResultInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OpenOrderListsStatusResponseResultInner& v);

} // namespace binance::spot::websocket_api
