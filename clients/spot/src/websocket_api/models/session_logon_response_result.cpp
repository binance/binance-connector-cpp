//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/session_logon_response_result.hpp>

namespace binance::spot::websocket_api {

SessionLogonResponseResult tag_invoke(boost::json::value_to_tag<SessionLogonResponseResult> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SessionLogonResponseResult");
    SessionLogonResponseResult out;
    common::detail::json::read(obj, "apiKey", out.api_key);
    common::detail::json::read(obj, "authorizedSince", out.authorized_since);
    common::detail::json::read(obj, "connectedSince", out.connected_since);
    common::detail::json::read(obj, "returnRateLimits", out.return_rate_limits);
    common::detail::json::read(obj, "serverTime", out.server_time);
    common::detail::json::read(obj, "userDataStream", out.user_data_stream);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SessionLogonResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "apiKey", v.api_key);
    common::detail::json::write(obj, "authorizedSince", v.authorized_since);
    common::detail::json::write(obj, "connectedSince", v.connected_since);
    common::detail::json::write(obj, "returnRateLimits", v.return_rate_limits);
    common::detail::json::write(obj, "serverTime", v.server_time);
    common::detail::json::write(obj, "userDataStream", v.user_data_stream);
}

} // namespace binance::spot::websocket_api
