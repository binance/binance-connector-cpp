//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/greek_update.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

GreekUpdate tag_invoke(boost::json::value_to_tag<GreekUpdate> /*tag*/,
                       const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GreekUpdate");
    GreekUpdate out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "G", out.g_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const GreekUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "G", v.g_uppercase);
}

} // namespace binance::derivatives_trading_options::websocket_streams
