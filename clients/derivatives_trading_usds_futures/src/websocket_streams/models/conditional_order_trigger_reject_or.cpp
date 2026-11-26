//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/conditional_order_trigger_reject_or.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

ConditionalOrderTriggerRejectOr
tag_invoke(boost::json::value_to_tag<ConditionalOrderTriggerRejectOr> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ConditionalOrderTriggerRejectOr");
    ConditionalOrderTriggerRejectOr out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "r", out.r);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ConditionalOrderTriggerRejectOr& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "r", v.r);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
