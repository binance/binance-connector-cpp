//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/algo_update_o.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

AlgoUpdateO tag_invoke(boost::json::value_to_tag<AlgoUpdateO> /*tag*/,
                       const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AlgoUpdateO");
    AlgoUpdateO out;
    common::detail::json::read(obj, "caid", out.caid);
    common::detail::json::read(obj, "aid", out.aid);
    common::detail::json::read(obj, "at", out.at);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "S", out.s_uppercase);
    common::detail::json::read(obj, "ps", out.ps);
    common::detail::json::read(obj, "f", out.f);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "X", out.x_uppercase);
    common::detail::json::read(obj, "ai", out.ai);
    common::detail::json::read(obj, "ap", out.ap);
    common::detail::json::read(obj, "aq", out.aq);
    common::detail::json::read(obj, "act", out.act);
    common::detail::json::read(obj, "tp", out.tp);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "V", out.v_uppercase);
    common::detail::json::read(obj, "wt", out.wt);
    common::detail::json::read(obj, "pm", out.pm);
    common::detail::json::read(obj, "cp", out.cp);
    common::detail::json::read(obj, "pP", out.p_p);
    common::detail::json::read(obj, "R", out.r_uppercase);
    common::detail::json::read(obj, "tt", out.tt);
    common::detail::json::read(obj, "gtd", out.gtd);
    common::detail::json::read(obj, "rm", out.rm);
    common::detail::json::read(obj, "ia", out.ia);
    common::detail::json::read(obj, "spt", out.spt);
    common::detail::json::read(obj, "spv", out.spv);
    common::detail::json::read(obj, "splv", out.splv);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const AlgoUpdateO& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "caid", v.caid);
    common::detail::json::write(obj, "aid", v.aid);
    common::detail::json::write(obj, "at", v.at);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "S", v.s_uppercase);
    common::detail::json::write(obj, "ps", v.ps);
    common::detail::json::write(obj, "f", v.f);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "X", v.x_uppercase);
    common::detail::json::write(obj, "ai", v.ai);
    common::detail::json::write(obj, "ap", v.ap);
    common::detail::json::write(obj, "aq", v.aq);
    common::detail::json::write(obj, "act", v.act);
    common::detail::json::write(obj, "tp", v.tp);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "V", v.v_uppercase);
    common::detail::json::write(obj, "wt", v.wt);
    common::detail::json::write(obj, "pm", v.pm);
    common::detail::json::write(obj, "cp", v.cp);
    common::detail::json::write(obj, "pP", v.p_p);
    common::detail::json::write(obj, "R", v.r_uppercase);
    common::detail::json::write(obj, "tt", v.tt);
    common::detail::json::write(obj, "gtd", v.gtd);
    common::detail::json::write(obj, "rm", v.rm);
    common::detail::json::write(obj, "ia", v.ia);
    common::detail::json::write(obj, "spt", v.spt);
    common::detail::json::write(obj, "spv", v.spv);
    common::detail::json::write(obj, "splv", v.splv);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
