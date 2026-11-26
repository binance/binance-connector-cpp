//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/all_market_liquidation_order_streams_response.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

AllMarketLiquidationOrderStreamsResponse
tag_invoke(boost::json::value_to_tag<AllMarketLiquidationOrderStreamsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AllMarketLiquidationOrderStreamsResponse");
    AllMarketLiquidationOrderStreamsResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "ps", out.ps);
    common::detail::json::read(obj, "st", out.st);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AllMarketLiquidationOrderStreamsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "ps", v.ps);
    common::detail::json::write(obj, "st", v.st);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
