//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/margin_call.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

MarginCall tag_invoke(boost::json::value_to_tag<MarginCall> /*tag*/, const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MarginCall");
    MarginCall out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "cw", out.cw);
    common::detail::json::read(obj, "p", out.p);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const MarginCall& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "cw", v.cw);
    common::detail::json::write(obj, "p", v.p);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
