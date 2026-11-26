//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_order_detail_response.hpp>

namespace binance::stock_options::rest_api {

OptionOrderDetailResponse tag_invoke(boost::json::value_to_tag<OptionOrderDetailResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionOrderDetailResponse");
    OptionOrderDetailResponse out;
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
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "commission", out.commission);
    common::detail::json::read(obj, "platformFee", out.platform_fee);
    common::detail::json::read(obj, "sec", out.sec);
    common::detail::json::read(obj, "taf", out.taf);
    common::detail::json::read(obj, "cat", out.cat);
    common::detail::json::read(obj, "orf", out.orf);
    common::detail::json::read(obj, "occ", out.occ);
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "filledAt", out.filled_at);
    common::detail::json::read(obj, "canceledAt", out.canceled_at);
    common::detail::json::read(obj, "expiredAt", out.expired_at);
    common::detail::json::read(obj, "settlementDate", out.settlement_date);
    common::detail::json::read(obj, "trades", out.trades);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionOrderDetailResponse& v) {
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
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "commission", v.commission);
    common::detail::json::write(obj, "platformFee", v.platform_fee);
    common::detail::json::write(obj, "sec", v.sec);
    common::detail::json::write(obj, "taf", v.taf);
    common::detail::json::write(obj, "cat", v.cat);
    common::detail::json::write(obj, "orf", v.orf);
    common::detail::json::write(obj, "occ", v.occ);
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "filledAt", v.filled_at);
    common::detail::json::write(obj, "canceledAt", v.canceled_at);
    common::detail::json::write(obj, "expiredAt", v.expired_at);
    common::detail::json::write(obj, "settlementDate", v.settlement_date);
    common::detail::json::write(obj, "trades", v.trades);
}

} // namespace binance::stock_options::rest_api
