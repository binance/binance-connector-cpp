//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/user_data_streams_api.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

UserDataStreamsApi::UserDataStreamsApi(std::shared_ptr<common::WebsocketApi> client)
    : client_(std::move(client)) {}

common::Params
UserDataStreamsApi::close_user_data_stream_payload(const CloseUserDataStreamParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return p;
}

common::WebsocketApiResponse<boost::json::value>
UserDataStreamsApi::close_user_data_stream(const CloseUserDataStreamParams& params) const {
    return common::send<boost::json::value>(*client_, "userDataStream.stop",
                                            close_user_data_stream_payload(params),
                                            make_options(true, false, false, false));
}

common::Params UserDataStreamsApi::keepalive_user_data_stream_payload(
    const KeepaliveUserDataStreamParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return p;
}

common::WebsocketApiResponse<KeepaliveUserDataStreamResponseResult>
UserDataStreamsApi::keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params) const {
    return common::send<KeepaliveUserDataStreamResponseResult>(
        *client_, "userDataStream.ping", keepalive_user_data_stream_payload(params),
        make_options(true, false, false, false));
}

common::Params
UserDataStreamsApi::start_user_data_stream_payload(const StartUserDataStreamParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return p;
}

common::WebsocketApiResponse<StartUserDataStreamResponseResult>
UserDataStreamsApi::start_user_data_stream(const StartUserDataStreamParams& params) const {
    return common::send<StartUserDataStreamResponseResult>(*client_, "userDataStream.start",
                                                           start_user_data_stream_payload(params),
                                                           make_options(true, false, false, false));
}

} // namespace binance::derivatives_trading_coin_futures::websocket_api
