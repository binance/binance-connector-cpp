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
#include <binance/derivatives_trading_usds_futures/rest_api/models/modify_multiple_orders_batch_orders_parameter_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

std::string_view to_string(ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum value) noexcept {
    switch (value) {
    case ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum::Buy:
        return "BUY";
    case ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum::Sell:
        return "SELL";
    case ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum::Unknown:
        break;
    }
    return "";
}

ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum::Buy;
    }
    if (s == "SELL") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum::Sell;
    }
    return ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum value) {
    if (value == ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum::Unknown) {
        throw std::invalid_argument(
            "ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view
to_string(ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value) noexcept {
    switch (value) {
    case ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent:
        return "OPPONENT";
    case ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue:
        return "QUEUE";
    case ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Queue20;
    }
    return ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value) {
    if (value == ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Unknown) {
        throw std::invalid_argument(
            "ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

ModifyMultipleOrdersBatchOrdersParameterInner
tag_invoke(boost::json::value_to_tag<ModifyMultipleOrdersBatchOrdersParameterInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ModifyMultipleOrdersBatchOrdersParameterInner");
    ModifyMultipleOrdersBatchOrdersParameterInner out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "origClientOrderId", out.orig_client_order_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "priceMatch", out.price_match);
    common::detail::json::read(obj, "stopPrice", out.stop_price);
    common::detail::json::read(obj, "modifyId", out.modify_id);
    common::detail::json::read(obj, "recvWindow", out.recv_window);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ModifyMultipleOrdersBatchOrdersParameterInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "origClientOrderId", v.orig_client_order_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "priceMatch", v.price_match);
    common::detail::json::write(obj, "stopPrice", v.stop_price);
    common::detail::json::write(obj, "modifyId", v.modify_id);
    common::detail::json::write(obj, "recvWindow", v.recv_window);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
