//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/trading_session_stream_response.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

TradingSessionStreamResponse
tag_invoke(boost::json::value_to_tag<TradingSessionStreamResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradingSessionStreamResponse");
    TradingSessionStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "S", out.s_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradingSessionStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "S", v.s_uppercase);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
