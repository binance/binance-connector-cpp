//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/trade_api.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

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
    case NewAlgoOrderTypeEnum::Limit:
        return "LIMIT";
    case NewAlgoOrderTypeEnum::Market:
        return "MARKET";
    case NewAlgoOrderTypeEnum::Stop:
        return "STOP";
    case NewAlgoOrderTypeEnum::StopMarket:
        return "STOP_MARKET";
    case NewAlgoOrderTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case NewAlgoOrderTypeEnum::TakeProfitMarket:
        return "TAKE_PROFIT_MARKET";
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
    if (s == "LIMIT") {
        return NewAlgoOrderTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return NewAlgoOrderTypeEnum::Market;
    }
    if (s == "STOP") {
        return NewAlgoOrderTypeEnum::Stop;
    }
    if (s == "STOP_MARKET") {
        return NewAlgoOrderTypeEnum::StopMarket;
    }
    if (s == "TAKE_PROFIT") {
        return NewAlgoOrderTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_MARKET") {
        return NewAlgoOrderTypeEnum::TakeProfitMarket;
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

std::string_view to_string(NewAlgoOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case NewAlgoOrderTimeInForceEnum::Gtc:
        return "GTC";
    case NewAlgoOrderTimeInForceEnum::Ioc:
        return "IOC";
    case NewAlgoOrderTimeInForceEnum::Fok:
        return "FOK";
    case NewAlgoOrderTimeInForceEnum::Gtx:
        return "GTX";
    case NewAlgoOrderTimeInForceEnum::Gtd:
        return "GTD";
    case NewAlgoOrderTimeInForceEnum::Rpi:
        return "RPI";
    case NewAlgoOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

NewAlgoOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return NewAlgoOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return NewAlgoOrderTimeInForceEnum::Ioc;
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
    if (s == "RPI") {
        return NewAlgoOrderTimeInForceEnum::Rpi;
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

std::string_view to_string(ChangeMarginTypeMarginTypeEnum value) noexcept {
    switch (value) {
    case ChangeMarginTypeMarginTypeEnum::Isolated:
        return "ISOLATED";
    case ChangeMarginTypeMarginTypeEnum::Crossed:
        return "CROSSED";
    case ChangeMarginTypeMarginTypeEnum::Unknown:
        break;
    }
    return "";
}

ChangeMarginTypeMarginTypeEnum
tag_invoke(boost::json::value_to_tag<ChangeMarginTypeMarginTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ISOLATED") {
        return ChangeMarginTypeMarginTypeEnum::Isolated;
    }
    if (s == "CROSSED") {
        return ChangeMarginTypeMarginTypeEnum::Crossed;
    }
    return ChangeMarginTypeMarginTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ChangeMarginTypeMarginTypeEnum value) {
    if (value == ChangeMarginTypeMarginTypeEnum::Unknown) {
        throw std::invalid_argument("ChangeMarginTypeMarginTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderSideEnum value) noexcept {
    switch (value) {
    case TestOrderSideEnum::Buy:
        return "BUY";
    case TestOrderSideEnum::Sell:
        return "SELL";
    case TestOrderSideEnum::Unknown:
        break;
    }
    return "";
}

TestOrderSideEnum tag_invoke(boost::json::value_to_tag<TestOrderSideEnum> /*tag*/,
                             const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return TestOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return TestOrderSideEnum::Sell;
    }
    return TestOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderSideEnum value) {
    if (value == TestOrderSideEnum::Unknown) {
        throw std::invalid_argument("TestOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderTypeEnum value) noexcept {
    switch (value) {
    case TestOrderTypeEnum::Limit:
        return "LIMIT";
    case TestOrderTypeEnum::Market:
        return "MARKET";
    case TestOrderTypeEnum::Stop:
        return "STOP";
    case TestOrderTypeEnum::StopMarket:
        return "STOP_MARKET";
    case TestOrderTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case TestOrderTypeEnum::TakeProfitMarket:
        return "TAKE_PROFIT_MARKET";
    case TestOrderTypeEnum::TrailingStopMarket:
        return "TRAILING_STOP_MARKET";
    case TestOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

TestOrderTypeEnum tag_invoke(boost::json::value_to_tag<TestOrderTypeEnum> /*tag*/,
                             const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return TestOrderTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return TestOrderTypeEnum::Market;
    }
    if (s == "STOP") {
        return TestOrderTypeEnum::Stop;
    }
    if (s == "STOP_MARKET") {
        return TestOrderTypeEnum::StopMarket;
    }
    if (s == "TAKE_PROFIT") {
        return TestOrderTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_MARKET") {
        return TestOrderTypeEnum::TakeProfitMarket;
    }
    if (s == "TRAILING_STOP_MARKET") {
        return TestOrderTypeEnum::TrailingStopMarket;
    }
    return TestOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderTypeEnum value) {
    if (value == TestOrderTypeEnum::Unknown) {
        throw std::invalid_argument("TestOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderPositionSideEnum value) noexcept {
    switch (value) {
    case TestOrderPositionSideEnum::Both:
        return "BOTH";
    case TestOrderPositionSideEnum::Long:
        return "LONG";
    case TestOrderPositionSideEnum::Short:
        return "SHORT";
    case TestOrderPositionSideEnum::Unknown:
        break;
    }
    return "";
}

TestOrderPositionSideEnum tag_invoke(boost::json::value_to_tag<TestOrderPositionSideEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return TestOrderPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return TestOrderPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return TestOrderPositionSideEnum::Short;
    }
    return TestOrderPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderPositionSideEnum value) {
    if (value == TestOrderPositionSideEnum::Unknown) {
        throw std::invalid_argument("TestOrderPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderReduceOnlyEnum value) noexcept {
    switch (value) {
    case TestOrderReduceOnlyEnum::True_:
        return "true";
    case TestOrderReduceOnlyEnum::False_:
        return "false";
    case TestOrderReduceOnlyEnum::Unknown:
        break;
    }
    return "";
}

TestOrderReduceOnlyEnum tag_invoke(boost::json::value_to_tag<TestOrderReduceOnlyEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return TestOrderReduceOnlyEnum::True_;
    }
    if (s == "false") {
        return TestOrderReduceOnlyEnum::False_;
    }
    return TestOrderReduceOnlyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderReduceOnlyEnum value) {
    if (value == TestOrderReduceOnlyEnum::Unknown) {
        throw std::invalid_argument("TestOrderReduceOnlyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderClosePositionEnum value) noexcept {
    switch (value) {
    case TestOrderClosePositionEnum::True_:
        return "true";
    case TestOrderClosePositionEnum::False_:
        return "false";
    case TestOrderClosePositionEnum::Unknown:
        break;
    }
    return "";
}

TestOrderClosePositionEnum tag_invoke(boost::json::value_to_tag<TestOrderClosePositionEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return TestOrderClosePositionEnum::True_;
    }
    if (s == "false") {
        return TestOrderClosePositionEnum::False_;
    }
    return TestOrderClosePositionEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderClosePositionEnum value) {
    if (value == TestOrderClosePositionEnum::Unknown) {
        throw std::invalid_argument("TestOrderClosePositionEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case TestOrderTimeInForceEnum::Gtc:
        return "GTC";
    case TestOrderTimeInForceEnum::Ioc:
        return "IOC";
    case TestOrderTimeInForceEnum::Fok:
        return "FOK";
    case TestOrderTimeInForceEnum::Gtx:
        return "GTX";
    case TestOrderTimeInForceEnum::Gtd:
        return "GTD";
    case TestOrderTimeInForceEnum::Rpi:
        return "RPI";
    case TestOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

TestOrderTimeInForceEnum tag_invoke(boost::json::value_to_tag<TestOrderTimeInForceEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return TestOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return TestOrderTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return TestOrderTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return TestOrderTimeInForceEnum::Gtx;
    }
    if (s == "GTD") {
        return TestOrderTimeInForceEnum::Gtd;
    }
    if (s == "RPI") {
        return TestOrderTimeInForceEnum::Rpi;
    }
    return TestOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderTimeInForceEnum value) {
    if (value == TestOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("TestOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderWorkingTypeEnum value) noexcept {
    switch (value) {
    case TestOrderWorkingTypeEnum::MarkPrice:
        return "MARK_PRICE";
    case TestOrderWorkingTypeEnum::ContractPrice:
        return "CONTRACT_PRICE";
    case TestOrderWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

TestOrderWorkingTypeEnum tag_invoke(boost::json::value_to_tag<TestOrderWorkingTypeEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARK_PRICE") {
        return TestOrderWorkingTypeEnum::MarkPrice;
    }
    if (s == "CONTRACT_PRICE") {
        return TestOrderWorkingTypeEnum::ContractPrice;
    }
    return TestOrderWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderWorkingTypeEnum value) {
    if (value == TestOrderWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("TestOrderWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderPriceProtectEnum value) noexcept {
    switch (value) {
    case TestOrderPriceProtectEnum::True_:
        return "true";
    case TestOrderPriceProtectEnum::False_:
        return "false";
    case TestOrderPriceProtectEnum::Unknown:
        break;
    }
    return "";
}

TestOrderPriceProtectEnum tag_invoke(boost::json::value_to_tag<TestOrderPriceProtectEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return TestOrderPriceProtectEnum::True_;
    }
    if (s == "false") {
        return TestOrderPriceProtectEnum::False_;
    }
    return TestOrderPriceProtectEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderPriceProtectEnum value) {
    if (value == TestOrderPriceProtectEnum::Unknown) {
        throw std::invalid_argument("TestOrderPriceProtectEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case TestOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case TestOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case TestOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

TestOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<TestOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return TestOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return TestOrderNewOrderRespTypeEnum::Result;
    }
    return TestOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderNewOrderRespTypeEnum value) {
    if (value == TestOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("TestOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case TestOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case TestOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case TestOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case TestOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case TestOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case TestOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case TestOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case TestOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case TestOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

TestOrderPriceMatchEnum tag_invoke(boost::json::value_to_tag<TestOrderPriceMatchEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return TestOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return TestOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return TestOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return TestOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return TestOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return TestOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return TestOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return TestOrderPriceMatchEnum::Queue20;
    }
    return TestOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderPriceMatchEnum value) {
    if (value == TestOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("TestOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TestOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case TestOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case TestOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case TestOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case TestOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case TestOrderSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

TestOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<TestOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return TestOrderSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return TestOrderSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_BOTH") {
        return TestOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "EXPIRE_MAKER") {
        return TestOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    return TestOrderSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TestOrderSelfTradePreventionModeEnum value) {
    if (value == TestOrderSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument("TestOrderSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(UsersForceOrdersAutoCloseTypeEnum value) noexcept {
    switch (value) {
    case UsersForceOrdersAutoCloseTypeEnum::Liquidation:
        return "LIQUIDATION";
    case UsersForceOrdersAutoCloseTypeEnum::Adl:
        return "ADL";
    case UsersForceOrdersAutoCloseTypeEnum::Unknown:
        break;
    }
    return "";
}

UsersForceOrdersAutoCloseTypeEnum
tag_invoke(boost::json::value_to_tag<UsersForceOrdersAutoCloseTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIQUIDATION") {
        return UsersForceOrdersAutoCloseTypeEnum::Liquidation;
    }
    if (s == "ADL") {
        return UsersForceOrdersAutoCloseTypeEnum::Adl;
    }
    return UsersForceOrdersAutoCloseTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                UsersForceOrdersAutoCloseTypeEnum value) {
    if (value == UsersForceOrdersAutoCloseTypeEnum::Unknown) {
        throw std::invalid_argument("UsersForceOrdersAutoCloseTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
TradeApi::account_trade_list_request(const AccountTradeListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/userTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<AccountTradeListResponseInner>>
TradeApi::account_trade_list(const AccountTradeListParams& params) const {
    return common::send<std::vector<AccountTradeListResponseInner>>(
        *client_, account_trade_list_request(params));
}

common::RestRequest TradeApi::all_orders_request(const AllOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/allOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<AllOrdersResponseInner>>
TradeApi::all_orders(const AllOrdersParams& params) const {
    return common::send<std::vector<AllOrdersResponseInner>>(*client_, all_orders_request(params));
}

common::RestRequest
TradeApi::auto_cancel_all_open_orders_request(const AutoCancelAllOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/countdownCancelAll";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "countdownTime", params.countdown_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AutoCancelAllOpenOrdersResponse>
TradeApi::auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params) const {
    return common::send<AutoCancelAllOpenOrdersResponse>(
        *client_, auto_cancel_all_open_orders_request(params));
}

common::RestRequest TradeApi::cancel_algo_order_request(const CancelAlgoOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/fapi/v1/algoOrder";
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAlgoOrderResponse>
TradeApi::cancel_algo_order(const CancelAlgoOrderParams& params) const {
    return common::send<CancelAlgoOrderResponse>(*client_, cancel_algo_order_request(params));
}

common::RestRequest TradeApi::new_algo_order_request(const NewAlgoOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/algoOrder";
    common::detail::json::set_param(req.query, "algoType", params.algo_type);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "triggerPrice", params.trigger_price);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "priceMatch", params.price_match);
    common::detail::json::set_param(req.query, "closePosition", params.close_position);
    common::detail::json::set_param(req.query, "priceProtect", params.price_protect);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "activatePrice", params.activate_price);
    common::detail::json::set_param(req.query, "callbackRate", params.callback_rate);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "goodTillDate", params.good_till_date);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<NewAlgoOrderResponse>
TradeApi::new_algo_order(const NewAlgoOrderParams& params) const {
    return common::send<NewAlgoOrderResponse>(*client_, new_algo_order_request(params));
}

common::RestRequest TradeApi::query_algo_order_request(const QueryAlgoOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/algoOrder";
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryAlgoOrderResponse>
TradeApi::query_algo_order(const QueryAlgoOrderParams& params) const {
    return common::send<QueryAlgoOrderResponse>(*client_, query_algo_order_request(params));
}

common::RestRequest
TradeApi::cancel_all_algo_open_orders_request(const CancelAllAlgoOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/fapi/v1/algoOpenOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllAlgoOpenOrdersResponse>
TradeApi::cancel_all_algo_open_orders(const CancelAllAlgoOpenOrdersParams& params) const {
    return common::send<CancelAllAlgoOpenOrdersResponse>(
        *client_, cancel_all_algo_open_orders_request(params));
}

common::RestRequest
TradeApi::cancel_all_open_orders_request(const CancelAllOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/fapi/v1/allOpenOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllOpenOrdersResponse>
TradeApi::cancel_all_open_orders(const CancelAllOpenOrdersParams& params) const {
    return common::send<CancelAllOpenOrdersResponse>(*client_,
                                                     cancel_all_open_orders_request(params));
}

common::RestRequest
TradeApi::cancel_multiple_orders_request(const CancelMultipleOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/fapi/v1/batchOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderIdList", params.order_id_list);
    common::detail::json::set_param(req.query, "origClientOrderIdList",
                                    params.orig_client_order_id_list);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CancelMultipleOrdersResponseInner>>
TradeApi::cancel_multiple_orders(const CancelMultipleOrdersParams& params) const {
    return common::send<std::vector<CancelMultipleOrdersResponseInner>>(
        *client_, cancel_multiple_orders_request(params));
}

common::RestRequest
TradeApi::modify_multiple_orders_request(const ModifyMultipleOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/fapi/v1/batchOrders";
    common::detail::json::set_param(req.query, "batchOrders", params.batch_orders);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<ModifyMultipleOrdersResponseInner>>
TradeApi::modify_multiple_orders(const ModifyMultipleOrdersParams& params) const {
    return common::send<std::vector<ModifyMultipleOrdersResponseInner>>(
        *client_, modify_multiple_orders_request(params));
}

common::RestRequest
TradeApi::place_multiple_orders_request(const PlaceMultipleOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/batchOrders";
    common::detail::json::set_param(req.query, "batchOrders", params.batch_orders);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<PlaceMultipleOrdersResponseInner>>
TradeApi::place_multiple_orders(const PlaceMultipleOrdersParams& params) const {
    return common::send<std::vector<PlaceMultipleOrdersResponseInner>>(
        *client_, place_multiple_orders_request(params));
}

common::RestRequest TradeApi::cancel_order_request(const CancelOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/fapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelOrderResponse>
TradeApi::cancel_order(const CancelOrderParams& params) const {
    return common::send<CancelOrderResponse>(*client_, cancel_order_request(params));
}

common::RestRequest TradeApi::modify_order_request(const ModifyOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/fapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "priceMatch", params.price_match);
    common::detail::json::set_param(req.query, "modifyId", params.modify_id);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ModifyOrderResponse>
TradeApi::modify_order(const ModifyOrderParams& params) const {
    return common::send<ModifyOrderResponse>(*client_, modify_order_request(params));
}

common::RestRequest TradeApi::new_order_request(const NewOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "priceMatch", params.price_match);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "goodTillDate", params.good_till_date);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<NewOrderResponse> TradeApi::new_order(const NewOrderParams& params) const {
    return common::send<NewOrderResponse>(*client_, new_order_request(params));
}

common::RestRequest TradeApi::query_order_request(const QueryOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryOrderResponse>
TradeApi::query_order(const QueryOrderParams& params) const {
    return common::send<QueryOrderResponse>(*client_, query_order_request(params));
}

common::RestRequest
TradeApi::change_initial_leverage_request(const ChangeInitialLeverageParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/leverage";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "leverage", params.leverage);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeInitialLeverageResponse>
TradeApi::change_initial_leverage(const ChangeInitialLeverageParams& params) const {
    return common::send<ChangeInitialLeverageResponse>(*client_,
                                                       change_initial_leverage_request(params));
}

common::RestRequest
TradeApi::change_margin_type_request(const ChangeMarginTypeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/marginType";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "marginType", params.margin_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeMarginTypeResponse>
TradeApi::change_margin_type(const ChangeMarginTypeParams& params) const {
    return common::send<ChangeMarginTypeResponse>(*client_, change_margin_type_request(params));
}

common::RestRequest
TradeApi::change_multi_assets_mode_request(const ChangeMultiAssetsModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/multiAssetsMargin";
    common::detail::json::set_param(req.query, "multiAssetsMargin", params.multi_assets_margin);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeMultiAssetsModeResponse>
TradeApi::change_multi_assets_mode(const ChangeMultiAssetsModeParams& params) const {
    return common::send<ChangeMultiAssetsModeResponse>(*client_,
                                                       change_multi_assets_mode_request(params));
}

common::RestRequest
TradeApi::change_position_mode_request(const ChangePositionModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/positionSide/dual";
    common::detail::json::set_param(req.query, "dualSidePosition", params.dual_side_position);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangePositionModeResponse>
TradeApi::change_position_mode(const ChangePositionModeParams& params) const {
    return common::send<ChangePositionModeResponse>(*client_, change_position_mode_request(params));
}

common::RestRequest
TradeApi::current_all_algo_open_orders_request(const CurrentAllAlgoOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/openAlgoOrders";
    common::detail::json::set_param(req.query, "algoType", params.algo_type);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CurrentAllAlgoOpenOrdersResponseInner>>
TradeApi::current_all_algo_open_orders(const CurrentAllAlgoOpenOrdersParams& params) const {
    return common::send<std::vector<CurrentAllAlgoOpenOrdersResponseInner>>(
        *client_, current_all_algo_open_orders_request(params));
}

common::RestRequest
TradeApi::current_all_open_orders_request(const CurrentAllOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CurrentAllOpenOrdersResponseInner>>
TradeApi::current_all_open_orders(const CurrentAllOpenOrdersParams& params) const {
    return common::send<std::vector<CurrentAllOpenOrdersResponseInner>>(
        *client_, current_all_open_orders_request(params));
}

common::RestRequest TradeApi::futures_tradfi_perps_contract_request(
    const FuturesTradfiPerpsContractParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/stock/contract";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FuturesTradfiPerpsContractResponse>
TradeApi::futures_tradfi_perps_contract(const FuturesTradfiPerpsContractParams& params) const {
    return common::send<FuturesTradfiPerpsContractResponse>(
        *client_, futures_tradfi_perps_contract_request(params));
}

common::RestRequest
TradeApi::get_order_modify_history_request(const GetOrderModifyHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/orderAmendment";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetOrderModifyHistoryResponseInner>>
TradeApi::get_order_modify_history(const GetOrderModifyHistoryParams& params) const {
    return common::send<std::vector<GetOrderModifyHistoryResponseInner>>(
        *client_, get_order_modify_history_request(params));
}

common::RestRequest TradeApi::get_position_margin_change_history_request(
    const GetPositionMarginChangeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/positionMargin/history";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetPositionMarginChangeHistoryResponseInner>>
TradeApi::get_position_margin_change_history(
    const GetPositionMarginChangeHistoryParams& params) const {
    return common::send<std::vector<GetPositionMarginChangeHistoryResponseInner>>(
        *client_, get_position_margin_change_history_request(params));
}

common::RestRequest TradeApi::modify_isolated_position_margin_request(
    const ModifyIsolatedPositionMarginParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/positionMargin";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ModifyIsolatedPositionMarginResponse>
TradeApi::modify_isolated_position_margin(const ModifyIsolatedPositionMarginParams& params) const {
    return common::send<ModifyIsolatedPositionMarginResponse>(
        *client_, modify_isolated_position_margin_request(params));
}

common::RestRequest TradeApi::position_adl_quantile_estimation_request(
    const PositionAdlQuantileEstimationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/adlQuantile";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<PositionAdlQuantileEstimationResponseInner>>
TradeApi::position_adl_quantile_estimation(
    const PositionAdlQuantileEstimationParams& params) const {
    return common::send<std::vector<PositionAdlQuantileEstimationResponseInner>>(
        *client_, position_adl_quantile_estimation_request(params));
}

common::RestRequest
TradeApi::position_information_v2_request(const PositionInformationV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v2/positionRisk";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<PositionInformationV2ResponseInner>>
TradeApi::position_information_v2(const PositionInformationV2Params& params) const {
    return common::send<std::vector<PositionInformationV2ResponseInner>>(
        *client_, position_information_v2_request(params));
}

common::RestRequest
TradeApi::position_information_v3_request(const PositionInformationV3Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v3/positionRisk";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<PositionInformationV3ResponseInner>>
TradeApi::position_information_v3(const PositionInformationV3Params& params) const {
    return common::send<std::vector<PositionInformationV3ResponseInner>>(
        *client_, position_information_v3_request(params));
}

common::RestRequest
TradeApi::query_all_algo_orders_request(const QueryAllAlgoOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/allAlgoOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryAllAlgoOrdersResponseInner>>
TradeApi::query_all_algo_orders(const QueryAllAlgoOrdersParams& params) const {
    return common::send<std::vector<QueryAllAlgoOrdersResponseInner>>(
        *client_, query_all_algo_orders_request(params));
}

common::RestRequest
TradeApi::query_current_open_order_request(const QueryCurrentOpenOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/openOrder";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCurrentOpenOrderResponse>
TradeApi::query_current_open_order(const QueryCurrentOpenOrderParams& params) const {
    return common::send<QueryCurrentOpenOrderResponse>(*client_,
                                                       query_current_open_order_request(params));
}

common::RestRequest TradeApi::test_order_request(const TestOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/order/test";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "closePosition", params.close_position);
    common::detail::json::set_param(req.query, "activationPrice", params.activation_price);
    common::detail::json::set_param(req.query, "callbackRate", params.callback_rate);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "priceProtect", params.price_protect);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "priceMatch", params.price_match);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "goodTillDate", params.good_till_date);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TestOrderResponse>
TradeApi::test_order(const TestOrderParams& params) const {
    return common::send<TestOrderResponse>(*client_, test_order_request(params));
}

common::RestRequest
TradeApi::users_force_orders_request(const UsersForceOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/forceOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "autoCloseType", params.auto_close_type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<UsersForceOrdersResponseInner>>
TradeApi::users_force_orders(const UsersForceOrdersParams& params) const {
    return common::send<std::vector<UsersForceOrdersResponseInner>>(
        *client_, users_force_orders_request(params));
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
