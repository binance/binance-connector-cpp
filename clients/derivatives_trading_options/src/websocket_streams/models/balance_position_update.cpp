//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/balance_position_update.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

BalancePositionUpdate tag_invoke(boost::json::value_to_tag<BalancePositionUpdate> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BalancePositionUpdate");
    BalancePositionUpdate out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "m", out.m);
    common::detail::json::read(obj, "B", out.b_uppercase);
    common::detail::json::read(obj, "P", out.p_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BalancePositionUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "m", v.m);
    common::detail::json::write(obj, "B", v.b_uppercase);
    common::detail::json::write(obj, "P", v.p_uppercase);
}

} // namespace binance::derivatives_trading_options::websocket_streams
