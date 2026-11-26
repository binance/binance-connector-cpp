//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/trade_api.hpp>

namespace binance::spot::rest_api {

namespace {
constexpr bool kHasTimeUnit = true;
} // namespace

std::string_view to_string(DeleteOrderCancelRestrictionsEnum value) noexcept {
    switch (value) {
    case DeleteOrderCancelRestrictionsEnum::OnlyNew:
        return "ONLY_NEW";
    case DeleteOrderCancelRestrictionsEnum::OnlyPartiallyFilled:
        return "ONLY_PARTIALLY_FILLED";
    case DeleteOrderCancelRestrictionsEnum::Unknown:
        break;
    }
    return "";
}

DeleteOrderCancelRestrictionsEnum
tag_invoke(boost::json::value_to_tag<DeleteOrderCancelRestrictionsEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ONLY_NEW") {
        return DeleteOrderCancelRestrictionsEnum::OnlyNew;
    }
    if (s == "ONLY_PARTIALLY_FILLED") {
        return DeleteOrderCancelRestrictionsEnum::OnlyPartiallyFilled;
    }
    return DeleteOrderCancelRestrictionsEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                DeleteOrderCancelRestrictionsEnum value) {
    if (value == DeleteOrderCancelRestrictionsEnum::Unknown) {
        throw std::invalid_argument("DeleteOrderCancelRestrictionsEnum::Unknown cannot be sent");
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
    case NewOrderTypeEnum::Market:
        return "MARKET";
    case NewOrderTypeEnum::Limit:
        return "LIMIT";
    case NewOrderTypeEnum::StopLoss:
        return "STOP_LOSS";
    case NewOrderTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case NewOrderTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case NewOrderTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case NewOrderTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case NewOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderTypeEnum tag_invoke(boost::json::value_to_tag<NewOrderTypeEnum> /*tag*/,
                            const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return NewOrderTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return NewOrderTypeEnum::Limit;
    }
    if (s == "STOP_LOSS") {
        return NewOrderTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return NewOrderTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return NewOrderTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return NewOrderTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return NewOrderTypeEnum::LimitMaker;
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
    return NewOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderTimeInForceEnum value) {
    if (value == NewOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("NewOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case NewOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case NewOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case NewOrderNewOrderRespTypeEnum::Full:
        return "FULL";
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
    if (s == "FULL") {
        return NewOrderNewOrderRespTypeEnum::Full;
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

std::string_view to_string(NewOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case NewOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case NewOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case NewOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case NewOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case NewOrderSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case NewOrderSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
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
    if (s == "EXPIRE_MAKER") {
        return NewOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return NewOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return NewOrderSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return NewOrderSelfTradePreventionModeEnum::Transfer;
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

std::string_view to_string(NewOrderPegPriceTypeEnum value) noexcept {
    switch (value) {
    case NewOrderPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case NewOrderPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case NewOrderPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderPegPriceTypeEnum tag_invoke(boost::json::value_to_tag<NewOrderPegPriceTypeEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return NewOrderPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return NewOrderPegPriceTypeEnum::MarketPeg;
    }
    return NewOrderPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderPegPriceTypeEnum value) {
    if (value == NewOrderPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("NewOrderPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case NewOrderPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case NewOrderPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderPegOffsetTypeEnum tag_invoke(boost::json::value_to_tag<NewOrderPegOffsetTypeEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return NewOrderPegOffsetTypeEnum::PriceLevel;
    }
    return NewOrderPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderPegOffsetTypeEnum value) {
    if (value == NewOrderPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("NewOrderPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplaceSideEnum value) noexcept {
    switch (value) {
    case OrderCancelReplaceSideEnum::Buy:
        return "BUY";
    case OrderCancelReplaceSideEnum::Sell:
        return "SELL";
    case OrderCancelReplaceSideEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplaceSideEnum tag_invoke(boost::json::value_to_tag<OrderCancelReplaceSideEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderCancelReplaceSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderCancelReplaceSideEnum::Sell;
    }
    return OrderCancelReplaceSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplaceSideEnum value) {
    if (value == OrderCancelReplaceSideEnum::Unknown) {
        throw std::invalid_argument("OrderCancelReplaceSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplaceTypeEnum value) noexcept {
    switch (value) {
    case OrderCancelReplaceTypeEnum::Market:
        return "MARKET";
    case OrderCancelReplaceTypeEnum::Limit:
        return "LIMIT";
    case OrderCancelReplaceTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderCancelReplaceTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderCancelReplaceTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderCancelReplaceTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderCancelReplaceTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderCancelReplaceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplaceTypeEnum tag_invoke(boost::json::value_to_tag<OrderCancelReplaceTypeEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return OrderCancelReplaceTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return OrderCancelReplaceTypeEnum::Limit;
    }
    if (s == "STOP_LOSS") {
        return OrderCancelReplaceTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderCancelReplaceTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderCancelReplaceTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderCancelReplaceTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderCancelReplaceTypeEnum::LimitMaker;
    }
    return OrderCancelReplaceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplaceTypeEnum value) {
    if (value == OrderCancelReplaceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderCancelReplaceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplaceCancelReplaceModeEnum value) noexcept {
    switch (value) {
    case OrderCancelReplaceCancelReplaceModeEnum::StopOnFailure:
        return "STOP_ON_FAILURE";
    case OrderCancelReplaceCancelReplaceModeEnum::AllowFailure:
        return "ALLOW_FAILURE";
    case OrderCancelReplaceCancelReplaceModeEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplaceCancelReplaceModeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceCancelReplaceModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_ON_FAILURE") {
        return OrderCancelReplaceCancelReplaceModeEnum::StopOnFailure;
    }
    if (s == "ALLOW_FAILURE") {
        return OrderCancelReplaceCancelReplaceModeEnum::AllowFailure;
    }
    return OrderCancelReplaceCancelReplaceModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplaceCancelReplaceModeEnum value) {
    if (value == OrderCancelReplaceCancelReplaceModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderCancelReplaceCancelReplaceModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplaceTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderCancelReplaceTimeInForceEnum::Gtc:
        return "GTC";
    case OrderCancelReplaceTimeInForceEnum::Ioc:
        return "IOC";
    case OrderCancelReplaceTimeInForceEnum::Fok:
        return "FOK";
    case OrderCancelReplaceTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplaceTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderCancelReplaceTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderCancelReplaceTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderCancelReplaceTimeInForceEnum::Fok;
    }
    return OrderCancelReplaceTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplaceTimeInForceEnum value) {
    if (value == OrderCancelReplaceTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderCancelReplaceTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplaceNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderCancelReplaceNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderCancelReplaceNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderCancelReplaceNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderCancelReplaceNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplaceNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderCancelReplaceNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderCancelReplaceNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderCancelReplaceNewOrderRespTypeEnum::Full;
    }
    return OrderCancelReplaceNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplaceNewOrderRespTypeEnum value) {
    if (value == OrderCancelReplaceNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderCancelReplaceNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplaceSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderCancelReplaceSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderCancelReplaceSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderCancelReplaceSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderCancelReplaceSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderCancelReplaceSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderCancelReplaceSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderCancelReplaceSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplaceSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderCancelReplaceSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderCancelReplaceSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderCancelReplaceSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderCancelReplaceSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderCancelReplaceSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderCancelReplaceSelfTradePreventionModeEnum::Transfer;
    }
    return OrderCancelReplaceSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplaceSelfTradePreventionModeEnum value) {
    if (value == OrderCancelReplaceSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderCancelReplaceSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplaceCancelRestrictionsEnum value) noexcept {
    switch (value) {
    case OrderCancelReplaceCancelRestrictionsEnum::OnlyNew:
        return "ONLY_NEW";
    case OrderCancelReplaceCancelRestrictionsEnum::OnlyPartiallyFilled:
        return "ONLY_PARTIALLY_FILLED";
    case OrderCancelReplaceCancelRestrictionsEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplaceCancelRestrictionsEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceCancelRestrictionsEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ONLY_NEW") {
        return OrderCancelReplaceCancelRestrictionsEnum::OnlyNew;
    }
    if (s == "ONLY_PARTIALLY_FILLED") {
        return OrderCancelReplaceCancelRestrictionsEnum::OnlyPartiallyFilled;
    }
    return OrderCancelReplaceCancelRestrictionsEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplaceCancelRestrictionsEnum value) {
    if (value == OrderCancelReplaceCancelRestrictionsEnum::Unknown) {
        throw std::invalid_argument(
            "OrderCancelReplaceCancelRestrictionsEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplaceOrderRateLimitExceededModeEnum value) noexcept {
    switch (value) {
    case OrderCancelReplaceOrderRateLimitExceededModeEnum::DoNothing:
        return "DO_NOTHING";
    case OrderCancelReplaceOrderRateLimitExceededModeEnum::CancelOnly:
        return "CANCEL_ONLY";
    case OrderCancelReplaceOrderRateLimitExceededModeEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplaceOrderRateLimitExceededModeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceOrderRateLimitExceededModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "DO_NOTHING") {
        return OrderCancelReplaceOrderRateLimitExceededModeEnum::DoNothing;
    }
    if (s == "CANCEL_ONLY") {
        return OrderCancelReplaceOrderRateLimitExceededModeEnum::CancelOnly;
    }
    return OrderCancelReplaceOrderRateLimitExceededModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplaceOrderRateLimitExceededModeEnum value) {
    if (value == OrderCancelReplaceOrderRateLimitExceededModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderCancelReplaceOrderRateLimitExceededModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplacePegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderCancelReplacePegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderCancelReplacePegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderCancelReplacePegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplacePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplacePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderCancelReplacePegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderCancelReplacePegPriceTypeEnum::MarketPeg;
    }
    return OrderCancelReplacePegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplacePegPriceTypeEnum value) {
    if (value == OrderCancelReplacePegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderCancelReplacePegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderCancelReplacePegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderCancelReplacePegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderCancelReplacePegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelReplacePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplacePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderCancelReplacePegOffsetTypeEnum::PriceLevel;
    }
    return OrderCancelReplacePegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelReplacePegOffsetTypeEnum value) {
    if (value == OrderCancelReplacePegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("OrderCancelReplacePegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoSideEnum value) noexcept {
    switch (value) {
    case OrderListOcoSideEnum::Buy:
        return "BUY";
    case OrderListOcoSideEnum::Sell:
        return "SELL";
    case OrderListOcoSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoSideEnum tag_invoke(boost::json::value_to_tag<OrderListOcoSideEnum> /*tag*/,
                                const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListOcoSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListOcoSideEnum::Sell;
    }
    return OrderListOcoSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoSideEnum value) {
    if (value == OrderListOcoSideEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoAboveTypeEnum value) noexcept {
    switch (value) {
    case OrderListOcoAboveTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListOcoAboveTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListOcoAboveTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListOcoAboveTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListOcoAboveTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListOcoAboveTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoAboveTypeEnum tag_invoke(boost::json::value_to_tag<OrderListOcoAboveTypeEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListOcoAboveTypeEnum::StopLossLimit;
    }
    if (s == "STOP_LOSS") {
        return OrderListOcoAboveTypeEnum::StopLoss;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListOcoAboveTypeEnum::LimitMaker;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListOcoAboveTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListOcoAboveTypeEnum::TakeProfitLimit;
    }
    return OrderListOcoAboveTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoAboveTypeEnum value) {
    if (value == OrderListOcoAboveTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoAboveTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoBelowTypeEnum value) noexcept {
    switch (value) {
    case OrderListOcoBelowTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListOcoBelowTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListOcoBelowTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListOcoBelowTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListOcoBelowTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoBelowTypeEnum tag_invoke(boost::json::value_to_tag<OrderListOcoBelowTypeEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS") {
        return OrderListOcoBelowTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListOcoBelowTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListOcoBelowTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListOcoBelowTypeEnum::TakeProfitLimit;
    }
    return OrderListOcoBelowTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoBelowTypeEnum value) {
    if (value == OrderListOcoBelowTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoBelowTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoAboveTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOcoAboveTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOcoAboveTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOcoAboveTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOcoAboveTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOcoAboveTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOcoAboveTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOcoAboveTimeInForceEnum::Fok;
    }
    return OrderListOcoAboveTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoAboveTimeInForceEnum value) {
    if (value == OrderListOcoAboveTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoAboveTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoAbovePegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOcoAbovePegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOcoAbovePegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOcoAbovePegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOcoAbovePegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOcoAbovePegPriceTypeEnum::MarketPeg;
    }
    return OrderListOcoAbovePegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoAbovePegPriceTypeEnum value) {
    if (value == OrderListOcoAbovePegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoAbovePegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoAbovePegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOcoAbovePegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOcoAbovePegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOcoAbovePegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOcoAbovePegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoAbovePegOffsetTypeEnum value) {
    if (value == OrderListOcoAbovePegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoAbovePegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoBelowTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOcoBelowTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOcoBelowTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOcoBelowTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOcoBelowTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOcoBelowTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOcoBelowTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOcoBelowTimeInForceEnum::Fok;
    }
    return OrderListOcoBelowTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoBelowTimeInForceEnum value) {
    if (value == OrderListOcoBelowTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoBelowTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoBelowPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOcoBelowPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOcoBelowPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOcoBelowPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOcoBelowPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOcoBelowPegPriceTypeEnum::MarketPeg;
    }
    return OrderListOcoBelowPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoBelowPegPriceTypeEnum value) {
    if (value == OrderListOcoBelowPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoBelowPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoBelowPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOcoBelowPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOcoBelowPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOcoBelowPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOcoBelowPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoBelowPegOffsetTypeEnum value) {
    if (value == OrderListOcoBelowPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoBelowPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListOcoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListOcoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListOcoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListOcoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListOcoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListOcoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListOcoNewOrderRespTypeEnum::Full;
    }
    return OrderListOcoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoNewOrderRespTypeEnum value) {
    if (value == OrderListOcoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOcoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOcoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListOcoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListOcoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListOcoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListOcoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListOcoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListOcoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListOcoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOcoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListOcoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListOcoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListOcoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListOcoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListOcoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListOcoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListOcoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOcoSelfTradePreventionModeEnum value) {
    if (value == OrderListOcoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOcoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoWorkingTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpoWorkingTypeEnum::Limit:
        return "LIMIT";
    case OrderListOpoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListOpoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListOpoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListOpoWorkingTypeEnum::LimitMaker;
    }
    return OrderListOpoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoWorkingTypeEnum value) {
    if (value == OrderListOpoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoWorkingSideEnum value) noexcept {
    switch (value) {
    case OrderListOpoWorkingSideEnum::Buy:
        return "BUY";
    case OrderListOpoWorkingSideEnum::Sell:
        return "SELL";
    case OrderListOpoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListOpoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListOpoWorkingSideEnum::Sell;
    }
    return OrderListOpoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoWorkingSideEnum value) {
    if (value == OrderListOpoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoPendingTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpoPendingTypeEnum::Limit:
        return "LIMIT";
    case OrderListOpoPendingTypeEnum::Market:
        return "MARKET";
    case OrderListOpoPendingTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListOpoPendingTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListOpoPendingTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListOpoPendingTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListOpoPendingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListOpoPendingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoPendingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoPendingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListOpoPendingTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return OrderListOpoPendingTypeEnum::Market;
    }
    if (s == "STOP_LOSS") {
        return OrderListOpoPendingTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListOpoPendingTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListOpoPendingTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListOpoPendingTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListOpoPendingTypeEnum::LimitMaker;
    }
    return OrderListOpoPendingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoPendingTypeEnum value) {
    if (value == OrderListOpoPendingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoPendingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoPendingSideEnum value) noexcept {
    switch (value) {
    case OrderListOpoPendingSideEnum::Buy:
        return "BUY";
    case OrderListOpoPendingSideEnum::Sell:
        return "SELL";
    case OrderListOpoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListOpoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListOpoPendingSideEnum::Sell;
    }
    return OrderListOpoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoPendingSideEnum value) {
    if (value == OrderListOpoPendingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListOpoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListOpoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListOpoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListOpoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListOpoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListOpoNewOrderRespTypeEnum::Full;
    }
    return OrderListOpoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoNewOrderRespTypeEnum value) {
    if (value == OrderListOpoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListOpoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListOpoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListOpoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListOpoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListOpoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListOpoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListOpoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListOpoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListOpoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListOpoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListOpoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListOpoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListOpoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListOpoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoSelfTradePreventionModeEnum value) {
    if (value == OrderListOpoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOpoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOpoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOpoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOpoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOpoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOpoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOpoWorkingTimeInForceEnum::Fok;
    }
    return OrderListOpoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoWorkingTimeInForceEnum value) {
    if (value == OrderListOpoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoWorkingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpoWorkingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOpoWorkingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOpoWorkingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOpoWorkingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOpoWorkingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListOpoWorkingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoWorkingPegPriceTypeEnum value) {
    if (value == OrderListOpoWorkingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoWorkingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoWorkingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpoWorkingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOpoWorkingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOpoWorkingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOpoWorkingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoWorkingPegOffsetTypeEnum value) {
    if (value == OrderListOpoWorkingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoWorkingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoPendingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOpoPendingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOpoPendingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOpoPendingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOpoPendingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOpoPendingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOpoPendingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOpoPendingTimeInForceEnum::Fok;
    }
    return OrderListOpoPendingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoPendingTimeInForceEnum value) {
    if (value == OrderListOpoPendingTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoPendingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoPendingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpoPendingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOpoPendingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOpoPendingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoPendingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoPendingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOpoPendingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOpoPendingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListOpoPendingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoPendingPegPriceTypeEnum value) {
    if (value == OrderListOpoPendingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoPendingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpoPendingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpoPendingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOpoPendingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpoPendingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoPendingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOpoPendingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOpoPendingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpoPendingPegOffsetTypeEnum value) {
    if (value == OrderListOpoPendingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpoPendingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoWorkingTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoWorkingTypeEnum::Limit:
        return "LIMIT";
    case OrderListOpocoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListOpocoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListOpocoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListOpocoWorkingTypeEnum::LimitMaker;
    }
    return OrderListOpocoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoWorkingTypeEnum value) {
    if (value == OrderListOpocoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpocoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoWorkingSideEnum value) noexcept {
    switch (value) {
    case OrderListOpocoWorkingSideEnum::Buy:
        return "BUY";
    case OrderListOpocoWorkingSideEnum::Sell:
        return "SELL";
    case OrderListOpocoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListOpocoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListOpocoWorkingSideEnum::Sell;
    }
    return OrderListOpocoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoWorkingSideEnum value) {
    if (value == OrderListOpocoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListOpocoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoPendingSideEnum value) noexcept {
    switch (value) {
    case OrderListOpocoPendingSideEnum::Buy:
        return "BUY";
    case OrderListOpocoPendingSideEnum::Sell:
        return "SELL";
    case OrderListOpocoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListOpocoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListOpocoPendingSideEnum::Sell;
    }
    return OrderListOpocoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoPendingSideEnum value) {
    if (value == OrderListOpocoPendingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListOpocoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoPendingAboveTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoPendingAboveTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListOpocoPendingAboveTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListOpocoPendingAboveTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListOpocoPendingAboveTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListOpocoPendingAboveTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListOpocoPendingAboveTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListOpocoPendingAboveTypeEnum::StopLossLimit;
    }
    if (s == "STOP_LOSS") {
        return OrderListOpocoPendingAboveTypeEnum::StopLoss;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListOpocoPendingAboveTypeEnum::LimitMaker;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListOpocoPendingAboveTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListOpocoPendingAboveTypeEnum::TakeProfitLimit;
    }
    return OrderListOpocoPendingAboveTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoPendingAboveTypeEnum value) {
    if (value == OrderListOpocoPendingAboveTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpocoPendingAboveTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListOpocoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListOpocoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListOpocoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListOpocoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListOpocoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListOpocoNewOrderRespTypeEnum::Full;
    }
    return OrderListOpocoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoNewOrderRespTypeEnum value) {
    if (value == OrderListOpocoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpocoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListOpocoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListOpocoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListOpocoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListOpocoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListOpocoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListOpocoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListOpocoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListOpocoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListOpocoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListOpocoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListOpocoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListOpocoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListOpocoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoSelfTradePreventionModeEnum value) {
    if (value == OrderListOpocoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpocoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOpocoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOpocoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOpocoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOpocoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOpocoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOpocoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOpocoWorkingTimeInForceEnum::Fok;
    }
    return OrderListOpocoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoWorkingTimeInForceEnum value) {
    if (value == OrderListOpocoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderListOpocoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoWorkingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoWorkingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOpocoWorkingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOpocoWorkingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOpocoWorkingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOpocoWorkingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListOpocoWorkingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoWorkingPegPriceTypeEnum value) {
    if (value == OrderListOpocoWorkingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpocoWorkingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoWorkingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoWorkingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOpocoWorkingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOpocoWorkingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOpocoWorkingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoWorkingPegOffsetTypeEnum value) {
    if (value == OrderListOpocoWorkingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpocoWorkingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoPendingAboveTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOpocoPendingAboveTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOpocoPendingAboveTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOpocoPendingAboveTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOpocoPendingAboveTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOpocoPendingAboveTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOpocoPendingAboveTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOpocoPendingAboveTimeInForceEnum::Fok;
    }
    return OrderListOpocoPendingAboveTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoPendingAboveTimeInForceEnum value) {
    if (value == OrderListOpocoPendingAboveTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpocoPendingAboveTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoPendingAbovePegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoPendingAbovePegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOpocoPendingAbovePegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOpocoPendingAbovePegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoPendingAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOpocoPendingAbovePegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOpocoPendingAbovePegPriceTypeEnum::MarketPeg;
    }
    return OrderListOpocoPendingAbovePegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoPendingAbovePegPriceTypeEnum value) {
    if (value == OrderListOpocoPendingAbovePegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpocoPendingAbovePegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoPendingAbovePegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoPendingAbovePegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOpocoPendingAbovePegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoPendingAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOpocoPendingAbovePegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOpocoPendingAbovePegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoPendingAbovePegOffsetTypeEnum value) {
    if (value == OrderListOpocoPendingAbovePegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpocoPendingAbovePegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoPendingBelowTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoPendingBelowTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListOpocoPendingBelowTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListOpocoPendingBelowTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListOpocoPendingBelowTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListOpocoPendingBelowTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS") {
        return OrderListOpocoPendingBelowTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListOpocoPendingBelowTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListOpocoPendingBelowTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListOpocoPendingBelowTypeEnum::TakeProfitLimit;
    }
    return OrderListOpocoPendingBelowTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoPendingBelowTypeEnum value) {
    if (value == OrderListOpocoPendingBelowTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOpocoPendingBelowTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoPendingBelowTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOpocoPendingBelowTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOpocoPendingBelowTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOpocoPendingBelowTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOpocoPendingBelowTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOpocoPendingBelowTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOpocoPendingBelowTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOpocoPendingBelowTimeInForceEnum::Fok;
    }
    return OrderListOpocoPendingBelowTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoPendingBelowTimeInForceEnum value) {
    if (value == OrderListOpocoPendingBelowTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpocoPendingBelowTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoPendingBelowPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoPendingBelowPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOpocoPendingBelowPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOpocoPendingBelowPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoPendingBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOpocoPendingBelowPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOpocoPendingBelowPegPriceTypeEnum::MarketPeg;
    }
    return OrderListOpocoPendingBelowPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoPendingBelowPegPriceTypeEnum value) {
    if (value == OrderListOpocoPendingBelowPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpocoPendingBelowPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOpocoPendingBelowPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOpocoPendingBelowPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOpocoPendingBelowPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOpocoPendingBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOpocoPendingBelowPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOpocoPendingBelowPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOpocoPendingBelowPegOffsetTypeEnum value) {
    if (value == OrderListOpocoPendingBelowPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOpocoPendingBelowPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoWorkingTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtoWorkingTypeEnum::Limit:
        return "LIMIT";
    case OrderListOtoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListOtoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListOtoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListOtoWorkingTypeEnum::LimitMaker;
    }
    return OrderListOtoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoWorkingTypeEnum value) {
    if (value == OrderListOtoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoWorkingSideEnum value) noexcept {
    switch (value) {
    case OrderListOtoWorkingSideEnum::Buy:
        return "BUY";
    case OrderListOtoWorkingSideEnum::Sell:
        return "SELL";
    case OrderListOtoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListOtoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListOtoWorkingSideEnum::Sell;
    }
    return OrderListOtoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoWorkingSideEnum value) {
    if (value == OrderListOtoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoPendingTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtoPendingTypeEnum::Limit:
        return "LIMIT";
    case OrderListOtoPendingTypeEnum::Market:
        return "MARKET";
    case OrderListOtoPendingTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListOtoPendingTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListOtoPendingTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListOtoPendingTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListOtoPendingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListOtoPendingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoPendingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoPendingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListOtoPendingTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return OrderListOtoPendingTypeEnum::Market;
    }
    if (s == "STOP_LOSS") {
        return OrderListOtoPendingTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListOtoPendingTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListOtoPendingTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListOtoPendingTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListOtoPendingTypeEnum::LimitMaker;
    }
    return OrderListOtoPendingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoPendingTypeEnum value) {
    if (value == OrderListOtoPendingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoPendingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoPendingSideEnum value) noexcept {
    switch (value) {
    case OrderListOtoPendingSideEnum::Buy:
        return "BUY";
    case OrderListOtoPendingSideEnum::Sell:
        return "SELL";
    case OrderListOtoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListOtoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListOtoPendingSideEnum::Sell;
    }
    return OrderListOtoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoPendingSideEnum value) {
    if (value == OrderListOtoPendingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListOtoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListOtoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListOtoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListOtoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListOtoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListOtoNewOrderRespTypeEnum::Full;
    }
    return OrderListOtoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoNewOrderRespTypeEnum value) {
    if (value == OrderListOtoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListOtoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListOtoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListOtoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListOtoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListOtoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListOtoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListOtoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListOtoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListOtoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListOtoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListOtoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListOtoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListOtoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListOtoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoSelfTradePreventionModeEnum value) {
    if (value == OrderListOtoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOtoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOtoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOtoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOtoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOtoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOtoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOtoWorkingTimeInForceEnum::Fok;
    }
    return OrderListOtoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoWorkingTimeInForceEnum value) {
    if (value == OrderListOtoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoWorkingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtoWorkingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOtoWorkingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOtoWorkingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOtoWorkingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOtoWorkingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListOtoWorkingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoWorkingPegPriceTypeEnum value) {
    if (value == OrderListOtoWorkingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoWorkingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoWorkingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtoWorkingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOtoWorkingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOtoWorkingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOtoWorkingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoWorkingPegOffsetTypeEnum value) {
    if (value == OrderListOtoWorkingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoWorkingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoPendingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOtoPendingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOtoPendingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOtoPendingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOtoPendingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOtoPendingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOtoPendingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOtoPendingTimeInForceEnum::Fok;
    }
    return OrderListOtoPendingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoPendingTimeInForceEnum value) {
    if (value == OrderListOtoPendingTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoPendingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoPendingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtoPendingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOtoPendingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOtoPendingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoPendingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoPendingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOtoPendingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOtoPendingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListOtoPendingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoPendingPegPriceTypeEnum value) {
    if (value == OrderListOtoPendingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoPendingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtoPendingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtoPendingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOtoPendingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtoPendingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoPendingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOtoPendingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOtoPendingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtoPendingPegOffsetTypeEnum value) {
    if (value == OrderListOtoPendingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtoPendingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoWorkingTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoWorkingTypeEnum::Limit:
        return "LIMIT";
    case OrderListOtocoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListOtocoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListOtocoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListOtocoWorkingTypeEnum::LimitMaker;
    }
    return OrderListOtocoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoWorkingTypeEnum value) {
    if (value == OrderListOtocoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtocoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoWorkingSideEnum value) noexcept {
    switch (value) {
    case OrderListOtocoWorkingSideEnum::Buy:
        return "BUY";
    case OrderListOtocoWorkingSideEnum::Sell:
        return "SELL";
    case OrderListOtocoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListOtocoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListOtocoWorkingSideEnum::Sell;
    }
    return OrderListOtocoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoWorkingSideEnum value) {
    if (value == OrderListOtocoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListOtocoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoPendingSideEnum value) noexcept {
    switch (value) {
    case OrderListOtocoPendingSideEnum::Buy:
        return "BUY";
    case OrderListOtocoPendingSideEnum::Sell:
        return "SELL";
    case OrderListOtocoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListOtocoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListOtocoPendingSideEnum::Sell;
    }
    return OrderListOtocoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoPendingSideEnum value) {
    if (value == OrderListOtocoPendingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListOtocoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoPendingAboveTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoPendingAboveTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListOtocoPendingAboveTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListOtocoPendingAboveTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListOtocoPendingAboveTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListOtocoPendingAboveTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListOtocoPendingAboveTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListOtocoPendingAboveTypeEnum::StopLossLimit;
    }
    if (s == "STOP_LOSS") {
        return OrderListOtocoPendingAboveTypeEnum::StopLoss;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListOtocoPendingAboveTypeEnum::LimitMaker;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListOtocoPendingAboveTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListOtocoPendingAboveTypeEnum::TakeProfitLimit;
    }
    return OrderListOtocoPendingAboveTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoPendingAboveTypeEnum value) {
    if (value == OrderListOtocoPendingAboveTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtocoPendingAboveTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListOtocoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListOtocoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListOtocoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListOtocoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListOtocoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListOtocoNewOrderRespTypeEnum::Full;
    }
    return OrderListOtocoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoNewOrderRespTypeEnum value) {
    if (value == OrderListOtocoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtocoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListOtocoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListOtocoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListOtocoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListOtocoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListOtocoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListOtocoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListOtocoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListOtocoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListOtocoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListOtocoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListOtocoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListOtocoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListOtocoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoSelfTradePreventionModeEnum value) {
    if (value == OrderListOtocoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtocoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOtocoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOtocoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOtocoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOtocoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOtocoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOtocoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOtocoWorkingTimeInForceEnum::Fok;
    }
    return OrderListOtocoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoWorkingTimeInForceEnum value) {
    if (value == OrderListOtocoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderListOtocoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoWorkingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoWorkingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOtocoWorkingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOtocoWorkingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOtocoWorkingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOtocoWorkingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListOtocoWorkingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoWorkingPegPriceTypeEnum value) {
    if (value == OrderListOtocoWorkingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtocoWorkingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoWorkingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoWorkingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOtocoWorkingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOtocoWorkingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOtocoWorkingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoWorkingPegOffsetTypeEnum value) {
    if (value == OrderListOtocoWorkingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtocoWorkingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoPendingAboveTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOtocoPendingAboveTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOtocoPendingAboveTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOtocoPendingAboveTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOtocoPendingAboveTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOtocoPendingAboveTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOtocoPendingAboveTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOtocoPendingAboveTimeInForceEnum::Fok;
    }
    return OrderListOtocoPendingAboveTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoPendingAboveTimeInForceEnum value) {
    if (value == OrderListOtocoPendingAboveTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtocoPendingAboveTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoPendingAbovePegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoPendingAbovePegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOtocoPendingAbovePegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOtocoPendingAbovePegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoPendingAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOtocoPendingAbovePegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOtocoPendingAbovePegPriceTypeEnum::MarketPeg;
    }
    return OrderListOtocoPendingAbovePegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoPendingAbovePegPriceTypeEnum value) {
    if (value == OrderListOtocoPendingAbovePegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtocoPendingAbovePegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoPendingAbovePegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoPendingAbovePegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOtocoPendingAbovePegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoPendingAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOtocoPendingAbovePegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOtocoPendingAbovePegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoPendingAbovePegOffsetTypeEnum value) {
    if (value == OrderListOtocoPendingAbovePegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtocoPendingAbovePegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoPendingBelowTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoPendingBelowTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListOtocoPendingBelowTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListOtocoPendingBelowTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListOtocoPendingBelowTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListOtocoPendingBelowTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS") {
        return OrderListOtocoPendingBelowTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListOtocoPendingBelowTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListOtocoPendingBelowTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListOtocoPendingBelowTypeEnum::TakeProfitLimit;
    }
    return OrderListOtocoPendingBelowTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoPendingBelowTypeEnum value) {
    if (value == OrderListOtocoPendingBelowTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListOtocoPendingBelowTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoPendingBelowTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListOtocoPendingBelowTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListOtocoPendingBelowTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListOtocoPendingBelowTimeInForceEnum::Fok:
        return "FOK";
    case OrderListOtocoPendingBelowTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListOtocoPendingBelowTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListOtocoPendingBelowTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListOtocoPendingBelowTimeInForceEnum::Fok;
    }
    return OrderListOtocoPendingBelowTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoPendingBelowTimeInForceEnum value) {
    if (value == OrderListOtocoPendingBelowTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtocoPendingBelowTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoPendingBelowPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoPendingBelowPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListOtocoPendingBelowPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListOtocoPendingBelowPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoPendingBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListOtocoPendingBelowPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListOtocoPendingBelowPegPriceTypeEnum::MarketPeg;
    }
    return OrderListOtocoPendingBelowPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoPendingBelowPegPriceTypeEnum value) {
    if (value == OrderListOtocoPendingBelowPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtocoPendingBelowPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListOtocoPendingBelowPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListOtocoPendingBelowPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListOtocoPendingBelowPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListOtocoPendingBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListOtocoPendingBelowPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListOtocoPendingBelowPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListOtocoPendingBelowPegOffsetTypeEnum value) {
    if (value == OrderListOtocoPendingBelowPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListOtocoPendingBelowPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderOcoSideEnum value) noexcept {
    switch (value) {
    case OrderOcoSideEnum::Buy:
        return "BUY";
    case OrderOcoSideEnum::Sell:
        return "SELL";
    case OrderOcoSideEnum::Unknown:
        break;
    }
    return "";
}

OrderOcoSideEnum tag_invoke(boost::json::value_to_tag<OrderOcoSideEnum> /*tag*/,
                            const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderOcoSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderOcoSideEnum::Sell;
    }
    return OrderOcoSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderOcoSideEnum value) {
    if (value == OrderOcoSideEnum::Unknown) {
        throw std::invalid_argument("OrderOcoSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderOcoStopLimitTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderOcoStopLimitTimeInForceEnum::Gtc:
        return "GTC";
    case OrderOcoStopLimitTimeInForceEnum::Ioc:
        return "IOC";
    case OrderOcoStopLimitTimeInForceEnum::Fok:
        return "FOK";
    case OrderOcoStopLimitTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderOcoStopLimitTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderOcoStopLimitTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderOcoStopLimitTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderOcoStopLimitTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderOcoStopLimitTimeInForceEnum::Fok;
    }
    return OrderOcoStopLimitTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderOcoStopLimitTimeInForceEnum value) {
    if (value == OrderOcoStopLimitTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderOcoStopLimitTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderOcoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderOcoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderOcoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderOcoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderOcoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderOcoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderOcoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderOcoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderOcoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderOcoNewOrderRespTypeEnum::Full;
    }
    return OrderOcoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderOcoNewOrderRespTypeEnum value) {
    if (value == OrderOcoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("OrderOcoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderOcoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderOcoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderOcoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderOcoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderOcoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderOcoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderOcoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderOcoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderOcoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderOcoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderOcoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderOcoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderOcoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderOcoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderOcoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderOcoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderOcoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderOcoSelfTradePreventionModeEnum value) {
    if (value == OrderOcoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument("OrderOcoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderTestSideEnum value) noexcept {
    switch (value) {
    case OrderTestSideEnum::Buy:
        return "BUY";
    case OrderTestSideEnum::Sell:
        return "SELL";
    case OrderTestSideEnum::Unknown:
        break;
    }
    return "";
}

OrderTestSideEnum tag_invoke(boost::json::value_to_tag<OrderTestSideEnum> /*tag*/,
                             const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderTestSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderTestSideEnum::Sell;
    }
    return OrderTestSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderTestSideEnum value) {
    if (value == OrderTestSideEnum::Unknown) {
        throw std::invalid_argument("OrderTestSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderTestTypeEnum value) noexcept {
    switch (value) {
    case OrderTestTypeEnum::Market:
        return "MARKET";
    case OrderTestTypeEnum::Limit:
        return "LIMIT";
    case OrderTestTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderTestTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderTestTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderTestTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderTestTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderTestTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderTestTypeEnum tag_invoke(boost::json::value_to_tag<OrderTestTypeEnum> /*tag*/,
                             const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return OrderTestTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return OrderTestTypeEnum::Limit;
    }
    if (s == "STOP_LOSS") {
        return OrderTestTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderTestTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderTestTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderTestTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderTestTypeEnum::LimitMaker;
    }
    return OrderTestTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderTestTypeEnum value) {
    if (value == OrderTestTypeEnum::Unknown) {
        throw std::invalid_argument("OrderTestTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderTestTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderTestTimeInForceEnum::Gtc:
        return "GTC";
    case OrderTestTimeInForceEnum::Ioc:
        return "IOC";
    case OrderTestTimeInForceEnum::Fok:
        return "FOK";
    case OrderTestTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderTestTimeInForceEnum tag_invoke(boost::json::value_to_tag<OrderTestTimeInForceEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderTestTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderTestTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderTestTimeInForceEnum::Fok;
    }
    return OrderTestTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderTestTimeInForceEnum value) {
    if (value == OrderTestTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderTestTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderTestNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderTestNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderTestNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderTestNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderTestNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderTestNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderTestNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderTestNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderTestNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderTestNewOrderRespTypeEnum::Full;
    }
    return OrderTestNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderTestNewOrderRespTypeEnum value) {
    if (value == OrderTestNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("OrderTestNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderTestSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderTestSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderTestSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderTestSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderTestSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderTestSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderTestSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderTestSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderTestSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderTestSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderTestSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderTestSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderTestSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderTestSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderTestSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderTestSelfTradePreventionModeEnum::Transfer;
    }
    return OrderTestSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderTestSelfTradePreventionModeEnum value) {
    if (value == OrderTestSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument("OrderTestSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderTestPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderTestPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderTestPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderTestPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderTestPegPriceTypeEnum tag_invoke(boost::json::value_to_tag<OrderTestPegPriceTypeEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderTestPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderTestPegPriceTypeEnum::MarketPeg;
    }
    return OrderTestPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderTestPegPriceTypeEnum value) {
    if (value == OrderTestPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderTestPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderTestPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderTestPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderTestPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderTestPegOffsetTypeEnum tag_invoke(boost::json::value_to_tag<OrderTestPegOffsetTypeEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderTestPegOffsetTypeEnum::PriceLevel;
    }
    return OrderTestPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderTestPegOffsetTypeEnum value) {
    if (value == OrderTestPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("OrderTestPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderSideEnum value) noexcept {
    switch (value) {
    case SorOrderSideEnum::Buy:
        return "BUY";
    case SorOrderSideEnum::Sell:
        return "SELL";
    case SorOrderSideEnum::Unknown:
        break;
    }
    return "";
}

SorOrderSideEnum tag_invoke(boost::json::value_to_tag<SorOrderSideEnum> /*tag*/,
                            const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return SorOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return SorOrderSideEnum::Sell;
    }
    return SorOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderSideEnum value) {
    if (value == SorOrderSideEnum::Unknown) {
        throw std::invalid_argument("SorOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderTypeEnum value) noexcept {
    switch (value) {
    case SorOrderTypeEnum::Market:
        return "MARKET";
    case SorOrderTypeEnum::Limit:
        return "LIMIT";
    case SorOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

SorOrderTypeEnum tag_invoke(boost::json::value_to_tag<SorOrderTypeEnum> /*tag*/,
                            const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return SorOrderTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return SorOrderTypeEnum::Limit;
    }
    return SorOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderTypeEnum value) {
    if (value == SorOrderTypeEnum::Unknown) {
        throw std::invalid_argument("SorOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case SorOrderTimeInForceEnum::Gtc:
        return "GTC";
    case SorOrderTimeInForceEnum::Ioc:
        return "IOC";
    case SorOrderTimeInForceEnum::Fok:
        return "FOK";
    case SorOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

SorOrderTimeInForceEnum tag_invoke(boost::json::value_to_tag<SorOrderTimeInForceEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return SorOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return SorOrderTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return SorOrderTimeInForceEnum::Fok;
    }
    return SorOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderTimeInForceEnum value) {
    if (value == SorOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("SorOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case SorOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case SorOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case SorOrderNewOrderRespTypeEnum::Full:
        return "FULL";
    case SorOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

SorOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<SorOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return SorOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return SorOrderNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return SorOrderNewOrderRespTypeEnum::Full;
    }
    return SorOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderNewOrderRespTypeEnum value) {
    if (value == SorOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("SorOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case SorOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case SorOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case SorOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case SorOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case SorOrderSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case SorOrderSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case SorOrderSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

SorOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<SorOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return SorOrderSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return SorOrderSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return SorOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return SorOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return SorOrderSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return SorOrderSelfTradePreventionModeEnum::Transfer;
    }
    return SorOrderSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderSelfTradePreventionModeEnum value) {
    if (value == SorOrderSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument("SorOrderSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderTestSideEnum value) noexcept {
    switch (value) {
    case SorOrderTestSideEnum::Buy:
        return "BUY";
    case SorOrderTestSideEnum::Sell:
        return "SELL";
    case SorOrderTestSideEnum::Unknown:
        break;
    }
    return "";
}

SorOrderTestSideEnum tag_invoke(boost::json::value_to_tag<SorOrderTestSideEnum> /*tag*/,
                                const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return SorOrderTestSideEnum::Buy;
    }
    if (s == "SELL") {
        return SorOrderTestSideEnum::Sell;
    }
    return SorOrderTestSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderTestSideEnum value) {
    if (value == SorOrderTestSideEnum::Unknown) {
        throw std::invalid_argument("SorOrderTestSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderTestTypeEnum value) noexcept {
    switch (value) {
    case SorOrderTestTypeEnum::Market:
        return "MARKET";
    case SorOrderTestTypeEnum::Limit:
        return "LIMIT";
    case SorOrderTestTypeEnum::Unknown:
        break;
    }
    return "";
}

SorOrderTestTypeEnum tag_invoke(boost::json::value_to_tag<SorOrderTestTypeEnum> /*tag*/,
                                const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return SorOrderTestTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return SorOrderTestTypeEnum::Limit;
    }
    return SorOrderTestTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderTestTypeEnum value) {
    if (value == SorOrderTestTypeEnum::Unknown) {
        throw std::invalid_argument("SorOrderTestTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderTestTimeInForceEnum value) noexcept {
    switch (value) {
    case SorOrderTestTimeInForceEnum::Gtc:
        return "GTC";
    case SorOrderTestTimeInForceEnum::Ioc:
        return "IOC";
    case SorOrderTestTimeInForceEnum::Fok:
        return "FOK";
    case SorOrderTestTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

SorOrderTestTimeInForceEnum
tag_invoke(boost::json::value_to_tag<SorOrderTestTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return SorOrderTestTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return SorOrderTestTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return SorOrderTestTimeInForceEnum::Fok;
    }
    return SorOrderTestTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderTestTimeInForceEnum value) {
    if (value == SorOrderTestTimeInForceEnum::Unknown) {
        throw std::invalid_argument("SorOrderTestTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderTestNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case SorOrderTestNewOrderRespTypeEnum::Ack:
        return "ACK";
    case SorOrderTestNewOrderRespTypeEnum::Result:
        return "RESULT";
    case SorOrderTestNewOrderRespTypeEnum::Full:
        return "FULL";
    case SorOrderTestNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

SorOrderTestNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<SorOrderTestNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return SorOrderTestNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return SorOrderTestNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return SorOrderTestNewOrderRespTypeEnum::Full;
    }
    return SorOrderTestNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderTestNewOrderRespTypeEnum value) {
    if (value == SorOrderTestNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("SorOrderTestNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderTestSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case SorOrderTestSelfTradePreventionModeEnum::None_:
        return "NONE";
    case SorOrderTestSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case SorOrderTestSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case SorOrderTestSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case SorOrderTestSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case SorOrderTestSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case SorOrderTestSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

SorOrderTestSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<SorOrderTestSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return SorOrderTestSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return SorOrderTestSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return SorOrderTestSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return SorOrderTestSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return SorOrderTestSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return SorOrderTestSelfTradePreventionModeEnum::Transfer;
    }
    return SorOrderTestSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderTestSelfTradePreventionModeEnum value) {
    if (value == SorOrderTestSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "SorOrderTestSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
TradeApi::delete_open_orders_request(const DeleteOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/api/v3/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<DeleteOpenOrdersResponseInner>>
TradeApi::delete_open_orders(const DeleteOpenOrdersParams& params) const {
    return common::send<std::vector<DeleteOpenOrdersResponseInner>>(
        *client_, delete_open_orders_request(params));
}

common::RestRequest TradeApi::delete_order_request(const DeleteOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/api/v3/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "cancelRestrictions", params.cancel_restrictions);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DeleteOrderResponse>
TradeApi::delete_order(const DeleteOrderParams& params) const {
    return common::send<DeleteOrderResponse>(*client_, delete_order_request(params));
}

common::RestRequest TradeApi::new_order_request(const NewOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "quoteOrderQty", params.quote_order_qty);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "strategyId", params.strategy_id);
    common::detail::json::set_param(req.query, "strategyType", params.strategy_type);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "trailingDelta", params.trailing_delta);
    common::detail::json::set_param(req.query, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "pegPriceType", params.peg_price_type);
    common::detail::json::set_param(req.query, "pegOffsetValue", params.peg_offset_value);
    common::detail::json::set_param(req.query, "pegOffsetType", params.peg_offset_type);
    common::detail::json::set_param(req.query, "quoteNotionalLimit", params.quote_notional_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<NewOrderResponse> TradeApi::new_order(const NewOrderParams& params) const {
    return common::send<NewOrderResponse>(*client_, new_order_request(params));
}

common::RestRequest TradeApi::delete_order_list_request(const DeleteOrderListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/api/v3/orderList";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderListId", params.order_list_id);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DeleteOrderListResponse>
TradeApi::delete_order_list(const DeleteOrderListParams& params) const {
    return common::send<DeleteOrderListResponse>(*client_, delete_order_list_request(params));
}

common::RestRequest
TradeApi::order_amend_keep_priority_request(const OrderAmendKeepPriorityParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/api/v3/order/amend/keepPriority";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "newQty", params.new_qty);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderAmendKeepPriorityResponse>
TradeApi::order_amend_keep_priority(const OrderAmendKeepPriorityParams& params) const {
    return common::send<OrderAmendKeepPriorityResponse>(*client_,
                                                        order_amend_keep_priority_request(params));
}

common::RestRequest
TradeApi::order_cancel_replace_request(const OrderCancelReplaceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/order/cancelReplace";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "cancelReplaceMode", params.cancel_replace_mode);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "quoteOrderQty", params.quote_order_qty);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "cancelNewClientOrderId",
                                    params.cancel_new_client_order_id);
    common::detail::json::set_param(req.query, "cancelOrigClientOrderId",
                                    params.cancel_orig_client_order_id);
    common::detail::json::set_param(req.query, "cancelOrderId", params.cancel_order_id);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "strategyId", params.strategy_id);
    common::detail::json::set_param(req.query, "strategyType", params.strategy_type);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "trailingDelta", params.trailing_delta);
    common::detail::json::set_param(req.query, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "cancelRestrictions", params.cancel_restrictions);
    common::detail::json::set_param(req.query, "orderRateLimitExceededMode",
                                    params.order_rate_limit_exceeded_mode);
    common::detail::json::set_param(req.query, "pegPriceType", params.peg_price_type);
    common::detail::json::set_param(req.query, "pegOffsetValue", params.peg_offset_value);
    common::detail::json::set_param(req.query, "pegOffsetType", params.peg_offset_type);
    common::detail::json::set_param(req.query, "quoteNotionalLimit", params.quote_notional_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderCancelReplaceResponse>
TradeApi::order_cancel_replace(const OrderCancelReplaceParams& params) const {
    return common::send<OrderCancelReplaceResponse>(*client_, order_cancel_replace_request(params));
}

common::RestRequest TradeApi::order_list_oco_request(const OrderListOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/orderList/oco";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "aboveType", params.above_type);
    common::detail::json::set_param(req.query, "belowType", params.below_type);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "aboveClientOrderId", params.above_client_order_id);
    common::detail::json::set_param(req.query, "aboveIcebergQty", params.above_iceberg_qty);
    common::detail::json::set_param(req.query, "abovePrice", params.above_price);
    common::detail::json::set_param(req.query, "aboveStopPrice", params.above_stop_price);
    common::detail::json::set_param(req.query, "aboveTrailingDelta", params.above_trailing_delta);
    common::detail::json::set_param(req.query, "aboveTimeInForce", params.above_time_in_force);
    common::detail::json::set_param(req.query, "aboveStrategyId", params.above_strategy_id);
    common::detail::json::set_param(req.query, "aboveStrategyType", params.above_strategy_type);
    common::detail::json::set_param(req.query, "abovePegPriceType", params.above_peg_price_type);
    common::detail::json::set_param(req.query, "abovePegOffsetType", params.above_peg_offset_type);
    common::detail::json::set_param(req.query, "abovePegOffsetValue",
                                    params.above_peg_offset_value);
    common::detail::json::set_param(req.query, "belowClientOrderId", params.below_client_order_id);
    common::detail::json::set_param(req.query, "belowIcebergQty", params.below_iceberg_qty);
    common::detail::json::set_param(req.query, "belowPrice", params.below_price);
    common::detail::json::set_param(req.query, "belowStopPrice", params.below_stop_price);
    common::detail::json::set_param(req.query, "belowTrailingDelta", params.below_trailing_delta);
    common::detail::json::set_param(req.query, "belowTimeInForce", params.below_time_in_force);
    common::detail::json::set_param(req.query, "belowStrategyId", params.below_strategy_id);
    common::detail::json::set_param(req.query, "belowStrategyType", params.below_strategy_type);
    common::detail::json::set_param(req.query, "belowPegPriceType", params.below_peg_price_type);
    common::detail::json::set_param(req.query, "belowPegOffsetType", params.below_peg_offset_type);
    common::detail::json::set_param(req.query, "belowPegOffsetValue",
                                    params.below_peg_offset_value);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "aboveQuoteNotionalLimit",
                                    params.above_quote_notional_limit);
    common::detail::json::set_param(req.query, "belowQuoteNotionalLimit",
                                    params.below_quote_notional_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderListOcoResponse>
TradeApi::order_list_oco(const OrderListOcoParams& params) const {
    return common::send<OrderListOcoResponse>(*client_, order_list_oco_request(params));
}

common::RestRequest TradeApi::order_list_opo_request(const OrderListOpoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/orderList/opo";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "workingSide", params.working_side);
    common::detail::json::set_param(req.query, "workingPrice", params.working_price);
    common::detail::json::set_param(req.query, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(req.query, "pendingType", params.pending_type);
    common::detail::json::set_param(req.query, "pendingSide", params.pending_side);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "workingClientOrderId",
                                    params.working_client_order_id);
    common::detail::json::set_param(req.query, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(req.query, "workingTimeInForce", params.working_time_in_force);
    common::detail::json::set_param(req.query, "workingStrategyId", params.working_strategy_id);
    common::detail::json::set_param(req.query, "workingStrategyType", params.working_strategy_type);
    common::detail::json::set_param(req.query, "workingPegPriceType",
                                    params.working_peg_price_type);
    common::detail::json::set_param(req.query, "workingPegOffsetType",
                                    params.working_peg_offset_type);
    common::detail::json::set_param(req.query, "workingPegOffsetValue",
                                    params.working_peg_offset_value);
    common::detail::json::set_param(req.query, "pendingClientOrderId",
                                    params.pending_client_order_id);
    common::detail::json::set_param(req.query, "pendingPrice", params.pending_price);
    common::detail::json::set_param(req.query, "pendingStopPrice", params.pending_stop_price);
    common::detail::json::set_param(req.query, "pendingTrailingDelta",
                                    params.pending_trailing_delta);
    common::detail::json::set_param(req.query, "pendingIcebergQty", params.pending_iceberg_qty);
    common::detail::json::set_param(req.query, "pendingTimeInForce", params.pending_time_in_force);
    common::detail::json::set_param(req.query, "pendingStrategyId", params.pending_strategy_id);
    common::detail::json::set_param(req.query, "pendingStrategyType", params.pending_strategy_type);
    common::detail::json::set_param(req.query, "pendingPegPriceType",
                                    params.pending_peg_price_type);
    common::detail::json::set_param(req.query, "pendingPegOffsetType",
                                    params.pending_peg_offset_type);
    common::detail::json::set_param(req.query, "pendingPegOffsetValue",
                                    params.pending_peg_offset_value);
    common::detail::json::set_param(req.query, "workingQuoteNotionalLimit",
                                    params.working_quote_notional_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderListOpoResponse>
TradeApi::order_list_opo(const OrderListOpoParams& params) const {
    return common::send<OrderListOpoResponse>(*client_, order_list_opo_request(params));
}

common::RestRequest TradeApi::order_list_opoco_request(const OrderListOpocoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/orderList/opoco";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "workingSide", params.working_side);
    common::detail::json::set_param(req.query, "workingPrice", params.working_price);
    common::detail::json::set_param(req.query, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(req.query, "pendingSide", params.pending_side);
    common::detail::json::set_param(req.query, "pendingAboveType", params.pending_above_type);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "workingClientOrderId",
                                    params.working_client_order_id);
    common::detail::json::set_param(req.query, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(req.query, "workingTimeInForce", params.working_time_in_force);
    common::detail::json::set_param(req.query, "workingStrategyId", params.working_strategy_id);
    common::detail::json::set_param(req.query, "workingStrategyType", params.working_strategy_type);
    common::detail::json::set_param(req.query, "workingPegPriceType",
                                    params.working_peg_price_type);
    common::detail::json::set_param(req.query, "workingPegOffsetType",
                                    params.working_peg_offset_type);
    common::detail::json::set_param(req.query, "workingPegOffsetValue",
                                    params.working_peg_offset_value);
    common::detail::json::set_param(req.query, "pendingAboveClientOrderId",
                                    params.pending_above_client_order_id);
    common::detail::json::set_param(req.query, "pendingAbovePrice", params.pending_above_price);
    common::detail::json::set_param(req.query, "pendingAboveStopPrice",
                                    params.pending_above_stop_price);
    common::detail::json::set_param(req.query, "pendingAboveTrailingDelta",
                                    params.pending_above_trailing_delta);
    common::detail::json::set_param(req.query, "pendingAboveIcebergQty",
                                    params.pending_above_iceberg_qty);
    common::detail::json::set_param(req.query, "pendingAboveTimeInForce",
                                    params.pending_above_time_in_force);
    common::detail::json::set_param(req.query, "pendingAboveStrategyId",
                                    params.pending_above_strategy_id);
    common::detail::json::set_param(req.query, "pendingAboveStrategyType",
                                    params.pending_above_strategy_type);
    common::detail::json::set_param(req.query, "pendingAbovePegPriceType",
                                    params.pending_above_peg_price_type);
    common::detail::json::set_param(req.query, "pendingAbovePegOffsetType",
                                    params.pending_above_peg_offset_type);
    common::detail::json::set_param(req.query, "pendingAbovePegOffsetValue",
                                    params.pending_above_peg_offset_value);
    common::detail::json::set_param(req.query, "pendingBelowType", params.pending_below_type);
    common::detail::json::set_param(req.query, "pendingBelowClientOrderId",
                                    params.pending_below_client_order_id);
    common::detail::json::set_param(req.query, "pendingBelowPrice", params.pending_below_price);
    common::detail::json::set_param(req.query, "pendingBelowStopPrice",
                                    params.pending_below_stop_price);
    common::detail::json::set_param(req.query, "pendingBelowTrailingDelta",
                                    params.pending_below_trailing_delta);
    common::detail::json::set_param(req.query, "pendingBelowIcebergQty",
                                    params.pending_below_iceberg_qty);
    common::detail::json::set_param(req.query, "pendingBelowTimeInForce",
                                    params.pending_below_time_in_force);
    common::detail::json::set_param(req.query, "pendingBelowStrategyId",
                                    params.pending_below_strategy_id);
    common::detail::json::set_param(req.query, "pendingBelowStrategyType",
                                    params.pending_below_strategy_type);
    common::detail::json::set_param(req.query, "pendingBelowPegPriceType",
                                    params.pending_below_peg_price_type);
    common::detail::json::set_param(req.query, "pendingBelowPegOffsetType",
                                    params.pending_below_peg_offset_type);
    common::detail::json::set_param(req.query, "pendingBelowPegOffsetValue",
                                    params.pending_below_peg_offset_value);
    common::detail::json::set_param(req.query, "workingQuoteNotionalLimit",
                                    params.working_quote_notional_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderListOpocoResponse>
TradeApi::order_list_opoco(const OrderListOpocoParams& params) const {
    return common::send<OrderListOpocoResponse>(*client_, order_list_opoco_request(params));
}

common::RestRequest TradeApi::order_list_oto_request(const OrderListOtoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/orderList/oto";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "workingSide", params.working_side);
    common::detail::json::set_param(req.query, "workingPrice", params.working_price);
    common::detail::json::set_param(req.query, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(req.query, "pendingType", params.pending_type);
    common::detail::json::set_param(req.query, "pendingSide", params.pending_side);
    common::detail::json::set_param(req.query, "pendingQuantity", params.pending_quantity);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "workingClientOrderId",
                                    params.working_client_order_id);
    common::detail::json::set_param(req.query, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(req.query, "workingTimeInForce", params.working_time_in_force);
    common::detail::json::set_param(req.query, "workingStrategyId", params.working_strategy_id);
    common::detail::json::set_param(req.query, "workingStrategyType", params.working_strategy_type);
    common::detail::json::set_param(req.query, "workingPegPriceType",
                                    params.working_peg_price_type);
    common::detail::json::set_param(req.query, "workingPegOffsetType",
                                    params.working_peg_offset_type);
    common::detail::json::set_param(req.query, "workingPegOffsetValue",
                                    params.working_peg_offset_value);
    common::detail::json::set_param(req.query, "pendingClientOrderId",
                                    params.pending_client_order_id);
    common::detail::json::set_param(req.query, "pendingPrice", params.pending_price);
    common::detail::json::set_param(req.query, "pendingStopPrice", params.pending_stop_price);
    common::detail::json::set_param(req.query, "pendingTrailingDelta",
                                    params.pending_trailing_delta);
    common::detail::json::set_param(req.query, "pendingIcebergQty", params.pending_iceberg_qty);
    common::detail::json::set_param(req.query, "pendingTimeInForce", params.pending_time_in_force);
    common::detail::json::set_param(req.query, "pendingStrategyId", params.pending_strategy_id);
    common::detail::json::set_param(req.query, "pendingStrategyType", params.pending_strategy_type);
    common::detail::json::set_param(req.query, "pendingPegPriceType",
                                    params.pending_peg_price_type);
    common::detail::json::set_param(req.query, "pendingPegOffsetType",
                                    params.pending_peg_offset_type);
    common::detail::json::set_param(req.query, "pendingPegOffsetValue",
                                    params.pending_peg_offset_value);
    common::detail::json::set_param(req.query, "workingQuoteNotionalLimit",
                                    params.working_quote_notional_limit);
    common::detail::json::set_param(req.query, "pendingQuoteNotionalLimit",
                                    params.pending_quote_notional_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderListOtoResponse>
TradeApi::order_list_oto(const OrderListOtoParams& params) const {
    return common::send<OrderListOtoResponse>(*client_, order_list_oto_request(params));
}

common::RestRequest TradeApi::order_list_otoco_request(const OrderListOtocoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/orderList/otoco";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "workingSide", params.working_side);
    common::detail::json::set_param(req.query, "workingPrice", params.working_price);
    common::detail::json::set_param(req.query, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(req.query, "pendingSide", params.pending_side);
    common::detail::json::set_param(req.query, "pendingQuantity", params.pending_quantity);
    common::detail::json::set_param(req.query, "pendingAboveType", params.pending_above_type);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "workingClientOrderId",
                                    params.working_client_order_id);
    common::detail::json::set_param(req.query, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(req.query, "workingTimeInForce", params.working_time_in_force);
    common::detail::json::set_param(req.query, "workingStrategyId", params.working_strategy_id);
    common::detail::json::set_param(req.query, "workingStrategyType", params.working_strategy_type);
    common::detail::json::set_param(req.query, "workingPegPriceType",
                                    params.working_peg_price_type);
    common::detail::json::set_param(req.query, "workingPegOffsetType",
                                    params.working_peg_offset_type);
    common::detail::json::set_param(req.query, "workingPegOffsetValue",
                                    params.working_peg_offset_value);
    common::detail::json::set_param(req.query, "pendingAboveClientOrderId",
                                    params.pending_above_client_order_id);
    common::detail::json::set_param(req.query, "pendingAbovePrice", params.pending_above_price);
    common::detail::json::set_param(req.query, "pendingAboveStopPrice",
                                    params.pending_above_stop_price);
    common::detail::json::set_param(req.query, "pendingAboveTrailingDelta",
                                    params.pending_above_trailing_delta);
    common::detail::json::set_param(req.query, "pendingAboveIcebergQty",
                                    params.pending_above_iceberg_qty);
    common::detail::json::set_param(req.query, "pendingAboveTimeInForce",
                                    params.pending_above_time_in_force);
    common::detail::json::set_param(req.query, "pendingAboveStrategyId",
                                    params.pending_above_strategy_id);
    common::detail::json::set_param(req.query, "pendingAboveStrategyType",
                                    params.pending_above_strategy_type);
    common::detail::json::set_param(req.query, "pendingAbovePegPriceType",
                                    params.pending_above_peg_price_type);
    common::detail::json::set_param(req.query, "pendingAbovePegOffsetType",
                                    params.pending_above_peg_offset_type);
    common::detail::json::set_param(req.query, "pendingAbovePegOffsetValue",
                                    params.pending_above_peg_offset_value);
    common::detail::json::set_param(req.query, "pendingBelowType", params.pending_below_type);
    common::detail::json::set_param(req.query, "pendingBelowClientOrderId",
                                    params.pending_below_client_order_id);
    common::detail::json::set_param(req.query, "pendingBelowPrice", params.pending_below_price);
    common::detail::json::set_param(req.query, "pendingBelowStopPrice",
                                    params.pending_below_stop_price);
    common::detail::json::set_param(req.query, "pendingBelowTrailingDelta",
                                    params.pending_below_trailing_delta);
    common::detail::json::set_param(req.query, "pendingBelowIcebergQty",
                                    params.pending_below_iceberg_qty);
    common::detail::json::set_param(req.query, "pendingBelowTimeInForce",
                                    params.pending_below_time_in_force);
    common::detail::json::set_param(req.query, "pendingBelowStrategyId",
                                    params.pending_below_strategy_id);
    common::detail::json::set_param(req.query, "pendingBelowStrategyType",
                                    params.pending_below_strategy_type);
    common::detail::json::set_param(req.query, "pendingBelowPegPriceType",
                                    params.pending_below_peg_price_type);
    common::detail::json::set_param(req.query, "pendingBelowPegOffsetType",
                                    params.pending_below_peg_offset_type);
    common::detail::json::set_param(req.query, "pendingBelowPegOffsetValue",
                                    params.pending_below_peg_offset_value);
    common::detail::json::set_param(req.query, "workingQuoteNotionalLimit",
                                    params.working_quote_notional_limit);
    common::detail::json::set_param(req.query, "pendingAboveQuoteNotionalLimit",
                                    params.pending_above_quote_notional_limit);
    common::detail::json::set_param(req.query, "pendingBelowQuoteNotionalLimit",
                                    params.pending_below_quote_notional_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderListOtocoResponse>
TradeApi::order_list_otoco(const OrderListOtocoParams& params) const {
    return common::send<OrderListOtocoResponse>(*client_, order_list_otoco_request(params));
}

common::RestRequest TradeApi::order_oco_request(const OrderOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/order/oco";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "limitClientOrderId", params.limit_client_order_id);
    common::detail::json::set_param(req.query, "limitStrategyId", params.limit_strategy_id);
    common::detail::json::set_param(req.query, "limitStrategyType", params.limit_strategy_type);
    common::detail::json::set_param(req.query, "limitIcebergQty", params.limit_iceberg_qty);
    common::detail::json::set_param(req.query, "trailingDelta", params.trailing_delta);
    common::detail::json::set_param(req.query, "stopClientOrderId", params.stop_client_order_id);
    common::detail::json::set_param(req.query, "stopStrategyId", params.stop_strategy_id);
    common::detail::json::set_param(req.query, "stopStrategyType", params.stop_strategy_type);
    common::detail::json::set_param(req.query, "stopLimitPrice", params.stop_limit_price);
    common::detail::json::set_param(req.query, "stopIcebergQty", params.stop_iceberg_qty);
    common::detail::json::set_param(req.query, "stopLimitTimeInForce",
                                    params.stop_limit_time_in_force);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderOcoResponse> TradeApi::order_oco(const OrderOcoParams& params) const {
    return common::send<OrderOcoResponse>(*client_, order_oco_request(params));
}

common::RestRequest TradeApi::order_test_request(const OrderTestParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/order/test";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "computeCommissionRates",
                                    params.compute_commission_rates);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "quoteOrderQty", params.quote_order_qty);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "strategyId", params.strategy_id);
    common::detail::json::set_param(req.query, "strategyType", params.strategy_type);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "trailingDelta", params.trailing_delta);
    common::detail::json::set_param(req.query, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "pegPriceType", params.peg_price_type);
    common::detail::json::set_param(req.query, "pegOffsetValue", params.peg_offset_value);
    common::detail::json::set_param(req.query, "pegOffsetType", params.peg_offset_type);
    common::detail::json::set_param(req.query, "quoteNotionalLimit", params.quote_notional_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderTestResponse>
TradeApi::order_test(const OrderTestParams& params) const {
    return common::send<OrderTestResponse>(*client_, order_test_request(params));
}

common::RestRequest TradeApi::sor_order_request(const SorOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/sor/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "strategyId", params.strategy_id);
    common::detail::json::set_param(req.query, "strategyType", params.strategy_type);
    common::detail::json::set_param(req.query, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SorOrderResponse> TradeApi::sor_order(const SorOrderParams& params) const {
    return common::send<SorOrderResponse>(*client_, sor_order_request(params));
}

common::RestRequest TradeApi::sor_order_test_request(const SorOrderTestParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/api/v3/sor/order/test";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "computeCommissionRates",
                                    params.compute_commission_rates);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "strategyId", params.strategy_id);
    common::detail::json::set_param(req.query, "strategyType", params.strategy_type);
    common::detail::json::set_param(req.query, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SorOrderTestResponse>
TradeApi::sor_order_test(const SorOrderTestParams& params) const {
    return common::send<SorOrderTestResponse>(*client_, sor_order_test_request(params));
}

} // namespace binance::spot::rest_api
