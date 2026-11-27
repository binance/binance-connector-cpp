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
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/user_data_stream_events_response.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

UserDataStreamEventsResponse
tag_invoke(boost::json::value_to_tag<UserDataStreamEventsResponse> /*tag*/,
           const boost::json::value& jv) {
    UserDataStreamEventsResponse out;
    if (const auto* obj = jv.if_object()) {
        if (const auto* tag = obj->if_contains("e"); tag != nullptr && tag->is_string()) {
            const std::string_view name = tag->get_string();
            if (name == "ACCOUNT_CONFIG_UPDATE") {
                out.value = boost::json::value_to<AccountConfigUpdate>(jv);
                return out;
            }
            if (name == "ACCOUNT_UPDATE") {
                out.value = boost::json::value_to<AccountUpdate>(jv);
                return out;
            }
            if (name == "ALGO_UPDATE") {
                out.value = boost::json::value_to<AlgoUpdate>(jv);
                return out;
            }
            if (name == "CONDITIONAL_ORDER_TRIGGER_REJECT") {
                out.value = boost::json::value_to<ConditionalOrderTriggerReject>(jv);
                return out;
            }
            if (name == "GRID_UPDATE") {
                out.value = boost::json::value_to<GridUpdate>(jv);
                return out;
            }
            if (name == "MARGIN_CALL") {
                out.value = boost::json::value_to<MarginCall>(jv);
                return out;
            }
            if (name == "ORDER_TRADE_UPDATE") {
                out.value = boost::json::value_to<OrderTradeUpdate>(jv);
                return out;
            }
            if (name == "STRATEGY_UPDATE") {
                out.value = boost::json::value_to<StrategyUpdate>(jv);
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
    if (std::holds_alternative<AccountConfigUpdate>(v.value)) {
        (*obj)["e"] = "ACCOUNT_CONFIG_UPDATE";
        return;
    }
    if (std::holds_alternative<AccountUpdate>(v.value)) {
        (*obj)["e"] = "ACCOUNT_UPDATE";
        return;
    }
    if (std::holds_alternative<AlgoUpdate>(v.value)) {
        (*obj)["e"] = "ALGO_UPDATE";
        return;
    }
    if (std::holds_alternative<ConditionalOrderTriggerReject>(v.value)) {
        (*obj)["e"] = "CONDITIONAL_ORDER_TRIGGER_REJECT";
        return;
    }
    if (std::holds_alternative<GridUpdate>(v.value)) {
        (*obj)["e"] = "GRID_UPDATE";
        return;
    }
    if (std::holds_alternative<MarginCall>(v.value)) {
        (*obj)["e"] = "MARGIN_CALL";
        return;
    }
    if (std::holds_alternative<OrderTradeUpdate>(v.value)) {
        (*obj)["e"] = "ORDER_TRADE_UPDATE";
        return;
    }
    if (std::holds_alternative<StrategyUpdate>(v.value)) {
        (*obj)["e"] = "STRATEGY_UPDATE";
        return;
    }
    if (std::holds_alternative<ListenKeyExpired>(v.value)) {
        (*obj)["e"] = "listenKeyExpired";
        return;
    }
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
