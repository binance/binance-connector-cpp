//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/kline_candlestick_streams_response.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

KlineCandlestickStreamsResponse
tag_invoke(boost::json::value_to_tag<KlineCandlestickStreamsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "KlineCandlestickStreamsResponse");
    KlineCandlestickStreamsResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "k", out.k);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const KlineCandlestickStreamsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "k", v.k);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
