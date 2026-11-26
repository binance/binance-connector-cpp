//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_streams/models/event_stream_terminated.hpp>

namespace binance::spot::websocket_streams {

EventStreamTerminated tag_invoke(boost::json::value_to_tag<EventStreamTerminated> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "EventStreamTerminated");
    EventStreamTerminated out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EventStreamTerminated& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
}

} // namespace binance::spot::websocket_streams
