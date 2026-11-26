//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/trade_api.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(NewCmConditionalOrderSideEnum value) noexcept {
    switch (value) {
    case NewCmConditionalOrderSideEnum::Buy:
        return "BUY";
    case NewCmConditionalOrderSideEnum::Sell:
        return "SELL";
    case NewCmConditionalOrderSideEnum::Unknown:
        break;
    }
    return "";
}

NewCmConditionalOrderSideEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return NewCmConditionalOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return NewCmConditionalOrderSideEnum::Sell;
    }
    return NewCmConditionalOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmConditionalOrderSideEnum value) {
    if (value == NewCmConditionalOrderSideEnum::Unknown) {
        throw std::invalid_argument("NewCmConditionalOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmConditionalOrderStrategyTypeEnum value) noexcept {
    switch (value) {
    case NewCmConditionalOrderStrategyTypeEnum::Stop:
        return "STOP";
    case NewCmConditionalOrderStrategyTypeEnum::StopMarket:
        return "STOP_MARKET";
    case NewCmConditionalOrderStrategyTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case NewCmConditionalOrderStrategyTypeEnum::TakeProfitMarket:
        return "TAKE_PROFIT_MARKET";
    case NewCmConditionalOrderStrategyTypeEnum::TrailingStopMarket:
        return "TRAILING_STOP_MARKET";
    case NewCmConditionalOrderStrategyTypeEnum::Unknown:
        break;
    }
    return "";
}

NewCmConditionalOrderStrategyTypeEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderStrategyTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP") {
        return NewCmConditionalOrderStrategyTypeEnum::Stop;
    }
    if (s == "STOP_MARKET") {
        return NewCmConditionalOrderStrategyTypeEnum::StopMarket;
    }
    if (s == "TAKE_PROFIT") {
        return NewCmConditionalOrderStrategyTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_MARKET") {
        return NewCmConditionalOrderStrategyTypeEnum::TakeProfitMarket;
    }
    if (s == "TRAILING_STOP_MARKET") {
        return NewCmConditionalOrderStrategyTypeEnum::TrailingStopMarket;
    }
    return NewCmConditionalOrderStrategyTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmConditionalOrderStrategyTypeEnum value) {
    if (value == NewCmConditionalOrderStrategyTypeEnum::Unknown) {
        throw std::invalid_argument(
            "NewCmConditionalOrderStrategyTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmConditionalOrderPositionSideEnum value) noexcept {
    switch (value) {
    case NewCmConditionalOrderPositionSideEnum::Both:
        return "BOTH";
    case NewCmConditionalOrderPositionSideEnum::Long:
        return "LONG";
    case NewCmConditionalOrderPositionSideEnum::Short:
        return "SHORT";
    case NewCmConditionalOrderPositionSideEnum::Unknown:
        break;
    }
    return "";
}

NewCmConditionalOrderPositionSideEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderPositionSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return NewCmConditionalOrderPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return NewCmConditionalOrderPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return NewCmConditionalOrderPositionSideEnum::Short;
    }
    return NewCmConditionalOrderPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmConditionalOrderPositionSideEnum value) {
    if (value == NewCmConditionalOrderPositionSideEnum::Unknown) {
        throw std::invalid_argument(
            "NewCmConditionalOrderPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmConditionalOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case NewCmConditionalOrderTimeInForceEnum::Gtc:
        return "GTC";
    case NewCmConditionalOrderTimeInForceEnum::Ioc:
        return "IOC";
    case NewCmConditionalOrderTimeInForceEnum::Fok:
        return "FOK";
    case NewCmConditionalOrderTimeInForceEnum::Gtx:
        return "GTX";
    case NewCmConditionalOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

NewCmConditionalOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return NewCmConditionalOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return NewCmConditionalOrderTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return NewCmConditionalOrderTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return NewCmConditionalOrderTimeInForceEnum::Gtx;
    }
    return NewCmConditionalOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmConditionalOrderTimeInForceEnum value) {
    if (value == NewCmConditionalOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("NewCmConditionalOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmConditionalOrderWorkingTypeEnum value) noexcept {
    switch (value) {
    case NewCmConditionalOrderWorkingTypeEnum::MarkPrice:
        return "MARK_PRICE";
    case NewCmConditionalOrderWorkingTypeEnum::ContractPrice:
        return "CONTRACT_PRICE";
    case NewCmConditionalOrderWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

NewCmConditionalOrderWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARK_PRICE") {
        return NewCmConditionalOrderWorkingTypeEnum::MarkPrice;
    }
    if (s == "CONTRACT_PRICE") {
        return NewCmConditionalOrderWorkingTypeEnum::ContractPrice;
    }
    return NewCmConditionalOrderWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmConditionalOrderWorkingTypeEnum value) {
    if (value == NewCmConditionalOrderWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("NewCmConditionalOrderWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmConditionalOrderPriceProtectEnum value) noexcept {
    switch (value) {
    case NewCmConditionalOrderPriceProtectEnum::True_:
        return "true";
    case NewCmConditionalOrderPriceProtectEnum::False_:
        return "false";
    case NewCmConditionalOrderPriceProtectEnum::Unknown:
        break;
    }
    return "";
}

NewCmConditionalOrderPriceProtectEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderPriceProtectEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewCmConditionalOrderPriceProtectEnum::True_;
    }
    if (s == "false") {
        return NewCmConditionalOrderPriceProtectEnum::False_;
    }
    return NewCmConditionalOrderPriceProtectEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmConditionalOrderPriceProtectEnum value) {
    if (value == NewCmConditionalOrderPriceProtectEnum::Unknown) {
        throw std::invalid_argument(
            "NewCmConditionalOrderPriceProtectEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ModifyCmOrderSideEnum value) noexcept {
    switch (value) {
    case ModifyCmOrderSideEnum::Buy:
        return "BUY";
    case ModifyCmOrderSideEnum::Sell:
        return "SELL";
    case ModifyCmOrderSideEnum::Unknown:
        break;
    }
    return "";
}

ModifyCmOrderSideEnum tag_invoke(boost::json::value_to_tag<ModifyCmOrderSideEnum> /*tag*/,
                                 const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return ModifyCmOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return ModifyCmOrderSideEnum::Sell;
    }
    return ModifyCmOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyCmOrderSideEnum value) {
    if (value == ModifyCmOrderSideEnum::Unknown) {
        throw std::invalid_argument("ModifyCmOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ModifyCmOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case ModifyCmOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case ModifyCmOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case ModifyCmOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case ModifyCmOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case ModifyCmOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case ModifyCmOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case ModifyCmOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case ModifyCmOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case ModifyCmOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

ModifyCmOrderPriceMatchEnum
tag_invoke(boost::json::value_to_tag<ModifyCmOrderPriceMatchEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return ModifyCmOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return ModifyCmOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return ModifyCmOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return ModifyCmOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return ModifyCmOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return ModifyCmOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return ModifyCmOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return ModifyCmOrderPriceMatchEnum::Queue20;
    }
    return ModifyCmOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyCmOrderPriceMatchEnum value) {
    if (value == ModifyCmOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("ModifyCmOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmOrderSideEnum value) noexcept {
    switch (value) {
    case NewCmOrderSideEnum::Buy:
        return "BUY";
    case NewCmOrderSideEnum::Sell:
        return "SELL";
    case NewCmOrderSideEnum::Unknown:
        break;
    }
    return "";
}

NewCmOrderSideEnum tag_invoke(boost::json::value_to_tag<NewCmOrderSideEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return NewCmOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return NewCmOrderSideEnum::Sell;
    }
    return NewCmOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmOrderSideEnum value) {
    if (value == NewCmOrderSideEnum::Unknown) {
        throw std::invalid_argument("NewCmOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmOrderTypeEnum value) noexcept {
    switch (value) {
    case NewCmOrderTypeEnum::Limit:
        return "LIMIT";
    case NewCmOrderTypeEnum::Market:
        return "MARKET";
    case NewCmOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

NewCmOrderTypeEnum tag_invoke(boost::json::value_to_tag<NewCmOrderTypeEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return NewCmOrderTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return NewCmOrderTypeEnum::Market;
    }
    return NewCmOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmOrderTypeEnum value) {
    if (value == NewCmOrderTypeEnum::Unknown) {
        throw std::invalid_argument("NewCmOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmOrderPositionSideEnum value) noexcept {
    switch (value) {
    case NewCmOrderPositionSideEnum::Both:
        return "BOTH";
    case NewCmOrderPositionSideEnum::Long:
        return "LONG";
    case NewCmOrderPositionSideEnum::Short:
        return "SHORT";
    case NewCmOrderPositionSideEnum::Unknown:
        break;
    }
    return "";
}

NewCmOrderPositionSideEnum tag_invoke(boost::json::value_to_tag<NewCmOrderPositionSideEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return NewCmOrderPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return NewCmOrderPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return NewCmOrderPositionSideEnum::Short;
    }
    return NewCmOrderPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmOrderPositionSideEnum value) {
    if (value == NewCmOrderPositionSideEnum::Unknown) {
        throw std::invalid_argument("NewCmOrderPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case NewCmOrderTimeInForceEnum::Gtc:
        return "GTC";
    case NewCmOrderTimeInForceEnum::Ioc:
        return "IOC";
    case NewCmOrderTimeInForceEnum::Fok:
        return "FOK";
    case NewCmOrderTimeInForceEnum::Gtx:
        return "GTX";
    case NewCmOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

NewCmOrderTimeInForceEnum tag_invoke(boost::json::value_to_tag<NewCmOrderTimeInForceEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return NewCmOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return NewCmOrderTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return NewCmOrderTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return NewCmOrderTimeInForceEnum::Gtx;
    }
    return NewCmOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmOrderTimeInForceEnum value) {
    if (value == NewCmOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("NewCmOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmOrderReduceOnlyEnum value) noexcept {
    switch (value) {
    case NewCmOrderReduceOnlyEnum::True_:
        return "true";
    case NewCmOrderReduceOnlyEnum::False_:
        return "false";
    case NewCmOrderReduceOnlyEnum::Unknown:
        break;
    }
    return "";
}

NewCmOrderReduceOnlyEnum tag_invoke(boost::json::value_to_tag<NewCmOrderReduceOnlyEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewCmOrderReduceOnlyEnum::True_;
    }
    if (s == "false") {
        return NewCmOrderReduceOnlyEnum::False_;
    }
    return NewCmOrderReduceOnlyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmOrderReduceOnlyEnum value) {
    if (value == NewCmOrderReduceOnlyEnum::Unknown) {
        throw std::invalid_argument("NewCmOrderReduceOnlyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case NewCmOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case NewCmOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case NewCmOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case NewCmOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case NewCmOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case NewCmOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case NewCmOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case NewCmOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case NewCmOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

NewCmOrderPriceMatchEnum tag_invoke(boost::json::value_to_tag<NewCmOrderPriceMatchEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return NewCmOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return NewCmOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return NewCmOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return NewCmOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return NewCmOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return NewCmOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return NewCmOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return NewCmOrderPriceMatchEnum::Queue20;
    }
    return NewCmOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmOrderPriceMatchEnum value) {
    if (value == NewCmOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("NewCmOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewCmOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case NewCmOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case NewCmOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case NewCmOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

NewCmOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewCmOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return NewCmOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return NewCmOrderNewOrderRespTypeEnum::Result;
    }
    return NewCmOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewCmOrderNewOrderRespTypeEnum value) {
    if (value == NewCmOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("NewCmOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewMarginOrderSideEnum value) noexcept {
    switch (value) {
    case NewMarginOrderSideEnum::Buy:
        return "BUY";
    case NewMarginOrderSideEnum::Sell:
        return "SELL";
    case NewMarginOrderSideEnum::Unknown:
        break;
    }
    return "";
}

NewMarginOrderSideEnum tag_invoke(boost::json::value_to_tag<NewMarginOrderSideEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return NewMarginOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return NewMarginOrderSideEnum::Sell;
    }
    return NewMarginOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewMarginOrderSideEnum value) {
    if (value == NewMarginOrderSideEnum::Unknown) {
        throw std::invalid_argument("NewMarginOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewMarginOrderTypeEnum value) noexcept {
    switch (value) {
    case NewMarginOrderTypeEnum::Limit:
        return "LIMIT";
    case NewMarginOrderTypeEnum::Market:
        return "MARKET";
    case NewMarginOrderTypeEnum::StopLoss:
        return "STOP_LOSS";
    case NewMarginOrderTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case NewMarginOrderTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case NewMarginOrderTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case NewMarginOrderTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case NewMarginOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

NewMarginOrderTypeEnum tag_invoke(boost::json::value_to_tag<NewMarginOrderTypeEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return NewMarginOrderTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return NewMarginOrderTypeEnum::Market;
    }
    if (s == "STOP_LOSS") {
        return NewMarginOrderTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return NewMarginOrderTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return NewMarginOrderTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return NewMarginOrderTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return NewMarginOrderTypeEnum::LimitMaker;
    }
    return NewMarginOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewMarginOrderTypeEnum value) {
    if (value == NewMarginOrderTypeEnum::Unknown) {
        throw std::invalid_argument("NewMarginOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewMarginOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case NewMarginOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case NewMarginOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case NewMarginOrderNewOrderRespTypeEnum::Full:
        return "FULL";
    case NewMarginOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

NewMarginOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewMarginOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return NewMarginOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return NewMarginOrderNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return NewMarginOrderNewOrderRespTypeEnum::Full;
    }
    return NewMarginOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewMarginOrderNewOrderRespTypeEnum value) {
    if (value == NewMarginOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("NewMarginOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewMarginOrderSideEffectTypeEnum value) noexcept {
    switch (value) {
    case NewMarginOrderSideEffectTypeEnum::NoSideEffect:
        return "NO_SIDE_EFFECT";
    case NewMarginOrderSideEffectTypeEnum::MarginBuy:
        return "MARGIN_BUY";
    case NewMarginOrderSideEffectTypeEnum::AutoRepay:
        return "AUTO_REPAY";
    case NewMarginOrderSideEffectTypeEnum::AutoBorrowRepay:
        return "AUTO_BORROW_REPAY";
    case NewMarginOrderSideEffectTypeEnum::Unknown:
        break;
    }
    return "";
}

NewMarginOrderSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<NewMarginOrderSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NO_SIDE_EFFECT") {
        return NewMarginOrderSideEffectTypeEnum::NoSideEffect;
    }
    if (s == "MARGIN_BUY") {
        return NewMarginOrderSideEffectTypeEnum::MarginBuy;
    }
    if (s == "AUTO_REPAY") {
        return NewMarginOrderSideEffectTypeEnum::AutoRepay;
    }
    if (s == "AUTO_BORROW_REPAY") {
        return NewMarginOrderSideEffectTypeEnum::AutoBorrowRepay;
    }
    return NewMarginOrderSideEffectTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewMarginOrderSideEffectTypeEnum value) {
    if (value == NewMarginOrderSideEffectTypeEnum::Unknown) {
        throw std::invalid_argument("NewMarginOrderSideEffectTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewMarginOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case NewMarginOrderTimeInForceEnum::Gtc:
        return "GTC";
    case NewMarginOrderTimeInForceEnum::Ioc:
        return "IOC";
    case NewMarginOrderTimeInForceEnum::Fok:
        return "FOK";
    case NewMarginOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

NewMarginOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<NewMarginOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return NewMarginOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return NewMarginOrderTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return NewMarginOrderTimeInForceEnum::Fok;
    }
    return NewMarginOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewMarginOrderTimeInForceEnum value) {
    if (value == NewMarginOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("NewMarginOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewMarginOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case NewMarginOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case NewMarginOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case NewMarginOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case NewMarginOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case NewMarginOrderSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

NewMarginOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewMarginOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return NewMarginOrderSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return NewMarginOrderSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_BOTH") {
        return NewMarginOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "EXPIRE_MAKER") {
        return NewMarginOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    return NewMarginOrderSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewMarginOrderSelfTradePreventionModeEnum value) {
    if (value == NewMarginOrderSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "NewMarginOrderSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderAlgoTypeEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderAlgoTypeEnum::Conditional:
        return "CONDITIONAL";
    case NewUmAlgoOrderAlgoTypeEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderAlgoTypeEnum tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderAlgoTypeEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "CONDITIONAL") {
        return NewUmAlgoOrderAlgoTypeEnum::Conditional;
    }
    return NewUmAlgoOrderAlgoTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderAlgoTypeEnum value) {
    if (value == NewUmAlgoOrderAlgoTypeEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderAlgoTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderSideEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderSideEnum::Buy:
        return "BUY";
    case NewUmAlgoOrderSideEnum::Sell:
        return "SELL";
    case NewUmAlgoOrderSideEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderSideEnum tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderSideEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return NewUmAlgoOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return NewUmAlgoOrderSideEnum::Sell;
    }
    return NewUmAlgoOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderSideEnum value) {
    if (value == NewUmAlgoOrderSideEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderTypeEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderTypeEnum::Stop:
        return "STOP";
    case NewUmAlgoOrderTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case NewUmAlgoOrderTypeEnum::StopMarket:
        return "STOP_MARKET";
    case NewUmAlgoOrderTypeEnum::TakeProfitMarket:
        return "TAKE_PROFIT_MARKET";
    case NewUmAlgoOrderTypeEnum::TrailingStopMarket:
        return "TRAILING_STOP_MARKET";
    case NewUmAlgoOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderTypeEnum tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderTypeEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP") {
        return NewUmAlgoOrderTypeEnum::Stop;
    }
    if (s == "TAKE_PROFIT") {
        return NewUmAlgoOrderTypeEnum::TakeProfit;
    }
    if (s == "STOP_MARKET") {
        return NewUmAlgoOrderTypeEnum::StopMarket;
    }
    if (s == "TAKE_PROFIT_MARKET") {
        return NewUmAlgoOrderTypeEnum::TakeProfitMarket;
    }
    if (s == "TRAILING_STOP_MARKET") {
        return NewUmAlgoOrderTypeEnum::TrailingStopMarket;
    }
    return NewUmAlgoOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderTypeEnum value) {
    if (value == NewUmAlgoOrderTypeEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderPositionSideEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderPositionSideEnum::Both:
        return "BOTH";
    case NewUmAlgoOrderPositionSideEnum::Long:
        return "LONG";
    case NewUmAlgoOrderPositionSideEnum::Short:
        return "SHORT";
    case NewUmAlgoOrderPositionSideEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderPositionSideEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderPositionSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return NewUmAlgoOrderPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return NewUmAlgoOrderPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return NewUmAlgoOrderPositionSideEnum::Short;
    }
    return NewUmAlgoOrderPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderPositionSideEnum value) {
    if (value == NewUmAlgoOrderPositionSideEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderTimeInForceEnum::Ioc:
        return "IOC";
    case NewUmAlgoOrderTimeInForceEnum::Gtc:
        return "GTC";
    case NewUmAlgoOrderTimeInForceEnum::Fok:
        return "FOK";
    case NewUmAlgoOrderTimeInForceEnum::Gtx:
        return "GTX";
    case NewUmAlgoOrderTimeInForceEnum::Gtd:
        return "GTD";
    case NewUmAlgoOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "IOC") {
        return NewUmAlgoOrderTimeInForceEnum::Ioc;
    }
    if (s == "GTC") {
        return NewUmAlgoOrderTimeInForceEnum::Gtc;
    }
    if (s == "FOK") {
        return NewUmAlgoOrderTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return NewUmAlgoOrderTimeInForceEnum::Gtx;
    }
    if (s == "GTD") {
        return NewUmAlgoOrderTimeInForceEnum::Gtd;
    }
    return NewUmAlgoOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderTimeInForceEnum value) {
    if (value == NewUmAlgoOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderWorkingTypeEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderWorkingTypeEnum::MarkPrice:
        return "MARK_PRICE";
    case NewUmAlgoOrderWorkingTypeEnum::ContractPrice:
        return "CONTRACT_PRICE";
    case NewUmAlgoOrderWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARK_PRICE") {
        return NewUmAlgoOrderWorkingTypeEnum::MarkPrice;
    }
    if (s == "CONTRACT_PRICE") {
        return NewUmAlgoOrderWorkingTypeEnum::ContractPrice;
    }
    return NewUmAlgoOrderWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderWorkingTypeEnum value) {
    if (value == NewUmAlgoOrderWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case NewUmAlgoOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case NewUmAlgoOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case NewUmAlgoOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case NewUmAlgoOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case NewUmAlgoOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case NewUmAlgoOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case NewUmAlgoOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case NewUmAlgoOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderPriceMatchEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderPriceMatchEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return NewUmAlgoOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return NewUmAlgoOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return NewUmAlgoOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return NewUmAlgoOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return NewUmAlgoOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return NewUmAlgoOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return NewUmAlgoOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return NewUmAlgoOrderPriceMatchEnum::Queue20;
    }
    return NewUmAlgoOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderPriceMatchEnum value) {
    if (value == NewUmAlgoOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderClosePositionEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderClosePositionEnum::True_:
        return "true";
    case NewUmAlgoOrderClosePositionEnum::False_:
        return "false";
    case NewUmAlgoOrderClosePositionEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderClosePositionEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderClosePositionEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewUmAlgoOrderClosePositionEnum::True_;
    }
    if (s == "false") {
        return NewUmAlgoOrderClosePositionEnum::False_;
    }
    return NewUmAlgoOrderClosePositionEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderClosePositionEnum value) {
    if (value == NewUmAlgoOrderClosePositionEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderClosePositionEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderPriceProtectEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderPriceProtectEnum::True_:
        return "true";
    case NewUmAlgoOrderPriceProtectEnum::False_:
        return "false";
    case NewUmAlgoOrderPriceProtectEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderPriceProtectEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderPriceProtectEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewUmAlgoOrderPriceProtectEnum::True_;
    }
    if (s == "false") {
        return NewUmAlgoOrderPriceProtectEnum::False_;
    }
    return NewUmAlgoOrderPriceProtectEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderPriceProtectEnum value) {
    if (value == NewUmAlgoOrderPriceProtectEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderPriceProtectEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderReduceOnlyEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderReduceOnlyEnum::True_:
        return "true";
    case NewUmAlgoOrderReduceOnlyEnum::False_:
        return "false";
    case NewUmAlgoOrderReduceOnlyEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderReduceOnlyEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderReduceOnlyEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewUmAlgoOrderReduceOnlyEnum::True_;
    }
    if (s == "false") {
        return NewUmAlgoOrderReduceOnlyEnum::False_;
    }
    return NewUmAlgoOrderReduceOnlyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderReduceOnlyEnum value) {
    if (value == NewUmAlgoOrderReduceOnlyEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderReduceOnlyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case NewUmAlgoOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case NewUmAlgoOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return NewUmAlgoOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return NewUmAlgoOrderNewOrderRespTypeEnum::Result;
    }
    return NewUmAlgoOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderNewOrderRespTypeEnum value) {
    if (value == NewUmAlgoOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("NewUmAlgoOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmAlgoOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case NewUmAlgoOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case NewUmAlgoOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case NewUmAlgoOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case NewUmAlgoOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case NewUmAlgoOrderSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

NewUmAlgoOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return NewUmAlgoOrderSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return NewUmAlgoOrderSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return NewUmAlgoOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return NewUmAlgoOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    return NewUmAlgoOrderSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmAlgoOrderSelfTradePreventionModeEnum value) {
    if (value == NewUmAlgoOrderSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "NewUmAlgoOrderSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ModifyUmOrderSideEnum value) noexcept {
    switch (value) {
    case ModifyUmOrderSideEnum::Buy:
        return "BUY";
    case ModifyUmOrderSideEnum::Sell:
        return "SELL";
    case ModifyUmOrderSideEnum::Unknown:
        break;
    }
    return "";
}

ModifyUmOrderSideEnum tag_invoke(boost::json::value_to_tag<ModifyUmOrderSideEnum> /*tag*/,
                                 const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return ModifyUmOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return ModifyUmOrderSideEnum::Sell;
    }
    return ModifyUmOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyUmOrderSideEnum value) {
    if (value == ModifyUmOrderSideEnum::Unknown) {
        throw std::invalid_argument("ModifyUmOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ModifyUmOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case ModifyUmOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case ModifyUmOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case ModifyUmOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case ModifyUmOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case ModifyUmOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case ModifyUmOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case ModifyUmOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case ModifyUmOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case ModifyUmOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

ModifyUmOrderPriceMatchEnum
tag_invoke(boost::json::value_to_tag<ModifyUmOrderPriceMatchEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return ModifyUmOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return ModifyUmOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return ModifyUmOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return ModifyUmOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return ModifyUmOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return ModifyUmOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return ModifyUmOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return ModifyUmOrderPriceMatchEnum::Queue20;
    }
    return ModifyUmOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyUmOrderPriceMatchEnum value) {
    if (value == ModifyUmOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("ModifyUmOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmOrderSideEnum value) noexcept {
    switch (value) {
    case NewUmOrderSideEnum::Buy:
        return "BUY";
    case NewUmOrderSideEnum::Sell:
        return "SELL";
    case NewUmOrderSideEnum::Unknown:
        break;
    }
    return "";
}

NewUmOrderSideEnum tag_invoke(boost::json::value_to_tag<NewUmOrderSideEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return NewUmOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return NewUmOrderSideEnum::Sell;
    }
    return NewUmOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmOrderSideEnum value) {
    if (value == NewUmOrderSideEnum::Unknown) {
        throw std::invalid_argument("NewUmOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmOrderTypeEnum value) noexcept {
    switch (value) {
    case NewUmOrderTypeEnum::Limit:
        return "LIMIT";
    case NewUmOrderTypeEnum::Market:
        return "MARKET";
    case NewUmOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

NewUmOrderTypeEnum tag_invoke(boost::json::value_to_tag<NewUmOrderTypeEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return NewUmOrderTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return NewUmOrderTypeEnum::Market;
    }
    return NewUmOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmOrderTypeEnum value) {
    if (value == NewUmOrderTypeEnum::Unknown) {
        throw std::invalid_argument("NewUmOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmOrderPositionSideEnum value) noexcept {
    switch (value) {
    case NewUmOrderPositionSideEnum::Both:
        return "BOTH";
    case NewUmOrderPositionSideEnum::Long:
        return "LONG";
    case NewUmOrderPositionSideEnum::Short:
        return "SHORT";
    case NewUmOrderPositionSideEnum::Unknown:
        break;
    }
    return "";
}

NewUmOrderPositionSideEnum tag_invoke(boost::json::value_to_tag<NewUmOrderPositionSideEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return NewUmOrderPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return NewUmOrderPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return NewUmOrderPositionSideEnum::Short;
    }
    return NewUmOrderPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmOrderPositionSideEnum value) {
    if (value == NewUmOrderPositionSideEnum::Unknown) {
        throw std::invalid_argument("NewUmOrderPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case NewUmOrderTimeInForceEnum::Gtc:
        return "GTC";
    case NewUmOrderTimeInForceEnum::Ioc:
        return "IOC";
    case NewUmOrderTimeInForceEnum::Fok:
        return "FOK";
    case NewUmOrderTimeInForceEnum::Gtx:
        return "GTX";
    case NewUmOrderTimeInForceEnum::Gtd:
        return "GTD";
    case NewUmOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

NewUmOrderTimeInForceEnum tag_invoke(boost::json::value_to_tag<NewUmOrderTimeInForceEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return NewUmOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return NewUmOrderTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return NewUmOrderTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return NewUmOrderTimeInForceEnum::Gtx;
    }
    if (s == "GTD") {
        return NewUmOrderTimeInForceEnum::Gtd;
    }
    return NewUmOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmOrderTimeInForceEnum value) {
    if (value == NewUmOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("NewUmOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmOrderReduceOnlyEnum value) noexcept {
    switch (value) {
    case NewUmOrderReduceOnlyEnum::True_:
        return "true";
    case NewUmOrderReduceOnlyEnum::False_:
        return "false";
    case NewUmOrderReduceOnlyEnum::Unknown:
        break;
    }
    return "";
}

NewUmOrderReduceOnlyEnum tag_invoke(boost::json::value_to_tag<NewUmOrderReduceOnlyEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewUmOrderReduceOnlyEnum::True_;
    }
    if (s == "false") {
        return NewUmOrderReduceOnlyEnum::False_;
    }
    return NewUmOrderReduceOnlyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmOrderReduceOnlyEnum value) {
    if (value == NewUmOrderReduceOnlyEnum::Unknown) {
        throw std::invalid_argument("NewUmOrderReduceOnlyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case NewUmOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case NewUmOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case NewUmOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

NewUmOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewUmOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return NewUmOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return NewUmOrderNewOrderRespTypeEnum::Result;
    }
    return NewUmOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmOrderNewOrderRespTypeEnum value) {
    if (value == NewUmOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("NewUmOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case NewUmOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case NewUmOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case NewUmOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case NewUmOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case NewUmOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case NewUmOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case NewUmOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case NewUmOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case NewUmOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

NewUmOrderPriceMatchEnum tag_invoke(boost::json::value_to_tag<NewUmOrderPriceMatchEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return NewUmOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return NewUmOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return NewUmOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return NewUmOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return NewUmOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return NewUmOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return NewUmOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return NewUmOrderPriceMatchEnum::Queue20;
    }
    return NewUmOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmOrderPriceMatchEnum value) {
    if (value == NewUmOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("NewUmOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewUmOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case NewUmOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case NewUmOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case NewUmOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case NewUmOrderSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

NewUmOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewUmOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "EXPIRE_TAKER") {
        return NewUmOrderSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_BOTH") {
        return NewUmOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "EXPIRE_MAKER") {
        return NewUmOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    return NewUmOrderSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewUmOrderSelfTradePreventionModeEnum value) {
    if (value == NewUmOrderSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "NewUmOrderSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum value) noexcept {
    switch (value) {
    case ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::True_:
        return "true";
    case ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::False_:
        return "false";
    case ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::Unknown:
        break;
    }
    return "";
}

ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum
tag_invoke(boost::json::value_to_tag<ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::True_;
    }
    if (s == "false") {
        return ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::False_;
    }
    return ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum value) {
    if (value == ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::Unknown) {
        throw std::invalid_argument(
            "ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOcoSideEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOcoSideEnum::Buy:
        return "BUY";
    case MarginAccountNewOcoSideEnum::Sell:
        return "SELL";
    case MarginAccountNewOcoSideEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOcoSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return MarginAccountNewOcoSideEnum::Buy;
    }
    if (s == "SELL") {
        return MarginAccountNewOcoSideEnum::Sell;
    }
    return MarginAccountNewOcoSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOcoSideEnum value) {
    if (value == MarginAccountNewOcoSideEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOcoSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOcoStopLimitTimeInForceEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOcoStopLimitTimeInForceEnum::Gtc:
        return "GTC";
    case MarginAccountNewOcoStopLimitTimeInForceEnum::Ioc:
        return "IOC";
    case MarginAccountNewOcoStopLimitTimeInForceEnum::Fok:
        return "FOK";
    case MarginAccountNewOcoStopLimitTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOcoStopLimitTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoStopLimitTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return MarginAccountNewOcoStopLimitTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return MarginAccountNewOcoStopLimitTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return MarginAccountNewOcoStopLimitTimeInForceEnum::Fok;
    }
    return MarginAccountNewOcoStopLimitTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOcoStopLimitTimeInForceEnum value) {
    if (value == MarginAccountNewOcoStopLimitTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOcoStopLimitTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOcoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOcoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case MarginAccountNewOcoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case MarginAccountNewOcoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOcoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return MarginAccountNewOcoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return MarginAccountNewOcoNewOrderRespTypeEnum::Result;
    }
    return MarginAccountNewOcoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOcoNewOrderRespTypeEnum value) {
    if (value == MarginAccountNewOcoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOcoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOcoSideEffectTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOcoSideEffectTypeEnum::NoSideEffect:
        return "NO_SIDE_EFFECT";
    case MarginAccountNewOcoSideEffectTypeEnum::MarginBuy:
        return "MARGIN_BUY";
    case MarginAccountNewOcoSideEffectTypeEnum::AutoRepay:
        return "AUTO_REPAY";
    case MarginAccountNewOcoSideEffectTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOcoSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NO_SIDE_EFFECT") {
        return MarginAccountNewOcoSideEffectTypeEnum::NoSideEffect;
    }
    if (s == "MARGIN_BUY") {
        return MarginAccountNewOcoSideEffectTypeEnum::MarginBuy;
    }
    if (s == "AUTO_REPAY") {
        return MarginAccountNewOcoSideEffectTypeEnum::AutoRepay;
    }
    return MarginAccountNewOcoSideEffectTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOcoSideEffectTypeEnum value) {
    if (value == MarginAccountNewOcoSideEffectTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOcoSideEffectTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryUsersCmForceOrdersAutoCloseTypeEnum value) noexcept {
    switch (value) {
    case QueryUsersCmForceOrdersAutoCloseTypeEnum::Liquidation:
        return "LIQUIDATION";
    case QueryUsersCmForceOrdersAutoCloseTypeEnum::Adl:
        return "ADL";
    case QueryUsersCmForceOrdersAutoCloseTypeEnum::Unknown:
        break;
    }
    return "";
}

QueryUsersCmForceOrdersAutoCloseTypeEnum
tag_invoke(boost::json::value_to_tag<QueryUsersCmForceOrdersAutoCloseTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIQUIDATION") {
        return QueryUsersCmForceOrdersAutoCloseTypeEnum::Liquidation;
    }
    if (s == "ADL") {
        return QueryUsersCmForceOrdersAutoCloseTypeEnum::Adl;
    }
    return QueryUsersCmForceOrdersAutoCloseTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryUsersCmForceOrdersAutoCloseTypeEnum value) {
    if (value == QueryUsersCmForceOrdersAutoCloseTypeEnum::Unknown) {
        throw std::invalid_argument(
            "QueryUsersCmForceOrdersAutoCloseTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryUsersUmForceOrdersAutoCloseTypeEnum value) noexcept {
    switch (value) {
    case QueryUsersUmForceOrdersAutoCloseTypeEnum::Liquidation:
        return "LIQUIDATION";
    case QueryUsersUmForceOrdersAutoCloseTypeEnum::Adl:
        return "ADL";
    case QueryUsersUmForceOrdersAutoCloseTypeEnum::Unknown:
        break;
    }
    return "";
}

QueryUsersUmForceOrdersAutoCloseTypeEnum
tag_invoke(boost::json::value_to_tag<QueryUsersUmForceOrdersAutoCloseTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIQUIDATION") {
        return QueryUsersUmForceOrdersAutoCloseTypeEnum::Liquidation;
    }
    if (s == "ADL") {
        return QueryUsersUmForceOrdersAutoCloseTypeEnum::Adl;
    }
    return QueryUsersUmForceOrdersAutoCloseTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryUsersUmForceOrdersAutoCloseTypeEnum value) {
    if (value == QueryUsersUmForceOrdersAutoCloseTypeEnum::Unknown) {
        throw std::invalid_argument(
            "QueryUsersUmForceOrdersAutoCloseTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest TradeApi::cancel_all_cm_open_conditional_orders_request(
    const CancelAllCmOpenConditionalOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/cm/conditional/allOpenOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllCmOpenConditionalOrdersResponse>
TradeApi::cancel_all_cm_open_conditional_orders(
    const CancelAllCmOpenConditionalOrdersParams& params) const {
    return common::send<CancelAllCmOpenConditionalOrdersResponse>(
        *client_, cancel_all_cm_open_conditional_orders_request(params));
}

common::RestRequest
TradeApi::cancel_all_cm_open_orders_request(const CancelAllCmOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/cm/allOpenOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllCmOpenOrdersResponse>
TradeApi::cancel_all_cm_open_orders(const CancelAllCmOpenOrdersParams& params) const {
    return common::send<CancelAllCmOpenOrdersResponse>(*client_,
                                                       cancel_all_cm_open_orders_request(params));
}

common::RestRequest TradeApi::cancel_all_um_algo_open_orders_request(
    const CancelAllUmAlgoOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/um/algo/allOpenOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllUmAlgoOpenOrdersResponse>
TradeApi::cancel_all_um_algo_open_orders(const CancelAllUmAlgoOpenOrdersParams& params) const {
    return common::send<CancelAllUmAlgoOpenOrdersResponse>(
        *client_, cancel_all_um_algo_open_orders_request(params));
}

common::RestRequest
TradeApi::cancel_all_um_open_orders_request(const CancelAllUmOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/um/allOpenOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllUmOpenOrdersResponse>
TradeApi::cancel_all_um_open_orders(const CancelAllUmOpenOrdersParams& params) const {
    return common::send<CancelAllUmOpenOrdersResponse>(*client_,
                                                       cancel_all_um_open_orders_request(params));
}

common::RestRequest
TradeApi::cancel_cm_conditional_order_request(const CancelCmConditionalOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/cm/conditional/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "strategyId", params.strategy_id);
    common::detail::json::set_param(req.query, "newClientStrategyId",
                                    params.new_client_strategy_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelCmConditionalOrderResponse>
TradeApi::cancel_cm_conditional_order(const CancelCmConditionalOrderParams& params) const {
    return common::send<CancelCmConditionalOrderResponse>(
        *client_, cancel_cm_conditional_order_request(params));
}

common::RestRequest
TradeApi::new_cm_conditional_order_request(const NewCmConditionalOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/cm/conditional/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "strategyType", params.strategy_type);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "priceProtect", params.price_protect);
    common::detail::json::set_param(req.query, "newClientStrategyId",
                                    params.new_client_strategy_id);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "activationPrice", params.activation_price);
    common::detail::json::set_param(req.query, "callbackRate", params.callback_rate);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<NewCmConditionalOrderResponse>
TradeApi::new_cm_conditional_order(const NewCmConditionalOrderParams& params) const {
    return common::send<NewCmConditionalOrderResponse>(*client_,
                                                       new_cm_conditional_order_request(params));
}

common::RestRequest TradeApi::cancel_cm_order_request(const CancelCmOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/cm/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelCmOrderResponse>
TradeApi::cancel_cm_order(const CancelCmOrderParams& params) const {
    return common::send<CancelCmOrderResponse>(*client_, cancel_cm_order_request(params));
}

common::RestRequest TradeApi::modify_cm_order_request(const ModifyCmOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/papi/v1/cm/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "priceMatch", params.price_match);
    common::detail::json::set_param(req.query, "modifyId", params.modify_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ModifyCmOrderResponse>
TradeApi::modify_cm_order(const ModifyCmOrderParams& params) const {
    return common::send<ModifyCmOrderResponse>(*client_, modify_cm_order_request(params));
}

common::RestRequest TradeApi::new_cm_order_request(const NewCmOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/cm/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "priceMatch", params.price_match);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<NewCmOrderResponse>
TradeApi::new_cm_order(const NewCmOrderParams& params) const {
    return common::send<NewCmOrderResponse>(*client_, new_cm_order_request(params));
}

common::RestRequest TradeApi::query_cm_order_request(const QueryCmOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCmOrderResponse>
TradeApi::query_cm_order(const QueryCmOrderParams& params) const {
    return common::send<QueryCmOrderResponse>(*client_, query_cm_order_request(params));
}

common::RestRequest TradeApi::cancel_margin_account_all_open_orders_on_a_symbol_request(
    const CancelMarginAccountAllOpenOrdersOnASymbolParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/margin/allOpenOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CancelMarginAccountAllOpenOrdersOnASymbolResponseInner>>
TradeApi::cancel_margin_account_all_open_orders_on_a_symbol(
    const CancelMarginAccountAllOpenOrdersOnASymbolParams& params) const {
    return common::send<std::vector<CancelMarginAccountAllOpenOrdersOnASymbolResponseInner>>(
        *client_, cancel_margin_account_all_open_orders_on_a_symbol_request(params));
}

common::RestRequest TradeApi::cancel_margin_account_oco_orders_request(
    const CancelMarginAccountOcoOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/margin/orderList";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderListId", params.order_list_id);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelMarginAccountOcoOrdersResponse>
TradeApi::cancel_margin_account_oco_orders(const CancelMarginAccountOcoOrdersParams& params) const {
    return common::send<CancelMarginAccountOcoOrdersResponse>(
        *client_, cancel_margin_account_oco_orders_request(params));
}

common::RestRequest
TradeApi::query_margin_accounts_oco_request(const QueryMarginAccountsOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/orderList";
    common::detail::json::set_param(req.query, "orderListId", params.order_list_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryMarginAccountsOcoResponse>
TradeApi::query_margin_accounts_oco(const QueryMarginAccountsOcoParams& params) const {
    return common::send<QueryMarginAccountsOcoResponse>(*client_,
                                                        query_margin_accounts_oco_request(params));
}

common::RestRequest
TradeApi::cancel_margin_account_order_request(const CancelMarginAccountOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/margin/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelMarginAccountOrderResponse>
TradeApi::cancel_margin_account_order(const CancelMarginAccountOrderParams& params) const {
    return common::send<CancelMarginAccountOrderResponse>(
        *client_, cancel_margin_account_order_request(params));
}

common::RestRequest TradeApi::new_margin_order_request(const NewMarginOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/margin/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "quoteOrderQty", params.quote_order_qty);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(req.query, "sideEffectType", params.side_effect_type);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "autoRepayAtCancel", params.auto_repay_at_cancel);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<NewMarginOrderResponse>
TradeApi::new_margin_order(const NewMarginOrderParams& params) const {
    return common::send<NewMarginOrderResponse>(*client_, new_margin_order_request(params));
}

common::RestRequest
TradeApi::query_margin_account_order_request(const QueryMarginAccountOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryMarginAccountOrderResponse>
TradeApi::query_margin_account_order(const QueryMarginAccountOrderParams& params) const {
    return common::send<QueryMarginAccountOrderResponse>(
        *client_, query_margin_account_order_request(params));
}

common::RestRequest
TradeApi::cancel_um_algo_order_request(const CancelUmAlgoOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/um/algo/order";
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelUmAlgoOrderResponse>
TradeApi::cancel_um_algo_order(const CancelUmAlgoOrderParams& params) const {
    return common::send<CancelUmAlgoOrderResponse>(*client_, cancel_um_algo_order_request(params));
}

common::RestRequest TradeApi::new_um_algo_order_request(const NewUmAlgoOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/um/algo/order";
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

common::RestApiResponse<NewUmAlgoOrderResponse>
TradeApi::new_um_algo_order(const NewUmAlgoOrderParams& params) const {
    return common::send<NewUmAlgoOrderResponse>(*client_, new_um_algo_order_request(params));
}

common::RestRequest TradeApi::cancel_um_order_request(const CancelUmOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/papi/v1/um/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelUmOrderResponse>
TradeApi::cancel_um_order(const CancelUmOrderParams& params) const {
    return common::send<CancelUmOrderResponse>(*client_, cancel_um_order_request(params));
}

common::RestRequest TradeApi::modify_um_order_request(const ModifyUmOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/papi/v1/um/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "priceMatch", params.price_match);
    common::detail::json::set_param(req.query, "modifyId", params.modify_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ModifyUmOrderResponse>
TradeApi::modify_um_order(const ModifyUmOrderParams& params) const {
    return common::send<ModifyUmOrderResponse>(*client_, modify_um_order_request(params));
}

common::RestRequest TradeApi::new_um_order_request(const NewUmOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/um/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
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

common::RestApiResponse<NewUmOrderResponse>
TradeApi::new_um_order(const NewUmOrderParams& params) const {
    return common::send<NewUmOrderResponse>(*client_, new_um_order_request(params));
}

common::RestRequest TradeApi::query_um_order_request(const QueryUmOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryUmOrderResponse>
TradeApi::query_um_order(const QueryUmOrderParams& params) const {
    return common::send<QueryUmOrderResponse>(*client_, query_um_order_request(params));
}

common::RestRequest
TradeApi::cm_account_trade_list_request(const CmAccountTradeListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/userTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CmAccountTradeListResponseInner>>
TradeApi::cm_account_trade_list(const CmAccountTradeListParams& params) const {
    return common::send<std::vector<CmAccountTradeListResponseInner>>(
        *client_, cm_account_trade_list_request(params));
}

common::RestRequest TradeApi::cm_position_adl_quantile_estimation_request(
    const CmPositionAdlQuantileEstimationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/adlQuantile";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CmPositionAdlQuantileEstimationResponseInner>>
TradeApi::cm_position_adl_quantile_estimation(
    const CmPositionAdlQuantileEstimationParams& params) const {
    return common::send<std::vector<CmPositionAdlQuantileEstimationResponseInner>>(
        *client_, cm_position_adl_quantile_estimation_request(params));
}

common::RestRequest TradeApi::futures_tradfi_perps_contract_request(
    const FuturesTradfiPerpsContractParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/um/stock/contract";
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

common::RestRequest TradeApi::get_um_futures_bnb_burn_status_request(
    const GetUmFuturesBnbBurnStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/feeBurn";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetUmFuturesBnbBurnStatusResponse>
TradeApi::get_um_futures_bnb_burn_status(const GetUmFuturesBnbBurnStatusParams& params) const {
    return common::send<GetUmFuturesBnbBurnStatusResponse>(
        *client_, get_um_futures_bnb_burn_status_request(params));
}

common::RestRequest TradeApi::toggle_bnb_burn_on_um_futures_trade_request(
    const ToggleBnbBurnOnUmFuturesTradeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/um/feeBurn";
    common::detail::json::set_param(req.query, "feeBurn", params.fee_burn);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ToggleBnbBurnOnUmFuturesTradeResponse>
TradeApi::toggle_bnb_burn_on_um_futures_trade(
    const ToggleBnbBurnOnUmFuturesTradeParams& params) const {
    return common::send<ToggleBnbBurnOnUmFuturesTradeResponse>(
        *client_, toggle_bnb_burn_on_um_futures_trade_request(params));
}

common::RestRequest
TradeApi::margin_account_borrow_request(const MarginAccountBorrowParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/marginLoan";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountBorrowResponse>
TradeApi::margin_account_borrow(const MarginAccountBorrowParams& params) const {
    return common::send<MarginAccountBorrowResponse>(*client_,
                                                     margin_account_borrow_request(params));
}

common::RestRequest
TradeApi::margin_account_new_oco_request(const MarginAccountNewOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/margin/order/oco";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "limitClientOrderId", params.limit_client_order_id);
    common::detail::json::set_param(req.query, "limitIcebergQty", params.limit_iceberg_qty);
    common::detail::json::set_param(req.query, "stopClientOrderId", params.stop_client_order_id);
    common::detail::json::set_param(req.query, "stopLimitPrice", params.stop_limit_price);
    common::detail::json::set_param(req.query, "stopIcebergQty", params.stop_iceberg_qty);
    common::detail::json::set_param(req.query, "stopLimitTimeInForce",
                                    params.stop_limit_time_in_force);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "sideEffectType", params.side_effect_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountNewOcoResponse>
TradeApi::margin_account_new_oco(const MarginAccountNewOcoParams& params) const {
    return common::send<MarginAccountNewOcoResponse>(*client_,
                                                     margin_account_new_oco_request(params));
}

common::RestRequest
TradeApi::margin_account_repay_request(const MarginAccountRepayParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/repayLoan";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountRepayResponse>
TradeApi::margin_account_repay(const MarginAccountRepayParams& params) const {
    return common::send<MarginAccountRepayResponse>(*client_, margin_account_repay_request(params));
}

common::RestRequest
TradeApi::margin_account_repay_debt_request(const MarginAccountRepayDebtParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/papi/v1/margin/repay-debt";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "specifyRepayAssets", params.specify_repay_assets);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountRepayDebtResponse>
TradeApi::margin_account_repay_debt(const MarginAccountRepayDebtParams& params) const {
    return common::send<MarginAccountRepayDebtResponse>(*client_,
                                                        margin_account_repay_debt_request(params));
}

common::RestRequest
TradeApi::margin_account_trade_list_request(const MarginAccountTradeListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/myTrades";
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

common::RestApiResponse<std::vector<MarginAccountTradeListResponseInner>>
TradeApi::margin_account_trade_list(const MarginAccountTradeListParams& params) const {
    return common::send<std::vector<MarginAccountTradeListResponseInner>>(
        *client_, margin_account_trade_list_request(params));
}

common::RestRequest TradeApi::query_all_cm_conditional_orders_request(
    const QueryAllCmConditionalOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/conditional/allOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "strategyId", params.strategy_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryAllCmConditionalOrdersResponseInner>>
TradeApi::query_all_cm_conditional_orders(const QueryAllCmConditionalOrdersParams& params) const {
    return common::send<std::vector<QueryAllCmConditionalOrdersResponseInner>>(
        *client_, query_all_cm_conditional_orders_request(params));
}

common::RestRequest
TradeApi::query_all_cm_orders_request(const QueryAllCmOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/allOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>
TradeApi::query_all_cm_orders(const QueryAllCmOrdersParams& params) const {
    return common::send<std::vector<QueryAllCmOrdersResponseInner>>(
        *client_, query_all_cm_orders_request(params));
}

common::RestRequest TradeApi::query_all_current_cm_open_conditional_orders_request(
    const QueryAllCurrentCmOpenConditionalOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/conditional/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryAllCurrentCmOpenConditionalOrdersResponseInner>>
TradeApi::query_all_current_cm_open_conditional_orders(
    const QueryAllCurrentCmOpenConditionalOrdersParams& params) const {
    return common::send<std::vector<QueryAllCurrentCmOpenConditionalOrdersResponseInner>>(
        *client_, query_all_current_cm_open_conditional_orders_request(params));
}

common::RestRequest TradeApi::query_all_current_cm_open_orders_request(
    const QueryAllCurrentCmOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>
TradeApi::query_all_current_cm_open_orders(const QueryAllCurrentCmOpenOrdersParams& params) const {
    return common::send<std::vector<QueryAllCmOrdersResponseInner>>(
        *client_, query_all_current_cm_open_orders_request(params));
}

common::RestRequest TradeApi::query_all_current_um_open_algo_orders_request(
    const QueryAllCurrentUmOpenAlgoOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/algo/openAlgoOrders";
    common::detail::json::set_param(req.query, "algoType", params.algo_type);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryAllCurrentUmOpenAlgoOrdersResponseInner>>
TradeApi::query_all_current_um_open_algo_orders(
    const QueryAllCurrentUmOpenAlgoOrdersParams& params) const {
    return common::send<std::vector<QueryAllCurrentUmOpenAlgoOrdersResponseInner>>(
        *client_, query_all_current_um_open_algo_orders_request(params));
}

common::RestRequest TradeApi::query_all_current_um_open_orders_request(
    const QueryAllCurrentUmOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>
TradeApi::query_all_current_um_open_orders(const QueryAllCurrentUmOpenOrdersParams& params) const {
    return common::send<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>(
        *client_, query_all_current_um_open_orders_request(params));
}

common::RestRequest TradeApi::query_all_margin_account_orders_request(
    const QueryAllMarginAccountOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/allOrders";
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

common::RestApiResponse<std::vector<QueryAllMarginAccountOrdersResponseInner>>
TradeApi::query_all_margin_account_orders(const QueryAllMarginAccountOrdersParams& params) const {
    return common::send<std::vector<QueryAllMarginAccountOrdersResponseInner>>(
        *client_, query_all_margin_account_orders_request(params));
}

common::RestRequest
TradeApi::query_all_um_orders_request(const QueryAllUmOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/allOrders";
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

common::RestApiResponse<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>
TradeApi::query_all_um_orders(const QueryAllUmOrdersParams& params) const {
    return common::send<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>(
        *client_, query_all_um_orders_request(params));
}

common::RestRequest TradeApi::query_cm_conditional_order_history_request(
    const QueryCmConditionalOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/conditional/orderHistory";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "strategyId", params.strategy_id);
    common::detail::json::set_param(req.query, "newClientStrategyId",
                                    params.new_client_strategy_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCmConditionalOrderHistoryResponse>
TradeApi::query_cm_conditional_order_history(
    const QueryCmConditionalOrderHistoryParams& params) const {
    return common::send<QueryCmConditionalOrderHistoryResponse>(
        *client_, query_cm_conditional_order_history_request(params));
}

common::RestRequest TradeApi::query_cm_modify_order_history_request(
    const QueryCmModifyOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/orderAmendment";
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

common::RestApiResponse<std::vector<QueryCmModifyOrderHistoryResponseInner>>
TradeApi::query_cm_modify_order_history(const QueryCmModifyOrderHistoryParams& params) const {
    return common::send<std::vector<QueryCmModifyOrderHistoryResponseInner>>(
        *client_, query_cm_modify_order_history_request(params));
}

common::RestRequest TradeApi::query_current_cm_open_conditional_order_request(
    const QueryCurrentCmOpenConditionalOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/conditional/openOrder";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "strategyId", params.strategy_id);
    common::detail::json::set_param(req.query, "newClientStrategyId",
                                    params.new_client_strategy_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCurrentCmOpenConditionalOrderResponse>
TradeApi::query_current_cm_open_conditional_order(
    const QueryCurrentCmOpenConditionalOrderParams& params) const {
    return common::send<QueryCurrentCmOpenConditionalOrderResponse>(
        *client_, query_current_cm_open_conditional_order_request(params));
}

common::RestRequest
TradeApi::query_current_cm_open_order_request(const QueryCurrentCmOpenOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/openOrder";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>
TradeApi::query_current_cm_open_order(const QueryCurrentCmOpenOrderParams& params) const {
    return common::send<std::vector<QueryAllCmOrdersResponseInner>>(
        *client_, query_current_cm_open_order_request(params));
}

common::RestRequest TradeApi::query_current_margin_open_order_request(
    const QueryCurrentMarginOpenOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryCurrentMarginOpenOrderResponseInner>>
TradeApi::query_current_margin_open_order(const QueryCurrentMarginOpenOrderParams& params) const {
    return common::send<std::vector<QueryCurrentMarginOpenOrderResponseInner>>(
        *client_, query_current_margin_open_order_request(params));
}

common::RestRequest TradeApi::query_current_um_open_algo_order_request(
    const QueryCurrentUmOpenAlgoOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/algo/algoOrder";
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCurrentUmOpenAlgoOrderResponse>
TradeApi::query_current_um_open_algo_order(const QueryCurrentUmOpenAlgoOrderParams& params) const {
    return common::send<QueryCurrentUmOpenAlgoOrderResponse>(
        *client_, query_current_um_open_algo_order_request(params));
}

common::RestRequest
TradeApi::query_current_um_open_order_request(const QueryCurrentUmOpenOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/openOrder";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCurrentUmOpenOrderResponse>
TradeApi::query_current_um_open_order(const QueryCurrentUmOpenOrderParams& params) const {
    return common::send<QueryCurrentUmOpenOrderResponse>(
        *client_, query_current_um_open_order_request(params));
}

common::RestRequest TradeApi::query_margin_accounts_all_oco_request(
    const QueryMarginAccountsAllOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/allOrderList";
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryMarginAccountsAllOcoResponseInner>>
TradeApi::query_margin_accounts_all_oco(const QueryMarginAccountsAllOcoParams& params) const {
    return common::send<std::vector<QueryMarginAccountsAllOcoResponseInner>>(
        *client_, query_margin_accounts_all_oco_request(params));
}

common::RestRequest TradeApi::query_margin_accounts_open_oco_request(
    const QueryMarginAccountsOpenOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/openOrderList";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryMarginAccountsOpenOcoResponseInner>>
TradeApi::query_margin_accounts_open_oco(const QueryMarginAccountsOpenOcoParams& params) const {
    return common::send<std::vector<QueryMarginAccountsOpenOcoResponseInner>>(
        *client_, query_margin_accounts_open_oco_request(params));
}

common::RestRequest
TradeApi::query_um_algo_order_history_request(const QueryUmAlgoOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/algo/allAlgoOrders";
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

common::RestApiResponse<std::vector<QueryUmAlgoOrderHistoryResponseInner>>
TradeApi::query_um_algo_order_history(const QueryUmAlgoOrderHistoryParams& params) const {
    return common::send<std::vector<QueryUmAlgoOrderHistoryResponseInner>>(
        *client_, query_um_algo_order_history_request(params));
}

common::RestRequest TradeApi::query_um_modify_order_history_request(
    const QueryUmModifyOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/orderAmendment";
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

common::RestApiResponse<std::vector<QueryUmModifyOrderHistoryResponseInner>>
TradeApi::query_um_modify_order_history(const QueryUmModifyOrderHistoryParams& params) const {
    return common::send<std::vector<QueryUmModifyOrderHistoryResponseInner>>(
        *client_, query_um_modify_order_history_request(params));
}

common::RestRequest
TradeApi::query_users_cm_force_orders_request(const QueryUsersCmForceOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/cm/forceOrders";
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

common::RestApiResponse<std::vector<QueryUsersCmForceOrdersResponseInner>>
TradeApi::query_users_cm_force_orders(const QueryUsersCmForceOrdersParams& params) const {
    return common::send<std::vector<QueryUsersCmForceOrdersResponseInner>>(
        *client_, query_users_cm_force_orders_request(params));
}

common::RestRequest TradeApi::query_users_margin_force_orders_request(
    const QueryUsersMarginForceOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/margin/forceOrders";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryUsersMarginForceOrdersResponse>
TradeApi::query_users_margin_force_orders(const QueryUsersMarginForceOrdersParams& params) const {
    return common::send<QueryUsersMarginForceOrdersResponse>(
        *client_, query_users_margin_force_orders_request(params));
}

common::RestRequest
TradeApi::query_users_um_force_orders_request(const QueryUsersUmForceOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/forceOrders";
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

common::RestApiResponse<std::vector<QueryUsersUmForceOrdersResponseInner>>
TradeApi::query_users_um_force_orders(const QueryUsersUmForceOrdersParams& params) const {
    return common::send<std::vector<QueryUsersUmForceOrdersResponseInner>>(
        *client_, query_users_um_force_orders_request(params));
}

common::RestRequest
TradeApi::um_account_trade_list_request(const UmAccountTradeListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/userTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<UmAccountTradeListResponseInner>>
TradeApi::um_account_trade_list(const UmAccountTradeListParams& params) const {
    return common::send<std::vector<UmAccountTradeListResponseInner>>(
        *client_, um_account_trade_list_request(params));
}

common::RestRequest TradeApi::um_position_adl_quantile_estimation_request(
    const UmPositionAdlQuantileEstimationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/papi/v1/um/adlQuantile";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<UmPositionAdlQuantileEstimationResponseInner>>
TradeApi::um_position_adl_quantile_estimation(
    const UmPositionAdlQuantileEstimationParams& params) const {
    return common::send<std::vector<UmPositionAdlQuantileEstimationResponseInner>>(
        *client_, um_position_adl_quantile_estimation_request(params));
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
