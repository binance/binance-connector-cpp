//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
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
#include <binance/spot/websocket_api/models/session_subscriptions_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/user_data_stream_events_response.hpp>
#include <binance/spot/websocket_api/models/user_data_stream_subscribe_response_result.hpp>

namespace binance::spot::websocket_api {

struct SessionSubscriptionsParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
};

struct UserDataStreamSubscribeParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Optional filter that controls which events are delivered on this subscription. See User Data
    /// Stream Subscription Filters. When omitted, all events for the subscribed account are
    /// delivered.
    std::optional<boost::json::value> filter = std::nullopt;
};

struct UserDataStreamSubscribeSignatureParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
    /// Optional event filter. See User Data Stream Subscription Filters. When included, `filter`
    /// must be in the signed string with sorted keys and no whitespace between JSON elements.
    std::optional<boost::json::value> filter = std::nullopt;
};

struct UserDataStreamUnsubscribeParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// When called with no parameter, this will close all subscriptions. When called with the
    /// subscriptionId parameter, this will attempt to close the subscription with that subscription
    /// id, if it exists.
    std::optional<std::int64_t> subscription_id = std::nullopt;
};

class BINANCE_SPOT_EXPORT UserDataStreamApi {
public:
    explicit UserDataStreamApi(std::shared_ptr<common::WebsocketApi> client);

    /// Listing all subscriptions
    ///
    /// `session.subscriptions`.
    ///
    /// **Note:**
    ///
    /// * Users should track the corresponding subscription status of related accounts as needed.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/user-data-stream#session-subscriptions
    [[nodiscard]] common::WebsocketApiResponse<std::vector<SessionSubscriptionsResponseResultInner>>
    session_subscriptions(const SessionSubscriptionsParams& params = {}) const;

    /// Asynchronous `session_subscriptions()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<SessionSubscriptionsResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_session_subscriptions(const SessionSubscriptionsParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<SessionSubscriptionsResponseResultInner>>(
            client_, "session.subscriptions", session_subscriptions_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Subscribe to User Data Stream (USER_STREAM)
    ///
    /// `userDataStream.subscribe`.
    ///
    /// Subscribe to the User Data Stream in the current WebSocket connection.
    ///
    /// **Notes:**
    ///   - This method requires an authenticated WebSocket connection using Ed25519 keys. Please
    ///   refer to `session.logon`.
    ///   - To check the subscription status, use `session.status`, see the `userDataStream` flag
    ///   indicating you have an active subscription.
    ///   - User Data Stream events are available in both JSON and SBE sessions.
    ///     - Please refer to User Data Streams for the event format details.
    ///     - For SBE, only SBE schema 2:1 or later is supported.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/user-data-stream#user-data-stream-subscribe
    [[nodiscard]] common::WebsocketApiSubscription<UserDataStreamSubscribeResponseResult,
                                                   UserDataStreamEventsResponse>
    user_data_stream_subscribe(const UserDataStreamSubscribeParams& params = {}) const;

    /// Asynchronous `user_data_stream_subscribe()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiSubscription<UserDataStreamSubscribeResponseResult,
    /// UserDataStreamEventsResponse>)`.
    template <class CompletionToken>
    auto async_user_data_stream_subscribe(const UserDataStreamSubscribeParams& params,
                                          CompletionToken&& token) const {
        return common::async_subscribe<UserDataStreamSubscribeResponseResult,
                                       UserDataStreamEventsResponse>(
            client_, "userDataStream.subscribe", user_data_stream_subscribe_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Subscribe to User Data Stream through signature subscription (USER_STREAM)
    ///
    /// `userDataStream.subscribe.signature`.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: USER_STREAM
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/user-data-stream#user-data-stream-subscribe-signature
    [[nodiscard]] common::WebsocketApiSubscription<UserDataStreamSubscribeResponseResult,
                                                   UserDataStreamEventsResponse>
    user_data_stream_subscribe_signature(
        const UserDataStreamSubscribeSignatureParams& params = {}) const;

    /// Asynchronous `user_data_stream_subscribe_signature()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiSubscription<UserDataStreamSubscribeResponseResult,
    /// UserDataStreamEventsResponse>)`.
    template <class CompletionToken>
    auto
    async_user_data_stream_subscribe_signature(const UserDataStreamSubscribeSignatureParams& params,
                                               CompletionToken&& token) const {
        return common::async_subscribe<UserDataStreamSubscribeResponseResult,
                                       UserDataStreamEventsResponse>(
            client_, "userDataStream.subscribe.signature",
            user_data_stream_subscribe_signature_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Unsubscribe from User Data Stream
    ///
    /// `userDataStream.unsubscribe`.
    ///
    /// Stop listening to the User Data Stream in the current WebSocket
    /// connection.
    ///
    /// Note that `session.logout` will only close the subscription created with
    /// `userDataStream.subscribe` but not subscriptions opened with
    /// `userDataStream.subscribe.signature`.
    ///
    /// Weight(IP): 2
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/user-data-stream#user-data-stream-unsubscribe
    [[nodiscard]] common::WebsocketApiResponse<boost::json::value>
    user_data_stream_unsubscribe(const UserDataStreamUnsubscribeParams& params = {}) const;

    /// Asynchronous `user_data_stream_unsubscribe()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_user_data_stream_unsubscribe(const UserDataStreamUnsubscribeParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<boost::json::value>(
            client_, "userDataStream.unsubscribe", user_data_stream_unsubscribe_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params
    session_subscriptions_payload(const SessionSubscriptionsParams& params);
    [[nodiscard]] static common::Params
    user_data_stream_subscribe_payload(const UserDataStreamSubscribeParams& params);
    [[nodiscard]] static common::Params user_data_stream_subscribe_signature_payload(
        const UserDataStreamSubscribeSignatureParams& params);
    [[nodiscard]] static common::Params
    user_data_stream_unsubscribe_payload(const UserDataStreamUnsubscribeParams& params);
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
