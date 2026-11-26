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
#include <binance/derivatives_trading_options/rest_api/models/place_multiple_orders_orders_parameter_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

std::string_view to_string(PlaceMultipleOrdersOrdersParameterInnerSideEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersOrdersParameterInnerSideEnum::Buy:
        return "BUY";
    case PlaceMultipleOrdersOrdersParameterInnerSideEnum::Sell:
        return "SELL";
    case PlaceMultipleOrdersOrdersParameterInnerSideEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersOrdersParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return PlaceMultipleOrdersOrdersParameterInnerSideEnum::Buy;
    }
    if (s == "SELL") {
        return PlaceMultipleOrdersOrdersParameterInnerSideEnum::Sell;
    }
    return PlaceMultipleOrdersOrdersParameterInnerSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersOrdersParameterInnerSideEnum value) {
    if (value == PlaceMultipleOrdersOrdersParameterInnerSideEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersOrdersParameterInnerSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceMultipleOrdersOrdersParameterInnerTypeEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersOrdersParameterInnerTypeEnum::Limit:
        return "LIMIT";
    case PlaceMultipleOrdersOrdersParameterInnerTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersOrdersParameterInnerTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInnerTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return PlaceMultipleOrdersOrdersParameterInnerTypeEnum::Limit;
    }
    return PlaceMultipleOrdersOrdersParameterInnerTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersOrdersParameterInnerTypeEnum value) {
    if (value == PlaceMultipleOrdersOrdersParameterInnerTypeEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersOrdersParameterInnerTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Gtc:
        return "GTC";
    case PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Ioc:
        return "IOC";
    case PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Fok:
        return "FOK";
    case PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Gtx:
        return "GTX";
    case PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Gtx;
    }
    return PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum value) {
    if (value == PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum::Ack:
        return "ACK";
    case PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum::Result:
        return "RESULT";
    case PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum::Result;
    }
    return PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum value) {
    if (value == PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<
               PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "EXPIRE_TAKER") {
        return PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum::ExpireBoth;
    }
    return PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum value) {
    if (value == PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument("PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionMode"
                                    "Enum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

PlaceMultipleOrdersOrdersParameterInner
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "PlaceMultipleOrdersOrdersParameterInner");
    PlaceMultipleOrdersOrdersParameterInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "reduceOnly", out.reduce_only);
    common::detail::json::read(obj, "postOnly", out.post_only);
    common::detail::json::read(obj, "newOrderRespType", out.new_order_resp_type);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    common::detail::json::read(obj, "isMmp", out.is_mmp);
    common::detail::json::read(obj, "selfTradePreventionMode", out.self_trade_prevention_mode);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PlaceMultipleOrdersOrdersParameterInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "reduceOnly", v.reduce_only);
    common::detail::json::write(obj, "postOnly", v.post_only);
    common::detail::json::write(obj, "newOrderRespType", v.new_order_resp_type);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
    common::detail::json::write(obj, "isMmp", v.is_mmp);
    common::detail::json::write(obj, "selfTradePreventionMode", v.self_trade_prevention_mode);
}

} // namespace binance::derivatives_trading_options::rest_api
