//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/session_logon_response_result.hpp>
#include <binance/spot/websocket_api/models/session_logout_response_result.hpp>
#include <binance/spot/websocket_api/models/session_status_response_result.hpp>

namespace binance::spot::websocket_api {

struct SessionLogonParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// The value cannot be greater than `60000`. Supports up to three decimal places of precision
    /// (e.g., 6000.346) so that microseconds may be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct SessionLogoutParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
};

struct SessionStatusParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
};

class BINANCE_SPOT_EXPORT AuthApi {
public:
    explicit AuthApi(std::shared_ptr<common::WebsocketApi> client);

    /// Log in with API key (USER_DATA)
    ///
    /// `session.logon`.
    ///
    /// Authenticate WebSocket connection using the provided API key.
    ///
    /// After calling `session.logon`, you can omit `apiKey` and `signature` parameters for future
    /// requests that require them.
    ///
    /// Note that only one API key can be authenticated.
    ///
    /// Calling `session.logon` multiple times changes the current authenticated API key.
    ///
    /// **Note:** Only Ed25519 keys are supported for this feature.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/auth#session-logon
    [[nodiscard]] std::vector<common::WebsocketApiResponse<SessionLogonResponseResult>>
    session_logon(const SessionLogonParams& params = {}) const;

    /// Asynchronous `session_logon()`. Completes with
    /// `void(std::exception_ptr,
    /// std::vector<common::WebsocketApiResponse<SessionLogonResponseResult>>)`.
    template <class CompletionToken>
    auto async_session_logon(const SessionLogonParams& params, CompletionToken&& token) const {
        return common::async_send_all<SessionLogonResponseResult>(
            client_, "session.logon", session_logon_payload(params),
            make_options(false, true, true, false), std::forward<CompletionToken>(token));
    }

    /// Log out of the session
    ///
    /// `session.logout`.
    ///
    /// Forget the API key previously authenticated. If the connection is not authenticated, this
    /// request does nothing.
    ///
    /// Note that the WebSocket connection stays open after `session.logout` request. You can
    /// continue using the connection, but now you will have to explicitly provide the `apiKey` and
    /// `signature` parameters where needed.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/auth#session-logout
    [[nodiscard]] std::vector<common::WebsocketApiResponse<SessionLogoutResponseResult>>
    session_logout(const SessionLogoutParams& params = {}) const;

    /// Asynchronous `session_logout()`. Completes with
    /// `void(std::exception_ptr,
    /// std::vector<common::WebsocketApiResponse<SessionLogoutResponseResult>>)`.
    template <class CompletionToken>
    auto async_session_logout(const SessionLogoutParams& params, CompletionToken&& token) const {
        return common::async_send_all<SessionLogoutResponseResult>(
            client_, "session.logout", session_logout_payload(params),
            make_options(false, false, false, true), std::forward<CompletionToken>(token));
    }

    /// Query session status
    ///
    /// `session.status`.
    ///
    /// Query the status of the WebSocket connection,
    /// inspecting which API key (if any) is used to authorize requests.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/auth#session-status
    [[nodiscard]] common::WebsocketApiResponse<SessionStatusResponseResult>
    session_status(const SessionStatusParams& params = {}) const;

    /// Asynchronous `session_status()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<SessionStatusResponseResult>)`.
    template <class CompletionToken>
    auto async_session_status(const SessionStatusParams& params, CompletionToken&& token) const {
        return common::async_send<SessionStatusResponseResult>(
            client_, "session.status", session_status_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params session_logon_payload(const SessionLogonParams& params);
    [[nodiscard]] static common::Params session_logout_payload(const SessionLogoutParams& params);
    [[nodiscard]] static common::Params session_status_payload(const SessionStatusParams& params);
    [[nodiscard]] static common::WebsocketMessageSendOptions
    make_options(bool with_api_key, bool is_signed, bool is_session_logon, bool is_session_logout) {
        common::WebsocketMessageSendOptions options;
        options.with_api_key = with_api_key;
        options.is_signed = is_signed;
        options.is_session_logon = is_session_logon;
        options.is_session_logout = is_session_logout;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
};

} // namespace binance::spot::websocket_api
