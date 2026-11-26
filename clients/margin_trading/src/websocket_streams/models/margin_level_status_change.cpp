//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/websocket_streams/models/margin_level_status_change.hpp>

namespace binance::margin_trading::websocket_streams {

MarginLevelStatusChange tag_invoke(boost::json::value_to_tag<MarginLevelStatusChange> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MarginLevelStatusChange");
    MarginLevelStatusChange out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "s", out.s);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MarginLevelStatusChange& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "s", v.s);
}

} // namespace binance::margin_trading::websocket_streams
