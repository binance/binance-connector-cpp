//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/conditional_order_trade_update_so.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

ConditionalOrderTradeUpdateSo
tag_invoke(boost::json::value_to_tag<ConditionalOrderTradeUpdateSo> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ConditionalOrderTradeUpdateSo");
    ConditionalOrderTradeUpdateSo out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "si", out.si);
    common::detail::json::read(obj, "S", out.s_uppercase);
    common::detail::json::read(obj, "st", out.st);
    common::detail::json::read(obj, "f", out.f);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "sp", out.sp);
    common::detail::json::read(obj, "os", out.os);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "ut", out.ut);
    common::detail::json::read(obj, "R", out.r_uppercase);
    common::detail::json::read(obj, "wt", out.wt);
    common::detail::json::read(obj, "ps", out.ps);
    common::detail::json::read(obj, "cp", out.cp);
    common::detail::json::read(obj, "AP", out.ap_uppercase);
    common::detail::json::read(obj, "cr", out.cr);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "V", out.v_uppercase);
    common::detail::json::read(obj, "gtd", out.gtd);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ConditionalOrderTradeUpdateSo& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "si", v.si);
    common::detail::json::write(obj, "S", v.s_uppercase);
    common::detail::json::write(obj, "st", v.st);
    common::detail::json::write(obj, "f", v.f);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "sp", v.sp);
    common::detail::json::write(obj, "os", v.os);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "ut", v.ut);
    common::detail::json::write(obj, "R", v.r_uppercase);
    common::detail::json::write(obj, "wt", v.wt);
    common::detail::json::write(obj, "ps", v.ps);
    common::detail::json::write(obj, "cp", v.cp);
    common::detail::json::write(obj, "AP", v.ap_uppercase);
    common::detail::json::write(obj, "cr", v.cr);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "V", v.v_uppercase);
    common::detail::json::write(obj, "gtd", v.gtd);
}

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
