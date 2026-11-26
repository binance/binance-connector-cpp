//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_order_history_response_rows_inner.hpp>

namespace binance::stock_options::rest_api {

OptionOrderHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<OptionOrderHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionOrderHistoryResponseRowsInner");
    OptionOrderHistoryResponseRowsInner out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "underlyingSymbol", out.underlying_symbol);
    common::detail::json::read(obj, "rootSymbol", out.root_symbol);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "expirationDate", out.expiration_date);
    common::detail::json::read(obj, "multiplier", out.multiplier);
    common::detail::json::read(obj, "positionIntent", out.position_intent);
    common::detail::json::read(obj, "autoLiquidation", out.auto_liquidation);
    common::detail::json::read(obj, "quote", out.quote);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "orderType", out.order_type);
    common::detail::json::read(obj, "limitPrice", out.limit_price);
    common::detail::json::read(obj, "avgFilledPrice", out.avg_filled_price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "filledQty", out.filled_qty);
    common::detail::json::read(obj, "filledTotal", out.filled_total);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "createdAt", out.created_at);
    common::detail::json::read(obj, "updatedAt", out.updated_at);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionOrderHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "underlyingSymbol", v.underlying_symbol);
    common::detail::json::write(obj, "rootSymbol", v.root_symbol);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "expirationDate", v.expiration_date);
    common::detail::json::write(obj, "multiplier", v.multiplier);
    common::detail::json::write(obj, "positionIntent", v.position_intent);
    common::detail::json::write(obj, "autoLiquidation", v.auto_liquidation);
    common::detail::json::write(obj, "quote", v.quote);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "orderType", v.order_type);
    common::detail::json::write(obj, "limitPrice", v.limit_price);
    common::detail::json::write(obj, "avgFilledPrice", v.avg_filled_price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "filledQty", v.filled_qty);
    common::detail::json::write(obj, "filledTotal", v.filled_total);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "createdAt", v.created_at);
    common::detail::json::write(obj, "updatedAt", v.updated_at);
}

} // namespace binance::stock_options::rest_api
