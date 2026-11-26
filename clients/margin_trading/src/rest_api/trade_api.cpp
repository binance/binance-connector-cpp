//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/trade_api.hpp>

namespace binance::margin_trading::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(CreateSpecialKeyPermissionModeEnum value) noexcept {
    switch (value) {
    case CreateSpecialKeyPermissionModeEnum::Trade:
        return "TRADE";
    case CreateSpecialKeyPermissionModeEnum::Read:
        return "READ";
    case CreateSpecialKeyPermissionModeEnum::Unknown:
        break;
    }
    return "";
}

CreateSpecialKeyPermissionModeEnum
tag_invoke(boost::json::value_to_tag<CreateSpecialKeyPermissionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADE") {
        return CreateSpecialKeyPermissionModeEnum::Trade;
    }
    if (s == "READ") {
        return CreateSpecialKeyPermissionModeEnum::Read;
    }
    return CreateSpecialKeyPermissionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                CreateSpecialKeyPermissionModeEnum value) {
    if (value == CreateSpecialKeyPermissionModeEnum::Unknown) {
        throw std::invalid_argument("CreateSpecialKeyPermissionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum value) noexcept {
    switch (value) {
    case MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum::True_:
        return "TRUE";
    case MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum::False_:
        return "FALSE";
    case MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum tag_invoke(
    boost::json::value_to_tag<MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum::False_;
    }
    return MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum value) {
    if (value == MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryMarginAccountsOpenOrdersIsIsolatedEnum value) noexcept {
    switch (value) {
    case QueryMarginAccountsOpenOrdersIsIsolatedEnum::True_:
        return "TRUE";
    case QueryMarginAccountsOpenOrdersIsIsolatedEnum::False_:
        return "FALSE";
    case QueryMarginAccountsOpenOrdersIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginAccountsOpenOrdersIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOpenOrdersIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return QueryMarginAccountsOpenOrdersIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return QueryMarginAccountsOpenOrdersIsIsolatedEnum::False_;
    }
    return QueryMarginAccountsOpenOrdersIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginAccountsOpenOrdersIsIsolatedEnum value) {
    if (value == QueryMarginAccountsOpenOrdersIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "QueryMarginAccountsOpenOrdersIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountCancelOcoIsIsolatedEnum value) noexcept {
    switch (value) {
    case MarginAccountCancelOcoIsIsolatedEnum::True_:
        return "TRUE";
    case MarginAccountCancelOcoIsIsolatedEnum::False_:
        return "FALSE";
    case MarginAccountCancelOcoIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountCancelOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountCancelOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return MarginAccountCancelOcoIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return MarginAccountCancelOcoIsIsolatedEnum::False_;
    }
    return MarginAccountCancelOcoIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountCancelOcoIsIsolatedEnum value) {
    if (value == MarginAccountCancelOcoIsIsolatedEnum::Unknown) {
        throw std::invalid_argument("MarginAccountCancelOcoIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryMarginAccountsOcoIsIsolatedEnum value) noexcept {
    switch (value) {
    case QueryMarginAccountsOcoIsIsolatedEnum::True_:
        return "TRUE";
    case QueryMarginAccountsOcoIsIsolatedEnum::False_:
        return "FALSE";
    case QueryMarginAccountsOcoIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginAccountsOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return QueryMarginAccountsOcoIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return QueryMarginAccountsOcoIsIsolatedEnum::False_;
    }
    return QueryMarginAccountsOcoIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginAccountsOcoIsIsolatedEnum value) {
    if (value == QueryMarginAccountsOcoIsIsolatedEnum::Unknown) {
        throw std::invalid_argument("QueryMarginAccountsOcoIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountCancelOrderIsIsolatedEnum value) noexcept {
    switch (value) {
    case MarginAccountCancelOrderIsIsolatedEnum::True_:
        return "TRUE";
    case MarginAccountCancelOrderIsIsolatedEnum::False_:
        return "FALSE";
    case MarginAccountCancelOrderIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountCancelOrderIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountCancelOrderIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return MarginAccountCancelOrderIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return MarginAccountCancelOrderIsIsolatedEnum::False_;
    }
    return MarginAccountCancelOrderIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountCancelOrderIsIsolatedEnum value) {
    if (value == MarginAccountCancelOrderIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountCancelOrderIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOrderSideEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOrderSideEnum::Buy:
        return "BUY";
    case MarginAccountNewOrderSideEnum::Sell:
        return "SELL";
    case MarginAccountNewOrderSideEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOrderSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return MarginAccountNewOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return MarginAccountNewOrderSideEnum::Sell;
    }
    return MarginAccountNewOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOrderSideEnum value) {
    if (value == MarginAccountNewOrderSideEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOrderTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOrderTypeEnum::Limit:
        return "LIMIT";
    case MarginAccountNewOrderTypeEnum::Market:
        return "MARKET";
    case MarginAccountNewOrderTypeEnum::StopLoss:
        return "STOP_LOSS";
    case MarginAccountNewOrderTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case MarginAccountNewOrderTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case MarginAccountNewOrderTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case MarginAccountNewOrderTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case MarginAccountNewOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOrderTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return MarginAccountNewOrderTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return MarginAccountNewOrderTypeEnum::Market;
    }
    if (s == "STOP_LOSS") {
        return MarginAccountNewOrderTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return MarginAccountNewOrderTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return MarginAccountNewOrderTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return MarginAccountNewOrderTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return MarginAccountNewOrderTypeEnum::LimitMaker;
    }
    return MarginAccountNewOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOrderTypeEnum value) {
    if (value == MarginAccountNewOrderTypeEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOrderIsIsolatedEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOrderIsIsolatedEnum::True_:
        return "TRUE";
    case MarginAccountNewOrderIsIsolatedEnum::False_:
        return "FALSE";
    case MarginAccountNewOrderIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOrderIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return MarginAccountNewOrderIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return MarginAccountNewOrderIsIsolatedEnum::False_;
    }
    return MarginAccountNewOrderIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOrderIsIsolatedEnum value) {
    if (value == MarginAccountNewOrderIsIsolatedEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOrderIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case MarginAccountNewOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case MarginAccountNewOrderNewOrderRespTypeEnum::Full:
        return "FULL";
    case MarginAccountNewOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return MarginAccountNewOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return MarginAccountNewOrderNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return MarginAccountNewOrderNewOrderRespTypeEnum::Full;
    }
    return MarginAccountNewOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOrderNewOrderRespTypeEnum value) {
    if (value == MarginAccountNewOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOrderSideEffectTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOrderSideEffectTypeEnum::NoSideEffect:
        return "NO_SIDE_EFFECT";
    case MarginAccountNewOrderSideEffectTypeEnum::MarginBuy:
        return "MARGIN_BUY";
    case MarginAccountNewOrderSideEffectTypeEnum::AutoRepay:
        return "AUTO_REPAY";
    case MarginAccountNewOrderSideEffectTypeEnum::AutoBorrowRepay:
        return "AUTO_BORROW_REPAY";
    case MarginAccountNewOrderSideEffectTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOrderSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NO_SIDE_EFFECT") {
        return MarginAccountNewOrderSideEffectTypeEnum::NoSideEffect;
    }
    if (s == "MARGIN_BUY") {
        return MarginAccountNewOrderSideEffectTypeEnum::MarginBuy;
    }
    if (s == "AUTO_REPAY") {
        return MarginAccountNewOrderSideEffectTypeEnum::AutoRepay;
    }
    if (s == "AUTO_BORROW_REPAY") {
        return MarginAccountNewOrderSideEffectTypeEnum::AutoBorrowRepay;
    }
    return MarginAccountNewOrderSideEffectTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOrderSideEffectTypeEnum value) {
    if (value == MarginAccountNewOrderSideEffectTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOrderSideEffectTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOrderTimeInForceEnum::Gtc:
        return "GTC";
    case MarginAccountNewOrderTimeInForceEnum::Ioc:
        return "IOC";
    case MarginAccountNewOrderTimeInForceEnum::Fok:
        return "FOK";
    case MarginAccountNewOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return MarginAccountNewOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return MarginAccountNewOrderTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return MarginAccountNewOrderTimeInForceEnum::Fok;
    }
    return MarginAccountNewOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOrderTimeInForceEnum value) {
    if (value == MarginAccountNewOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case MarginAccountNewOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case MarginAccountNewOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case MarginAccountNewOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case MarginAccountNewOrderSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "EXPIRE_TAKER") {
        return MarginAccountNewOrderSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return MarginAccountNewOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return MarginAccountNewOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "NONE") {
        return MarginAccountNewOrderSelfTradePreventionModeEnum::None_;
    }
    return MarginAccountNewOrderSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOrderSelfTradePreventionModeEnum value) {
    if (value == MarginAccountNewOrderSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOrderSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryMarginAccountsOrderIsIsolatedEnum value) noexcept {
    switch (value) {
    case QueryMarginAccountsOrderIsIsolatedEnum::True_:
        return "TRUE";
    case QueryMarginAccountsOrderIsIsolatedEnum::False_:
        return "FALSE";
    case QueryMarginAccountsOrderIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginAccountsOrderIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOrderIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return QueryMarginAccountsOrderIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return QueryMarginAccountsOrderIsIsolatedEnum::False_;
    }
    return QueryMarginAccountsOrderIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginAccountsOrderIsIsolatedEnum value) {
    if (value == QueryMarginAccountsOrderIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "QueryMarginAccountsOrderIsIsolatedEnum::Unknown cannot be sent");
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

std::string_view to_string(MarginAccountNewOcoIsIsolatedEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOcoIsIsolatedEnum::True_:
        return "TRUE";
    case MarginAccountNewOcoIsIsolatedEnum::False_:
        return "FALSE";
    case MarginAccountNewOcoIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return MarginAccountNewOcoIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return MarginAccountNewOcoIsIsolatedEnum::False_;
    }
    return MarginAccountNewOcoIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOcoIsIsolatedEnum value) {
    if (value == MarginAccountNewOcoIsIsolatedEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOcoIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOcoStopLimitTimeInForceEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOcoStopLimitTimeInForceEnum::Gtc:
        return "GTC";
    case MarginAccountNewOcoStopLimitTimeInForceEnum::Fok:
        return "FOK";
    case MarginAccountNewOcoStopLimitTimeInForceEnum::Ioc:
        return "IOC";
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
    if (s == "FOK") {
        return MarginAccountNewOcoStopLimitTimeInForceEnum::Fok;
    }
    if (s == "IOC") {
        return MarginAccountNewOcoStopLimitTimeInForceEnum::Ioc;
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
    case MarginAccountNewOcoNewOrderRespTypeEnum::Full:
        return "FULL";
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
    if (s == "FULL") {
        return MarginAccountNewOcoNewOrderRespTypeEnum::Full;
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
    case MarginAccountNewOcoSideEffectTypeEnum::AutoBorrowRepay:
        return "AUTO_BORROW_REPAY";
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
    if (s == "AUTO_BORROW_REPAY") {
        return MarginAccountNewOcoSideEffectTypeEnum::AutoBorrowRepay;
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

std::string_view to_string(MarginAccountNewOcoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOcoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case MarginAccountNewOcoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case MarginAccountNewOcoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case MarginAccountNewOcoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case MarginAccountNewOcoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOcoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "EXPIRE_TAKER") {
        return MarginAccountNewOcoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return MarginAccountNewOcoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return MarginAccountNewOcoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "NONE") {
        return MarginAccountNewOcoSelfTradePreventionModeEnum::None_;
    }
    return MarginAccountNewOcoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOcoSelfTradePreventionModeEnum value) {
    if (value == MarginAccountNewOcoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOcoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoWorkingTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoWorkingTypeEnum::Limit:
        return "LIMIT";
    case MarginAccountNewOtoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case MarginAccountNewOtoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return MarginAccountNewOtoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return MarginAccountNewOtoWorkingTypeEnum::LimitMaker;
    }
    return MarginAccountNewOtoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoWorkingTypeEnum value) {
    if (value == MarginAccountNewOtoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOtoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoWorkingSideEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoWorkingSideEnum::Buy:
        return "BUY";
    case MarginAccountNewOtoWorkingSideEnum::Sell:
        return "SELL";
    case MarginAccountNewOtoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return MarginAccountNewOtoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return MarginAccountNewOtoWorkingSideEnum::Sell;
    }
    return MarginAccountNewOtoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoWorkingSideEnum value) {
    if (value == MarginAccountNewOtoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOtoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoPendingTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoPendingTypeEnum::Limit:
        return "LIMIT";
    case MarginAccountNewOtoPendingTypeEnum::Market:
        return "MARKET";
    case MarginAccountNewOtoPendingTypeEnum::StopLoss:
        return "STOP_LOSS";
    case MarginAccountNewOtoPendingTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case MarginAccountNewOtoPendingTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case MarginAccountNewOtoPendingTypeEnum::TakeProfitLimit:
        return "TAKE_PROFIT_LIMIT";
    case MarginAccountNewOtoPendingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case MarginAccountNewOtoPendingTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoPendingTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoPendingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return MarginAccountNewOtoPendingTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return MarginAccountNewOtoPendingTypeEnum::Market;
    }
    if (s == "STOP_LOSS") {
        return MarginAccountNewOtoPendingTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return MarginAccountNewOtoPendingTypeEnum::StopLossLimit;
    }
    if (s == "TAKE_PROFIT") {
        return MarginAccountNewOtoPendingTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_LIMIT") {
        return MarginAccountNewOtoPendingTypeEnum::TakeProfitLimit;
    }
    if (s == "LIMIT_MAKER") {
        return MarginAccountNewOtoPendingTypeEnum::LimitMaker;
    }
    return MarginAccountNewOtoPendingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoPendingTypeEnum value) {
    if (value == MarginAccountNewOtoPendingTypeEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOtoPendingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoPendingSideEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoPendingSideEnum::Buy:
        return "BUY";
    case MarginAccountNewOtoPendingSideEnum::Sell:
        return "SELL";
    case MarginAccountNewOtoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoPendingSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return MarginAccountNewOtoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return MarginAccountNewOtoPendingSideEnum::Sell;
    }
    return MarginAccountNewOtoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoPendingSideEnum value) {
    if (value == MarginAccountNewOtoPendingSideEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOtoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoIsIsolatedEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoIsIsolatedEnum::True_:
        return "TRUE";
    case MarginAccountNewOtoIsIsolatedEnum::False_:
        return "FALSE";
    case MarginAccountNewOtoIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return MarginAccountNewOtoIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return MarginAccountNewOtoIsIsolatedEnum::False_;
    }
    return MarginAccountNewOtoIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoIsIsolatedEnum value) {
    if (value == MarginAccountNewOtoIsIsolatedEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOtoIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case MarginAccountNewOtoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case MarginAccountNewOtoNewOrderRespTypeEnum::Full:
        return "FULL";
    case MarginAccountNewOtoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return MarginAccountNewOtoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return MarginAccountNewOtoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return MarginAccountNewOtoNewOrderRespTypeEnum::Full;
    }
    return MarginAccountNewOtoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoNewOrderRespTypeEnum value) {
    if (value == MarginAccountNewOtoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoSideEffectTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoSideEffectTypeEnum::NoSideEffect:
        return "NO_SIDE_EFFECT";
    case MarginAccountNewOtoSideEffectTypeEnum::MarginBuy:
        return "MARGIN_BUY";
    case MarginAccountNewOtoSideEffectTypeEnum::AutoBorrowRepay:
        return "AUTO_BORROW_REPAY";
    case MarginAccountNewOtoSideEffectTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NO_SIDE_EFFECT") {
        return MarginAccountNewOtoSideEffectTypeEnum::NoSideEffect;
    }
    if (s == "MARGIN_BUY") {
        return MarginAccountNewOtoSideEffectTypeEnum::MarginBuy;
    }
    if (s == "AUTO_BORROW_REPAY") {
        return MarginAccountNewOtoSideEffectTypeEnum::AutoBorrowRepay;
    }
    return MarginAccountNewOtoSideEffectTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoSideEffectTypeEnum value) {
    if (value == MarginAccountNewOtoSideEffectTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtoSideEffectTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case MarginAccountNewOtoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case MarginAccountNewOtoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case MarginAccountNewOtoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case MarginAccountNewOtoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "EXPIRE_TAKER") {
        return MarginAccountNewOtoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return MarginAccountNewOtoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return MarginAccountNewOtoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "NONE") {
        return MarginAccountNewOtoSelfTradePreventionModeEnum::None_;
    }
    return MarginAccountNewOtoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoSelfTradePreventionModeEnum value) {
    if (value == MarginAccountNewOtoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case MarginAccountNewOtoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case MarginAccountNewOtoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case MarginAccountNewOtoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return MarginAccountNewOtoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return MarginAccountNewOtoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return MarginAccountNewOtoWorkingTimeInForceEnum::Fok;
    }
    return MarginAccountNewOtoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoWorkingTimeInForceEnum value) {
    if (value == MarginAccountNewOtoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtoPendingTimeInForceEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtoPendingTimeInForceEnum::Gtc:
        return "GTC";
    case MarginAccountNewOtoPendingTimeInForceEnum::Ioc:
        return "IOC";
    case MarginAccountNewOtoPendingTimeInForceEnum::Fok:
        return "FOK";
    case MarginAccountNewOtoPendingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return MarginAccountNewOtoPendingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return MarginAccountNewOtoPendingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return MarginAccountNewOtoPendingTimeInForceEnum::Fok;
    }
    return MarginAccountNewOtoPendingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtoPendingTimeInForceEnum value) {
    if (value == MarginAccountNewOtoPendingTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtoPendingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoWorkingTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoWorkingTypeEnum::Limit:
        return "LIMIT";
    case MarginAccountNewOtocoWorkingTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case MarginAccountNewOtocoWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return MarginAccountNewOtocoWorkingTypeEnum::Limit;
    }
    if (s == "LIMIT_MAKER") {
        return MarginAccountNewOtocoWorkingTypeEnum::LimitMaker;
    }
    return MarginAccountNewOtocoWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoWorkingTypeEnum value) {
    if (value == MarginAccountNewOtocoWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOtocoWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoWorkingSideEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoWorkingSideEnum::Buy:
        return "BUY";
    case MarginAccountNewOtocoWorkingSideEnum::Sell:
        return "SELL";
    case MarginAccountNewOtocoWorkingSideEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return MarginAccountNewOtocoWorkingSideEnum::Buy;
    }
    if (s == "SELL") {
        return MarginAccountNewOtocoWorkingSideEnum::Sell;
    }
    return MarginAccountNewOtocoWorkingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoWorkingSideEnum value) {
    if (value == MarginAccountNewOtocoWorkingSideEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOtocoWorkingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoPendingSideEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoPendingSideEnum::Buy:
        return "BUY";
    case MarginAccountNewOtocoPendingSideEnum::Sell:
        return "SELL";
    case MarginAccountNewOtocoPendingSideEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoPendingSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return MarginAccountNewOtocoPendingSideEnum::Buy;
    }
    if (s == "SELL") {
        return MarginAccountNewOtocoPendingSideEnum::Sell;
    }
    return MarginAccountNewOtocoPendingSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoPendingSideEnum value) {
    if (value == MarginAccountNewOtocoPendingSideEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOtocoPendingSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoPendingAboveTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoPendingAboveTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case MarginAccountNewOtocoPendingAboveTypeEnum::StopLoss:
        return "STOP_LOSS";
    case MarginAccountNewOtocoPendingAboveTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case MarginAccountNewOtocoPendingAboveTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT_MAKER") {
        return MarginAccountNewOtocoPendingAboveTypeEnum::LimitMaker;
    }
    if (s == "STOP_LOSS") {
        return MarginAccountNewOtocoPendingAboveTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return MarginAccountNewOtocoPendingAboveTypeEnum::StopLossLimit;
    }
    return MarginAccountNewOtocoPendingAboveTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoPendingAboveTypeEnum value) {
    if (value == MarginAccountNewOtocoPendingAboveTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtocoPendingAboveTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoIsIsolatedEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoIsIsolatedEnum::True_:
        return "TRUE";
    case MarginAccountNewOtocoIsIsolatedEnum::False_:
        return "FALSE";
    case MarginAccountNewOtocoIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return MarginAccountNewOtocoIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return MarginAccountNewOtocoIsIsolatedEnum::False_;
    }
    return MarginAccountNewOtocoIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoIsIsolatedEnum value) {
    if (value == MarginAccountNewOtocoIsIsolatedEnum::Unknown) {
        throw std::invalid_argument("MarginAccountNewOtocoIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoSideEffectTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoSideEffectTypeEnum::NoSideEffect:
        return "NO_SIDE_EFFECT";
    case MarginAccountNewOtocoSideEffectTypeEnum::MarginBuy:
        return "MARGIN_BUY";
    case MarginAccountNewOtocoSideEffectTypeEnum::AutoBorrowRepay:
        return "AUTO_BORROW_REPAY";
    case MarginAccountNewOtocoSideEffectTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NO_SIDE_EFFECT") {
        return MarginAccountNewOtocoSideEffectTypeEnum::NoSideEffect;
    }
    if (s == "MARGIN_BUY") {
        return MarginAccountNewOtocoSideEffectTypeEnum::MarginBuy;
    }
    if (s == "AUTO_BORROW_REPAY") {
        return MarginAccountNewOtocoSideEffectTypeEnum::AutoBorrowRepay;
    }
    return MarginAccountNewOtocoSideEffectTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoSideEffectTypeEnum value) {
    if (value == MarginAccountNewOtocoSideEffectTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtocoSideEffectTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoNewOrderRespTypeEnum::Ack:
        return "ACK";
    case MarginAccountNewOtocoNewOrderRespTypeEnum::Result:
        return "RESULT";
    case MarginAccountNewOtocoNewOrderRespTypeEnum::Full:
        return "FULL";
    case MarginAccountNewOtocoNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return MarginAccountNewOtocoNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return MarginAccountNewOtocoNewOrderRespTypeEnum::Result;
    }
    if (s == "FULL") {
        return MarginAccountNewOtocoNewOrderRespTypeEnum::Full;
    }
    return MarginAccountNewOtocoNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoNewOrderRespTypeEnum value) {
    if (value == MarginAccountNewOtocoNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtocoNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case MarginAccountNewOtocoSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case MarginAccountNewOtocoSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case MarginAccountNewOtocoSelfTradePreventionModeEnum::None_:
        return "NONE";
    case MarginAccountNewOtocoSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "EXPIRE_TAKER") {
        return MarginAccountNewOtocoSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return MarginAccountNewOtocoSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return MarginAccountNewOtocoSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "NONE") {
        return MarginAccountNewOtocoSelfTradePreventionModeEnum::None_;
    }
    return MarginAccountNewOtocoSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoSelfTradePreventionModeEnum value) {
    if (value == MarginAccountNewOtocoSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtocoSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoWorkingTimeInForceEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoWorkingTimeInForceEnum::Gtc:
        return "GTC";
    case MarginAccountNewOtocoWorkingTimeInForceEnum::Ioc:
        return "IOC";
    case MarginAccountNewOtocoWorkingTimeInForceEnum::Fok:
        return "FOK";
    case MarginAccountNewOtocoWorkingTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return MarginAccountNewOtocoWorkingTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return MarginAccountNewOtocoWorkingTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return MarginAccountNewOtocoWorkingTimeInForceEnum::Fok;
    }
    return MarginAccountNewOtocoWorkingTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoWorkingTimeInForceEnum value) {
    if (value == MarginAccountNewOtocoWorkingTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtocoWorkingTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoPendingAboveTimeInForceEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoPendingAboveTimeInForceEnum::Gtc:
        return "GTC";
    case MarginAccountNewOtocoPendingAboveTimeInForceEnum::Ioc:
        return "IOC";
    case MarginAccountNewOtocoPendingAboveTimeInForceEnum::Fok:
        return "FOK";
    case MarginAccountNewOtocoPendingAboveTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return MarginAccountNewOtocoPendingAboveTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return MarginAccountNewOtocoPendingAboveTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return MarginAccountNewOtocoPendingAboveTimeInForceEnum::Fok;
    }
    return MarginAccountNewOtocoPendingAboveTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoPendingAboveTimeInForceEnum value) {
    if (value == MarginAccountNewOtocoPendingAboveTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtocoPendingAboveTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoPendingBelowTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoPendingBelowTypeEnum::LimitMaker:
        return "LIMIT_MAKER";
    case MarginAccountNewOtocoPendingBelowTypeEnum::StopLoss:
        return "STOP_LOSS";
    case MarginAccountNewOtocoPendingBelowTypeEnum::StopLossLimit:
        return "STOP_LOSS_LIMIT";
    case MarginAccountNewOtocoPendingBelowTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT_MAKER") {
        return MarginAccountNewOtocoPendingBelowTypeEnum::LimitMaker;
    }
    if (s == "STOP_LOSS") {
        return MarginAccountNewOtocoPendingBelowTypeEnum::StopLoss;
    }
    if (s == "STOP_LOSS_LIMIT") {
        return MarginAccountNewOtocoPendingBelowTypeEnum::StopLossLimit;
    }
    return MarginAccountNewOtocoPendingBelowTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoPendingBelowTypeEnum value) {
    if (value == MarginAccountNewOtocoPendingBelowTypeEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtocoPendingBelowTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountNewOtocoPendingBelowTimeInForceEnum value) noexcept {
    switch (value) {
    case MarginAccountNewOtocoPendingBelowTimeInForceEnum::Gtc:
        return "GTC";
    case MarginAccountNewOtocoPendingBelowTimeInForceEnum::Ioc:
        return "IOC";
    case MarginAccountNewOtocoPendingBelowTimeInForceEnum::Fok:
        return "FOK";
    case MarginAccountNewOtocoPendingBelowTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountNewOtocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return MarginAccountNewOtocoPendingBelowTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return MarginAccountNewOtocoPendingBelowTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return MarginAccountNewOtocoPendingBelowTimeInForceEnum::Fok;
    }
    return MarginAccountNewOtocoPendingBelowTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountNewOtocoPendingBelowTimeInForceEnum value) {
    if (value == MarginAccountNewOtocoPendingBelowTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountNewOtocoPendingBelowTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginManualLiquidationTypeEnum value) noexcept {
    switch (value) {
    case MarginManualLiquidationTypeEnum::Margin:
        return "MARGIN";
    case MarginManualLiquidationTypeEnum::Isolated:
        return "ISOLATED";
    case MarginManualLiquidationTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginManualLiquidationTypeEnum
tag_invoke(boost::json::value_to_tag<MarginManualLiquidationTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARGIN") {
        return MarginManualLiquidationTypeEnum::Margin;
    }
    if (s == "ISOLATED") {
        return MarginManualLiquidationTypeEnum::Isolated;
    }
    return MarginManualLiquidationTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginManualLiquidationTypeEnum value) {
    if (value == MarginManualLiquidationTypeEnum::Unknown) {
        throw std::invalid_argument("MarginManualLiquidationTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryCurrentMarginOrderCountUsageIsIsolatedEnum value) noexcept {
    switch (value) {
    case QueryCurrentMarginOrderCountUsageIsIsolatedEnum::True_:
        return "TRUE";
    case QueryCurrentMarginOrderCountUsageIsIsolatedEnum::False_:
        return "FALSE";
    case QueryCurrentMarginOrderCountUsageIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

QueryCurrentMarginOrderCountUsageIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryCurrentMarginOrderCountUsageIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return QueryCurrentMarginOrderCountUsageIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return QueryCurrentMarginOrderCountUsageIsIsolatedEnum::False_;
    }
    return QueryCurrentMarginOrderCountUsageIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryCurrentMarginOrderCountUsageIsIsolatedEnum value) {
    if (value == QueryCurrentMarginOrderCountUsageIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "QueryCurrentMarginOrderCountUsageIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryMarginAccountsAllOcoIsIsolatedEnum value) noexcept {
    switch (value) {
    case QueryMarginAccountsAllOcoIsIsolatedEnum::True_:
        return "TRUE";
    case QueryMarginAccountsAllOcoIsIsolatedEnum::False_:
        return "FALSE";
    case QueryMarginAccountsAllOcoIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginAccountsAllOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsAllOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return QueryMarginAccountsAllOcoIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return QueryMarginAccountsAllOcoIsIsolatedEnum::False_;
    }
    return QueryMarginAccountsAllOcoIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginAccountsAllOcoIsIsolatedEnum value) {
    if (value == QueryMarginAccountsAllOcoIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "QueryMarginAccountsAllOcoIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryMarginAccountsAllOrdersIsIsolatedEnum value) noexcept {
    switch (value) {
    case QueryMarginAccountsAllOrdersIsIsolatedEnum::True_:
        return "TRUE";
    case QueryMarginAccountsAllOrdersIsIsolatedEnum::False_:
        return "FALSE";
    case QueryMarginAccountsAllOrdersIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginAccountsAllOrdersIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsAllOrdersIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return QueryMarginAccountsAllOrdersIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return QueryMarginAccountsAllOrdersIsIsolatedEnum::False_;
    }
    return QueryMarginAccountsAllOrdersIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginAccountsAllOrdersIsIsolatedEnum value) {
    if (value == QueryMarginAccountsAllOrdersIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "QueryMarginAccountsAllOrdersIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryMarginAccountsOpenOcoIsIsolatedEnum value) noexcept {
    switch (value) {
    case QueryMarginAccountsOpenOcoIsIsolatedEnum::True_:
        return "TRUE";
    case QueryMarginAccountsOpenOcoIsIsolatedEnum::False_:
        return "FALSE";
    case QueryMarginAccountsOpenOcoIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginAccountsOpenOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOpenOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return QueryMarginAccountsOpenOcoIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return QueryMarginAccountsOpenOcoIsIsolatedEnum::False_;
    }
    return QueryMarginAccountsOpenOcoIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginAccountsOpenOcoIsIsolatedEnum value) {
    if (value == QueryMarginAccountsOpenOcoIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "QueryMarginAccountsOpenOcoIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryMarginAccountsTradeListIsIsolatedEnum value) noexcept {
    switch (value) {
    case QueryMarginAccountsTradeListIsIsolatedEnum::True_:
        return "TRUE";
    case QueryMarginAccountsTradeListIsIsolatedEnum::False_:
        return "FALSE";
    case QueryMarginAccountsTradeListIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginAccountsTradeListIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsTradeListIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return QueryMarginAccountsTradeListIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return QueryMarginAccountsTradeListIsIsolatedEnum::False_;
    }
    return QueryMarginAccountsTradeListIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginAccountsTradeListIsIsolatedEnum value) {
    if (value == QueryMarginAccountsTradeListIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "QueryMarginAccountsTradeListIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryPreventedMatchesIsIsolatedEnum value) noexcept {
    switch (value) {
    case QueryPreventedMatchesIsIsolatedEnum::True_:
        return "TRUE";
    case QueryPreventedMatchesIsIsolatedEnum::False_:
        return "FALSE";
    case QueryPreventedMatchesIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

QueryPreventedMatchesIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryPreventedMatchesIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return QueryPreventedMatchesIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return QueryPreventedMatchesIsIsolatedEnum::False_;
    }
    return QueryPreventedMatchesIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryPreventedMatchesIsIsolatedEnum value) {
    if (value == QueryPreventedMatchesIsIsolatedEnum::Unknown) {
        throw std::invalid_argument("QueryPreventedMatchesIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
TradeApi::create_special_key_request(const CreateSpecialKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/apiKey";
    common::detail::json::set_param(req.query, "apiName", params.api_name);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "ip", params.ip);
    common::detail::json::set_param(req.query, "publicKey", params.public_key);
    common::detail::json::set_param(req.query, "permissionMode", params.permission_mode);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CreateSpecialKeyResponse>
TradeApi::create_special_key(const CreateSpecialKeyParams& params) const {
    return common::send<CreateSpecialKeyResponse>(*client_, create_special_key_request(params));
}

common::RestRequest
TradeApi::delete_special_key_request(const DeleteSpecialKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/margin/apiKey";
    common::detail::json::set_param(req.query, "apiName", params.api_name);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<boost::json::value>
TradeApi::delete_special_key(const DeleteSpecialKeyParams& params) const {
    return common::send<boost::json::value>(*client_, delete_special_key_request(params));
}

common::RestRequest TradeApi::query_special_key_request(const QuerySpecialKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/apiKey";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySpecialKeyResponse>
TradeApi::query_special_key(const QuerySpecialKeyParams& params) const {
    return common::send<QuerySpecialKeyResponse>(*client_, query_special_key_request(params));
}

common::RestRequest
TradeApi::edit_ip_for_special_key_request(const EditIpForSpecialKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/sapi/v1/margin/apiKey/ip";
    common::detail::json::set_param(req.query, "ip", params.ip);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<boost::json::value>
TradeApi::edit_ip_for_special_key(const EditIpForSpecialKeyParams& params) const {
    return common::send<boost::json::value>(*client_, edit_ip_for_special_key_request(params));
}

common::RestRequest
TradeApi::exit_special_key_mode_request(const ExitSpecialKeyModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/exit-special-key-mode";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<boost::json::value>
TradeApi::exit_special_key_mode(const ExitSpecialKeyModeParams& params) const {
    return common::send<boost::json::value>(*client_, exit_special_key_mode_request(params));
}

common::RestRequest TradeApi::get_force_liquidation_record_request(
    const GetForceLiquidationRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/forceLiquidationRec";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "isolatedSymbol", params.isolated_symbol);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetForceLiquidationRecordResponse>
TradeApi::get_force_liquidation_record(const GetForceLiquidationRecordParams& params) const {
    return common::send<GetForceLiquidationRecordResponse>(
        *client_, get_force_liquidation_record_request(params));
}

common::RestRequest TradeApi::get_small_liability_exchange_coin_list_request(
    const GetSmallLiabilityExchangeCoinListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/exchange-small-liability";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetSmallLiabilityExchangeCoinListResponseInner>>
TradeApi::get_small_liability_exchange_coin_list(
    const GetSmallLiabilityExchangeCoinListParams& params) const {
    return common::send<std::vector<GetSmallLiabilityExchangeCoinListResponseInner>>(
        *client_, get_small_liability_exchange_coin_list_request(params));
}

common::RestRequest
TradeApi::small_liability_exchange_request(const SmallLiabilityExchangeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/exchange-small-liability";
    common::detail::json::set_param(req.query, "assetNames", params.asset_names);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<boost::json::value>
TradeApi::small_liability_exchange(const SmallLiabilityExchangeParams& params) const {
    return common::send<boost::json::value>(*client_, small_liability_exchange_request(params));
}

common::RestRequest TradeApi::get_small_liability_exchange_history_request(
    const GetSmallLiabilityExchangeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/exchange-small-liability-history";
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSmallLiabilityExchangeHistoryResponse>
TradeApi::get_small_liability_exchange_history(
    const GetSmallLiabilityExchangeHistoryParams& params) const {
    return common::send<GetSmallLiabilityExchangeHistoryResponse>(
        *client_, get_small_liability_exchange_history_request(params));
}

common::RestRequest
TradeApi::liquidation_loan_repay_request(const LiquidationLoanRepayParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/liquidation-loan/repay";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<LiquidationLoanRepayResponse>
TradeApi::liquidation_loan_repay(const LiquidationLoanRepayParams& params) const {
    return common::send<LiquidationLoanRepayResponse>(*client_,
                                                      liquidation_loan_repay_request(params));
}

common::RestRequest TradeApi::margin_account_cancel_all_open_orders_on_a_symbol_request(
    const MarginAccountCancelAllOpenOrdersOnASymbolParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/margin/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<MarginAccountCancelAllOpenOrdersOnASymbolResponseInner>>
TradeApi::margin_account_cancel_all_open_orders_on_a_symbol(
    const MarginAccountCancelAllOpenOrdersOnASymbolParams& params) const {
    return common::send<std::vector<MarginAccountCancelAllOpenOrdersOnASymbolResponseInner>>(
        *client_, margin_account_cancel_all_open_orders_on_a_symbol_request(params));
}

common::RestRequest TradeApi::query_margin_accounts_open_orders_request(
    const QueryMarginAccountsOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryMarginAccountsOpenOrdersResponseInner>>
TradeApi::query_margin_accounts_open_orders(
    const QueryMarginAccountsOpenOrdersParams& params) const {
    return common::send<std::vector<QueryMarginAccountsOpenOrdersResponseInner>>(
        *client_, query_margin_accounts_open_orders_request(params));
}

common::RestRequest
TradeApi::margin_account_cancel_oco_request(const MarginAccountCancelOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/margin/orderList";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "orderListId", params.order_list_id);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountCancelOcoResponse>
TradeApi::margin_account_cancel_oco(const MarginAccountCancelOcoParams& params) const {
    return common::send<MarginAccountCancelOcoResponse>(*client_,
                                                        margin_account_cancel_oco_request(params));
}

common::RestRequest
TradeApi::query_margin_accounts_oco_request(const QueryMarginAccountsOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/orderList";
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
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
TradeApi::margin_account_cancel_order_request(const MarginAccountCancelOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/margin/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountCancelOrderResponse>
TradeApi::margin_account_cancel_order(const MarginAccountCancelOrderParams& params) const {
    return common::send<MarginAccountCancelOrderResponse>(
        *client_, margin_account_cancel_order_request(params));
}

common::RestRequest
TradeApi::margin_account_new_order_request(const MarginAccountNewOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "quoteOrderQty", params.quote_order_qty);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "icebergQty", params.iceberg_qty);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "sideEffectType", params.side_effect_type);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "trailingDelta", params.trailing_delta);
    common::detail::json::set_param(req.query, "autoRepayAtCancel", params.auto_repay_at_cancel);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountNewOrderResponse>
TradeApi::margin_account_new_order(const MarginAccountNewOrderParams& params) const {
    return common::send<MarginAccountNewOrderResponse>(*client_,
                                                       margin_account_new_order_request(params));
}

common::RestRequest
TradeApi::query_margin_accounts_order_request(const QueryMarginAccountsOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryMarginAccountsOrderResponse>
TradeApi::query_margin_accounts_order(const QueryMarginAccountsOrderParams& params) const {
    return common::send<QueryMarginAccountsOrderResponse>(
        *client_, query_margin_accounts_order_request(params));
}

common::RestRequest
TradeApi::margin_account_new_oco_request(const MarginAccountNewOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/order/oco";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
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
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "autoRepayAtCancel", params.auto_repay_at_cancel);
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
TradeApi::margin_account_new_oto_request(const MarginAccountNewOtoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/order/oto";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "workingSide", params.working_side);
    common::detail::json::set_param(req.query, "workingPrice", params.working_price);
    common::detail::json::set_param(req.query, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(req.query, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(req.query, "pendingType", params.pending_type);
    common::detail::json::set_param(req.query, "pendingSide", params.pending_side);
    common::detail::json::set_param(req.query, "pendingQuantity", params.pending_quantity);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "sideEffectType", params.side_effect_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "autoRepayAtCancel", params.auto_repay_at_cancel);
    common::detail::json::set_param(req.query, "workingClientOrderId",
                                    params.working_client_order_id);
    common::detail::json::set_param(req.query, "workingTimeInForce", params.working_time_in_force);
    common::detail::json::set_param(req.query, "pendingClientOrderId",
                                    params.pending_client_order_id);
    common::detail::json::set_param(req.query, "pendingPrice", params.pending_price);
    common::detail::json::set_param(req.query, "pendingStopPrice", params.pending_stop_price);
    common::detail::json::set_param(req.query, "pendingTrailingDelta",
                                    params.pending_trailing_delta);
    common::detail::json::set_param(req.query, "pendingIcebergQty", params.pending_iceberg_qty);
    common::detail::json::set_param(req.query, "pendingTimeInForce", params.pending_time_in_force);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountNewOtoResponse>
TradeApi::margin_account_new_oto(const MarginAccountNewOtoParams& params) const {
    return common::send<MarginAccountNewOtoResponse>(*client_,
                                                     margin_account_new_oto_request(params));
}

common::RestRequest
TradeApi::margin_account_new_otoco_request(const MarginAccountNewOtocoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/order/otoco";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "workingSide", params.working_side);
    common::detail::json::set_param(req.query, "workingPrice", params.working_price);
    common::detail::json::set_param(req.query, "workingQuantity", params.working_quantity);
    common::detail::json::set_param(req.query, "pendingSide", params.pending_side);
    common::detail::json::set_param(req.query, "pendingQuantity", params.pending_quantity);
    common::detail::json::set_param(req.query, "pendingAboveType", params.pending_above_type);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "sideEffectType", params.side_effect_type);
    common::detail::json::set_param(req.query, "autoRepayAtCancel", params.auto_repay_at_cancel);
    common::detail::json::set_param(req.query, "listClientOrderId", params.list_client_order_id);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "workingClientOrderId",
                                    params.working_client_order_id);
    common::detail::json::set_param(req.query, "workingIcebergQty", params.working_iceberg_qty);
    common::detail::json::set_param(req.query, "workingTimeInForce", params.working_time_in_force);
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
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountNewOtocoResponse>
TradeApi::margin_account_new_otoco(const MarginAccountNewOtocoParams& params) const {
    return common::send<MarginAccountNewOtocoResponse>(*client_,
                                                       margin_account_new_otoco_request(params));
}

common::RestRequest
TradeApi::margin_manual_liquidation_request(const MarginManualLiquidationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/manual-liquidation";
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginManualLiquidationResponse>
TradeApi::margin_manual_liquidation(const MarginManualLiquidationParams& params) const {
    return common::send<MarginManualLiquidationResponse>(*client_,
                                                         margin_manual_liquidation_request(params));
}

common::RestRequest TradeApi::query_current_margin_order_count_usage_request(
    const QueryCurrentMarginOrderCountUsageParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/rateLimit/order";
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryCurrentMarginOrderCountUsageResponseInner>>
TradeApi::query_current_margin_order_count_usage(
    const QueryCurrentMarginOrderCountUsageParams& params) const {
    return common::send<std::vector<QueryCurrentMarginOrderCountUsageResponseInner>>(
        *client_, query_current_margin_order_count_usage_request(params));
}

common::RestRequest
TradeApi::query_liquidation_loan_request(const QueryLiquidationLoanParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/liquidation-loan";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryLiquidationLoanResponse>
TradeApi::query_liquidation_loan(const QueryLiquidationLoanParams& params) const {
    return common::send<QueryLiquidationLoanResponse>(*client_,
                                                      query_liquidation_loan_request(params));
}

common::RestRequest TradeApi::query_liquidation_loan_repay_history_request(
    const QueryLiquidationLoanRepayHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/liquidation-loan/repay-history";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryLiquidationLoanRepayHistoryResponse>
TradeApi::query_liquidation_loan_repay_history(
    const QueryLiquidationLoanRepayHistoryParams& params) const {
    return common::send<QueryLiquidationLoanRepayHistoryResponse>(
        *client_, query_liquidation_loan_repay_history_request(params));
}

common::RestRequest TradeApi::query_margin_accounts_all_oco_request(
    const QueryMarginAccountsAllOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/allOrderList";
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
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

common::RestRequest TradeApi::query_margin_accounts_all_orders_request(
    const QueryMarginAccountsAllOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/allOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryMarginAccountsAllOrdersResponseInner>>
TradeApi::query_margin_accounts_all_orders(const QueryMarginAccountsAllOrdersParams& params) const {
    return common::send<std::vector<QueryMarginAccountsAllOrdersResponseInner>>(
        *client_, query_margin_accounts_all_orders_request(params));
}

common::RestRequest TradeApi::query_margin_accounts_open_oco_request(
    const QueryMarginAccountsOpenOcoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/openOrderList";
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
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

common::RestRequest TradeApi::query_margin_accounts_open_otootoco_order_lists_request(
    const QueryMarginAccountsOpenOtootocoOrderListsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/oto/openOrderList";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryMarginAccountsOpenOtootocoOrderListsResponseInner>>
TradeApi::query_margin_accounts_open_otootoco_order_lists(
    const QueryMarginAccountsOpenOtootocoOrderListsParams& params) const {
    return common::send<std::vector<QueryMarginAccountsOpenOtootocoOrderListsResponseInner>>(
        *client_, query_margin_accounts_open_otootoco_order_lists_request(params));
}

common::RestRequest TradeApi::query_margin_accounts_trade_list_request(
    const QueryMarginAccountsTradeListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/myTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
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

common::RestApiResponse<std::vector<QueryMarginAccountsTradeListResponseInner>>
TradeApi::query_margin_accounts_trade_list(const QueryMarginAccountsTradeListParams& params) const {
    return common::send<std::vector<QueryMarginAccountsTradeListResponseInner>>(
        *client_, query_margin_accounts_trade_list_request(params));
}

common::RestRequest
TradeApi::query_prevented_matches_request(const QueryPreventedMatchesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/myPreventedMatches";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "preventedMatchId", params.prevented_match_id);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "fromPreventedMatchId",
                                    params.from_prevented_match_id);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryPreventedMatchesResponseInner>>
TradeApi::query_prevented_matches(const QueryPreventedMatchesParams& params) const {
    return common::send<std::vector<QueryPreventedMatchesResponseInner>>(
        *client_, query_prevented_matches_request(params));
}

common::RestRequest
TradeApi::query_special_key_list_request(const QuerySpecialKeyListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/api-key-list";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QuerySpecialKeyListResponseInner>>
TradeApi::query_special_key_list(const QuerySpecialKeyListParams& params) const {
    return common::send<std::vector<QuerySpecialKeyListResponseInner>>(
        *client_, query_special_key_list_request(params));
}

} // namespace binance::margin_trading::rest_api
