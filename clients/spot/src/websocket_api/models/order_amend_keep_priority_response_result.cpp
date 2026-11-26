//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/order_amend_keep_priority_response_result.hpp>

namespace binance::spot::websocket_api {

OrderAmendKeepPriorityResponseResult
tag_invoke(boost::json::value_to_tag<OrderAmendKeepPriorityResponseResult> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OrderAmendKeepPriorityResponseResult");
    OrderAmendKeepPriorityResponseResult out;
    common::detail::json::read(obj, "transactTime", out.transact_time);
    common::detail::json::read(obj, "executionId", out.execution_id);
    common::detail::json::read(obj, "amendedOrder", out.amended_order);
    common::detail::json::read(obj, "listStatus", out.list_status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderAmendKeepPriorityResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "transactTime", v.transact_time);
    common::detail::json::write(obj, "executionId", v.execution_id);
    common::detail::json::write(obj, "amendedOrder", v.amended_order);
    common::detail::json::write(obj, "listStatus", v.list_status);
}

} // namespace binance::spot::websocket_api
