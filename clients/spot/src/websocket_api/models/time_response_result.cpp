//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/time_response_result.hpp>

namespace binance::spot::websocket_api {

TimeResponseResult tag_invoke(boost::json::value_to_tag<TimeResponseResult> /*tag*/,
                              const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TimeResponseResult");
    TimeResponseResult out;
    common::detail::json::read(obj, "serverTime", out.server_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TimeResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "serverTime", v.server_time);
}

} // namespace binance::spot::websocket_api
