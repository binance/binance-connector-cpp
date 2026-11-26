//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/outbound_account_position.hpp>

namespace binance::spot::websocket_api {

OutboundAccountPosition tag_invoke(boost::json::value_to_tag<OutboundAccountPosition> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OutboundAccountPosition");
    OutboundAccountPosition out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "u", out.u);
    common::detail::json::read(obj, "B", out.b_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OutboundAccountPosition& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "u", v.u);
    common::detail::json::write(obj, "B", v.b_uppercase);
}

} // namespace binance::spot::websocket_api
