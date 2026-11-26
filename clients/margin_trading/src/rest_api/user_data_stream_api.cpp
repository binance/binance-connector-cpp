//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/user_data_stream_api.hpp>

namespace binance::margin_trading::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

UserDataStreamApi::UserDataStreamApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest UserDataStreamApi::close_user_data_stream_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/margin/listen-key";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<boost::json::value> UserDataStreamApi::close_user_data_stream() const {
    return common::send<boost::json::value>(*client_, close_user_data_stream_request());
}

common::RestRequest UserDataStreamApi::keepalive_user_data_stream_request(
    const KeepaliveUserDataStreamParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/sapi/v1/margin/listen-key";
    common::detail::json::set_param(req.query, "listenKey", params.listen_key);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<boost::json::value>
UserDataStreamApi::keepalive_user_data_stream(const KeepaliveUserDataStreamParams& params) const {
    return common::send<boost::json::value>(*client_, keepalive_user_data_stream_request(params));
}

common::RestRequest UserDataStreamApi::start_user_data_stream_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/listen-key";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<StartUserDataStreamResponse>
UserDataStreamApi::start_user_data_stream() const {
    return common::send<StartUserDataStreamResponse>(*client_, start_user_data_stream_request());
}

common::RestRequest UserDataStreamApi::close_user_data_stream_v2_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v2/margin/listen-key";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<boost::json::value> UserDataStreamApi::close_user_data_stream_v2() const {
    return common::send<boost::json::value>(*client_, close_user_data_stream_v2_request());
}

common::RestRequest UserDataStreamApi::keepalive_user_data_stream_v2_request(
    const KeepaliveUserDataStreamV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/sapi/v2/margin/listen-key";
    common::detail::json::set_param(req.query, "listenKey", params.listen_key);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<boost::json::value> UserDataStreamApi::keepalive_user_data_stream_v2(
    const KeepaliveUserDataStreamV2Params& params) const {
    return common::send<boost::json::value>(*client_,
                                            keepalive_user_data_stream_v2_request(params));
}

common::RestRequest UserDataStreamApi::start_user_data_stream_v2_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v2/margin/listen-key";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<StartUserDataStreamV2Response>
UserDataStreamApi::start_user_data_stream_v2() const {
    return common::send<StartUserDataStreamV2Response>(*client_,
                                                       start_user_data_stream_v2_request());
}

} // namespace binance::margin_trading::rest_api
