//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/balance_position_update_p_inner.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

BalancePositionUpdatePInner
tag_invoke(boost::json::value_to_tag<BalancePositionUpdatePInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BalancePositionUpdatePInner");
    BalancePositionUpdatePInner out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "a", out.a);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BalancePositionUpdatePInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "a", v.a);
}

} // namespace binance::derivatives_trading_options::websocket_streams
