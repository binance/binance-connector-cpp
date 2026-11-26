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
#include <binance/derivatives_trading_options/rest_api/models/new_block_trade_order_legs_parameter_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

std::string_view to_string(NewBlockTradeOrderLegsParameterInnerSideEnum value) noexcept {
    switch (value) {
    case NewBlockTradeOrderLegsParameterInnerSideEnum::Buy:
        return "BUY";
    case NewBlockTradeOrderLegsParameterInnerSideEnum::Sell:
        return "SELL";
    case NewBlockTradeOrderLegsParameterInnerSideEnum::Unknown:
        break;
    }
    return "";
}

NewBlockTradeOrderLegsParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<NewBlockTradeOrderLegsParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return NewBlockTradeOrderLegsParameterInnerSideEnum::Buy;
    }
    if (s == "SELL") {
        return NewBlockTradeOrderLegsParameterInnerSideEnum::Sell;
    }
    return NewBlockTradeOrderLegsParameterInnerSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewBlockTradeOrderLegsParameterInnerSideEnum value) {
    if (value == NewBlockTradeOrderLegsParameterInnerSideEnum::Unknown) {
        throw std::invalid_argument(
            "NewBlockTradeOrderLegsParameterInnerSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewBlockTradeOrderLegsParameterInnerTypeEnum value) noexcept {
    switch (value) {
    case NewBlockTradeOrderLegsParameterInnerTypeEnum::Limit:
        return "LIMIT";
    case NewBlockTradeOrderLegsParameterInnerTypeEnum::Unknown:
        break;
    }
    return "";
}

NewBlockTradeOrderLegsParameterInnerTypeEnum
tag_invoke(boost::json::value_to_tag<NewBlockTradeOrderLegsParameterInnerTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return NewBlockTradeOrderLegsParameterInnerTypeEnum::Limit;
    }
    return NewBlockTradeOrderLegsParameterInnerTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewBlockTradeOrderLegsParameterInnerTypeEnum value) {
    if (value == NewBlockTradeOrderLegsParameterInnerTypeEnum::Unknown) {
        throw std::invalid_argument(
            "NewBlockTradeOrderLegsParameterInnerTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

NewBlockTradeOrderLegsParameterInner
tag_invoke(boost::json::value_to_tag<NewBlockTradeOrderLegsParameterInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "NewBlockTradeOrderLegsParameterInner");
    NewBlockTradeOrderLegsParameterInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "price", out.price);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const NewBlockTradeOrderLegsParameterInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "price", v.price);
}

} // namespace binance::derivatives_trading_options::rest_api
