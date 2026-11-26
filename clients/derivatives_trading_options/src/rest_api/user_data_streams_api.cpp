//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/user_data_streams_api.hpp>

namespace binance::derivatives_trading_options::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

UserDataStreamsApi::UserDataStreamsApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest UserDataStreamsApi::close_user_data_stream_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/eapi/v1/listenKey";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<boost::json::value> UserDataStreamsApi::close_user_data_stream() const {
    return common::send<boost::json::value>(*client_, close_user_data_stream_request());
}

common::RestRequest UserDataStreamsApi::keepalive_user_data_stream_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/eapi/v1/listenKey";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<boost::json::value> UserDataStreamsApi::keepalive_user_data_stream() const {
    return common::send<boost::json::value>(*client_, keepalive_user_data_stream_request());
}

common::RestRequest UserDataStreamsApi::start_user_data_stream_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/listenKey";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<StartUserDataStreamResponse>
UserDataStreamsApi::start_user_data_stream() const {
    return common::send<StartUserDataStreamResponse>(*client_, start_user_data_stream_request());
}

} // namespace binance::derivatives_trading_options::rest_api
