//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/websocket_streams/models/risklevelchange.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams {

Risklevelchange tag_invoke(boost::json::value_to_tag<Risklevelchange> /*tag*/,
                           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "Risklevelchange");
    Risklevelchange out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "u", out.u);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "eq", out.eq);
    common::detail::json::read(obj, "ae", out.ae);
    common::detail::json::read(obj, "m", out.m);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const Risklevelchange& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "u", v.u);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "eq", v.eq);
    common::detail::json::write(obj, "ae", v.ae);
    common::detail::json::write(obj, "m", v.m);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams
