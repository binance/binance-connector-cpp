//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/grid_update.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

GridUpdate tag_invoke(boost::json::value_to_tag<GridUpdate> /*tag*/, const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GridUpdate");
    GridUpdate out;
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "gu", out.gu);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const GridUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "gu", v.gu);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
