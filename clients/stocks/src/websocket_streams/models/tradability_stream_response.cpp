//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/websocket_streams/models/tradability_stream_response.hpp>

namespace binance::stocks::websocket_streams {

TradabilityStreamResponse tag_invoke(boost::json::value_to_tag<TradabilityStreamResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradabilityStreamResponse");
    TradabilityStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "assetCode", out.asset_code);
    common::detail::json::read(obj, "tradability", out.tradability);
    common::detail::json::read(obj, "t", out.t);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradabilityStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "assetCode", v.asset_code);
    common::detail::json::write(obj, "tradability", v.tradability);
    common::detail::json::write(obj, "t", v.t);
}

} // namespace binance::stocks::websocket_streams
