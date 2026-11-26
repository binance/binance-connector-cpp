//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/accept_block_trade_order_response_legs_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

AcceptBlockTradeOrderResponseLegsInner
tag_invoke(boost::json::value_to_tag<AcceptBlockTradeOrderResponseLegsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AcceptBlockTradeOrderResponseLegsInner");
    AcceptBlockTradeOrderResponseLegsInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "price", out.price);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AcceptBlockTradeOrderResponseLegsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "price", v.price);
}

} // namespace binance::derivatives_trading_options::rest_api
