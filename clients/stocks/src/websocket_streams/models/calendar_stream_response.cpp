//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/websocket_streams/models/calendar_stream_response.hpp>

namespace binance::stocks::websocket_streams {

CalendarStreamResponse tag_invoke(boost::json::value_to_tag<CalendarStreamResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CalendarStreamResponse");
    CalendarStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "from", out.from);
    common::detail::json::read(obj, "to", out.to);
    common::detail::json::read(obj, "ts", out.ts);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CalendarStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "from", v.from);
    common::detail::json::write(obj, "to", v.to);
    common::detail::json::write(obj, "ts", v.ts);
}

} // namespace binance::stocks::websocket_streams
