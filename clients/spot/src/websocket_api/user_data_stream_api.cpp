//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/user_data_stream_api.hpp>

namespace binance::spot::websocket_api {

UserDataStreamApi::UserDataStreamApi(std::shared_ptr<common::WebsocketApi> client)
    : client_(std::move(client)) {}

common::Params
UserDataStreamApi::session_subscriptions_payload(const SessionSubscriptionsParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return p;
}

common::WebsocketApiResponse<std::vector<SessionSubscriptionsResponseResultInner>>
UserDataStreamApi::session_subscriptions(const SessionSubscriptionsParams& params) const {
    return common::send<std::vector<SessionSubscriptionsResponseResultInner>>(
        *client_, "session.subscriptions", session_subscriptions_payload(params),
        make_options(false, false, false, false));
}

common::Params
UserDataStreamApi::user_data_stream_subscribe_payload(const UserDataStreamSubscribeParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "filter", params.filter);
    return p;
}

common::WebsocketApiSubscription<UserDataStreamSubscribeResponseResult,
                                 UserDataStreamEventsResponse>
UserDataStreamApi::user_data_stream_subscribe(const UserDataStreamSubscribeParams& params) const {
    return common::subscribe<UserDataStreamSubscribeResponseResult, UserDataStreamEventsResponse>(
        *client_, "userDataStream.subscribe", user_data_stream_subscribe_payload(params),
        make_options(false, false, false, false));
}

common::Params UserDataStreamApi::user_data_stream_subscribe_signature_payload(
    const UserDataStreamSubscribeSignatureParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    common::detail::json::set_param(p, "filter", params.filter);
    return p;
}

common::WebsocketApiSubscription<UserDataStreamSubscribeResponseResult,
                                 UserDataStreamEventsResponse>
UserDataStreamApi::user_data_stream_subscribe_signature(
    const UserDataStreamSubscribeSignatureParams& params) const {
    return common::subscribe<UserDataStreamSubscribeResponseResult, UserDataStreamEventsResponse>(
        *client_, "userDataStream.subscribe.signature",
        user_data_stream_subscribe_signature_payload(params),
        make_options(false, true, false, false));
}

common::Params UserDataStreamApi::user_data_stream_unsubscribe_payload(
    const UserDataStreamUnsubscribeParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "subscriptionId", params.subscription_id);
    return p;
}

common::WebsocketApiResponse<boost::json::value> UserDataStreamApi::user_data_stream_unsubscribe(
    const UserDataStreamUnsubscribeParams& params) const {
    return common::send<boost::json::value>(*client_, "userDataStream.unsubscribe",
                                            user_data_stream_unsubscribe_payload(params),
                                            make_options(false, false, false, false));
}

} // namespace binance::spot::websocket_api
