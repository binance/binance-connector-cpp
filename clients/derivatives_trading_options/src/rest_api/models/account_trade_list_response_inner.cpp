//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_trade_list_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

AccountTradeListResponseInner
tag_invoke(boost::json::value_to_tag<AccountTradeListResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountTradeListResponseInner");
    AccountTradeListResponseInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "tradeId", out.trade_id);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "realizedProfit", out.realized_profit);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "liquidity", out.liquidity);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "priceScale", out.price_scale);
    common::detail::json::read(obj, "quantityScale", out.quantity_scale);
    common::detail::json::read(obj, "optionSide", out.option_side);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountTradeListResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "tradeId", v.trade_id);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "realizedProfit", v.realized_profit);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "liquidity", v.liquidity);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "priceScale", v.price_scale);
    common::detail::json::write(obj, "quantityScale", v.quantity_scale);
    common::detail::json::write(obj, "optionSide", v.option_side);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
}

} // namespace binance::derivatives_trading_options::rest_api
