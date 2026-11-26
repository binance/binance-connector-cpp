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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/websocket_api.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/keepalive_user_data_stream_response_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/start_user_data_stream_response_result.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct CloseUserDataStreamParams {
    /// Id.
    std::optional<std::string> id = std::nullopt;
};

struct KeepaliveUserDataStreamParams {
    /// Id.
    std::optional<std::string> id = std::nullopt;
};

struct StartUserDataStreamParams {
    /// Id.
    std::optional<std::string> id = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT UserDataStreamsApi {
public:
    explicit UserDataStreamsApi(std::shared_ptr<common::WebsocketApi> client);

    /// Close User Data Stream (USER_STREAM)
    ///
    /// `userDataStream.stop`.
    ///
    /// Close out a user data stream.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/user-data-streams#close-user-data-stream
    [[nodiscard]] common::WebsocketApiResponse<boost::json::value>
    close_user_data_stream(const CloseUserDataStreamParams& params = {}) const;

    /// Asynchronous `close_user_data_stream()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_close_user_data_stream(const CloseUserDataStreamParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<boost::json::value>(
            client_, "userDataStream.stop", close_user_data_stream_payload(params),
            make_options(true, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Keepalive User Data Stream (USER_STREAM)
    ///
    /// `userDataStream.ping`.
    ///
    /// Keepalive a user data stream to prevent a time out. User data streams will close after 60
    /// minutes. It's recommended to send a ping about every 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/user-data-streams#keepalive-user-data-stream
    [[nodiscard]] common::WebsocketApiResponse<KeepaliveUserDataStreamResponseResult>
    keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params = {}) const;

    /// Asynchronous `keepalive_user_data_stream()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<KeepaliveUserDataStreamResponseResult>)`.
    template <class CompletionToken>
    auto async_keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<KeepaliveUserDataStreamResponseResult>(
            client_, "userDataStream.ping", keepalive_user_data_stream_payload(params),
            make_options(true, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Start User Data Stream (USER_STREAM)
    ///
    /// `userDataStream.start`.
    ///
    /// Start a new user data stream. The stream will close after 60 minutes unless a keepalive is
    /// sent. If the account has an active `listenKey`, that `listenKey` will be returned and its
    /// validity will be extended for 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/user-data-streams#start-user-data-stream
    [[nodiscard]] common::WebsocketApiResponse<StartUserDataStreamResponseResult>
    start_user_data_stream(const StartUserDataStreamParams& params = {}) const;

    /// Asynchronous `start_user_data_stream()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<StartUserDataStreamResponseResult>)`.
    template <class CompletionToken>
    auto async_start_user_data_stream(const StartUserDataStreamParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<StartUserDataStreamResponseResult>(
            client_, "userDataStream.start", start_user_data_stream_payload(params),
            make_options(true, false, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params
    close_user_data_stream_payload(const CloseUserDataStreamParams& params);
    [[nodiscard]] static common::Params
    keepalive_user_data_stream_payload(const KeepaliveUserDataStreamParams& params);
    [[nodiscard]] static common::Params
    start_user_data_stream_payload(const StartUserDataStreamParams& params);
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

} // namespace binance::derivatives_trading_usds_futures::websocket_api
