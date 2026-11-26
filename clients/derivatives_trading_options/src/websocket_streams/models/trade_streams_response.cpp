//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/trade_streams_response.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

TradeStreamsResponse tag_invoke(boost::json::value_to_tag<TradeStreamsResponse> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradeStreamsResponse");
    TradeStreamsResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "X", out.x_uppercase);
    common::detail::json::read(obj, "S", out.s_uppercase);
    common::detail::json::read(obj, "m", out.m);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradeStreamsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "X", v.x_uppercase);
    common::detail::json::write(obj, "S", v.s_uppercase);
    common::detail::json::write(obj, "m", v.m);
}

} // namespace binance::derivatives_trading_options::websocket_streams
