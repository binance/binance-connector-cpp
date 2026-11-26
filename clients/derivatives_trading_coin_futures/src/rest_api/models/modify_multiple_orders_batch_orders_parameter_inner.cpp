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
#include <binance/derivatives_trading_coin_futures/rest_api/models/modify_multiple_orders_batch_orders_parameter_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

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
    common::detail::json::write(obj, "modifyId", v.modify_id);
    common::detail::json::write(obj, "recvWindow", v.recv_window);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
