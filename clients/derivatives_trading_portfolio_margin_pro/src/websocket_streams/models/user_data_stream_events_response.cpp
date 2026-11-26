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
#include <binance/derivatives_trading_portfolio_margin_pro/websocket_streams/models/user_data_stream_events_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams {

UserDataStreamEventsResponse
tag_invoke(boost::json::value_to_tag<UserDataStreamEventsResponse> /*tag*/,
           const boost::json::value& jv) {
    UserDataStreamEventsResponse out;
    if (const auto* obj = jv.if_object()) {
        if (const auto* tag = obj->if_contains("e"); tag != nullptr && tag->is_string()) {
            const std::string_view name = tag->get_string();
            if (name == "PM_PRO_ACCOUNT_UPDATE") {
                out.value = boost::json::value_to<PmProAccountUpdate>(jv);
                return out;
            }
            if (name == "riskLevelChange") {
                out.value = boost::json::value_to<Risklevelchange>(jv);
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
    if (std::holds_alternative<PmProAccountUpdate>(v.value)) {
        (*obj)["e"] = "PM_PRO_ACCOUNT_UPDATE";
        return;
    }
    if (std::holds_alternative<Risklevelchange>(v.value)) {
        (*obj)["e"] = "riskLevelChange";
        return;
    }
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams
