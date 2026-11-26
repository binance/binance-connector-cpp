//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/auth_api.hpp>

namespace binance::spot::websocket_api {

AuthApi::AuthApi(std::shared_ptr<common::WebsocketApi> client) : client_(std::move(client)) {}

common::Params AuthApi::session_logon_payload(const SessionLogonParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

std::vector<common::WebsocketApiResponse<SessionLogonResponseResult>>
AuthApi::session_logon(const SessionLogonParams& params) const {
    return common::send_all<SessionLogonResponseResult>(*client_, "session.logon",
                                                        session_logon_payload(params),
                                                        make_options(false, true, true, false));
}

common::Params AuthApi::session_logout_payload(const SessionLogoutParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return p;
}

std::vector<common::WebsocketApiResponse<SessionLogoutResponseResult>>
AuthApi::session_logout(const SessionLogoutParams& params) const {
    return common::send_all<SessionLogoutResponseResult>(*client_, "session.logout",
                                                         session_logout_payload(params),
                                                         make_options(false, false, false, true));
}

common::Params AuthApi::session_status_payload(const SessionStatusParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return p;
}

common::WebsocketApiResponse<SessionStatusResponseResult>
AuthApi::session_status(const SessionStatusParams& params) const {
    return common::send<SessionStatusResponseResult>(*client_, "session.status",
                                                     session_status_payload(params),
                                                     make_options(false, false, false, false));
}

} // namespace binance::spot::websocket_api
