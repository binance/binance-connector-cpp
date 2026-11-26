//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/keepalive_user_data_stream_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/start_user_data_stream_response.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT UserDataStreamsApi {
public:
    explicit UserDataStreamsApi(std::shared_ptr<common::RestClient> client);

    /// Close User Data Stream (USER_STREAM)
    ///
    /// DELETE /dapi/v1/listenKey.
    ///
    /// Close out a user data stream.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/user-data-streams#close-user-data-stream
    [[nodiscard]] common::RestApiResponse<boost::json::value> close_user_data_stream() const;

    /// Asynchronous `close_user_data_stream()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_close_user_data_stream(CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_, close_user_data_stream_request(),
                                                      std::forward<CompletionToken>(token));
    }

    /// Keepalive User Data Stream (USER_STREAM)
    ///
    /// PUT /dapi/v1/listenKey.
    ///
    /// Keepalive a user data stream to prevent a time out. User data streams
    /// will close after 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/user-data-streams#keepalive-user-data-stream
    [[nodiscard]] common::RestApiResponse<KeepaliveUserDataStreamResponse>
    keepalive_user_data_stream() const;

    /// Asynchronous `keepalive_user_data_stream()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<KeepaliveUserDataStreamResponse>)`.
    template <class CompletionToken>
    auto async_keepalive_user_data_stream(CompletionToken&& token) const {
        return common::async_send<KeepaliveUserDataStreamResponse>(
            client_, keepalive_user_data_stream_request(), std::forward<CompletionToken>(token));
    }

    /// Start User Data Stream (USER_STREAM)
    ///
    /// POST /dapi/v1/listenKey.
    ///
    /// Start a new user data stream. The stream will close after 60 minutes
    /// unless a keepalive is sent. If the account has an active `listenKey`,
    /// that `listenKey` will be returned and its validity will be extended for
    /// 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/user-data-streams#start-user-data-stream
    [[nodiscard]] common::RestApiResponse<StartUserDataStreamResponse>
    start_user_data_stream() const;

    /// Asynchronous `start_user_data_stream()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<StartUserDataStreamResponse>)`.
    template <class CompletionToken>
    auto async_start_user_data_stream(CompletionToken&& token) const {
        return common::async_send<StartUserDataStreamResponse>(
            client_, start_user_data_stream_request(), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest close_user_data_stream_request() const;
    [[nodiscard]] common::RestRequest keepalive_user_data_stream_request() const;
    [[nodiscard]] common::RestRequest start_user_data_stream_request() const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_coin_futures::rest_api
