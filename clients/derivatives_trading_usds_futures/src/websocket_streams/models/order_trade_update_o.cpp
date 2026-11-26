//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/order_trade_update_o.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

OrderTradeUpdateO tag_invoke(boost::json::value_to_tag<OrderTradeUpdateO> /*tag*/,
                             const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OrderTradeUpdateO");
    OrderTradeUpdateO out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "S", out.s_uppercase);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "f", out.f);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "ap", out.ap);
    common::detail::json::read(obj, "sp", out.sp);
    common::detail::json::read(obj, "x", out.x);
    common::detail::json::read(obj, "X", out.x_uppercase);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "M", out.m_uppercase);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "z", out.z);
    common::detail::json::read(obj, "L", out.l_uppercase);
    common::detail::json::read(obj, "N", out.n_uppercase);
    common::detail::json::read(obj, "n", out.n);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "b", out.b);
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "m", out.m);
    common::detail::json::read(obj, "R", out.r_uppercase);
    common::detail::json::read(obj, "wt", out.wt);
    common::detail::json::read(obj, "ot", out.ot);
    common::detail::json::read(obj, "ps", out.ps);
    common::detail::json::read(obj, "cp", out.cp);
    common::detail::json::read(obj, "AP", out.ap_uppercase);
    common::detail::json::read(obj, "cr", out.cr);
    common::detail::json::read(obj, "pP", out.p_p);
    common::detail::json::read(obj, "si", out.si);
    common::detail::json::read(obj, "ss", out.ss);
    common::detail::json::read(obj, "rp", out.rp);
    common::detail::json::read(obj, "V", out.v_uppercase);
    common::detail::json::read(obj, "pm", out.pm);
    common::detail::json::read(obj, "gtd", out.gtd);
    common::detail::json::read(obj, "er", out.er);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderTradeUpdateO& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "S", v.s_uppercase);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "f", v.f);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "ap", v.ap);
    common::detail::json::write(obj, "sp", v.sp);
    common::detail::json::write(obj, "x", v.x);
    common::detail::json::write(obj, "X", v.x_uppercase);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "M", v.m_uppercase);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "z", v.z);
    common::detail::json::write(obj, "L", v.l_uppercase);
    common::detail::json::write(obj, "N", v.n_uppercase);
    common::detail::json::write(obj, "n", v.n);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "b", v.b);
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "m", v.m);
    common::detail::json::write(obj, "R", v.r_uppercase);
    common::detail::json::write(obj, "wt", v.wt);
    common::detail::json::write(obj, "ot", v.ot);
    common::detail::json::write(obj, "ps", v.ps);
    common::detail::json::write(obj, "cp", v.cp);
    common::detail::json::write(obj, "AP", v.ap_uppercase);
    common::detail::json::write(obj, "cr", v.cr);
    common::detail::json::write(obj, "pP", v.p_p);
    common::detail::json::write(obj, "si", v.si);
    common::detail::json::write(obj, "ss", v.ss);
    common::detail::json::write(obj, "rp", v.rp);
    common::detail::json::write(obj, "V", v.v_uppercase);
    common::detail::json::write(obj, "pm", v.pm);
    common::detail::json::write(obj, "gtd", v.gtd);
    common::detail::json::write(obj, "er", v.er);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
