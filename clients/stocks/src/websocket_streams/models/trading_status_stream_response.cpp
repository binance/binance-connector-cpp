//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/websocket_streams/models/trading_status_stream_response.hpp>

namespace binance::stocks::websocket_streams {

TradingStatusStreamResponse
tag_invoke(boost::json::value_to_tag<TradingStatusStreamResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradingStatusStreamResponse");
    TradingStatusStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "assetCode", out.asset_code);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "msg", out.msg);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "z", out.z);
    common::detail::json::read(obj, "tradability", out.tradability);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradingStatusStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "assetCode", v.asset_code);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "msg", v.msg);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "z", v.z);
    common::detail::json::write(obj, "tradability", v.tradability);
}

} // namespace binance::stocks::websocket_streams
