//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_position_information_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

OptionPositionInformationResponseInner
tag_invoke(boost::json::value_to_tag<OptionPositionInformationResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionPositionInformationResponseInner");
    OptionPositionInformationResponseInner out;
    common::detail::json::read(obj, "entryPrice", out.entry_price);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "markValue", out.mark_value);
    common::detail::json::read(obj, "unrealizedPNL", out.unrealized_pnl);
    common::detail::json::read(obj, "markPrice", out.mark_price);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "expiryDate", out.expiry_date);
    common::detail::json::read(obj, "priceScale", out.price_scale);
    common::detail::json::read(obj, "quantityScale", out.quantity_scale);
    common::detail::json::read(obj, "optionSide", out.option_side);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "bidQuantity", out.bid_quantity);
    common::detail::json::read(obj, "askQuantity", out.ask_quantity);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionPositionInformationResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "entryPrice", v.entry_price);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "markValue", v.mark_value);
    common::detail::json::write(obj, "unrealizedPNL", v.unrealized_pnl);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "expiryDate", v.expiry_date);
    common::detail::json::write(obj, "priceScale", v.price_scale);
    common::detail::json::write(obj, "quantityScale", v.quantity_scale);
    common::detail::json::write(obj, "optionSide", v.option_side);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "bidQuantity", v.bid_quantity);
    common::detail::json::write(obj, "askQuantity", v.ask_quantity);
}

} // namespace binance::derivatives_trading_options::rest_api
