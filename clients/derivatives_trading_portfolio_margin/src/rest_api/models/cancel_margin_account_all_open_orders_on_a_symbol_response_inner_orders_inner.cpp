//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_margin_account_all_open_orders_on_a_symbol_response_inner_orders_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner
tag_invoke(boost::json::value_to_tag<
               CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner");
    CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
