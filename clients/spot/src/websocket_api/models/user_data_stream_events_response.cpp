//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string_view>
#include <variant>

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/user_data_stream_events_response.hpp>

namespace binance::spot::websocket_api {

UserDataStreamEventsResponse
tag_invoke(boost::json::value_to_tag<UserDataStreamEventsResponse> /*tag*/,
           const boost::json::value& jv) {
    UserDataStreamEventsResponse out;
    if (const auto* obj = jv.if_object()) {
        if (const auto* tag = obj->if_contains("e"); tag != nullptr && tag->is_string()) {
            const std::string_view name = tag->get_string();
            if (name == "balanceUpdate") {
                out.value = boost::json::value_to<BalanceUpdate>(jv);
                return out;
            }
            if (name == "eventStreamTerminated") {
                out.value = boost::json::value_to<EventStreamTerminated>(jv);
                return out;
            }
            if (name == "executionReport") {
                out.value = boost::json::value_to<ExecutionReport>(jv);
                return out;
            }
            if (name == "externalLockUpdate") {
                out.value = boost::json::value_to<ExternalLockUpdate>(jv);
                return out;
            }
            if (name == "listStatus") {
                out.value = boost::json::value_to<ListStatus>(jv);
                return out;
            }
            if (name == "outboundAccountPosition") {
                out.value = boost::json::value_to<OutboundAccountPosition>(jv);
                return out;
            }
        }
    }
    out.value = jv;
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UserDataStreamEventsResponse& v) {
    std::visit([&jv](const auto& alternative) { jv = boost::json::value_from(alternative); },
               v.value);
    // The alternatives do not store the tag that selected them.
    auto* obj = jv.if_object();
    if (obj == nullptr || obj->contains("e")) {
        return;
    }
    if (std::holds_alternative<BalanceUpdate>(v.value)) {
        (*obj)["e"] = "balanceUpdate";
        return;
    }
    if (std::holds_alternative<EventStreamTerminated>(v.value)) {
        (*obj)["e"] = "eventStreamTerminated";
        return;
    }
    if (std::holds_alternative<ExecutionReport>(v.value)) {
        (*obj)["e"] = "executionReport";
        return;
    }
    if (std::holds_alternative<ExternalLockUpdate>(v.value)) {
        (*obj)["e"] = "externalLockUpdate";
        return;
    }
    if (std::holds_alternative<ListStatus>(v.value)) {
        (*obj)["e"] = "listStatus";
        return;
    }
    if (std::holds_alternative<OutboundAccountPosition>(v.value)) {
        (*obj)["e"] = "outboundAccountPosition";
        return;
    }
}

} // namespace binance::spot::websocket_api
