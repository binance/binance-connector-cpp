//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_streams/models/trade_response.hpp>

namespace binance::spot::websocket_streams {

TradeResponse tag_invoke(boost::json::value_to_tag<TradeResponse> /*tag*/,
                         const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradeResponse");
    TradeResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "m", out.m);
    common::detail::json::read(obj, "M", out.m_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradeResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "m", v.m);
    common::detail::json::write(obj, "M", v.m_uppercase);
}

} // namespace binance::spot::websocket_streams
