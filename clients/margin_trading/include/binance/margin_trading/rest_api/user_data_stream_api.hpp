//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <string>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/start_user_data_stream_response.hpp>
#include <binance/margin_trading/rest_api/models/start_user_data_stream_v2_response.hpp>

namespace binance::margin_trading::rest_api {

struct KeepaliveUserDataStreamParams {
    common::Required<std::string> listen_key;
};

struct KeepaliveUserDataStreamV2Params {
    common::Required<std::string> listen_key;
};

class BINANCE_MARGIN_TRADING_EXPORT UserDataStreamApi {
public:
    explicit UserDataStreamApi(std::shared_ptr<common::RestClient> client);

    /// Close User Data Stream (USER_STREAM)
    ///
    /// DELETE /sapi/v1/margin/listen-key.
    ///
    /// Close out a user data stream.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#close-user-data-stream
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
    /// PUT /sapi/v1/margin/listen-key.
    ///
    /// Keepalive a user data stream to prevent a time out.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#keepalive-user-data-stream
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params) const;

    /// Asynchronous `keepalive_user_data_stream()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_,
                                                      keepalive_user_data_stream_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Start User Data Stream (USER_STREAM)
    ///
    /// POST /sapi/v1/margin/listen-key.
    ///
    /// Start a new user data stream.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#start-user-data-stream
    [[nodiscard]] common::RestApiResponse<StartUserDataStreamResponse>
    start_user_data_stream() const;

    /// Asynchronous `start_user_data_stream()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<StartUserDataStreamResponse>)`.
    template <class CompletionToken>
    auto async_start_user_data_stream(CompletionToken&& token) const {
        return common::async_send<StartUserDataStreamResponse>(
            client_, start_user_data_stream_request(), std::forward<CompletionToken>(token));
    }

    /// Close User Data Stream V2 (USER_STREAM)
    ///
    /// DELETE /sapi/v2/margin/listen-key.
    ///
    /// Close out a user data stream.
    ///
    /// **Note:** After this request, you will receive another WebSocket message:
    ///
    /// ```json
    /// {
    ///   "e": "eventStreamTerminated",
    ///   "E": 1793646860552
    /// }
    /// ```
    ///
    /// - `e` (string): event type. Example: `eventStreamTerminated`
    /// - `E` (integer): current timestamp. Example: `1793646860552`
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#close-user-data-stream-v2
    [[nodiscard]] common::RestApiResponse<boost::json::value> close_user_data_stream_v2() const;

    /// Asynchronous `close_user_data_stream_v2()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_close_user_data_stream_v2(CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_, close_user_data_stream_v2_request(),
                                                      std::forward<CompletionToken>(token));
    }

    /// Keepalive User Data Stream V2 (USER_STREAM)
    ///
    /// PUT /sapi/v2/margin/listen-key.
    ///
    /// Keep alive a user data stream to prevent a timeout. Each successful request extends the
    /// listen key validity for 1 hour.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#keepalive-user-data-stream-v2
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    keepalive_user_data_stream_v2(const KeepaliveUserDataStreamV2Params& params) const;

    /// Asynchronous `keepalive_user_data_stream_v2()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_keepalive_user_data_stream_v2(const KeepaliveUserDataStreamV2Params& params,
                                             CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_,
                                                      keepalive_user_data_stream_v2_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Start User Data Stream V2 (USER_STREAM)
    ///
    /// POST /sapi/v2/margin/listen-key.
    ///
    /// Start a new user data stream.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/user-data-stream#start-user-data-stream-v2
    [[nodiscard]] common::RestApiResponse<StartUserDataStreamV2Response>
    start_user_data_stream_v2() const;

    /// Asynchronous `start_user_data_stream_v2()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<StartUserDataStreamV2Response>)`.
    template <class CompletionToken>
    auto async_start_user_data_stream_v2(CompletionToken&& token) const {
        return common::async_send<StartUserDataStreamV2Response>(
            client_, start_user_data_stream_v2_request(), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest close_user_data_stream_request() const;
    [[nodiscard]] common::RestRequest
    keepalive_user_data_stream_request(const KeepaliveUserDataStreamParams& params) const;
    [[nodiscard]] common::RestRequest start_user_data_stream_request() const;
    [[nodiscard]] common::RestRequest close_user_data_stream_v2_request() const;
    [[nodiscard]] common::RestRequest
    keepalive_user_data_stream_v2_request(const KeepaliveUserDataStreamV2Params& params) const;
    [[nodiscard]] common::RestRequest start_user_data_stream_v2_request() const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::margin_trading::rest_api
