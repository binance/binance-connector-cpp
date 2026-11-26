//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/margin_call_p_inner.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

MarginCallPInner tag_invoke(boost::json::value_to_tag<MarginCallPInner> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MarginCallPInner");
    MarginCallPInner out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "ps", out.ps);
    common::detail::json::read(obj, "pa", out.pa);
    common::detail::json::read(obj, "mt", out.mt);
    common::detail::json::read(obj, "iw", out.iw);
    common::detail::json::read(obj, "mp", out.mp);
    common::detail::json::read(obj, "up", out.up);
    common::detail::json::read(obj, "mm", out.mm);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MarginCallPInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "ps", v.ps);
    common::detail::json::write(obj, "pa", v.pa);
    common::detail::json::write(obj, "mt", v.mt);
    common::detail::json::write(obj, "iw", v.iw);
    common::detail::json::write(obj, "mp", v.mp);
    common::detail::json::write(obj, "up", v.up);
    common::detail::json::write(obj, "mm", v.mm);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
