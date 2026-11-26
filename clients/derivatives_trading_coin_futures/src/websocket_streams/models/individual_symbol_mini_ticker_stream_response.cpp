//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/individual_symbol_mini_ticker_stream_response.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

IndividualSymbolMiniTickerStreamResponse
tag_invoke(boost::json::value_to_tag<IndividualSymbolMiniTickerStreamResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "IndividualSymbolMiniTickerStreamResponse");
    IndividualSymbolMiniTickerStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "ps", out.ps);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "h", out.h);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "v", out.v);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "st", out.st);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const IndividualSymbolMiniTickerStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "ps", v.ps);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "h", v.h);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "v", v.v);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "st", v.st);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
