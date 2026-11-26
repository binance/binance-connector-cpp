//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/trade_api.hpp>

namespace binance::spot::websocket_api {

std::string_view to_string(OrderCancelCancelRestrictionsEnum value) noexcept {
    switch (value) {
    case OrderCancelCancelRestrictionsEnum::OnlyNew:
        return "ONLY_NEW";
    case OrderCancelCancelRestrictionsEnum::OnlyPartiallyFilled:
        return "ONLY_PARTIALLY_FILLED";
    case OrderCancelCancelRestrictionsEnum::Unknown:
        break;
    }
    return "";
}

OrderCancelCancelRestrictionsEnum
tag_invoke(boost::json::value_to_tag<OrderCancelCancelRestrictionsEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ONLY_NEW") {
        return OrderCancelCancelRestrictionsEnum::OnlyNew;
    }
    if (s == "ONLY_PARTIALLY_FILLED") {
        return OrderCancelCancelRestrictionsEnum::OnlyPartiallyFilled;
    }
    return OrderCancelCancelRestrictionsEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderCancelCancelRestrictionsEnum value) {
    if (value == OrderCancelCancelRestrictionsEnum::Unknown) {
        throw std::invalid_argument("OrderCancelCancelRestrictionsEnum::Unknown cannot be sent");
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

std::string_view to_string(OrderListPlaceSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceSideEnum::Buy:
        return "BUY";
    case OrderListPlaceSideEnum::Sell:
        return "SELL";
    case OrderListPlaceSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceSideEnum tag_invoke(boost::json::value_to_tag<OrderListPlaceSideEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceSideEnum::Sell;
    }
    return OrderListPlaceSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceSideEnum value) {
    if (value == OrderListPlaceSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceStopLimitTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceStopLimitTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceStopLimitTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceStopLimitTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceStopLimitTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceStopLimitTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceStopLimitTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceStopLimitTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceStopLimitTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceStopLimitTimeInForceEnum::Fok;
    }
    return OrderListPlaceStopLimitTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceStopLimitTimeInForceEnum value) {
    if (value == OrderListPlaceStopLimitTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceStopLimitTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListPlaceNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListPlaceNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListPlaceNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListPlaceNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListPlaceNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListPlaceNewOrderRespTypeEnum::Full;
    }
    return OrderListPlaceNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceNewOrderRespTypeEnum value) {
    if (value == OrderListPlaceNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListPlaceSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListPlaceSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListPlaceSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListPlaceSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListPlaceSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListPlaceSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListPlaceSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListPlaceSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListPlaceSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListPlaceSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListPlaceSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListPlaceSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListPlaceSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceSelfTradePreventionModeEnum value) {
    if (value == OrderListPlaceSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoSideEnum::Buy:
        return "BUY";
    case OrderListPlaceOcoSideEnum::Sell:
        return "SELL";
    case OrderListPlaceOcoSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoSideEnum tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoSideEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceOcoSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceOcoSideEnum::Sell;
    }
    return OrderListPlaceOcoSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoSideEnum value) {
    if (value == OrderListPlaceOcoSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOcoSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoAboveTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoAboveTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListPlaceOcoAboveTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListPlaceOcoAboveTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListPlaceOcoAboveTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListPlaceOcoAboveTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListPlaceOcoAboveTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoAboveTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListPlaceOcoAboveTypeEnum::StopLossLimit;
    }
    if (s == "STOP_LOSS") {
        return OrderListPlaceOcoAboveTypeEnum::StopLoss;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListPlaceOcoAboveTypeEnum::LimitMaker;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListPlaceOcoAboveTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListPlaceOcoAboveTypeEnum::TakeProfitLimit;
    }
    return OrderListPlaceOcoAboveTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoAboveTypeEnum value) {
    if (value == OrderListPlaceOcoAboveTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOcoAboveTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoBelowTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoBelowTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListPlaceOcoBelowTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListPlaceOcoBelowTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListPlaceOcoBelowTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListPlaceOcoBelowTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoBelowTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS") {
        return OrderListPlaceOcoBelowTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListPlaceOcoBelowTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListPlaceOcoBelowTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListPlaceOcoBelowTypeEnum::TakeProfitLimit;
    }
    return OrderListPlaceOcoBelowTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoBelowTypeEnum value) {
    if (value == OrderListPlaceOcoBelowTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOcoBelowTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoAboveTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoAboveTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOcoAboveTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOcoAboveTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOcoAboveTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOcoAboveTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOcoAboveTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOcoAboveTimeInForceEnum::Fok;
    }
    return OrderListPlaceOcoAboveTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoAboveTimeInForceEnum value) {
    if (value == OrderListPlaceOcoAboveTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOcoAboveTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoAbovePegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoAbovePegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOcoAbovePegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOcoAbovePegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOcoAbovePegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOcoAbovePegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOcoAbovePegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoAbovePegPriceTypeEnum value) {
    if (value == OrderListPlaceOcoAbovePegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOcoAbovePegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoAbovePegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoAbovePegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOcoAbovePegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOcoAbovePegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOcoAbovePegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoAbovePegOffsetTypeEnum value) {
    if (value == OrderListPlaceOcoAbovePegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOcoAbovePegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoBelowTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoBelowTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOcoBelowTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOcoBelowTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOcoBelowTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOcoBelowTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOcoBelowTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOcoBelowTimeInForceEnum::Fok;
    }
    return OrderListPlaceOcoBelowTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoBelowTimeInForceEnum value) {
    if (value == OrderListPlaceOcoBelowTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOcoBelowTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoBelowPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoBelowPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOcoBelowPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOcoBelowPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOcoBelowPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOcoBelowPegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOcoBelowPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoBelowPegPriceTypeEnum value) {
    if (value == OrderListPlaceOcoBelowPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOcoBelowPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoBelowPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoBelowPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOcoBelowPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOcoBelowPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOcoBelowPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoBelowPegOffsetTypeEnum value) {
    if (value == OrderListPlaceOcoBelowPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOcoBelowPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListPlaceOcoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListPlaceOcoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListPlaceOcoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListPlaceOcoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListPlaceOcoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListPlaceOcoNewOrderRespTypeEnum::Full;
    }
    return OrderListPlaceOcoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoNewOrderRespTypeEnum value) {
    if (value == OrderListPlaceOcoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOcoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOcoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOcoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListPlaceOcoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListPlaceOcoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListPlaceOcoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListPlaceOcoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListPlaceOcoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListPlaceOcoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOcoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListPlaceOcoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListPlaceOcoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListPlaceOcoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListPlaceOcoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListPlaceOcoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListPlaceOcoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListPlaceOcoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOcoSelfTradePreventionModeEnum value) {
    if (value == OrderListPlaceOcoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOcoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoWorkingTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoWorkingTypeEnum::Limit:
        return "LIMIT";
    case OrderListPlaceOpoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListPlaceOpoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListPlaceOpoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListPlaceOpoWorkingTypeEnum::LimitMaker;
    }
    return OrderListPlaceOpoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoWorkingTypeEnum value) {
    if (value == OrderListPlaceOpoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOpoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoWorkingSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoWorkingSideEnum::Buy:
        return "BUY";
    case OrderListPlaceOpoWorkingSideEnum::Sell:
        return "SELL";
    case OrderListPlaceOpoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceOpoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceOpoWorkingSideEnum::Sell;
    }
    return OrderListPlaceOpoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoWorkingSideEnum value) {
    if (value == OrderListPlaceOpoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOpoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoPendingTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoPendingTypeEnum::Limit:
        return "LIMIT";
    case OrderListPlaceOpoPendingTypeEnum::Market:
        return "MARKET";
    case OrderListPlaceOpoPendingTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListPlaceOpoPendingTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListPlaceOpoPendingTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListPlaceOpoPendingTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListPlaceOpoPendingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListPlaceOpoPendingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoPendingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListPlaceOpoPendingTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return OrderListPlaceOpoPendingTypeEnum::Market;
    }
    if (s == "STOP_LOSS") {
        return OrderListPlaceOpoPendingTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListPlaceOpoPendingTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListPlaceOpoPendingTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListPlaceOpoPendingTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListPlaceOpoPendingTypeEnum::LimitMaker;
    }
    return OrderListPlaceOpoPendingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoPendingTypeEnum value) {
    if (value == OrderListPlaceOpoPendingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOpoPendingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoPendingSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoPendingSideEnum::Buy:
        return "BUY";
    case OrderListPlaceOpoPendingSideEnum::Sell:
        return "SELL";
    case OrderListPlaceOpoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceOpoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceOpoPendingSideEnum::Sell;
    }
    return OrderListPlaceOpoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoPendingSideEnum value) {
    if (value == OrderListPlaceOpoPendingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOpoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListPlaceOpoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListPlaceOpoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListPlaceOpoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListPlaceOpoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListPlaceOpoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListPlaceOpoNewOrderRespTypeEnum::Full;
    }
    return OrderListPlaceOpoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoNewOrderRespTypeEnum value) {
    if (value == OrderListPlaceOpoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListPlaceOpoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListPlaceOpoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListPlaceOpoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListPlaceOpoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListPlaceOpoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListPlaceOpoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListPlaceOpoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListPlaceOpoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListPlaceOpoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListPlaceOpoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListPlaceOpoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListPlaceOpoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListPlaceOpoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoSelfTradePreventionModeEnum value) {
    if (value == OrderListPlaceOpoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOpoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOpoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOpoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOpoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOpoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOpoWorkingTimeInForceEnum::Fok;
    }
    return OrderListPlaceOpoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoWorkingTimeInForceEnum value) {
    if (value == OrderListPlaceOpoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoWorkingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoWorkingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOpoWorkingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOpoWorkingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOpoWorkingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOpoWorkingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOpoWorkingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoWorkingPegPriceTypeEnum value) {
    if (value == OrderListPlaceOpoWorkingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpoWorkingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoWorkingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoWorkingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOpoWorkingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOpoWorkingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOpoWorkingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoWorkingPegOffsetTypeEnum value) {
    if (value == OrderListPlaceOpoWorkingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpoWorkingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoPendingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoPendingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOpoPendingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOpoPendingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOpoPendingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOpoPendingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOpoPendingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOpoPendingTimeInForceEnum::Fok;
    }
    return OrderListPlaceOpoPendingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoPendingTimeInForceEnum value) {
    if (value == OrderListPlaceOpoPendingTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpoPendingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoPendingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoPendingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOpoPendingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOpoPendingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoPendingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOpoPendingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOpoPendingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOpoPendingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoPendingPegPriceTypeEnum value) {
    if (value == OrderListPlaceOpoPendingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpoPendingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpoPendingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpoPendingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOpoPendingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpoPendingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOpoPendingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOpoPendingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpoPendingPegOffsetTypeEnum value) {
    if (value == OrderListPlaceOpoPendingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpoPendingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoWorkingTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoWorkingTypeEnum::Limit:
        return "LIMIT";
    case OrderListPlaceOpocoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListPlaceOpocoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListPlaceOpocoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListPlaceOpocoWorkingTypeEnum::LimitMaker;
    }
    return OrderListPlaceOpocoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoWorkingTypeEnum value) {
    if (value == OrderListPlaceOpocoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOpocoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoWorkingSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoWorkingSideEnum::Buy:
        return "BUY";
    case OrderListPlaceOpocoWorkingSideEnum::Sell:
        return "SELL";
    case OrderListPlaceOpocoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceOpocoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceOpocoWorkingSideEnum::Sell;
    }
    return OrderListPlaceOpocoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoWorkingSideEnum value) {
    if (value == OrderListPlaceOpocoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOpocoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoPendingSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoPendingSideEnum::Buy:
        return "BUY";
    case OrderListPlaceOpocoPendingSideEnum::Sell:
        return "SELL";
    case OrderListPlaceOpocoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceOpocoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceOpocoPendingSideEnum::Sell;
    }
    return OrderListPlaceOpocoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoPendingSideEnum value) {
    if (value == OrderListPlaceOpocoPendingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOpocoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoPendingAboveTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoPendingAboveTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListPlaceOpocoPendingAboveTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListPlaceOpocoPendingAboveTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListPlaceOpocoPendingAboveTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListPlaceOpocoPendingAboveTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListPlaceOpocoPendingAboveTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListPlaceOpocoPendingAboveTypeEnum::StopLossLimit;
    }
    if (s == "STOP_LOSS") {
        return OrderListPlaceOpocoPendingAboveTypeEnum::StopLoss;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListPlaceOpocoPendingAboveTypeEnum::LimitMaker;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListPlaceOpocoPendingAboveTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListPlaceOpocoPendingAboveTypeEnum::TakeProfitLimit;
    }
    return OrderListPlaceOpocoPendingAboveTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoPendingAboveTypeEnum value) {
    if (value == OrderListPlaceOpocoPendingAboveTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoPendingAboveTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListPlaceOpocoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListPlaceOpocoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListPlaceOpocoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListPlaceOpocoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListPlaceOpocoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListPlaceOpocoNewOrderRespTypeEnum::Full;
    }
    return OrderListPlaceOpocoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoNewOrderRespTypeEnum value) {
    if (value == OrderListPlaceOpocoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListPlaceOpocoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListPlaceOpocoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListPlaceOpocoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListPlaceOpocoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListPlaceOpocoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListPlaceOpocoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListPlaceOpocoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListPlaceOpocoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListPlaceOpocoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListPlaceOpocoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListPlaceOpocoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListPlaceOpocoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListPlaceOpocoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoSelfTradePreventionModeEnum value) {
    if (value == OrderListPlaceOpocoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOpocoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOpocoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOpocoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOpocoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOpocoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOpocoWorkingTimeInForceEnum::Fok;
    }
    return OrderListPlaceOpocoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoWorkingTimeInForceEnum value) {
    if (value == OrderListPlaceOpocoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoWorkingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoWorkingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOpocoWorkingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOpocoWorkingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOpocoWorkingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOpocoWorkingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOpocoWorkingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoWorkingPegPriceTypeEnum value) {
    if (value == OrderListPlaceOpocoWorkingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoWorkingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoWorkingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoWorkingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOpocoWorkingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOpocoWorkingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOpocoWorkingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoWorkingPegOffsetTypeEnum value) {
    if (value == OrderListPlaceOpocoWorkingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoWorkingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoPendingAboveTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoPendingAboveTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOpocoPendingAboveTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOpocoPendingAboveTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOpocoPendingAboveTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOpocoPendingAboveTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOpocoPendingAboveTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOpocoPendingAboveTimeInForceEnum::Fok;
    }
    return OrderListPlaceOpocoPendingAboveTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoPendingAboveTimeInForceEnum value) {
    if (value == OrderListPlaceOpocoPendingAboveTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoPendingAboveTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoPendingAbovePegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoPendingAbovePegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOpocoPendingAbovePegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOpocoPendingAbovePegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoPendingAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOpocoPendingAbovePegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOpocoPendingAbovePegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOpocoPendingAbovePegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoPendingAbovePegPriceTypeEnum value) {
    if (value == OrderListPlaceOpocoPendingAbovePegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoPendingAbovePegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum value) {
    if (value == OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoPendingBelowTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoPendingBelowTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListPlaceOpocoPendingBelowTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListPlaceOpocoPendingBelowTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListPlaceOpocoPendingBelowTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListPlaceOpocoPendingBelowTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS") {
        return OrderListPlaceOpocoPendingBelowTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListPlaceOpocoPendingBelowTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListPlaceOpocoPendingBelowTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListPlaceOpocoPendingBelowTypeEnum::TakeProfitLimit;
    }
    return OrderListPlaceOpocoPendingBelowTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoPendingBelowTypeEnum value) {
    if (value == OrderListPlaceOpocoPendingBelowTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoPendingBelowTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoPendingBelowTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoPendingBelowTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOpocoPendingBelowTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOpocoPendingBelowTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOpocoPendingBelowTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOpocoPendingBelowTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOpocoPendingBelowTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOpocoPendingBelowTimeInForceEnum::Fok;
    }
    return OrderListPlaceOpocoPendingBelowTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoPendingBelowTimeInForceEnum value) {
    if (value == OrderListPlaceOpocoPendingBelowTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoPendingBelowTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoPendingBelowPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoPendingBelowPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOpocoPendingBelowPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOpocoPendingBelowPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoPendingBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOpocoPendingBelowPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOpocoPendingBelowPegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOpocoPendingBelowPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoPendingBelowPegPriceTypeEnum value) {
    if (value == OrderListPlaceOpocoPendingBelowPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoPendingBelowPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum value) {
    if (value == OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoWorkingTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoWorkingTypeEnum::Limit:
        return "LIMIT";
    case OrderListPlaceOtoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListPlaceOtoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListPlaceOtoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListPlaceOtoWorkingTypeEnum::LimitMaker;
    }
    return OrderListPlaceOtoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoWorkingTypeEnum value) {
    if (value == OrderListPlaceOtoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOtoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoWorkingSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoWorkingSideEnum::Buy:
        return "BUY";
    case OrderListPlaceOtoWorkingSideEnum::Sell:
        return "SELL";
    case OrderListPlaceOtoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceOtoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceOtoWorkingSideEnum::Sell;
    }
    return OrderListPlaceOtoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoWorkingSideEnum value) {
    if (value == OrderListPlaceOtoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOtoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoPendingTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoPendingTypeEnum::Limit:
        return "LIMIT";
    case OrderListPlaceOtoPendingTypeEnum::Market:
        return "MARKET";
    case OrderListPlaceOtoPendingTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListPlaceOtoPendingTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListPlaceOtoPendingTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListPlaceOtoPendingTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListPlaceOtoPendingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListPlaceOtoPendingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoPendingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListPlaceOtoPendingTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return OrderListPlaceOtoPendingTypeEnum::Market;
    }
    if (s == "STOP_LOSS") {
        return OrderListPlaceOtoPendingTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListPlaceOtoPendingTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListPlaceOtoPendingTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListPlaceOtoPendingTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListPlaceOtoPendingTypeEnum::LimitMaker;
    }
    return OrderListPlaceOtoPendingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoPendingTypeEnum value) {
    if (value == OrderListPlaceOtoPendingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOtoPendingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoPendingSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoPendingSideEnum::Buy:
        return "BUY";
    case OrderListPlaceOtoPendingSideEnum::Sell:
        return "SELL";
    case OrderListPlaceOtoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceOtoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceOtoPendingSideEnum::Sell;
    }
    return OrderListPlaceOtoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoPendingSideEnum value) {
    if (value == OrderListPlaceOtoPendingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOtoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListPlaceOtoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListPlaceOtoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListPlaceOtoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListPlaceOtoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListPlaceOtoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListPlaceOtoNewOrderRespTypeEnum::Full;
    }
    return OrderListPlaceOtoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoNewOrderRespTypeEnum value) {
    if (value == OrderListPlaceOtoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListPlaceOtoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListPlaceOtoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListPlaceOtoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListPlaceOtoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListPlaceOtoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListPlaceOtoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListPlaceOtoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListPlaceOtoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListPlaceOtoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListPlaceOtoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListPlaceOtoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListPlaceOtoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListPlaceOtoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoSelfTradePreventionModeEnum value) {
    if (value == OrderListPlaceOtoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOtoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOtoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOtoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOtoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOtoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOtoWorkingTimeInForceEnum::Fok;
    }
    return OrderListPlaceOtoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoWorkingTimeInForceEnum value) {
    if (value == OrderListPlaceOtoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoWorkingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoWorkingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOtoWorkingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOtoWorkingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOtoWorkingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOtoWorkingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOtoWorkingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoWorkingPegPriceTypeEnum value) {
    if (value == OrderListPlaceOtoWorkingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtoWorkingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoWorkingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoWorkingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOtoWorkingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOtoWorkingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOtoWorkingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoWorkingPegOffsetTypeEnum value) {
    if (value == OrderListPlaceOtoWorkingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtoWorkingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoPendingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoPendingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOtoPendingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOtoPendingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOtoPendingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOtoPendingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOtoPendingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOtoPendingTimeInForceEnum::Fok;
    }
    return OrderListPlaceOtoPendingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoPendingTimeInForceEnum value) {
    if (value == OrderListPlaceOtoPendingTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtoPendingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoPendingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoPendingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOtoPendingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoPendingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOtoPendingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOtoPendingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoPendingPegOffsetTypeEnum value) {
    if (value == OrderListPlaceOtoPendingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtoPendingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtoPendingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtoPendingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOtoPendingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOtoPendingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtoPendingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOtoPendingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOtoPendingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOtoPendingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtoPendingPegPriceTypeEnum value) {
    if (value == OrderListPlaceOtoPendingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtoPendingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoWorkingTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoWorkingTypeEnum::Limit:
        return "LIMIT";
    case OrderListPlaceOtocoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListPlaceOtocoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return OrderListPlaceOtocoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListPlaceOtocoWorkingTypeEnum::LimitMaker;
    }
    return OrderListPlaceOtocoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoWorkingTypeEnum value) {
    if (value == OrderListPlaceOtocoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOtocoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoWorkingSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoWorkingSideEnum::Buy:
        return "BUY";
    case OrderListPlaceOtocoWorkingSideEnum::Sell:
        return "SELL";
    case OrderListPlaceOtocoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceOtocoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceOtocoWorkingSideEnum::Sell;
    }
    return OrderListPlaceOtocoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoWorkingSideEnum value) {
    if (value == OrderListPlaceOtocoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOtocoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoPendingSideEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoPendingSideEnum::Buy:
        return "BUY";
    case OrderListPlaceOtocoPendingSideEnum::Sell:
        return "SELL";
    case OrderListPlaceOtocoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderListPlaceOtocoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderListPlaceOtocoPendingSideEnum::Sell;
    }
    return OrderListPlaceOtocoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoPendingSideEnum value) {
    if (value == OrderListPlaceOtocoPendingSideEnum::Unknown) {
        throw std::invalid_argument("OrderListPlaceOtocoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoPendingAboveTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoPendingAboveTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListPlaceOtocoPendingAboveTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListPlaceOtocoPendingAboveTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderListPlaceOtocoPendingAboveTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListPlaceOtocoPendingAboveTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListPlaceOtocoPendingAboveTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListPlaceOtocoPendingAboveTypeEnum::StopLossLimit;
    }
    if (s == "STOP_LOSS") {
        return OrderListPlaceOtocoPendingAboveTypeEnum::StopLoss;
    }
    if (s == "LIMIT_MAKER") {
        return OrderListPlaceOtocoPendingAboveTypeEnum::LimitMaker;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListPlaceOtocoPendingAboveTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListPlaceOtocoPendingAboveTypeEnum::TakeProfitLimit;
    }
    return OrderListPlaceOtocoPendingAboveTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoPendingAboveTypeEnum value) {
    if (value == OrderListPlaceOtocoPendingAboveTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoPendingAboveTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderListPlaceOtocoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderListPlaceOtocoNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderListPlaceOtocoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderListPlaceOtocoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderListPlaceOtocoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderListPlaceOtocoNewOrderRespTypeEnum::Full;
    }
    return OrderListPlaceOtocoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoNewOrderRespTypeEnum value) {
    if (value == OrderListPlaceOtocoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderListPlaceOtocoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderListPlaceOtocoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderListPlaceOtocoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderListPlaceOtocoSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderListPlaceOtocoSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderListPlaceOtocoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderListPlaceOtocoSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderListPlaceOtocoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderListPlaceOtocoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderListPlaceOtocoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderListPlaceOtocoSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderListPlaceOtocoSelfTradePreventionModeEnum::Transfer;
    }
    return OrderListPlaceOtocoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoSelfTradePreventionModeEnum value) {
    if (value == OrderListPlaceOtocoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOtocoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOtocoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOtocoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOtocoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOtocoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOtocoWorkingTimeInForceEnum::Fok;
    }
    return OrderListPlaceOtocoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoWorkingTimeInForceEnum value) {
    if (value == OrderListPlaceOtocoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoWorkingPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoWorkingPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOtocoWorkingPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOtocoWorkingPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOtocoWorkingPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOtocoWorkingPegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOtocoWorkingPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoWorkingPegPriceTypeEnum value) {
    if (value == OrderListPlaceOtocoWorkingPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoWorkingPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoWorkingPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoWorkingPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOtocoWorkingPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOtocoWorkingPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOtocoWorkingPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoWorkingPegOffsetTypeEnum value) {
    if (value == OrderListPlaceOtocoWorkingPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoWorkingPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoPendingAboveTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoPendingAboveTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOtocoPendingAboveTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOtocoPendingAboveTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOtocoPendingAboveTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOtocoPendingAboveTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOtocoPendingAboveTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOtocoPendingAboveTimeInForceEnum::Fok;
    }
    return OrderListPlaceOtocoPendingAboveTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoPendingAboveTimeInForceEnum value) {
    if (value == OrderListPlaceOtocoPendingAboveTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoPendingAboveTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoPendingAbovePegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoPendingAbovePegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOtocoPendingAbovePegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOtocoPendingAbovePegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoPendingAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOtocoPendingAbovePegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOtocoPendingAbovePegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOtocoPendingAbovePegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoPendingAbovePegPriceTypeEnum value) {
    if (value == OrderListPlaceOtocoPendingAbovePegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoPendingAbovePegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum value) {
    if (value == OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoPendingBelowTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoPendingBelowTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderListPlaceOtocoPendingBelowTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderListPlaceOtocoPendingBelowTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderListPlaceOtocoPendingBelowTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderListPlaceOtocoPendingBelowTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "STOP_LOSS") {
        return OrderListPlaceOtocoPendingBelowTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderListPlaceOtocoPendingBelowTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderListPlaceOtocoPendingBelowTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderListPlaceOtocoPendingBelowTypeEnum::TakeProfitLimit;
    }
    return OrderListPlaceOtocoPendingBelowTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoPendingBelowTypeEnum value) {
    if (value == OrderListPlaceOtocoPendingBelowTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoPendingBelowTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoPendingBelowTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoPendingBelowTimeInForceEnum::Gtc:
        return "GTC";
    case OrderListPlaceOtocoPendingBelowTimeInForceEnum::Ioc:
        return "IOC";
    case OrderListPlaceOtocoPendingBelowTimeInForceEnum::Fok:
        return "FOK";
    case OrderListPlaceOtocoPendingBelowTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderListPlaceOtocoPendingBelowTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderListPlaceOtocoPendingBelowTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderListPlaceOtocoPendingBelowTimeInForceEnum::Fok;
    }
    return OrderListPlaceOtocoPendingBelowTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoPendingBelowTimeInForceEnum value) {
    if (value == OrderListPlaceOtocoPendingBelowTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoPendingBelowTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoPendingBelowPegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoPendingBelowPegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderListPlaceOtocoPendingBelowPegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderListPlaceOtocoPendingBelowPegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoPendingBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderListPlaceOtocoPendingBelowPegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderListPlaceOtocoPendingBelowPegPriceTypeEnum::MarketPeg;
    }
    return OrderListPlaceOtocoPendingBelowPegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoPendingBelowPegPriceTypeEnum value) {
    if (value == OrderListPlaceOtocoPendingBelowPegPriceTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoPendingBelowPegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum::PriceLevel;
    }
    return OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum value) {
    if (value == OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderPlaceSideEnum value) noexcept {
    switch (value) {
    case OrderPlaceSideEnum::Buy:
        return "BUY";
    case OrderPlaceSideEnum::Sell:
        return "SELL";
    case OrderPlaceSideEnum::Unknown:
        break;
    }
    return "";
}

OrderPlaceSideEnum tag_invoke(boost::json::value_to_tag<OrderPlaceSideEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OrderPlaceSideEnum::Buy;
    }
    if (s == "SELL") {
        return OrderPlaceSideEnum::Sell;
    }
    return OrderPlaceSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderPlaceSideEnum value) {
    if (value == OrderPlaceSideEnum::Unknown) {
        throw std::invalid_argument("OrderPlaceSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderPlaceTypeEnum value) noexcept {
    switch (value) {
    case OrderPlaceTypeEnum::Market:
        return "MARKET";
    case OrderPlaceTypeEnum::Limit:
        return "LIMIT";
    case OrderPlaceTypeEnum::StopLoss:
        return "STOP_LOSS";
    case OrderPlaceTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case OrderPlaceTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case OrderPlaceTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case OrderPlaceTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case OrderPlaceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderPlaceTypeEnum tag_invoke(boost::json::value_to_tag<OrderPlaceTypeEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return OrderPlaceTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return OrderPlaceTypeEnum::Limit;
    }
    if (s == "STOP_LOSS") {
        return OrderPlaceTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return OrderPlaceTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return OrderPlaceTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return OrderPlaceTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return OrderPlaceTypeEnum::LimitMaker;
    }
    return OrderPlaceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderPlaceTypeEnum value) {
    if (value == OrderPlaceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderPlaceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderPlaceTimeInForceEnum value) noexcept {
    switch (value) {
    case OrderPlaceTimeInForceEnum::Gtc:
        return "GTC";
    case OrderPlaceTimeInForceEnum::Ioc:
        return "IOC";
    case OrderPlaceTimeInForceEnum::Fok:
        return "FOK";
    case OrderPlaceTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

OrderPlaceTimeInForceEnum tag_invoke(boost::json::value_to_tag<OrderPlaceTimeInForceEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return OrderPlaceTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return OrderPlaceTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return OrderPlaceTimeInForceEnum::Fok;
    }
    return OrderPlaceTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderPlaceTimeInForceEnum value) {
    if (value == OrderPlaceTimeInForceEnum::Unknown) {
        throw std::invalid_argument("OrderPlaceTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderPlaceNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case OrderPlaceNewOrderRespTypeEnum::Ack:
        return "ACK";
    case OrderPlaceNewOrderRespTypeEnum::Result:
        return "RESULT";
    case OrderPlaceNewOrderRespTypeEnum::Full:
        return "FULL";
    case OrderPlaceNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderPlaceNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderPlaceNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return OrderPlaceNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return OrderPlaceNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return OrderPlaceNewOrderRespTypeEnum::Full;
    }
    return OrderPlaceNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderPlaceNewOrderRespTypeEnum value) {
    if (value == OrderPlaceNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("OrderPlaceNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderPlaceSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case OrderPlaceSelfTradePreventionModeEnum::None_:
        return "NONE";
    case OrderPlaceSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case OrderPlaceSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case OrderPlaceSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case OrderPlaceSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case OrderPlaceSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case OrderPlaceSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

OrderPlaceSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderPlaceSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return OrderPlaceSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return OrderPlaceSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return OrderPlaceSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return OrderPlaceSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return OrderPlaceSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return OrderPlaceSelfTradePreventionModeEnum::Transfer;
    }
    return OrderPlaceSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderPlaceSelfTradePreventionModeEnum value) {
    if (value == OrderPlaceSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "OrderPlaceSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderPlacePegPriceTypeEnum value) noexcept {
    switch (value) {
    case OrderPlacePegPriceTypeEnum::PrimaryPeg:
        return "PRIMARY_PEG";
    case OrderPlacePegPriceTypeEnum::MarketPeg:
        return "MARKET_PEG";
    case OrderPlacePegPriceTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderPlacePegPriceTypeEnum tag_invoke(boost::json::value_to_tag<OrderPlacePegPriceTypeEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRIMARY_PEG") {
        return OrderPlacePegPriceTypeEnum::PrimaryPeg;
    }
    if (s == "MARKET_PEG") {
        return OrderPlacePegPriceTypeEnum::MarketPeg;
    }
    return OrderPlacePegPriceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderPlacePegPriceTypeEnum value) {
    if (value == OrderPlacePegPriceTypeEnum::Unknown) {
        throw std::invalid_argument("OrderPlacePegPriceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OrderPlacePegOffsetTypeEnum value) noexcept {
    switch (value) {
    case OrderPlacePegOffsetTypeEnum::PriceLevel:
        return "PRICE_LEVEL";
    case OrderPlacePegOffsetTypeEnum::Unknown:
        break;
    }
    return "";
}

OrderPlacePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderPlacePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PRICE_LEVEL") {
        return OrderPlacePegOffsetTypeEnum::PriceLevel;
    }
    return OrderPlacePegOffsetTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OrderPlacePegOffsetTypeEnum value) {
    if (value == OrderPlacePegOffsetTypeEnum::Unknown) {
        throw std::invalid_argument("OrderPlacePegOffsetTypeEnum::Unknown cannot be sent");
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

std::string_view to_string(SorOrderPlaceSideEnum value) noexcept {
    switch (value) {
    case SorOrderPlaceSideEnum::Buy:
        return "BUY";
    case SorOrderPlaceSideEnum::Sell:
        return "SELL";
    case SorOrderPlaceSideEnum::Unknown:
        break;
    }
    return "";
}

SorOrderPlaceSideEnum tag_invoke(boost::json::value_to_tag<SorOrderPlaceSideEnum> /*tag*/,
                                 const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return SorOrderPlaceSideEnum::Buy;
    }
    if (s == "SELL") {
        return SorOrderPlaceSideEnum::Sell;
    }
    return SorOrderPlaceSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderPlaceSideEnum value) {
    if (value == SorOrderPlaceSideEnum::Unknown) {
        throw std::invalid_argument("SorOrderPlaceSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderPlaceTypeEnum value) noexcept {
    switch (value) {
    case SorOrderPlaceTypeEnum::Market:
        return "MARKET";
    case SorOrderPlaceTypeEnum::Limit:
        return "LIMIT";
    case SorOrderPlaceTypeEnum::Unknown:
        break;
    }
    return "";
}

SorOrderPlaceTypeEnum tag_invoke(boost::json::value_to_tag<SorOrderPlaceTypeEnum> /*tag*/,
                                 const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return SorOrderPlaceTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return SorOrderPlaceTypeEnum::Limit;
    }
    return SorOrderPlaceTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderPlaceTypeEnum value) {
    if (value == SorOrderPlaceTypeEnum::Unknown) {
        throw std::invalid_argument("SorOrderPlaceTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderPlaceTimeInForceEnum value) noexcept {
    switch (value) {
    case SorOrderPlaceTimeInForceEnum::Gtc:
        return "GTC";
    case SorOrderPlaceTimeInForceEnum::Ioc:
        return "IOC";
    case SorOrderPlaceTimeInForceEnum::Fok:
        return "FOK";
    case SorOrderPlaceTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

SorOrderPlaceTimeInForceEnum
tag_invoke(boost::json::value_to_tag<SorOrderPlaceTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return SorOrderPlaceTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return SorOrderPlaceTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return SorOrderPlaceTimeInForceEnum::Fok;
    }
    return SorOrderPlaceTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderPlaceTimeInForceEnum value) {
    if (value == SorOrderPlaceTimeInForceEnum::Unknown) {
        throw std::invalid_argument("SorOrderPlaceTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderPlaceNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case SorOrderPlaceNewOrderRespTypeEnum::Ack:
        return "ACK";
    case SorOrderPlaceNewOrderRespTypeEnum::Result:
        return "RESULT";
    case SorOrderPlaceNewOrderRespTypeEnum::Full:
        return "FULL";
    case SorOrderPlaceNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

SorOrderPlaceNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<SorOrderPlaceNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return SorOrderPlaceNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return SorOrderPlaceNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return SorOrderPlaceNewOrderRespTypeEnum::Full;
    }
    return SorOrderPlaceNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderPlaceNewOrderRespTypeEnum value) {
    if (value == SorOrderPlaceNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("SorOrderPlaceNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SorOrderPlaceSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case SorOrderPlaceSelfTradePreventionModeEnum::None_:
        return "NONE";
    case SorOrderPlaceSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case SorOrderPlaceSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case SorOrderPlaceSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case SorOrderPlaceSelfTradePreventionModeEnum::Decrement:
        return "DECREMENT";
    case SorOrderPlaceSelfTradePreventionModeEnum::Transfer:
        return "TRANSFER";
    case SorOrderPlaceSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

SorOrderPlaceSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<SorOrderPlaceSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return SorOrderPlaceSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return SorOrderPlaceSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return SorOrderPlaceSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return SorOrderPlaceSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "DECREMENT") {
        return SorOrderPlaceSelfTradePreventionModeEnum::Decrement;
    }
    if (s == "TRANSFER") {
        return SorOrderPlaceSelfTradePreventionModeEnum::Transfer;
    }
    return SorOrderPlaceSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SorOrderPlaceSelfTradePreventionModeEnum value) {
    if (value == SorOrderPlaceSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "SorOrderPlaceSelfTradePreventionModeEnum::Unknown cannot be sent");
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

TradeApi::TradeApi(std::shared_ptr<common::WebsocketApi> client) : client_(std::move(client)) {}

common::Params TradeApi::open_orders_cancel_all_payload(const OpenOrdersCancelAllParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<OpenOrdersCancelAllResponseResultInner>>
TradeApi::open_orders_cancel_all(const OpenOrdersCancelAllParams& params) const {
    return common::send<std::vector<OpenOrdersCancelAllResponseResultInner>>(
        *client_, "openOrders.cancelAll", open_orders_cancel_all_payload(params),
        make_options(false, true, false, false));
}

common::Params
TradeApi::order_amend_keep_priority_payload(const OrderAmendKeepPriorityParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "newQty", params.new_qty);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderAmendKeepPriorityResponseResult>
TradeApi::order_amend_keep_priority(const OrderAmendKeepPriorityParams& params) const {
    return common::send<OrderAmendKeepPriorityResponseResult>(
        *client_, "order.amend.keepPriority", order_amend_keep_priority_payload(params),
        make_options(false, true, false, false));
}

common::Params TradeApi::order_cancel_payload(const OrderCancelParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "orderId", params.order_id);
    common::detail::json::set_param(p, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "cancelRestrictions", params.cancel_restrictions);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderCancelResponseResult>
TradeApi::order_cancel(const OrderCancelParams& params) const {
    return common::send<OrderCancelResponseResult>(*client_, "order.cancel",
                                                   order_cancel_payload(params),
                                                   make_options(false, true, false, false));
}

common::Params TradeApi::order_cancel_replace_payload(const OrderCancelReplaceParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "cancelReplaceMode", params.cancel_replace_mode);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "type", params.type);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "cancelOrderId", params.cancel_order_id);
    common::detail::json::set_param(p, "cancelOrigClientOrderId",
                                    params.cancel_orig_client_order_id);
    common::detail::json::set_param(p, "cancelNewClientOrderId", params.cancel_new_client_order_id);
    common::detail::json::set_param(p, "timeInForce", params.time_in_force);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "quoteOrderQty", params.quote_order_qty);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "stopPrice", params.stop_price);
    common::detail::json::set_param(p, "trailingDelta", params.trailing_delta);
    common::detail::json::set_param(p, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(p, "strategyId", params.strategy_id);
    common::detail::json::set_param(p, "strategyType", params.strategy_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "cancelRestrictions", params.cancel_restrictions);
    common::detail::json::set_param(p, "orderRateLimitExceededMode",
                                    params.order_rate_limit_exceeded_mode);
    common::detail::json::set_param(p, "pegPriceType", params.peg_price_type);
    common::detail::json::set_param(p, "pegOffsetValue", params.peg_offset_value);
    common::detail::json::set_param(p, "pegOffsetType", params.peg_offset_type);
    common::detail::json::set_param(p, "quoteNotionalLimit", params.quote_notional_limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderCancelReplaceResponseResult>
TradeApi::order_cancel_replace(const OrderCancelReplaceParams& params) const {
    return common::send<OrderCancelReplaceResponseResult>(*client_, "order.cancelReplace",
                                                          order_cancel_replace_payload(params),
                                                          make_options(false, true, false, false));
}

common::Params TradeApi::order_list_cancel_payload(const OrderListCancelParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "orderListId", params.order_list_id);
    common::detail::json::set_param(p, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderListCancelResponseResult>
TradeApi::order_list_cancel(const OrderListCancelParams& params) const {
    return common::send<OrderListCancelResponseResult>(*client_, "orderList.cancel",
                                                       order_list_cancel_payload(params),
                                                       make_options(false, true, false, false));
}

common::Params TradeApi::order_list_place_payload(const OrderListPlaceParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(p, "limitClientOrderId", params.limit_client_order_id);
    common::detail::json::set_param(p, "limitIcebergQty", params.limit_iceberg_qty);
    common::detail::json::set_param(p, "limitStrategyId", params.limit_strategy_id);
    common::detail::json::set_param(p, "limitStrategyType", params.limit_strategy_type);
    common::detail::json::set_param(p, "stopPrice", params.stop_price);
    common::detail::json::set_param(p, "trailingDelta", params.trailing_delta);
    common::detail::json::set_param(p, "stopClientOrderId", params.stop_client_order_id);
    common::detail::json::set_param(p, "stopLimitPrice", params.stop_limit_price);
    common::detail::json::set_param(p, "stopLimitTimeInForce", params.stop_limit_time_in_force);
    common::detail::json::set_param(p, "stopIcebergQty", params.stop_iceberg_qty);
    common::detail::json::set_param(p, "stopStrategyId", params.stop_strategy_id);
    common::detail::json::set_param(p, "stopStrategyType", params.stop_strategy_type);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderListPlaceResponseResult>
TradeApi::order_list_place(const OrderListPlaceParams& params) const {
    return common::send<OrderListPlaceResponseResult>(*client_, "orderList.place",
                                                      order_list_place_payload(params),
                                                      make_options(false, true, false, false));
}

common::Params TradeApi::order_list_place_oco_payload(const OrderListPlaceOcoParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "aboveType", params.above_type);
    common::detail::json::set_param(p, "belowType", params.below_type);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(p, "aboveClientOrderId", params.above_client_order_id);
    common::detail::json::set_param(p, "aboveIcebergQty", params.above_iceberg_qty);
    common::detail::json::set_param(p, "abovePrice", params.above_price);
    common::detail::json::set_param(p, "aboveStopPrice", params.above_stop_price);
    common::detail::json::set_param(p, "aboveTrailingDelta", params.above_trailing_delta);
    common::detail::json::set_param(p, "aboveTimeInForce", params.above_time_in_force);
    common::detail::json::set_param(p, "aboveStrategyId", params.above_strategy_id);
    common::detail::json::set_param(p, "aboveStrategyType", params.above_strategy_type);
    common::detail::json::set_param(p, "abovePegPriceType", params.above_peg_price_type);
    common::detail::json::set_param(p, "abovePegOffsetType", params.above_peg_offset_type);
    common::detail::json::set_param(p, "abovePegOffsetValue", params.above_peg_offset_value);
    common::detail::json::set_param(p, "belowClientOrderId", params.below_client_order_id);
    common::detail::json::set_param(p, "belowIcebergQty", params.below_iceberg_qty);
    common::detail::json::set_param(p, "belowPrice", params.below_price);
    common::detail::json::set_param(p, "belowStopPrice", params.below_stop_price);
    common::detail::json::set_param(p, "belowTrailingDelta", params.below_trailing_delta);
    common::detail::json::set_param(p, "belowTimeInForce", params.below_time_in_force);
    common::detail::json::set_param(p, "belowStrategyId", params.below_strategy_id);
    common::detail::json::set_param(p, "belowStrategyType", params.below_strategy_type);
    common::detail::json::set_param(p, "belowPegPriceType", params.below_peg_price_type);
    common::detail::json::set_param(p, "belowPegOffsetType", params.below_peg_offset_type);
    common::detail::json::set_param(p, "belowPegOffsetValue", params.below_peg_offset_value);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "aboveQuoteNotionalLimit",
                                    params.above_quote_notional_limit);
    common::detail::json::set_param(p, "belowQuoteNotionalLimit",
                                    params.below_quote_notional_limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderListPlaceOcoResponseResult>
TradeApi::order_list_place_oco(const OrderListPlaceOcoParams& params) const {
    return common::send<OrderListPlaceOcoResponseResult>(*client_, "orderList.place.oco",
                                                         order_list_place_oco_payload(params),
                                                         make_options(false, true, false, false));
}

common::Params TradeApi::order_list_place_opo_payload(const OrderListPlaceOpoParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "workingType", params.working_type);
    common::detail::json::set_param(p, "workingSide", params.working_side);
    common::detail::json::set_param(p, "workingPrice", params.working_price);
    common::detail::json::set_param(p, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(p, "pendingType", params.pending_type);
    common::detail::json::set_param(p, "pendingSide", params.pending_side);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "workingClientOrderId", params.working_client_order_id);
    common::detail::json::set_param(p, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(p, "workingTimeInForce", params.working_time_in_force);
    common::detail::json::set_param(p, "workingStrategyId", params.working_strategy_id);
    common::detail::json::set_param(p, "workingStrategyType", params.working_strategy_type);
    common::detail::json::set_param(p, "workingPegPriceType", params.working_peg_price_type);
    common::detail::json::set_param(p, "workingPegOffsetType", params.working_peg_offset_type);
    common::detail::json::set_param(p, "workingPegOffsetValue", params.working_peg_offset_value);
    common::detail::json::set_param(p, "pendingClientOrderId", params.pending_client_order_id);
    common::detail::json::set_param(p, "pendingPrice", params.pending_price);
    common::detail::json::set_param(p, "pendingStopPrice", params.pending_stop_price);
    common::detail::json::set_param(p, "pendingTrailingDelta", params.pending_trailing_delta);
    common::detail::json::set_param(p, "pendingIcebergQty", params.pending_iceberg_qty);
    common::detail::json::set_param(p, "pendingTimeInForce", params.pending_time_in_force);
    common::detail::json::set_param(p, "pendingStrategyId", params.pending_strategy_id);
    common::detail::json::set_param(p, "pendingStrategyType", params.pending_strategy_type);
    common::detail::json::set_param(p, "pendingPegPriceType", params.pending_peg_price_type);
    common::detail::json::set_param(p, "pendingPegOffsetType", params.pending_peg_offset_type);
    common::detail::json::set_param(p, "pendingPegOffsetValue", params.pending_peg_offset_value);
    common::detail::json::set_param(p, "workingQuoteNotionalLimit",
                                    params.working_quote_notional_limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderListPlaceOpoResponseResult>
TradeApi::order_list_place_opo(const OrderListPlaceOpoParams& params) const {
    return common::send<OrderListPlaceOpoResponseResult>(*client_, "orderList.place.opo",
                                                         order_list_place_opo_payload(params),
                                                         make_options(false, true, false, false));
}

common::Params TradeApi::order_list_place_opoco_payload(const OrderListPlaceOpocoParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "workingType", params.working_type);
    common::detail::json::set_param(p, "workingSide", params.working_side);
    common::detail::json::set_param(p, "workingPrice", params.working_price);
    common::detail::json::set_param(p, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(p, "pendingSide", params.pending_side);
    common::detail::json::set_param(p, "pendingAboveType", params.pending_above_type);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "workingClientOrderId", params.working_client_order_id);
    common::detail::json::set_param(p, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(p, "workingTimeInForce", params.working_time_in_force);
    common::detail::json::set_param(p, "workingStrategyId", params.working_strategy_id);
    common::detail::json::set_param(p, "workingStrategyType", params.working_strategy_type);
    common::detail::json::set_param(p, "workingPegPriceType", params.working_peg_price_type);
    common::detail::json::set_param(p, "workingPegOffsetType", params.working_peg_offset_type);
    common::detail::json::set_param(p, "workingPegOffsetValue", params.working_peg_offset_value);
    common::detail::json::set_param(p, "pendingAboveClientOrderId",
                                    params.pending_above_client_order_id);
    common::detail::json::set_param(p, "pendingAbovePrice", params.pending_above_price);
    common::detail::json::set_param(p, "pendingAboveStopPrice", params.pending_above_stop_price);
    common::detail::json::set_param(p, "pendingAboveTrailingDelta",
                                    params.pending_above_trailing_delta);
    common::detail::json::set_param(p, "pendingAboveIcebergQty", params.pending_above_iceberg_qty);
    common::detail::json::set_param(p, "pendingAboveTimeInForce",
                                    params.pending_above_time_in_force);
    common::detail::json::set_param(p, "pendingAboveStrategyId", params.pending_above_strategy_id);
    common::detail::json::set_param(p, "pendingAboveStrategyType",
                                    params.pending_above_strategy_type);
    common::detail::json::set_param(p, "pendingAbovePegPriceType",
                                    params.pending_above_peg_price_type);
    common::detail::json::set_param(p, "pendingAbovePegOffsetType",
                                    params.pending_above_peg_offset_type);
    common::detail::json::set_param(p, "pendingAbovePegOffsetValue",
                                    params.pending_above_peg_offset_value);
    common::detail::json::set_param(p, "pendingBelowType", params.pending_below_type);
    common::detail::json::set_param(p, "pendingBelowClientOrderId",
                                    params.pending_below_client_order_id);
    common::detail::json::set_param(p, "pendingBelowPrice", params.pending_below_price);
    common::detail::json::set_param(p, "pendingBelowStopPrice", params.pending_below_stop_price);
    common::detail::json::set_param(p, "pendingBelowTrailingDelta",
                                    params.pending_below_trailing_delta);
    common::detail::json::set_param(p, "pendingBelowIcebergQty", params.pending_below_iceberg_qty);
    common::detail::json::set_param(p, "pendingBelowTimeInForce",
                                    params.pending_below_time_in_force);
    common::detail::json::set_param(p, "pendingBelowStrategyId", params.pending_below_strategy_id);
    common::detail::json::set_param(p, "pendingBelowStrategyType",
                                    params.pending_below_strategy_type);
    common::detail::json::set_param(p, "pendingBelowPegPriceType",
                                    params.pending_below_peg_price_type);
    common::detail::json::set_param(p, "pendingBelowPegOffsetType",
                                    params.pending_below_peg_offset_type);
    common::detail::json::set_param(p, "pendingBelowPegOffsetValue",
                                    params.pending_below_peg_offset_value);
    common::detail::json::set_param(p, "workingQuoteNotionalLimit",
                                    params.working_quote_notional_limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderListPlaceOpocoResponseResult>
TradeApi::order_list_place_opoco(const OrderListPlaceOpocoParams& params) const {
    return common::send<OrderListPlaceOpocoResponseResult>(*client_, "orderList.place.opoco",
                                                           order_list_place_opoco_payload(params),
                                                           make_options(false, true, false, false));
}

common::Params TradeApi::order_list_place_oto_payload(const OrderListPlaceOtoParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "workingType", params.working_type);
    common::detail::json::set_param(p, "workingSide", params.working_side);
    common::detail::json::set_param(p, "workingPrice", params.working_price);
    common::detail::json::set_param(p, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(p, "pendingType", params.pending_type);
    common::detail::json::set_param(p, "pendingSide", params.pending_side);
    common::detail::json::set_param(p, "pendingQuantity", params.pending_quantity);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "workingClientOrderId", params.working_client_order_id);
    common::detail::json::set_param(p, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(p, "workingTimeInForce", params.working_time_in_force);
    common::detail::json::set_param(p, "workingStrategyId", params.working_strategy_id);
    common::detail::json::set_param(p, "workingStrategyType", params.working_strategy_type);
    common::detail::json::set_param(p, "workingPegPriceType", params.working_peg_price_type);
    common::detail::json::set_param(p, "workingPegOffsetType", params.working_peg_offset_type);
    common::detail::json::set_param(p, "workingPegOffsetValue", params.working_peg_offset_value);
    common::detail::json::set_param(p, "pendingClientOrderId", params.pending_client_order_id);
    common::detail::json::set_param(p, "pendingPrice", params.pending_price);
    common::detail::json::set_param(p, "pendingStopPrice", params.pending_stop_price);
    common::detail::json::set_param(p, "pendingTrailingDelta", params.pending_trailing_delta);
    common::detail::json::set_param(p, "pendingIcebergQty", params.pending_iceberg_qty);
    common::detail::json::set_param(p, "pendingTimeInForce", params.pending_time_in_force);
    common::detail::json::set_param(p, "pendingStrategyId", params.pending_strategy_id);
    common::detail::json::set_param(p, "pendingStrategyType", params.pending_strategy_type);
    common::detail::json::set_param(p, "pendingPegOffsetType", params.pending_peg_offset_type);
    common::detail::json::set_param(p, "pendingPegPriceType", params.pending_peg_price_type);
    common::detail::json::set_param(p, "pendingPegOffsetValue", params.pending_peg_offset_value);
    common::detail::json::set_param(p, "workingQuoteNotionalLimit",
                                    params.working_quote_notional_limit);
    common::detail::json::set_param(p, "pendingQuoteNotionalLimit",
                                    params.pending_quote_notional_limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderListPlaceOtoResponseResult>
TradeApi::order_list_place_oto(const OrderListPlaceOtoParams& params) const {
    return common::send<OrderListPlaceOtoResponseResult>(*client_, "orderList.place.oto",
                                                         order_list_place_oto_payload(params),
                                                         make_options(false, true, false, false));
}

common::Params TradeApi::order_list_place_otoco_payload(const OrderListPlaceOtocoParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "workingType", params.working_type);
    common::detail::json::set_param(p, "workingSide", params.working_side);
    common::detail::json::set_param(p, "workingPrice", params.working_price);
    common::detail::json::set_param(p, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(p, "pendingSide", params.pending_side);
    common::detail::json::set_param(p, "pendingQuantity", params.pending_quantity);
    common::detail::json::set_param(p, "pendingAboveType", params.pending_above_type);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "workingClientOrderId", params.working_client_order_id);
    common::detail::json::set_param(p, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(p, "workingTimeInForce", params.working_time_in_force);
    common::detail::json::set_param(p, "workingStrategyId", params.working_strategy_id);
    common::detail::json::set_param(p, "workingStrategyType", params.working_strategy_type);
    common::detail::json::set_param(p, "workingPegPriceType", params.working_peg_price_type);
    common::detail::json::set_param(p, "workingPegOffsetType", params.working_peg_offset_type);
    common::detail::json::set_param(p, "workingPegOffsetValue", params.working_peg_offset_value);
    common::detail::json::set_param(p, "pendingAboveClientOrderId",
                                    params.pending_above_client_order_id);
    common::detail::json::set_param(p, "pendingAbovePrice", params.pending_above_price);
    common::detail::json::set_param(p, "pendingAboveStopPrice", params.pending_above_stop_price);
    common::detail::json::set_param(p, "pendingAboveTrailingDelta",
                                    params.pending_above_trailing_delta);
    common::detail::json::set_param(p, "pendingAboveIcebergQty", params.pending_above_iceberg_qty);
    common::detail::json::set_param(p, "pendingAboveTimeInForce",
                                    params.pending_above_time_in_force);
    common::detail::json::set_param(p, "pendingAboveStrategyId", params.pending_above_strategy_id);
    common::detail::json::set_param(p, "pendingAboveStrategyType",
                                    params.pending_above_strategy_type);
    common::detail::json::set_param(p, "pendingAbovePegPriceType",
                                    params.pending_above_peg_price_type);
    common::detail::json::set_param(p, "pendingAbovePegOffsetType",
                                    params.pending_above_peg_offset_type);
    common::detail::json::set_param(p, "pendingAbovePegOffsetValue",
                                    params.pending_above_peg_offset_value);
    common::detail::json::set_param(p, "pendingBelowType", params.pending_below_type);
    common::detail::json::set_param(p, "pendingBelowClientOrderId",
                                    params.pending_below_client_order_id);
    common::detail::json::set_param(p, "pendingBelowPrice", params.pending_below_price);
    common::detail::json::set_param(p, "pendingBelowStopPrice", params.pending_below_stop_price);
    common::detail::json::set_param(p, "pendingBelowTrailingDelta",
                                    params.pending_below_trailing_delta);
    common::detail::json::set_param(p, "pendingBelowIcebergQty", params.pending_below_iceberg_qty);
    common::detail::json::set_param(p, "pendingBelowTimeInForce",
                                    params.pending_below_time_in_force);
    common::detail::json::set_param(p, "pendingBelowStrategyId", params.pending_below_strategy_id);
    common::detail::json::set_param(p, "pendingBelowStrategyType",
                                    params.pending_below_strategy_type);
    common::detail::json::set_param(p, "pendingBelowPegPriceType",
                                    params.pending_below_peg_price_type);
    common::detail::json::set_param(p, "pendingBelowPegOffsetType",
                                    params.pending_below_peg_offset_type);
    common::detail::json::set_param(p, "pendingBelowPegOffsetValue",
                                    params.pending_below_peg_offset_value);
    common::detail::json::set_param(p, "workingQuoteNotionalLimit",
                                    params.working_quote_notional_limit);
    common::detail::json::set_param(p, "pendingAboveQuoteNotionalLimit",
                                    params.pending_above_quote_notional_limit);
    common::detail::json::set_param(p, "pendingBelowQuoteNotionalLimit",
                                    params.pending_below_quote_notional_limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderListPlaceOtocoResponseResult>
TradeApi::order_list_place_otoco(const OrderListPlaceOtocoParams& params) const {
    return common::send<OrderListPlaceOtocoResponseResult>(*client_, "orderList.place.otoco",
                                                           order_list_place_otoco_payload(params),
                                                           make_options(false, true, false, false));
}

common::Params TradeApi::order_place_payload(const OrderPlaceParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "type", params.type);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "timeInForce", params.time_in_force);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "quoteOrderQty", params.quote_order_qty);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "stopPrice", params.stop_price);
    common::detail::json::set_param(p, "trailingDelta", params.trailing_delta);
    common::detail::json::set_param(p, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(p, "strategyId", params.strategy_id);
    common::detail::json::set_param(p, "strategyType", params.strategy_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "pegPriceType", params.peg_price_type);
    common::detail::json::set_param(p, "pegOffsetValue", params.peg_offset_value);
    common::detail::json::set_param(p, "pegOffsetType", params.peg_offset_type);
    common::detail::json::set_param(p, "quoteNotionalLimit", params.quote_notional_limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderPlaceResponseResult>
TradeApi::order_place(const OrderPlaceParams& params) const {
    return common::send<OrderPlaceResponseResult>(*client_, "order.place",
                                                  order_place_payload(params),
                                                  make_options(false, true, false, false));
}

common::Params TradeApi::order_test_payload(const OrderTestParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "type", params.type);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "computeCommissionRates", params.compute_commission_rates);
    common::detail::json::set_param(p, "timeInForce", params.time_in_force);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "quoteOrderQty", params.quote_order_qty);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "stopPrice", params.stop_price);
    common::detail::json::set_param(p, "trailingDelta", params.trailing_delta);
    common::detail::json::set_param(p, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(p, "strategyId", params.strategy_id);
    common::detail::json::set_param(p, "strategyType", params.strategy_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "pegPriceType", params.peg_price_type);
    common::detail::json::set_param(p, "pegOffsetValue", params.peg_offset_value);
    common::detail::json::set_param(p, "pegOffsetType", params.peg_offset_type);
    common::detail::json::set_param(p, "quoteNotionalLimit", params.quote_notional_limit);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<OrderTestResponseResult>
TradeApi::order_test(const OrderTestParams& params) const {
    return common::send<OrderTestResponseResult>(*client_, "order.test", order_test_payload(params),
                                                 make_options(false, true, false, false));
}

common::Params TradeApi::sor_order_place_payload(const SorOrderPlaceParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "type", params.type);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "timeInForce", params.time_in_force);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(p, "strategyId", params.strategy_id);
    common::detail::json::set_param(p, "strategyType", params.strategy_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<SorOrderPlaceResponseResultInner>>
TradeApi::sor_order_place(const SorOrderPlaceParams& params) const {
    return common::send<std::vector<SorOrderPlaceResponseResultInner>>(
        *client_, "sor.order.place", sor_order_place_payload(params),
        make_options(false, true, false, false));
}

common::Params TradeApi::sor_order_test_payload(const SorOrderTestParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "side", params.side);
    common::detail::json::set_param(p, "type", params.type);
    common::detail::json::set_param(p, "quantity", params.quantity);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "computeCommissionRates", params.compute_commission_rates);
    common::detail::json::set_param(p, "timeInForce", params.time_in_force);
    common::detail::json::set_param(p, "price", params.price);
    common::detail::json::set_param(p, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(p, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(p, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(p, "strategyId", params.strategy_id);
    common::detail::json::set_param(p, "strategyType", params.strategy_type);
    common::detail::json::set_param(p, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<SorOrderTestResponseResult>
TradeApi::sor_order_test(const SorOrderTestParams& params) const {
    return common::send<SorOrderTestResponseResult>(*client_, "sor.order.test",
                                                    sor_order_test_payload(params),
                                                    make_options(false, true, false, false));
}

} // namespace binance::spot::websocket_api
