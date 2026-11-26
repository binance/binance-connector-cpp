//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_block_trade_list_response_inner_legs_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

AccountBlockTradeListResponseInnerLegsInner
tag_invoke(boost::json::value_to_tag<AccountBlockTradeListResponseInnerLegsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AccountBlockTradeListResponseInnerLegsInner");
    AccountBlockTradeListResponseInnerLegsInner out;
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "orderPrice", out.order_price);
    common::detail::json::read(obj, "orderQuantity", out.order_quantity);
    common::detail::json::read(obj, "orderStatus", out.order_status);
    common::detail::json::read(obj, "executedQty", out.executed_qty);
    common::detail::json::read(obj, "executedAmount", out.executed_amount);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "orderType", out.order_type);
    common::detail::json::read(obj, "orderSide", out.order_side);
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "tradeId", out.trade_id);
    common::detail::json::read(obj, "tradePrice", out.trade_price);
    common::detail::json::read(obj, "tradeQty", out.trade_qty);
    common::detail::json::read(obj, "tradeTime", out.trade_time);
    common::detail::json::read(obj, "liquidity", out.liquidity);
    common::detail::json::read(obj, "commission", out.commission);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountBlockTradeListResponseInnerLegsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "orderPrice", v.order_price);
    common::detail::json::write(obj, "orderQuantity", v.order_quantity);
    common::detail::json::write(obj, "orderStatus", v.order_status);
    common::detail::json::write(obj, "executedQty", v.executed_qty);
    common::detail::json::write(obj, "executedAmount", v.executed_amount);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "orderType", v.order_type);
    common::detail::json::write(obj, "orderSide", v.order_side);
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "tradeId", v.trade_id);
    common::detail::json::write(obj, "tradePrice", v.trade_price);
    common::detail::json::write(obj, "tradeQty", v.trade_qty);
    common::detail::json::write(obj, "tradeTime", v.trade_time);
    common::detail::json::write(obj, "liquidity", v.liquidity);
    common::detail::json::write(obj, "commission", v.commission);
}

} // namespace binance::derivatives_trading_options::rest_api
