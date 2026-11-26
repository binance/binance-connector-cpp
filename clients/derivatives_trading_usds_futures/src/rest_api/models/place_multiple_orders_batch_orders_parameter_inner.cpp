//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>
#include <string_view>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/place_multiple_orders_batch_orders_parameter_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

std::string_view to_string(PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum::Buy:
        return "BUY";
    case PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum::Sell:
        return "SELL";
    case PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum::Buy;
    }
    if (s == "SELL") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum::Sell;
    }
    return PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum value) {
    if (value == PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Both:
        return "BOTH";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Long:
        return "LONG";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Short:
        return "SHORT";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Short;
    }
    return PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum value) {
    if (value == PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Limit:
        return "LIMIT";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Market:
        return "MARKET";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Stop:
        return "STOP";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::StopMarket:
        return "STOP_MARKET";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::TakeProfitMarket:
        return "TAKE_PROFIT_MARKET";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::TrailingStopMarket:
        return "TRAILING_STOP_MARKET";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Limit;
    }
    if (s == "MARKET") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Market;
    }
    if (s == "STOP") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Stop;
    }
    if (s == "STOP_MARKET") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::StopMarket;
    }
    if (s == "TAKE_PROFIT") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_MARKET") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::TakeProfitMarket;
    }
    if (s == "TRAILING_STOP_MARKET") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::TrailingStopMarket;
    }
    return PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum value) {
    if (value == PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Gtc:
        return "GTC";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Ioc:
        return "IOC";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Fok:
        return "FOK";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Gtx:
        return "GTX";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Gtd:
        return "GTD";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Rpi:
        return "RPI";
    case PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Gtx;
    }
    if (s == "GTD") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Gtd;
    }
    if (s == "RPI") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Rpi;
    }
    return PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum value) {
    if (value == PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum::True_:
        return "true";
    case PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum::False_:
        return "false";
    case PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum::True_;
    }
    if (s == "false") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum::False_;
    }
    return PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum value) {
    if (value == PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum::Ack:
        return "ACK";
    case PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum::Result:
        return "RESULT";
    case PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<
               PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum::Result;
    }
    return PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum value) {
    if (value == PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEn"
                                    "um::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent:
        return "OPPONENT";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue:
        return "QUEUE";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue20;
    }
    return PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value) {
    if (value == PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::None_:
        return "NONE";
    case PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<
               PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_BOTH") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "EXPIRE_MAKER") {
        return PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::ExpireMaker;
    }
    return PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum value) {
    if (value == PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument("PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventio"
                                    "nModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

PlaceMultipleOrdersBatchOrdersParameterInner
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "PlaceMultipleOrdersBatchOrdersParameterInner");
    PlaceMultipleOrdersBatchOrdersParameterInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "reduceOnly", out.reduce_only);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "newClientOrderId", out.new_client_order_id);
    common::detail::json::read(obj, "newOrderRespType", out.new_order_resp_type);
    common::detail::json::read(obj, "priceMatch", out.price_match);
    common::detail::json::read(obj, "selfTradePreventionMode", out.self_trade_prevention_mode);
    common::detail::json::read(obj, "goodTillDate", out.good_till_date);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PlaceMultipleOrdersBatchOrdersParameterInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "reduceOnly", v.reduce_only);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "newClientOrderId", v.new_client_order_id);
    common::detail::json::write(obj, "newOrderRespType", v.new_order_resp_type);
    common::detail::json::write(obj, "priceMatch", v.price_match);
    common::detail::json::write(obj, "selfTradePreventionMode", v.self_trade_prevention_mode);
    common::detail::json::write(obj, "goodTillDate", v.good_till_date);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
