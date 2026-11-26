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
#include <binance/derivatives_trading_options/websocket_streams/models/user_data_stream_events_response.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

UserDataStreamEventsResponse
tag_invoke(boost::json::value_to_tag<UserDataStreamEventsResponse> /*tag*/,
           const boost::json::value& jv) {
    UserDataStreamEventsResponse out;
    if (const auto* obj = jv.if_object()) {
        if (const auto* tag = obj->if_contains("e"); tag != nullptr && tag->is_string()) {
            const std::string_view name = tag->get_string();
            if (name == "ACCOUNT_UPDATE") {
                out.value = boost::json::value_to<AccountUpdate>(jv);
                return out;
            }
            if (name == "BALANCE_POSITION_UPDATE") {
                out.value = boost::json::value_to<BalancePositionUpdate>(jv);
                return out;
            }
            if (name == "GREEK_UPDATE") {
                out.value = boost::json::value_to<GreekUpdate>(jv);
                return out;
            }
            if (name == "ORDER_TRADE_UPDATE") {
                out.value = boost::json::value_to<OrderTradeUpdate>(jv);
                return out;
            }
            if (name == "RISK_LEVEL_CHANGE") {
                out.value = boost::json::value_to<RiskLevelChange>(jv);
                return out;
            }
            if (name == "listenKeyExpired") {
                out.value = boost::json::value_to<ListenKeyExpired>(jv);
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
    if (std::holds_alternative<AccountUpdate>(v.value)) {
        (*obj)["e"] = "ACCOUNT_UPDATE";
        return;
    }
    if (std::holds_alternative<BalancePositionUpdate>(v.value)) {
        (*obj)["e"] = "BALANCE_POSITION_UPDATE";
        return;
    }
    if (std::holds_alternative<GreekUpdate>(v.value)) {
        (*obj)["e"] = "GREEK_UPDATE";
        return;
    }
    if (std::holds_alternative<OrderTradeUpdate>(v.value)) {
        (*obj)["e"] = "ORDER_TRADE_UPDATE";
        return;
    }
    if (std::holds_alternative<RiskLevelChange>(v.value)) {
        (*obj)["e"] = "RISK_LEVEL_CHANGE";
        return;
    }
    if (std::holds_alternative<ListenKeyExpired>(v.value)) {
        (*obj)["e"] = "listenKeyExpired";
        return;
    }
}

} // namespace binance::derivatives_trading_options::websocket_streams
