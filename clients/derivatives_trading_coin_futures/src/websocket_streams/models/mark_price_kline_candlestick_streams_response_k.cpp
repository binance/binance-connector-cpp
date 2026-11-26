//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/mark_price_kline_candlestick_streams_response_k.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

MarkPriceKlineCandlestickStreamsResponseK
tag_invoke(boost::json::value_to_tag<MarkPriceKlineCandlestickStreamsResponseK> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "MarkPriceKlineCandlestickStreamsResponseK");
    MarkPriceKlineCandlestickStreamsResponseK out;
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "f", out.f);
    common::detail::json::read(obj, "L", out.l_uppercase);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "h", out.h);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "v", out.v);
    common::detail::json::read(obj, "n", out.n);
    common::detail::json::read(obj, "x", out.x);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "V", out.v_uppercase);
    common::detail::json::read(obj, "Q", out.q_uppercase);
    common::detail::json::read(obj, "B", out.b_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MarkPriceKlineCandlestickStreamsResponseK& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "f", v.f);
    common::detail::json::write(obj, "L", v.l_uppercase);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "h", v.h);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "v", v.v);
    common::detail::json::write(obj, "n", v.n);
    common::detail::json::write(obj, "x", v.x);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "V", v.v_uppercase);
    common::detail::json::write(obj, "Q", v.q_uppercase);
    common::detail::json::write(obj, "B", v.b_uppercase);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
