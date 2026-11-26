//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/conditional_order_trade_update.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

ConditionalOrderTradeUpdate
tag_invoke(boost::json::value_to_tag<ConditionalOrderTradeUpdate> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ConditionalOrderTradeUpdate");
    ConditionalOrderTradeUpdate out;
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "fs", out.fs);
    common::detail::json::read(obj, "so", out.so);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ConditionalOrderTradeUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "fs", v.fs);
    common::detail::json::write(obj, "so", v.so);
}

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
