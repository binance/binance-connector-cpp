//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/all_market_liquidation_order_streams_response_o.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

AllMarketLiquidationOrderStreamsResponseO
tag_invoke(boost::json::value_to_tag<AllMarketLiquidationOrderStreamsResponseO> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AllMarketLiquidationOrderStreamsResponseO");
    AllMarketLiquidationOrderStreamsResponseO out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "S", out.s_uppercase);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "f", out.f);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "ap", out.ap);
    common::detail::json::read(obj, "X", out.x_uppercase);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "z", out.z);
    common::detail::json::read(obj, "T", out.t_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AllMarketLiquidationOrderStreamsResponseO& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "S", v.s_uppercase);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "f", v.f);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "ap", v.ap);
    common::detail::json::write(obj, "X", v.x_uppercase);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "z", v.z);
    common::detail::json::write(obj, "T", v.t_uppercase);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
