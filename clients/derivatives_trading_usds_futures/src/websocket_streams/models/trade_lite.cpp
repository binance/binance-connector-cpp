//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/trade_lite.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

TradeLite tag_invoke(boost::json::value_to_tag<TradeLite> /*tag*/, const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradeLite");
    TradeLite out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "m", out.m);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "S", out.s_uppercase);
    common::detail::json::read(obj, "L", out.l_uppercase);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "i", out.i);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const TradeLite& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "m", v.m);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "S", v.s_uppercase);
    common::detail::json::write(obj, "L", v.l_uppercase);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "i", v.i);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
