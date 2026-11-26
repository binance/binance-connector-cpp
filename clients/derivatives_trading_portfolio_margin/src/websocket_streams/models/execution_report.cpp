//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/execution_report.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

ExecutionReport tag_invoke(boost::json::value_to_tag<ExecutionReport> /*tag*/,
                           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExecutionReport");
    ExecutionReport out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "S", out.s_uppercase);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "f", out.f);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "P", out.p_uppercase);
    common::detail::json::read(obj, "d", out.d);
    common::detail::json::read(obj, "F", out.f_uppercase);
    common::detail::json::read(obj, "g", out.g);
    common::detail::json::read(obj, "C", out.c_uppercase);
    common::detail::json::read(obj, "x", out.x);
    common::detail::json::read(obj, "X", out.x_uppercase);
    common::detail::json::read(obj, "r", out.r);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "z", out.z);
    common::detail::json::read(obj, "L", out.l_uppercase);
    common::detail::json::read(obj, "n", out.n);
    common::detail::json::read(obj, "N", out.n_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "v", out.v);
    common::detail::json::read(obj, "I", out.i_uppercase);
    common::detail::json::read(obj, "w", out.w);
    common::detail::json::read(obj, "m", out.m);
    common::detail::json::read(obj, "O", out.o_uppercase);
    common::detail::json::read(obj, "Z", out.z_uppercase);
    common::detail::json::read(obj, "Y", out.y_uppercase);
    common::detail::json::read(obj, "Q", out.q_uppercase);
    common::detail::json::read(obj, "D", out.d_uppercase);
    common::detail::json::read(obj, "j", out.j);
    common::detail::json::read(obj, "J", out.j_uppercase);
    common::detail::json::read(obj, "W", out.w_uppercase);
    common::detail::json::read(obj, "V", out.v_uppercase);
    common::detail::json::read(obj, "u", out.u);
    common::detail::json::read(obj, "U", out.u_uppercase);
    common::detail::json::read(obj, "A", out.a_uppercase);
    common::detail::json::read(obj, "B", out.b_uppercase);
    common::detail::json::read(obj, "Cs", out.cs);
    common::detail::json::read(obj, "pl", out.pl);
    common::detail::json::read(obj, "pL", out.p_l);
    common::detail::json::read(obj, "pY", out.p_y);
    common::detail::json::read(obj, "eR", out.e_r);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExecutionReport& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "S", v.s_uppercase);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "f", v.f);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "P", v.p_uppercase);
    common::detail::json::write(obj, "d", v.d);
    common::detail::json::write(obj, "F", v.f_uppercase);
    common::detail::json::write(obj, "g", v.g);
    common::detail::json::write(obj, "C", v.c_uppercase);
    common::detail::json::write(obj, "x", v.x);
    common::detail::json::write(obj, "X", v.x_uppercase);
    common::detail::json::write(obj, "r", v.r);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "z", v.z);
    common::detail::json::write(obj, "L", v.l_uppercase);
    common::detail::json::write(obj, "n", v.n);
    common::detail::json::write(obj, "N", v.n_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "v", v.v);
    common::detail::json::write(obj, "I", v.i_uppercase);
    common::detail::json::write(obj, "w", v.w);
    common::detail::json::write(obj, "m", v.m);
    common::detail::json::write(obj, "O", v.o_uppercase);
    common::detail::json::write(obj, "Z", v.z_uppercase);
    common::detail::json::write(obj, "Y", v.y_uppercase);
    common::detail::json::write(obj, "Q", v.q_uppercase);
    common::detail::json::write(obj, "D", v.d_uppercase);
    common::detail::json::write(obj, "j", v.j);
    common::detail::json::write(obj, "J", v.j_uppercase);
    common::detail::json::write(obj, "W", v.w_uppercase);
    common::detail::json::write(obj, "V", v.v_uppercase);
    common::detail::json::write(obj, "u", v.u);
    common::detail::json::write(obj, "U", v.u_uppercase);
    common::detail::json::write(obj, "A", v.a_uppercase);
    common::detail::json::write(obj, "B", v.b_uppercase);
    common::detail::json::write(obj, "Cs", v.cs);
    common::detail::json::write(obj, "pl", v.pl);
    common::detail::json::write(obj, "pL", v.p_l);
    common::detail::json::write(obj, "pY", v.p_y);
    common::detail::json::write(obj, "eR", v.e_r);
}

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
