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
#include <binance/margin_trading/websocket_streams/models/risk_data_stream_events_response.hpp>

namespace binance::margin_trading::websocket_streams {

RiskDataStreamEventsResponse
tag_invoke(boost::json::value_to_tag<RiskDataStreamEventsResponse> /*tag*/,
           const boost::json::value& jv) {
    RiskDataStreamEventsResponse out;
    if (const auto* obj = jv.if_object()) {
        if (const auto* tag = obj->if_contains("e"); tag != nullptr && tag->is_string()) {
            const std::string_view name = tag->get_string();
            if (name == "MARGIN_LEVEL_STATUS_CHANGE") {
                out.value = boost::json::value_to<MarginLevelStatusChange>(jv);
                return out;
            }
            if (name == "USER_LIABILITY_CHANGE") {
                out.value = boost::json::value_to<UserLiabilityChange>(jv);
                return out;
            }
        }
    }
    out.value = jv;
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RiskDataStreamEventsResponse& v) {
    std::visit([&jv](const auto& alternative) { jv = boost::json::value_from(alternative); },
               v.value);
    // The alternatives do not store the tag that selected them.
    auto* obj = jv.if_object();
    if (obj == nullptr || obj->contains("e")) {
        return;
    }
    if (std::holds_alternative<MarginLevelStatusChange>(v.value)) {
        (*obj)["e"] = "MARGIN_LEVEL_STATUS_CHANGE";
        return;
    }
    if (std::holds_alternative<UserLiabilityChange>(v.value)) {
        (*obj)["e"] = "USER_LIABILITY_CHANGE";
        return;
    }
}

} // namespace binance::margin_trading::websocket_streams
