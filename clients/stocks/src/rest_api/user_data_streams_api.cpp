//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/user_data_streams_api.hpp>

namespace binance::stocks::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

UserDataStreamsApi::UserDataStreamsApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest UserDataStreamsApi::create_renew_listen_key_request(
    const CreateRenewListenKeyParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/listenKey";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<CreateRenewListenKeyResponse>
UserDataStreamsApi::create_renew_listen_key(const CreateRenewListenKeyParams& params) const {
    return common::send<CreateRenewListenKeyResponse>(*client_,
                                                      create_renew_listen_key_request(params));
}

} // namespace binance::stocks::rest_api
