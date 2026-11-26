//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/trade_api.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

std::string_view to_string(ModifyOrderSideEnum value) noexcept {
    switch (value) {
    case ModifyOrderSideEnum::Buy:
        return "BUY";
    case ModifyOrderSideEnum::Sell:
        return "SELL";
    case ModifyOrderSideEnum::Unknown:
        break;
    }
    return "";
}

ModifyOrderSideEnum tag_invoke(boost::json::value_to_tag<ModifyOrderSideEnum> /*tag*/,
                               const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return ModifyOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return ModifyOrderSideEnum::Sell;
    }
    return ModifyOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyOrderSideEnum value) {
    if (value == ModifyOrderSideEnum::Unknown) {
        throw std::invalid_argument("ModifyOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ModifyOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case ModifyOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case ModifyOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case ModifyOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case ModifyOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case ModifyOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case ModifyOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case ModifyOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case ModifyOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case ModifyOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

ModifyOrderPriceMatchEnum tag_invoke(boost::json::value_to_tag<ModifyOrderPriceMatchEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return ModifyOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return ModifyOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return ModifyOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return ModifyOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return ModifyOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return ModifyOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return ModifyOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return ModifyOrderPriceMatchEnum::Queue20;
    }
    return ModifyOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyOrderPriceMatchEnum value) {
    if (value == ModifyOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("ModifyOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderSideEnum value) noexcept {
    switch (value) {
    case NewOrderSideEnum::Buy:
        return "BUY";
    case NewOrderSideEnum::Sell:
        return "SELL";
    case NewOrderSideEnum::Unknown:
        break;
    }
    return "";
}

NewOrderSideEnum tag_invoke(boost::json::value_to_tag<NewOrderSideEnum> /*tag*/,
                            const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return NewOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return NewOrderSideEnum::Sell;
    }
    return NewOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderSideEnum value) {
    if (value == NewOrderSideEnum::Unknown) {
        throw std::invalid_argument("NewOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderTypeEnum value) noexcept {
    switch (value) {
    case NewOrderTypeEnum::Limit:
        return "LIMIT";
    case NewOrderTypeEnum::Market:
        return "MARKET";
    case NewOrderTypeEnum::Stop:
        return "STOP";
    case NewOrderTypeEnum::StopMarket:
        return "STOP_MARKET";
    case NewOrderTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case NewOrderTypeEnum::TakeProfitMarket:
        return "TAKE_PROFIT_MARKET";
    case NewOrderTypeEnum::TrailingStopMarket:
        return "TRAILING_STOP_MARKET";
    case NewOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderTypeEnum tag_invoke(boost::json::value_to_tag<NewOrderTypeEnum> /*tag*/,
                            const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return NewOrderTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return NewOrderTypeEnum::Market;
    }
    if (s == "STOP") {
        return NewOrderTypeEnum::Stop;
    }
    if (s == "STOP_MARKET") {
        return NewOrderTypeEnum::StopMarket;
    }
    if (s == "TAKE_PROFIT") {
        return NewOrderTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_MARKET") {
        return NewOrderTypeEnum::TakeProfitMarket;
    }
    if (s == "TRAILING_STOP_MARKET") {
        return NewOrderTypeEnum::TrailingStopMarket;
    }
    return NewOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderTypeEnum value) {
    if (value == NewOrderTypeEnum::Unknown) {
        throw std::invalid_argument("NewOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderPositionSideEnum value) noexcept {
    switch (value) {
    case NewOrderPositionSideEnum::Both:
        return "BOTH";
    case NewOrderPositionSideEnum::Long:
        return "LONG";
    case NewOrderPositionSideEnum::Short:
        return "SHORT";
    case NewOrderPositionSideEnum::Unknown:
        break;
    }
    return "";
}

NewOrderPositionSideEnum tag_invoke(boost::json::value_to_tag<NewOrderPositionSideEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return NewOrderPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return NewOrderPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return NewOrderPositionSideEnum::Short;
    }
    return NewOrderPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderPositionSideEnum value) {
    if (value == NewOrderPositionSideEnum::Unknown) {
        throw std::invalid_argument("NewOrderPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case NewOrderTimeInForceEnum::Gtc:
        return "GTC";
    case NewOrderTimeInForceEnum::Ioc:
        return "IOC";
    case NewOrderTimeInForceEnum::Fok:
        return "FOK";
    case NewOrderTimeInForceEnum::Gtx:
        return "GTX";
    case NewOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

NewOrderTimeInForceEnum tag_invoke(boost::json::value_to_tag<NewOrderTimeInForceEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return NewOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return NewOrderTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return NewOrderTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return NewOrderTimeInForceEnum::Gtx;
    }
    return NewOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderTimeInForceEnum value) {
    if (value == NewOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("NewOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderReduceOnlyEnum value) noexcept {
    switch (value) {
    case NewOrderReduceOnlyEnum::True_:
        return "true";
    case NewOrderReduceOnlyEnum::False_:
        return "false";
    case NewOrderReduceOnlyEnum::Unknown:
        break;
    }
    return "";
}

NewOrderReduceOnlyEnum tag_invoke(boost::json::value_to_tag<NewOrderReduceOnlyEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewOrderReduceOnlyEnum::True_;
    }
    if (s == "false") {
        return NewOrderReduceOnlyEnum::False_;
    }
    return NewOrderReduceOnlyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderReduceOnlyEnum value) {
    if (value == NewOrderReduceOnlyEnum::Unknown) {
        throw std::invalid_argument("NewOrderReduceOnlyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderClosePositionEnum value) noexcept {
    switch (value) {
    case NewOrderClosePositionEnum::True_:
        return "true";
    case NewOrderClosePositionEnum::False_:
        return "false";
    case NewOrderClosePositionEnum::Unknown:
        break;
    }
    return "";
}

NewOrderClosePositionEnum tag_invoke(boost::json::value_to_tag<NewOrderClosePositionEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewOrderClosePositionEnum::True_;
    }
    if (s == "false") {
        return NewOrderClosePositionEnum::False_;
    }
    return NewOrderClosePositionEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderClosePositionEnum value) {
    if (value == NewOrderClosePositionEnum::Unknown) {
        throw std::invalid_argument("NewOrderClosePositionEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderWorkingTypeEnum value) noexcept {
    switch (value) {
    case NewOrderWorkingTypeEnum::MarkPrice:
        return "MARK_PRICE";
    case NewOrderWorkingTypeEnum::ContractPrice:
        return "CONTRACT_PRICE";
    case NewOrderWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderWorkingTypeEnum tag_invoke(boost::json::value_to_tag<NewOrderWorkingTypeEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARK_PRICE") {
        return NewOrderWorkingTypeEnum::MarkPrice;
    }
    if (s == "CONTRACT_PRICE") {
        return NewOrderWorkingTypeEnum::ContractPrice;
    }
    return NewOrderWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderWorkingTypeEnum value) {
    if (value == NewOrderWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("NewOrderWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderPriceProtectEnum value) noexcept {
    switch (value) {
    case NewOrderPriceProtectEnum::True_:
        return "true";
    case NewOrderPriceProtectEnum::False_:
        return "false";
    case NewOrderPriceProtectEnum::Unknown:
        break;
    }
    return "";
}

NewOrderPriceProtectEnum tag_invoke(boost::json::value_to_tag<NewOrderPriceProtectEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewOrderPriceProtectEnum::True_;
    }
    if (s == "false") {
        return NewOrderPriceProtectEnum::False_;
    }
    return NewOrderPriceProtectEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderPriceProtectEnum value) {
    if (value == NewOrderPriceProtectEnum::Unknown) {
        throw std::invalid_argument("NewOrderPriceProtectEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case NewOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case NewOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case NewOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return NewOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return NewOrderNewOrderRespTypeEnum::Result;
    }
    return NewOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderNewOrderRespTypeEnum value) {
    if (value == NewOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("NewOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case NewOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case NewOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case NewOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case NewOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case NewOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case NewOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case NewOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case NewOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case NewOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

NewOrderPriceMatchEnum tag_invoke(boost::json::value_to_tag<NewOrderPriceMatchEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return NewOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return NewOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return NewOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return NewOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return NewOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return NewOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return NewOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return NewOrderPriceMatchEnum::Queue20;
    }
    return NewOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderPriceMatchEnum value) {
    if (value == NewOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("NewOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case NewOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case NewOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case NewOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case NewOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case NewOrderSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return NewOrderSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return NewOrderSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_BOTH") {
        return NewOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "EXPIRE_MAKER") {
        return NewOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    return NewOrderSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderSelfTradePreventionModeEnum value) {
    if (value == NewOrderSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument("NewOrderSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::WebsocketApi> client) : client_(std::move(client)) {}

common::Params TradeApi::cancel_order_payload(const CancelOrderParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<CancelOrderResponseResult>
TradeApi::cancel_order(const CancelOrderParams& params) const {
    return common::send<CancelOrderResponseResult>(*client_, "order.cancel",
                                                   cancel_order_payload(params),
                                                   make_options(false, true, false, false));
}

common::Params TradeApi::modify_order_payload(const ModifyOrderParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(p, "priceMatch", params.price_match);
    common::detail::json::set_param(p, "modifyId", params.modify_id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<ModifyOrderResponseResult>
TradeApi::modify_order(const ModifyOrderParams& params) const {
    return common::send<ModifyOrderResponseResult>(*client_, "order.modify",
                                                   modify_order_payload(params),
                                                   make_options(false, true, false, false));
}

common::Params TradeApi::new_order_payload(const NewOrderParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "type", params.type);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "positionSide", params.position_side);
    common::detail::json::set_param(p, "timeInForce", params.time_in_force);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "stopPrice", params.stop_price);
    common::detail::json::set_param(p, "closePosition", params.close_position);
    common::detail::json::set_param(p, "activationPrice", params.activation_price);
    common::detail::json::set_param(p, "callbackRate", params.callback_rate);
    common::detail::json::set_param(p, "workingType", params.working_type);
    common::detail::json::set_param(p, "priceProtect", params.price_protect);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "priceMatch", params.price_match);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<NewOrderResponseResult>
TradeApi::new_order(const NewOrderParams& params) const {
    return common::send<NewOrderResponseResult>(*client_, "order.place", new_order_payload(params),
                                                make_options(false, true, false, false));
}

common::Params TradeApi::position_information_payload(const PositionInformationParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "marginAsset", params.margin_asset);
    common::detail::json::set_param(p, "pair", params.pair);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<PositionInformationResponseResultInner>>
TradeApi::position_information(const PositionInformationParams& params) const {
    return common::send<std::vector<PositionInformationResponseResultInner>>(
        *client_, "account.position", position_information_payload(params),
        make_options(false, true, false, false));
}

common::Params TradeApi::query_order_payload(const QueryOrderParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<QueryOrderResponseResult>
TradeApi::query_order(const QueryOrderParams& params) const {
    return common::send<QueryOrderResponseResult>(*client_, "order.status",
                                                  query_order_payload(params),
                                                  make_options(false, true, false, false));
}

} // namespace binance::derivatives_trading_coin_futures::websocket_api
