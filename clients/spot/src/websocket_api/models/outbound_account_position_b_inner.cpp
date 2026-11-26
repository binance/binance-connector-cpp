//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/outbound_account_position_b_inner.hpp>

namespace binance::spot::websocket_api {

OutboundAccountPositionBInner
tag_invoke(boost::json::value_to_tag<OutboundAccountPositionBInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OutboundAccountPositionBInner");
    OutboundAccountPositionBInner out;
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "f", out.f);
    common::detail::json::read(obj, "l", out.l);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OutboundAccountPositionBInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "f", v.f);
    common::detail::json::write(obj, "l", v.l);
}

} // namespace binance::spot::websocket_api
