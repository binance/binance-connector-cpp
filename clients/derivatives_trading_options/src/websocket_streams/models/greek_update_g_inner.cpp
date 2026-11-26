//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/greek_update_g_inner.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

GreekUpdateGInner tag_invoke(boost::json::value_to_tag<GreekUpdateGInner> /*tag*/,
                             const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GreekUpdateGInner");
    GreekUpdateGInner out;
    common::detail::json::read(obj, "u", out.u);
    common::detail::json::read(obj, "d", out.d);
    common::detail::json::read(obj, "g", out.g);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "v", out.v);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GreekUpdateGInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "u", v.u);
    common::detail::json::write(obj, "d", v.d);
    common::detail::json::write(obj, "g", v.g);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "v", v.v);
}

} // namespace binance::derivatives_trading_options::websocket_streams
