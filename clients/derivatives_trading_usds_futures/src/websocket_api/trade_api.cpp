//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/trade_api.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

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

std::string_view to_string(ModifyOrderReduceOnlyEnum value) noexcept {
    switch (value) {
    case ModifyOrderReduceOnlyEnum::True_:
        return "true";
    case ModifyOrderReduceOnlyEnum::False_:
        return "false";
    case ModifyOrderReduceOnlyEnum::Unknown:
        break;
    }
    return "";
}

ModifyOrderReduceOnlyEnum tag_invoke(boost::json::value_to_tag<ModifyOrderReduceOnlyEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return ModifyOrderReduceOnlyEnum::True_;
    }
    if (s == "false") {
        return ModifyOrderReduceOnlyEnum::False_;
    }
    return ModifyOrderReduceOnlyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyOrderReduceOnlyEnum value) {
    if (value == ModifyOrderReduceOnlyEnum::Unknown) {
        throw std::invalid_argument("ModifyOrderReduceOnlyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderAlgoTypeEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderAlgoTypeEnum::Conditional:
        return "CONDITIONAL";
    case NewAlgoOrderAlgoTypeEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderAlgoTypeEnum tag_invoke(boost::json::value_to_tag<NewAlgoOrderAlgoTypeEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "CONDITIONAL") {
        return NewAlgoOrderAlgoTypeEnum::Conditional;
    }
    return NewAlgoOrderAlgoTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderAlgoTypeEnum value) {
    if (value == NewAlgoOrderAlgoTypeEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderAlgoTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderSideEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderSideEnum::Buy:
        return "BUY";
    case NewAlgoOrderSideEnum::Sell:
        return "SELL";
    case NewAlgoOrderSideEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderSideEnum tag_invoke(boost::json::value_to_tag<NewAlgoOrderSideEnum> /*tag*/,
                                const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return NewAlgoOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return NewAlgoOrderSideEnum::Sell;
    }
    return NewAlgoOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderSideEnum value) {
    if (value == NewAlgoOrderSideEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderTypeEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderTypeEnum::StopMarket:
        return "STOP_MARKET";
    case NewAlgoOrderTypeEnum::TakeProfitMarket:
        return "TAKE_PROFIT_MARKET";
    case NewAlgoOrderTypeEnum::Stop:
        return "STOP";
    case NewAlgoOrderTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case NewAlgoOrderTypeEnum::TrailingStopMarket:
        return "TRAILING_STOP_MARKET";
    case NewAlgoOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderTypeEnum tag_invoke(boost::json::value_to_tag<NewAlgoOrderTypeEnum> /*tag*/,
                                const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_MARKET") {
        return NewAlgoOrderTypeEnum::StopMarket;
    }
    if (s == "TAKE_PROFIT_MARKET") {
        return NewAlgoOrderTypeEnum::TakeProfitMarket;
    }
    if (s == "STOP") {
        return NewAlgoOrderTypeEnum::Stop;
    }
    if (s == "TAKE_PROFIT") {
        return NewAlgoOrderTypeEnum::TakeProfit;
    }
    if (s == "TRAILING_STOP_MARKET") {
        return NewAlgoOrderTypeEnum::TrailingStopMarket;
    }
    return NewAlgoOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderTypeEnum value) {
    if (value == NewAlgoOrderTypeEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderPositionSideEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderPositionSideEnum::Both:
        return "BOTH";
    case NewAlgoOrderPositionSideEnum::Long:
        return "LONG";
    case NewAlgoOrderPositionSideEnum::Short:
        return "SHORT";
    case NewAlgoOrderPositionSideEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderPositionSideEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderPositionSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return NewAlgoOrderPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return NewAlgoOrderPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return NewAlgoOrderPositionSideEnum::Short;
    }
    return NewAlgoOrderPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderPositionSideEnum value) {
    if (value == NewAlgoOrderPositionSideEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderTimeInForceEnum::Ioc:
        return "IOC";
    case NewAlgoOrderTimeInForceEnum::Gtc:
        return "GTC";
    case NewAlgoOrderTimeInForceEnum::Fok:
        return "FOK";
    case NewAlgoOrderTimeInForceEnum::Gtx:
        return "GTX";
    case NewAlgoOrderTimeInForceEnum::Gtd:
        return "GTD";
    case NewAlgoOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "IOC") {
        return NewAlgoOrderTimeInForceEnum::Ioc;
    }
    if (s == "GTC") {
        return NewAlgoOrderTimeInForceEnum::Gtc;
    }
    if (s == "FOK") {
        return NewAlgoOrderTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return NewAlgoOrderTimeInForceEnum::Gtx;
    }
    if (s == "GTD") {
        return NewAlgoOrderTimeInForceEnum::Gtd;
    }
    return NewAlgoOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderTimeInForceEnum value) {
    if (value == NewAlgoOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderWorkingTypeEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderWorkingTypeEnum::MarkPrice:
        return "MARK_PRICE";
    case NewAlgoOrderWorkingTypeEnum::ContractPrice:
        return "CONTRACT_PRICE";
    case NewAlgoOrderWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARK_PRICE") {
        return NewAlgoOrderWorkingTypeEnum::MarkPrice;
    }
    if (s == "CONTRACT_PRICE") {
        return NewAlgoOrderWorkingTypeEnum::ContractPrice;
    }
    return NewAlgoOrderWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderWorkingTypeEnum value) {
    if (value == NewAlgoOrderWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case NewAlgoOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case NewAlgoOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case NewAlgoOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case NewAlgoOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case NewAlgoOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case NewAlgoOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case NewAlgoOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case NewAlgoOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderPriceMatchEnum tag_invoke(boost::json::value_to_tag<NewAlgoOrderPriceMatchEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return NewAlgoOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return NewAlgoOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return NewAlgoOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return NewAlgoOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return NewAlgoOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return NewAlgoOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return NewAlgoOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return NewAlgoOrderPriceMatchEnum::Queue20;
    }
    return NewAlgoOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderPriceMatchEnum value) {
    if (value == NewAlgoOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderClosePositionEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderClosePositionEnum::True_:
        return "true";
    case NewAlgoOrderClosePositionEnum::False_:
        return "false";
    case NewAlgoOrderClosePositionEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderClosePositionEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderClosePositionEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewAlgoOrderClosePositionEnum::True_;
    }
    if (s == "false") {
        return NewAlgoOrderClosePositionEnum::False_;
    }
    return NewAlgoOrderClosePositionEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderClosePositionEnum value) {
    if (value == NewAlgoOrderClosePositionEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderClosePositionEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderPriceProtectEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderPriceProtectEnum::True_:
        return "true";
    case NewAlgoOrderPriceProtectEnum::False_:
        return "false";
    case NewAlgoOrderPriceProtectEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderPriceProtectEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderPriceProtectEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewAlgoOrderPriceProtectEnum::True_;
    }
    if (s == "false") {
        return NewAlgoOrderPriceProtectEnum::False_;
    }
    return NewAlgoOrderPriceProtectEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderPriceProtectEnum value) {
    if (value == NewAlgoOrderPriceProtectEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderPriceProtectEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderReduceOnlyEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderReduceOnlyEnum::True_:
        return "true";
    case NewAlgoOrderReduceOnlyEnum::False_:
        return "false";
    case NewAlgoOrderReduceOnlyEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderReduceOnlyEnum tag_invoke(boost::json::value_to_tag<NewAlgoOrderReduceOnlyEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewAlgoOrderReduceOnlyEnum::True_;
    }
    if (s == "false") {
        return NewAlgoOrderReduceOnlyEnum::False_;
    }
    return NewAlgoOrderReduceOnlyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderReduceOnlyEnum value) {
    if (value == NewAlgoOrderReduceOnlyEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderReduceOnlyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case NewAlgoOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case NewAlgoOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return NewAlgoOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return NewAlgoOrderNewOrderRespTypeEnum::Result;
    }
    return NewAlgoOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderNewOrderRespTypeEnum value) {
    if (value == NewAlgoOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("NewAlgoOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewAlgoOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case NewAlgoOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case NewAlgoOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case NewAlgoOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case NewAlgoOrderSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return NewAlgoOrderSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return NewAlgoOrderSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_BOTH") {
        return NewAlgoOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "EXPIRE_MAKER") {
        return NewAlgoOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    return NewAlgoOrderSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewAlgoOrderSelfTradePreventionModeEnum value) {
    if (value == NewAlgoOrderSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "NewAlgoOrderSelfTradePreventionModeEnum::Unknown cannot be sent");
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
    case NewOrderTimeInForceEnum::Gtd:
        return "GTD";
    case NewOrderTimeInForceEnum::Rpi:
        return "RPI";
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
    if (s == "GTD") {
        return NewOrderTimeInForceEnum::Gtd;
    }
    if (s == "RPI") {
        return NewOrderTimeInForceEnum::Rpi;
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

common::Params TradeApi::cancel_algo_order_payload(const CancelAlgoOrderParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "algoId", params.algo_id);
    common::detail::json::set_param(p, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<CancelAlgoOrderResponseResult>
TradeApi::cancel_algo_order(const CancelAlgoOrderParams& params) const {
    return common::send<CancelAlgoOrderResponseResult>(*client_, "algoOrder.cancel",
                                                       cancel_algo_order_payload(params),
                                                       make_options(false, true, false, false));
}

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
    common::detail::json::set_param(p, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<ModifyOrderResponseResult>
TradeApi::modify_order(const ModifyOrderParams& params) const {
    return common::send<ModifyOrderResponseResult>(*client_, "order.modify",
                                                   modify_order_payload(params),
                                                   make_options(false, true, false, false));
}

common::Params TradeApi::new_algo_order_payload(const NewAlgoOrderParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "algoType", params.algo_type);
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "type", params.type);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "positionSide", params.position_side);
    common::detail::json::set_param(p, "timeInForce", params.time_in_force);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "triggerPrice", params.trigger_price);
    common::detail::json::set_param(p, "workingType", params.working_type);
    common::detail::json::set_param(p, "priceMatch", params.price_match);
    common::detail::json::set_param(p, "closePosition", params.close_position);
    common::detail::json::set_param(p, "priceProtect", params.price_protect);
    common::detail::json::set_param(p, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(p, "activatePrice", params.activate_price);
    common::detail::json::set_param(p, "callbackRate", params.callback_rate);
    common::detail::json::set_param(p, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "goodTillDate", params.good_till_date);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<NewAlgoOrderResponseResult>
TradeApi::new_algo_order(const NewAlgoOrderParams& params) const {
    return common::send<NewAlgoOrderResponseResult>(*client_, "algoOrder.place",
                                                    new_algo_order_payload(params),
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
    common::detail::json::set_param(p, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "priceMatch", params.price_match);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "goodTillDate", params.good_till_date);
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
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<PositionInformationResponseResultInner>>
TradeApi::position_information(const PositionInformationParams& params) const {
    return common::send<std::vector<PositionInformationResponseResultInner>>(
        *client_, "account.position", position_information_payload(params),
        make_options(false, true, false, false));
}

common::Params
TradeApi::position_information_v2_payload(const PositionInformationV2Params& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<PositionInformationV2ResponseResultInner>>
TradeApi::position_information_v2(const PositionInformationV2Params& params) const {
    return common::send<std::vector<PositionInformationV2ResponseResultInner>>(
        *client_, "v2/account.position", position_information_v2_payload(params),
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

} // namespace binance::derivatives_trading_usds_futures::websocket_api
