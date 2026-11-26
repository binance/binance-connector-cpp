//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/aggregate_trade_streams_response.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

AggregateTradeStreamsResponse
tag_invoke(boost::json::value_to_tag<AggregateTradeStreamsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AggregateTradeStreamsResponse");
    AggregateTradeStreamsResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "f", out.f);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "m", out.m);
    common::detail::json::read(obj, "st", out.st);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AggregateTradeStreamsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "f", v.f);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "m", v.m);
    common::detail::json::write(obj, "st", v.st);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
